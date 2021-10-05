#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
using namespace std;

struct card{
	int id;
	string name;
	int attack;
	int hp;
	int cost;
	int type; //0 - minion
};

void controls_panel(int state)
{
	if(state==0){
		cout << "    -               -          select" << endl;
		cout << "    -               -             E" << endl;
	}
	else if(state==1){
		cout << "move cursor       cancel       select" << endl;
		cout << " A <-> D             Q            E" << endl;
	}
	else if(state==2){
		cout << "move cursor        pass        select" << endl;
		cout << " A <-> D             Q            E" << endl;
	}
	else if(state==3 || state==4){
		cout << "    -               -          continue" << endl;
		cout << "    -               -             E" << endl;
	}
}

bool read_cards(card * Z, int & card_amount, string filename)
{
	card_amount=0;
	ifstream deck_file;
	deck_file.open( filename.c_str() );
	if(!deck_file.good()) return false;
	
	while(true)
	{
		Z[card_amount].id = card_amount;
		deck_file >> Z[card_amount].name >> Z[card_amount].attack >> Z[card_amount].hp >> Z[card_amount].cost >> Z[card_amount].type;
		
		if(deck_file.fail()) break;
		card_amount++;
	}
	return true;
	
}

void draw_panel(string message)
{
	if(message!="")
	{
		cout << "   >>> " << message << endl;
	}
	else
	{
		cout << endl;
	}
	cout << "-----------------------------------------------------------------------------" << endl;
}

void draw_enemy(int cards, int ehp, int emana, int emaxmana)
{
	cout << setw(10) << "YOUR ENEMY" << setw(10) << " " << setw(7) << "#######" << setw(10) << "MANA: " << emana << "/" << emaxmana << endl;
	cout << setw(20) << " " << setw(7) << "#  O  #" << setw(10) << "HP: " << ehp << endl;
	cout << setw(20) << " " << setw(7) << "# / \\ #" << setw(10) << "CARDS: ";
	for(int i=0; i<cards; i++) cout << "[x]";
	cout << endl << setw(20) << " " << setw(7) << "#######" << endl;
}

//####################################################################################################
//DRAW BOARD        DRAW BOARD        DRAW BOARD        DRAW BOARD        DRAW BOARD        DRAW BOARD 
void draw_board(card * eboard_u, card * eboard_d, card * pboard_u, card * pboard_d, int state, int selector, int combatloop)
{
	cout << "=============================================================================" << endl;
	cout << "|";
	//draw enemy up
	for(int i=0; i<4; i++) 
	{
		if(eboard_u[i].id==-1)
		{
			if(state==4 && combatloop==i)
				cout << setw(19) << "*                *|";
			else
				cout << setw(19) << "|";
		}
		else
		{
			if(state==4 && combatloop==i)
				cout << "*" << setw(2) <<eboard_u[i].attack  << setw(11) << eboard_u[i].name << " " << setw(2) << eboard_u[i].hp << "*|";
			else
				cout << "(" << setw(2)<<eboard_u[i].attack  << setw(11) << eboard_u[i].name << " " << setw(2) << eboard_u[i].hp << ")|";
		}
	}
	cout <<endl<< "|";
	
	//draw enemy down
	for(int i=0; i<4; i++) 
	{
		if(eboard_d[i].id==-1)
		{
			if(state==4 && combatloop==i)
				cout << setw(19) << "*                *|";
			else
				cout << setw(19) << "|";
		}
		else
		{
			if(state==4 && combatloop==i)
				cout << "*" << setw(2)  <<eboard_d[i].attack << setw(11) << eboard_d[i].name << " " << setw(2) << eboard_d[i].hp << "*|";
			else
				cout << "(" << setw(2)  <<eboard_d[i].attack << setw(11) << eboard_d[i].name << " " << setw(2) << eboard_d[i].hp << ")|";
		}
	}
	
	cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	
	//draw player down
	cout << "|";
	for(int i=0; i<4; i++) 
	{
		if(pboard_d[i].id==-1)
		{
			if(state==4 && combatloop==i)
				cout << setw(19) << "*                *|";
			else
				cout << setw(19) << "|";
		}
		else
		{
			if(state==4 && combatloop==i)
				cout << "*" << setw(2)  <<pboard_d[i].attack << setw(11) << pboard_d[i].name <<" " <<  setw(2) << pboard_d[i].hp << "*|";
			else
				cout << "(" << setw(2)<< pboard_d[i].attack  << setw(11) << pboard_d[i].name << " " << setw(2) << pboard_d[i].hp << ")|";
		}
	}
	cout << endl;
	//if state is 1 draw selector below bottom lane
	if(state==1){
		for(int i=0; i<selector;i++) cout << setw(19) << " ";
		cout<< setw(19) << "^^^^^^^^^^^^^^^^^^" << endl;
	}
	
	
	//draw player up
	cout << "|";
	for(int i=0; i<4; i++) 
	{
		if(pboard_u[i].id==-1)
		{
			if(state==4 && combatloop==i)
				cout << setw(19) << "*                *|";
			else
				cout << setw(19) << "|";
		}
		else
		{
			if(state==4 && combatloop==i)
				cout << "*" << setw(2)  <<pboard_u[i].attack << setw(11) << pboard_u[i].name <<" " <<  setw(2) << pboard_u[i].hp << "*|";
			else
				cout << "(" << setw(2)  <<pboard_u[i].attack << setw(11) << pboard_u[i].name <<" " <<  setw(2) << pboard_u[i].hp << ")|";
		}
	}
	
	if(state!=1 && state != 4) cout << endl;
	if(state==4)
	{
		cout << endl;
		for(int i=0; i<combatloop; i++) 
			cout << setw(19) << " ";
		cout << setw(19) <<"******************";
	}
	
	cout << endl;
	cout << "=============================================================================" << endl;
	
}

void draw_card(card * Z, card * hand, int cards, int Zlen)
{
	for(int i=0; i<cards; i++)
	{
		if(hand[i].id==-1){
			hand[i] = Z[rand()%Zlen];
			return;
		}
	}
}

void draw_player(int cards, card * phand, int pmana, int pmaxmana, int php, int state, int cselector)
{
	cout << setw(10) << "PLAYER" << setw(10) << " " << setw(7) << "#######" << setw(10) << "MANA: " << pmana << "/" << pmaxmana << endl;
	cout << setw(20) << " " << setw(7) << "#  O  #" << setw(10) << "HP: " << php << endl;
	cout << setw(20) << " " << setw(7) << "# / \\ #" << setw(10) << "CARDS: ";
	
	for(int i=0; i<cards; i++) 
	{
		if(i!=cselector)
			cout << "[x]";
		else
			cout << "[{" << setw(2) << phand[i].cost  <<"}     ]";
	}
	
	cout << endl << setw(20) << " " << setw(7) << "#######" << setw(10) <<" ";
	
	for(int i=0; i<cards; i++) 
	{
		if(i!=cselector)
			cout << "   ";
		else
			cout << "|<" << setw(2) <<  phand[i].attack  <<  "> (" << setw(2) << phand[i].hp <<")|";
	}
	cout << endl << setw(37) << " ";
	for(int i=0; i<cards; i++) 
	{
		if(i!=cselector)
			cout << "   ";
		else
			cout << "[" << setw(9) << phand[i].name <<"]";
	}
	
	cout << endl << endl;
}

void sort_hand(card * hand, int cards, int spot)
{
	//move cards next to played card
	for(int i=spot; i<cards-1; i++)
	{
		hand[i]=hand[i+1];
	}
	hand[cards-1].id=-1;
}

int main()
{
	int card_amount;
	card * Z = new card[100];
	
	srand(time(NULL));
	
	//read cards from file
	if(!read_cards(Z, card_amount, "deck.txt"))
		cout << "Error. Can't read card data file'." << endl;
	else
		cout << "Loaded " << card_amount << " cards." << endl;
	
	//initialize variables
	int combatloop=0;
	bool playerpass=false;
	string topmessage="Welcome both players! Time for a d-d-d-d-duel.";
	
	int state=2; 
	//state:
	//0 - informative loop, press select to continue
	//1 - user is selecting where to place card on board
	//2 - user is selecting card from his hand
	//3 - enemy turn
	//4 - combat turn
	
	int selector=0; //cursor of player when selecting card spot
	int cselector=0; //card cursor which is separate so it remembers position
	int round=1; //round count
	//player and enemy initial hand card count
	int enemy_cards=5;
	int player_cards=5;
	char input;
	int php=20; //player and enemy hp
	int ehp=20;
	int pmana = 1; //player and enemy mana
	int emana = 1;
	int pmaxmana = 1;
	int emaxmana = 1;
	card player_hand[11]; //player and enemy's hand
	card enemy_hand[11];
	
	//board state - what cards are placed on the board
	card eboard_u[4];
	card pboard_u[4];
	
	card eboard_d[4];
	card pboard_d[4];
	
	//fill empty
	for(int i=0; i<10; i++) player_hand[i].id=-1;
	for(int i=0; i<10; i++) enemy_hand[i].id=-1;
	
	//give initial cards to players
	for(int i=0; i<player_cards; i++) draw_card(Z, player_hand, player_cards, card_amount);
	for(int i=0; i<enemy_cards; i++) draw_card(Z, enemy_hand, enemy_cards, card_amount);
	
	for(int i=0; i<4; i++) {pboard_u[i].id=-1;pboard_d[i].id=-1;}
	for(int i=0; i<4; i++) {eboard_u[i].id=-1;eboard_d[i].id=-1;}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////// testing hands
	//eboard_d[2]=Z[5];
	
	//player_hand[4]=Z[4];
	
	//game loop
	while(true)
	{
		system("clear");
		if(state==1)topmessage = "Select where do you want to place this card or cancel.";
		
		
		
		draw_panel(topmessage);
		topmessage="";
		
		//enemy panel
		draw_enemy(enemy_cards, ehp, emana, emaxmana);
		
		//board panel
		draw_board(eboard_u, eboard_d, pboard_u, pboard_d, state, selector, combatloop);
		
		//player panel
		draw_player(player_cards, player_hand, pmana, pmaxmana, php, state, cselector);
		
		controls_panel(state);
		cin >> input;
		
		
		//mechanisms
		//######################################################################################
		//SELECTING SPOT      SELECTING SPOT      SELECTING SPOT      SELECTING SPOT         
		if(state==0){
			break;
		}
		else if(state==1)
		{
			if(input=='a' || input == 'A')
			{
				selector--;
				if(selector<0) selector=0;
			}
			else if(input=='d' || input == 'D')
			{
				selector++;
				if(selector>3) selector=3;
			}
			else if(input=='q' || input == 'Q')
			{
				state=2;
			}
			else if(input=='e' || input == 'E')
			{
				pboard_d[selector]=player_hand[cselector];
				pmana -= player_hand[cselector].cost;
				player_hand[cselector].id=-1;
				sort_hand(player_hand, player_cards, cselector);
				player_cards--;
				if(cselector>player_cards-1) cselector=player_cards-1;
				topmessage = "Player plays " + pboard_d[selector].name;
				state=3;
			}
			else
				topmessage = "Unknown input.";
		}
		//######################################################################################
		//SELECTING CARD    SELECTING CARD    SELECTING CARD    SELECTING CARD    SELECTING CARD  
		else if(state==2)
		{
			if(input=='a' || input == 'A')
			{
				cselector--;
				if(cselector<0) cselector=0;
			}
			else if(input=='d' || input == 'D')
			{
				cselector++;
				if(cselector>=player_cards) cselector=player_cards-1;
			}
			else if(input=='q' || input == 'Q')
			{
				playerpass=true;
				state=3;
			}
			else if(input=='e' || input == 'E')
			{
				if(pmana<player_hand[cselector].cost) topmessage="Not enough mana to play this card!";
				else 
				{
					state=1;
				}
			}
			else
				topmessage = "Unknown input.";
		}
		//##########################################################################################
		//ENEMY TURN      ENEMY TURN      ENEMY TURN      ENEMY TURN      ENEMY TURN      ENEMY TURN      
		else if(state==3)
		{
			if(input=='e' || input=='E')
			{
				bool canplay=false;
				bool wascardplayed=false;
				bool enemypass=false;
				int ei=0;
				//search for first card possible to play
				//if there are free spots - defend first
				//if there are no free spots check if it's valuable to replace any minion
				//if it's not valuable - search for next card and eventually pass
				//if it's valuable to replace any minion - replace first found minion that's valuable to replace
				while(ei<enemy_cards)
				{
					for(; ei<enemy_cards; ei++)
						if(enemy_hand[ei].cost<=emana)
						{
							canplay=true;
							break;
						}
					
					if(canplay)
					{
						//check if there are free spots where player has cards
						for(int i=0; i<4; i++)
						{
							if(eboard_d[i].id==-1 && pboard_d[i].id!=-1)
							{
								//there are! find the spot with greatest attack
								int maxplayerattackpos=i;
								for(int j=i; j<4; j++)
								{
									if(pboard_d[j].id!=-1 && pboard_d[j].attack>pboard_d[maxplayerattackpos].attack) maxplayerattackpos=j;
								}
								//play card
								eboard_d[maxplayerattackpos]=enemy_hand[ei];
								emana-=enemy_hand[ei].cost;
								enemy_hand[ei].id=-1;
								enemy_cards--;
								sort_hand(enemy_hand, enemy_cards, ei);
								wascardplayed=true;
								topmessage = "Enemy played card: " + eboard_d[maxplayerattackpos].name ;
							}
						}
						if(!wascardplayed) //if there was no card played search again for any free spots
						{
							for(int i=0; i<4; i++)
							{
								if(eboard_d[i].id==-1) //found free spot! will play card
								{
									eboard_d[i]=enemy_hand[ei];
									emana-=enemy_hand[ei].cost;
									enemy_hand[ei].id=-1;
									enemy_cards--;
									sort_hand(enemy_hand, enemy_cards, ei);
									wascardplayed=true;
									topmessage = "Enemy played card: " + eboard_d[i].name ;
									break;
								}
							}
						}
						if(!wascardplayed)	 //if there was no card played it means there were no free spots at all
						{
							//we need to find if there are any valuable replacements
							//valuable means that card in hand has more health or is more expensive
							for(int i=0; i<4; i++)
							{
								if(eboard_d[i].cost<enemy_hand[ei].cost || enemy_hand[ei].hp>eboard_d[i].hp)
								{
									//conditions met - play the card
									eboard_d[i]=enemy_hand[ei];
									emana-=enemy_hand[ei].cost;
									enemy_hand[ei].id=-1;
									enemy_cards--;
									sort_hand(enemy_hand, enemy_cards, ei);
									wascardplayed=true;
									topmessage = "Enemy played card: " + eboard_d[i].name;
									break;
								}
							}
						}
							
							
							
						
					}

				
					if(wascardplayed || !canplay || ei>=enemy_cards) 
					{
						enemypass=true;
						break;
					}
					ei++;
				}
				
				
				if(enemypass==true && playerpass==true) //both players passed - time for combat
				{
					state = 4;
					enemypass=false;
					playerpass=false;
					topmessage = "Both players passed. Time for combat!";
				}  
				else if(enemypass==true && !wascardplayed && playerpass==false)
				{
					state = 2;
					topmessage = "Enemy passed. Your turn.";
				}
				else if(enemypass==true && wascardplayed && playerpass == false)
				{
					state = 2;
					topmessage = topmessage + " Your turn.";
				}
				else if(enemypass==true && wascardplayed && playerpass == true)
				{
					state = 2;
				}
			}
			else
				topmessage = "Unknown input.";
			
		}
		else if(state==4)
		{
			//combat turn - lanes from left to right fight each other. 
			if(input=='e' || input=='E' || input=='d' || input=='D')
			{
				int enemydamage = 0;
				int playerdamage = 0;
				bool miniondied = false;
				
				//check if there are minions on both sides
				if(eboard_d[combatloop].id!=-1 && pboard_d[combatloop].id!=-1)
				{
					//there are. make them fight.
					eboard_d[combatloop].hp-=pboard_d[combatloop].attack;
					pboard_d[combatloop].hp-=eboard_d[combatloop].attack;
					
					//check if they are destroyed
					if(eboard_d[combatloop].hp<=0)
					{
						//check if there was some card already on upper lane
						if(eboard_u[combatloop].id!=-1)
						{
							//deal according damage
							ehp -= eboard_u[combatloop].attack;
							enemydamage=eboard_u[combatloop].attack;
						}
						
						//move the new card up and set the id of bottom one to -1
						eboard_d[combatloop].hp=0;
						eboard_u[combatloop] = eboard_d[combatloop];
						eboard_d[combatloop].id=-1;
						miniondied=true;
					}
					
					if(pboard_d[combatloop].hp<=0)
					{
						//check if there was some card already on upper lane
						if(pboard_u[combatloop].id!=-1)
						{
							//deal according damage
							php -= pboard_u[combatloop].attack;
							playerdamage=pboard_u[combatloop].attack;
						}
						
						//move the new card up and set the id of bottom one to -1
						pboard_d[combatloop].hp=0;
						pboard_u[combatloop] = pboard_d[combatloop];
						pboard_d[combatloop].id=-1;
						miniondied=true;
					}
					
				}
				else if(eboard_d[combatloop].id!=-1 && pboard_d[combatloop].id==-1) //check if minion was on enemy side only
				{
					//deal direct damage
					php-=eboard_d[combatloop].attack;
					playerdamage=eboard_d[combatloop].attack;
				}
				else if(pboard_d[combatloop].id!=-1 && eboard_d[combatloop].id==-1) //check for the opposite
				{
					//deal direct damage
					ehp-=pboard_d[combatloop].attack;
					enemydamage=pboard_d[combatloop].attack;
				}
				
				//issue detailed info from narrator
				bool anymessage=false;
				if(playerdamage > 0) {
					topmessage = "Player took " + to_string(playerdamage) + " damage. ";
					anymessage=true;
				}
				if(enemydamage > 0) 
				{
					topmessage = topmessage + "Enemy took " + to_string(enemydamage) + " damage. ";
					anymessage=true;
				}
				if(miniondied) {
					topmessage = topmessage + "Some minions didn't make it...";
					anymessage=true;
				}
				
				if(!anymessage)
					topmessage = "There was no damage taken here.";
				
				if(combatloop<3) combatloop++;
				else
				{
					combatloop=0;
					round++;
					state=2;
					pmaxmana++;
					emaxmana++;
					pmana=pmaxmana;
					emana=emaxmana;
					topmessage = "Round " + to_string(round) + " begins!";
					
					//give one card to each player
					if(player_cards<10) 
					{
						player_cards++;
						draw_card(Z, player_hand, player_cards, card_amount);
					}
					if(enemy_cards<10)
					{
						enemy_cards++;
						draw_card(Z, enemy_hand, enemy_cards, card_amount);
					}
					
				}
			}
			else
				topmessage = "Unknown input.";
		}
		
		if(php<=0 && ehp<=0)
		{
			state=0;
			topmessage="Now that's what I'm talking about! IT'S A DRAW!!!!!";
		}
		else if(php<=0 && ehp>0)
		{
			state=0;
			topmessage="Well... You LOSE!";
		}
		else if(php>0 && ehp<=0)
		{
			state=0;
			topmessage="Congratulations! You win!";
		}
	}
	
	system("clear");
	cout << "The end. Thank you." << endl;
	
	
	delete[] Z;
	return 0;
}

# cards
Tiny text based c++ card game I made in one day. You can create own unit cards for the game, the process is explained later.

# how to play

Compile core.cpp and place deck.txt in the same folder as the executable file.

# screens

![Welcome screen](https://github.com/rr-adam/cpp-card-game/blob/main/scr1.png?raw=true "Welcome screen")

![Placing card screen](https://github.com/rr-adam/cpp-card-game/blob/main/scr2%20placing%20card.png?raw=true "Placing card screen")

![Combat screen](https://github.com/rr-adam/cpp-card-game/blob/main/scr3%20combat.png?raw=true "Combat screen")


# rules
Your goal is to bring your opponent's health points (HP) to 0. You need to keep your HP above 0 too.
In the game players play cards one after another. Players can pass playing a card. They have to pass when they don't have card to play.

Players have their mana pool which enables them to play cards. Each card has mana cost. When player plays a card, his mana is lowered by the card's cost.

The board consists of 4 vertical lanes. Both players have two rows in each lane: inner and ouuter one. The inner one is where player places cards. Cards in inner lane fight during combat phase. If there is no card in enemy's inner lane you hit them directly with the card's damage. Otherwise cards deal damage to each other.
The outter lane is a graveyard. When card dies in inner lane they move to graveyard lane. If there was another card in graveyard new card pushes the old one out, the old card deals damage to you.

It's easier to understand when you just play the game.

# making own cards
In deck.txt each line a is different card. You can delete and add new cards, both players use the same deck.

<name (max 11 characters)> <attack> <hp> <cost> <type>
the type is just there so that it's possible to create "magic" cards instead just units. set the type to 0.
cost - man cost of the unit, the rest is self explanatory.

# bugs
There's a rare bug where enemy can place a card with cost higher than enemy's max mana.
# cpp-card-game

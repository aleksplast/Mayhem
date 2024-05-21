# Mayhem
Trivial card game project
## Requirements
1. nlohmann/json
2. SFML
3. gRPC (1.62.2)
4. protobuf (26.1.0)
5. gtest (only if you want to perform test, see below)
## Build and Run
```sh
pushd src/proto
protoc --cpp_out=. --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./engine.proto
popd
mkdir build
cd build
cmake .. (if you installed gRPC into some $INSTALL_DIR, run cmake .. -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR)
make
./game [offline/online] [port] [you number as a player]
```

## Tests and Debug

There is possibility of game running in DEBUG mode. To build game in debug mode, run
```
cmake .. -DDEBUG=1 -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR
make
```

In debug mode, game will generate dump of starting state of the game.

There is also exists test for the game, including testing engine interface.
To build game with tests, run
```
cmake .. -DDEBUG=1 -DENABLE_TESTING=1 -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR
make
```

To run test:

```
./test_engine
```

## Overview

This is trivial card game called Mayhem. Our team developed it during 4th semester in MIPT. The goal of this project was to develop skills in C++, Objected Oriented Programming and also have some fun. You can play this game by the rules, described below.

## Rules

First of all, we have Playground, it includes all players with their decks and bases. Bases lie in the center of the playground, let's talk about player first.

### Player

Each player has deck with card of one faction, which is picked randomly at the start of the game. Then, each player draws 5 cards from their decks to hand. Cards has 2 types: Minions and Actions. Hand is the cards on the center of the screen. Deck is the card back on the right side and dump deck is the card back on the left. Each player can play 1 Action and 1 Minion at turn. After the Action was played, it moves to the dump deck. Same happens with the Minion after it was destroyed (by Action or after Base's capture). Player can check card ability by right-clicking it.

#### Minion

Minion is a card you can play to the base (for this click minion, then base). You can distinguish Minion from Action by it's power: each Minion has the power parameter in the top left corner.

<details>
<summary> Example of the Minion </summary>
<img alilgn = "center" src = "https://github.com/aleksplast/Mayhem/assets/111467660/1ec40f5b-d8e2-4cc4-b0e9-79e9aa92482b" width = 200>
</details>

#### Action

Action is the other type of card, it perfoms some kind of action. There is 5 types of actions:

1. Destroy Action - destroys minion (to play: click Action, then Base with Minion, then Minion)
2. Move Action - moves Minion from one Base to another (to play: click Action, then Base to move from, then Minion, then Base to move to)
3. Draw Action - draws cards from deck (to play: click Action, then click on your deck)
4. Buff Action - increases power of the Minion (to play: click Action, then click Base with Minion, then click Minion)
5. Debuff Action - decreases power of the Minion (played same as Buff action)

<details>
<summary> Example of the Action (this one is Draw Action) </summary>
<img alilgn = "center" src = "https://github.com/aleksplast/Mayhem/assets/111467660/1ec148ee-3569-4bd2-93aa-b677396180d4" width = 200>
</details>

### Base

Each base has 2 main parts: it's defence and winning points. Defence is the number in top left corner. Base will be captured after sum of the Minions on the base is greater or equal to its defence. After that, player, who has most power on the Base, gains first number from winning points, then second gains second number and third gains third. If two players has the same power, they gain same number of points, but next player gets points if they had different points.

<details>
<summary> Example of the Base </summary>
<img alilgn = "center" src = "https://github.com/aleksplast/Mayhem/assets/111467660/31aa687f-41a2-4646-bf38-bb2a65c86c76" width = 200>
</details>

### Winning

Player will win a game, when he gets 15 winning points. If two players gain 15 points at the same time, game continues until someone has more points then the others.

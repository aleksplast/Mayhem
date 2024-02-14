#ifndef GAME_CORE_H
#define GAME_CORE_H

#include <array>
#include <list>
#include <stdlib.h>
#include <vector>
#include <string>
#include <deque>
#include <SFML/Graphics.hpp>
#include "deck.h"
#include "card.h"
#include "entity.h"

namespace Mayhem {

class Player: public Entity {
private:
    Deck<PlayerCard> hand_;
    Deck<PlayerCard> dump_deck_;
    Deck<PlayerCard> deck_;

    uint32_t points_;

public:
    void play_card(PlayerCard* card); //from hand to base, just destroys card in hand, no interaction with the base
    void end_turn();
    void dump_card(PlayerCard* card); // card to dump deck
    void gain_card(); // from deck to hand

public: // graphic functions
    void draw(sf::Window &window);
}; // class Player

class Playground {
private:
    Deck<Base*> active_bases_;
    Deck<Base*> bases_;
    Deck<Base*> dump_;

    std::vector<Player> players_;

public:
    void clear_base(Base& base); // FIXME: just mock
    void destroy_base(Base& base);
    void set_new_base();

public: //graphic functions
    void draw(sf::Window &window);
}; // class Playground

class Engine {
private:
    Playground playground;
    int time; // FIXME: just mock
    int turn; // FIXME: just mock

public:
    void give_points(uint16_t number, uint16_t player_id) {};
    void give_card(uint16_t id, PlayerCard* card); // так это типо отдать игроку карту, после завершения хода
    void place_card(uint16_t player_id, PlayerCard* card, uint16_t base);
    void end_turn(uint16_t player_id);

public: //graphic functions
    PlayerCard* contains(sf::Vector2f &pos);
    void draw(sf::Window &window, uint16_t player_id);
}; // class Engine

} // namespace Mayhem

#endif // GAME_CORE_H


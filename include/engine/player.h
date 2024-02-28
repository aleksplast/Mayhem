#ifndef PLAYER_H
#define PLAYER_H

#include "core/base.h"
#include "graphics/graphics.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

namespace Mayhem {
using LeaderBoard_t = std::map<uint32_t, uint32_t>;

class Player : public Entity {
  private:
    Deck<PlayerCard *> hand_;
    Deck<PlayerCard *> dump_deck_;
    Deck<PlayerCard *> deck_;

    uint32_t points_;

    virtual void activate_abillity(){};

    // get number of card
  public:
    Player(Graphics &grpahics, uint32_t id)
        : Entity("../src/graphics/images/player.png", id), hand_(), dump_deck_(), deck_(), points_(0) {
        sprite.setColor(sf::Color(0, 0, 0, 100));
    };
    ~Player() = default;

  public:
    void play_card(PlayerCard *card);// from hand to base, just destroys card in hand, no interaction with the base
    void dump_card(PlayerCard *card); // card to dump deck
    void gain_card_on_start(PlayerCard *card); // gain card to deck on the start of the game
    void end_turn();
    void take_card(uint32_t number_of_cards); // from deck to hand, just card to hand
    void set_points(uint32_t point);
    size_t get_number_of_cards() { return hand_.size(); };

  public: // graphic function
    void draw(Graphics &graphic);
}; // class Player

} // namespace Mayhem

#endif // PLAYER_H
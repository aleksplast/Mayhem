#ifndef PLAYER_H
#define PLAYER_H

#include "core/base.h"
#include "graphics/graphics.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

namespace Mayhem {

// Structure with leading players IDs from the base and their points
using LeaderBoard_t = std::map<uint32_t, uint32_t>;

// Class representing Player
class Player : public Entity {
  private:
    // Card in hand
    Deck<PlayerCard *> hand_;

    // Cards in dump
    Deck<PlayerCard *> dump_deck_;

    // Cards in deck
    Deck<PlayerCard *> deck_;

    // Current points player have
    uint32_t points_;

  public:
    Player(uint32_t id);
    ~Player() = default;

  public:
    // Destroyrs card in hand, no interaction with the base
    void play_card(PlayerCard *card);

    // Move card from deck to dump deck
    void dump_card(PlayerCard *card);

    // Gain card to deck on the start of the game
    void gain_card_on_start(PlayerCard *card);

    // End turn of the player
    void end_turn();

    // Moves number_of_cards from deck to hand
    void take_card(uint32_t number_of_cards);

    // Returns number of cards in hand
    size_t get_number_of_cards();

    // Dump state of the player
    void dump_state(std::ostream &os) const;

    // Dump random card from hand
    void dump_random_card();

    // Gain winning points
    void gain_points(uint32_t points);

    // Get number of winning points
    uint32_t get_points() const;

    // Shuffle deck_, dump_deck_ and hand_ untouched
    void shuffle_deck();

  public: // graphics function
    // Draw player
    void draw(GraphicsModel::Data::Attributes &attributes, const sf::FloatRect &rect, const float angle);
    void draw(sf::RenderWindow &window, const sf::FloatRect &rect, const float angle) override;
}; // class Player

} // namespace Mayhem

#endif // PLAYER_H

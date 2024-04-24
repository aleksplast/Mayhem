#ifndef CARD_H
#define CARD_H

#include "entity.h"
#include "graphics/button.hpp"
#include <fstream>
#include <stdlib.h>
#include <string>

namespace Mayhem {

// Card type
class Card : public Entity {
  public:
    Card(const std::string &name_main_file, int id, const std::string &name_extra_file = "");
}; // class Card

// Card that can belong to a player
class PlayerCard : public Card {
  private:
    // Owner of the card
    uint32_t owner_id_;

  public:
    PlayerCard(const std::string &name_main_file, int id, const std::string &name_extra_file = "");

    // Get owner of the card
    uint32_t get_owner();

    // Change owner of the card
    void change_owner(uint32_t owner);

    // Dump state of the card
    virtual void dump_state(std::ostream &os) const {};
}; // class PlayerCard

// Minion class
class Minion : public PlayerCard {
  private:
    // Power of the minion
    uint32_t power_;
    Button power_picture_;

  public:
    Minion(const std::string &minion_main_file, const std::string &minion_extra_file, int id, uint32_t power);

    // Dump state of the minion
    void dump_state(std::ostream &os) const override;

    uint32_t get_power() const;

    void increase_power(uint32_t power);

    // Decrease power of the minion
    void decrease_power(uint32_t power);

  public: // graphics functions
    // Draw minion on the window
    void draw(sf::RenderWindow &window, const sf::FloatRect &rect, const float angle) override;
}; // class Minion

} // namespace Mayhem

#endif // CARD_H

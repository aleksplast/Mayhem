#ifndef BASE_H
#define BASE_H

#include "card.h"
#include "deck.h"
#include "graphics/graphics_model.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace Mayhem {

class Base : public Card {
  private:
    // Power player need to get to win here
    uint32_t power_to_win_ = 0;

    // Points players gain after capture
    std::array<uint32_t, 3> points_ = {0, 0, 0};

    // Minions on the base
    Deck<Minion *> cards_;

    // Current power on the base
    uint32_t current_power_ = 0;

  public:
    // Add minion to cards on the base
    void gain_minion(Minion *card);

    // Remove minion from minion on the base
    void remove_minion(Minion *card);

    // Is the base captured
    bool is_captured() const;

    // Get power to win on this base
    uint32_t get_power_to_win() const;

    // Get current power on this base
    uint32_t get_current_power() const;

    // Get winning points on this base
    std::array<uint32_t, 3> get_points() const;

    // Dump state of the base
    void dump_state(std::ostream &os) const;

  public: // graphic functions
    Base(const std::string &base_file, int id, uint32_t power_to_win, std::array<uint32_t, 3> points);

    // Show cards on the base
    void show_cards(GraphicsModel::Data::Attributes &attributes) const;

    // Get cards on the base
    const Deck<Minion *> &get_cards();
}; // class Base

} // namespace Mayhem

#endif // END_H

#ifndef BASE_H
#define BASE_H

#include "card.h"
#include "deck.h"
#include "graphics/graphics.hpp"
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
    void gain_minion(Minion *card) {
        current_power_ += card->get_power();

        cards_.gain_card(card);
    }

    // Remove minion from minion on the base
    void remove_minion(Minion *card) {
        current_power_ -= card->get_power();

        cards_.remove_card(card);
    }

    // Is the base captured
    bool is_captured() const {
        if (current_power_ >= power_to_win_) {
            return true;
        } else {
            return false;
        }
    }

    // Get power to win on this base
    uint32_t get_power_to_win() const { return power_to_win_; }

    // Get current power on this base
    uint32_t get_current_power() const { return current_power_; }

    // Get winning points on this base
    std::array<uint32_t, 3> get_points() const { return points_; }

    // Dump state of the base
    void dump_state(std::ofstream &os) const {
        os << "\nDumping base\n";
        os << "---\n";
        os << "points: " << points_.at(0) << " " << points_.at(1) << " " << points_.at(2) << "\n";
        os << "current power: " << current_power_ << "\n";
        os << "power to win: " << power_to_win_ << "\n";
        cards_.dump_state(os);
        os << "---\n";
    }

  public: // graphic functions
    Base(const std::string &base_file, int id, uint32_t power_to_win, std::array<uint32_t, 3> points)
        : Card(base_file, id), power_to_win_(power_to_win), points_(points), cards_("../assets/images/deck"){};

    // Show cards on the base
    void show_cards(Graphics::DrawingAttributes &attributes) const { cards_.show_cards(attributes); }

    // Get cards on the base
    const Deck<Minion *> &get_cards() { return cards_; }
}; // class Base

} // namespace Mayhem

#endif // END_H

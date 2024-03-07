#ifndef BASE_H
#define BASE_H

#include "card.h"
#include "deck.h"
#include <cstdint>
#include <iostream>
#include <fstream>

namespace Mayhem {

class Base : public Card {
  private:
    uint32_t power_to_win_ = 0;
    std::array<uint32_t, 3> points_ = {0, 0, 0};
    Deck<Minion *> cards_;
    uint32_t current_power_ = 0;

  public:
    void activate_abillity() override{};

    void gain_minion(Minion *card) {
        current_power_ += card->get_power();

        cards_.gain_card(card);
    }

    void remove_minion(Minion *card) {
        current_power_ -= card->get_power();

        cards_.remove_card(card);
    }

    bool is_captured() const {
        if (current_power_ >= power_to_win_) {
            return true;
        } else {
            return false;
        }
    }

    uint32_t get_power_to_win() const {
      return power_to_win_;
    }

    uint32_t get_current_power() const {
      return current_power_;
    }

    std::array<uint32_t, 3> get_points() const {
      return points_;
    }

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
    Base(const std::string &base_file, int id, std::string ability, uint32_t power_to_win,
         std::array<uint32_t, 3> points)
        : Card(base_file, id, ability), power_to_win_(power_to_win), points_(points){};

    const Deck<Minion *> &get_cards() { return cards_; }
}; // class Base

} // namespace Mayhem

#endif // END_H

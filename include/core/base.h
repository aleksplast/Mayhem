#ifndef BASE_H
#define BASE_H

#include "card.h"
#include "deck.h"

namespace Mayhem {

class Base : public Card {
  private:
    uint32_t power_to_win_;
    std::array<uint32_t, 3> points_;
    Deck<Minion> cards_;
    uint32_t current_power_;

  public:
    void activate_abillity() override{};

    void gain_minion(const Minion *card) {
        current_power_ += card->get_power();

        cards_.gain_card(card);
    }

    void remove_minion(const Minion &card) {
        current_power_ -= card.get_power();

        cards_.remove_card(card);
    }

    bool is_captured() const {
        if (current_power_ >= power_to_win_) {
            return true;
        } else {
            return false;
        }
    }

  public: // graphic functions
    Base(const std::string &base_file, int id, std::string ability, uint32_t power_to_win,
         std::array<uint32_t, 3> points)
        : Card(base_file, id, ability), power_to_win_(power_to_win), points_(points){};
        
    const Deck<Minion>& get_cards() { return cards_; }
}; // class Base

} // namespace Mayhem

#endif // END_H

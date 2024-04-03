#include "core/base.h"

namespace Mayhem {

void Base::gain_minion(Minion *card) {
    current_power_ += card->get_power();

    cards_.gain_card(card);
}

void Base::remove_minion(Minion *card) {
    current_power_ -= card->get_power();

    cards_.remove_card(card);
}

bool Base::is_captured() const {
    if (current_power_ >= power_to_win_) {
        return true;
    } else {
        return false;
    }
}

uint32_t Base::get_power_to_win() const { return power_to_win_; }

uint32_t Base::get_current_power() const { return current_power_; }

std::array<uint32_t, 3> Base::get_points() const { return points_; }

void Base::dump_state(std::ofstream &os) const {
    os << "\nDumping base\n";
    os << "---\n";
    os << "points: " << points_.at(0) << " " << points_.at(1) << " " << points_.at(2) << "\n";
    os << "current power: " << current_power_ << "\n";
    os << "power to win: " << power_to_win_ << "\n";
    cards_.dump_state(os);
    os << "---\n";
}

Base::Base(const std::string &base_file, int id, uint32_t power_to_win, std::array<uint32_t, 3> points)
    : Card(base_file, id), power_to_win_(power_to_win), points_(points), cards_("../assets/images/deck"){};

void Base::show_cards(Graphics::DrawingAttributes &attributes) const { cards_.show_cards(attributes); }

const Deck<Minion *> &Base::get_cards() { return cards_; }

} // namespace Mayhem

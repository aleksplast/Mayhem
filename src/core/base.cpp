#include "core/base.h"

namespace Mayhem {

void Base::gain_minion(Minion *card) { cards_.gain_card(card); }

void Base::remove_minion(Minion *card) { cards_.remove_card(card); }

bool Base::is_captured() const { return get_current_power() >= power_to_win_; }

uint32_t Base::get_power_to_win() const { return power_to_win_; }

uint32_t Base::get_current_power() const {
    uint32_t current_power = 0;
    for (auto curr_it = cards_.begin(), end_it = cards_.end(); curr_it != end_it; ++curr_it) {
        current_power += (*curr_it)->get_power();
    }

    return current_power;
}

std::array<uint32_t, 3> Base::get_points() const { return points_; }

void Base::dump_state(std::ostream &os) const {
    os << "\nDumping base\n";
    os << "---\n";
    os << "points: " << points_[0] << " " << points_[1] << " " << points_[2] << "\n";
    os << "current power: " << get_current_power() << "\n";
    os << "power to win: " << power_to_win_ << "\n";
    cards_.dump_state(os);
    os << "---\n";
}

Base::Base(const std::string &base_file, int id, uint32_t power_to_win, std::array<uint32_t, 3> points)
    : Card(base_file, id), power_to_win_(power_to_win), points_(points), cards_("../assets/images/shirt") {
    units_power_.set_background_color(sf::Color::Black);
    units_power_.set_text_color(sf::Color::Red);
    units_power_.set_char_size(14);
};

void Base::show_cards(GraphicsModel::Data::Attributes &attributes) const { cards_.show_cards(attributes); }

const Deck<Minion *> &Base::get_cards() { return cards_; }

} // namespace Mayhem

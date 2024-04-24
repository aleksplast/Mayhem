#include "core/card.h"
#include "core/deck.h"
#include <cstdint>
#include <fstream>

namespace Mayhem {

Card::Card(const std::string &name_file, int id) : Entity(name_file, id){};

uint32_t PlayerCard::get_owner() { return owner_id_; };

void PlayerCard::change_owner(uint32_t owner_id) { owner_id_ = owner_id; }

PlayerCard::PlayerCard(const std::string &name_file, int id) : Card(name_file, id){};

uint32_t Minion::get_power() const { return power_; }

void Minion::increase_power(uint32_t power) { power_ += power; }

void Minion::dump_state(std::ostream &os) const {
    os << "\nDumping Minion\n";
    os << "power: " << power_ << "\n";
}

void Minion::decrease_power(uint32_t power) {
    if (power > power_) {
        power_ = 0;
    } else {
        power_ -= power;
    }
}

Minion::Minion(const std::string &minion_file, int id, uint32_t power)
    : PlayerCard(minion_file, id), power_(power), power_picture_(std::to_string(power_)) {
    power_picture_.set_background_color(sf::Color(0, 0, 0, 0));
    power_picture_.set_text_color(sf::Color::Black);
};

} // namespace Mayhem

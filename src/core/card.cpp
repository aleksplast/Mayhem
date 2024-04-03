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

void Minion::dump_state(std::ofstream &os) const {
    os << "\nDumping Minion\n";
    os << "power: " << power_ << "\n";
}

void Minion::decrease_power(uint32_t power) {
    if (power > power_) {
        power_ = 0;
        return;
    }

    power_ -= power;
}

Minion::Minion(const std::string &minion_file, int id, uint32_t power) : PlayerCard(minion_file, id), power_(power){};

void Action::dump_state(std::ofstream &os) const {
    os << "\nDumping Action\n";
    os << "Not implemented\n";
}

Action::Action(const std::string &action_file, int id) : PlayerCard(action_file, id){};

} // namespace Mayhem

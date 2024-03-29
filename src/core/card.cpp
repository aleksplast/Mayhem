#include "core/card.h"
#include "core/deck.h"
#include <cstdint>
#include <fstream>

namespace Mayhem {

void PlayerCard::change_owner(uint32_t owner_id) { owner_id_ = owner_id; }

void Minion::dump_state(std::ofstream &os) const {
    os << "\nDumping Minion\n";
    os << "power: " << power_ << "\n";
}

void Action::dump_state(std::ofstream &os) const {
    os << "\nDumping Action\n";
    os << "Not implemented\n";
}

void Minion::decrease_power(uint32_t power) {
    if (power > power_) {
        power_ = 0;
        return;
    }

    power_ -= power;
}
} // namespace Mayhem

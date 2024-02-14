#include "../../include/core/card.h"
#include <cstdint>

namespace Mayhem {

void PlayerCard::change_owner(uint32_t owner_id) {
    owner_id_ = owner_id;
}

void Base::gain_minion(const Minion* card) {
    current_power_ += card->get_power();

    cards_.gain_card(card);
}

void Base::remove_minion(const Minion& card) {
    current_power_ -= card.get_power();

    cards_.remove_card(card);
}

bool Base::is_captured() const {
    if (current_power_ >= power_to_win_) {
        return true;
    } else {
        return false;
    }
}

} // namespace Mayhem

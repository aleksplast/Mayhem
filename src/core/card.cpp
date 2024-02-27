#include "core/card.h"
#include "core/deck.h"
#include <cstdint>

namespace Mayhem {

void PlayerCard::change_owner(uint32_t owner_id) { owner_id_ = owner_id; }

} // namespace Mayhem

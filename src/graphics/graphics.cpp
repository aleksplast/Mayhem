#include "../../include/graphics/graphics.hpp"

namespace Mayhem {

const float Graphics::get_num_cards_per_side() const {
  return num_cards_per_side_;
}

const float Graphics::get_num_players_per_side() const {
  return num_players_per_side_;
}

uint16_t Graphics::get_draw_player() const { return draw_player_; }

const float Graphics::get_player_increase() const { return player_increase_; }

} // namespace Mayhem
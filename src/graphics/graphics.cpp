#include "graphics/graphics.hpp"
#include <SFML/Graphics.hpp>

namespace Mayhem {

Graphics::Graphics(GameType type, uint16_t draw_player) : type_(type), draw_player_(draw_player) {};

uint16_t Graphics::get_draw_player() const { return draw_player_; }

} // namespace Mayhem

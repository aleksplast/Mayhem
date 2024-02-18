#include "../../include/graphics/graphics.hpp"

#include <iostream>

namespace Mayhem
{

Drawable::Drawable(const std::string &texture_file)
{
    texture.loadFromFile(texture_file);
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

const float Graphics::get_num_cards_per_side() const
{
    return num_cards_per_side_;
}

uint16_t Graphics::get_draw_player() const
{
    return draw_player_;
}

const float Graphics::get_player_increase() const
{
    return player_increase_;
}

} // namespace Mayhem
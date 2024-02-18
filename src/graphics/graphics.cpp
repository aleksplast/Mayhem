#include "../../include/graphics/graphics.hpp"

#include <iostream>

namespace Mayhem
{

Drawable::Drawable(const std::string &texture_file)
{
    texture.loadFromFile(texture_file);
    texture.setSmooth(true);
    sprite.setTexture(texture);
}

} // namespace Mayhem
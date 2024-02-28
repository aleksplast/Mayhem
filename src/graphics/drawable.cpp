#include "graphics/drawable.hpp"
#include <SFML/Graphics.hpp>

namespace Mayhem {

Drawable::Drawable(const std::string &texture_file) {
    texture.loadFromFile(texture_file);
    texture.setSmooth(true);
    sprite.setTexture(texture);
    auto texture_size = texture.getSize();
    sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
}

} // namespace Mayhem

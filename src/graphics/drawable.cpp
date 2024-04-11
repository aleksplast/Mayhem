#include "graphics/drawable.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

namespace Mayhem {

Drawable::Drawable(const std::string &texture_file) : texture() {
    texture.loadFromFile(texture_file);
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sf::Vector2u texture_size = texture.getSize();
    sprite.setOrigin(static_cast<float>(texture_size.x) / 2, static_cast<float>(texture_size.y) / 2);
}

void Drawable::draw(sf::RenderWindow &window, const sf::FloatRect &rect, const float angle) {
    sprite.setPosition(rect.left + rect.width / 2, rect.top + rect.height / 2);
    sf::Vector2f texture_size = sf::Vector2f(texture.getSize());
    sprite.setScale(rect.width / texture_size.x, rect.height / texture_size.y);
    sprite.setRotation(angle);

    if (is_pressed)
        sprite.setColor(sf::Color(30,144,220));
    else
        sprite.setColor(sf::Color::White);

    window.draw(sprite);
}

void Drawable::press() { is_pressed = true; }
void Drawable::release() { is_pressed = false; }

} // namespace Mayhem

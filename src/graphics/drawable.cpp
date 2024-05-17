#include "graphics/drawable.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

namespace Mayhem {

Drawable::Drawable(const std::string &main_file, const std::string &extra_file) : main_texture(), extra_texture() {
    main_texture.loadFromFile(main_file);
    main_texture.setSmooth(true);

#ifdef DEBUG
    texture_name = main_file;
#endif

    if (extra_file == "")
        extra_texture = main_texture;
    else {
        extra_texture.loadFromFile(extra_file);
        extra_texture.setSmooth(true);
    }
    sprite.setTexture(extra_texture);
    sf::Vector2u texture_size = extra_texture.getSize();
    sprite.setOrigin(static_cast<float>(texture_size.x) / 2, static_cast<float>(texture_size.y) / 2);
}

void Drawable::draw(sf::RenderWindow &window, const sf::FloatRect &rect, const float angle) {
    const sf::Texture *texture = sprite.getTexture();

    sprite.setPosition(rect.left + rect.width / 2, rect.top + rect.height / 2);
    sf::Vector2f texture_size = sf::Vector2f(texture->getSize());
    sprite.setScale(rect.width / texture_size.x, rect.height / texture_size.y);
    sprite.setRotation(angle);

    if (is_pressed)
        sprite.setColor(sf::Color(8, 173, 199));
    else
        sprite.setColor(sf::Color::White);

    window.draw(sprite);
}

void Drawable::set_main_texture() { sprite.setTexture(main_texture); }
void Drawable::set_extra_texture() { sprite.setTexture(extra_texture); }
void Drawable::press() { is_pressed = true; }
void Drawable::release() { is_pressed = false; }

} // namespace Mayhem

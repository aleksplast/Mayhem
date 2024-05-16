#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace Mayhem {

// class describing the objects to be drawn
class Drawable {
  protected:
#ifndef DEBUG
    std::string texture_name;
#endif

    sf::Texture main_texture;
    sf::Texture extra_texture;
    bool is_pressed = false;

  public:
    sf::Sprite sprite;

  public:
    Drawable() = default;
    Drawable(const std::string &main_file, const std::string &extra_file = "");

    // Draw entity on the window
    virtual void draw(sf::RenderWindow &window, const sf::FloatRect &rect, const float angle);

    // set main texture
    void set_main_texture();

    // set extra texture
    void set_extra_texture();

    // clicks on the entity
    void press();

    // disable entity selection
    void release();

    ~Drawable() = default;
}; // class Drawable

} // namespace Mayhem

#endif // DRAWABLE_H

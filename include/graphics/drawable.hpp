#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>

namespace Mayhem {

// class describing the objects to be drawn
class Drawable {
  protected:
    sf::Texture texture;
    bool is_pressed = false;

  public:
    sf::Sprite sprite;

  public:
    Drawable() = default;
    Drawable(const std::string &texture_file);

    // Draw entity on the window
    virtual void draw(sf::RenderWindow &window, const sf::FloatRect &rect, const float angle);

    // clicks on the entity
    void press();

    // disable entity selection
    void release();

    ~Drawable() = default;
}; // class Drawable

} // namespace Mayhem

#endif // DRAWABLE_H

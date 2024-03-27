#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>

namespace Mayhem {

class Drawable {
  private:
    sf::Texture texture;

  public:
    sf::Sprite sprite;

  public:
    Drawable() = default;
    Drawable(const std::string &texture_file);
    virtual void draw(sf::RenderWindow &window, const sf::FloatRect &rect, const float angle);
    ~Drawable() = default;
}; // class Drawable

} // namespace Mayhem

#endif // DRAWABLE_H

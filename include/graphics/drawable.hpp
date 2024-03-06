#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>

namespace Mayhem {

class Drawable {
  public:
    sf::Sprite sprite;
    sf::Texture texture;

  public:
    Drawable() = default;
    Drawable(const std::string &texture_file);
    ~Drawable() = default;
}; // class Drawable

} // namespace Mayhem

#endif // DRAWABLE_H

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <string>

namespace Mayhem {

class Button {
  private:
    sf::Font font;
    std::string text;
    sf::IntRect rect;

  public:
    Button();
    ~Button();
    void set_background_color(int R, int G, int B);
};

} // namespace Mayhem

#endif // BUTTON_HPP

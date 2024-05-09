#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "graphics/button.hpp"
#include "graphics/drawable.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <initializer_list>
#include <vector>

namespace Mayhem {

// Describes the basic behavior of the screen
class Screen {
  private:
    Drawable background;
    std::vector<Button *> buttons_;

  private:
    // Detects the pressed button
    int16_t process_mouse_click(const sf::Vector2u mouse_pos);

  public:
    Screen();
    Screen(const std::string &str);
    Screen(const std::initializer_list<const std::string> &list);
    ~Screen();

    // Push button with name "str" to the begin of the list of buttons
    void push(const std::string &str);

    // Push buttons with name in list to the begin of the list of buttons
    void push(const std::initializer_list<const std::string> &list);

    // Pop button from the end of the list of buttons
    void pop();

    // Clear the screan
    void claer();

    // displays the contents of the screen
    void draw(sf::RenderWindow &window, sf::Vector2u window_size);

    // return number of pressed button or -1 (to exit)
    int16_t get_event(sf::RenderWindow &window, sf::Vector2u window_size);
}; // Screen

} // namespace Mayhem

#endif // SCREEN_HPP

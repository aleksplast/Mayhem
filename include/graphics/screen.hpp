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

/// Describes the basic behavior of the screen
class Screen {
  private:
    /// @brief Background
    Drawable background = Drawable();
    /// @brief Buttons on the screen
    std::vector<Button *> buttons_ = std::vector<Button *>();

  private:
    /// @brief Detects the pressed button
    /// @param[in] mouse_pos Mouse positon
    /// @return Number of button
    int16_t process_mouse_click(const sf::Vector2f mouse_pos);

  public:
    /// @brief Constructor
    Screen();
    /// @brief Constructor
    /// @param str Other Screen
    Screen(const std::string &str);
    /// @brief Constructor
    /// @param[in] list List of name of buttons
    Screen(const std::initializer_list<const std::string> &list);
    /// @brief Destructor
    ~Screen();

    /// @brief Push button with name to the begin of the list of buttons
    /// @param[in] str Name of button
    void push(const std::string &str);

    /// @brief Push buttons with name in list to the begin of the list of buttons
    /// @param[in] list List of name of buttons
    void push(const std::initializer_list<const std::string> &list);

    /// @brief Pop button from the end of the list of buttons
    void pop();

    /// @brief Clear the screan
    void claer();

    /// @brief Displays the contents of the screen
    /// @param[out] window Window
    /// @param[in] window_size Window size
    void draw(sf::RenderWindow &window, sf::Vector2u window_size);

    /// @brief Return number of pressed button or -1 (to exit)
    /// @param[out] window Window
    /// @param[in] window_size Window size
    /// @return Number of button
    int16_t get_event(sf::RenderWindow &window, sf::Vector2u window_size);
}; // Screen

} // namespace Mayhem

#endif // SCREEN_HPP

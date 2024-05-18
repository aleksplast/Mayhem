#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <string>

namespace Mayhem {

// A class describing the functions of the button
class Button {
  public:
    // enum class Type
    enum class Type {
        no_type,
        end_turn,
        close_window,
    }; // enum class Type

  private:
    sf::Font font_ = sf::Font();
    sf::Text text_ = sf::Text();
    sf::RectangleShape rect_ = sf::RectangleShape();

  private:
    // Sets the position of the text
    void set_text_position();

  public:
    Button();
    Button(const Button &rhs);
    Button(Button &&rhs);
    Button(const std::string &text, const sf::IntRect &rect = sf::IntRect());
    Button &operator=(const Button &rhs);
    Button &operator=(Button &&rhs);

    ~Button();

    // Set button position
    void set_position(const sf::IntRect &rect);

    // Set char size
    void set_char_size(unsigned int size);

    // Set background color
    void set_background_color(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha);

    // Set background color
    void set_background_color(const sf::Color &color);

    // Set string
    void set_string(const std::string &text);

    // Set text color
    void set_text_color(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha);

    // Set text color
    void set_text_color(const sf::Color &color);

    // Draw button on the window
    void draw(sf::RenderWindow &window);

    // Return button global bounds
    sf::FloatRect get_global_bounds() const;
};

} // namespace Mayhem

#endif // BUTTON_HPP

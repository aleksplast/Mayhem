#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <string>

namespace Mayhem {

class Button {
  public:
    enum class Type {
        no_type,
        end_turn,
        close_window,
    }; // enum class Type

  private:
    sf::Font font_;
    sf::Text text_;
    sf::RectangleShape rect_;

  private:
    void set_text_possition();

  public:
    Button();
    Button(const std::string &text, const sf::IntRect &rect = sf::IntRect());
    ~Button();
    void set_possition(const sf::IntRect &rect);
    void set_char_size(unsigned int size);
    void set_background_color(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha);
    void set_background_color(const sf::Color &color);
    void set_text_color(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha);
    void set_text_color(const sf::Color &color);
    void draw(sf::RenderWindow &window);
    sf::FloatRect get_global_bounds() const;
};

} // namespace Mayhem

#endif // BUTTON_HPP

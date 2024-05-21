#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <string>

namespace Mayhem {

/// A class describing the functions of the button
class Button {
  public:
    /// Listing all types of buttons
    enum class Type {
        no_type,      ///< Lack of type
        end_turn,     ///< End of turn button
        close_window, ///< Closing the game window
    };                // enum class Type

  private:
    sf::Font font_ = sf::Font();                     ///< Font of the text
    sf::Text text_ = sf::Text();                     ///< Text on the button
    sf::RectangleShape rect_ = sf::RectangleShape(); ///< Button boundaries

  private:
    /**
        @brief Sets the position of the text
    */
    void set_text_position();

  public:
    /**
        @brief Button constructor
    */
    Button();
    /**
        @brief Button copy-constructor

        @param[in] rhs The button being copied
    */
    Button(const Button &rhs);
    /**
        @brief Button move-constructor

        @param[out] rhs The button being copied
    */
    Button(Button &&rhs);
    /**
        @brief Button constructor

        @param[in] text Button text
        @param[in] rect Button boundaries
    */
    Button(const std::string &text, const sf::IntRect &rect = sf::IntRect());
    /**
        @brief Copies the button

        @param[in] rhs The button being copied
        @return This button
    */
    Button &operator=(const Button &rhs);
    /**
        @brief Copies the button

        @param[out] rhs The button being copied
        @return This button
    */
    Button &operator=(Button &&rhs);

    /**
        @brief Button destructor
    */
    ~Button();

    /**
        @brief Set button position

        @param[in] rect Button boundaries
    */
    void set_position(const sf::IntRect &rect);

    /**
        @brief Set char size of the text

        @param[in] size
    */
    void set_char_size(unsigned int size);

    /**
        @brief Set background color. RGB code

        @param[in] red Value from 0 to 255
        @param[in] green Value from 0 to 255
        @param[in] blue Value from 0 to 255
        @param[in] alpha Visibility. Value from 0 to 255
    */
    void set_background_color(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha);

    /**
        @brief Set background color

        @param[in] color background color
    */
    void set_background_color(const sf::Color &color);

    /**
        @brief Set button text

        @param[in] text
    */
    void set_string(const std::string &text);

    /**
        @brief Set text color. RGB code

        @param[in] red Value from 0 to 255
        @param[in] green Value from 0 to 255
        @param[in] blue Value from 0 to 255
        @param[in] alpha Visibility. Value from 0 to 255
    */
    void set_text_color(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha);

    /**
        @brief Set text color

        @param[in] color text color
    */
    void set_text_color(const sf::Color &color);

    /**
        @brief Draw button on the window

        @param[out] window
    */
    void draw(sf::RenderWindow &window);

    /**
        @brief Return button global bounds
        @return Return button global bounds
    */
    sf::FloatRect get_global_bounds() const;
};

} // namespace Mayhem

#endif // BUTTON_HPP

#include "graphics/button.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>

namespace Mayhem {

Button::Button() {
    font_.loadFromFile("../assets/font/font.ttf");
    text_.setFont(font_);
}

Button::Button(const std::string &text, const sf::IntRect &rect) : Button() {
    text_.setString(text);
    rect_.setTextureRect(rect);
}

Button::Button(const Button &rhs) : font_(rhs.font_), text_(rhs.text_) {
    rect_.setTextureRect(rhs.rect_.getTextureRect());
    rect_.setPosition(rhs.rect_.getPosition());
}

Button::Button(Button &&rhs) : font_(std::move(rhs.font_)), text_(std::move(rhs.text_)) {
    rect_ = std::move(rhs.rect_);
}

Button &Button::operator=(const Button &rhs) {
    font_ = rhs.font_;
    text_ = rhs.text_;
    rect_.setTextureRect(rhs.rect_.getTextureRect());
    rect_.setPosition(rhs.rect_.getPosition());
    return *this;
}

Button &Button::operator=(Button &&rhs) {
    font_ = std::move(rhs.font_);
    text_ = std::move(rhs.text_);
    rect_ = std::move(rhs.rect_);
    return *this;
}

void Button::set_text_position() {
    sf::FloatRect rect_bounds = rect_.getGlobalBounds();
    sf::Vector2u center_pos = sf::Vector2u(static_cast<unsigned>(rect_bounds.left + rect_bounds.width / 2),
                                           static_cast<unsigned>(rect_bounds.top + rect_bounds.height / 2));
    sf::String str = text_.getString();
    sf::FloatRect text_bounds = text_.getGlobalBounds();
    text_.setPosition(static_cast<float>(center_pos.x) - text_bounds.width / 2,
                      static_cast<float>(center_pos.y) - text_bounds.height / 2);
}

void Button::set_char_size(unsigned int size) { text_.setCharacterSize(size); }

void Button::set_position(const sf::IntRect &rect) {
    rect_.setSize(sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height)));
    rect_.setPosition(sf::Vector2f(static_cast<float>(rect.left), static_cast<float>(rect.top)));
}

void Button::set_background_color(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha) {
    rect_.setFillColor(sf::Color(red, green, blue, alpha));
}

void Button::set_background_color(const sf::Color &color) { rect_.setFillColor(color); }

void Button::set_string(const std::string &text) { text_.setString(text); }

void Button::set_text_color(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha) {
    text_.setFillColor(sf::Color(red, green, blue, alpha));
}

void Button::set_text_color(const sf::Color &color) { text_.setFillColor(color); }

void Button::draw(sf::RenderWindow &window) {
    set_text_position();
    window.draw(rect_);
    window.draw(text_);
}

sf::FloatRect Button::get_global_bounds() const { return rect_.getGlobalBounds(); }

Button::~Button() = default;
} // namespace Mayhem

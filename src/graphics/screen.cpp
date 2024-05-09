#include "graphics/screen.hpp"
#include "graphics/graphics_model.hpp"
#include <SFML/System/Vector2.hpp>

using namespace Mayhem;

const std::string BACKGROUND_IMAGES = "../assets/images/background";

Screen::Screen() : background(BACKGROUND_IMAGES) {}

Screen::Screen(const std::string &str) : Screen() { buttons_.push_back(new Button(str)); }

Screen::Screen(const std::initializer_list<const std::string> &list) : Screen() {
    buttons_.reserve(list.size());
    for (auto str = list.begin(); str != list.end(); ++str)
        buttons_.push_back(new Button(*str));
}

void Screen::push(const std::string &str) { buttons_.push_back(new Button(str)); }

void Screen::push(const std::initializer_list<const std::string> &list) {
    for (auto str = list.begin(); str != list.end(); ++str)
        buttons_.push_back(new Button(*str));
}

void Screen::pop() {
    delete buttons_.front();
    buttons_.pop_back();
}

void Screen::claer() {
    for (auto it = buttons_.begin(); it != buttons_.end(); ++it) {
        delete *it;
    }
    buttons_.clear();
}

void Screen::draw(sf::RenderWindow &window, sf::Vector2u window_size) {
    background.draw(window, sf::FloatRect(0, 0, window_size.x, window_size.y), 0);
    using Scope = GraphicsModel::Settings::Rendering::Button::ScreenButtons;
    sf::Vector2u button_size = sf::Vector2u(window_size.x * Scope::Scale::x, window_size.y * Scope::Scale::y);
    size_t size = buttons_.size();
    unsigned start_offset = window_size.y * Scope::Offset::start;
    unsigned offset_x = window_size.x * Scope::Offset::x;
    unsigned offset_y = window_size.y * Scope::Offset::y;

    for (size_t i = 0; i < size; ++i) {
        Button &button = *buttons_[i];
        button.set_background_color(sf::Color::Cyan);
        button.set_text_color(sf::Color::Red);
        button.set_char_size(Scope::char_size);
        button.set_position(sf::IntRect(offset_x - button_size.x / 2, start_offset + offset_y * i - button_size.y / 2,
                                        button_size.x, button_size.y));
        button.draw(window);
    }
}

int16_t Screen::get_event(sf::RenderWindow &window, sf::Vector2u window_size) {
    sf::Event event;

    while (true) {
        int16_t num_event = -1;
        window.pollEvent(event);
        switch (event.type) {
        case sf::Event::Closed:
            return -1;
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button != sf::Mouse::Left)
                break;
            num_event = process_mouse_click(sf::Vector2u(event.mouseButton.x * window_size.x / window.getSize().x,
                                                         event.mouseButton.y * window_size.y / window.getSize().y));
            if (num_event != -1)
                return num_event;
            break;
        case sf::Event::Resized:
            window.clear();
            Screen::draw(window, window_size);
            window.display();
            break;
        }
    }
}

int16_t Screen::process_mouse_click(const sf::Vector2u mouse_pos) {
    int16_t i = 0;

    for (auto button = buttons_.begin(); button != buttons_.end(); ++button, ++i) {
        auto bound = (*button)->get_global_bounds();
        if (bound.contains(mouse_pos.x, mouse_pos.y))
            return i;
    }
    return -1;
}

Screen::~Screen() {
    for (auto it = buttons_.begin(); it != buttons_.end(); ++it) {
        delete *it;
    }
}

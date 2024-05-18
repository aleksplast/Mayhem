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
    background.draw(window, sf::FloatRect(0, 0, static_cast<float>(window_size.x), static_cast<float>(window_size.y)),
                    0);
    using Scope = GraphicsModel::Settings::Rendering::Button::ScreenButtons;
    sf::Vector2f button_size = sf::Vector2f(static_cast<float>(window_size.x) * Scope::Scale::x,
                                            static_cast<float>(window_size.y) * Scope::Scale::y);
    size_t size = buttons_.size();
    float start_offset = static_cast<float>(window_size.y) * Scope::Offset::start;
    float offset_x = static_cast<float>(window_size.x) * Scope::Offset::x;
    float offset_y = static_cast<float>(window_size.y) * Scope::Offset::y;

    for (size_t i = 0; i < size; ++i) {
        Button &button = *buttons_[i];
        button.set_background_color(sf::Color::Cyan);
        button.set_text_color(sf::Color::Red);
        button.set_char_size(Scope::char_size);
        button.set_position(
            sf::IntRect(static_cast<int>(offset_x - button_size.x / 2),
                        static_cast<int>(start_offset + offset_y * static_cast<float>(i) - button_size.y / 2),
                        static_cast<int>(button_size.x), static_cast<int>(button_size.y)));
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
            num_event = process_mouse_click(sf::Vector2f(
                static_cast<float>(event.mouseButton.x * static_cast<int>(window_size.x)) / static_cast<float>(window.getSize().x),
                static_cast<float>(event.mouseButton.y * static_cast<int>(window_size.y)) / static_cast<float>(window.getSize().y)));
            if (num_event != -1)
                return num_event;
            break;
        case sf::Event::Resized:
            window.clear();
            Screen::draw(window, window_size);
            window.display();
            break;
        default:
            break;
        }
    }
}

int16_t Screen::process_mouse_click(const sf::Vector2f mouse_pos) {
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

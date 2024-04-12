#include "graphics/graphics_controller.hpp"
#include "core/base.h"
#include "core/deck.h"
#include <SFML/Window/Event.hpp>

namespace Mayhem {

GraphicsController::GraphicsController(GraphicsModel &m) : model(m), command(model) {}

Base *GraphicsController::pressed_base(const sf::Vector2f &pos) {
    auto end_it = model.attributes.active_bases.rend();
    for (auto it = model.attributes.active_bases.rbegin(); it != end_it; ++it) {
        if ((*it)->sprite.getGlobalBounds().contains(pos.x, pos.y)) {
            return *it;
        }
    }
    return nullptr;
}

Deck<PlayerCard *> *GraphicsController::pressed_deck(const sf::Vector2f &pos) {
    auto end_it = model.attributes.current_decks.rend();
    for (auto it = model.attributes.current_decks.rbegin(); it != end_it; ++it) {
        if ((*it)->sprite.getGlobalBounds().contains(pos.x, pos.y)) {
            return *it;
        }
    }
    return nullptr;
}

Button::Type GraphicsController::pressed_button(const sf::Vector2f &pos) {
    for (auto it : model.attributes.buttuns) {
        if (it.second.contains(pos)) {
            return it.first;
        }
    }
    return Button::Type::no_type;
}

PlayerCard *GraphicsController::pressed_card(const sf::Vector2f &pos) {
    auto end_it = model.attributes.current_player_cards.rend();
    for (auto it = model.attributes.current_player_cards.rbegin(); it != end_it; ++it) {
        if ((*it)->sprite.getGlobalBounds().contains(pos.x, pos.y)) {
            return *it;
        }
    }
    return nullptr;
}

void GraphicsController::process_mouse_events(const sf::Event &event) {
    if (event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2u window_size = model.attributes.window.getSize();
        sf::Vector2f mouse_pos =
            sf::Vector2f(event.mouseButton.x * model.attributes.default_window_size.x / window_size.x,
                         event.mouseButton.y * model.attributes.default_window_size.y / window_size.y);

        PlayerCard *card = pressed_card(mouse_pos);
        Base *base = pressed_base(mouse_pos);
        Deck<PlayerCard *> *deck = pressed_deck(mouse_pos);
        Button::Type button_type = pressed_button(mouse_pos);

        if (card)
            command.set_card(card);
        else if (base)
            command.set_base(base);
        else if (deck)
            command.set_deck(deck);
        else if (button_type != Button::Type::no_type)
            command.set_button(button_type);
        else
            command.clear();
    }
}

void GraphicsController::process_events() {
    sf::Event event;
    while (model.attributes.window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            command.set_button(Button::Type::close_window);
            break;

        case sf::Event::MouseButtonPressed:
            process_mouse_events(event);
            break;
        }
    }
}

} // namespace Mayhem

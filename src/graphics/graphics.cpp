#include "graphics/graphics.hpp"
#include "core/base.h"
#include "core/card.h"
#include "engine/engine.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cstdio>
#include <ostream>

namespace Mayhem {

Graphics::Graphics() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::VideoMode video_mode = sf::VideoMode::getFullscreenModes()[4];
    attributes.default_window_size = sf::Vector2u(video_mode.width, video_mode.height);
    attributes.window.create(video_mode, "Mayhem", sf::Style::Default, settings);
    attributes.window.setFramerateLimit(100);
}

void Graphics::launch_game(Engine &engine) {
    while (attributes.window.isOpen()) {
        process_events(engine);
        attributes.window.clear();
        engine.draw(attributes);
        attributes.window.display();
    }
}

PlayerCard *Graphics::pressed_card(const sf::Vector2f &pos) const {
    for (auto it : attributes.current_player_cards) {
        if (it->sprite.getGlobalBounds().contains(pos.x, pos.y)) {
            return it;
        }
    }
    return nullptr;
}

Base *Graphics::pressed_base(const sf::Vector2f &pos) const {
    for (auto it : attributes.active_bases) {
        if (it->sprite.getGlobalBounds().contains(pos.x, pos.y)) {
            return it;
        }
    }
    return nullptr;
}

Deck<PlayerCard *> *Graphics::pressed_deck(const sf::Vector2f &pos) const {
    for (auto it : attributes.current_decks) {
        if (it->sprite.getGlobalBounds().contains(pos.x, pos.y)) {
            return it;
        }
    }
    return nullptr;
}

void Graphics::get_event_parameters(const sf::Event &event, GameEvent &game_event) const {
    if (event.type == sf::Event::Closed) {
        game_event.type = GameEvent::EventType::close_window;
    } else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2u window_size = attributes.window.getSize();
            sf::Vector2f mouse_pos =
                sf::Vector2f(event.mouseButton.x * attributes.default_window_size.x / window_size.x,
                             event.mouseButton.y * attributes.default_window_size.y / window_size.y);
            if (!game_event.card)
                game_event.card = pressed_card(mouse_pos);

            if (!game_event.base)
                game_event.base = pressed_base(mouse_pos);
            if (!game_event.base)
                game_event.deck = pressed_deck(mouse_pos);
        }
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            game_event.type = GameEvent::EventType::end_turn;
        }
    }
    set_event_type(game_event);
}

void Graphics::set_event_type(GameEvent &game_event) const {
    if (game_event.card) {
        if (game_event.base)
            game_event.type = GameEvent::EventType::place_card_to_base;
        if (game_event.deck)
            game_event.type = GameEvent::EventType::place_card_to_deck;
        if (!game_event.base && !game_event.deck)
            game_event.type = GameEvent::EventType::wait_event;
    } else {
        if (game_event.base)
            game_event.type = GameEvent::EventType::show_base;
        if (game_event.deck)
            game_event.type = GameEvent::EventType::show_deck;
    }
}

void Graphics::parse_events(GameEvent &game_event) {
    game_event = GameEvent(GameEvent::EventType::no_event, nullptr, nullptr, nullptr);
    sf::Event event;

    while (attributes.window.pollEvent(event) || game_event.type == GameEvent::EventType::wait_event) {
        get_event_parameters(event, game_event);
    }
}

void Graphics::process_events(Engine &engine) {
    GameEvent game_event;
    parse_events(game_event);
    if (game_event.type == GameEvent::EventType::close_window)
        attributes.window.close();
    else if (game_event.type == GameEvent::EventType::place_card_to_base) {
        engine.place_card(attributes.draw_player, game_event.card->get_id(), game_event.base->get_id());
        game_event = GameEvent();
    } else if (game_event.type == GameEvent::EventType::end_turn) {
        engine.end_turn(attributes.draw_player);
        game_event = GameEvent();
    }
}

} // namespace Mayhem

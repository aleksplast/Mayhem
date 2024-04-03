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
    type_ = GameType::OFLINE;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::VideoMode video_mode = sf::VideoMode::getFullscreenModes()[4];
    attributes.default_window_size = sf::Vector2u(video_mode.width, video_mode.height);
    attributes.window.create(video_mode, "Mayhem", sf::Style::Default, settings);
    attributes.window.setFramerateLimit(100);
}

const Graphics::GameEvent &Graphics::GameEvent::operator=(const GameEvent &rhs) {
    type = rhs.type;
    card = rhs.card;
    displayed_base = rhs.displayed_base;
    displayed_deck = rhs.displayed_deck;
    base = rhs.base;
    deck = rhs.deck;
    return *this;
}

const Graphics::GameEvent &Graphics::GameEvent::operator=(GameEvent &&rhs) {
    type = std::move(rhs.type);
    card = std::move(rhs.card);
    displayed_base = std::move(rhs.displayed_base);
    displayed_deck = std::move(rhs.displayed_deck);
    base = std::move(rhs.base);
    deck = std::move(rhs.deck);
    return *this;
}

void Graphics::launch_game(Engine &engine) {
    while (attributes.window.isOpen()) {
        attributes.window.clear();
        engine.draw(attributes);
        process_events(engine);
        attributes.window.display();
    }
}

PlayerCard *Graphics::pressed_card(const sf::Vector2f &pos) const {
    auto end_it = attributes.current_player_cards.rend();
    for (auto it = attributes.current_player_cards.rbegin(); it != end_it; ++it) {
        if ((*it)->sprite.getGlobalBounds().contains(pos.x, pos.y)) {
            return *it;
        }
    }
    return nullptr;
}

Base *Graphics::pressed_base(const sf::Vector2f &pos) const {
    auto end_it = attributes.active_bases.rend();
    for (auto it = attributes.active_bases.rbegin(); it != end_it; ++it) {
        if ((*it)->sprite.getGlobalBounds().contains(pos.x, pos.y)) {
            return *it;
        }
    }
    return nullptr;
}

Deck<PlayerCard *> *Graphics::pressed_deck(const sf::Vector2f &pos) const {
    auto end_it = attributes.current_decks.rend();
    for (auto it = attributes.current_decks.rbegin(); it != end_it; ++it) {
        if ((*it)->sprite.getGlobalBounds().contains(pos.x, pos.y)) {
            return *it;
        }
    }
    return nullptr;
}

Graphics::DrawingAttributes::ButtonType Graphics::pressed_button(const sf::Vector2f &pos) const {
    for (auto it : attributes.buttuns) {
        if (it.second.contains(pos)) {
            return it.first;
        }
    }
    return DrawingAttributes::ButtonType::no_type;
}

void Graphics::get_event_parameters(const sf::Event &event, GameEvent &game_event) const {
    if (event.type == sf::Event::Closed) {
        game_event = GameEvent(GameEvent::EventType::close_window);

    } else if (event.type == sf::Event::MouseButtonPressed) {

        if (event.mouseButton.button == sf::Mouse::Left) {

            sf::Vector2u window_size = attributes.window.getSize();
            sf::Vector2f mouse_pos =
                sf::Vector2f(event.mouseButton.x * attributes.default_window_size.x / window_size.x,
                             event.mouseButton.y * attributes.default_window_size.y / window_size.y);

            PlayerCard *card = pressed_card(mouse_pos);
            Base *base = pressed_base(mouse_pos);
            Deck<PlayerCard *> *deck = pressed_deck(mouse_pos);
            DrawingAttributes::ButtonType button_type = pressed_button(mouse_pos);

            if (button_type != DrawingAttributes::ButtonType::no_type) {
                game_event = GameEvent(GameEvent::EventType::end_turn);
            } else if (card) {
                game_event = GameEvent(GameEvent::EventType::wait_event, card, game_event.displayed_base,
                                       game_event.displayed_deck, nullptr, nullptr);
            } else if (base) {
                if (game_event.type == GameEvent::EventType::wait_event) {
                    game_event = GameEvent(GameEvent::EventType::place_card_to_base, game_event.card,
                                           game_event.displayed_base, game_event.displayed_deck, base, nullptr);
                } else {
                    game_event = GameEvent(GameEvent::EventType::show_base, nullptr, base, nullptr, nullptr, nullptr);
                }

            } else if (deck) {
                if (game_event.type == GameEvent::EventType::wait_event) {
                    game_event = GameEvent(GameEvent::EventType::place_card_to_deck, game_event.card,
                                           game_event.displayed_base, game_event.displayed_deck, nullptr, deck);
                } else {
                    game_event = GameEvent(GameEvent::EventType::show_deck, nullptr, nullptr, deck, nullptr, nullptr);
                }

            } else {
                game_event = GameEvent(GameEvent::EventType::no_event);
            }
        }
    }
}

void Graphics::parse_events(GameEvent &game_event) {
    sf::Event event;
    while (attributes.window.pollEvent(event) || game_event.type == GameEvent::EventType::wait_event) {
        get_event_parameters(event, game_event);
    }
}

void Graphics::process_events(Engine &engine) {
    static GameEvent game_event;
    parse_events(game_event);
    if (game_event.type == GameEvent::EventType::close_window) {
        game_event = GameEvent();
        attributes.window.close();
        return;

    } else if (game_event.type == GameEvent::EventType::place_card_to_base) {
        engine.place_card(attributes.draw_player, game_event.card->get_id(), game_event.base->get_id());
        game_event = GameEvent(GameEvent::EventType::no_event, nullptr, game_event.displayed_base,
                               game_event.displayed_deck, nullptr, nullptr);

    } else if (game_event.type == GameEvent::EventType::end_turn) {
        if (type_ == GameType::OFLINE) {
            attributes.draw_player = engine.end_turn(attributes.draw_player);
        } else {
            engine.end_turn(attributes.draw_player);
        }
        game_event = GameEvent();
    }

    if (game_event.displayed_base) {
        game_event.displayed_base->show_cards(attributes);

    } else if (game_event.displayed_deck)
        game_event.displayed_deck->show_cards(attributes);
}

} // namespace Mayhem

#include "graphics/graphics.hpp"
#include "core/base.h"
#include "core/card.h"
#include "engine/engine.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cstdio>
#include <ostream>

namespace Mayhem {

Graphics::Graphics(GameType type, uint16_t draw_player) : type_(type), draw_player_(draw_player){};

uint16_t Graphics::get_draw_player() const { return draw_player_; }

PlayerCard *Graphics::pressed_card(float x, float y) const {
    for (auto it : current_player_cards) {
        if (it->sprite.getGlobalBounds().contains(x, y)) {
            return it;
        }
    }
    return nullptr;
}

Base *Graphics::pressed_base(float x, float y) const {
    for (auto it : active_bases) {
        if (it->sprite.getGlobalBounds().contains(x, y)) {
            return it;
        }
    }
    return nullptr;
}

Deck<PlayerCard *> *Graphics::pressed_deck(float x, float y) const {
    for (auto it : current_decks) {
        if (it->sprite.getGlobalBounds().contains(x, y)) {
            return it;
        }
    }
    return nullptr;
}

void Graphics::parse_events(GameEvent &game_event) {
    game_event.type = GameEvent::EventType::no_event;
    sf::Event event;

    while (window.pollEvent(event) || game_event.type == GameEvent::EventType::wait_event) {
        if (event.type == sf::Event::Closed) {
            game_event.type = GameEvent::EventType::close_window;
            break;
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (!game_event.card)
                    game_event.card = pressed_card(event.mouseButton.x, event.mouseButton.y);

                if (!game_event.base)
                    game_event.base = pressed_base(event.mouseButton.x, event.mouseButton.y);
                if (!game_event.base)
                    game_event.deck = pressed_deck(event.mouseButton.x, event.mouseButton.y);
            }
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                game_event.type = GameEvent::EventType::end_turn;
            }
        }

        if (game_event.card) {
            if (game_event.base)
                game_event.type = GameEvent::EventType::place_card_to_base;
            if (game_event.deck)
                game_event.type = GameEvent::EventType::place_card_to_deck;
            if (!game_event.base && !game_event.deck) game_event.type = GameEvent::EventType::wait_event;
        } else {
            if (game_event.base)
                game_event.type = GameEvent::EventType::show_base;
            if (game_event.deck)
                game_event.type = GameEvent::EventType::show_deck;
        }
    }
}

void Graphics::process_events(Engine &engine, GameEvent &game_event) {
    parse_events(game_event);
    if (game_event.type == GameEvent::EventType::close_window)
        window.close();
    else
    if (game_event.type == GameEvent::EventType::place_card_to_base) {
        engine.place_card(draw_player_, game_event.card->get_id(), game_event.base->get_id());
        game_event = GameEvent();
    } else
    if (game_event.type == GameEvent::EventType::end_turn) {
        engine.end_turn(draw_player_);
        game_event = GameEvent();
    }
}

} // namespace Mayhem

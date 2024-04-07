#include "SFML/Graphics.hpp"
#include "core/card.h"
#include "engine/engine.h"
#include "engine/player.h"
#include "engine/playground.h"
#include "graphics/graphics.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <iterator>

namespace Mayhem {

void Player::draw(Graphics::DrawingAttributes &attributes, const sf::FloatRect &rect, const float angle) // draw cards
{
    Drawable::draw(attributes.window, rect, angle);

    sf::Vector2f place_size = sf::Vector2f(rect.width * Graphics::LocationSettings::cards_place_to_player_x,
                                           rect.height * Graphics::LocationSettings::cards_place_to_player_y);
    sf::Vector2f card_size = sf::Vector2f(rect.width * Graphics::LocationSettings::card_scale_to_player_x,
                                          rect.height * Graphics::LocationSettings::card_scale_to_player_y);

    float index_card = 1;
    float num_cards = static_cast<float>(hand_.size());

    if (angle == 0.0) {
        for (auto curr_card = hand_.begin(); curr_card != hand_.end(); ++curr_card, ++index_card) {
            (*curr_card)
                ->draw(attributes.window,
                       sf::FloatRect(rect.left + rect.width / 2 +
                                         (index_card - (num_cards + 1.0) / 2) * place_size.x / (num_cards + 1.0) -
                                         card_size.x / 2,
                                     rect.top + rect.height / 2 - card_size.y / 2, card_size.x, card_size.y),
                       angle);
        }
        deck_.draw(attributes.window,
                   sf::FloatRect(rect.left - card_size.x / 2, rect.top + rect.height / 2 - card_size.y / 2, card_size.x,
                                 card_size.y),
                   angle);
        dump_deck_.draw(attributes.window,
                        sf::FloatRect(rect.left + rect.width - card_size.x / 2,
                                      rect.top + rect.height / 2 - card_size.y / 2, card_size.x, card_size.y),
                        angle);

    } else if (angle == 90.0) {
        for (auto curr_card = hand_.begin(); curr_card != hand_.end(); ++curr_card, ++index_card) {
            (*curr_card)
                ->draw(attributes.window,
                       sf::FloatRect(rect.left + rect.width / 2 - card_size.x / 2,
                                     rect.top + rect.height / 2 +
                                         (index_card - (num_cards + 1.0) / 2) * place_size.x / (num_cards + 1.0) -
                                         card_size.y / 2,
                                     card_size.x, card_size.y),
                       angle);
        }
        deck_.draw(attributes.window,
                   sf::FloatRect(rect.left + rect.width / 2 - card_size.x / 2,
                                 rect.top + rect.height / 2 - rect.width / 2 - card_size.y / 2, card_size.x,
                                 card_size.y),
                   angle);
        dump_deck_.draw(attributes.window,
                        sf::FloatRect(rect.left + rect.width / 2 - card_size.x / 2,
                                      rect.top + rect.height / 2 + rect.width / 2 - card_size.y / 2, card_size.x,
                                      card_size.y),
                        angle);

    } else if (angle == 180.0) {
        for (auto curr_card = hand_.begin(); curr_card != hand_.end(); ++curr_card, ++index_card) {
            (*curr_card)
                ->draw(attributes.window,
                       sf::FloatRect(rect.left + rect.width / 2 -
                                         (index_card - (num_cards + 1.0) / 2) * place_size.x / (num_cards + 1.0) -
                                         card_size.x / 2,
                                     rect.top + rect.height / 2 - card_size.y / 2, card_size.x, card_size.y),
                       angle);
        }
        deck_.draw(attributes.window,
                   sf::FloatRect(rect.left + rect.width - card_size.x / 2, rect.top + rect.height / 2 - card_size.y / 2,
                                 card_size.x, card_size.y),
                   angle);
        dump_deck_.draw(attributes.window,
                        sf::FloatRect(rect.left - card_size.x / 2, rect.top + rect.height / 2 - card_size.y / 2,
                                      card_size.x, card_size.y),
                        angle);

    } else { // angle == 270.0
        for (auto curr_card = hand_.begin(); curr_card != hand_.end(); ++curr_card, ++index_card) {
            (*curr_card)
                ->draw(attributes.window,
                       sf::FloatRect(rect.left + rect.width / 2 - card_size.x / 2,
                                     rect.top + rect.height / 2 -
                                         (index_card - (num_cards + 1.0) / 2) * place_size.x / (num_cards + 1.0) -
                                         card_size.y / 2,
                                     card_size.x, card_size.y),
                       angle);
        }
        deck_.draw(attributes.window,
                   sf::FloatRect(rect.left + rect.width / 2 - card_size.x / 2,
                                 rect.top + rect.height / 2 + rect.width / 2 - card_size.y / 2, card_size.x,
                                 card_size.y),
                   angle);
        dump_deck_.draw(attributes.window,
                        sf::FloatRect(rect.left + rect.width / 2 - card_size.x / 2,
                                      rect.top + rect.height / 2 - rect.width / 2 - card_size.y / 2, card_size.x,
                                      card_size.y),
                        angle);
    }

    if (angle == 0.0) {
        for (auto it : hand_) {
            attributes.current_player_cards.push_back(it);
        }
        attributes.current_decks.push_back(&dump_deck_);
        attributes.current_decks.push_back(&deck_);
    }
}

void Playground::draw_active_bases(Graphics::DrawingAttributes &attributes, const sf::FloatRect &rect) {
    uint16_t num_base = 1;
    uint16_t num_active_bases = active_bases_.size();
    sf::Vector2f base_size = sf::Vector2f(rect.width * Graphics::LocationSettings::bases_scale_to_place_x,
                                          rect.height * Graphics::LocationSettings::bases_scale_to_place_y);
    const float base_shift = rect.width / static_cast<float>(num_active_bases + 1);
    for (auto curr_base = active_bases_.begin(); curr_base != active_bases_.end(); ++curr_base, ++num_base) {
        Base &base = **curr_base;
        base.draw(
            attributes.window,
            sf::FloatRect(rect.left + base_shift * num_base - base_size.x / 2, rect.top, base_size.x, base_size.y), 0);
    }
}

void Playground::draw_button(sf::RenderWindow &window, const sf::FloatRect &rect) {
    sf::Vector2f end_turn_size = sf::Vector2f(rect.width * Graphics::LocationSettings::end_turn_scale_to_playground_x,
                                              rect.height * Graphics::LocationSettings::end_turn_scale_to_playground_y);
    end_turn_.set_possition(
        sf::IntRect(static_cast<int>(rect.left + rect.width * Graphics::LocationSettings::end_turn_pos_to_playground_x -
                                     end_turn_size.x / 2),
                    static_cast<int>(rect.top + rect.height * Graphics::LocationSettings::end_turn_pos_to_playground_y -
                                     end_turn_size.y / 2),
                    static_cast<int>(end_turn_size.x), static_cast<int>(end_turn_size.y)));

    end_turn_.set_text_color(sf::Color::Red);
    end_turn_.set_background_color(0, 140, 140, 0);
    end_turn_.draw(window);
}

void Playground::draw(Graphics::DrawingAttributes &attributes, const sf::FloatRect &rect,
                      const float angle) // draw bases, players
{
    Drawable::draw(attributes.window, rect, angle);

    uint16_t num_players = players_.size();
    uint16_t drawing_player = attributes.draw_player;
    sf::Vector2f player_size = sf::Vector2f(rect.width * Graphics::LocationSettings::player_scale_to_playground_x,
                                            rect.height * Graphics::LocationSettings::player_scale_to_playground_y);
    do {
        uint16_t drawing_id = (num_players + drawing_player - attributes.draw_player) % num_players;
        switch (drawing_id) {
        case 0:
            players_[drawing_player]->draw(
                attributes,
                sf::FloatRect(rect.left + rect.width / 2 -
                                  Graphics::LocationSettings::player_increase * player_size.x / 2,
                              rect.top + rect.height - Graphics::LocationSettings::player_increase * player_size.y / 2,
                              Graphics::LocationSettings::player_increase * player_size.x,
                              Graphics::LocationSettings::player_increase * player_size.y),
                0);
            break;
        case 1:
            players_[drawing_player]->draw(attributes,
                                           sf::FloatRect(rect.left + (rect.width - player_size.x) / 2,
                                                         rect.top - player_size.y / 2, player_size.x, player_size.y),
                                           180);
            break;
        case 2:
            players_[drawing_player]->draw(attributes,
                                           sf::FloatRect(rect.left - player_size.x / 2,
                                                         rect.top + (rect.height - player_size.y) / 2, player_size.x,
                                                         player_size.y),
                                           90);
            break;
        case 3:
            players_[drawing_player]->draw(attributes,
                                           sf::FloatRect(rect.left + rect.width - player_size.x / 2,
                                                         rect.top + rect.height / 2 - player_size.y / 2, player_size.x,
                                                         player_size.y),
                                           270);
            break;
        }
        drawing_player = (drawing_player + 1) % num_players;
    } while (drawing_player != attributes.draw_player);

    draw_active_bases(
        attributes,
        sf::FloatRect(rect.left + rect.width * (1.0 - Graphics::LocationSettings::bases_place_to_playground_x) / 2,
                      rect.top + rect.height * Graphics::LocationSettings::bases_pos_to_playground,
                      rect.width * Graphics::LocationSettings::bases_place_to_playground_x,
                      rect.height * Graphics::LocationSettings::bases_plase_to_playground_y));

    draw_button(attributes.window, rect);

    for (auto it : active_bases_) {
        attributes.active_bases.push_back(it);
    }

    attributes.buttuns.push_back(
        std::make_pair(Graphics::DrawingAttributes::ButtonType::end_tern, end_turn_.get_global_bounds()));
}

void Engine::draw(Graphics::DrawingAttributes &attributes) // draw Playground
{
    attributes.active_bases.clear();
    attributes.current_player_cards.clear();
    attributes.current_decks.clear();
    attributes.buttuns.clear();

    sf::Vector2f window_size = sf::Vector2f(attributes.default_window_size);
    playground.draw(attributes, sf::FloatRect(0.0, 0.0, window_size.x, window_size.y), 0);
}
} // namespace Mayhem

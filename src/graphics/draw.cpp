#include "core/actions.h"
#include "core/card.h"
#include "engine/engine.h"
#include "engine/player.h"
#include "engine/playground.h"
#include "graphics/graphics_model.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace Mayhem {

void Minion::draw(sf::RenderWindow &window, const sf::FloatRect &rect, const float angle) {
    Drawable::draw(window, rect, angle);

    if (angle == 0.0f) {
        using Scope = GraphicsModel::Settings::Rendering::Button::Power::Scale;
        power_picture_.set_position(sf::IntRect(static_cast<int>(rect.left), static_cast<int>(rect.top),
                                                static_cast<int>(rect.width * Scope::x),
                                                static_cast<int>(rect.height * Scope::y)));
        power_picture_.set_string(std::to_string(power_));
        power_picture_.set_char_size(25);
        power_picture_.draw(window);
    }
}

void Base::draw(sf::RenderWindow &window, const sf::FloatRect &rect, const float angle) {
    Drawable::draw(window, rect, angle);

    using Scope = GraphicsModel::Settings::Rendering::Button::UnitsPower;
    units_power_.set_string("POWER: " + std::to_string(get_current_power()));
    sf::Vector2f power_size = sf::Vector2f(rect.width * Scope::Scale::x, rect.height * Scope::Scale::y);
    units_power_.set_position(
        sf::IntRect(static_cast<int>(rect.left + rect.width * Scope::Position::x - power_size.x / 2),
                    static_cast<int>(rect.top + rect.height * Scope::Position::y - power_size.y / 2),
                    static_cast<int>(power_size.x), static_cast<int>(power_size.y)));
    units_power_.draw(window);
}

void Player::draw(sf::RenderWindow &window, const sf::FloatRect &rect, const float angle) {
    sprite.setPosition(rect.left + rect.width / 2, rect.top + rect.height / 2);
    const sf::Texture *texture = sprite.getTexture();
    sf::Vector2f texture_size = sf::Vector2f(texture->getSize());
    sprite.setScale(rect.width / texture_size.x, rect.height / texture_size.y);
    sprite.setRotation(angle);

    if (is_pressed)
        sprite.setColor(sf::Color(50, 200, 50, 100));
    else
        sprite.setColor(sf::Color(0, 0, 0, 100));

    window.draw(sprite);
}

void Player::draw(GraphicsModel::Data::Attributes &attributes, const sf::FloatRect &rect,
                  const float angle) // draw cards
{
    draw(attributes.window, rect, angle);

    using Scope = GraphicsModel::Settings::Rendering::Player::CardsPlace;
    using PointsScope = GraphicsModel::Settings::Rendering::Button::Points;

    sf::Vector2f place_size = sf::Vector2f(rect.width * Scope::Scale::x, rect.height * Scope::Scale::y);
    sf::Vector2f card_size = sf::Vector2f(place_size.x * Scope::Card::Scale::x, place_size.y * Scope::Card::Scale::y);

    float index_card = 1;
    float num_cards = static_cast<float>(hand_.size());

    points_widget_.set_string("POINTS: " + std::to_string(points_));
    sf::Vector2f points_size;

    if (angle == 0.0f) {
        attributes.current_decks.push_back(&hand_);
        points_size = sf::Vector2f(static_cast<float>(rect.width) * PointsScope::Scale::x,
                                   static_cast<float>(rect.height) * PointsScope::Scale::y);
        points_widget_.set_position(sf::IntRect(static_cast<int>(rect.left),
                                                static_cast<int>(rect.top - points_size.y / 6),
                                                static_cast<int>(points_size.x), static_cast<int>(points_size.y)));
        points_widget_.set_char_size(25);

        for (auto curr_card = hand_.begin(); curr_card != hand_.end(); ++curr_card, ++index_card) {
            (*curr_card)->set_main_texture();
            (*curr_card)
                ->draw(attributes.window,
                       sf::FloatRect(rect.left + rect.width / 2 +
                                         (index_card - (num_cards + 1.0f) / 2) * place_size.x / (num_cards + 1.0f) -
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

    } else if (angle == 90.0f) {
        points_size = sf::Vector2f(rect.width * PointsScope::Scale::x, rect.height * PointsScope::Scale::y);
        points_widget_.set_position(sf::IntRect(static_cast<int>(rect.left + rect.width / 2 + rect.height / 2),
                                                static_cast<int>(rect.top + rect.height / 2 - rect.width / 2),
                                                static_cast<int>(points_size.x), static_cast<int>(points_size.y)));
        points_widget_.set_char_size(20);

        for (auto curr_card = hand_.begin(); curr_card != hand_.end(); ++curr_card, ++index_card) {
            (*curr_card)->set_extra_texture();
            (*curr_card)
                ->draw(attributes.window,
                       sf::FloatRect(rect.left + rect.width / 2 - card_size.x / 2,
                                     rect.top + rect.height / 2 +
                                         (index_card - (num_cards + 1.0f) / 2) * place_size.x / (num_cards + 1.0f) -
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

    } else if (angle == 180.0f) {
        points_size = sf::Vector2f(rect.width * PointsScope::Scale::x, rect.height * PointsScope::Scale::y);
        points_widget_.set_position(sf::IntRect(static_cast<int>(rect.left + rect.width - points_size.x),
                                                static_cast<int>(rect.top + rect.height - points_size.y),
                                                static_cast<int>(points_size.x), static_cast<int>(points_size.y)));
        points_widget_.set_char_size(20);

        for (auto curr_card = hand_.begin(); curr_card != hand_.end(); ++curr_card, ++index_card) {
            (*curr_card)->set_extra_texture();
            (*curr_card)
                ->draw(attributes.window,
                       sf::FloatRect(rect.left + rect.width / 2 -
                                         (index_card - (num_cards + 1.0f) / 2) * place_size.x / (num_cards + 1.0f) -
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
        points_size = sf::Vector2f(rect.width * PointsScope::Scale::x, rect.height * PointsScope::Scale::y);
        points_widget_.set_position(
            sf::IntRect(static_cast<int>(rect.left + rect.width / 2 - rect.height / 2 - points_size.x),
                        static_cast<int>(rect.top + rect.height / 2 - rect.width / 2), static_cast<int>(points_size.x),
                        static_cast<int>(points_size.y)));
        points_widget_.set_char_size(20);

        for (auto curr_card = hand_.begin(); curr_card != hand_.end(); ++curr_card, ++index_card) {
            (*curr_card)->set_extra_texture();
            (*curr_card)
                ->draw(attributes.window,
                       sf::FloatRect(rect.left + rect.width / 2 - card_size.x / 2,
                                     rect.top + rect.height / 2 -
                                         (index_card - (num_cards + 1.0f) / 2) * place_size.x / (num_cards + 1.0f) -
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

    points_widget_.draw(attributes.window);

    if (angle == 0.0f) {
        for (auto it : hand_) {
            attributes.current_player_cards.push_back(it);
        }
        attributes.current_decks.push_back(&dump_deck_);
        attributes.current_decks.push_back(&deck_);
    }
}

void Playground::draw_active_bases(GraphicsModel::Data::Attributes &attributes, const sf::FloatRect &rect) {
    size_t num_base = 1;
    size_t num_active_bases = active_bases_.size();

    using Scope = GraphicsModel::Settings::Rendering::BasesPlace::Base;
    sf::Vector2f base_size = sf::Vector2f(rect.width * Scope::Scale::x, rect.height * Scope::Scale::y);
    const float base_shift = rect.width / static_cast<float>(num_active_bases + 1);
    for (auto curr_base = active_bases_.begin(); curr_base != active_bases_.end(); ++curr_base, ++num_base) {
        Base &base = **curr_base;
        base.draw(attributes.window,
                  sf::FloatRect(rect.left + base_shift * static_cast<float>(num_base) - base_size.x / 2, rect.top,
                                base_size.x, base_size.y),
                  0);
    }
}

void Playground::draw_button(sf::RenderWindow &window, const sf::FloatRect &rect) {
    using Scope = GraphicsModel::Settings::Rendering::Button;
    sf::Vector2f end_turn_size =
        sf::Vector2f(rect.width * Scope::EndTurn::Scale::x, rect.height * Scope::EndTurn::Scale::y);
    end_turn_.set_position(
        sf::IntRect(static_cast<int>(rect.left + rect.width * Scope::EndTurn::Position::x - end_turn_size.x / 2),
                    static_cast<int>(rect.top + rect.height * Scope::EndTurn::Position::y - end_turn_size.y / 2),
                    static_cast<int>(end_turn_size.x), static_cast<int>(end_turn_size.y)));

    end_turn_.set_text_color(sf::Color::Red);
    end_turn_.set_background_color(0, 140, 140, 0);
    end_turn_.draw(window);
}

void Playground::draw(GraphicsModel::Data::Attributes &attributes, const sf::FloatRect &rect,
                      const float angle) // draw bases, players
{
    Drawable::draw(attributes.window, rect, angle);

    using Scope = GraphicsModel::Settings::Rendering;
    size_t num_players = players_.size();
    size_t drawing_player = attributes.draw_player;
    sf::Vector2f player_size =
        sf::Vector2f(rect.width * Scope::Player::Scale::x, rect.height * Scope::Player::Scale::y);
    do {
        size_t drawing_id = (num_players + drawing_player - attributes.draw_player) % num_players;
        switch (drawing_id) {
        case 0:
            players_[drawing_player]->draw(
                attributes,
                sf::FloatRect(rect.left + rect.width / 2 - Scope::Player::increase * player_size.x / 2,
                              rect.top + rect.height - Scope::Player::increase * player_size.y / 2,
                              Scope::Player::increase * player_size.x, Scope::Player::increase * player_size.y),
                0.0f);
            break;
        case 1:
            players_[drawing_player]->draw(attributes,
                                           sf::FloatRect(rect.left + (rect.width - player_size.x) / 2,
                                                         rect.top - player_size.y / 2, player_size.x, player_size.y),
                                           180.0f);
            break;
        case 2:
            players_[drawing_player]->draw(attributes,
                                           sf::FloatRect(rect.left - player_size.x / 2,
                                                         rect.top + (rect.height - player_size.y) / 2, player_size.x,
                                                         player_size.y),
                                           90.0f);
            break;
        case 3:
            players_[drawing_player]->draw(attributes,
                                           sf::FloatRect(rect.left + rect.width - player_size.x / 2,
                                                         rect.top + rect.height / 2 - player_size.y / 2, player_size.x,
                                                         player_size.y),
                                           270.0f);
            break;
        default:
            break;
        }
        drawing_player = (drawing_player + 1) % num_players;
    } while (drawing_player != attributes.draw_player);

    draw_active_bases(
        attributes,
        sf::FloatRect(rect.left + rect.width * (Scope::BasesPlace::Position::x - Scope::BasesPlace::Scale::x / 2),
                      rect.top + rect.height * (Scope::BasesPlace::Position::y - Scope::BasesPlace::Scale::y / 2),
                      rect.width * Scope::BasesPlace::Scale::x, rect.height * Scope::BasesPlace::Scale::y));

    draw_button(attributes.window, rect);

    if (attributes.popping_up_card) {
        using PopUpScope = GraphicsModel::Settings::Rendering::PopUpCard;
        sf::Vector2f size = sf::Vector2f(rect.width * PopUpScope::Scale::x, rect.height * PopUpScope::Scale::y);
        sf::FloatRect card_rect =
            sf::FloatRect(rect.left + rect.width * PopUpScope::Position::x - size.x / 2,
                          rect.top + rect.height * PopUpScope::Position::y - size.y / 2, size.x, size.y);

        if (popping_up_card)
            delete popping_up_card;

        if (Minion *minion = dynamic_cast<Minion *>(attributes.popping_up_card); minion)
            popping_up_card = dynamic_cast<PlayerCard *>(new Minion(*minion));
        else if (Action *action = dynamic_cast<Action *>(attributes.popping_up_card); action)
            popping_up_card = new Action(*action);

        popping_up_card->release();
        popping_up_card->draw(attributes.window, card_rect, 0.0f);
    } else {
        if (popping_up_card)
            delete popping_up_card;
        popping_up_card = nullptr;
    }

    for (auto it : active_bases_)
        attributes.active_bases.push_back(it);

    if (attributes.shown_place.first)
        attributes.shown_place.first->show_cards(attributes);

    attributes.buttuns.push_back(std::make_pair(Button::Type::end_turn, end_turn_.get_global_bounds()));
}

void Engine::draw(GraphicsModel::Data::Attributes &attributes) // draw Playground
{
    attributes.active_bases.clear();
    attributes.current_player_cards.clear();
    attributes.current_decks.clear();
    attributes.buttuns.clear();
    attributes.shown_place.second.clear();

    sf::Vector2f window_size = sf::Vector2f(attributes.default_window_size);
    playground.draw(attributes, sf::FloatRect(0.0, 0.0, window_size.x, window_size.y), 0.0f);
}
} // namespace Mayhem

#include "SFML/Graphics.hpp"
#include "core/card.h"
#include "engine/engine.h"
#include "engine/player.h"
#include "engine/playground.h"
#include <SFML/System/Vector2.hpp>

namespace Mayhem {

void Player::set_decks_position(Graphics &graphics) {
    sf::Vector2f player_pos = sprite.getPosition();
    sf::Vector2f player_size =
        sf::Vector2f(texture.getSize().x * sprite.getScale().x, texture.getSize().y * sprite.getScale().y);

    int num_cards = hand_.size();
    auto rotation = sprite.getRotation();
    sf::Vector2f cards_place(player_size.x * graphics.cards_place_to_player,
                             player_size.y * graphics.cards_place_to_player);
    const float shift = cards_place.x / static_cast<float>(num_cards + 1);
    int num_card = 1;
    if (rotation == 0.0) {
        for (auto curr_card = hand_.begin(); curr_card != hand_.end(); ++curr_card, ++num_card) {
            (*curr_card)
                ->sprite.setPosition(player_pos.x + static_cast<float>(2 * num_card - num_cards) * shift / 2,
                                     player_pos.y);
        }
        deck_.sprite.setPosition(player_pos.x + player_size.x / 2, player_pos.y);
        dump_deck_.sprite.setPosition(player_pos.x - player_size.x / 2, player_pos.y);

    } else if (rotation == 90.0) {
        for (auto curr_card = hand_.begin(); curr_card != hand_.end(); ++curr_card, ++num_card) {
            (*curr_card)
                ->sprite.setPosition(player_pos.x,
                                     player_pos.y + static_cast<float>(2 * num_card - num_cards) * shift / 2);
        }
        deck_.sprite.setPosition(player_pos.x, player_pos.y - player_size.x / 2);
        dump_deck_.sprite.setPosition(player_pos.x, player_pos.y + player_size.x / 2);

    } else if (rotation == 180.0) {
        for (auto curr_card = hand_.begin(); curr_card != hand_.end(); ++curr_card, ++num_card) {
            (*curr_card)
                ->sprite.setPosition(player_pos.x - static_cast<float>(2 * num_card - num_cards) * shift / 2,
                                     player_pos.y);
        }
        deck_.sprite.setPosition(player_pos.x - player_size.x / 2, player_pos.y);
        dump_deck_.sprite.setPosition(player_pos.x + player_size.x / 2, player_pos.y);

    } else if (rotation == 270.0) {
        for (auto curr_card = hand_.begin(); curr_card != hand_.end(); ++curr_card, ++num_card) {
            (*curr_card)
                ->sprite.setPosition(player_pos.x,
                                     player_pos.y - static_cast<float>(2 * num_card - num_cards) * shift / 2);
        }
        deck_.sprite.setPosition(player_pos.x, player_pos.y + player_size.x / 2);
        dump_deck_.sprite.setPosition(player_pos.x, player_pos.y - player_size.x / 2);
    }
}

void Player::set_decks_rotation() {
    auto player_rotation = sprite.getRotation();
    for (auto curr_card = hand_.begin(); curr_card != hand_.end(); ++curr_card) {
        (*curr_card)->sprite.setRotation(player_rotation);
    }
    deck_.sprite.setRotation(player_rotation);
    dump_deck_.sprite.setRotation(player_rotation);
}

void Player::set_decks_scale(Graphics &graphics) {
    sf::Vector2f player_size =
        sf::Vector2f(texture.getSize().x * sprite.getScale().x, texture.getSize().y * sprite.getScale().y);

    for (auto curr_card = hand_.begin(); curr_card != hand_.end(); ++curr_card) {
        sf::Vector2u texture_size = (*curr_card)->texture.getSize();
        const float card_scale = player_size.x * graphics.card_scale_to_player / texture_size.x;
        (*curr_card)->sprite.setScale(card_scale, card_scale);
    }
    const float deck_scale = player_size.x * graphics.card_scale_to_player / deck_.texture.getSize().x;
    const float dump_deck_scale = player_size.x * graphics.card_scale_to_player / dump_deck_.texture.getSize().x;

    deck_.sprite.setScale(deck_scale, deck_scale);
    dump_deck_.sprite.setScale(dump_deck_scale, dump_deck_scale);
}

void Player::draw(Graphics &graphics) // draw cards
{
    set_decks_position(graphics);
    set_decks_scale(graphics);
    set_decks_rotation();

    graphics.window.draw(deck_.sprite);
    graphics.window.draw(dump_deck_.sprite);
    for (auto curr_card = hand_.begin(); curr_card != hand_.end(); ++curr_card)
        graphics.window.draw((*curr_card)->sprite);
}

void Playground::set_player_position(Graphics &graphics, uint16_t player_id) {
    sf::Vector2f playground_size =
        sf::Vector2f(texture.getSize().x * sprite.getScale().x, texture.getSize().y * sprite.getScale().y);
    auto &curr_sprite = players_[player_id]->sprite;
    switch (player_id) {
    case 0:
        curr_sprite.setPosition(playground_size.x / 2, playground_size.y);
        break;
    case 1:
        curr_sprite.setPosition(playground_size.x / 2, 0.0);
        break;
    case 2:
        curr_sprite.setPosition(0.0, playground_size.y / 2);
        break;
    case 3:
        curr_sprite.setPosition(playground_size.x, playground_size.y / 2);
        break;
    default:
        break;
    }
}

void Playground::set_player_rotate(Graphics &graphics, uint16_t player_id) {
    auto &curr_sprite = players_[player_id]->sprite;
    switch (player_id) {
    case 1:
        curr_sprite.setRotation(180);
        break;
    case 2:
        curr_sprite.setRotation(90);
        break;
    case 3:
        curr_sprite.setRotation(270);
        break;
    default:
        break;
    }
}

void Playground::set_player_scale(Graphics &graphics, uint16_t player_id) {
    sf::Vector2f playground_size =
        sf::Vector2f(texture.getSize().x * sprite.getScale().x, texture.getSize().y * sprite.getScale().y);
    auto texture_size = players_[player_id]->texture.getSize();
    auto &curr_sprite = players_[player_id]->sprite;

    if (player_id == 0) {
        curr_sprite.setScale(
            graphics.player_increase * playground_size.x * graphics.player_scale_to_playground / texture_size.x,
            graphics.player_increase * playground_size.y * graphics.player_scale_to_playground / texture_size.y);
    } else {
        curr_sprite.setScale(playground_size.x * graphics.player_scale_to_playground / texture_size.x,
                             playground_size.y * graphics.player_scale_to_playground / texture_size.y);
    }
}

void Playground::draw_active_bases(Graphics &graphics) {
    uint16_t num_base = 1;
    uint16_t num_active_bases = active_bases_.size();

    sf::Vector2f playground_size(texture.getSize().x * sprite.getScale().x, texture.getSize().y * sprite.getScale().y);
    sf::Vector2f place_size(playground_size.x * graphics.bases_place_to_playground,
                            playground_size.y * graphics.bases_place_to_playground);

    for (auto curr_base = active_bases_.begin(); curr_base != active_bases_.end(); ++curr_base, ++num_base) {
        Base &base = **curr_base;
        base.sprite.setPosition((playground_size.x - place_size.x) / 2 + static_cast<float>(num_base) * place_size.x /
                                                                             static_cast<float>(num_active_bases + 1),
                                playground_size.y * graphics.bases_pos_to_playground);
        const float base_scale = graphics.base_shift_to_playground * playground_size.x / base.texture.getSize().x;
        base.sprite.setScale(base_scale, base_scale);
        graphics.window.draw(base.sprite);
    }
}

void Playground::draw(Graphics &graphics) // draw bases, players
{
    uint16_t num_players = players_.size();
    uint16_t draw_player = graphics.get_draw_player();
    auto window_size = graphics.window.getSize();
    do {
        uint16_t player_id = (num_players + draw_player - graphics.get_draw_player()) % num_players;
        set_player_position(graphics, player_id);
        set_player_rotate(graphics, player_id);
        set_player_scale(graphics, player_id);
        graphics.window.draw(players_[draw_player]->sprite);
        players_[player_id]->draw(graphics);
        draw_player = (draw_player + 1) % num_players;
    } while (draw_player != graphics.get_draw_player());

    draw_active_bases(graphics);
}

void Engine::draw(Graphics &graphics) // draw Playground
{
    graphics.window.draw(playground.sprite);
    playground.draw(graphics);
}
} // namespace Mayhem

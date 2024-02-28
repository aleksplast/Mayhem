#include "SFML/Graphics.hpp"
#include "core/card.h"
#include "core/game_core.h"
#include <SFML/System/Vector2.hpp>

namespace Mayhem {

void Player::draw(Graphics &graphics) // draw cards
{}

void Playground::set_player_position(Graphics &graphics, uint16_t player_id) {
    sf::Vector2f playground_size =
        sf::Vector2f(texture.getSize().x * sprite.getScale().x, texture.getSize().y * sprite.getScale().y);
    auto &curr_sprite = players_[player_id].sprite;
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

void Playground::set_rotate(Graphics &graphics, uint16_t player_id) {
    auto &curr_sprite = players_[player_id].sprite;
    switch (player_id) {
    case 1:
        curr_sprite.setRotation(180);
        break;
    case 2:
        curr_sprite.setRotation(90);
        break;
    case 3:
        curr_sprite.setRotation(-90);
        break;
    default:
        break;
    }
}

void Playground::set_scale(Graphics &graphics, uint16_t player_id) {
    sf::Vector2f playground_size =
        sf::Vector2f(texture.getSize().x * sprite.getScale().x, texture.getSize().y * sprite.getScale().y);
    auto texture_size = players_[player_id].texture.getSize();
    auto &curr_sprite = players_[player_id].sprite;

    if (player_id == 0) {
        curr_sprite.setScale(graphics.get_player_increase() * playground_size.x /
                                 (graphics.get_num_players_per_side() * texture_size.x),
                             graphics.get_player_increase() * playground_size.y /
                                 (graphics.get_num_players_per_side() * texture_size.y));
    } else {
        curr_sprite.setScale(playground_size.x / (graphics.get_num_players_per_side() * texture_size.x),
                             playground_size.y / (graphics.get_num_players_per_side() * texture_size.y));
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
        set_rotate(graphics, player_id);
        set_scale(graphics, player_id);
        players_[player_id].draw(graphics);
        graphics.window.draw(players_[draw_player].sprite);
        draw_player = (draw_player + 1) % num_players;
    } while (draw_player != graphics.get_draw_player());
}

void Engine::draw(Graphics &graphics) // draw Playground
{
    graphics.window.draw(playground.sprite);
    playground.draw(graphics);
}
} // namespace Mayhem

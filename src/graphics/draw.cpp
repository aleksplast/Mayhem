#include "../../include/core/card.h"
#include "../../include/core/game_core.h"

namespace Mayhem {

void Base::draw(Graphics &graphics) // draw cards
{

}

void Player::draw(Graphics &graphics) // draw cards
{

}

void Playground::draw(Graphics &graphics) // draw bases, players 
{
    uint16_t num_players = players_.size();
    uint16_t draw_player = graphics.get_draw_player();
    auto texture_size = players_[0].texture.getSize();
    auto window_size = graphics.window.getSize();
    float indent_y = texture_size.y / 2; 
    do
    {
        auto &curr_sprite = players_[draw_player].sprite;
        switch ((num_players + draw_player - graphics.get_draw_player()) % num_players)
        {
        case 0:
            curr_sprite.setPosition(window_size.x / 2, window_size.y - indent_y);
            curr_sprite.setOrigin(texture_size.x / 2, texture_size.y / 2);
            curr_sprite.setScale(sf::Vector2f(graphics.get_player_increase(), graphics.get_player_increase()));
            break;
        case 1:
            curr_sprite.setPosition(window_size.x / 2, 0.0);
            curr_sprite.setRotation(180);
            break;
        case 2:
            curr_sprite.setPosition(0.0, window_size.y / 2);
            curr_sprite.setRotation(90);
            break;
        case 3:
            curr_sprite.setPosition(window_size.x, window_size.y / 2);
            curr_sprite.setRotation(-90);
            break;
        }
        graphics.window.draw(curr_sprite);
        draw_player = (draw_player + 1) % num_players;
    } while (draw_player != graphics.get_draw_player());
    
}

void Engine::draw(Graphics &graphics) // draw Playground
{
    graphics.window.draw(playground.sprite);
    playground.draw(graphics);
}
} // namespace Mayhem
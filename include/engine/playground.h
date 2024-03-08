#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include "core/base.h"
#include "core/card.h"
#include "core/deck.h"
#include "core/entity.h"
#include "player.h"
#include "graphics/graphics.hpp"
#include "parser/parser.h"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

namespace Mayhem {

using LeaderBoard_t = std::map<uint32_t, uint32_t>;

class Playground : public Drawable {
  private:
    Deck<Base *> active_bases_;
    Deck<Base *> bases_;
    Deck<Base *> dump_;

    std::vector<Player *> players_;

  public:
    Playground() = delete;

    Playground(Graphics &graphics, std::vector<Entity *> &entities)
        : Drawable("../src/graphics/images/playground.jpg"), bases_(), active_bases_(), dump_() {
        auto window_size = graphics.window.getSize();
        sprite.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2));
        sprite.setScale(static_cast<float>(window_size.x) / texture.getSize().x,
                        static_cast<float>(window_size.y) / texture.getSize().y);

        for (int i = 0; i < 4; i++) {
            Player *player = new Player(graphics, i);
            players_.push_back(player);
            entities.push_back(player);
        }
    }

    std::vector<Base *> check_bases();
    LeaderBoard_t capture_base(Base *base);
    void clear_base(Base *base); // FIXME: just mock
    void destroy_base(Base *base);
    void set_new_base();
    uint16_t get_number_of_players() { return players_.size(); };
    void gain_base_on_start(Base *base);
    void dump_state(std::ofstream &os) const;
    ~Playground() = default;

  public: // graphics functions
    void set_player_position(Graphics &graphics, uint16_t player_id);
    void set_player_rotate(Graphics &graphics, uint16_t player_id);
    void set_player_scale(Graphics &graphics, uint16_t player_id);
    void draw_active_bases(Graphics &graphics);
    void draw(Graphics &graphics);
}; // class Playground

} // namespace Mayhem

#endif // PLAYGROUND_H

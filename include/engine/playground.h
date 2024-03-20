#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include "core/base.h"
#include "core/card.h"
#include "core/deck.h"
#include "core/entity.h"
#include "graphics/graphics.hpp"
#include "parser/parser.h"
#include "player.h"
#include "graphics/button.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <fstream>
#include <iostream>
#include <utility>

namespace Mayhem {

using LeaderBoard_t = std::map<uint32_t, uint32_t>;

class Playground : public Drawable {
  private:
    Deck<Base *> active_bases_;
    Deck<Base *> bases_;
    Deck<Base *> dump_;

    std::vector<Player *> players_;

    Button end_turn_;

  public:
    Playground() = delete;

    Playground(const Playground &rhs) = delete;
    Playground &operator=(const Playground &rhs) = delete;

    Playground(Playground &&rhs) = delete;
    Playground &operator=(Playground &&rhs) = delete;

    Playground(std::vector<Entity *> &entities)
        : Drawable("../assets/images/playground.jpg"), bases_(), active_bases_(), dump_(),
        end_turn_("") {
        for (int i = 0; i < 4; i++) {
            Player *player = new Player(i);
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
    std::pair<bool, uint32_t> check_for_winner();
    ~Playground() = default;

  private: // graphics functions
    void draw_active_bases(Graphics::DrawingAttributes &attributes, const sf::FloatRect &rect);
    void draw_button(sf::RenderWindow &window, const sf::FloatRect &rect);

  public: // graphics functions
    void draw(Graphics::DrawingAttributes &attributes, const sf::FloatRect &rect, const float angle);
}; // class Playground

} // namespace Mayhem

#endif // PLAYGROUND_H

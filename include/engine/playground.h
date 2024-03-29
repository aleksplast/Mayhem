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

// Struct with top players and their points
using LeaderBoard_t = std::map<uint32_t, uint32_t>;

// Class, containing all players and bases
class Playground : public Drawable {
  private:
    // Bases on the field
    Deck<Base *> active_bases_;

    // Bases that wasn't in game
    Deck<Base *> bases_;

    // Already destroyed bases
    Deck<Base *> dump_;

    // Players in the game
    std::vector<Player *> players_;

    // Button to end turn
    Button end_turn_;

  public:
    // Playground cannot be constructed without parameters
    Playground() = delete;

    // Playground can't be copied
    Playground(const Playground &rhs) = delete;
    Playground &operator=(const Playground &rhs) = delete;

    // Playground can't be moved
    Playground(Playground &&rhs) = delete;
    Playground &operator=(Playground &&rhs) = delete;

    // Constructor for Playground
    Playground(std::vector<Entity *> &entities)
        : Drawable("../assets/images/playground.jpg"), bases_(), active_bases_(), dump_(),
        end_turn_("") {
        for (int i = 0; i < 4; i++) {
            Player *player = new Player(i);
            players_.push_back(player);
            entities.push_back(player);
        }
    }

    // Check, if any base was captured
    std::vector<Base *> check_bases();

    // Logic of capturing base, returns leaderboard
    LeaderBoard_t capture_base(Base *base);

    // Move base from active_bases to dump
    void destroy_base(Base *base);

    // Move base from bases to active_bases
    void set_new_base();

    // Get number of players in the game
    uint16_t get_number_of_players() { return players_.size(); };

    // Base deck gain card on the game start
    void gain_base_on_start(Base *base);

    // Dump state of Playground
    void dump_state(std::ofstream &os) const;

    // Check for winner of the game
    std::pair<bool, uint32_t> check_for_winner();

    ~Playground() = default;

  private: // graphics functions

    // Draws active bases
    void draw_active_bases(Graphics::DrawingAttributes &attributes, const sf::FloatRect &rect);

    // draw button of end turn
    void draw_button(sf::RenderWindow &window, const sf::FloatRect &rect);

  public: // graphics functions

  // Draws playground
    void draw(Graphics::DrawingAttributes &attributes, const sf::FloatRect &rect, const float angle);
}; // class Playground

} // namespace Mayhem

#endif // PLAYGROUND_H

#ifndef ENGINE_H
#define ENGINE_H

#include "core/actions.h"
#include "core/base.h"
#include "core/card.h"
#include "core/deck.h"
#include "core/entity.h"
#include "graphics/graphics_view.hpp"
#include "parser/parser.h"
#include "player.h"
#include "playground.h"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

namespace Mayhem {

// Main controlling structure
class Engine final {

  private:
    // Time for one turn
    int time_; // FIXME: just mock
    // Indicates, which player's turn is now
    uint16_t turn_;
    // All entities in the game
    std::vector<Entity *> entities_;
    // Playground of the game
    Playground playground;
    // Parser for game start
    Parser parser_;
    // Winner of the game
    size_t winner_ = SIZE_MAX;
    // Flag, indicates if the game is over
    bool game_over_ = false;

  public:
    // Engine can't be copied
    Engine(const Engine &rhs) = delete;
    Engine &operator=(Engine &&rhs) = delete;

    // Engine can't be moved
    Engine(Engine &&rhs) = delete;
    Engine &operator=(const Engine &rhs) = delete;

    // Default Constructor for Engine
    Engine();

    // Default Engine Destructor
    ~Engine();

    // Return pointer to Entity by it's id
    Entity *get_by_id(uint16_t entity_id);

    // Function for placing Minion to Base.
    // Takes player's, minion's, base's id.
    // Removes minion from player hand, adds minion to base.
    bool place_card(uint16_t player_id, uint16_t card_id, uint16_t base_id);

    // Function for playing Action.
    // Takes player's, action's id.
    // Removes action from player hand.
    bool play_action(uint16_t player_id, uint16_t card_id);

    // End turn logic.
    uint16_t end_turn(uint16_t player_id);

    // After base capture distribute points between top players
    void distribute_points(Base *base, LeaderBoard_t &leaderboard);

    // Parse players' decks, create bases, distribute cards
    void start_game(GraphicsModel::Data::Attributes &attributes);

    // Dumps state of Engine
    void dump_state(std::string file_name) const;

    // Flag, indicates if the game is over
    bool is_over() const;

    // Get winner of the game
    uint32_t get_winner() const;

  public: // graphic functions
    // Draw Engine
    void draw(GraphicsModel::Data::Attributes &attributes);
}; // class Engine

} // namespace Mayhem

#endif // ENGINE_H

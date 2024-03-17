#ifndef ENGINE_H
#define ENGINE_H

#include "core/base.h"
#include "core/card.h"
#include "core/deck.h"
#include "core/entity.h"
#include "parser/parser.h"
#include "playground.h"
#include "player.h"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

namespace Mayhem {

class Engine {

  private:
    int time_;      // FIXME: just mock
    uint16_t turn_;
    std::vector<Entity *> entities_;
    Playground playground;
    Parser parser_;
    size_t winner_ = SIZE_MAX;
    bool game_over_ = false;

  public:
    Engine(const Engine &rhs) = delete;
    Engine& operator=(Engine &&rhs) = delete;

    Engine(Engine &&rhs) = delete;
    Engine& operator=(const Engine &rhs) = delete;

    Engine() : turn_(0), time_(0), entities_(), playground(entities_), parser_() {};
    Entity *get_by_id(uint16_t entity_id);
    ~Engine();
    void give_card(uint16_t player_id, uint16_t card_id);
    bool place_card(uint16_t player_id, uint16_t card_id, uint16_t base_id);
    uint16_t end_turn(uint16_t player_id);
    void distribute_points(LeaderBoard_t &leaderboard){};
    void start_game(Graphics::DrawingAttributes &attributes);
    void place_card_to_deck(uint16_t player_id, Entity *entity);
    void dump_state(std::string file_name) const;
    bool is_over() const;
    uint32_t get_winner() const;

  public: // graphic functions
    void draw(Graphics::DrawingAttributes &attributes);
}; // class Engine

} // namespace Mayhem

#endif // ENGINE_H

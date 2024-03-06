#ifndef ENGINE_H
#define ENGINE_H

#include "core/base.h"
#include "core/card.h"
#include "core/deck.h"
#include "core/entity.h"
#include "graphics/graphics.hpp"
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
    uint16_t turn_; // FIXME: just mock
    std::vector<Entity *> entities_;
    Playground playground;
    Parser parser_;

  public:
    Engine(Graphics &graphics) : turn_(1), time_(0), entities_(), playground(graphics, entities_), parser_(){};
    Entity *get_by_id(uint16_t entity_id);
    void give_card(uint16_t player_id, uint16_t card_id); // так это типо отдать игроку
                                                          // карту, после завершения хода
    bool place_card(uint16_t player_id, uint16_t card_id, uint16_t base_id);
    void end_turn(uint16_t player_id);
    void distribute_points(LeaderBoard_t &leaderboard){};
    void start_game();
    void place_card_to_deck(uint16_t player_id, Entity *entity);
    void dump_state(std::string file_name) const;

  public: // graphic functions
    void draw(Graphics &grafics);
}; // class Engine

} // namespace Mayhem

#endif // ENGINE_H

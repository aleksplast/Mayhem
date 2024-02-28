#ifndef GAME_CORE_H
#define GAME_CORE_H

#include "graphics/graphics.hpp"
#include "card.h"
#include "deck.h"
#include "entity.h"
#include "base.h"

#include <array>
#include <cstdint>
#include <deque>
#include <iostream>
#include <list>
#include <stdlib.h>
#include <string>
#include <vector>

namespace Mayhem {
using  LeaderBoard_t = std::map<uint32_t, uint32_t>;

class Player : public Entity {
  private:
    Deck<PlayerCard> hand_;
    Deck<PlayerCard> dump_deck_;
    Deck<PlayerCard> deck_;

    uint32_t points_;

    virtual void activate_abillity() {};

// get number of card
public:
  Player(Graphics &graphics, uint32_t id) : Entity("./src/graphics/images/player.png", id) {
    sprite.setColor(sf::Color(0, 0, 0, 100));
  };
  ~Player() = default;

public:
    void play_card(PlayerCard* card) {} ;//from hand to base, just destroys card in hand, no interaction with the base
    void dump_card(PlayerCard* card) {}; // card to dump deck
    void end_turn();
    void take_card(uint32_t number_of_cards); // from deck to hand, just card to hand
    void set_points(uint32_t point);
    std::size_t get_number_of_cards() { return hand_.size(); };

  public: // graphic function
    void draw(Graphics &graphic);
}; // class Player

class Playground : public Drawable {
private:
  Deck<Base> active_bases_;
  Deck<Base> bases_;
  Deck<Base> dump_;

    std::vector<Player> players_;

public:
    Playground() = delete;
    Playground(Graphics &graphics)
      : Drawable("./src/graphics/images/playground.jpg") {
    auto window_size = graphics.window.getSize();
    sprite.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2));
    sprite.setScale(static_cast<float>(window_size.x) / texture.getSize().x,
                    static_cast<float>(window_size.y) / texture.getSize().y);

        players_.push_back(*(new Player(graphics, 0)));
        players_.push_back(*(new Player(graphics, 1)));
        players_.push_back(*(new Player(graphics, 2)));
        players_.push_back(*(new Player(graphics, 3)));
    };

    Playground(std::vector<Entity*>& entities);
    std::vector<Base*> check_bases();
    LeaderBoard_t capture_base(Base& base);
    void clear_base(Base& base); // FIXME: just mock
    void destroy_base(Base& base);
    void set_new_base();
    ~Playground() = default;


public:
    uint16_t get_number_of_players() { return players_.size(); };


public: //graphic functions
    void set_player_position(Graphics &graphics, uint16_t player_id);
    void set_rotate(Graphics &graphics, uint16_t player_id);
    void set_scale(Graphics &graphics, uint16_t player_id);
    void draw(Graphics &graphics);
}; // class Playground

class Engine {

private:
    int time_; // FIXME: just mock
    uint16_t turn_; // FIXME: just mock
    std::vector<Entity*> entities_;
    Playground playground;

public:
    Engine();
    Entity* get_by_id(uint16_t entity_id);
    void give_card(uint16_t player_id, uint16_t card_id); // так это типо отдать игроку карту, после завершения хода
    bool place_card(uint16_t player_id, uint16_t card_id, uint16_t base_id);
    void end_turn(uint16_t player_id);
    void distribute_points(LeaderBoard_t& leaderboard) {};

    Engine(Graphics &graphics) : playground(graphics){};

  public: // graphic functions
    void draw(Graphics &grafics);
}; // class Engine

} // namespace Mayhem

#endif // GAME_CORE_H

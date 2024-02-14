#ifndef GAME_CORE_H
#define GAME_CORE_H

#include "graphics/graphics.hpp"
#include "card.h"
#include "deck.h"
#include "entity.h"
#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <stdlib.h>
#include <string>
#include <vector>

namespace Mayhem {

class Player : public Entity {
  private:
    Deck<PlayerCard> hand_;
    Deck<PlayerCard> dump_deck_;
    Deck<PlayerCard> deck_;

    uint32_t points_;

public:
  Player() = default;
  Player(Graphics &graphics) : Entity("./src/graphics/images/player.png") {
    sprite.setColor(sf::Color(0, 0, 0, 100));
  };
  void play_card(PlayerCard *card); // from hand to base, just destroys card in
                                    // hand, no interaction with the base
    ~Player() = default;
public:
    void play_card(PlayerCard* card); //from hand to base, just destroys card in hand, no interaction with the base
    void dump_card(PlayerCard *card); // card to dump deck
    void end_turn();
    void gain_card(PlayerCard* card); // from deck to hand, just card to hand
    void give_points(uint32_t point);

  public: // graphic function
    void draw(Graphics &graphic);
}; // class Player

class Playground : public Drawable {
  private:
    Deck<Base *> active_bases_;
    Deck<Base *> bases_;
    Deck<Base *> dump_;

    std::vector<Player> players_;

public:
<<<<<<< HEAD
  Playground() = delete;
  Playground(Graphics &graphics)
      : Drawable("./src/graphics/images/playground.jpg") {
    auto window_size = graphics.window.getSize();
    sprite.setPosition(sf::Vector2f(window_size.x / 2, window_size.y / 2));
    sprite.setScale(static_cast<float>(window_size.x) / texture.getSize().x,
                    static_cast<float>(window_size.y) / texture.getSize().y);
=======
    Playground(std::vector<Entity*>& entities);
    void clear_base(Base& base); // FIXME: just mock
    void destroy_base(Base& base);
    void set_new_base();

public:
    uint16_t get_number_of_players();

public: //graphic functions
    void draw(sf::Window &window);
}; // class Playground

class Engine {
private:
    Playground playground;
    int time_; // FIXME: just mock
    uint16_t turn_; // FIXME: just mock
    std::vector<Entity*> entities_;
>>>>>>> e6275e1 ([core] Added almost all engine methods)

        players_.push_back(*(new Player(graphics, 0)));
        players_.push_back(*(new Player(graphics, 1)));
        players_.push_back(*(new Player(graphics, 2)));
        players_.push_back(*(new Player(graphics, 3)));
    };
  void clear_base(Base &base); // FIXME: just mock
  void destroy_base(Base &base);
  void set_new_base();
  ~Playground() = default;
public:
    Engine();
    Entity* get_by_id(uint16_t entity_id);
    void give_card(uint16_t player_id, uint16_t card_id); // так это типо отдать игроку карту, после завершения хода
    bool place_card(uint16_t player_id, uint16_t card_id, uint16_t base_id);
    void end_turn(uint16_t player_id);

  private: // graphic function
    void set_player_posission(Graphics &graphics, uint16_t player_id);
    void set_rotate(Graphics &graphics, uint16_t player_id);
    void set_scale(Graphics &graphics, uint16_t player_id);

  public: // graphic function
    void draw(Graphics &graphic);
}; // class Playground

class Engine {
  private:
    Playground playground;
    int time; // FIXME: just mock
    int turn; // FIXME: just mock

  public:
    Engine() = delete;
    Engine(Graphics &graphics) : playground(graphics){};
    void give_points(uint16_t number, uint16_t player_id){};
    void give_card(uint16_t id, PlayerCard *card); // так это типо отдать игроку
                                                   // карту, после завершения хода
    void place_card(uint16_t player_id, PlayerCard *card, uint16_t base);
    void end_turn(uint16_t player_id);
    ~Engine() = default;

  public: // graphic functions
    void draw(Graphics &grafics);
}; // class Engine

} // namespace Mayhem

#endif // GAME_CORE_H

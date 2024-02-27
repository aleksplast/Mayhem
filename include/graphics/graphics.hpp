#ifndef GRAFICS_H
#define GRAFICS_H

#include "core/deck.h"
#include <SFML/Graphics.hpp>

class PlayerCard;
class Deck;
class Base;

namespace Mayhem {

class Graphics {
  public:
    enum class GameType { ONLINE, OFLINE };

  private:
    const float num_cards_per_side_ = 10;
    const float num_players_per_side_ = 3;
    const GameType type_;
    uint16_t draw_player_; // num player who graphic draw
    const float player_increase_ = 1.8;

  public:
    sf::RenderWindow window;
    Deck<PlayerCard *> player_cards;
    Deck<PlayerCard *> decks;
    Deck<Base *> active_bases;

  public:
    Graphics() = delete;
    Graphics(GameType type, uint16_t draw_player = 0) : type_(type), draw_player_(draw_player){};
    void end_turn();
    const float get_num_cards_per_side() const;
    uint16_t get_draw_player() const;
    const float get_num_players_per_side() const;
    const float get_player_increase() const;
    ~Graphics() = default;
}; // class Grafics

} // namespace Mayhem

#endif

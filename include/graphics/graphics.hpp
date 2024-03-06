#ifndef GRAFICS_H
#define GRAFICS_H

#include "core/deck.h"
#include <SFML/Graphics.hpp>

class PlayerCard;
class Base;

namespace Mayhem {

class Graphics {
  public:
    enum class GameType { ONLINE, OFLINE };

  private:
    const GameType type_;
    uint16_t draw_player_; // num player who graphic draw

  public:
    constexpr static const float player_scale_to_playground = 0.35;
    constexpr static const float player_increase = 1.8;
    constexpr static const float base_shift_to_playground = 0.1;
    constexpr static const float card_scale_to_player = 0.2;
    constexpr static const float bases_place_to_playground = 0.8;
    constexpr static const float cards_place_to_player = 0.6;
    constexpr static const float bases_pos_to_playground = 0.4;

  public:
    sf::RenderWindow window;
    Deck<PlayerCard *> player_cards;
    Deck<PlayerCard *> decks;
    Deck<Base *> active_bases;

  public:
    Graphics() = delete;
    Graphics(GameType type, uint16_t draw_player = 0);
    void end_turn();
    uint16_t get_draw_player() const;
    ~Graphics() = default;
}; // class Grafics

} // namespace Mayhem

#endif

#ifndef GRAFICS_H
#define GRAFICS_H

#include <SFML/Graphics.hpp>
#include "../../include/core/deck.h"

class PlayerCard;
class Deck;
class Base;

namespace Mayhem {

class Graphics {
public:
    enum class GameType
    {
        ONLINE,
        OFLINE
    };

private:
    const GameType type_;
    const uint16_t num_players_;
    uint16_t draw_plaeyr_; // num player who graphic draw
    
public:
    sf::RenderWindow window;
    std::vector<PlayerCard*> player_cards;
    std::vector<Deck<PlayerCard>*> decks;
    std::vector<Base*> active_bases;
    
public:
    Graphics() = delete;
    Graphics(GameType type, uint16_t num_players, uint16_t draw_player = 0) : type_(type), num_players_(num_players), draw_plaeyr_(draw_player) {};
    void end_turn();
    ~Graphics() = default;
}; // class Grafics

class Drawable {
protected:
    sf::Texture texture;

public:
    sf::Sprite sprite;

public:
    Drawable() = default;
    Drawable(const std::string &texture_file);
    ~Drawable() = default;
}; // class Drawable

} // namespace Mayhem

#endif
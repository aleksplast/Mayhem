#ifndef CARD_H
#define CARD_H

#include <array>
#include <list>
#include <stdlib.h>
#include <vector>
#include <string>
#include <deque>
#include <SFML/Graphics.hpp>
#include "deck.h"
#include "entity.h"

namespace Mayhem {

class Card: public Entity
{
private:
    std::string abillity_;

public:
    sf::Texture texture;
    sf::Sprite sprite;

public:
    virtual void activate_abillity() = 0;
    virtual ~Card() {};

public: //graphic functions
    virtual void draw(sf::Window &window) = 0;
}; // class Card

class PlayerCard : public Card
{
private:
    uint32_t owner_id_;

public:
    virtual ~PlayerCard() override {};
    void change_owner(uint32_t owner_id);
    virtual void activate_abillity() override = 0;
}; // class PlayerCard

class Minion : public PlayerCard {
private:
    uint32_t power_;

public:
    virtual ~Minion() override {};
    void activate_abillity() override;
    uint32_t get_power() const { return power_;}
}; // class Minion

class Action : public PlayerCard {
public:
    virtual ~Action() override {};
    void activate_abillity() override;
}; // class Action

class Base : public Card {
private:
    uint32_t power_to_win_;
    std::array<uint32_t, 3> points_;
    Deck<PlayerCard> cards_;
    uint32_t current_power_;

public:
    void activate_abillity() override;
    void gain_minion(const Minion* card);
    void remove_minion(const Minion& card);
    bool is_captured() const;

public: //graphic functions
    void draw (sf::Window &window) override;
}; // class Base

} // namespace Mayhem

#endif // CARD_H

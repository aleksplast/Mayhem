#ifndef CARD_H
#define CARD_H

#include <array>
#include <list>
#include <stdlib.h>
#include <vector>
#include <string>
#include <deque>
#include <SFML/Graphics.hpp>
#include "entity.h"

namespace Mayhem {

class Card: public Entity
{
protected:
    std::string ability_;

public:
    virtual void activate_abillity() = 0;
    Card(int id, std::string ability) : Entity(id), ability_(ability) {};

}; // class Card

class PlayerCard : public Card{
private:
    uint32_t owner_id_;

public:
    void change_owner(uint32_t owner_id);
}; // class PlayerCard

class Minion : public PlayerCard {
private:
    uint32_t power_;

public:
    void activate_abillity() override {};
    uint32_t get_power() const { return power_;}
}; // class Minion

class Action : public PlayerCard {
public:
    virtual ~Action() override {};
    void activate_abillity() override;
}; // class Action

} // namespace Mayhem

#endif // CARD_H

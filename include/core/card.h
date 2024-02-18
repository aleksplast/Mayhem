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
    Card(Graphics &graphics, const std::string &name_file) : Entity(name_file)
    {
        auto window_size = graphics.window.getSize();
        float x_axis_stretching = window_size.x / (graphics.get_num_cards_per_side() * texture.getSize().x); 
        sprite.setScale(x_axis_stretching, x_axis_stretching * texture.getSize().y / texture.getSize().x);
    };
    virtual void activate_abillity() = 0;
    Card(int id, std::string ability) : Entity(id), ability_(ability) {};

}; // class Card

class PlayerCard : public Card{
private:
    uint32_t owner_id_;

public:
    PlayerCard() = default;
    PlayerCard(Graphics &graphics, const std::string &name_file) : Card(graphics, name_file) {};
    void change_owner(uint32_t owner);
}; // class PlayerCard

class Minion : public PlayerCard {
private:
    uint32_t power_;

public:
    Minion(Graphics &graphics, const std::string &minion_file) : PlayerCard(graphics, minion_file) {};
    void activate_abillity() override {};
    uint32_t get_power() const { return power_;}
}; // class Minion

class Action : public PlayerCard {
public:
    Action(Graphics &graphics, const std::string &action_file) : PlayerCard(graphics, action_file) {};
    void activate_abillity() override {};
}; // class Action

} // namespace Mayhem

#endif // CARD_H

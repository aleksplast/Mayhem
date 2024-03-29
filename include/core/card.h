#ifndef CARD_H
#define CARD_H

#include "entity.h"
#include "graphics/graphics.hpp"
#include <array>
#include <deque>
#include <fstream>
#include <list>
#include <stdlib.h>
#include <string>
#include <vector>

namespace Mayhem {

// Card type
class Card : public Entity {
  public:
    Card(const std::string &name_file, int id) : Entity(name_file, id){};
}; // class Card

// Card that can belong to a player
class PlayerCard : public Card {
  private:
    // Owner of the card
    uint32_t owner_id_;

  public:
    PlayerCard(const std::string &name_file, int id) : Card(name_file, id){};

    // Get owner of the card
    uint32_t get_owner() { return owner_id_; };

    // Change owner of the card
    void change_owner(uint32_t owner);

    // Dump state of the card
    virtual void dump_state(std::ofstream &os) const {};
}; // class PlayerCard

// Minion class
class Minion : public PlayerCard {
  private:
    // Power of the minion
    uint32_t power_;

  public:
    Minion(const std::string &minion_file, int id, uint32_t power) : PlayerCard(minion_file, id), power_(power){};

    // Dump state of the minion
    void dump_state(std::ofstream &os) const override;

    // Get power of the minion
    uint32_t get_power() const { return power_; }

    // Increase power of the minion
    void increase_power(uint32_t power) { power_ += power; }

    // Decrease power of the minion
    void decrease_power(uint32_t power);
}; // class Minion

// Action class
class Action : public PlayerCard {
    // FIXME: change it to abstract class
  public:
    Action(const std::string &action_file, int id) : PlayerCard(action_file, id){};

    // Activate ability of the action
    virtual void activate_abillity(Minion *target, Base *src = NULL, Base *dest = NULL){};

    // Dump state of the action
    void dump_state(std::ofstream &os) const override;
}; // class Action

} // namespace Mayhem

#endif // CARD_H

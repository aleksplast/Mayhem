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

class Card : public Entity {
  protected:
    std::string ability_;

  public:
    Card(const std::string &name_file, int id) : Entity(name_file, id){};
}; // class Card

class PlayerCard : public Card {
  private:
    uint32_t owner_id_;

  public:
    PlayerCard(const std::string &name_file, int id) : Card(name_file, id){};
    uint32_t get_owner() { return owner_id_; };
    void change_owner(uint32_t owner);
    virtual void dump_state(std::ofstream &os) const {};
}; // class PlayerCard

class Minion : public PlayerCard {
  private:
    uint32_t power_;

  public:
    Minion(const std::string &minion_file, int id, uint32_t power) : PlayerCard(minion_file, id), power_(power){};
    void dump_state(std::ofstream &os) const override;
    uint32_t get_power() const { return power_; }
    void increase_power(uint32_t power) { power_ += power; }
    void decrease_power(uint32_t power);
}; // class Minion

class Action : public PlayerCard {
    // FIXME: change it to abstract class
  public:
    Action(const std::string &action_file, int id) : PlayerCard(action_file, id){};
    virtual void activate_abillity(Minion *target, Base *src = NULL, Base *dest = NULL){};
    void dump_state(std::ofstream &os) const override;
}; // class Action

} // namespace Mayhem

#endif // CARD_H

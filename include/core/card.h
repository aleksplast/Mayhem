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
    Card(const std::string &name_file, int id, std::string ability) : Entity(name_file, id){};
    virtual void activate_abillity(){};

}; // class Card

class PlayerCard : public Card {
  private:
    uint32_t owner_id_;

  public:
    PlayerCard(const std::string &name_file, int id, std::string ability) : Card(name_file, id, ability){};
    uint32_t get_owner() { return owner_id_; };
    void change_owner(uint32_t owner);
    virtual void dump_state(std::ofstream &os) const{};
}; // class PlayerCard

class Minion : public PlayerCard {
  private:
    uint32_t power_;

  public:
    Minion(const std::string &minion_file, int id, std::string ability, uint32_t power) : PlayerCard(minion_file, id, ability), power_(power){};
    void activate_abillity() override{};
    void dump_state(std::ofstream &os) const override;
    uint32_t get_power() const { return power_; }
}; // class Minion

class Action : public PlayerCard {
  public:
    Action(const std::string &action_file, int id, std::string ability) : PlayerCard(action_file, id, ability){};
    void activate_abillity() override{};
    void dump_state(std::ofstream &os) const override;
}; // class Action

} // namespace Mayhem

#endif // CARD_H

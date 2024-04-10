#ifndef ACTIONS_H
#define ACTIONS_H

#include "base.h"
#include "card.h"

namespace Mayhem {

// Action class
class Action : public PlayerCard {
    // FIXME: change it to abstract class
  public:
    Action(const std::string &action_file, int id);

    // Activate ability of the action
    virtual void activate_abillity(Minion *target, Base *src = NULL, Base *dest = NULL){};

    // Dump state of the action
    void dump_state(std::ofstream &os) const override;
}; // class Action

// Action, that buffs other minion
class BuffAction : public Action {
    // Buff size
    uint32_t buff_;

  public:
    BuffAction(const std::string &action_file, int id, std::string ability, uint32_t buff);

    // Buffs minion
    void activate_abillity(Minion *target, Base *src = NULL, Base *dest = NULL) override;

}; // class BuffAction

class DebuffAction : public Action {
    // Debuff size
    uint32_t debuff_;

  public:
    DebuffAction(const std::string &action_file, int id, std::string ability, uint32_t debuff);

    // Debuffs minion
    void activate_abillity(Minion *target, Base *src = NULL, Base *dest = NULL) override;
}; // class DebuffAction

class DestroyAction : public Action {
    // Destroy minion
    void activate_abillity(Minion *target, Base *src, Base *dest = NULL) override;
}; // class DestroyAction

class MoveAction : public Action {
    // Move minion
    void activate_abillity(Minion *target, Base *src, Base *dest) override;
}; // class MoveAction

} // namespace Mayhem

#endif // ACTIONS_H

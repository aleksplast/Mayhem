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
    virtual void activate_abillity(Minion *target, Base *src = nullptr, Base *dest = nullptr){};

    // Dump state of the action
    void dump_state(std::ostream &os) const override;
}; // class Action

// Action, that buffs other minion
class BuffAction : public Action {
    // Buff size
    uint32_t buff_;

  public:
    BuffAction(const std::string &action_file, int id, uint32_t buff);

    // Buffs minion
    void activate_abillity(Minion *target, Base *src = nullptr, Base *dest = nullptr) override;

}; // class BuffAction

class DebuffAction : public Action {
    // Debuff size
    uint32_t debuff_;

  public:
    DebuffAction(const std::string &action_file, int id, uint32_t debuff);

    // Debuffs minion
    void activate_abillity(Minion *target, Base *src = nullptr, Base *dest = nullptr) override;
}; // class DebuffAction

class DestroyAction : public Action {
  public:
    DestroyAction(const std::string &action_file, int id) : Action(action_file, id){};

    // Destroy minion
    void activate_abillity(Minion *target, Base *src, Base *dest = nullptr) override;
}; // class DestroyAction

class MoveAction : public Action {
  public:
    MoveAction(const std::string &action_file, int id) : Action(action_file, id){};

    // Move minion
    void activate_abillity(Minion *target, Base *src, Base *dest) override;
}; // class MoveAction

} // namespace Mayhem

#endif // ACTIONS_H

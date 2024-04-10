#ifndef ACTIONS_H
#define ACTIONS_H

#include "base.h"
#include "card.h"

namespace Mayhem {

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
  public:
    DestroyAction(const std::string &action_file, int id, std::string &ability) : Action(action_file, id){};

    // Destroy minion
    void activate_abillity(Minion *target, Base *src, Base *dest = NULL) override;
}; // class DestroyAction

class MoveAction : public Action {
  public:
    MoveAction(const std::string &action_file, int id, std::string &type) : Action(action_file, id){};

    // Move minion
    void activate_abillity(Minion *target, Base *src, Base *dest) override;
}; // class MoveAction

} // namespace Mayhem

#endif // ACTIONS_H

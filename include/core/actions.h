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
    BuffAction(const std::string &action_file, int id, std::string ability, uint32_t buff)
        : Action(action_file, id), buff_(buff){};

    // Buffs minion
    void activate_abillity(Minion *target, Base *src = NULL, Base *dest = NULL) override {
        target->increase_power(buff_);
    };

}; // class BuffAction

class DebuffAction : public Action {
    // Debuff size
    uint32_t debuff_;

  public:
    DebuffAction(const std::string &action_file, int id, std::string ability, uint32_t debuff)
        : Action(action_file, id), debuff_(debuff){};

    // Debuffs minion
    void activate_abillity(Minion *target, Base *src = NULL, Base *dest = NULL) override {
        target->decrease_power(debuff_);
    };
}; // class DebuffAction

class DestroyAction : public Action {
    // Destroy minion
    void activate_abillity(Minion *target, Base *src, Base *dest = NULL) override { src->remove_minion(target); };
}; // class DestroyAction

class MoveAction : public Action {
    // Move minion
    void activate_abillity(Minion *target, Base *src, Base *dest) override {
        src->remove_minion(target);
        dest->gain_minion(target);
    };
}; // class MoveAction

} // namespace Mayhem

#endif // ACTIONS_H

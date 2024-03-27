#ifndef ACTIONS_H
#define ACTIONS_H

#include "card.h"
#include "base.h"

namespace Mayhem {

class BuffAction : public Action {
    uint32_t buff_;

  public:
    BuffAction(const std::string &action_file, int id, std::string ability, uint32_t buff)
        : Action(action_file, id), buff_(buff){};

    void activate_abillity(Minion *target, Base *src = NULL, Base *dest = NULL) override{
        target->increase_power(buff_);
    };

}; // class BuffAction

class DebuffAction : public Action {
    uint32_t debuff_;

  public:
    DebuffAction(const std::string &action_file, int id, std::string ability, uint32_t debuff)
        : Action(action_file, id), debuff_(debuff){};

    void activate_abillity(Minion *target, Base *src = NULL, Base *dest = NULL) override{
        target->decrease_power(debuff_);
    };
}; // class DebuffAction

class DestroyAction : public Action {
    void activate_abillity(Minion *target, Base *src, Base *dest = NULL) override{
        src->remove_minion(target);
    };
}; // class DestroyAction

class MoveAction : public Action {
    void activate_abillity(Minion *target, Base *src, Base *dest) override{
        src->remove_minion(target);
        dest->gain_minion(target);
    };
}; // class MoveAction

} // namespace Mayhem

#endif // ACTIONS_H

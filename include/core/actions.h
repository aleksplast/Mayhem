#ifndef ACTIONS_H
#define ACTIONS_H

#include "base.h"
#include "card.h"
#include "engine/player.h"

namespace Mayhem {

// Action class
class Action : public PlayerCard {
    // FIXME: change it to abstract class
  public:
    Action(const std::string &action_main_file, const std::string &action_extra_file, int id);

    // Activate ability of the action
    virtual void activate_abillity(Minion *target, Base *src = nullptr, Base *dest = nullptr){};

    // Dump state of the action
    void dump_state(std::ostream &os) const override;
}; // class Action

// Action, that buffs other minion
class BuffAction final : public Action {
    // Buff size
    uint32_t buff_;

  public:
    BuffAction(const std::string &action_main_file, const std::string &action_extra_file, int id, uint32_t buff);

    // Buffs minion
    void activate_abillity(Minion *target, Base *src = nullptr, Base *dest = nullptr) override;

}; // class BuffAction

class DebuffAction final : public Action {
    // Debuff size
    uint32_t debuff_;

  public:
    DebuffAction(const std::string &action_main_file, const std::string &action_extra_file, int id, uint32_t debuff);

    // Debuffs minion
    void activate_abillity(Minion *target, Base *src = nullptr, Base *dest = nullptr) override;
}; // class DebuffAction

class DestroyAction final : public Action {
  public:
    DestroyAction(const std::string &action_main_file, const std::string &action_extra_file, int id)
        : Action(action_main_file, action_extra_file, id){};

    // Destroy minion
    void activate_abillity(Minion *target, Base *src, Base *dest = nullptr) override;
}; // class DestroyAction

class MoveAction final : public Action {
  public:
    MoveAction(const std::string &action_main_file, const std::string &action_extra_file, int id)
        : Action(action_main_file, action_extra_file, id){};

    // Move minion
    void activate_abillity(Minion *target, Base *src, Base *dest) override;
}; // class MoveAction

class DrawAction final : public Action {
    // Number of cards to draw
    uint32_t num_;

  public:
    DrawAction(const std::string &action_main_file, const std::string &action_extra_file, int id, int num)
        : Action(action_main_file, action_extra_file, id), num_(num){};

    // Draw cards
    void activate_ability(Player *player);
};

} // namespace Mayhem

#endif // ACTIONS_H

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
    //!--------------------------------
    //! @brief Constructor for Action
    //! @param[out] action_main_file main file image for action
    //! @param[out] action_extra_file extra file image for action
    //! @param[in] id id of the action
    //!--------------------------------
    Action(const std::string &action_main_file, const std::string &action_extra_file, int id);

    //!--------------------------------
    //! @brief Activate ability of the action (this is virtual method for other types of action)
    //! @param[out] target Target for an action
    //! @param[out] src Base, where target is located
    //! @param[out] dest Base, where target must be moved (null for all actions expect Move action)
    //!--------------------------------
    virtual void activate_abillity(Minion *target, Base *src = nullptr, Base *dest = nullptr){};
}; // class Action

// Action, that buffs other minion
class BuffAction final : public Action {
    // Buff size
    uint32_t buff_;

  public:
    //!--------------------------------
    //! @brief Constructor for BuffAction
    //! @param[out] action_main_file main file image for action
    //! @param[out] action_extra_file extra file image for action
    //! @param[in] id id of the action
    //! @param[in] buff buff of the action
    //!--------------------------------
    BuffAction(const std::string &action_main_file, const std::string &action_extra_file, int id, uint32_t buff);

    //!--------------------------------
    //! @brief Buff minion
    //! @param[out] target Target for an action
    //! @param[out] src Base, where target is located
    //!--------------------------------
    void activate_abillity(Minion *target, Base *src = nullptr, Base *dest = nullptr) override;

    void dump_state(std::ostream &os) const override;
}; // class BuffAction

class DebuffAction final : public Action {
    // Debuff size
    uint32_t debuff_;

  public:
    //!--------------------------------
    //! @brief Constructor for DebuffAction
    //! @param[out] action_main_file main file image for action
    //! @param[out] action_extra_file extra file image for action
    //! @param[in] id id of the action
    //! @param[in] debuff debuff of the action
    //!--------------------------------
    DebuffAction(const std::string &action_main_file, const std::string &action_extra_file, int id, uint32_t debuff);

    //!--------------------------------
    //! @brief Debuffs minion
    //! @param[out] target Target for an action
    //! @param[out] src Base, where target is located
    //!--------------------------------
    void activate_abillity(Minion *target, Base *src = nullptr, Base *dest = nullptr) override;

    void dump_state(std::ostream &os) const override;
}; // class DebuffAction

class DestroyAction final : public Action {
  public:
    //!--------------------------------
    //! @brief Constructor for DestroyAction
    //! @param[out] action_main_file main file image for action
    //! @param[out] action_extra_file extra file image for action
    //! @param[in] id id of the action
    //!--------------------------------
    DestroyAction(const std::string &action_main_file, const std::string &action_extra_file, int id)
        : Action(action_main_file, action_extra_file, id){};

    //!--------------------------------
    //! @brief Destroys minion
    //! @param[out] target Target for an action
    //! @param[out] src Base, where target is located
    //!--------------------------------
    void activate_abillity(Minion *target, Base *src, Base *dest = nullptr) override;

    void dump_state(std::ostream &os) const override;
}; // class DestroyAction

class MoveAction final : public Action {
  public:
    //!--------------------------------
    //! @brief Constructor for MoveAction
    //! @param[out] action_main_file main file image for action
    //! @param[out] action_extra_file extra file image for action
    //! @param[in] id id of the action
    //!--------------------------------
    MoveAction(const std::string &action_main_file, const std::string &action_extra_file, int id)
        : Action(action_main_file, action_extra_file, id){};

    //!--------------------------------
    //! @brief Move minion
    //! @param[out] target Target for an action
    //! @param[out] src Base, where target is located
    //! @param[out] dest Base, where target must be moved
    //!--------------------------------
    void activate_abillity(Minion *target, Base *src, Base *dest) override;

    void dump_state(std::ostream &os) const override;
}; // class MoveAction

class DrawAction final : public Action {
    // Number of cards to draw
    uint32_t num_;

  public:
    //!--------------------------------
    //! @brief Constructor for MoveAction
    //! @param[out] action_main_file main file image for action
    //! @param[out] action_extra_file extra file image for action
    //! @param[in] id id of the action
    //! @param[in] num num of cards to draw
    //!--------------------------------
    DrawAction(const std::string &action_main_file, const std::string &action_extra_file, int id, int num)
        : Action(action_main_file, action_extra_file, id), num_(num){};

    //!--------------------------------
    //! @brief Draw cards
    //! @param[out] player player to draw cards
    //!--------------------------------
    void activate_ability(Player *player);

    void dump_state(std::ostream &os) const override;
};

} // namespace Mayhem

#endif // ACTIONS_H

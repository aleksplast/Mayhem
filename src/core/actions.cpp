#include "core/actions.h"

namespace Mayhem {

void Action::dump_state(std::ostream &os) const {
    os << "\nDumping Action\n";
    os << "Not implemented\n";
}

Action::Action(const std::string &action_file, int id) : PlayerCard(action_file, id){};

BuffAction::BuffAction(const std::string &action_file, int id, uint32_t buff) : Action(action_file, id), buff_(buff){};

void BuffAction::activate_abillity(Minion *target, Base *src, Base *dest) { target->increase_power(buff_); };

DebuffAction::DebuffAction(const std::string &action_file, int id, uint32_t debuff)
    : Action(action_file, id), debuff_(debuff){};

void DebuffAction::activate_abillity(Minion *target, Base *src, Base *dest) { target->decrease_power(debuff_); };

void DestroyAction::activate_abillity(Minion *target, Base *src, Base *dest) { src->remove_minion(target); };

void MoveAction::activate_abillity(Minion *target, Base *src, Base *dest) {
    src->remove_minion(target);
    dest->gain_minion(target);
};
} // namespace Mayhem

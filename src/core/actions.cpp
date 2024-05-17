#include "core/actions.h"

namespace Mayhem {

Action::Action(const std::string &action_main_file, const std::string &action_extra_file, int id)
    : PlayerCard(action_main_file, id, action_extra_file){};

BuffAction::BuffAction(const std::string &action_main_file, const std::string &action_extra_file, int id, uint32_t buff)
    : Action(action_main_file, action_extra_file, id), buff_(buff){};

void BuffAction::activate_abillity(Minion *target, Base *src, Base *dest) { target->increase_power(buff_); };

void BuffAction::dump_state(std::ostream &os) const {
#ifdef DEBUG
    os << "\nDumping BuffAction\n";
    os << "buff: " << buff_ << "\n";
    os << "texture_name: " << texture_name << "\n";
    os << "id: " << id_ << "\n";
#endif
}

DebuffAction::DebuffAction(const std::string &action_main_file, const std::string &action_extra_file, int id,
                           uint32_t debuff)
    : Action(action_main_file, action_extra_file, id), debuff_(debuff){};

void DebuffAction::activate_abillity(Minion *target, Base *src, Base *dest) { target->decrease_power(debuff_); };

void DebuffAction::dump_state(std::ostream &os) const {
#ifdef DEBUG
    os << "\nDumping BuffAction\n";
    os << "debuff: " << debuff_ << "\n";
    os << "texture_name: " << texture_name << "\n";
    os << "id: " << id_ << "\n";
#endif
}

void DestroyAction::activate_abillity(Minion *target, Base *src, Base *dest) { src->remove_minion(target); };

void DestroyAction::dump_state(std::ostream &os) const {
#ifdef DEBUG
    os << "\nDumping DestroyAction\n";
    os << "texture_name: " << texture_name << "\n";
    os << "id: " << id_ << "\n";
#endif
}

void MoveAction::activate_abillity(Minion *target, Base *src, Base *dest) {
    src->remove_minion(target);
    dest->gain_minion(target);
};

void MoveAction::dump_state(std::ostream &os) const {
#ifdef DEBUG
    os << "\nDumping MoveAction\n";
    os << "texture_name: " << texture_name << "\n";
    os << "id: " << id_ << "\n";
#endif
}

void DrawAction::activate_ability(Player *player) { player->take_card(num_); }

void DrawAction::dump_state(std::ostream &os) const {
#ifdef DEBUG
    os << "\nDumping DrawAction\n";
    os << "num: " << num_ << "\n";
    os << "texture_name: " << texture_name << "\n";
    os << "id: " << id_ << "\n";
#endif
}
} // namespace Mayhem

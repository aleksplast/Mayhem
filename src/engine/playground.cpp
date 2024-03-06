#include "engine/playground.h"
#include "core/base.h"
#include "graphics/graphics.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

namespace Mayhem { // Playground methods

std::vector<Base *> Playground::check_bases() {
    std::vector<Base *> captured_bases{};

    for (auto curr = active_bases_.begin(), end = active_bases_.end(); curr != end;
         ++curr) { // here we can iterate over ref, not iterators
        if ((*curr)->is_captured()) {
            captured_bases.push_back(*curr);
        }
    }

    return captured_bases;
}

LeaderBoard_t Playground::capture_base(Base *base) {
    auto cards = base->get_cards();
    LeaderBoard_t leader_board;

    for (auto curr = cards.begin(), end = cards.end(); curr != end; ++curr) {
        players_[(*curr)->get_owner()]->dump_card(*curr); //
        leader_board[(*curr)->get_owner()] += (*curr)->get_power();
        base->remove_minion(*curr);
    }

    return leader_board;
}

void Playground::destroy_base(Base *base) {
    active_bases_.remove_card(base);
    dump_.gain_card(base);
}

void Playground::set_new_base() {
    Base *top_base = bases_.take_card();
    active_bases_.gain_card(top_base);
}

void Playground::gain_base_on_start(Base *base) { bases_.gain_card(base); }

} // namespace Mayhem

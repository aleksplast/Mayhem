#include "engine/playground.h"
#include "core/base.h"
#include "graphics/graphics.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

namespace Mayhem { // Playground methods

const uint32_t POINTS_TO_WIN = 15;

std::vector<Base *> Playground::check_bases() {
    std::vector<Base *> captured_bases{};

    for (auto curr = active_bases_.begin(), end = active_bases_.end(); curr != end; ++curr) {
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
    if (bases_.size() == 0) {
        bases_ = dump_;
        dump_.clear_deck();
        // bases_.shuffle();
    }
    if (bases_.size() == 0) {
        return;
    }

    Base *top_base = bases_.take_card();
    active_bases_.gain_card(top_base);
}

void Playground::gain_base_on_start(Base *base) { bases_.gain_card(base); }

std::pair<bool, uint32_t> Playground::check_for_winner() {
    uint32_t max_points = 0;
    uint32_t winner = SIZE_MAX;
    bool winner_exists = false;

    for (auto player: players_) {
        uint32_t player_points = player->get_points();

        if (player_points > POINTS_TO_WIN) {
            if (player_points > max_points) {
                max_points = player_points;
                winner = player->get_id();
                winner_exists = true;
            } else if (player_points == max_points) {
                winner = SIZE_MAX;
                winner_exists = false;
            }
        }
    }

    return {winner_exists, winner};
}

void Playground::dump_state(std::ofstream &os) const {
    os << "\nDumping playground\n";
    os << "-------------\n";

    os << "Dumping bases deck\n";
    bases_.dump_state(os);
    os << "Dumping active bases\n";
    active_bases_.dump_state(os);
    os << "Dumping dump bases\n";
    dump_.dump_state(os);

    for (auto& player : players_) {
        player->dump_state(os);
    }

    os << "-------------\n";
}

} // namespace Mayhem

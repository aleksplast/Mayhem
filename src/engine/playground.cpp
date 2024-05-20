#include "engine/playground.h"
#include "core/base.h"
#include "engine/player.h"
#include "graphics/graphics.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <unordered_map>
#include <utility>

namespace Mayhem { // Playground methods

const uint32_t POINTS_TO_WIN = 15;

const std::string PLAYGROUND_IMAGES = "../assets/images/playground.jpg";

Playground::Playground(std::vector<Entity *> &entities)
    : Drawable(PLAYGROUND_IMAGES), active_bases_(), bases_(), dump_(), end_turn_("") {
    for (int i = 0; i < 4; i++) {
        Player *player = new Player(i);
        players_.push_back(player);
        entities.push_back(player);
    }
}

std::vector<Base *> Playground::check_bases() {
    std::vector<Base *> captured_bases{};

    for (auto curr = active_bases_.begin(), end = active_bases_.end(); curr != end; ++curr) {
        if ((*curr)->is_captured()) {
            captured_bases.push_back(*curr);
        }
    }

    return captured_bases;
}

uint16_t Playground::get_number_of_players() const { return players_.size(); };

LeaderBoard_t Playground::capture_base(Base *base) {
    auto cards = base->get_cards();
    LeaderBoard_t leader_board;
    std::unordered_map<uint32_t, uint32_t> players_to_points;

    for (uint16_t i = 0; i < get_number_of_players(); i++) {
        leader_board.emplace_back(i, 0);
    }

    for (auto curr = cards.begin(), end = cards.end(); curr != end; ++curr) {
        uint32_t player_id = (*curr)->get_owner();
        players_to_points[player_id] += (*curr)->get_power();
        uint32_t player_power = players_to_points[player_id];

        auto player_it =
            std::find_if(leader_board.begin(), leader_board.end(),
                         [&player_id](Player_points_t player_points) { return player_id == player_points.first; });

        player_it->second = player_power;

        auto less_player_it = std::find_if(leader_board.begin(), leader_board.end(),
                                           [&player_power, &players_to_points](Player_points_t player_points) {
                                               return players_to_points[player_points.first] <= player_power;
                                           });

        leader_board.splice(less_player_it, leader_board, player_it);
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
        bases_.shuffle();
        return;
    }

    Base *top_base = bases_.take_card();
    active_bases_.gain_card(top_base);
}

void Playground::gain_base_on_start(Base *base) { bases_.gain_card(base); }

std::pair<bool, uint32_t> Playground::check_for_winner() {
    uint32_t max_points = 0;
    uint32_t winner = std::numeric_limits<uint32_t>::max();
    bool winner_exists = false;

    for (auto player : players_) {
        uint32_t player_points = player->get_points();

        if (player_points > POINTS_TO_WIN) {
            if (player_points > max_points) {
                max_points = player_points;
                winner = player->get_id();
                winner_exists = true;
            } else if (player_points == max_points) {
                winner = std::numeric_limits<uint32_t>::max();
                winner_exists = false;
            }
        }
    }

    return {winner_exists, winner};
}

void Playground::dump_state(std::ostream &os) const {
    os << "\nDumping playground\n";
    os << "-------------\n";

    os << "Dumping bases deck\n";
    bases_.dump_state(os);
    os << "Dumping active bases\n";
    active_bases_.dump_state(os);
    os << "Dumping dump bases\n";
    dump_.dump_state(os);

    for (auto &player : players_) {
        player->dump_state(os);
    }

    os << "-------------\n";
}

Playground::~Playground() { delete popping_up_card; }

} // namespace Mayhem

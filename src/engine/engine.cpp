#include "engine/engine.h"
#include "core/base.h"
#include "engine/player.h"
#include "graphics/graphics.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

namespace Mayhem { // Engine methods

// Player can only have 10 cards in hand
const uint32_t MAX_CARDS_IN_HAND = 10;

// At the end of the turn player draw 2 cards
const uint32_t CARDS_TO_DRAW_END_TURN = 2;

// Location of the data base with all bases
const std::string BASE_DATA_BASE_FILE = "../assets/base_data_base.json";

const std::string PLAYER = "player";

const std::string DECK_JSON_FILE = "_deck.json";

const uint32_t NUMBER_OF_WINNERS = 3;

Engine::Engine() : turn_(0), time_(0), entities_(), playground(entities_), parser_(){};

Entity *Engine::get_by_id(uint16_t entity_id) {
    if (entity_id >= entities_.size()) {
        std::cout << "HERE NEED TO BE LOG: entity id is bigger than vector size" << std::endl;
        return nullptr;
    }

    return entities_[entity_id];
}

bool Engine::place_card(uint16_t player_id, uint16_t card_id, uint16_t base_id) {
    if (player_id != turn_)
        return false;

    Player *player = static_cast<Player *>(get_by_id(player_id));

    if (player->get_minions_limit() == 0) {
        return false;
    }

    Minion *card = static_cast<Minion *>(get_by_id(card_id));
    Base *base = static_cast<Base *>(get_by_id(base_id));

    if (player_id != card->get_owner())
        return false;

    player->play_card(card); // FIXME: add error handling
    base->gain_minion(card);
    player->change_minions_limit(-1);

    return true;
}

bool Engine::play_action(uint16_t player_id, uint16_t card_id) {
    if (player_id != turn_)
        return false;

    if (auto *act = dynamic_cast<Action *>(get_by_id(card_id))) {
        Player *player = static_cast<Player *>(get_by_id(player_id));

        if (player->get_actions_limit() == 0) {
            return false;
        }

        player->play_card(act);
        player->change_actions_limit(-1);

        return true;
    }

    return false;
}

uint16_t Engine::end_turn(uint16_t player_id) {
    if (player_id != turn_) {
        return turn_;
    }
    Player *player = dynamic_cast<Player *>(get_by_id(player_id));

    std::vector<Base *> captured_bases = playground.check_bases();
    for (auto base : captured_bases) {
        LeaderBoard_t leader_board = playground.capture_base(base);
        playground.destroy_base(base);
        playground.set_new_base();

        distribute_points(base, leader_board);
    }

    player->take_card(CARDS_TO_DRAW_END_TURN);
    player->set_actions_limit(1);
    player->set_minions_limit(1);

    while (player->get_number_of_cards() > MAX_CARDS_IN_HAND) {
        player->dump_random_card();
    }

    auto win_pair = playground.check_for_winner();

    if (win_pair.first) {
        game_over_ = true;
        winner_ = win_pair.second;
    }

    turn_ = (turn_ + 1) % (playground.get_number_of_players());
    return turn_;
}

bool Engine::is_over() const { return game_over_; }

uint32_t Engine::get_winner() const { return winner_; }

void Engine::prepare_game() {
    for (uint16_t i = 0; i < playground.get_number_of_players(); i++) {
        std::string player_deck_file = PLAYER + std::to_string(i) + DECK_JSON_FILE;
        parser_.json_for_player(player_deck_file);
    }
}

void Engine::start_game(GraphicsModel::Data::Attributes &attributes) {
    size_t curr_id = playground.get_number_of_players();

    parser_.parse_json(entities_, BASE_DATA_BASE_FILE);
    for (size_t id = curr_id; id < entities_.size(); id++) {
        playground.gain_base_on_start(static_cast<Base *>(get_by_id(id)));
    }

    for (size_t i = 0; i < playground.get_number_of_players(); ++i) {
        playground.set_new_base();
    }

    curr_id = entities_.size();

    for (uint16_t i = 0; i < playground.get_number_of_players(); i++) {
        std::string player_deck_file = PLAYER + std::to_string(i) + DECK_JSON_FILE;

        parser_.parse_json(entities_, player_deck_file);
        Player *player = static_cast<Player *>(get_by_id(i));

        for (size_t id = curr_id; id < entities_.size(); id++) {
            PlayerCard *card = static_cast<PlayerCard *>(get_by_id(id));
            card->change_owner(i);
            player->gain_card_on_start(card);
        }

        curr_id = entities_.size();

        player->shuffle_deck();
        player->take_card(5);
    }
    attributes.draw_player = 0;
}

void Engine::distribute_points(Base *base, LeaderBoard_t &leader_board) {
    uint32_t winner_num = 0;
    uint32_t prev_points = leader_board.front().second;
    uint32_t same_score = 1;

    for (auto &player_winner : leader_board) {
        Player *player = static_cast<Player *>(get_by_id(player_winner.first));

        if (player_winner.first == leader_board.front().first) {
            player->gain_points(base->get_points().at(winner_num));
            prev_points = player_winner.second;
            continue;
        } else if (prev_points == player_winner.second) {
            same_score += 1;
        } else {
            winner_num += same_score;
            same_score = 1;
        }

        if (winner_num >= NUMBER_OF_WINNERS) {
            break;
        }

        player->gain_points(base->get_points().at(winner_num));
    }
}

Engine::~Engine() {
    for (auto curr = entities_.begin(), end = entities_.end(); curr != end; ++curr) {
        delete (*curr);
    }
}

void Engine::dump_state(std::string file_name) const {
    std::ofstream os(file_name);

    os << "------------------------------------\n";
    os << "Dumping state of engine\n";
    os << "Turn: " << turn_ << "\n";
    os << "Time: " << time_ << "\n";

    os << "Dumping entities\n";
    for (auto curr = entities_.begin(), end = entities_.end(); curr != end; ++curr) {
        os << "\tId: " << (*curr)->get_id() << "\n";
    }

    playground.dump_state(os);

    os << "------------------------------------\n";
}

} // namespace Mayhem

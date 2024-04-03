#include "engine/engine.h"
#include "core/base.h"
#include "engine/player.h"
#include "graphics/graphics.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

namespace Mayhem { // Engine methods

// Player can only have 10 cards in hand
const uint32_t MAX_CARDS_IN_HAND = 10;

// At the end of the turn player draw 2 cards
const uint32_t CARDS_TO_DRAW_END_TURN = 2;

// Location of the data base with all cards
const std::string CARDS_DATA_BASE_FILE = "../assets/cards_data_base.json";

// Location of the data base with all bases
const std::string BASE_DATA_BASE_FILE = "../assets/base_data_base.json";

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

    std::cout << "Player " << player_id << " played card " << card_id << " on base " << base_id
              << std::endl; // Change to more readable

    Player *player = static_cast<Player *>(get_by_id(player_id)); // FIXME: Change that
    Minion *card = static_cast<Minion *>(get_by_id(card_id));
    Base *base = static_cast<Base *>(get_by_id(base_id));

    if (player_id != card->get_owner())
        return false;

    player->play_card(card); // FIXME: add error handling
    base->gain_minion(card);

    return true;
}

bool Engine::play_action(uint16_t player_id, uint16_t card_id) {
    if (player_id != turn_)
        return false;

    std::cout << "Player " << player_id << " played action " << card_id << std::endl;

    if (auto *act = dynamic_cast<Action *>(get_by_id(card_id))) {
        Player *player = static_cast<Player *>(get_by_id(player_id)); // FIXME: Change that
        player->play_card(act);

        return true;
    }

    return false;
}

uint16_t Engine::end_turn(uint16_t player_id) {
    if (player_id != turn_) {
        return turn_;
    }
    Player *player = dynamic_cast<Player *>(get_by_id(player_id));

    auto captured_bases = playground.check_bases();
    for (auto base : captured_bases) {
        auto leader_board = playground.capture_base(base);
        playground.destroy_base(base);
        playground.set_new_base();

        distribute_points(leader_board);
    }

    player->take_card(CARDS_TO_DRAW_END_TURN);

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

void Engine::start_game(Graphics::DrawingAttributes &attributes) {
    std::srand(std::time(0));

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
        std::string player_deck_file = "player_deck.json";
        parser_.json_for_player(CARDS_DATA_BASE_FILE, player_deck_file);

        parser_.parse_json(entities_, player_deck_file);
        Player *player = static_cast<Player *>(get_by_id(i));

        for (size_t id = curr_id; id < entities_.size(); id++) {
            PlayerCard *card = static_cast<PlayerCard *>(get_by_id(id));
            card->change_owner(i);
            player->gain_card_on_start(card);
        }

        curr_id = entities_.size();

        player->take_card(5);
    }
    attributes.draw_player = 0;
}

void Engine::distribute_points(LeaderBoard_t &leader_board) {
    for (auto pair : leader_board) {
        Player *player = static_cast<Player *>(get_by_id(pair.first));
        player->gain_points(pair.second);
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

#include "core/game_core.h"
#include "core/base.h"
#include "graphics/graphics.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Mayhem { // Engine methods

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

    Player *player = dynamic_cast<Player *>(get_by_id(player_id)); // FIXME: Change that
    Minion *card = dynamic_cast<Minion *>(get_by_id(card_id));
    Base *base = dynamic_cast<Base *>(get_by_id(base_id));

    if (player_id != card->get_owner())
        return false;

    player->play_card(card); // FIXME: add error handling
    base->gain_minion(card);

    return true;
}

void Engine::end_turn(uint16_t player_id) {
    Player *player = dynamic_cast<Player *>(get_by_id(player_id));

    auto captured_bases = playground.check_bases();
    for (auto p : captured_bases) {
        auto leader_board = playground.capture_base(p);
        playground.destroy_base(p);
        playground.set_new_base();

        distribute_points(leader_board);
    }

    player->take_card(
        2); // no overflow yet. For overflow I can suggest to make a state of overflow, So the interface constantly
            // reads this state, and make player to choose card. He won't make a next move, before he choose card

    turn_ = (turn_ + 1) % (playground.get_number_of_players());
}

void Engine::start_game() {
    size_t curr_id = playground.get_number_of_players();

    parser_.parse_json(entities_, "base_deck.json"); // FIXME: automate it

    for (size_t id = curr_id; id < entities_.size(); id++) {
        playground.gain_base_on_start(static_cast<Base *>(entities_.at(id)));
    }

    curr_id = entities_.size();

    for (uint16_t i = 0; i < playground.get_number_of_players(); i++) {
        parser_.parse_json(entities_, "player1_deck.json"); // FIXME: need to somehow automate input file
        Player *player = static_cast<Player *>(get_by_id(i));

        for (size_t id = curr_id; id < entities_.size(); id++) {
            PlayerCard *card = static_cast<PlayerCard *>(entities_.at(id));
            card->change_owner(i);
            player->gain_card_on_start(card);
        }

        curr_id = entities_.size();

        player->take_card(5);
    }

}

} // namespace Mayhem

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

namespace Mayhem { // Player methods

void Player::dump_card (PlayerCard* card) {
    deck_.remove_card(card);
    dump_deck_.gain_card(card);
}

void Player::take_card (uint32_t number_of_cards) { 
    for (uint32_t i = 0; i < number_of_cards; ++i) {
        if (deck_.size == 0) {
            deck_ = dump_deck_;
            dump_deck_.clear_deck();
        }

        PlayerCard* new_card = deck_.take_card();
        hand_.take_card(new_card);
    }
}

void Player::play_card (PlayerCard *card) {
    hand_.remove_card(card);
}

void Player::gain_card_on_start(PlayerCard *card) {
    dump_deck_.gain_card(card);
}

} // namespace Mayhem

#include "engine/engine.h"
#include "engine/player.h"
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

        player->take_card(2);
    }

}

} // namespace Mayhem
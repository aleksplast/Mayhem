#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../include/core/game_core.h"

namespace Mayhem
{

Entity* Engine::get_by_id(uint16_t entity_id) {
    if (entity_id >= entities_.size()) {
        std::cout << "HERE NEED TO BE LOG: entity id is bigger than vector size" << std::endl;
        return nullptr;
    }
     
    return entities_[entity_id];
}

Engine::Engine(): turn_(1), time_(0), entities_(), playground(entities_) {
    // ----------------------FIXME:Mock --------------------------------
    std::cout << "Making two players" << std::endl;
    
}

bool Engine::place_card(uint16_t player_id, uint16_t card_id, uint16_t base_id) {
    if (player_id != turn_)
        return false;

    std::cout << "Player "<< player_id << " played card "<< card_id << " on base "<< base_id << std::endl; // Change to more readable

    Player*     player = dynamic_cast<Player*>(get_by_id(player_id));
    PlayerCard* card   = dynamic_cast<PlayerCard*>(get_by_id(card_id));
    Base*       base   = dynamic_cast<Base*>(get_by_id(base_id));

    if (player_id != card->get_owner())
        return false;

    player->play_card(card); // FIXME: add error handling
    base->gain_card(card);

    return true;
}

void Engine::give_card(uint16_t player_id, uint16_t card_id) {
    std::cout << "Give card " << card_id << "to player " << player_id << std::endl;
    
    Player*     player = dynamic_cast<Player*>(get_by_id(player_id));
    PlayerCard* card   = dynamic_cast<PlayerCard*>(get_by_id(card_id));

    player->gain_card(card);
}

void Engine::end_turn(uint16_t player_id) {
    //FIXME: capture bases, give cards, return cards

    turn_ = (turn_ + 1) % (playground.get_number_of_players());
}

} // namespace Mayhem
//

int main() {
}

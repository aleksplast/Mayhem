#include <iostream>
#include <SFML/Graphics.hpp>
#include "core/game_core.h"
#include "core/base.h"

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

    Player*     player = dynamic_cast<Player*>(get_by_id(player_id)); // FIXME: Change that
    Minion*     card   = dynamic_cast<Minion*>(get_by_id(card_id));
    Base*       base   = dynamic_cast<Base*>(get_by_id(base_id));

    if (player_id != card->get_owner())
        return false;

    player->play_card(card); // FIXME: add error handling
    base->gain_minion(card);

    return true;
}

void Engine::end_turn(uint16_t player_id) {
    Player* player = dynamic_cast<Player*>(get_by_id(player_id));
    
    std::vector<Base*> captured_bases = playground.check_bases();
    for (auto p: captured_bases) {
        auto leader_board = playground.capture_base(*p);
        playground.destroy_base(*p);
        playground.set_new_base();

        distribute_points(leader_board);
    }
    
    player->take_card(2); // no overflow yet. For overflow I can suggest to make a state of overflow, So the interface constantly reads this state, and make player to choose card. He won't make a next move, before he choose card

    turn_ = (turn_ + 1) % (playground.get_number_of_players());
}

} // namespace Mayhem

namespace Mayhem
{
    Playground::Playground(std::vector<Entity*>& entities) {
        
    }

    std::vector<Base*> Playground::check_bases() {
        std::vector<Base*> captured_bases {};

        for (auto curr = active_bases_.begin(), end = active_bases_.end(); curr != end; ++curr) { // here we can iterate over ref, not iterators
            if ((*curr).is_captured()) {
                captured_bases.push_back(&*curr);
            }
        }

        return captured_bases;
    }
    
    LeaderBoard_t& Playground::capture_base(Base& base) {
        auto cards = base.get_cards();
        LeaderBoard_t leader_board;

        for (auto curr = cards.begin(), end = cards.end(); curr != end; ++curr) {
            players_[ curr->get_owner() ].dump_card(&*curr); // 
            leader_board[curr->get_owner()] += curr->get_power();
            base.remove_minion(*curr);
        }

        return leader_board;
    }

    void Playground::destroy_base(Base& base) {
        active_bases_.remove_card(base);
        dump_.gain_card(&base);
    }

    void Playground::set_new_base() {
        active_bases_.gain_card(&bases_.take_card()); 
    }
    
} // namespace Mayhem


int main() {
}

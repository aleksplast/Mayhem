#include "engine/player.h"
#include "core/base.h"
#include "graphics/graphics.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Mayhem { // Player methods

void Player::dump_card(PlayerCard* card) {
    deck_.remove_card(card);
    dump_deck_.gain_card(card);
}

void Player::take_card(uint32_t number_of_cards) {
    for (uint32_t i = 0; i < number_of_cards; ++i) {
        if (deck_.size() == 0) {
            deck_ = dump_deck_;
            dump_deck_.clear_deck();
        }

        PlayerCard* new_card = deck_.take_card();
        hand_.gain_card(new_card);
    }
}

void Player::play_card(PlayerCard *card) {
    hand_.remove_card(card);
}

void Player::gain_card_on_start(PlayerCard *card) {
    dump_deck_.gain_card(card);
}

} // namespace Mayhem

#include "engine/player.h"
#include "core/base.h"
#include "graphics/graphics.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace Mayhem { // Player methods

Player::Player(uint32_t id)
        : Entity("../assets/images/player.png", id), hand_("../assets/images/deck"),
          dump_deck_("../assets/images/deck"), deck_("../assets/images/deck"), points_(0) {
        sprite.setColor(sf::Color(0, 0, 0, 100));
    };

size_t Player::get_number_of_cards() { return hand_.size(); };

void Player::dump_card(PlayerCard *card) {
    deck_.remove_card(card);
    dump_deck_.gain_card(card);
}

void Player::take_card(uint32_t number_of_cards) {
    for (uint32_t i = 0; i < number_of_cards; ++i) {
        if (deck_.size() == 0) {
            deck_ = dump_deck_;
            dump_deck_.clear_deck();
            // deck_.shuffle();
        }
        if (deck_.size() == 0) {
            return;
        }

        PlayerCard *new_card = deck_.take_card();
        hand_.gain_card(new_card);
    }
}

void Player::play_card(PlayerCard *card) { hand_.remove_card(card); }

void Player::gain_card_on_start(PlayerCard *card) { dump_deck_.gain_card(card); }

void Player::dump_random_card() {
    size_t card_num = static_cast<size_t>(std::rand()) % hand_.size();
    size_t num = 0;
    auto dump = hand_.begin();
    for (auto end = hand_.end(); dump != end; ++dump) {
        if (num == card_num)
            break;
        num += 1;
    }

    hand_.remove_card(*dump);
}

void Player::gain_points(uint32_t points) { points_ += points; }

uint32_t Player::get_points() const { return points_; }

void Player::dump_state(std::ofstream &os) const {
    os << "\nDumping player\n";
    os << "-----\n";
    os << "points: " << points_;
    os << "\nDumping deck\n";
    deck_.dump_state(os);
    os << "\nDumping hand\n";
    hand_.dump_state(os);
    os << "\nDumping dump deck\n";
    dump_deck_.dump_state(os);

    os << "-----\n";
}

} // namespace Mayhem

#include "engine/player.h"
#include "core/base.h"
#include "graphics/graphics.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace Mayhem { // Player methods

const std::string PLAYER_IMAGE = "../assets/images/player.png";
const std::string DECK_IMAGE = "../assets/images/deck";

Player::Player(uint32_t id)
    : Entity(PLAYER_IMAGE, id), hand_(DECK_IMAGE), dump_deck_(DECK_IMAGE), deck_(DECK_IMAGE), points_(0){};

size_t Player::get_number_of_cards() { return hand_.size(); };

void Player::dump_card(PlayerCard *card) { dump_deck_.gain_card(card); }

void Player::take_card(uint32_t number_of_cards) {
    for (uint32_t i = 0; i < number_of_cards; ++i) {
        if (deck_.size() == 0) {
            deck_ = dump_deck_;
            dump_deck_.clear_deck();
            deck_.shuffle();
        }
        if (deck_.size() == 0) {
            return;
        }

        PlayerCard *new_card = deck_.take_card();
        hand_.gain_card(new_card);
    }
}

void Player::play_card(PlayerCard *card) { hand_.remove_card(card); }

int Player::get_minions_limit() const { return minions_limit_; }

int Player::get_actions_limit() const { return actions_limit_; }

void Player::change_minions_limit(int num) { minions_limit_ += num; }

void Player::change_actions_limit(int num) { actions_limit_ += num; }

void Player::set_actions_limit(int num) { actions_limit_ = num; }

void Player::set_minions_limit(int num) { minions_limit_ = num; }

void Player::gain_card_on_start(PlayerCard *card) { deck_.gain_card(card); }

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

void Player::shuffle_deck() { deck_.shuffle(); }

void Player::dump_state(std::ostream &os) const {
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

#ifndef PLAYER_H
#define PLAYER_H

#include "core/base.h"
#include "graphics/graphics.hpp"
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>

namespace Mayhem {

// Struct with player id and his points
using Player_points_t = std::pair<uint32_t, uint32_t>;
// Struct with top players and their points
using LeaderBoard_t = std::list<Player_points_t>;

// Class representing Player
class Player final : public Entity {
  private:
    // Card in hand
    Deck<PlayerCard *> hand_;

    // Cards in dump
    Deck<PlayerCard *> dump_deck_;

    // Cards in deck
    Deck<PlayerCard *> deck_;

    // Victory points as a widget
    Button points_widget_;

    // Current points player have
    uint32_t points_;

    // How many actions player can play per turn
    int actions_limit_ = 1;

    // How many minions player can play per turn
    int minions_limit_ = 1;

  public:
    Player(uint32_t id);
    ~Player() = default;

  public:
    //!--------------------------------
    //! @brief Destroys card in hand, no interaction with the base
    //! @param[out] card card to destroy
    //!--------------------------------
    void play_card(PlayerCard *card);

    //!--------------------------------
    //! @brief Add card to dump deck
    //! @param[out] card Card to add
    //!--------------------------------
    void dump_card(PlayerCard *card);

    //!--------------------------------
    //! @brief Gain card to deck on the start of the game
    //! @param[out] card Card to gain
    //!--------------------------------
    void gain_card_on_start(PlayerCard *card);

    //!--------------------------------
    //! @brief End turn of the player
    //!--------------------------------
    void end_turn();

    //!--------------------------------
    //! @brief Moves number_of_cards from deck to hand
    //! @param[in] number_of_cards Number of cards to draw
    //!--------------------------------
    void take_card(uint32_t number_of_cards);

    //!--------------------------------
    //! @brief Returns number of cards in hand
    //! @return Number of cards in hand
    //!--------------------------------
    size_t get_number_of_cards();

    //!--------------------------------
    //! @brief Returns minions_limit_
    //!--------------------------------
    int get_minions_limit() const;

    //!--------------------------------
    //! @brief Return actions_limit_
    //!--------------------------------
    int get_actions_limit() const;

    //!--------------------------------
    //! @brief Change actions limit by num
    //! @param[in] num Add num to current minions limit
    //!--------------------------------
    void change_minions_limit(int num);

    //!--------------------------------
    //! @brief Change actions limit by num
    //! @param[in] num Add num to current minions limit
    //!--------------------------------
    void change_actions_limit(int num);

    //!--------------------------------
    //! @brief Set minions limit to num
    //! @param[in] num Num minions limit must be set to
    //!--------------------------------
    void set_minions_limit(int num);

    //!--------------------------------
    //! @brief Set minions limit to num
    //! @param[in] num Num actions limit must be set to
    //!--------------------------------
    void set_actions_limit(int num);

    //!--------------------------------
    //! @brief Dump state of the player
    //! @param[in] os ostream to write to
    //!--------------------------------
    void dump_state(std::ostream &os) const;

    //!--------------------------------
    //! @brief Dump random card from hand
    //!--------------------------------
    void dump_random_card();

    //!--------------------------------
    //! @brief Gain winning points
    //! @param[in] points points to gain
    //!--------------------------------
    void gain_points(uint32_t points);

    //!--------------------------------
    //! @return Get number of winning points
    //!--------------------------------
    uint32_t get_points() const;

    //!--------------------------------
    //! @brief Shuffle deck_, dump_deck_ and hand_ untouched
    //!--------------------------------
    void shuffle_deck();

  public: // graphics function
    // Draw player
    void draw(GraphicsModel::Data::Attributes &attributes, const sf::FloatRect &rect, const float angle);
    void draw(sf::RenderWindow &window, const sf::FloatRect &rect, const float angle) override;
}; // class Player

} // namespace Mayhem

#endif // PLAYER_H

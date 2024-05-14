#ifndef CARD_H
#define CARD_H

#include "entity.h"
#include "graphics/button.hpp"
#include <fstream>
#include <stdlib.h>
#include <string>

namespace Mayhem {

// Card type
class Card : public Entity {
  public:
    Card(const std::string &name_main_file, int id, const std::string &name_extra_file = "");
}; // class Card

// Card that can belong to a player
class PlayerCard : public Card {
  private:
    // Owner of the card
    uint32_t owner_id_;

  public:
    PlayerCard(const std::string &name_main_file, int id, const std::string &name_extra_file = "");

    // Get owner of the card
    uint32_t get_owner();

    // Change owner of the card
    void change_owner(uint32_t owner);

    // Dump state of the card
    virtual void dump_state(std::ostream &os) const {};

  public:
    virtual void copy(const PlayerCard &card) {}
}; // class PlayerCard

// Minion class
class Minion final : public PlayerCard {
  private:
    // Power of the minion
    uint32_t power_;
    Button power_picture_;

  public:
    //!--------------------------------
    //! @brief Constructor for Minion
    //! @param[out] minion_main_file main file image for minion
    //! @param[out] minion_extra_file extra file image for minion
    //! @param[in] id id of the minion
    //! @param[in] power power of the minion
    //!--------------------------------
    Minion(const std::string &minion_main_file, const std::string &minion_extra_file, int id, uint32_t power);

    //!--------------------------------
    //! @brief Dump state of the minion
    //! @param[out] os ostream to dump to
    //!--------------------------------
    void dump_state(std::ostream &os) const override;

    //!--------------------------------
    //! @brief Get power of the minion
    //!--------------------------------
    uint32_t get_power() const;

    //!--------------------------------
    //! @brief Increase power of the minion
    //! @param[in] power power to increase by
    //!--------------------------------
    void increase_power(uint32_t power);

    //!--------------------------------
    //! @brief Decrease power of the minion
    //! @param[in] power power to decrease by
    //!--------------------------------
    void decrease_power(uint32_t power);

  public: // graphics functions
    // Draw minion on the window
    void draw(sf::RenderWindow &window, const sf::FloatRect &rect, const float angle) override;
}; // class Minion

} // namespace Mayhem

#endif // CARD_H

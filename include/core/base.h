#ifndef BASE_H
#define BASE_H

#include "card.h"
#include "deck.h"
#include "graphics/graphics_model.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace Mayhem {

class Base final : public Card {
  private:
    // Power player need to get to win here
    uint32_t power_to_win_ = 0;

    // Points players gain after capture
    std::array<uint32_t, 3> points_ = {0, 0, 0};

    // Minions on the base
    Deck<Minion *> cards_;

    // Units power as a widget
    Button units_power_;

  public:
    //!--------------------------------
    //! @brief Add minion to cards on the base
    //! @param[out] card minion to add
    //!--------------------------------
    void gain_minion(Minion *card);

    //!--------------------------------
    //! @brief Remove minion from minion on the base
    //! @param[out] card minion to remove
    //!--------------------------------
    void remove_minion(Minion *card);

    //!--------------------------------
    //! @brief Check if the base is captured
    //! @return true if captured, false if not
    //!--------------------------------
    bool is_captured() const;

    //!--------------------------------
    //! @brief Get power to win on this base
    //!--------------------------------
    uint32_t get_power_to_win() const;

    //!--------------------------------
    //! @brief Get current power on this base
    //!--------------------------------
    uint32_t get_current_power() const;

    //!--------------------------------
    //! @brief Get winning points on this base
    //!--------------------------------
    std::array<uint32_t, 3> get_points() const;

    //!--------------------------------
    //! @brief Dump state of the base
    //! @param[out] os ostream to dump to
    //!--------------------------------
    void dump_state(std::ostream &os) const;

  public: // graphic functions
    Base(const std::string &base_file, int id, uint32_t power_to_win, std::array<uint32_t, 3> points);

    // Show cards on the base
    void show_cards(GraphicsModel::Data::Attributes &attributes) const;

    // Get cards on the base
    const Deck<Minion *> &get_cards();

    void draw(sf::RenderWindow &window, const sf::FloatRect &rect, const float angle) override;
}; // class Base

} // namespace Mayhem

#endif // END_H

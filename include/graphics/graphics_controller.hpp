#ifndef GRAPHICS_CONTROLLER_HPP
#define GRAPHICS_CONTROLLER_HPP

#include "graphics/command.hpp"
#include "graphics/graphics_model.hpp"

namespace Mayhem {

/// The graphics subclass that handles events from the user
class GraphicsController {
  private:
    /// @brief Graphics model
    GraphicsModel &model;
    /// @brief Event buffer
    Command command;

  private:
    /// @brief Searches for the selected player card
    /// @param[in] pos Mouse pos
    /// @return Pointer to the pressed card or nullptr if don't found
    PlayerCard *pressed_card(const sf::Vector2f &pos);

    /// @brief Searches for the selected base
    /// @param[in] pos Mouse pos
    /// @return Pointer to the pressed base or nullptr if don't found
    Base *pressed_base(const sf::Vector2f &pos);

    /// @brief Searches for the selected deck
    /// @param[in] pos Mouse pos
    /// @return Pointer to the pressed deck or nullptr if don't found
    Deck<PlayerCard *> *pressed_deck(const sf::Vector2f &pos);

    /// @brief Searches for the selected button
    /// @param[in] pos Mouse pos
    /// @return Type of pressed button
    Button::Type pressed_button(const sf::Vector2f &pos);

    /// @brief Searches for the selected shown card
    /// @param[in] pos Mouse pos
    /// @return Pointer to the pressed card or nullptr if don't found
    PlayerCard *pressed_shown_card(const sf::Vector2f &pos);

    /// @brief Parse mouse events
    /// @param[out] event Event
    void process_mouse_events(const sf::Event &event);

  public:
    /// @brief Constructor
    GraphicsController() = delete;
    /// @brief Constructor
    /// @param m Link to the graphics model
    GraphicsController(GraphicsModel &m);

    /// Receives and distributes events
    void process_events();

    /// @brief Destructor
    ~GraphicsController() = default;

}; // class GraphicsColntroller

} // namespace Mayhem

#endif // GRAPHICS_CONTROLLER_HPP

#ifndef GRAPHICS_CONTROLLER_HPP
#define GRAPHICS_CONTROLLER_HPP

#include "graphics/command.hpp"
#include "graphics/graphics_model.hpp"

namespace Mayhem {

// The graphics subclass that handles events from the user
class GraphicsController {
  private:
    GraphicsModel &model;
    Command command;

  private:
    // searches for the selected player card
    PlayerCard *pressed_card(const sf::Vector2f &pos);

    // searches for the selected base
    Base *pressed_base(const sf::Vector2f &pos);

    // searches for the selected deck
    Deck<PlayerCard *> *pressed_deck(const sf::Vector2f &pos);

    // searches for the selected button
    Button::Type pressed_button(const sf::Vector2f &pos);

    // searches for the selected shown cards
    PlayerCard *pressed_shown_card(const sf::Vector2f &pos);

    // parse mouse events
    void process_mouse_events(const sf::Event &event);

  public:
    GraphicsController() = delete;
    GraphicsController(GraphicsModel &m);

    // receives and distributes events
    void process_events();
    ~GraphicsController() = default;

}; // class GraphicsColntroller

} // namespace Mayhem

#endif // GRAPHICS_CONTROLLER_HPP

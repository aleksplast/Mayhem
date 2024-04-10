#ifndef GRAPHICS_CONTROLLER_HPP
#define GRAPHICS_CONTROLLER_HPP

#include "graphics/command.hpp"
#include "graphics/graphics_model.hpp"

namespace Mayhem {

class GraphicsController {
  private:
    GraphicsModel &model;
    Command command;

  private:
    PlayerCard *pressed_card(const sf::Vector2f &pos);
    Base *pressed_base(const sf::Vector2f &pos);
    Deck<PlayerCard *> *pressed_deck(const sf::Vector2f &pos);
    Button::Type pressed_button(const sf::Vector2f &pos);
    void process_mouse_events(const sf::Event &event);

  public:
    GraphicsController() = delete;
    GraphicsController(GraphicsModel &m);
    void process_events();
    ~GraphicsController() = default;

}; // class GraphicsColntroller

} // namespace Mayhem

#endif // GRAPHICS_CONTROLLER_HPP

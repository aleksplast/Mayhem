#include "../include/core/game_core.h"
#include "../include/graphics/graphics.hpp"

using namespace Mayhem;

int main() {
  Graphics graphics(Graphics::GameType::OFLINE, 0);
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  graphics.window.create(sf::VideoMode::getFullscreenModes()[0], "Mayhem",
                         sf::Style::Default, settings);
  graphics.window.setFramerateLimit(100);

  Engine engine(graphics);
  while (graphics.window.isOpen()) {
    sf::Event event;
    while (graphics.window.pollEvent(event))
      ;
    {
      if (event.type == sf::Event::Closed) {
        graphics.window.close();
      }
    }
    graphics.window.clear();
    engine.draw(graphics);
    graphics.window.display();
  }
  return 0;
}
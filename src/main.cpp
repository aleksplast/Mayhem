#include "engine/engine.h"
#include "graphics/graphics.hpp"
#include <SFML/Graphics.hpp>
#include "core/base.h"
#include "core/deck.h"


using namespace Mayhem;

int main() {
    Graphics graphics(Graphics::GameType::OFLINE, 0);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    graphics.window.create(sf::VideoMode::getFullscreenModes()[0], "Mayhem", sf::Style::Default, settings);
    graphics.window.setFramerateLimit(100);

    Engine engine (graphics);
    engine.start_game();
    engine.dump_state("dump_file");

    while (graphics.window.isOpen()) {
        graphics.process_events(engine);
        graphics.window.clear();
        engine.draw(graphics);
        graphics.window.display();
    }
    return 0;
}

#include "../include/core/game_core.h"
#include "../include/graphics/graphics.hpp"

using namespace Mayhem;

int main()
{
    Engine engine;
    Graphics graphics(Graphics::GameType::OFLINE, 4, 0);
    graphics.window.create(sf::VideoMode(800, 600), "Mayhem");
    
    while (graphics.window.isOpen())
    {
        sf::Event event;
        while (graphics.window.pollEvent(event));
        {
            if (event.type == sf::Event::Closed)
            {
                graphics.window.close();
            }
        }
    }
    return 0;
}
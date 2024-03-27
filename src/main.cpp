#include "core/base.h"
#include "core/deck.h"
#include "engine/engine.h"
#include "graphics/graphics.hpp"
#include <SFML/Graphics.hpp>

using namespace Mayhem;

int main() {
    Graphics graphics;
    Engine engine;
    engine.start_game(graphics.attributes);
    engine.dump_state("dump_file");
    graphics.launch_game(engine);
    return 0;
}

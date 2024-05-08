#include "graphics/graphics.hpp"
#include "engine/engine.h"
#include "graphics/graphics_controller.hpp"
#include "graphics/graphics_model.hpp"
#include "graphics/graphics_view.hpp"

namespace Mayhem {

void Graphics::launch_game() {
    Engine engine;
    GraphicsModel model(engine);
    GraphicsController controller(model);
    GraphicsView view(model);
    engine.prepare_game();
    engine.start_game(model.attributes);
    engine.dump_state("dump_file");

    while (model.attributes.window.isOpen()) {
        controller.process_events();
        view.display();
    }
}

} // namespace Mayhem

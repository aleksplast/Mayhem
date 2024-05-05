#include "graphics/graphics.hpp"
#include "engine/engine.h"
#include "graphics/graphics_controller.hpp"
#include "graphics/graphics_model.hpp"
#include "graphics/graphics_view.hpp"

namespace Mayhem {

void Graphics::launch_game() {
    if (ifOffline) {
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
    else {
        //в engine будет лежат клиент, а поля онлайн и поля клиента дожны лежать в приватной части
        // Если онлайн, то будет вызываться метод онлайна, который под собой вызывает метод сервера
    }
}

} // namespace Mayhem

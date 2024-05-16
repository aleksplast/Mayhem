#include "graphics/graphics.hpp"
#include "engine/engine.h"
#include "graphics/graphics_controller.hpp"
#include "graphics/graphics_model.hpp"
#include "graphics/graphics_view.hpp"

namespace Mayhem {

void Graphics::launch_game(std::string mode, std::string port, std::string player) {
    if (mode.compare("offline") == 0) {
        Engine engine;
        GraphicsModel model(engine);
        GraphicsController controller(model);
        GraphicsView view(model);
        model.attributes.draw_player = 0;
        engine.prepare_game();
        engine.start_game(model.attributes);
        engine.dump_state("dump_file");

        while (model.attributes.window.isOpen()) {
            controller.process_events();
            view.display();
        }

    } else {
        if (port.compare("0") == 0) {
            std::string server_address("0.0.0.0:50051");
            Engine engine;
            GraphicsModel model(engine);
            GraphicsController controller(model);
            GraphicsView view(model);
            model.attributes.draw_player = 0;
            engine.prepare_game();
            engine.start_game(model.attributes);
            engine.dump_state("dump_file");

            // FIXME TIAHZ: function
            ServerBuilder builder;
            builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
            builder.RegisterService(static_cast<enginePackage::MainServerEngine::Service *>(&engine));
            std::unique_ptr<Server> server(builder.BuildAndStart());
            std::cout << "Server listening on " << server_address << std::endl;
            server->Wait();

            while (model.attributes.window.isOpen()) {
                controller.process_events();
                view.display();
            }
        } else {
            Engine engine(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()), port);
            GraphicsModel model(engine);
            std::cout << "Current player " << player << std::endl;
            model.attributes.draw_player = stoi(player); // FIXME: ADD CHECKS
            GraphicsController controller(model);
            GraphicsView view(model);
            engine.start_game(model.attributes);
            engine.dump_state("dump_file");

            while (model.attributes.window.isOpen()) {
                controller.process_events();
                view.display();
            }
        }
    }
}

} // namespace Mayhem

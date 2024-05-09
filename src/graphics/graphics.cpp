#include "graphics/graphics.hpp"
#include "engine/engine.h"
#include "graphics/graphics_controller.hpp"
#include "graphics/graphics_model.hpp"
#include "graphics/graphics_view.hpp"
#include "graphics/menu.hpp"

namespace Mayhem {

void Graphics::run(std::string server_address, std::string client_address) {
    using Scope = GraphicsModel::Data::MenuAttributes;
    Scope attributes;
    if (server_address.compare("server") == 0) {
        launch_game("server", server_address, client_address, 0, attributes);
        return;
    }
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::VideoMode video_mode = sf::VideoMode::getFullscreenModes()[4];
    sf::Vector2u default_window_size = sf::Vector2u(video_mode.width, video_mode.height);

    window.create(video_mode, "Mayhem", sf::Style::Default, settings);
    window.setFramerateLimit(100);

    sf::Image icon;
    if (icon.loadFromFile("../assets/images/icon")) {
        sf::Vector2u icon_size = icon.getSize();
        window.setIcon(icon_size.x, icon_size.y, icon.getPixelsPtr());
    }

    attributes.num_players = 4;
    attributes.action = GraphicsModel::Data::MenuAttributes::GameAction::play;
    attributes.type = GraphicsModel::Settings::GameType::offline;
    attributes.default_window_size = default_window_size;
    MainMenu menu;
    menu.run(window, attributes);
    if (attributes.action == Scope::GameAction::play)
        if (attributes.type == GraphicsModel::Settings::GameType::offline)
            launch_game(attributes);
        else if (attributes.type == GraphicsModel::Settings::GameType::online)
            launch_game("player", server_address, client_address, attributes.number_of_player, attributes);
        else
            return;
    else
        return;
}

void Graphics::launch_game(const GraphicsModel::Data::MenuAttributes &attributes) {
    Engine engine(attributes.num_players);
    GraphicsModel model(engine, window, attributes);
    GraphicsController controller(model);
    GraphicsView view(model);
    model.attributes.draw_player = 0;
    engine.prepare_game();
    engine.start_game();
    model.attributes.draw_player = 0;
    engine.dump_state("dump_file");

    while (model.attributes.window.isOpen()) {
        controller.process_events();
        view.display();
    }
}

void Graphics::launch_game(std::string engine_mode, std::string server_address, std::string client_address, int player,
                           const GraphicsModel::Data::MenuAttributes &attributes) {
    if (engine_mode.compare("server") == 0) {
        Engine engine(attributes.num_players);
        GraphicsModel model(engine, window, attributes);
        GraphicsController controller(model);
        GraphicsView view(model);
        model.attributes.draw_player = 0;
        engine.prepare_game();
        engine.start_game();
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
        Engine engine(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()), client_address,
                      attributes.num_players);
        GraphicsModel model(engine, window, attributes);
        std::cout << "Current player " << player << std::endl;
        model.attributes.draw_player = player; // FIXME: ADD CHECKS
        GraphicsController controller(model);
        GraphicsView view(model);
        engine.start_game();
        engine.dump_state("dump_file");

        while (model.attributes.window.isOpen()) {
            controller.process_events();
            view.display();
        }
    }
}

} // namespace Mayhem

#include "graphics/graphics_model.hpp"

namespace Mayhem {

GraphicsModel::GraphicsModel(Engine &e) : engine(e) {
    type = Settings::GameType::ofline;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::VideoMode video_mode = sf::VideoMode::getFullscreenModes()[4];
    attributes.default_window_size = sf::Vector2u(video_mode.width, video_mode.height);

    attributes.window.create(video_mode, "Mayhem", sf::Style::Default, settings);
    attributes.window.setFramerateLimit(100);
}

} // namespace Mayhem

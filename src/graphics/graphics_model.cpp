#include "graphics/graphics_model.hpp"
#include <SFML/Graphics/Image.hpp>

namespace Mayhem {

GraphicsModel::GraphicsModel(Engine &e) : engine(e) {
    type = Settings::GameType::offline;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::VideoMode video_mode = sf::VideoMode::getFullscreenModes()[4];
    attributes.default_window_size = sf::Vector2u(video_mode.width, video_mode.height);

    attributes.window.create(video_mode, "Mayhem", sf::Style::Default, settings);
    attributes.window.setFramerateLimit(100);

    sf::Image icon;
    if (icon.loadFromFile("../assets/images/icon")) {
        sf::Vector2u icon_size = icon.getSize();
        attributes.window.setIcon(icon_size.x, icon_size.y, icon.getPixelsPtr());
    }
}

} // namespace Mayhem

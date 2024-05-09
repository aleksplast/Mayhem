#include "graphics/graphics_model.hpp"
#include <SFML/Graphics/Image.hpp>

namespace Mayhem {

GraphicsModel::GraphicsModel(Engine &e, sf::RenderWindow &window, const Data::MenuAttributes &menu_attributes)
    : attributes(window), engine(e) {
    type = menu_attributes.type;
    attributes.default_window_size = menu_attributes.default_window_size;
}

} // namespace Mayhem

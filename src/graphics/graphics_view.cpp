#include "graphics/graphics_view.hpp"
#include "engine/engine.h"

namespace Mayhem {

GraphicsView::GraphicsView(GraphicsModel &m) : model(m) {}

void GraphicsView::display() {
    model.attributes.window.clear();
    model.engine.draw(model.attributes);
    model.attributes.window.display();
}

} // namespace Mayhem

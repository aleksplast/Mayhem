#ifndef GRAPHICS_VIEW_HPP
#define GRAPHICS_VIEW_HPP

#include "graphics/graphics_model.hpp"

namespace Mayhem {

// The graphics subclass responsible for drawing elements
class GraphicsView {
  private:
    GraphicsModel &model;

  public:
    GraphicsView() = delete;
    GraphicsView(const GraphicsView &) = delete;
    GraphicsView(GraphicsView &&) = delete;
    GraphicsView(GraphicsModel &m);

    // displays all items on the window
    void display();

    ~GraphicsView() = default;

}; // class GraphicsView

} // namespace Mayhem

#endif // GRAPHICS_VIEW_HPP

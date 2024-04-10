#ifndef GRAPHICS_VIEW_HPP
#define GRAPHICS_VIEW_HPP

#include "graphics/graphics_model.hpp"

namespace Mayhem {

class GraphicsView {
  private:
    GraphicsModel &model;

  public:
    GraphicsView() = delete;
    GraphicsView(const GraphicsView &) = delete;
    GraphicsView(GraphicsView &&) = delete;
    GraphicsView(GraphicsModel &m);
    void display();
    ~GraphicsView() = default;

}; // class GraphicsView

} // namespace Mayhem

#endif // GRAPHICS_VIEW_HPP

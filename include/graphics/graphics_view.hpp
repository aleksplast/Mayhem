#ifndef GRAPHICS_VIEW_HPP
#define GRAPHICS_VIEW_HPP

#include "graphics/graphics_model.hpp"

namespace Mayhem {

/// The graphics subclass responsible for drawing elements
class GraphicsView {
  private:
    /// @brief Graphics model
    GraphicsModel &model;

  public:
    GraphicsView() = delete;
    GraphicsView(const GraphicsView &) = delete;
    GraphicsView(GraphicsView &&) = delete;
    /// @brief Constructor
    /// @param m Graphics model
    GraphicsView(GraphicsModel &m);

    /// @brief displays all items on the window
    void display();

    /// @brief Destructor
    ~GraphicsView() = default;

}; // class GraphicsView

} // namespace Mayhem

#endif // GRAPHICS_VIEW_HPP

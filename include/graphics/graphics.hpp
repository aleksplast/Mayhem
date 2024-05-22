#ifndef GRAFICS_H
#define GRAFICS_H

#include "graphics/graphics_model.hpp"
#include <SFML/Graphics.hpp>
#include <string>

namespace Mayhem {

// class Graphics, that lauch and control the game
class Graphics {
  private:
    sf::RenderWindow window;

  private:
  public:
    Graphics() = default;

    void launch_game(GraphicsModel::Data::MenuAttributes &attributes);
    // initializes the main components of the game
    void launch_game(std::string engine_mode, std::string server_address, std::string client_address,
                     GraphicsModel::Data::MenuAttributes &attributes);

    // Starts the game as a whole
    void run(std::string server_address, std::string client_address = "");

    ~Graphics() = default;
}; // class Grafics

} // namespace Mayhem

#endif

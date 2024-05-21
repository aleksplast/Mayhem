#ifndef GRAFICS_H
#define GRAFICS_H
#include <string>

namespace Mayhem {

// class Graphics, that lauch and control the game
class Graphics {

  public:
    Graphics() = default;

    // initializes the main components of the game
    void launch_game(std::string game_mode, std::string engine_mode, std::string server_address,
                     std::string client_address, std::string player);

    ~Graphics() = default;
}; // class Grafics

} // namespace Mayhem

#endif

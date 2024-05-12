#ifndef GRAFICS_H
#define GRAFICS_H
#include <string>

namespace Mayhem {

// class Graphics, that lauch and control the game
class Graphics {

  public:
    Graphics() = default;

    // initializes the main components of the game
    void launch_game(std::string mode, std::string port, std::string player);

    ~Graphics() = default;
}; // class Grafics

} // namespace Mayhem

#endif

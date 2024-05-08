#ifndef GRAFICS_H
#define GRAFICS_H

namespace Mayhem {

// class Graphics, that lauch and control the game
class Graphics {

  public:
    Graphics() = default;

    // initializes the main components of the game
    void launch_game(bool isOffline);

    ~Graphics() = default;
}; // class Grafics

} // namespace Mayhem

#endif

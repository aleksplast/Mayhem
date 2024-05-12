#include "graphics/graphics.hpp"

using namespace Mayhem;

int main(int argc, char* argv[]) { // FIXME: Add some checks
    Graphics graphics;
    graphics.launch_game(argv[1], argv[2], argv[3]);
    return 0;
}

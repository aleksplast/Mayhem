#include "graphics/graphics.hpp"

using namespace Mayhem;

int main(int argc, char* argv[]) {
    Graphics graphics;
    graphics.launch_game(argv[1]);
    return 0;
}

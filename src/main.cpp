#include "graphics/graphics.hpp"

using namespace Mayhem;

int main(int argc, char* argv[]) { // FIXME: Add some checks
    if (argc != 3) return 0;
    Graphics graphics;
    graphics.run(argv[1], argv[2]);
    return 0;
}

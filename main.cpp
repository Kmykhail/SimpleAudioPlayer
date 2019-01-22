#include <iostream>
#include "MultimediaObj.hpp"

int main() {
    std::cout << "You can use mouse or key like:"
                 "\n`s`-play"
                 "\n`space`-stop"
                 "\n`p`-pause"
                 "\n`d`-next song"
                 "\n`a`-previous song" << std::endl;
    MultimediaObj mptr;
    mptr.Init();
    return 0;
}
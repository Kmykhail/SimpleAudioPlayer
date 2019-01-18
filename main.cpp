#include <iostream>
#include "MultimediaObj.hpp"

int main() {
    MultimediaObj *mptr = MultimediaObj::getInstance();
    mptr->Init();
    return 0;
}
cmake_minimum_required(VERSION 3.12)
project(audio)

set(CMAKE_CXX_STANDARD 11)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIBRARY})

add_executable(untitled main.cpp sdl_header.h MultimediaObj.cpp MultimediaObj.hpp Gui.cpp Gui.hpp AudioData.cpp Player.cpp Player.hpp)
target_link_libraries(untitled -lSDL2 -lSDL2_image -lSDL2_ttf )
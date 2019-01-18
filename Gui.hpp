//
// Created by kmykhailenko on 10.01.19.
//

#pragma once
#include "sdl_header.h"
#include <vector>

class Gui {
public:
    static Gui * getInstance();
    void InitGui();
    void DrawGui();
    char CatchEvent(char currKey);
    void RenderGui();
    void CleanWindow();
private:
    static Gui *_inst;
    static SDL_Renderer * renderer;
    static SDL_Window *_window;
    SDL_Event   _event;
    std::vector<SDL_Texture*> _textureButton;
    SDL_Rect    _bcR;//rectangle of Button
    std::string _dirPicture;
    std::pair<int, int> _mouseClick;
    Gui();
    int    MouseEvent();
    ~Gui();
    Gui(const Gui&) = delete;
    Gui(Gui&&) = delete;
    Gui &operator=(const Gui &) = delete;
    Gui &operator=(Gui&&) = delete;
};


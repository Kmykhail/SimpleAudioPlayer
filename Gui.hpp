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
    void DrawGui(std::string);
    char CatchEvent(char currKey);
    void RenderGui();
    void CleanWindow();
private:
    static Gui *_inst;
    static SDL_Renderer * renderer;
    static SDL_Window *_window;
    static TTF_Font *_font;
    static SDL_Texture *_text;
    SDL_Color   _textColor;
    SDL_Event   _event;
    std::vector<SDL_Texture*> _textureButton;
    SDL_Rect    _bcR;//struct position of Button
    SDL_Rect    _tcR;//struct position of Text
    std::string _dirPrj;
    Gui();
    ~Gui();
    void    drawNameSong(std::string & songName);
    Gui(const Gui&) = delete;
    Gui(Gui&&) = delete;
    Gui &operator=(const Gui &) = delete;
    Gui &operator=(Gui&&) = delete;
};


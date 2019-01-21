//
// Created by kmykhailenko on 10.01.19.
//

#include "Gui.hpp"
#include "sdl_header.h"
#include <unistd.h>
#define STOP_BUTTON(x) (x >= 0 && x <= 100) ? true : false
#define PLAY_BUTTON(x) (x >= 100 && x <= 200) ? true : false
#define PREVIOUS_BUTTON(x) (x >= 200 && x <= 300) ? true : false
#define NEXT_BUTTON(x) (x >= 300 && x <= 400) ? true : false

const char g_play_path[] = "/Picture/play.png";
const char g_stop_path[] = "/Picture/stop.png";
const char g_next_path[] = "/Picture/next_1.png";
const char g_previous_path[] = "/Picture/previos.png";
const char g_font[] = "/Fonts/AbyssinicaSIL-R.ttf";
const int g_weight = 400;
const int g_height = 400;

Gui* Gui::_inst = nullptr;
SDL_Renderer* Gui::renderer = nullptr;
SDL_Window*     Gui::_window = nullptr;
TTF_Font* Gui::_font = nullptr;
SDL_Texture*    Gui::_text = nullptr;

Gui* Gui::getInstance() {
    if (!_inst){
        _inst = new Gui;
    }
    return _inst;
}

Gui::Gui() {}
Gui::~Gui() {}

void Gui::InitGui() {
    /****************INIT SDL**********************/
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << SDL_GetError() << std::endl;
        exit(-1);
    }
    /****************INIT TTF_SDL**********************/
    if (TTF_Init() < 0){
        std::cout << TTF_GetError() << std::endl;
        exit(-1);
    }
    /****************INIT WINDOW**********************/
    _window = SDL_CreateWindow(
            "Multimedia",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            g_weight,//weight
            g_height,//height
            SDL_WINDOW_SHOWN
    );
    if (!_window){
        std::cout << "Error Window: " << &SDL_Error << std::endl;
        exit(-1);
    }
    renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Trouble wih render" << std::endl;
        return;
    }
    SDL_SetRenderDrawColor(renderer, 100, 100, 122, 255);
    char path[4096];
    _dirPrj = getwd(path);
    size_t  n = _dirPrj.rfind('/');
    _dirPrj.resize(n);
    /************INIT FONT FOR TEXT************/
    _font = TTF_OpenFont((_dirPrj + g_font).c_str(), 20);
    if (!_font){
        std::cout << TTF_GetError() << std::endl;
        exit(1);
    }
    /************INIT TEXTURE FOR PLA"/Fonts/AbyssinicaSIL-R.ttf"YER************/
    _textureButton.resize(4);
    _textureButton[0] = SDL_CreateTextureFromSurface(renderer, IMG_Load((_dirPrj + g_stop_path).c_str()));//Stop
    _textureButton[1] = SDL_CreateTextureFromSurface(renderer, IMG_Load((_dirPrj + g_play_path).c_str()));//Play
    _textureButton[2] = SDL_CreateTextureFromSurface(renderer, IMG_Load((_dirPrj + g_previous_path).c_str()));//Previous
    _textureButton[3] = SDL_CreateTextureFromSurface(renderer, IMG_Load((_dirPrj + g_next_path).c_str()));//Next
    /*************INIT TEXT******************/
    _textColor = {255, 255, 255, 0};
}

void Gui::drawNameSong(std::string & songName) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(_font, songName.c_str(), _textColor);
    _text = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!_text){
        std::cerr << SDL_GetError() << std::endl;
        exit(-1);
    }
    _tcR = {100, 100, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, _text, nullptr, &_tcR);
    SDL_FreeSurface(textSurface);
}

void Gui::DrawGui(std::string songName) {
    SDL_RenderClear(renderer);
    drawNameSong(songName);
    _bcR.w = _bcR.h = 100;
    _bcR.y = 300;
    for (int i = 0; i < _textureButton.size(); ++i) {
        if (i == 0 || i == 1){
            _bcR.x = (!i) ? 0 : 100;
        }
        else if (i == 2 || i == 3){
            _bcR.x = (i == 2) ? 200 : 300;
        }
        SDL_RenderCopy(renderer, _textureButton[i], nullptr, &_bcR);
    }
}
void Gui::RenderGui() {SDL_RenderPresent(renderer);}

char Gui::CatchEvent(char currKey) {
    char key = currKey;
    while(SDL_PollEvent(&_event)){
        if (_event.type == SDL_QUIT){
            std::cout << "EXIT" << std::endl;
            return 'q';
        }
        int x = 0;
        int y = 0;
        if (_event.type == SDL_KEYDOWN){
            switch (_event.key.keysym.sym){
                case SDLK_ESCAPE:
                    std::cout << "EXIT" << std::endl;
                    return 'q';
                case SDLK_s:
                    std::cout << "play" << std::endl;
                    return 's';
                case SDLK_p:
                    std::cout << "pause" << std::endl;
                    return 'p';
                case SDLK_a:
                    std::cout << "previous song" << std::endl;
                    return 'a';
                case SDLK_d:
                    std::cout << "!!next song" << std::endl;
                    return 'd';
                case SDLK_SPACE:
                    std::cout << "Stop song" << std::endl;
                    return ' ';
                default:
                    return (currKey == 'p') ? currKey : 's';
            }
        }
        if (_event.type == SDL_MOUSEMOTION) {
            x = _event.motion.x;
            y = _event.motion.y;
        }
        if (_event.type == SDL_MOUSEBUTTONDOWN) {
            //If the left mouse button is let go...
            if (_event.button.button == SDL_BUTTON_LEFT) {
                //get the mouse offsets
                x = _event.button.x;
                y = _event.button.y;
                if (y >= 300) {
                    if (STOP_BUTTON(x)) {
                        return ' ';
                    }
                    if (PLAY_BUTTON(x)) {
                        std::cout << "MOUSE PLAY" << std::endl;
                        return (key == 's') ? 'p' : 's';
                    }
                    if (PREVIOUS_BUTTON(x)) {
                        std::cout << "MOUSE PREVIOUS" << std::endl;
                        return 'a';
                    }
                    if (NEXT_BUTTON(x)) {
                        std::cout << "MOUSE NEX" << std::endl;
                        return 'd';
                    }
                }
            }
        }
    }
    if (currKey == 'p' || currKey == ' '){
        key = currKey;
    }
    return key;
}

void Gui::CleanWindow() {
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
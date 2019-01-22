//
// Created by kmykhailenko on 10.01.19.
//

#include <dirent.h>
#include <unistd.h>
#include "MultimediaObj.hpp"
#include <iterator>

MultimediaObj::MultimediaObj() {}
MultimediaObj::~MultimediaObj() {}


void MultimediaObj::OpenSoundDir() {
    _pathDir = get_current_dir_name();
    size_t n = _pathDir.rfind('/');
    _pathDir.resize(n);
    _pathDir += "/Sound/";
    DIR *dirp = opendir(_pathDir.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != nullptr) {
        char*  buff = strstr(dp->d_name, ".wav");
        if (buff){
            std::string qw = _pathDir + dp->d_name;
            _playList.push_back(new AudioData(qw));
        }
    }
    closedir(dirp);;
}

void MultimediaObj::Init() {
    OpenSoundDir();
    _guiPtr = Gui::getInstance();
    _guiPtr->InitGui();
    _guiPtr->DrawGui(_playList.front()->GetSongName());
    _guiPtr->RenderGui();
    _media.InitPlayer();
    MainLoop();
}


void MultimediaObj::MainLoop() {
    int i = 0;
    int const FPS = 60;
    uint32_t  frameStart;
    int frameTime;
    int const frameDealy = 3000 / FPS;
    for(auto it = _playList.begin(); it != _playList.end(); ){
        if (!HandlEvent()){
            break;
        }
        if (_media.GetKey() == 'a'){
            i = (it != _playList.begin()) ? -1 : (_playList.size() - 1);
        }
        if (!_media.isRuning() && !_media.GetStop()){
            std::advance(it, i);
            if (it == _playList.end()) {
                it = _playList.begin();
            }
            i = 1;
        }
        frameStart = SDL_GetTicks();
        _guiPtr->DrawGui((*it)->GetSongName());
        Render();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDealy > frameTime){
            SDL_Delay(frameDealy - frameTime);
        }
        _media.Play(*it);
    }
    Clean();
}

int MultimediaObj::HandlEvent() {
    char sym = _guiPtr->CatchEvent(_media.GetKey());
    if (sym == 'q')
        return 0;
    if (sym == 's' || sym == 'p' || sym == 'd'//s - play, p  pause, a - previous, d - next
    || sym == 'a' || sym == ' ') {
        _media.SetKey(sym);
    }
    return 1;
}

void MultimediaObj::Render() {
    _guiPtr->RenderGui();
}

void MultimediaObj::Clean() {
    _guiPtr->CleanWindow();
    for(auto it : _playList){
        delete(it);
    }
}

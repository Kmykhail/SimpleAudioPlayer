//
// Created by kmykhailenko on 10.01.19.
//

#include <dirent.h>
#include <unistd.h>
#include "MultimediaObj.hpp"
#include <iterator>

MultimediaObj * MultimediaObj::_inst = nullptr;

MultimediaObj::MultimediaObj() {}
MultimediaObj::~MultimediaObj() {}

MultimediaObj* MultimediaObj::getInstance() {
    if (!_inst){
        _inst = new MultimediaObj;
    }
    return _inst;
}

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
    for(auto it = _playList.begin(); it != _playList.end(); ){
        if (!HandlEvent()){
            break;
        }
        if (_media.GetKey() == 'a'){
            i = (it !=  _playList.begin()) ? -1 : 0;
        }
        if (!_media.isRuning() && !_media.GetStop()){
            std::cout << "Key: " << _media.GetKey() << " I: " << i  << std::endl;
            std::advance(it, i);
            if (it == _playList.end())
                break;
            i = 1;
        }
        _guiPtr->DrawGui((*it)->GetSongName());
        _guiPtr->RenderGui();
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
    //TODO delete audiodata from container _playList
//    for (auto it = _playList.begin(); it != _playList.end() ; it++) {
//        _playList.erase(it);
//    }
}



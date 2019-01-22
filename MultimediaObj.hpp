//
// Created by kmykhailenko on 10.01.19.
//
#pragma once
#include <list>
#include "Gui.hpp"
#include "AudioData.hpp"
#include "Player.hpp"
#include <string>

class MultimediaObj {
public:
    MultimediaObj();
    ~MultimediaObj();
    void Init();
    int HandlEvent();
    void Update();
    void Render();
private:
    static MultimediaObj *_inst;
    Gui *_guiPtr;
    Player _media;
    std::string _pathDir;
    std::list<AudioData*> _playList;
    void    Clean();
    void MainLoop();
    void OpenSoundDir();
    MultimediaObj(const MultimediaObj&) = delete;
    MultimediaObj(MultimediaObj&&) = delete;
    MultimediaObj & operator=(const MultimediaObj&) = delete;
    MultimediaObj & operator=(MultimediaObj&&) = delete;
};

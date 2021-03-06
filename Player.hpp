//
// Created by kmykhailenko on 10.01.19.
//

#pragma once

#include "sdl_header.h"
#include "AudioData.hpp"
#include <list>

class Player {
public:
    Player() noexcept;
    Player(const Player&) = delete;
    Player(const Player&&) = delete;
    Player &operator=(const Player&) = delete;
    Player &operator=(const Player&&) = delete;
    ~Player();
    void    InitPlayer();
    void    Play(AudioData* track);
    bool isRuning();
    void SetKey(char sym);
    char GetKey() const;
    bool GetStop() const;

    SDL_AudioDeviceID getDevice() const{ return _device;}
private:
    void PlaySound(AudioData*, uint32_t &pl);
    void PauseSound();
    bool isPaused();
    void StopSound();
    SDL_AudioDeviceID _device;
    bool _run;
    int  _flag;
    char _key;
    bool _stop;
    uint32_t _buffTrack;
    uint32_t _lengthTrack;
};

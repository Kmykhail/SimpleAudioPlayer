//
// Created by kmykhailenko on 10.01.19.
//

#include "Player.hpp"

Player::Player() noexcept : _run(false), _flag(0), _key(0), _stop(false), _lengthTrack(0), _buffTrack(0){}
Player::~Player() {}

void Player::InitPlayer() {
    _key = ' ';
    SDL_AudioSpec spec;
    SDL_zero(spec);
    spec.freq = 44100;
    spec.format = AUDIO_S16SYS;
    spec.channels = 2;
    spec.samples = 2048;
    spec.userdata = this;
    _flag = 0;
    _device = SDL_OpenAudioDevice(nullptr, 0, &spec, nullptr, 0);
    if (_device == 0){
        std::cerr << SDL_GetError() << std::endl;
        exit(1);
    }
    SDL_PauseAudioDevice(_device, _flag);
}
void Player::Play(AudioData *track) {
    if (_key == 's'){//Play song
        if (!_lengthTrack && _run){
            _run = false;
        }
        else if (!_lengthTrack && !_run){
            if (_buffTrack){
                track->SetWavLength(_buffTrack);
                _buffTrack = 0;
            }
            PlaySound(track, _lengthTrack);
            _run = true;
            _stop = false;
        }
        else if (_lengthTrack && _run && _flag == 1){//Case for pause
            PlaySound(track, _lengthTrack);
        }
    }
    else if (_key == 'p' && !_flag && !_stop){//Pause song
        if (_lengthTrack){
            _flag = 1;
            PauseSound(track);
            _buffTrack = track->GetWavLength();
            track->SetWavLength(0);
        }
    }
    else if (_key == ' '){//Stop song
        if (_flag == 1){
            track->SetWavLength(_buffTrack);
            PlaySound(track, _lengthTrack);
        }
        if(_lengthTrack) {
            StopSound();
        }
        _stop = true;
        _run = false;
    }
    else if (_key == 'd'){//Next song
        if (_flag == 1){
            PlaySound(track, _lengthTrack);
        }
        StopSound();
        _run = false;
        _key = 's';
    }
    else if (_key == 'a'){//Previous song
        if (_flag == 1){
            PlaySound(track, _lengthTrack);
        }
        StopSound();
        _run = false;
        _key = 's';
    }
    _lengthTrack = SDL_GetQueuedAudioSize(_device);
}

void Player::PlaySound(AudioData* track, uint32_t &pl) {
    SDL_LockAudioDevice(_device);
    if (_flag == 1){
        _flag = 0;
        SDL_PauseAudioDevice(_device, _flag);
    }else {
        if ((SDL_QueueAudio(_device, track->GetWavStart(), track->GetWavLength())) < 0){
            std::cout << SDL_GetError() << std::endl;
        }
    }
    pl = SDL_GetQueuedAudioSize(_device);
    SDL_UnlockAudioDevice(_device);
}

void Player::PauseSound(AudioData* track) {
    SDL_LockAudioDevice(_device);
    SDL_PauseAudioDevice(_device, _flag);
    SDL_UnlockAudioDevice(_device);
}

void Player::StopSound() {
    SDL_LockAudioDevice(_device);
    SDL_ClearQueuedAudio(_device);
    SDL_UnlockAudioDevice(_device);
}

bool Player::isPaused() { return static_cast<bool>(_flag);}
bool Player::isRuning() { return _run;}
void Player::SetKey(char sym) {
    _key = sym;
}
char Player::GetKey() const { return _key;}
bool Player::GetStop() const { return _stop;}
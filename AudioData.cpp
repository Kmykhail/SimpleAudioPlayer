//
// Created by kmykhailenko on 10.01.19.
//

#include "AudioData.hpp"
#include "sdl_header.h"
#include <regex>

AudioData::AudioData() noexcept{}

AudioData::AudioData(std::string &fileName) {
    SDL_AudioSpec wavSpec;
    Uint8* wavStart;
    Uint32 wavLength;
    if(SDL_LoadWAV(fileName.c_str(), &wavSpec, &wavStart, &wavLength) == nullptr)
    {
        std::cerr << SDL_GetError() << std::endl;
        exit(1);
    }
    _start = wavStart;
    _length = wavLength;
    _songName = fileName.substr(fileName.rfind('/') + 1);
    _songName = std::regex_replace(_songName, std::regex("[.]wav"), "");
}

AudioData::~AudioData() {
    std::cout << "FReee" << std::endl;
    SDL_FreeWAV(_start);
}

uint8_t* AudioData::GetWavStart() const { return _start;}
uint32_t AudioData::GetWavLength() const { return _length;}
void AudioData::SetWavLength(uint32_t val) {_length = val;}
std::string AudioData::GetSongName() const { return _songName;}
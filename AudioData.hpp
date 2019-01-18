//
// Created by kmykhailenko on 10.01.19.
//
#pragma once
#include <string>

class AudioData {
public:
    AudioData() noexcept;
    AudioData(std::string & fileName);
    ~AudioData();

    uint8_t * GetWavStart() const;
    uint32_t  GetWavLength() const;
    void  SetWavLength(uint32_t val);
private:
    uint8_t *_start;
    uint32_t _length;
};


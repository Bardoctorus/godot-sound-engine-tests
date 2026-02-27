#include "CppWavetableOscillator.h"

void CppWavetableOscillator::_bind_methods(){
}

CppWavetableOscillator::CppWavetableOscillator(Array _waveTable, float _sampleRate, float _frequency){
    waveTable = _waveTable;
    sampleRate = _sampleRate;
    setFrequency(_frequency);
    isPlaying = false;
}

float CppWavetableOscillator::getSample(){
    if (isPlaying == true){
        index = fmodf(index, (float)waveTable.size());
        float sample = interpolateLiniarly();
        index += increment;
        return sample;
    }
    else{
        return 0.0f;
    }
}

void CppWavetableOscillator::setFrequency(float _frequency){
    frequency = _frequency;
    increment = frequency * ((float)waveTable.size() /sampleRate);
}

void CppWavetableOscillator::start(){
    setFrequency(frequency);
    isPlaying = true;
}

void CppWavetableOscillator::update(float _frequency){
    setFrequency(frequency);  
}

void CppWavetableOscillator::stop(){
    isPlaying = false;
	index = 0.0f;
	increment = 0.0f;
}

float CppWavetableOscillator::interpolateLiniarly(){
    int truncatedIndex = floor(index);
    int nextIndex = ceil((int)index % waveTable.size());
    float nextIndexWeight = index - (float)truncatedIndex;
    return waveTable[nextIndex] * nextIndexWeight + (1 - nextIndexWeight) * waveTable[truncatedIndex];
}

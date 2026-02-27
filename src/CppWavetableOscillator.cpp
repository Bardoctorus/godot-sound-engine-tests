#include "CppWavetableOscillator.h"

void CppWavetableOscillator::_bind_methods(){
    godot::ClassDB::bind_method(D_METHOD("getSample"), &CppWavetableOscillator::getSample);
    godot::ClassDB::bind_method(D_METHOD("_init", "_waveTable", "_sampleRate","_frequency"), &CppWavetableOscillator::_init);
    godot::ClassDB::bind_method(D_METHOD("start"), &CppWavetableOscillator::start);
    godot::ClassDB::bind_method(D_METHOD("update", "_frequency"), &CppWavetableOscillator::update);
    godot::ClassDB::bind_method(D_METHOD("currentlyPlaying"), &CppWavetableOscillator::currentlyPlaying);
    godot::ClassDB::bind_method(D_METHOD("stop"), &CppWavetableOscillator::stop);
    godot::ClassDB::bind_method(D_METHOD("interpolateLiniarly"), &CppWavetableOscillator::interpolateLiniarly);

    godot::ClassDB::bind_method(D_METHOD("getFrequency"), &CppWavetableOscillator::getFrequency);
    godot::ClassDB::bind_method(D_METHOD("setFrequency", "_frequency"), &CppWavetableOscillator::setFrequency);
   
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "frequency"),"setFrequency", "getFrequency");
}

CppWavetableOscillator::CppWavetableOscillator()
{};

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

void CppWavetableOscillator::_init(Array _waveTable, float _sampleRate, float _frequency){
    waveTable = _waveTable;
    sampleRate = _sampleRate;
    setFrequency(_frequency);
    isPlaying = false;
}

void CppWavetableOscillator::setFrequency(float _frequency){
    frequency = _frequency;
    increment = frequency * ((float)waveTable.size() /sampleRate);
}

float CppWavetableOscillator::getFrequency() const{
    return frequency;
}

void CppWavetableOscillator::start(){
    setFrequency(frequency);
    isPlaying = true;
}

void CppWavetableOscillator::update(float _frequency){
    setFrequency(frequency);  
}

bool CppWavetableOscillator::currentlyPlaying(){
    return isPlaying;
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
    float nextWave = waveTable[nextIndex];
    float trucWave = waveTable[truncatedIndex];
    return nextWave * nextIndexWeight + (1 - nextIndexWeight) * trucWave;
}

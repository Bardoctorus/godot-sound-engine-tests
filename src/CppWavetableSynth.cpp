
#include "CppWavetableSynth.h"
#include "godot_cpp/core/math.hpp"




 void CppWavetableSynth::_bind_methods(){
    godot::ClassDB::bind_method(D_METHOD("initOscillator", "_sampleRate", "_startingFreq"), &CppWavetableSynth::initOscillator);
    godot::ClassDB::bind_method(D_METHOD("handleInput", "message"), &CppWavetableSynth::handleInput);
    godot::ClassDB::bind_method(D_METHOD("updateFreqency", "_frequency"), &CppWavetableSynth::updateFreqency);
    godot::ClassDB::bind_method(D_METHOD("prepareToPlay", "_sampleRate", "_startingFreq"), &CppWavetableSynth::prepareToPlay);
    godot::ClassDB::bind_method(D_METHOD("render", "playback"), &CppWavetableSynth::render);




 }


CppWavetableSynth::CppWavetableSynth(){};

void CppWavetableSynth::initOscillator(float _sampleRate, float _startingFreq){
    Array sineWaveTable;
    for(int i = 0; i < WAVETABLE_LENGTH; ++i){
        sineWaveTable.append(sinf(Math_TAU * ((float)i / WAVETABLE_LENGTH)));
    }
    oscillator._init(sineWaveTable, _sampleRate, _startingFreq);
}
void CppWavetableSynth::handleInput(bool message){
    if (message == true){
        oscillator.start();
    }
    else{
        oscillator.stop();
    }
}
void CppWavetableSynth::updateFreqency(float _frequency){
    oscillator.update(_frequency);
}
void CppWavetableSynth::prepareToPlay(float _samplerate, float _startingFreq){
    initOscillator(_samplerate, _startingFreq);
}
void CppWavetableSynth::render(AudioStreamGeneratorPlayback playback){
    if (oscillator.currentlyPlaying()){
        for (int i = 0; i < playback.get_frames_available(); ++i){
            float sample = oscillator.getSample();
            playback.push_frame(Vector2(sample, sample));
        }
    }
}


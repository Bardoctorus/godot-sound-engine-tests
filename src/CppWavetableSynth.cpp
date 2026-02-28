
#include "CppWavetableSynth.h"
#include "godot_cpp/core/math.hpp"
#include "godot_cpp/classes/audio_stream_generator_playback.hpp"




 void CppWavetableSynth::_bind_methods(){
    godot::ClassDB::bind_method(D_METHOD("initOscillator", "_sampleRate", "_startingFreq"), &CppWavetableSynth::initOscillator);
    godot::ClassDB::bind_method(D_METHOD("handleInput", "message"), &CppWavetableSynth::handleInput);
    godot::ClassDB::bind_method(D_METHOD("updateFrequency", "_frequency"), &CppWavetableSynth::updateFrequency);
    godot::ClassDB::bind_method(D_METHOD("prepareToPlay", "_sampleRate", "_startingFreq"), &CppWavetableSynth::prepareToPlay);
    godot::ClassDB::bind_method(D_METHOD("render", "playback"), &CppWavetableSynth::render);




 }


CppWavetableSynth::CppWavetableSynth(){
    oscillator.instantiate();
    print_line("constructor");
};

void CppWavetableSynth::initOscillator(float _sampleRate, float _startingFreq){
    Array sineWaveTable;
    for(int i = 0; i < WAVETABLE_LENGTH; ++i){
        sineWaveTable.append(sinf(Math_TAU * ((float)i / WAVETABLE_LENGTH)));
    }
    oscillator->_init(sineWaveTable, _sampleRate, _startingFreq);
}
void CppWavetableSynth::handleInput(bool message){
    if (message == true){
        oscillator->start();
    }
    else{
        oscillator->stop();
    }
}
void CppWavetableSynth::updateFrequency(float _frequency){
    print_line("update freq: %s", _frequency);
    oscillator->update(_frequency);
}
void CppWavetableSynth::prepareToPlay(float _samplerate, float _startingFreq){
    initOscillator(_samplerate, _startingFreq);
        print_line("prep to play");

}
void CppWavetableSynth::render(Ref<AudioStreamGeneratorPlayback> playback){
    if (oscillator->currentlyPlaying()){
        PackedVector2Array buffer;
        for (int i = 0; i < playback->get_frames_available(); ++i){
            float sample = oscillator->getSample();
           // playback->push_frame(Vector2(sample, sample)); // actually slower in c++ according to docs
           buffer.push_back(Vector2(sample, sample));
        }
        playback->push_buffer(buffer);
    }
}


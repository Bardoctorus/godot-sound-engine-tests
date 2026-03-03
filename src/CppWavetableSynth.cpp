
#include "CppWavetableSynth.h"
#include "godot_cpp/core/math.hpp"
#include "godot_cpp/classes/audio_stream_generator_playback.hpp"




 void CppWavetableSynth::_bind_methods(){
    godot::ClassDB::bind_method(D_METHOD("initOscillator", "_sampleRate", "_startingFreq"), &CppWavetableSynth::initOscillator);
    godot::ClassDB::bind_method(D_METHOD("handleInput", "message"), &CppWavetableSynth::handleInput);
    godot::ClassDB::bind_method(D_METHOD("updateFrequency", "_frequency"), &CppWavetableSynth::updateFrequency);
    godot::ClassDB::bind_method(D_METHOD("prepareToPlay", "_sampleRate", "_startingFreq"), &CppWavetableSynth::prepareToPlay);
    godot::ClassDB::bind_method(D_METHOD("render", "playback"), &CppWavetableSynth::render);
    godot::ClassDB::bind_method(D_METHOD("setWaveTableType" , "type"), &CppWavetableSynth::setWaveTableType);
    godot::ClassDB::bind_method(D_METHOD("getWaveTableType"), &CppWavetableSynth::getWaveTableType);
    godot::ClassDB::bind_method(D_METHOD("fillWaveTable", "int", "wavetype"), &CppWavetableSynth::fillWaveTable);


    ADD_PROPERTY(PropertyInfo(Variant::INT, "wtype", PROPERTY_HINT_ENUM, "sine,square,sawtooth,triangle"), "setWaveTableType",  "getWaveTableType");

    BIND_ENUM_CONSTANT(SINEWAVE);
    BIND_ENUM_CONSTANT(SQUAREWAVE);
    BIND_ENUM_CONSTANT(SAWTOOTHWAVE);
    BIND_ENUM_CONSTANT(TRIANGLEWAVE);

 }


CppWavetableSynth::CppWavetableSynth(){
    oscillator.instantiate();
    //WaveTableType waveTableType = WaveTableType::SAWTOOTHWAVE;
    setWaveTableType(WaveTableType::TRIANGLEWAVE);
    print_line("constructor");
};

void CppWavetableSynth::setWaveTableType(WaveTableType p_type){
    waveTableType = p_type;
}

WaveTableType CppWavetableSynth::getWaveTableType() const {
    return waveTableType;
}



float CppWavetableSynth::fillWaveTable (int i, WaveTableType waveTableType){
    float value;
    switch (waveTableType)
    {
    case SAWTOOTHWAVE:
        value = 2.0f * ((float)i / WAVETABLE_LENGTH) - 1.0f;
        break;
    case SQUAREWAVE:
        value = sinf(Math_TAU * ((float)i / WAVETABLE_LENGTH)) >= 0.0 ? 1.0:-1.0;;
        break;
    case SINEWAVE:
        value = sinf(Math_TAU * ((float)i / WAVETABLE_LENGTH));
        break;
    case TRIANGLEWAVE:
        value = 1 - fabs(((float)i / WAVETABLE_LENGTH)-0.5f) * 4;
        break;

    default:
        value = 0.0f;
        break;
    }

    return value;
}



void CppWavetableSynth::initOscillator(float _sampleRate, float _startingFreq, WaveTableType p_type){
    Array wavetable;
    
    for(int i = 0; i < WAVETABLE_LENGTH; ++i){
        wavetable.append(fillWaveTable(i, p_type));
    }
    oscillator->_init(wavetable, _sampleRate, _startingFreq);
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
void CppWavetableSynth::prepareToPlay(float _samplerate, float _startingFreq, WaveTableType initType){
    initOscillator(_samplerate, _startingFreq, initType);
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


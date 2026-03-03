#pragma once

#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/audio_stream_generator_playback.hpp"
#include "CppWavetableOscillator.h"

using namespace godot;

#define WAVETABLE_LENGTH 64

enum WaveTableType {
    SINEWAVE,
    SQUAREWAVE,
    SAWTOOTHWAVE,
    TRIANGLEWAVE,
};

VARIANT_ENUM_CAST(WaveTableType);

class CppWavetableSynth: public RefCounted {
    GDCLASS(CppWavetableSynth, RefCounted);

    protected:
        static void _bind_methods();

    public:
        CppWavetableSynth();
        ~CppWavetableSynth() = default;
        void initOscillator(float _sampleRate, float _startingFreq, WaveTableType initType);
        void handleInput(bool message);
        void updateFrequency(float _frequency);
        void prepareToPlay(float _samplerate, float _startingFreq, WaveTableType initType);
        void render(Ref<AudioStreamGeneratorPlayback> playback);
        void setWaveTableType(WaveTableType p_type);
        WaveTableType getWaveTableType() const;
        float fillWaveTable (int i, WaveTableType waveTableType);


    private:
        Ref<CppWavetableOscillator> oscillator;
        WaveTableType waveTableType = WaveTableType::SAWTOOTHWAVE;

};


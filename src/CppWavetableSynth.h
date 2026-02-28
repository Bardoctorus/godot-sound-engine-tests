#pragma once

#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/audio_stream_generator_playback.hpp"
#include "CppWavetableOscillator.h"

using namespace godot;

#define WAVETABLE_LENGTH 64

class CppWavetableSynth: public RefCounted {
    GDCLASS(CppWavetableSynth, RefCounted);

    protected:
        static void _bind_methods();

    public:
        CppWavetableSynth();
        ~CppWavetableSynth() = default;
        void initOscillator(float _sampleRate, float _startingFreq);
        void handleInput(bool message);
        void updateFreqency(float _frequency);
        void prepareToPlay(float _samplerate, float _startingFreq);
        void render(AudioStreamGeneratorPlayback* playback);

    private:
        CppWavetableOscillator oscillator;
};

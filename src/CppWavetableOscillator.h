#pragma once

#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/classes/ref_counted.hpp"


using namespace godot;

class CppWavetableOscillator : public RefCounted {
    GDCLASS(CppWavetableOscillator, RefCounted)

    protected:
        static void _bind_methods();

    public:
        CppWavetableOscillator();
        ~CppWavetableOscillator() = default;

        float getSample();
        void setFrequency(float _frequency);
        float getFrequency() const;
        void start();
        void stop();
        void update(float _frequency);
        float interpolateLiniarly();
        void _init(Array _waveTable, float _sampleRate, float _frequency);
        bool currentlyPlaying();

    private:
        Array waveTable;
        float sampleRate;
        float index;
        float increment;
        float frequency;
        bool isPlaying;


};
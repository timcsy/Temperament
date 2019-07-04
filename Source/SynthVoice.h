/*
  ==============================================================================

    SynthVoice.h
    Created: 1 Jul 2019 3:44:06pm
    Author:  timcsy

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Temperament.h"
#include <queue>

enum Timbre { SINEWAVE = 1, KARPLUS_STRONG = 2 };

class SynthVoice: public SynthesiserVoice {
public:
    SynthVoice(Temperament::Config& config);
    bool canPlaySound(SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void renderNextBlock (AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    void setTimbre(int kind) { timbre = kind; }
    void setDecay(int factor) { decay = factor; }
    
private:
    Temperament::Config& config;
    int timbre = SINEWAVE;
    double decay = 0.995;
    
    // For sine wave
    double currentAngle = 0.0, angleDelta = 0.0, level = 0.0, tailOff = 0.0;
    
    // For Karplus Strong
    const int tableSize = 44100;
    AudioSampleBuffer waveTable;
    float currentIndex = 0, tableDelta = 0;
    void createWavetable();
    void setFrequency (float frequency, float sampleRate);
    float getNextSample();
    std::queue<float> ringBuffer;
};

/*
  ==============================================================================

    SynthVoice.h
    Created: 1 Jul 2019 3:44:06pm
    Author:  timcsy

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class SynthVoice: public SynthesiserVoice {
public:
    bool canPlaySound(SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void renderNextBlock (AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    void setCenterNote(int note) { centerNote = note; }
    void setCenterFreq(int freq) { centerFreq = freq; }
    void setInterval(int interv) { interval = interv; }
    void setNoteNum(int num) { noteNum = num; }
    
private:
    double currentAngle = 0.0, angleDelta = 0.0, level = 0.0, tailOff = 0.0;
    double centerNote = 69, centerFreq = 440;
    double interval = 2, noteNum = 12;
};

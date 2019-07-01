/*
  ==============================================================================

    SynthVoice.cpp
    Created: 1 Jul 2019 3:44:06pm
    Author:  timcsy

  ==============================================================================
*/

#include "SynthVoice.h"
#include "SynthSound.h"

bool SynthVoice::canPlaySound(SynthesiserSound* sound) {
    return dynamic_cast<SynthSound*>(sound) != nullptr;
}

//===============================================================================

void SynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) {
    currentAngle = 0.0;
    level = velocity * 0.15;
    tailOff = 0.0;
    double noteFreq = centerFreq * pow(pow(interval, 1.0 / noteNum), midiNoteNumber - centerNote);
    auto cyclesPerSecond = noteFreq;
    auto cyclesPerSample = cyclesPerSecond / getSampleRate();
    angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
}

void SynthVoice::stopNote(float velocity, bool allowTailOff) {
    if (allowTailOff) {
        if (tailOff == 0.0) tailOff = 1.0;
    } else {
        clearCurrentNote();
        angleDelta = 0.0;
    }
}

//===============================================================================

void SynthVoice::pitchWheelMoved(int newPitchWheelValue) {
    
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) {
    
}

//===============================================================================

void SynthVoice::renderNextBlock(AudioBuffer< float > &outputBuffer, int startSample, int numSamples) {
    if (angleDelta != 0.0) {
        if (tailOff > 0.0) {
            while (--numSamples >= 0) {
                auto currentSample = (float) (std::sin(currentAngle) * level * tailOff);
                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample(i, startSample, currentSample);
                currentAngle += angleDelta;
                ++startSample;
                tailOff *= 0.99;
                if (tailOff <= 0.005) {
                    clearCurrentNote();
                    angleDelta = 0.0;
                    break;
                }
            }
        } else {
            while (--numSamples >= 0) {
                auto currentSample = (float) (std::sin(currentAngle) * level);
                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample(i, startSample, currentSample);
                currentAngle += angleDelta;
                ++startSample;
            }
        }
    }
}

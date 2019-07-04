/*
  ==============================================================================

    SynthVoice.cpp
    Created: 1 Jul 2019 3:44:06pm
    Author:  timcsy

  ==============================================================================
*/

#include "SynthVoice.h"
#include "SynthSound.h"

SynthVoice::SynthVoice(Temperament::Config& config) : config(config) {
    createWavetable();
}

bool SynthVoice::canPlaySound(SynthesiserSound* sound) {
    return dynamic_cast<SynthSound*>(sound) != nullptr;
}

//===============================================================================

void SynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) {
    if (timbre == SINEWAVE) {
        currentAngle = 0.0;
        level = velocity * 0.15;
        tailOff = 0.0;
        auto cyclesPerSecond = config.centerFreq * config.freq[midiNoteNumber];
        auto cyclesPerSample = cyclesPerSecond / getSampleRate();
        angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
    } else if (timbre == KARPLUS_STRONG) {
        auto frequency = config.centerFreq * config.freq[midiNoteNumber];
        auto sampleRate = getSampleRate();
        setFrequency(frequency, sampleRate);
    }
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
    if (timbre == SINEWAVE) {
        if (angleDelta != 0.0) {
            if (tailOff > 0.0) {
                while (--numSamples >= 0) {
                    auto currentSample = (float) (std::sin(currentAngle) * level * tailOff);
                    for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                        outputBuffer.addSample(i, startSample, currentSample);
                    currentAngle += angleDelta;
                    ++startSample;
                    tailOff *= decay;
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
    } else if (timbre == KARPLUS_STRONG) {
        while (--numSamples >= 0) {
            if (!ringBuffer.empty()) {
                auto currentSample = ringBuffer.front();
                ringBuffer.pop();
                for (auto i = 0; i < outputBuffer.getNumChannels(); ++i)
                    outputBuffer.addSample (i, startSample, currentSample * 0.25);
                auto avg = decay * 0.5 * (currentSample + ringBuffer.front());
                ringBuffer.push(avg);
                ++startSample;
            }
        }
    }
}

void SynthVoice::createWavetable() {
    waveTable.setSize(1, tableSize);
    auto* samples = waveTable.getWritePointer(0);
    for (auto i = 0; i < tableSize; ++i) {
        samples[i] = Random::getSystemRandom().nextFloat() - 0.5;
    }
}

void SynthVoice::setFrequency (float frequency, float sampleRate) {
    auto tableSizeOverSampleRate = tableSize / sampleRate;
    tableDelta = frequency * tableSizeOverSampleRate;
    currentIndex = 0;
    while (!ringBuffer.empty()) ringBuffer.pop();
    for (auto i = 0; i < sampleRate / frequency; i++) {
        ringBuffer.push(getNextSample());
    }
}

float SynthVoice::getNextSample() {
    auto tableSize = waveTable.getNumSamples();
    auto index0 = (unsigned int) currentIndex;
    auto index1 = index0 == (tableSize - 1) ? (unsigned int) 0 : index0 + 1;
    auto frac = currentIndex - (float) index0;
    auto* table = waveTable.getReadPointer(0);
    auto value0 = table[index0];
    auto value1 = table[index1];
    auto currentSample = value0 + frac * (value1 - value0);
    if ((currentIndex += tableDelta) > tableSize)
        currentIndex -= tableSize;
    return currentSample;
}

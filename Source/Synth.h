/*
  ==============================================================================

    Synth.h
    Created: 1 Jul 2019 4:39:31pm
    Author:  timcsy

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthVoice.h"
#include "SynthSound.h"

#define MAX_VOICES 16

class Synth: public Synthesiser {
public:
    Synth(Temperament::Config& config) : config(config) {
        // init synth
        for (int i = 0; i < MAX_VOICES; i++) {
            addVoice(new SynthVoice(config));
        }
        addSound(new SynthSound());
    }
    
    void setTimbre(int timbre) {
        for (int i = 0; i < voices.size(); i++) {
            dynamic_cast<SynthVoice*>(voices[i])->setTimbre(timbre);
        }
    }
    
    void setDecay(double decay) {
        for (int i = 0; i < voices.size(); i++) {
            dynamic_cast<SynthVoice*>(voices[i])->setDecay(decay);
        }
    }
    
private:
    Temperament::Config& config;
};

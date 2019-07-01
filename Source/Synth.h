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
    Synth() {
        // init synth
        for (int i = 0; i < MAX_VOICES; i++) {
            addVoice(new SynthVoice());
        }
        addSound(new SynthSound());
    }
    void setCenterNote(int note) {
        for (int i = 0; i < voices.size(); i++) {
            dynamic_cast<SynthVoice*>(voices[i])->setCenterNote(note);
        }
    }
    void setCenterFreq(int freq) {
        for (int i = 0; i < voices.size(); i++) {
             dynamic_cast<SynthVoice*>(voices[i])->setCenterFreq(freq);
        }
    }
    void setInterval(int interv) {
        for (int i = 0; i < voices.size(); i++) {
            dynamic_cast<SynthVoice*>(voices[i])->setInterval(interv);
        }
    }
    void setNoteNum(int num) {
        for (int i = 0; i < voices.size(); i++) {
             dynamic_cast<SynthVoice*>(voices[i])->setNoteNum(num);
        }
    }
};

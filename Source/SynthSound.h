/*
  ==============================================================================

    SynthSound.h
    Created: 1 Jul 2019 3:43:52pm
    Author:  timcsy

  ==============================================================================
*/

#pragma once

class SynthSound: public SynthesiserSound {
public:
    SynthSound() {}
    bool appliesToNote(int) override { return true; }
    bool appliesToChannel(int) override { return true; }
};

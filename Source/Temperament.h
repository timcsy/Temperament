/*
  ==============================================================================

    Temperament.h
    Created: 3 Jul 2019 1:02:32am
    Author:  timcsy

  ==============================================================================
*/

#pragma once
#include "CFrac.h"
#include "../JuceLibraryCode/JuceHeader.h"

namespace Temperament {
    
    enum TempMode { EQUAL_TEMP = 1, PYTHAGOREAN };
    
    class Config {
    public:
        Config();
        double centerFreq;
        int tempIndex[128];
        double freq[128];
    };
    
    CFrac::Q partition(double mainOvertune, double referenceOvertune, int precision);
    
    double equalTemp(double centerFreq, int centerNote, int note, double interval, double partition);
    
    double pythagorean(double centerFreq, int centerNote, int note, double interval, double partition, double unit);
    
    string noteToString(int note);
    
    void importConfig(Config& config);
    
    void exportConfig(const Config& config);
}

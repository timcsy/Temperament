/*
  ==============================================================================

    Temperament.cpp
    Created: 3 Jul 2019 3:00:16am
    Author:  timcsy

  ==============================================================================
*/

#include "Temperament.h"
#include <cmath>
#include <iostream>
#include <fstream>
using namespace CFrac;
using namespace Temperament;

Q Temperament::partition(double mainOvertune, double referenceOvertune, int precision) {
    double r = log(referenceOvertune) / log(mainOvertune);
    vector<long long int> v;
    real_to_conti(r, v, precision);
    return conti_to_rational(v);
}

double Temperament::equalTemp(double centerFreq, int centerNote, int note, double interval, double partition) {
    return centerFreq * pow(pow(interval, 1.0 / partition), note - centerNote);
}

double Temperament::pythagorean(double centerFreq, int centerNote, int note, double interval, double partition, double unit) {
    // generate scale table
    vector<double> scale;
    double freq = 1.0;
    for (int i = 0; i <= partition / 2; i++) {
        if (freq >= interval) freq /= interval;
        else if (freq < 1.0) freq *= interval;
        scale.push_back(freq);
        freq *= unit;
    }
    freq = (double)1.0 / unit;
    for (int i = 1; i < partition / 2; i++) {
        if (freq < 1.0) freq *= interval;
        else if (freq >= interval) freq /= interval;
        scale.push_back(freq);
        freq /= unit;
    }
    std::sort(scale.begin(), scale.end());
    
    // give the frequency of the note
    int diff = note - centerNote;
    freq = 1.0;
    bool modified = false;
    while (diff >= (int)scale.size()) {
        freq *= interval;
        diff -= (int)scale.size();
        if (diff < 0) modified = true;
    }
    if (modified) diff += (int)scale.size();
    modified = false;
    while (diff < 0) {
        freq /= interval;
        diff += (int)scale.size();
        if (diff >= (int)scale.size()) modified = true;
    }
    if (modified) diff -= (int)scale.size();
    freq *= scale[diff] * centerFreq;
    return freq;
}


string Temperament::noteToString(int note) {
    string noteName[] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
    return noteName[note%12] + to_string(note / 12 - 1);
}

void Temperament::importConfig(Config& config) {
    juce::FileChooser chooser("Select a Config File ...", {}, "*.tem");
    if (chooser.browseForFileToOpen()) {
        auto file = chooser.getResult();
        auto filepath = file.getFullPathName().getCharPointer();
        fstream fin(filepath, ios::in);
        fin >> config.centerFreq;
        int i, temp;
        double freq;
        while (fin >> i >> temp >> freq) {
            if (0 <= i && i < 128) {
                config.tempIndex[i] = temp;
                config.freq[i] = freq;
            }
        }
    }
}

void Temperament::exportConfig(const Config& config) {
    juce::FileChooser chooser("Create a Config File ...", {}, "*.tem");
    if (chooser.browseForFileToSave(true)) {
        auto file = chooser.getResult();
        auto filepath = file.getFullPathName().getCharPointer();
        fstream fout(filepath, ios::out);
        fout << config.centerFreq << endl;;
        for (int i = 0; i < 128; i++) {
            fout << i << " " << config.tempIndex[i] << " " << config.freq[i] << endl;;
        }
    }
}

Temperament::Config::Config() {
    centerFreq = 440; // A4
    int centerNote = 69; // A4
    double partition = 12;
    double interval = 2;
    
    for (int i = 0; i < 128; i++) {
        tempIndex[i] = i - centerNote;
        freq[i] = Temperament::equalTemp(1, 0, tempIndex[i], interval, partition);
    }
}

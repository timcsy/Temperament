/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TemperamentAudioProcessorEditor::TemperamentAudioProcessorEditor (TemperamentAudioProcessor& p, AudioProcessorValueTreeState& vts, Temperament::Config& config)
    : AudioProcessorEditor (&p), processor (p), valueTreeState (vts), config(config)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (630, 630);
    
    // Center Frequency
    addAndMakeVisible(centerFreqSlider);
    centerFreqAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "centerFreq", centerFreqSlider));
    centerFreqSlider.setTextValueSuffix(" Hz");
    config.centerFreq = centerFreqSlider.getValue();
    centerFreqSlider.onValueChange = [&] {
        config.centerFreq = centerFreqSlider.getValue();
        int note = midiNoteSlider.getValue();
        noteFreqSlider.setValue(config.freq[note] * config.centerFreq, dontSendNotification);
    };
    
    addAndMakeVisible(centerFreqLabel);
    centerFreqLabel.setText("Center Frequency", dontSendNotification);
    centerFreqLabel.attachToComponent(&centerFreqSlider, true);
    
    // MIDI Note
    addAndMakeVisible(midiNoteSlider);
    midiNoteSlider.setRange(0, 127, 1);
    midiNoteSlider.onValueChange = [&] {
        updateNote();
    };
    
    addAndMakeVisible(midiNoteLabel);
    midiNoteLabel.setText("MIDI Note", dontSendNotification);
    midiNoteLabel.attachToComponent(&midiNoteSlider, true);
    
    // Note Frequency
    addAndMakeVisible(noteFreqSlider);
    noteFreqSlider.setRange(0, 44000, 0.001);
    noteFreqSlider.setSkewFactor(0.2);
    noteFreqSlider.setTextValueSuffix(" Hz");
    noteFreqSlider.onValueChange = [&] {
        int note = midiNoteSlider.getValue();
        config.freq[note] = noteFreqSlider.getValue() / config.centerFreq;
    };
    
    addAndMakeVisible(noteFreqLabel);
    noteFreqLabel.setText("Note Frequency", dontSendNotification);
    noteFreqLabel.attachToComponent(&noteFreqSlider, true);
    
    // Temperament Scale
    addAndMakeVisible(indexScaleSlider);
    indexScaleSlider.setRange(-20, 20, 1);
    indexScaleSlider.onValueChange = [&] {
        updateIndex();
        calFreq();
    };
    
    addAndMakeVisible(indexScaleLabel);
    indexScaleLabel.setText("Temperament Scale", dontSendNotification);
    indexScaleLabel.attachToComponent(&indexScaleSlider, true);
    
    // Temperament Index
    addAndMakeVisible(tempIndexSlider);
    tempIndexSlider.setRange(0, 12, 1);
    tempIndexSlider.onValueChange = [&] {
        updateIndex();
        calFreq();
    };
    
    addAndMakeVisible(tempIndexLabel);
    tempIndexLabel.setText("Temperament Index", dontSendNotification);
    tempIndexLabel.attachToComponent(&tempIndexSlider, true);
    
    // Temperament Mode
    addAndMakeVisible(tempModeMenu);
    tempModeMenu.addItem("Equal Temperament", Temperament::EQUAL_TEMP);
    tempModeMenu.addItem("Pythagorean tuning", Temperament::PYTHAGOREAN);
    tempModeMenuAttachment.reset(new AudioProcessorValueTreeState::ComboBoxAttachment (valueTreeState, "tempMode", tempModeMenu));
    tempModeMenu.onChange = [&] {
        calFreq();
    };
    
    addAndMakeVisible(tempModeLabel);
    tempModeLabel.setText("Temperament Mode", dontSendNotification);
    tempModeLabel.attachToComponent(&tempModeMenu, true);
    
    // Center Note
    addAndMakeVisible(centerNoteSlider);
    centerNoteAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "centerNote", centerNoteSlider));
    centerNoteSlider.onValueChange = [&] {
        for (int i = 0; i < 128; i++) {
            config.tempIndex[i] = i - centerNoteSlider.getValue();
        }
        updateParams();
        calFreq();
    };
    
    addAndMakeVisible(centerNoteLabel);
    centerNoteLabel.setText("Center Note", dontSendNotification);
    centerNoteLabel.attachToComponent(&centerNoteSlider, true);
    
    // Partition
    addAndMakeVisible(partitionSlider);
    partitionAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "partition", partitionSlider));
    partitionSlider.onValueChange = [&] {
        calFreq();
    };
    
    addAndMakeVisible(partitionLabel);
    partitionLabel.setText("Partition", dontSendNotification);
    partitionLabel.attachToComponent(&partitionSlider, true);
    
    // Interval
    addAndMakeVisible(intervalSlider);
    intervalAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "interval", intervalSlider));
    intervalSlider.onValueChange = [&] {
        calFreq();
    };
    
    addAndMakeVisible(intervalLabel);
    intervalLabel.setText("Interval", dontSendNotification);
    intervalLabel.attachToComponent(&intervalSlider, true);
    
    // Scale Unit
    addAndMakeVisible(unitSlider);
    unitAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "unit", unitSlider));
    unitSlider.onValueChange = [&] {
        calFreq();
    };
    
    addAndMakeVisible(unitLabel);
    unitLabel.setText("Scale Unit", dontSendNotification);
    unitLabel.attachToComponent(&unitSlider, true);
    
    // Use Rational
    addAndMakeVisible(rationalButton);
    rationalAttachment.reset(new AudioProcessorValueTreeState::ButtonAttachment (valueTreeState, "rational", rationalButton));
    rationalButton.setButtonText("Use Rational");
    rationalButton.onClick = [&] {
        calFreq();
    };
    
    // Rational Error
    addAndMakeVisible(errorSlider);
    errorAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "error", errorSlider));
    errorSlider.onValueChange = [&] {
        calFreq();
    };
    
    addAndMakeVisible(errorLabel);
    errorLabel.setText("Rational Error", dontSendNotification);
    errorLabel.attachToComponent(&errorSlider, true);
    
    // Import Config
    addAndMakeVisible(importButton);
    importButton.setButtonText("Import Configuration");
    importButton.onClick = [&] {
        Temperament::importConfig(config);
        updateView();
    };
    
    // Export Config
    addAndMakeVisible(exportButton);
    exportButton.setButtonText("Export Configuration");
    exportButton.onClick = [&] {
        Temperament::exportConfig(config);
        updateView();
    };
    
    // Main Overtune
    addAndMakeVisible(mainOvertuneSlider);
    mainOvertuneAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "mainOvertune", mainOvertuneSlider));
    mainOvertuneSlider.onValueChange = [&] {
        updateParams();
        calFreq();
    };
    
    addAndMakeVisible(mainOvertuneLabel);
    mainOvertuneLabel.setText("Main Overtune", dontSendNotification);
    mainOvertuneLabel.attachToComponent(&mainOvertuneSlider, true);
    
    // Reference Overtune
    addAndMakeVisible(refOvertuneSlider);
    refOvertuneAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "refOvertune", refOvertuneSlider));
    refOvertuneSlider.onValueChange = [&] {
        updateParams();
        calFreq();
    };
    
    addAndMakeVisible(refOvertuneLabel);
    refOvertuneLabel.setText("Reference Overtune", dontSendNotification);
    refOvertuneLabel.attachToComponent(&refOvertuneSlider, true);
    
    // Precision
    addAndMakeVisible(precisionSlider);
    precisionAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "precision", precisionSlider));
    precisionSlider.onValueChange = [&] {
        updateParams();
        calFreq();
    };
    
    addAndMakeVisible(precisionLabel);
    precisionLabel.setText("Precision", dontSendNotification);
    precisionLabel.attachToComponent(&precisionSlider, true);
    
    // Infomation
    addAndMakeVisible(infoLabel);
    
    // Timbre
    addAndMakeVisible(timbreMenu);
    timbreMenu.addItem("Sine Wave", SINEWAVE);
    timbreMenu.addItem("Karplus Strong", KARPLUS_STRONG);
    timbreAttachment.reset(new AudioProcessorValueTreeState::ComboBoxAttachment (valueTreeState, "timbre", timbreMenu));
    timbreMenu.onChange = [&] {
        processor.synth.setTimbre(timbreMenu.getSelectedId());
    };
    
    addAndMakeVisible(timbreLabel);
    timbreLabel.setText("Timbre", dontSendNotification);
    timbreLabel.attachToComponent(&timbreMenu, true);
    
    // Decay Factor
    addAndMakeVisible(decaySlider);
    decayAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "decay", decaySlider));
    decaySlider.onValueChange = [&] {
        processor.synth.setDecay(decaySlider.getValue());
    };
    
    addAndMakeVisible(decayLabel);
    decayLabel.setText("Decay Factor", dontSendNotification);
    decayLabel.attachToComponent(&decaySlider, true);
    
    
    midiNoteSlider.setValue(centerNoteSlider.getValue(), dontSendNotification);
    updateView();
}

TemperamentAudioProcessorEditor::~TemperamentAudioProcessorEditor()
{
}

//==============================================================================
void TemperamentAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void TemperamentAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    int posX = 150, posY = 20;
    centerFreqSlider.setBounds(posX, posY, getWidth() - posX - 20, 20); posY += 30;
    midiNoteSlider.setBounds(posX, posY, getWidth() - posX - 20, 20); posY += 30;
    noteFreqSlider.setBounds(posX, posY, getWidth() - posX - 20, 20); posY += 30;
    indexScaleSlider.setBounds(posX, posY, getWidth() - posX - 20, 20); posY += 30;
    tempIndexSlider.setBounds(posX, posY, getWidth() - posX - 20, 20); posY += 30;
    tempModeMenu.setBounds(posX, posY, getWidth() / 2 - 20, 20); posY += 30;
    centerNoteSlider.setBounds(posX, posY, getWidth() - posX - 20, 20); posY += 30;
    partitionSlider.setBounds(posX, posY, getWidth() - posX - 20, 20); posY += 30;
    intervalSlider.setBounds(posX, posY, getWidth() - posX - 20, 20); posY += 30;
    unitSlider.setBounds(posX, posY, getWidth() - posX - 20, 20); posY += 30;
    rationalButton.setBounds(posX, posY, getWidth() - posX - 30, 30); posY += 40;
    errorSlider.setBounds(posX, posY, getWidth() - posX - 20, 20); posY += 30;
    importButton.setBounds(posX, posY, 200, 30);
    exportButton.setBounds(posX + 210, posY, 200, 30); posY += 40;
    mainOvertuneSlider.setBounds(posX, posY, getWidth() - posX - 20, 20); posY += 30;
    refOvertuneSlider.setBounds(posX, posY, getWidth() - posX - 20, 20); posY += 30;
    precisionSlider.setBounds(posX, posY, getWidth() - posX - 20, 20); posY += 30;
    infoLabel.setBounds(posX, posY, getWidth() - posX - 20, 20); posY += 30;
    timbreMenu.setBounds(posX, posY, getWidth() / 2 - 20, 20); posY += 30;
    decaySlider.setBounds(posX, posY, getWidth() - posX - 20, 20); posY += 30;
}

void TemperamentAudioProcessorEditor::updateNote() {
    int note = midiNoteSlider.getValue();
    midiNoteSlider.setTextValueSuffix(" (" + Temperament::noteToString(note) + ")");
    noteFreqSlider.setValue(config.freq[note] * config.centerFreq, dontSendNotification);
    int p = partitionSlider.getValue();
    int r = CFrac::mod(config.tempIndex[note], p);
    int q = (config.tempIndex[note] - r) / p;
    tempIndexSlider.setRange(0, p, 1);
    tempIndexSlider.setValue(r, dontSendNotification);
    indexScaleSlider.setValue(q, dontSendNotification);
}

void TemperamentAudioProcessorEditor::updateIndex() {
    int note = midiNoteSlider.getValue();
    int partition = partitionSlider.getValue();
    int scale = indexScaleSlider.getValue();
    int index = tempIndexSlider.getValue();
    config.tempIndex[note] = partition * scale + index;
}

void TemperamentAudioProcessorEditor::updateView() {
    centerFreqSlider.setValue(config.centerFreq, dontSendNotification);
    updateNote();
}

void TemperamentAudioProcessorEditor::updateParams() {
    // show the note name
    int centerNote = centerNoteSlider.getValue();
    centerNoteSlider.setTextValueSuffix(" (" + Temperament::noteToString(centerNote) + ")");

    // calculate good temperament
    double mainOvertune = mainOvertuneSlider.getValue();
    double refOvertune = refOvertuneSlider.getValue();
    int precision = precisionSlider.getValue();
    CFrac::Q cf = Temperament::partition(mainOvertune, refOvertune, precision);
    auto partition = cf.q;
    partitionSlider.setValue(partition, dontSendNotification);
    intervalSlider.setValue(mainOvertune, dontSendNotification);
    unitSlider.setValue(refOvertune / mainOvertune, dontSendNotification);

    // showing info
    int note = (int)cf.p - (int)cf.q;
    auto freq = Temperament::equalTemp(1, 0, note, mainOvertune, partition);
    double error = (freq - refOvertune / mainOvertune) * 100;
    infoLabel.setText(String("Fraction = ") + CFrac::to_rational_string(cf) + ", Harmonic Note = " + String(note) + ", error = " + String(error) + " %", dontSendNotification);
}

void TemperamentAudioProcessorEditor::calFreq() {
    int tempMode = tempModeMenu.getSelectedId();
    double partition = partitionSlider.getValue();
    double interval = intervalSlider.getValue();
    double unit = unitSlider.getValue();
    bool rational = rationalButton.getToggleState();
    double error = errorSlider.getValue();
    
    for (int i = 0; i < 128; i++) {
        double freq;
        switch (tempMode) {
            case Temperament::EQUAL_TEMP:
                freq = Temperament::equalTemp(1, 0, config.tempIndex[i], interval, partition);
                config.freq[i] = rational? CFrac::get_closest(freq, error): freq;
                break;
            case Temperament::PYTHAGOREAN:
                freq = Temperament::pythagorean(1, 0, config.tempIndex[i], interval, partition, unit);
                config.freq[i] = rational? CFrac::get_closest(freq, error): freq;
                break;
        }
    }
    
    updateNote();
}

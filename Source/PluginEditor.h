/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Temperament.h"

//==============================================================================
/**
*/
class TemperamentAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    TemperamentAudioProcessorEditor (TemperamentAudioProcessor& p, AudioProcessorValueTreeState&, Temperament::Config&);
    ~TemperamentAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TemperamentAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;
    Temperament::Config& config;
    void updateNote();
    void updateIndex();
    void updateParams();
    void updateView();
    void calFreq();
    
    Slider centerFreqSlider;
    Label centerFreqLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> centerFreqAttachment;
    Slider midiNoteSlider;
    Label midiNoteLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> midiNoteAttachment;
    Slider noteFreqSlider;
    Label noteFreqLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> noteFreqAttachment;
    Slider indexScaleSlider;
    Label indexScaleLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> indexScaleAttachment;
    Slider tempIndexSlider;
    Label tempIndexLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> tempIndexAttachment;
    
    
    ComboBox tempModeMenu;
    Label tempModeLabel;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> tempModeMenuAttachment;
    Slider centerNoteSlider;
    Label centerNoteLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> centerNoteAttachment;
    Slider partitionSlider;
    Label partitionLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> partitionAttachment;
    Slider intervalSlider;
    Label intervalLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> intervalAttachment;
    Slider unitSlider;
    Label unitLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> unitAttachment;
    
    ToggleButton rationalButton;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> rationalAttachment;
    Slider errorSlider;
    Label errorLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> errorAttachment;
    
    TextButton importButton;
    TextButton exportButton;
    
    Slider mainOvertuneSlider;
    Label mainOvertuneLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mainOvertuneAttachment;
    Slider refOvertuneSlider;
    Label refOvertuneLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> refOvertuneAttachment;
    Slider precisionSlider;
    Label precisionLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> precisionAttachment;
    
    Label infoLabel;
    
    ComboBox timbreMenu;
    Label timbreLabel;
    std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> timbreAttachment;
    
    Slider decaySlider;
    Label decayLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> decayAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TemperamentAudioProcessorEditor)
};

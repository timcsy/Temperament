/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TemperamentAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    TemperamentAudioProcessorEditor (TemperamentAudioProcessor& p, AudioProcessorValueTreeState&);
    ~TemperamentAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TemperamentAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;
    double overtuneSmall = 2, overtuneBig = 3, precision = 4;
    void updateIntervalNoteNum();
    
    Slider centerNoteSlider;
    Label centerNoteLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> centerNoteAttachment;
    Slider centerFreqSlider;
    Label centerFreqLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> centerFreqAttachment;
    Slider overtune1Slider;
    Label overtune1Label;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> overtune1Attachment;
    Slider overtune2Slider;
    Label overtune2Label;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> overtune2Attachment;
    Slider precisionSlider;
    Label precisionLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> precisionAttachment;
    Slider noteNumSlider;
    Label noteNumLabel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> noteNumAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TemperamentAudioProcessorEditor)
};

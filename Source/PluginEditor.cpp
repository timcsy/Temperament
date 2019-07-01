/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "CFrac.h"

#define NOTE_NUM_MAX 1000

//==============================================================================
TemperamentAudioProcessorEditor::TemperamentAudioProcessorEditor (TemperamentAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState (vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 210);
    
    addAndMakeVisible(centerNoteSlider);
    centerNoteAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "centerNote", centerNoteSlider));
    centerNoteSlider.onValueChange = [this] {
        processor.synth.setCenterNote(centerNoteSlider.getValue());
    };
    
    addAndMakeVisible(centerNoteLabel);
    centerNoteLabel.setText("Center Note", dontSendNotification);
    centerNoteLabel.attachToComponent(&centerNoteSlider, true);
    
    addAndMakeVisible(centerFreqSlider);
    centerFreqAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "centerFreq", centerFreqSlider));
    centerFreqSlider.setTextValueSuffix(" Hz");
    centerFreqSlider.onValueChange = [this] {
        processor.synth.setCenterFreq(centerFreqSlider.getValue());
    };
    
    addAndMakeVisible(centerFreqLabel);
    centerFreqLabel.setText("Center Frequency", dontSendNotification);
    centerFreqLabel.attachToComponent(&centerFreqSlider, true);
    
    addAndMakeVisible(overtune1Slider);
    overtune1Attachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "overtune1", overtune1Slider));
    overtune1Slider.onValueChange = [this] {
        updateIntervalNoteNum();
    };
    
    addAndMakeVisible(overtune1Label);
    overtune1Label.setText("Overtune 1", dontSendNotification);
    overtune1Label.attachToComponent(&overtune1Slider, true);
    
    addAndMakeVisible(overtune2Slider);
    overtune2Attachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "overtune2", overtune2Slider));
    overtune2Slider.onValueChange = [this] {
        updateIntervalNoteNum();
    };
    
    addAndMakeVisible(overtune2Label);
    overtune2Label.setText("Overtune 2", dontSendNotification);
    overtune2Label.attachToComponent(&overtune2Slider, true);
    
    addAndMakeVisible(precisionSlider);
    precisionAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "precision", precisionSlider));
    precisionSlider.onValueChange = [this] {
        updateIntervalNoteNum();
    };
    
    addAndMakeVisible(precisionLabel);
    precisionLabel.setText("Precision", dontSendNotification);
    precisionLabel.attachToComponent(&precisionSlider, true);
    
    addAndMakeVisible(noteNumSlider);
    noteNumAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "noteNum", noteNumSlider));
    noteNumSlider.onValueChange = [this] {
        processor.synth.setNoteNum(noteNumSlider.getValue());
    };
    
    addAndMakeVisible(noteNumLabel);
    noteNumLabel.setText("Temperament", dontSendNotification);
    noteNumLabel.attachToComponent(&noteNumSlider, true);
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
    int marginLeft = 140;
    centerNoteSlider.setBounds(marginLeft, 20, getWidth() - marginLeft - 20, 20);
    centerFreqSlider.setBounds(marginLeft, 50, getWidth() - marginLeft - 20, 20);
    overtune1Slider.setBounds(marginLeft, 80, getWidth() - marginLeft - 20, 20);
    overtune2Slider.setBounds(marginLeft, 110, getWidth() - marginLeft - 20, 20);
    precisionSlider.setBounds(marginLeft, 140, getWidth() - marginLeft - 20, 20);
    noteNumSlider.setBounds(marginLeft, 170, getWidth() - marginLeft - 20, 20);
}

void TemperamentAudioProcessorEditor::updateIntervalNoteNum()
{
    int overtune1 = overtune1Slider.getValue();
    int overtune2 = overtune2Slider.getValue();
    if (overtune1 > overtune2) { overtuneSmall = overtune2; overtuneBig = overtune1; }
    else { overtuneSmall = overtune1; overtuneBig = overtune2; }
    processor.synth.setInterval(overtuneSmall);
    precision = precisionSlider.getValue();
    int noteNum = CFrac::note_num(overtuneSmall, overtuneBig, precision, NOTE_NUM_MAX);
    noteNumSlider.setValue(noteNum, sendNotification);
}

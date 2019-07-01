/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthVoice.h"
#include "SynthSound.h"

#define MAX_VOICES 16

//==============================================================================
TemperamentAudioProcessor::TemperamentAudioProcessor() :
#ifndef JucePlugin_PreferredChannelConfigurations
     AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
    parameters(*this, nullptr, Identifier("Temperament"), {
        std::make_unique<AudioParameterFloat> ("centerNote", "Center Note", NormalisableRange<float>(0, 127, 1), 69),
        std::make_unique<AudioParameterFloat> ("centerFreq", "Center Frequency", NormalisableRange<float>(0, 22000, 0.01, 0.2), 440),
        std::make_unique<AudioParameterFloat> ("overtune1", "Overtune 1", NormalisableRange<float>(2, 128, 1, 0.3), 2),
        std::make_unique<AudioParameterFloat> ("overtune2", "Overtune 2", NormalisableRange<float>(2, 128, 1, 0.3), 3),
        std::make_unique<AudioParameterFloat> ("precision", "Precision", NormalisableRange<float>(1, 10, 1), 4),
        std::make_unique<AudioParameterFloat> ("noteNum", "Temperament", NormalisableRange<float>(1, 1000, 1, 0.3), 12)
    })
{
}

TemperamentAudioProcessor::~TemperamentAudioProcessor()
{
}

//==============================================================================
const String TemperamentAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TemperamentAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TemperamentAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TemperamentAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TemperamentAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TemperamentAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TemperamentAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TemperamentAudioProcessor::setCurrentProgram (int index)
{
}

const String TemperamentAudioProcessor::getProgramName (int index)
{
    return {};
}

void TemperamentAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TemperamentAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    synth.setCurrentPlaybackSampleRate(sampleRate);
}

void TemperamentAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TemperamentAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TemperamentAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    synth.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool TemperamentAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TemperamentAudioProcessor::createEditor()
{
    return new TemperamentAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void TemperamentAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void TemperamentAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.replaceState (ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TemperamentAudioProcessor();
}

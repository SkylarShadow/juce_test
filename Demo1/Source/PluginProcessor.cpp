/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Demo1AudioProcessor::Demo1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

Demo1AudioProcessor::~Demo1AudioProcessor()
{
}

//==============================================================================
const juce::String Demo1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Demo1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Demo1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Demo1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Demo1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Demo1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Demo1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Demo1AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Demo1AudioProcessor::getProgramName (int index)
{
    return {};
}

void Demo1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Demo1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Demo1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Demo1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void Demo1AudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    //buffer.applyGain(volume);  //把volume值设为音量，如果下方的channeldata设置了声音变化，则这里不起效
	juce::ScopedNoDenormals noDenormals;
	int pos;
	juce::MidiMessage midi_event;
	for (juce::MidiBuffer::Iterator i(midiMessages); i.getNextEvent(midi_event,pos);) {
		if (midi_event.isNoteOn()) {
			frequency = juce::MidiMessage::getMidiNoteInHertz(midi_event.getNoteNumber());
		}
		else if (midi_event.isNoteOff()) {
			frequency = -1;
		}
	}

	if (frequency > 0) {
		auto totalNumInputChannels = getTotalNumInputChannels();
		auto totalNumOutputChannels = getTotalNumOutputChannels();
		auto sampleRate = getSampleRate();
		auto* channelDataL = buffer.getWritePointer(0);
		auto* channelDataR = buffer.getWritePointer(1);


		for (auto sample = 0; sample < buffer.getNumSamples(); sample++) {
			auto sample_pos = (double)std::sin(currentAngle);
			currentAngle += 2 * juce::MathConstants<double>::pi * 1000 / sampleRate;
			channelDataL[sample] = sample_pos * volume;
			channelDataR[sample] = sample_pos * volume;
		}

	}
}

//==============================================================================
bool Demo1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Demo1AudioProcessor::createEditor()
{
    return new Demo1AudioProcessorEditor (*this);
}

//==============================================================================
void Demo1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Demo1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Demo1AudioProcessor();
}

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
OscAudioProcessor::OscAudioProcessor()
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

OscAudioProcessor::~OscAudioProcessor()
{
}

//==============================================================================
const juce::String OscAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool OscAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool OscAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool OscAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double OscAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int OscAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int OscAudioProcessor::getCurrentProgram()
{
    return 0;
}

void OscAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String OscAudioProcessor::getProgramName (int index)
{
    return {};
}

void OscAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void OscAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void OscAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool OscAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void OscAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)  //声音从processBlock方法产生
{
    juce::ScopedNoDenormals noDenormals; //提供raii(资源获取即初始化)机制 ，要求由对象的构造函数完成资源分配，由析构函数完成资源释放，保证代码异常安全性
	auto sampleRate = getSampleRate();
	auto* channelData = buffer.getWritePointer(0);
	auto* channelDataR = buffer.getWritePointer(1);
	
	for (auto sample = 0; sample < buffer.getNumSamples(); ++sample) {
		auto sample_pos = (float)std::sin(currentAngle);
		currentAngle += 2 * juce::MathConstants<double>::pi * 432 / sampleRate;
		channelData[sample] = sample_pos * volume;
		channelDataR[sample] = sample_pos * volume;

	}
}

//==============================================================================
bool OscAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* OscAudioProcessor::createEditor()
{
    return new OscAudioProcessorEditor (*this);
}

//==============================================================================
void OscAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void OscAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OscAudioProcessor();
}

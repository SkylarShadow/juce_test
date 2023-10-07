/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Demo1AudioProcessorEditor  : public juce::AudioProcessorEditor  // 重载AudioProcessorEditor父类
{
public:
    Demo1AudioProcessorEditor (Demo1AudioProcessor&);
    ~Demo1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Demo1AudioProcessor& audioProcessor;
	juce::Slider slider_vol;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Demo1AudioProcessorEditor)



};


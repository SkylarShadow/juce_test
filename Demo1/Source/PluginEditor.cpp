/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Demo1AudioProcessorEditor::Demo1AudioProcessorEditor (Demo1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
	slider_vol.setBounds(0, 0, 30, 300);   //推子大小和在界面位置
	slider_vol.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	slider_vol.setRange(0, 5, 0.05);

    slider_vol.onValueChange = [this]() {audioProcessor.volume = slider_vol.getValue(); };  // this能传入 Demo1AudioProcessorEditor中的slider_vol 和 audioProcessor
	addAndMakeVisible(slider_vol);
}

Demo1AudioProcessorEditor::~Demo1AudioProcessorEditor()
{
}

//==============================================================================
void Demo1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::grey);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void Demo1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

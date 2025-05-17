/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VisualWaveAudioProcessorEditor::VisualWaveAudioProcessorEditor (VisualWaveAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 300);
    startTimerHz(30); //repaint at 30fps
}

VisualWaveAudioProcessorEditor::~VisualWaveAudioProcessorEditor()
{
}

void VisualWaveAudioProcessorEditor::timerCallback()
{
    repaint();
}

//==============================================================================
void VisualWaveAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

    auto bounds = getLocalBounds().toFloat();
    g.setColour(juce::Colours::green);

    const auto& buffer = audioProcessor.waveformBuffer;

    if (buffer.getNumSamples() == 0 || buffer.getNumChannels() == 0)
        return;

    juce::Path waveformPath;
    auto* samples = buffer.getReadPointer(0);
    int numSamples = buffer.getNumSamples();

    waveformPath.startNewSubPath(0, bounds.getCentreY());

    for (int i = 0; i < numSamples; ++i)
    {
        float x = juce::jmap((float)i, 0.0f, (float)numSamples, 0.0f, bounds.getWidth());
        float y = juce::jmap(samples[i], -1.0f, 1.0f, bounds.getBottom(), bounds.getY());
        waveformPath.lineTo(x, y);
    }

    g.strokePath(waveformPath, juce::PathStrokeType(1.5f));
}

void VisualWaveAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

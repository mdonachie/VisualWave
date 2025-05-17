#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class VisualWaveAudioProcessorEditor : public juce::AudioProcessorEditor,
                                       private juce::Timer
{
public:
    VisualWaveAudioProcessorEditor(VisualWaveAudioProcessor&);
    ~VisualWaveAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    VisualWaveAudioProcessor& audioProcessor;

    void timerCallback() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VisualWaveAudioProcessorEditor)
};

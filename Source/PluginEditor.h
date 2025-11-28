#pragma once

#include "PluginProcessor.h"
#include "Parameters.h"


//==============================================================================
class delayAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit delayAudioProcessorEditor(DelayAudioProcessor& p);
    ~delayAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DelayAudioProcessor& audioProcessor;
    juce::Slider slider;

    juce::Label label;
    juce::AudioProcessorValueTreeState::SliderAttachment attachment{
        audioProcessor.apvts, gainParamID.getParamID(), slider
    };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(delayAudioProcessorEditor)
};

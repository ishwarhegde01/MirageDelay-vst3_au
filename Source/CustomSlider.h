#pragma once
#include <juce_audio_processors/juce_audio_processors.h>


class CSlider: public juce::Component
{
public:
    static constexpr float  scrollInterval{0.05f};
    static constexpr float scrollIntervalSensitive{0.01f};
    static constexpr float sensitiveSpeed{1.0f/16.0f};
    CSlider(juce::AudioProcessorValueTreeState& apvts, juce::String id):
    otherSlider{nullptr},
    paramText{nullptr},
    param{apvts.getParameter(id)},

    {
    }
    CSlider* otherSlider{};
    juce::RangedAudioParameter* param{};

};


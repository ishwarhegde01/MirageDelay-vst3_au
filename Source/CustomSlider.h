#pragma once
#include <juce_audio_processors/juce_audio_processors.h>


struct superSlider:public juce::Slider
{
    using Slider = juce::Slider;
    using Style = Slider::SliderStyle;
    using BoxPos = Slider::TextEntryBoxPosition;
    using Mouse = juce::MouseEvent;
    using Wheel = juce::MouseWheelDetails;
    static constexpr float normalWheel = .7f;
    static constexpr float sensitiveWheel = 0.1f;

    void mouseWheelMove(const juce::MouseEvent& event, const juce::MouseWheelDetails& wheel) override
    {
        auto newWheel = wheel;
        const auto speed = event.mods.isShiftDown() ? sensitiveWheel:normalWheel;
        newWheel.deltaX *= speed;

        Slider::mouseWheelMove(event, newWheel);

    }
};


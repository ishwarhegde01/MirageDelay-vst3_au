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
    static constexpr float sensitiveWheel = 0.5f;

    void mouseWheelMove(const juce::MouseEvent& event, const juce::MouseWheelDetails& wheel) override
    {
        // Strip out Alt modifier to prevent JUCE's default fine control
        auto modifiedEvent = event.withNewModifiers(
            event.mods.withoutFlags(juce::ModifierKeys::altModifier)
        );

        // Apply our own speed multiplier
        auto newWheel = wheel;
        const auto speed = event.mods.isShiftDown() ? sensitiveWheel : normalWheel;
        newWheel.deltaY *= speed;

        // Pass modified event and wheel to base class
        Slider::mouseWheelMove(modifiedEvent, newWheel);
    }
};


#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
delayAudioProcessorEditor::delayAudioProcessorEditor (DelayAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 70, 16);

    slider.setVelocityModeParameters(
        1.0,        // sensitivity (default)
        1,          // threshold (default)
        0.0,        // offset (default)
        true,       // userCanPressKeyToSwapMode
        juce::ModifierKeys::shiftModifier  // Use shift instead of ctrl
    );
    slider.setBounds(0, 0, 70, 86);
    addAndMakeVisible(slider);
    setSize (500, 330);



    label.setText("Gain", juce::NotificationType::dontSendNotification);
    label.setJustificationType(juce::Justification::horizontallyCentred);
    label.setBorderSize(juce::BorderSize<int>{ 0, 0, 2, 0 });
    // label.attachToComponent(&slider, true);
    addAndMakeVisible(label);
}

delayAudioProcessorEditor::~delayAudioProcessorEditor()
{
}

//==============================================================================
void delayAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::black);
}

void delayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor...
    slider.setTopLeftPosition(215, 120);
    label.setBounds(slider.getX(),
                slider.getBottom() ,   // 4 pixels spacing
                slider.getWidth(),
                20);
}

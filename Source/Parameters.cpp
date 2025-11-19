//
// Created by ishwar on 19/11/25.
//

#include "Parameters.h"

template <typename T>
static T castProcessor(const juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& id)
{
    auto result = dynamic_cast<T>(apvts.getParameter(id.getParamID()));
    jassert(result);
    return result;
}


Parameters::Parameters(const juce::AudioProcessorValueTreeState& apvts) :
    gainParam{castProcessor<juce::AudioParameterFloat*>(apvts, gainParamID)}
{
}



juce::AudioProcessorValueTreeState::ParameterLayout Parameters::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add(std::make_unique<juce::AudioParameterFloat>(gainParamID,
                                                           "Output Gain",
                                                           juce::NormalisableRange<float>{-12.0f, 12.0f},
                                                           0.0f));
    return layout;
}


void Parameters::update() noexcept
{
    gainSmoother.setTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));
}

void Parameters::prepareToPlay(double sampleRate) noexcept
{
    double duration {0.02};
    gainSmoother.reset(sampleRate,duration);
}

void Parameters::reset() noexcept
{
    gain = 0.0f;
    gainSmoother.setCurrentAndTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));

}

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

static juce::String stringFromMilliseconds(float value, int)
{
    if (value < 10.0f)
    {
        return juce::String(value, 2) + " ms";
    }
    else if (value < 100.0f)
    {
        return juce::String(value, 1) + " ms";
    }
    else if (value < 1000.0f)
    {
        return juce::String(static_cast<int>(value)) + " ms";
    }
    else
    {
        return juce::String(value * 0.001f, 2) + " s";
    }
}

static juce::String stringFromDecibels(float value, int)
{
    return juce::String(value, 1) + " dB";
}


static juce::String stringFromPercent(float value, int)
{
    return juce::String(static_cast<int>(value)) + " %";
}

Parameters::Parameters(const juce::AudioProcessorValueTreeState& apvts) :
    gainParam{castProcessor<juce::AudioParameterFloat*>(apvts, gainParamID)},
    delayTimeParam{castProcessor<juce::AudioParameterFloat*>(apvts, delayTimeParamID)},
    mixParam{castProcessor<juce::AudioParameterFloat*>(apvts, mixParamID)}
{
}

juce::AudioProcessorValueTreeState::ParameterLayout Parameters::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add(std::make_unique<juce::AudioParameterFloat>(gainParamID,
                                                           "Output Gain",
                                                           juce::NormalisableRange<float>{
                                                               -12.0f,
                                                               12.0f
                                                           },
                                                           0.0f,
                                                           juce::AudioParameterFloatAttributes().
                                                           withStringFromValueFunction(stringFromDecibels)));
    layout.add(std::make_unique<juce::AudioParameterFloat>(delayTimeParamID, "Delay Time",
                                                           juce::NormalisableRange<float>{
                                                               minDelayTime, maxDelayTime,
                                                               0.001f, 0.33f
                                                           },
                                                           100.0f,
                                                           juce::AudioParameterFloatAttributes().
                                                           withStringFromValueFunction(stringFromMilliseconds)));
    layout.add(std::make_unique<juce::AudioParameterFloat>(mixParamID, "mix",
                                                           juce::NormalisableRange<float>{0.0f, 100.0f,1.0f},
                                                           100.0f,
                                                           juce::AudioParameterFloatAttributes().
                                                           withStringFromValueFunction(stringFromPercent)));
    return layout;
}


void Parameters::update() noexcept
{
    gainSmoother.setTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));
    targetDelayTime = delayTimeParam->get();
    if (delayTime == 0.0f)
    {
        delayTime = targetDelayTime;
    }
    mixSmoother.setTargetValue(mixParam->get() * 0.01f);


}

void Parameters::prepareToPlay(double sampleRate) noexcept
{
    constexpr double duration{0.02};
    gainSmoother.reset(sampleRate, duration);
    coeff = 1.0f - std::exp(-1.0f / (0.2f * static_cast<float>(sampleRate)));
    mixSmoother.reset(sampleRate,duration);
}

void Parameters::reset() noexcept
{
    gain = 0.0f;
    gainSmoother.setCurrentAndTargetValue(juce::Decibels::decibelsToGain(gainParam->get()));
    delayTime = 0.0f;
    mix = 1.0f;
    mixSmoother.setCurrentAndTargetValue(mixParam->get() * 0.01f);
}

void Parameters::smoothen() noexcept
{
    gain = gainSmoother.getNextValue();
    delayTime += (targetDelayTime - delayTime) * coeff;
    mix = mixSmoother.getNextValue();
}

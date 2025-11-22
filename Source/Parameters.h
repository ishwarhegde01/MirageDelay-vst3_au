//
// Created by ishwar on 19/11/25.
//

#ifndef MIRAGEDELAY_PARAMETERS_H
#define MIRAGEDELAY_PARAMETERS_H


#include <juce_audio_processors/juce_audio_processors.h>
const juce::ParameterID gainParamID{"gain", 1};
const juce::ParameterID delayTimeParamID{"delayTime", 1};

class Parameters
{
public:
    explicit Parameters(const juce::AudioProcessorValueTreeState& apvts);
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void update() noexcept;
    void prepareToPlay(double sampleRate) noexcept;
    void reset() noexcept;
    void smoothen() noexcept;

    float gain{};
    static constexpr float minDelayTime{5.0f};
    static constexpr float maxDelayTime{5000.0f};
    float delayTime{0.0f};
private:
    juce::AudioParameterFloat* gainParam{};
    juce::LinearSmoothedValue<float> gainSmoother{};
    juce::AudioParameterFloat* delayTimeParam{};
};


#endif //MIRAGEDELAY_PARAMETERS_H

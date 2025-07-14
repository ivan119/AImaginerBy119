#pragma once

#include <JuceHeader.h>
#include "AudioProcessor.h"
#include "TunerComponent.h"

class AIImagerAudioProcessor : public juce::AudioProcessor
{
public:
    AIImagerAudioProcessor();
    ~AIImagerAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    bool isBusesLayoutSupported(const BusesLayout &busesLayout) const override;
    void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

    juce::AudioProcessorEditor *createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String &newName) override;

    void getStateInformation(juce::MemoryBlock &destData) override;
    void setStateInformation(const void *data, int sizeInBytes) override;

    // Futuristic parameters
    juce::AudioProcessorValueTreeState parameters;

    // Tuner component
    std::unique_ptr<TunerComponent> tuner;

    // AI Processing parameters
    juce::AudioParameterFloat *aiIntensity;
    juce::AudioParameterFloat *futureResonance;
    juce::AudioParameterFloat *quantumDepth;
    juce::AudioParameterBool *neuralEnhancement;
    juce::AudioParameterBool *holographicMode;

private:
    std::unique_ptr<AudioProcessor> audioProcessor;
    juce::dsp::Gain<float> inputGain;
    juce::dsp::Gain<float> outputGain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AIImagerAudioProcessor)
};
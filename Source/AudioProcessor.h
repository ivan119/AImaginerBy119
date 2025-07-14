#pragma once

#include <JuceHeader.h>

class AudioProcessor
{
public:
    AudioProcessor();
    ~AudioProcessor() = default;

    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void releaseResources();
    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages);

    // Futuristic effect parameters
    void setAIIntensity(float intensity);
    void setFutureResonance(float resonance);
    void setQuantumDepth(float depth);
    void setNeuralEnhancement(bool enabled);
    void setHolographicMode(bool enabled);

private:
    // DSP modules
    juce::dsp::Gain<float> inputGain;
    juce::dsp::Gain<float> outputGain;
    juce::dsp::Compressor<float> compressor;
    juce::dsp::IIR::Filter<float> lowPassFilter;
    juce::dsp::IIR::Filter<float> highPassFilter;

    // Parameters
    float aiIntensity;
    float futureResonance;
    float quantumDepth;
    bool neuralEnhancement;
    bool holographicMode;

    // Processing state
    double sampleRate;
    int blockSize;
    float phase;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioProcessor)
};
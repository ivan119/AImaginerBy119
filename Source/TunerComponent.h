#pragma once

#include <JuceHeader.h>

class TunerComponent : public juce::Component, public juce::Timer
{
public:
    TunerComponent();
    ~TunerComponent() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void releaseResources();
    void processAudio(const juce::AudioBuffer<float> &buffer);

    void paint(juce::Graphics &g) override;
    void resized() override;
    void timerCallback() override;

private:
    // Pitch detection
    std::vector<float> audioBuffer;
    double sampleRate;
    int bufferSize;

    // Current detected pitch
    float currentFrequency;
    float currentNote;
    float cents;
    bool isInTune;

    // Futuristic visual elements
    float visualIntensity;
    float pulseAnimation;
    juce::Colour primaryColor;
    juce::Colour secondaryColor;
    juce::Colour accentColor;

    // Note names for display
    const std::vector<juce::String> noteNames = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

    // Pitch detection algorithm
    float detectPitch(const std::vector<float> &buffer);
    float frequencyToNote(float frequency);
    float noteToFrequency(float note);
    float centsFromNote(float frequency, float note);

    // Visual helpers
    void drawFuturisticBackground(juce::Graphics &g);
    void drawTunerDisplay(juce::Graphics &g);
    void drawHolographicEffects(juce::Graphics &g);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TunerComponent)
};
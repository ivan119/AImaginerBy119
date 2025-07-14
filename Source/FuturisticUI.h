#pragma once

#include <JuceHeader.h>
#include "TunerComponent.h"

class FuturisticUI : public juce::Component, public juce::Timer
{
public:
    FuturisticUI();
    ~FuturisticUI() override;

    void paint(juce::Graphics &g) override;
    void resized() override;
    void timerCallback() override;

    // Parameter controls
    void setAIIntensity(float value);
    void setFutureResonance(float value);
    void setQuantumDepth(float value);
    void setNeuralEnhancement(bool enabled);
    void setHolographicMode(bool enabled);

    // Callbacks
    std::function<void(float)> onAIIntensityChanged;
    std::function<void(float)> onFutureResonanceChanged;
    std::function<void(float)> onQuantumDepthChanged;
    std::function<void(bool)> onNeuralEnhancementChanged;
    std::function<void(bool)> onHolographicModeChanged;

private:
    // UI Components
    std::unique_ptr<TunerComponent> tunerComponent;
    std::unique_ptr<juce::Slider> aiIntensitySlider;
    std::unique_ptr<juce::Slider> futureResonanceSlider;
    std::unique_ptr<juce::Slider> quantumDepthSlider;
    std::unique_ptr<juce::ToggleButton> neuralEnhancementButton;
    std::unique_ptr<juce::ToggleButton> holographicModeButton;

    // Visual effects
    float animationTime;
    float pulseIntensity;
    juce::Colour primaryColor;
    juce::Colour secondaryColor;
    juce::Colour accentColor;
    juce::Colour backgroundColor;

    // Parameters
    float aiIntensity;
    float futureResonance;
    float quantumDepth;
    bool neuralEnhancement;
    bool holographicMode;

    // Drawing helpers
    void drawFuturisticBackground(juce::Graphics &g);
    void drawHolographicGrid(juce::Graphics &g);
    void drawParticleEffects(juce::Graphics &g);
    void drawDataStreams(juce::Graphics &g);
    void drawStatusIndicators(juce::Graphics &g);

    // UI helpers
    void setupSliders();
    void setupButtons();
    void updateColors();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FuturisticUI)
};
#include "PluginProcessor.h"
#include "PluginEditor.h"

AIImagerAudioProcessorEditor::AIImagerAudioProcessorEditor(AIImagerAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Create futuristic UI
    futuristicUI = std::make_unique<FuturisticUI>();
    addAndMakeVisible(futuristicUI.get());

    // Connect UI callbacks to processor
    futuristicUI->onAIIntensityChanged = [this](float value)
    {
        if (audioProcessor.aiIntensity)
            audioProcessor.aiIntensity->setValueNotifyingHost(value);
    };

    futuristicUI->onFutureResonanceChanged = [this](float value)
    {
        if (audioProcessor.futureResonance)
            audioProcessor.futureResonance->setValueNotifyingHost(value);
    };

    futuristicUI->onQuantumDepthChanged = [this](float value)
    {
        if (audioProcessor.quantumDepth)
            audioProcessor.quantumDepth->setValueNotifyingHost(value);
    };

    futuristicUI->onNeuralEnhancementChanged = [this](bool enabled)
    {
        if (audioProcessor.neuralEnhancement)
            audioProcessor.neuralEnhancement->setValueNotifyingHost(enabled ? 1.0f : 0.0f);
    };

    futuristicUI->onHolographicModeChanged = [this](bool enabled)
    {
        if (audioProcessor.holographicMode)
            audioProcessor.holographicMode->setValueNotifyingHost(enabled ? 1.0f : 0.0f);
    };

    // Set initial values from processor
    if (audioProcessor.aiIntensity)
        futuristicUI->setAIIntensity(audioProcessor.aiIntensity->get());
    if (audioProcessor.futureResonance)
        futuristicUI->setFutureResonance(audioProcessor.futureResonance->get());
    if (audioProcessor.quantumDepth)
        futuristicUI->setQuantumDepth(audioProcessor.quantumDepth->get());
    if (audioProcessor.neuralEnhancement)
        futuristicUI->setNeuralEnhancement(audioProcessor.neuralEnhancement->get());
    if (audioProcessor.holographicMode)
        futuristicUI->setHolographicMode(audioProcessor.holographicMode->get());

    // Set window size for futuristic interface
    setSize(800, 600);
}

AIImagerAudioProcessorEditor::~AIImagerAudioProcessorEditor() = default;

void AIImagerAudioProcessorEditor::paint(juce::Graphics &g)
{
    // Background is handled by the futuristic UI component
    g.fillAll(juce::Colour(0xFF001122));
}

void AIImagerAudioProcessorEditor::resized()
{
    // The futuristic UI takes up the entire editor
    futuristicUI->setBounds(getLocalBounds());
}
#include "FuturisticUI.h"
#include <cmath>

FuturisticUI::FuturisticUI()
    : animationTime(0.0f), pulseIntensity(0.0f), primaryColor(juce::Colour(0xFF00FFFF)) // Cyan
      ,
      secondaryColor(juce::Colour(0xFF8000FF)) // Purple
      ,
      accentColor(juce::Colour(0xFFFF0080)) // Magenta
      ,
      backgroundColor(juce::Colour(0xFF001122)) // Dark blue
      ,
      aiIntensity(0.5f), futureResonance(0.3f), quantumDepth(0.7f), neuralEnhancement(false), holographicMode(false)
{
    // Create tuner component
    tunerComponent = std::make_unique<TunerComponent>();
    addAndMakeVisible(tunerComponent.get());

    // Setup UI components
    setupSliders();
    setupButtons();

    // Start animation timer
    startTimerHz(60); // 60 FPS for smooth animations
}

FuturisticUI::~FuturisticUI()
{
    stopTimer();
}

void FuturisticUI::setupSliders()
{
    // AI Intensity Slider
    aiIntensitySlider = std::make_unique<juce::Slider>(juce::Slider::RotaryHorizontalVerticalDrag);
    aiIntensitySlider->setRange(0.0, 1.0, 0.01);
    aiIntensitySlider->setValue(aiIntensity);
    aiIntensitySlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    aiIntensitySlider->setColour(juce::Slider::thumbColourId, primaryColor);
    aiIntensitySlider->setColour(juce::Slider::trackColourId, primaryColor.withAlpha(0.3f));
    aiIntensitySlider->onValueChange = [this]()
    {
        aiIntensity = static_cast<float>(aiIntensitySlider->getValue());
        if (onAIIntensityChanged)
            onAIIntensityChanged(aiIntensity);
    };
    addAndMakeVisible(aiIntensitySlider.get());

    // Future Resonance Slider
    futureResonanceSlider = std::make_unique<juce::Slider>(juce::Slider::RotaryHorizontalVerticalDrag);
    futureResonanceSlider->setRange(0.0, 1.0, 0.01);
    futureResonanceSlider->setValue(futureResonance);
    futureResonanceSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    futureResonanceSlider->setColour(juce::Slider::thumbColourId, secondaryColor);
    futureResonanceSlider->setColour(juce::Slider::trackColourId, secondaryColor.withAlpha(0.3f));
    futureResonanceSlider->onValueChange = [this]()
    {
        futureResonance = static_cast<float>(futureResonanceSlider->getValue());
        if (onFutureResonanceChanged)
            onFutureResonanceChanged(futureResonance);
    };
    addAndMakeVisible(futureResonanceSlider.get());

    // Quantum Depth Slider
    quantumDepthSlider = std::make_unique<juce::Slider>(juce::Slider::RotaryHorizontalVerticalDrag);
    quantumDepthSlider->setRange(0.0, 1.0, 0.01);
    quantumDepthSlider->setValue(quantumDepth);
    quantumDepthSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    quantumDepthSlider->setColour(juce::Slider::thumbColourId, accentColor);
    quantumDepthSlider->setColour(juce::Slider::trackColourId, accentColor.withAlpha(0.3f));
    quantumDepthSlider->onValueChange = [this]()
    {
        quantumDepth = static_cast<float>(quantumDepthSlider->getValue());
        if (onQuantumDepthChanged)
            onQuantumDepthChanged(quantumDepth);
    };
    addAndMakeVisible(quantumDepthSlider.get());
}

void FuturisticUI::setupButtons()
{
    // Neural Enhancement Button
    neuralEnhancementButton = std::make_unique<juce::ToggleButton>("NEURAL ENHANCEMENT");
    neuralEnhancementButton->setButtonText("NEURAL ENHANCEMENT");
    neuralEnhancementButton->setColour(juce::ToggleButton::textColourId, primaryColor);
    neuralEnhancementButton->setColour(juce::ToggleButton::tickColourId, primaryColor);
    neuralEnhancementButton->onClick = [this]()
    {
        neuralEnhancement = neuralEnhancementButton->getToggleState();
        if (onNeuralEnhancementChanged)
            onNeuralEnhancementChanged(neuralEnhancement);
    };
    addAndMakeVisible(neuralEnhancementButton.get());

    // Holographic Mode Button
    holographicModeButton = std::make_unique<juce::ToggleButton>("HOLOGRAPHIC MODE");
    holographicModeButton->setButtonText("HOLOGRAPHIC MODE");
    holographicModeButton->setColour(juce::ToggleButton::textColourId, accentColor);
    holographicModeButton->setColour(juce::ToggleButton::tickColourId, accentColor);
    holographicModeButton->onClick = [this]()
    {
        holographicMode = holographicModeButton->getToggleState();
        if (onHolographicModeChanged)
            onHolographicModeChanged(holographicMode);
    };
    addAndMakeVisible(holographicModeButton.get());
}

void FuturisticUI::paint(juce::Graphics &g)
{
    drawFuturisticBackground(g);
    drawHolographicGrid(g);
    drawParticleEffects(g);
    drawDataStreams(g);
    drawStatusIndicators(g);
}

void FuturisticUI::drawFuturisticBackground(juce::Graphics &g)
{
    auto bounds = getLocalBounds().toFloat();

    // Gradient background
    juce::ColourGradient gradient(
        backgroundColor,
        0.0f, 0.0f,
        backgroundColor.darker(0.3f),
        bounds.getWidth(), bounds.getHeight(),
        false);
    g.setGradientFill(gradient);
    g.fillAll();

    // Animated scan lines
    g.setColour(primaryColor.withAlpha(0.1f));
    for (int i = 0; i < 10; ++i)
    {
        float y = bounds.getHeight() * (static_cast<float>(i) / 9.0f);
        float alpha = 0.1f + 0.05f * std::sin(animationTime + i * 0.5f);
        g.setColour(primaryColor.withAlpha(alpha));
        g.drawHorizontalLine(static_cast<int>(y), 0.0f, bounds.getWidth());
    }
}

void FuturisticUI::drawHolographicGrid(juce::Graphics &g)
{
    auto bounds = getLocalBounds().toFloat();

    // Perspective grid
    g.setColour(primaryColor.withAlpha(0.2f));
    float gridSize = 40.0f;
    float perspective = 0.8f;

    for (int i = 0; i < 20; ++i)
    {
        float x = bounds.getWidth() * (static_cast<float>(i) / 19.0f);
        float y = bounds.getHeight() * (static_cast<float>(i) / 19.0f);

        // Vertical lines with perspective
        float alpha = 0.2f * (1.0f - static_cast<float>(i) / 19.0f);
        g.setColour(primaryColor.withAlpha(alpha));
        g.drawVerticalLine(static_cast<int>(x), 0.0f, bounds.getHeight());

        // Horizontal lines
        g.setColour(primaryColor.withAlpha(alpha));
        g.drawHorizontalLine(static_cast<int>(y), 0.0f, bounds.getWidth());
    }
}

void FuturisticUI::drawParticleEffects(juce::Graphics &g)
{
    auto bounds = getLocalBounds().toFloat();

    // Animated particles
    for (int i = 0; i < 50; ++i)
    {
        float x = bounds.getWidth() * (0.5f + 0.5f * std::sin(animationTime * 0.5f + i * 0.1f));
        float y = bounds.getHeight() * (0.5f + 0.5f * std::cos(animationTime * 0.3f + i * 0.15f));
        float size = 2.0f + std::sin(animationTime + i) * 3.0f;
        float alpha = 0.3f + 0.2f * std::sin(animationTime * 2.0f + i * 0.2f);

        g.setColour(accentColor.withAlpha(alpha));
        g.fillEllipse(x - size * 0.5f, y - size * 0.5f, size, size);
    }
}

void FuturisticUI::drawDataStreams(juce::Graphics &g)
{
    auto bounds = getLocalBounds().toFloat();

    // Data stream effect
    g.setColour(secondaryColor.withAlpha(0.4f));
    for (int i = 0; i < 5; ++i)
    {
        float x = bounds.getWidth() * (static_cast<float>(i) / 4.0f);
        float height = 20.0f + std::sin(animationTime + i) * 10.0f;

        juce::Path dataPath;
        dataPath.startNewSubPath(x, bounds.getHeight() - height);
        dataPath.lineTo(x, bounds.getHeight());
        g.strokePath(dataPath, juce::PathStrokeType(2.0f));
    }
}

void FuturisticUI::drawStatusIndicators(juce::Graphics &g)
{
    auto bounds = getLocalBounds().toFloat();

    // Status indicators
    g.setColour(primaryColor);
    g.setFont(juce::Font(16.0f, juce::Font::bold));
    g.drawText("AI IMAGER by 119", bounds.removeFromTop(30), juce::Justification::centred);

    // Parameter values
    g.setFont(juce::Font(12.0f));
    g.setColour(primaryColor);
    g.drawText("AI: " + juce::String(aiIntensity, 2), 10, 40, 100, 20, juce::Justification::left);
    g.setColour(secondaryColor);
    g.drawText("RES: " + juce::String(futureResonance, 2), 120, 40, 100, 20, juce::Justification::left);
    g.setColour(accentColor);
    g.drawText("QNT: " + juce::String(quantumDepth, 2), 230, 40, 100, 20, juce::Justification::left);
}

void FuturisticUI::resized()
{
    auto bounds = getLocalBounds();

    // Tuner component (center)
    auto tunerBounds = bounds.reduced(20);
    tunerBounds.removeFromTop(80);
    tunerBounds.removeFromBottom(120);
    tunerComponent->setBounds(tunerBounds);

    // Sliders (bottom row)
    auto sliderBounds = bounds.removeFromBottom(100);
    int sliderWidth = sliderBounds.getWidth() / 3;

    aiIntensitySlider->setBounds(sliderBounds.removeFromLeft(sliderWidth).reduced(10));
    futureResonanceSlider->setBounds(sliderBounds.removeFromLeft(sliderWidth).reduced(10));
    quantumDepthSlider->setBounds(sliderBounds.reduced(10));

    // Buttons (top)
    auto buttonBounds = bounds.removeFromTop(60);
    neuralEnhancementButton->setBounds(buttonBounds.removeFromLeft(buttonBounds.getWidth() / 2).reduced(10));
    holographicModeButton->setBounds(buttonBounds.reduced(10));
}

void FuturisticUI::timerCallback()
{
    // Update animation time
    animationTime += 0.016f; // 60 FPS
    if (animationTime > juce::MathConstants<float>::twoPi)
        animationTime -= juce::MathConstants<float>::twoPi;

    // Update pulse intensity
    pulseIntensity = 0.5f + 0.5f * std::sin(animationTime * 2.0f);

    // Trigger repaint for animations
    repaint();
}

void FuturisticUI::setAIIntensity(float value)
{
    aiIntensity = value;
    if (aiIntensitySlider)
        aiIntensitySlider->setValue(value);
}

void FuturisticUI::setFutureResonance(float value)
{
    futureResonance = value;
    if (futureResonanceSlider)
        futureResonanceSlider->setValue(value);
}

void FuturisticUI::setQuantumDepth(float value)
{
    quantumDepth = value;
    if (quantumDepthSlider)
        quantumDepthSlider->setValue(value);
}

void FuturisticUI::setNeuralEnhancement(bool enabled)
{
    neuralEnhancement = enabled;
    if (neuralEnhancementButton)
        neuralEnhancementButton->setToggleState(enabled, juce::dontSendNotification);
}

void FuturisticUI::setHolographicMode(bool enabled)
{
    holographicMode = enabled;
    if (holographicModeButton)
        holographicModeButton->setToggleState(enabled, juce::dontSendNotification);
}
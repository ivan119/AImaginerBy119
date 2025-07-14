#include "TunerComponent.h"
#include <cmath>
#include <algorithm>

TunerComponent::TunerComponent()
    : currentFrequency(0.0f), currentNote(0.0f), cents(0.0f), isInTune(false), visualIntensity(0.0f), pulseAnimation(0.0f), primaryColor(juce::Colour(0xFF00FFFF)) // Cyan
      ,
      secondaryColor(juce::Colour(0xFF8000FF)) // Purple
      ,
      accentColor(juce::Colour(0xFFFF0080)) // Magenta
{
    startTimerHz(30); // 30 FPS animation
}

TunerComponent::~TunerComponent()
{
    stopTimer();
}

void TunerComponent::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    this->sampleRate = sampleRate;
    this->bufferSize = samplesPerBlock;
    audioBuffer.resize(samplesPerBlock);
}

void TunerComponent::releaseResources()
{
    audioBuffer.clear();
}

void TunerComponent::processAudio(const juce::AudioBuffer<float> &buffer)
{
    if (buffer.getNumChannels() > 0)
    {
        const float *channelData = buffer.getReadPointer(0);

        // Copy audio data for pitch detection
        for (int i = 0; i < buffer.getNumSamples() && i < static_cast<int>(audioBuffer.size()); ++i)
        {
            audioBuffer[i] = channelData[i];
        }

        // Detect pitch
        currentFrequency = detectPitch(audioBuffer);

        if (currentFrequency > 0.0f)
        {
            currentNote = frequencyToNote(currentFrequency);
            float targetFreq = noteToFrequency(currentNote);
            cents = centsFromNote(currentFrequency, currentNote);
            isInTune = std::abs(cents) < 10.0f; // Within 10 cents is "in tune"

            // Update visual intensity based on signal strength
            float rms = 0.0f;
            for (float sample : audioBuffer)
                rms += sample * sample;
            rms = std::sqrt(rms / audioBuffer.size());
            visualIntensity = juce::jlimit(0.0f, 1.0f, rms * 10.0f);
        }
        else
        {
            visualIntensity *= 0.95f; // Fade out
        }
    }
}

float TunerComponent::detectPitch(const std::vector<float> &buffer)
{
    if (buffer.empty())
        return 0.0f;

    // Simple autocorrelation-based pitch detection
    const int maxLag = static_cast<int>(sampleRate / 80.0);   // Minimum frequency ~80 Hz
    const int minLag = static_cast<int>(sampleRate / 1000.0); // Maximum frequency ~1000 Hz

    float maxCorrelation = 0.0f;
    int bestLag = 0;

    for (int lag = minLag; lag < maxLag; ++lag)
    {
        float correlation = 0.0f;
        int count = 0;

        for (int i = 0; i < static_cast<int>(buffer.size()) - lag; ++i)
        {
            correlation += buffer[i] * buffer[i + lag];
            count++;
        }

        if (count > 0)
        {
            correlation /= count;
            if (correlation > maxCorrelation)
            {
                maxCorrelation = correlation;
                bestLag = lag;
            }
        }
    }

    if (maxCorrelation > 0.1f && bestLag > 0)
        return sampleRate / static_cast<float>(bestLag);

    return 0.0f;
}

float TunerComponent::frequencyToNote(float frequency)
{
    if (frequency <= 0.0f)
        return 0.0f;
    return 12.0f * std::log2(frequency / 440.0f) + 69.0f; // A4 = 440Hz, MIDI note 69
}

float TunerComponent::noteToFrequency(float note)
{
    return 440.0f * std::pow(2.0f, (note - 69.0f) / 12.0f);
}

float TunerComponent::centsFromNote(float frequency, float note)
{
    if (frequency <= 0.0f)
        return 0.0f;
    float targetFreq = noteToFrequency(note);
    return 1200.0f * std::log2(frequency / targetFreq);
}

void TunerComponent::paint(juce::Graphics &g)
{
    drawFuturisticBackground(g);
    drawTunerDisplay(g);
    drawHolographicEffects(g);
}

void TunerComponent::drawFuturisticBackground(juce::Graphics &g)
{
    auto bounds = getLocalBounds().toFloat();

    // Gradient background
    juce::ColourGradient gradient(
        primaryColor.withAlpha(0.3f),
        0.0f, 0.0f,
        secondaryColor.withAlpha(0.1f),
        bounds.getWidth(), bounds.getHeight(),
        false);
    g.setGradientFill(gradient);
    g.fillAll();

    // Grid pattern
    g.setColour(primaryColor.withAlpha(0.1f));
    float gridSize = 20.0f;
    for (float x = 0; x < bounds.getWidth(); x += gridSize)
    {
        g.drawVerticalLine(static_cast<int>(x), 0.0f, bounds.getHeight());
    }
    for (float y = 0; y < bounds.getHeight(); y += gridSize)
    {
        g.drawHorizontalLine(static_cast<int>(y), 0.0f, bounds.getWidth());
    }
}

void TunerComponent::drawTunerDisplay(juce::Graphics &g)
{
    auto bounds = getLocalBounds().toFloat();
    auto center = bounds.getCentre();

    // Main tuner circle
    float circleRadius = juce::jmin(bounds.getWidth(), bounds.getHeight()) * 0.3f;
    juce::Rectangle<float> tunerCircle(center.x - circleRadius, center.y - circleRadius,
                                       circleRadius * 2.0f, circleRadius * 2.0f);

    // Draw outer ring
    g.setColour(primaryColor.withAlpha(0.5f));
    g.drawEllipse(tunerCircle, 3.0f);

    // Draw frequency display
    if (currentFrequency > 0.0f)
    {
        // Note name
        int noteIndex = static_cast<int>(std::round(currentNote)) % 12;
        juce::String noteName = noteNames[noteIndex];

        g.setColour(isInTune ? juce::Colours::green : accentColor);
        g.setFont(juce::Font(48.0f, juce::Font::bold));
        g.drawText(noteName, tunerCircle, juce::Justification::centred);

        // Frequency
        g.setColour(primaryColor);
        g.setFont(juce::Font(16.0f));
        juce::String freqText = juce::String(currentFrequency, 1) + " Hz";
        g.drawText(freqText, tunerCircle.removeFromBottom(30), juce::Justification::centred);

        // Cents display
        juce::String centsText = juce::String(cents, 1) + " cents";
        g.setColour(cents > 0 ? juce::Colours::red : juce::Colours::blue);
        g.drawText(centsText, tunerCircle.removeFromTop(30), juce::Justification::centred);

        // Visual indicator
        float indicatorAngle = (cents / 50.0f) * juce::MathConstants<float>::pi;
        juce::Path indicatorPath;
        indicatorPath.addArc(tunerCircle.getX(), tunerCircle.getY(),
                             tunerCircle.getWidth(), tunerCircle.getHeight(),
                             -juce::MathConstants<float>::halfPi + indicatorAngle - 0.1f,
                             -juce::MathConstants<float>::halfPi + indicatorAngle + 0.1f, true);

        g.setColour(isInTune ? juce::Colours::green : accentColor);
        g.strokePath(indicatorPath, juce::PathStrokeType(4.0f));
    }
    else
    {
        g.setColour(primaryColor.withAlpha(0.3f));
        g.setFont(juce::Font(24.0f));
        g.drawText("NO SIGNAL", tunerCircle, juce::Justification::centred);
    }
}

void TunerComponent::drawHolographicEffects(juce::Graphics &g)
{
    auto bounds = getLocalBounds().toFloat();

    // Pulse animation
    float pulseRadius = 50.0f + pulseAnimation * 20.0f;
    auto center = bounds.getCentre();

    // Holographic rings
    for (int i = 0; i < 3; ++i)
    {
        float ringRadius = pulseRadius + i * 30.0f;
        float alpha = (1.0f - static_cast<float>(i) / 3.0f) * visualIntensity * 0.3f;

        g.setColour(accentColor.withAlpha(alpha));
        g.drawEllipse(center.x - ringRadius, center.y - ringRadius,
                      ringRadius * 2.0f, ringRadius * 2.0f, 2.0f);
    }

    // Scanning lines
    if (visualIntensity > 0.1f)
    {
        g.setColour(primaryColor.withAlpha(visualIntensity * 0.5f));
        for (int i = 0; i < 5; ++i)
        {
            float y = bounds.getHeight() * (static_cast<float>(i) / 4.0f);
            g.drawHorizontalLine(static_cast<int>(y), 0.0f, bounds.getWidth());
        }
    }
}

void TunerComponent::resized()
{
    // Component resized - update any layout-specific code here
}

void TunerComponent::timerCallback()
{
    // Update animations
    pulseAnimation += 0.1f;
    if (pulseAnimation > 1.0f)
        pulseAnimation = 0.0f;

    repaint();
}
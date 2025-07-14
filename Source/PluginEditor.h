#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "FuturisticUI.h"

class AIImagerAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    AIImagerAudioProcessorEditor(AIImagerAudioProcessor &);
    ~AIImagerAudioProcessorEditor() override;

    void paint(juce::Graphics &) override;
    void resized() override;

private:
    AIImagerAudioProcessor &audioProcessor;
    std::unique_ptr<FuturisticUI> futuristicUI;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AIImagerAudioProcessorEditor)
};
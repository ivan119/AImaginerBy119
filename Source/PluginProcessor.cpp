#include "PluginProcessor.h"
#include "PluginEditor.h"

AIImagerAudioProcessor::AIImagerAudioProcessor()
    : AudioProcessor(BusesProperties()
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      parameters(*this, nullptr, "Parameters", createParameterLayout()),
      tuner(std::make_unique<TunerComponent>())
{
    aiIntensity = dynamic_cast<juce::AudioParameterFloat *>(parameters.getParameter("aiIntensity"));
    futureResonance = dynamic_cast<juce::AudioParameterFloat *>(parameters.getParameter("futureResonance"));
    quantumDepth = dynamic_cast<juce::AudioParameterFloat *>(parameters.getParameter("quantumDepth"));
    neuralEnhancement = dynamic_cast<juce::AudioParameterBool *>(parameters.getParameter("neuralEnhancement"));
    holographicMode = dynamic_cast<juce::AudioParameterBool *>(parameters.getParameter("holographicMode"));

    audioProcessor = std::make_unique<AudioProcessor>();
}

AIImagerAudioProcessor::~AIImagerAudioProcessor() = default;

juce::AudioProcessorValueTreeState::ParameterLayout AIImagerAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "aiIntensity", "AI Intensity", 0.0f, 1.0f, 0.5f,
        juce::AudioParameterFloatAttributes().withLabel("AI %")));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "futureResonance", "Future Resonance", 0.0f, 1.0f, 0.3f,
        juce::AudioParameterFloatAttributes().withLabel("Resonance")));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "quantumDepth", "Quantum Depth", 0.0f, 1.0f, 0.7f,
        juce::AudioParameterFloatAttributes().withLabel("Quantum")));

    params.push_back(std::make_unique<juce::AudioParameterBool>(
        "neuralEnhancement", "Neural Enhancement", false));

    params.push_back(std::make_unique<juce::AudioParameterBool>(
        "holographicMode", "Holographic Mode", false));

    return {params.begin(), params.end()};
}

const juce::String AIImagerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AIImagerAudioProcessor::acceptsMidi() const { return false; }
bool AIImagerAudioProcessor::producesMidi() const { return false; }
bool AIImagerAudioProcessor::isMidiEffect() const { return false; }
double AIImagerAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int AIImagerAudioProcessor::getNumPrograms() { return 1; }
int AIImagerAudioProcessor::getCurrentProgram() { return 0; }
void AIImagerAudioProcessor::setCurrentProgram(int index) { juce::ignoreUnused(index); }
const juce::String AIImagerAudioProcessor::getProgramName(int index)
{
    juce::ignoreUnused(index);
    return {};
}
void AIImagerAudioProcessor::changeProgramName(int index, const juce::String &newName) { juce::ignoreUnused(index, newName); }

void AIImagerAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32>(samplesPerBlock);
    spec.numChannels = static_cast<juce::uint32>(juce::jmax(getTotalNumInputChannels(), getTotalNumOutputChannels()));

    inputGain.prepare(spec);
    outputGain.prepare(spec);

    if (audioProcessor)
        audioProcessor->prepareToPlay(sampleRate, samplesPerBlock);

    if (tuner)
        tuner->prepareToPlay(sampleRate, samplesPerBlock);
}

void AIImagerAudioProcessor::releaseResources()
{
    if (audioProcessor)
        audioProcessor->releaseResources();

    if (tuner)
        tuner->releaseResources();
}

bool AIImagerAudioProcessor::isBusesLayoutSupported(const BusesLayout &busesLayout) const
{
    if (busesLayout.getMainOutputChannelSet() != juce::AudioChannelSet::mono() && busesLayout.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (busesLayout.getMainOutputChannelSet() != busesLayout.getMainInputChannelSet())
        return false;

    return true;
}

void AIImagerAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // Process audio through AI algorithms
    if (audioProcessor)
        audioProcessor->processBlock(buffer, midiMessages);

    // Update tuner with audio data
    if (tuner)
        tuner->processAudio(buffer);

    // Apply futuristic effects based on parameters
    auto *channelData = buffer.getWritePointer(0);
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        float input = channelData[sample];

        // AI Intensity processing
        if (aiIntensity && aiIntensity->get() > 0.0f)
        {
            float aiAmount = aiIntensity->get();
            input = input * (1.0f + aiAmount * 0.5f);
        }

        // Future Resonance
        if (futureResonance && futureResonance->get() > 0.0f)
        {
            float resonance = futureResonance->get();
            input = input * (1.0f + resonance * 0.3f);
        }

        // Quantum Depth
        if (quantumDepth && quantumDepth->get() > 0.0f)
        {
            float quantum = quantumDepth->get();
            input = input * (1.0f + quantum * 0.2f);
        }

        // Neural Enhancement
        if (neuralEnhancement && neuralEnhancement->get())
        {
            input = std::tanh(input * 1.5f);
        }

        // Holographic Mode
        if (holographicMode && holographicMode->get())
        {
            input = input * (1.0f + 0.1f * std::sin(static_cast<float>(sample) * 0.01f));
        }

        channelData[sample] = juce::jlimit(-1.0f, 1.0f, input);
    }
}

bool AIImagerAudioProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor *AIImagerAudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor(*this);
}

void AIImagerAudioProcessor::getStateInformation(juce::MemoryBlock &destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void AIImagerAudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new AIImagerAudioProcessor();
}
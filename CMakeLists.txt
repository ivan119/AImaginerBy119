cmake_minimum_required(VERSION 3.15)
project(AIImager VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add JUCE as a subdirectory
add_subdirectory(JUCE)

# Create the VST3 plugin
juce_add_plugin(AIImager
    COMPANY_NAME "FutureAudio"
    PLUGIN_NAME "AI Imager"
    COMPANY_WEBSITE "https://futureaudio.com"
    COMPANY_EMAIL "contact@futureaudio.com"
    VST3_CATEGORIES "Fx"
    AU_MAIN_TYPE "kAudioUnitType_Effect"
    AU_SANDBOX_SAFE 1
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    VST3_CATEGORIES "Fx"
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "AI Imager"
)

# Add source files
target_sources(AIImager
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp
        Source/AudioProcessor.cpp
        Source/TunerComponent.cpp
        Source/FuturisticUI.cpp
)

# Add JUCE modules
target_compile_definitions(AIImager
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(AIImager
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_gui_extra
        juce::juce_dsp
        juce::juce_opengl
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
) 
cmake_minimum_required(VERSION 3.15)
project(juce_fft_equalizer VERSION 0.0.1)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(JUCE
  GIT_REPOSITORY    https://github.com/juce-framework/JUCE.git
  GIT_TAG           7.0.3
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(JUCE)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DFFT_DATA_LOGGING")

juce_add_gui_app(juce_fft_equalizer PRODUCT_NAME "FFT Equalizer")
juce_generate_juce_header(juce_fft_equalizer)

target_sources(juce_fft_equalizer 
    PRIVATE 
        Source/Main.cpp 
        Source/MainComponent.cpp 
        Source/AudioPlayer.cpp
        Source/Equalizer.cpp
)

target_compile_definitions(juce_fft_equalizer
    PRIVATE
        JUCE_STRICT_REFCOUNTEDPOINTER=1
        JUCE_USE_MP3AUDIOFORMAT=1
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:juce_fft_equalizer,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:juce_fft_equalizer,JUCE_VERSION>"
        JUCE_DISPLAY_SPLASH_SCREEN=0
)

target_link_libraries(juce_fft_equalizer
    PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

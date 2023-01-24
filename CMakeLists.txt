# Автор: Джумагельдиев С.А.
# Ответственный: Полевой Д.В.

cmake_minimum_required(VERSION 3.15)
project(juce_fft_equalizer VERSION 1.1.0)

set(EQ_SRC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

# Добавляет логгирование данных FFT при сборке с Debug
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DFFT_DATA_LOGGING")

include(CPM.cmake)
CPMAddPackage("gh:juce-framework/JUCE#7.0.3")

find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_OUTPUT_LANGUAGE Russian)
    set(DOXYGEN_HTML_COLORSTYLE LIGHT)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_LATEX YES)
    set(DOXYGEN_GENERATE_RTF YES)
    set(DOXYGEN_EXTRACT_PRIVATE YES)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs)
    doxygen_add_docs(docs ${EQ_SRC} ALL)
endif()

juce_add_gui_app(juce_fft_equalizer PRODUCT_NAME "FFT Equalizer")
juce_generate_juce_header(juce_fft_equalizer)

target_sources(juce_fft_equalizer 
    PRIVATE 
        ${EQ_SRC}/Main.cc
        ${EQ_SRC}/MainComponent.cc 
        ${EQ_SRC}/AudioPlayer.cc
        ${EQ_SRC}/Equalizer.cc
        # ${EQ_SRC}/FFT.h
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

install(TARGETS juce_fft_equalizer DESTINATION /bin)

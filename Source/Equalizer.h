#pragma once
#include <JuceHeader.h>

class Equalizer {
   public:
    Equalizer();
    ~Equalizer();

    /**
     * @brief Устанавливает громкость 
     * 
     * @param new_volume громкость от 0 до 100
     */
    void setVolume(float new_level);

    /**
     * @brief Возвращает громкость плеера
     * 
     * @return double - громкость от 0 до 100
     */
    float getVolume() { return level; };

    void processBuffer(const juce::AudioSourceChannelInfo &filledBuffer);
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);

   private:
    static constexpr auto fftOrder = 10;
    static constexpr auto fftSize = 1 << fftOrder;
    juce::dsp::FFT forwardFFT;
    std::array<float, fftSize> fifo;
    std::array<float, fftSize*2> fftData;
    size_t fifoIndex = 0;
    bool nextFFTBlockReady = false;
    float level = 1.0;
    double sample_rate;
    int samples_per_block_expected;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Equalizer)
};
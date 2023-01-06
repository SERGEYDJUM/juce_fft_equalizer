#pragma once
#include <JuceHeader.h>

class Equalizer {
   public:
    Equalizer();
    void setup(float new_sample_rate);
    void updateBand(int low, int high, float gain);
    void equalizeBuffer(const juce::AudioSourceChannelInfo &filledBuffer);

    static int constexpr fft_order = 10;
    static int constexpr fft_size = 1 << fft_order;
   private:
    juce::dsp::FFT fft;
    float sample_rate;
    float fundamental_harmonic;
    std::array<float, 25000> freq_gain;
    std::array<float, fft_size * 2> fft_data;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Equalizer)
};
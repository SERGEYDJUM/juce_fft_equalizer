#pragma once
#include <JuceHeader.h>
#include "fft.h"

class Equalizer {
   public:
    Equalizer(int fft_order);
    void updateSampleRate(float new_sample_rate);
    void updateBand(int low, int high, float gain);
    void equalizeBuffer(const juce::AudioSourceChannelInfo &filledBuffer);
    
   private:
    FFT fft;
    int block_size;
    float sample_rate;
    float fundamental_harmonic;
    std::array<float, 25000> harmonic_gain;
};
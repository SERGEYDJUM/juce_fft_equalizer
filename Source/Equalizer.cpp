#include "Equalizer.h"

void Equalizer::setup(float new_sample_rate) {
    sample_rate = new_sample_rate;
    fundamental_harmonic = sample_rate/fft_size;
    freq_gain.fill(1.0f);
    fft_data.fill(0.0f);
}

Equalizer::Equalizer() : fft{fft_order} {}

void Equalizer::updateBand(int low, int high, float gain) {
    for (int i = low; i <= high; i++) {
        freq_gain[i] = gain;
    }
}

void Equalizer::equalizeBuffer(const juce::AudioSourceChannelInfo& filledBuffer) {
    for (auto channel = 0; channel < filledBuffer.buffer->getNumChannels(); ++channel) {
        auto* buffer = filledBuffer.buffer->getWritePointer(channel, filledBuffer.startSample);
        juce::FloatVectorOperations::copy(fft_data.data(), buffer, filledBuffer.numSamples);

        fft.performRealOnlyForwardTransform(fft_data.data(), true);
        for (size_t i = 1; i < fft_size/2; ++i) {
            float gain = freq_gain[static_cast<size_t>(fundamental_harmonic * i - fundamental_harmonic/2)];
            fft_data[i*2] *= 1.0f + gain/10.0f;
            fft_data[i*2 + 1] *= 1.0f + gain/10.0f;
        }
        fft.performRealOnlyInverseTransform(fft_data.data());

        juce::FloatVectorOperations::copy(buffer, fft_data.data(), filledBuffer.numSamples);
    }
}

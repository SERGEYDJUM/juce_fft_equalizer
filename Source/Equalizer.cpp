#include "Equalizer.h"

Equalizer::Equalizer(int fft_order) : fft{fft_order}, block_size{1 << fft_order} {
    harmonic_gain.fill(1.0f);
    sample_rate = 48000.0f;
}

void Equalizer::updateSampleRate(float new_sample_rate) {
    sample_rate = new_sample_rate;
    fundamental_harmonic = sample_rate/block_size;
}

void Equalizer::updateBand(int low, int high, float gain) {
    for (int i = low; i <= high; i++) {
        harmonic_gain[i] = 1.0f + gain/10.0f;
    }
}

void Equalizer::equalizeBuffer(const juce::AudioSourceChannelInfo& filledBuffer) {
    for (auto channel = 0; channel < filledBuffer.buffer->getNumChannels(); ++channel) {
        auto* buffer = filledBuffer.buffer->getWritePointer(channel, filledBuffer.startSample);

        fft.read_block(buffer);
        fft.perform_forward();

        for (size_t i = 1; i < block_size/2; ++i) {
            auto harmonic = static_cast<size_t>(fundamental_harmonic * i - fundamental_harmonic/2);
            if (harmonic >= 25000) break;
            float gain = harmonic_gain[harmonic];
            fft[i] *= gain;
        }

        fft.perform_inverse();
        fft.write_block(buffer);
    }
}
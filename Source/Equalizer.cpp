#include "Equalizer.h"

Equalizer::Equalizer() : forwardFFT{fftOrder} {}

Equalizer::~Equalizer() {}

void Equalizer::setVolume(float new_level) {
    jassert(new_level >= 0.0 && new_level <= 100.0);
    level = new_level;
}

void Equalizer::processBuffer(const juce::AudioSourceChannelInfo& filledBuffer) {
    for (auto channel = 0; channel < filledBuffer.buffer->getNumChannels(); ++channel)
    {
        auto* buffer = filledBuffer.buffer->getWritePointer(channel, filledBuffer.startSample);

        for (auto sample = 0; sample < filledBuffer.numSamples; ++sample)
        {
            buffer[sample]  = buffer[sample] * (level/100);
        }
    }
}

void Equalizer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    sample_rate = sampleRate;
    samples_per_block_expected = samplesPerBlockExpected;
}

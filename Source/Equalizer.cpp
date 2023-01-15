#include "Equalizer.h"

#ifdef FFT_DATA_LOGGING
#include <fstream>
#endif


Equalizer::Equalizer(unsigned int fft_order) : fft{fft_order}, block_size{1u << fft_order} {
    harmonic_gain.fill(1.0f);
    sample_rate = 48000.0f;
}

void Equalizer::updateSampleRate(float new_sample_rate) {
    sample_rate = new_sample_rate;
    fundamental_harmonic = sample_rate / block_size;
}

void Equalizer::updateBand(int low, int high, float gain) {
    for (int i = low; i <= high; i++) {
        harmonic_gain[i] = 1.0f + gain / 10.0f;
    }
}

void Equalizer::equalizeBuffer(const juce::AudioSourceChannelInfo& filledBuffer) {
    for (auto channel = 0; channel < filledBuffer.buffer->getNumChannels(); ++channel) {
        auto* buffer = filledBuffer.buffer->getWritePointer(channel, filledBuffer.startSample);
        fft.read_block(buffer);
        fft.perform_forward();

#ifdef FFT_DATA_LOGGING
        std::ofstream eq_data_logger;
        if (log_next_block) {
            eq_data_logger.open("fft_log_" + std::to_string(log_file_index) + ".csv");
            ++log_file_index;
            eq_data_logger << "harmonic,magnitude,phase\n";
            eq_data_logger << "0," + std::to_string(fft[0].real()) + ",0.0\n";
        }
#endif

        for (size_t i = 1; i < block_size / 2; ++i) {
            auto harmonic = static_cast<size_t>(fundamental_harmonic * i - fundamental_harmonic / 2);
            if (harmonic >= 23000) break;
            float real = fft[i].real();
            float imag = fft[i].imag();
            float magnitude = sqrtf(real*real + imag*imag) * harmonic_gain[harmonic];
            float phase = atan2(imag, real);
            fft[i] = std::polar(magnitude, phase);
            fft[block_size - i] = std::conj(fft[i]);

#ifdef FFT_DATA_LOGGING
            if (log_next_block) {
                eq_data_logger << std::to_string(harmonic) + ',' + std::to_string(magnitude) + ',' + std::to_string(phase) + '\n';
            }
#endif
        }

#ifdef FFT_DATA_LOGGING 
        log_next_block = false;
        eq_data_logger.flush();
        eq_data_logger.close();
#endif

        fft.perform_inverse();
        fft.write_block(buffer);
    }
}
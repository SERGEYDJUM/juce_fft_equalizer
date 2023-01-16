#include "Equalizer.h"

#ifdef FFT_DATA_LOGGING
#include <fstream>
#endif

Equalizer::Equalizer(unsigned int fft_order) 
    : fft{fft_order}, block_size{1u << fft_order}, sample_rate{0}, fundamental_harmonic{0} {
    harmonic_gain.fill(1.0f);
}

void Equalizer::updateSampleRate(float new_sample_rate) {
    sample_rate = new_sample_rate;
    fundamental_harmonic = sample_rate / block_size + 2;
}

void Equalizer::updateBand(int low, int high, float gain) {
    for (int i = low; i <= high; i++) {
        harmonic_gain[i] = 1.0f + gain / 10.0f;
    }

#ifdef FFT_DATA_LOGGING
    std::ofstream band_data_log;
    band_data_log.open("last_band_data.csv");
    band_data_log << "harmonic,gain" << std::endl;
    for (int i = 0; i < harmonic_gain.size(); i++) {
        band_data_log << i << ',' << harmonic_gain[i] << std::endl;
    }
    band_data_log.flush();
    band_data_log.close();
#endif
}

void Equalizer::equalizeBuffer(const juce::AudioSourceChannelInfo& filledBuffer) {
    for (auto channel = 0; channel < filledBuffer.buffer->getNumChannels(); ++channel) {
        auto* buffer = filledBuffer.buffer->getWritePointer(channel, filledBuffer.startSample);
        fft.read_block(buffer);
        fft.perform_forward();

        for (size_t i = 1; i < block_size / 2; ++i) {
            auto harmonic = static_cast<size_t>(fundamental_harmonic * i - fundamental_harmonic / 2);
            if (harmonic >= 23000) break;
            float real = fft[i].real();
            float imag = fft[i].imag();
            float magnitude = sqrtf(real * real + imag * imag);
            float phase = atan2(imag, real);
            fft[i] = std::polar(magnitude * harmonic_gain[harmonic], phase);
            fft[block_size - i] = std::conj(fft[i]);
        }

#ifdef FFT_DATA_LOGGING
        if (log_next_block) {
            std::ofstream eq_data_log;
            eq_data_log.open("fft_log_" + std::to_string(log_file_index) + ".csv");
            eq_data_log << "#sample_rate=" << sample_rate << ", fft_size=" << block_size << std::endl;
            eq_data_log << "harmonic,magnitude,phase" << std::endl;
            eq_data_log << "0," + std::to_string(fft[0].real()) + ",0.0" << std::endl;

            for (size_t i = 1; i <= block_size / 2; ++i) {
                auto harmonic = static_cast<size_t>(fundamental_harmonic * i - fundamental_harmonic / 2);
                float real = fft[i].real();
                float imag = fft[i].imag();
                eq_data_log << std::to_string(harmonic) + ',' 
                    + std::to_string(sqrtf(real * real + imag * imag)) 
                    + ',' + std::to_string(atan2(imag, real)) 
                    << std::endl;
            }

            eq_data_log.flush();
            eq_data_log.close();
            log_next_block = false;
            ++log_file_index;
        }
#endif
        fft.perform_inverse();
        fft.write_block(buffer);
    }
}
#include "Equalizer.h"

#ifdef FFT_DATA_LOGGING
#include <fstream>
#endif

Equalizer::Equalizer(unsigned int fft_order)
    : fft{fft_order},
      //   fft_gains{10},
      block_size{1u << fft_order},
      sample_rate{0},
      base_freq{0} {
    harmonic_gain.fill(1.0f);

    // Данные взяты из ISO 266
    unsigned int band_centers[] = {16,   31,   63,   125,  250,  500,
                                   1000, 2000, 4000, 8000, 16000};
    unsigned band_len = 11;
    for (size_t i = 0; i < 11; i++) {
        unsigned int left = band_centers[i] - band_len / 2;
        unsigned int right = band_centers[i] + band_len / 2;
        bands[i] = Band{band_centers[i], left, right, 1.0f};
        band_len *= 2;
    }
}

void Equalizer::updateSampleRate(float new_sample_rate) {
    sample_rate = new_sample_rate;
    base_freq = sample_rate / block_size;

    // Я не знаю, почему так вышло, но так надо, чтобы частоты
    // более-менее правильно определялись
    base_freq += 2;
}

void Equalizer::updateBand(unsigned int band, float gain) {
    bands[band].gain = gain;
    _generate_harmonic_gain();
}

void Equalizer::_generate_harmonic_gain() {
    for (size_t i = 0; i < 11; i++) {
        if (harmonic_gain[bands[i].center] != bands[i].gain) {
            for (unsigned int j = bands[i].left; j < bands[i].right; j++) {
                harmonic_gain[j] = bands[i].gain;
            }
        }
    }

    // // Мои попытки сгладить коэффициенты
    // for (unsigned int j = 0; j < 20; j++) {
    //     fft_gains.read_block(harmonic_gain.data(), 1024*j);
    //     fft_gains.perform_forward();
    //     for (size_t i = 16; i < 512; i++) {
    //         fft_gains[1024 - i] = 0;
    //         fft_gains[i] = 0;
    //     }
    //     fft_gains.perform_inverse();
    //     fft_gains.write_block(harmonic_gain.data(), 1024*j);
    // }

    // for (size_t i = 0; i < harmonic_gain.size(); i++)
    //     if (harmonic_gain[i] < 0) harmonic_gain[i] = 0;

#ifdef FFT_DATA_LOGGING
    std::ofstream band_data_log;
    band_data_log.open("last_band_data.csv");
    band_data_log << "frequency,gain" << std::endl;
    for (int i = 0; i < harmonic_gain.size(); i++) {
        band_data_log << i << ',' << harmonic_gain[i] << std::endl;
    }
    band_data_log.flush();
    band_data_log.close();
#endif
}

void Equalizer::equalizeBuffer(const AudioSourceChannelInfo& filledBuffer) {
    auto channels = filledBuffer.buffer->getNumChannels();
    for (auto channel = 0; channel < channels; ++channel) {
        auto* buffer = filledBuffer.buffer->getWritePointer(
            channel, filledBuffer.startSample);
        fft.read_block(buffer);
        fft.perform_forward();

        for (size_t i = 1; i < block_size / 2; ++i) {
            // Частота i-го слота FFT
            auto freq = static_cast<size_t>(base_freq * i - base_freq / 2);

            // Никто не услышит, да и полосы там не определены
            if (freq >= 23000) break;

            float real = fft[i].real();
            float imag = fft[i].imag();
            float magnitude = sqrtf(real * real + imag * imag);
            float phase = atan2(imag, real);
            fft[i] = std::polar(magnitude * harmonic_gain[freq], phase);

            // Вторая половина блока - это комплексно сопряженные числа
            fft[block_size - i] = std::conj(fft[i]);
        }

#ifdef FFT_DATA_LOGGING
        if (log_next_block) {
            std::ofstream eq_data_log;
            eq_data_log.open("fft_audio_latest.csv");
            eq_data_log << "#sample_rate=" << sample_rate
                        << ", fft_size=" << block_size << std::endl;
            eq_data_log << "frequency,magnitude,phase" << std::endl;
            eq_data_log << "0," + std::to_string(fft[0].real()) + ",0.0"
                        << std::endl;

            for (size_t i = 1; i <= block_size / 2; ++i) {
                auto harmonic =
                    static_cast<size_t>(base_freq * i - base_freq / 2);
                float real = fft[i].real();
                float imag = fft[i].imag();
                eq_data_log
                    << std::to_string(harmonic) + ',' +
                           std::to_string(sqrtf(real * real + imag * imag)) +
                           ',' + std::to_string(atan2(imag, real))
                    << std::endl;
            }

            eq_data_log.flush();
            eq_data_log.close();
            log_next_block = false;
        }
#endif
        fft.perform_inverse();
        fft.write_block(buffer);
    }
}
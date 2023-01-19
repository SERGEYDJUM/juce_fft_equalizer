//! @file Equalizer.cc
//! @authors Джумагельдиев С.А.
//! @note Ответственный: Полевой Д.В.
//! @brief Файл с определением класса Equalizer

#include "Equalizer.h"

#ifdef FFT_DATA_LOGGING
#include <fstream>
#endif

Equalizer::Equalizer(unsigned int fft_order)
    : fft_{fft_order},
      //   fft_gains_{10},
      block_size_{1u << fft_order},
      sample_rate_{0},
      base_freq_{0} {
    harmonic_gain_.fill(1.0f);

    // Данные взяты из ISO 266
    unsigned int band_centers[] = {16,   31,   63,   125,  250,  500,
                                   1000, 2000, 4000, 8000, 16000};
    unsigned band_len = 11;
    for (size_t i = 0; i < 11; i++) {
        unsigned int left = band_centers[i] - band_len / 2;
        unsigned int right = band_centers[i] + band_len / 2;
        bands_[i] = Band{band_centers[i], left, right, 1.0f};
        band_len *= 2;
    }
}

void Equalizer::updateSampleRate(float new_sample_rate) {
    if (new_sample_rate < 0)
        throw std::domain_error("Sample rate is out of range");

    sample_rate_ = new_sample_rate;
    base_freq_ = sample_rate_ / block_size_;

    // Я не знаю, почему так вышло, но так надо, чтобы частоты
    // более-менее правильно определялись
    base_freq_ += 2;
}

void Equalizer::updateBand(unsigned int band, float gain) {
    if (band > 10) throw std::domain_error("Band is out of range");
    if (gain > 2 || gain < 0) throw std::domain_error("Gain is out of range");

    bands_[band].gain = gain;
    _generate_harmonic_gain();
}

void Equalizer::_generate_harmonic_gain() {
    for (size_t i = 0; i < 11; i++) {
        if (harmonic_gain_[bands_[i].center] != bands_[i].gain) {
            for (unsigned int j = bands_[i].left; j < bands_[i].right; j++) {
                harmonic_gain_[j] = bands_[i].gain;
            }
        }
    }

    // // Мои попытки сгладить коэффициенты
    // for (unsigned int j = 0; j < 20; j++) {
    //     fft_gains_.readBlock(harmonic_gain_.data(), 1024*j);
    //     fft_gains_.performForward();
    //     for (size_t i = 16; i < 512; i++) {
    //         fft_gains_[1024 - i] = 0;
    //         fft_gains_[i] = 0;
    //     }
    //     fft_gains_.performInverse();
    //     fft_gains_.writeBlock(harmonic_gain_.data(), 1024*j);
    // }

    // for (size_t i = 0; i < harmonic_gain_.size(); i++)
    //     if (harmonic_gain_[i] < 0) harmonic_gain_[i] = 0;

#ifdef FFT_DATA_LOGGING
    std::ofstream band_data_log;
    band_data_log.open("last_band_data.csv");
    band_data_log << "frequency,gain" << std::endl;
    for (int i = 0; i < harmonic_gain_.size(); i++) {
        band_data_log << i << ',' << harmonic_gain_[i] << '\n';
    }
    band_data_log.close();
#endif
}

void Equalizer::equalizeBuffer(const AudioSourceChannelInfo& filledBuffer) {
    auto channels = filledBuffer.buffer->getNumChannels();
    for (auto channel = 0; channel < channels; ++channel) {
        auto* buffer = filledBuffer.buffer->getWritePointer(
            channel, filledBuffer.startSample);
        fft_.readBlock(buffer);
        fft_.performForward();

        for (unsigned int i = 1; i < block_size_ / 2; ++i) {
            // Частота i-го слота FFT
            auto freq =
                static_cast<unsigned int>(base_freq_ * i - base_freq_ / 2);

            // Никто не услышит, да и полосы там не определены
            if (freq >= 23000) break;

            float real = fft_[i].real();
            float imag = fft_[i].imag();
            float magnitude = sqrtf(real * real + imag * imag);
            float phase = atan2(imag, real);
            fft_[i] = std::polar(magnitude * harmonic_gain_[freq], phase);

            // Вторая половина блока - это комплексно сопряженные числа
            fft_[block_size_ - i] = std::conj(fft_[i]);
        }

#ifdef FFT_DATA_LOGGING
        if (log_next_block) {
            std::ofstream eq_data_log;
            eq_data_log.open("fft_audio_latest.csv");
            eq_data_log << "#sample_rate_=" << sample_rate_
                        << ", fft_size=" << block_size_ << '\n';
            eq_data_log << "frequency,magnitude,phase\n";
            eq_data_log << "0," + std::to_string(fft_[0].real()) + ",0.0\n";

            for (size_t i = 1; i <= block_size_ / 2; ++i) {
                auto harmonic =
                    static_cast<size_t>(base_freq_ * i - base_freq_ / 2);
                float real = fft_[i].real();
                float imag = fft_[i].imag();
                eq_data_log << std::to_string(harmonic) + ',' +
                           std::to_string(sqrtf(real * real + imag * imag)) +
                           ',' + std::to_string(atan2(imag, real)) + '\n';
            }
            
            eq_data_log.close();
            log_next_block = false;
        }
#endif
        fft_.performInverse();
        fft_.writeBlock(buffer);
    }
}
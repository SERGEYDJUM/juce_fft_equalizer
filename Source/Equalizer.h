#pragma once
#include <JuceHeader.h>

#include "fft.h"

/// @brief FFT-эквалайзер с 11 полосами.
class Equalizer {
   public:
    /// @brief Консруирует эквалайзер.
    /// @param fft_order порядок размера буффера.
    Equalizer(unsigned int fft_order);

    /// @brief Перенастраивает эквалайзер для нового аудиофайла.
    /// @param new_sample_rate частота дискретизации файла.
    void updateSampleRate(float new_sample_rate);

    /// @brief Обновляет коэффициенты для частотного диапазона эквалайзера.
    /// @param band номер полосы.
    /// @param gain коэффициент от 0 до 2.
    void updateBand(unsigned int band, float gain);

    /// @brief Обрабатывает очередной аудиобуффер.
    /// @param filledBuffer буффер с любым количеством каналов.
    void equalizeBuffer(const AudioSourceChannelInfo &filledBuffer);

#ifdef FFT_DATA_LOGGING
    bool log_next_block = false;
    size_t log_file_index = 0;
#endif

   private:
    // Создаёт сглаженный массив кэффициентов по полосам.
    void _generate_harmonic_gain();

    // Хранит данные о полосе
    struct Band {
        unsigned int center;
        unsigned int left;
        unsigned int right;
        float gain;
    };

    Band bands[11];

    // Должна соответствовать частоте блока fft с индексом 1, а на практике
    // требует калибровки
    float base_freq;
    unsigned int block_size;
    float sample_rate;
    FFT fft;
    // Коэффициенты (от 0 до 2) для каждой целой частоты
    std::array<float, 23000> harmonic_gain;
};
//! @file Equalizer.h
//! @authors Джумагельдиев С.А.
//! @note Ответственный: Полевой Д.В.
//! @brief Заголовочный файл эквалайзера
//! @todo Сглаживание harmonic_gain_

#pragma once
#include <JuceHeader.h>

#include "FFT.h"

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
    /// @brief Следующий обработанный блок (в спектральном домене) будет записан
    /// в файл
    bool log_next_block = false;
#endif

   private:
    /// @brief Создаёт массив коэффициентов по полосам
    void _generate_harmonic_gain();

    /// @brief Хранит данные о полосе
    struct Band {

        /// @brief Центральная частота полосы
        unsigned int center;

        /// @brief Левая частотная граница
        unsigned int left;

        /// @brief Правая частотная граница
        unsigned int right;
        
        /// @brief Коэффициент-множитель полосы
        float gain;
    };

    /// @brief Хранит все полосы
    Band bands_[11];

    /// @brief Должна соответствовать частоте блока fft с индексом 1, а на
    /// практике требует калибровки
    float base_freq_;

    /// @brief Размер одного канала буфера и размер блока FFT
    unsigned int block_size_;

    /// @brief Частота дискретизации
    float sample_rate_;

    /// @brief Объект FFT для аудио
    FFT fft_;

    // /// @brief FFT для сглаживания полос
    // FFT fft_gains_;

    /// @brief Коэффициенты (от 0 до 2) для каждой целой частоты
    std::array<float, 23000> harmonic_gain_;
};
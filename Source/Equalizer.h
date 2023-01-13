#pragma once
#include <JuceHeader.h>

#include "fft.h"

/// @brief Класс FFT-эквалайзера.
class Equalizer {
   public:
    /// @brief Консруирует эквалайзер.
    /// @param fft_order порядок размера буффера.
    Equalizer(int fft_order);


    /// @brief Перенастраивает эквалайзер для нового аудиофайла.
    /// @param new_sample_rate частота дискретизации файла.
    void updateSampleRate(float new_sample_rate);

    /// @brief Обновляет коэффициенты для частотного диапазона.
    /// @param low левая граница диапазона.
    /// @param high правая граница диапазона.
    /// @param gain коэффициент от -10 до +10 в децибелах
    void updateBand(int low, int high, float gain);


    /// @brief Обрабатывает очередной аудиобуффер. 
    /// @param filledBuffer буффер с любым количеством каналов.
    void equalizeBuffer(const juce::AudioSourceChannelInfo &filledBuffer);

   private:
    FFT fft;
    int block_size;
    float sample_rate;
    float fundamental_harmonic;
    std::array<float, 23000> harmonic_gain;
};
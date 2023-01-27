//! @file FFT.h
//! @authors Джумагельдиев С.А.
//! @note Ответственный: Полевой Д.В.
//! @brief Содержит класс FFT

#pragma once
// #include <JuceHeader.h>
#include <complex>
#include <valarray>

/// @brief Класс, реализующий алгоритмы прямого и обратного Быстрого
/// Преобразования Фурье.
class FFT {
   public:
    /// @brief Конструирует FFT с заданным размером.
    /// @param size_order_ порядок размера преобразуемого блока.
    FFT(unsigned int size_order_) : order_{size_order_}, size_{1u << order_} {
        fft_data_.resize(size_);
        index_reverse_table_.resize(size_);
        for (unsigned int i = 0; i < size_; i++) {
            index_reverse_table_[i] = indexReversed(i);
        }
    }

    /// @brief Производит прямое преобразование Фурье хранимого блока без
    /// нормализации.
    inline void performForward() noexcept { fft(); }

    /// @brief Производит обратное преобразование Фурье хранимого блока.
    inline void performInverse() noexcept {
        conjugateData();
        fft();
        conjugateData();
        fft_data_ /= static_cast<float>(size_);
    }

    /// @brief Загружает блок в память FFT.
    /// @param buffer одноканальный буфер размером с блок или больше.
    /// @param offset индекс элемента, с которого начать читать.
    inline void readBlock(float buffer[], unsigned int offset = 0) {
        for (unsigned int i = 0; i < size_; ++i) {
            fft_data_[i] = buffer[i + offset];
        }
    }

    /// @brief Выгружает блок FFT в буфер.
    /// @param buffer одноканальный буфер размером с блок или больше.
    /// @param offset индекс элемента, с которого начать писать.
    inline void writeBlock(float buffer[], unsigned int offset = 0) const {
        for (unsigned int i = 0; i < size_; ++i) {
            buffer[i + offset] = fft_data_[i].real();
        }
    }

    /// @brief Позволяет напрямую изменять элементы внутренней памяти FFT.
    /// @details Для справки: fft[0] - DC слот, хранит сумму сэмплов блока,
    /// fft[size_/2] - слот Найквиста, хранит данные для (частота дискретизации)
    /// / 2, для остальных fft[i] = std::conj(fft[size_ - i]).
    /// @param index номер элемента.
    /// @return ссылка на элемент.
    inline std::complex<float>& operator[](size_t index) {
        return fft_data_[index];
    }

   private:
    // /// @brief Рекурсивный aлгоритм Cooley–Tukey
    // /// @param inp_arr ссылка на массив
    // /// @details Источник: https://rosettacode.org/wiki/Fast_Fourier_transform
    // void fft(std::valarray<std::complex<float>>& inp_arr) {
    //     unsigned int _size = inp_arr.size_();
    //     if (_size <= 1) return;

    //     std::valarray<std::complex<float>> even = inp_arr[std::slice(0, _size
    //     / 2, 2)]; std::valarray<std::complex<float>> odd =
    //     inp_arr[std::slice(1, _size / 2, 2)];

    //     fft(even);
    //     fft(odd);

    //     for (unsigned int i = 0; i < _size / 2; ++i) {
    //         auto t = std::polar(1.0f, -6.283185307179586f * i / _size) *
    //         odd[i]; inp_arr[i] = even[i] + t; inp_arr[i + _size / 2] =
    //         even[i] - t;
    //     }
    // }

    /// @brief Итеративный aлгоритм Cooley–Tukey (Decimation-in-frequency)
    /// @details Источник: https://rosettacode.org/wiki/Fast_Fourier_transform
    void fft() {
        auto phiT = std::polar(1.0f, -3.141592741f / static_cast<float>(size_));
        unsigned int half_k = size_, k;
        while (half_k != 0) {
            k = half_k;
            half_k >>= 1;
            phiT *= phiT;
            std::complex<float> magT = 1.0f;
            for (unsigned int l = 0; l < half_k; ++l) {
                for (unsigned int a = l; a < size_; a += k) {
                    auto b = a + half_k;
                    auto temp = fft_data_[a] - fft_data_[b];
                    fft_data_[a] += fft_data_[b];
                    fft_data_[b] = temp * magT;
                }
                magT *= phiT;
            }
        }

        for (unsigned int i = 0; i < size_; ++i) {
            auto j = index_reverse_table_[i];
            if (i != j) std::swap(fft_data_[i], fft_data_[j]);
        }
    }

    /// @brief Даёт индекс в блоке FFT, обратный данному.
    /// @param x индекс.
    /// @return обратный индекс.
    inline unsigned int indexReversed(unsigned int x) noexcept {
        auto y = x;
        y = ((y >> 1) & 0x55555555) | ((y & 0x55555555) << 1);
        y = ((y >> 2) & 0x33333333) | ((y & 0x33333333) << 2);
        y = ((y >> 4) & 0x0F0F0F0F) | ((y & 0x0F0F0F0F) << 4);
        y = ((y >> 8) & 0x00FF00FF) | ((y & 0x00FF00FF) << 8);
        y = (y >> 16) | (y << 16);
        y >>= (32 - order_);
        return (y > x) ? y : x;
    }

    /// @brief Меняет все элементы блока FFT на сопряженные
    inline void conjugateData() noexcept {
        for (auto &el : fft_data_) {
            el = std::conj(el);
        }
    }

    /// @brief Порядок размера блока FFT
    const unsigned int order_;

    /// @brief Размер блока FFT
    const unsigned int size_;

    /// @brief Хранит обратные индексы для оптимизации
    std::valarray<unsigned int> index_reverse_table_;

    /// @brief Хранит данные, на которых применяются преобразования
    std::valarray<std::complex<float>> fft_data_;
};
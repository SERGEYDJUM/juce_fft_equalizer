#pragma once
#include <complex>
#include <valarray>

/// @brief Класс, реализующий алгоритмы прямого и обратного Быстрого
/// Преобразования Фурье.
class FFT {
   public:
    /// @brief Конструирует FFT с заданным размером.
    /// @param size_order порядок размера преобразуемого блока.
    FFT(unsigned int size_order) : order{size_order}, size{1u << order} {
        fft_data.resize(size);
        index_reverse_table.resize(size);
        for (unsigned int i = 0; i < size; i++) {
            index_reverse_table[i] = _index_reversed(i);
        }
    }

    /// @brief Производит прямое преобразование Фурье хранимого блока без
    /// нормализации.
    inline void perform_forward() { _fft(); }

    /// @brief Производит обратное преобразование Фурье хранимого блока.
    inline void perform_inverse() {
        fft_data = fft_data.apply(std::conj);
        _fft();
        fft_data = fft_data.apply(std::conj);
        fft_data /= static_cast<float>(size);
    }

    /// @brief Загружает блок в память FFT.
    /// @param buffer одноканальный буффер размером с блок или больше.
    /// @param offset индекс элемента, с которого начать читать.
    inline void read_block(float buffer[], unsigned int offset = 0) {
        for (unsigned int i = 0; i < size; ++i) {
            fft_data[i] = buffer[i + offset];
        }
    }

    /// @brief Выгружает блок FFT в буффер.
    /// @param buffer одноканальный буффер размером с блок или больше.
    /// @param offset индекс элемента, с которого начать писать.
    inline void write_block(float buffer[], unsigned int offset = 0) {
        for (unsigned int i = 0; i < size; ++i) {
            buffer[i + offset] = fft_data[i].real();
        }
    }

    /// @brief Позволяет напрямую изменять элементы внутренней памяти FFT.
    /// @details Для справки: fft[0] - DC слот, хранит сумму сэмплов блока,
    /// fft[size/2] - слот Найквиста, хранит данные для (частота дискретизации)
    /// / 2, для остальных fft[i] = std::conj(fft[size - i]).
    /// @param index номер элемента.
    /// @return ссылка на элемент.
    inline std::complex<float>& operator[](size_t index) {
        return fft_data[index];
    }

   private:
    // /// @brief Рекурсивный aлгоритм Cooley–Tukey
    // /// @param inp_arr ссылка на массив
    // void _fft(std::valarray<std::complex<float>>& inp_arr) {
    //     unsigned int _size = inp_arr.size();
    //     if (_size <= 1) return;

    //     std::valarray<std::complex<float>> even = inp_arr[std::slice(0, _size
    //     / 2, 2)]; std::valarray<std::complex<float>> odd =
    //     inp_arr[std::slice(1, _size / 2, 2)];

    //     _fft(even);
    //     _fft(odd);

    //     for (unsigned int i = 0; i < _size / 2; ++i) {
    //         auto t = std::polar(1.0f, -6.283185307179586f * i / _size) *
    //         odd[i]; inp_arr[i] = even[i] + t; inp_arr[i + _size / 2] =
    //         even[i] - t;
    //     }
    // }

    /// @brief Итеративный aлгоритм Cooley–Tukey (Decimation-in-frequency)
    void _fft() {
        auto phiT = std::polar(1.0f, -3.141592741f / size);
        unsigned int half_k = size, k;
        while (half_k != 0) {
            k = half_k;
            half_k >>= 1;
            phiT *= phiT;
            std::complex<float> magT = 1.0f;
            for (unsigned int l = 0; l < half_k; ++l) {
                for (unsigned int a = l; a < size; a += k) {
                    auto b = a + half_k;
                    auto temp = fft_data[a] - fft_data[b];
                    fft_data[a] += fft_data[b];
                    fft_data[b] = temp * magT;
                }
                magT *= phiT;
            }
        }

        for (unsigned int i = 0; i < size; ++i) {
            auto j = index_reverse_table[i];
            if (i != j) std::swap(fft_data[i], fft_data[j]);
        }
    }

    /// @brief Даёт индекс в блоке FFT, обратный данному.
    /// @param x индекс.
    /// @return обратный индекс.
    inline unsigned int _index_reversed(unsigned int x) {
        auto y = x;
        y = ((y >> 1) & 0x55555555) | ((y & 0x55555555) << 1);
        y = ((y >> 2) & 0x33333333) | ((y & 0x33333333) << 2);
        y = ((y >> 4) & 0x0F0F0F0F) | ((y & 0x0F0F0F0F) << 4);
        y = ((y >> 8) & 0x00FF00FF) | ((y & 0x00FF00FF) << 8);
        y = (y >> 16) | (y << 16);
        y >>= (32 - order);
        return (y > x) ? y : x;
    }

    /// @brief Порядок размера блока FFT
    const unsigned int order;

    /// @brief Размер блока FFT
    const unsigned int size;

    /// @brief Хранит обратные индексы для оптимизации
    std::valarray<unsigned int> index_reverse_table;

    /// @brief Хранит данные, на которых применяются преобразования
    std::valarray<std::complex<float>> fft_data;
};
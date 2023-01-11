#pragma once
#include <complex>
#include <valarray>

/// @brief Класс, реализующий алгоритмы прямого и обратного Быстрого Преобразования Фурье.
class FFT {
   public:
    /// @brief Конструирует FFT с заданным размером.
    /// @param size_order порядок размера преобразуемого блока.
    FFT(int size_order) : order{size_order}, size{1 << order} {
        fft_data.resize(size);
    }

    /// @brief Производит прямое БПФ хранимого блока.
    void perform_forward() {
        _fft(fft_data);
        fft_data /= std::sqrtf((float)size);
    }

    /// @brief Производит обратное БПФ хранимого блока.
    void perform_inverse() {
        fft_data = fft_data.apply(std::conj);
        _fft(fft_data);
        fft_data = fft_data.apply(std::conj);
        fft_data /= std::sqrtf((float)size);
    }

    /// @brief Загружает блок в память FFT.
    /// @param buffer одноканальный буффер размером с блок или больше.
    void read_block(float buffer[]) {
        for (int i = 0; i < size; ++i) {
            fft_data[i] = std::complex<float>{buffer[i], 0};
        }
    }

    /// @brief Выгружает блок FFT в буффер.
    /// @param buffer одноканальный буффер размером с блок или больше.
    void write_block(float buffer[]) {
        for (int i = 0; i < size; ++i) {
            buffer[i] = fft_data[i].real();
        }
    }

    /// @brief Позволяет напрямую изменять элементы внутренней памяти FFT.
    /// @param index номер элемента.
    /// @return ссылка на элемент.
    inline std::complex<float>& operator[](size_t index) {
        return fft_data[index];
    }

   private:
    void _fft(std::valarray<std::complex<float>>& inp_arr) {
        size_t _size = inp_arr.size();
        if (_size <= 1) return;

        std::valarray<std::complex<float>> even = inp_arr[std::slice(0, _size / 2, 2)];
        std::valarray<std::complex<float>> odd = inp_arr[std::slice(1, _size / 2, 2)];

        _fft(even);
        _fft(odd);

        for (size_t i = 0; i < _size / 2; ++i) {
            auto t = std::polar(1.0f, -6.283185307179586f * i / _size) * odd[i];
            inp_arr[i] = even[i] + t;
            inp_arr[i + _size / 2] = even[i] - t;
        }
    }

    const int order;
    const int size;
    std::valarray<std::complex<float>> fft_data;
};
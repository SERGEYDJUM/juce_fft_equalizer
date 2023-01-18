//! @file AudioPlayer.h
//! @authors Джумагельдиев С.А.
//! @note Ответственный: Полевой Д.В.
//! @brief Заголовочный файл с объявлением класса AudioPlayer

#pragma once
#include <JuceHeader.h>

#include "Equalizer.h"

/// @brief Воспроизводит аудиофайлы форматов wav, mp3, flac и может быть
/// каких-то ещё
class AudioPlayer : public AudioAppComponent, public ChangeListener {
   public:
    /// @brief Набор состояний, в которых может находиться плееер
    enum PlayerState { Stopped, Playing, Paused };

    /**
     * @brief Конструирует плеер.
     * @param callback функция, которая будет вызываться при изменении состояния
     * объекта.
     */
    AudioPlayer(std::function<void(AudioPlayer *)> callback,
                unsigned int buffer_size_order);

    /**
     * @brief Возвращает состояние плеера.
     * @return Текущее состояние.
     */
    PlayerState getState() const noexcept { return state_; }

    /**
     * @brief Меняет состояние плеера.
     * @param new_state новое состояние.
     */
    void changeState(PlayerState new_state);

    /**
     * @brief Асинхронно запускает окно выбора аудиофайла.
     * При этом воспроизведение предыдущего не прекращается до момента выбора
     * корректного файла.
     */
    void selectFile();

    /**
     * @brief Устанавливает громкость.
     * @param new_level громкость от 0 до 1.
     */
    void setVolumeGain(float new_level);

    /**
     * @brief Возвращает громкость плеера.
     * @return Громкость от 0 до 1.
     */
    float getVolumeGain() const noexcept { return transport_source_.getGain(); }

    /// @brief Обновляет коэффициенты для частотного диапазона эквалайзера.
    /// @param band номер полосы.
    /// @param gain коэффициент от 0 до 2.
    void updateEqualizerBand(unsigned int band, float gain);

    /// @brief Сдвигает позицию при активном проигрывании
    /// @param seconds изменение времени в секундах, отрицательное значения
    /// перематывает назад.
    void jumpSeconds(double seconds);

    ~AudioPlayer() override;

#ifdef FFT_DATA_LOGGING
    /// @brief Указывает эквалайзеру записать результат FFT следующего
    /// аудиобуфера на диск.
    void logNextBlock() noexcept { equalizer_.log_next_block = true; }
#endif

   private:
    /// @brief Состояние плеера
    PlayerState state_;

    /// @brief Позиция проигрывания
    double playback_position_ = 0.0;

    /// @brief Встроенный эквалайзер
    Equalizer equalizer_;

    /// @brief Управляет списком поддерживаемых форматов и определяет какой
    /// использовать для аудиофайла
    AudioFormatManager format_manager_;

    /// @brief Воспроизводит аудиобуферы
    AudioTransportSource transport_source_;

    /// @brief Хранит окно выбора файлов, необходимо в силу асинхронности
    std::unique_ptr<FileChooser> chooser_;

    /// @brief Читает данные из аудиофайла
    std::unique_ptr<AudioFormatReaderSource> reader_source_;

    /// @brief Хранит коллбэк, вызываемый при изменении состояния
    std::function<void(AudioPlayer *)> state_callback_;

    /// @brief Вызывается при изменении состояния AudioTransportSource,
    /// используется для обработки остановки трека.
    /// @param source вызвавший коллбэк.
    void changeListenerCallback(ChangeBroadcaster *source) override;

    /// @brief Обработчик очередного буфера с аудио.
    /// @param bufferToFill принятый многоканальный буфер.
    void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override;

    /// @brief Вызывается для подготовки AudioTransportSource к воспроизведения
    /// нового файла.
    /// @param samplesPerBlockExpected ожидаемый размер блока.
    /// @param sampleRate частота дискретизации.
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

    /// @brief Освобождает ресурсы AudioTransportSource.
    void releaseResources() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPlayer)
};

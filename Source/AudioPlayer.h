#pragma once
#include <JuceHeader.h>

#include "Equalizer.h"

/// @brief Воспроизводит аудиофайлы форматов wav, mp3 и flac.
class AudioPlayer : public AudioAppComponent, public ChangeListener {
   public:
    /// @brief Набор состояний, в которых может находиться плееер.
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
    PlayerState getState();

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
     * @param new_volume громкость от 0 до 1.
     */
    void setVolumeGain(float new_level);

    /**
     * @brief Возвращает громкость плеера.
     * @return Громкость от 0 до 1.
     */
    float getVolumeGain() { return transport_source.getGain(); };

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
    /// аудиобуффера на диск.
    void logNextBlock() { equalizer.log_next_block = true; }
#endif

   private:
    PlayerState state;
    double playback_position = 0.0;
    Equalizer equalizer;
    AudioFormatManager format_manager;
    AudioTransportSource transport_source;
    std::unique_ptr<FileChooser> chooser;
    std::unique_ptr<AudioFormatReaderSource> reader_source;
    std::function<void(AudioPlayer *)> state_callback;

    // Наследованные от AudioAppComponent методы работы со звуком и этим
    // компонентом
    void changeListenerCallback(ChangeBroadcaster *source) override;
    void getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill) override;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPlayer)
};

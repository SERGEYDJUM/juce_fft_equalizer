#pragma once
#include <JuceHeader.h>

#include "Equalizer.h"

/// @brief Воспроизводит аудиофайл форматов wav, mp3 и flac; позволяет ставить на паузу и начинать заново.
class AudioPlayer : public juce::AudioAppComponent,
                    public juce::ChangeListener {
   public:
    /// @brief Набор состояний, в которых может находиться плееер.
    enum PlayerState { 
        Stopped,
        Playing,
        Paused
    };

    /**
     * @brief Конструирует плеер.
     * @param callback функция, которая будет вызываться при изменении его состояния.
     */
    AudioPlayer(std::function<void(AudioPlayer *)> callback, int buffer_size_order);

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
     * При этом воспроизведение предыдущего останавливается только если был выбран корректный файл.
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

    /// @brief Обновляет коэффициенты для частотного диапазона внутреннего эквалайзера.
    /// @param low левая граница диапазона.
    /// @param high правая граница диапазона.
    /// @param gain коэффициент от -10 до +10 в децибелах
    void updateBand(int low, int high, float gain);

    /// @brief Сдвигает позицию при активном проигрывании 
    /// @param seconds изменение времени в секундах, отрицательное значения перематывают назад.
    void jumpSeconds(double seconds);

    ~AudioPlayer() override;

#ifdef FFT_DATA_LOGGING
    /// @brief Указывает эквалайзеру записать результат FFT следующего аудиобуффера на диск.
    void logNextBlock() {
        equalizer.log_next_block = true;
    }
#endif

   private:
    /// @brief Позиция в треке
    double playback_position = 0.0;
    PlayerState state; 
    Equalizer equalizer;
    juce::AudioFormatManager format_manager;
    juce::AudioTransportSource transport_source;
    std::unique_ptr<juce::FileChooser> chooser;
    std::unique_ptr<juce::AudioFormatReaderSource> reader_source;
    std::function<void(AudioPlayer *)> state_callback;

    // Наследованные от AudioAppComponent методы работы со звуком и этим компонентом

    void changeListenerCallback(juce::ChangeBroadcaster *source) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPlayer)
};

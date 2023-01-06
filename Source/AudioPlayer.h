#pragma once
#include <JuceHeader.h>

#include "Equalizer.h"

/**
 * Воспроизводит аудиофайл формата wav и mp3, позволяет ставить на паузу и
 * начинать заново.
 */
class AudioPlayer : public juce::AudioAppComponent,
                    public juce::ChangeListener {
   public:
    /**
     * Набор состояний, в которых плеер может находиться плееер.
     */
    enum PlayerState { Stopped, Playing, Paused };

    /**
     * Конструирует плеер
     *
     * \param state_caller Функция, которая будет вызываться при изменении его
     * состояния.
     */
    AudioPlayer(std::function<void(PlayerState)> state_caller = [](PlayerState state) { state; });

    ~AudioPlayer() override;

    /**
     * Возвращает состояние плеера.
     *
     * \return состояние плеера.
     */
    PlayerState getState();

    /**
     * Изменяет состояние плеера (PlayerState)
     *
     * \param new_state Новое состояние
     */
    void changeState(PlayerState new_state);

    /**
     * Асинхронно запускает окно выбора аудиофайла.
     * При этом воспроизведение предыдущего останавливается только если был
     * выбран корректный файл.
     *
     */
    void selectFile();

    /**
     * @brief Устанавливает громкость
     *
     * @param new_volume громкость от 0 до 1
     */
    void setVolumeGain(float new_level);

    /**
     * @brief Возвращает громкость плеера
     *
     * @return double - громкость от 0 до 1
     */
    float getVolumeGain() { return transport_source.getGain(); };

    void updateBand(int low, int high, float gain);

   private:
    double playback_position = 0.0;  // Позиция в треке

    PlayerState state;  // Состояние плеера

    Equalizer equalizer;

    juce::AudioFormatManager format_manager;  // Хранит доступные форматы аудио

    juce::AudioTransportSource transport_source;  // Проигрыватель аудио-буфферов

    std::unique_ptr<juce::FileChooser> chooser;  // Окно выбора файла, которое необходимо хранить из-за асинхронности

    std::unique_ptr<juce::AudioFormatReaderSource> reader_source;  // Считыватель аудио с файла

    std::function<void(PlayerState)> state_callback;  // Хранит функцию, вызываемую при изменении состояния

    // Наследованные от AudioAppComponent методы работы со звуком и этим компонентом
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPlayer)
};

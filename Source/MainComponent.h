#pragma once
#include <JuceHeader.h>

#include "AudioPlayer.h"

/// @brief Класс контента основного окна
class MainComponent : public juce::Component,
                      public juce::Slider::Listener,
                      public juce::KeyListener,
                      public juce::Button::Listener {
   public:
    /**
     * @brief Конструирует контент основного окна и создаёт плеер
     * @param buffer_size_order указывает степень 2-ки размера аудиобуффера и блока FFT
     */
    MainComponent(int buffer_size_order = 11);

    /// @brief Вызывается при изменении размера окна, адаптирует контент. 
    void resized() override;

    /// @brief Коллбэк для всех слайдеров в окне.
    /// @param sliderThatWasMoved слайдер, который изменился.
    void sliderValueChanged(juce::Slider *sliderThatWasMoved) override;

    /// @brief Коллбэк для всех кнопок в окне.
    /// @param buttonThatWasClicked нажатая кнопка.
    void buttonClicked(juce::Button *buttonThatWasClicked) override;

    /// @brief Кастомный коллбэк для плеера.
    /// @param playerWhichStateChanged этот плеер.
    void playerStateChanged(AudioPlayer *playerWhichStateChanged);

    /// @brief Коллбэк для всех нажатий на клавиатуре.
    /// @param k информация о нажатии.
    /// @param c компонент, получивший сообщение о нажатии.
    /// @return Статус обработанности события.
    bool keyPressed(const KeyPress &k, Component *c) override;

    ~MainComponent() override;

    /// @brief Количество регулируемых диапазонов частот
    static constexpr int bands_num = 11;
   private:
    std::unique_ptr<AudioPlayer> player;
    juce::OwnedArray<juce::Slider> knobs;
    juce::OwnedArray<juce::Label> knob_labels;
    std::unique_ptr<juce::Slider> volume_slider;
    std::unique_ptr<juce::TextButton> fileselect_button;
    std::unique_ptr<juce::TextButton> playback_button;
    std::unique_ptr<juce::Label> volume_label;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
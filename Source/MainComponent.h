#pragma once
#include <JuceHeader.h>

#include "AudioPlayer.h"

/// @brief Класс контента основного окна
class MainComponent : public Component,
                      public Slider::Listener,
                      public KeyListener,
                      public Button::Listener {
   public:
    /**
     * @brief Конструирует весь контент основного окна и создаёт плеер.
     * @param buffer_size_order указывает степень 2-ки размера аудиобуффера и
     * блока FFT.
     */
    explicit MainComponent(unsigned int buffer_size_order = 11);

    /// @brief Вызывается при изменении размера окна, адаптирует контент.
    void resized() override;

    /// @brief Коллбэк для всех слайдеров в окне.
    /// @param sliderThatWasMoved слайдер, который изменился.
    void sliderValueChanged(Slider *sliderThatWasMoved) override;

    /// @brief Коллбэк для всех кнопок в окне.
    /// @param buttonThatWasClicked нажатая кнопка.
    void buttonClicked(Button *buttonThatWasClicked) override;

    /// @brief Кастомный коллбэк для плеера, обновляющий текст и состояние
    /// кнопки паузы.
    /// @param playerWhichStateChanged этот плеер.
    void playerStateChanged(AudioPlayer *playerWhichStateChanged);

    /// @brief Коллбэк для всех нажатий на клавиатуре.
    /// @param k информация о нажатии.
    /// @param c компонент, получивший сообщение о нажатии.
    /// @return было ли нажатие обработано.
    bool keyPressed(const KeyPress &k, Component *c) override;

    ~MainComponent() override;

   private:
    // Количество регулируемых диапазонов частот (полос)
    static constexpr unsigned int bands_num = 11;

    std::unique_ptr<AudioPlayer> player;
    // Слайдеры, отвечающие за полосы
    OwnedArray<Slider> knobs;
    OwnedArray<Label> knob_labels;
    std::unique_ptr<Slider> volume_slider;
    std::unique_ptr<TextButton> fileselect_button;
    std::unique_ptr<TextButton> playback_button;
    std::unique_ptr<Label> volume_label;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
//! @file MainComponent.h
//! @authors Джумагельдиев С.А.
//! @note Ответственный: Полевой Д.В.
//! @brief Заголовочный файл с объявлением класса MainComponent

#pragma once
#include <JuceHeader.h>

#include "AudioPlayer.h"

/// @brief Класс контента основного окна
class MainComponent : public Component,
                      public Slider::Listener,
                      public KeyListener,
                      public Button::Listener {
   public:
    /// @brief Конструирует весь контент основного окна и создаёт плеер.
    /// @param title_change_callback коллбэк для изменения заголовка окна.
    MainComponent(std::function<void(String)> title_change_callback);

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

    ~MainComponent() noexcept override;

   private:
    /// @brief Количество регулируемых диапазонов частот (полос)
    static constexpr int bands_num_ = 11;

    /// @brief Плеер со встроенным эквалайзером
    std::unique_ptr<AudioPlayer> player_;

    /// @brief Слайдеры, отвечающие за полосы
    OwnedArray<Slider> knobs_;

    /// @brief Надписи герцовок под слайдерами
    OwnedArray<Label> knob_labels_;

    /// @brief Регулятор громкости
    std::unique_ptr<Slider> volume_slider_;

    /// @brief Кнопка, открывающая окно выбора файла
    std::unique_ptr<TextButton> fileselect_button_;

    /// @brief Кнопка паузы с меняющимся текстом
    std::unique_ptr<TextButton> playback_button_;

    /// @brief Надпись "Громкость"
    std::unique_ptr<Label> volume_label_;

    /// @brief Коллбэк для изменения заголовка окна
    std::function<void(String)> title_callback;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
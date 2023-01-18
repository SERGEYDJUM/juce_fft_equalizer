//! @file Main.cc
//! @authors Projucer, Джумагельдиев С.А.
//! @note Ответственный: Полевой Д.В.
//! @brief Файл с инициализацией приложения

#include <JuceHeader.h>

#include "MainComponent.h"

/// @brief Основной класс приложения, сгенерирован Projucer-ом для проекта типа
/// "GUI-приложение", инстанциируется JUCE-ом.
class juce_fft_equalizer : public JUCEApplication {
   public:
    /// @brief Конструктор
    juce_fft_equalizer() {}

    /// @brief Возвращает название приложения
    /// @return навзвание
    const String getApplicationName() override {
        return ProjectInfo::projectName;
    }

    /// @brief Возвращает версию приложения
    /// @return строка версии
    const String getApplicationVersion() override {
        return ProjectInfo::versionString;
    }

    /// @brief Возвращает доступность создания копии приложения
    /// @return всегда false
    bool moreThanOneInstanceAllowed() override { return false; }

    /// @brief Закрывает окно
    void shutdown() override { mainWindow = nullptr; }

    /// @brief Обрабатывает запрос на закрытие
    void systemRequestedQuit() override { quit(); }

    /// @brief Создаёт новое окно
    /// @param arguments аргументы при запуске 
    void initialise(const String &arguments) override {
        arguments;
        mainWindow.reset(new MainWindow(getApplicationName()));
    }

    /// @brief Класс главного окна приложения
    class MainWindow : public DocumentWindow {
       public:
        /// @brief Конструирует главное окно
        /// @param name заголовок окна
        MainWindow(String name)
            : DocumentWindow(
                  name,
                  Desktop::getInstance().getDefaultLookAndFeel().findColour(
                      ResizableWindow::backgroundColourId),
                  DocumentWindow::allButtons) {
            setUsingNativeTitleBar(true);
            setContentOwned(new MainComponent(), true);

#if JUCE_IOS || JUCE_ANDROID
            setFullScreen(true);
#else
            setResizable(true, false);
            centreWithSize(getWidth(), getHeight());
#endif
            setVisible(true);
        }

        /// @brief Обрабатывает нажатие на "крестик"
        void closeButtonPressed() override {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

       private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
    };

   private:
    /// @brief Хранит главное окно
    std::unique_ptr<MainWindow> mainWindow;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(juce_fft_equalizer)
};

START_JUCE_APPLICATION(juce_fft_equalizer)

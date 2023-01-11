#include <JuceHeader.h>

#include "MainComponent.h"

/// @brief Cгенерирован Projucer-ом для проекта типа "GUI-приложение"
class juce_fft_equalizer : public juce::JUCEApplication {
   public:
    juce_fft_equalizer() {}
    const juce::String getApplicationName() override { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion() override { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override { return false; }
    void shutdown() override { mainWindow = nullptr; }
    void systemRequestedQuit() override { quit(); }
    void initialise(const juce::String &) override {
        mainWindow.reset(new MainWindow(getApplicationName()));
    }

    class MainWindow : public juce::DocumentWindow {
       public:
        MainWindow(juce::String name)
            : DocumentWindow(
                  name,
                  juce::Desktop::getInstance()
                      .getDefaultLookAndFeel()
                      .findColour(juce::ResizableWindow::backgroundColourId),
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

        void closeButtonPressed() override {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

       private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
    };

   private:
    std::unique_ptr<MainWindow> mainWindow;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(juce_fft_equalizer)
};

START_JUCE_APPLICATION(juce_fft_equalizer)

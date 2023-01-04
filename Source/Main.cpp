#include <JuceHeader.h>

#include "MainComponent.h"

class fft_equalizerApplication : public juce::JUCEApplication {
   public:
    fft_equalizerApplication() {}

    const juce::String getApplicationName() override {
        return ProjectInfo::projectName;
    }
    const juce::String getApplicationVersion() override {
        return ProjectInfo::versionString;
    }
    bool moreThanOneInstanceAllowed() override { return false; }

    void initialise(const juce::String &commandLine) override {
        commandLine;
        mainWindow.reset(new MainWindow(getApplicationName()));
    }

    void shutdown() override { mainWindow = nullptr; }

    void systemRequestedQuit() override { quit(); }

    void anotherInstanceStarted(const juce::String &commandLine) override {
        commandLine;
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
            setUsingNativeTitleBar(false);
            setContentOwned(new MainComponent(), true);

#if JUCE_IOS || JUCE_ANDROID
            setFullScreen(true);
#else
            setResizable(true, true);
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
};

START_JUCE_APPLICATION(fft_equalizerApplication)

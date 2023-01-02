#pragma once
#include <JuceHeader.h>

class MainComponent : public juce::Component,
                       public juce::Slider::Listener,
                       public juce::Button::Listener
{
public:
    MainComponent ();
    ~MainComponent() override;

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;

private:
    const int band_number = 11;
    juce::OwnedArray<juce::Slider> knobs;
    juce::OwnedArray<juce::Label> knob_labels;
    std::unique_ptr<juce::Slider> volume_slider;
    std::unique_ptr<juce::TextButton> fileselection_button;
    std::unique_ptr<juce::TextButton> playback_button;
    std::unique_ptr<juce::Label> volume_label;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

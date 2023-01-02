/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.3

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
		An auto-generated component, created by the Projucer.

		Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainComponent  : public juce::Component,
                       public juce::Slider::Listener,
                       public juce::Button::Listener
{
public:
    //==============================================================================
    MainComponent ();
    ~MainComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Slider> knob0;
    std::unique_ptr<juce::Slider> knob1;
    std::unique_ptr<juce::Slider> knob2;
    std::unique_ptr<juce::Slider> knob3;
    std::unique_ptr<juce::Slider> knob4;
    std::unique_ptr<juce::Slider> knob5;
    std::unique_ptr<juce::Slider> knob6;
    std::unique_ptr<juce::Slider> knob7;
    std::unique_ptr<juce::Slider> knob8;
    std::unique_ptr<juce::Slider> knob9;
    std::unique_ptr<juce::Slider> knob10;

    std::unique_ptr<juce::Label> _knobLabel0;
    std::unique_ptr<juce::Label> _knobLabel2;
    std::unique_ptr<juce::Label> _knobLabel3;
    std::unique_ptr<juce::Label> _knobLabel4;
    std::unique_ptr<juce::Label> _knobLabel5;
    std::unique_ptr<juce::Label> _knobLabel6;
    std::unique_ptr<juce::Label> _knobLabel7;
    std::unique_ptr<juce::Label> _knobLabel8;
    std::unique_ptr<juce::Label> _knobLabel9;
    std::unique_ptr<juce::Label> _knobLabel10;
    std::unique_ptr<juce::Label> _knobLabel11;
    std::unique_ptr<juce::Slider> volume_slider;
    std::unique_ptr<juce::TextButton> fileSelectButton;
    std::unique_ptr<juce::TextButton> playbackControlButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]


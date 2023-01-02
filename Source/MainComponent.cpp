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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainComponent::MainComponent()
{
	//[Constructor_pre] You can add your own custom stuff here..
	/*juce::Grid grid;

	using GridTrack = juce::Grid::TrackInfo;
	using GridFr = juce::Grid::Fr;
	using Slider = juce::Slider;

	juce::OwnedArray<Slider> knobs;

	grid.templateRows = { GridTrack(GridFr(1)), GridTrack(GridFr(10)), GridTrack(GridFr(1)) };
	for (size_t i = 0; i < 11; i++)
	{
		grid.templateColumns.add(GridTrack(GridFr(1)));
	}

	for (size_t i = 0; i < 11; i++)
	{
		Slider knob;
		knob.setSliderStyle(Slider::SliderStyle::LinearVertical);
		knobs.add(&knob);

		juce::GridItem knob_cell{knobs.getLast()};
		knob_cell.setArea(1, i, 1, i);
		grid.items.add(knob_cell);
	}*/
	//[/Constructor_pre]

	knob0.reset(new juce::Slider("new slider"));
	addAndMakeVisible(knob0.get());
	knob0->setRange(-10, 10, 0.1);
	knob0->setSliderStyle(juce::Slider::LinearVertical);
	knob0->setTextBoxStyle(juce::Slider::TextBoxAbove, false, 80, 20);
	knob0->addListener(this);

	knob0->setBounds(0, 8, 40, 200);

	knob1.reset(new juce::Slider("new slider"));
	addAndMakeVisible(knob1.get());
	knob1->setRange(-10, 10, 0.1);
	knob1->setSliderStyle(juce::Slider::LinearVertical);
	knob1->setTextBoxStyle(juce::Slider::TextBoxAbove, false, 80, 20);
	knob1->addListener(this);

	knob1->setBounds(56, 8, 40, 200);

	knob2.reset(new juce::Slider("new slider"));
	addAndMakeVisible(knob2.get());
	knob2->setRange(-10, 10, 0.1);
	knob2->setSliderStyle(juce::Slider::LinearVertical);
	knob2->setTextBoxStyle(juce::Slider::TextBoxAbove, false, 80, 20);
	knob2->addListener(this);

	knob2->setBounds(112, 8, 40, 200);

	knob3.reset(new juce::Slider("new slider"));
	addAndMakeVisible(knob3.get());
	knob3->setRange(-10, 10, 0.1);
	knob3->setSliderStyle(juce::Slider::LinearVertical);
	knob3->setTextBoxStyle(juce::Slider::TextBoxAbove, false, 80, 20);
	knob3->addListener(this);

	knob3->setBounds(168, 8, 40, 200);

	knob4.reset(new juce::Slider("new slider"));
	addAndMakeVisible(knob4.get());
	knob4->setRange(-10, 10, 0.1);
	knob4->setSliderStyle(juce::Slider::LinearVertical);
	knob4->setTextBoxStyle(juce::Slider::TextBoxAbove, false, 80, 20);
	knob4->addListener(this);

	knob4->setBounds(224, 8, 40, 200);

	knob5.reset(new juce::Slider("new slider"));
	addAndMakeVisible(knob5.get());
	knob5->setRange(-10, 10, 0.1);
	knob5->setSliderStyle(juce::Slider::LinearVertical);
	knob5->setTextBoxStyle(juce::Slider::TextBoxAbove, false, 80, 20);
	knob5->addListener(this);

	knob5->setBounds(280, 8, 40, 200);

	knob6.reset(new juce::Slider("new slider"));
	addAndMakeVisible(knob6.get());
	knob6->setRange(-10, 10, 0.1);
	knob6->setSliderStyle(juce::Slider::LinearVertical);
	knob6->setTextBoxStyle(juce::Slider::TextBoxAbove, false, 80, 20);
	knob6->addListener(this);

	knob6->setBounds(336, 8, 40, 200);

	knob7.reset(new juce::Slider("new slider"));
	addAndMakeVisible(knob7.get());
	knob7->setRange(-10, 10, 0.1);
	knob7->setSliderStyle(juce::Slider::LinearVertical);
	knob7->setTextBoxStyle(juce::Slider::TextBoxAbove, false, 80, 20);
	knob7->addListener(this);

	knob7->setBounds(392, 8, 40, 200);

	knob8.reset(new juce::Slider("new slider"));
	addAndMakeVisible(knob8.get());
	knob8->setRange(-10, 10, 0.1);
	knob8->setSliderStyle(juce::Slider::LinearVertical);
	knob8->setTextBoxStyle(juce::Slider::TextBoxAbove, false, 80, 20);
	knob8->addListener(this);

	knob8->setBounds(448, 8, 40, 200);

	knob9.reset(new juce::Slider("new slider"));
	addAndMakeVisible(knob9.get());
	knob9->setRange(-10, 10, 0.1);
	knob9->setSliderStyle(juce::Slider::LinearVertical);
	knob9->setTextBoxStyle(juce::Slider::TextBoxAbove, false, 80, 20);
	knob9->addListener(this);

	knob9->setBounds(504, 8, 40, 200);

	knob10.reset(new juce::Slider("new slider"));
	addAndMakeVisible(knob10.get());
	knob10->setRange(-10, 10, 0.1);
	knob10->setSliderStyle(juce::Slider::LinearVertical);
	knob10->setTextBoxStyle(juce::Slider::TextBoxAbove, false, 80, 20);
	knob10->addListener(this);

	knob10->setBounds(560, 8, 40, 200);

	_knobLabel0.reset(new juce::Label("new label",
		TRANS("16 Hz")));
	addAndMakeVisible(_knobLabel0.get());
	_knobLabel0->setFont(juce::Font(9.00f, juce::Font::plain).withTypefaceStyle("Regular"));
	_knobLabel0->setJustificationType(juce::Justification::centred);
	_knobLabel0->setEditable(false, false, false);
	_knobLabel0->setColour(juce::TextEditor::textColourId, juce::Colours::black);
	_knobLabel0->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

	_knobLabel0->setBounds(0, 208, 40, 8);

	_knobLabel2.reset(new juce::Label("new label",
		TRANS("31 Hz")));
	addAndMakeVisible(_knobLabel2.get());
	_knobLabel2->setFont(juce::Font(9.00f, juce::Font::plain).withTypefaceStyle("Regular"));
	_knobLabel2->setJustificationType(juce::Justification::centred);
	_knobLabel2->setEditable(false, false, false);
	_knobLabel2->setColour(juce::TextEditor::textColourId, juce::Colours::black);
	_knobLabel2->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

	_knobLabel2->setBounds(56, 208, 40, 8);

	_knobLabel3.reset(new juce::Label("new label",
		TRANS("63 Hz")));
	addAndMakeVisible(_knobLabel3.get());
	_knobLabel3->setFont(juce::Font(9.00f, juce::Font::plain).withTypefaceStyle("Regular"));
	_knobLabel3->setJustificationType(juce::Justification::centred);
	_knobLabel3->setEditable(false, false, false);
	_knobLabel3->setColour(juce::TextEditor::textColourId, juce::Colours::black);
	_knobLabel3->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

	_knobLabel3->setBounds(112, 208, 40, 8);

	_knobLabel4.reset(new juce::Label("new label",
		TRANS("125 Hz")));
	addAndMakeVisible(_knobLabel4.get());
	_knobLabel4->setFont(juce::Font(9.00f, juce::Font::plain).withTypefaceStyle("Regular"));
	_knobLabel4->setJustificationType(juce::Justification::centred);
	_knobLabel4->setEditable(false, false, false);
	_knobLabel4->setColour(juce::TextEditor::textColourId, juce::Colours::black);
	_knobLabel4->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

	_knobLabel4->setBounds(168, 208, 40, 8);

	_knobLabel5.reset(new juce::Label("new label",
		TRANS("250 Hz")));
	addAndMakeVisible(_knobLabel5.get());
	_knobLabel5->setFont(juce::Font(9.00f, juce::Font::plain).withTypefaceStyle("Regular"));
	_knobLabel5->setJustificationType(juce::Justification::centred);
	_knobLabel5->setEditable(false, false, false);
	_knobLabel5->setColour(juce::TextEditor::textColourId, juce::Colours::black);
	_knobLabel5->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

	_knobLabel5->setBounds(224, 208, 40, 8);

	_knobLabel6.reset(new juce::Label("new label",
		TRANS("500 Hz")));
	addAndMakeVisible(_knobLabel6.get());
	_knobLabel6->setFont(juce::Font(9.00f, juce::Font::plain).withTypefaceStyle("Regular"));
	_knobLabel6->setJustificationType(juce::Justification::centred);
	_knobLabel6->setEditable(false, false, false);
	_knobLabel6->setColour(juce::TextEditor::textColourId, juce::Colours::black);
	_knobLabel6->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

	_knobLabel6->setBounds(280, 208, 40, 8);

	_knobLabel7.reset(new juce::Label("new label",
		TRANS("1000 Hz")));
	addAndMakeVisible(_knobLabel7.get());
	_knobLabel7->setFont(juce::Font(9.00f, juce::Font::plain).withTypefaceStyle("Regular"));
	_knobLabel7->setJustificationType(juce::Justification::centred);
	_knobLabel7->setEditable(false, false, false);
	_knobLabel7->setColour(juce::TextEditor::textColourId, juce::Colours::black);
	_knobLabel7->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

	_knobLabel7->setBounds(336, 208, 40, 8);

	_knobLabel8.reset(new juce::Label("new label",
		TRANS("2000 Hz")));
	addAndMakeVisible(_knobLabel8.get());
	_knobLabel8->setFont(juce::Font(9.00f, juce::Font::plain).withTypefaceStyle("Regular"));
	_knobLabel8->setJustificationType(juce::Justification::centred);
	_knobLabel8->setEditable(false, false, false);
	_knobLabel8->setColour(juce::TextEditor::textColourId, juce::Colours::black);
	_knobLabel8->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

	_knobLabel8->setBounds(392, 208, 40, 8);

	_knobLabel9.reset(new juce::Label("new label",
		TRANS("4000 Hz")));
	addAndMakeVisible(_knobLabel9.get());
	_knobLabel9->setFont(juce::Font(9.00f, juce::Font::plain).withTypefaceStyle("Regular"));
	_knobLabel9->setJustificationType(juce::Justification::centred);
	_knobLabel9->setEditable(false, false, false);
	_knobLabel9->setColour(juce::TextEditor::textColourId, juce::Colours::black);
	_knobLabel9->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

	_knobLabel9->setBounds(448, 208, 40, 8);

	_knobLabel10.reset(new juce::Label("new label",
		TRANS("8000 Hz")));
	addAndMakeVisible(_knobLabel10.get());
	_knobLabel10->setFont(juce::Font(9.00f, juce::Font::plain).withTypefaceStyle("Regular"));
	_knobLabel10->setJustificationType(juce::Justification::centred);
	_knobLabel10->setEditable(false, false, false);
	_knobLabel10->setColour(juce::TextEditor::textColourId, juce::Colours::black);
	_knobLabel10->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

	_knobLabel10->setBounds(504, 208, 40, 8);

	_knobLabel11.reset(new juce::Label("new label",
		TRANS("16000 Hz")));
	addAndMakeVisible(_knobLabel11.get());
	_knobLabel11->setFont(juce::Font(9.00f, juce::Font::plain).withTypefaceStyle("Regular"));
	_knobLabel11->setJustificationType(juce::Justification::centred);
	_knobLabel11->setEditable(false, false, false);
	_knobLabel11->setColour(juce::TextEditor::textColourId, juce::Colours::black);
	_knobLabel11->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

	_knobLabel11->setBounds(560, 208, 40, 8);

	volume_slider.reset(new juce::Slider("new slider"));
	addAndMakeVisible(volume_slider.get());
	volume_slider->setRange(0, 100, 1);
	volume_slider->setSliderStyle(juce::Slider::LinearHorizontal);
	volume_slider->setTextBoxStyle(juce::Slider::TextBoxLeft, false, 30, 20);
	volume_slider->addListener(this);

	volume_slider->setBounds(440, 256, 150, 20);

	fileSelectButton.reset(new juce::TextButton("Select File"));
	addAndMakeVisible(fileSelectButton.get());
	fileSelectButton->addListener(this);
	fileSelectButton->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff42a2c8));

	fileSelectButton->setBounds(16, 256, 150, 24);

	playbackControlButton.reset(new juce::TextButton("Select File"));
	addAndMakeVisible(playbackControlButton.get());
	playbackControlButton->setButtonText(TRANS("Play / Pause"));
	playbackControlButton->addListener(this);
	playbackControlButton->setColour(juce::TextButton::buttonColourId, juce::Colour(0xff42a2c8));

	playbackControlButton->setBounds(192, 256, 150, 24);


	//[UserPreSize]
	//[/UserPreSize]

	setSize(600, 300);


	//[Constructor] You can add your own custom stuff here..
	//[/Constructor]
}

MainComponent::~MainComponent()
{
	//[Destructor_pre]. You can add your own custom destruction code here..
	//[/Destructor_pre]

	knob0 = nullptr;
	knob1 = nullptr;
	knob2 = nullptr;
	knob3 = nullptr;
	knob4 = nullptr;
	knob5 = nullptr;
	knob6 = nullptr;
	knob7 = nullptr;
	knob8 = nullptr;
	knob9 = nullptr;
	knob10 = nullptr;
	_knobLabel0 = nullptr;
	_knobLabel2 = nullptr;
	_knobLabel3 = nullptr;
	_knobLabel4 = nullptr;
	_knobLabel5 = nullptr;
	_knobLabel6 = nullptr;
	_knobLabel7 = nullptr;
	_knobLabel8 = nullptr;
	_knobLabel9 = nullptr;
	_knobLabel10 = nullptr;
	_knobLabel11 = nullptr;
	volume_slider = nullptr;
	fileSelectButton = nullptr;
	playbackControlButton = nullptr;


	//[Destructor]. You can add your own custom destruction code here..
	//[/Destructor]
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
	//[UserPrePaint] Add your own custom painting code here..
	//[/UserPrePaint]

	g.fillAll(juce::Colour(0xff323e44));

	{
		int x = 0, y = 230, width = 600, height = 2;
		juce::Colour fillColour = juce::Colour(0xff283237);
		//[UserPaintCustomArguments] Customize the painting arguments here..
		//[/UserPaintCustomArguments]
		g.setColour(fillColour);
		g.fillRect(x, y, width, height);
	}

	//[UserPaint] Add your own custom painting code here..
	//[/UserPaint]
}

void MainComponent::resized()
{
	//[UserPreResize] Add your own custom resize code here..
	//[/UserPreResize]

	//[UserResized] Add your own custom resize handling here..
	//[/UserResized]
}

void MainComponent::sliderValueChanged(juce::Slider* sliderThatWasMoved)
{
	//[UsersliderValueChanged_Pre]
	//[/UsersliderValueChanged_Pre]

	if (sliderThatWasMoved == knob0.get())
	{
		//[UserSliderCode_knob0] -- add your slider handling code here..
		//[/UserSliderCode_knob0]
	}

	//[UsersliderValueChanged_Post]
	//[/UsersliderValueChanged_Post]
}

void MainComponent::buttonClicked(juce::Button* buttonThatWasClicked)
{
	//[UserbuttonClicked_Pre]
	//[/UserbuttonClicked_Pre]

	if (buttonThatWasClicked == fileSelectButton.get())
	{
		//[UserButtonCode_fileSelectButton] -- add your button handler code here..
		//[/UserButtonCode_fileSelectButton]
	}
	else if (buttonThatWasClicked == playbackControlButton.get())
	{
		//[UserButtonCode_playbackControlButton] -- add your button handler code here..
		//[/UserButtonCode_playbackControlButton]
	}

	//[UserbuttonClicked_Post]
	//[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

	This is where the Projucer stores the metadata that describe this GUI layout, so
	make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainComponent" componentName=""
				 parentClasses="public juce::Component" constructorParams="" variableInitialisers=""
				 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
				 fixedSize="1" initialWidth="600" initialHeight="300">
  <BACKGROUND backgroundColour="ff323e44">
	<RECT pos="0 230 600 2" fill="solid: ff283237" hasStroke="0"/>
  </BACKGROUND>
  <SLIDER name="new slider" id="767c17fad952dd63" memberName="knob0" virtualName=""
		  explicitFocusOrder="0" pos="0 8 40 200" min="-10.0" max="10.0"
		  int="0.1" style="LinearVertical" textBoxPos="TextBoxAbove" textBoxEditable="1"
		  textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="29a2463c04f4709b" memberName="knob1" virtualName=""
		  explicitFocusOrder="0" pos="56 8 40 200" min="-10.0" max="10.0"
		  int="0.1" style="LinearVertical" textBoxPos="TextBoxAbove" textBoxEditable="1"
		  textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="4cce2ca53c2d6825" memberName="knob2" virtualName=""
		  explicitFocusOrder="0" pos="112 8 40 200" min="-10.0" max="10.0"
		  int="0.1" style="LinearVertical" textBoxPos="TextBoxAbove" textBoxEditable="1"
		  textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="154456d7b2d2a8e7" memberName="knob3" virtualName=""
		  explicitFocusOrder="0" pos="168 8 40 200" min="-10.0" max="10.0"
		  int="0.1" style="LinearVertical" textBoxPos="TextBoxAbove" textBoxEditable="1"
		  textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="8131b1b21a077ea2" memberName="knob4" virtualName=""
		  explicitFocusOrder="0" pos="224 8 40 200" min="-10.0" max="10.0"
		  int="0.1" style="LinearVertical" textBoxPos="TextBoxAbove" textBoxEditable="1"
		  textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="bbc3de9e81634971" memberName="knob5" virtualName=""
		  explicitFocusOrder="0" pos="280 8 40 200" min="-10.0" max="10.0"
		  int="0.1" style="LinearVertical" textBoxPos="TextBoxAbove" textBoxEditable="1"
		  textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="3bb6c9f3ea885e61" memberName="knob6" virtualName=""
		  explicitFocusOrder="0" pos="336 8 40 200" min="-10.0" max="10.0"
		  int="0.1" style="LinearVertical" textBoxPos="TextBoxAbove" textBoxEditable="1"
		  textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="aabac39b78efdd46" memberName="knob7" virtualName=""
		  explicitFocusOrder="0" pos="392 8 40 200" min="-10.0" max="10.0"
		  int="0.1" style="LinearVertical" textBoxPos="TextBoxAbove" textBoxEditable="1"
		  textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="9e90fdf68f3c8fcc" memberName="knob8" virtualName=""
		  explicitFocusOrder="0" pos="448 8 40 200" min="-10.0" max="10.0"
		  int="0.1" style="LinearVertical" textBoxPos="TextBoxAbove" textBoxEditable="1"
		  textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="423696fd25f425cc" memberName="knob9" virtualName=""
		  explicitFocusOrder="0" pos="504 8 40 200" min="-10.0" max="10.0"
		  int="0.1" style="LinearVertical" textBoxPos="TextBoxAbove" textBoxEditable="1"
		  textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="d8548fa9b59f62e0" memberName="knob10" virtualName=""
		  explicitFocusOrder="0" pos="560 8 40 200" min="-10.0" max="10.0"
		  int="0.1" style="LinearVertical" textBoxPos="TextBoxAbove" textBoxEditable="1"
		  textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="new label" id="dbaae14bbe6f9cdb" memberName="_knobLabel0"
		 virtualName="" explicitFocusOrder="0" pos="0 208 40 8" edTextCol="ff000000"
		 edBkgCol="0" labelText="16 Hz" editableSingleClick="0" editableDoubleClick="0"
		 focusDiscardsChanges="0" fontname="Default font" fontsize="9.0"
		 kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="b01b4fb5390416a3" memberName="_knobLabel2"
		 virtualName="" explicitFocusOrder="0" pos="56 208 40 8" edTextCol="ff000000"
		 edBkgCol="0" labelText="31 Hz" editableSingleClick="0" editableDoubleClick="0"
		 focusDiscardsChanges="0" fontname="Default font" fontsize="9.0"
		 kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="2d48538ec1f1496" memberName="_knobLabel3"
		 virtualName="" explicitFocusOrder="0" pos="112 208 40 8" edTextCol="ff000000"
		 edBkgCol="0" labelText="63 Hz" editableSingleClick="0" editableDoubleClick="0"
		 focusDiscardsChanges="0" fontname="Default font" fontsize="9.0"
		 kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="5c1757c79e02b17b" memberName="_knobLabel4"
		 virtualName="" explicitFocusOrder="0" pos="168 208 40 8" edTextCol="ff000000"
		 edBkgCol="0" labelText="125 Hz" editableSingleClick="0" editableDoubleClick="0"
		 focusDiscardsChanges="0" fontname="Default font" fontsize="9.0"
		 kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="2b1cddd98c2a6ec5" memberName="_knobLabel5"
		 virtualName="" explicitFocusOrder="0" pos="224 208 40 8" edTextCol="ff000000"
		 edBkgCol="0" labelText="250 Hz" editableSingleClick="0" editableDoubleClick="0"
		 focusDiscardsChanges="0" fontname="Default font" fontsize="9.0"
		 kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="43f528844c017da2" memberName="_knobLabel6"
		 virtualName="" explicitFocusOrder="0" pos="280 208 40 8" edTextCol="ff000000"
		 edBkgCol="0" labelText="500 Hz" editableSingleClick="0" editableDoubleClick="0"
		 focusDiscardsChanges="0" fontname="Default font" fontsize="9.0"
		 kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="454365433b033770" memberName="_knobLabel7"
		 virtualName="" explicitFocusOrder="0" pos="336 208 40 8" edTextCol="ff000000"
		 edBkgCol="0" labelText="1000 Hz" editableSingleClick="0" editableDoubleClick="0"
		 focusDiscardsChanges="0" fontname="Default font" fontsize="9.0"
		 kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="13f3d7f99d86296e" memberName="_knobLabel8"
		 virtualName="" explicitFocusOrder="0" pos="392 208 40 8" edTextCol="ff000000"
		 edBkgCol="0" labelText="2000 Hz" editableSingleClick="0" editableDoubleClick="0"
		 focusDiscardsChanges="0" fontname="Default font" fontsize="9.0"
		 kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="6ec8f135b27fa7b6" memberName="_knobLabel9"
		 virtualName="" explicitFocusOrder="0" pos="448 208 40 8" edTextCol="ff000000"
		 edBkgCol="0" labelText="4000 Hz" editableSingleClick="0" editableDoubleClick="0"
		 focusDiscardsChanges="0" fontname="Default font" fontsize="9.0"
		 kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="85ad04b744f91b6a" memberName="_knobLabel10"
		 virtualName="" explicitFocusOrder="0" pos="504 208 40 8" edTextCol="ff000000"
		 edBkgCol="0" labelText="8000 Hz" editableSingleClick="0" editableDoubleClick="0"
		 focusDiscardsChanges="0" fontname="Default font" fontsize="9.0"
		 kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="138a643379cf802d" memberName="_knobLabel11"
		 virtualName="" explicitFocusOrder="0" pos="560 208 40 8" edTextCol="ff000000"
		 edBkgCol="0" labelText="16000 Hz" editableSingleClick="0" editableDoubleClick="0"
		 focusDiscardsChanges="0" fontname="Default font" fontsize="9.0"
		 kerning="0.0" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="72e686bb266f4148" memberName="volume_slider"
		  virtualName="" explicitFocusOrder="0" pos="440 256 150 20" min="0.0"
		  max="100.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
		  textBoxEditable="1" textBoxWidth="30" textBoxHeight="20" skewFactor="1.0"
		  needsCallback="1"/>
  <TEXTBUTTON name="Select File" id="1ccb40898eb64f9d" memberName="fileSelectButton"
			  virtualName="" explicitFocusOrder="0" pos="16 256 150 24" bgColOff="ff42a2c8"
			  buttonText="Select File" connectedEdges="0" needsCallback="1"
			  radioGroupId="0"/>
  <TEXTBUTTON name="Select File" id="f633485be5870d85" memberName="playbackControlButton"
			  virtualName="" explicitFocusOrder="0" pos="192 256 150 24" bgColOff="ff42a2c8"
			  buttonText="Play / Pause" connectedEdges="0" needsCallback="1"
			  radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]


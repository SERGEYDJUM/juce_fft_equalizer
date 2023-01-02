#include "MainComponent.h"

MainComponent::MainComponent()
{
	int band_center = 16;
	for (int i = 0; i < band_number; i++)
	{
		knobs.add(new juce::Slider("knob" + std::to_string(i)));
		juce::Slider* knob = knobs.getLast();
		addAndMakeVisible(knob);
		knob->setSliderStyle(juce::Slider::LinearBarVertical);
		knob->setTextBoxIsEditable(false);
		knob->setRange(-10, 10, 0.1);
		knob->addListener(this);

		knob_labels.add(new juce::Label("knobLabel" + std::to_string(i), std::to_string(band_center) + " Hz"));
		juce::Label* label = knob_labels.getLast();
		label->setEditable(false, false, false);
		label->setJustificationType(juce::Justification::centred);
		addAndMakeVisible(label);
		band_center *= 2;
	}

	volume_slider.reset(new juce::Slider("Volume Slider"));
	addAndMakeVisible(volume_slider.get());
	volume_slider->setRange(0, 100, 1);
	volume_slider->setValue(100);
	volume_slider->setSliderStyle(juce::Slider::LinearHorizontal);
	volume_slider->setTextBoxStyle(juce::Slider::NoTextBox, true, -1, -1);
	volume_slider->addListener(this);

	volume_label.reset(new juce::Label("volume_label", "Volume"));
	volume_label->setEditable(false, false, false);
	volume_label->setJustificationType(juce::Justification::centred);
	addAndMakeVisible(volume_label.get());

	fileselection_button.reset(new juce::TextButton("Select File"));
	addAndMakeVisible(fileselection_button.get());
	fileselection_button->addListener(this);


	playback_button.reset(new juce::TextButton("Play/Pause"));
	addAndMakeVisible(playback_button.get());
	playback_button->addListener(this);

	setSize(600, 300);
}

MainComponent::~MainComponent()
{
	volume_slider = nullptr;
	fileselection_button = nullptr;
	playback_button = nullptr;
	knobs.clear(true);
	knob_labels.clear(true);
}

void MainComponent::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colour(0xff323e44));
}

void MainComponent::resized()
{
	using GridTrackInfo = juce::Grid::TrackInfo;
	using GridFr = juce::Grid::Fr;
	using Grid = juce::Grid;
	using GridItem = juce::GridItem;

	Grid grid;
	grid.templateRows = { GridTrackInfo(GridFr(12)), GridTrackInfo(GridFr(1)), GridTrackInfo(GridFr(1)), GridTrackInfo(GridFr(2)), GridTrackInfo(GridFr(1))};
	for (int i = 0; i < band_number; i++)
	{
		grid.templateColumns.add(GridTrackInfo(GridFr(1)));
	}

	for (int i = 1; i <= band_number; i++)
	{
		GridItem knob_cell{knobs[i-1]};
		knob_cell.setArea(1, i, 1, i);
		grid.items.add(knob_cell);

		GridItem knob_label_cell{ knob_labels[i - 1] };
		knob_label_cell.setArea(2, i, 2, i);
		grid.items.add(knob_label_cell);
	}

	GridItem fsbutton{ fileselection_button.get() };
	fsbutton.setArea(4, 1, 4, 4);
	grid.items.add(fsbutton.withMargin(GridItem::Margin(2, 5, 2, 5)));

	GridItem ppbutton{ playback_button.get() };
	ppbutton.setArea(4, 4, 4, 6);
	grid.items.add(ppbutton.withMargin(GridItem::Margin(2, 5, 2, 5)));

	GridItem volumeslider{ volume_slider.get() };
	volumeslider.setArea(4, 8, 4, 12);
	grid.items.add(volumeslider);

	GridItem volumelabel{ volume_label.get() };
	volumelabel.setArea(4, 7, 4, 8);
	grid.items.add(volumelabel);

	grid.performLayout(getLocalBounds());
}

void MainComponent::sliderValueChanged(juce::Slider* sliderThatWasMoved)
{
	if (sliderThatWasMoved == volume_slider.get()) {

	}
	else {

	}
}

void MainComponent::buttonClicked(juce::Button* buttonThatWasClicked)
{
	if (buttonThatWasClicked == fileselection_button.get()) {

	}
	else if (buttonThatWasClicked == playback_button.get()) {

	}
	else {

	}
}

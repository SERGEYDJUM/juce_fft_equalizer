#include "MainComponent.h"

MainComponent::MainComponent() {
    int band_center = 16;
    for (int i = 0; i < band_number; i++) {
        knobs.add(new juce::Slider("knob" + std::to_string(i)));
        juce::Slider *knob = knobs.getLast();
        addAndMakeVisible(knob);
        knob->setSliderStyle(juce::Slider::LinearBarVertical);
        knob->setTextBoxIsEditable(false);
        knob->setRange(-10, 10, 0.1);
        knob->addListener(this);

        knob_labels.add(new juce::Label("knobLabel" + std::to_string(i),
                                        std::to_string(band_center) + " Hz"));
        juce::Label *label = knob_labels.getLast();
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

    playback_button.reset(new juce::TextButton("Play"));
    addAndMakeVisible(playback_button.get());
    playback_button->addListener(this);
    playback_button->setEnabled(false);

    player.reset(new AudioPlayer([this](AudioPlayer::PlayerState state) {
        switch (state) {
            case AudioPlayer::Stopped:
                playback_button->setButtonText("Play Again");
                break;

            case AudioPlayer::Playing:
                playback_button->setEnabled(true);
                playback_button->setButtonText("Pause");
                break;

            case AudioPlayer::Paused:
                playback_button->setButtonText("Resume");
                break;
        }
    }));

    addChildComponent(player.get());

    setSize(700, 400);
}

MainComponent::~MainComponent() {
    player = nullptr;
    volume_slider = nullptr;
    fileselection_button = nullptr;
    playback_button = nullptr;
    knobs.clear(true);
    knob_labels.clear(true);
}

void MainComponent::resized() {
    using GridTrackInfo = juce::Grid::TrackInfo;
    using GridFr = juce::Grid::Fr;
    using Grid = juce::Grid;
    using GridItem = juce::GridItem;

    Grid grid;
    grid.templateRows = {GridTrackInfo(GridFr(12)), GridTrackInfo(GridFr(1)),
                         GridTrackInfo(GridFr(1)), GridTrackInfo(GridFr(2))};
    for (int i = 0; i < band_number; i++) {
        grid.templateColumns.add(GridTrackInfo(GridFr(1)));
    }

    for (int i = 1; i <= band_number; i++) {
        GridItem knob_cell{knobs[i - 1]};
        knob_cell.setArea(1, i, 1, i);
        grid.items.add(knob_cell);

        GridItem knob_label_cell{knob_labels[i - 1]};
        knob_label_cell.setArea(2, i, 2, i);
        grid.items.add(knob_label_cell);
    }
    GridItem::Margin common_margin{5, 5, 5, 5};
    GridItem fsbutton{fileselection_button.get()};
    fsbutton.setArea(4, 1, 4, 4);
    grid.items.add(fsbutton.withMargin(common_margin));

    GridItem ppbutton{playback_button.get()};
    ppbutton.setArea(4, 4, 4, 6);
    grid.items.add(ppbutton.withMargin(common_margin));

    GridItem volumeslider{volume_slider.get()};
    volumeslider.setArea(4, 8, 4, 12);
    grid.items.add(volumeslider.withMargin(common_margin));

    GridItem volumelabel{volume_label.get()};
    volumelabel.setArea(4, 7, 4, 8);
    grid.items.add(volumelabel);

    grid.performLayout(getLocalBounds());
}

void MainComponent::sliderValueChanged(juce::Slider *sliderThatWasMoved) {
    float slider_value = static_cast<float>(sliderThatWasMoved->getValue());

    if (sliderThatWasMoved == volume_slider.get()) {
        player->setVolumeGain(slider_value/100);
    } else if (knobs[0] == sliderThatWasMoved) {
        player->updateBand(11, 22, slider_value);
    } else if (knobs[1] == sliderThatWasMoved) {
        player->updateBand(23, 45, slider_value);
    } else if (knobs[2] == sliderThatWasMoved) {
        player->updateBand(46, 89, slider_value);
    } else if (knobs[3] == sliderThatWasMoved) {
        player->updateBand(90, 177, slider_value);
    } else if (knobs[4] == sliderThatWasMoved) {
        player->updateBand(178, 354, slider_value);
    } else if (knobs[5] == sliderThatWasMoved) {
        player->updateBand(355, 707, slider_value);
    } else if (knobs[6] == sliderThatWasMoved) {
        player->updateBand(708, 1412, slider_value);
    } else if (knobs[7] == sliderThatWasMoved) {
        player->updateBand(1413, 2818, slider_value);
    } else if (knobs[8] == sliderThatWasMoved) {
        player->updateBand(2819, 5623, slider_value);
    } else if (knobs[9] == sliderThatWasMoved) {
        player->updateBand(5624, 11220, slider_value);
    } else if (knobs[10] == sliderThatWasMoved) {
        player->updateBand(11221, 22387, slider_value);
    }
}

void MainComponent::buttonClicked(juce::Button *buttonThatWasClicked) {
    if (buttonThatWasClicked == fileselection_button.get()) {
        player->selectFile();
    } else if (buttonThatWasClicked == playback_button.get()) {
        if (player->getState() == AudioPlayer::Playing) {
            player->changeState(AudioPlayer::Paused);
        } else {
            player->changeState(AudioPlayer::Playing);
        }
    }
}

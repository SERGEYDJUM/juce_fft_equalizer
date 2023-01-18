#include "MainComponent.h"

MainComponent::MainComponent(unsigned int buffer_size_order) {
    for (int i = 0; i < bands_num; ++i) {
        knobs.add(new Slider);
        auto &knob = *knobs.getLast();
        knob.setSliderStyle(Slider::LinearBarVertical);
        knob.setTextBoxIsEditable(false);
        knob.setRange(0, 2, 0.05);
        knob.setValue(1, NotificationType::dontSendNotification);
        knob.addListener(this);
        addAndMakeVisible(knob);

        knob_labels.add(new Label);
        auto &label = *knob_labels.getLast();
        label.setEditable(false, false, false);
        label.setJustificationType(Justification::centred);
        addAndMakeVisible(label);
    }

    int band_central_harmonic = 16000;
    for (int i = bands_num - 1; i >= 0; --i) {
        knob_labels[i]->setText(std::to_string(band_central_harmonic) + " Hz",
                                NotificationType::dontSendNotification);
        band_central_harmonic /= 2;
    }

    volume_slider.reset(new Slider);
    volume_slider->setRange(0, 100, 1);
    volume_slider->setValue(100);
    volume_slider->setSliderStyle(Slider::LinearHorizontal);
    volume_slider->setTextBoxStyle(Slider::NoTextBox, true, -1, -1);
    volume_slider->addListener(this);
    addAndMakeVisible(volume_slider.get());

    volume_label.reset(new Label);
    volume_label->setText("Volume", NotificationType::dontSendNotification);
    volume_label->setEditable(false, false, false);
    volume_label->setJustificationType(Justification::centred);
    addAndMakeVisible(volume_label.get());

    fileselect_button.reset(new TextButton);
    fileselect_button->setButtonText("Select File");
    fileselect_button->addListener(this);
    addAndMakeVisible(fileselect_button.get());

    playback_button.reset(new TextButton);
    playback_button->setButtonText("Play");
    playback_button->setEnabled(false);
    playback_button->addListener(this);
    addAndMakeVisible(playback_button.get());

    auto player_callback = [this](AudioPlayer *plr) {
        playerStateChanged(plr);
    };
    player.reset(new AudioPlayer(player_callback, buffer_size_order));
    addChildComponent(player.get());

    setWantsKeyboardFocus(true);
    addKeyListener(this);

    setSize(700, 400);
}

MainComponent::~MainComponent() {
    player = nullptr;
    volume_slider = nullptr;
    fileselect_button = nullptr;
    playback_button = nullptr;
    knobs.clear(true);
    knob_labels.clear(true);
}

void MainComponent::resized() {
    using Track = Grid::TrackInfo;
    using Fr = Grid::Fr;
    using Item = GridItem;

    Grid grid;
    grid.templateRows = {Track(Fr(12)), Track(Fr(1)), Track(Fr(1)),
                         Track(Fr(2))};
    for (int i = 0; i < bands_num; ++i) {
        grid.templateColumns.add(Track(Fr(1)));
    }

    for (int i = 1; i <= bands_num; ++i) {
        Item knob_cell{knobs[i - 1]};
        knob_cell.setArea(1, i, 1, i);
        grid.items.add(knob_cell);

        Item knob_label_cell{knob_labels[i - 1]};
        knob_label_cell.setArea(2, i, 2, i);
        grid.items.add(knob_label_cell);
    }

    Item::Margin common_margin{5, 5, 5, 5};
    Item fsbutton{fileselect_button.get()};
    fsbutton.setArea(4, 1, 4, 4);
    grid.items.add(fsbutton.withMargin(common_margin));

    Item ppbutton{playback_button.get()};
    ppbutton.setArea(4, 4, 4, 6);
    grid.items.add(ppbutton.withMargin(common_margin));

    Item volumeslider{volume_slider.get()};
    volumeslider.setArea(4, 8, 4, 12);
    grid.items.add(volumeslider.withMargin(common_margin));

    Item volumelabel{volume_label.get()};
    volumelabel.setArea(4, 7, 4, 8);
    grid.items.add(volumelabel);

    grid.performLayout(getLocalBounds());
}

void MainComponent::sliderValueChanged(Slider *sliderThatWasMoved) {
    float slider_value = static_cast<float>(sliderThatWasMoved->getValue());
    if (sliderThatWasMoved == volume_slider.get()) {
        player->setVolumeGain(slider_value / 100);
    } else {
        for (unsigned int i = 0; i < bands_num; i++) {
            if (knobs[i] == sliderThatWasMoved) {
                player->updateEqualizerBand(i, slider_value);
                break;
            }
        }
    }
}

void MainComponent::buttonClicked(Button *buttonThatWasClicked) {
    if (buttonThatWasClicked == fileselect_button.get()) {
        player->selectFile();
    } else if (buttonThatWasClicked == playback_button.get()) {
        if (player->getState() == AudioPlayer::Playing) {
            player->changeState(AudioPlayer::Paused);
        } else {
            player->changeState(AudioPlayer::Playing);
        }
    }
}

void MainComponent::playerStateChanged(AudioPlayer *playerWhichStateChanged) {
    switch (playerWhichStateChanged->getState()) {
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
}

bool MainComponent::keyPressed(const KeyPress &k, Component *) {
    if (k.getKeyCode() == KeyPress::homeKey) {
        for (auto &knob : knobs) {
            knob->setValue(1);
        }
    } else if (k.getKeyCode() == KeyPress::rightKey) {
        player->jumpSeconds(5);
    } else if (k.getKeyCode() == KeyPress::leftKey) {
        player->jumpSeconds(-5);
    } else if (k.getKeyCode() == KeyPress::spaceKey &&
               playback_button->isEnabled()) {
        buttonClicked(playback_button.get());
    }
#ifdef FFT_DATA_LOGGING
    else if (k.getKeyCode() == KeyPress::downKey) {
        player->logNextBlock();
    }
#endif

    else {
        return false;
    }
    return true;
}

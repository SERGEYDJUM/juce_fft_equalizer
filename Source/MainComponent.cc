//! @file MainComponent.h
//! @authors Джумагельдиев С.А.
//! @note Ответственный: Полевой Д.В.
//! @brief Файл с определением класса MainComponent

#include "MainComponent.h"

MainComponent::MainComponent(unsigned int buffer_size_order) {
    for (int i = 0; i < bands_num_; ++i) {
        knobs_.add(new Slider);
        auto &knob = *knobs_.getLast();
        knob.setSliderStyle(Slider::LinearBarVertical);
        knob.setTextBoxIsEditable(false);
        knob.setRange(0, 2, 0.05);
        knob.setValue(1, NotificationType::dontSendNotification);
        knob.addListener(this);
        addAndMakeVisible(knob);

        knob_labels_.add(new Label);
        auto &label = *knob_labels_.getLast();
        label.setEditable(false, false, false);
        label.setJustificationType(Justification::centred);
        addAndMakeVisible(label);
    }

    int band_central_harmonic = 16000;
    for (int i = bands_num_ - 1; i >= 0; --i) {
        knob_labels_[i]->setText(std::to_string(band_central_harmonic) + " Hz",
                                 NotificationType::dontSendNotification);
        band_central_harmonic /= 2;
    }

    volume_slider_.reset(new Slider);
    volume_slider_->setRange(0, 100, 1);
    volume_slider_->setValue(100);
    volume_slider_->setSliderStyle(Slider::LinearHorizontal);
    volume_slider_->setTextBoxStyle(Slider::NoTextBox, true, -1, -1);
    volume_slider_->addListener(this);
    addAndMakeVisible(volume_slider_.get());

    volume_label_.reset(new Label);
    volume_label_->setText("Volume", NotificationType::dontSendNotification);
    volume_label_->setEditable(false, false, false);
    volume_label_->setJustificationType(Justification::centred);
    addAndMakeVisible(volume_label_.get());

    fileselect_button_.reset(new TextButton);
    fileselect_button_->setButtonText("Select File");
    fileselect_button_->addListener(this);
    addAndMakeVisible(fileselect_button_.get());

    playback_button_.reset(new TextButton);
    playback_button_->setButtonText("Play");
    playback_button_->setEnabled(false);
    playback_button_->addListener(this);
    addAndMakeVisible(playback_button_.get());

    auto player_callback = [this](AudioPlayer *plr) {
        playerStateChanged(plr);
    };
    player_.reset(new AudioPlayer(player_callback, buffer_size_order));
    addChildComponent(player_.get());

    setWantsKeyboardFocus(true);
    addKeyListener(this);

    setSize(700, 400);
}

MainComponent::~MainComponent() {
    player_ = nullptr;
    volume_slider_ = nullptr;
    fileselect_button_ = nullptr;
    playback_button_ = nullptr;
    knobs_.clear(true);
    knob_labels_.clear(true);
}

void MainComponent::resized() {
    Grid grid;
    grid.templateRows = {
        Grid::TrackInfo(Grid::Fr(12)), Grid::TrackInfo(Grid::Fr(1)),
        Grid::TrackInfo(Grid::Fr(1)), Grid::TrackInfo(Grid::Fr(2))};

    for (int i = 0; i < bands_num_; ++i) {
        grid.templateColumns.add(Grid::TrackInfo(Grid::Fr(1)));
    }

    for (int i = 1; i <= bands_num_; ++i) {
        GridItem knob_cell{knobs_[i - 1]};
        knob_cell.setArea(1, i, 1, i);
        grid.items.add(knob_cell);

        GridItem knob_label_cell{knob_labels_[i - 1]};
        knob_label_cell.setArea(2, i, 2, i);
        grid.items.add(knob_label_cell);
    }

    GridItem::Margin common_margin{5, 5, 5, 5};
    GridItem fsbutton{fileselect_button_.get()};
    fsbutton.setArea(4, 1, 4, 4);
    grid.items.add(fsbutton.withMargin(common_margin));

    GridItem ppbutton{playback_button_.get()};
    ppbutton.setArea(4, 4, 4, 6);
    grid.items.add(ppbutton.withMargin(common_margin));

    GridItem volumeslider{volume_slider_.get()};
    volumeslider.setArea(4, 8, 4, 12);
    grid.items.add(volumeslider.withMargin(common_margin));

    GridItem volumelabel{volume_label_.get()};
    volumelabel.setArea(4, 7, 4, 8);
    grid.items.add(volumelabel);

    grid.performLayout(getLocalBounds());
}

void MainComponent::sliderValueChanged(Slider *sliderThatWasMoved) {
    float slider_value = static_cast<float>(sliderThatWasMoved->getValue());
    if (sliderThatWasMoved == volume_slider_.get()) {
        player_->setVolumeGain(slider_value / 100);
    } else {
        for (unsigned int i = 0; i < bands_num_; i++) {
            if (knobs_[i] == sliderThatWasMoved) {
                player_->updateEqualizerBand(i, slider_value);
                break;
            }
        }
    }
}

void MainComponent::buttonClicked(Button *buttonThatWasClicked) {
    if (buttonThatWasClicked == fileselect_button_.get()) {
        player_->selectFile();
    } else if (buttonThatWasClicked == playback_button_.get()) {
        if (player_->getState() == AudioPlayer::Playing) {
            player_->changeState(AudioPlayer::Paused);
        } else {
            player_->changeState(AudioPlayer::Playing);
        }
    }
}

void MainComponent::playerStateChanged(AudioPlayer *playerWhichStateChanged) {
    switch (playerWhichStateChanged->getState()) {
        case AudioPlayer::Stopped:
            playback_button_->setButtonText("Play Again");
            break;

        case AudioPlayer::Playing:
            playback_button_->setEnabled(true);
            playback_button_->setButtonText("Pause");
            break;

        case AudioPlayer::Paused:
            playback_button_->setButtonText("Resume");
            break;
    }
}

bool MainComponent::keyPressed(const KeyPress &k, Component *) {
    if (k.getKeyCode() == KeyPress::homeKey) {
        for (auto &knob : knobs_) {
            knob->setValue(1);
        }
    } else if (k.getKeyCode() == KeyPress::rightKey) {
        player_->jumpSeconds(5);
    } else if (k.getKeyCode() == KeyPress::leftKey) {
        player_->jumpSeconds(-5);
    } else if (k.getKeyCode() == KeyPress::spaceKey &&
               playback_button_->isEnabled()) {
        buttonClicked(playback_button_.get());
    }
#ifdef FFT_DATA_LOGGING
    else if (k.getKeyCode() == KeyPress::downKey) {
        player_->logNextBlock();
    }
#endif

    else {
        return false;
    }
    return true;
}

//! @file AudioPlayer.cc
//! @authors Джумагельдиев С.А.
//! @note Ответственный: Полевой Д.В.
//! @brief Файл с определением класса AudioPlayer

#include "AudioPlayer.h"

#include <JuceHeader.h>

AudioPlayer::AudioPlayer(std::function<void(AudioPlayer *)> callback,
                         unsigned int buffer_size_order)
    : state_{Stopped},
      state_callback_{callback},
      equalizer_{buffer_size_order} {
    format_manager_.registerBasicFormats();
    transport_source_.addChangeListener(this);
    setAudioChannels(0, 2);

    auto new_device_sestup = deviceManager.getAudioDeviceSetup();
    new_device_sestup.bufferSize = 1 << buffer_size_order;
    deviceManager.setAudioDeviceSetup(new_device_sestup, true);
}

void AudioPlayer::changeState(PlayerState new_state) {
    if (state_ != new_state) {
        state_ = new_state;
        switch (state_) {
            case Stopped:
                transport_source_.stop();
                transport_source_.setPosition(0.0);
                playback_position_ = 0.0;
                break;

            case Playing:
                transport_source_.start();
                transport_source_.setPosition(playback_position_);
                break;

            case Paused:
                playback_position_ = transport_source_.getCurrentPosition();
                transport_source_.stop();
                break;
        }
        state_callback_(this);
    }
}

void AudioPlayer::changeListenerCallback(ChangeBroadcaster *source) {
    if (source == &transport_source_) {
        if (!transport_source_.isPlaying() &&
            transport_source_.hasStreamFinished())
            changeState(Stopped);
    }
}

void AudioPlayer::getNextAudioBlock(
    const AudioSourceChannelInfo &bufferToFill) {
    if (reader_source_.get() == nullptr) {
        bufferToFill.clearActiveBufferRegion();
    } else {
        transport_source_.getNextAudioBlock(bufferToFill);
        if (state_ == Playing) equalizer_.equalizeBuffer(bufferToFill);
    }
}

void AudioPlayer::releaseResources() { transport_source_.releaseResources(); }

AudioPlayer::~AudioPlayer() {
    reader_source_ = nullptr;
    chooser_ = nullptr;
}

void AudioPlayer::selectFile() {
    chooser_ = std::make_unique<FileChooser>("Select audiofile to play...",
                                             File::getCurrentWorkingDirectory(), "*.wav;*.mp3;*.flac");
    auto fc_flags =
        FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles;
    chooser_->launchAsync(fc_flags, [this](const FileChooser &file_chooser) {
        auto file = file_chooser.getResult();
        if (file != File{}) {
            auto *reader = format_manager_.createReaderFor(file);
            if (reader != nullptr) {
                changeState(Stopped);
                auto new_reader_source =
                    std::make_unique<AudioFormatReaderSource>(reader, true);
                transport_source_.setSource(new_reader_source.get(), 0, nullptr,
                                            reader->sampleRate);
                std::swap(new_reader_source, reader_source_);
                equalizer_.updateSampleRate(
                    static_cast<float>(reader->sampleRate));
                changeState(Playing);
            }
        }
    });
}

void AudioPlayer::setVolumeGain(float new_level) {
    if (new_level > 1 || new_level < 0)
        throw std::domain_error("Volume gain is out of range");
    transport_source_.setGain(new_level);
}

void AudioPlayer::updateEqualizerBand(unsigned int band, float gain) {
    equalizer_.updateBand(band, gain);
}

void AudioPlayer::jumpSeconds(double seconds) {
    if (state_ != Playing) return;
    auto new_pos = transport_source_.getCurrentPosition() + seconds;
    if (new_pos < transport_source_.getLengthInSeconds()) {
        if (new_pos >= 0) {
            transport_source_.setPosition(new_pos);
        } else {
            transport_source_.setPosition(0);
        }
    }
}

void AudioPlayer::prepareToPlay(int samplesPerBlockExpected,
                                double sampleRate) {
    transport_source_.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

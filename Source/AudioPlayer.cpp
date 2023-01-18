#include "AudioPlayer.hpp"

#include <JuceHeader.h>

AudioPlayer::AudioPlayer(std::function<void(AudioPlayer *)> callback,
                         unsigned int buffer_size_order)
    : state{Stopped}, state_callback{callback}, equalizer{buffer_size_order} {
    format_manager.registerBasicFormats();
    transport_source.addChangeListener(this);
    setAudioChannels(0, 2);

    auto new_device_sestup = deviceManager.getAudioDeviceSetup();
    new_device_sestup.bufferSize = 1 << buffer_size_order;
    deviceManager.setAudioDeviceSetup(new_device_sestup, true);
}

AudioPlayer::PlayerState AudioPlayer::getState() { return state; }

void AudioPlayer::changeState(PlayerState new_state) {
    if (state != new_state) {
        state = new_state;
        switch (state) {
            case Stopped:
                transport_source.stop();
                transport_source.setPosition(0.0);
                playback_position = 0.0;
                break;

            case Playing:
                transport_source.start();
                transport_source.setPosition(playback_position);
                break;

            case Paused:
                playback_position = transport_source.getCurrentPosition();
                transport_source.stop();
                break;
        }
        state_callback(this);
    }
}

void AudioPlayer::changeListenerCallback(ChangeBroadcaster *source) {
    if (source == &transport_source) {
        if (!transport_source.isPlaying() &&
            transport_source.hasStreamFinished())
            changeState(Stopped);
    }
}

void AudioPlayer::getNextAudioBlock(
    const AudioSourceChannelInfo &bufferToFill) {
    if (reader_source.get() == nullptr) {
        bufferToFill.clearActiveBufferRegion();
    } else {
        transport_source.getNextAudioBlock(bufferToFill);
        if (state == Playing) equalizer.equalizeBuffer(bufferToFill);
    }
}

void AudioPlayer::releaseResources() { transport_source.releaseResources(); }

AudioPlayer::~AudioPlayer() {
    reader_source = nullptr;
    chooser = nullptr;
}

void AudioPlayer::selectFile() {
    chooser = std::make_unique<FileChooser>("Select audiofile to play...",
                                            File{}, "*.wav;*.mp3;*.flac");
    auto fc_flags =
        FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles;
    chooser->launchAsync(fc_flags, [this](const FileChooser &file_chooser) {
        auto file = file_chooser.getResult();
        if (file != File{}) {
            auto *reader = format_manager.createReaderFor(file);
            if (reader != nullptr) {
                changeState(Stopped);
                auto new_reader_source =
                    std::make_unique<AudioFormatReaderSource>(reader, true);
                transport_source.setSource(new_reader_source.get(), 0, nullptr,
                                           reader->sampleRate);
                std::swap(new_reader_source, reader_source);
                equalizer.updateSampleRate(
                    static_cast<float>(reader->sampleRate));
                changeState(Playing);
            }
        }
    });
}

void AudioPlayer::setVolumeGain(float new_level) {
    transport_source.setGain(new_level);
}

void AudioPlayer::updateEqualizerBand(unsigned int band, float gain) {
    equalizer.updateBand(band, gain);
}

void AudioPlayer::jumpSeconds(double seconds) {
    if (state != Playing) return;
    auto new_pos = transport_source.getCurrentPosition() + seconds;
    if (new_pos < transport_source.getLengthInSeconds()) {
        if (new_pos >= 0) {
            transport_source.setPosition(new_pos);
        } else {
            transport_source.setPosition(0);
        }
    }
}

void AudioPlayer::prepareToPlay(int samplesPerBlockExpected,
                                double sampleRate) {
    transport_source.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
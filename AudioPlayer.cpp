#include "AudioPlayer.h"

#include <JuceHeader.h>

AudioPlayer::AudioPlayer(std::function<void(PlayerState)> state_caller) : state{Stopped}, state_callback{state_caller}
{
    format_manager.registerBasicFormats();
    transport_source.addChangeListener(this);
    setAudioChannels(0, 2);
}

AudioPlayer::PlayerState AudioPlayer::getState() { return state; }

void AudioPlayer::changeState(PlayerState new_state)
{
    if (state != new_state)
    {
        state = new_state;
        switch (state)
        {
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
        state_callback(state);
    }
}

void AudioPlayer::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    if (source == &transport_source)
    {
        if (!transport_source.isPlaying() && transport_source.hasStreamFinished())
            changeState(Stopped);
    }
}

void AudioPlayer::getNextAudioBlock(
    const juce::AudioSourceChannelInfo &bufferToFill)
{
    if (reader_source.get() == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }
    transport_source.getNextAudioBlock(bufferToFill);
}

void AudioPlayer::prepareToPlay(int samplesPerBlockExpected,
                                double sampleRate)
{
    transport_source.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void AudioPlayer::releaseResources() { transport_source.releaseResources(); }

AudioPlayer::~AudioPlayer()
{
    shutdownAudio();
    releaseResources();
    reader_source = nullptr;
    chooser = nullptr;
}

void AudioPlayer::selectFile()
{
    chooser = std::make_unique<juce::FileChooser>("Select a file to play...",
                                                  juce::File{}, "*.wav;*.mp3");
    auto chooser_flags = juce::FileBrowserComponent::openMode |
                         juce::FileBrowserComponent::canSelectFiles;
    chooser->launchAsync(chooser_flags, [this](const juce::FileChooser &fc)
                         {
    auto file = fc.getResult();
    if (file != juce::File{}) {
      auto* reader = format_manager.createReaderFor(file);
      if (reader != nullptr) {
        changeState(Stopped);
        auto new_source =
            std::make_unique<juce::AudioFormatReaderSource>(reader, true);
        transport_source.setSource(new_source.get(), 0, nullptr,
                                   reader->sampleRate);
        reader_source.reset(new_source.release());
      }
    } });
}

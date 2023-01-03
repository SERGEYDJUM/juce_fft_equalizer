#pragma once
#include <JuceHeader.h>

class AudioPlayer : public juce::AudioAppComponent,
                    public juce::ChangeListener {
 public:
  enum TransportState { Stopped, Playing, Paused };
  AudioPlayer(std::function<void(TransportState)> state_caller =
                  [](TransportState state) {});
  ~AudioPlayer() override;

  TransportState getState();
  void changeState(TransportState new_state);
  void selectFile();

 private:
  double playback_position = 0.0;
  TransportState state;
  juce::AudioFormatManager format_manager;
  juce::AudioTransportSource transport_source;

  std::unique_ptr<juce::FileChooser> chooser;
  std::unique_ptr<juce::AudioFormatReaderSource> reader_source;
  std::function<void(TransportState)> state_callback;

  void changeListenerCallback(juce::ChangeBroadcaster* source) override;
  void getNextAudioBlock(
      const juce::AudioSourceChannelInfo& bufferToFill) override;
  void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
  void releaseResources() override;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPlayer)
};

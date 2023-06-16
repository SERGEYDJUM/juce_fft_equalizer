# FFT Equalizer: Overview

11-band FFT Equalizer built on JUCE framework.

Supports wav, mp3 and flac audiofiles for now.

# Building and installing

It assumes that CMake, Git and build tools are already installed. 

0. If you are building on linux, install ```juce-tools``` packages.
1. ```git clone https://github.com/SERGEYDJUM/juce_fft_equalizer.git```
2. ```cd juce_fft_equalizer```
4. ```cmake -S . -B build```
5. ```cmake --build build --config Release```
6. ```cmake --install build --prefix .```

Executable will be in ./bin and Doxygen-generated documentation in ./docs

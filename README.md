# Sidechain Receiver
VST3 plugin that receives sidechain audio

## What is this?
It's a VST3 plugin that receives sidechain audio. That's it.

It's intended for use in Renoise.

### Why?
Renoise (my DAW of choice) cannot arbitrarily route track audio. This fixes 
that.

Most DAWs may route track audio to any other track.

However, Renoise *only* permits routing track audio to Send tracks, which are 
awkward to use.

So, given that Renoise supports VST3 sidechaining, no less, ships with a 
sidechain routing device, I created a VST3 sidechain receiver plugin. In other 
words, we're free from Send tracks.

## Installation (Linux)
```
git clone https://github.com/stygian-phrygian/sidechain-receiver
cd sidechain-receiver
cmake -S . -B build
cmake --build build
cp -r ./build/bin/SidechainReceiver.vst3 ~/.vst3/ # or wherever your vst3 plugins are installed
```

## Usage (Renoise)
1. Place a `#Sidechain` device on a track
2. Place this `Sidechain Receiver` plugin on any track *to the right* (Renoise processes left to right)
3. Connect them

## Shoutouts
This project is made possible through the Distrho DPF plugin 
framework: https://github.com/DISTRHO/DPF/


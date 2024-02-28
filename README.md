# guitarix

![guitarix](https://a.fsdn.com/con/app/proj/guitarix/screenshots/Guitarix_Dark.png/max/max/1)

Guitarix is a modular, virtual amplifier for Linux.
With Guitarix you can choose different preamp and amp models,
load *.nam files with the Neural Amp Modeler module,
combine them with various effects and speaker cabinet emulations
and/or load your own Impulse Response files
to come up with your very own tones.
Guitarix comes as a standalone application or as [vst3 plugin](https://github.com/brummer10/guitarix.vst).
Its modules are also available in the LV2 plugin format, 
which you can incorporate into your DAW of choice. 
Furthermore, it can even be run headless, so you can turn a Raspberry Pi, 
or any other such devices, into a dedicated amp modeler. 
You can even control Guitarix via a MIDI controller or foot-board.

Guitarix comes with an extensive list of effects 
including compression, distortion, modulation, reverb, delay, EQ, etc. 
Some of the effects modules that are included in Guitarix 
are influenced by some popular hardware units, 
for example the Tube Screamer is, not surprisingly, based off of the Ibanez Tube Screamer.
Guitarix can also load up LAPSPA and LV2 plugins to comply the effect chain. 


## Building guitarix from source code

- git clone https://github.com/brummer10/guitarix.git
- cd guitarix
- git submodule update --init --recursive
- cd trunk
- ./waf configure --prefix=/usr  --includeresampler --includeconvolver --optimization 
- ./waf build
- sudo ./waf install

## (build) Dependencies

- gperf,
- intltool,
- libavahi-gobject-dev,
- libbluetooth-dev 
- libboost-dev,
- libboost-iostreams-dev,
- libboost-system-dev,
- libboost-thread-dev,
- libeigen3-dev,
- libgtk-3-dev,
- libgtkmm-3.0-dev,
- libjack-dev | libjack-jackd2-dev,
- liblilv-dev,
- liblrdf0-dev,
- libsndfile1-dev,
- lv2-dev,
- python3,
- sassc,


# guitarix

![guitarix](https://a.fsdn.com/con/app/proj/guitarix/screenshots/Guitarix_Dark.png/max/max/1)

Guitarix is a modular, virtual amplifier for Linux.
With Guitarix you can choose different preamp and amp models
and /or could load [*.nam files](https://tonehunt.org/all) with the [Neural Amp Modeler](https://github.com/sdatkinson/NeuralAmpModelerCore) modules,
or load [*.json or .aidax files](https://cloud.aida-x.cc/all) with the [RTNeural](https://github.com/jatinchowdhury18/RTNeural) modules, 
to simulate a specific hardware unit.
Combine them with various effects and speaker cabinet emulations
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
- libfftw3-dev,
- lv2-dev,
- python3,
- sassc,

## Hardware Optimization and Containerized Deployment

Guitarix can be easily built with hardware optimizations and deployed in a containerized environment using GuitarixContainer, a Docker-based solution. This approach ensures the code is automatically built for your hardware, enabling low-latency performance, especially when running Neural Amp Modeler (NAM) module. Perfect for devices like Raspberry Pi or laptop/workstation setups. Learn more at the [GuitarixContainer](https://github.com/fjammes/GuitarixContainer) GitHub repository.


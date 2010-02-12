#include <map>
#include <set>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <cmath>
#include <cstring>
#include <gtk/gtk.h>
#include <jack/jack.h>
#include <sndfile.h>
using namespace std;
#include "guitarix.h"

namespace gx_gui {

ParamMap parameter_map;

static ParameterGroups pgroups;
static ParameterNames pnames;

string BaseParameter::group() const
{
     cout << id << endl;
     assert(false);
}

string BaseParameter::name() const
{
     cout << id << endl;
     assert(false);
}

string Parameter::group() const
{
     return _group;
}

string Parameter::name() const
{
     return _name;
}

void Parameter::init()
{
  _group = pgroups[group_id()];
  assert(_group != "");
  _name = pnames[id];
  assert(_name != "");
}

void initGroups()
{
     pgroups.insert("jconv","JConvolver");
     pgroups.insert("amp","Amplifier");
     pgroups.insert("amp.tone","Tone");
     pgroups.insert("shaper","Shaper");
     pgroups.insert("noise_gate","Noise Gate");
     pgroups.insert("anti_aliase","Anti Alias");
     pgroups.insert("amp.oversample","Oversampling");
     pgroups.insert("amp.bass_boost","Bass Boost");
     pgroups.insert("convolve","Convolver");
     pgroups.insert("preamp","Pre-Amp");
     pgroups.insert("drive","Drive");
     pgroups.insert("tube","Tube 1");
     pgroups.insert("tube.vibrato","Tube 1 Vibrato");
     pgroups.insert("tube2","Tube 2");
     pgroups.insert("compressor","Compressor");
     pgroups.insert("overdrive","Overdrive");
     pgroups.insert("distortion","Distortion");
     pgroups.insert("freeverb","Freeverb");
     pgroups.insert("IR","IR");
     pgroups.insert("crybaby","Crybaby");
     pgroups.insert("echo","Echo");
     pgroups.insert("delay","Delay");
     pgroups.insert("chorus","Chorus");
     pgroups.insert("MultiBandFilter","Multiband Filter");
     pgroups.insert("midi_out.channel_1","Midi Out 1");
     pgroups.insert("midi_out.channel_2","Midi Out 2");
     pgroups.insert("midi_out.channel_3","Midi Out 3");
     pgroups.insert("beat_detector","Beat Detector");
}

void initNames()
{
     pnames.insert("amp.feedback", "Feedback");
     pnames.insert("amp.feedforward", "Feedforward");
     pnames.insert("amp.balance", "Balance");
     pnames.insert("jconv.left_delay", "Left Delay");
     pnames.insert("jconv.right_delay", "Right Delay");
     pnames.insert("jconv.left_gain", "Left Gain");
     pnames.insert("jconv.right_gain", "Right Gain");
     pnames.insert("jconv.wet_dry", "wet/dry");
     pnames.insert("amp.in_level", "in level");
     pnames.insert("amp.out_master", "out master");
     pnames.insert("amp.tone.bass", "Bass");
     pnames.insert("amp.tone.middle", "Middle");
     pnames.insert("amp.tone.treble", "Treble");
     pnames.insert("shaper.on_off", "on/off");
     pnames.insert("shaper.sharper", "Sharper");
     pnames.insert("noise_gate.on_off", "on/off");
     pnames.insert("noise_gate.threshold", "Threshold");
     pnames.insert("anti_aliase.on_off", "on/off");
     pnames.insert("anti_aliase.feedback", "Feedback");
     pnames.insert("amp.oversample.on_off", "on/off");
     pnames.insert("amp.bass_boost.on_off", "on/off");
     pnames.insert("convolve.type", "Type");
     pnames.insert("preamp.on_off", "on/off");
     pnames.insert("preamp.atan", "atan");
     pnames.insert("preamp.drive", "drive");
     pnames.insert("amp.fuzz", "fuzz");
     pnames.insert("amp.threshold", "threshold");
     pnames.insert("drive.on_off", "on/off");
     pnames.insert("drive.value", "value");
     pnames.insert("tube.on_off", "on/off");
     pnames.insert("tube.count", "count");
     pnames.insert("tube.vibrato.on_off", "on/off");
     pnames.insert("tube.vibrato", "vibrato");
     pnames.insert("tube2.on_off", "on/off");
     pnames.insert("tube2.count", "count");
     pnames.insert("tube2.resonanz", "resonanz");
     pnames.insert("tube2.vibrato", "vibrato");
     pnames.insert("compressor.ratio", "ratio");
     pnames.insert("compressor.on_off", "on/off");
     pnames.insert("compressor.knee", "knee");
     pnames.insert("compressor.ratio", "ratio");
     pnames.insert("compressor.threshold", "threshold");
     pnames.insert("compressor.attack", "attack");
     pnames.insert("compressor.release", "release");
     pnames.insert("overdrive.drive", "drive");
     pnames.insert("overdrive.on_off", "on/off");
     pnames.insert("distortion.drive", "drive");
     pnames.insert("distortion.dialog", "dialog");
     pnames.insert("distortion.drive", "drive");
     pnames.insert("distortion.level", "level");
     pnames.insert("distortion.gain", "gain");
     pnames.insert("distortion.high_freq", "high freq");
     pnames.insert("distortion.low_freq", "low freq");
     pnames.insert("distortion.low_highpass", "low highpass");
     pnames.insert("distortion.low_highcutoff", "low highcutoff");
     pnames.insert("distortion.trigger", "trigger");
     pnames.insert("distortion.vibrato", "vibrato");
     pnames.insert("freeverb.RoomSize", "RoomSize");
     pnames.insert("freeverb.dialog", "dialog");
     pnames.insert("freeverb.RoomSize", "RoomSize");
     pnames.insert("freeverb.damp", "damp");
     pnames.insert("freeverb.wet_dry", "wet/dry");
     pnames.insert("IR.freq", "freq");
     pnames.insert("IR.dialog", "dialog");
     pnames.insert("IR.freq", "freq");
     pnames.insert("IR.peak", "peak");
     pnames.insert("IR.bandwidth", "bandwidth");
     pnames.insert("IR.auto_freq", "auto freq");
     pnames.insert("crybaby.wah", "wah");
     pnames.insert("crybaby.dialog", "dialog");
     pnames.insert("crybaby.level", "level");
     pnames.insert("crybaby.wet_dry", "wet/dry");
     pnames.insert("crybaby.autowah", "autowah");
     pnames.insert("echo.percent", "percent");
     pnames.insert("echo.time", "time");
     pnames.insert("echo.on_off", "on/off");
     pnames.insert("delay.delay", "delay");
     pnames.insert("delay.gain", "gain");
     pnames.insert("delay.on_off", "on/off");
     pnames.insert("chorus.level", "level");
     pnames.insert("chorus.dialog", "dialog");
     pnames.insert("chorus.delay", "delay");
     pnames.insert("chorus.depth", "depth");
     pnames.insert("chorus.freq", "freq");
     pnames.insert("MultiBandFilter.MultiBandFilter", "MultiBandFilter");
     pnames.insert("MultiBandFilter.f31_25", "f31_25");
     pnames.insert("MultiBandFilter.f62_5", "f62_5");
     pnames.insert("MultiBandFilter.f125", "f125");
     pnames.insert("MultiBandFilter.f250", "f250");
     pnames.insert("MultiBandFilter.f500", "f500");
     pnames.insert("MultiBandFilter.f1k", "f1k");
     pnames.insert("MultiBandFilter.f2k", "f2k");
     pnames.insert("MultiBandFilter.f4k", "f4k");
     pnames.insert("MultiBandFilter.f8k", "f8k");
     pnames.insert("MultiBandFilter.f16k", "f16k");
     pnames.insert("midi_out.channel_1.velocity", "velocity");
     pnames.insert("midi_out.channel_1.volume", "volume");
     pnames.insert("midi_out.channel_1.autogain", "autogain");
     pnames.insert("midi_out.channel_1.channel", "channel");
     pnames.insert("midi_out.channel_1.program", "program");
     pnames.insert("midi_out.channel_1.oktave", "oktave");
     pnames.insert("midi_out.channel_1.sensity", "sensity");
     pnames.insert("midi_out.channel_1.auto_pitch", "auto_pitch");
     pnames.insert("midi_out.channel_2.velocity", "velocity");
     pnames.insert("midi_out.channel_2.volume", "volume");
     pnames.insert("midi_out.channel_2.autogain", "autogain");
     pnames.insert("midi_out.channel_2.channel", "channel");
     pnames.insert("midi_out.channel_2.program", "program");
     pnames.insert("midi_out.channel_2.oktave", "oktave");
     pnames.insert("midi_out.channel_2.sensity", "sensity");
     pnames.insert("midi_out.channel_2.on_off", "on_off");
     pnames.insert("midi_out.channel_2.auto_pitch", "auto_pitch");
     pnames.insert("midi_out.channel_3.velocity", "velocity");
     pnames.insert("midi_out.channel_3.volume", "volume");
     pnames.insert("midi_out.channel_3.autogain", "autogain");
     pnames.insert("midi_out.channel_3.channel", "channel");
     pnames.insert("midi_out.channel_3.program", "program");
     pnames.insert("midi_out.channel_3.oktave", "oktave");
     pnames.insert("midi_out.channel_3.sensity", "sensity");
     pnames.insert("midi_out.channel_3.on_off", "on_off");
     pnames.insert("midi_out.channel_3.auto_pitch", "auto_pitch");
     pnames.insert("beat_detector.stepper", "stepper");
     pnames.insert("beat_detector.note_off", "note_off");
     pnames.insert("beat_detector.atack_gain", "atack_gain");
     pnames.insert("beat_detector.beat_gain", "beat_gain");
     pnames.insert("beat_detector.midi_gain", "midi_gain");
}

void ParamMap::insert(const BaseParameter* param)
{
     addr_map.insert(pair<const void*, const BaseParameter*>(param->f.value, param));
     id_map.insert(pair<string, const BaseParameter*>(param->id, param));
}

void initParams(gx_engine::GxEngine* e)
{
     parameter_map.insert(new Parameter("amp.feedback", &e->fslider0, 0.000000f, -1.000000f, 1.000000f, 1.000000e-02f));
     parameter_map.insert(new Parameter("amp.feedforward", &e->fslider23, 0.000000f, -1.000000f, 1.000000f, 1.000000e-02f));
     parameter_map.insert(new Parameter("amp.feedforward", &e->fslider23, 0.000000f, -1.000000f, 1.000000f, 1.000000e-02f));
     parameter_map.insert(new Parameter("amp.balance", &e->fslider25, 0.f, -1.f, 1.f, 1.e-01f));
     parameter_map.insert(new Parameter("jconv.left_delay", &e->fsliderdel0,  0.f, 0.f, 5000.0f, 10.f));
     parameter_map.insert(new Parameter("jconv.right_delay", &e->fsliderdel1,  0.f, 0.f, 5000.0f, 10.f));
     parameter_map.insert(new Parameter("jconv.left_gain", &e->fjc_ingain,  0.f, -20.f, 20.f, 0.1f));
     parameter_map.insert(new Parameter("jconv.right_gain", &e->fjc_ingain1,  0.f, -20.f, 20.f, 0.1f));
     parameter_map.insert(new Parameter("jconv.wet_dry", &e->fslider24,  0.f, -1.f, 1.f, 1.e-01f));
     parameter_map.insert(new Parameter("amp.in_level", &e->fslider3, 0.f, -40.f, 40.f, 0.1f));
     parameter_map.insert(new Parameter("amp.out_master", &e->fslider17, 0.f, -40.f, 40.f, 0.1f));
     parameter_map.insert(new Parameter("amp.tone.bass", &e->fslider_tone2, 0.f, -20.f, 20.f, 0.1f));
     parameter_map.insert(new Parameter("amp.tone.middle", &e->fslider_tone1, 0.f, -20.f, 20.f, 0.1f));
     parameter_map.insert(new Parameter("amp.tone.treble", &e->fslider_tone0, 0.f, -20.f, 20.f, 0.1f));
     parameter_map.insert(new Parameter("shaper.on_off", &e->fng, 0));
     parameter_map.insert(new Parameter("shaper.sharper", &e->fsharp0, 1.f, 1.f, 10.f, 1.0f));
     parameter_map.insert(new Parameter("noise_gate.on_off", &e->fnoise_g, 0));
     parameter_map.insert(new Parameter("noise_gate.threshold", &e->fnglevel, 0.017f, 0.01f, 0.21f, 0.001f));
     parameter_map.insert(new Parameter("anti_aliase.on_off", &e->antialis0, 0));
     parameter_map.insert(new Parameter("anti_aliase.feedback", &e->faas1, 0.3f, 0.3f, 0.9f, 0.01f));
     parameter_map.insert(new Parameter("amp.oversample.on_off", &e->fupsample, 0));
     parameter_map.insert(new Parameter("amp.bass_boost.on_off", &e->fboost, 0));
     parameter_map.insert(new Parameter("convolve.type", &e->fconvolve, 0));
     parameter_map.insert(new Parameter("preamp.on_off", &e->fcheckbox1, 0));
     parameter_map.insert(new Parameter("preamp.drive",  &e->fprdr, 0));
     parameter_map.insert(new Parameter("preamp.atan", &e->fatan, 1.f, 1.f, 10.f, 1.0f));
     parameter_map.insert(new Parameter("amp.fuzz", &e->fthreshold, 1.f, 0.f, 1.f, 0.01f));
     //FIXME
     //parameter_map.insert(new Parameter("amp.threshold", &e->ffuse,3, {"    off","    clip","foldback"}));
     parameter_map.insert(new Parameter("drive.on_off", &e->fprdr, 0));
     parameter_map.insert(new Parameter("drive.value", &e->fpredrive, 1.f, 1.f, 10.f, 1.0f));
     parameter_map.insert(new Parameter("tube.on_off", &e->ftube, 0));
     parameter_map.insert(new Parameter("tube.count", &e->ffuzzytube, 1.f, -3.f, 10.f, 1.0f));
     parameter_map.insert(new Parameter("tube.vibrato.on_off", &e->fresoon, 0));
     parameter_map.insert(new Parameter("tube.vibrato", &e->fvibrato, 0.f, 0.f, 2.f, 0.02f));
     parameter_map.insert(new Parameter("tube2.on_off", &e->ftube3, 0));
     parameter_map.insert(new Parameter("tube2.count", &e->fresotube3, 1.f, -3.f, 10.f, 1.0f));
     parameter_map.insert(new Parameter("tube2.resonanz", &e->fresotube1, 0.5f, 0.f, 0.9f, 0.01f));
     parameter_map.insert(new Parameter("tube2.vibrato", &e->fresotube2, 1.f, 0.f, 1.f, 0.01f));
     parameter_map.insert(new Parameter("compressor.ratio", &e->fentrycom2, 2.000000f, 1.000000f, 20.000000f, 0.100000f));
     parameter_map.insert(new Parameter("compressor.on_off", &e->fcheckboxcom1, 0));
     parameter_map.insert(new Parameter("compressor.knee", &e->fentrycom1, 3.000000f, 0.000000f, 20.000000f, 0.100000f));
     parameter_map.insert(new Parameter("compressor.ratio", &e->fentrycom2, 2.000000f, 1.000000f, 20.000000f, 0.100000f));
     parameter_map.insert(new Parameter("compressor.threshold", &e->fentrycom0, -20.000000f, -96.000000f, 10.000000f, 0.100000f));
     parameter_map.insert(new Parameter("compressor.attack", &e->fslidercom0, 2.000000e-03f, 0.000000f, 1.000000f, 1.000000e-03f));
     parameter_map.insert(new Parameter("compressor.release", &e->fslidercom1, 0.500000f, 0.000000f, 10.000000f, 1.000000e-02f));
     parameter_map.insert(new Parameter("overdrive.drive", &e->drive, 1.f, 1.f, 20.f, 0.1f));
     parameter_map.insert(new Parameter("overdrive.on_off", &e->foverdrive4, 0));
     parameter_map.insert(new Parameter("distortion.drive", &e->fslider9, 0.64f, 0.f, 1.f, 1.e-02f));
     parameter_map.insert(new Parameter("distortion.dialog", &e->fcheckbox4, 0));
     parameter_map.insert(new Parameter("distortion.drive", &e->fslider9, 0.64f, 0.f, 1.f, 1.e-02f));
     parameter_map.insert(new Parameter("distortion.level", &e->fslider8, 1.000000e-02f, 0.0f, 0.50f, 1.000000e-02f));
     parameter_map.insert(new Parameter("distortion.gain", &e->fslider10, 2.0f, -10.0f, 10.0f, 0.1f));
     parameter_map.insert(new Parameter("distortion.high_freq", &e->fentry1, 130.0f, 20.0f, 7040.0f, 10.0f));
     parameter_map.insert(new Parameter("distortion.low_freq", &e->fentry0, 5000.0f, 20.0f, 12000.0f, 10.0f));
     parameter_map.insert(new Parameter("distortion.low_highpass", &e->fcheckbox2, 0));
     parameter_map.insert(new Parameter("distortion.high_freq", &e->fslider6, 5000.0f, 1000.0f, 12000.0f, 10.0f));
     parameter_map.insert(new Parameter("distortion.low_freq", &e->fslider7, 130.0f, 20.0f, 1000.0f, 10.0f));
     parameter_map.insert(new Parameter("distortion.low_highcutoff", &e->fcheckbox3, 0));
     parameter_map.insert(new Parameter("distortion.trigger", &e->fslider4, 0.12f, 0.0f, 1.0f, 1.000000e-02f));
     parameter_map.insert(new Parameter("distortion.vibrato", &e->fslider5, 1.0f, 0.0f, 1.0f, 1.000000e-02f));
     parameter_map.insert(new Parameter("freeverb.RoomSize", &e->fslider16, 0.500000f, 0.000000f, 1.000000f, 2.500000e-02f));
     parameter_map.insert(new Parameter("freeverb.dialog", &e->fcheckbox6, 0));
     parameter_map.insert(new Parameter("freeverb.RoomSize", &e->fslider16, 0.500000f, 0.000000f, 1.000000f, 2.500000e-02f));
     parameter_map.insert(new Parameter("freeverb.damp", &e->fslider15, 0.5f, 0.0f, 1.0f, 2.500000e-02f));
     parameter_map.insert(new Parameter("freeverb.wet_dry", &e->fslider14, 0.0f, -0.5f, 0.5f, 1.e-01f));
     parameter_map.insert(new Parameter("IR.freq", &e->fslider21, 440.000000f, 20.000000f, 12000.000000f, 10.000000f));
     parameter_map.insert(new Parameter("IR.dialog", &e->fcheckbox8, 0));
     parameter_map.insert(new Parameter("IR.freq", &e->fslider21, 440.000000f, 20.000000f, 12000.000000f, 10.000000f));
     parameter_map.insert(new Parameter("IR.peak", &e->fslider22, 1.000000f, 0.000000f, 10.000000f, 0.200000f));
     parameter_map.insert(new Parameter("IR.bandwidth", &e->fslider20, 100.0f, 20.0f, 20000.0f, 10.0f));
     parameter_map.insert(new Parameter("IR.auto_freq", &e->auto_ir, 0));
     parameter_map.insert(new Parameter("crybaby.wah", &e->fslider11, 0.000000f, 0.000000f, 1.000000f, 1.000000e-02f));
     parameter_map.insert(new Parameter("crybaby.dialog", &e->fcheckbox5, 0));
     parameter_map.insert(new Parameter("crybaby.level", &e->fslider12, 0.1f, 0.0f, 1.0f, 1.000000e-02f));
     parameter_map.insert(new Parameter("crybaby.wet_dry", &e->fslider13, 0.f, -1.f, 1.f, 1.e-01f));
     parameter_map.insert(new Parameter("crybaby.autowah", &e->fautowah, 0));
     parameter_map.insert(new Parameter("echo.percent", &e->fslider19, 0.000000f, 0.000000f, 100.000000f, 0.100000f));
     parameter_map.insert(new Parameter("echo.time", &e->fslider18, 1.000000f, 1.000000f, 2000.000000f, 1.000000f));
     parameter_map.insert(new Parameter("echo.on_off", &e->fcheckbox7, 0));
     parameter_map.insert(new Parameter("delay.delay", &e->fsliderdel2,  0.f, 0.f, 5000.0f, 10.f));
     parameter_map.insert(new Parameter("delay.gain", &e->fdel_gain1, 0.0f, -20.0f, 20.0f, 0.1f));
     parameter_map.insert(new Parameter("delay.on_off", &e->fdelay, 0));
     parameter_map.insert(new Parameter("chorus.level", &e->fslider_CH3, 0.5f, 0.0f, 1.0f, 1.000000e-02f));
     parameter_map.insert(new Parameter("chorus.dialog", &e->fchorus, 0));
     parameter_map.insert(new Parameter("chorus.delay", &e->fslider_CH2, 2.500000e-02f, 0.0f, 0.2f, 1.000000e-03f));
     parameter_map.insert(new Parameter("chorus.depth", &e->fslider_CH1, 2.000000e-02f, 0.0f, 1.0f, 1.000000e-03f));
     parameter_map.insert(new Parameter("chorus.freq", &e->fslider_CH0, 3.0f, 0.0f, 10.0f, 1.000000e-02f));
     parameter_map.insert(new Parameter("MultiBandFilter.MultiBandFilter", &e->fmultifilter, 0));
     parameter_map.insert(new Parameter("MultiBandFilter.f31_25", &e->fslMulti9, 0.0f, -50.0f, 10.0f, 0.1f));
     parameter_map.insert(new Parameter("MultiBandFilter.f62_5", &e->fslMulti8, 0.0f, -50.0f, 10.0f, 0.1f));
     parameter_map.insert(new Parameter("MultiBandFilter.f125", &e->fslMulti7, 0.0f, -50.0f, 10.0f, 0.1f));
     parameter_map.insert(new Parameter("MultiBandFilter.f250", &e->fslMulti6, 0.0f, -50.0f, 10.0f, 0.1f));
     parameter_map.insert(new Parameter("MultiBandFilter.f500", &e->fslMulti5, 0.0f, -50.0f, 10.0f, 0.1f));
     parameter_map.insert(new Parameter("MultiBandFilter.f1k", &e->fslMulti4, 0.0f, -50.0f, 10.0f, 0.1f));
     parameter_map.insert(new Parameter("MultiBandFilter.f2k", &e->fslMulti3, 0.0f, -50.0f, 10.0f, 0.1f));
     parameter_map.insert(new Parameter("MultiBandFilter.f4k", &e->fslMulti2, 0.0f, -50.0f, 10.0f, 0.1f));
     parameter_map.insert(new Parameter("MultiBandFilter.f8k", &e->fslMulti1, 0.0f, -50.0f, 10.0f, 0.1f));
     parameter_map.insert(new Parameter("MultiBandFilter.f16k", &e->fslMulti0, 0.0f, -50.0f, 10.0f, 0.1f));
     parameter_map.insert(new Parameter("midi_out.channel_1.velocity", &e->fslider26, 64.f, 0.f, 127.f, 1.f));
     parameter_map.insert(new Parameter("midi_out.channel_1.volume", &e->fslider46, 64.f, 0.f, 127.f, 1.f));
     parameter_map.insert(new Parameter("midi_out.channel_1.autogain", &e->fautogain));
     parameter_map.insert(new Parameter("midi_out.channel_1.channel", &e->fslider30, 0.f, 0.f, 16.f, 1.f));
     parameter_map.insert(new Parameter("midi_out.channel_1.program", &e->fslider31, 0.f, 0.f, 248.f, 1.f));
     parameter_map.insert(new Parameter("midi_out.channel_1.oktave", &e->fslider29, 0.f, -2.f, 2.f, 1.f));
     parameter_map.insert(new Parameter("midi_out.channel_1.sensity", &e->fslider27, 20.f, 1.f, 500.f, 1.f));
     parameter_map.insert(new Parameter("midi_out.channel_1.auto_pitch", &e->fpitch));
     parameter_map.insert(new Parameter("midi_out.channel_2.velocity", &e->fslider32, 64.f, 0.f, 127.f, 1.f));
     parameter_map.insert(new Parameter("midi_out.channel_2.volume", &e->fslider47, 64.f, 0.f, 127.f, 1.f));
     parameter_map.insert(new Parameter("midi_out.channel_2.autogain", &e->fautogain1));
     parameter_map.insert(new Parameter("midi_out.channel_2.channel", &e->fslider35, 0.f, 0.f, 16.f, 1.f));
     parameter_map.insert(new Parameter("midi_out.channel_2.program", &e->fslider36, 0.f, 0.f, 248.f, 1.f));
     parameter_map.insert(new Parameter("midi_out.channel_2.oktave", &e->fslider34, 0.f, -2.f, 2.f, 1.f));
     parameter_map.insert(new Parameter("midi_out.channel_2.sensity", &e->fslider33, 20.f, 1.f, 500.f, 1.f));
     parameter_map.insert(new Parameter("midi_out.channel_2.on_off", &e->fcheckbox10, 0));
     parameter_map.insert(new Parameter("midi_out.channel_2.auto_pitch", &e->fpitch1));
     parameter_map.insert(new Parameter("midi_out.channel_3.velocity", &e->fslider40, 64.f, 0.f, 127.f, 1.f));
     parameter_map.insert(new Parameter("midi_out.channel_3.volume", &e->fslider48, 64.f, 0.f, 127.f, 1.f));
     parameter_map.insert(new Parameter("midi_out.channel_3.autogain", &e->fautogain2));
     parameter_map.insert(new Parameter("midi_out.channel_3.channel", &e->fslider44, 0.f, 0.f, 16.f, 1.f));
     parameter_map.insert(new Parameter("midi_out.channel_3.program", &e->fslider43, 0.f, 0.f, 248.f, 1.f));
     parameter_map.insert(new Parameter("midi_out.channel_3.oktave", &e->fslider42, 0.f, -2.f, 2.f, 1.f));
     parameter_map.insert(new Parameter("midi_out.channel_3.sensity", &e->fslider41, 20.f, 1.f, 500.f, 1.f));
     parameter_map.insert(new Parameter("midi_out.channel_3.on_off", &e->fcheckbox11, 0));
     parameter_map.insert(new Parameter("midi_out.channel_3.auto_pitch", &e->fpitch2));
     parameter_map.insert(new Parameter("beat_detector.stepper", &e->fslider39, 1.f, 1.f, 32.f, 1.f));
     parameter_map.insert(new Parameter("beat_detector.note_off", &e->fslider37, 2.f, 1.f, 127.f, 1.f));
     parameter_map.insert(new Parameter("beat_detector.atack_gain", &e->fslider45, 5.f, 1.f, 127.f, 1.f));
     parameter_map.insert(new Parameter("beat_detector.beat_gain", &e->fslider38, 1.f, 0.0f, 127.f, 1.f));
     parameter_map.insert(new Parameter("beat_detector.midi_gain", &e->midi_gain, 0.f, -20.f, 60.f, 1.f));
     // only save and restore, no midi control
     parameter_map.insert(new BaseParameter("system.latency_nowarn", &e->fwarn));
     parameter_map.insert(new BaseParameter("system.fskin", &e->fskin));
     parameter_map.insert(new BaseParameter("system.fConsta1t", &e->fConsta1t));
     parameter_map.insert(new BaseParameter("system.fexpand2", &e->fexpand2));
     parameter_map.insert(new BaseParameter("system.fdialogboxj", &e->fdialogboxj));
     parameter_map.insert(new BaseParameter("system.filebutton", &e->filebutton));
     parameter_map.insert(new BaseParameter("system.jconv_checkbutton7", &gx_jconv::GxJConvSettings::checkbutton7));
     parameter_map.insert(new BaseParameter("system.fexpand", &e->fexpand));
     parameter_map.insert(new BaseParameter("system.convolvefilter", &e->convolvefilter));
     parameter_map.insert(new BaseParameter("system.posit5", &e->posit5));
     parameter_map.insert(new BaseParameter("system.fdialogbox8", &e->fdialogbox8));
     parameter_map.insert(new BaseParameter("system.posit1", &e->posit1));
     parameter_map.insert(new BaseParameter("system.drive", &e->drive));
     parameter_map.insert(new BaseParameter("system.posit2", &e->posit2));
     parameter_map.insert(new BaseParameter("system.fdialogbox1", &e->fdialogbox1));
     parameter_map.insert(new BaseParameter("system.posit3", &e->posit3));
     parameter_map.insert(new BaseParameter("system.fdialogbox2", &e->fdialogbox2));
     parameter_map.insert(new BaseParameter("system.posit4", &e->posit4));
     parameter_map.insert(new BaseParameter("system.fdialogbox3", &e->fdialogbox3));
     parameter_map.insert(new BaseParameter("system.posit0", &e->posit0));
     parameter_map.insert(new BaseParameter("system.fdialogbox4", &e->fdialogbox4));
     parameter_map.insert(new BaseParameter("system.posit6", &e->posit6));
     parameter_map.insert(new BaseParameter("system.posit7", &e->posit7));
     parameter_map.insert(new BaseParameter("system.posit8", &e->posit8));
     parameter_map.insert(new BaseParameter("system.fchorusbox", &e->fchorusbox));
     parameter_map.insert(new BaseParameter("system.viv", &e->viv));
     parameter_map.insert(new BaseParameter("system.ffuse", &e->ffuse));
     parameter_map.insert(new BaseParameter("system.fdialogbox6", &e->fdialogbox6));
     parameter_map.insert(new BaseParameter("system.midistat", &e->midistat));
}

void initParameter(gx_engine::GxEngine* engine)
{
     initGroups();
     initNames();
     initParams(engine);
}

}

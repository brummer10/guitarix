#include <map>
#include <set>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <gtk/gtk.h>
#include <jack/jack.h>
#include <sndfile.h>
using namespace std;
#include "guitarix.h"

namespace gx_gui
{

/* Parameters */
ParameterGroups param_groups; // map group id -> group name
ParamMap parameter_map; // map id -> parameter, zone -> parameter

/* Midi */
MidiStandardControllers midi_std_ctr; // map ctrl num -> standard name
MidiControllerList controller_map; // map ctrl num -> controlled parameters


MidiStandardControllers::MidiStandardControllers()
{
	m.insert(pair<int, const char*>(0, "Bank Select MSB"));
	m.insert(pair<int, const char*>(1, "Modulation MSB"));
	m.insert(pair<int, const char*>(2, "Breath Contoller"));

	m.insert(pair<int, const char*>(4, "Foot Controller MSB"));
	m.insert(pair<int, const char*>(5, "Portamento Time MSB"));
	m.insert(pair<int, const char*>(6, "Data Entry MSB"));
	m.insert(pair<int, const char*>(7, "Main Volume"));
	m.insert(pair<int, const char*>(8, "Balance"));

	m.insert(pair<int, const char*>(10, "Pan"));
	m.insert(pair<int, const char*>(11, "Expression"));
	m.insert(pair<int, const char*>(12, "Effect Control 1"));
	m.insert(pair<int, const char*>(13, "Effect Control 2"));

	m.insert(pair<int, const char*>(32, "Bank Select LSB"));

	m.insert(pair<int, const char*>(64, "Sustain"));
	m.insert(pair<int, const char*>(65, "Portamento"));
	m.insert(pair<int, const char*>(66, "Sostenuto"));
	m.insert(pair<int, const char*>(67, "Soft Pedal"));
	m.insert(pair<int, const char*>(68, "Legato Footswitch"));
	m.insert(pair<int, const char*>(69, "Hold 2"));
	m.insert(pair<int, const char*>(70, "Sound Contr. 1")); // default: Sound Variation
	m.insert(pair<int, const char*>(71, "Sound Contr. 2")); // default: Timbre/Harmonic Content
	m.insert(pair<int, const char*>(72, "Sound Contr. 3")); // default: Release Time
	m.insert(pair<int, const char*>(73, "Sound Contr. 4")); // default: Attack Time
	m.insert(pair<int, const char*>(74, "Sound Contr. 5")); // default: Brightness
	m.insert(pair<int, const char*>(75, "Sound Contr. 6"));
	m.insert(pair<int, const char*>(76, "Sound Contr. 7"));
	m.insert(pair<int, const char*>(77, "Sound Contr. 8"));
	m.insert(pair<int, const char*>(78, "Sound Contr. 9"));
	m.insert(pair<int, const char*>(79, "Sound Contr. 10"));

	m.insert(pair<int, const char*>(84, "Portamento Control"));

	m.insert(pair<int, const char*>(91, "Eff. 1 Depth"));
	m.insert(pair<int, const char*>(92, "Eff. 2 Depth"));
	m.insert(pair<int, const char*>(93, "Eff. 3 Depth"));
	m.insert(pair<int, const char*>(94, "Eff. 4 Depth"));
	m.insert(pair<int, const char*>(95, "Eff. 5 Depth"));
	m.insert(pair<int, const char*>(96, "Data Inc"));
	m.insert(pair<int, const char*>(97, "Data Dec"));
	m.insert(pair<int, const char*>(98, "NRPN LSB"));
	m.insert(pair<int, const char*>(99, "NRPN MSB"));
	m.insert(pair<int, const char*>(100, "RPN LSB"));
	m.insert(pair<int, const char*>(101, "RPN MSB"));
	//Channel Mode Messages
	m.insert(pair<int, const char*>(120, "All Sounds Off"));
	m.insert(pair<int, const char*>(121, "Controller Reset"));
	m.insert(pair<int, const char*>(122, "Local Control"));
	m.insert(pair<int, const char*>(123, "All Notes Off"));
	m.insert(pair<int, const char*>(124, "Omni Off"));
	m.insert(pair<int, const char*>(125, "Omni On"));
	m.insert(pair<int, const char*>(126, "Mono On (Poly Off)"));
	m.insert(pair<int, const char*>(127, "Poly On (Mono Off)"));
}

void MidiController::writeJSON(gx_system::JsonWriter& jw) const
{
	jw.begin_array();
	jw.write(param.id());
	if (param.getControlType() == Parameter::Continuous) {
		jw.write(_lower);
		jw.write(_upper);
	}
	jw.end_array();
}

MidiController *MidiController::readJSON(gx_system::JsonParser& jp)
{
	jp.next(gx_system::JsonParser::begin_array);
	jp.next(gx_system::JsonParser::value_string);
	string id = jp.current_value();
	Parameter* param = parameter_map[id];
	if (!param) {
		gx_system::gx_print_warning("Midi controller settings",
		                            "unknown parameter: " + id);
		while (jp.next() != gx_system::JsonParser::end_array);
		return 0;
	}
	float lower, upper;
	if (param->getControlType() == Parameter::Continuous) {
		jp.next(gx_system::JsonParser::value_number);
		lower = jp.current_value_float();
		jp.next(gx_system::JsonParser::value_number);
		upper = jp.current_value_float();
	} else {
		lower = upper = 0;
	}
	jp.next(gx_system::JsonParser::end_array);
	return new MidiController(*param, lower, upper);
}

MidiControllerList::MidiControllerList():
	midi_config_mode(false),
	last_midi_control(-1)
{
}

void MidiControllerList::set_config_mode(bool mode, int ctl)
{
	assert(mode != midi_config_mode);
	if (mode)
		last_midi_control = ctl;
	midi_config_mode = mode;
}

int MidiControllerList::param2controller(Parameter& param, const MidiController** p)
{
	for (controller_array::size_type n = 0; n < map.size(); n++) {
		const midi_controller_list& cl = map[n];
		for (midi_controller_list::const_iterator i = cl.cbegin(); i != cl.end(); i++) {
			if (i->hasParameter(param)) {
				if (p) {
					*p = &(*i);
				}
				return n;
			}
		}
	}
	return -1;
}

void MidiControllerList::deleteParameter(Parameter& p)
{
	assert(midi_config_mode == true);
	for (controller_array::iterator pctr = map.begin(); pctr != map.end(); pctr++) {
		for (midi_controller_list::iterator i = pctr->begin(); i != pctr->end(); i++) {
			if (i->hasParameter(p)) {
				pctr->erase(i);
				break;
			}
		}
	}
}

void MidiControllerList::modifyCurrent(Parameter &param,
                                       float lower, float upper)
{
	assert(midi_config_mode == true);
	// maximal one controller for a zone allowed
	deleteParameter(param);
	if (last_midi_control == -1)
		return;
	// add zone to controller
	map[last_midi_control].push_front(MidiController(param, lower, upper));
}

void MidiControllerList::set(int ctr, int val)
{
	if (midi_config_mode)
	{
		last_midi_control = ctr;
		last_midi_control_value = val;
	}
	else {
		midi_controller_list& ctr_list = map[ctr];
		for (midi_controller_list::iterator i = ctr_list.begin(); i != ctr_list.end(); i++)
			i->set(val);
	}
}

void MidiControllerList::MidiDef(int ctr, const char* p, float l, float u)
{
	Parameter *pm = parameter_map[p];
	cout << p << endl;
	assert(pm);
	map[ctr].push_front(MidiController(*pm, l, u));
}

void MidiControllerList::load_defaults()
{
	MidiDef(0x07,"amp.out_master", -40, 40);
	MidiDef(0x28,"amp.in_level", -40, 40);
	MidiDef(0x29,"crybaby.wah", 0, 1);
	MidiDef(0x44,"compressor.on_off");
	MidiDef(0x45,"distortion.on_off");
	MidiDef(0x46,"overdrive.on_off");
	MidiDef(0x47,"freeverb.on_off");
	MidiDef(0x48,"IR.on_off");
	MidiDef(0x49,"crybaby.on_off");
	MidiDef(0x4a,"echo.on_off");
	MidiDef(0x4b,"delay.on_off");
	MidiDef(0x4c,"chorus.on_off");
}

void MidiControllerList::writeJSON(gx_system::JsonWriter& w)
{
	w.begin_array(true);
	for (unsigned int n = 0; n < map.size(); n++)
	{
		const midi_controller_list& cl = map[n];
		if (cl.empty())
			continue;
		w.write(n);
		w.begin_array();
		for (midi_controller_list::const_iterator i = cl.cbegin(); i != cl.end(); i++)
			i->writeJSON(w);
		w.end_array(true);
	}
	w.newline();
	w.end_array(true);
}

MidiControllerList::MidiControllerList(gx_system::JsonParser& jp):
	midi_config_mode(false),
	last_midi_control(-1)
{
	jp.next(gx_system::JsonParser::begin_array);
	while (jp.peek() != gx_system::JsonParser::end_array) {
		jp.next(gx_system::JsonParser::value_number);
		midi_controller_list& l = map[jp.current_value_int()];
		jp.next(gx_system::JsonParser::begin_array);
		while (jp.peek() != gx_system::JsonParser::end_array) {
			MidiController *p = MidiController::readJSON(jp);
			if (p) {
				l.push_front(*p);
			}
		}
		jp.next(gx_system::JsonParser::end_array);
	}
	jp.next(gx_system::JsonParser::end_array);
	jp.next(gx_system::JsonParser::end_token);
}

void recall_midi_controller_map()
{
    string filename = gx_system::gx_user_dir + gx_jack::client_name  + "_midi_rc";
	ifstream f(filename.c_str());
	if (!f.good()) {
		controller_map.load_defaults();
		if (save_midi_controller_map()) {
			gx_system::gx_print_warning("Midi controller settings", "initializing default settings");
		}
	} else {
		gx_system::JsonParser p(f);
		try {
			controller_map = MidiControllerList(p);
		}
		catch (gx_system::JsonException& e) {
			gx_system::gx_print_warning("Midi controller settings", "parse error");
		}
	}
}

bool save_midi_controller_map()
{
	string fname = gx_system::gx_user_dir + gx_jack::client_name + "_midi_rc";
	ofstream f(fname);
	if (f.good()) {
		gx_system::JsonWriter w(f);
		controller_map.writeJSON(w);
	}
	if (!f.good()) {
		gx_system::gx_print_warning("Midi controller settings", "cannot write to "+fname);
		return false;
	}
	return true;
}


void *FloatParameter::zone() const
{
	return &value;
}

void FloatParameter::set(int n, int high, float llimit, float ulimit)
{
	switch (c_type) {
	case Continuous:
		value = llimit + ((float)(n) / (high)) * (ulimit - llimit);
		break;
	case Switch:
	case Enum:
		value = lower + min(n, upper-lower-1); //FIXME "-1" ??
		cout << value << endl;
		break;
	default:
		assert(false);
		break;
	}
}

void *IntParameter::zone() const
{
	return &value;
}

void IntParameter::set(int n, int high, float llimit, float ulimit)
{
	switch (c_type) {
	case Continuous:
		assert(false); // not implemented
		break;
	case Switch:
		value = (2*n > high ? 1065353216 : 0); // FIXME float/int problem
	case Enum:
		assert(false); // not implemented
		break;
	default:
		assert(false);
		break;
	}
}

void *BoolParameter::zone() const
{
	return &value;
}

void BoolParameter::set(int n, int high, float llimit, float ulimit)
{
	switch (c_type) {
	case Switch:
		value = (2*n > high);
	default:
		assert(false);
		break;
	}
}

void initGroups()
{
	param_groups.insert("jconv","JConvolver");
	param_groups.insert("amp","Amplifier");
	param_groups.insert("amp.tone","Tone");
	param_groups.insert("shaper","Shaper");
	param_groups.insert("noise_gate","Noise Gate");
	param_groups.insert("anti_aliase","Anti Alias");
	param_groups.insert("amp.oversample","Oversampling");
	param_groups.insert("amp.bass_boost","Bass Boost");
	param_groups.insert("convolve","Amp Model");
	param_groups.insert("preamp","Pre-Amp");
	param_groups.insert("drive","Drive");
	param_groups.insert("tube","Tube 1");
	param_groups.insert("tube.vibrato","Tube 1 Vibrato");
	param_groups.insert("tube2","Tube 2");
	param_groups.insert("compressor","Compressor");
	param_groups.insert("overdrive","Overdrive");
	param_groups.insert("distortion","Distortion");
	param_groups.insert("distortion.low_highpass","Distortion low/highpass");
	param_groups.insert("distortion.low_highcutoff","Distortion low/highcutoff");
	param_groups.insert("freeverb","Freeverb");
	param_groups.insert("IR","IR");
	param_groups.insert("crybaby","Crybaby");
	param_groups.insert("echo","Echo");
	param_groups.insert("delay","Delay");
	param_groups.insert("chorus","Chorus");
	param_groups.insert("MultiBandFilter","Multiband Filter");
	param_groups.insert("midi_out","Midi Out");
	param_groups.insert("midi_out.channel_1","Midi Out 1");
	param_groups.insert("midi_out.channel_2","Midi Out 2");
	param_groups.insert("midi_out.channel_3","Midi Out 3");
	param_groups.insert("beat_detector","Beat Detector");
	param_groups.insert("ui","User Interface");
	param_groups.insert("system", "System");
}

void ParamMap::insert(Parameter* param)
{
	assert(addr_map.find(param->zone()) == addr_map.end());
	addr_map.insert(pair<const void*, Parameter*>(param->zone(), param));
	assert(id_map.find(param->id()) == id_map.end());
	id_map.insert(pair<string, Parameter*>(param->id(), param));
}

inline void Pa(const char*a,const char*b,float*c,float std,float lower,float upper,float step)
{
	parameter_map.insert(new FloatParameter(a,b,Parameter::Continuous,true,*c,std,lower,upper,step,true));
}

inline void Pa(const char*a,const char*b,float*c,float std=0)
{
	parameter_map.insert(new FloatParameter(a,b,Parameter::Switch,true,*c,std,0,1,1,true));
}

// should be int
inline void PaE(const char*a,const char*b,float*c,float std=0,float lower=0,float upper=1,float step=1)
{
	parameter_map.insert(new FloatParameter(a,b,Parameter::Enum,true,*c,std,lower,upper,step,true));
}

// should be bool
inline void Pa(const char*a,const char*b,int*c,int d)
{
	parameter_map.insert(new IntParameter(a,b,Parameter::Switch,true,*c,d,0,1,true));
}

inline void Pa(const char*a,const char*b,bool*c,bool d=false)
{
	parameter_map.insert(new BoolParameter(a,b,Parameter::Switch,true,*c,d,true));
}

inline void PaN(const char*a, float*c, bool d)
{
	parameter_map.insert(new FloatParameter(a,"",Parameter::None,d,*c,0,0,0,0,false));
}

void initParams(gx_engine::GxEngine* e)
{
	Pa("amp.feedback", "Feedback", &e->fslider0, 0.0f, -1.0f, 1.0f, 1.0e-02f);
	Pa("amp.feedforward", "Feedforward", &e->fslider23, 0.0f, -1.0f, 1.0f, 1.0e-02f);
	Pa("amp.balance", "Balance", &e->fslider25, 0.f, -1.f, 1.f, 1.e-01f);
	Pa("amp.in_level", "in level", &e->fslider3, 0.f, -40.f, 40.f, 0.1f);
	Pa("amp.out_master", "out / master", &e->fslider17, 0.f, -40.f, 40.f, 0.1f);
	Pa("amp.tone.bass", "Bass", &e->fslider_tone2, 0.f, -20.f, 20.f, 0.1f);
	Pa("amp.tone.middle", "Middle", &e->fslider_tone1, 0.f, -20.f, 20.f, 0.1f);
	Pa("amp.tone.treble", "Treble", &e->fslider_tone0, 0.f, -20.f, 20.f, 0.1f);
	Pa("amp.oversample.on_off", "on/off", &e->fupsample, 0);
	Pa("amp.bass_boost.on_off", "on/off", &e->fboost, 0);
	Pa("amp.fuzz", "fuzz", &e->fthreshold, 1.f, 0.f, 1.f, 0.01f);
	PaE("amp.threshold", "threshold", &e->ffuse, 0.f, 0.f, 3.f, 1.0f);

	Pa("convolve.on_off", "on/off", &e->fconvolve, 0);
	PaE("convolve.select", "select", &e->convolvefilter, 0.f, 0.f, 7.f, 1.0f);

	Pa("shaper.on_off", "on/off", &e->fng, 0);
	Pa("shaper.sharper", "Sharper", &e->fsharp0, 1.f, 1.f, 10.f, 1.0f);

	Pa("noise_gate.on_off", "on/off", &e->fnoise_g, 0);
	Pa("noise_gate.threshold", "Threshold", &e->fnglevel, 0.017f, 0.01f, 0.21f, 0.001f);

	Pa("anti_aliase.on_off", "on/off", &e->antialis0, 0);
	Pa("anti_aliase.feedback", "Feedback", &e->faas1, 0.3f, 0.3f, 0.9f, 0.01f);

	Pa("preamp.on_off", "on/off", &e->fcheckbox1, 0);
	Pa("preamp.atan", "drive", &e->fatan, 1.f, 1.f, 10.f, 1.0f);

	Pa("tube.on_off", "on/off", &e->ftube, 0);
	Pa("tube.fuzzy", "count", &e->ffuzzytube, 1.f, -3.f, 10.f, 1.0f);
	Pa("tube.vibrato.on_off", "on/off", &e->fresoon, 0);
	Pa("tube.vibrato", "vibrato", &e->fvibrato, 0.f, 0.f, 2.f, 0.02f);

	Pa("tube2.on_off", "on/off", &e->ftube3, 0);
	Pa("tube2.fuzzy", "count", &e->fresotube3, 1.f, -3.f, 10.f, 1.0f);
	Pa("tube2.resonanz", "resonanz", &e->fresotube1, 0.5f, 0.f, 0.9f, 0.01f);
	Pa("tube2.vibrato", "vibrato", &e->fresotube2, 1.f, 0.f, 1.f, 0.01f);

	Pa("drive.on_off", "on/off", &e->fprdr, 0);
	Pa("drive.value", "drive", &e->fpredrive, 1.f, 1.f, 10.f, 1.0f);

	Pa("jconv.on_off", "Run", &gx_jconv::GxJConvSettings::checkbutton7);
	Pa("jconv.left_delay", "Left Delay", &e->fsliderdel0,  0.f, 0.f, 5000.0f, 10.f);
	Pa("jconv.right_delay", "Right Delay", &e->fsliderdel1,  0.f, 0.f, 5000.0f, 10.f);
	Pa("jconv.left_gain", "Left Gain", &e->fjc_ingain,  0.f, -20.f, 20.f, 0.1f);
	Pa("jconv.right_gain", "Right Gain", &e->fjc_ingain1,  0.f, -20.f, 20.f, 0.1f);
	Pa("jconv.wet_dry", "wet/dry", &e->fslider24,  0.f, -1.f, 1.f, 1.e-01f);

	Pa("compressor.on_off", "on/off", &e->fcheckboxcom1, 0);
	Pa("compressor.knee", "knee", &e->fentrycom1, 3.0f, 0.0f, 20.0f, 0.10f);
	Pa("compressor.ratio", "ratio", &e->fentrycom2, 2.0f, 1.0f, 20.0f, 0.10f);
	Pa("compressor.threshold", "threshold", &e->fentrycom0, -20.0f, -96.0f, 10.0f, 0.10f);
	Pa("compressor.attack", "attack", &e->fslidercom0, 2.0e-03f, 0.0f, 1.0f, 1.0e-03f);
	Pa("compressor.release", "release", &e->fslidercom1, 0.50f, 0.0f, 10.0f, 1.0e-02f);

	Pa("overdrive.on_off", "on/off", &e->foverdrive4, 0);
	Pa("overdrive.drive", "drive", &e->drive, 1.f, 1.f, 20.f, 0.1f);

	Pa("distortion.on_off", "on/off", &e->fcheckbox4, 0);
	Pa("distortion.level", "level", &e->fslider8, 1.0e-02f, 0.0f, 0.50f, 1.0e-02f);
	Pa("distortion.gain", "gain", &e->fslider10, 2.0f, -10.0f, 10.0f, 0.1f);
	Pa("distortion.drive", "drive", &e->fslider9, 0.64f, 0.f, 1.f, 1.e-02f);
	Pa("distortion.trigger", "trigger", &e->fslider4, 0.12f, 0.0f, 1.0f, 1.0e-02f);
	Pa("distortion.vibrato", "vibrato", &e->fslider5, 1.0f, 0.0f, 1.0f, 1.0e-02f);
	Pa("distortion.low_highpass.high_freq", "high freq", &e->fentry1, 130.0f, 20.0f, 7040.0f, 10.0f);
	Pa("distortion.low_highpass.low_freq", "low freq", &e->fentry0, 5000.0f, 20.0f, 12000.0f, 10.0f);
	Pa("distortion.low_highpass.on_off", "low highpass", &e->fcheckbox2, 0);
	Pa("distortion.low_highcutoff.high_freq", "high freq", &e->fslider6, 5000.f, 1000.f, 12000.f, 10.f);
	Pa("distortion.low_highcutoff.low_freq", "low freq", &e->fslider7, 130.f, 20.f, 1000.f, 10.f);
	Pa("distortion.low_highcutoff.on_off", "low highcutoff", &e->fcheckbox3, 0);

	Pa("freeverb.on_off", "on/off", &e->fcheckbox6, 0);
	Pa("freeverb.wet_dry", "wet/dry", &e->fslider14, 0.0f, -0.5f, 0.5f, 1.e-01f);
	Pa("freeverb.damp", "damp", &e->fslider15, 0.5f, 0.0f, 1.0f, 2.50e-02f);
	Pa("freeverb.RoomSize", "RoomSize", &e->fslider16, 0.50f, 0.0f, 1.0f, 2.50e-02f);

	Pa("IR.on_off", "on/off", &e->fcheckbox8, 0);
	Pa("IR.freq", "freq", &e->fslider21, 440.0f, 20.0f, 12000.0f, 10.0f);
	Pa("IR.peak", "peak", &e->fslider22, 1.0f, 0.0f, 10.0f, 0.20f);
	Pa("IR.bandwidth", "bandwidth", &e->fslider20, 100.0f, 20.0f, 20000.0f, 10.0f);
	Pa("IR.auto_freq", "auto freq", &e->auto_ir, 0);

	Pa("crybaby.on_off", "on/off", &e->fcheckbox5, 0);
	Pa("crybaby.wah", "wah", &e->fslider11, 0.0f, 0.0f, 1.0f, 1.0e-02f);
	Pa("crybaby.level", "level", &e->fslider12, 0.1f, 0.0f, 1.0f, 1.0e-02f);
	Pa("crybaby.wet_dry", "wet/dry", &e->fslider13, 0.f, -1.f, 1.f, 1.e-01f);
	Pa("crybaby.autowah", "autowah", &e->fautowah, 0);

	Pa("echo.on_off", "on/off", &e->fcheckbox7, 0);
	Pa("echo.time", "time", &e->fslider18, 1.0f, 1.0f, 2000.0f, 1.0f);
	Pa("echo.percent", "percent", &e->fslider19, 0.0f, 0.0f, 100.0f, 0.10f);

	Pa("delay.on_off", "on/off", &e->fdelay, 0);
	Pa("delay.delay", "delay", &e->fsliderdel2,  0.f, 0.f, 5000.0f, 10.f);
	Pa("delay.gain", "gain", &e->fdel_gain1, 0.0f, -20.0f, 20.0f, 0.1f);

	Pa("chorus.on_off", "on/off", &e->fchorus, 0);
	Pa("chorus.freq", "freq", &e->fslider_CH0, 3.0f, 0.0f, 10.0f, 1.0e-02f);
	Pa("chorus.depth", "depth", &e->fslider_CH1, 2.0e-02f, 0.0f, 1.0f, 1.0e-03f);
	Pa("chorus.delay", "delay", &e->fslider_CH2, 2.50e-02f, 0.0f, 0.2f, 1.0e-03f);
	Pa("chorus.level", "level", &e->fslider_CH3, 0.5f, 0.0f, 1.0f, 1.0e-02f);

	Pa("MultiBandFilter.on_off", "on/off", &e->fmultifilter, 0);
	Pa("MultiBandFilter.f31_25", "f31_25", &e->fslMulti9, 0.0f, -50.0f, 10.0f, 0.1f);
	Pa("MultiBandFilter.f62_5", "f62_5", &e->fslMulti8, 0.0f, -50.0f, 10.0f, 0.1f);
	Pa("MultiBandFilter.f125", "f125", &e->fslMulti7, 0.0f, -50.0f, 10.0f, 0.1f);
	Pa("MultiBandFilter.f250", "f250", &e->fslMulti6, 0.0f, -50.0f, 10.0f, 0.1f);
	Pa("MultiBandFilter.f500", "f500", &e->fslMulti5, 0.0f, -50.0f, 10.0f, 0.1f);
	Pa("MultiBandFilter.f1k", "f1k", &e->fslMulti4, 0.0f, -50.0f, 10.0f, 0.1f);
	Pa("MultiBandFilter.f2k", "f2k", &e->fslMulti3, 0.0f, -50.0f, 10.0f, 0.1f);
	Pa("MultiBandFilter.f4k", "f4k", &e->fslMulti2, 0.0f, -50.0f, 10.0f, 0.1f);
	Pa("MultiBandFilter.f8k", "f8k", &e->fslMulti1, 0.0f, -50.0f, 10.0f, 0.1f);
	Pa("MultiBandFilter.f16k", "f16k", &e->fslMulti0, 0.0f, -50.0f, 10.0f, 0.1f);

	Pa("midi_out.channel_1.velocity", "velocity", &e->fslider26, 64.f, 0.f, 127.f, 1.f);
	Pa("midi_out.channel_1.volume", "volume", &e->fslider46, 64.f, 0.f, 127.f, 1.f);
	Pa("midi_out.channel_1.autogain", "autogain", &e->fautogain);
	Pa("midi_out.channel_1.channel", "channel", &e->fslider30, 0.f, 0.f, 16.f, 1.f);
	Pa("midi_out.channel_1.program", "program", &e->fslider31, 0.f, 0.f, 248.f, 1.f);
	Pa("midi_out.channel_1.oktave", "oktave", &e->fslider29, 0.f, -2.f, 2.f, 1.f);
	Pa("midi_out.channel_1.sensity", "sensity", &e->fslider27, 20.f, 1.f, 500.f, 1.f);
	Pa("midi_out.channel_1.auto_pitch", "auto pitch", &e->fpitch);

	Pa("midi_out.channel_2.on_off", "on/off", &e->fcheckbox10, 0);
	Pa("midi_out.channel_2.velocity", "velocity", &e->fslider32, 64.f, 0.f, 127.f, 1.f);
	Pa("midi_out.channel_2.volume", "volume", &e->fslider47, 64.f, 0.f, 127.f, 1.f);
	Pa("midi_out.channel_2.autogain", "autogain", &e->fautogain1);
	Pa("midi_out.channel_2.channel", "channel", &e->fslider35, 0.f, 0.f, 16.f, 1.f);
	Pa("midi_out.channel_2.program", "program", &e->fslider36, 0.f, 0.f, 248.f, 1.f);
	Pa("midi_out.channel_2.oktave", "oktave", &e->fslider34, 0.f, -2.f, 2.f, 1.f);
	Pa("midi_out.channel_2.sensity", "sensity", &e->fslider33, 20.f, 1.f, 500.f, 1.f);
	Pa("midi_out.channel_2.auto_pitch", "auto pitch", &e->fpitch1);

	Pa("midi_out.channel_3.on_off", "on/off", &e->fcheckbox11, 0);
	Pa("midi_out.channel_3.velocity", "velocity", &e->fslider40, 64.f, 0.f, 127.f, 1.f);
	Pa("midi_out.channel_3.volume", "volume", &e->fslider48, 64.f, 0.f, 127.f, 1.f);
	Pa("midi_out.channel_3.autogain", "autogain", &e->fautogain2);
	Pa("midi_out.channel_3.channel", "channel", &e->fslider44, 0.f, 0.f, 16.f, 1.f);
	Pa("midi_out.channel_3.program", "program", &e->fslider43, 0.f, 0.f, 248.f, 1.f);
	Pa("midi_out.channel_3.oktave", "oktave", &e->fslider42, 0.f, -2.f, 2.f, 1.f);
	Pa("midi_out.channel_3.sensity", "sensity", &e->fslider41, 20.f, 1.f, 500.f, 1.f);
	Pa("midi_out.channel_3.auto_pitch", "auto pitch", &e->fpitch2);

	Pa("beat_detector.stepper", "stepper", &e->fslider39, 1.f, 1.f, 32.f, 1.f);
	Pa("beat_detector.note_off", "note off", &e->fslider37, 2.f, 1.f, 127.f, 1.f);
	Pa("beat_detector.atack_gain", "atack gain", &e->fslider45, 5.f, 1.f, 127.f, 1.f);
	Pa("beat_detector.beat_gain", "beat gain", &e->fslider38, 1.f, 0.0f, 127.f, 1.f);
	Pa("beat_detector.midi_gain", "midi gain", &e->midi_gain, 0.f, -20.f, 60.f, 1.f);

	// only save and restore, no midi control

	// positions of effects
	PaN("crybaby.position", &e->posit0, true);
	PaN("overdrive.position", &e->posit1, true);
	PaN("distortion.position", &e->posit2, true);
	PaN("freeverb.position", &e->posit3, true);
	PaN("IR.position", &e->posit4, true);
	PaN("compressor.position", &e->posit5, true);
	PaN("echo.position", &e->posit6, true);
	PaN("delay.position", &e->posit7, true);
	PaN("system.unused1", &e->posit8, true); // unused?

	// togglebuttons for dialogboxes and expander for effect details
	PaN("compressor.dialog", &e->fdialogbox8, false);
	PaN("distortion.dialog", &e->fdialogbox1, false);
	PaN("freeverb.dialog", &e->fdialogbox2, false);
	PaN("IR.dialog", &e->fdialogbox3, false);
	PaN("crybaby.dialog", &e->fdialogbox4, false);
	PaN("chorus.dialog", &e->fchorusbox, false);
	PaN("midi_out.dialog", &e->fdialogbox6, false);
	PaN("jconv.dialog", &e->fdialogboxj, false);
	PaN("jconv.expander", &e->fexpand2, false);
	PaN("jconv.filedialog", &e->filebutton, false);

	// user interface options
	PaN("ui.latency_nowarn", &e->fwarn, false);
	PaN("ui.skin", &e->fskin, false);
	PaN("ui.main_expander", &e->fexpand, false);

	// shouldn't be saved, only output?
	PaN("system.fConsta1t", &e->fConsta1t, false);
	PaN("system.midistat", &e->midistat, false);
	PaN("system.waveview", &e->viv, false);
}

void initParameter(gx_engine::GxEngine* engine)
{
	initGroups();
	initParams(engine);

#ifndef NDEBUG
	map<string,bool> gmap;
	param_groups.fill_map(gmap);
	for (ParamMap::iterator i = parameter_map.begin(); i != parameter_map.end(); i++) {
		string gp = group_id(i->first);
		if (param_groups[gp] == "" && !gmap[gp])
			gx_system::gx_print_error("Debug Check", "group not found: " + gp);
		gmap[gp] = true;
	}
	for (map<string,bool>::iterator i = gmap.begin(); i != gmap.end(); i++) {
		if (not i->second)
			gx_system::gx_print_error("Debug Check", "group not used: " + i->first);
	}
#endif
}

}

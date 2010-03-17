/*
 * Copyright (C) 2010 Hermann Meyer, James Warden, Andreas Degert
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * ---------------------------------------------------------------------------
 *
 *    parameter and midi data
 *
 * ----------------------------------------------------------------------------
 */

#include <map>
#include <set>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
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

/****************************************************************
 ** Global Variables
 */

/* Midi */
MidiStandardControllers midi_std_ctr; // map ctrl num -> standard name
MidiControllerList controller_map; // map ctrl num -> controlled parameters

/* Parameters */
ParamMap parameter_map; // map id -> parameter, zone -> parameter


/****************************************************************
 ** Midi
 */

static struct midi_std_init {
	int ctrl;
	const char *name;
} midi_std_itab[] = {
	{ 0, "Bank Select MSB"},
	{ 1, "Modulation MSB"},
	{ 2, "Breath Contoller"},

	{ 4, "Foot Controller MSB"},
	{ 5, "Portamento Time MSB"},
	{ 6, "Data Entry MSB"},
	{ 7, "Main Volume"},
	{ 8, "Balance"},

	{10, "Pan"},
	{11, "Expression"},
	{12, "Effect Control 1"},
	{13, "Effect Control 2"},

	{32, "Bank Select LSB"},

	{64, "Sustain"},
	{65, "Portamento"},
	{66, "Sostenuto"},
	{67, "Soft Pedal"},
	{68, "Legato Footswitch"},
	{69, "Hold 2"},
	{70, "Sound Contr. 1"}, // default: Sound Variation
	{71, "Sound Contr. 2"}, // default: Timbre/Harmonic Content
	{72, "Sound Contr. 3"}, // default: Release Time
	{73, "Sound Contr. 4"}, // default: Attack Time
	{74, "Sound Contr. 5"}, // default: Brightness
	{75, "Sound Contr. 6"},
	{76, "Sound Contr. 7"},
	{77, "Sound Contr. 8"},
	{78, "Sound Contr. 9"},
	{79, "Sound Contr. 10"},

	{84, "Portamento Control"},

	{91, "Eff. 1 Depth"},
	{92, "Eff. 2 Depth"},
	{93, "Eff. 3 Depth"},
	{94, "Eff. 4 Depth"},
	{95, "Eff. 5 Depth"},
	{96, "Data Inc"},
	{97, "Data Dec"},
	{98, "NRPN LSB"},
	{99, "NRPN MSB"},
	{100, "RPN LSB"},
	{101, "RPN MSB"},

	{120, "All Sounds Off"},
	{121, "Controller Reset"},
	{122, "Local Control"},
	{123, "All Notes Off"},
	{124, "Omni Off"},
	{125, "Omni On"},
	{126, "Mono On (Poly Off)"},
	{127, "Poly On (Mono Off)"},
};

MidiStandardControllers::MidiStandardControllers()
{
	for (unsigned int i = 0; i < sizeof(midi_std_itab)/sizeof(midi_std_itab[0]); i++) {
		m.insert(pair<int, modstring>(midi_std_itab[i].ctrl, modstring(midi_std_itab[i].name)));
	}
}

void MidiStandardControllers::replace(int ctr, string name)
{
	map<int,modstring>::iterator i = m.find(ctr);
	if (name.empty()) {
		if (i != m.end()) {
			if (i->second.modified) {
				if (i->second.std) {
					i->second.name = m[ctr].std;
					m[ctr].modified = false;
				} else {
					m.erase(i);
				}
			}
		}
	} else {
		if (i == m.end()) {
			m[ctr] = modstring(name, true, 0);
		} else {
			i->second.modified = true;
			i->second.name = name;
		}
	}
}

void MidiStandardControllers::writeJSON(gx_system::JsonWriter& jw) const
{
	jw.begin_object(true);
	for (map<int,modstring>::const_iterator i = m.cbegin(); i != m.cend(); i++) {
		if (i->second.modified) {
			ostringstream ostr;
			ostr << i->first;
			jw.write_key(ostr.str());
			jw.write(i->second.name, true);
		}
	}
	jw.end_object(true);
}

void MidiStandardControllers::readJSON(gx_system::JsonParser& jp)
{
	jp.next(gx_system::JsonParser::begin_object);
	while (jp.peek() == gx_system::JsonParser::value_key) {
		jp.next();
		istringstream istr(jp.current_value());
		int ctl;
		istr >> ctl;
		if (istr.fail()) {
			throw gx_system::JsonException("midi standard controllers: number expected");
		}
		jp.next();
		replace(ctl, jp.current_value());
	}
	jp.next(gx_system::JsonParser::end_object);
}

void MidiController::writeJSON(gx_system::JsonWriter& jw) const
{
	jw.begin_array();
	jw.write(param.id());
	if (param.getControlType() == Parameter::Continuous ||
	    param.getControlType() == Parameter::Enum) {
		jw.write(_lower);
		jw.write(_upper);
	} else {
		assert(param.getControlType() == Parameter::Switch);
	}
	jw.end_array();
}

MidiController *MidiController::readJSON(gx_system::JsonParser& jp)
{
	jp.next(gx_system::JsonParser::begin_array);
	jp.next(gx_system::JsonParser::value_string);
	string id = jp.current_value();
	if (!parameter_map.hasId(id)) {
		gx_system::gx_print_warning("Midi controller settings",
		                            "unknown parameter: " + id);
		while (jp.next() != gx_system::JsonParser::end_array);
		return 0;
	}
	Parameter& param = parameter_map[id];
	float lower = 0, upper = 0;
	bool bad = false;
	bool chg = false;
	if (param.getControlType() == Parameter::Continuous ||
	    param.getControlType() == Parameter::Enum) {
		if (jp.peek() != gx_system::JsonParser::end_array) {
			float pmin, pmax;
			if (param.hasRange()) {
				pmin = param.getLowerAsFloat();
				pmax = param.getUpperAsFloat();
			} else {
				bad = true;
				pmin = pmax = 0;
			}
			jp.next(gx_system::JsonParser::value_number);
			lower = jp.current_value_float();
			jp.next(gx_system::JsonParser::value_number);
			upper = jp.current_value_float();
			if (lower > pmax) {
				lower = pmax;
				chg = true;
			} else if (lower < pmin) {
				lower = pmin;
				chg = true;
			}
			if (upper > pmax) {
				upper = pmax;
				chg = true;
			} else if (upper < pmin) {
				upper = pmin;
				chg = true;
			}
		} else {
			bad = true;
		}
	} else {
		if (param.getControlType() != Parameter::Switch) {
			bad = true;
		}
	}
	while (jp.next() != gx_system::JsonParser::end_array); // be tolerant
	if (bad) {
		gx_system::gx_print_warning(
			"recall MIDI state",
			"invalid format, Parameter skipped: " + id);
		return 0;
	}
	if (chg) {
		gx_system::gx_print_warning(
			"recall MIDI state",
			"Parameter range outside bounds, changed: " + id);
	}
	return new MidiController(param, lower, upper);
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

void MidiControllerList::deleteParameter(Parameter& p, bool quiet)
{
	bool mode = get_config_mode();
	if (!mode) {
		set_config_mode(true); // keep rt thread away from table
	}
	bool found = false;
	for (controller_array::iterator pctr = map.begin(); pctr != map.end(); pctr++) {
		for (midi_controller_list::iterator i = pctr->begin(); i != pctr->end(); i++) {
			if (i->hasParameter(p)) {
				pctr->erase(i);
				found = true;
				break;
			}
		}
	}
	if (found && !quiet) {
		changed();
	}
	if (!mode) {
		set_config_mode(false);
	}
}

void MidiControllerList::modifyCurrent(Parameter &param,
                                       float lower, float upper)
{
	assert(midi_config_mode == true); // keep rt thread away from table
	// maximal one controller for a zone allowed
	deleteParameter(param);
	if (last_midi_control == -1)
		return;
	// add zone to controller
	map[last_midi_control].push_front(MidiController(param, lower, upper));
	changed();
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

void MidiControllerList::readJSON(gx_system::JsonParser& jp)
{
	controller_array m;
	jp.next(gx_system::JsonParser::begin_array);
	while (jp.peek() != gx_system::JsonParser::end_array) {
		jp.next(gx_system::JsonParser::value_number);
		midi_controller_list& l = m[jp.current_value_int()];
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
	bool mode = get_config_mode();
	if (!mode) {
		set_config_mode(true); // keep rt thread away from table
	}
	map = m;
	if (!mode) {
		set_config_mode(false);
	}
	changed();
}


/****************************************************************
 ** Parameter Groups
 */

class ParameterGroups
{
private:
	map<string,string> groups;

#ifndef NDEBUG
	map<string,bool> used;

	void group_exists(string id)
		{
			if (groups.find(id) == groups.end()) {
				gx_system::gx_print_error("Debug Check", "Group does not exist: " + id);
			} else {
				used[id] = true;
			}
		}
	void group_is_new(string id)
		{
			if (groups.find(id) != groups.end()) {
				gx_system::gx_print_error("Debug Check", "Group already exists: " + id);
			}
		}

	~ParameterGroups()
		{
			for (map<string,bool>::iterator i = used.begin(); i != used.end(); i++) {
				if (!i->second) {
					gx_system::gx_print_error("Debug Check", "Group not used: " + i->first);
				}
			}
		}
	friend string param_group(string id);
#endif

public:
	ParameterGroups();

	inline string operator[](string id)
		{
			debug_check(group_exists, id); return groups[id];
		}
	inline void insert(string id, string group)
		{
			debug_check(group_is_new, id);
			groups.insert(pair<string,string>(id, group));
		}
};

ParameterGroups::ParameterGroups()
{
	insert("jconv","Convolver");
	insert("amp","Amplifier");
	insert("amp.tone","Tone");
	insert("shaper","Shaper");
	insert("noise_gate","Noise Gate");
	insert("anti_aliase","Anti Alias");
	insert("amp.oversample","Oversampling");
	insert("amp.bass_boost","Bass Boost");
	insert("convolve","Amp Model");
	insert("preamp","Pre-Amp");
	insert("drive","Drive");
	insert("tube","Tube 1");
	insert("tube.vibrato","Tube 1 Vibrato");
	insert("tube2","Tube 2");
	insert("compressor","Compressor");
	insert("overdrive","Overdrive");
	insert("distortion","Distortion");
	insert("distortion.low_highpass","Distortion low/highpass");
	insert("distortion.low_highcutoff","Distortion low/highcutoff");
	insert("freeverb","Freeverb");
	insert("IR","ImpulseResponse");
	insert("crybaby","Crybaby");
	insert("echo","Echo");
	insert("delay","Delay");
	insert("chorus","Chorus");
	insert("MultiBandFilter","Multiband Filter");
	insert("midi_out","Midi Out");
	insert("midi_out.channel_1","Midi Out 1");
	insert("midi_out.channel_2","Midi Out 2");
	insert("midi_out.channel_3","Midi Out 3");
	insert("beat_detector","Beat Detector");
	insert("ui","User Interface");
	insert("system", "System");
}

string param_group(string id)
{
	static ParameterGroups groups = ParameterGroups();
	return groups[id.substr(0, id.find_last_of("."))];
}

/****************************************************************
 ** Parameter
 */

bool Parameter::hasRange() const
{
	return false;
}

float Parameter::getStepAsFloat() const
{
	return 1;
}

float Parameter::getLowerAsFloat() const
{
	return 0;
}

float Parameter::getUpperAsFloat() const
{
	return 0;
}


/* FloatParameter */

void *FloatParameter::zone()
{
	return &value;
}

void FloatParameter::set(int n, int high, float llimit, float ulimit)
{
	switch (c_type) {
	case Continuous:
		assert(n >= 0 && n <= high);
		value = llimit + ((float)(n) / (high)) * (ulimit - llimit);
		break;
	case Switch:
	case Enum:
		value = lower + min((float)n, upper-lower-1); //FIXME "-1" ??
		break;
	default:
		assert(false);
		break;
	}
}

void FloatParameter::set_std_value()
{
	value = std_value;
}

void FloatParameter::writeJSON(gx_system::JsonWriter& jw)
{
	jw.write_key(_id.c_str());
	jw.write(value);
}

void FloatParameter::readJSON_value(gx_system::JsonParser& jp)
{
	jp.next(gx_system::JsonParser::value_number);
	set(jp.current_value_float());
}

bool FloatParameter::hasRange() const
{
	return true;
}

float FloatParameter::getLowerAsFloat() const
{
	return lower;
}

float FloatParameter::getUpperAsFloat() const
{
	return upper;
}

float FloatParameter::getStepAsFloat() const
{
	return step;
}


/* IntParameter */

void *IntParameter::zone()
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
		break;
	case Enum:
		assert(false); // not implemented
		break;
	default:
		assert(false);
		break;
	}
}

void IntParameter::set_std_value()
{
	value = std_value;
}

void IntParameter::writeJSON(gx_system::JsonWriter& jw)
{
	jw.write_key(_id.c_str());
	jw.write(value);
}

void IntParameter::readJSON_value(gx_system::JsonParser& jp)
{
	jp.next(gx_system::JsonParser::value_number);
	set(jp.current_value_int());
}

bool IntParameter::hasRange() const
{
	return true;
}

float IntParameter::getLowerAsFloat() const
{
	return lower;
}

float IntParameter::getUpperAsFloat() const
{
	return upper;
}


/* BoolParameter */

void *BoolParameter::zone()
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

void BoolParameter::set_std_value()
{
	value = std_value;
}

void BoolParameter::writeJSON(gx_system::JsonWriter& jw)
{
	jw.write_key(_id.c_str());
	jw.write(value);
}

void BoolParameter::readJSON_value(gx_system::JsonParser& jp)
{
	jp.next(gx_system::JsonParser::value_number);
	value = jp.current_value_int();
}


/* SwitchParameter */

void SwitchParameter::set(bool val)
{
	value = val;
	changed(value);
}

void *SwitchParameter::zone()
{
	return &value;
}

void SwitchParameter::set_std_value()
{
	set(std_value);
}

void SwitchParameter::set(int n, int high, float llimit, float ulimit)
{
	assert(false);
}

void SwitchParameter::writeJSON(gx_system::JsonWriter& jw)
{
	jw.write_key(_id.c_str());
	jw.write(value);
}

void SwitchParameter::readJSON_value(gx_system::JsonParser& jp)
{
	jp.next(gx_system::JsonParser::value_number);
	set(jp.current_value_int());
}


/****************************************************************
 ** Parameter Map
 */

#ifndef NDEBUG
void ParamMap::unique_zone(Parameter* param)
{
	if (addr_map.find(param->zone()) != addr_map.end()) {
		gx_system::gx_print_error("Debug Check", "zone registered twice (id: " + param->id() +")");
	}
}

void ParamMap::unique_id(Parameter* param)
{
	if (id_map.find(param->id()) != id_map.end()) {
		gx_system::gx_print_error("Debug Check", "id registered twice: " + param->id());
	}
}

void ParamMap::check_addr(const void *p)
{
	if (!hasZone(p)) {
		cerr << "zone not found: " << p << endl;
	}
}
void ParamMap::check_id(string id)
{
	if (!hasId(id)) {
		cerr << "string-id not found: " << id << endl;
	}
}

void ParamMap::check_p(const char *p)
{
	if (!hasId(p)) {
		cerr << "char-id not found: " << p << endl;
	}
}
#endif

void ParamMap::insert(Parameter* param)
{
	debug_check(unique_zone, param);
	addr_map.insert(pair<const void*, Parameter*>(param->zone(), param));
	debug_check(unique_id, param);
	id_map.insert(pair<string, Parameter*>(param->id(), param));
}

void ParamMap::set_init_values()
{
	for (iterator i = id_map.begin(); i != id_map.end(); i++) {
		i->second->set_std_value();
	}
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

inline void PaE(const char*a,const char*b,int*c,int std=0,int lower=0,int upper=1)
{
	parameter_map.insert(new IntParameter(a,b,Parameter::Enum,true,*c,std,lower,upper,true));
}

// should be bool
inline void Pa(const char*a,const char*b,int*c,int d)
{
	parameter_map.insert(new IntParameter(a,b,Parameter::Switch,true,*c,d,0,1065353216,true)); //FIXME (see above float/int)
}

inline void Pa(const char*a,const char*b,bool*c,bool d=false)
{
	parameter_map.insert(new BoolParameter(a,b,Parameter::Switch,true,*c,d,true));
}

inline void PaN(const char*a, float*c, bool d, float std=0, float lower=0, float upper=1)
{
	parameter_map.insert(new FloatParameter(a,"",Parameter::None,d,*c,std,lower,upper,0,false));
}

void initParams()
{
	Pa("midi_out.channel_1.velocity", "velocity", &gx_engine::fslider26, 64.f, 0.f, 127.f, 1.f);
	Pa("midi_out.channel_1.volume", "volume", &gx_engine::fslider46, 64.f, 0.f, 127.f, 1.f);
	Pa("midi_out.channel_1.autogain", "autogain", &gx_engine::fautogain);
	Pa("midi_out.channel_1.channel", "channel 1", &gx_engine::fslider30, 0.f, 0.f, 16.f, 1.f);
	Pa("midi_out.channel_1.program", "program", &gx_engine::fslider31, 0.f, 0.f, 248.f, 1.f);
	Pa("midi_out.channel_1.oktave", "oktave", &gx_engine::fslider29, 0.f, -2.f, 2.f, 1.f);
	Pa("midi_out.channel_1.sensity", "sensity", &gx_engine::fslider27, 20.f, 1.f, 500.f, 1.f);
	Pa("midi_out.channel_1.auto_pitch", "auto pitch", &gx_engine::fpitch);

	Pa("midi_out.channel_2.on_off", "on/off", &gx_engine::fcheckbox10, 0);
	Pa("midi_out.channel_2.velocity", "velocity", &gx_engine::fslider32, 64.f, 0.f, 127.f, 1.f);
	Pa("midi_out.channel_2.volume", "volume", &gx_engine::fslider47, 64.f, 0.f, 127.f, 1.f);
	Pa("midi_out.channel_2.autogain", "autogain", &gx_engine::fautogain1);
	Pa("midi_out.channel_2.channel", "channel 2", &gx_engine::fslider35, 0.f, 0.f, 16.f, 1.f);
	Pa("midi_out.channel_2.program", "program", &gx_engine::fslider36, 0.f, 0.f, 248.f, 1.f);
	Pa("midi_out.channel_2.oktave", "oktave", &gx_engine::fslider34, 0.f, -2.f, 2.f, 1.f);
	Pa("midi_out.channel_2.sensity", "sensity", &gx_engine::fslider33, 20.f, 1.f, 500.f, 1.f);
	Pa("midi_out.channel_2.auto_pitch", "auto pitch", &gx_engine::fpitch1);

	Pa("midi_out.channel_3.on_off", "on/off", &gx_engine::fcheckbox11, 0);
	Pa("midi_out.channel_3.velocity", "velocity", &gx_engine::fslider40, 64.f, 0.f, 127.f, 1.f);
	Pa("midi_out.channel_3.volume", "volume", &gx_engine::fslider48, 64.f, 0.f, 127.f, 1.f);
	Pa("midi_out.channel_3.autogain", "autogain", &gx_engine::fautogain2);
	Pa("midi_out.channel_3.channel", "channel 3", &gx_engine::fslider44, 0.f, 0.f, 16.f, 1.f);
	Pa("midi_out.channel_3.program", "program", &gx_engine::fslider43, 0.f, 0.f, 248.f, 1.f);
	Pa("midi_out.channel_3.oktave", "oktave", &gx_engine::fslider42, 0.f, -2.f, 2.f, 1.f);
	Pa("midi_out.channel_3.sensity", "sensity", &gx_engine::fslider41, 20.f, 1.f, 500.f, 1.f);
	Pa("midi_out.channel_3.auto_pitch", "auto pitch", &gx_engine::fpitch2);

	Pa("beat_detector.stepper", "stepper", &gx_engine::fslider39, 1.f, 1.f, 32.f, 1.f);
	Pa("beat_detector.note_off", "note off", &gx_engine::fslider37, 2.f, 1.f, 127.f, 1.f);
	Pa("beat_detector.atack_gain", "atack gain", &gx_engine::fslider45, 5.f, 1.f, 127.f, 1.f);
	Pa("beat_detector.beat_gain", "beat gain", &gx_engine::fslider38, 1.f, 0.0f, 127.f, 1.f);
	Pa("beat_detector.midi_gain", "midi gain", &gx_engine::midi_gain, 0.f, -20.f, 60.f, 1.f);

	PaE("amp.threshold", "threshold", &gx_engine::ffuse, 0.f, 0.f, 3.f, 1.0f);
	Pa("MultiBandFilter.on_off", "on/off", &gx_engine::fmultifilter, 0);
	Pa("crybaby.autowah", "autowah", &gx_engine::fautowah, 0);
	Pa("overdrive.on_off", "on/off", &gx_engine::foverdrive4, 0);
	Pa("distortion.on_off", "on/off", &gx_engine::fcheckbox4, 0);
	Pa("freeverb.on_off", "on/off", &gx_engine::fcheckbox6, 0);
	Pa("IR.on_off", "on/off", &gx_engine::fcheckbox8, 0);
	Pa("crybaby.on_off", "on/off", &gx_engine::fcheckbox5, 0);
	Pa("echo.on_off", "on/off", &gx_engine::fcheckbox7, 0);
	Pa("delay.on_off", "on/off", &gx_engine::fdelay, 0);
	Pa("chorus.on_off", "on/off", &gx_engine::fchorus, 0);
	Pa("compressor.on_off", "on/off", &gx_engine::fcheckboxcom1, 0);
	Pa("tube2.on_off", "on/off", &gx_engine::ftube3, 0);
	Pa("tube.vibrato.on_off", "on/off", &gx_engine::fresoon, 0);
	Pa("tube.on_off", "on/off", &gx_engine::ftube, 0);
	Pa("drive.on_off", "on/off", &gx_engine::fprdr, 0);
	Pa("preamp.on_off", "on/off", &gx_engine::fcheckbox1, 0);
	PaE("convolve.select", "select", &gx_engine::convolvefilter, 0.f, 0.f, 7.f, 1.0f);
	Pa("convolve.on_off", "on/off", &gx_engine::fconvolve, 0);
	Pa("amp.bass_boost.on_off", "on/off", &gx_engine::fboost, 0);
	Pa("amp.oversample.on_off", "on/off", &gx_engine::fupsample, 0);
	Pa("anti_aliase.on_off", "on/off", &gx_engine::antialis0, 0);
	Pa("noise_gate.on_off", "on/off", &gx_engine::fnoise_g, 0);
	Pa("noise_gate.threshold", "Threshold", &gx_engine::fnglevel, 0.017f, 0.01f, 0.21f, 0.001f);
	Pa("shaper.on_off", "on/off", &gx_engine::fng, 0);
	Pa("jconv.on_off", "Run", &gx_jconv::GxJConvSettings::checkbutton7);
	// only save and restore, no midi control

	// positions of effects
	PaN("crybaby.position", &gx_engine::posit0, true, 5, 0, 8);
	PaN("overdrive.position", &gx_engine::posit1, true, 2, 0, 8);
	PaN("distortion.position", &gx_engine::posit2, true, 1, 0, 8);
	PaN("freeverb.position", &gx_engine::posit3, true, 3, 0, 8);
	PaN("IR.position", &gx_engine::posit4, true, 4, 0, 8);
	PaN("compressor.position", &gx_engine::posit5, true, 0, 0, 8);
	PaN("echo.position", &gx_engine::posit6, true, 6, 0, 8);
	PaN("delay.position", &gx_engine::posit7, true, 8, 0, 8);
	PaN("chorus.position", &gx_engine::posit8, true, 7, 0, 8);

	// togglebuttons for dialogboxes and expander for effect details
	PaN("compressor.dialog", &gx_engine::fdialogbox8, false);
	PaN("distortion.dialog", &gx_engine::fdialogbox1, false);
	PaN("freeverb.dialog", &gx_engine::fdialogbox2, false);
	PaN("IR.dialog", &gx_engine::fdialogbox3, false);
	PaN("crybaby.dialog", &gx_engine::fdialogbox4, false);
	PaN("chorus.dialog", &gx_engine::fchorusbox, false);
	PaN("midi_out.dialog", &gx_engine::fdialogbox6, false);
	PaN("jconv.dialog", &gx_engine::fdialogboxj, false);
	PaN("jconv.expander", &gx_engine::fexpand2, false);
	PaN("jconv.filedialog", &gx_engine::filebutton, false);

	// user interface options
	PaN("ui.latency_nowarn", &gx_engine::fwarn, false, 0);
	PaN("ui.skin", &gx_engine::fskin, false, 0, 0, 100);
	PaN("ui.main_expander", &gx_engine::fexpand, false);

	// shouldn't be saved, only output?
	PaN("system.fConsta1t", &gx_engine::fConsta1t, false);
	PaN("system.midistat", &gx_engine::midistat, false);
	PaN("system.waveview", &gx_engine::viv, false);
	parameter_map.set_init_values();
}

}

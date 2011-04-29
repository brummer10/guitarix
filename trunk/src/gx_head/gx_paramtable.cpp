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

#include <set>
#include "guitarix.h"
#include <glibmm/i18n.h>

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
	for (map<int,modstring>::const_iterator i = m.begin(); i != m.end(); i++) {
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
			throw gx_system::JsonException(_("midi standard controllers: number expected"));
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
		gx_system::gx_print_warning(_("Midi controller settings"),
		                            _("unknown parameter: ") + id);
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
			_("recall MIDI state"),
			_("invalid format, Parameter skipped: ") + id);
		return 0;
	}
	if (chg) {
		gx_system::gx_print_warning(
			_("recall MIDI state"),
			_("Parameter range outside bounds, changed: ") + id);
	}
	return new MidiController(param, lower, upper);
}

MidiControllerList::MidiControllerList():
	map(controller_array_size),
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
		for (midi_controller_list::const_iterator i = cl.begin(); i != cl.end(); i++) {
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
		for (midi_controller_list::const_iterator i = cl.begin(); i != cl.end(); i++)
			i->writeJSON(w);
		w.end_array(true);
	}
	w.newline();
	w.end_array(true);
}

void MidiControllerList::readJSON(gx_system::JsonParser& jp, controller_array& m)
{
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
}

void MidiControllerList::set_controller_array(const controller_array& m)
{
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

void MidiControllerList::remove_controlled_parameters(paramlist& plist, const controller_array *new_m)
{
	std::set<Parameter*> pset;
	for (unsigned int i = 0; i < map.size(); i++) {
		midi_controller_list& ctr = map[i];
		for (midi_controller_list::iterator j = ctr.begin(); j != ctr.end(); j++) {
			if (new_m) {
				const midi_controller_list& ctr_new = (*new_m)[i];
				for (midi_controller_list::const_iterator jn = ctr_new.begin(); jn != ctr_new.end(); jn++) {
					if (j->getParameter() == jn->getParameter()) {
						pset.insert(&j->getParameter());
						break;
					}
				}
			} else {
				pset.insert(&j->getParameter());
			}
		}
	}
	for (paramlist::iterator n = plist.begin(); n != plist.end(); ) {
		paramlist::iterator n1 = n++;
		if (pset.find(*n1) != pset.end()) {
			plist.erase(n1);
		}
	}
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
	friend string param_group(string id, bool nowarn);
#endif

public:
	ParameterGroups();

	inline string get(string id) { return groups[id]; }
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
	insert("jconv",N_("Convolver"));
	insert("eq", N_("EQ"));
	insert("eqs", N_("Scaleable EQ"));
	insert("eqt", N_("Scwitch EQ"));
	insert("amp",N_("Amplifier"));
	insert("amp2",N_("Amplifier2"));
	insert("amp2.preamp",N_("Preamp"));
	insert("amp2.stage1",N_("Tube1"));
	insert("amp2.stage2",N_("Tube2"));
	insert("stage3",N_("Amplifier2"));
	insert("stage3.gain3",N_("Tube3"));
	insert("shaper",N_("Shaper"));
	insert("noise_gate",N_("Noise Gate"));
	insert("anti_aliase",N_("Anti Alias"));
	insert("amp.oversample",N_("Oversampling"));
	insert("amp.bass_boost",N_("Bass Boost"));
	insert("convolve",N_("Amp Model"));
	insert("preamp",N_("Pre-Amp"));
	insert("drive",N_("Drive"));
	insert("tube",N_("Tube 1"));
	insert("tube.vibrato",N_("Tube 1 Vibrato"));
	insert("tube2",N_("Tube 2"));
	insert("tube3",N_("Tube 3"));
	insert("amp.tonestack",N_("Tonestack"));
	insert("compressor",N_("Compressor"));
	insert("overdrive",N_("Overdrive"));
	insert("gxdistortion",N_("Multi Band Distortion"));
	insert("gx_distortion",N_("Multi Band Distortion"));
	insert("low_high_pass.lhp",N_("low_highpass"));
	insert("low_high_pass.lhc",N_("low_highcutoff"));
	insert("low_highpass",N_("low high pass"));
	insert("gx_distortion.resonator",N_("Distortion resonator"));
	insert("distortion1",N_("Single Band Distortion"));
	insert("distortion1.low_highpass",N_("Distortion low/highpass"));
	insert("distortion1.low_highcutoff",N_("Distortion low/highcutoff"));
	insert("distortion1.resonator",N_("Distortion resonator"));
	insert("distortiont",N_("Switch Distortion"));
	insert("freeverb",N_("Freeverb"));
	insert("IR",N_("ImpulseResponse"));
	insert("crybaby",N_("Crybaby"));
	insert("echo",N_("Echo"));
	insert("delay",N_("Delay"));
	insert("stereodelay",N_("Stereo Delay"));
	insert("stereoecho",N_("Stereo Echo"));
	insert("chorus",N_("Chorus"));
	insert("MultiBandFilter",N_("Multiband Filter"));
	insert("moog",N_("Moog Filter"));
	insert("biquad",N_("BiQuad Filter"));
	insert("flanger",N_("Flanger"));
	insert("SampleLooper",N_("Sample Looper"));
	insert("cab",N_("Cab-ImpResp"));
	insert("phaser",N_("Phaser"));
	insert("midi_out",N_("Midi Out"));
	insert("midi_out.channel_1",N_("Midi Out 1"));
	insert("midi_out.channel_2",N_("Midi Out 2"));
	insert("midi_out.channel_3",N_("Midi Out 3"));
	insert("beat_detector",N_("Beat Detector"));
	insert("ui",N_("User Interface"));
	insert("system", N_("System"));
	insert("oscilloscope", N_("Oscilloscope"));
	insert("ampmodul", N_("Postamp"));
	insert("ampmodul.amp2.stage1", N_("Postamp Tube1"));
	insert("ampmodul.amp2.stage2", N_("Postamp Tube2"));
	insert("amp.clip", N_("clipper"));
	insert("tonemodul", N_("3 Band EQ"));
	insert("tremolo", N_("Tremolo"));
	insert("phaser_mono", N_("Phaser Mono"));
	insert("chorus_mono", N_("Chorus Mono"));
}

string param_group(string id, bool nowarn)
{
	static ParameterGroups groups = ParameterGroups();
	const string& group_id = id.substr(0, id.find_last_of("."));
	if (nowarn) {
		return groups.get(group_id);
	} else {
		return groups[group_id];
	}
}

/****************************************************************
 ** Parameter
 */

Parameter::~Parameter()
{
}

static int get_upper(const char **vn)
{
	for (int n = 0; ; n++) {
		if (!vn[n]) {
			return n - 1;
		}
	}
}

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

const char **Parameter::getValueNames() const
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
		value = (2*n > high ? 1.0 : 0.0);
		break;
	case Enum:
		value = lower + min((float)n, upper-lower);
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
	json_value = jp.current_value_float();
}

void FloatParameter::setJSON_value()
{
	set(json_value);
}

void FloatParameter::convert_from_range(float low, float up)
{
	json_value = lower + (json_value - low) / (up - low) * (upper - lower);
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


/* FloatEnumParameter */

FloatEnumParameter::FloatEnumParameter(string id, string name, const char** vn, bool preset,
                                       float &v, int sv, bool ctrl, bool exp):
	FloatParameter(id, name, Enum, preset, v, sv, 0, get_upper(vn), 1, ctrl, exp),
	value_names(vn)
{
}

const char **FloatEnumParameter::getValueNames() const
{
	return value_names;
}

void FloatEnumParameter::writeJSON(gx_system::JsonWriter& jw)
{
	jw.write_key(_id.c_str());
	jw.write(value_names[(int)round(value)]);
}

void FloatEnumParameter::readJSON_value(gx_system::JsonParser& jp)
{
	gx_system::JsonParser::token tok = jp.next();
	if (tok == gx_system::JsonParser::value_number) {
		// old version compatability
		json_value = jp.current_value_int();
		return;
	}
	jp.check_expect(gx_system::JsonParser::value_string);
	int up = int(round(upper));
	int n = 0;
	for (; n <= up; n++) {
		if (jp.current_value() == value_names[n]) {
			break;
		}
	}
	if (n > up) {
		gx_system::gx_print_warning(
			_("read parameter"), (boost::format(_("parameter %1%: unknown enum value: %2%"))
			                   % _id % jp.current_value()).str());
		n = 0;
	}
	json_value = n;
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
	json_value = jp.current_value_int();
}

void IntParameter::setJSON_value()
{
	set(json_value);
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


/* EnumParameter */

EnumParameter::EnumParameter(string id, string name, const char** vn, bool preset,
                             int &v, int sv, bool ctrl, bool exp):
	IntParameter(id, name, Enum, preset, v, sv, 0, get_upper(vn), ctrl, exp),
	value_names(vn)
{
}

const char **EnumParameter::getValueNames() const
{
	return value_names;
}

void EnumParameter::writeJSON(gx_system::JsonWriter& jw)
{
	jw.write_key(_id.c_str());
	jw.write(value_names[value]);
}

void EnumParameter::readJSON_value(gx_system::JsonParser& jp)
{
	gx_system::JsonParser::token tok = jp.next();
	if (tok == gx_system::JsonParser::value_number) {
		// old version compatability
		json_value = jp.current_value_int();
		return;
	}
	jp.check_expect(gx_system::JsonParser::value_string);
	int n = 0;
	for (; n <= upper; n++) {
		if (jp.current_value() == value_names[n]) {
			break;
		}
	}
	if (n > upper) {
		gx_system::gx_print_warning(
			_("read parameter"), (boost::format(_("parameter %1%: unknown enum value: %2%"))
			                   % _id % jp.current_value()).str());
		n = 0;
	}
	json_value = n;
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
	json_value = jp.current_value_int();
}

void BoolParameter::setJSON_value()
{
	set(json_value);
}


/* SwitchParameter */

void SwitchParameter::set(bool val)
{
	if (val != value){
		value = val;
		changed(value);
	}
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
	json_value = jp.current_value_int();
}

void SwitchParameter::setJSON_value()
{
	set(json_value);
}


/* FileParameter */

void FileParameter::set_path(const string& path)
{
	value = Gio::File::create_for_path(path);
}

void FileParameter::set(const Glib::RefPtr<Gio::File>& val)
{
	value = val;
}

void FileParameter::set_standard(const string& filename)
{
	std_value = Gio::File::create_for_path(filename);
	if (!value) {
		value = std_value->dup();
	}
}

void FileParameter::set_std_value()
{
	set(std_value->dup());
}

void *FileParameter::zone()
{
	return &value;
}

void FileParameter::set(int n, int high, float llimit, float ulimit)
{
	assert(false);
}

void FileParameter::writeJSON(gx_system::JsonWriter& jw)
{
	jw.write_key(_id.c_str());
	jw.write(get_path());
}

void FileParameter::readJSON_value(gx_system::JsonParser& jp)
{
	jp.next(gx_system::JsonParser::value_string);
	json_value = Gio::File::create_for_path(jp.current_value());
}

void FileParameter::setJSON_value()
{
	set(json_value);
}

static string get_file_id(const Glib::RefPtr<Gio::File>& f)
{
	return f->query_info(G_FILE_ATTRIBUTE_ID_FILE)->get_attribute_string(G_FILE_ATTRIBUTE_ID_FILE);
}

bool FileParameter::is_standard() const
{
	string id;
	try {
		id = get_file_id(value);
	} catch (Gio::Error ex) {
		return false; // FIXME check type of exception
	}
	return id == get_file_id(std_value);
}

string FileParameter::get_path()
{
	return value->get_path();
}

string FileParameter::get_directory_path()
{
	return value->get_parent()->get_path();
}

string FileParameter::get_parse_name()
{
	return value->get_parse_name();
}

string FileParameter::get_display_name()
{
	return value->query_info(G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME)->get_display_name();
}

void FileParameter::copy(const string& destination)
{
	value->copy(Gio::File::create_for_path(destination));
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

} // namespace gx_gui

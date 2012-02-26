/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * ---------------------------------------------------------------------------
 *
 *    parameter and midi data
 *
 * ----------------------------------------------------------------------------
 */

#ifndef NDEBUG
#include <iostream>
#endif

#include "engine.h"               // NOLINT

namespace gx_engine {

/****************************************************************
 ** Global Variables
 */

/* Midi */
MidiStandardControllers midi_std_ctr; // map ctrl num -> standard name
MidiControllerList controller_map; // map ctrl num -> controlled parameters


/****************************************************************
 ** class MidiStandardControllers
 */

static struct midi_std_init {
    int ctrl;
    const char *name;
} midi_std_itab[] = {
    { 0, "Bank Select MSB"},
    { 1, "Modulation MSB"},
    { 2, "Breath Controller"},

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

MidiStandardControllers::MidiStandardControllers() {
    for (unsigned int i = 0; i < sizeof(midi_std_itab)/sizeof(midi_std_itab[0]); i++) {
        m.insert(pair<int, modstring>(midi_std_itab[i].ctrl, modstring(midi_std_itab[i].name)));
    }
}

void MidiStandardControllers::replace(int ctr, const string& name) {
    map<int, modstring>::iterator i = m.find(ctr);
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

void MidiStandardControllers::writeJSON(gx_system::JsonWriter& jw) const {
    jw.begin_object(true);
    for (map<int, modstring>::const_iterator i = m.begin(); i != m.end(); ++i) {
        if (i->second.modified) {
            ostringstream ostr;
            ostr << i->first;
            jw.write_key(ostr.str());
            jw.write(i->second.name, true);
        }
    }
    jw.end_object(true);
}

void MidiStandardControllers::readJSON(gx_system::JsonParser& jp) {
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


/****************************************************************
 ** class MidiController
 */

void MidiController::writeJSON(gx_system::JsonWriter& jw) const {
    jw.begin_array();
    jw.write(param->id());
    if (param->getControlType() == Parameter::Continuous ||
        param->getControlType() == Parameter::Enum) {
        jw.write(_lower);
        jw.write(_upper);
    } else {
        assert(param->getControlType() == Parameter::Switch);
    }
    jw.end_array();
}

MidiController *MidiController::readJSON(gx_system::JsonParser& jp, ParamMap& pmap) {
    jp.next(gx_system::JsonParser::begin_array);
    jp.next(gx_system::JsonParser::value_string);
    string id = jp.current_value();
    if (!pmap.hasId(id)) {
        gx_system::gx_print_warning(_("Midi controller settings"),
                                    _("unknown parameter: ") + id);
        while (jp.next() != gx_system::JsonParser::end_array);
        return 0;
    }
    Parameter& pm = pmap[id];
    float lower = 0, upper = 0;
    bool bad = false;
    bool chg = false;
    if (pm.getControlType() == Parameter::Continuous ||
        pm.getControlType() == Parameter::Enum) {
        if (jp.peek() != gx_system::JsonParser::end_array) {
            float pmin, pmax;
            if (pm.hasRange()) {
                pmin = pm.getLowerAsFloat();
                pmax = pm.getUpperAsFloat();
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
        if (pm.getControlType() != Parameter::Switch) {
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
    return new MidiController(pm, lower, upper);
}


/****************************************************************
 ** class MidiControllerList
 */

MidiControllerList::MidiControllerList()
    : map(controller_array_size),
      midi_config_mode(false),
      last_midi_control(-1),
      program_change(-1),
      pgm_chg(),
      changed(),
      new_program() {
    pgm_chg.connect(sigc::mem_fun(*this, &MidiControllerList::on_pgm_chg));
}

void MidiControllerList::on_pgm_chg() {
    int pgm;
    do {
	pgm = gx_system::atomic_get(program_change);
    } while (!gx_system::atomic_compare_and_exchange(&program_change, pgm, -1));
    new_program(pgm);
}

void MidiControllerList::set_config_mode(bool mode, int ctl) {
    assert(mode != midi_config_mode);
    if (mode)
        last_midi_control = ctl;
    midi_config_mode = mode;
}

int MidiControllerList::param2controller(Parameter& param, const MidiController** p) {
    for (controller_array::size_type n = 0; n < map.size(); ++n) {
        const midi_controller_list& cl = map[n];
        for (midi_controller_list::const_iterator i = cl.begin(); i != cl.end(); ++i) {
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

void MidiControllerList::deleteParameter(Parameter& p, bool quiet) {
    bool mode = get_config_mode();
    if (!mode) {
        set_config_mode(true); // keep rt thread away from table
    }
    bool found = false;
    for (controller_array::iterator pctr = map.begin(); pctr != map.end(); ++pctr) {
        for (midi_controller_list::iterator i = pctr->begin(); i != pctr->end(); ++i) {
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
                                       float lower, float upper) {
    assert(midi_config_mode == true); // keep rt thread away from table
    // maximal one controller for a zone allowed
    deleteParameter(param);
    if (last_midi_control == -1)
        return;
    // add zone to controller
    map[last_midi_control].push_front(MidiController(param, lower, upper));
    changed();
}

void MidiControllerList::set_ctr_val(int ctr, int val) {
    if (midi_config_mode) {
        last_midi_control = ctr;
    } else {
        midi_controller_list& ctr_list = map[ctr];
        for (midi_controller_list::iterator i = ctr_list.begin(); i != ctr_list.end(); ++i)
            i->set(val);
    }
}

void MidiControllerList::writeJSON(gx_system::JsonWriter& w) {
    w.begin_array(true);
    for (unsigned int n = 0; n < map.size(); n++) {
        const midi_controller_list& cl = map[n];
        if (cl.empty())
            continue;
        w.write(n);
        w.begin_array();
        for (midi_controller_list::const_iterator i = cl.begin(); i != cl.end(); ++i)
            i->writeJSON(w);
        w.end_array(true);
    }
    w.newline();
    w.end_array(true);
}

void MidiControllerList::readJSON(gx_system::JsonParser& jp, ParamMap& param, controller_array& m) {
    jp.next(gx_system::JsonParser::begin_array);
    while (jp.peek() != gx_system::JsonParser::end_array) {
        jp.next(gx_system::JsonParser::value_number);
        midi_controller_list& l = m[jp.current_value_int()];
        jp.next(gx_system::JsonParser::begin_array);
        while (jp.peek() != gx_system::JsonParser::end_array) {
            MidiController *p = MidiController::readJSON(jp, param);
            if (p) {
                l.push_front(*p);
            }
        }
        jp.next(gx_system::JsonParser::end_array);
    }
    jp.next(gx_system::JsonParser::end_array);
}

void MidiControllerList::set_controller_array(const controller_array& m) {
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

void MidiControllerList::remove_controlled_parameters(paramlist& plist,
                                                      const controller_array *new_m) {
    std::set<Parameter*> pset;
    for (unsigned int i = 0; i < map.size(); i++) {
        midi_controller_list& ctr = map[i];
        for (midi_controller_list::iterator j = ctr.begin(); j != ctr.end(); ++j) {
            if (new_m) {
                const midi_controller_list& ctr_new = (*new_m)[i];
                for (midi_controller_list::const_iterator jn = ctr_new.begin();
                                                          jn != ctr_new.end(); ++jn) {
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

// ----- jack process callback for the midi input
void MidiControllerList::compute_midi_in(void* midi_input_port_buf) {
    jack_midi_event_t in_event;
    jack_nframes_t event_count = jack_midi_get_event_count(midi_input_port_buf);
    unsigned int i;
    for (i = 0; i < event_count; i++) {
        jack_midi_event_get(&in_event, midi_input_port_buf, i);
        if ((in_event.buffer[0] & 0xf0) == 0xc0) {  // program change on any midi channel
            gx_system::atomic_set(&program_change, in_event.buffer[1]);
            pgm_chg();
        } else if ((in_event.buffer[0] & 0xf0) == 0xb0) {   // controller
            set_ctr_val(in_event.buffer[1], in_event.buffer[2]);
        }
    }
}

/****************************************************************
 ** Parameter Groups
 */

ParameterGroups::ParameterGroups() {
    insert("system", N_("System"));
    insert("ui", N_("User Interface"));
}

ParameterGroups::~ParameterGroups() {
#ifndef NDEBUG
    for (map<string, bool>::iterator i = used.begin(); i != used.end(); ++i) {
	if (!i->second) {
	    gx_system::gx_print_error("Debug Check", "Group not used: " + i->first);
	}
    }
#endif
}

#ifndef NDEBUG
void ParameterGroups::group_exists(const string& id) {
    if (groups.find(id) == groups.end()) {
	gx_system::gx_print_error("Debug Check", "Group does not exist: " + id);
    } else {
	used[id] = true;
    }
}

void ParameterGroups::group_is_new(const string& id) {
    if (groups.find(id) != groups.end()) {
	gx_system::gx_print_error("Debug Check", "Group already exists: " + id);
    }
}

void ParameterGroups::dump() {
    for (map<string, string>::iterator i = groups.begin(); i != groups.end(); ++i) {
	printf("PG %s: %s\n", i->first.c_str(), i->second.c_str());
    }
}

#endif

ParameterGroups& get_group_table() {
    static ParameterGroups groups;
    return groups;
}

string param_group(const string& id, bool nowarn) {
    static ParameterGroups& groups = get_group_table();
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

Parameter::~Parameter() {
}

static int get_upper(const value_pair *vn) {
    for (int n = 0; ; n++) {
        if (!vn[n].value_id) {
            return n - 1;
        }
    }
}

bool Parameter::hasRange() const {
    return false;
}

float Parameter::getStepAsFloat() const {
    return 1;
}

float Parameter::getLowerAsFloat() const {
    return 0;
}

float Parameter::getUpperAsFloat() const {
    return 0;
}

const value_pair *Parameter::getValueNames() const {
    return 0;
}

#ifndef NDEBUG
void compare_parameter(const char *title, Parameter* p1, Parameter* p2, bool all) {
    if (p1->_id != p2->_id) {
	printf("%s: Different ID's: %s / %s\n", title, p1->_id.c_str(), p2->_id.c_str());
    }
    if (p1->_name != p2->_name) {
	printf("%s[%s]: Different name: %s / %s\n", title, p1->_id.c_str(), p1->_name.c_str(), p2->_name.c_str());
    }
    if (p1->_group != p2->_group) {
	printf("%s[%s]: Different group: %s / %s\n", title, p1->_id.c_str(), p1->_group.c_str(), p2->_group.c_str());
    }
    if (p1->_desc != p2->_desc) {
	printf("%s[%s]: Different desc: %s / %s\n", title, p1->_id.c_str(), p1->_desc.c_str(), p2->_desc.c_str());
    }
    if (p1->save_in_preset != p2->save_in_preset) {
	printf("%s[%s]: save_in_preset different: %d / %d\n", title, p1->_id.c_str(), p1->save_in_preset, p2->save_in_preset);
    }
    if (p1->controllable != p2->controllable) {
	printf("%s[%s]: controllable different: %d / %d\n", title, p1->_id.c_str(), p1->controllable, p2->controllable);
    }
    if (p1->used != p2->used) {
	printf("%s[%s]: used different: %d / %d\n", title, p1->_id.c_str(), p1->used, p2->used);
    }
    if (p1->c_type != p2->c_type) {
	printf("%s[%s]: c_type different: %d / %d\n", title, p1->_id.c_str(), p1->c_type, p2->c_type);
    }
    if (p1->v_type != p2->v_type) {
	printf("%s[%s]: v_type different: %d / %d\n", title, p1->_id.c_str(), p1->v_type, p2->v_type);
	return;
    }
    if (p1->isFloat()) {
	FloatParameter& f1 = p1->getFloat();
	FloatParameter& f2 = p2->getFloat();
	if (f1.value != f2.value) {
	    printf("%s[%s]: value address different: %p / %p\n", title, p1->_id.c_str(), f1.value, f2.value);
	}
	if (f1.lower != f2.lower) {
	    printf("%s[%s]: float lower different: %g / %g\n", title, p1->_id.c_str(), f1.lower, f2.lower);
	}
	if (f1.upper != f2.upper) {
	    printf("%s[%s]: float upper different: %g / %g\n", title, p1->_id.c_str(), f1.upper, f2.upper);
	}
	if (f1.step != f2.step) {
	    printf("%s[%s]: float step different: %g / %g\n", title, p1->_id.c_str(), f1.step, f2.step);
	}
	if (f1.std_value != f2.std_value) {
	    printf("%s[%s]: float std value different: %g / %g\n", title, p1->_id.c_str(), f1.std_value, f2.std_value);
	}
	if (all) {
	    if (f1.value != f2.value) {
		printf("%s[%s]: float value different: %g / %g\n", title, p1->_id.c_str(), *f1.value, *f2.value);
	    }
	    if (f1.json_value != f2.json_value) {
		printf("%s[%s]: float json value different: %g / %g\n", title, p1->_id.c_str(), f1.json_value, f2.json_value);
	    }
	}
	return;
    }
    if (p1->isInt()) {
	assert(false);
	return;
    }
    if (p1->isUInt()) {
	assert(false);
	return;
    }
    if (p1->isBool()) {
	assert(false);
	return;
    }
    if (p1->isSwitch()) {
	assert(false);
	return;
    }
    if (p1->isFile()) {
	assert(false);
	return;
    }
    assert(false);
}
#endif

/* FloatParameter */

FloatParameter::~ParameterV() {
    if (own_var) {
	delete value;
    }
}

void *FloatParameter::zone() {
    return value;
}

void FloatParameter::set(float n, float high, float llimit, float ulimit) {
    switch (c_type) {
    case Continuous:
        assert(n >= 0 && n <= high);
        *value = llimit + (n / high) * (ulimit - llimit);
        break;
    case Switch:
        *value = (2*n > high ? 1.0 : 0.0);
        break;
    case Enum:
        *value = lower + min(n, upper-lower);
        break;
    default:
        assert(false);
        break;
    }
}

void FloatParameter::stdJSON_value() {
    json_value = std_value;
}

void FloatParameter::writeJSON(gx_system::JsonWriter& jw) {
    jw.write_key(_id.c_str());
    jw.write(*value);
}

void FloatParameter::readJSON_value(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::value_number);
    json_value = jp.current_value_float();
}

bool FloatParameter::compareJSON_value() {
    return json_value == *value;
}

void FloatParameter::setJSON_value() {
    set(json_value);
}

void FloatParameter::convert_from_range(float low, float up) {
    json_value = lower + (json_value - low) / (up - low) * (upper - lower);
}

bool FloatParameter::hasRange() const {
    return true;
}

float FloatParameter::getLowerAsFloat() const {
    return lower;
}

float FloatParameter::getUpperAsFloat() const {
    return upper;
}

float FloatParameter::getStepAsFloat() const {
    return step;
}


/* FloatEnumParameter */

FloatEnumParameter::FloatEnumParameter(const string& id, const string& name, const value_pair* vn, bool preset,
                                       float *v, int sv, bool ctrl):
    FloatParameter(id, name, Enum, preset, v, sv, 0, get_upper(vn), 1, ctrl),
    value_names(vn) {}

const value_pair *FloatEnumParameter::getValueNames() const {
    return value_names;
}

void FloatEnumParameter::writeJSON(gx_system::JsonWriter& jw) {
    jw.write_key(_id.c_str());
    jw.write(value_names[static_cast<int>(round(*value))].value_id);
}

void FloatEnumParameter::readJSON_value(gx_system::JsonParser& jp) {
    gx_system::JsonParser::token tok = jp.next();
    if (tok == gx_system::JsonParser::value_number) {
        // old version compatability
        json_value = jp.current_value_int();
        return;
    }
    jp.check_expect(gx_system::JsonParser::value_string);
    int up = static_cast<int>(round(upper));
    int n = 0;
    for (; n <= up; n++) {
        if (jp.current_value() == value_names[n].value_id) {
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

IntParameter::~ParameterV() {
    if (own_var) {
	delete value;
    }
}

void *IntParameter::zone() {
    return value;
}

int IntParameter::idx_from_id(string v_id) {
    assert(false);
    return 0;
}

void IntParameter::set(float n, float high, float llimit, float ulimit) {
    switch (c_type) {
    case Continuous:
        assert(false); // not implemented
        break;
    case Switch:
	assert(false); // not implemented
        break;
    case Enum:
        *value = lower + min(static_cast<int>(n), upper-lower);
        break;
    default:
        assert(false);
        break;
    }
}

void IntParameter::stdJSON_value() {
    json_value = std_value;
}

void IntParameter::writeJSON(gx_system::JsonWriter& jw) {
    jw.write_key(_id.c_str());
    jw.write(*value);
}

void IntParameter::readJSON_value(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::value_number);
    json_value = jp.current_value_int();
}

bool IntParameter::compareJSON_value() {
    return json_value == *value;
}

void IntParameter::setJSON_value() {
    set(json_value);
}

bool IntParameter::hasRange() const {
    return true;
}

float IntParameter::getLowerAsFloat() const {
    return lower;
}

float IntParameter::getUpperAsFloat() const {
    return upper;
}

/* EnumParameter */

EnumParameter::EnumParameter(const string& id, const string& name, const value_pair* vn, bool preset,
                             int *v, int sv, bool ctrl):
    IntParameter(id, name, Enum, preset, v, sv, 0, get_upper(vn), ctrl),
    value_names(vn) {}

const value_pair *EnumParameter::getValueNames() const {
    return value_names;
}

int EnumParameter::idx_from_id(string v_id) {
    int n = 0;
    for (; n <= upper; n++) {
        if (v_id == value_names[n].value_id) {
            return n;
        }
    }
    return -1;
}

void EnumParameter::writeJSON(gx_system::JsonWriter& jw) {
    jw.write_key(_id.c_str());
    jw.write(value_names[*value].value_id);
}

void EnumParameter::readJSON_value(gx_system::JsonParser& jp) {
    gx_system::JsonParser::token tok = jp.next();
    if (tok == gx_system::JsonParser::value_number) {
        // old version compatability
        json_value = jp.current_value_int();
        return;
    }
    jp.check_expect(gx_system::JsonParser::value_string);
    int n = idx_from_id(jp.current_value());
    if (n < 0) {
        gx_system::gx_print_warning(
            _("read parameter"), (boost::format(_("parameter %1%: unknown enum value: %2%"))
                               % _id % jp.current_value()).str());
        n = 0;
    }
    json_value = n;
}

/* unsigned IntParameter */

UIntParameter::~ParameterV() {
    if (own_var) {
	delete value;
    }
}

void *UIntParameter::zone() {
    return value;
}

void UIntParameter::set(float n, float high, float llimit, float ulimit) {
    switch (c_type) {
    case Continuous:
        assert(false); // not implemented
        break;
    case Switch:
	assert(false); // not implemented
        break;
    case Enum:
        *value = lower + min(static_cast<unsigned int>(n), upper-lower);
        break;
    default:
        assert(false);
        break;
    }
}

void UIntParameter::stdJSON_value() {
    json_value = std_value;
}

void UIntParameter::writeJSON(gx_system::JsonWriter& jw) {
    jw.write_key(_id.c_str());
    jw.write(*value);
}

void UIntParameter::readJSON_value(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::value_number);
    json_value = jp.current_value_uint();
}

bool UIntParameter::compareJSON_value() {
    return json_value == *value;
}

void UIntParameter::setJSON_value() {
    set(json_value);
}

bool UIntParameter::hasRange() const {
    return true;
}

float UIntParameter::getLowerAsFloat() const {
    return lower;
}

float UIntParameter::getUpperAsFloat() const {
    return upper;
}

/* UEnumParameter */

UEnumParameter::UEnumParameter(const string& id, const string& name, const value_pair* vn, bool preset,
                             unsigned int *v, unsigned int sv, bool ctrl):
    UIntParameter(id, name, Enum, preset, v, sv, 0, get_upper(vn), ctrl),
    value_names(vn) {}

const value_pair *UEnumParameter::getValueNames() const {
    return value_names;
}

void UEnumParameter::writeJSON(gx_system::JsonWriter& jw) {
    jw.write_key(_id.c_str());
    jw.write(value_names[*value].value_id);
}

void UEnumParameter::readJSON_value(gx_system::JsonParser& jp) {
    gx_system::JsonParser::token tok = jp.next();
    if (tok == gx_system::JsonParser::value_number) {
        // old version compatability
        json_value = jp.current_value_uint();
        return;
    }
    jp.check_expect(gx_system::JsonParser::value_string);
    unsigned int n = 0;
    for (; n <= upper; n++) {
        if (jp.current_value() == value_names[n].value_id) {
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

BoolParameter::~ParameterV() {
    if (own_var) {
	delete value;
    }
}

void *BoolParameter::zone() {
    return value;
}

void BoolParameter::set(float n, float high, float llimit, float ulimit) {
    switch (c_type) {
    case Switch:
        *value = (2*n > high);
    default:
        assert(false);
        break;
    }
}

void BoolParameter::stdJSON_value() {
    json_value = std_value;
}

void BoolParameter::writeJSON(gx_system::JsonWriter& jw) {
    jw.write_key(_id.c_str());
    jw.write(*value);
}

void BoolParameter::readJSON_value(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::value_number);
    json_value = jp.current_value_int();
}

bool BoolParameter::compareJSON_value() {
    return json_value == *value;
}

void BoolParameter::setJSON_value() {
    set(json_value);
}


/* SwitchParameter */

void SwitchParameter::set(bool val) {
    if (val != value) {
        value = val;
        changed(value);
    }
}

void *SwitchParameter::zone() {
    return &value;
}

void SwitchParameter::stdJSON_value() {
    json_value = std_value;
}

void SwitchParameter::set(float n, float high, float llimit, float ulimit) {
    assert(false);
}

void SwitchParameter::writeJSON(gx_system::JsonWriter& jw) {
    jw.write_key(_id.c_str());
    jw.write(value);
}

void SwitchParameter::readJSON_value(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::value_number);
    json_value = jp.current_value_int();
}

bool SwitchParameter::compareJSON_value() {
    return json_value == value;
}

void SwitchParameter::setJSON_value() {
    set(json_value);
}


/* FileParameter */

void FileParameter::set_path(const string& path) {
    Glib::RefPtr<Gio::File> v = Gio::File::create_for_path(path);
    if (is_equal(v)) {
	return;
    }
    value = v;
    changed();
}

void FileParameter::set(const Glib::RefPtr<Gio::File>& val) {
    if (is_equal(val)) {
	return;
    }
    value = val;
    changed();
}

void FileParameter::set_standard(const string& filename) {
    std_value = Gio::File::create_for_path(filename);
    if (!value) {
        value = std_value->dup();
	changed();
    }
}

void FileParameter::stdJSON_value() {
    json_value = std_value->dup();
    changed();
}

void *FileParameter::zone() {
    return &value;
}

void FileParameter::set(float n, float high, float llimit, float ulimit) {
    assert(false);
}

void FileParameter::writeJSON(gx_system::JsonWriter& jw) {
    jw.write_key(_id.c_str());
    jw.write(get_path());
}

void FileParameter::readJSON_value(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::value_string);
    json_value = Gio::File::create_for_path(jp.current_value());
}

bool FileParameter::compareJSON_value() {
    return json_value->get_path() == value->get_path(); //FIXME
}

void FileParameter::setJSON_value() {
    set(json_value);
}

static string get_file_id(const Glib::RefPtr<Gio::File>& f) {
    return f->query_info(G_FILE_ATTRIBUTE_ID_FILE)->get_attribute_string(G_FILE_ATTRIBUTE_ID_FILE);
}

bool FileParameter::is_equal(const Glib::RefPtr<Gio::File>& v) const {
    string id, id2;
    try {
        id = get_file_id(value);
    } catch(Gio::Error& ex) {
        return false; // FIXME check type of exception
    }
    try {
	id2 = get_file_id(v);
    } catch(Gio::Error& ex) {
        return false; // FIXME check type of exception
    }
    return id == id2;
}

string FileParameter::get_path() {
    return value->get_path();
}

string FileParameter::get_directory_path() {
    return value->get_parent()->get_path();
}

string FileParameter::get_parse_name() {
    return value->get_parse_name();
}

string FileParameter::get_display_name() {
    return value->query_info(G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME)->get_display_name();
}

void FileParameter::copy(const string& destination) {
    value->copy(Gio::File::create_for_path(destination));
}


/* StringParameter */

StringParameter::~ParameterV() {
    if (own_var) {
	delete value;
    }
}

void *StringParameter::zone() {
    return value;
}

void StringParameter::set(float n, float high, float llimit, float ulimit) {
    assert(false);
}

void StringParameter::stdJSON_value() {
    json_value = std_value;
}

void StringParameter::writeJSON(gx_system::JsonWriter& jw) {
    jw.write_key(_id.c_str());
    jw.write(*value);
}

void StringParameter::readJSON_value(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::value_string);
    json_value = jp.current_value();
}

bool StringParameter::compareJSON_value() {
    return json_value == *value;
}

void StringParameter::setJSON_value() {
    set(json_value);
}


/****************************************************************
 ** Parameter Map
 */

ParamMap::ParamMap()
    : id_map(),
      addr_map() {
}

ParamMap::~ParamMap() {
    for (iterator i = id_map.begin(); i != id_map.end(); ++i) {
	delete i->second;
    }
}

#ifndef NDEBUG
void ParamMap::unique_zone(Parameter* param) {
    if (addr_map.find(param->zone()) != addr_map.end()) {
        gx_system::gx_print_error("Debug Check", "zone registered twice (id: " + param->id() +")");
    }
}

void ParamMap::unique_id(Parameter* param) {
    if (id_map.find(param->id()) != id_map.end()) {
        gx_system::gx_print_error("Debug Check", "id registered twice: " + param->id());
    }
}

void ParamMap::check_addr(const void *p) {
    if (!hasZone(p)) {
        cerr << "zone not found: " << p << endl;
    }
}
void ParamMap::check_id(const string& id) {
    if (!hasId(id)) {
        cerr << "string-id not found: " << id << endl;
    }
}

void ParamMap::check_p(const char *p) {
    if (!hasId(p)) {
        cerr << "char-id not found: " << p << endl;
    }
}

void ParamMap::dump(const string& fmt) {
    gx_system::JsonWriter *p = 0;
    gx_system::JsonWriter jw;
    if (fmt == "json") {
	jw.set_stream(&cout);
	p = &jw;
	jw.begin_array();
	jw.newline();
    } else {
	printf("parameter map dump\n");
    }
    for (iterator i = id_map.begin(); i != id_map.end(); ++i) {
	i->second->dump(p);
    }
    if (p) {
	jw.end_array();
	jw.close();
    } else {
	printf("---------------------\n");
    }
}

void Parameter::dump(gx_system::JsonWriter *jw) {
    if (jw) {
	jw->begin_array();
	jw->write(id());
	jw->write(l_group());
	jw->write(l_name());
	switch (v_type) {
	case tp_float:  jw->write("f"); jw->write(getFloat().get_value());     break;
	case tp_int:    jw->write("i"); jw->write(getInt().get_value());       break;
	case tp_uint:   jw->write("u"); jw->write(getUInt().get_value());      break;
	case tp_bool:   jw->write("b"); jw->write(getBool().get_value());      break;
	case tp_switch: jw->write("s"); jw->write(getSwitch().get());          break;
	case tp_file:   jw->write("F"); jw->write(getFile().get_parse_name()); break;
	case tp_string: jw->write("S"); jw->write(getString().get_value());    break;
	default: assert(false);
	}
	jw->write(getLowerAsFloat());
	jw->write(getUpperAsFloat());
	jw->write(getStepAsFloat());
	const value_pair *vn = getValueNames();
	if (vn) {
	    jw->begin_array();
	    for (int n = 0; ; ++n) {
		if (!vn[n].value_id) {
		    break;
		}
		jw->begin_array();
		jw->write(vn[n].value_id);
		jw->write(vn[n].value_label ? vn[n].value_label : vn[n].value_id);
		jw->end_array();
	    }
	    jw->end_array();
	}
	jw->end_array();
	jw->newline();
    } else {
	printf("P: %s vt=%d ct=%d c=%d\n", _id.c_str(), v_type, c_type, controllable);
    }
}
#endif

void ParamMap::insert(Parameter* param) {
    debug_check(unique_zone, param);
    addr_map.insert(pair<const void*, Parameter*>(param->zone(), param));
    debug_check(unique_id, param);
    id_map.insert(pair<string, Parameter*>(param->id(), param));
}

void ParamMap::set_init_values() {
    for (iterator i = id_map.begin(); i != id_map.end(); ++i) {
        i->second->stdJSON_value();
	i->second->setJSON_value();
    }
}
} // namespace gx_gui


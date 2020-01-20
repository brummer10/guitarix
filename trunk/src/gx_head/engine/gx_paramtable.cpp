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

    {22, "Midi Beat Clock"},
    {23, "Clock start/stop"},
    {24, "Jack Transport"},

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

string MidiStandardControllers::midi_to_note(int ctr) {
	static const char* notes[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
    int octave = (ctr / 12) - 1;
    ostringstream b;
    b << octave;
    string p = b.str().substr(0, 1);
    int index = (ctr % 12);
    string note = notes[index];
    return note + p;
}

string MidiStandardControllers::ctr_desc(int ctr) {
    string p = midi_to_note(ctr-200);
    return  "Note On ( " + p + " )";
 }

MidiStandardControllers::MidiStandardControllers() {
    for (unsigned int i = 0; i < sizeof(midi_std_itab)/sizeof(midi_std_itab[0]); i++) {
        m.insert(pair<int, modstring>(midi_std_itab[i].ctrl, modstring(midi_std_itab[i].name)));
    }
    for (unsigned int i = 0; i < 127; i++) {
        const int mm = i + 200;
        m.insert(pair<int, modstring>(mm, modstring(ctr_desc(mm).c_str())));
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
            jw.write_kv(ostr.str().c_str(), i->second.name);
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
        jw.write(toggle);
        jw.write(_toggle_behaviour);
    }
    jw.end_array();
}

MidiController *MidiController::readJSON(gx_system::JsonParser& jp, ParamMap& pmap) {
    jp.next(gx_system::JsonParser::begin_array);
    jp.next(gx_system::JsonParser::value_string);
    string id = jp.current_value();
    if (!pmap.hasId(id)) {
        gx_print_warning(_("Midi controller settings"),
                                    _("unknown parameter: ") + id);
        while (jp.next() != gx_system::JsonParser::end_array);
        return 0;
    }
    Parameter& pm = pmap[id];
    float lower = 0, upper = 0;
    bool toggle = false;
    int toggle_behaviour = 0;
    bool bad = false;
    bool chg = false;
    if (pm.getControlType() == Parameter::Continuous ||
        pm.getControlType() == Parameter::Enum) {
        if (jp.peek() == gx_system::JsonParser::value_number) {
            jp.next(gx_system::JsonParser::value_number);
            if (jp.peek() == gx_system::JsonParser::value_number) {
                // two numbers -> range
                float pmin, pmax;
                if (pm.hasRange()) {
                    pmin = pm.getLowerAsFloat();
                    pmax = pm.getUpperAsFloat();
                } else {
                    bad = true;
                    pmin = pmax = 0;
                }
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
                // just one number -> switch (new format)
                bad = true;
            }
        } else {
            // no number -> switch (old format)
            bad = true;
        }
    } else if (pm.getControlType() == Parameter::Switch) {
        if (jp.peek() == gx_system::JsonParser::value_number) {
            jp.next(gx_system::JsonParser::value_number);
            int _toggle = jp.current_value_int();
            if (jp.peek() == gx_system::JsonParser::value_number) {
                jp.next(gx_system::JsonParser::value_number);
                if (jp.current_value_int() < Parameter::toggle_type::_Count) {
                   toggle = _toggle;
                   toggle_behaviour = jp.current_value_int();
                } else {
                   // two numbers -> range
                   bad = true;
                }
            } else {
                toggle = _toggle;
            }
        }
    } else {
        // bad control type
        bad = true;
    }
    assert(jp.peek() == gx_system::JsonParser::end_array);
    while (jp.next() != gx_system::JsonParser::end_array); // be tolerant (non-debug mode)
    if (bad) {
        gx_print_warning(
            _("recall MIDI state"),
            _("invalid format, Parameter skipped: ") + id);
        return 0;
    }
    if (chg) {
        gx_print_warning(
            _("recall MIDI state"),
            _("Parameter range outside bounds, changed: ") + id);
    }
    return new MidiController(pm, lower, upper, toggle, toggle_behaviour);
}

bool MidiController::set_midi(int n, int last_value, bool update) {
    bool ret = false;
    if (param->get_midi_blocked()) return ret;
    if (toggle) {
        switch (_toggle_behaviour) {
            case Parameter::toggle_type::OnOff: {
                bool s_o = (2*last_value > 127);
                bool s_n = (2*n > 127);
                if (!s_o && s_n) {
                    if (param->on_off_value()) {
                        ret = param->midi_set(0, 127, _lower, _upper);
                    } else {
                        ret = param->midi_set(127, 127, _lower, _upper);
                    }
                }
                break;
            }
            case Parameter::toggle_type::Constant: {
                if (n == last_value || last_value == -1) {
                    if (param->on_off_value()) {
                        if (!update) ret = param->midi_set(0, n, _lower, _upper);
                        else ret = param->midi_set(127, n, _lower, _upper);
                    } else {
                        if (!update) ret = param->midi_set(127, n, _lower, _upper);
                        else ret = param->midi_set(0, n, _lower, _upper);
                    }
                }
                break;
            }
            case Parameter::toggle_type::Toggle: {
                if (param->on_off_value() && !n) {
                    ret = param->midi_set(0, 127, _lower, _upper);
                } else {
                    ret = param->midi_set(127, 127, _lower, _upper);
                }
                break;
            }
        }
    } else {
        //fprintf(stderr,"continues %s \n",param->id().c_str());
        //fprintf(stderr,"%f \n",(127.*log10f(double(n+1.)))/2.1072);
        //fprintf(stderr,"%f \n",double(n * double(double(n+1.)/128)));
        ret = param->midi_set(n, 127, _lower, _upper);
        param->trigger_changed();
    }
    //param->trigger_changed();
    return ret;
}

bool MidiController::set_trans(int n, int last_value) {
    bool ret = false;
    if (param->get_blocked()) return ret;
    if (strcmp(param->id().c_str(), "engine.mute")==0) {
        if ( n == 0) n = 127;
        else n = 0;
    }
    ret = param->midi_set(n, 127, _lower, _upper);
    return ret;
}

bool MidiController::set_bpm(int n, int last_value) {
    bool ret = false;
    if (param->get_blocked()) return ret;
    if (toggle) {
	bool s_o = (2*last_value > 360);
	bool s_n = (2*n > 360);
	if (!s_o && s_n) {
	    if (param->on_off_value()) {
		ret = param->midi_set_bpm(0, 360, _lower, _upper);
	    } else {
		ret = param->midi_set_bpm(360, 360, _lower, _upper);
	    }
	}
    } else {
	ret = param->midi_set_bpm(n, 360, _lower, _upper);
    }
    return ret;
}

/****************************************************************
 ** class ControllerArray
 */

void ControllerArray::readJSON(gx_system::JsonParser& jp, ParamMap& param) {
    for (unsigned int n = 0; n < array_size; n++) {
	operator[](n).clear();
    }
    jp.next(gx_system::JsonParser::begin_array);
    while (jp.peek() != gx_system::JsonParser::end_array) {
        jp.next(gx_system::JsonParser::value_number);
	midi_controller_list& l = operator[](jp.current_value_int());
        jp.next(gx_system::JsonParser::begin_array);
        while (jp.peek() != gx_system::JsonParser::end_array) {
            MidiController *p = MidiController::readJSON(jp, param);
            if (p) {
                l.push_back(*p);
		delete p;
            }
        }
        jp.next(gx_system::JsonParser::end_array);
    }
    jp.next(gx_system::JsonParser::end_array);
}

void ControllerArray::writeJSON(gx_system::JsonWriter& w) const {
    w.begin_array(true);
    for (unsigned int n = 0; n < array_size; n++) {
        const midi_controller_list& cl = operator[](n);
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

int ControllerArray::param2controller(Parameter& param, const MidiController** p) {
    for (ControllerArray::size_type n = 0; n < size(); ++n) {
        const midi_controller_list& cl = operator[](n);
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

bool ControllerArray::deleteParameter(Parameter& p) {
    for (iterator pctr = begin(); pctr != end(); ++pctr) {
        for (midi_controller_list::iterator i = pctr->begin(); i != pctr->end(); ++i) {
            if (i->hasParameter(p)) {
                pctr->erase(i);
                return true;
            }
        }
    }
    return false;
}


/****************************************************************
 ** class MidiClockToBpm
 */


MidiClockToBpm::MidiClockToBpm()
    : time1(0),
      time_diff(0),
      collect(0),
      collect_(0),
      bpm(0),
      bpm_new(0),
      ret(false) {}

unsigned int MidiClockToBpm::rounded(float f) {
    if (f >= 0x1.0p23) return (unsigned int) f;
    return (unsigned int) (f + 0.49999997f);
}

bool MidiClockToBpm::time_to_bpm(double time, unsigned int* bpm_) {
    ret = false;
    // if time drift to far, reset bpm detection.
    if ((time-time1)> (1.05*time_diff) || (time-time1)*1.05 < (time_diff)) { 
        bpm = 0;
        collect = 0;
        collect_ = 0;
    } else {
        bpm_new = ((1000000000. / (time-time1) / 24) * 60);
        bpm += bpm_new;
        collect++;
        
        if (collect >= (bpm_new*bpm_new*0.0002)+1) {
          bpm = (bpm/collect);
          if (collect_>=2) {
            (*bpm_) = rounded(min(360.,max(24.,bpm))); 
            collect_ = 0;
            ret = true;
          }
          collect_++;
          collect = 1;
        }
    }
    time_diff = time-time1;
    time1 = time;
    return ret;
}

/****************************************************************
 ** class MidiControllerList
 */

MidiControllerList::MidiControllerList()
    : map(),
      last_midi_control_value(),
      last_midi_control(-2),
      changed_midi_control_value(),
      program_change(-1),
      mute_change(-1),
      bank_change(-1),
      time0(0),
      bpm_(9),
      mp(),
      pgm_chg(),
      mute_chg(),
      bank_chg(),
      val_chg(),
      changed(),
      new_program(),
      new_mute_state(),
      new_bank(),
      midi_value_changed() {
    for (int i = 0; i < ControllerArray::array_size; ++i) {
	last_midi_control_value[i] = -1;
	changed_midi_control_value[i] = 0;
    }
    pgm_chg.connect(sigc::mem_fun(*this, &MidiControllerList::on_pgm_chg));
    mute_chg.connect(sigc::mem_fun(*this, &MidiControllerList::on_mute_chg));
    bank_chg.connect(sigc::mem_fun(*this, &MidiControllerList::on_bank_chg));
    val_chg.connect(sigc::mem_fun(*this, &MidiControllerList::on_val_chg));
   // Glib::signal_timeout().connect(
	// sigc::mem_fun(this, &MidiControllerList::check_midi_values), 60);
}

bool MidiControllerList::check_midi_values() {
    static int saved_values[ControllerArray::array_size];
    for (unsigned int n = 0; n < ControllerArray::array_size; ++n) {
        if (changed_midi_control_value[n]) {
            changed_midi_control_value[n] = 0;
            saved_values[n] = last_midi_control_value[n];
            midi_value_changed(n, saved_values[n]);
            if (!get_config_mode()) {
                midi_controller_list& ctr_list = map[n];
                for (midi_controller_list::iterator i = ctr_list.begin(); i != ctr_list.end(); ++i) {
                    if (i->is_toggle()
                        && i->toggle_behaviour() == Parameter::toggle_type::Constant) {
                        midi_value_changed(n, i->getParameter().on_off_value() * 127);
                    }
                    i->trigger_changed();
                }
            }
        }
    }
    return true;
}

void MidiControllerList::on_val_chg() {
    static int saved_values[ControllerArray::array_size];
    for (unsigned int n = 0; n < ControllerArray::array_size; ++n) {
        if (changed_midi_control_value[n]) {
            changed_midi_control_value[n] = 0;
            saved_values[n] = last_midi_control_value[n];
            midi_value_changed(n, saved_values[n]);
            if (!get_config_mode()) {
                midi_controller_list& ctr_list = map[n];
                for (midi_controller_list::iterator i = ctr_list.begin(); i != ctr_list.end(); ++i) {
                    if (i->is_toggle()
                        && i->toggle_behaviour() == Parameter::toggle_type::Constant) {
                        midi_value_changed(n, i->getParameter().on_off_value() * 127);
                    }
                    i->trigger_changed();
                }
            }
        }
    }
}

/** update all controlled parameters with last received value from MIDI controller ctr. */
void MidiControllerList::update_from_controller(int ctr) {
    int v = get_last_midi_control_value(ctr);
    if (v >= 0) {
	midi_controller_list& cl = map[ctr];
	for (midi_controller_list::iterator i = cl.begin(); i != cl.end(); ++i) {
	    i->set_midi(v, v, true);
	}
    }
}

void MidiControllerList::update_from_controllers() {
    for (unsigned int n = 0; n < map.size(); n++) {
	update_from_controller(n);
    }
}

void MidiControllerList::on_pgm_chg() {
    int pgm;
    do {
	pgm = gx_system::atomic_get(program_change);
    } while (!gx_system::atomic_compare_and_exchange(&program_change, pgm, -1));
    if (pgm>=0) new_program(pgm);
}

void MidiControllerList::on_mute_chg() {
    int mute;
    do {
	mute = gx_system::atomic_get(mute_change);
    } while (!gx_system::atomic_compare_and_exchange(&mute_change, mute, -1));
    new_mute_state(mute);
}

void MidiControllerList::on_bank_chg() {
    int bk;
    do {
	bk = gx_system::atomic_get(bank_change);
    } while (!gx_system::atomic_compare_and_exchange(&bank_change, bk, -1));
    if (bk>=0) new_bank(bk);
}

void MidiControllerList::set_config_mode(bool mode, int ctl) {
    assert(mode != get_config_mode());
    if (mode) {
        last_midi_control = ctl;
    } else {
        last_midi_control = -2;
    }
}

void MidiControllerList::deleteParameter(Parameter& p) {
    bool mode = get_config_mode();
    if (!mode) {
        set_config_mode(true); // keep rt thread away from table
    }
    if (map.deleteParameter(p)) {
        changed();
    }
    if (!mode) {
        set_config_mode(false);
    }
}

void MidiControllerList::modifyCurrent(Parameter &param,
                                       float lower, float upper, bool toggle, int toggle_behaviour) {
    if (!get_config_mode()) {
	assert(false);
	return;	// keep rt thread away from table
    }
    // maximal one controller for a zone allowed
    deleteParameter(param);
    if (last_midi_control < 0)
        return;
    // add zone to controller
    map[last_midi_control].push_front(MidiController(param, lower, upper, toggle, toggle_behaviour));
    update_from_controller(last_midi_control);
    changed();
}

void MidiControllerList::request_midi_value_update() {
    for (unsigned int n = 0; n < ControllerArray::array_size; ++n) {
        int v = last_midi_control_value[n];
        midi_controller_list& ctr_list = map[n];
        for (midi_controller_list::iterator i = ctr_list.begin(); i != ctr_list.end(); ++i) {
            if (i->is_toggle()) {
                v = i->getParameter().on_off_value() * 127;
            }
            midi_value_changed(n, v);
        }
    }
}

void MidiControllerList::set_ctr_val(int ctr, int val) {
    if (get_config_mode()) {
        last_midi_control = ctr;
    } else {
        midi_controller_list& ctr_list = map[ctr];
        for (midi_controller_list::iterator i = ctr_list.begin(); i != ctr_list.end(); ++i) {
            i->set_midi(val, get_last_midi_control_value(ctr), false);
        }
    }
    MidiControllerList::set_last_midi_control_value(ctr, val);
}

void MidiControllerList::set_bpm_val(unsigned int val) {
    if (get_config_mode()) {
        last_midi_control = 22;
    } else {
        midi_controller_list& ctr_list = map[22];
        for (midi_controller_list::iterator i = ctr_list.begin(); i != ctr_list.end(); ++i) {
            i->set_bpm(val, get_last_midi_control_value(22));
	}
    }
    MidiControllerList::set_last_midi_control_value(22, val);
}

void MidiControllerList::set_controller_array(const ControllerArray& m) {
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
                                                      const ControllerArray *new_m) {
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

void MidiControllerList::set_midi_channel(int s) {
    channel_select = s;
}

void MidiControllerList::process_trans(int transport_state) {
    unsigned int val = 0;
    switch (transport_state) {
        case JackTransportStopped:
            val = 0;
            break;
        case JackTransportRolling:
            val = 127;
            break;
        case JackTransportStarting:
            val = 127;
            break;
        default:
            return;
    }
    if (get_config_mode()) {
        last_midi_control = 24;
    } else {
        midi_controller_list& ctr_list = map[24];
        for (midi_controller_list::iterator i = ctr_list.begin(); i != ctr_list.end(); ++i) {
            i->set_trans(val, get_last_midi_control_value(24));
        }
    }
    MidiControllerList::set_last_midi_control_value(24, val);
    val_chg();
}

// ----- jack process callback for the midi input
void MidiControllerList::compute_midi_in(void* midi_input_port_buf, void *arg) {
    jack_midi_event_t in_event;
    jack_nframes_t event_count = jack_midi_get_event_count(midi_input_port_buf);
    unsigned int i;
    for (i = 0; i < event_count; i++) {
        jack_midi_event_get(&in_event, midi_input_port_buf, i);
        bool ch = true;
        if (channel_select>0) {
            if ((channel_select) != (int(in_event.buffer[0]&0x0f)+1)) {
                ch = false;
            }
        }
        if ((in_event.buffer[0] & 0xf0) == 0xc0 && ch) {  // program change on any midi channel
            gx_system::atomic_set(&program_change, in_event.buffer[1]);
            pgm_chg();
        } else if ((in_event.buffer[0] & 0xf0) == 0xb0 && ch) {   // controller
			if (in_event.buffer[1]== 120) { // engine mute by All Sound Off on any midi channel
				gx_system::atomic_set(&mute_change, in_event.buffer[2]);
				 mute_chg();
			} else if (in_event.buffer[1]== 32 && ch) { // bank change on any midi channel
				gx_system::atomic_set(&bank_change, in_event.buffer[2]);
				 bank_chg();
			} else {
				set_ctr_val(in_event.buffer[1], in_event.buffer[2]);
				val_chg();
			}
        } else if ((in_event.buffer[0] & 0xf0) == 0x90 && ch) {   // Note On
			set_ctr_val(in_event.buffer[1]+200, 1);
			val_chg();
			//fprintf(stderr,"Note On %i", (int)in_event.buffer[1]);
		} else if ((in_event.buffer[0] ) > 0xf0) {   // midi clock
            if ((in_event.buffer[0] ) == 0xf8) {   // midi beat clock
                clock_gettime(CLOCK_MONOTONIC, &ts1);
                gx_jack::GxJack& jack = *static_cast<gx_jack::GxJack*>(arg);
                static unsigned int sr = jack.get_jack_sr();
                time0 = (ts1.tv_sec*1000000000.0)+(ts1.tv_nsec)+
                        (1000000000.0/(double)(sr/(double)in_event.time));
                if (mp.time_to_bpm(time0, &bpm_)) {
                    set_bpm_val(bpm_);
                    val_chg();
                }
            } else if ((in_event.buffer[0] ) == 0xfa) {   // midi clock start
                set_ctr_val(23, 127);
                val_chg();
            } else if ((in_event.buffer[0] ) == 0xfb) {   // midi clock continue
               //  set_ctr_val(23, 127);
            } else if ((in_event.buffer[0] ) == 0xfc) {   // midi clock stop
                set_ctr_val(23, 0);
                val_chg();
            } else if ((in_event.buffer[0] ) == 0xf2) {   // midi clock position
              // not implemented 
              //  set_ctr_val(24,(in_event.buffer[2]<<7) | in_event.buffer[1]);
            }
        }
    }
}

/****************************************************************
 ** Parameter Groups
 */

ParameterGroups::ParameterGroups() {
    insert("system", N_("System"));
    insert("ui", N_("User Interface"));
    insert("ui.amp", N_("User Interface")); // FIXME (ui.amp.tonestack)
    insert("engine", N_("Audio Engine"));
}

ParameterGroups::~ParameterGroups() {
#ifndef NDEBUG
    for (map<string, bool>::iterator i = used.begin(); i != used.end(); ++i) {
	if (!i->second) {
	    gx_print_error("Debug Check", "Group not used: " + i->first);
	}
    }
#endif
}

#ifndef NDEBUG
void ParameterGroups::group_exists(const string& id) {
    if (groups.find(id) == groups.end()) {
	gx_print_error("Debug Check", "Group does not exist: " + id);
    } else {
	used[id] = true;
    }
}

void ParameterGroups::group_is_new(const string& id) {
    if (groups.find(id) != groups.end()) {
	gx_print_error("Debug Check", "Group already exists: " + id);
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

string param_group(const string& group_id, bool nowarn) {
    static ParameterGroups& groups = get_group_table();
    if (nowarn) {
        return groups.get(group_id);
    } else {
        return groups[group_id];
    }
}

bool ParameterGroups::group_exist(const string& id) {
    if (groups.find(id) == groups.end()) {
	return false;
    } else {
	return true;
    }
}

/****************************************************************
 ** Parameter
 */

gx_system::JsonParser& Parameter::jp_next(gx_system::JsonParser& jp, const char *key) {
    jp.next(gx_system::JsonParser::begin_object);
    jp.next(gx_system::JsonParser::value_key);
    assert(jp.current_value() == key);
    return jp;
}

void Parameter::serializeJSON(gx_system::JsonWriter& jw) {
    jw.begin_object();
    jw.write_kv("id", _id);
    jw.write_kv("name", _name);
    jw.write_kv("group", _group);
    jw.write_kv("desc", _desc);
    jw.write_kv("v_type", v_type); //FIXME
    jw.write_kv("c_type", c_type); //FIXME
    jw.write_kv("d_flags", d_flags); //FIXME
    if (!controllable) {
	jw.write_key("non_controllable"); jw.write(false);
    }
    if (!save_in_preset) {
	jw.write_key("non_preset"); jw.write(false);
    }
    jw.end_object();
}

Parameter::Parameter(gx_system::JsonParser& jp)
    : boost::noncopyable(),
      _id(),
      _name(),
      _group(),
      _desc(),
      v_type(tp_float),
      c_type(Continuous),
      d_flags(0),
      save_in_preset(true),
      controllable(true),
      do_not_save(false),
      blocked(false),
      used(false) {
    jp.next(gx_system::JsonParser::begin_object);
    while (jp.peek() != gx_system::JsonParser::end_object) {
	jp.next(gx_system::JsonParser::value_key);
	if (jp.read_kv("id", _id) ||
	    jp.read_kv("name", _name) ||
	    jp.read_kv("group", _group) ||
	    jp.read_kv("desc", _desc)) {
	} else if (jp.current_value() == "v_type") {
	    jp.next(gx_system::JsonParser::value_number);
	    v_type = static_cast<value_type>(jp.current_value_int());
	} else if (jp.current_value() == "c_type") {
	    jp.next(gx_system::JsonParser::value_number);
	    c_type = static_cast<ctrl_type>(jp.current_value_int());
	} else if (jp.current_value() == "d_flags") {
	    jp.next(gx_system::JsonParser::value_number);
	    d_flags = jp.current_value_int();
	} else if (jp.current_value() == "non_controllable") {
	    jp.next(gx_system::JsonParser::value_number);
	    controllable = false;
	} else if (jp.current_value() == "non_preset") {
	    jp.next(gx_system::JsonParser::value_number);
	    save_in_preset = false;
	} else {
	    gx_print_warning(
		"Parameter", Glib::ustring::compose("%1: unknown key: %2", _id, jp.current_value()));
	    jp.skip_object();
	}
    }
    jp.next(gx_system::JsonParser::end_object);
}

Parameter::~Parameter() {
}

bool Parameter::midi_set(float n, float high, float llimit, float ulimit) {
    assert(false);
    return false;
}

bool Parameter::midi_set_bpm(float n, float high, float llimit, float ulimit) {
    assert(false);
    return false;
}

void Parameter::trigger_changed() {
    assert(false);
}

static int get_upper(const value_pair *vn) {
    for (int n = 0; ; n++) {
        if (!vn[n].value_id) {
            return n - 1;
        }
    }
}

void Parameter::range_warning(float value, float lower, float upper) {
    gx_print_warning(
	_("parameter load"),
	Glib::ustring::compose(_("parameter %1: value %2 out of range [%3, %4]"),
			       _id, value, lower, upper));
}

const char *Parameter::get_typename() const {
    static const char *tpname[] = {
	"float", "int", "bool", "bool", "filename", "string", "special"};
    assert(0 <= v_type and v_type < sizeof(tpname)/sizeof(tpname[0]));
    return tpname[v_type];
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
	gx_print_warning(
	    title, Glib::ustring::compose("Different ID's: %2 / %3",
					  p1->_id, p2->_id));
    }
    if (p1->_name != p2->_name) {
	gx_print_warning(
	    title, Glib::ustring::compose("[%1]: Different name: %2 / %3",
					  p1->_id, p1->_name, p2->_name));
    }
    if (p1->_group != p2->_group) {
	gx_print_warning(
	    title, Glib::ustring::compose("[%1]: Different group: %2 / %3",
					  p1->_id, p1->_group, p2->_group));
    }
    if (p1->_desc != p2->_desc) {
	gx_print_warning(
	    title, Glib::ustring::compose("[%1]: Different desc: %2 / %3",
					  p1->_id, p1->_desc, p2->_desc));
    }
    if (p1->save_in_preset != p2->save_in_preset) {
	gx_print_warning(
	    title, Glib::ustring::compose("[%1]: save_in_preset different: %2 / %3",
					  p1->_id, p1->save_in_preset, p2->save_in_preset));
    }
    if (p1->controllable != p2->controllable) {
	gx_print_warning(
	    title, Glib::ustring::compose("[%1]: controllable different: %2 / %3",
					  p1->_id, p1->controllable, p2->controllable));
    }
    if (p1->used != p2->used) {
	gx_print_warning(
	    title, Glib::ustring::compose("[%1]: used different: %2 / %3",
					  p1->_id, p1->used, p2->used));
    }
    if (p1->c_type != p2->c_type) {
	gx_print_warning(
	    title, Glib::ustring::compose("[%1]: c_type different: %2 / %3",
					  p1->_id, p1->c_type, p2->c_type));
    }
    if (p1->v_type != p2->v_type) {
	gx_print_warning(
	    title, Glib::ustring::compose("[%1]: v_type different: %2 / %3",
					  p1->_id, p1->v_type, p2->v_type));
	return;
    }
    if (p1->isFloat()) {
	FloatParameter& f1 = p1->getFloat();
	FloatParameter& f2 = p2->getFloat();
	if (f1.value != f2.value) {
	    gx_print_warning(
		title, Glib::ustring::compose("[%1]: value address different: %2 / %3",
					      p1->_id, f1.value, f2.value));
	}
	if (f1.lower != f2.lower) {
	    gx_print_warning(

		title, Glib::ustring::compose("[%1]: float lower different: %2 / %3",
					      p1->_id, f1.lower, f2.lower));
	}
	if (f1.upper != f2.upper) {
	    gx_print_warning(
		title, Glib::ustring::compose("[%1]: float upper different: %2 / %3",
					      p1->_id, f1.upper, f2.upper));
	}
	if (f1.step != f2.step) {
	    gx_print_warning(
		title, Glib::ustring::compose("[%1]: float step different: %2 / %3",
					      p1->_id, f1.step, f2.step));
	}
	if (f1.std_value != f2.std_value) {
	    gx_print_warning(
		title, Glib::ustring::compose("[%1]: float std value different: %2 / %3",
					      p1->_id, f1.std_value, f2.std_value));
	}
	if (all) {
	    if (f1.value != f2.value) {
		gx_print_warning(
		    title, Glib::ustring::compose("[%1]: float value different: %2 / %3",
						  p1->_id, *f1.value, *f2.value));
	    }
	    if (f1.json_value != f2.json_value) {
		gx_print_warning(
		    title, Glib::ustring::compose("[%1]: float json value different: %2 / %3",
						  p1->_id, f1.json_value, f2.json_value));
	    }
	}
	return;
    }
    if (p1->isInt()) {
	assert(false);
	return;
    }
    if (p1->isBool()) {
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

void FloatParameter::serializeJSON(gx_system::JsonWriter& jw) {
    jw.begin_object();
    jw.write_key("Parameter"); Parameter::serializeJSON(jw);
    jw.write_kv("lower", lower);
    jw.write_kv("upper", upper);
    jw.write_kv("step", step);
    jw.write_kv("value", *value);
    jw.write_kv("std_value", std_value);
    jw.end_object();
}

FloatParameter::ParameterV(gx_system::JsonParser& jp)
    : Parameter(jp_next(jp, "Parameter")), json_value(0), value(&value_storage), std_value(0), lower(), upper(), step() {
    while (jp.peek() != gx_system::JsonParser::end_object) {
	jp.next(gx_system::JsonParser::value_key);
	if (jp.read_kv("lower", lower) ||
	    jp.read_kv("upper", upper) ||
	    jp.read_kv("step", step) ||
	    jp.read_kv("value", *value) ||
	    jp.read_kv("std_value", std_value)) {
	} else {
	    gx_print_warning(
		"FloatParameter", Glib::ustring::compose("%1: unknown key: %2", _id, jp.current_value()));
	    jp.skip_object();
	}
    }
    jp.next(gx_system::JsonParser::end_object);
}

FloatParameter::~ParameterV() {
}

bool FloatParameter::set(float val) const {
    float v = min(max(val, lower), upper);
    if (v != *value) {
	*value = v;
	changed(v);
	return true;
    }
    return false;
}

bool FloatParameter::on_off_value() {
    return *value != 0;
}

float FloatParameter::idx_from_id(string v_id) {
    assert(false);
    return 0;
}

bool FloatParameter::midi_set(float n, float high, float llimit, float ulimit) {
    float v;
    switch (c_type) {
    case Continuous:
        assert(n >= 0 && n <= high);
        v = llimit + (n / high) * (ulimit - llimit);
        break;
    case Switch:
        v = (2*n > high ? 1.0 : 0.0);
        break;
    case Enum:
        v = lower + min(n, upper-lower);
        break;
    default:
        assert(false);
        return false;
    }
    if (v != *value) {
	*value = v;
	return true;
    }
    return false;
}

bool FloatParameter::midi_set_bpm(float n, float high, float llimit, float ulimit) {
    float v;
    switch (c_type) {
    case Continuous:
        assert(n >= 0 && n <= high);
        if (high <= ulimit) {
            v = max(llimit,min(ulimit,n));
        } else {
            v = llimit + (n / high) * (ulimit - llimit);
        }
        break;
    case Switch:
        v = (2*n > high ? 1.0 : 0.0);
        break;
    case Enum:
        v = lower + min(n, upper-lower);
        break;
    default:
        assert(false);
        return false;
    }
    if (v != *value) {
	*value = v;
	return true;
    }
    return false;
}

void FloatParameter::trigger_changed() {
    changed(*value);
}

void FloatParameter::stdJSON_value() {
    json_value = std_value;
}

void FloatParameter::writeJSON(gx_system::JsonWriter& jw) const {
    jw.write_kv(_id.c_str(), *value);
}

bool FloatParameter::ramp_value(float val) {
    if (std::abs(json_value - val) < 10*FLT_EPSILON || std::abs(json_value )> std::abs(val)) {
        json_value = val;
        setJSON_value();
        return false;
    } else if (val<=std_value) {
        json_value = val;
        setJSON_value();
        return false;
    }
    float v = val * 0.1;
    json_value += v;
    setJSON_value();
    //fprintf(stderr, "set value %f of %f\n",json_value, val);
    return true;
}

void FloatParameter::rampJSON_value(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::value_number);
    json_value = std_value;
     Glib::signal_timeout().connect(sigc::bind<float>(
         sigc::mem_fun (*this, &FloatParameter::ramp_value),jp.current_value_float()), 10);
}

void FloatParameter::readJSON_value(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::value_number);
    json_value = jp.current_value_float();
    if (json_value < lower-std::abs(5*FLT_EPSILON*lower) || json_value > upper+std::abs(5*FLT_EPSILON*upper)) {
	range_warning(json_value, lower, upper);
	json_value = std_value;
    }
}

bool FloatParameter::compareJSON_value() {
    return std::abs(json_value - *value) < 5*FLT_EPSILON;
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

static void serializeValueNames(gx_system::JsonWriter& jw, const value_pair *p) {
    jw.write_key("value_names");
    jw.begin_array();
    while (p->value_id) {
	jw.write(p->value_id);
	if (p->value_label) {
	    jw.write(p->value_label);
	} else {
	    jw.write(p->value_id);
	}
	p++;
    }
    jw.end_array();
}

void FloatEnumParameter::serializeJSON(gx_system::JsonWriter& jw) {
    jw.begin_object();
    jw.write_key("FloatParameter"); FloatParameter::serializeJSON(jw);
    serializeValueNames(jw, value_names);
    jw.end_object();
}

FloatEnumParameter::FloatEnumParameter(const string& id, const string& name, const value_pair* vn, bool preset,
                                       float *v, int sv, int low, bool ctrl, bool no_init):
    FloatParameter(id, name, Enum, preset, v, sv, low, low+get_upper(vn), 1, ctrl, no_init),
    value_names(vn) {}

const value_pair *FloatEnumParameter::getValueNames() const {
    return value_names;
}

void FloatEnumParameter::writeJSON(gx_system::JsonWriter& jw) const {
    jw.write_key(_id.c_str());
    jw.write(value_names[static_cast<int>(round(*value-lower))].value_id);
}

float FloatEnumParameter::idx_from_id(string v_id) {
    int up = static_cast<int>(round(upper));
    int low = static_cast<int>(round(lower));
    int n = 0;
    for (; n <= up-low; n++) {
        if (v_id == value_names[n].value_id) {
            return low + n;
        }
    }
    return -1;
}

void FloatEnumParameter::readJSON_value(gx_system::JsonParser& jp) {
    gx_system::JsonParser::token tok = jp.next();
    if (tok == gx_system::JsonParser::value_number) {
        // old version compatability
        json_value = jp.current_value_int();
        return;
    }
    jp.check_expect(gx_system::JsonParser::value_string);
    float n = idx_from_id(jp.current_value());
    if (n < 0) {
        gx_print_warning(
            _("read parameter"), (boost::format(_("parameter %1%: unknown enum value: %2%"))
                               % _id % jp.current_value()).str());
        n = lower;
    }
    json_value = n;
}

/* IntParameter */

void IntParameter::serializeJSON(gx_system::JsonWriter& jw) {
    jw.begin_object();
    jw.write_key("Parameter"); Parameter::serializeJSON(jw);
    jw.write_kv("lower", lower);
    jw.write_kv("upper", upper);
    jw.write_kv("value", *value);
    jw.write_kv("std_value", std_value);
    jw.end_object();
}

IntParameter::ParameterV(gx_system::JsonParser& jp)
    : Parameter(jp_next(jp, "Parameter")), json_value(0), value(&value_storage), std_value(0), lower(), upper() {
    while (jp.peek() != gx_system::JsonParser::end_object) {
	jp.next(gx_system::JsonParser::value_key);
	if (jp.read_kv("lower", lower) ||
	    jp.read_kv("upper", upper) ||
	    jp.read_kv("value", *value) ||
	    jp.read_kv("std_value", std_value)) {
	} else {
	    gx_print_warning(
		"IntParameter", Glib::ustring::compose("%1: unknown key: %2", _id, jp.current_value()));
	    jp.skip_object();
	}
    }
    jp.next(gx_system::JsonParser::end_object);
}

IntParameter::~ParameterV() {
}

bool IntParameter::set(int val) const {
    int v = min(max(val, lower), upper);
    if (v != *value) {
	*value = v;
	changed(v);
	return true;
    }
    return false;
}

int IntParameter::idx_from_id(string v_id) {
    assert(false);
    return 0;
}

bool IntParameter::on_off_value() {
    return *value != 0;
}

bool IntParameter::midi_set(float n, float high, float llimit, float ulimit) {
    int v;
    switch (c_type) {
    case Continuous:
        assert(false); // not implemented
        return false;
    case Switch:
	assert(false); // not implemented
        return false;
    case Enum:
        v = lower + min(static_cast<int>(n), upper-lower);
        break;
    default:
        assert(false);
        return false;
    }
    if (v != *value) {
	*value = v;
	return true;
    }
    return false;
}

void IntParameter::trigger_changed() {
    changed(*value);
}

void IntParameter::stdJSON_value() {
    json_value = std_value;
}

void IntParameter::writeJSON(gx_system::JsonWriter& jw) const {
    jw.write_kv(_id.c_str(), *value);
}

void IntParameter::readJSON_value(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::value_number);
    json_value = jp.current_value_int();
    if (json_value < lower || json_value > upper) {
	range_warning(json_value, lower, upper);
    }
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

void EnumParameter::serializeJSON(gx_system::JsonWriter& jw) {
    jw.begin_object();
    jw.write_key("IntParameter"); IntParameter::serializeJSON(jw);
    serializeValueNames(jw, value_names);
    jw.end_object();
}

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

void EnumParameter::writeJSON(gx_system::JsonWriter& jw) const {
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
        gx_print_warning(
            _("read parameter"), (boost::format(_("parameter %1%: unknown enum value: %2%"))
                               % _id % jp.current_value()).str());
        n = 0;
    }
    json_value = n;
}

/* derived enum parameters */

typedef std::pair<std::string,std::string> id_label;

void enum_parameter_load_values(gx_system::JsonParser& jp, std::vector<id_label>& value_array, const value_pair **value_names) {
    while (jp.peek() != gx_system::JsonParser::end_object) {
	jp.next(gx_system::JsonParser::value_key);
	if (jp.current_value() == "value_names") {
	    jp.next(gx_system::JsonParser::begin_array);
	    while (jp.peek() != gx_system::JsonParser::end_array) {
		jp.next(gx_system::JsonParser::value_string);
		std::string value_id = jp.current_value();
		jp.next(gx_system::JsonParser::value_string);
		std::string value_label = jp.current_value();
		value_array.push_back(id_label(value_id, value_label));
	    }
	    jp.next(gx_system::JsonParser::end_array);
	} else {
	    gx_print_warning(
		"EnumValueNames", Glib::ustring::compose("unknown key: %1", jp.current_value()));
	    jp.skip_object();
	}
    }
    jp.next(gx_system::JsonParser::end_object);
    value_pair* p = new value_pair[value_array.size()+1];
    *value_names = p;
    for (std::vector<id_label>::iterator i = value_array.begin(); i != value_array.end(); ++i) {
	p->value_id = i->first.c_str();
	p->value_label = i->second.c_str();
	p++;
    }
    p->value_id = p->value_label = 0;
}

class FloatEnumParameterD: public FloatEnumParameter {
private:
    std::vector<id_label> value_array;
public:
    FloatEnumParameterD(gx_system::JsonParser& jp);
    ~FloatEnumParameterD();
};

FloatEnumParameterD::FloatEnumParameterD(gx_system::JsonParser& jp)
    : FloatEnumParameter(jp), value_array() {
    enum_parameter_load_values(jp, value_array, &value_names);
}

FloatEnumParameterD::~FloatEnumParameterD() {
    delete value_names;
}

class EnumParameterD: public EnumParameter {
private:
    std::vector<id_label> value_array;
public:
    EnumParameterD(gx_system::JsonParser& jp);
    ~EnumParameterD();
};

EnumParameterD::EnumParameterD(gx_system::JsonParser& jp)
    : EnumParameter(jp), value_array() {
    enum_parameter_load_values(jp, value_array, &value_names);
}

EnumParameterD::~EnumParameterD() {
    delete value_names;
}


/* BoolParameter */

void BoolParameter::serializeJSON(gx_system::JsonWriter& jw) {
    jw.begin_object();
    jw.write_key("Parameter"); Parameter::serializeJSON(jw);
    jw.write_kv("value", *value);
    jw.write_kv("std_value", std_value);
    jw.end_object();
}

BoolParameter::ParameterV(gx_system::JsonParser& jp)
    : Parameter(jp_next(jp, "Parameter")), json_value(0), value(&value_storage), std_value(0) {
    while (jp.peek() != gx_system::JsonParser::end_object) {
	jp.next(gx_system::JsonParser::value_key);
	if (jp.read_kv("value", *value) || jp.read_kv("std_value", std_value)) {
	} else {
	    gx_print_warning(
		"BoolParameter", Glib::ustring::compose("%1: unknown key: %2", _id, jp.current_value()));
	    jp.skip_object();
	}
    }
    jp.next(gx_system::JsonParser::end_object);
}

BoolParameter::~ParameterV() {
}

bool BoolParameter::set(bool val) const {
    if (val != *value) {
	*value = val;
	changed(val);
	return true;
    }
    return false;
}

bool BoolParameter::on_off_value() {
    return *value;
}

bool BoolParameter::midi_set(float n, float high, float llimit, float ulimit) {
    bool v;
    switch (c_type) {
    case Switch:
        v = (2*n > high);
	break;
    default:
        assert(false);
        return false;
    }
    if (v != *value) {
	*value = v;
	return true;
    }
    return false;
}

void BoolParameter::trigger_changed() {
    changed(*value);
}

void BoolParameter::stdJSON_value() {
    json_value = std_value;
}

void BoolParameter::writeJSON(gx_system::JsonWriter& jw) const {
    jw.write_kv(_id.c_str(), *value);
}

void BoolParameter::readJSON_value(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::value_number);
    if (jp.current_value_int() < 0 || jp.current_value_int() > 1) {
	range_warning(json_value, 0, 1);
    }
    json_value = jp.current_value_int();
}

bool BoolParameter::compareJSON_value() {
    return json_value == *value;
}

void BoolParameter::setJSON_value() {
    set(json_value);
}


/* FileParameter */

void FileParameter::serializeJSON(gx_system::JsonWriter& jw) {
    jw.begin_object();
    jw.write_key("Parameter"); Parameter::serializeJSON(jw);
    jw.write_kv("value", value->get_path());
    jw.write_kv("std_value", std_value->get_path());
    jw.end_object();
}

FileParameter::FileParameter(gx_system::JsonParser& jp)
    : Parameter(jp_next(jp, "Parameter")), value(0), std_value(0), json_value(0) {
    while (jp.peek() != gx_system::JsonParser::end_object) {
	jp.next(gx_system::JsonParser::value_key);
	if (jp.current_value() == "value") {
	    jp.next(gx_system::JsonParser::value_string);
	    value = Gio::File::create_for_path(jp.current_value());
	} else if (jp.current_value() == "std_value") {
	    jp.next(gx_system::JsonParser::value_string);
	    std_value = Gio::File::create_for_path(jp.current_value());
	} else {
	    gx_print_warning(
		"FileParameter", Glib::ustring::compose("%1: unknown key: %2", _id, jp.current_value()));
	    jp.skip_object();
	}
    }
    jp.next(gx_system::JsonParser::end_object);
}

void FileParameter::set_path(const string& path) {
    Glib::RefPtr<Gio::File> v = Gio::File::create_for_path(path);
    if (is_equal(v)) {
	return;
    }
    value = v;
    changed();
}

bool FileParameter::set(const Glib::RefPtr<Gio::File>& val) {
    if (is_equal(val)) {
	return false;
    }
    value = val;
    changed();
    return true;
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

bool FileParameter::on_off_value() {
    return bool(value);
}

void FileParameter::writeJSON(gx_system::JsonWriter& jw) const {
    jw.write_kv(_id.c_str(), get_path());
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

string FileParameter::get_path() const {
    return value->get_path();
}

string FileParameter::get_directory_path() const {
    return value->get_parent()->get_path();
}

string FileParameter::get_parse_name() const {
    return value->get_parse_name();
}

string FileParameter::get_display_name() const {
    return value->query_info(G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME)->get_display_name();
}

void FileParameter::copy(const string& destination) const {
    value->copy(Gio::File::create_for_path(destination));
}


/* StringParameter */

void StringParameter::serializeJSON(gx_system::JsonWriter& jw) {
    jw.begin_object();
    jw.write_key("Parameter"); Parameter::serializeJSON(jw);
    jw.write_kv("value", *value);
    jw.write_kv("std_value", std_value);
    jw.end_object();
}

StringParameter::ParameterV(gx_system::JsonParser& jp)
    : Parameter(jp_next(jp, "Parameter")), json_value(""), value(&value_storage), std_value("") {
    while (jp.peek() != gx_system::JsonParser::end_object) {
	jp.next(gx_system::JsonParser::value_key);
	if (jp.read_kv("value", *value) || jp.read_kv("std_value", std_value)) {
	} else {
	    gx_print_warning(
		"StringParameter", Glib::ustring::compose("%1: unknown key: %2", _id, jp.current_value()));
	    jp.skip_object();
	}
    }
    jp.next(gx_system::JsonParser::end_object);
}

StringParameter::~ParameterV() {
}

bool StringParameter::set(const Glib::ustring& val) const {
    if (val != *value) {
	*value = val;
	changed(*value);
	return true;
    }
    return false;
}

bool StringParameter::on_off_value() {
    return !value->empty();
}

void StringParameter::stdJSON_value() {
    json_value = std_value;
}

void StringParameter::writeJSON(gx_system::JsonWriter& jw) const {
    jw.write_kv(_id.c_str(), *value);
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
      replace_mode(false) {
}

ParamMap::~ParamMap() {
    for (iterator i = id_map.begin(); i != id_map.end(); ++i) {
	delete i->second;
    }
}

void ParamMap::writeJSON_one(gx_system::JsonWriter& jw, Parameter *p) {
    if (p->isFloat()) {
	if (p->getControlType() == Parameter::Enum) {
	    jw.write("FloatEnum");
	} else {
	    jw.write("Float");
	}
    } else if (p->isInt()) {
	if (p->getControlType() == Parameter::Enum) {
	    jw.write("Enum");
	} else {
	    jw.write("Int");
	}
    } else if (p->isBool()) {
	jw.write("Bool");
    } else if (p->isFile()) {
	jw.write("File");
    } else if (p->isString()) {
	jw.write("String");
    } else if (dynamic_cast<JConvParameter*>(p) != 0) {
	jw.write("JConv");
    } else if (dynamic_cast<SeqParameter*>(p) != 0) {
	jw.write("Seq");
    } else {
#ifndef NDEBUG
	cerr << "skipping " << p->id() << endl;
#endif
	return;
    }
    p->serializeJSON(jw);
}

void ParamMap::writeJSON(gx_system::JsonWriter& jw) {
    jw.begin_array();
    for (iterator i = id_map.begin(); i != id_map.end(); ++i) {
	writeJSON_one(jw, i->second);
    }
    jw.end_array();
}

Parameter *ParamMap::readJSON_one(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::value_string);
    if (jp.current_value() == "FloatEnum") {
	return insert(new FloatEnumParameterD(jp));
    } else if (jp.current_value() == "Float") {
	return insert(new FloatParameter(jp));
    } else if (jp.current_value() == "Enum") {
	return insert(new EnumParameterD(jp));
    } else if (jp.current_value() == "Int") {
	return insert(new IntParameter(jp));
    } else if (jp.current_value() == "Bool") {
	return insert(new BoolParameter(jp));
    } else if (jp.current_value() == "File") {
	return insert(new FileParameter(jp));
    } else if (jp.current_value() == "String") {
	return insert(new StringParameter(jp));
    } else if (jp.current_value() == "JConv") {
	return insert(new JConvParameter(jp));
    } else if (jp.current_value() == "Seq") {
	return insert(new SeqParameter(jp));
    } else {
	gx_print_warning(
	    "ParamMap", Glib::ustring::compose("unknown parameter type: %1", jp.current_value()));
	jp.skip_object();
	return 0;
    }
}

void ParamMap::readJSON(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::begin_array);
    while (jp.peek() != gx_system::JsonParser::end_array) {
	readJSON_one(jp);
    }
    jp.next(gx_system::JsonParser::end_array);
}

#ifndef NDEBUG
void ParamMap::unique_id(Parameter* param) {
    if (id_map.find(param->id()) != id_map.end()) {
        gx_print_error("Debug Check", "id registered twice: " + param->id());
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
	switch (c_type) {
	case None: jw->write("None"); break;
	case Continuous: jw->write("Cont"); break;
	case Switch: jw->write("Swth"); break;
	case Enum: jw->write("Enum"); break;
	default: assert(false);
	}
	if (save_in_preset) {
	    jw->write("preset");
	}
	if (controllable) {
	    jw->write("control");
	}
	jw->write(l_group());
	jw->write(l_name());
	/*
	switch (v_type) {
	case tp_float:  jw->write("f"); jw->write(getFloat().get_value());     break;
	case tp_int:    jw->write("i"); jw->write(getInt().get_value());       break;
	case tp_bool:   jw->write("b"); jw->write(getBool().get_value());      break;
	case tp_switch: jw->write("s"); jw->write(getSwitch().get());          break;
	case tp_file:   jw->write("F"); jw->write(getFile().get_parse_name()); break;
	case tp_string: jw->write("S"); jw->write(getString().get_value());    break;
	case tp_special: jw->write("G"); break;
	default: assert(false);
	}
	*/
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

Parameter *ParamMap::insert(Parameter* param) {
    if (replace_mode) {
	map<string, Parameter*>::iterator ii = id_map.find(param->id());
	if (ii != id_map.end()) {
	    Parameter *p = ii->second;
	    insert_remove(p,false);
	    id_map.erase(ii);
	    delete p;
	}
    }
    debug_check(unique_id, param);
    id_map.insert(pair<string, Parameter*>(param->id(), param));
    insert_remove(param,true);
    return param;
}

void ParamMap::unregister(Parameter *p) {
    if (!p) {
	return;
    }
    insert_remove(p, false);
    id_map.erase(p->id());
    delete p;
}

void ParamMap::unregister(const string& id) {
    if (!hasId(id)) {
	return;
    }
    unregister(&(*this)[id]);
}

void ParamMap::set_init_values() {
    for (iterator i = id_map.begin(); i != id_map.end(); ++i) {
        i->second->stdJSON_value();
	i->second->setJSON_value();
    }
}

static inline bool compare_groups(const std::string& id, const char **groups) {
    if (!groups) {
	return false;
    }
    for (const char **g = groups; *g; g += 2) {
	const char *p = *g;
	if ((*p) != '.') {
	    continue;
	}
	p++;
	int n = strlen(p);
	if (strncmp(id.c_str(), p, n) == 0 && id[n] == '.') {
	    return true;
	}
    }
    return false;
}

bool ParamMap::unit_has_std_values(const PluginDef *pdef) const {
    std::string group_id(pdef->id);
    group_id += ".";
    std::string on_off = group_id + "on_off";
    std::string pp = group_id + "pp";
    std::string position = group_id + "position";
    for (iterator i = begin(); i != end(); ++i) {
	if (i->first.compare(0, group_id.size(), group_id) == 0 || compare_groups(i->first, pdef->groups)) {
	    if (i->second->isInPreset()) {
		if (i->first != on_off && i->first != pp && i->first != position) {
		    i->second->stdJSON_value();
		    if (!i->second->compareJSON_value()) {
			return false;
			break;
		    }
		}
	    }
	}
    }
    return true;
}

// reset all parameters to default settings
void ParamMap::reset_unit(const PluginDef *pdef) const {
    std::string group_id(pdef->id);
    group_id += ".";
    std::string on_off = group_id + "on_off";
    std::string pp = group_id + "pp";
    std::string position = group_id + "position";
    for (iterator i = begin(); i != end(); ++i) {
        if (i->first.compare(0, group_id.size(), group_id) == 0 || compare_groups(i->first, pdef->groups)) {
	    if (i->second->isInPreset()) {
		if (i->first != on_off && i->first != pp && i->first != position) {
		    i->second->stdJSON_value();
		    i->second->setJSON_value();
		}
	    }
        }
    }
}

} // namespace gx_gui

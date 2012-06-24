/*
 * Copyright (C) 2012 Andreas Degert, Hermann Meyer
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
 */

#include <lrdf.h>
#include <ladspa.h>
#include <dlfcn.h>

#include "guitarix.h"

using Glib::ustring;
using gx_system::JsonParser;
using gx_system::JsonWriter;
using gx_system::JsonException;

namespace ladspa {

//#define HARD_RT_ONLY

static int SR = 44100;

static const unsigned long blacklist[] = {
    4069, 4070,		      // ladspa_guitarix
    1912,                     // jamincont (crashes on unload?)
    //1044, 1045, 1046, 1047, // sine
};

static bool lib_is_blacklisted(const std::string& name) {
    static const char *blacklist[] = {
        "dssi-vst.so",
    };
    for (unsigned int i = 0; i < sizeof(blacklist) / sizeof(blacklist[0]); i++) {
        if (name == blacklist[i]) {
            return true;
        }
    }
    return false;
}

static const unsigned long quirklist_no_cleanup[] = { 1912, 0 };
static const unsigned long quirklist_activate[] = { 1890, 1891, 1893, 1894, 1892, 1903, 1904, 0 };
static const struct {
    int flag;
    const unsigned long *ids;
} quirk_list[] = {
    {1, quirklist_no_cleanup},
    {2, quirklist_activate},
    {0, 0}
};

#define unknown_category "External"

static const char *cat_subst[][2] = {
    {"Reverbs", "Reverb"},
    {"Filters", "Tone control"},
    {"EQs", "Tone control"},
    {"Compressors", "Guitar Effects"},
    {"Utilities", "Misc"},
    {"Delays", "Echo / Delay"},
    {"Phasers", "Modulation"},
    {"Chorus", "Modulation"},
    {"Flangers", "Modulation"},
    {"Modulators", "Modulation"},
    {"Distortions", "Distortion"},
    {"Waveshapers", "Distortion"},
    {"Amplifiers", "Distortion"},
    {0, 0}
};

const char *step_type_names[] = { "coarse", "normal", "fine" };

/****************************************************************
 ** PluginDesc, PortDesc
 */

static inline bool float_eq(float v1, float v2) {
    return abs(v1 - v2) <= 1e-5 * abs(v1);
}

const char *display_type_names[] = { "Scale", "Log. Scale", "Toggle", "Enum", "Display", "Led", "Hide", "Int" };


bool operator!=(const ChangeableValues& v1, const ChangeableValues& v2) {
    if (v1.set_flags != v2.set_flags) {
	return true;
    }
    if (v1.is_set(ChangeableValues::name_set) && v1.name != v2.name) {
	return true;
    }
    if (v1.is_set(ChangeableValues::dflt_set) && !float_eq(v1.dflt, v2.dflt)) {
	return true;
    }
    if (v1.is_set(ChangeableValues::low_set) && !float_eq(v1.low, v2.low)) {
	return true;
    }
    if (v1.is_set(ChangeableValues::up_set) && !float_eq(v1.up, v2.up)) {
	return true;
    }
    if (v1.is_set(ChangeableValues::tp_set) && v1.tp != v2.tp) {
	return true;
    }
    if (v1.is_set(ChangeableValues::newrow_set) && v1.newrow != v2.newrow) {
	return true;
    }
    if (v1.enumdict.size() != v2.enumdict.size()) {
	return true;
    }
    for (std::map<int, ustring>::const_iterator i = v1.enumdict.begin(); i != v1.enumdict.end(); ++i) {
	std::map<int, ustring>::const_iterator j = v2.enumdict.find(i->first);
	if (j == v2.enumdict.end() || j->second != i->second) {
	    return true;
	}
    }
    return false;
}

int ChangeableValues::get_excl_flags(DisplayType t) const {
    switch (t) {
    case tp_toggle:         return low_set|up_set;
    case tp_display:        return dflt_set;
    case tp_display_toggle: return dflt_set|low_set|up_set;
    case tp_none:           return dflt_set|low_set|up_set;
    default:                return 0;
    }
}

bool ChangeableValues::has_settings(DisplayType t) const {
    if ((set_flags & ~get_excl_flags(t)) || enumdict.size()) {
	return true;
    }
    return false;
}

PortDesc::PortDesc(int idx_, int pos_, bool is_output_, ustring name, const LADSPA_PortRangeHint& hint)
    : idx(idx_), pos(pos_), is_output(is_output_), hint_desc(hint.HintDescriptor),
      fake_low(false), fake_up(false), fake_dflt(false),
      step(stp_normal), use_sr(false), has_sr(LADSPA_IS_HINT_SAMPLE_RATE(hint_desc)),
      has_caption(true), factory(), user() {
    factory.set_name(name);
    set_range_default(hint, factory);
    set_default_value(hint, factory);
    set_tp_default(hint, factory);
}

void PortDesc::set_default_value(const LADSPA_PortRangeHint& h, ChangeableValues& store) {
    if (!LADSPA_IS_HINT_HAS_DEFAULT(h.HintDescriptor)) {
	store.unset(ChangeableValues::dflt_set);
    } else if (LADSPA_IS_HINT_DEFAULT_0(h.HintDescriptor)) {
	store.set_dflt(0);
    } else if (LADSPA_IS_HINT_DEFAULT_1(h.HintDescriptor)) {
	store.set_dflt(1);
    } else if (LADSPA_IS_HINT_DEFAULT_100(h.HintDescriptor)) {
	store.set_dflt(100);
    } else if (LADSPA_IS_HINT_DEFAULT_440(h.HintDescriptor)) {
	store.set_dflt(440);
    } else if (LADSPA_IS_HINT_DEFAULT_MINIMUM(h.HintDescriptor)) {
	store.set_dflt(get_low());
    } else if (LADSPA_IS_HINT_DEFAULT_MAXIMUM(h.HintDescriptor)) {
	store.set_dflt(get_up());
    } else {
	float low = get_low();
	float up = get_up();
	if (!factory.is_set(ChangeableValues::low_set) || !factory.is_set(ChangeableValues::up_set)) {
	    store.unset(ChangeableValues::dflt_set);
	} else if (LADSPA_IS_HINT_LOGARITHMIC(hint_desc)) {
	    if (low > 0) {
		if (LADSPA_IS_HINT_DEFAULT_LOW(h.HintDescriptor)) {
		    store.set_dflt(exp(log(low)*0.75 + log(up)*0.25));
		} else if (LADSPA_IS_HINT_DEFAULT_MIDDLE(h.HintDescriptor)) {
		    store.set_dflt(exp(log(low)*0.5 + log(up)*0.5));
		} else if (LADSPA_IS_HINT_DEFAULT_HIGH(h.HintDescriptor)) {
		    store.set_dflt(exp(log(low)*0.25 + log(up)*0.75));
		}
	    } else {
		store.unset(ChangeableValues::dflt_set);
	    }
	} else {
	    if (LADSPA_IS_HINT_DEFAULT_LOW(h.HintDescriptor)) {
		store.set_dflt(low * 0.75 + up * 0.25);
	    } else if (LADSPA_IS_HINT_DEFAULT_MIDDLE(h.HintDescriptor)) {
		store.set_dflt(low * 0.5 + up * 0.5);
	    } else if (LADSPA_IS_HINT_DEFAULT_HIGH(h.HintDescriptor)) {
		store.set_dflt(low * 0.25 + up * 0.75);
	    }
	}
    }
}

void PortDesc::set_range_default(const LADSPA_PortRangeHint& h, ChangeableValues& store) {
    if (LADSPA_IS_HINT_TOGGLED(h.HintDescriptor)) {
	store.set_low(0);
	store.set_up(1);
    } else {
	if (LADSPA_IS_HINT_BOUNDED_BELOW(h.HintDescriptor)) {
	    store.set_low(h.LowerBound);
	} else {
	    store.unset(ChangeableValues::low_set);
	}
	if (LADSPA_IS_HINT_BOUNDED_ABOVE(h.HintDescriptor)) {
	    store.set_up(h.UpperBound);
	} else {
	    store.unset(ChangeableValues::up_set);
	}
    }
}

void PortDesc::reset() {
    step = stp_normal;
    use_sr = false;
    has_sr = LADSPA_IS_HINT_SAMPLE_RATE(hint_desc);
    has_caption = true;
    user = ChangeableValues();
}

void PortDesc::set_low(float v) {
    if (!fake_low && float_eq(v, factory.get_low())) {
	user.unset(ChangeableValues::low_set);
    } else {
	user.set_low(v);
    }
}

void PortDesc::set_up(float v) {
    if (!fake_up && float_eq(v, factory.get_up())) {
	user.unset(ChangeableValues::up_set);
    } else {
	user.set_up(v);
    }
}

void PortDesc::set_dflt(float v) {
    if (!fake_dflt && float_eq(v, factory.get_dflt())) {
	user.unset(ChangeableValues::dflt_set);
    } else {
	user.set_dflt(v);
    }
}

void PortDesc::set_tp(DisplayType v) {
    if (v == factory.get_tp()) {
	user.unset(ChangeableValues::tp_set);
    } else {
	user.set_tp(v);
    }
}

void PortDesc::set_newrow(bool v) {
    if (v == factory.get_newrow()) {
	user.unset(ChangeableValues::newrow_set);
    } else {
	user.set_newrow(v);
    }
}

ustring PortDesc::get_enum(int idx) {
    std::map<int, ustring>::iterator i;
    i = user.find_enum(idx);
    if (i != user.enum_end()) {
	return i->second;
    }
    i = factory.find_enum(idx);
    if (i != factory.enum_end()) {
	return i->second;
    }
    return "";
}

bool PortDesc::check_changed(const PortDesc& vp) const {
    if (pos != vp.pos) {
	return true;
    }
    if (fake_low != vp.fake_low) {
	return true;
    }
    if (fake_up != vp.fake_up) {
	return true;
    }
    if (fake_dflt != vp.fake_dflt) {
	return true;
    }
    if (step != vp.step) {
	return true;
    }
    if (use_sr != vp.use_sr) {
	return true;
    }
    if (has_sr != vp.has_sr) {
	return true;
    }
    if (has_caption != vp.has_caption) {
	return true;
    }
    if (factory != vp.factory) {
	return true;
    }
    if (user != vp.user) {
	return true;
    }
    return false;
}

bool PortDesc::has_settings() {
    return !has_caption || step != stp_normal || use_sr || user.has_settings(get_tp());
}

void PortDesc::fixup(bool newrow) {
    ChangeableValues& f = factory;
    f.set_newrow(newrow);
    if (LADSPA_IS_HINT_LOGARITHMIC(hint_desc)) {
	if (!f.is_set(ChangeableValues::low_set) && !f.is_set(ChangeableValues::up_set)) {
	    if (!f.is_set(ChangeableValues::dflt_set)) {
		f.set_up(1.0);
		f.set_low(1.0/1000.0);
		f.set_dflt(sqrt(f.get_low()*f.get_up()));
		fake_dflt = true;
	    } else if (f.get_dflt() <= 0) {
		f.set_dflt(1.0);
		fake_dflt = true;
		f.set_low(f.get_dflt()/100.0);
		f.set_up(f.get_dflt()*100.0);
	    } else {
		f.set_low(f.get_dflt()/100.0);
		f.set_up(f.get_dflt()*100.0);
	    }
	    fake_low = fake_up = true;
	} else if (!f.is_set(ChangeableValues::low_set)) {
	    if (!f.is_set(ChangeableValues::dflt_set)) {
		f.set_low(f.get_up()/1000.0);
		f.set_dflt(f.get_low());
		fake_dflt = true;
	    } else {
		if (f.get_dflt() >= f.get_up()) {
		    f.set_dflt(f.get_up());
		    f.set_low(f.get_up() / 1000.0);
		} else {
		    f.set_low(f.get_dflt());
		}
	    }
	    fake_low = true;
	} else if (!f.is_set(ChangeableValues::up_set)) {
	    if (f.get_low() == 0) {
		f.set_low(1e-1);
		fake_low = true;
	    }
	    if (!f.is_set(ChangeableValues::dflt_set)) {
		f.set_up(f.get_low() * 1000.0);
		f.set_dflt(f.get_low());
		fake_dflt = true;
	    } else {
		if (f.get_dflt() <= f.get_low()) {
		    f.set_dflt(f.get_low());
		    f.set_up(f.get_low() * 1000.0);
		} else {
		    f.set_up(f.get_dflt());
		}
	    }
	    fake_up = true;
	} else if (f.get_low() <= 0) {
	    f.set_low(1e-7);
	    fake_low = true;
	}
    } else {
	if (!f.is_set(ChangeableValues::low_set) && !f.is_set(ChangeableValues::up_set)) {
	    if (!f.is_set(ChangeableValues::dflt_set)) {
		f.set_low(-1000);
		f.set_up(1000);
		f.set_dflt(0);
		fake_dflt = true;
	    } else {
		f.set_low(f.get_dflt() - 100);
		f.set_up(f.get_dflt() + 100);
	    }
	    fake_low = fake_up = true;
	} else if (!f.is_set(ChangeableValues::low_set)) {
	    if (!f.is_set(ChangeableValues::dflt_set)) {
		f.set_low(f.get_up() - 1000);
		f.set_dflt(f.get_low());
		fake_dflt = true;
	    } else {
		if (f.get_dflt() >= f.get_up()) {
		    f.set_dflt(f.get_up());
		    f.set_low(f.get_up() - 1000);
		} else {
		    f.set_low(f.get_dflt());
		}
	    }
	    fake_low = true;
	} else if (!f.is_set(ChangeableValues::up_set)) {
	    if (!f.is_set(ChangeableValues::dflt_set)) {
		f.set_up(f.get_low() + 1000);
		f.set_dflt(f.get_low());
		fake_dflt = true;
	    } else {
		if (f.get_dflt() <= f.get_low()) {
		    f.set_dflt(f.get_low());
		    f.set_up(f.get_low() + 1000);
		} else {
		    f.set_up(f.get_dflt());
		}
	    }
	    fake_up = true;
	}
    }
    if (!f.is_set(ChangeableValues::dflt_set)) {
	fake_dflt = true;
	f.set_dflt(f.get_low());
    }
    if (f.get_tp() == tp_enum) {
	for (int k = int(f.get_low()); k < int(f.get_up()+1); k++) {
	    if (!f.has_enumkey(k)) {
		f.set_enumvalue(k, gx_system::to_string(k));
	    }
	}
    }
}

float PortDesc::calc_step() {
    if (get_tp() == tp_toggle || get_tp() == tp_enum || get_tp() == tp_int) {
	return 1.0;
    }
    float up = get_up();
    float low = get_low();
    if (get_tp() == tp_scale_log) {
	if (step == stp_coarse) {
	    return pow(up/low, 1.0/50);
	}
	if (step == stp_normal) {
	    return pow(up/low, 1.0/100);
	}
	if (step == stp_fine) {
	    return pow(up/low, 1.0/500);
	}
	assert(false);
	return 1.0;
    } else {
	float s = 1.0;
	if (step == stp_coarse) {
	    s = (up - low) / 30.0;
	}
	if (step == stp_normal) {
	    s = (up - low) / 300.0;
	}
	if (step == stp_fine) {
	    s = (up - low) / 3000.0;
	}
	if (has_sr && !use_sr) {
	    s *= SR;
	}
	return pow(10.0, round(log10(s)));
    }
}

void PortDesc::set_tp_default(const LADSPA_PortRangeHint& h, ChangeableValues& store) {
    if (is_output) {
	if (LADSPA_IS_HINT_TOGGLED(h.HintDescriptor)) {
	    store.set_tp(tp_display_toggle);
	} else if (get_name() == "latency") {
	    store.set_tp(tp_none);
	} else {
	    store.set_tp(tp_display);
	}
    } else if (LADSPA_IS_HINT_TOGGLED(h.HintDescriptor)) {
	store.set_tp(tp_toggle);
    } else if (LADSPA_IS_HINT_LOGARITHMIC(hint_desc)) {
	store.set_tp(tp_scale_log);
    } else if (LADSPA_IS_HINT_INTEGER(h.HintDescriptor)) {
	store.set_tp(tp_int);
    } else {
	store.set_tp(tp_scale);
    }
}

void PortDesc::set_default(float value, ustring label) {
    if (!factory.is_set(ChangeableValues::dflt_set)) {
	factory.set_dflt(value);
    }
}

void PortDesc::output(JsonWriter& jw) {
    float dflt = get_dflt();
    float low = get_low();
    float up = get_up();
    if (has_sr && !use_sr) {
	if (factory.is_set(ChangeableValues::dflt_set)) {
	    dflt *= SR;
	}
	if (factory.is_set(ChangeableValues::low_set)) {
	    low *= SR;
	}
	if (factory.is_set(ChangeableValues::up_set)) {
	    up *= SR;
	}
    }
    jw.begin_array();
    jw.write(idx);
    jw.begin_array(); jw.write(step); jw.end_array();
    if (user.is_set(ChangeableValues::name_set)) {
	jw.write(user.get_name());
    } else {
	jw.write("");
    }
    jw.write(use_sr);
    jw.write(dflt);
    jw.write(low);
    jw.write(up);
    jw.write(calc_step());
    jw.write(get_tp());
    jw.write(get_newrow());
    jw.write(has_caption);
    jw.begin_array();
    if (get_tp() == tp_enum) {
	int iup = int(round(up));
	for (int i = int(round(low)); i < iup+1; ++i) {
	    jw.write(get_enum(i));
	}
    }
    jw.end_array();
    jw.end_array(true);
}

void PortDesc::set_state(JsonParser& jp, int version) {
    jp.next(JsonParser::begin_array);
    jp.next(JsonParser::value_number);
    step = static_cast<step_mode>(jp.current_value_int());
    jp.next(JsonParser::end_array);
    jp.next(JsonParser::value_string);
    if (!jp.current_value().empty()) {
	user.set_name(jp.current_value());
    }
    jp.next(JsonParser::value_number);
    use_sr = jp.current_value_int();
    jp.next(JsonParser::value_number);
    float dflt = jp.current_value_float();
    jp.next(JsonParser::value_number);
    float low = jp.current_value_float();
    jp.next(JsonParser::value_number);
    float up = jp.current_value_float();
    jp.next(JsonParser::value_number);
    jp.current_value_float(); // step value, ignored
    jp.next(JsonParser::value_number);
    DisplayType tp = DisplayType(jp.current_value_int());
    if (tp != factory.get_tp()) {
	user.set_tp(tp);
    }
    if (has_sr && !use_sr) {
	dflt /= SR;
	low /= SR;
	up /= SR;
    }
    if (!float_eq(dflt, factory.get_dflt())) {
	user.set_dflt(dflt);
    }
    if (!float_eq(low, factory.get_low())) {
	user.set_low(low);
    }
    if (!float_eq(up, factory.get_up())) {
	user.set_up(up);
    }
    jp.next(JsonParser::value_number);
    bool b = bool(jp.current_value_int());
    if (b != factory.get_newrow()) {
	user.set_newrow(b);
    }
    jp.next(JsonParser::value_number);
    b = bool(jp.current_value_int());
    has_caption = b;
    jp.next(JsonParser::begin_array);
    int s = int(low);
    while (jp.peek() != JsonParser::end_array) {
	jp.next(JsonParser::value_string);
	std::map<int, ustring>::iterator it = factory.find_enum(s);
	if (it != factory.enum_end() && jp.current_value() != it->second) {
	    user.set_enumvalue(s, jp.current_value());
	}
	s += 1;
    }
    jp.next(JsonParser::end_array);
}

PluginDesc::PluginDesc(const LADSPA_Descriptor& desc, int tp_, std::vector<PortDesc*>& ctrl_ports_, const std::string path_, int index_)
    : UniqueID(desc.UniqueID), Label(desc.Label), Name(desc.Name), shortname(desc.Name), Maker(desc.Maker),
      MasterIdx(-1), MasterLabel(), tp(tp_), ctrl_ports(ctrl_ports_), path(path_), index(index_),
      category(unknown_category), deduced_category(unknown_category), quirks(), quirks_default(),
      ladspa_category(), active(false), active_set(false), has_settings(false), old(0) {
    quirks = quirks_default = quirks_get();
}

PluginDesc::~PluginDesc() {
    delete old;
    for (std::vector<PortDesc*>::iterator i = ctrl_ports.begin(); i != ctrl_ports.end(); ++i) {
	delete *i;
    }
}

int PluginDesc::quirks_get() {
    int flag = 0;
    for (int i = 0; quirk_list[i].flag; i++) {
	for (int j = 0; quirk_list[i].ids[j]; j++) {
	    if (UniqueID == quirk_list[i].ids[j]) {
		flag |= quirk_list[i].flag;
	    }
	}
    }
    return flag;
}

bool cmp_ctrl_ports(const PortDesc *a, const PortDesc *b) {
    return a->pos < b->pos;
}

void PluginDesc::reset() {
    shortname = Name;
    MasterIdx = -1;
    MasterLabel = "";
    add_wet_dry = 0;
    category = deduced_category;
    quirks = quirks_default;
    has_settings = false;
    std::sort(ctrl_ports.begin(), ctrl_ports.end(), cmp_ctrl_ports);
    for (std::vector<PortDesc*>::iterator p = ctrl_ports.begin(); p != ctrl_ports.end(); ++p) {
	(*p)->reset();
    }
}

void PluginDesc::copy_ports(PluginDesc *p) {
    assert(ctrl_ports.size() == 0);
    for (std::vector<PortDesc*>::iterator i = p->ctrl_ports.begin(); i != p->ctrl_ports.end(); ++i) {
	ctrl_ports.push_back(new PortDesc(**i));
    }
}

static void ladspa_add_plugin(const LADSPA_Descriptor& desc, std::map<unsigned long, PluginDesc*>& d, const std::string& path, int index) {
    for (unsigned int j = 0; j < sizeof(blacklist)/sizeof(blacklist[0]); j++) {
	if (desc.UniqueID == blacklist[j]) {
	    return;
	}
    }
#ifdef HARD_RT_ONLY
    if (!LADSPA_IS_HARD_RT_CAPABLE(desc.Properties)) {
        return;
    }
#endif
    int n_in = 0;
    int n_out = 0;
    std::vector<PortDesc*> ctrl_ports;
    int pos = 0;
    for (unsigned int n = 0; n < desc.PortCount; n++) {
	LADSPA_PortDescriptor pd = desc.PortDescriptors[n];
	if (LADSPA_IS_PORT_AUDIO(pd)) {
	    if (LADSPA_IS_PORT_INPUT(pd)) {
		n_in += 1;
	    } else {
		n_out += 1;
	    }
	} else {
	    ctrl_ports.push_back(new PortDesc(n, pos, LADSPA_IS_PORT_OUTPUT(pd), desc.PortNames[n], desc.PortRangeHints[n]));
	    pos += 1;
	}
    }
    int tp;
    if (n_in == 1 && n_out == 1) {
	tp = 0;
    } else if (n_in == 2 && n_out == 2) {
	tp = 1;
    } else {
	return;
    }
    d[desc.UniqueID] = new PluginDesc(desc, tp, ctrl_ports, path, index);
}

static void load_ladspa_defs(const std::string& path, std::map<unsigned long, PluginDesc*>& d) {
    void *handle;
    handle = dlopen(path.c_str(), RTLD_LOCAL|RTLD_NOW);
    if (!handle) {
	gx_system::gx_print_warning(
	    "ladspalist",
	    ustring::compose(_("Cannot open plugin: %1\n"), dlerror()));
        return;
    }
    LADSPA_Descriptor_Function ladspa_descriptor = (LADSPA_Descriptor_Function)dlsym(handle, "ladspa_descriptor");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
	gx_system::gx_print_warning("ladspalist", dlsym_error);
        dlclose(handle);
        handle = 0;
        return;
    }
    int i = 0;
    while (true) {
	const LADSPA_Descriptor *desc = ladspa_descriptor(i);
	if (!desc) {
	    break;
	}
	ladspa_add_plugin(*desc, d, path, i);
	i += 1;
    }
    dlclose(handle);
}

bool PluginDesc::check_changed() {
    if (!old) {
	return false;
    }
    if (UniqueID != old->UniqueID) {
	return true;
    }
    if (Label != old->Label) {
	return true;
    }
    if (Name != old->Name) {
	return true;
    }
    if (shortname != old->shortname) {
	return true;
    }
    if (Maker != old->Maker) {
	return true;
    }
    if (MasterIdx != old->MasterIdx) {
	return true;
    }
    if (MasterIdx > -1 && MasterLabel != old->MasterLabel) {
	return true;
    }
    if (add_wet_dry != old->add_wet_dry) {
    return true;
    }
    if (tp != old->tp) {
	return true;
    }
    if (path != old->path) {
	return true;
    }
    if (index != old->index) {
	return true;
    }
    if (category != old->category) {
	return true;
    }
    if (deduced_category != old->deduced_category) {
	return true;
    }
    if (quirks != old->quirks) {
	return true;
    }
    if (quirks_default != old->quirks_default) {
	return true;
    }
    if (ladspa_category != old->ladspa_category) {
	return true;
    }
    for (unsigned int i = 0; i < ctrl_ports.size(); ++i) {
	if (ctrl_ports[i]->check_changed(*old->ctrl_ports[i])) {
	    return true;
	}
    }
    return false;
}

bool PluginDesc::_i_check_has_settings() {
    if (shortname != Name) {
	return true;
    }
    if (category != deduced_category) {
	return true;
    }
    if (quirks != quirks_default) {
	return true;
    }
    if (MasterIdx != -1) {
	return true;
    }
    for (int i = 0; i < static_cast<int>(ctrl_ports.size()); ++i) {
	if (i != ctrl_ports[i]->get_pos()) {
	    return true;
	}
	if (ctrl_ports[i]->has_settings()) {
	    return true;
	}
    }
    return false;
}

void PluginDesc::check_has_settings() {
    has_settings = _i_check_has_settings();
}

int PluginDesc::set_active(bool v) {
    if (v == active) {
	return 0;
    }
    active = v;
    if (v == active_set) {
	return -1;
    }
    return 1;
}

void PluginDesc::set_add_wet_dry_controller(bool v) {
    if (v) {
    add_wet_dry = 1;
    } else {
    add_wet_dry = 0;
    }
}

void PluginDesc::fixup() {
    int i = 0;
    for (unsigned int n = 0; n < ctrl_ports.size(); ++n) {
	bool newrow = false;
	if (ctrl_ports[n]->get_tp() != tp_none) {
	    newrow = (i % 4 == 0 && i != 0);
	    i += 1;
	}
	ctrl_ports[n]->fixup(newrow);
    }
}

void PluginDesc::set_category(const std::vector<ustring>& s) {
    bool found = false;
    ustring t = "";
    for (std::vector<ustring>::const_iterator i = s.begin(); i != s.end(); ++i) {
	if (!t.empty()) {
	    t += "/";
	}
	t += *i;
	if (!found) {
	    for (const char *(*p)[2] = cat_subst; (*p)[0]; ++p) {
		if (*i == (*p)[0]) {
		    category = deduced_category = (*p)[1];
		    found = true;
		    break;
		}
	    }
	}
    }
    ladspa_category = t;
}

void PluginDesc::set_default(int idx, float value, const ustring& label) {
    for (std::vector<PortDesc*>::iterator p = ctrl_ports.begin(); p != ctrl_ports.end(); ++p) {
	if ((*p)->idx == idx) {
	    (*p)->set_default(value, label);
	    return;
	}
    }
}

void PluginDesc::output(JsonWriter& jw) {
    ustring s = shortname;
    if (s == Name) {
	s = "";
    }
    int idx = -1;
    ustring sm = "";
    if (MasterIdx >= 0) {
	for (std::vector<PortDesc*>::iterator p = ctrl_ports.begin(); p != ctrl_ports.end(); ++p) {
	    ++idx;
	    if ((*p)->pos == MasterIdx) {
		sm = MasterLabel;
		if (sm == (*p)->get_name()) {
		    sm = "";
		}
		break;
	    }
	}
    }
    jw.begin_array();
    jw.write(3); // version
    jw.write(s);
    jw.write(category);
    jw.write(idx);
    jw.write(sm);
    jw.write(quirks);
    jw.write(add_wet_dry);
    jw.begin_array(true);
    for (std::vector<PortDesc*>::iterator p = ctrl_ports.begin(); p != ctrl_ports.end(); ++p) {
	(*p)->output(jw);
    }
    jw.end_array(true);
    jw.end_array(true);
}

void PluginDesc::output_entry(JsonWriter& jw) {
    jw.begin_array();
    jw.write(path);
    jw.write(index);
    jw.write(uint(UniqueID));
    jw.write(Label);
    jw.end_array(true);
}

void PluginDesc::set_state(const ustring& fname) {
    ifstream is(fname.c_str());
    if (is.fail()) {
	gx_system::gx_print_error("ladspalist", ustring::compose(_("can't open %1"), fname));
	return;
    }
    try {
	JsonParser jp(&is);
	jp.next(JsonParser::begin_array);
	jp.next(JsonParser::value_number);
	int version = jp.current_value_int();
	jp.next(JsonParser::value_string);
	shortname = jp.current_value();
	if (shortname.empty()) {
	    shortname = Name;
	}
	jp.next(JsonParser::value_string);
	category = jp.current_value();
	jp.next(JsonParser::value_number);
	MasterIdx = jp.current_value_int();
	jp.next(JsonParser::value_string);
	MasterLabel = jp.current_value();
	jp.next(JsonParser::value_number);
	quirks = jp.current_value_int();
    jp.next(JsonParser::value_number);
	add_wet_dry = jp.current_value_int();
	std::vector<PortDesc*> ports;
	jp.next(JsonParser::begin_array);
	int n = 0;
	int m_idx = MasterIdx;
	while (jp.peek() != JsonParser::end_array) {
	    jp.next(JsonParser::begin_array);
	    jp.next(JsonParser::value_number);
	    int idx = jp.current_value_int();
	    for (std::vector<PortDesc*>::iterator p = ctrl_ports.begin(); p != ctrl_ports.end(); ++p) {
		if ((*p)->idx == idx) {
		    if (m_idx == n) {
			MasterIdx = (*p)->pos;
		    }
		    (*p)->set_state(jp, version);
		    ports.push_back((*p));
		    break;
		}
	    }
	    n++;
	    jp.next(JsonParser::end_array);
	}
	jp.next(JsonParser::end_array);
	assert(ctrl_ports.size() == ports.size());
	ctrl_ports = ports;
	jp.next(JsonParser::end_array);
	jp.next(JsonParser::end_token);
	jp.close();
    } catch(JsonException& e) {
	gx_system::gx_print_error(
	    "ladspalist",
	    ustring::compose(_("error parsing LADSPA plugin config file %1: %2"), fname, e.what()));
	return;
    }
    is.close();
    check_has_settings();
}


/****************************************************************
 ** class PluginDisplay
 */

static const char *menudef = "\
<ui>\n\
  <menubar name=\"ladspalist\">\n\
    <menu action=\"FileMenuAction\">\n\
      <menuitem action=\"SelectAllAction\" />\n\
      <menuitem action=\"SelectNoneAction\" />\n\
      <menuitem action=\"SaveAction\" />\n\
      <menuitem action=\"ApplyAction\" />\n\
      <menuitem action=\"QuitAction\" />\n\
    </menu>\n\
    <menu action=\"ViewMenuAction\">\n\
      <menuitem action= \"FindAction\" />\n\
    </menu>\n\
  </menubar>\n\
</ui>\n\
";

static void append_displaytype(Glib::RefPtr<Gtk::ListStore> ls, DisplayType tp) {
    Gtk::TreeIter it = ls->append();
    it->set_value(0, ustring(display_type_names[tp]));
    it->set_value(1, tp);
}

class CellRendererComboDerived : public Gtk::CellRendererCombo {
public:
    CellRendererComboDerived() : Glib::ObjectBase (0), Gtk::CellRendererCombo() { }
    CellRendererComboDerived(BaseObjectType* castitem) : Glib::ObjectBase (0), Gtk::CellRendererCombo((GtkCellRendererCombo*)(castitem)) { }
    virtual ~CellRendererComboDerived() { }
    static CellRendererComboDerived* create_from_builder(BaseObjectType* cobject) {
	return new CellRendererComboDerived(cobject);
    }
};

PluginDisplay::PluginDisplay(const gx_system::CmdlineOptions& options_, Glib::RefPtr<Gdk::Pixbuf> icon, sigc::slot<void, bool, bool> finished_callback_)
    : options(options_), pluginlist(), current_plugin(0), old_state(0), bld(), change_count(0),
      actiongroup(Gtk::ActionGroup::create("ladspa_window")), uimanager(),
      enum_liststore(new EnumListStore), port_liststore(new PortListStore),
      plugin_liststore(new PluginListStore), masteridx_liststore(new MasterIdxListStore),
      on_reordered_conn(), display_type_list(), display_type_list_sr(), output_type_list(),
      finished_callback(finished_callback_)
{
    std::vector<unsigned long> old_not_found;
    load_ladspalist(old_not_found, pluginlist);
    bld = gx_gui::GxBuilder::create_from_file(options.get_builder_filepath("ladspaliste.glade"));
    bld->get_toplevel("window1", window);
    bld->find_widget("treeview1", treeview1);
    bld->find_widget("treeview2", treeview2);
    bld->find_widget("treeview3", treeview3);
    bld->find_widget("ladspa_category", ladspa_category);
    bld->find_widget("ladspa_maker", ladspa_maker);
    bld->find_widget("ladspa_uniqueid", ladspa_uniqueid);
    bld->find_widget("search_entry", search_entry);
    bld->find_widget("combobox_mono_stereo", combobox_mono_stereo);
    bld->find_widget("selected_only", selected_only);
    bld->find_widget("changed_only", changed_only);
    bld->find_widget("show_all", show_all);
    bld->find_widget("details_box", details_box);
    bld->find_widget("plugin_name", plugin_name);
    bld->find_widget("plugin_category", plugin_category);
    bld->find_widget("plugin_quirks", plugin_quirks);
    bld->find_widget("master_slider_idx", master_slider_idx);
    bld->find_widget("master_slider_name", master_slider_name);
    bld->find_widget("cellrenderer_master", cellrenderer_master);
    bld->find_widget("cellrenderer_newrow", cellrenderer_newrow);
    bld->find_widget("cellrenderer_caption", cellrenderer_caption);
    bld->find_widget("cellrenderer_active", cellrenderer_active);
    bld->find_widget("cellrenderer_category", cellrenderer_category);
    bld->find_widget("cellrenderer_quirks", cellrenderer_quirks);

    set_title();
    actiongroup->add(Gtk::Action::create("FileMenuAction",_("_File")));
    save_action = Gtk::Action::create("SaveAction", _("_Ok"));
    actiongroup->add(save_action, sigc::mem_fun(this, &PluginDisplay::on_save));
    apply_action = Gtk::Action::create("ApplyAction", _("_Apply"));
    actiongroup->add(apply_action, sigc::mem_fun(this, &PluginDisplay::on_apply));
    quit_action = Gtk::Action::create("QuitAction", _("_Quit"));
    actiongroup->add(quit_action, sigc::mem_fun(this, &PluginDisplay::on_quit));
    select_all_action = Gtk::Action::create("SelectAllAction", _("_Select All"));
    actiongroup->add(select_all_action, sigc::bind(sigc::mem_fun(this, &PluginDisplay::on_select_all), true));
    select_none_action = Gtk::Action::create("SelectNoneAction", _("Select _None"));
    actiongroup->add(select_none_action, sigc::bind(sigc::mem_fun(this, &PluginDisplay::on_select_all), false));
    actiongroup->add(Gtk::Action::create("ViewMenuAction", _("_View")));
    Glib::RefPtr<Gtk::Action> act = Gtk::Action::create("FindAction", _("_Find"));
    actiongroup->add(act, sigc::mem_fun(this, &PluginDisplay::on_find));

    uimanager = Gtk::UIManager::create();
    uimanager->insert_action_group(actiongroup, 0);
    uimanager->add_ui_from_string(menudef);
    //uimanager->get_widget("/ladspalist");
    //Gtk::HBox *ww; bld->find_widget("menubox", ww); ww->pack_start(*uimanager->get_widget("/ladspalist"));
    window->add_accel_group(uimanager->get_accel_group());

    window->signal_delete_event().connect(sigc::mem_fun(this, &PluginDisplay::on_delete_event));
    bld->find_widget("show_details", show_details);
    show_details->signal_clicked().connect(sigc::mem_fun(this, &PluginDisplay::on_show_details));
    treeview3->get_selection()->set_mode(Gtk::SELECTION_BROWSE);
    treeview3->set_model(enum_liststore);
    Gtk::CellRendererText *r;
    bld->find_widget("cellrenderer_label", r);
    r->signal_edited().connect(sigc::mem_fun(this, &PluginDisplay::on_label_edited));
    Gtk::TreeViewColumn *c;
    bld->find_widget("treeviewcolumn_label", c);
    c->set_cell_data_func(*r, sigc::mem_fun(this, &PluginDisplay::display_label));
    
    bld->find_widget("dry_wet_button", dry_wet_button);
    dry_wet_button->signal_clicked().connect(sigc::mem_fun(this, &PluginDisplay::on_add_dry_wet_controller));
   // dry_wet_button->set_active(current_plugin->add_wet_dry);

    Glib::RefPtr<Gtk::TreeSelection> sel = treeview2->get_selection();
    sel->set_mode(Gtk::SELECTION_BROWSE);
    sel->signal_changed().connect(sigc::mem_fun(this, &PluginDisplay::on_parameter_selection_changed));
    on_reordered_conn = port_liststore->signal_row_deleted().connect(sigc::mem_fun(this, &PluginDisplay::on_reordered));
    treeview2->set_model(port_liststore);

    CellRendererComboDerived *rd;
    bld->find_widget_derived("cellrenderer_type", rd, sigc::ptr_fun(CellRendererComboDerived::create_from_builder));
    rd->signal_edited().connect(sigc::mem_fun(this, &PluginDisplay::on_type_edited));
    bld->find_widget("treeviewcolumn_type", c);
    c->set_cell_data_func(*rd, sigc::mem_fun(this, &PluginDisplay::display_type));

    bld->find_widget_derived("cellrenderer_step", rd, sigc::ptr_fun(CellRendererComboDerived::create_from_builder));
    rd->signal_edited().connect(sigc::mem_fun(this, &PluginDisplay::on_step_edited));
    bld->find_widget("treeviewcolumn_step", c);
    c->set_cell_data_func(*rd, sigc::mem_fun(this, &PluginDisplay::display_step));

    cellrenderer_newrow->signal_toggled().connect(sigc::mem_fun(this, &PluginDisplay::on_newrow_toggled));
    Gtk::Label *label = new Gtk::Label("N");
    label->set_tooltip_text(_("start a new row of controls in the rackbox unit"));
    label->show();
    bld->find_widget("treeviewcolumn_newrow", c);
    c->set_widget(*manage(label));
    c->set_cell_data_func(*cellrenderer_newrow, sigc::mem_fun(this, &PluginDisplay::display_newrow));
    cellrenderer_caption->signal_toggled().connect(sigc::mem_fun(this, &PluginDisplay::on_caption_toggled));
    label = new Gtk::Label("C");
    label->set_tooltip_text(_("display the name as caption above the control"));
    label->show();
    bld->find_widget("treeviewcolumn_caption", c);
    c->set_widget(*manage(label));
    c->set_cell_data_func(*cellrenderer_caption, sigc::mem_fun(this, &PluginDisplay::display_caption));

    bld->find_widget("cellrenderer_name", r);
    r->signal_edited().connect(sigc::mem_fun(this, &PluginDisplay::on_name_edited));
    bld->find_widget("treeviewcolumn_name", c);
    c->set_cell_data_func(*r, sigc::mem_fun(this, &PluginDisplay::display_name));
    bld->find_widget("cellrenderer_dflt", r);
    r->signal_edited().connect(sigc::mem_fun(this, &PluginDisplay::on_dflt_edited));
    bld->find_widget("treeviewcolumn_dflt", c);
    c->set_cell_data_func(*r, sigc::mem_fun(this, &PluginDisplay::display_default));
    bld->find_widget("cellrenderer_low", r);
    r->signal_edited().connect(sigc::mem_fun(this, &PluginDisplay::on_low_edited));
    bld->find_widget("treeviewcolumn_low", c);
    c->set_cell_data_func(*r, sigc::mem_fun(this, &PluginDisplay::display_lower));
    bld->find_widget("cellrenderer_up", r);
    r->signal_edited().connect(sigc::mem_fun(this, &PluginDisplay::on_up_edited));
    bld->find_widget("treeviewcolumn_up", c);
    c->set_cell_data_func(*r, sigc::mem_fun(this, &PluginDisplay::display_upper));
    bld->find_widget("cellrenderer_idx", r);
    bld->find_widget("treeviewcolumn_idx", c);
    c->set_cell_data_func(*r, sigc::mem_fun(this, &PluginDisplay::display_idx));

    bld->find_widget("treeviewcolumn_SR", c);
    label = new Gtk::Label("SR");
    label->set_tooltip_text(_("marked rows: range depends on samplerate; using 44100 as fixed value"));
    label->show();
    c->set_widget(*manage(label));
    Gtk::CellRendererToggle *t;
    bld->find_widget("cellrenderer_SR", t);
    c->set_cell_data_func(*t, sigc::mem_fun(this, &PluginDisplay::display_SR));

    Gtk::TreeModelColumnRecord recdef;
    Gtk::TreeModelColumn<Glib::ustring> strcol;
    Gtk::TreeModelColumn<DisplayType> intcol;
    recdef.add(strcol);
    recdef.add(intcol);
    display_type_list = Gtk::ListStore::create(recdef);
    append_displaytype(display_type_list, tp_scale);
    append_displaytype(display_type_list, tp_scale_log);
    append_displaytype(display_type_list, tp_toggle);
    append_displaytype(display_type_list, tp_int);
    append_displaytype(display_type_list, tp_enum);
    append_displaytype(display_type_list, tp_none);
    display_type_list_sr = Gtk::ListStore::create(recdef);
    append_displaytype(display_type_list_sr, tp_scale);
    append_displaytype(display_type_list_sr, tp_scale_log);
    append_displaytype(display_type_list_sr, tp_none);
    output_type_list = Gtk::ListStore::create(recdef);
    append_displaytype(output_type_list, tp_display);
    append_displaytype(output_type_list, tp_display_toggle);
    append_displaytype(output_type_list, tp_none);

    treeview1->signal_row_activated().connect(sigc::mem_fun(this, &PluginDisplay::on_row_activated));
    treeview1->set_search_equal_func(sigc::mem_fun(this,&PluginDisplay::search_equal));
    Gtk::Entry *e;
    bld->find_widget("search_entry", e);
    e->signal_activate().connect(sigc::mem_fun(this, &PluginDisplay::on_search_entry_activate));
    treeview1->set_search_entry(*e);
    sel = treeview1->get_selection();
    sel->set_mode(Gtk::SELECTION_BROWSE);
    sel->signal_changed().connect(sigc::mem_fun(this, &PluginDisplay::selection_changed));
    treeview1->set_model(plugin_liststore);
    cellrenderer_active->signal_toggled().connect(sigc::mem_fun(this, &PluginDisplay::on_active_toggled));
    bld->find_widget("cellrenderer_ladspa", r);
    bld->find_widget("treeviewcolumn_ladspa", c);
    c->set_cell_data_func(*r, sigc::mem_fun(this, &PluginDisplay::display_ladspa));

    Gtk::ComboBox *cb;
    bld->find_widget("plugin_category", cb);
    cb->set_cell_data_func(*cellrenderer_category, sigc::mem_fun(this, &PluginDisplay::display_category));
    bld->find_widget("plugin_quirks", cb);
    cb->set_cell_data_func(*cellrenderer_quirks, sigc::mem_fun(this, &PluginDisplay::display_quirks));

    master_slider_idx->set_cell_data_func(*cellrenderer_master, sigc::mem_fun(this, &PluginDisplay::display_master_idx));
    master_slider_idx->signal_changed().connect(sigc::mem_fun(this, &PluginDisplay::set_master_text));

    selected_only->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &PluginDisplay::on_view_changed), selected_only));
    changed_only->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &PluginDisplay::on_view_changed), changed_only));
    show_all->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &PluginDisplay::on_view_changed), show_all));

    bld->find_widget("combobox_mono_stereo", cb);
    cb->signal_changed().connect(sigc::mem_fun(this, &PluginDisplay::on_mono_stereo_changed));
    cb->set_active(0);
    Gtk::Button *b;
    bld->find_widget("reset_changes", b);
    b->signal_clicked().connect(sigc::mem_fun(this, &PluginDisplay::on_delete_changes));

    bld->find_widget("master_slider_idx", cb);
    cb->set_model(masteridx_liststore);

    bld->find_widget("button_cancel", b);
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(b->gobj()), actiongroup->get_action("QuitAction")->gobj());
    bld->find_widget("button_apply", b);
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(b->gobj()), actiongroup->get_action("ApplyAction")->gobj());
    bld->find_widget("button_save", b);
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(b->gobj()), actiongroup->get_action("SaveAction")->gobj());
    bld->find_widget("select_all", b);
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(b->gobj()), actiongroup->get_action("SelectAllAction")->gobj());
    bld->find_widget("select_none", b);
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(b->gobj()), actiongroup->get_action("SelectNoneAction")->gobj());

    window->set_icon(icon);
    window->show();
}

PluginDisplay::~PluginDisplay() {
    delete window;
    for (std::vector<PluginDesc*>::iterator i = pluginlist.begin(); i != pluginlist.end(); ++i) {
	delete *i;
    }
}

static void split(std::vector<ustring>& strvec, const ustring& str) {
    size_t start = 0, np = ustring::npos;
    while (true) {
        size_t end = str.find_first_of(' ', start);
	size_t len = (end == np) ? np : end - start;
	if (len > 0) {
	    strvec.push_back(str.substr(start, len));
	}
	if (end == np) {
	    return;
	}
        start = end + 1;
    }
}

bool PluginDisplay::search_equal(const Glib::RefPtr<Gtk::TreeModel>& model, int column, const ustring& key, const Gtk::TreeIter& iter) {
    PluginDesc *p = iter->get_value(plugin_liststore->col.pdesc);
    ustring txt(gx_system::to_string(p->UniqueID));
    if (txt.compare(0, ustring::npos, key, 0, key.size()) == 0) {
        return false;
    }
    txt = iter->get_value(plugin_liststore->col.name).lowercase();
    std::vector<ustring> keyvec;
    split(keyvec, key);
    for (std::vector<ustring>::iterator i = keyvec.begin(); i != keyvec.end(); ++i) {
        if (txt.find(*i) == ustring::npos) {
            return true;
	}
    }
    return false;
}

void PluginDisplay::display_step(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    PortDesc *q = it->get_value(port_liststore->col.port);
    DisplayType tp = q->get_tp();
    cell->property_visible().set_value(tp == tp_scale || tp == tp_scale_log);
    if (q->step != stp_normal) {
        dynamic_cast<Gtk::CellRendererText*>(cell)->property_foreground().set_value("red");
    } else {
        dynamic_cast<Gtk::CellRendererText*>(cell)->property_foreground_set().set_value(false);
    }
}

void PluginDisplay::display_ladspa(Gtk::CellRenderer *cell, const Gtk::TreeIter& iter) {
    PluginDesc *p = iter->get_value(plugin_liststore->col.pdesc);
    if (p->has_settings) {
        dynamic_cast<Gtk::CellRendererText*>(cell)->property_foreground().set_value("red");
    } else {
        dynamic_cast<Gtk::CellRendererText*>(cell)->property_foreground_set().set_value(false);
    }
}

void PluginDisplay::display_label(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    PortDesc *q = it->get_value(enum_liststore->col.port);
    if (q->enumkey_changed(int(it->get_value(enum_liststore->col.value)))) {
	dynamic_cast<Gtk::CellRendererText*>(cell)->property_foreground().set_value("red");
    } else {
        dynamic_cast<Gtk::CellRendererText*>(cell)->property_foreground_set().set_value(false);
    }
}

void PluginDisplay::display_idx(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    PortDesc *q = it->get_value(port_liststore->col.port);
    if (int(port_liststore->get_path(it)[0]) != q->get_pos()) {
	dynamic_cast<Gtk::CellRendererText*>(cell)->property_foreground().set_value("red");
    } else {
        dynamic_cast<Gtk::CellRendererText*>(cell)->property_foreground_set().set_value(false);
    }
}

void PluginDisplay::display_name(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    PortDesc *q = it->get_value(port_liststore->col.port);
    if (q->is_set(ChangeableValues::name_set)) {
	dynamic_cast<Gtk::CellRendererText*>(cell)->property_foreground().set_value("red");
    } else {
        dynamic_cast<Gtk::CellRendererText*>(cell)->property_foreground_set().set_value(false);
    }
}

void PluginDisplay::display_default(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    PortDesc *q = it->get_value(port_liststore->col.port);
    Gtk::CellRendererText *tcell = dynamic_cast<Gtk::CellRendererText*>(cell);
    tcell->property_foreground_set().set_value(false);
    tcell->property_background_set().set_value(false);
    DisplayType tp = q->get_tp();
    if (tp == tp_display || tp == tp_display_toggle || tp == tp_none) {
        cell->property_visible().set_value(false);
        return;
    }
    cell->property_visible().set_value(true);
    if (q->is_set(ChangeableValues::dflt_set)) {
        tcell->property_foreground().set_value("red");
    } else if (q->fake_dflt) {
        tcell->property_background().set_value("grey");
    }
}

void PluginDisplay::display_lower(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    PortDesc *q = it->get_value(port_liststore->col.port);
    Gtk::CellRendererText *tcell = dynamic_cast<Gtk::CellRendererText*>(cell);
    tcell->property_foreground_set().set_value(false);
    tcell->property_background_set().set_value(false);
    DisplayType tp = q->get_tp();
    if (tp == tp_toggle || tp == tp_display_toggle || tp == tp_none) {
        cell->property_visible().set_value(false);
        return;
    }
    cell->property_visible().set_value(true);
    if (q->is_set(ChangeableValues::low_set)) {
        tcell->property_foreground().set_value("red");
    } else if (q->fake_low) {
        tcell->property_background().set_value("grey");
    }
}

void PluginDisplay::display_upper(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    PortDesc *q = it->get_value(port_liststore->col.port);
    Gtk::CellRendererText *tcell = dynamic_cast<Gtk::CellRendererText*>(cell);
    tcell->property_foreground_set().set_value(false);
    tcell->property_background_set().set_value(false);
    DisplayType tp = q->get_tp();
    if (tp == tp_toggle || tp == tp_display_toggle || tp == tp_none) {
        cell->property_visible().set_value(false);
        return;
    }
    cell->property_visible().set_value(true);
    if (q->is_set(ChangeableValues::up_set)) {
        tcell->property_foreground().set_value("red");
    } else if (q->fake_up) {
        tcell->property_background().set_value("grey");
    }
}

void PluginDisplay::display_SR(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    cell->property_visible().set_value(it->get_value(port_liststore->col.port)->has_sr);
}

void PluginDisplay::display_type(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    PortDesc *q = it->get_value(port_liststore->col.port);
    Gtk::CellRendererText *tcell = dynamic_cast<Gtk::CellRendererText*>(cell);
    if (q->is_set(ChangeableValues::tp_set)) {
        tcell->property_foreground().set_value("red");
    } else {
        tcell->property_foreground_set().set_value(false);
    }
}

void PluginDisplay::display_newrow(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    PortDesc *q = it->get_value(port_liststore->col.port);
    if (q->is_set(ChangeableValues::newrow_set)) {
        cell->property_cell_background().set_value("red");
    } else {
        cell->property_cell_background_set().set_value(false);
    }
}

void PluginDisplay::display_caption(Gtk::CellRenderer *cell, const Gtk::TreeIter& it) {
    PortDesc *q = it->get_value(port_liststore->col.port);
    if (!q->has_caption) {
        cell->property_cell_background().set_value("red");
    } else {
        cell->property_cell_background_set().set_value(false);
    }
}

void PluginDisplay::on_delete_changes() {
    if (!current_plugin) {
	return;
    }
    current_plugin->reset();
    int changed = current_plugin->check_changed();
    int change_diff = changed - old_state;
    if (change_diff) {
	change_count += change_diff;
	set_title();
    }
    if (!changed) {
	delete current_plugin->old;
	current_plugin->old = 0;
    }
    current_plugin = 0;
    selection_changed();
}

void PluginDisplay::on_search_entry_activate() {
    Gtk::TreeIter it = treeview1->get_selection()->get_selected();
    if (it) {
	bool v = !it->get_value(plugin_liststore->col.active);
	it->set_value(plugin_liststore->col.active, v);
	change_count += it->get_value(plugin_liststore->col.pdesc)->set_active(v);
	set_title();
    }
}

bool PluginDisplay::check_for_changes() {
    PluginDesc *cur = current_plugin;
    save_current();
    bool ret = false;
    for (std::vector<PluginDesc*>::iterator p = pluginlist.begin(); p != pluginlist.end(); ++p) {
	if ((*p)->active != (*p)->active_set) {
	    ret = true;
	    break;
	}
	if ((*p)->old) {
	    ret = true;
	    break;
	}
    }
    if (cur) {
	set_old_state(cur);
    }
    return ret;
}

int PluginDisplay::ask_discard() {
    Gtk::MessageDialog d(*window, _("Discard changes to plugin definitions?"), false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO, true);
    return d.run();
}

bool PluginDisplay::check_exit() {
    if (check_for_changes()) {
	int ret = ask_discard();
	if (ret != Gtk::RESPONSE_YES) {
	    return false;
	}
    }
    return true;
}

bool PluginDisplay::on_delete_event(GdkEventAny *) {
    return !check_exit();
}

void PluginDisplay::on_quit() {
    if (check_exit()) {
	finished_callback(false, true);
    }
}

void PluginDisplay::on_find() {
    search_entry->grab_focus();
}

void PluginDisplay::display_quirks(const Gtk::TreeIter& it) {
    if (!current_plugin) {
	cellrenderer_quirks->property_foreground_set().set_value(false);
    } else {
	int quirks;
	it->get_value(1, quirks);
	if (quirks == current_plugin->quirks_default) {
	    cellrenderer_quirks->property_foreground_set().set_value(false);
	} else {
	    cellrenderer_quirks->property_foreground().set_value("red");
	}
    }
}

void PluginDisplay::display_category(const Gtk::TreeIter& it) {
    if (!current_plugin) {
	cellrenderer_category->property_foreground_set().set_value(false);
    } else {
	ustring cat;
	it->get_value(0, cat);
	if (cat == current_plugin->deduced_category) {
	    cellrenderer_category->property_foreground_set().set_value(false);
	} else {
	    cellrenderer_category->property_foreground().set_value("red");
	}
    }
}

void PluginDisplay::load() {
    int a = combobox_mono_stereo->get_model()->get_path(combobox_mono_stereo->get_active())[0];
    bool s = selected_only->get_active();
    bool c = changed_only->get_active();
    plugin_liststore->clear();
    for (std::vector<PluginDesc*>::iterator v = pluginlist.begin(); v != pluginlist.end(); ++v) {
	if (s && !(*v)->active) {
	    continue;
	}
	if (c && !(*v)->has_settings) {
	    continue;
	}
	if ((a == 1 && (*v)->tp != 0) || (a == 2 && (*v)->tp != 1)) {
	    continue;
	}
	Gtk::TreeIter it = plugin_liststore->append();
	it->set_value(plugin_liststore->col.name, ustring((*v)->Name));
	it->set_value(plugin_liststore->col.active, (*v)->active);
	it->set_value(plugin_liststore->col.pdesc, *v);
    }
}

void PluginDisplay::on_save() {
    finished_callback(do_save(), true);
}

void PluginDisplay::on_apply() {
    if (do_save()) {
	finished_callback(true, false);
    }
    selection_changed();
}

bool PluginDisplay::do_save() {
    bool changed = check_for_changes();
    std::string fname = get_config_filename();
    std::string tfname = fname + ".tmp";
    ofstream tfile(tfname.c_str());
    JsonWriter jw(&tfile);
    jw.begin_array(true);
    for (std::vector<PluginDesc*>::iterator p = pluginlist.begin(); p != pluginlist.end(); ++p) {
	if ((*p)->active) {
	    (*p)->output_entry(jw);
	}
    }
    jw.end_array(true);
    jw.close();
    tfile.close();
    std::vector<std::pair<std::string,std::string> > fl;
    for (std::vector<PluginDesc*>::iterator p = pluginlist.begin(); p != pluginlist.end(); ++p) {
	std::string cname = options.get_plugin_filepath(
	    gx_engine::LadspaLoader::get_ladspa_filename((*p)->UniqueID));
	if ((*p)->active || (*p)->has_settings) {
	    std::string tcname = cname + ".tmp";
	    ofstream tcfile(tcname.c_str());
	    JsonWriter jw2(&tcfile);
	    (*p)->output(jw2);
	    jw2.close();
	    tcfile.close();
	    fl.push_back(std::pair<std::string,std::string>(tcname, cname));
	} else {
	    fl.push_back(std::pair<std::string,std::string>("", cname));
	}
    }
    if (rename(tfname.c_str(), fname.c_str()) != 0) {
	char buf[100];
	char *p = strerror_r(errno, buf, sizeof(buf));
	gx_system::gx_print_error(
	    "ladspalist",ustring::compose(_("error renaming LADSPA config file '%1': %2\n"), fname, p));
	return false;
    }
    for (std::vector<std::pair<std::string,std::string> >::iterator i = fl.begin(); i != fl.end(); ++i) {
	if (i->first.empty()) {
	    unlink(i->second.c_str());
	} else {
	    if (rename(i->first.c_str(), i->second.c_str()) != 0) {
		char buf[100];
		char *p = strerror_r(errno, buf, sizeof(buf));
		gx_system::gx_print_error(
		    "ladspalist",
		    ustring::compose("error renaming %1 to %2: %3\n", i->first, i->second, p));
	    }
	}
    }
    for (std::vector<PluginDesc*>::iterator p = pluginlist.begin(); p != pluginlist.end(); ++p) {
	(*p)->active_set = (*p)->active;
	delete (*p)->old;
	(*p)->old = 0;
    }
    old_state = 0;
    change_count = 0;
    set_title();
    current_plugin = 0;
    return changed;
}

void PluginDisplay::on_select_all(bool v) {
    int d = 0;
    Gtk::TreeNodeChildren ch = plugin_liststore->children();
    for (Gtk::TreeIter it = ch.begin(); it != ch.end(); ++it) {
	it->set_value(plugin_liststore->col.active, v);
	d += it->get_value(plugin_liststore->col.pdesc)->set_active(v);
    }
    if (d) {
	change_count += d;
	set_title();
    }
}

void PluginDisplay::on_show_details() {
    details_box->set_visible(show_details->get_active());
    int w, h;
    window->get_size(w, h);
    window->resize(1, h);
}

void PluginDisplay::on_add_dry_wet_controller() {
    if (!current_plugin) {
	return;
    }
    current_plugin->set_add_wet_dry_controller(dry_wet_button->get_active()); 
}

void PluginDisplay::on_row_activated(const Gtk::TreePath& path, Gtk::TreeViewColumn* column) {
    show_details->clicked();
}

void PluginDisplay::on_mono_stereo_changed() {
    load();
}

void PluginDisplay::on_view_changed(const Gtk::ToggleButton *b) {
    if (b->get_active()) {
	load();
    }
}

void PluginDisplay::save_current() {
    if (!current_plugin) {
	return;
    }
    ustring s = plugin_name->get_text();
    gx_system::strip(s);
    if (s.empty()) {
	current_plugin->shortname = current_plugin->Name;
    } else {
	current_plugin->shortname = s;
    }
    plugin_category->get_active()->get_value(0, current_plugin->category);
    plugin_quirks->get_active()->get_value(1, current_plugin->quirks);
    Gtk::TreeIter it = master_slider_idx->get_active();
    if (it) {
	it->get_value(0, current_plugin->MasterIdx);
    } else {
	current_plugin->MasterIdx = -1;
    }
    if (current_plugin->MasterIdx < 0) {
	current_plugin->MasterLabel = "";
    } else {
	current_plugin->MasterLabel = master_slider_name->get_text();
    }
    current_plugin->check_has_settings();
    int changed = current_plugin->check_changed();
    int change_diff = changed - old_state;
    if (change_diff) {
	change_count += change_diff;
	set_title();
    }
    if (!changed) {
	delete current_plugin->old;
	current_plugin->old = 0;
    }
    current_plugin = 0;
}

void PluginDisplay::set_title() {
    ustring t = _("Select LADSPA plugins for Guitarix");
    if (change_count) {
	window->set_title(t + _(" (*changed*)"));
    } else {
	window->set_title(t);
    }
}

void PluginDisplay::set_old_state(PluginDesc *p) {
    current_plugin = p;
    old_state = (p->old != 0);
    if (!p->old) {
	p->old = new PluginDesc(*p);
	p->old->ctrl_ports.clear();
	p->old->copy_ports(p);
    }
}

void PluginDisplay::selection_changed() {
    Gtk::TreeIter it = treeview1->get_selection()->get_selected();
    PluginDesc *p = 0;
    if (it) {
	p = it->get_value(plugin_liststore->col.pdesc);
	if (current_plugin == p) {
	    return;
	}
    }
    save_current();
    on_reordered_conn.block();
    port_liststore->clear();
    on_reordered_conn.unblock();
    ladspa_category->set_text("");
    ladspa_maker->set_text("");
    ladspa_uniqueid->set_text("");
    plugin_name->set_text("");
    plugin_category->set_active(-1);
    plugin_quirks->set_active(-1);
    if (!p) {
	return;
    }
    set_old_state(p);
    if (p->shortname != p->Name) {
	plugin_name->modify_text(Gtk::STATE_NORMAL, Gdk::Color("red"));
    } else {
	plugin_name->unset_text(Gtk::STATE_NORMAL);
    }
    plugin_name->set_text(p->shortname);
    Gtk::TreeNodeChildren ch = plugin_category->get_model()->children();
    int i = 0;
    for (it = ch.begin(); it != ch.end(); ++it, ++i) {
	ustring cat;
	it->get_value(0, cat);
	if (cat == p->category) {
	    plugin_category->set_active(i);
	    break;
	}
    }
    ch = plugin_quirks->get_model()->children();
    for (i = 0, it = ch.begin(); it != ch.end(); ++it, ++i) {
	int quirks;
	it->get_value(1, quirks);
	if (quirks == p->quirks) {
	    plugin_quirks->set_active(i);
	    break;
	}
    }
    Glib::RefPtr<Gtk::ListStore> ls_master = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(master_slider_idx->get_model());
    ls_master->clear();
    it = ls_master->append();
    i = -1;
    it->set_value(0, i);
    ustring ml("");
    for (unsigned int i = 0; i < p->ctrl_ports.size(); ++i) {
	it = ls_master->append();
	it->set_value(0, int(i));
	if (p->ctrl_ports[i]->pos == p->MasterIdx) {
	    ml = p->ctrl_ports[i]->factory.get_name();
	}
    }
    master_slider_idx->set_active(p->MasterIdx+1);
    master_slider_name->unset_text(Gtk::STATE_NORMAL);
    if (!p->MasterLabel.empty()) {
	master_slider_name->set_text(p->MasterLabel);
	if (p->MasterLabel != ml) {
	    master_slider_name->modify_text(Gtk::STATE_NORMAL, Gdk::Color("red"));
	}
    }
    dry_wet_button->set_active(current_plugin->add_wet_dry);
    ladspa_category->set_text(p->ladspa_category);
    ladspa_maker->set_text(p->Maker);
    ladspa_uniqueid->set_text(ustring::compose("%1: %2[%3]", p->UniqueID, p->path, p->index));
    for (unsigned int i = 0; i < p->ctrl_ports.size(); ++i) {
	PortDesc *q = p->ctrl_ports[i];
	Glib::RefPtr<Gtk::ListStore> tls;
	if (q->is_output) {
	    tls = output_type_list;
	} else if (q->has_sr) {
	    tls = display_type_list_sr;
	} else {
	    tls = display_type_list;
	}
	float dflt = q->get_dflt();
	float low = q->get_low();
	float up = q->get_up();
	if (q->has_sr && !q->use_sr) {
	    if (q->factory.is_set(ChangeableValues::dflt_set)) {
		dflt *= SR;
	    }
	    if (q->factory.is_set(ChangeableValues::low_set)) {
		low *= SR;
	    }
	    if (q->factory.is_set(ChangeableValues::up_set)) {
		up *= SR;
	    }
	}
	it = port_liststore->append();
	it->set_value(port_liststore->col.pos, q->pos);
	it->set_value(port_liststore->col.name, q->get_name());
	it->set_value(port_liststore->col.dflt, ustring::format(dflt));
	it->set_value(port_liststore->col.low, ustring::format(low));
	it->set_value(port_liststore->col.up, ustring::format(up));
	it->set_value(port_liststore->col.step, ustring(step_type_names[q->step]));
	it->set_value(port_liststore->col.display, ustring(display_type_names[q->get_tp()]));
	it->set_value(port_liststore->col.display_types, tls);
	it->set_value(port_liststore->col.port, q);
	it->set_value(port_liststore->col.newrow, q->get_newrow());
	it->set_value(port_liststore->col.use_sr, q->has_sr && !q->use_sr);
	it->set_value(port_liststore->col.has_caption, q->has_caption);
    }
}

void PluginDisplay::display_master_idx(const Gtk::TreeIter& it) {
    int i;
    it->get_value(0, i);
    if (i < 0) {
	cellrenderer_master->property_text().set_value("--");
	cellrenderer_master->property_foreground_set().set_value(false);
    } else {
	cellrenderer_master->property_foreground().set_value("red");
    }
}

void PluginDisplay::set_master_text() {
    Gtk::TreeIter it = master_slider_idx->get_active();
    if (!it) {
	master_slider_name->set_text("");
	master_slider_name->set_editable(false);
	return;
    }
    int idx;
    it->get_value(0, idx);
    if (idx < 0) {
	master_slider_name->set_text("");
	master_slider_name->set_editable(false);
    } else {
	for (std::vector<PortDesc*>::iterator q = current_plugin->ctrl_ports.begin(); q != current_plugin->ctrl_ports.end(); ++q) {
	    if ((*q)->pos == idx) {
		master_slider_name->set_text((*q)->factory.get_name());
		break;
	    }
	}
	master_slider_name->set_editable(true);
    }
}

void PluginDisplay::on_parameter_selection_changed() {
    Gtk::TreeIter it = treeview2->get_selection()->get_selected();
    enum_liststore->clear();
    if (it) {
	PortDesc *q = it->get_value(port_liststore->col.port);
	if (q->get_tp() == tp_enum) {
	    int up = int(q->get_up());
	    for (int idx = int(q->get_low()); idx <= up; ++idx) {
		it = enum_liststore->append();
		it->set_value(enum_liststore->col.value, idx);
		it->set_value(enum_liststore->col.label, q->get_enum(idx));
		it->set_value(enum_liststore->col.port, q);
	    }
	}
    }
}

void PluginDisplay::on_reordered(const Gtk::TreePath& path) {
    assert(current_plugin);
    std::map<int,int> d;
    for (unsigned int i = 0; i < current_plugin->ctrl_ports.size(); ++i) {
	d[current_plugin->ctrl_ports[i]->pos] = i;
    }
    std::vector<PortDesc*> l;
    Gtk::TreeNodeChildren ch = port_liststore->children();
    for (Gtk::TreeIter it = ch.begin(); it != ch.end(); ++it) {
	l.push_back(current_plugin->ctrl_ports[d[it->get_value(port_liststore->col.pos)]]);
    }
    current_plugin->ctrl_ports = l;
}

void PluginDisplay::on_type_edited(const ustring& path, const ustring& newtext) {
    Gtk::TreeIter it = port_liststore->get_iter(path);
    PortDesc *q = it->get_value(port_liststore->col.port);
    DisplayType tp_old = q->user.get_tp();
    DisplayType tp = tp_scale;
    for (unsigned int i = 0; i < sizeof(display_type_names)/sizeof(display_type_names[0]); i++) {
	if (newtext == display_type_names[i]) {
	    tp = static_cast<DisplayType>(i);
	    break;
	}
    }
    q->set_tp(tp);
    if (tp != tp_old) {
	if (tp == tp_scale_log) {
	    if (q->get_low() <= 0) {
		q->set_low(1e-7);
	    }
	    if (q->get_up() <= q->get_low()) {
		q->set_up(q->get_low()*1000);
	    }
	    float dflt = q->get_dflt();
	    if (!(q->get_low() <= dflt && dflt <= q->get_up())) {
		q->set_dflt(q->get_low());
	    }
	} else if (tp == tp_toggle) {
	    q->set_dflt(int(q->get_dflt() != 0));
	    q->set_low(0);
	    q->set_up(1);
	} else if (tp == tp_enum || tp == tp_int) {
	    q->set_dflt(round(q->get_dflt()));
	    q->set_low(round(q->get_low()));
	    q->set_up(round(q->get_up()));
	}
	float dflt = q->get_dflt();
	float low = q->get_low();
	float up = q->get_up();
	if (q->has_sr && !q->use_sr) {
	    dflt *= SR;
	    low *= SR;
	    up *= SR;
	}
	it->set_value(port_liststore->col.dflt, ustring::format(dflt));
	it->set_value(port_liststore->col.low, ustring::format(low));
	it->set_value(port_liststore->col.up, ustring::format(up));
    }
    it->set_value(port_liststore->col.display, newtext);
    on_parameter_selection_changed();
}

void PluginDisplay::on_step_edited(const ustring& path, const ustring& newtext) {
    Gtk::TreeIter it = port_liststore->get_iter(path);
    step_mode m = stp_normal;
    for (unsigned int i = 0; i < sizeof(step_type_names)/sizeof(step_type_names[0]); ++i) {
	if (step_type_names[i] == newtext) {
	    m = static_cast<step_mode>(i);
	    break;
	}
    }
    it->get_value(port_liststore->col.port)->step = m;
    it->set_value(port_liststore->col.step, newtext);
}

void PluginDisplay::on_label_edited(const ustring& path, const ustring& newtext) {
    Gtk::TreeIter it = enum_liststore->get_iter(path);
    PortDesc *q = it->get_value(enum_liststore->col.port);
    ustring text(newtext);
    gx_system::strip(text);
    int idx = it->get_value(enum_liststore->col.value);
    std::map<int, ustring>::iterator i = q->factory.find_enum(idx);
    if (text.empty() || (i != q->factory.enum_end() && i->second == text)) {
	q->user.erase_enum(idx);
	text = "";
    }
    if (text.empty()) {
	std::map<int, ustring>::iterator i = q->factory.find_enum(idx);
	if (i == q->factory.enum_end()) {
	    text = ustring::format(idx);
	} else {
	    text = i->second;
	}
    } else {
	q->user.set_enumvalue(idx, text);
    }
    it->set_value(enum_liststore->col.label, text);
}

void PluginDisplay::on_name_edited(const ustring& path, const ustring& newtext) {
    Gtk::TreeIter it = port_liststore->get_iter(path);
    PortDesc *q = it->get_value(port_liststore->col.port);
    ustring text(newtext);
    gx_system::strip(text);
    if (text.empty() || q->factory.get_name() == text) {
	q->user.unset(ChangeableValues::name_set);
    } else {
	q->user.set_name(text);
    }
    it->set_value(port_liststore->col.name, q->get_name());
}

void PluginDisplay::on_dflt_edited(const ustring& path, const ustring& newtext) {
    Gtk::TreeIter it = port_liststore->get_iter(path);
    PortDesc *q = it->get_value(port_liststore->col.port);
    ustring text(newtext);
    gx_system::strip(text);
    float val;
    if (text.empty()) {
	q->user.unset(ChangeableValues::dflt_set);
	val = q->factory.get_dflt();
	if (val < q->get_low()) {
	    q->set_low(val);
	}
	if (val > q->get_up()) {
	    q->set_up(val);
	}
	if (q->has_sr && !q->use_sr) {
	    val *= SR;
	}
    } else {
	char *p;
	val = strtod(text.c_str(), &p);
	if (p != text.c_str() + text.size()) {
	    return;
	}
	float val2;
	if (q->has_sr && !q->use_sr) {
	    val2 = val / SR;
	} else {
	    val2 = val;
	}
	if (!(q->get_low() <= val2 && val2 <= q->get_up())) {
	    return;
	}
	q->set_dflt(val2);
    }
    it->set_value(port_liststore->col.dflt, ustring::format(val));
}

void PluginDisplay::on_low_edited(const ustring& path, const ustring& newtext) {
    Gtk::TreeIter it = port_liststore->get_iter(path);
    PortDesc *q = it->get_value(port_liststore->col.port);
    ustring text(newtext);
    gx_system::strip(text);
    float val;
    if (text.empty()) {
	q->user.unset(ChangeableValues::low_set);
	val = q->factory.get_low();
	if (q->get_dflt() < val) {
	    q->set_dflt(val);
	}
	if (q->get_up() < val) {
	    q->set_up(min(q->get_up(),val+1));
	}
	if (q->has_sr && !q->use_sr) {
	    val *= SR;
	}
    } else {
	char *p;
	val = strtod(text.c_str(), &p);
	if (p != text.c_str() + text.size()) {
	    return;
	}
	float val2;
	if (q->has_sr && !q->use_sr) {
	    val2 = val/SR;
	} else {
	    val2 = val;
	}
	if (!(val2 < q->get_up())) {
	    return;
	}
	if (q->get_dflt() < val2) {
	    q->user.set_dflt(val2);
	}
	it->set_value(port_liststore->col.dflt, ustring::format(q->get_dflt()));
	q->set_low(val2);
	if (q->get_tp() == tp_enum) {
	    on_parameter_selection_changed();
	}
    }
    it->set_value(port_liststore->col.low, ustring::format(val));
}

void PluginDisplay::on_up_edited(const ustring& path, const ustring& newtext) {
    Gtk::TreeIter it = port_liststore->get_iter(path);
    PortDesc *q = it->get_value(port_liststore->col.port);
    ustring text(newtext);
    gx_system::strip(text);
    float val;
    if (text.empty()) {
	q->user.unset(ChangeableValues::up_set);
	val = q->factory.get_up();
	if (q->get_dflt() > val) {
	    q->set_dflt(val);
	}
	if (q->get_low() > val) {
	    q->set_low(max(q->get_low(),val-1));
	}
	if (q->has_sr && !q->use_sr) {
	    val *= SR;
	}
    } else {
	char *p;
	val = strtod(text.c_str(), &p);
	if (p != text.c_str() + text.size()) {
	    return;
	}
	float val2;
	if (q->has_sr && !q->use_sr) {
	    val2 = val/SR;
	} else {
	    val2 = val;
	}
	if (!(val2 > q->get_low())) {
	    return;
	}
	if (q->get_dflt() > val2) {
	    q->user.set_dflt(val2);
	}
	it->set_value(port_liststore->col.dflt, ustring::format(q->get_dflt()));
	q->set_up(val2);
	if (q->get_tp() == tp_enum) {
	    on_parameter_selection_changed();
	}
    }
    it->set_value(port_liststore->col.up, ustring::format(val));
}

void PluginDisplay::on_newrow_toggled(const ustring& path) {
    Gtk::TreeIter it = port_liststore->get_iter(path);
    PortDesc *q = it->get_value(port_liststore->col.port);
    bool s = !cellrenderer_newrow->get_active();
    it->set_value(port_liststore->col.newrow, s);
    if (s == q->factory.get_newrow()) {
	q->user.unset(ChangeableValues::newrow_set);
    } else {
	q->user.set_newrow(s);
    }
}

void PluginDisplay::on_caption_toggled(const ustring& path) {
    Gtk::TreeIter it = port_liststore->get_iter(path);
    PortDesc *q = it->get_value(port_liststore->col.port);
    bool s = !cellrenderer_caption->get_active();
    it->set_value(port_liststore->col.has_caption, s);
    q->has_caption = s;
}

void PluginDisplay::on_active_toggled(const ustring& path) {
    Gtk::TreeIter it = plugin_liststore->get_iter(path);
    bool s = !cellrenderer_active->get_active();
    it->set_value(plugin_liststore->col.active, s);
    change_count += it->get_value(plugin_liststore->col.pdesc)->set_active(s);
    set_title();
}


static struct {
    unsigned long from, to;
} ranges_1_based[] = {
    // swh
    {1181, 1440},
    {1605, 1605},
    {1881, 1922},
    // blop
    {1641, 1680},
    {2021, 2038},
};

static bool in_1_based_range(unsigned long uid) {
    for (unsigned int i = 0; i < sizeof(ranges_1_based)/sizeof(ranges_1_based[0]); ++i) {
        if (uid >= ranges_1_based[i].from && uid <= ranges_1_based[i].to) {
            return true;
	}
    }
    return false;
}

static void set_instances(const char *uri, std::map<unsigned long, PluginDesc*>& d, std::vector<ustring>& label,
			  std::vector<unsigned long>& not_found, std::set<unsigned long>& seen) {
    lrdf_uris *uris = lrdf_get_instances(uri);
    if (uris) {
        for (unsigned int i = 0; i < uris->count; ++i) {
            const char *u = uris->items[i];
            unsigned long uid = lrdf_get_uid(u);
            if (d.find(uid) == d.end()) {
                not_found.push_back(uid);
                seen.insert(uid);
                continue;
	    }
            if (seen.find(uid) == seen.end()) {
		PluginDesc *pd = d[uid];
                pd->set_category(label);
		for (unsigned int n = 0; n < pd->ctrl_ports.size(); n++) {
		    PortDesc *p = pd->ctrl_ports[n];
                    lrdf_defaults *sval = lrdf_get_scale_values(uid, p->idx);
                    if (sval) {
                        for (unsigned int nn = 0; nn < sval[0].count; nn++) {
                            lrdf_portvalue& t = sval[0].items[nn];
                            p->factory.set_enumvalue(t.value, t.label);
			}
			lrdf_free_setting_values(sval);
			if (LADSPA_IS_HINT_INTEGER(p->hint_desc)) {
			    p->factory.set_tp(tp_enum);
			}
		    }
		}
                uri = lrdf_get_default_uri(uid);
                if (uri) {
                    lrdf_defaults *sval = lrdf_get_setting_values(uri);
		    if (sval) {
			for (unsigned int nn = 0; nn < sval[0].count; nn++) {
                            lrdf_portvalue& t = sval[0].items[nn];
                            int idx = t.pid;
                            if (in_1_based_range(uid)) {
                                idx -= 1;
			    }
                            pd->set_default(idx, t.value, t.label);
			}
                        lrdf_free_setting_values(sval);
		    }
		}
	    }
            seen.insert(uid);
	}
        lrdf_free_uris(uris);
    }
}

static void descend(const char *uri, std::map<unsigned long, PluginDesc*>& d,
		    std::vector<unsigned long>& not_found, std::set<unsigned long>& seen,
		    std::vector<ustring>& base) {
    lrdf_uris *uris = lrdf_get_subclasses(uri);
    if (uris) {
	for (unsigned int i = 0; i < uris->count; ++i) {
	    const char *u = uris->items[i];
	    base.push_back(lrdf_get_label(u));
            set_instances(u, d, base, not_found, seen);
            descend(u, d, not_found, seen, base);
	    base.pop_back();
	}
        lrdf_free_uris(uris);
    }
}

std::string PluginDisplay::get_ladspa_plugin_config(unsigned long UniqueID) {
    return options.get_plugin_filepath("ladspa"+gx_system::to_string(UniqueID)+".js");
}

static bool cmp_plugins(const PluginDesc *a, const PluginDesc *b) {
    return ustring(a->Name) < ustring(b->Name);
}

void PluginDisplay::load_ladspalist(std::vector<unsigned long>& old_not_found, std::vector<PluginDesc*>& l) {
    gx_system::PathList pl("LADSPA_PATH");
    if (!pl.size()) {
        pl.add("/usr/lib/ladspa");
        pl.add("/usr/local/lib/ladspa");
    }
    std::map<unsigned long, PluginDesc*> d;
    for (gx_system::PathList::iterator it = pl.begin(); it != pl.end(); ++it) {
        Glib::RefPtr<Gio::File> file = *it;
        if (!file->query_exists()) {
            continue;
        }
        Glib::RefPtr<Gio::FileEnumerator> child_enumeration =
            file->enumerate_children(G_FILE_ATTRIBUTE_STANDARD_NAME
                                     "," G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME
                                     "," G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE);
        Glib::RefPtr<Gio::FileInfo> file_info;

        while ((file_info = child_enumeration->next_file()) != 0) {
            if (file_info->get_attribute_string(G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE) == "application/x-sharedlib") {
                std::string nm = file_info->get_attribute_byte_string(G_FILE_ATTRIBUTE_STANDARD_NAME);
                if (lib_is_blacklisted(nm)) {
                    continue;
                }
		//printf("opening %s/%s\n", file->get_path().c_str(), nm.c_str());
		load_ladspa_defs(Glib::build_filename(file->get_path(), nm), d);
            }
        }
    }
    gx_system::PathList rpl("LADSPA_RDF_PATH");
    if (!rpl.size()) {
        rpl.add("/usr/share/ladspa/rdf");
        rpl.add("/usr/local/share/ladspa/rdf");
    }
    lrdf_init();
    for (gx_system::PathList::iterator it = rpl.begin(); it != rpl.end(); ++it) {
        Glib::RefPtr<Gio::File> file = *it;
        if (!file->query_exists()) {
            continue;
        }
        Glib::RefPtr<Gio::FileEnumerator> child_enumeration =
            file->enumerate_children(G_FILE_ATTRIBUTE_STANDARD_NAME
                                     "," G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME
                                     "," G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE);
        Glib::RefPtr<Gio::FileInfo> file_info;

        while ((file_info = child_enumeration->next_file()) != 0) {
	    //if not f.endswith((".rdf",".rdfs")):
            if (file_info->get_attribute_string(G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE) == "application/rdf+xml") {
                std::string nm = file_info->get_attribute_byte_string(G_FILE_ATTRIBUTE_STANDARD_NAME);
                if (lib_is_blacklisted(nm)) {
                    continue;
                }
                lrdf_read_file(("file://"+Glib::build_filename(file->get_path(), nm)).c_str());
            }
        }
    }
    std::vector<unsigned long> not_found;
    std::set<unsigned long> seen;
    std::vector<ustring> base;
    locale_t loc = newlocale(LC_ALL, "C", 0);
    uselocale(loc);
    descend(LADSPA_BASE "Plugin", d, not_found, seen, base);
    uselocale(LC_GLOBAL_LOCALE);
    freelocale(loc);
    lrdf_cleanup();

    ifstream is(get_config_filename().c_str());
    if (!is.fail()) {
	try {
	    JsonParser jp(&is);
	    jp.next(JsonParser::begin_array);
	    while (jp.peek() == JsonParser::begin_array) {
		jp.next(JsonParser::begin_array);
		jp.next(JsonParser::value_string); // path
		jp.next(JsonParser::value_number); // index
		jp.next(JsonParser::value_number); // UniqueID
		unsigned long uid = jp.current_value_uint();
		if (d.find(uid) == d.end()) {
		    old_not_found.push_back(uid);
		} else {
		    d[uid]->set_active(true);
		    d[uid]->active_set = true;
		}
		jp.next(JsonParser::value_string); // Label
		jp.next(JsonParser::end_array);
	    }
	    jp.close();
	} catch(JsonException& e) {
	    gx_system::gx_print_error(
		"ladspalist", ustring::compose(
		    _("error loading ladspa plugin selection data from file %1"),
		    get_config_filename()));
	}
	is.close();
    }
    for (std::map<unsigned long, PluginDesc*>::iterator v = d.begin(); v != d.end(); ++v) {
	v->second->fixup();
	std::string s = gx_engine::LadspaLoader::get_ladspa_filename(v->first);
	std::string fname = options.get_plugin_filepath(s);
	if (access(fname.c_str(), F_OK) != 0) {
	    fname = options.get_factory_filepath(s);
	    if (access(fname.c_str(), F_OK) != 0) {
		fname = "";
	    }
	}
	if (!fname.empty()) {
	    v->second->set_state(fname);
	}
    }
    for (std::map<unsigned long, PluginDesc*>::iterator i = d.begin(); i != d.end(); ++i) {
	l.push_back(i->second);
    }
    std::sort(l.begin(), l.end(), cmp_plugins);
}

} // namespace ladspa

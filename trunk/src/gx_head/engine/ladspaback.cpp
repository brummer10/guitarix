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

#include "engine.h"

using Glib::ustring;
using gx_system::JsonParser;
using gx_system::JsonWriter;
using gx_system::JsonException;

namespace ladspa {

//#define HARD_RT_ONLY

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

/****************************************************************
 ** PluginDesc, PortDesc
 */

static inline bool float_eq(float v1, float v2) {
    return abs(v1 - v2) <= 1e-5 * abs(v1);
}

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


ChangeableValues::ChangeableValues(gx_system::JsonParser& jp)
    : name(), dflt(), low(), up(), tp(tp_scale), enumdict(), newrow(), set_flags(0) {
    jp.next(gx_system::JsonParser::begin_object);
    while (jp.peek() != gx_system::JsonParser::end_object) {
	jp.next(gx_system::JsonParser::value_key);
	if (jp.read_kv("name", name) ||
	    jp.read_kv("dflt", dflt) ||
	    jp.read_kv("low", low) ||
	    jp.read_kv("up", up) ||
	    jp.read_kv("tp", tp) ||
	    jp.read_kv("newrow", newrow) ||
	    jp.read_kv("set_flags", set_flags)) {
	} else if (jp.current_value() == "enumdict") {
	    jp.next(gx_system::JsonParser::begin_object);
	    while (jp.peek() != gx_system::JsonParser::end_object) {
		jp.next(gx_system::JsonParser::value_key);
		int k = jp.current_value_int();
		jp.next(gx_system::JsonParser::value_string);
		enumdict[k] = jp.current_value();
	    }
	    jp.next(gx_system::JsonParser::end_object);
	} else {
	    gx_print_warning(
		"ladspa::ChangeableValues", Glib::ustring::compose("unknown key: %1", jp.current_value()));
	    jp.skip_object();
	}
    }
    jp.next(gx_system::JsonParser::end_object);
}

void ChangeableValues::serializeJSON(gx_system::JsonWriter& jw) {
    jw.begin_object();
    jw.write_kv("name", name);
    jw.write_kv("dflt", dflt);
    jw.write_kv("low", low);
    jw.write_kv("up", up);
    jw.write_kv("tp", tp);
    jw.write_kv("newrow", newrow);
    jw.write_kv("set_flags", set_flags);
    jw.write_key("enumdict");
    jw.begin_object();
    for (std::map<int, Glib::ustring>::iterator i = enumdict.begin(); i != enumdict.end(); ++i) {
	jw.write_kv(gx_system::to_string(i->first).c_str(), i->second);
    }
    jw.end_object();
    jw.end_object();
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

PortDesc::PortDesc(gx_system::JsonParser& jp)
    : idx(), pos(), is_output(), hint_desc(),
      fake_low(false), fake_up(false), fake_dflt(false),
      step(stp_normal), use_sr(false), has_sr(false),
      has_caption(true), factory(), user() {
    jp.next(gx_system::JsonParser::begin_object);
    while (jp.peek() != gx_system::JsonParser::end_object) {
	jp.next(gx_system::JsonParser::value_key);
	if (jp.read_kv("idx", idx) ||
	    jp.read_kv("pos", pos) ||
	    jp.read_kv("is_output", is_output) ||
	    jp.read_kv("hint_desc", hint_desc) ||
	    jp.read_kv("fake_low", fake_low) ||
	    jp.read_kv("fake_up", fake_up) ||
	    jp.read_kv("fake_dflt", fake_dflt) ||
	    jp.read_kv("step", step) ||
	    jp.read_kv("use_sr", use_sr) ||
	    jp.read_kv("has_sr", has_sr) ||
	    jp.read_kv("has_caption", has_caption)) {
	} else if (jp.current_value() == "factory") {
	    factory = ChangeableValues(jp);
	} else if (jp.current_value() == "user") {
	    user = ChangeableValues(jp);
	} else {
	    gx_print_warning(
		"ladspa::PortDesc", Glib::ustring::compose("unknown key: %1", jp.current_value()));
	    jp.skip_object();
	}
    }
    jp.next(gx_system::JsonParser::end_object);
}

void PortDesc::serializeJSON(gx_system::JsonWriter& jw) {
    jw.begin_object();
    jw.write_kv("idx", idx);
    jw.write_kv("pos", pos);
    jw.write_kv("is_output", is_output);
    jw.write_kv("hint_desc", hint_desc);
    jw.write_kv("fake_low", fake_low);
    jw.write_kv("fake_up", fake_up);
    jw.write_kv("fake_dflt", fake_dflt);
    jw.write_kv("step", step);
    jw.write_kv("use_sr", use_sr);
    jw.write_kv("has_sr", has_sr);
    jw.write_kv("has_caption", has_caption);
    jw.write_key("factory"); factory.serializeJSON(jw);
    jw.write_key("user"); user.serializeJSON(jw);
    jw.end_object();
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
      ladspa_category(), active(false), active_set(false), has_settings(false), add_wet_dry(0), old(0) {
    quirks = quirks_default = quirks_get();
}

PluginDesc::~PluginDesc() {
    delete old;
    for (std::vector<PortDesc*>::iterator i = ctrl_ports.begin(); i != ctrl_ports.end(); ++i) {
	delete *i;
    }
}

PluginDesc::PluginDesc(gx_system::JsonParser& jp):
    UniqueID(),
    Label(),
    Name(),
    shortname(),
    Maker(),
    MasterIdx(),
    MasterLabel(),
    tp(),
    ctrl_ports(),
    path(),
    index(),
    category(),
    deduced_category(),
    quirks(),
    quirks_default(),
    ladspa_category(),
    active(),
    active_set(),
    has_settings(),
    add_wet_dry(),
    old(0) {
    jp.next(gx_system::JsonParser::begin_object);
    while (jp.peek() != gx_system::JsonParser::end_object) {
	jp.next(gx_system::JsonParser::value_key);
	if (jp.read_kv("UniqueID", UniqueID) ||
	    jp.read_kv("Label", Label) ||
	    jp.read_kv("Name", Name) ||
	    jp.read_kv("shortname", shortname) ||
	    jp.read_kv("Maker", Maker) ||
	    jp.read_kv("MasterIdx", MasterIdx) ||
	    jp.read_kv("MasterLabel", MasterLabel) ||
	    jp.read_kv("tp", tp) ||
	    jp.read_kv("path", path) ||
	    jp.read_kv("index", index) ||
	    jp.read_kv("category", category) ||
	    jp.read_kv("deduced_category", deduced_category) ||
	    jp.read_kv("quirks", quirks) ||
	    jp.read_kv("quirks_default", quirks_default) ||
	    jp.read_kv("ladspa_category", ladspa_category) ||
	    jp.read_kv("active", active) ||
	    jp.read_kv("active_set", active_set) ||
	    jp.read_kv("has_settings", has_settings) ||
	    jp.read_kv("add_wet_dry", add_wet_dry)) {
	} else if (jp.current_value() == "old") {
	    old = new PluginDesc(jp);
	} else if (jp.current_value() == "ctrl_ports") {
	    jp.next(gx_system::JsonParser::begin_array);
	    while (jp.peek() != gx_system::JsonParser::end_array) {
		ctrl_ports.push_back(new PortDesc(jp));
	    }
	    jp.next(gx_system::JsonParser::end_array);
	} else {
	    gx_print_warning(
		"ladspa::PluginDesc", Glib::ustring::compose("unknown key: %1", jp.current_value()));
	    jp.skip_object();
	}
    }
    jp.next(gx_system::JsonParser::end_object);
}

void PluginDesc::serializeJSON(gx_system::JsonWriter& jw) {
    jw.begin_object();
    jw.write_kv("UniqueID", static_cast<unsigned int>(UniqueID));
    jw.write_kv("Label", Label);
    jw.write_kv("Name", Name);
    jw.write_kv("shortname", shortname);
    jw.write_kv("Maker", Maker);
    jw.write_kv("MasterIdx", MasterIdx);
    jw.write_kv("MasterLabel", MasterLabel);
    jw.write_kv("tp", tp);
    jw.write_kv("path", path);
    jw.write_kv("index", index);
    jw.write_kv("category", category);
    jw.write_kv("deduced_category", deduced_category);
    jw.write_kv("quirks", quirks);
    jw.write_kv("quirks_default", quirks_default);
    jw.write_kv("ladspa_category", ladspa_category);
    jw.write_kv("active", active);
    jw.write_kv("active_set", active_set);
    jw.write_kv("has_settings", has_settings);
    jw.write_kv("add_wet_dry", add_wet_dry);
    if (old) {
	jw.write_key("old");
	old->serializeJSON(jw);
    }
    jw.write_key("ctrl_ports");
    jw.begin_array();
    for (std::vector<PortDesc*>::iterator i = ctrl_ports.begin(); i != ctrl_ports.end(); ++i) {
	(*i)->serializeJSON(jw);
    }
    jw.end_array();
    jw.end_object();
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

//static
void LadspaPluginList::add_plugin(const LADSPA_Descriptor& desc, pluginmap& d, const std::string& path, int index) {
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

//static
void LadspaPluginList::load_defs(const std::string& path, pluginmap& d) {
    void *handle;
    handle = dlopen(path.c_str(), RTLD_LOCAL|RTLD_NOW);
    if (!handle) {
	gx_print_warning(
	    "ladspalist",
	    ustring::compose(_("Cannot open plugin: %1\n"), dlerror()));
        return;
    }
    LADSPA_Descriptor_Function ladspa_descriptor = (LADSPA_Descriptor_Function)dlsym(handle, "ladspa_descriptor");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
	gx_print_warning("ladspalist", dlsym_error);
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
	add_plugin(*desc, d, path, i);
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
	gx_print_error("ladspalist", ustring::compose(_("can't open %1"), fname));
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
	gx_print_error(
	    "ladspalist",
	    ustring::compose(_("error parsing LADSPA plugin config file %1: %2"), fname, e.what()));
	return;
    }
    is.close();
    check_has_settings();
}

void PluginDesc::set_old() {
    old = new PluginDesc(*this);
    old->ctrl_ports.clear();
    old->copy_ports(this);
}

/****************************************************************
 ** class LadspaPluginList
 */

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

//static
void LadspaPluginList::set_instances(const char *uri, pluginmap& d, std::vector<ustring>& label,
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

//static
void LadspaPluginList::descend(const char *uri, pluginmap& d,
			       std::vector<unsigned long>& not_found,
			       std::set<unsigned long>& seen,
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

static bool cmp_plugins(const PluginDesc *a, const PluginDesc *b) {
    return ustring(a->Name) < ustring(b->Name);
}

void LadspaPluginList::load(gx_system::CmdlineOptions& options, std::vector<unsigned long>& old_not_found) {
    gx_system::PathList pl("LADSPA_PATH");
    if (!pl.size()) {
        pl.add("/usr/lib/ladspa");
        pl.add("/usr/local/lib/ladspa");
    }
    pluginmap d;
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
		load_defs(Glib::build_filename(file->get_path(), nm), d);
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

    ifstream is(options.get_ladspa_config_filename().c_str());
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
	    gx_print_error(
		"ladspalist", ustring::compose(
		    _("error loading ladspa plugin selection data from file %1"),
		    options.get_ladspa_config_filename()));
	}
	is.close();
    }
    for (pluginmap::iterator v = d.begin(); v != d.end(); ++v) {
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
    for (pluginmap::iterator i = d.begin(); i != d.end(); ++i) {
	push_back(i->second);
    }
    std::sort(begin(), end(), cmp_plugins);
}

void LadspaPluginList::save(gx_system::CmdlineOptions& options) {
    std::string fname = options.get_ladspa_config_filename();
    std::string tfname = fname + ".tmp";
    ofstream tfile(tfname.c_str());
    JsonWriter jw(&tfile);
    jw.begin_array(true);
    for (std::vector<PluginDesc*>::iterator p = begin(); p != end(); ++p) {
	if ((*p)->active) {
	    (*p)->output_entry(jw);
	}
    }
    jw.end_array(true);
    jw.close();
    tfile.close();
    std::vector<std::pair<std::string,std::string> > fl;
    for (std::vector<PluginDesc*>::iterator p = begin(); p != end(); ++p) {
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
	gx_print_error(
	    "ladspalist",ustring::compose(_("error renaming LADSPA config file '%1': %2"), fname, p));
	return;
    }
    for (std::vector<std::pair<std::string,std::string> >::iterator i = fl.begin(); i != fl.end(); ++i) {
	if (i->first.empty()) {
	    unlink(i->second.c_str());
	} else {
	    if (rename(i->first.c_str(), i->second.c_str()) != 0) {
		char buf[100];
		char *p = strerror_r(errno, buf, sizeof(buf));
		gx_print_error(
		    "ladspalist",
		    ustring::compose("error renaming %1 to %2: %3\n", i->first, i->second, p));
	    }
	}
    }
}


void LadspaPluginList::readJSON(gx_system::JsonParser& jp) {
    jp.next(gx_system::JsonParser::begin_array);
    while (jp.peek() != gx_system::JsonParser::end_array) {
	push_back(new ladspa::PluginDesc(jp));
    }
    jp.next(gx_system::JsonParser::end_array);
}

void LadspaPluginList::writeJSON(gx_system::JsonWriter& jw) {
    jw.begin_array();
    for (iterator i = begin(); i != end(); ++i) {
	(*i)->serializeJSON(jw);
    }
    jw.end_array();
}

LadspaPluginList::~LadspaPluginList() {
    for (iterator i = begin(); i != end(); ++i) {
	delete *i;
    }
}

} // namespace ladspa

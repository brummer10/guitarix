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

#include <dlfcn.h>
#include <ladspa.h>

#include "engine.h"

using gx_system::JsonException;
using gx_system::JsonParser;
using gx_system::to_string;
using gx_system::gx_print_error;
using Glib::ustring;

namespace gx_engine {

/****************************************************************
 ** class LadspaDsp
 */

class LadspaDsp: public PluginDef {
private:
    static void init(unsigned int samplingFreq, PluginDef *plugin);
    static void mono_process(int count, float *input, float *output, PluginDef *plugin);
    static void stereo_process(int count, float *input1, float *input2, float *output1, float *output2, PluginDef *plugin);
    static int activate(bool start, PluginDef *plugin);
    static int registerparam(const ParamReg& reg);
    static int uiloader(const UiBuilder& builder);
    static void del_instance(PluginDef *plugin);
    //
    const LADSPA_Descriptor *desc;
    void *handle;
    LADSPA_Handle instance;
    LADSPA_Data *ports;
    Glib::ustring name_str;
    const plugdesc *pd;
    bool is_activated;
    void connect(int tp, int i, float *v);
    inline void cleanup();
    void set_shortname();
    std::string make_id(const paradesc& p);
    LadspaDsp(const plugdesc *plug, void *handle_, const LADSPA_Descriptor *desc_, bool mono);
    ~LadspaDsp();
public:
    static LadspaDsp *create(const plugdesc *plug);
    void set_plugdesc(const plugdesc* pd_);
};

LadspaDsp *LadspaDsp::create(const plugdesc *plug) {
    void *handle;
    handle = dlopen(plug->path.c_str(), RTLD_LOCAL|RTLD_NOW);
    if (!handle) {
	gx_print_error("ladspaloader",ustring::compose(_("Cannot open plugin: %1 [%2]"), plug->path, dlerror()));
	return NULL;
    }
    LADSPA_Descriptor_Function ladspa_descriptor = (LADSPA_Descriptor_Function)dlsym(handle, "ladspa_descriptor");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
	gx_print_error("ladspaloader",ustring::compose(_("Cannot load symbol 'ladspa_descriptor': %1"), dlsym_error));
	dlclose(handle);
	handle = 0;
	return NULL;
    }
    const LADSPA_Descriptor *desc = ladspa_descriptor(plug->index);
    if (!desc) {
	gx_print_error("ladspaloader",ustring::compose(_("Cannot load ladspa descriptor #%1 from %2"), plug->index, plug->path));
	dlclose(handle);
	handle = 0;
	return NULL;
    }
    if (desc->UniqueID == 4069 || desc->UniqueID == 4070) {
	gx_print_error("ladspaloader",_("ladspa_guitarix not loaded"));
	dlclose(handle);
	handle = 0;
	return NULL;
    }
    int num_inputs = 0;
    int num_outputs = 0;
    for (unsigned int i = 0; i < desc->PortCount; ++i) {
	if (LADSPA_IS_PORT_AUDIO(desc->PortDescriptors[i])) {
	    if (LADSPA_IS_PORT_INPUT(desc->PortDescriptors[i])) {
		num_inputs += 1;
	    } else { // LADSPA_IS_PORT_OUTPUT(desc->PortDescriptors[i])
		num_outputs += 1;
	    }
	}
    }
    bool mono;
    if (num_inputs == 1 && num_outputs == 1) {
	mono = true;
    } else if (num_inputs == 2 && num_outputs == 2) {
	mono = false;
    } else {
	gx_print_error(
	    "ladspaloader",ustring::compose(
		_("cannot use ladspa plugin %1 with %2 inputs and %3 outputs"),
		desc->Label, num_inputs, num_outputs));
	dlclose(handle);
	handle = 0;
	return NULL;
    }
    return new LadspaDsp(plug, handle, desc, mono);
}

LadspaDsp::LadspaDsp(const plugdesc *plug, void *handle_, const LADSPA_Descriptor *desc_, bool mono)
    : PluginDef(), desc(desc_), handle(handle_), instance(),
      ports(new LADSPA_Data[desc->PortCount]), name_str(), pd(plug), is_activated(false) {
    version = PLUGINDEF_VERSION;
    id = pd->id_str.c_str();
    category = pd->category.c_str();
    description = desc->Name;
    name = desc->Name;
    set_shortname();
    set_samplerate = init;
    if (mono) {
	mono_audio = mono_process;
    } else {
	stereo_audio = stereo_process;
    }
    activate_plugin = activate;
    register_params = registerparam;
    load_ui = uiloader;
    delete_instance = del_instance;
}

inline void LadspaDsp::cleanup() {
    if (instance) {
	if (pd->quirks & need_activate) {
	    activate(true, this);
	}
	activate(false, this);
	if (!(pd->quirks & no_cleanup)) {
	    desc->cleanup(instance);
	}
	instance = 0;
    }
}

plugdesc::~plugdesc() {
    for (std::vector<paradesc*>::const_iterator it = names.begin(); it != names.end(); ++it) {
	delete *it;
    }
}

LadspaDsp::~LadspaDsp() {
    cleanup();
    if (handle && !(pd->quirks & no_cleanup)) {
	dlclose(handle);
    }
    delete[] ports;
}

int LadspaDsp::activate(bool start, PluginDef *plugin) {
    LadspaDsp& self = *static_cast<LadspaDsp*>(plugin);
    if (start == self.is_activated) {
	return 0;
    }
    self.is_activated = start;
    if (start) {
	if (self.desc->activate) {
	    self.desc->activate(self.instance);
	}
    } else {
	if (self.desc->deactivate) {
	    self.desc->deactivate(self.instance);
	}
    }
    return 0;
}

void LadspaDsp::connect(int tp, int i, float *v) {
    for (unsigned int n = 0; n < desc->PortCount; ++n) {
	if (!LADSPA_IS_PORT_AUDIO(desc->PortDescriptors[n])) {
	    continue;
	}
	if (desc->PortDescriptors[n] & tp) {
	    if (i == 0) {
		desc->connect_port(instance, n, v);
		return;
	    }
	    i -= 1;
	}
    }
    gx_print_error("ladspaloader", _("audio port not found"));
}

void LadspaDsp::set_plugdesc(const plugdesc* pd_) {
    pd = pd_;
    category = pd->category.c_str();
    set_shortname();
}

void LadspaDsp::set_shortname() {
    if (!pd->shortname.empty()) {
	shortname = pd->shortname.c_str();
    } else {
	name_str = desc->Name;
	if (name_str.size() > 24) {
	    name_str.erase(24);
	}
	shortname = name_str.c_str();
    }
}

void LadspaDsp::init(unsigned int samplingFreq, PluginDef *plugin) {
    LadspaDsp& self = *static_cast<LadspaDsp*>(plugin);
    self.cleanup();
    if (samplingFreq == 0) {
	return;
    }
    self.instance = self.desc->instantiate(self.desc, samplingFreq);
    int n = 0;
    for (std::vector<paradesc*>::const_iterator it = self.pd->names.begin(); it != self.pd->names.end(); ++it, ++n) {
	self.desc->connect_port(self.instance, (*it)->index, &self.ports[(*it)->index]);
    }
}

void LadspaDsp::mono_process(int count, float *input, float *output, PluginDef *plugin) {
    LadspaDsp& self = *static_cast<LadspaDsp*>(plugin);
    assert(self.is_activated);
    self.connect(LADSPA_PORT_INPUT, 0, input);
    self.connect(LADSPA_PORT_OUTPUT, 0, output);
    self.desc->run(self.instance, count);
}

void LadspaDsp::stereo_process(int count, float *input1, float *input2, float *output1, float *output2, PluginDef *plugin) {
    LadspaDsp& self = *static_cast<LadspaDsp*>(plugin);
    assert(self.is_activated);
    self.connect(LADSPA_PORT_INPUT, 0, input1);
    self.connect(LADSPA_PORT_INPUT, 1, input2);
    self.connect(LADSPA_PORT_OUTPUT, 0, output1);
    self.connect(LADSPA_PORT_OUTPUT, 1, output2);
    self.desc->run(self.instance, count);
}

static Glib::ustring TrimLabel(const char *label, int cnt_in_row) {
    const unsigned int minlen = 60  / cnt_in_row - 1;
    const unsigned int maxlen = minlen + 10;
    const unsigned int cutlen = (maxlen + minlen) / 2;
    Glib::ustring pn(label);
    unsigned int rem = pn.find_first_of("([");
    if(rem != Glib::ustring::npos) {
	pn.erase(rem);
    }
    while ((rem = pn.find_last_of(" ")) == pn.size()-1) {
	pn.erase(rem);
    }
    rem = 0;
    unsigned int rem1 = 0;
    unsigned int lastpos = 0;
    while (true) {
	rem1 = pn.find_first_of(" ", rem1);
	if (rem1 == Glib::ustring::npos) {
	    rem1 = pn.size();
	}
	while (rem1 > rem + minlen) {
	    if (lastpos > rem) {
		rem = lastpos;
		pn.replace(lastpos, 1, 1, '\n');
	    } else if (rem1 < rem + maxlen) {
		if (rem1 == pn.size()) {
		    break;
		}
		rem = rem1;
		pn.replace(rem1, 1, 1, '\n');
	    } else {
		rem += cutlen;
		pn.insert(rem, "\n");
	    }
	    rem += 1;
	}
	lastpos = rem1;
	rem1 += 1;
	if (rem1 >= pn.size()) {
	    break;
	}
    }
    return pn;
}

std::string LadspaDsp::make_id(const paradesc& p) {
    return pd->id_str + "." + to_string(p.index);
}

int LadspaDsp::registerparam(const ParamReg& reg) {
    LadspaDsp& self = *static_cast<LadspaDsp*>(reg.plugin);
    int n = 0;
    int cnt_in_row = 0;
    int left = 0;
    for (std::vector<paradesc*>::const_iterator it = self.pd->names.begin(); it != self.pd->names.end(); ++it, ++n) {
	paradesc *d = *it;
	if (d->tp != tp_none) {
	    left -= 1;
	    if (left < 0) {
		cnt_in_row = 1;
		std::vector<paradesc*>::const_iterator it2 = it+1;
		while (it2 != self.pd->names.end() && !(*it2)->newrow) {
		    if ((*it2)->tp != tp_none) {
			++cnt_in_row;
		    }
		    ++it2;
		}
		left = cnt_in_row;
	    }
	}
	const char *nm = self.desc->PortNames[d->index];
	Glib::ustring snm(d->name);
	if (snm.empty() && d->tp != tp_none) {
	    snm = TrimLabel(nm, cnt_in_row);
	}
	if (d->tp == tp_enum) {
	    reg.registerEnumVar(self.make_id(*d).c_str(), snm.c_str(), "S", nm, d->values, &self.ports[d->index],
				d->dflt, d->low, d->up, d->step);
	} else {
	    const char *tp = 0;
	    switch (d->tp) {
	    case tp_none:           tp = "S";  break;
	    case tp_int:            tp = "S";  break;
	    case tp_scale:          tp = "S";  break;
	    case tp_scale_log:      tp = "SL"; break;
	    case tp_toggle:         tp = "B";  break;
	    case tp_display:        tp = "SO"; break;
	    case tp_display_toggle: tp = "BO"; break;
	    default: assert(false);
	    }
	    reg.registerVar(self.make_id(*d).c_str(), snm.c_str(), tp, nm, &self.ports[d->index],
			    d->dflt, d->low, d->up, d->step);
	}
    }
    return 0;
}

int LadspaDsp::uiloader(const UiBuilder& b) {
    LadspaDsp& self = *static_cast<LadspaDsp*>(b.plugin);
    b.openHorizontalhideBox("");
    if (self.pd->master_idx >= 0) {
	const char *p = self.pd->master_label.c_str();
	if (!*p) {
	    p = 0;
	}
	b.create_master_slider(self.make_id(*self.pd->names[self.pd->master_idx]).c_str(), p);
    }
    b.closeBox();
    b.openVerticalBox("");
    b.openHorizontalBox("");
    int n = 0;
    for (std::vector<paradesc*>::const_iterator it = self.pd->names.begin(); it != self.pd->names.end(); ++it, ++n) {
	if ((*it)->newrow) {
	    b.closeBox();
	    b.openHorizontalBox("");
	}
	const char *p = 0;
	std::string id = self.make_id(**it);
	switch ((*it)->tp) {
	case tp_scale:
	case tp_scale_log:
	    if (!(*it)->has_caption) {
		p = "";
	    }
	    b.create_small_rackknob(id.c_str(), p);
	    break;
	case tp_toggle:
	    if ((*it)->has_caption) {
		b.create_switch("switch",id.c_str(), 0);
	    } else {
		b.create_switch_no_caption("switchit",id.c_str());
	    }
	    break;
	case tp_display:
	    if (!(*it)->has_caption) {
		p = "";
	    }
	    b.create_port_display(id.c_str(), p);
	    break;
	case tp_display_toggle:
	    if ((*it)->has_caption) {
		b.create_switch("led",id.c_str(), 0);
	    } else {
		b.create_switch_no_caption("led",id.c_str());
	    }
	    break;
	case tp_int:
	    b.create_spin_value(id.c_str(), 0);
	    break;
	case tp_enum:
	    if ((*it)->has_caption) {
		b.create_selector(id.c_str(), 0);
	    } else {
		b.create_selector_no_caption(id.c_str());
	    }
	    break;
	case tp_none:
	    break;
	default:
	    assert(false);
	}
    }
    b.closeBox();
    b.closeBox();
    return 0;
}

void LadspaDsp::del_instance(PluginDef *plugin) {
    delete static_cast<LadspaDsp*>(plugin);
}


/****************************************************************
 ** class LadspaLoader
 */

PluginDef *LadspaLoader::create(plugdesc *p) {
    return LadspaDsp::create(p);
}

LadspaLoader::LadspaLoader(const gx_system::CmdlineOptions& options)
    : plugins() {
    load(options, plugins);
}

LadspaLoader::~LadspaLoader() {
    for (pluginarray::iterator i = plugins.begin(); i != plugins.end(); ++i) {
	delete *i;
    }
}

bool LadspaLoader::load(const gx_system::CmdlineOptions& options, pluginarray& ml) {
    try {
	read_module_list(options, ml);
    } catch (JsonException &e) {
	gx_print_error("ladspaloader",ustring::compose(_("Exception in LADSPA list reader: %1"), e.what()));
	return false;
    }
    return true;
}

LadspaLoader::pluginarray::iterator LadspaLoader::find(unsigned long uniqueid) {
    for (pluginarray::iterator i = begin(); i != end(); ++i) {
	if ((*i)->UniqueID == uniqueid) {
	    return i;
	}
    }
    return end();
}

void LadspaLoader::update_instance(PluginDef *pdef, plugdesc *pdesc) {
    static_cast<LadspaDsp*>(pdef)->set_plugdesc(pdesc);
}

paradesc::~paradesc() {
    for (value_pair *p = values; p->value_id; ++p) {
	g_free(const_cast<char*>(p->value_id));
    }
    delete[] values;
}

void paradesc::set_valuelist(const std::vector<value_pair>& v) {
    values = new value_pair[v.size()+1];
    int n = 0;
    for (std::vector<value_pair>::const_iterator i = v.begin(); i != v.end(); ++i) {
	values[n++] = *i;
    }
    values[n].value_id = 0;
    values[n].value_label = 0;
}

void LadspaLoader::read_module_config(const std::string& filename, plugdesc *p) {
    std::ifstream ifs(filename.c_str());
    if (ifs.fail()) {
	gx_print_error("ladspaloader", ustring::compose(_("can't open %1"), filename));
        return;
    }
    gx_system::JsonParser jp(&ifs);
    jp.next(gx_system::JsonParser::begin_array);
    jp.next(gx_system::JsonParser::value_number);
    jp.current_value_int(); // int version
    jp.next(gx_system::JsonParser::value_string);
    p->shortname = jp.current_value();
    jp.next(gx_system::JsonParser::value_string);
    p->category = jp.current_value();
    jp.next(gx_system::JsonParser::value_number);
    p->master_idx = jp.current_value_int();
    jp.next(gx_system::JsonParser::value_string);
    p->master_label = jp.current_value();
    jp.next(gx_system::JsonParser::value_number);
    p->quirks = jp.current_value_int();
    jp.next(gx_system::JsonParser::begin_array);
    while (jp.peek() != gx_system::JsonParser::end_array) {
	paradesc *para = new paradesc;
	jp.next(gx_system::JsonParser::begin_array);
	jp.next(gx_system::JsonParser::value_number);
	para->index = jp.current_value_int();
	jp.skip_object(); // meta data
	jp.next(gx_system::JsonParser::value_string);
	para->name = jp.current_value();
	jp.next(gx_system::JsonParser::value_number); // use_sr
	jp.next(gx_system::JsonParser::value_number);
	para->dflt = jp.current_value_float();
	jp.next(gx_system::JsonParser::value_number);
	para->low = jp.current_value_float();
	jp.next(gx_system::JsonParser::value_number);
	para->up = jp.current_value_float();
	jp.next(gx_system::JsonParser::value_number);
	para->step = jp.current_value_float();
	jp.next(gx_system::JsonParser::value_number);
	para->tp = static_cast<widget_type>(jp.current_value_int()); //FIXME
	jp.next(gx_system::JsonParser::value_number);
	para->newrow = jp.current_value_int();
	jp.next(gx_system::JsonParser::value_number);
	para->has_caption = jp.current_value_int();
	jp.next(gx_system::JsonParser::begin_array);
	std::vector<value_pair> v;
	while (jp.peek() != gx_system::JsonParser::end_array) {
	    jp.next(gx_system::JsonParser::value_string);
	    const char *s = g_strdup(jp.current_value().c_str());
	    value_pair p = {s, s};
	    v.push_back(p);
	}
	jp.next(gx_system::JsonParser::end_array);
	para->set_valuelist(v);
	jp.next(gx_system::JsonParser::end_array);
	p->names.push_back(para);
    }
    jp.next(gx_system::JsonParser::end_array);
    jp.close();
    ifs.close();
}

void LadspaLoader::read_module_list(const gx_system::CmdlineOptions& options, pluginarray& ml) {
    std::ifstream ifs(options.get_user_filepath("ladspa_defs.js").c_str());
    if (ifs.fail()) {
        return;
    }
    gx_system::JsonParser jp(&ifs);
    jp.next(gx_system::JsonParser::begin_array);
    while (jp.peek() != gx_system::JsonParser::end_array) {
	jp.next(gx_system::JsonParser::begin_array);
	jp.next(gx_system::JsonParser::value_string);
	plugdesc *p = new plugdesc;
	p->path = jp.current_value();
	jp.next(gx_system::JsonParser::value_number);
	p->index = jp.current_value_int();
	jp.next(gx_system::JsonParser::value_number);
	p->UniqueID = jp.current_value_int();
	jp.next(gx_system::JsonParser::value_string);
	p->Label = jp.current_value();
	jp.next(gx_system::JsonParser::end_array);
	std::string s = get_ladspa_filename(p->UniqueID);
	std::string fname = options.get_plugin_filepath(s);
	if (access(fname.c_str(), F_OK) != 0) {
	    fname = options.get_factory_filepath(s);
	    if (access(fname.c_str(), F_OK) != 0) {
		fname = "";
	    }
	}
	if (!fname.empty()) {
	    try {
		read_module_config(fname, p);
	    } catch (JsonException &e) {
		gx_print_error("ladspaloader",ustring::compose(_("read error in file %1: %2"), s, e.what()));
	    }
	}
	p->id_str = "ladspa_";
	p->id_str += to_string(p->UniqueID);
	ml.push_back(p);
    }
    jp.close();
    ifs.close();
}

} // namespace gx_engine

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

class port_data {
public:
    LADSPA_Data port;
    std::string id;
    port_data(): port(), id() {}
};

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
    port_data *ctrl_ports;
    Glib::ustring name_str;
    const plugdesc *pd;
    bool is_activated;
    void connect(int tp, int i, float *v);
    inline void cleanup();
    void set_shortname();
    LadspaDsp(const plugdesc *plug, void *handle_, const LADSPA_Descriptor *desc_, int num_ctrl, bool mono);
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
    int num_ctrl = 0;
    int num_inputs = 0;
    int num_outputs = 0;
    for (unsigned int i = 0; i < desc->PortCount; ++i) {
	if (LADSPA_IS_PORT_CONTROL(desc->PortDescriptors[i])) {
	    num_ctrl += 1;
	} else if (LADSPA_IS_PORT_INPUT(desc->PortDescriptors[i])) {
	    num_inputs += 1;
	} else if (LADSPA_IS_PORT_OUTPUT(desc->PortDescriptors[i])) {
	    num_outputs += 1;
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
    return new LadspaDsp(plug, handle, desc, num_ctrl, mono);
}

LadspaDsp::LadspaDsp(const plugdesc *plug, void *handle_, const LADSPA_Descriptor *desc_, int num_ctrl, bool mono)
    : PluginDef(), desc(desc_), handle(handle_), instance(),
      ctrl_ports(), name_str(), pd(plug), is_activated(false) {
    ctrl_ports = new port_data[num_ctrl];
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
    }
}

LadspaDsp::~LadspaDsp() {
    cleanup();
    if (handle) {
	dlclose(handle);
    }
    delete[] ctrl_ports;
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
    self.instance = self.desc->instantiate(self.desc, samplingFreq);
    int n = 0;
    for (std::vector<paradesc>::const_iterator it = self.pd->names.begin(); it != self.pd->names.end(); ++it, ++n) {
	self.desc->connect_port(self.instance, it->index, &self.ctrl_ports[n].port);
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

int LadspaDsp::registerparam(const ParamReg& reg) {
    LadspaDsp& self = *static_cast<LadspaDsp*>(reg.plugin);
    int n = 0;
    int cnt_in_row = 0;
    int left = 0;
    for (std::vector<paradesc>::const_iterator it = self.pd->names.begin(); it != self.pd->names.end(); ++it, ++n) {
	if (it->tp != tp_none) {
	    left -= 1;
	    if (left < 0) {
		cnt_in_row = 1;
		std::vector<paradesc>::const_iterator it2 = it+1;
		while (it2 != self.pd->names.end() && !it2->newrow) {
		    if (it2->tp != tp_none) {
			++cnt_in_row;
		    }
		    ++it2;
		}
		left = cnt_in_row;
	    }
	}
	std::string& s = self.ctrl_ports[n].id;
	s = "ladspa_" + to_string(self.pd->UniqueID) + "." + to_string(it->index);
	const char *nm = self.desc->PortNames[it->index];
	Glib::ustring snm(it->name);
	if (snm.empty() && it->tp != tp_none) {
	    snm = TrimLabel(nm, cnt_in_row);
	}
	if (it->tp == tp_enum) {
	    reg.registerEnumVar(s.c_str(), snm.c_str(), "S", nm, it->values, &self.ctrl_ports[n].port,
				it->dflt, it->low, it->up, it->step);
	    } else {
	    const char *tp = 0;
	    switch (it->tp) {
	    case tp_none:           tp = "S";  break;
	    case tp_int:            tp = "S";  break;
	    case tp_scale:          tp = "S";  break;
	    case tp_scale_log:      tp = "SL"; break;
	    case tp_toggle:         tp = "B";  break;
	    case tp_display:        tp = "SO"; break;
	    case tp_display_toggle: tp = "BO"; break;
	    default: assert(false);
	    }
	    reg.registerVar(s.c_str(), snm.c_str(), tp, nm, &self.ctrl_ports[n].port,
			    it->dflt, it->low, it->up, it->step);
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
	b.create_master_slider(self.ctrl_ports[self.pd->master_idx].id.c_str(), p);
    }
    b.closeBox();
    b.openVerticalBox("");
    b.openHorizontalBox("");
    int n = 0;
    for (std::vector<paradesc>::const_iterator it = self.pd->names.begin(); it != self.pd->names.end(); ++it, ++n) {
	if (it->newrow) {
	    b.closeBox();
	    b.openHorizontalBox("");
	}
	const char *p = 0;
	switch (it->tp) {
	case tp_scale:
	case tp_scale_log:
	    if (!it->has_caption) {
		p = "";
	    }
	    b.create_small_rackknob(self.ctrl_ports[n].id.c_str(), p);
	    break;
	case tp_toggle:
	    if (it->has_caption) {
		b.create_switch("switch",self.ctrl_ports[n].id.c_str(), 0);
	    } else {
		b.create_switch_no_caption("switchit",self.ctrl_ports[n].id.c_str());
	    }
	    break;
	case tp_display:
	    if (!it->has_caption) {
		p = "";
	    }
	    b.create_port_display(self.ctrl_ports[n].id.c_str(), p);
	    break;
	case tp_display_toggle:
	    if (it->has_caption) {
		b.create_switch("led",self.ctrl_ports[n].id.c_str(), 0);
	    } else {
		b.create_switch_no_caption("led",self.ctrl_ports[n].id.c_str());
	    }
	    break;
	case tp_int:
	    b.create_spin_value(self.ctrl_ports[n].id.c_str(), 0);
	    break;
	case tp_enum:
	    if (it->has_caption) {
		b.create_selector(self.ctrl_ports[n].id.c_str(), 0);
	    } else {
		b.create_selector_no_caption(self.ctrl_ports[n].id.c_str());
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


#if 0 // unused
class PathList {
public:
    typedef std::list< Glib::RefPtr<Gio::File> > pathlist;
    typedef std::list< Glib::RefPtr<Gio::File> >::const_iterator iterator;
private:
    pathlist dirs;
public:
    PathList(const char *env_name = 0);
    void add(const std::string& d) { dirs.push_back(Gio::File::create_for_path(d)); }
    bool contains(const std::string& d) const;
    bool find_dir(std::string *d, const std::string& filename) const;
    iterator begin() { return dirs.begin(); }
    iterator end() { return dirs.end(); }
    size_t size() { return dirs.size(); }
};

PathList::PathList(const char *env_name): dirs() {
    if (!env_name) {
	return;
    }
    const char *p = getenv(env_name);
    if (!p) {
	return;
    }
    while (true) {
	const char *q = strchr(p, ':');
	if (q) {
	    int n = q - p;
	    if (n) {
		add(std::string(p, n));
	    }
	    p = q;
	} else {
	    if (*p) {
		add(p);
	    }
	    break;
	}
    }
}
#endif


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
    //FIXME
    static_cast<LadspaDsp*>(pdef)->set_plugdesc(pdesc);
}

void LadspaLoader::try_read_module_config(const std::string& filename, plugdesc *p) {
    std::ifstream ifs(filename.c_str());
    if (ifs.fail()) {
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
	paradesc para;
	jp.next(gx_system::JsonParser::begin_array);
	jp.next(gx_system::JsonParser::value_number);
	para.index = jp.current_value_int();
	jp.skip_object(); // meta data
	jp.next(gx_system::JsonParser::value_string);
	para.name = jp.current_value();
	jp.next(gx_system::JsonParser::value_number); // use_sr
	jp.next(gx_system::JsonParser::value_number);
	para.dflt = jp.current_value_float();
	jp.next(gx_system::JsonParser::value_number);
	para.low = jp.current_value_float();
	jp.next(gx_system::JsonParser::value_number);
	para.up = jp.current_value_float();
	jp.next(gx_system::JsonParser::value_number);
	para.step = jp.current_value_float();
	jp.next(gx_system::JsonParser::value_number);
	para.tp = static_cast<widget_type>(jp.current_value_int()); //FIXME
	jp.next(gx_system::JsonParser::value_number);
	para.newrow = jp.current_value_int();
	jp.next(gx_system::JsonParser::value_number);
	para.has_caption = jp.current_value_int();
	jp.next(gx_system::JsonParser::begin_array);
	std::vector<value_pair> v;
	while (jp.peek() != gx_system::JsonParser::end_array) {
	    jp.next(gx_system::JsonParser::value_string);
	    const char *s = g_strdup(jp.current_value().c_str());
	    value_pair p = {s, s};
	    v.push_back(p);
	}
	jp.next(gx_system::JsonParser::end_array);
	para.values = new value_pair[v.size()+1];
	int n = 0;
	for (std::vector<value_pair>::iterator i = v.begin(); i != v.end(); ++i) {
	    para.values[n++] = *i;
	}
	para.values[n].value_id = 0;
	para.values[n].value_label = 0;
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
	std::string s = options.get_plugin_filepath("ladspa"+to_string(p->UniqueID)+".js");
	try {
	    try_read_module_config(s, p);
	} catch (JsonException &e) {
	    gx_print_error("ladspaloader",ustring::compose(_("read error in file %1"), s));
	    throw e;
	}
	p->id_str = "ladspa_";
	p->id_str += to_string(p->UniqueID);
	ml.push_back(p);
    }
    jp.close();
    ifs.close();
}

} // namespace gx_engine

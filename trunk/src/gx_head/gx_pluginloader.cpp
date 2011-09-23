#include "guitarix.h"
#include <glibmm/i18n.h>
#include <dlfcn.h>
#include <dirent.h>

/****************************************************************
 ** uibuilder
 */

void uibuilder::openVerticalBox(const char* label) const {
    intf->openVerticalBox(label);
}

void uibuilder::openHorizontalBox(const char* label) const {
    intf->openHorizontalBox(label);
}

void uibuilder::create_small_rackknob(const char *id) const {
    intf->create_small_rackknob(id);
}

void uibuilder::create_small_rackknob(const char *id, const char *label) const {
    intf->create_small_rackknob(id, label);
}

void uibuilder::closeBox() const {
    intf->closeBox();
}

/****************************************************************
 ** regparam
 */

void paramreg::registerVar(const char* id, const char* name, const char* tp,
			   const char* tooltip, float* var, float val,
			   float low, float up, float step, bool exp) const
{
    gx_engine::registerVar(id, name, tp, tooltip, var, val, low, up, step, exp);
}

/****************************************************************
 ** support
 */

inline void registerNonMidiParam(const char*a, float*c, bool d,
                                 float std, float lower, float upper) {
    gx_gui::parameter_map.insert(new gx_gui::FloatParameter(a, "", gx_gui::Parameter::None, d, *c, std,
							    lower, upper, 0, false));
}

inline void registerNonMidiParam(const char*a, bool*c, bool d, float std = false) {
    gx_gui::parameter_map.insert(new gx_gui::BoolParameter(a, "", gx_gui::Parameter::None, d, *c, std, 0, false));
}

inline void registerUEnumParam(const char*a, const char*b, const char** vl, unsigned int*c, unsigned int std = 0,
			       bool exp = false) {
    gx_gui::parameter_map.insert(new gx_gui::UEnumParameter(a, b, vl, true, *c, std,
							    true, exp)); // false == no_midi_var
}

/****************************************************************
 ** PluginList
 */

PluginList::PluginList()
{
}

PluginList::~PluginList()
{
    for (pluginlist::iterator p = plist.begin(); p != plist.end(); p++) {
	delete *p;
    }
}

Plugin *PluginList::find_plugin(const char *name) {
    for (pluginlist::iterator p = plist.begin(); p != plist.end(); p++) {
	if (strcmp((*p)->plugin->name, name) == 0) {
	    return (*p);
	}
    }
    return 0;
}

int PluginList::load_library(string path) {
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
	gx_system::gx_print_warning("Plugin Loader", string("Cannot open library: ") + dlerror() + "\n");
        return -1;
    }
    dlerror();    // reset errors
    plugin_inifunc get_gx_plugins = (plugin_inifunc) dlsym(handle, "get_gx_plugins");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
	gx_system::gx_print_warning("Plugin Loader", string("Cannot load symbol 'get_gx_plugins': ") + dlsym_error + "\n");
        dlclose(handle);
        return -1;
    }
    plugindef *p;
    int n;
    if (get_gx_plugins(&n, &p)) {
	return -1;
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
	if (!add(&p[i])) {
	    cnt++;
	}
    }
    return cnt;
}

int PluginList::load_from_path(string path) {
    DIR *dp;
    struct dirent *dirp;
    if((dp = opendir(path.c_str())) == NULL) {
	gx_system::gx_print_warning("Plugin Loader", string("Error opening '" + path + "'"));
        return -1;
    }
    int cnt = 0;
    while ((dirp = readdir(dp)) != NULL) {
	string n = dirp->d_name;
	if (n.size() > 3 && n.compare(n.size()-3,3,".so") == 0) {
	    int res = load_library(path+"/"+n);
	    if (res > 0) {
		cnt += res;
	    }
	}
    }
    closedir(dp);
    return cnt;
}

int PluginList::add(plugindef *p) {
    if ((p->version & PLUGINDEF_VERMAJOR) != (PLUGINDEF_VERMAJOR & PLUGINDEF_VERSION)) {
	gx_system::gx_print_error("Plugin Loader", string("Plugin '") + p->name + "' has wrong version");
	return -1;
    }
    if (find_plugin(p->name)) {
	gx_system::gx_print_error("Plugin Loader", string("Plugin '") + p->name + "' already exists: skipped");
	return -1;
    }
    Plugin *pvars = new Plugin;
    memset(pvars, 0, sizeof(*pvars));
    pvars->plugin = p;
    plist.push_back(pvars);
    return 0;
}

void PluginList::registerParameter(gx_gui::ParameterGroups& groups, int pos_offset) {
    for (pluginlist::iterator p = plist.begin(); p != plist.end(); p++) {
	plugindef *pd = (*p)->plugin;
	groups.insert("gxpoweramp", pd->name);
	string s = pd->id;
	string id_dialog = s+".dialog";
	string id_on_off = s+".on_off";
	string id_pre_post = s+".pp";
	registerNonMidiParam(id_dialog.c_str(), &((*p)->box_visible), false);
	gx_gui::registerParam(id_on_off.c_str(),N_("on/off"), &((*p)->on_off), 0);
	static const char *post_pre[] = {N_("post"), N_("pre"), 0};
	registerUEnumParam(id_pre_post.c_str(), "select", post_pre,
			   &((*p)->effect_post_pre), 0);
	registerNonMidiParam((s+".position").c_str(), &((*p)->position), true,
			     pos_offset+plist.size()-1, 1, 999);
	pd->register_params(paramreg());
	gx_engine::registerInit(pd->name, pd->set_samplerate);
    }
}

void PluginList::append_rack(gx_gui::GxMainInterface *ui) {
    for (pluginlist::iterator p = plist.begin(); p != plist.end(); p++) {
	plugindef *pd = (*p)->plugin;
	string s = pd->id;
	string id_dialog = s+".dialog";
	string id_on_off = s+".on_off";
	string id_pre_post = s+".pp";
	ui->openMonoRackBox(pd->name, &((*p)->position), id_on_off.c_str(), id_pre_post.c_str(), id_dialog.c_str());
	pd->load_ui(uibuilder(ui));
	ui->closeMonoRackBox();
    }
}

void PluginList::append_module(int m, unsigned int chain) {
    for (pluginlist::iterator p = plist.begin(); p != plist.end(); p++) {
	if ((*p)->on_off && (*p)->position == m) {
	    plugindef *pd = (*p)->plugin;
	    if (chain == 2) {
		if (pd->stereo_audio) {
		    gx_engine::stereo_chain.append(pd->stereo_audio);
		}
	    } else if (pd->mono_audio) {
		if (chain != (*p)->effect_post_pre) {  // chain 0 is pre
		    gx_engine::mono_chain.append(pd->mono_audio);
		}
	    }
	}
    }
}

PluginList& get_pluginlist() {
    static PluginList pl;
    return pl;
}

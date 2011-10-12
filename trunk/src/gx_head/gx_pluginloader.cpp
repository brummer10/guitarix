#include "guitarix.h"
#include <glibmm/i18n.h>
#include <dlfcn.h>
#include <dirent.h>

/****************************************************************
 ** UiBuilder
 */

void UiBuilder::openVerticalBox(const char* label) const {
    intf->openVerticalBox(label);
}

void UiBuilder::openHorizontalBox(const char* label) const {
    intf->openHorizontalBox(label);
}

void UiBuilder::create_small_rackknob(const char *id) const {
    intf->create_small_rackknob(id);
}

void UiBuilder::create_small_rackknob(const char *id, const char *label) const {
    intf->create_small_rackknob(id, label);
}

void UiBuilder::closeBox() const {
    intf->closeBox();
}

void UiBuilder::load_glade(const char *data) const {
    intf->loadRackFromGladeData(data);
}

/****************************************************************
 ** regparam
 */

static float *register_var(const char* id, const char* name, const char* tp,
			   const char* tooltip, float* var, float val,
			   float low, float up, float step, bool exp) {
    if (!name[0]) {
	assert(strrchr(id, '.'));
	name = strrchr(id, '.')+1;
    }
    int n = strlen(tp);
    if (n && tp[n-1] == 'A') {
	if (gx_gui::parameter_map.hasId(id)) {
	    gx_gui::Parameter& p = gx_gui::parameter_map[id];
#ifndef NDEBUG
	    gx_gui::FloatParameter p2(
		id, name, gx_gui::Parameter::Continuous, true,
		p.getFloat().value, val, low, up, step, true, exp);
	    gx_gui::compare_parameter("Alias Parameter", &p, &p2);
#endif
	    return &p.getFloat().value;
	}
    }
    gx_gui::Parameter *p = new gx_gui::FloatParameter(
        id, name, gx_gui::Parameter::Continuous, true, *var, val,
	low, up, step, true, exp);
    if (tooltip && tooltip[0]) {
        p->set_desc(tooltip);
    }
    gx_gui::parameter_map.insert(p);
    return var;
}

static void register_enum_var(
    const char *id, const char* name, const char* tp,
    const char* tooltip, const value_pair* values,
    float *var, float val, float low, float up, float step, bool exp) {
    if (!name[0]) {
        assert(strrchr(id, '.'));
        name = strrchr(id, '.')+1;
    }
    assert(low == 0.0 && step == 1.0);
    gx_gui::FloatEnumParameter *p = new gx_gui::FloatEnumParameter(
        id, name, values, true, *var,
        static_cast<int>(round(val)), true, exp); // false == no_midi_var
    assert(up == p->upper); // calculated by constructor
    gx_gui::parameter_map.insert(p);
}

static void register_uenum_var(
    const char *id, const char* name, const char* tp,
    const char* tooltip, const value_pair* values,
    unsigned int *var, unsigned int std, bool exp) {
    if (!name[0]) {
        assert(strrchr(id, '.'));
        name = strrchr(id, '.')+1;
    }
    gx_gui::UEnumParameter *p = new gx_gui::UEnumParameter(
        id, name, values, true, *var, std, true, exp);
    gx_gui::parameter_map.insert(p);
}

float *ParamReg::registerVar(const char* id, const char* name, const char* tp,
			     const char* tooltip, float* var, float val,
			     float low, float up, float step, bool exp) const
{
    return register_var(id, name, tp, tooltip, var, val, low, up, step, exp);
}

void ParamReg::registerEnumVar(const char *id, const char* name, const char* tp,
			       const char* tooltip, const value_pair* values, float *var,
			       float val, float low, float up, float step, bool exp) const {
    register_enum_var(id, name, tp, tooltip, values, var,
		      val, low, up, step, exp);
}

void ParamReg::registerUEnumVar(const char *id, const char* name, const char* tp,
				const char* tooltip, const value_pair* values,
				unsigned int *var, unsigned int std, bool exp) const {
    register_uenum_var(id, name, tp, tooltip, values, var,
		       std, exp);
}


/****************************************************************
 ** class Plugin
 */

Plugin::Plugin(PluginDef *pl):
  box_visible(false),
  on_off(false),
  position(0),
  effect_post_pre(1),
  pdef(pl) {}

/****************************************************************
 ** class PluginList
 */

PluginList::PluginList()
{
    plugin_pos[PLUGIN_POS_START]       = -1000;
    plugin_pos[PLUGIN_POS_RACK]        = 1;
    plugin_pos[PLUGIN_POS_END]         = 1000;
    plugin_pos[PLUGIN_POS_RACK_STEREO] = 1;
};

PluginList::~PluginList()
{
    for (pluginmap::iterator p = pmap.begin(); p != pmap.end(); p++) {
	if (!(p->second->pdef->flags & PGNI_NOT_OWN)) {
	    delete p->second;
	}
    }
}

Plugin *PluginList::find_plugin(const char *id) {
    pluginmap::iterator p = pmap.find(id);
    if (p == pmap.end()) {
	return 0;
    }
    return p->second;
}

Plugin *PluginList::lookup_plugin(const char *id) {
    Plugin *p = find_plugin(id);
    if (!p) {
	gx_system::gx_print_fatal(
	    _("lookup plugin"),
	    boost::format("id not found: %1%") % id);
    }
    return p;
}

int* PluginList::pos_var(const char *id) {
    Plugin *p = find_plugin(id);
#ifndef NDEBUG
    if (!p) {
	gx_system::gx_print_error(
	    "Debug Check",
	    string("plugin position unknown id: ") + id);
	static int dummy = 0;
	return &dummy;
    }
#endif
    return &p->position;
}

bool* PluginList::on_off_var(const char *id) {
    Plugin *p = find_plugin(id);
#ifndef NDEBUG
    if (!p) {
	gx_system::gx_print_error(
	    "Debug Check",
	    string("plugin on_off unknown id: ") + id);
	static bool dummy;
	return &dummy;
    }
#endif
    return &p->on_off;
}

int PluginList::load_library(string path, PluginPos pos) {
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
	gx_system::gx_print_warning(
	    _("Plugin Loader"),
	    boost::format(_("Cannot open library: %1%")) % dlerror());
        return -1;
    }
    dlerror();    // reset errors
    plugin_inifunc get_gx_plugins = (plugin_inifunc) dlsym(handle, "get_gx_plugins");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
	gx_system::gx_print_warning(
	    _("Plugin Loader"),
	    boost::format(_("Cannot load symbol 'get_gx_plugins': %1%")) % dlsym_error);
        dlclose(handle);
        return -1;
    }
    PluginDef *p;
    int n;
    if (get_gx_plugins(&n, &p)) {
	return -1;
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
	if (!add(&p[i], pos)) {
	    cnt++;
	}
    }
    return cnt;
}

int PluginList::load_from_path(string path, PluginPos pos) {
    DIR *dp;
    struct dirent *dirp;
    if((dp = opendir(path.c_str())) == NULL) {
	gx_system::gx_print_warning(
	    _("Plugin Loader"),
	    boost::format(_("Error opening '%1%'")) % path);
        return -1;
    }
    int cnt = 0;
    while ((dirp = readdir(dp)) != NULL) {
	string n = dirp->d_name;
	if (n.size() > 3 && n.compare(n.size()-3,3,".so") == 0) {
	    int res = load_library(path+"/"+n, pos);
	    if (res > 0) {
		cnt += res;
	    }
	}
    }
    closedir(dp);
    return cnt;
}

int PluginList::check_version(PluginDef *p) {
    if ((p->version & PLUGINDEF_VERMAJOR_MASK) != (PLUGINDEF_VERSION & PLUGINDEF_VERMAJOR_MASK)) {
	gx_system::gx_print_error(
	    _("Plugin Loader"),
	    boost::format(_("Plugin '%1%' has wrong version")) % p->id);
	return -1;
    }
    return 0;
}

int PluginList::add_module(Plugin *pvars, PluginPos pos, int flags) {
    const int mode_mask = (PGN_MODE_NORMAL|PGN_MODE_BYPASS|PGN_MODE_MUTE);  // all mode bits
    PluginDef *p = pvars->pdef;
    p->flags |= flags;
    if (!(p->flags & mode_mask)) {
	p->flags |= PGN_MODE_NORMAL;
    }
    if (p->stereo_audio) {
	p->flags |= PGN_STEREO;
    }
    if (p->load_ui) {
	p->flags |= PGN_GUI;
    }
    int ipos = pos;
    if (ipos == PLUGIN_POS_RACK) {
	p->flags |= PGNI_DYN_POSITION;
	if (p->flags & PGN_STEREO) {
	    ipos = PLUGIN_POS_RACK_STEREO;
	}
    }
    if (!(p->flags & (PGN_GUI|PGN_ALTERNATIVE))) {
	// otherwise would be always off
	pvars->on_off = true;
    }
    pvars->position = plugin_pos[ipos];
    if (p->flags & PGN_POST) {
	pvars->effect_post_pre = 0;
    }
    pair<pluginmap::iterator,bool> ret = pmap.insert(map_pair(p->id, pvars));
    if (!ret.second) {
	gx_system::gx_print_error(
	    _("Plugin Loader"),
	    boost::format(_("Plugin '%1%' already exists: skipped")) % p->id);
	return -1;
    }
    if (!(p->flags & PGN_ALTERNATIVE)) {
	// normal case: position will not be set by ModuleSelector
	plugin_pos[ipos]++;
    }
    return 0;
}

int PluginList::add(Plugin *pvars, PluginPos pos, int flags) {
    if (check_version(pvars->pdef) != 0) {
	return -1;
    }
    return add_module(pvars, pos, flags|PGNI_NOT_OWN);
}

int PluginList::add(PluginDef *p, PluginPos pos, int flags) {
    if (check_version(p) != 0) {
	return -1;
    }
    Plugin *pl = new Plugin(p);
    int ret = add_module(pl, pos, flags);
    if (ret != 0) {
	delete pl;
    }
    return ret;
}

int PluginList::add(PluginDef **p, PluginPos pos, int flags) {
    int count = 0;
    while (*p) {
        if (add(*p++, pos, flags) == 0) {
	    count++;
	}
    }
    return count;
}

static const char* tr_name(const char *name) {
    if (name && name[0]) {
	return gettext(name);
    }
    return "";
}

void PluginList::registerParameter(gx_gui::ParameterGroups& groups) {
    for (pluginmap::iterator p = pmap.begin(); p != pmap.end(); p++) {
	PluginDef *pd = p->second->pdef;
	groups.insert(pd->id, tr_name(pd->name));
	const char **gp = pd->groups;
	if (gp) {
	    while (*gp) {
		string id = *gp++;
		const char *name = *gp++;
		if (!name) {
		    break;
		}
		if (id[0] == '.') {
		    id = id.substr(1);
		} else {
		    id = string(pd->id) + "." + id;
		}
		groups.insert(id, tr_name(name));
	    }
	}
    }
    for (pluginmap::iterator p = pmap.begin(); p != pmap.end(); p++) {
	Plugin *pl = p->second;
	PluginDef *pd = pl->pdef;
	if (pd->load_ui || (pd->flags & PGN_GUI)) {
	    string s = pd->id;
	    gx_gui::registerParam((s+".on_off").c_str(),N_("on/off"), &(pl->on_off), 0);
	    if (pd->flags & PGNI_DYN_POSITION) {
		// PLUGIN_POS_RACK .. PLUGIN_POS_POST_START-1
		gx_gui::registerNonMidiParam((s+".dialog").c_str(), &(pl->box_visible), false);
		gx_gui::registerNonMidiParam((s+".position").c_str(), &(pl->position), true,
					     pl->position, 1, 999);
		if (pd->mono_audio || (pd->flags & PGN_POST_PRE)) {
		    if (pd->flags & PGN_PRE) {
			pl->effect_post_pre = 1;
		    } else if (pd->flags & PGN_POST) {
			pl->effect_post_pre = 0;
		    } else {
			static const value_pair post_pre[] = {{N_("post")}, {N_("pre")}, {0}};
			gx_gui::registerUEnumParam((s+".pp").c_str(), "select", post_pre,
						   &(pl->effect_post_pre), 0);
		    }
		}
	    }
	}
	if (pd->register_params) {
	    pd->register_params(ParamReg(pd));
	}
    }
}

void PluginList::append_rack(gx_gui::GxMainInterface *ui) {
    for (pluginmap::iterator p = pmap.begin(); p != pmap.end(); p++) {
	PluginDef *pd = p->second->pdef;
	if (!pd->load_ui) {
	    continue;
	}
	string s = pd->id;
	string id_on_off = s+".on_off";
	string id_dialog = s+".dialog";
	if (pd->flags & PGN_STEREO) {
	    ui->openStereoRackBox(tr_name(pd->name), &(p->second->position), id_on_off.c_str(), id_dialog.c_str());
	    pd->load_ui(UiBuilder(ui,p->second->pdef));
	    ui->closeStereoRackBox();
	} else {
	    string id_pre_post = s+".pp";
	    ui->openMonoRackBox(tr_name(pd->name), &(p->second->position), id_on_off.c_str(), id_pre_post.c_str(), id_dialog.c_str());
	    pd->load_ui(UiBuilder(ui,p->second->pdef));
	    ui->closeMonoRackBox();
	}
    }
}

static bool plugin_order(Plugin* p1, Plugin* p2) {
    return p1->position_weight() < p2->position_weight();
}

void PluginList::ordered_mono_list(list<Plugin*>& mono, int mode) {
    mono.clear();
    for (pluginmap::iterator p = pmap.begin(); p != pmap.end(); p++) {
	Plugin *pl = p->second;
	if (pl->on_off && pl->pdef->mono_audio && (pl->pdef->flags & mode)) {
	    mono.push_back(pl);
	}
    }
    mono.sort(plugin_order);
}

void PluginList::ordered_stereo_list(list<Plugin*>& stereo, int mode) {
    stereo.clear();
    for (pluginmap::iterator p = pmap.begin(); p != pmap.end(); p++) {
	Plugin *pl = p->second;
	if (pl->on_off && pl->pdef->stereo_audio && (pl->pdef->flags & mode)) {
	    stereo.push_back(pl);
	}
    }
    stereo.sort(plugin_order);
}

void PluginList::set_samplerate(int samplerate) {
    for (pluginmap::iterator p = pmap.begin(); p != pmap.end(); p++) {
	inifunc f = p->second->pdef->set_samplerate;
	if (f) {
	    f(samplerate, p->second->pdef);
	}
    }
}

#ifndef NDEBUG
void PluginList::printlist(bool order) {
    list<Plugin*> pl_mono, pl_stereo;
    for (pluginmap::iterator p = pmap.begin(); p != pmap.end(); p++) {
	if (p->second->pdef->flags & PGN_STEREO) {
	    pl_stereo.push_back(p->second);
	} else {
	    pl_mono.push_back(p->second);
	}
    }
    if (order) {
	pl_mono.sort(plugin_order);
	pl_stereo.sort(plugin_order);
    }
    ::printlist("Plugin Map", pl_mono);
    ::printlist(0, pl_stereo, false);
}

void printlist(const char *title, const list<Plugin*>& modules, bool header) {
    if (!getenv("GUITARIX_MODULE_DEBUG")) {
	return;
    }
    const char *fmth = "%-25s %5s %5s %3s %2s %3s %8s\n";
    const char *fmtl = "%-25s %5d %5d %3d %2d %3d %8s\n";
    static int cnt = 0;
    if (header) {
	printf("%d %s:\n", ++cnt, title);
	printf(fmth, "id","wght","pos","pre","on","vis","channels");
    } else {
	printf("\n");
    }
    for (list<Plugin*>::const_iterator i = modules.begin(); i != modules.end(); i++) {
	Plugin *p = *i;
	PluginDef *pd = p->pdef;
	const char *c = "-";
	if (pd->mono_audio) {
	    c = "mono";
	} else if (pd->stereo_audio) {
	    c = "stereo";
	}
	printf(fmtl, pd->id, p->position_weight(), p->position, p->effect_post_pre,
	       p->on_off,p->box_visible, c);
    }
}
#endif

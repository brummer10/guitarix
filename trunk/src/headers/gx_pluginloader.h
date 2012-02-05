/*
 * Copyright (C) 2011 Hermann Meyer, James Warden, Andreas Degert, Pete Shorthose
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

// utility class
// FIXME should be moved somewhere else
struct stringcomp {
    inline bool operator() (const char* lhs, const char* rhs) const {
	return strcmp(lhs, rhs) < 0;
    }
};

namespace gx_engine {

/****************************************************************
 ** class Plugin
 ** Defines audio processing module and variables for
 ** user interface
*/

enum {			       // additional flags for PluginDef (used internally)
    PGNI_DYN_POSITION = 0x1000, // plugin is part of dynamically ordered rack
    PGNI_NOT_OWN      = 0x2000,	// not owned by PluginList
};

class Plugin {
public:
    bool box_visible;		// In Rack: UI Interface Box visible
    bool plug_visible;		// In Box: UI Interface Box visible
    bool on_off;		// Audio Processing
    int position;		// Position in Rack / Audio Processing Chain
    unsigned int effect_post_pre; // pre/post amp position (post = 0)
    PluginDef *pdef;
    enum { POST_WEIGHT = 2000 };
    inline int position_weight() { return effect_post_pre ? position : position + POST_WEIGHT; }
    Plugin(PluginDef *pl=0);
};

/****************************************************************
 ** class UiBuilderBase
 */

class UiBuilderBase: public UiBuilder {
public:
    virtual void load(Plugin *p) = 0;
};

/****************************************************************
 ** class PluginList
 ** container of plugins for all processing chains
 */

enum PluginPos { // where to add a plugin (per processing chain)
    PLUGIN_POS_START,
    PLUGIN_POS_RACK,
    PLUGIN_POS_END		// keep last one
};

class EngineControl;

typedef PluginDef *(*plugindef_creator)();

class PluginList {
public:
    typedef pair<const char*, Plugin*> map_pair;
    typedef map<const char*, Plugin*, stringcomp> pluginmap;
private:
    enum PluginPosInternal {
	PLUGIN_POS_RACK_STEREO = PLUGIN_POS_END+1,
	PLUGIN_POS_COUNT		// keep last one
    };
    pluginmap pmap;
    EngineControl& seq;
    gx_ui::GxUI& ui;
    list<gx_ui::GxUiItem*> rackchanger;
    int plugin_pos[PLUGIN_POS_COUNT];
    Plugin *find_plugin(const char *id) const;
    int add_module(Plugin *pl, PluginPos pos, int flags);
public:
    class iterator;
    PluginList(gx_ui::GxUI& ui, EngineControl& seq);
    ~PluginList();
    Plugin *lookup_plugin(const char *id) const;
    void set_samplerate(int samplerate); // call set_samplerate of all plugins
    int* pos_var(const char *id);     // return the position of the plugin
    bool* on_off_var(const char *id); // return the on/off switch variable of the plugin
    int load_from_path(const string& path, PluginPos pos = PLUGIN_POS_RACK);
    int load_library(const string& path, PluginPos pos = PLUGIN_POS_RACK);
    int add(Plugin *pl, PluginPos pos, int flags);
    int add(PluginDef *p, PluginPos pos = PLUGIN_POS_RACK, int flags=0);
    int add(PluginDef **p, PluginPos pos = PLUGIN_POS_RACK, int flags=0);
    int add(plugindef_creator *p, PluginPos pos = PLUGIN_POS_RACK, int flags=0);
    int check_version(PluginDef *p);
    void registerParameter(gx_engine::ParamMap& param, gx_engine::ParameterGroups& groups);
    void append_rack(UiBuilderBase& ui);
    void ordered_mono_list(list<Plugin*>& mono, int mode);
    void ordered_stereo_list(list<Plugin*>& stereo, int mode);
#ifndef NDEBUG
    void printlist(bool ordered = true);
#endif
    template<class T> friend class RackChangerUiItem;
};

#ifndef NDEBUG
void printlist(const char *title, const list<Plugin*>& modules, bool header=true);
#else 
inline void printlist(const char *, const list<Plugin*>&, bool=true) {}
#endif

} // !namespace gx_engine

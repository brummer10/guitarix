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

class EngineControl;

/****************************************************************
 ** class Plugin
 ** Defines audio processing module and variables for
 ** user interface
*/

enum {			       // additional flags for PluginDef (used internally)
    PGNI_DYN_POSITION = 0x10000, // plugin is part of dynamically ordered rack
    PGNI_NOT_OWN      = 0x20000, // not owned by PluginList
    PGNI_UI_REG       = 0x40000, // Plugin registered in user interface
};

class Plugin {
private:
    PluginDef *pdef;
    bool box_visible;		// In Rack: UI Interface Box visible
    bool plug_visible;		// In Box: UI Interface Box visible
    bool on_off;		// Audio Processing
    int position;		// Position in Rack / Audio Processing Chain
    int effect_post_pre; // pre/post amp position (post = 0)
public:
    std::string id_box_visible;
    std::string id_plug_visible;
    std::string id_on_off;
    std::string id_position;
    std::string id_effect_post_pre;
public:
    PluginDef *get_pdef() { return pdef; }
    void set_pdef(PluginDef *p) { pdef = p; }
    enum { POST_WEIGHT = 2000 };
    inline int position_weight() { return effect_post_pre ? position : position + POST_WEIGHT; }
    Plugin(PluginDef *pl=0);
    Plugin(gx_system::JsonParser& jp);
    void writeJSON(gx_system::JsonWriter& jw);
    bool get_box_visible() const { return box_visible; }
    bool get_plug_visible() const { return plug_visible; }
    bool get_on_off() const { return on_off; }
    int get_position() const { return position; }
    int get_effect_post_pre() const { return effect_post_pre; }
    void register_vars(ParamMap& param, EngineControl& seq);
    void copy_position(const Plugin& plugin, ParamMap& param);
    friend class PluginList;
    friend void printlist(const char *title, const list<Plugin*>& modules, bool header);
};

/****************************************************************
 ** class UiBuilderBase
 */

class UiBuilderBase: public UiBuilder {
public:
    virtual bool load(Plugin *p) = 0;
};

/****************************************************************
 ** class ParamRegImpl
 */

class ParamRegImpl: public ParamReg {
private:
    static ParamMap *pmap;
    static float *registerVar_(const char* id, const char* name, const char* tp,
			       const char* tooltip, float* var, float val,
			       float low, float up, float step);
    static void registerBoolVar_(const char* id, const char* name, const char* tp,
				 const char* tooltip, bool* var, bool val);
    static void registerNonMidiVar_(const char * id, bool*var, bool preset, bool nosave);
    static void registerEnumVar_(const char *id, const char* name, const char* tp,
				 const char* tooltip, const value_pair* values, float *var, float val,
				 float low, float up, float step);
    static void registerIEnumVar_(const char *id, const char* name, const char* tp,
				  const char* tooltip, const value_pair* values, int *var, int val);
public:
    ParamRegImpl(ParamMap* pm);
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

typedef PluginDef *(*plugindef_creator)();

class PluginListBase {
public:
    typedef pair<const char*, Plugin*> map_pair;
    typedef map<const char*, Plugin*, stringcomp> pluginmap;
protected:
    enum PluginPosInternal {
	PLUGIN_POS_RACK_STEREO = PLUGIN_POS_END+1,
	PLUGIN_POS_COUNT		// keep last one
    };
    pluginmap pmap;
public:
    PluginListBase();
    ~PluginListBase();
    Plugin *find_plugin(const char *id) const;
    Plugin *lookup_plugin(const char *id) const;
    void append_rack(UiBuilderBase& ui);
    void writeJSON(gx_system::JsonWriter& jw);
    void readJSON(gx_system::JsonParser& jp);
    pluginmap::iterator begin() { return pmap.begin(); }
    pluginmap::iterator end() { return pmap.end(); }
};

class PluginList: public PluginListBase {
    EngineControl& seq;
    int plugin_pos[PLUGIN_POS_COUNT];
    int add_module(Plugin *pl, PluginPos pos, int flags);
public:
    PluginList(EngineControl& seq);
    ~PluginList();
    void set_samplerate(int samplerate); // call set_samplerate of all plugins
    int load_from_path(const string& path, PluginPos pos = PLUGIN_POS_RACK);
    int load_library(const string& path, PluginPos pos = PLUGIN_POS_RACK);
    int add(Plugin *pl, PluginPos pos, int flags);
    int add(PluginDef *p, PluginPos pos = PLUGIN_POS_RACK, int flags=0);
    int add(PluginDef **p, PluginPos pos = PLUGIN_POS_RACK, int flags=0);
    int add(plugindef_creator *p, PluginPos pos = PLUGIN_POS_RACK, int flags=0);
    void delete_module(Plugin *pl, ParamMap& param, ParameterGroups& groups);
    int check_version(PluginDef *p);
    void registerGroup(PluginDef *pd, ParameterGroups& groups);
    void registerParameter(Plugin *pl, ParamMap& param, ParamRegImpl& preg);
    void registerPlugin(Plugin *pl, ParamMap& param, ParameterGroups& groups);
    void unregisterGroup(PluginDef *pd, ParameterGroups& groups);
    void unregisterParameter(Plugin *pl, ParamMap& param);
    void unregisterPlugin(Plugin *pl, ParamMap& param, ParameterGroups& groups);
    void registerAllPlugins(ParamMap& param, ParameterGroups& groups);
    void ordered_mono_list(list<Plugin*>& mono, int mode);
    void ordered_stereo_list(list<Plugin*>& stereo, int mode);
    void ordered_list(list<Plugin*>& l, bool stereo, int flagmask, int flagvalue);
#ifndef NDEBUG
    void printlist(bool ordered = true);
#endif
};

#ifndef NDEBUG
void printlist(const char *title, const list<Plugin*>& modules, bool header=true);
#else 
inline void printlist(const char *, const list<Plugin*>&, bool=true) {}
#endif

} // !namespace gx_engine

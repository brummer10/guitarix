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
    PGNI_NEED_UPDATE  = 0x80000, // Plugin needs update
};

class Plugin {
private:
    PluginDef *pdef;
    BoolParameter *p_box_visible; // In Rack: UI Interface Box visible
    BoolParameter *p_plug_visible; // In Box: UI Interface Box visible
    BoolParameter *p_on_off;	   // Audio Processing
    IntParameter  *p_position; // Position in Rack / Audio Processing Chain
    IntParameter  *p_effect_post_pre; // pre/post amp position (post = 0)
    int pos_tmp;
public:
    PluginDef *get_pdef() { return pdef; }
    void set_pdef(PluginDef *p) { pdef = p; }
    enum { POST_WEIGHT = 2000 };
    Plugin(PluginDef *pl=0);
    Plugin(gx_system::JsonParser& jp, ParamMap& pmap);
    void writeJSON(gx_system::JsonWriter& jw);
    bool get_box_visible() const { return p_box_visible && p_box_visible->get_value(); }
    bool get_plug_visible() const { return p_plug_visible && p_plug_visible->get_value(); }
    bool get_on_off() const { return p_on_off->get_value(); }
    int get_position() const { return p_position->get_value(); }
    int get_effect_post_pre() const { return p_effect_post_pre->get_value(); }
    void set_box_visible(bool v) const { if (p_box_visible) p_box_visible->set(v); }
    void set_plug_visible(bool v) const { if (p_plug_visible) p_plug_visible->set(v); }
    void set_on_off(bool v) const { p_on_off->set(v); }
    void set_position(int v) const { p_position->set(v); }
    void set_effect_post_pre(int v) const { p_effect_post_pre->set(v); }
    const std::string& id_box_visible() const { return p_box_visible->id(); }
    const std::string& id_plug_visible() const { return p_plug_visible->id(); }
    const std::string& id_on_off() const { return p_on_off->id(); }
    const std::string& id_position() const { return p_position->id(); }
    const std::string& id_effect_post_pre() const { return p_effect_post_pre->id(); }
    inline int position_weight() { return get_effect_post_pre() ? get_position() : get_position() + POST_WEIGHT; }
    void register_vars(ParamMap& param, EngineControl& seq);
    void copy_position(const Plugin& plugin);
    friend class PluginListBase;
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
    static void registerNonMidiFloatVar_(const char * id, float *var, bool preset, bool nosave,
              float val, float low, float up, float step);
    static float *registerNonMidiSharedVar_(const char * id, float *var, bool preset, bool nosave,
              float val, float low, float up, float step);
    static void registerEnumVar_(const char *id, const char* name, const char* tp,
				 const char* tooltip, const value_pair* values, float *var, float val,
				 float low, float up, float step);
    static float *registerSharedEnumVar_(const char *id, const char* name, const char* tp,
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
    typedef pair<const std::string, Plugin*> map_pair;
    typedef map<const std::string, Plugin*> pluginmap;
protected:
    enum PluginPosInternal {
	PLUGIN_POS_RACK_STEREO = PLUGIN_POS_END+1,
	PLUGIN_POS_COUNT		// keep last one
    };
    pluginmap pmap;
    sigc::signal<void,const char*,bool> insert_remove;
public:
    PluginListBase();
    ~PluginListBase();
    void cleanup();
    Plugin *find_plugin(const std::string& id) const;
    Plugin *lookup_plugin(const std::string& id) const;
    void append_rack(UiBuilderBase& ui);
    void writeJSON(gx_system::JsonWriter& jw);
    void readJSON(gx_system::JsonParser& jp, ParamMap& pmap);
    pluginmap::iterator begin() { return pmap.begin(); }
    pluginmap::iterator end() { return pmap.end(); }
    int insert_plugin(Plugin *pvars);
    void update_plugin(Plugin *pvars);
    void delete_module(Plugin *pl);
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
    Plugin *add(PluginDef *p, PluginPos pos = PLUGIN_POS_RACK, int flags=0);
    int add(PluginDef **p, PluginPos pos = PLUGIN_POS_RACK, int flags=0);
    int add(plugindef_creator *p, PluginPos pos = PLUGIN_POS_RACK, int flags=0);
    int check_version(PluginDef *p);
    void registerGroup(PluginDef *pd, ParameterGroups& groups);
    void registerParameter(Plugin *pl, ParamMap& param, ParamRegImpl& preg);
    void registerPlugin(Plugin *pl, ParamMap& param, ParameterGroups& groups);
    void unregisterGroup(PluginDef *pd, ParameterGroups& groups);
    void unregisterParameter(Plugin *pl, ParamMap& param);
    void rescueParameter(Plugin *pl, ParamMap& param);
    void unregisterPlugin(Plugin *pl, ParamMap& param, ParameterGroups& groups);
    void registerAllPlugins(ParamMap& param, ParameterGroups& groups);
    void ordered_mono_list(list<Plugin*>& mono, int mode);
    void ordered_stereo_list(list<Plugin*>& stereo, int mode);
    void ordered_list(list<Plugin*>& l, bool stereo, int flagmask, int flagvalue);
    sigc::signal<void,const char*,bool>& signal_insert_remove() { return insert_remove; }
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

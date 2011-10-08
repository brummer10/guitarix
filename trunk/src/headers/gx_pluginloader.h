#include "gx_plugin.h"
#include <string.h>

// utility class
// FIXME should be moved somewhere else
struct stringcomp {
    inline bool operator() (const char* lhs, const char* rhs) const {
	return strcmp(lhs, rhs) < 0;
    }
};

/****************************************************************
 ** class AbstractModuleSelector
 ** does not really belong here, but must be included before
 ** gx_engine.h and gx_internal_plugins.h
 */

class ModuleSelector {
public:
    virtual ~ModuleSelector() {}
    virtual void set_module() = 0;
};


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
    bool on_off;		// Audio Processing
    int position;		// Position in Rack / Audio Processing Chain
    unsigned int effect_post_pre; // pre/post amp position (post = 0)
    PluginDef *pdef;
    enum { POST_WEIGHT = 2000 };
    inline int position_weight() { return effect_post_pre ? position : position + POST_WEIGHT; }
    Plugin(PluginDef *pl=0);
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
    int plugin_pos[PLUGIN_POS_COUNT];
    Plugin *find_plugin(const char *id);
    int add_module(Plugin *pl, PluginPos pos, int flags);
public:
    class iterator;
    PluginList();
    ~PluginList();
    Plugin *lookup_plugin(const char *id);
    void set_samplerate(int samplerate); // call set_samplerate of all plugins
    int* pos_var(const char *id);     // return the position of the plugin
    bool* on_off_var(const char *id); // return the on/off switch variable of the plugin
    int load_from_path(string path, PluginPos pos = PLUGIN_POS_RACK);
    int load_library(string path, PluginPos pos = PLUGIN_POS_RACK);
    int add(Plugin *pl, PluginPos pos, int flags);
    int add(PluginDef *p, PluginPos pos = PLUGIN_POS_RACK, int flags=0);
    int add(PluginDef **p, PluginPos pos = PLUGIN_POS_RACK, int flags=0);
    int check_version(PluginDef *p);
    void registerParameter(gx_gui::ParameterGroups& groups);
    void append_rack(gx_gui::GxMainInterface *ui);
    void ordered_mono_list(list<Plugin*>& mono, int mode);
    void ordered_stereo_list(list<Plugin*>& stereo, int mode);
#ifndef NDEBUG
    void printlist(bool ordered = true);
#endif
};

PluginList& get_pluginlist(); // return the global PluginList object

#ifndef NDEBUG
void printlist(const char *title, const list<Plugin*>& modules, bool header=true);
#else 
inline void printlist(const char *, const list<Plugin*>&, bool=true) {}
#endif

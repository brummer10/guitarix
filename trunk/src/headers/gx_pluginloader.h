#include "gx_plugin.h"

struct Plugin {
    bool box_visible;
    bool on_off;
    float position; //FIXME: int
    unsigned int effect_post_pre;
    plugindef *plugin;
};

class PluginList {
private:
    typedef list<Plugin*> pluginlist;
    pluginlist plist;
public:
    PluginList();
    ~PluginList();
    Plugin *find_plugin(const char *name);
    int load_from_path(string path);
    int load_library(string path);
    int add(plugindef *p);
    void registerParameter(gx_gui::ParameterGroups& groups, int pos_offset);
    void append_rack(gx_gui::GxMainInterface *ui);
    void append_module(gx_engine::ModulPointer* modulpointer, int m, unsigned chain);
};

PluginList& get_pluginlist();

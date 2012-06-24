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

#include <ladspa.h>

namespace ladspa {

/****************************************************************
 ** PortDesc
 */

enum DisplayType {
    tp_scale, tp_scale_log, tp_toggle, tp_enum, tp_display, tp_display_toggle, tp_none, tp_int,
};

class ChangeableValues {
public:
    enum { name_set = 0x01, dflt_set = 0x02, low_set = 0x04, up_set = 0x08, tp_set = 0x10, newrow_set = 0x20 };
private:
    Glib::ustring name;
    float dflt;
    float low;
    float up;
    DisplayType tp;
    std::map<int, Glib::ustring> enumdict;
    bool newrow;
    int set_flags;
    inline void sf(int f) { set_flags |= f; }
    friend bool operator!=(const ChangeableValues& v1, const ChangeableValues& v2);
public:
    ChangeableValues(): name(), dflt(), low(), up(), tp(tp_scale), enumdict(), newrow(), set_flags(0) {}
    int get_excl_flags(DisplayType tp) const;
    bool has_settings(DisplayType tp) const;
    inline bool is_set(int f) const { return set_flags & f; }
    inline void unset(int f) { set_flags &= ~f; }
    inline void set_name(const Glib::ustring& nm) { name = nm; sf(name_set); }
    inline void set_dflt(float v) { dflt = v; sf(dflt_set); }
    inline void set_low(float v) { low = v; sf(low_set); }
    inline void set_up(float v) { up = v; sf(up_set); }
    inline void set_tp(DisplayType v) { tp = v; sf(tp_set); }
    inline void set_newrow(bool v) { newrow = v; sf(newrow_set); }
    inline const Glib::ustring& get_name() { return name; }
    inline float get_dflt() { return dflt; }
    inline float get_low() { return low; }
    inline float get_up() { return up; }
    inline DisplayType get_tp() { return tp; }
    inline bool get_newrow() { return newrow; }
    inline bool has_enumkey(int k) { return enumdict.find(k) != enumdict.end(); }
    void set_enumvalue(int k, const Glib::ustring& v) { enumdict[k] = v; }
    inline std::map<int, Glib::ustring>::iterator find_enum(int k) { return enumdict.find(k); }
    inline void erase_enum(int k) { enumdict.erase(enumdict.find(k)); }
    inline std::map<int, Glib::ustring>::iterator enum_end() { return enumdict.end(); }
};

enum step_mode {
    stp_coarse,
    stp_normal,
    stp_fine,
};

class PortDesc {
private:
public:
    const int idx;
    int pos;
    const bool is_output;
    const LADSPA_PortRangeHintDescriptor hint_desc;
    bool fake_low;
    bool fake_up;
    bool fake_dflt;
    step_mode step;
    bool use_sr;
    bool has_sr;
    bool has_caption;
    ChangeableValues factory;
    ChangeableValues user;
    void set_range_default(const LADSPA_PortRangeHint& h, ChangeableValues& store);
    void set_default_value(const LADSPA_PortRangeHint& h, ChangeableValues& store);
    void set_tp_default(const LADSPA_PortRangeHint& h, ChangeableValues& store);
    float calc_step();
    void set_default(float value, Glib::ustring label);
    void output(gx_system::JsonWriter& jw);
    friend bool cmp_ctrl_ports(const PortDesc *a, const PortDesc *b);
public:
    PortDesc(int idx_, int pos_, bool is_output_, Glib::ustring name, const LADSPA_PortRangeHint& hint);
    void reset();
    void fixup(bool newrow);
    bool check_changed(const PortDesc& vp) const;
    Glib::ustring get_enum(int idx);
    inline DisplayType get_tp() { return user.is_set(ChangeableValues::tp_set) ? user.get_tp() : factory.get_tp(); }
    inline float get_low() { return user.is_set(ChangeableValues::low_set) ? user.get_low() : factory.get_low(); }
    inline float get_up() { return user.is_set(ChangeableValues::up_set) ? user.get_up() : factory.get_up(); }
    inline float get_dflt() { return user.is_set(ChangeableValues::dflt_set) ? user.get_dflt() : factory.get_dflt(); }
    inline bool get_newrow() { return user.is_set(ChangeableValues::newrow_set) ? user.get_newrow() : factory.get_newrow(); }
    const Glib::ustring& get_name() { return user.is_set(ChangeableValues::name_set) ? user.get_name() : factory.get_name(); }
    inline int get_pos() { return pos; }
    void set_low(float v);
    void set_up(float v);
    void set_dflt(float v);
    void set_tp(DisplayType v);
    void set_newrow(bool v);
    bool has_settings();
    bool enumkey_changed(int k) { return user.has_enumkey(k); }
    bool is_set(int f) { return user.is_set(f); }
    void set_state(gx_system::JsonParser& jp, int version);
};


/****************************************************************
 ** class PluginDesc
 */

class PluginDesc {
private:
public:
    unsigned long UniqueID;
    Glib::ustring Label;
    Glib::ustring Name;
    Glib::ustring shortname;
    Glib::ustring Maker;
    int MasterIdx;
    Glib::ustring MasterLabel;
    int tp;
    std::vector<PortDesc*> ctrl_ports;
    std::string path;
    int index;
    Glib::ustring category;
    Glib::ustring deduced_category;
    int quirks;
    int quirks_default;
    std::string ladspa_category;
    bool active;
    bool active_set;
    bool has_settings;
    int add_wet_dry;
    PluginDesc *old;
    int quirks_get();
    void reset();
    bool check_changed();
    bool _i_check_has_settings();
    void check_has_settings();
    int set_active(bool v);
    void fixup();
    void set_add_wet_dry_controller(bool v);
    void copy_ports(PluginDesc *p);
    void set_category(const std::vector<Glib::ustring>& s);
    void set_default(int idx, float value, const Glib::ustring& label);
    void set_state(const Glib::ustring& fname);
public:
    PluginDesc(const LADSPA_Descriptor& desc, int tp_, std::vector<PortDesc*>& ctrl_ports_, const std::string path_, int index_);
    ~PluginDesc();
    void output_entry(gx_system::JsonWriter& jw);
    void output(gx_system::JsonWriter& jw);
};

/****************************************************************
 ** class PluginDisplay
 */

class EnumListStore: public Gtk::ListStore {
public:
    class Columns: public Gtk::TreeModel::ColumnRecord {
    public:
	Gtk::TreeModelColumn<int> value;
	Gtk::TreeModelColumn<Glib::ustring> label;
	Gtk::TreeModelColumn<PortDesc*> port;
	Columns() { add(value); add(label); add(port); }
    } col;
    EnumListStore(): Gtk::ListStore(Columns()) {}
};

class PortListStore: public Gtk::ListStore {
public:
    class Columns: public Gtk::TreeModel::ColumnRecord {
    public:
	Gtk::TreeModelColumn<int> pos;
	Gtk::TreeModelColumn<Glib::ustring> name;
	Gtk::TreeModelColumn<Glib::ustring> dflt;
	Gtk::TreeModelColumn<Glib::ustring> low;
	Gtk::TreeModelColumn<Glib::ustring> up;
	Gtk::TreeModelColumn<Glib::ustring> step;
	Gtk::TreeModelColumn<Glib::ustring> display;
	Gtk::TreeModelColumn<Glib::RefPtr<Gtk::ListStore> > display_types;
	Gtk::TreeModelColumn<PortDesc*> port;
	Gtk::TreeModelColumn<bool> newrow;
	Gtk::TreeModelColumn<bool> use_sr;
	Gtk::TreeModelColumn<bool> has_caption;
	Columns() {
	    add(pos); add(name); add(dflt); add(low); add(up); add(step); add(display);
	    add(display_types); add(port); add(newrow); add(use_sr); add(has_caption);
	}
    } col;
    PortListStore(): Gtk::ListStore(Columns()) {}
};

class PluginListStore: public Gtk::ListStore {
public:
    class Columns: public Gtk::TreeModel::ColumnRecord {
    public:
	Gtk::TreeModelColumn<Glib::ustring> name;
	Gtk::TreeModelColumn<bool> active;
	Gtk::TreeModelColumn<PluginDesc*> pdesc;
	Columns() { add(name); add(active); add(pdesc); }
    } col;
    PluginListStore(): Gtk::ListStore(Columns()) {}
};

class MasterIdxListStore: public Gtk::ListStore {
public:
    class Columns: public Gtk::TreeModel::ColumnRecord {
    public:
	Gtk::TreeModelColumn<int> idx;
	Columns() { add(idx); }
    } col;
    MasterIdxListStore(): Gtk::ListStore(Columns()) {}
};

class PluginDisplay {
private:
    const gx_system::CmdlineOptions& options;
    std::vector<PluginDesc*> pluginlist;
    PluginDesc *current_plugin;
    int old_state;
    Glib::RefPtr<gx_gui::GxBuilder> bld;
    int change_count;
    Glib::RefPtr<Gtk::ActionGroup> actiongroup;
    Glib::RefPtr<Gtk::UIManager> uimanager;
    Glib::RefPtr<EnumListStore> enum_liststore;
    Glib::RefPtr<PortListStore> port_liststore;
    Glib::RefPtr<PluginListStore> plugin_liststore;
    Glib::RefPtr<MasterIdxListStore> masteridx_liststore;
    sigc::connection on_reordered_conn;
    Glib::RefPtr<Gtk::ListStore> display_type_list;
    Glib::RefPtr<Gtk::ListStore> display_type_list_sr;
    Glib::RefPtr<Gtk::ListStore> output_type_list;
    sigc::slot<void,bool,bool> finished_callback;
    //
    Glib::RefPtr<Gtk::Action> quit_action;
    Glib::RefPtr<Gtk::Action> save_action;
    Glib::RefPtr<Gtk::Action> apply_action;
    Glib::RefPtr<Gtk::Action> select_all_action;
    Glib::RefPtr<Gtk::Action> select_none_action;
    //
    Gtk::Window *window;
    Gtk::TreeView *treeview1;
    Gtk::TreeView *treeview2;
    Gtk::TreeView *treeview3;
    Gtk::Entry *ladspa_category;
    Gtk::Entry *ladspa_maker;
    Gtk::Entry *ladspa_uniqueid;
    Gtk::Entry *search_entry;
    Gtk::ComboBox *combobox_mono_stereo;
    Gtk::ToggleButton *selected_only;
    Gtk::ToggleButton *changed_only;
    Gtk::ToggleButton *show_all;
    Gtk::Box *details_box;
    Gtk::ToggleButton *show_details;
    Gtk::Entry *plugin_name;
    Gtk::ComboBox *plugin_category;
    Gtk::ToggleButton *dry_wet_button;
    Gtk::ComboBox *plugin_quirks;
    Gtk::ComboBox *master_slider_idx;
    Gtk::Entry *master_slider_name;
    Gtk::CellRendererText *cellrenderer_master;
    Gtk::CellRendererToggle *cellrenderer_newrow;
    Gtk::CellRendererToggle *cellrenderer_caption;
    Gtk::CellRendererToggle *cellrenderer_active;
    Gtk::CellRendererText *cellrenderer_category;
    Gtk::CellRendererText *cellrenderer_quirks;
private:
    void set_title();
    void on_save();
    void on_apply();
    void on_quit();
    void on_select_all(bool v);
    void on_find();
    bool on_delete_event(GdkEventAny*);
    void on_show_details();
    void on_add_dry_wet_controller();
    void on_row_activated(const Gtk::TreePath& path, Gtk::TreeViewColumn* column);
    void on_label_edited(const Glib::ustring& path, const Glib::ustring& newtext);
    void on_parameter_selection_changed();
    void on_reordered(const Gtk::TreePath& path);
    void on_type_edited(const Glib::ustring& path, const Glib::ustring& newtext);
    void on_step_edited(const Glib::ustring& path, const Glib::ustring& newtext);
    void on_newrow_toggled(const Glib::ustring& path);
    void on_caption_toggled(const Glib::ustring& path);
    void on_name_edited(const Glib::ustring& path, const Glib::ustring& newtext);
    void on_dflt_edited(const Glib::ustring& path, const Glib::ustring& newtext);
    void on_low_edited(const Glib::ustring& path, const Glib::ustring& newtext);
    void on_up_edited(const Glib::ustring& path, const Glib::ustring& newtext);
    void on_search_entry_activate();
    void selection_changed();
    void on_active_toggled(const Glib::ustring& path);
    void on_view_changed(const Gtk::ToggleButton*);
    void display_category(const Gtk::TreeIter& it);
    void display_quirks(const Gtk::TreeIter& it);
    void on_mono_stereo_changed();
    void on_delete_changes();
    bool search_equal(const Glib::RefPtr<Gtk::TreeModel>& model, int column, const Glib::ustring& key, const Gtk::TreeIter& iter);
    void display_label(Gtk::CellRenderer *cell, const Gtk::TreeIter& it);
    void display_step(Gtk::CellRenderer *cell, const Gtk::TreeIter& it);
    void display_ladspa(Gtk::CellRenderer *cell, const Gtk::TreeIter& it);
    void display_idx(Gtk::CellRenderer *cell, const Gtk::TreeIter& it);
    void display_name(Gtk::CellRenderer *cell, const Gtk::TreeIter& it);
    void display_default(Gtk::CellRenderer *cell, const Gtk::TreeIter& it);
    void display_lower(Gtk::CellRenderer *cell, const Gtk::TreeIter& it);
    void display_upper(Gtk::CellRenderer *cell, const Gtk::TreeIter& it);
    void display_SR(Gtk::CellRenderer *cell, const Gtk::TreeIter& it);
    void display_type(Gtk::CellRenderer *cell, const Gtk::TreeIter& it);
    void display_newrow(Gtk::CellRenderer *cell, const Gtk::TreeIter& it);
    void display_caption(Gtk::CellRenderer *cell, const Gtk::TreeIter& it);
    bool check_for_changes();
    int ask_discard();
    void save_current();
    void load();
    bool do_save();
    void set_old_state(PluginDesc *p);
    void display_master_idx(const Gtk::TreeIter& it);
    void set_master_text();
    std::string get_config_filename() { return options.get_user_filepath("ladspa_defs.js"); }
    void load_ladspalist(std::vector<unsigned long>& old_not_found, std::vector<PluginDesc*>& l);
    std::string get_ladspa_plugin_config(unsigned long UniqueID);
public:
    PluginDisplay(const gx_system::CmdlineOptions& options, Glib::RefPtr<Gdk::Pixbuf> icon, sigc::slot<void,bool,bool> finished_callback);
    ~PluginDisplay();
    bool check_exit();
    void present() { window->present(); }
};

} // namespace ladspa

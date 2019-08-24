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
    gx_engine::GxMachineBase& machine;
    LadspaPluginList pluginlist;
    std::vector<PluginDesc*> needs_reload;
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
    Gtk::ToggleButton *ladspa_only;
    Gtk::ToggleButton *lv2_only;
    Gtk::ToggleButton *show_all;
    Gtk::Box *details_box;
    Gtk::ToggleButton *show_details;
    Gtk::Entry *plugin_name;
    Gtk::ComboBox *plugin_category;
    Gtk::ToggleButton *dry_wet_button;
    Gtk::ToggleButton *stereo_to_mono_button;
    Gtk::ComboBox *plugin_quirks;
    Gtk::ComboBox *master_slider_idx;
    Gtk::Entry *master_slider_name;
    Glib::RefPtr<Gtk::CellRendererText> cellrenderer_master;
    Glib::RefPtr<Gtk::CellRendererToggle> cellrenderer_newrow;
    Glib::RefPtr<Gtk::CellRendererToggle> cellrenderer_caption;
    Glib::RefPtr<Gtk::CellRendererToggle> cellrenderer_active;
    Glib::RefPtr<Gtk::CellRendererText> cellrenderer_category;
    Glib::RefPtr<Gtk::CellRendererText> cellrenderer_quirks;
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
    void on_stereo_to_mono_controller();
    void on_stereo_to_mono();
    bool reload_plug;
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
    void load_ladspalist(std::vector<unsigned long>& old_not_found, std::vector<PluginDesc*>& l);
public:
    PluginDisplay(gx_engine::GxMachineBase& machine, Glib::RefPtr<Gdk::Pixbuf> icon, sigc::slot<void,bool,bool> finished_callback);
    ~PluginDisplay();
    bool check_exit();
    void present() { window->present(); }
    void hide() { window->hide(); }
};

} // namespace ladspa

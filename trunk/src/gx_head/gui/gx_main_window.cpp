/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
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
 * ---------------------------------------------------------------------------
 *
 *    This is the gx_head GUI main class
 *
 * ----------------------------------------------------------------------------
 */

#include <gtkmm.h>
#include <gxwmm.h>
using namespace std;
#include <engine.h>
#include <gx_ui.h>
#include <gx_ui_builder.h>

/****************************************************************
 ** class PresetFile, PresetBanks
 */

class PresetFile {
private:
    Glib::ustring name;
    Glib::ustring path;
    int tp;
    int flags;
    std::list<Glib::ustring> settings;
public:
    typedef std::list<Glib::ustring>::iterator iterator;
    PresetFile(const Glib::ustring& name, int tp, int flags, const std::list<Glib::ustring>& settingslist);
    bool has_entry(const Glib::ustring& name) const;
    void append(const Glib::ustring& name);
    void insert_before(const Glib::ustring& nm, const Glib::ustring& newentry);
    void insert_after(const Glib::ustring& nm, const Glib::ustring& newentry);
    bool rename(const Glib::ustring& old, const Glib::ustring& newname);
    void remove(const Glib::ustring& name);
    void reorder(const std::list<Glib::ustring>& namelist);
    int get_flags() const { return flags; }
    void set_flags(int f) { flags = f; }
    int get_type() const { return tp; }
    const Glib::ustring& get_name() const { return name; }
    void set_name(Glib::ustring n) { name = n; }
    iterator begin() { return settings.begin(); }
    iterator end() { return settings.end(); }
};

class PresetBanks {
private:
    std::list<PresetFile*> banklist;
    void parse_factory_list(const gx_system::CmdlineOptions& options);
public:
    class iterator {
    private:
	std::list<PresetFile*>::iterator it;
    public:
	iterator(std::list<PresetFile*>::iterator i): it(i) {}
	bool operator!=(const iterator& i) const { return it != i.it; }
	iterator& operator++() { ++it; return *this; }
	PresetFile* operator->() { return *it; }
	PresetFile* operator*() { return *it; }
    };
    PresetBanks(const gx_system::CmdlineOptions&options);
    ~PresetBanks();
    PresetFile* get_file(const Glib::ustring& bank) const;
    iterator begin() { return iterator(banklist.begin()); }
    iterator end() { return iterator(banklist.end()); }
    bool remove(const Glib::ustring& bank);
    void add(PresetFile* f) { banklist.push_back(f); }
    bool has_entry(const Glib::ustring& bank) const { return get_file(bank) != 0; }
    bool rename(const Glib::ustring& oldname, const Glib::ustring& newname);
};


/****************************************************************
 ** class PresetWindow
 */

class PresetStore: public Gtk::ListStore {
public:
    class PresetModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:
	Gtk::TreeModelColumn<Glib::ustring> name;
	Gtk::TreeModelColumn< Glib::RefPtr<Gdk::Pixbuf> > edit_pb;
	Gtk::TreeModelColumn< Glib::RefPtr<Gdk::Pixbuf> > del_pb;

	PresetModelColumns() { add(name); add(edit_pb); add(del_pb); }
    } col;
public:
    PresetStore();
    virtual bool row_draggable_vfunc(const TreeModel::Path& path) const;
};

class TargetModelColumns : public Gtk::TreeModel::ColumnRecord {
public:
    Gtk::TreeModelColumn<Glib::ustring> name;
    TargetModelColumns() { add(name); }
};

class BankModelColumns : public Gtk::TreeModel::ColumnRecord {
public:
    Gtk::TreeModelColumn<Glib::ustring> name;
    Gtk::TreeModelColumn< Glib::RefPtr<Gdk::Pixbuf> > type_pb;
    Gtk::TreeModelColumn< Glib::RefPtr<Gdk::Pixbuf> > edit_pb;
    Gtk::TreeModelColumn< Glib::RefPtr<Gdk::Pixbuf> > del_pb;
    Gtk::TreeModelColumn<int> tp;
    BankModelColumns() { add(name); add(type_pb); add(edit_pb); add(del_pb); add(tp); }
};

class MyTreeView: public Gtk::TreeView {
private:
    MyTreeView(BaseObjectType* cobject): Gtk::TreeView(cobject) {}
public:
    static MyTreeView *create_from_builder(BaseObjectType* cobject) { return new MyTreeView(cobject); }
    //virtual bool on_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp);
    using Gtk::TreeView::on_drag_motion;
};

class PresetWindow {
public:
    enum { PRESET_SEP = -1, PRESET_SCRATCH = 0, PRESET_FILE = 1, PRESET_FACTORY = 2 };
private:
    Glib::RefPtr<Gtk::ActionGroup> actiongroup;
    int paned_child_height;
    bool in_edit;
    Gtk::TreeModel::iterator edit_iter;
    Glib::RefPtr<Gdk::Pixbuf> pb_edit;
    Glib::RefPtr<Gdk::Pixbuf> pb_del;
    Glib::RefPtr<Gdk::Pixbuf> pb_scratch;
    Glib::RefPtr<Gdk::Pixbuf> pb_versiondiff;
    Glib::RefPtr<Gdk::Pixbuf> pb_readonly;
    Glib::RefPtr<Gdk::Pixbuf> pb_factory;
    Glib::RefPtr<PresetStore> pstore;
    TargetModelColumns target_col;
    BankModelColumns bank_col;
    PresetBanks banks;
    sigc::connection bank_row_del_conn;
    sigc::connection preset_row_del_conn;
    int vpaned_pos;
    int vpaned_step;
    int vpaned_target;
    bool animate;
    Glib::ustring current_bank; //FIXME
    Glib::ustring current_preset; //FIXME

    //
    Gtk::Button *close_preset;
    Gtk::Button *save_preset;
    Gtk::Button *new_preset_bank;
    Gtk::ToggleButton *organize_presets;
    MyTreeView *bank_treeview;
    Gtk::CellRendererText *bank_cellrenderer;
    MyTreeView *preset_treeview;
    Gtk::CellRendererText *preset_cellrenderer;
    Gtk::ComboBox *banks_combobox;
    MyTreeView *presets_target_treeview;
    Gtk::Label *preset_title;
    Gtk::ScrolledWindow *presets_target_scrolledbox;
    Gtk::TreeViewColumn *bank_column_edit;
    Gtk::TreeViewColumn *bank_column_delete;
    Gtk::TreeViewColumn *preset_column_edit;
    Gtk::TreeViewColumn *preset_column_delete;
    Gtk::VPaned *main_vpaned;
    Gtk::ScrolledWindow *preset_scrolledbox;
    Gtk::Entry *preset_status;
private:
    void load_widget_pointers(Glib::RefPtr<gx_gui::GxBuilder> bld);
    void target_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, guint info, guint timestamp);
    bool on_target_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp);
    Glib::ustring get_combo_selection();
    void reload_combo();
    void on_preset_combo_changed();
    void reload_target();
    bool select_func(const Glib::RefPtr<Gtk::TreeModel>& model, const Gtk::TreePath& path, bool path_currently_selected);
    void text_func(Gtk::CellRenderer *cell, const Gtk::TreeModel::iterator& iter);
    void on_editing_started(const Gtk::CellEditable* edit, const Glib::ustring& path, Glib::RefPtr<Gtk::TreeModel>& model);
    bool edit_cell(Gtk::TreeModel::Path pt, Gtk::TreeViewColumn& col, Gtk::CellRenderer& cell);
    void reset_edit(Gtk::TreeViewColumn& col);
    void on_edit_canceled(Gtk::TreeViewColumn *col);
    void start_edit(const Gtk::TreeModel::Path& pt, Gtk::TreeViewColumn& col, Gtk::CellRenderer& cell);
    Gtk::TreeModel::Row get_current_bank_row();
    Glib::ustring get_current_bank();
    bool run_message_dialog(Gtk::Widget& w, const Glib::ustring& msg);
    bool on_bank_button_release(GdkEventButton *ev);
    void on_bank_edited(const Glib::ustring& path, const Glib::ustring& newtext, Gtk::TreeView* w);
    bool is_row_separator(const Glib::RefPtr<Gtk::TreeModel>& model, const Gtk::TreeModel::iterator& iter);
    void on_new_bank();
    void on_preset_save();
    bool on_bank_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp);
    void on_bank_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, guint info, guint timestamp);
    void on_bank_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp);
    void reload_presets();
    void on_bank_changed();
    void reload_banks(Glib::ustring& sel_bank);
    void set_presets();
    void on_bank_reordered(const Gtk::TreeModel::Path& path);
    bool on_preset_button_release(GdkEventButton *ev);
    bool on_preset_button_press(GdkEventButton *ev);
    void on_preset_edited(const Glib::ustring& path, const Glib::ustring& newtext);
    void on_cursor_changed();
    void on_preset_changed();
    bool on_preset_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp);
    void on_preset_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp);
    void on_preset_reordered(const Gtk::TreeModel::Path& path);
    void autosize();
    void on_organize();
    void on_presets_close();
    bool animate_preset_show();
    bool animate_preset_hide();
    void show_selected_preset();
public:
    PresetWindow(Glib::RefPtr<gx_gui::GxBuilder> bld, const gx_system::CmdlineOptions& options, Glib::RefPtr<Gtk::ActionGroup> actiongroup);
    ~PresetWindow();
    void on_preset_select(bool v);
};


/****************************************************************
 ** class Liveplay
 */

class Liveplay {
private:
    Glib::RefPtr<gx_gui::GxBuilder> bld;
    gx_preset::GxSettings& gx_settings;
    gx_ui::GxUI ui;
    bool use_composite;
    Gtk::Adjustment brightness_adj;
    Gtk::Adjustment background_adj;

    //
    Gtk::Window *window;
    Gtk::Image *bypass_image;
    Gtk::Image *mute_image;
    Gtk::Label *liveplay_preset;
    Gtk::Widget *liveplay_canvas;
    Gxw::HSlider *brightness_slider;
    Gtk::Box *brightness_box;
    Gxw::HSlider *background_slider;
    Gtk::ToggleButton *liveplay_exit;
    Gtk::Table *midictrl_table;
    Gxw::RackTuner *tuner;
private:
    void add_midi_elements(gx_engine::MidiControllerList& controller);
    bool on_delete(GdkEventAny *ev);
    void on_brightness_changed();
    void on_background_changed();
    bool transparent_expose(GdkEventExpose *event);
    bool window_expose_event(GdkEventExpose* event);
    void on_realize();
public:
    Liveplay(const gx_system::CmdlineOptions& options, gx_preset::GxSettings& gx_settings,
	     const std::string& fname, Glib::RefPtr<Gtk::ActionGroup> actiongroup);
    ~Liveplay();
    void on_live_play(Glib::RefPtr<Gtk::ToggleAction> act);
    void display_tuner(bool v);
};

/****************************************************************
 ** class PluginUI
 */

enum PluginType {
    PLUGIN_TYPE_MONO,
    PLUGIN_TYPE_STEREO,
};

class PluginUI {
public:
    gx_engine::Plugin *plugin;
    Glib::ustring fname;
    Glib::ustring tooltip;

    // data for ToolPalette entry
    Glib::RefPtr<Gdk::Pixbuf> icon;
    Gtk::ToolItemGroup *group;
    Gtk::ToolItem *toolitem;

    PluginUI(const gx_engine::PluginList& pl, const char* id_,
	     const Glib::ustring& fname_="", const Glib::ustring& tooltip_="");
    PluginType get_type() const {
	return (plugin->pdef->flags & PGN_STEREO) ? PLUGIN_TYPE_STEREO : PLUGIN_TYPE_MONO;
    }
    const char *get_id() const { return plugin->pdef->id; }
    const char *get_name() const { return plugin->pdef->name; }
};

PluginUI::PluginUI(const gx_engine::PluginList& pl, const char *name,
		   const Glib::ustring& fname_, const Glib::ustring& tooltip_)
    : plugin(pl.lookup_plugin(name)), fname(fname_), tooltip(tooltip_),
      icon(), group(), toolitem() {
}

/****************************************************************
 ** class DragIcon
 */

class DragIcon {
private:
    Gtk::Window *window;
    Glib::RefPtr<Gdk::Pixbuf> drag_icon_pixbuf;
private:
    bool icon_expose_event(GdkEventExpose *ev);
    void create_drag_icon_pixbuf(const PluginUI& plugin, Glib::RefPtr<Gdk::Colormap> rgba, gx_system::CmdlineOptions& options);
    bool window_expose_event(GdkEventExpose *event, Gtk::OffscreenWindow& w);
public:
    DragIcon(const PluginUI& plugin, Glib::RefPtr<Gdk::DragContext> context, gx_system::CmdlineOptions& options, int xoff=0);
    ~DragIcon();
};

/****************************************************************
 ** class RackBox, class MiniRackBox
 */

class MainWindow;
class MiniRackBox;

class RackBox: public Gtk::VBox {
private:
    static Glib::RefPtr<Gtk::SizeGroup> szg;
    const PluginUI& plugin;
    MainWindow& main;
    bool vis;
    bool config_mode;
    sigc::connection anim_tag;
    bool compress;
    bool delete_button;
    Gxw::PaintBox mbox;
    Glib::RefPtr<Gtk::ToggleAction> on_off_action;
    MiniRackBox* minibox;
    Gtk::Widget *fbox;
    std::string target;
    int anim_height;
    DragIcon *drag_icon;
    int target_height;
    int preset_index;
    std::vector<Glib::ustring> presets;
    Gxw::PaintBox box;
private:
    static void set_paintbox(Gxw::PaintBox& pb, PluginType tp);
    static Gtk::Widget *make_label(const PluginUI& plugin, gx_system::CmdlineOptions& options);
    static Gtk::Widget *make_bar(int left=4, int right=4, bool sens=false);
    void init_dnd();
    void enable_drag(bool v);
    bool animate_vanish();
    void on_my_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context);
    bool animate_create();
    void on_my_drag_end(const Glib::RefPtr<Gdk::DragContext>& context);
    void on_my_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp);
    void on_my_drag_data_delete(const Glib::RefPtr<Gdk::DragContext>& context);
    void vis_switch(Gtk::Widget& a, Gtk::Widget& b);
    void on_expand(bool mini);
    Gtk::Button *make_expand_button(bool expand);
    void on_preset_popup_destroy(Gtk::Menu *w);
    void preset_popup();
    Gtk::Button *make_preset_button();
    Gtk::HBox *make_full_box(gx_system::CmdlineOptions& options);
    Gtk::VBox *switcher_vbox(gx_system::CmdlineOptions& options);
    bool has_delete() const { return delete_button; }
    void on_kill();
public:
    RackBox(const PluginUI& plugin, MainWindow& main, Gtk::Widget* bare=0);
    static Gtk::Widget *create_drag_widget(const PluginUI& plugin, gx_system::CmdlineOptions& options);
    bool can_compress() { return compress; }
    friend class MiniRackBox;
    const char *get_id() const { return plugin.get_id(); }
    void set_config_mode(bool mode);
    void swtch(bool mini);
    void pack(Gtk::Widget& child);
    void animate_insert();
    static Gtk::Widget *create_icon_widget(const PluginUI& plugin, gx_system::CmdlineOptions& options);
};

class MiniRackBox: public Gtk::HBox {
private:
    static Glib::RefPtr<Gtk::SizeGroup> szg_label;
    Gtk::EventBox evbox;
    Gtk::HBox mconbox;
    Gtk::Button *mb_expand_button;
    Gtk::Widget *mb_delete_button;
    Gtk::Button *preset_button;
private:
    Gtk::Widget *make_delete_button(RackBox& rb);
public:
    MiniRackBox(RackBox& rb, const Glib::RefPtr<Gtk::Action>& action, gx_system::CmdlineOptions& options);
    void set_config_mode(bool mode);
};


/****************************************************************
 ** class RackContainer
 */

class RackContainer: public Gtk::VBox {
private:
    PluginType tp;
    MainWindow& main;
    bool config_mode;
    int in_drag;
    int child_count;
    int switch_level;
    std::vector<std::string> targets;
    sigc::connection hightlight_connection;
private:
    bool drag_highlight_expose(GdkEventExpose *event, int y0);
    void find_index(int x, int y, int* len, int *ypos);
    void on_my_remove(Gtk::Widget*);
    bool check_targets(const std::vector<std::string>& targets);
    virtual bool on_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp);
    virtual void on_drag_leave(const Glib::RefPtr<Gdk::DragContext>& context, guint timestamp);
    virtual void on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, guint info, guint timestamp);
    virtual void on_add(Widget* ch);
    void reorder(const std::string& name, int pos);
public:
    RackContainer(PluginType tp, MainWindow& main);
    Glib::ListHandle<RackBox*> get_children() {
	Glib::ListHandle<Widget*> l = Gtk::VBox::get_children();
	void *p = &l;
	return *reinterpret_cast<Glib::ListHandle<RackBox*>*>(p);
    }
    Glib::ListHandle<const RackBox*> get_children() const {
	Glib::ListHandle<const Widget*> l = Gtk::VBox::get_children();
	void *p = &l;
	return *reinterpret_cast<Glib::ListHandle<const RackBox*>*>(p);
    }
    bool check_if_animate(const RackBox& rackbox);
    void show_entries();
    void hide_entries();
    void compress_all();
    void expand_all();
    void set_config_mode(bool mode);
    bool empty() const;
    void add(RackBox& r, int pos=-1);
};


/****************************************************************
 ** class MainWindow
 */

class Freezer {
private:
    Gtk::Window *window;
    sigc::connection tag;
    int size_x;
    int size_y;
public:
    Freezer();
    ~Freezer();
    void freeze(Gtk::Window *w, int width, int height);
    void freeze_until_width_update(Gtk::Window *w, int width) { freeze(w, width, -1); }
    void freeze_and_size_request(Gtk::Window *w, int width, int height);
    bool thaw_timeout();
    void thaw();
    bool check_thaw(int width, int height);
};

class MainWindow: public sigc::trackable {
private:
    int window_height;
    Freezer freezer;
    Glib::RefPtr<gx_gui::GxBuilder> bld;
    int oldpos;
    int scrl_size_x;
    int scrl_size_y;
    RackContainer monorackcontainer;
    RackContainer stereorackcontainer;
    int pre_act;
    bool is_visible;
    DragIcon *drag_icon;
    std::map<std::string, PluginUI*> plugin_dict;
    Glib::RefPtr<Gtk::ActionGroup> actiongroup;
    Glib::RefPtr<Gtk::UIManager> uimanager;
    gx_ui::GxUI ui;
    gx_system::CmdlineOptions& options;
    gx_engine::ParamMap&  pmap;
    gx_engine::GxEngine&  engine;
    gx_jack::GxJack       jack;
    gx_preset::GxSettings gx_settings;
    PluginUI mainamp_plugin;
    Liveplay *live_play;
    PresetWindow *preset_window;

    // Widget pointers
    Gxw::PaintBox *tunerbox;
    Gtk::ScrolledWindow *vrack_scrolledbox;
    Gtk::HBox *stereorackcontainerH;
    Gtk::HBox *stereorackcontainerV;
    Gxw::PaintBox *rackcontainer;
    Gtk::ScrolledWindow *stereorackbox;
    Gtk::VBox *monocontainer;
    Gxw::PaintBox *monoampcontainer;
    Gtk::VPaned *main_vpaned;
    Gtk::HBox *amp_toplevel_box;
    Gtk::VBox *monobox;
    Gtk::VBox *upper_rackbox;
    Gtk::ScrolledWindow *preset_scrolledbox;
    Gxw::PaintBox *effects_frame_paintbox;
    Gtk::Image *status_image;
    Gtk::Image *jackd_image;
    Gtk::Image *logstate_image;
    Gtk::Window *window;
    Gtk::HBox *menubox;
    Gtk::ToggleButton *show_rack_button;
    Gtk::ToggleButton *liveplay_button;
    Gtk::ToggleButton *tuner_button;
    Gtk::ToggleButton *effects_button;
    Gtk::ToggleButton *presets_button;
    Gtk::Button *compress_button;
    Gtk::Button *expand_button;
    Gtk::ToolPalette *effects_toolpalette;
    Gxw::PaintBox *amp_background;
public:
    // ToggleActions
    Glib::RefPtr<Gtk::ToggleAction> show_plugin_bar_action;
    Glib::RefPtr<Gtk::ToggleAction> presets_action;
    Glib::RefPtr<Gtk::ToggleAction> show_rack_action;
    Glib::RefPtr<Gtk::ToggleAction> tuner_action;
    Glib::RefPtr<Gtk::Action> compress_action;
    Glib::RefPtr<Gtk::Action> expand_action;
    Glib::RefPtr<Gtk::ToggleAction> show_values_action;
    Glib::RefPtr<Gtk::ToggleAction> live_play_action;
    Gtk::RadioButtonGroup dir_group;
    Glib::RefPtr<Gtk::RadioAction> rackv_action;
    Glib::RefPtr<Gtk::RadioAction> rackh_action;
private:
    void load_widget_pointers();
    void maybe_shrink_horizontally();
    void on_show_tuner();
    bool is_variable_size();
    void maybe_change_resizable(void);
    void on_show_rack();
    void on_preset_action();
    void on_compress_all();
    void on_expand_all();
    void on_show_plugin_bar();
    void move_widget(Gtk::Widget& w, Gtk::Box& b1, Gtk::Box& b2);
    int get_dir() const;
    static void change_expand(Gtk::Widget& w, bool value);
    void on_dir_changed(Glib::RefPtr<Gtk::RadioAction> act);
    void on_configure_event(GdkEventConfigure *ev);
    void clear_box(Gtk::Container& box);
    void add_rackbox_internal(const PluginUI& plugin, Gtk::Widget *widget, bool mini=false, int pos=-1, bool animate=false, Gtk::Widget *bare=0);
    void on_show_values();
    Glib::RefPtr<Gtk::UIManager> create_menu(Glib::RefPtr<Gtk::ActionGroup>& actiongroup);
    void add_toolitem(PluginUI& pl, Gtk::ToolItemGroup *gw);
    bool on_visibility_notify(GdkEventVisibility *ev);
    void on_live_play();
    void on_ti_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context, const PluginUI& plugin);
    void on_ti_drag_end(const Glib::RefPtr<Gdk::DragContext>& context);
    void on_ti_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp, const char *effect_id);
    void hide_effect(const std::string& name);
    void on_ti_drag_data_delete(const Glib::RefPtr<Gdk::DragContext>& context, const char *effect_id);
    bool on_ti_button_press(GdkEventButton *ev, const char *effect_id);
    void on_tp_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, int info, int timestamp);
public:
    MainWindow(gx_engine::GxEngine& engine, gx_system::CmdlineOptions& options, gx_engine::ParamMap& pmap);
    ~MainWindow();
    bool check_if_animate(RackContainer& rb) const;
    RackContainer& get_monorackcontainer() { return monorackcontainer; }
    void add_rackbox(const PluginUI& pl, bool mini=false, int pos=-1, bool animate=false);
    bool check_if_rack_container_size_animate(const RackContainer& rackcontainer) const;
    void add_icon(const std::string& name);
    PluginUI *get_plugin(const std::string& name) { return plugin_dict[name]; }
    void run() { Gtk::Main::run(*window); }
    gx_system::CmdlineOptions& get_options() { return options; }
};

/****************************************************************
 **
 ** Implementation
 **
 ****************************************************************/

void child_set_property(Gtk::Container& container, Gtk::Widget& child, const char *property_name, bool value) {
    GValue v = {0};
    g_value_init(&v, G_TYPE_BOOLEAN);
    g_value_set_boolean(&v, value);
    gtk_container_child_set_property(container.gobj(), child.gobj(), property_name, &v);
}

/****************************************************************
 ** class PresetFile
 */

enum {
    PRESET_FLAG_VERSIONDIFF = 1,
    PRESET_FLAG_READONLY = 2,
};

PresetFile::PresetFile(const Glib::ustring& name_, int tp_, int flags_, const std::list<Glib::ustring>& settingslist)
    : name(name_), path(), tp(tp_), flags(flags_), settings(settingslist) {
}

bool PresetFile::has_entry(const Glib::ustring& name) const {
    return std::find(settings.begin(), settings.end(), name) != settings.end();
}

void PresetFile::append(const Glib::ustring& name) {
    settings.push_back(name);
}

void PresetFile::insert_before(const Glib::ustring& nm, const Glib::ustring& newentry) {
    settings.insert(std::find(settings.begin(), settings.end(), nm), newentry);
}

void PresetFile::insert_after(const Glib::ustring& nm, const Glib::ustring& newentry) {
    std::list<Glib::ustring>::iterator i = std::find(settings.begin(), settings.end(), nm);
    settings.insert(++i, newentry);
}

bool PresetFile::rename(const Glib::ustring& old, const Glib::ustring& newname) {
    std::list<Glib::ustring>::iterator i = std::find(settings.begin(), settings.end(), old);
    if (i == settings.end()) {
	return false;
    }
    *i = newname;
    return true;
}

void PresetFile::remove(const Glib::ustring& name) {
    settings.erase(std::find(settings.begin(), settings.end(), name));
}

void PresetFile::reorder(const std::list<Glib::ustring>& settingslist) {
    //print "PD", namelist
    //assert len(namelist) == len(self.settings)
    settings = settingslist;
}


/****************************************************************
 ** class PresetBanks
 */

PresetBanks::PresetBanks(const gx_system::CmdlineOptions& options): banklist() {
    add(new PresetFile("Scratchpad", PresetWindow::PRESET_SCRATCH, 0, std::list<Glib::ustring>()));
    parse_factory_list(options);
}

PresetBanks::~PresetBanks() {
    for (iterator i = begin(); i != end(); ++i) {
	delete *i;
    }
}

void PresetBanks::parse_factory_list(const gx_system::CmdlineOptions& options) {
    ifstream is(options.get_factory_filepath("dirlist.js").c_str());
    if (is.fail()) {
	gx_system::gx_print_error(_("Presets"), _("factory preset list not found"));
	return;
    }
    gx_system::JsonParser jp(&is);
    jp.next(gx_system::JsonParser::begin_array);
    while (jp.peek() != gx_system::JsonParser::end_array) {
	jp.next(gx_system::JsonParser::begin_array);
	jp.next(gx_system::JsonParser::value_string);
	string name = jp.current_value();
	jp.next(gx_system::JsonParser::value_string);
	string path = options.get_factory_filepath(jp.current_value());
	PresetFile *f = new PresetFile(name, PresetWindow::PRESET_FACTORY, 0, std::list<Glib::ustring>());
	/*
	try {
	    f->setting.open(path);
	    factory_presets.push_back(f);
	} catch (gx_system::JsonException& e) {
	    delete f;
	    gx_system::gx_print_error(path.c_str(), _("not found or parse error"));
	}
	*/
	add(f);
	jp.next(gx_system::JsonParser::end_array);
    }
    jp.next(gx_system::JsonParser::end_array);
    jp.next(gx_system::JsonParser::end_token);
    jp.close();
    is.close();
}

PresetFile *PresetBanks::get_file(const Glib::ustring& bank) const {
    for (std::list<PresetFile*>::const_iterator i = banklist.begin(); i != banklist.end(); ++i) {
	if ((*i)->get_name() == bank) {
	    return *i;
	}
    }
    return 0;
}

bool PresetBanks::rename(const Glib::ustring& oldname, const Glib::ustring& newname) {
    PresetFile *f = get_file(oldname);
    if (!f) {
	return false;
    }
    f->set_name(newname);
    return true;
}

bool PresetBanks::remove(const Glib::ustring& bank) {
    PresetFile *f = get_file(bank);
    if (!f) {
	return false;
    }
    banklist.remove(f);
    delete f;
    return true;
}

/****************************************************************
 ** class PresetWindow
 */

PresetStore::PresetStore(): Gtk::ListStore(PresetModelColumns())
{}

bool PresetStore::row_draggable_vfunc(const TreeModel::Path& path) const {
    Gtk::TreeModel::const_iterator i = const_cast<PresetStore*>(this)->get_iter(path); // Bug in Gtkmm: no get_iter() const
    Glib::ustring s(i->get_value(col.name));
    if (s.empty()) {
	return false;
    } else {
	return true;
    }
}


PresetWindow::PresetWindow(Glib::RefPtr<gx_gui::GxBuilder> bld, const gx_system::CmdlineOptions& options, Glib::RefPtr<Gtk::ActionGroup> actiongroup_)
    : actiongroup(actiongroup_), paned_child_height(200), in_edit(false), edit_iter(), pb_edit(), pb_del(), pb_scratch(), pb_versiondiff(),
      pb_readonly(), pb_factory(), pstore(new PresetStore), target_col(), bank_col(), banks(options), bank_row_del_conn(), preset_row_del_conn(),
      vpaned_pos(), vpaned_step(), vpaned_target(), animate(true), current_bank(), current_preset() {
    load_widget_pointers(bld);
    Glib::RefPtr<Gtk::Action> act = Gtk::Action::create("ClosePresetsAction");
    actiongroup->add(act, sigc::mem_fun(*this, &PresetWindow::on_presets_close));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(close_preset->gobj()), act->gobj());
    act = Gtk::Action::create("NewBankAction");
    actiongroup->add(act, sigc::mem_fun(*this, &PresetWindow::on_new_bank));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(new_preset_bank->gobj()), act->gobj());
    act = Gtk::Action::create("SaveAction");
    actiongroup->add(act, sigc::mem_fun(*this, &PresetWindow::on_preset_save));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(save_preset->gobj()), act->gobj());
    Glib::RefPtr<Gtk::ToggleAction> actt = Gtk::ToggleAction::create("OrganizeAction");
    actiongroup->add(actt, sigc::mem_fun(*this, &PresetWindow::on_organize));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(organize_presets->gobj()), GTK_ACTION(actt->gobj()));

    bank_treeview->set_model(Gtk::ListStore::create(bank_col));
    bank_treeview->get_selection()->set_select_function(
	sigc::mem_fun(*this, &PresetWindow::select_func));
    pb_edit = bank_treeview->render_icon(Gtk::Stock::EDIT, Gtk::ICON_SIZE_MENU);
    pb_del = bank_treeview->render_icon(Gtk::Stock::DELETE, Gtk::ICON_SIZE_MENU);
    pb_scratch = Gdk::Pixbuf::create_from_file(options.get_style_filepath("scratch.png"));
    pb_versiondiff = Gdk::Pixbuf::create_from_file(options.get_style_filepath("versiondiff.png"));
    pb_readonly = Gdk::Pixbuf::create_from_file(options.get_style_filepath("readonly.png"));
    pb_factory = Gdk::Pixbuf::create_from_file(options.get_style_filepath("factory.png"));
    bank_treeview->set_row_separator_func(sigc::mem_fun(*this, &PresetWindow::is_row_separator));
    bank_cellrenderer->signal_edited().connect(
	sigc::bind(sigc::mem_fun(*this, &PresetWindow::on_bank_edited), bank_treeview));
    bank_cellrenderer->signal_editing_canceled().connect(
	sigc::bind(sigc::mem_fun(*this, &PresetWindow::on_edit_canceled), bank_treeview->get_column(1)));
    bank_cellrenderer->signal_editing_started().connect(
	sigc::bind(sigc::mem_fun(*this, &PresetWindow::on_editing_started), bank_treeview->get_model()));
    Gtk::TreeViewColumn *col = bank_treeview->get_column(1);
    col->set_cell_data_func(**col->get_cell_renderers().begin(), sigc::mem_fun(*this, &PresetWindow::text_func));

    std::vector<Gtk::TargetEntry> listTargets;
    listTargets.push_back(Gtk::TargetEntry("GTK_TREE_MODEL_ROW", Gtk::TARGET_SAME_WIDGET, 0));
    listTargets.push_back(Gtk::TargetEntry("text/uri-list", Gtk::TARGET_OTHER_APP, 1));
    bank_treeview->enable_model_drag_source(listTargets, Gdk::BUTTON1_MASK, Gdk::ACTION_COPY);
    bank_treeview->signal_drag_motion().connect(sigc::mem_fun(*this, &PresetWindow::on_bank_drag_motion), false);
    bank_treeview->enable_model_drag_dest(listTargets, Gdk::ACTION_COPY);
    bank_treeview->signal_drag_data_received().connect(
	sigc::mem_fun(*this, &PresetWindow::on_bank_drag_data_received));
    bank_treeview->signal_drag_data_get().connect(
	sigc::mem_fun(*this, &PresetWindow::on_bank_drag_data_get));
    Glib::RefPtr<Gtk::TreeSelection> sel = bank_treeview->get_selection();
    sel->set_mode(Gtk::SELECTION_BROWSE);
    sel->signal_changed().connect(sigc::mem_fun(*this, &PresetWindow::on_bank_changed));
    bank_treeview->signal_button_release_event().connect(sigc::mem_fun(*this, &PresetWindow::on_bank_button_release), true);
    Glib::RefPtr<Gtk::TreeModel> ls = bank_treeview->get_model();
    bank_row_del_conn = ls->signal_row_deleted().connect(sigc::mem_fun(*this, &PresetWindow::on_bank_reordered));

    preset_treeview->set_model(pstore);
    std::vector<Gtk::TargetEntry> listTargets2;
    listTargets2.push_back(Gtk::TargetEntry("GTK_TREE_MODEL_ROW", Gtk::TARGET_SAME_WIDGET, 0));
    listTargets2.push_back(Gtk::TargetEntry("application/x-guitarix-preset", Gtk::TARGET_SAME_APP, 1));
    preset_treeview->enable_model_drag_source(listTargets2, Gdk::BUTTON1_MASK, Gdk::ACTION_COPY|Gdk::ACTION_MOVE);
    preset_treeview->signal_drag_motion().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_drag_motion), false);
    preset_treeview->signal_drag_data_get().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_drag_data_get));
    preset_treeview->signal_button_press_event().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_button_press));
    preset_treeview->signal_button_release_event().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_button_release), true);
    preset_row_del_conn = preset_treeview->get_model()->signal_row_deleted().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_reordered));
    preset_treeview->get_selection()->set_mode(Gtk::SELECTION_BROWSE);
    preset_treeview->get_selection()->set_select_function(
	sigc::mem_fun(*this, &PresetWindow::select_func));
    preset_treeview->get_selection()->signal_changed().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_changed));
    preset_treeview->signal_cursor_changed().connect(sigc::mem_fun(*this, &PresetWindow::on_cursor_changed));
    preset_cellrenderer->signal_edited().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_edited));
    preset_cellrenderer->signal_editing_canceled().connect(
	sigc::bind(sigc::mem_fun(*this, &PresetWindow::on_edit_canceled), preset_treeview->get_column(0)));
    preset_cellrenderer->signal_editing_started().connect(
	sigc::bind(sigc::mem_fun(*this, &PresetWindow::on_editing_started), preset_treeview->get_model()));
    preset_treeview->get_column(0)->set_cell_data_func(*preset_cellrenderer, sigc::mem_fun(*this, &PresetWindow::text_func));
    banks_combobox->signal_changed().connect(sigc::mem_fun(*this, &PresetWindow::on_preset_combo_changed));
    presets_target_treeview->get_selection()->set_mode(Gtk::SELECTION_NONE);
    std::vector<Gtk::TargetEntry> listTargets3;
    listTargets3.push_back(Gtk::TargetEntry("application/x-guitarix-preset", Gtk::TARGET_SAME_APP, 0));
    presets_target_treeview->enable_model_drag_dest(listTargets3, Gdk::ACTION_COPY);
    presets_target_treeview->signal_drag_motion().connect(sigc::mem_fun(*this, &PresetWindow::on_target_drag_motion), false);
    presets_target_treeview->signal_drag_data_received().connect(sigc::mem_fun(*this, &PresetWindow::target_drag_data_received));
    set_presets();
}

PresetWindow::~PresetWindow() {
}

void PresetWindow::load_widget_pointers(Glib::RefPtr<gx_gui::GxBuilder> bld) {
    bld->find_widget("close_preset", close_preset);
    bld->find_widget("save_preset", save_preset);
    bld->find_widget("new_preset_bank", new_preset_bank);
    bld->find_widget("organize_presets", organize_presets);
    bld->find_widget_derived("bank_treeview", bank_treeview, sigc::ptr_fun(MyTreeView::create_from_builder));
    bld->find_widget("bank_cellrenderer", bank_cellrenderer);
    bld->find_widget_derived("preset_treeview", preset_treeview, sigc::ptr_fun(MyTreeView::create_from_builder));
    bld->find_widget("preset_cellrenderer", preset_cellrenderer);
    bld->find_widget("banks_combobox", banks_combobox);
    bld->find_widget_derived("presets_target_treeview", presets_target_treeview, sigc::ptr_fun(MyTreeView::create_from_builder));
    bld->find_widget("preset_title", preset_title);
    bld->find_widget("presets_target_scrolledbox", presets_target_scrolledbox);
    bld->find_widget("bank_column_edit", bank_column_edit);
    bld->find_widget("bank_column_delete", bank_column_delete);
    bld->find_widget("preset_column_edit", preset_column_edit);
    bld->find_widget("preset_column_delete", preset_column_delete);
    bld->find_widget("main_vpaned", main_vpaned);
    bld->find_widget("preset_scrolledbox", preset_scrolledbox);
    bld->find_widget("preset_status", preset_status);
}

static bool preset_button_press_idle(Gtk::Widget& w) {
    w.grab_focus();
    return false;
}

bool PresetWindow::on_preset_button_press(GdkEventButton *ev) {
    Glib::signal_idle().connect(sigc::bind(sigc::ptr_fun(preset_button_press_idle), sigc::ref(*preset_treeview)));
    return false;
}


void PresetWindow::on_preset_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp) {
    if (selection.get_target() == "application/x-guitarix-preset") {
	Gtk::TreeModel::Path path;
	Gtk::TreeViewColumn *focus_column;
	preset_treeview->get_cursor(path, focus_column);
	Glib::ustring data = pstore->get_iter(path)->get_value(pstore->col.name);
	selection.set("application/x-guitarix-preset", data);
    }
}

void PresetWindow::on_bank_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp) {
    if (selection.get_target() == "text/uri-list") {
	const char *uris[] = { "file:///home/ad/guitarix/trunk/tt/t.py", 0 };
	selection.set_uris(uris);
    }
}

void PresetWindow::on_bank_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, guint info, guint timestamp) {
    if (info == 1) {
	//print info, data.get_uris(), context.actions, context.action, context.suggested_action
	context->drag_finish(false, true, gtk_get_current_event_time());
    }
}

Glib::ustring PresetWindow::get_combo_selection() {
    Gtk::TreeIter idx = banks_combobox->get_active();
    if (!idx) {
	return "";
    }
    return idx->get_value(target_col.name);
}

/*
 ** dnd target
 */

void PresetWindow::target_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, guint info, guint timestamp) {
    Glib::ustring bank = get_combo_selection();
    if (bank.empty()) {
	presets_target_treeview->signal_drag_data_received().emission_stop();
	return;
    }
    PresetFile& fl = *banks.get_file(bank);
    Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(presets_target_treeview->get_model());
    Glib::ustring nm = data.get_data_as_string();
    Glib::ustring t = nm;
    int n = 1;
    while (fl.has_entry(nm)) {
	nm = t + "-" + gx_system::to_string(n);
	n += 1;
    }
    Gtk::TreeModel::Path pt;
    Gtk::TreeViewDropPosition dst;
    if (!presets_target_treeview->get_dest_row_at_pos(x, y, pt, dst)) {
	ls->append()->set_value(target_col.name, nm);
	fl.append(nm);
    } else {
	Gtk::TreeIter it = ls->get_iter(pt);
	if (dst == Gtk::TREE_VIEW_DROP_BEFORE || dst == Gtk::TREE_VIEW_DROP_INTO_OR_BEFORE) {
	    ls->insert(it)->set_value(target_col.name, nm);
	    fl.insert_before(it->get_value(target_col.name), nm);
	} else { // gtk.TREE_VIEW_DROP_INTO_OR_AFTER, gtk.TREE_VIEW_DROP_AFTER
	    ls->insert_after(it)->set_value(target_col.name, nm);
	    fl.insert_after(it->get_value(target_col.name), nm);
	}
    }
    if (context->get_action() == Gdk::ACTION_MOVE) {
	Gtk::TreeModel::Path pt;
	Gtk::TreeViewColumn *col;
	preset_treeview->get_cursor(pt, col);
	Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(preset_treeview->get_model());
	preset_row_del_conn.block();
	ls->erase(ls->get_iter(pt));
	preset_row_del_conn.unblock();
	banks.get_file(get_current_bank())->remove(nm);
    }
    reload_presets(); // if preset list == target list
}

bool PresetWindow::on_target_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp) {
    Gtk::Widget *source_widget = Gtk::Widget::drag_get_source_widget(context);
    if (source_widget != preset_treeview || get_combo_selection().empty()) {
	context->drag_status((Gdk::DragAction)0, timestamp);
	return true;
    }
    presets_target_treeview->on_drag_motion(context, x, y, timestamp);
    Gtk::TreeIter it = bank_treeview->get_selection()->get_selected();
    int tp = it->get_value(bank_col.tp);
    Glib::ustring nm = it->get_value(bank_col.name);
    if ((tp != PRESET_SCRATCH && tp != PRESET_FILE) || banks.get_file(nm)->get_flags() ||
	get_combo_selection() == nm) {
	context->drag_status(Gdk::ACTION_COPY, timestamp);
    }
    return true;
}

void PresetWindow::reload_combo() {
    Glib::ustring old = get_combo_selection();
    Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(banks_combobox->get_model());
    ls->clear();
    int n = 0;
    int nn = -1;
    for (PresetBanks::iterator i = banks.begin(); i != banks.end(); ++i) {
	int tp = i->get_type();
	if (tp != PRESET_FILE && tp != PRESET_SCRATCH) {
	    continue;
	}
	if (i->get_flags()) {
	    continue;
	}
	Glib::ustring s = i->get_name();
	ls->append()->set_value(bank_col.name, s);
	if (s == old) {
	    nn = n;
	}
	n += 1;
    }
    banks_combobox->set_active(nn);
}

void PresetWindow::on_preset_combo_changed() {
    Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(presets_target_treeview->get_model());
    ls->clear();
    Glib::ustring nm = get_combo_selection();
    if (nm.empty()) {
	return;
    }
    PresetFile& f = *banks.get_file(nm);
    for (PresetFile::iterator i = f.begin(); i != f.end(); ++i) {
	ls->append()->set_value(bank_col.name, *i);
    }
}

void PresetWindow::reload_target() {
    on_preset_combo_changed();
}

/*
 ** name edit
 */

bool PresetWindow::select_func(const Glib::RefPtr<Gtk::TreeModel>& model, const Gtk::TreePath& path, bool path_currently_selected) {
    Glib::ustring s = model->get_iter(path)->get_value(bank_col.name);
    if (s.empty()) {
	return false;
    }
    return true;
}

void PresetWindow::text_func(Gtk::CellRenderer *cell, const Gtk::TreeModel::iterator& iter) {
    Glib::ustring t = iter->get_value(bank_col.name);
    if (t.empty() && !cell->property_editing().get_value()) {
	t = "<new>";
    }
    cell->set_property("text", t);
}

void PresetWindow::on_editing_started(const Gtk::CellEditable* edit, const Glib::ustring& path, Glib::RefPtr<Gtk::TreeModel>& model) {
    Glib::ustring s = model->get_iter(path)->get_value(bank_col.name);
    if (s.empty()) {
	dynamic_cast<Gtk::Entry*>(const_cast<Gtk::CellEditable*>(edit))->set_text("");
    }
}

bool PresetWindow::edit_cell(const Gtk::TreeModel::Path pt, Gtk::TreeViewColumn& col, Gtk::CellRenderer& cell) {
    dynamic_cast<Gtk::CellRendererText*>(&cell)->property_editable().set_value(true);
    col.get_tree_view()->set_cursor(pt, col, true);
    return false;
}

void PresetWindow::reset_edit(Gtk::TreeViewColumn& col) {
    if (edit_iter) {
	Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(col.get_tree_view()->get_model());
	ls->erase(edit_iter);
	edit_iter = ls->children().end();
    }
    Gtk::CellRendererText& cell = *dynamic_cast<Gtk::CellRendererText*>(col.get_first_cell());
    cell.property_editable().set_value(false);
    col.set_min_width(0);
    col.queue_resize();
    in_edit = false;
}

void PresetWindow::on_edit_canceled(Gtk::TreeViewColumn *col) {
    reset_edit(*col);
}

void PresetWindow::start_edit(const Gtk::TreeModel::Path& pt, Gtk::TreeViewColumn& col, Gtk::CellRenderer& cell) {
    col.set_min_width(100);
    Glib::signal_idle().connect(
	sigc::bind(sigc::mem_fun(*this, &PresetWindow::edit_cell),
		   pt, sigc::ref(col), sigc::ref(cell)));
}

/*
 ** list of banks
 */

Gtk::TreeModel::Row PresetWindow::get_current_bank_row() {
    Gtk::TreeIter it = bank_treeview->get_selection()->get_selected();
    if (it) {
	return *it;
    } else {
	return Gtk::TreeModel::Row();
    }
}

Glib::ustring PresetWindow::get_current_bank() {
    Gtk::TreeModel::Row row = get_current_bank_row();
    if (!row) {
	return "";
    }
    return row[bank_col.name];
}

bool PresetWindow::run_message_dialog(Gtk::Widget& w, const Glib::ustring& msg) {
    Gtk::MessageDialog d(*dynamic_cast<Gtk::Window*>(w.get_toplevel()), msg, false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL, true);
    d.set_position(Gtk::WIN_POS_MOUSE);
    return d.run() == Gtk::RESPONSE_OK;
}

bool PresetWindow::on_bank_button_release(GdkEventButton *ev) {
    // edit bank name / delete bank
    Gtk::TreeModel::Path pt;
    Gtk::TreeViewColumn *col;
    int dx, dy;
    if (!bank_treeview->get_path_at_pos(ev->x, ev->y, pt, col, dx, dy)) {
	return false;
    }
    Gtk::TreeModel::Path path;
    Gtk::TreeViewColumn *focus_column;
    bank_treeview->get_cursor(path, focus_column);
    if (col != focus_column || pt != path) {
	return false;
    }
    Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(bank_treeview->get_model());
    Gtk::TreeModel::iterator it = ls->get_iter(pt);
    Glib::ustring nm = it->get_value(bank_col.name);
    int tp = it->get_value(bank_col.tp);
    if (col == bank_treeview->get_column(0)) {
	if (tp == PRESET_SCRATCH || tp == PRESET_FILE) {
	    int flags = banks.get_file(nm)->get_flags();
	    if (flags == 0 && tp == PRESET_FILE) {
		if (run_message_dialog(*bank_treeview, "set bank " + nm + " to readonly?")) {
		    banks.get_file(nm)->set_flags(PRESET_FLAG_READONLY);
		    reload_banks(nm);
		}
	    } else if (flags == PRESET_FLAG_VERSIONDIFF) {
		if (run_message_dialog(*bank_treeview, "convert bank " + nm + " to new version?")) {
		    banks.get_file(nm)->set_flags(0);
		    reload_banks(nm);
		}
	    } else if (flags == PRESET_FLAG_READONLY) {
		if (run_message_dialog(*bank_treeview, "set bank " + nm + " %s to read/write?")) {
		    banks.get_file(nm)->set_flags(0);
		    reload_banks(nm);
		}
	    } else if (flags == (PRESET_FLAG_READONLY | PRESET_FLAG_VERSIONDIFF)) {
		if (run_message_dialog(*bank_treeview, "convert readonly bank " + nm + " to new version?")) {
		    banks.get_file(nm)->set_flags(PRESET_FLAG_READONLY);
		    reload_banks(nm);
		}
	    }
	}
	return false;
    }
    if (tp != PRESET_FILE || banks.get_file(nm)->get_flags()) {
	return false;
    }
    if (col == bank_treeview->get_column(2)) {
	col = bank_treeview->get_column(1);
	start_edit(pt, *col, *col->get_first_cell());
    } else if (col == bank_treeview->get_column(3)) {
	Gtk::MessageDialog d(*dynamic_cast<Gtk::Window*>(bank_treeview->get_toplevel()), "delete bank " + nm + "?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL, true);
	d.set_position(Gtk::WIN_POS_MOUSE);
	if (d.run() == Gtk::RESPONSE_OK) {
	    bank_row_del_conn.block();
	    ls->erase(it);
	    bank_row_del_conn.unblock();
	    banks.remove(nm);
	    reload_combo();
	    if (nm == current_bank) {
		current_bank = current_preset = "";
	    }
	}
    }
    return false;
}

static void strip(Glib::ustring& s) {
    size_t n = s.find_first_not_of(' ');
    if (n == Glib::ustring::npos) {
	s.erase();
	return;
    }
    if (n != 0) {
	s.erase(0, n);
    }
    s.erase(s.find_last_not_of(' ')+1);
}

void PresetWindow::on_bank_edited(const Glib::ustring& path, const Glib::ustring& newtext, Gtk::TreeView* w) {
    Gtk::TreeIter sel = w->get_model()->get_iter(path);
    Gtk::TreeModel::Row row = *sel;
    Glib::ustring oldname = row[bank_col.name];
    Glib::ustring newname = newtext;
    strip(newname);
    if (newname.empty() || newname == oldname) {
	Gtk::TreeViewColumn *p = w->get_column(1);
	reset_edit(*p);
	return;
    }
    Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(banks_combobox->get_model());
    int n = 1;
    Glib::ustring t = newname;
    while (banks.has_entry(newname)) {
	newname = t + "-" + gx_system::to_string(n);
	n += 1;
    }
    if (edit_iter) {
	ls->prepend()->set_value(target_col.name, newname);
	edit_iter = ls->children().end();
	row[bank_col.name] = newname;
	row[bank_col.edit_pb] = pb_edit;
	row[bank_col.del_pb] = pb_del;
	banks.add(new PresetFile(newname, PRESET_FILE, 0, std::list<Glib::ustring>()));
    } else {
	Gtk::TreeNodeChildren ch = ls->children();
	for (Gtk::TreeIter it = ch.begin(); it != ch.end(); ++it) {
	    if (it->get_value(bank_col.name) == oldname) {
		it->set_value(bank_col.name, newname);
	    }
	}
	banks.rename(oldname, newname);
	if (oldname == current_bank) {
	    current_bank = newname;
	}
	row[bank_col.name] = newname;
    }
    w->get_selection()->select(sel);
    Gtk::TreeViewColumn *p = w->get_column(1);
    reset_edit(*p);
}

bool PresetWindow::is_row_separator(const Glib::RefPtr<Gtk::TreeModel>& model, const Gtk::TreeModel::iterator& iter) {
    return iter->get_value(bank_col.tp) == PRESET_SEP;
}

void PresetWindow::on_new_bank() {
    Glib::RefPtr<Gtk::ListStore> m = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(bank_treeview->get_model());
    edit_iter = m->prepend();
    edit_iter->set_value(bank_col.tp, static_cast<int>(PRESET_FILE));
    in_edit = true;
    start_edit(m->get_path(edit_iter), *bank_treeview->get_column(1), *bank_cellrenderer);
}

bool PresetWindow::on_bank_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp) {
    Gtk::Widget *source_widget = Gtk::Widget::drag_get_source_widget(context);
    if (!source_widget) {
	// URI from other application
	Gdk::DragAction a;
	if (context->get_suggested_action() == Gdk::ACTION_MOVE) {
	    a = context->get_suggested_action();
	} else {
	    a = Gdk::ACTION_COPY;
	}
	context->drag_status(a, timestamp);
    } else if (source_widget != bank_treeview) {
	// other window
	context->drag_status((Gdk::DragAction)0, timestamp);
    } else {
	// reorder
	Gtk::TreeIter it = bank_treeview->get_selection()->get_selected();
	if (!it) {
	    return true;
	}
	int tp = it->get_value(bank_col.tp);
	if (tp != PRESET_SCRATCH && tp != PRESET_FILE) {
	    context->drag_status((Gdk::DragAction)0, timestamp);
	    return true;
	}
	Gtk::TreeModel::Path pt;
	Gtk::TreeViewDropPosition dst;
	if (bank_treeview->get_dest_row_at_pos(x, y, pt, dst)) {
	    tp = bank_treeview->get_model()->get_iter(pt)->get_value(bank_col.tp);
	    if (tp != PRESET_SCRATCH && tp != PRESET_FILE) {
		context->drag_status((Gdk::DragAction)0, timestamp);
		return true;
	    }
	}
	bank_treeview->on_drag_motion(context, x, y, timestamp);
	context->drag_status(Gdk::ACTION_MOVE, timestamp);
    }
    return true;
}

void PresetWindow::reload_presets() {
    on_bank_changed();
}

void PresetWindow::on_bank_changed() {
    Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(preset_treeview->get_model());
    preset_row_del_conn.block();
    ls->clear();
    preset_row_del_conn.unblock();
    Gtk::TreeIter it = bank_treeview->get_selection()->get_selected();
    if (!it) {
	return;
    }
    int tp = it->get_value(bank_col.tp);
    Glib::ustring nm = it->get_value(bank_col.name);
    preset_title->set_text(nm);
    Glib::ustring cp;
    if (nm == current_bank) {
	cp = current_preset;
    }
    Gtk::TreeIter i;
    if (tp == PRESET_SCRATCH || tp == PRESET_FILE) {
	PresetFile& ll = *banks.get_file(nm);
	if (ll.get_flags()) {
	    for (PresetFile::iterator s = ll.begin(); s != ll.end(); ++s) {
		i = ls->append();
		i->set_value(pstore->col.name, *s);
		if (*s == cp) {
		    preset_treeview->get_selection()->select(i);
		}
	    }
	} else {
	    for (PresetFile::iterator s = ll.begin(); s != ll.end(); ++s) {
		i = ls->append();
		i->set_value(pstore->col.name, *s);
		i->set_value(pstore->col.edit_pb, pb_edit);
		i->set_value(pstore->col.del_pb, pb_del);
		if (*s == cp) {
		    preset_treeview->get_selection()->select(i);
		}
	    }
	    i = ls->append();
	}
    } else if (tp == PRESET_FACTORY) {
	PresetFile& ll = *banks.get_file(nm);
	for (PresetFile::iterator s = ll.begin(); s != ll.end(); ++s) {
	    i = ls->append();
	    if (*s == cp) {
		preset_treeview->get_selection()->select(i);
	    }
	}
    }
}

void PresetWindow::reload_banks(Glib::ustring& sel_bank) {
    Glib::RefPtr<Gtk::ListStore> ls3 = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(preset_treeview->get_model());
    preset_row_del_conn.block();
    ls3->clear();
    preset_row_del_conn.unblock();
    Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(bank_treeview->get_model());
    bank_row_del_conn.block();
    ls->clear();
    bank_row_del_conn.unblock();
    Gtk::TreeIter i;
    int in_factory = false;
    for (PresetBanks::iterator v = banks.begin(); v != banks.end(); ++v) {
	PresetFile& l = **v;
	Glib::RefPtr<Gdk::Pixbuf> pb;
	if (l.get_type() == PRESET_SCRATCH) {
	    pb = pb_scratch;
	} else if (l.get_type() == PRESET_FILE) {
	    pb.reset();
	} else if (l.get_type() == PRESET_FACTORY) {
	    if (!in_factory) {
		i = ls->append();
		i->set_value(bank_col.tp, static_cast<int>(PRESET_SEP));
		in_factory = true;
	    }
	    pb = pb_factory;
	} else {
	    assert(false);
	}
	if (l.get_flags() & PRESET_FLAG_VERSIONDIFF) {
	    pb = pb_versiondiff;
	} else if (l.get_flags() & PRESET_FLAG_READONLY) {
	    pb = pb_readonly;
	}
	if (l.get_type() == PRESET_SCRATCH) {
	    i = ls->append();
	    i->set_value(bank_col.name, v->get_name());
	    i->set_value(bank_col.type_pb, pb);
	    i->set_value(bank_col.tp, static_cast<int>(PRESET_SCRATCH));
	    if (v->get_name() == sel_bank) {
		bank_treeview->get_selection()->select(i);
	    }
	} else if (l.get_type() == PRESET_FILE) {
	    if (pb) {
		i = ls->append();
		i->set_value(bank_col.name, v->get_name());
		i->set_value(bank_col.type_pb, pb);
		i->set_value(bank_col.tp, static_cast<int>(PRESET_FILE));
	    } else {
		i = ls->append();
		i->set_value(bank_col.name, v->get_name());
		i->set_value(bank_col.edit_pb, pb_edit);
		i->set_value(bank_col.del_pb, pb_del);
		i->set_value(bank_col.tp, static_cast<int>(PRESET_FILE));
	    }
	    if (v->get_name() == sel_bank) {
		bank_treeview->get_selection()->select(i);
	    }
	} else if (l.get_type() == PRESET_FACTORY) {
	    i = ls->append();
	    i->set_value(bank_col.name, v->get_name());
	    i->set_value(bank_col.type_pb, pb_factory);
	    i->set_value(bank_col.tp, static_cast<int>(PRESET_FACTORY));
	    if (v->get_name() == sel_bank) {
		bank_treeview->get_selection()->select(i);
	    }
	} else {
	    assert(false);
	}
    }
    reload_combo();
}

void PresetWindow::set_presets() {
    reload_banks(current_bank);
}

void PresetWindow::on_bank_reordered(const Gtk::TreeModel::Path& path) {
    // save changed order to file
    //global preset_files;
    //print "BD", [v[0] for v in ls], pt
    //s = collections.OrderedDict();
    /*
    Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(bank_treeview->get_model());
    for v in ls:
	if v[0] and v[4] in (self.PRESET_SCRATCH, self.PRESET_FILE):
	    s[v[0]] = preset_files[v[0]]
    preset_files = s
    */
    //FIXME
}

/*
 ** list of presets
 */

bool PresetWindow::on_preset_button_release(GdkEventButton *ev) {
    Gtk::TreeModel::Path pt;
    Gtk::TreeViewColumn *col;
    int dx, dy;
    if (!preset_treeview->get_path_at_pos(ev->x, ev->y, pt, col, dx, dy)) {
	return false;
    }
    Gtk::TreeModel::Path path;
    Gtk::TreeViewColumn *focus_column;
    preset_treeview->get_cursor(path, focus_column);
    if (col != focus_column || pt != path) {
	return false;
    }
    Gtk::TreeModel::Row bank_row = get_current_bank_row();
    int tp = bank_row[bank_col.tp];
    if ((tp != PRESET_SCRATCH && tp != PRESET_FILE) || banks.get_file(bank_row[bank_col.name])->get_flags()) {
	return false;
    }
    if (col == preset_treeview->get_column(1)) {
	col = preset_treeview->get_column(0);
	start_edit(pt, *col, *col->get_first_cell());
    } else if (col == preset_treeview->get_column(2)) {
	Glib::RefPtr<Gtk::ListStore> ls = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(preset_treeview->get_model());
	Glib::ustring nm = ls->get_iter(pt)->get_value(pstore->col.name);
	Gtk::MessageDialog d(*dynamic_cast<Gtk::Window*>(preset_treeview->get_toplevel()), Glib::ustring::compose("delete preset %1?", nm), false,
			     Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL, true);
	d.set_position(Gtk::WIN_POS_MOUSE);
	if (d.run() == Gtk::RESPONSE_OK) {
	    preset_row_del_conn.block();
	    ls->erase(ls->get_iter(pt));
	    preset_row_del_conn.unblock();
	    banks.get_file(bank_row[bank_col.name])->remove(nm);
	    reload_target();
	}
    }
    return false;
}

void PresetWindow::on_preset_edited(const Glib::ustring& path, const Glib::ustring& newtext) {
    Glib::ustring newname = newtext;
    strip(newname);
    if (newname.empty()) {
	reset_edit(*preset_treeview->get_column(0));
	return;
    }
    PresetFile& fl = *banks.get_file(get_current_bank());
    Glib::ustring t = newname;
    int n = 1;
    while (fl.has_entry(newname)) {
	newname = Glib::ustring::compose("%1-%2", t, n);
	n += 1;
    }
    Glib::RefPtr<Gtk::ListStore> m = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(preset_treeview->get_model());
    Gtk::TreeRow row = *m->get_iter(path);
    t = row[pstore->col.name];
    if (t.empty()) {
	m->append();
	fl.append(newname);
    } else {
	fl.rename(t, newname);
	if (current_bank == get_current_bank() && current_preset == row[pstore->col.name]) {
	    current_preset = newname;
	}
    }
    row[pstore->col.name] = newname;
    row[pstore->col.edit_pb] = pb_edit;
    row[pstore->col.del_pb] = pb_del;
    preset_treeview->get_selection()->select(m->get_iter(path));
    reload_target();
    reset_edit(*preset_treeview->get_column(0));
}

void PresetWindow::on_cursor_changed() {
    if (in_edit) {
	return;
    }
    Gtk::TreeModel::Path path;
    Gtk::TreeViewColumn *focus_column;
    preset_treeview->get_cursor(path, focus_column);
    Glib::RefPtr<Gtk::TreeModel> ls = preset_treeview->get_model();
    if (!ls->get_iter(path)->get_value(pstore->col.name).empty()) {
	return;
    }
    in_edit = true;
    start_edit(path, *preset_treeview->get_column(0), *preset_cellrenderer);
}

void PresetWindow::on_preset_changed() {
    if (!Glib::RefPtr<Gtk::ToggleAction>::cast_dynamic(actiongroup->get_action("OrganizeAction"))->get_active()) {
	show_selected_preset();
    }
}

bool PresetWindow::on_preset_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp) {
    Gtk::Widget *source_widget = Gtk::Widget::drag_get_source_widget(context);
    if (source_widget == preset_treeview) {
	preset_treeview->on_drag_motion(context, x, y, timestamp);
	Gtk::TreeModel::Path pt;
	Gtk::TreeViewDropPosition dst;
	if (preset_treeview->get_dest_row_at_pos(x, y, pt, dst)) {
	    if (dst == Gtk::TREE_VIEW_DROP_BEFORE ||
		(dst == Gtk::TREE_VIEW_DROP_AFTER &&
		 !preset_treeview->get_model()->get_iter(pt)->get_value(pstore->col.name).empty())) {
		context->drag_status(Gdk::ACTION_MOVE, timestamp);
		return true;
	    }
	}
    }
    context->drag_status((Gdk::DragAction)0, timestamp);
    return true;
}

void PresetWindow::on_preset_reordered(const Gtk::TreeModel::Path& path) {
    // save changed order to file
    //preset_files[self.get_current_bank()].reorder([v[0] for v in ls if v[0]]) FIXME
    reload_target();
}

void PresetWindow::autosize() {
    bank_treeview->columns_autosize();
    preset_treeview->columns_autosize();
}

void PresetWindow::on_organize() {
    bool v = organize_presets->get_active();
    bank_column_edit->set_visible(v);
    bank_column_delete->set_visible(v);
    preset_column_edit->set_visible(v);
    preset_column_delete->set_visible(v);
    save_preset->set_sensitive(!v); // FIXME -> SaveAction
    Glib::RefPtr<Gtk::TreeSelection> sel = preset_treeview->get_selection();
    if (v) {
	sel->set_mode(Gtk::SELECTION_NONE);
	banks_combobox->set_active(-1);
	banks_combobox->show();
	presets_target_scrolledbox->show();
    } else {
	sel->set_mode(Gtk::SELECTION_BROWSE);
	banks_combobox->hide();
	presets_target_scrolledbox->hide();
    }
    autosize();
}

void PresetWindow::on_presets_close() {
    Glib::RefPtr<Gtk::ToggleAction>::cast_dynamic(actiongroup->get_action("PresetsAction"))->set_active(false); // FIXME
}

/*
 ** preset window
 */

bool PresetWindow::animate_preset_show() {
    vpaned_pos -= vpaned_step;
    if (vpaned_pos <= vpaned_target) {
	main_vpaned->set_position(vpaned_target);
	child_set_property(*main_vpaned, *preset_scrolledbox, "shrink", false);
	return false;
    }
    main_vpaned->set_position(vpaned_pos);
    return true;
}

bool PresetWindow::animate_preset_hide() {
    vpaned_pos += vpaned_step;
    if (vpaned_pos >= vpaned_target) {
	preset_scrolledbox->hide();
	return false;
    }
    main_vpaned->set_position(vpaned_pos);
    return true;
}

void PresetWindow::show_selected_preset() {
    Gtk::TreeIter it = bank_treeview->get_selection()->get_selected();
    if (!it) {
	return;
    }
    Glib::ustring cb = it->get_value(bank_col.name);
    it = preset_treeview->get_selection()->get_selected();
    if (!it) {
	return;
    }
    current_bank = cb;
    current_preset = it->get_value(pstore->col.name);
    preset_status->set_text(cb + " / " + current_preset);
}

void PresetWindow::on_preset_save() {
    //FIXME
}

void PresetWindow::on_preset_select(bool v) {
    if (v) {
	autosize();
	vpaned_pos = main_vpaned->get_allocation().get_height();
	vpaned_target = vpaned_pos - paned_child_height;
	if (animate) {
	    main_vpaned->set_position(vpaned_pos);
	    vpaned_step = paned_child_height / 5;
	    preset_scrolledbox->show();
	    animate_preset_show();
	    Glib::signal_timeout().connect(sigc::mem_fun(*this, &PresetWindow::animate_preset_show), 20);
	} else {
	    main_vpaned->set_position(vpaned_target);
	    child_set_property(*main_vpaned, *preset_scrolledbox, "shrink", false);
	    preset_scrolledbox->show();
	}
    } else {
	vpaned_target = main_vpaned->get_allocation().get_height();
	if (animate) {
	    vpaned_pos = main_vpaned->get_position();
	    paned_child_height = vpaned_target - vpaned_pos;
	    vpaned_step = paned_child_height / 5;
	    child_set_property(*main_vpaned, *preset_scrolledbox, "shrink", true);
	    Glib::signal_timeout().connect(sigc::mem_fun(*this, &PresetWindow::animate_preset_hide), 20);
	} else {
	    preset_scrolledbox->hide();
	}
	Glib::RefPtr<Gtk::ToggleAction>::cast_dynamic(actiongroup->get_action("OrganizeAction"))->set_active(false);
    }
}

/****************************************************************
 ** class Liveplay
 */

gboolean do_action(GtkAccelGroup *accel_group, GObject *acceleratable,
	    guint keyval, GdkModifierType modifier,
	    GtkAction* act) {
    gtk_action_activate(act);
    return true;
}

Liveplay::Liveplay(const gx_system::CmdlineOptions& options, gx_preset::GxSettings& gx_settings_,
		   const std::string& fname, Glib::RefPtr<Gtk::ActionGroup> actiongroup)
    : bld(), gx_settings(gx_settings_), ui(), use_composite(),
      brightness_adj(1,0.5,1,0.01,0.1), background_adj(0,0,1,0.01,0.1),
      window() {
    const char *id_list[] = {"LivePlay", 0};
    bld = gx_gui::GxBuilder::create_from_file(fname, &ui, id_list);
    bld->get_toplevel("LivePlay", window);

    bld->find_widget("liveplay_preset", liveplay_preset);
    bld->find_widget("liveplay_bypass_image", bypass_image);
    bld->find_widget("liveplay_mute_image", mute_image);
    bld->find_widget("liveplay_canvas", liveplay_canvas);
    bld->find_widget("brightness_slider", brightness_slider);
    bld->find_widget("brightness_box", brightness_box);
    bld->find_widget("background_slider", background_slider);
    bld->find_widget("liveplay_exit:barbutton", liveplay_exit);
    bld->find_widget("liveplay_tuner", tuner);
    bld->find_widget("liveplay_midictrl_table", midictrl_table);

    Glib::RefPtr<Gdk::Pixbuf> pb = Gdk::Pixbuf::create_from_file(
	options.get_style_filepath("bypass.svg"), 300, 150);
    bypass_image->set(pb);
    pb = Gdk::Pixbuf::create_from_file(
	options.get_style_filepath("mute.svg"), 300, 150);
    mute_image->set(pb);
    use_composite = window->get_display()->supports_composite();
    if (use_composite) {
	brightness_adj.signal_value_changed().connect(sigc::mem_fun(*this, &Liveplay::on_brightness_changed));
	brightness_slider->set_adjustment(brightness_adj);
	liveplay_canvas->signal_realize().connect(sigc::mem_fun(*this, &Liveplay::on_realize));
	window->signal_expose_event().connect(
	    sigc::mem_fun(*this, &Liveplay::window_expose_event), true);
    } else {
	brightness_box->hide();
    }
    background_adj.signal_value_changed().connect(
	sigc::mem_fun(*this, &Liveplay::on_background_changed));
    background_slider->set_adjustment(background_adj);
    Glib::RefPtr<Gdk::Screen> screen = liveplay_canvas->get_screen();
    Glib::RefPtr<Gdk::Colormap> rgba = screen->get_rgba_colormap();
    liveplay_canvas->set_colormap(rgba);
    liveplay_canvas->set_app_paintable(true);
    liveplay_canvas->signal_expose_event().connect(
	sigc::mem_fun(*this, &Liveplay::transparent_expose));
    window->signal_delete_event().connect(
	sigc::mem_fun(*this, &Liveplay::on_delete));
    Glib::RefPtr<Gtk::Action> act = actiongroup->get_action("LiveplayAction");
    gtk_activatable_set_related_action(
	GTK_ACTIVATABLE(liveplay_exit->gobj()),
	act->gobj());
    Glib::RefPtr<Gtk::AccelGroup> ag = Gtk::AccelGroup::create();
    GClosure *cl = g_cclosure_new(G_CALLBACK(do_action), (gpointer)(act->gobj()), 0);
    gtk_accel_group_connect_by_path(ag->gobj(), act->get_accel_path().c_str(), cl);
    cl = g_cclosure_new(G_CALLBACK(do_action), (gpointer)(act->gobj()), 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_Escape, (GdkModifierType)0, (GtkAccelFlags)0, cl);
    act = actiongroup->get_action("TunerAction");
    cl = g_cclosure_new(G_CALLBACK(do_action), (gpointer)(act->gobj()), 0);
    gtk_accel_group_connect_by_path(ag->gobj(), act->get_accel_path().c_str(), cl);
    act = actiongroup->get_action("QuitAction");
    cl = g_cclosure_new(G_CALLBACK(do_action), (gpointer)(act->gobj()), 0);
    gtk_accel_group_connect_by_path(ag->gobj(), act->get_accel_path().c_str(), cl);
    window->add_accel_group(ag);
}

Liveplay::~Liveplay() {
    delete window;
}

void Liveplay::on_live_play(Glib::RefPtr<Gtk::ToggleAction> act) {
    if (act->get_active()) {
	Glib::ustring s;
	if (true) {//!preset_window.current_bank) {
	    s = "----";
	} else {
	    //s = "%s / %s" % (self.preset_window.current_bank,
	    //		     self.preset_window.current_preset)
	}
	liveplay_preset->set_text(s);
	window->fullscreen();
	add_midi_elements(gx_engine::controller_map);
	window->show();
    } else {
	window->hide();
    }
}

bool Liveplay::window_expose_event(GdkEventExpose *event) {
    Cairo::RefPtr<Cairo::Context> cr = Glib::wrap(event->window, true)->create_cairo_context();
    Gtk::Allocation a = liveplay_canvas->get_allocation();
    gdk_cairo_set_source_window(cr->cobj(), liveplay_canvas->get_window()->gobj(), a.get_x(), a.get_y());
    Gdk::Region region(a);
    region.intersect(Glib::wrap(event->region, true));
    Gdk::Cairo::add_region_to_path(cr, region);
    cr->clip();

    cr->set_operator(Cairo::OPERATOR_OVER);
    cr->paint_with_alpha(pow(brightness_adj.get_value(),2.2));
    return false;
}

bool Liveplay::on_delete(GdkEventAny *ev) {
    liveplay_exit->set_active(false);
    return true;
}

void Liveplay::on_brightness_changed() {
    window->queue_draw();
}

void Liveplay::on_background_changed() {
    window->queue_draw();
}

bool Liveplay::transparent_expose(GdkEventExpose *event) {
    Cairo::RefPtr<Cairo::Context> cr = Glib::wrap(event->window, true)->create_cairo_context();
    gdk_cairo_region(cr->cobj(), event->region);
    cr->set_source_rgba(0.0, 1.0, 0.0, pow(background_adj.get_value(),2.2));
    cr->fill();
    return false;
}

void Liveplay::display_tuner(bool v) {
    tuner->set_sensitive(v);
}

void Liveplay::on_realize() {
    liveplay_canvas->get_window()->set_composited(true);
}

#if 0
    for (int i = 0; i < gx_engine::controller_map.size(); i++) {
        gx_engine::midi_controller_list& cl = gx_engine::controller_map[i];
        for (gx_engine::midi_controller_list::iterator j = cl.begin(); j != cl.end(); ++j) {
            gx_engine::Parameter& p = j->getParameter();
            string low, up;
            const char *tp;
            float step = p.getStepAsFloat();
            if (p.getControlType() == gx_engine::Parameter::Continuous) {
                tp = "Scale";
                low = gx_gui::fformat(j->lower(), step);
                up = gx_gui::fformat(j->upper(), step);
            } else if (p.getControlType() == gx_engine::Parameter::Enum) {
                tp = "Select";
                low = gx_gui::fformat(j->lower(), step);
                up = gx_gui::fformat(j->upper(), step);
            } else if (p.getControlType() == gx_engine::Parameter::Switch) {
                tp = "Switch";
                low = up = "";
            } else {
                tp = "??";
                assert(false);
            }
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               0, i,
                               1, gx_engine::midi_std_ctr[i].c_str(),
                               2, p.l_group().c_str(),
                               3, p.l_name().c_str(),
                               4, tp,
                               5, low.c_str(),
                               6, up.c_str(),
                               7, p.id().c_str(),
                               -1);
        }
    }
#endif

void Liveplay::add_midi_elements(gx_engine::MidiControllerList& controller) {
    printf("%d\n", controller.size());
    int left = 0;
    int top = 0;
    int top_max = 6;
    int left_max = 3;
    for (int i = 0; i < gx_engine::controller_map.size(); i++) {
        gx_engine::midi_controller_list& cl = gx_engine::controller_map[i];
	if (cl.empty()) {
	    continue;
	}
	std::string v = gx_engine::midi_std_ctr[i];
	printf("%s\n", v.c_str());
	Gtk::ProgressBar *b = new Gtk::ProgressBar();
	b->set_size_request(300, 50);
	b->set_fraction(0.4);
	b->set_text(v);
	midictrl_table->attach(*manage(b), left, left+1, top, top+1);
	top += 1;
	if (top >= top_max) {
	    top = 0;
	    left += 1;
	}
	if (left >= left_max) {
	    break;
	}
    }
    midictrl_table->show_all();
}

/****************************************************************
 ** class DragIcon
 */

inline guint8 convert_color_channel (guint8 src, guint8 alpha) {
    return alpha ? ((guint (src) << 8) - src) / alpha : 0;
}

void convert_bgra_to_rgba (guint8 const* src, guint8* dst, int width, int height) {
    guint8 const* src_pixel = src;
    guint8*       dst_pixel = dst;

    for (int i = 0; i < height*width; ++i) {
        dst_pixel[0] = convert_color_channel(src_pixel[2], src_pixel[3]);
        dst_pixel[1] = convert_color_channel(src_pixel[1], src_pixel[3]);
        dst_pixel[2] = convert_color_channel(src_pixel[0], src_pixel[3]);
        dst_pixel[3] = src_pixel[3];

        dst_pixel += 4;
        src_pixel += 4;
    }
}

DragIcon::DragIcon(const PluginUI& plugin, Glib::RefPtr<Gdk::DragContext> context, gx_system::CmdlineOptions& options, int xoff)
    : window(), drag_icon_pixbuf() {
    Glib::RefPtr<Gdk::Screen> screen = context->get_source_window()->get_screen();
    Glib::RefPtr<Gdk::Colormap> rgba = screen->get_rgba_colormap();
    if (screen->is_composited()) {
	window = new Gtk::Window(Gtk::WINDOW_POPUP);
	if (rgba) { // else will look ugly..
	    window->set_colormap(rgba);
	}
    }
    create_drag_icon_pixbuf(plugin, rgba, options);
    int w = drag_icon_pixbuf->get_width();
    int h = drag_icon_pixbuf->get_height();
    int h2 = (h/2)-2;
    int w2 = std::min(w, xoff) - 4;
    if (window) {
	window->set_size_request(w, h);
	window->signal_expose_event().connect(sigc::mem_fun(*this, &DragIcon::icon_expose_event));
	//context->set_icon_widget(window, w2, h2);
	gtk_drag_set_icon_widget(context->gobj(), GTK_WIDGET(window->gobj()), w2, h2);
    } else {
	context->set_icon(drag_icon_pixbuf, w2, h2);
    }
}

DragIcon::~DragIcon() {
    delete window;
}

bool DragIcon::icon_expose_event(GdkEventExpose *ev) {
    Cairo::RefPtr<Cairo::Context> cr = Glib::wrap(ev->window, true)->create_cairo_context();
    gdk_cairo_region(cr->cobj(), ev->region);
    cr->set_operator(Cairo::OPERATOR_SOURCE);
    cr->clip();
    Gdk::Cairo::set_source_pixbuf(cr, drag_icon_pixbuf, 0, 0);
    cr->paint();
    return true;
}

void DragIcon::create_drag_icon_pixbuf(const PluginUI& plugin, Glib::RefPtr<Gdk::Colormap> rgba, gx_system::CmdlineOptions& options) {
    Gtk::OffscreenWindow w;
    w.signal_expose_event().connect(sigc::bind(sigc::mem_fun(*this, &DragIcon::window_expose_event), sigc::ref(w)));
    if (rgba) {
	w.set_colormap(rgba);
    }
    Gtk::Widget *r = RackBox::create_drag_widget(plugin, options);
    w.add(*r);
    w.show_all();
    w.get_window()->process_updates(true);
}

static void destroy_data(const guint8 *data) {
    delete[] data;
}

bool DragIcon::window_expose_event(GdkEventExpose *event, Gtk::OffscreenWindow& widget) {
    Cairo::RefPtr<Cairo::Context> cr = widget.get_window()->create_cairo_context();
    cr->set_operator(Cairo::OPERATOR_SOURCE);
    cr->set_source_rgba(0,0,0,0);
    cr->paint();
    Gtk::Widget *child = widget.get_child();
    if (child) {
	widget.propagate_expose(*child, event);
    }
    Cairo::RefPtr<Cairo::Surface> x_surf = cr->get_target();
    int w = gdk_window_get_width(event->window);
    int h = gdk_window_get_height(event->window);
    int dp = 40;
    Cairo::RefPtr<Cairo::LinearGradient> grad = Cairo::LinearGradient::create(w, 0, w-dp, 0);
    grad->add_color_stop_rgba(0, 1, 1, 1, 1);
    grad->add_color_stop_rgba(1, 1, 1, 1, 0);
    cr->rectangle(w-dp, 0, dp, h);
    cr->mask(grad);
    Cairo::RefPtr<Cairo::ImageSurface> i_surf = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, w, h);
    Cairo::RefPtr<Cairo::Context> crt = Cairo::Context::create(i_surf);
    crt->set_operator(Cairo::OPERATOR_SOURCE);
    crt->set_source(x_surf, 0, 0);
    crt->paint();
    guint8 *data = new guint8[w*h*4];
    convert_bgra_to_rgba(i_surf->get_data(), data, w, h);
    drag_icon_pixbuf = Gdk::Pixbuf::create_from_data(data, Gdk::COLORSPACE_RGB, true, 8, w, h, i_surf->get_stride(), sigc::ptr_fun(destroy_data));
    return true;
}


/****************************************************************
 ** class MiniRackBox
 */

Glib::RefPtr<Gtk::SizeGroup> MiniRackBox::szg_label;

Gtk::Widget *MiniRackBox::make_delete_button(RackBox& rb) {
    Gtk::Widget *w;
    if (rb.has_delete()) {
	Gtk::Label *l = new Gtk::Label("\u2a2f");
	l->show();
	Gtk::Button *b = new Gtk::Button();
	b->set_focus_on_click(false);
	b->add(*manage(l));
	b->signal_clicked().connect(sigc::mem_fun(rb, &RackBox::on_kill));
	w = b;
    } else {
	w = new Gtk::Alignment();
    }
    w->set_size_request(20, 15);
    return w;
}

MiniRackBox::MiniRackBox(RackBox& rb, const Glib::RefPtr<Gtk::Action>& action, gx_system::CmdlineOptions& options)
    : Gtk::HBox(), evbox(), mconbox(false, 4), mb_expand_button(), mb_delete_button(), preset_button() {
    if (!szg_label) {
	szg_label = Gtk::SizeGroup::create(Gtk::SIZE_GROUP_HORIZONTAL);
    }
    evbox.set_visible_window(false);
    add(evbox);
    Gtk::HBox *box = new Gtk::HBox();
    evbox.add(*manage(box));
    Gxw::Switch *swtch = new Gxw::Switch("minitoggle");
    swtch->cp_set_var("eqs.on_off");
    //swtch->set_related_action(action);
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(swtch->gobj()), action->gobj());
    Gtk::Alignment *al = new Gtk::Alignment(0.5,0.5);
    al->add(*manage(swtch));
    RackBox::szg->add_widget(*al);
    box->pack_start(*manage(al), Gtk::PACK_SHRINK);
    Gtk::Widget *effect_label = RackBox::make_label(rb.plugin, options);
    szg_label->add_widget(*manage(effect_label));
    al = new Gtk::Alignment();
    al->add(*manage(RackBox::make_bar()));
    box->pack_start(*manage(al), Gtk::PACK_SHRINK);
    box->pack_start(*manage(effect_label), Gtk::PACK_SHRINK);
    Gxw::HSlider *sl = new Gxw::HSlider();
    sl->set_show_value(false);
    sl->set_adjustment(*manage(new Gtk::Adjustment(0,-1,1)));
    mconbox.pack_start(*manage(sl), Gtk::PACK_SHRINK);
    Gtk::Label *l = new Gtk::Label("depth");
    l->set_name("rack_label");
    l->set_size_request(-1,18);
    l->set_alignment(0,1.0);
    mconbox.pack_start(*manage(l), Gtk::PACK_SHRINK, 4);
    box->pack_start(mconbox, Gtk::PACK_EXPAND_WIDGET, 20);
    al = new Gtk::Alignment();
    Gtk::HBox *hb = new Gtk::HBox();
    al->add(*manage(hb));
    mb_expand_button = rb.make_expand_button(true);
    hb->pack_start(*manage(mb_expand_button), Gtk::PACK_SHRINK);
    mb_delete_button = make_delete_button(rb);
    mb_delete_button->set_no_show_all(true);
    hb->pack_start(*manage(mb_delete_button), Gtk::PACK_SHRINK);
    al->set_padding(1, 0, 4, 4);
    pack_end(*manage(al), Gtk::PACK_SHRINK);
    box->pack_end(*manage(RackBox::make_bar(8)), Gtk::PACK_SHRINK);
    preset_button = rb.make_preset_button();
    box->pack_end(*manage(preset_button), Gtk::PACK_SHRINK);
    show_all();
}

void MiniRackBox::set_config_mode(bool mode) {
    evbox.set_above_child(mode);
    if (mode) {
	mconbox.hide();
	preset_button->hide();
	mb_expand_button->hide();
	if (mb_delete_button) {
	    mb_delete_button->show();
	}
    } else {
	mconbox.show();
	preset_button->show();
	mb_expand_button->show();
	if (mb_delete_button) {
	    mb_delete_button->hide();
	}
    }
}

/****************************************************************
 ** class RackBox
 */

Glib::RefPtr<Gtk::SizeGroup> RackBox::szg;

void RackBox::set_paintbox(Gxw::PaintBox& pb, PluginType tp) {
    pb.set_name("rackbox");
    pb.property_paint_func().set_value("rectangle_skin_color_expose");
    pb.set_border_width(4);
}

Gtk::Widget *RackBox::make_label(const PluginUI& plugin, gx_system::CmdlineOptions& options) {
    Gtk::Label *effect_label = new Gtk::Label(plugin.get_name());
    effect_label->set_alignment(0, 0.5);
    effect_label->set_name("rack_effect_label");
    Pango::FontDescription font_desc = effect_label->get_style()->get_font();
    font_desc.set_size(int(7.5*Pango::SCALE));
    font_desc.set_weight(Pango::WEIGHT_BOLD);
    effect_label->modify_font(font_desc);
    if (plugin.get_type() == PLUGIN_TYPE_STEREO) {
	Gtk::HBox *hbox = new Gtk::HBox(false, 4);
	Gtk::Image *e = new Gtk::Image(options.get_style_filepath("stereo.png"));
	hbox->pack_start(*manage(e), Gtk::PACK_SHRINK);
	hbox->pack_start(*manage(effect_label));
	hbox->show_all();
	return hbox;
    } else {
	return effect_label;
    }
}

Gtk::Widget *RackBox::make_bar(int left, int right, bool sens) {
    Gtk::Alignment *al = new Gtk::Alignment(0, 0, 1.0, 1.0);
    al->set_padding(4, 4, left, right);
    Gtk::Button *button = new Gtk::Button();
    button->set_size_request(6,-1);
    button->set_name("effect_reset");
    button->set_sensitive(sens);
    al->add(*manage(button));
    return al;
}

Gtk::Widget *RackBox::create_icon_widget(const PluginUI& plugin, gx_system::CmdlineOptions& options) {
    Gxw::PaintBox *pb = new Gxw::PaintBox(Gtk::ORIENTATION_HORIZONTAL);
    RackBox::set_paintbox(*pb, plugin.get_type());
    Gtk::Widget *effect_label = RackBox::make_label(plugin, options);
    Gtk::Alignment *al = new Gtk::Alignment();
    al->set_padding(0,2,2,0);
    al->add(*manage(effect_label));
    pb->pack_start(*manage(al), Gtk::PACK_SHRINK);
    pb->show_all();
    return pb;
}

Gtk::Widget *RackBox::create_drag_widget(const PluginUI& plugin, gx_system::CmdlineOptions& options) {
    Gxw::PaintBox *pb = new Gxw::PaintBox(Gtk::ORIENTATION_HORIZONTAL);
    RackBox::set_paintbox(*pb, plugin.get_type());
    if (strcmp(plugin.get_id(), "ampstack") == 0) { // FIXME
	pb->property_paint_func().set_value("zac_expose");
    }
    Gxw::Switch *swtch = new Gxw::Switch("minitoggle");
    swtch->cp_set_var("eqs.on_off");
    RackBox::szg->add_widget(*swtch);
    pb->pack_start(*manage(swtch), Gtk::PACK_SHRINK);
    Gtk::Widget *effect_label = RackBox::make_label(plugin, options);
    Gtk::Alignment *al = new Gtk::Alignment();
    al->set_padding(0,0,4,20);
    al->add(*manage(RackBox::make_bar(4, 4, true))); // FIXME: fix style and remove sens parameter
    pb->pack_start(*manage(al), Gtk::PACK_SHRINK);
    pb->pack_start(*manage(effect_label), Gtk::PACK_SHRINK);
    al = new Gtk::Alignment();
    al->set_size_request(50,-1);
    pb->pack_start(*manage(al), Gtk::PACK_SHRINK);
    pb->show_all();
    return pb;
}

RackBox::RackBox(const PluginUI& plugin_, MainWindow& tl, Gtk::Widget* bare)
    : Gtk::VBox(), plugin(plugin_), main(tl), vis(true), config_mode(false), anim_tag(),
      compress(true), delete_button(true), mbox(Gtk::ORIENTATION_HORIZONTAL), on_off_action(Gtk::ToggleAction::create()), minibox(0),
      fbox(0), target(), anim_height(0), drag_icon(), target_height(0), preset_index(-1), presets(),
      box(Gtk::ORIENTATION_HORIZONTAL, 2) {
    if (!szg) {
	szg = Gtk::SizeGroup::create(Gtk::SIZE_GROUP_HORIZONTAL);
    }
    //FIXME fill presets
    if (bare) {
	compress = false;
	delete_button = false;
    }
    set_paintbox(mbox, plugin.get_type());
    minibox = new MiniRackBox(*this, on_off_action, tl.get_options());
    mbox.pack_start(*manage(minibox));
    pack_start(mbox, Gtk::PACK_SHRINK);
    if (bare) {
	add(*manage(bare));
	fbox = bare;
	mbox.property_paint_func().set_value("zac_expose");
    } else {
	Gxw::PaintBox *pb = new Gxw::PaintBox(Gtk::ORIENTATION_HORIZONTAL);
	pb->show();
	set_paintbox(*pb, plugin.get_type());
	pb->pack_start(*manage(make_full_box(tl.get_options())));
	pack_start(*manage(pb), Gtk::PACK_SHRINK);
	fbox = pb;
    }
    init_dnd();
    show();
}

void RackBox::init_dnd() {
    target = "application/x-guitarix-";
    if (plugin.get_type() == PLUGIN_TYPE_MONO) {
	target += "mono";
    } else {
	target += "stereo";
    }
    if (!delete_button) {
	target += "-s";
    }
    mbox.signal_drag_begin().connect(sigc::mem_fun(*this, &RackBox::on_my_drag_begin));
    mbox.signal_drag_end().connect(sigc::mem_fun(*this, &RackBox::on_my_drag_end));
    mbox.signal_drag_data_get().connect(sigc::mem_fun(*this, &RackBox::on_my_drag_data_get));
    mbox.signal_drag_data_delete().connect(sigc::mem_fun(*this, &RackBox::on_my_drag_data_delete));
}

void RackBox::enable_drag(bool v) {
    if (v) {
	std::vector<Gtk::TargetEntry> listTargets;
	listTargets.push_back(Gtk::TargetEntry(target, Gtk::TARGET_SAME_APP, 0));
	mbox.drag_source_set(listTargets, Gdk::BUTTON1_MASK, Gdk::ACTION_MOVE);
    } else {
	mbox.drag_source_unset();
    }
}

bool RackBox::animate_vanish() {
    anim_height -= 7;
    if (anim_height <= 0) {
	hide();
	set_size_request(-1,-1);
	//anim_tag.disconnect(); //FIXME
	return false;
    } else {
	set_size_request(-1, anim_height);
	return true;
    }
}

void RackBox::on_my_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context) {
    int x, y;
    get_pointer(x, y);
    drag_icon = new DragIcon(plugin, context, main.get_options(), x);
    if (!dynamic_cast<RackContainer*>(get_parent())->check_if_animate(*this)) { //FIXME
	hide();
    } else {
	if (anim_tag.connected()) {
	    //Glib::source_remove(anim_tag);
	    anim_tag.disconnect();
	    set_size_request(-1,-1);
	    show();
	}
	anim_height = size_request().height;
	anim_tag = Glib::signal_timeout().connect(sigc::mem_fun(*this, &RackBox::animate_vanish), 20);
    }
}

bool RackBox::animate_create() {
    anim_height += 7;
    if (anim_height >= target_height) {
	set_size_request(-1,-1);
	//anim_tag.disconnect(); //FIXME
	return false;
    } else {
	set_size_request(-1, anim_height);
	return true;
    }
}

void RackBox::animate_insert() {
    if (!dynamic_cast<RackContainer*>(get_parent())->check_if_animate(*this)) { //FIXME
	show();
    } else {
	if (anim_tag.connected()) {
	    hide();
	    //glib.source_remove(self.anim_tag);
	    anim_tag.disconnect();
	    set_size_request(-1,-1);
	}
	target_height = size_request().height;
	set_size_request(-1,0);
	show();
	anim_height = 0;
	anim_tag = Glib::signal_timeout().connect(mem_fun(*this, &RackBox::animate_create), 20);
    }
}

void RackBox::on_my_drag_end(const Glib::RefPtr<Gdk::DragContext>& context) {
    if (drag_icon) {
	delete drag_icon;
	drag_icon = 0;
    }
    animate_insert();
}

void RackBox::on_my_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp) {
    selection.set(target, plugin.get_id());
}

void RackBox::on_my_drag_data_delete(const Glib::RefPtr<Gdk::DragContext>& context) {
    on_kill();
}

void RackBox::on_kill() {
    main.add_icon(plugin.get_id());
    on_off_action->set_active(false);
    delete this;
}

void RackBox::vis_switch(Gtk::Widget& a, Gtk::Widget& b) {
    a.hide();
    b.show();
}

void RackBox::swtch(bool mini) {
    if (mini) {
	vis_switch(*fbox, mbox);
    } else {
	vis_switch(mbox, *fbox);
    }
}

void RackBox::on_expand(bool mini) {
    swtch(mini);
}

void RackBox::set_config_mode(bool mode) {
    config_mode = mode;
    minibox->set_config_mode(mode);
    if (mode) {
	vis = fbox->get_visible();
	if (vis) {
	    swtch(true);
	}
    } else {
	if (vis) {
	    swtch(false);
	}
    }
    enable_drag(mode);
}

Gtk::Button *RackBox::make_expand_button(bool expand) {
    Glib::ustring t;
    if (expand) {
	t = "▶";
    } else {
	t = "▼"; // ▲
    }
    Gtk::Label *l = new Gtk::Label(t);
    l->set_name("rack_slider");
    Gtk::Button *b = new Gtk::Button();
    b->set_focus_on_click(false);
    b->add(*manage(l));
    b->set_size_request(20, 15);
    b->set_name("effect_reset");
    b->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &RackBox::on_expand), !expand));
    return b;
}

void RackBox::on_preset_popup_destroy(Gtk::Menu *w) {
    preset_index = w->property_active();
}

void RackBox::preset_popup() {
    //FIXME delete m
    Gtk::Menu *m = new Gtk::Menu();
    int i = 0;
    for (std::vector<Glib::ustring>::iterator s = presets.begin(); s != presets.end(); ++s) {
	Gtk::CheckMenuItem *c = new Gtk::CheckMenuItem(*s);
	if (i == preset_index) {
	    c->set_active(true);
	}
	m->append(*manage(c));
	++i;
    }
    m->signal_selection_done().connect(sigc::bind(sigc::mem_fun(*this, &RackBox::on_preset_popup_destroy), m));
    m->show_all();
    m->popup(1, gtk_get_current_event_time());
}

Gtk::Button *RackBox::make_preset_button() {
    Gtk::Button *p = new Gtk::Button("p");
    p->set_can_default(false);
    p->set_can_focus(false);
    p->set_size_request(18,18);
    //presets = ["setting %d" % (i+1) for i in range(3)]
    p->signal_clicked().connect(mem_fun(*this, &RackBox::preset_popup));
    return p;
}

void RackBox::pack(Gtk::Widget& child) {
    box.pack_start(child);
}

Gtk::HBox *RackBox::make_full_box(gx_system::CmdlineOptions& options) {
    Gtk::HBox *bx = new Gtk::HBox();
    bx->pack_start(*manage(switcher_vbox(options)), Gtk::PACK_SHRINK);
    box.set_name(plugin.get_id());
    box.set_border_width(4);
    box.property_paint_func().set_value("RackBox_expose");
    bx->pack_start(box);
    Gtk::VBox *vbox = new Gtk::VBox();
    vbox->pack_start(*manage(make_expand_button(false)), Gtk::PACK_SHRINK);
    vbox->pack_start(*manage(make_preset_button()), Gtk::PACK_EXPAND_PADDING);
    Gtk::Alignment *al = new Gtk::Alignment(0.5, 0.5, 1.0, 0.7);
    al->add(*manage(vbox));
    al->set_padding(1, 0, 0, 4);
    bx->pack_end(*manage(al), Gtk::PACK_SHRINK);
    bx->pack_end(*manage(make_bar(4, 8)), Gtk::PACK_SHRINK);
    bx->show_all();
    return bx;
}

Gtk::VBox *RackBox::switcher_vbox(gx_system::CmdlineOptions& options) {
    Gtk::VBox *vbox = new Gtk::VBox();
    Gtk::Widget *effect_label = make_label(plugin, options);
    vbox->pack_start(*manage(effect_label), Gtk::PACK_SHRINK);
    Gtk::HBox *hbox = new Gtk::HBox();
    vbox->pack_start(*manage(hbox));
    Gtk::HBox *hbox2 = new Gtk::HBox();
    hbox->pack_start(*manage(hbox2), Gtk::PACK_SHRINK);
    Gtk::VBox *vbox2 = new Gtk::VBox();
    hbox2->pack_start(*manage(vbox2));
    hbox2->pack_start(*manage(make_bar()), Gtk::PACK_SHRINK);
    Gxw::Switch *swtch = new Gxw::Switch("switchit");
    szg->add_widget(*swtch);
    swtch->cp_set_var("eqs.on_off");
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(swtch->gobj()), GTK_ACTION(on_off_action->gobj()));
    Gtk::Alignment *al = new Gtk::Alignment(0.5,0.5);
    al->add(*manage(swtch));
    vbox2->pack_start(*manage(al));
    return vbox;
}


/****************************************************************
 ** class RackContainer
 */

RackContainer::RackContainer(PluginType tp_, MainWindow& main_)
    : Gtk::VBox(), tp(tp_), main(main_), config_mode(false), in_drag(-2), child_count(0), switch_level(1), targets(),
      hightlight_connection() {
    if (tp == PLUGIN_TYPE_MONO) {
	targets.push_back("application/x-guitarix-mono");
	targets.push_back("application/x-guitarix-mono-s");
	targets.push_back("application/x-gtk-tool-palette-item-mono");
    } else {
	targets.push_back("application/x-guitarix-stereo");
	targets.push_back("application/x-guitarix-stereo-s");
	targets.push_back("application/x-gtk-tool-palette-item-stereo");
    }
    std::vector<Gtk::TargetEntry> listTargets;
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-mono", Gtk::TARGET_SAME_APP, 0));
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-mono-s", Gtk::TARGET_SAME_APP, 1));
    listTargets.push_back(Gtk::TargetEntry("application/x-gtk-tool-palette-item-mono", Gtk::TARGET_SAME_APP, 2));
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-stereo", Gtk::TARGET_SAME_APP, 3));
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-stereo-s", Gtk::TARGET_SAME_APP, 4));
    listTargets.push_back(Gtk::TargetEntry("application/x-gtk-tool-palette-item-stereo", Gtk::TARGET_SAME_APP, 5));
    drag_dest_set(listTargets, Gtk::DEST_DEFAULT_DROP, Gdk::ACTION_MOVE);
    signal_remove().connect(sigc::mem_fun(*this, &RackContainer::on_my_remove));
    show_all();
}

bool RackContainer::drag_highlight_expose(GdkEventExpose *event, int y0) {
    if (!is_drawable()) {
	return false;
    }
    Cairo::RefPtr<Cairo::Context> cr = Glib::wrap(event->window, true)->create_cairo_context();
    cr->set_source_rgb(1.0, 1.0, 1.0);
    int x, y, width, height;
    if (!get_has_window()) {
	Gtk::Allocation a = get_allocation();
	x = a.get_x();
	y = a.get_y();
	width = a.get_width();
	height = a.get_height();
    } else {
	x = 0;
	y = 0;
	Glib::RefPtr<Gdk::Window> w = get_window();
	width = w->get_width();
	height = w->get_height();
    }
    if (y0 < 0) {
	get_style()->paint_shadow(
	    get_window(), Gtk::STATE_NORMAL, Gtk::SHADOW_OUT,
	    Glib::wrap(&event->area), *this, "dnd", x, y, width, height);
	cr->set_line_width(1.0);
	cr->rectangle(x + 0.5, y + 0.5, width - 1, height - 1);
    } else {
	y0 -= 1;
	y0 = std::max(y0, y);
	cr->set_line_width(1.0);
	cr->move_to(x+0.5, y0+0.5);
	cr->rel_line_to(width - 1, 0);
    }
    cr->stroke();
    return false;
}

struct childpos {
    int y0, y1;
    Gtk::Widget *child;
    childpos(int y0_, int y1_, Gtk::Widget* ch): y0(y0_), y1(y1_), child(ch) {}
    bool operator<(const childpos& p) { return y0 < p.y0; }
};

void RackContainer::find_index(int x, int y, int* len, int *ypos) {
    std::list<childpos> l;
    std::vector<RackBox*> children = get_children();
    for (std::vector<RackBox*>::iterator ch = children.begin(); ch != children.end(); ++ch) {
	Gtk::Allocation a = (*ch)->get_allocation();
	int ht;
	if (!(*ch)->get_visible()) {
	    ht = 0;
	} else {
	    ht = a.get_height();
	}
	l.push_back(childpos(a.get_y(), a.get_y()+ht, (*ch)));
    }
    if (l.empty()) {
	*len = -1;
	*ypos = -1;
	return;
    }
    l.sort();
    Gtk::Allocation a0 = get_allocation();
    y += a0.get_y();
    int sy = l.begin()->y0;
    int i = 0;
    for (std::list<childpos>::iterator cp = l.begin(); cp != l.end(); ++cp) {
	if (y < (cp->y0 + cp->y1) / 2) {
	    *len = i;
	    *ypos = (cp->y0+sy)/2;
	    return;
	}
	sy = cp->y1;
	++i;
    }
    *len = l.size();
    *ypos = sy;
}

void RackContainer::on_my_remove(Gtk::Widget *ch) {
    child_count -= 1;
    //assert self.child_count >= 0
    if (child_count == 0 && tp == PLUGIN_TYPE_MONO && main.show_plugin_bar_action->get_active()) {
	main.get_monorackcontainer().set_size_request(-1, 20);
    }
}

bool RackContainer::check_targets(const std::vector<std::string>& tgts) {
    for (std::vector<std::string>::iterator t = targets.begin(); t != targets.end(); ++t) {
	for (std::vector<std::string>::const_iterator t2 = tgts.begin(); t2 != tgts.end(); ++t2) {
	    if (*t == *t2) {
		return true;
	    }
	}
    }
    return false;
}

bool RackContainer::on_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp) {
    if (!check_targets(context->get_targets())) {
	return false;
    }
    context->drag_status(Gdk::ACTION_MOVE, timestamp);
    int i, ind;
    find_index(x, y, &i, &ind);
    if (in_drag == ind) {
	return true;
    }
    if (in_drag > -2) {
	hightlight_connection.disconnect();
    }
    hightlight_connection = signal_expose_event().connect(sigc::bind(sigc::mem_fun(*this, &RackContainer::drag_highlight_expose), ind), true);
    queue_draw();
    in_drag = ind;
    return true;
}

void RackContainer::on_drag_leave(const Glib::RefPtr<Gdk::DragContext>& context, guint timestamp) {
    if (in_drag > -2) {
	hightlight_connection.disconnect();
	queue_draw();
	in_drag = -2;
    }
}

void RackContainer::on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, guint info, guint timestamp) {
    int i, ind;
    find_index(x, y, &i, &ind);
    std::string dtype = data.get_data_type();
    if (dtype == "application/x-gtk-tool-palette-item-mono" || dtype == "application/x-gtk-tool-palette-item-stereo") {
	main.add_rackbox(*main.get_plugin(data.get_data_as_string()), false, i, true);
    } else {
	reorder(data.get_data_as_string(), i);
	context->drag_status(Gdk::ACTION_COPY, timestamp);
    }
}

void RackContainer::show_entries() {
    Glib::ListHandle<RackBox*> l = get_children();
    for (Glib::ListHandle<RackBox*>::iterator ch = l.begin(); ch != l.end(); ++ch) {
	(*ch)->show();
    }
}

void RackContainer::hide_entries() {
    Glib::ListHandle<RackBox*> l = get_children();
    for (Glib::ListHandle<RackBox*>::iterator ch = l.begin(); ch != l.end(); ++ch) {
	if ((*ch)->can_compress()) {
	    (*ch)->hide();
	}
    }
}

void RackContainer::reorder(const std::string& name, int pos) {
    std::vector<RackBox*> l = get_children();
    int i = 0;
    RackBox *r = 0;
    for (std::vector<RackBox*>::iterator v = l.begin(); v != l.end(); ++v) {
	if ((*v)->get_id() == name) {
	    if (pos > i) {
		pos -= 1;
	    }
	    if (i == pos) {
		return;
	    }
	    r = *v;
	    break;
	}
	++i;
    }
    if (!r) {
	//FIXME errormessage
	return;
    }
    reorder_child(*r, pos);
}

void RackContainer::on_add(Widget *ch) {
    add(*dynamic_cast<RackBox*>(ch));
}

void RackContainer::add(RackBox& r, int pos) {
    pack_start(r, Gtk::PACK_SHRINK);
    ++child_count;
    reorder_child(r, pos);
    if (config_mode) {
	r.set_config_mode(true);
    }
}

void RackContainer::set_config_mode(bool mode) {
    config_mode = mode;
    std::vector<RackBox*> l = get_children();
    for (std::vector<RackBox*>::iterator c = l.begin(); c != l.end(); ++c) {
	(*c)->set_config_mode(mode);
    }
}

bool RackContainer::check_if_animate(const RackBox& rackbox) {
    std::vector<RackBox*> l = get_children();
    if (l.empty()) {
	return true;
    }
    if (l[l.size()-1] != &rackbox) {
	return true;
    }
    // is last child
    return main.check_if_rack_container_size_animate(*this);
}

void RackContainer::compress_all() {
    std::vector<RackBox*> l = get_children();
    for (std::vector<RackBox*>::iterator c = l.begin(); c != l.end(); ++c) {
	if ((*c)->can_compress()) {
	    (*c)->swtch(true);
	}
    }
}

void RackContainer::expand_all() {
    std::vector<RackBox*> l = get_children();
    for (std::vector<RackBox*>::iterator c = l.begin(); c != l.end(); ++c) {
	if ((*c)->can_compress()) {
	    (*c)->swtch(false);
	}
    }
}

bool RackContainer::empty() const {
    return get_children().empty();
}


/****************************************************************
 ** class Freezer
 */

Freezer::Freezer()
    : window(0), tag(), size_x(-1), size_y(-1) {
}

Freezer::~Freezer() {
    thaw();
}

void Freezer::freeze(Gtk::Window *w, int width, int height) {
    if (window) {
	thaw();
    }
    size_x = width;
    size_y = height;
    window = w;
    //self.tag = None
    Glib::RefPtr<Gdk::Window> win = window->get_window();
    if (win) {
	win->freeze_updates();
	tag = Glib::signal_timeout().connect(sigc::mem_fun(*this, &Freezer::thaw_timeout), 500);
    }
}

void Freezer::freeze_and_size_request(Gtk::Window *w, int width, int height) {
    int wd, ht;
    w->get_size(wd, ht);
    if (wd >= width && ht == height) {
	return;
    }
    freeze(w, width, height);
    w->set_size_request(width, height);
}

bool Freezer::thaw_timeout() {
    //print "TM", self.size  // FIXME do logging
    //self.tag = None
    if (size_y != -1) {
	window->set_size_request(-1,-1);
    }
    size_x = size_y = -1;
    Glib::RefPtr<Gdk::Window> win = window->get_window();
    window = 0;
    if (!win) {
	return false;
    }
    win->thaw_updates();
    return false;
}

void Freezer::thaw() {
    if (!tag.connected()) {
	return;
    }
    tag.disconnect();
    //glib.source_remove(self.tag)
    //self.tag = None
    //self.size = None
    size_x = size_y = -1;
    Glib::RefPtr<Gdk::Window> win = window->get_window();
    window = 0;
    if (!win) {
	return;
    }
    win->thaw_updates();
}

bool Freezer::check_thaw(int width, int height) {
    if (size_x == -1) {
	return true;
    }
    //print self.size, (width, height), self.widget.window.get_state()
    Glib::RefPtr<Gdk::Window> win = window->get_window();
    if (!win) {
	return false;
    }
    if (win->get_state()) {
	thaw();
	return true;
    }
    if (size_y == -1) {
	if (size_x == width) {
	    window->set_size_request(-1,-1);
	    thaw();
	    return true;
	}
    }
    if (size_x <= width && size_y == height) {
	window->set_size_request(-1,-1);
	thaw();
	return true;
    }
    return false;
}


/****************************************************************
 ** class MainWindow
 */

void update_scrolled_window(Gtk::ScrolledWindow& w) {
    Gtk::PolicyType hp, vp;
    w.get_policy(hp, vp);
    w.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    w.set_policy(hp, vp);
}

/*
** moving / hiding / showing parts of the UI
*/

void MainWindow::maybe_shrink_horizontally() {
    Glib::RefPtr<Gdk::Window> w = window->get_window();
    if (!w) {
	return;
    }
    int state = w->get_state();
    if (state & (Gdk::WINDOW_STATE_MAXIMIZED | Gdk::WINDOW_STATE_FULLSCREEN)) {
	return;
    }
    Gtk::Requisition req;
    window->size_request(req);
    int x, y;
    window->get_position(x, y);
    gdk_window_set_geometry_hints(w->gobj(), 0, static_cast<GdkWindowHints>(0));
    w->move_resize(x, y, req.width, std::max(req.height, window_height));
    if (!state) {
	freezer.freeze_until_width_update(window, req.width);
    }
}

void MainWindow::on_show_tuner() {
    bool v = tuner_action->get_active();
    if (v) {
	tunerbox->show();
    } else {
	tunerbox->hide();
    }
    live_play->display_tuner(v);
    update_scrolled_window(*vrack_scrolledbox);
}

void MainWindow::load_widget_pointers() {
    bld->get_toplevel("MainWindow", window);
    bld->find_widget("tunerbox", tunerbox);
    bld->find_widget("tunerbox", tunerbox);
    bld->find_widget("vrack_scrolledbox", vrack_scrolledbox);
    bld->find_widget("stereorackcontainerH", stereorackcontainerH);
    bld->find_widget("stereorackcontainerV", stereorackcontainerV);
    bld->find_widget("rackcontainer", rackcontainer);
    bld->find_widget("stereorackbox", stereorackbox);
    bld->find_widget("monorackcontainer", monocontainer);
    bld->find_widget("monoampcontainer:ampdetails", monoampcontainer);
    bld->find_widget("main_vpaned", main_vpaned);
    bld->find_widget("amp_toplevel_box", amp_toplevel_box);
    bld->find_widget("monobox", monobox);
    bld->find_widget("upper_rackbox", upper_rackbox);
    bld->find_widget("preset_scrolledbox", preset_scrolledbox);
    bld->find_widget("effects_frame_paintbox", effects_frame_paintbox);
    bld->find_widget("status_image", status_image);
    bld->find_widget("jackd_image", jackd_image);
    bld->find_widget("logstate_image", logstate_image);
    bld->find_widget("menubox", menubox);
    bld->find_widget("show_rack:barbutton", show_rack_button);
    bld->find_widget("liveplay:barbutton", liveplay_button);
    bld->find_widget("tuner:barbutton", tuner_button);
    bld->find_widget("effects:barbutton", effects_button);
    bld->find_widget("presets:barbutton", presets_button);
    bld->find_widget("compress:barbutton", compress_button);
    bld->find_widget("expand:barbutton", expand_button);
    bld->find_widget("effects_toolpalette", effects_toolpalette);
    bld->find_widget("amp_background:ampbox", amp_background);
}

bool MainWindow::is_variable_size() {
    return presets_action->get_active() || show_rack_action->get_active();
}

void MainWindow::maybe_change_resizable() {
    if (window->get_window()->get_state() != 0) {
	return;
    }
    if (!is_variable_size() && window->get_resizable()) {
	window->set_resizable(false);
    } else if (!window->get_resizable()) {
	window->set_resizable(true);
    }
}

void MainWindow::on_show_rack() {
    Gtk::Widget *w;
    if (get_dir() == 0) {
	// vertically
	w = stereorackcontainerV;
    } else {
	w = stereorackbox;
    }
    bool v = show_rack_action->get_active();
    rackv_action->set_sensitive(v);
    rackh_action->set_sensitive(v);
    if (v) {
	//main_vpaned->child_set_property(amp_toplevel_box, "resize", true);
	child_set_property(*main_vpaned, *amp_toplevel_box, "resize", true);
	main_vpaned->set_position(oldpos);
	w->show();
	monoampcontainer->show();
	monorackcontainer.show_entries();
	vrack_scrolledbox->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
	vrack_scrolledbox->set_size_request(scrl_size_x, scrl_size_y);
	if (window->get_window()->get_state() == 0) {
	    Gtk::Requisition req;
	    window->size_request(req);
	    req.height = max(req.height, window_height);
	    freezer.freeze_and_size_request(window, req.width, req.height);
	}
    } else {
	oldpos = main_vpaned->get_position();
	child_set_property(*main_vpaned, *amp_toplevel_box, "resize", false);
	main_vpaned->set_position(0);
	int wd;
	window->get_size(wd, window_height);
	//#print "##", self.window_height
	w->hide();
	monoampcontainer->hide();
	monorackcontainer.hide_entries();
	vrack_scrolledbox->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_NEVER);
	vrack_scrolledbox->get_size_request(scrl_size_x, scrl_size_y);
	vrack_scrolledbox->set_size_request(-1,-1);
	maybe_shrink_horizontally();
    }
    maybe_change_resizable();
}

void MainWindow::on_compress_all() {
    monorackcontainer.compress_all();
    stereorackcontainer.compress_all();
}

void MainWindow::on_expand_all() {
    monorackcontainer.expand_all();
    stereorackcontainer.expand_all();
}

void MainWindow::on_show_plugin_bar() {
    bool v = show_plugin_bar_action->get_active();
    show_rack_action->set_sensitive(!v);
    tuner_action->set_sensitive(!v);
    presets_action->set_sensitive(!v);
    compress_action->set_sensitive(!v);
    expand_action->set_sensitive(!v);
    Gtk::Requisition req;
    monobox->size_request(req);
    stereorackcontainer.set_config_mode(v);
    monorackcontainer.set_config_mode(v);
    if (v) {
	pre_act = presets_action->get_active();
	if (pre_act) {
	    preset_scrolledbox->hide();
	    presets_action->set_active(false);
	}
	show_rack_action->set_active(true);
	effects_frame_paintbox->show();
	upper_rackbox->hide();
	Gtk::Requisition req2;
	effects_frame_paintbox->size_request(req2);
	if (get_dir() == 0) {
	    // vertically
	    monobox->set_size_request(req.width-req2.width,-1);
	    if (stereorackcontainer.empty()) {
		change_expand(*monobox, true);
	    } else if (monorackcontainer.empty()) {
		monorackcontainer.set_size_request(-1, 20);
	    }
	} else {
	    monobox->set_size_request(req.width-req2.width/2,-1);
	    change_expand(*monobox, true);
	}
    } else {
	if (pre_act) {
	    presets_action->set_active(true);
	}
	monobox->set_size_request(-1,-1);
	effects_frame_paintbox->hide();
	upper_rackbox->show();
	change_expand(*monobox, false);
	monorackcontainer.set_size_request(-1, -1);
    }
    update_scrolled_window(*vrack_scrolledbox);
    update_scrolled_window(*stereorackbox);
    maybe_shrink_horizontally();
    //show_size_request(self.window)
}

void MainWindow::move_widget(Gtk::Widget& w, Gtk::Box& b1, Gtk::Box& b2) {
    // reparent does not always work when child is hidden
    // (sometimes wrong position when shown later),
    // use remove / add
    b1.remove(w);
    b1.hide();
    b2.pack_start(w);
    b2.show();
}

int MainWindow::get_dir() const {
    return rackv_action->get_current_value();
}

void MainWindow::change_expand(Gtk::Widget& w, bool value) {
    Gtk::Box *p = dynamic_cast<Gtk::Box*>(w.get_parent());
    int expand, fill;
    unsigned int padding;
    GtkPackType pack_type;
    gtk_box_query_child_packing(p->gobj(), w.gobj(), &expand, &fill, &padding, &pack_type);
    gtk_box_set_child_packing(p->gobj(), w.gobj(), value, fill, padding, pack_type);
}

void MainWindow::on_dir_changed(Glib::RefPtr<Gtk::RadioAction> act) {
    if (act->get_current_value()) {
	// horizontally
	move_widget(stereorackcontainer, *stereorackcontainerV, *stereorackcontainerH);
	change_expand(*monobox, true);
	stereorackbox->show();
    } else {
	move_widget(stereorackcontainer, *stereorackcontainerH, *stereorackcontainerV);
	stereorackbox->hide();
	if (show_plugin_bar_action->get_active()) {
	    change_expand(*monobox, stereorackcontainer.empty());
	    if (monorackcontainer.empty()) {
		monorackcontainer.set_size_request(-1, 20);
	    }
	} else {
	    if (!stereorackcontainer.empty()) {
		change_expand(*monobox, false);
	    }
	}
	maybe_shrink_horizontally();
    }
}

void MainWindow::on_configure_event(GdkEventConfigure *ev) {
    // print ev.x, ev.y, ev.width, ev.height
    if (freezer.check_thaw(ev->width, ev->height)) {
	if (is_variable_size()) {
	    window_height = ev->height;
	}
    }
}

void MainWindow::add_rackbox_internal(const PluginUI& plugin, Gtk::Widget *widget, bool mini, int pos, bool animate, Gtk::Widget *bare) {
    RackBox *r = new RackBox(plugin, *this, bare);
    if (mini) {
	r->swtch(true);
    }
    if (widget) {
	r->pack(*manage(widget));
    }
    if (plugin.get_type() == PLUGIN_TYPE_MONO) {
	monorackcontainer.add(*manage(r), pos);
	monorackcontainer.set_size_request(-1, -1);
    } else {
	stereorackcontainer.add(*manage(r), pos);
    }
    if (animate) {
	r->animate_insert();
    }
}

Gtk::Widget *load_rack_ui(const std::string& fname, gx_ui::GxUI& ui) {
    const char *id_list[] = {"rackbox", 0};
    Glib::RefPtr<gx_gui::GxBuilder> bld = gx_gui::GxBuilder::create_from_file(fname, &ui, id_list);
    Gtk::Widget *w;
    bld->get_toplevel("rackbox", w);
    return w;
}

void MainWindow::add_rackbox(const PluginUI& pl, bool mini, int pos, bool animate) {
    Gtk::Widget *widget = 0;
    if (!pl.fname.empty()) {
	widget = load_rack_ui(pl.fname, ui);
    }
    add_rackbox_internal(pl, widget, mini, pos, animate);
}

bool MainWindow::check_if_rack_container_size_animate(const RackContainer& rackcontainer) const {
    if (&rackcontainer == &monorackcontainer && get_dir() == 0 && !stereorackcontainer.empty()) {
	// non-empty stereo box below
	return true;
    }
    return false;
}

void MainWindow::add_icon(const std::string& name) {
    plugin_dict[name]->toolitem->show();
}

void MainWindow::on_show_values() {
    std::string s =
	"style \"ShowValue\n\" {\n"
	"  GxRegler::show-value = " + gx_system::to_string(show_values_action->get_active()) + "\n"
	"}\n"
	"class \"*GxRegler*\" style:highest \"ShowValue\"\n";
    gtk_rc_parse_string(s.c_str());
    gtk_rc_reset_styles(gtk_settings_get_default());
}

void MainWindow::on_preset_action() {
    maybe_change_resizable();
    bool v = presets_action->get_active();
    preset_window->on_preset_select(v);
    if (v && !show_rack_action->get_active()) {
	Gtk::Requisition req;
	window->size_request(req);
	int x, y;
	window->get_position(x, y);
	while (Gtk::Main::events_pending()) {
	    Gtk::Main::iteration();
	}
	window->get_window()->move_resize(x, y, req.width, max(req.height, window_height));
    }
}

/*
** UI initialization
*/

void MainWindow::add_toolitem(PluginUI& pl, Gtk::ToolItemGroup *gw) {
    Gtk::ToolItem *tb = new Gtk::ToolItem();
    tb->set_use_drag_window(true);
    tb->signal_drag_begin().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ti_drag_begin), sigc::ref(pl)));
    tb->signal_drag_end().connect(sigc::mem_fun(*this, &MainWindow::on_ti_drag_end));
    tb->signal_drag_data_delete().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ti_drag_data_delete), pl.get_id()));
    tb->signal_button_press_event().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ti_button_press), pl.get_id()));
    std::vector<Gtk::TargetEntry> listTargets;
    if (pl.get_type() == PLUGIN_TYPE_MONO) {
	listTargets.push_back(Gtk::TargetEntry("application/x-gtk-tool-palette-item-mono", Gtk::TARGET_SAME_APP, 0));
    } else {
	listTargets.push_back(Gtk::TargetEntry("application/x-gtk-tool-palette-item-stereo", Gtk::TARGET_SAME_APP, 0));
    }
    tb->drag_source_set(listTargets, Gdk::BUTTON1_MASK, Gdk::ACTION_MOVE);
    tb->signal_drag_data_get().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::on_ti_drag_data_get), pl.get_id()));
    Gtk::Image *img = new Gtk::Image(pl.icon);
    if (!pl.tooltip.empty()) {
	img->set_tooltip_text(pl.tooltip);
    }
    tb->add(*manage(img));
    pl.toolitem = tb;
    gw->add(*manage(tb));
    pl.group = gw;
}

bool MainWindow::on_visibility_notify(GdkEventVisibility *ev) {
    bool v = ev->state != GDK_VISIBILITY_FULLY_OBSCURED;
    if (v == is_visible) {
	return false;
    }
    is_visible = v;
    return false;
}

void MainWindow::on_live_play() {
    live_play->on_live_play(live_play_action);
}

void MainWindow::on_ti_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context, const PluginUI& plugin) {
    drag_icon = new DragIcon(plugin, context, options);
}

void MainWindow::on_ti_drag_end(const Glib::RefPtr<Gdk::DragContext>& context) {
    if (drag_icon) {
	delete drag_icon;
	drag_icon = 0;
    }
}

void MainWindow::on_ti_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp, const char *effect_id) {
    selection.set(*context->get_targets().begin(), effect_id);
}

void MainWindow::hide_effect(const std::string& name) {
    plugin_dict[name]->toolitem->hide();
}

void MainWindow::on_ti_drag_data_delete(const Glib::RefPtr<Gdk::DragContext>& context, const char *effect_id) {
    hide_effect(effect_id);
}

bool MainWindow::on_ti_button_press(GdkEventButton *ev, const char *effect_id) {
    if (ev->type == GDK_2BUTTON_PRESS) {
	add_rackbox(*get_plugin(effect_id), false, -1, true);
	hide_effect(effect_id);
	return true;
    }
    return false;
}

void MainWindow::on_tp_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, int info, int timestamp) {
    add_icon(data.get_data_as_string());
    get_plugin(data.get_data_as_string())->group->set_collapsed(false);
}

const char *menudef =
    "<ui>\n"
    "  <menubar>\n"
    "    <menu name=\"engine\" action=\"EngineMenuAction\">\n"
    "      <menuitem name=\"quit\" action=\"QuitAction\" />\n"
    "    </menu>\n"
    "    <menu name=\"presets\" action=\"PresetsMenuAction\">\n"
    "      <menuitem name=\"select_preset\" action=\"PresetsAction\" />\n"
    "    </menu>\n"
    "    <menu name=\"plugins\" action=\"PluginsMenuAction\">\n"
    "      <menuitem name=\"show_plugin_bar\" action=\"ShowPluginBarAction\" />\n"
    "      <menuitem name=\"show_rack\" action=\"ShowRackAction\" />\n"
    "      <menuitem name=\"compress_all\" action=\"CompressAction\" />\n"
    "      <menuitem name=\"expand_all\" action=\"ExpandAction\" />\n"
    "      <menuitem name=\"order_rack_vertically\" action=\"RackVAction\" />\n"
    "      <menuitem name=\"order_rack_horizontally\" action=\"RackHAction\" />\n"
    "    </menu>\n"
    "    <menu name=\"tube\" action=\"TubeMenuAction\">\n"
    "    </menu>\n"
    "    <menu name=\"options\" action=\"OptionsMenuAction\">\n"
    "      <menuitem name=\"tuner\" action=\"TunerAction\" />\n"
    "      <menuitem name=\"values\" action=\"ShowValuesAction\" />\n"
    "      <menuitem name=\"live display\" action=\"LiveplayAction\" />\n"
    "    </menu>\n"
    "    <menu name=\"about\" action=\"AboutMenuAction\">\n"
    "    </menu>\n"
    "  </menubar>\n"
    "</ui>\n";

Glib::RefPtr<Gtk::UIManager> MainWindow::create_menu(Glib::RefPtr<Gtk::ActionGroup>& actiongroup) {
    Glib::RefPtr<Gtk::UIManager> uimanager = Gtk::UIManager::create();
    // Create actions
    actiongroup->add(Gtk::Action::create("EngineMenuAction","_Engine"));
    actiongroup->add(Gtk::Action::create("PresetsMenuAction","_Presets"));
    actiongroup->add(Gtk::Action::create("PluginsMenuAction","P_lugins"));
    actiongroup->add(Gtk::Action::create("TubeMenuAction","_Tube"));
    actiongroup->add(Gtk::Action::create("OptionsMenuAction","_Options"));
    actiongroup->add(Gtk::Action::create("AboutMenuAction","_About"));
    actiongroup->add(Gtk::Action::create("QuitAction","_Quit"),Gtk::AccelKey("<Control>q"),sigc::ptr_fun(Gtk::Main::quit));
    compress_action = Gtk::Action::create("CompressAction","_Compress all");
    actiongroup->add(compress_action,Gtk::AccelKey("<control>c"),sigc::mem_fun(*this, &MainWindow::on_compress_all));
    expand_action = Gtk::Action::create("ExpandAction","E_xpand all");
    actiongroup->add(expand_action, Gtk::AccelKey("<control>e"),sigc::mem_fun(*this, &MainWindow::on_expand_all));
    // Create a ToggleAction, etc.
    show_plugin_bar_action = Gtk::ToggleAction::create("ShowPluginBarAction","Show _Plugin Bar","",true);
    actiongroup->add(show_plugin_bar_action, Gtk::AccelKey("<Control>b"), sigc::mem_fun(*this, &MainWindow::on_show_plugin_bar));
    show_rack_action = Gtk::ToggleAction::create("ShowRackAction","Show _Rack","",true);
    actiongroup->add(show_rack_action, Gtk::AccelKey("<Control>r"),sigc::mem_fun(*this, &MainWindow::on_show_rack));
    live_play_action = Gtk::ToggleAction::create("LiveplayAction","_Live Display");
    actiongroup->add(live_play_action, Gtk::AccelKey("<Control>l"),sigc::mem_fun(*this, &MainWindow::on_live_play));
    tuner_action = Gtk::ToggleAction::create("TunerAction","_Tuner","",true);
    actiongroup->add(tuner_action,Gtk::AccelKey("<Control>t"),sigc::mem_fun(*this, &MainWindow::on_show_tuner));
    show_values_action = Gtk::ToggleAction::create("ShowValuesAction","_Show Values");
    actiongroup->add(show_values_action, Gtk::AccelKey("<Control>s"), sigc::mem_fun(*this, &MainWindow::on_show_values));
    presets_action = Gtk::ToggleAction::create("PresetsAction","_Preset Selection");
    actiongroup->add(presets_action, Gtk::AccelKey("<control>p"), sigc::mem_fun(*this, &MainWindow::on_preset_action));
    // Create some RadioActions
    rackv_action = Gtk::RadioAction::create(dir_group, "RackVAction", "Order Rack Vertically");
    rackv_action->property_value().set_value(0);
    actiongroup->add(rackv_action, Gtk::AccelKey("<Control>v"));
    rackh_action = Gtk::RadioAction::create(dir_group, "RackHAction", "Order Rack Horizontally");
    rackh_action->property_value().set_value(1);
    actiongroup->add(rackh_action, Gtk::AccelKey("<Control>h"));
    rackh_action->set_active(true);
    rackv_action->signal_changed().connect(sigc::mem_fun(*this, &MainWindow::on_dir_changed));
    // Add the actiongroup to the uimanager
    uimanager->insert_action_group(actiongroup);
    uimanager->add_ui_from_string(menudef);
    return uimanager;
}

int get_current_workarea_height_from_desktop(GdkWindow *root) {
    // use "xprop -root" to view desktop properties
    GdkAtom actual_type, atom_cardinal;
    gint actual_format;
    gint num_items;
    int *ret_data_ptr;
    int idx;
    atom_cardinal = gdk_atom_intern("CARDINAL", false);
    if (!gdk_property_get(
	    root, gdk_atom_intern("_NET_CURRENT_DESKTOP", false), atom_cardinal,
	    0, 1, false, &actual_type, &actual_format, &num_items,
	    (guchar**)&ret_data_ptr)) {
	return -1;
    }
    idx = *ret_data_ptr * 4 + 3; // [x, y, width, height] * desktop_count
    g_free(ret_data_ptr);
    if (!gdk_property_get(
	    root, gdk_atom_intern("_NET_WORKAREA", false), atom_cardinal,
	    idx, 1, false, &actual_type, &actual_format, &num_items,
	    (guchar**)&ret_data_ptr)) {
	return -1;
    }
    if (idx >= num_items) {
	//??
	return -1;
    }
    int height = *ret_data_ptr;
    g_free(ret_data_ptr);
    return height;
}

int get_current_workarea_height() {
    // Helper fetching the current workarea (i.e. usable space) size
    GdkWindow *root = gdk_get_default_root_window();
    int height = get_current_workarea_height_from_desktop(root);
    if (height > 0) {
	return height;
    }
    int x, y, width, depth;
    gdk_window_get_geometry(root, &x, &y, &width, &height, &depth);
    return height;
}

void MainWindow::clear_box(Gtk::Container& box) {
    std::vector<Gtk::Widget*> l = box.get_children();
    for (std::vector<Gtk::Widget*>::iterator p = l.begin(); p != l.end(); ++p) {
	box.remove(**p);
    }
}

struct PluginDesc {
    Glib::ustring group;
    std::vector<PluginUI*> *plugins;
    PluginDesc(const Glib::ustring& g, std::vector<PluginUI*> *p)
	: group(g), plugins(p) {}
};

std::vector<PluginDesc*>& get_pluginlist(const gx_engine::PluginList& pl, gx_system::CmdlineOptions& options) {
    //FIXME free list
    static std::vector<PluginDesc*> l;
    std::vector<PluginUI*> *p;

    p = new std::vector<PluginUI*>;
    p->push_back(new PluginUI(pl, "low_highpass"));
    p->push_back(new PluginUI(pl, "eqs"));
    p->push_back(new PluginUI(pl, "IR"));
    p->push_back(new PluginUI(pl, "biquad"));
    p->push_back(new PluginUI(pl, "feedback"));
    p->push_back(new PluginUI(pl, "amp.tonestack", options.get_builder_filepath("tonestack_ui.glade")));
    p->push_back(new PluginUI(pl, "cab"));
    p->push_back(new PluginUI(pl, "moog"));
    p->push_back(new PluginUI(pl, "tonemodul"));
    l.push_back(new PluginDesc("Tone control", p));

    p = new std::vector<PluginUI*>;
    p->push_back(new PluginUI(pl, "gx_distortion"));
    p->push_back(new PluginUI(pl, "overdrive"));
    p->push_back(new PluginUI(pl, "ampmodul"));
    l.push_back(new PluginDesc("Distortion", p));

    p = new std::vector<PluginUI*>;
    p->push_back(new PluginUI(pl, "freeverb"));
    p->push_back(new PluginUI(pl, "jconv"));
    p->push_back(new PluginUI(pl, "stereoverb"));
    p->push_back(new PluginUI(pl, "zita_rev1", options.get_builder_filepath("zita_rev1_ui.glade"), "High Quality Reverb"));
    l.push_back(new PluginDesc("Reverb", p));

    p = new std::vector<PluginUI*>;
    p->push_back(new PluginUI(pl, "echo"));
    p->push_back(new PluginUI(pl, "delay"));
    p->push_back(new PluginUI(pl, "stereodelay"));
    p->push_back(new PluginUI(pl, "stereoecho"));
    l.push_back(new PluginDesc("Echo / Delay", p));

    p = new std::vector<PluginUI*>;
    p->push_back(new PluginUI(pl, "tremolo", options.get_builder_filepath("tremolo_ui.glade")));
    p->push_back(new PluginUI(pl, "phaser_mono"));
    p->push_back(new PluginUI(pl, "chorus_mono"));
    p->push_back(new PluginUI(pl, "flanger_mono"));
    p->push_back(new PluginUI(pl, "chorus"));
    p->push_back(new PluginUI(pl, "flanger"));
    p->push_back(new PluginUI(pl, "phaser"));
    //p->push_back(new PluginUI(pl, PLUGIN_TYPE_STEREO, "univibe"));
    l.push_back(new PluginDesc("Modulation", p));

    p = new std::vector<PluginUI*>;
    p->push_back(new PluginUI(pl, "crybaby", options.get_builder_filepath("crybaby_ui.glade")));
    //p->push_back(new PluginUI(pl, PLUGIN_TYPE_MONO, "crybaby2"));
    p->push_back(new PluginUI(pl, "compressor"));
    l.push_back(new PluginDesc("Guitar Effects", p));

    p = new std::vector<PluginUI*>;
    p->push_back(new PluginUI(pl, "oscilloscope"));
    p->push_back(new PluginUI(pl, "midi_out"));
    l.push_back(new PluginDesc("Misc", p));

    return l;
}

void make_icons(std::map<std::string, PluginUI*>& plugin_dict, gx_system::CmdlineOptions& options) {
    Gtk::OffscreenWindow w;
    Glib::RefPtr<Gdk::Screen> screen = w.get_screen();
    Glib::RefPtr<Gdk::Colormap> rgba = screen->get_rgba_colormap();
    if (rgba) {
        w.set_colormap(rgba);
    }
    Gtk::VBox vb;
    w.add(vb);
    Glib::RefPtr<Gtk::SizeGroup> sz = Gtk::SizeGroup::create(Gtk::SIZE_GROUP_BOTH);
    std::vector<std::pair<PluginUI*,Gtk::Widget*> > l;
    for (std::map<std::string, PluginUI*>::iterator i = plugin_dict.begin(); i != plugin_dict.end(); ++i) {
        Gtk::Widget *r = RackBox::create_icon_widget(*i->second, options);
        r->hide();
        r->set_no_show_all(true);
        vb.add(*manage(r));
        sz->add_widget(*r);
	l.push_back(std::pair<PluginUI*,Gtk::Widget*>(i->second, r));
    }
    for (std::vector<std::pair<PluginUI*,Gtk::Widget*> >::iterator i = l.begin(); i != l.end(); ++i) {
        i->second->show();
        w.show_all();
	while (Gtk::Main::events_pending()) {
	    Gtk::Main::iteration();
	}
        //w.get_window()->process_updates(true);
	i->first->icon = w.get_pixbuf();
        i->second->hide();
    }
    //w.destroy();
}

MainWindow::MainWindow(gx_engine::GxEngine& engine_, gx_system::CmdlineOptions& options_, gx_engine::ParamMap& pmap_)
    : sigc::trackable(), window_height(0), freezer(), bld(), oldpos(0), scrl_size_x(-1), scrl_size_y(-1),
      monorackcontainer(PLUGIN_TYPE_MONO, *this), stereorackcontainer(PLUGIN_TYPE_STEREO, *this),
      pre_act(false), is_visible(false), drag_icon(0), plugin_dict(), actiongroup(), uimanager(),
      ui(), options(options_), pmap(pmap_), engine(engine_), jack(engine),
      gx_settings(options, jack, engine.convolver, gx_engine::midi_std_ctr, gx_engine::controller_map, engine, pmap_),
      mainamp_plugin(engine.pluginlist, "ampstack"), live_play(), preset_window() {
    /*
    ** max window size is work area reduce by arbitrary amount to
    ** make it visually more appealing and to account for the unknown
    ** frame size (difficult to find out, would have to query the
    ** window mananger)
    */
    //window_height = std::min(600, get_current_workarea_height()-50);
    window_height = get_current_workarea_height() - 80;

    //self.pmap = ParamMap(param_fname)
    //gtk_rc_parse(options.get_style_filepath(style_fname));
    //gtk.rc_parse_string(styledef % style_dir);

    // load builder def
    const char *id_list[] = {"MainWindow", "amp_background:ampbox", "bank_liststore", "target_liststore", "bank_combo_liststore", 0};
    bld = gx_gui::GxBuilder::create_from_file(options.get_builder_filepath("mainpanel.glade"), &ui, id_list);
    load_widget_pointers();
    int width, height;
    window->get_default_size(width, height);
    window->set_default_size(width, window_height);
    rackcontainer->set_homogeneous(true); // setting it in glade is awkward to use with glade tool
    status_image->set(options.get_pixmap_filepath("gx_on.png"));
    jackd_image->set(options.get_pixmap_filepath("jackd_off.png"));
    logstate_image->set(options.get_pixmap_filepath("gx_off.png"));
    // remove child labels from boxes used for demo:
    clear_box(*monocontainer);
    clear_box(*stereorackcontainerH);
    clear_box(*stereorackcontainerV);

    // create menu
    actiongroup = Gtk::ActionGroup::create("Main");
    uimanager = create_menu(actiongroup);
    Gtk::Widget *menubar = uimanager->get_widget("/menubar");
    menubox->pack_start(*menubar);
    window->add_accel_group(uimanager->get_accel_group());

    // create rack
    stereorackcontainerH->pack_start(stereorackcontainer, Gtk::PACK_EXPAND_WIDGET);
    monocontainer->pack_start(monorackcontainer, Gtk::PACK_EXPAND_WIDGET);

    std::vector<PluginDesc*>& pluginlist = get_pluginlist(engine.pluginlist, options);
    for (std::vector<PluginDesc*>::iterator l = pluginlist.begin(); l != pluginlist.end(); ++l) {
	for (std::vector<PluginUI*>::iterator v = (*l)->plugins->begin(); v != (*l)->plugins->end(); ++v) {
	    PluginUI *pui = *v;
	    plugin_dict[pui->get_id()] = pui;
	}
    }
    make_icons(plugin_dict, options);

    // connect signal
    window->signal_configure_event().connect_notify(sigc::mem_fun(*this, &MainWindow::on_configure_event));
    //w.connect("destroy", gtk.main_quit);
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(show_rack_button->gobj()), GTK_ACTION(show_rack_action->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(liveplay_button->gobj()),GTK_ACTION(live_play_action->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(tuner_button->gobj()),GTK_ACTION(tuner_action->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(effects_button->gobj()), GTK_ACTION(show_plugin_bar_action->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(presets_button->gobj()), GTK_ACTION(presets_action->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(compress_button->gobj()), GTK_ACTION(compress_action->gobj()));
    gtk_activatable_set_related_action(GTK_ACTIVATABLE(expand_button->gobj()), GTK_ACTION(expand_action->gobj()));

    live_play = new Liveplay(options, gx_settings, options.get_builder_filepath("mainpanel.glade"), actiongroup);
    preset_window = new PresetWindow(bld, options, actiongroup);


    tuner_action->set_active(false);
    show_plugin_bar_action->set_active(false);
    if (rackv_action->get_current_value()) {
	// horizontally
	stereorackcontainerV->hide();
    } else {
	stereorackcontainerH->hide();
    }
    std::vector<Gtk::TargetEntry> listTargets;
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-mono", Gtk::TARGET_SAME_APP, 1));
    listTargets.push_back(Gtk::TargetEntry("application/x-guitarix-stereo", Gtk::TARGET_SAME_APP, 2));
    effects_toolpalette->drag_dest_set(listTargets, Gtk::DEST_DEFAULT_ALL, Gdk::ACTION_MOVE);
    effects_toolpalette->signal_drag_data_received().connect(sigc::mem_fun(*this, &MainWindow::on_tp_drag_data_received));
    bool collapse = false;
    for (std::vector<PluginDesc*>::iterator l = pluginlist.begin(); l != pluginlist.end(); ++l) {
	Gtk::ToolItemGroup *gw = new Gtk::ToolItemGroup((*l)->group);
	gw->set_collapsed(collapse);
	collapse = true;
	for (std::vector<PluginUI*>::iterator v = (*l)->plugins->begin(); v != (*l)->plugins->end(); ++v) {
	    add_toolitem(**v, gw);
	}
	effects_toolpalette->add(*manage(gw));
	effects_toolpalette->set_exclusive(*gw, true);
	effects_toolpalette->set_expand(*gw, true);
    }
    effects_toolpalette->show_all();

    plugin_dict[mainamp_plugin.get_id()] = &mainamp_plugin;
    add_rackbox_internal(mainamp_plugin, 0, false, -1, false, amp_background);
    /*
    for pl in rack_plugins:
	self.add_rackbox(pl)
	self.hide_effect(pl)
    */
    window->signal_visibility_notify_event().connect(sigc::mem_fun(*this, &MainWindow::on_visibility_notify));
    window->show();
}

MainWindow::~MainWindow() {
    delete live_play;
    delete preset_window;
    delete window;
}

void start_main(gx_engine::GxEngine& engine, gx_system::CmdlineOptions& options, gx_engine::ParamMap& pmap) {
    MainWindow w(engine, options, pmap);
    w.run();
}

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

/****************************************************************
 ** class GxTheme
 */

class GxTheme {
private:
    gx_system::CmdlineOptions* options;
    Glib::RefPtr<Gtk::CssProvider> css_provider;
    Glib::RefPtr<Gtk::CssProvider> css_show_values;
    Glib::RefPtr<Gtk::StyleContext> style_context;
#ifndef NDEBUG
    Gtk::Window *window;
    int window_x, window_y;
    void reload_css_post();
#endif
public:
    GxTheme() {}
    void init(gx_system::CmdlineOptions *options_);
    bool set_new_skin(const Glib::ustring& skin_name);
    void update_show_values();
#ifndef NDEBUG
    void reload_css();
    void set_window(Gtk::Window *window_) { window = window_; }
#endif
};

/****************************************************************
 ** class PosixSignals
 **
 ** Block unix signals and catch them in a special thread.
 ** Blocking is inherited by all threads created after an
 ** instance of PosixSignals
 */

class PosixSignals {
private:
    sigset_t waitset;
    std::thread *thread;
    bool gui;
    GxTheme *theme;
    volatile bool exit;
    void signal_helper_thread();
    void quit_slot();
    void gx_ladi_handler();
    void create_thread();
    bool gtk_level();
    static void relay_sigchld(int);
    sigc::signal<void > trigger_nsm_exit;
    
public:
    bool nsm_session_control;
    sigc::signal<void >& signal_trigger_nsm_exit() { return trigger_nsm_exit; }
    PosixSignals(bool gui, GxTheme *theme = nullptr);
    ~PosixSignals();
};

/****************************************************************
 ** Actions:
 ** class ToggleAction
 ** class RadioAction
 ** template class UiToggleAction
 */

class ToggleAction: public Gio::SimpleAction {
protected:
    ToggleAction(const Glib::ustring& name, bool state)
        : Gio::SimpleAction(name, Glib::Variant<bool>::create(state)) {}
public:
    static Glib::RefPtr<ToggleAction> create(const Glib::ustring& name, bool state=false) {
        return Glib::RefPtr<ToggleAction>(new ToggleAction(name, state)); }
    Glib::SignalProxyProperty signal_toggled() { return property_state().signal_changed(); }
    bool get_active() const { bool v; get_state(v); return v; }
    void set_active(bool v);
};

class RadioAction: public Gio::SimpleAction {
protected:
    RadioAction(const Glib::ustring& name);
public:
    static Glib::RefPtr<RadioAction> create(const Glib::ustring& name) {
        return Glib::RefPtr<RadioAction>(new RadioAction(name)); }

    bool get_current_value() const { int v; get_state(v); return v; }
    void set_current_value(int v) { change_state(v); }
};

template <class T>
class UiToggleAction: public ToggleAction {
private:
    gx_engine::GxMachineBase& machine;
    std::string id;
    void on_toggled();
protected:
    UiToggleAction(
        gx_engine::GxMachineBase& machine_, const std::string& id,
        const Glib::ustring& name, bool is_active=false);
    ~UiToggleAction();
public:
    static Glib::RefPtr<UiToggleAction> create(
        gx_engine::GxMachineBase& machine, const std::string& id,
        const Glib::ustring& name, bool is_active=false) {
        return Glib::RefPtr<UiToggleAction>(
            new UiToggleAction(machine, id, name, is_active));
    }
};

typedef UiToggleAction<bool> UiBoolToggleAction;


/****************************************************************
 ** class UIManager
 */

class UIManager {
public:
    typedef std::function<bool(const Glib::ustring&, Glib::RefPtr<Gio::Menu>&, int, int)> search_func;
private:
    Glib::RefPtr<Gio::Menu> menu;
    Glib::RefPtr<Gtk::AccelGroup> accelgroup;
    Glib::RefPtr<Gio::SimpleActionGroup> actiongroup;
    Gtk::MenuBar *menubar;
    void set_accelerators_from_menu(Glib::RefPtr<Gio::Menu>& menu);
    bool foreach_menu_(Glib::RefPtr<Gio::Menu>& menu, search_func& func, int& startpos);
public:
    UIManager(const std::string& file, Gtk::MenuBar *bar);
    Glib::RefPtr<Gtk::AccelGroup>& get_accel_group() { return accelgroup; }
    Glib::RefPtr<Gio::SimpleActionGroup>& get_action_group() { return actiongroup; }
    void insert_action_group(Glib::RefPtr<Gio::SimpleActionGroup>& group) { actiongroup = group; }


    void set_accelerators_from_menu() { set_accelerators_from_menu(menu); }
    bool foreach_menu(search_func func) { int pos = 0; return foreach_menu_(menu, func, pos); }
    Glib::RefPtr<Gio::SimpleAction> add_action(const Glib::ustring& action);
    Glib::RefPtr<Gio::SimpleAction> add_action(const Glib::ustring& action, sigc::slot<void()> slot);
    Glib::RefPtr<ToggleAction> add_toggle_action(const Glib::ustring& action, bool state = false);
    Glib::RefPtr<RadioAction> add_radio_action(const Glib::ustring& action);
    Glib::RefPtr<UiBoolToggleAction> add_ui_bool_action(
        gx_engine::GxMachineBase& machine, const std::string& id,
        const Glib::ustring& name, bool is_active=false);
    static void add_accelerator(Glib::RefPtr<Gtk::AccelGroup>& group,
                                Glib::RefPtr<Gio::Action> action,
                                const Glib::ustring& accelerator,
                                Glib::VariantBase& target);
    void add_accelerator(Glib::RefPtr<Gio::Action> action, Glib::VariantBase& target,
                         const Glib::ustring& accelerator);
    Glib::RefPtr<Gio::Menu> get_linked_menu(const Glib::ustring& action);
    Gtk::MenuItem *find_item(const Glib::ustring& action);
    bool remove_item(const Glib::ustring& action);
    static void set_widget_action(Gtk::Widget *w, const Glib::ustring& action);
    static void set_widget_action(Gtk::Widget *w, const Glib::RefPtr<Gio::Action>& action);
};

/****************************************************************
 ** class KeySwitcher
 */

class KeySwitcher: public sigc::trackable {
private:
    gx_engine::GxMachineBase& machine;
    sigc::slot<void, const Glib::ustring&, const Glib::ustring&> display;
    sigc::connection key_timeout;
    Glib::ustring last_bank_key;
private:
    void display_empty(const Glib::ustring& bank, const Glib::ustring& preset);
    bool display_selected_bank();
    bool display_current();
public:
    KeySwitcher(gx_engine::GxMachineBase& machine_,
		sigc::slot<void, const Glib::ustring&, const Glib::ustring&> display_)
	: machine(machine_), display(display_) {}
    bool process_bank_key(int key);
    bool process_preset_key(int key);
    void display_key_error();
    void deactivate();
    static char idx_to_char(int idx);
    static int key_offset_to_idx(int offset);
    static char bank_idx_to_char(int idx, int bank_size);
    static int key_offset_to_bank_idx(int offset, int bank_size);
    static int next_idx(int idx = -1);
};


/****************************************************************
 ** class Liveplay
 */

class Liveplay: public sigc::trackable {
private:
    Glib::RefPtr<gx_gui::GxBuilder> bld;
    gx_engine::GxMachineBase &machine;
    const GxActions& actions;
    bool use_composite;
    Glib::RefPtr<Gtk::Adjustment> brightness_adj;
    Glib::RefPtr<Gtk::Adjustment> background_adj;
    KeySwitcher keyswitch;
    sigc::connection midi_conn;
    Gtk::Window *window;
    sigc::connection mouse_hide_conn;
    //
    Gtk::Image *bypass_image;
    Gtk::Image *mute_image;
    Gtk::Label *liveplay_bank;
    Gtk::Label *liveplay_preset;
    Gtk::Widget *liveplay_canvas;
    Gxw::HSlider *brightness_slider;
    Gtk::Box *brightness_box;
    Gxw::HSlider *background_slider;
    Gtk::ToggleButton *liveplay_exit;
    Gtk::Grid *midictrl_table;
    Gxw::RackTuner *tuner;
private:
    void add_midi_elements();
    bool on_delete(GdkEventAny *ev);
    void on_brightness_changed();
    void on_background_changed();
    bool transparent_draw(const Cairo::RefPtr<Cairo::Context> &cr);
    bool window_draw(const Cairo::RefPtr<Cairo::Context> &cr);
    void on_realize();
    void on_engine_state_change(gx_engine::GxEngineState state);
    void on_selection_done(bool v);
    void on_selection_changed();
    static bool on_keyboard_preset_select(
	GtkAccelGroup *accel_group, GObject *acceleratable,
	guint keyval, GdkModifierType modifier, Liveplay& self);
    static bool on_keyboard_toggle_mute(
	GtkAccelGroup *accel_group, GObject *acceleratable,
	guint keyval, GdkModifierType modifier, Liveplay& self);
    static bool on_keyboard_toggle_bypass(
	GtkAccelGroup *accel_group, GObject *acceleratable,
	guint keyval, GdkModifierType modifier, Liveplay& self);
    static bool on_keyboard_arrows(
	GtkAccelGroup *accel_group, GObject *acceleratable,
	guint keyval, GdkModifierType modifier, Liveplay& self);
    static bool on_keyboard_mode_switch(
	GtkAccelGroup *accel_group, GObject *acceleratable,
	guint keyval, GdkModifierType modifier, Liveplay& self);
    bool pointer_motion(GdkEventMotion* event);
    void display(const Glib::ustring& bank, const Glib::ustring& preset);
    void set_display_state(TunerSwitcher::SwitcherState s);
public:
    Liveplay(const gx_system::CmdlineOptions& options, gx_engine::GxMachineBase& machine,
             const std::string& fname, const GxActions& actions,
             Glib::RefPtr<Gio::SimpleActionGroup>& group);
    ~Liveplay();
    void on_live_play(Glib::RefPtr<ToggleAction> act);
    void display_tuner(bool v);
    Gxw::RackTuner& get_tuner() { return *tuner; }
};


/****************************************************************
 ** class DragIcon
 */

class DragIcon {
private:
    enum { gradient_length = 60 };
    Gtk::Window *window;
    Glib::RefPtr<Gdk::Pixbuf> drag_icon_pixbuf;
private:
    bool icon_draw(const Cairo::RefPtr<Cairo::Context> &cr);
    void create_drag_icon_pixbuf(const PluginUI& plugin, Glib::RefPtr<Gdk::Visual> rgba, gx_system::CmdlineOptions& options);
    bool window_draw(const Cairo::RefPtr<Cairo::Context> &cr, Gtk::OffscreenWindow& w);
public:
    DragIcon(PluginUI& plugin, Glib::RefPtr<Gdk::DragContext> context, gx_system::CmdlineOptions& options, int xoff=0);
    ~DragIcon();
};


/****************************************************************
 ** class RackBox, class MiniRackBox
 */

class MainWindow;
class RackContainer;
class MiniRackBox;

class RackBox: public Gtk::VBox {
    friend class PluginUI;
private:
    PluginUI& plugin;
    PluginDict& plugin_dict;
    sigc::connection anim_tag;
    bool compress;
    bool delete_button;
    Gxw::PaintBox mbox;
    MiniRackBox* minibox;
    Gtk::Widget *fbox;
    std::string target;
    int anim_height;
    int anim_step;
    DragIcon *drag_icon;
    int target_height;
    Gxw::PaintBox box;
    Gxw::Switch on_off_switch;
private:
    static void set_paintbox(Gxw::PaintBox& pb, PluginType tp);
    static void set_paintbox_unit(Gxw::PaintBox& pb, const PluginUI& plugin);
    static void set_paintbox_unit_shrink(Gxw::PaintBox& pb, PluginType tp);
    static Gtk::Widget *make_label(const PluginUI& plugin, gx_system::CmdlineOptions& options, bool useshort=true);
    static Gtk::Widget *make_bar(int left=4, int right=4, bool sens=false);
    Gtk::Widget *wrap_bar(int left=4, int right=4, bool sens=false);
    void init_dnd();
    void enable_drag(bool v);
    void on_my_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context);
    bool animate_create();
    bool on_my_leave_out(GdkEventCrossing *focus);
    bool on_my_enter_in(GdkEventCrossing *focus);
    void on_my_drag_end(const Glib::RefPtr<Gdk::DragContext>& context);
    bool on_my_drag_failed(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::DragResult result);
    void on_my_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp);
    void vis_switch(Gtk::Widget& a, Gtk::Widget& b);
    void set_visibility(bool v);
    Gtk::Button *make_expand_button(bool expand);
    Gtk::Button *make_preset_button();
    Gtk::HBox *make_full_box(gx_system::CmdlineOptions& options);
    bool has_delete() const { return delete_button; }
    void do_expand();
public:
    RackBox(PluginUI& plugin, PluginDict& plugin_dict, Gtk::Widget* bare=0);
    static Gtk::Widget *create_drag_widget(const PluginUI& plugin, gx_system::CmdlineOptions& options);
    RackContainer *get_parent();
    bool can_compress() { return compress; }
    friend class MiniRackBox;
    const char *get_id() const;
    void set_config_mode(bool mode);
    void swtch(bool mini);
    void pack(Gtk::Widget *mainbox, Gtk::Widget *minibox);
    void animate_insert();
    static Gtk::Widget *create_icon_widget(const PluginUI& plugin, gx_system::CmdlineOptions& options);
    void set_position(int pos, int post_pre);
    bool compare_position(int pos, int post_pre);
    void display(bool v, bool animate);
    bool get_plug_visible();
};

class MiniRackBox: public Gtk::HBox {
private:
    static Glib::RefPtr<Gtk::SizeGroup> szg_label;
    Gtk::EventBox evbox;
    Gtk::HBox mconbox;
    Gtk::Button *mb_expand_button;
    Gtk::Widget *mb_delete_button;
    Gtk::Button *preset_button;
    Gxw::Switch on_off_switch;
    bool on_my_leave_out(GdkEventCrossing *focus);
    bool on_my_enter_in(GdkEventCrossing *focus);
    sigc::connection evbox_button;
private:
    Gtk::Widget *make_delete_button(RackBox& rb);
public:
    MiniRackBox(RackBox& rb, gx_system::CmdlineOptions& options);
    void set_config_mode(bool mode, PluginUI& plugin);
    void pack(Gtk::Widget *w);
};

/****************************************************************
 ** class RackContainer
 */

class PluginDict;

class RackContainer: public Gtk::VBox {
private:
    PluginDict& plugin_dict;
    int in_drag;
    int count;                  ///< count of visible children
    std::vector<std::string> targets;
    std::vector<std::string> othertargets;
    sigc::connection highlight_connection;
    sigc::connection autoscroll_connection;
private:
    using Gtk::VBox::add;
    bool drag_highlight_draw(const Cairo::RefPtr<Cairo::Context>&, int y0);
    void find_index(int x, int y, string* before, int *ypos);
    bool check_targets(const std::vector<std::string>& tgts1, const std::vector<std::string>& tgts2);
    virtual bool on_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp);
    virtual void on_drag_leave(const Glib::RefPtr<Gdk::DragContext>& context, guint timestamp);
    virtual void on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, guint info, guint timestamp);
    virtual void on_add(Widget* ch);
    bool scroll_timeout();
    bool scrollother_timeout();
public:
    typedef Glib::ListHandle<const RackBox*> rackbox_const_list;
    typedef Glib::ListHandle<RackBox*> rackbox_list;
    RackContainer(PluginDict& plugin_dict);
    rackbox_list get_children() {
	return rackbox_list(
	    gtk_container_get_children(GTK_CONTAINER(gobj())),
	    Glib::OWNERSHIP_SHALLOW);
    }
    rackbox_const_list get_children() const {
	return rackbox_const_list(
	    gtk_container_get_children(const_cast<GtkContainer*>(GTK_CONTAINER(gobj()))),
	    Glib::OWNERSHIP_SHALLOW);
    }
    void add(RackBox& r, int pos=-1);
    void ensure_visible(RackBox& child);
    void renumber();
    double stop_at_bottom(double off, double step_size, double pagesize);
    double stop_at_top(double off, double step_size);
    void set_list_targets(const std::vector<Gtk::TargetEntry>& listTargets,
			  const std::vector<std::string>& targets_,
			  const std::vector<std::string>& othertargets_);
    void set_child_count(int n);
    void change_child_count(int n) { set_child_count(count + n); }
    inline void reorder(const std::string& name, const std::string& before);
};


/****************************************************************
 ** class PluginUI
 */

class PluginUI: public sigc::trackable {
    friend class PluginDict;
    friend class RackContainer;
private:
    Glib::RefPtr<ToggleAction> action;
    // data for ToolPalette entry
    Gtk::ToolItemGroup *group;
    Gtk::ToolItem *toolitem;
    RackBox *rackbox;		///< rack widget or nullptr
    bool hidden; 		///< Plugin not visible (but might be in rack, e.g. "Rack" is off)
    bool active;                ///< Plugin is in rack (effect bar icon not visible) 
    sigc::signal<void(bool)> output_widget_state; ///< state of output_widgets_active changed
    bool output_widgets_active;	///< send data updates for output variables
    Glib::ustring tooltip;
    const char *shortname;
private:
    void on_action_toggled();
    bool animate_vanish();
protected:
    PluginUI(PluginDict& plugin_dict, const char* id_, const Glib::ustring& tooltip_="");
    virtual ~PluginUI();
public:
    gx_engine::Plugin *plugin;


    PluginDict& plugin_dict;

    PluginType get_type() const {
	return (plugin->get_pdef()->flags & PGN_STEREO) ? PLUGIN_TYPE_STEREO : PLUGIN_TYPE_MONO;
    }
    bool has_gui() const {
	PluginDef const * const pdef  = plugin->get_pdef();
	return  pdef->flags & PGN_GUI || pdef->load_ui;
    }
    const char *get_id() const { return plugin->get_pdef()->id; }
    const char *get_name() const { return plugin->get_pdef()->name; }
    void activate(bool animate);
    void decativate(bool animate);
    void set_action(Glib::RefPtr<ToggleAction>& act);
    void set_active(bool v) { if (action) action->set_active(v); }
    Glib::RefPtr<ToggleAction> get_action() { return action; }
    static bool is_registered(gx_engine::GxMachineBase& m, const char *name);
    virtual void on_plugin_preset_popup();
    inline const char *get_category() {
	const char *cat = plugin->get_pdef()->category;
	return (cat && *cat) ? cat : N_("External");
    }
    inline const char *get_shortname() const {
	const char *name = shortname;
	if (!name) {
	    name = plugin->get_pdef()->shortname;
	}
	if (!name || !*name) {
	    name = get_name();
	}
	return name;
    }
    void update_rackbox();
    void compress(bool state);
    void hide(bool animate);
    void show(bool animate);
    void set_config_mode(bool state);
    friend bool plugins_by_name_less(PluginUI *a, PluginUI *b);
    void on_ti_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context);
    void on_ti_drag_end(const Glib::RefPtr<Gdk::DragContext>& context);
    void on_ti_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp);
    void on_ti_drag_data_delete(const Glib::RefPtr<Gdk::DragContext>& context);
    bool on_ti_button_press(GdkEventButton *ev);
    bool on_my_leave_out(GdkEventCrossing *focus);
    bool on_my_enter_in(GdkEventCrossing *focus);
    void add_toolitem(Gtk::ToolItemGroup *gw);
    void activate(bool animate, const string& before);
    void deactivate(bool animate);
    bool get_update_cond();
    void set_update_state(bool state);
    void on_state_change();
    void remove(bool animate);
    void dispose_rackbox();
    bool on_rack_handle_press(GdkEventButton* ev);
    Glib::ustring get_displayname(bool useshort) const;
    sigc::signal<void(bool)> *get_output_widget_state() { return &output_widget_state; }
};

bool plugins_by_name_less(PluginUI *a, PluginUI *b);

inline const char *RackBox::get_id() const { return plugin.get_id(); }
inline bool RackBox::get_plug_visible() { return plugin.plugin->get_plug_visible(); }

/****************************************************************
 ** class PluginDict
 */

class PluginDict: private std::map<std::string, PluginUI*> {
private:
    RackContainer monorackcontainer;
    RackContainer stereorackcontainer;
    std::map<Glib::ustring, Gtk::ToolItemGroup*> groupmap;
    std::vector<std::string> monotargets;
    std::vector<std::string> stereotargets;
    gx_gui::StackBoxBuilder& boxbuilder;
    gx_engine::GxMachineBase& machine;
    gx_system::CmdlineOptions& options;
    Gtk::ToolPalette& toolpalette;
    UIManager& uimanager;
    bool config_mode;
    bool plugins_hidden;
public:
    DragIcon *drag_icon;
private:
    Glib::ustring category_id(const std::string& group, bool stereo);
    void on_plugin_changed(gx_engine::Plugin *pl, gx_engine::PluginChange::pc c);
    Gtk::ToolItemGroup *add_plugin_category(const char *cat, bool collapse = true);
    Glib::ustring add_plugin_menu_entry(PluginUI *pui);
    void remove_plugin_menu_entry(PluginUI *pui);
    void register_plugin(PluginUI *pui);
    void fill_pluginlist();
public:
    typedef std::map<std::string, PluginUI*>::iterator iterator;
    PluginDict(gx_engine::GxMachineBase& machine, gx_system::CmdlineOptions& options,
	       Gtk::ToolPalette& toolpalette, gx_gui::StackBoxBuilder& boxbuilder,
	       UIManager& uimanager);
    ~PluginDict();
    void cleanup();
    void add_bare(const char * id, Gtk::Container *box);
    void add(PluginUI *p);
    void remove(PluginUI *p);
    PluginUI *operator[](const std::string& s) { return find(s)->second; }
    using std::map<std::string, PluginUI*>::begin;
    using std::map<std::string, PluginUI*>::end;
    void compress(bool state);
    bool get_plugins_hidden() { return plugins_hidden; }
    void set_config_mode(bool state);
    bool get_config_mode() { return config_mode; }
    RackContainer& get_monorackcontainer() { return monorackcontainer; }
    RackContainer& get_stereorackcontainer() { return stereorackcontainer; }
    double stop_at(RackContainer *container, double off, double step_size, double page_size);
    void show_entries();
    void hide_entries();
    void check_order();
    void check_order(PluginType tp, bool animate);
    void unit_order_changed(bool stereo);
    void reorder(RackContainer *container, const std::string& name, const std::string& before);
    bool use_animations() { return options.system_animations; }
    void on_tp_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, int info, int timestamp);
    gx_engine::GxMachineBase& get_machine() { return machine; }
    gx_system::CmdlineOptions& get_options() { return options; }
    void plugin_preset_popup(const PluginDef *pdef);
    void plugin_preset_popup(const PluginDef *pdef, const Glib::ustring& name);
    RackBox *add_rackbox_internal(PluginUI& plugin, Gtk::Widget *mainwidget, Gtk::Widget *miniwidget,
				  bool mini=false, int pos=-1, bool animate=false, Gtk::Widget *bare=0);
    RackBox *add_rackbox(PluginUI& pl, bool mini=false, int pos=-1, bool animate=false);
    void pluginlist_append(std::vector<PluginUI*>& p);
    void add_plugin(std::vector<PluginUI*>& p, const char *id, const Glib::ustring& tooltip_="");
    PluginUI *activate(const string& id, const string& before, bool animate);
    PluginUI *deactivate(const string& id, bool animate);
};


/****************************************************************
 ** class TextLoggingBox
 */

class TextLoggingBox: public Gtk::Window {
private:
    struct tab_table {
	const char *tagname;
	const char *tag_color;
    };
    Gtk::VBox box;
    Gtk::Button ok_button;
    Gtk::HButtonBox buttonbox;
    Gtk::ScrolledWindow scrollbox;
    Gtk::TextView tbox;
    static tab_table tagdefs[GxLogger::kMessageTypeCount];
    Glib::RefPtr<Gtk::TextTag> tags[GxLogger::kMessageTypeCount];
    int highest_unseen_msg_level;
    sigc::signal<void> msg_level_changed;
private:
    virtual bool on_key_press_event(GdkEventKey *event);
    void show_msg(string msgbuf, GxLogger::MsgType msgtype, bool plugged);
    virtual void on_show();
    virtual void on_hide();
public:
    TextLoggingBox();
    ~TextLoggingBox();
    void reset_msg_level();
    int get_unseen_msg_level() { return highest_unseen_msg_level; }
    sigc::signal<void>& signal_msg_level_changed() { return msg_level_changed; }
};


/****************************************************************
 ** class MainWindow
 */

class Freezer {
private:
    Gtk::Window *window;
    sigc::connection tag;
    bool need_thaw;
    int size_x;
    int size_y;
    sigc::slot<void> work;
private:
    void do_thaw();
    bool thaw_timeout();
    void freeze(Gtk::Window *w, int width, int height);
    void thaw();
public:
    Freezer();
    ~Freezer();
    void freeze_until_width_update(Gtk::Window *w, int width);
    void set_slot(sigc::slot<void> w);
    void freeze_and_size_request(Gtk::Window *w, int width, int height);
    bool check_thaw(int width, int height);
};


/****************************************************************
 ** class PluginPresetPopup
 */

class PluginPresetPopup: public Gtk::Menu {
private:
    const PluginDef *pdef;
    gx_engine::GxMachineBase& machine;
    const Glib::ustring save_name_default;
    gx_preset::UnitPresetList presetnames;
    void set_plugin_std_preset();
    void set_plugin_preset(bool factory, const Glib::ustring& name);
    bool add_plugin_preset_list(bool *found);
    void save_plugin_preset();
    void remove_plugin_preset();
protected:
    virtual void on_selection_done();
public:
    PluginPresetPopup(const PluginDef *pdef, gx_engine::GxMachineBase& machine,
		      const Glib::ustring& save_name_default = "");
    gx_preset::UnitPresetList::const_iterator begin() { return presetnames.begin(); }
    gx_preset::UnitPresetList::const_iterator end() { return presetnames.end(); }
    const PluginDef *get_pdef() { return pdef; }
    gx_engine::GxMachineBase& get_machine() { return machine; }
};


/****************************************************************
 ** GxUiRadioMenu
 ** adds the values of an EnumParameter as Gio::MenuItem's
 ** to a Gio::Menu
 */

class GxUiRadioMenu {
private:
    gx_engine::GxMachineBase& machine;
    const std::string id;
    Glib::RefPtr<Gio::SimpleAction> action;
    void set_value(int v);
    void on_changed(const Glib::VariantBase& value);
public:
    GxUiRadioMenu(gx_engine::GxMachineBase& machine, const std::string& id);
    void setup(UIManager& uimanager);
};


class GxActions {
public:
    // Main Window
    Glib::RefPtr<Gio::SimpleAction> quit;
    Glib::RefPtr<Gio::SimpleAction> compress;
    Glib::RefPtr<Gio::SimpleAction> expand;
    Glib::RefPtr<Gio::SimpleAction> jackstartup;
    Glib::RefPtr<Gio::SimpleAction> loadladspa;

    Glib::RefPtr<ToggleAction> rack_config;
    Glib::RefPtr<ToggleAction> live_play;
    Glib::RefPtr<ToggleAction> engine_mute;
    sigc::connection engine_mute_conn;
    Glib::RefPtr<ToggleAction> engine_bypass;
    sigc::connection engine_bypass_conn;
    Glib::RefPtr<ToggleAction> jackserverconnection;
    Glib::RefPtr<ToggleAction> jackports;
    Glib::RefPtr<ToggleAction> midicontroller;
    Glib::RefPtr<ToggleAction> meterbridge;
    Glib::RefPtr<ToggleAction> loggingbox;
    Glib::RefPtr<ToggleAction> animations;

    Glib::RefPtr<ToggleAction> show_plugin_bar;
    Glib::RefPtr<ToggleAction> presets;
    Glib::RefPtr<ToggleAction> show_rack;
    Glib::RefPtr<UiBoolToggleAction> tuner;
    Glib::RefPtr<UiBoolToggleAction> tunermove;
    Glib::RefPtr<UiBoolToggleAction> livetuner;
    Glib::RefPtr<ToggleAction> show_values;
    Glib::RefPtr<ToggleAction> tooltips;
    Glib::RefPtr<UiBoolToggleAction> midi_in_presets;
    Glib::RefPtr<ToggleAction> rackh;
    Glib::RefPtr<ToggleAction> midiout;

    Glib::RefPtr<RadioAction> skin;
    Glib::RefPtr<RadioAction> latency;
    Glib::RefPtr<RadioAction> osc_buffer_size;
    Glib::RefPtr<RadioAction> preset_list_menu;

    // preset window
    Glib::RefPtr<Gio::SimpleAction> new_bank;
    Glib::RefPtr<Gio::SimpleAction> save_changes;
    Glib::RefPtr<ToggleAction> organize;
    Glib::RefPtr<Gio::SimpleAction> online_preset_bank;
};



class SelectMidiChannel: public Gtk::Window {
private:
    Gtk::Label  *description;
    Gtk::ComboBox *channelcombo;
    gx_engine::GxMachineBase& machine;
    sigc::signal<void> close;
    void on_ok_button();
    void on_cancel_button();
    bool on_delete_event(GdkEventAny* event);
    bool on_key_press_event(GdkEventKey *event);
    static SelectMidiChannel* create_from_builder(BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld, gx_engine::GxMachineBase& m) {
	return new SelectMidiChannel(cobject, bld, m);
    }
    SelectMidiChannel(BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld, gx_engine::GxMachineBase& m);
public:
    ~SelectMidiChannel();
    static SelectMidiChannel* create(gx_system::CmdlineOptions& opt, gx_engine::GxMachineBase& machine);
    sigc::signal<void>& signal_close() { return close; }
};

class MainWindowBuilder: public Glib::RefPtr<gx_gui::GxBuilder> {
public:
    Gxw::PaintBox *tunerbox;
    Gtk::Box *tuner_box_no_rack;
    Gtk::ScrolledWindow *vrack_scrolledbox;
    Gtk::Scrollbar *monorackscroller;
    Gtk::Box *stereorackcontainerH;
    Gtk::Box *stereorackcontainerV;
    Gxw::PaintBox *rackcontainer;
    Gtk::ScrolledWindow *stereorackbox;
    Gtk::Box *monocontainer;
    Gxw::PaintBox *monoampcontainer;
    Gtk::Paned *main_vpaned;
    Gtk::Box *monobox;
    Gtk::Box *upper_rackbox;
    Gtk::ScrolledWindow *preset_scrolledbox;
    Gtk::Box *preset_box_no_rack;
    Gxw::PaintBox *effects_frame_paintbox;
    Gtk::Image *insert_image;
    Gtk::Image *status_image;
    Gtk::Image *jackd_image;
    Gtk::Image *logstate_image;
    Gtk::Window *window;
    Gtk::ToggleButton *show_rack_button;
    Gtk::ToggleButton *rack_order_h_button;
    Gtk::ToggleButton *config_mode_button;
    Gtk::ToggleButton *liveplay_button;
    Gtk::ToggleButton *tuner_button;
    Gtk::ToggleButton *effects_button;
    Gtk::ToggleButton *presets_button;
    Gtk::Button *compress_button;
    Gtk::Button *expand_button;
    Gtk::ToolPalette *effects_toolpalette;
    Gxw::PaintBox *amp_background;
    Gxw::Switch *tuner_on_off;
    Gxw::Selector *tuner_mode;
    Gxw::ValueDisplay *tuner_reference_pitch;
    Gxw::Selector *tuner_tuning;
    Gxw::Selector *tuner_temperament;
    Gxw::RackTuner *racktuner;
    Gtk::Button *ampdetail_compress;
    Gtk::Button *ampdetail_expand;
    Gtk::Widget *ampdetail_mini;
    Gtk::Widget *ampdetail_normal;
    Gxw::FastMeter *fastmeter[2];
    Gtk::Entry *preset_status;
    Gtk::MenuBar *menubar;
private:
    void load_widget_pointers();
public:
    MainWindowBuilder(const gx_system::CmdlineOptions& options, gx_engine::GxMachineBase&  machine);
    ~MainWindowBuilder();
};

class MainWindow: public sigc::trackable {
private:
    gx_system::CmdlineOptions& options;
    gx_engine::GxMachineBase&  machine;
    PosixSignals& posixsig;
    GxTheme& theme;
    MainWindowBuilder bld;
    Freezer freezer;
    Glib::RefPtr<Gdk::Pixbuf> gx_head_icon;
    gx_gui::StackBoxBuilder boxbuilder;
    UIManager uimanager;
    GxActions actions;
    PluginDict plugin_dict;
    int oldpos;
    int scrl_size_x;
    int scrl_size_y;
    int pre_act;
    int pool_act;
    bool is_visible;
    Glib::ustring preset_list_menu_bank;
    Liveplay *live_play;
    PresetWindow *preset_window;
    gx_portmap::PortMapWindow* portmap_window;
    gx_gui::SelectJackControlPgm *select_jack_control;
    SelectMidiChannel *select_midi_channel;
    TextLoggingBox fLoggingWindow;
    GxUiRadioMenu amp_radio_menu;
    Glib::RefPtr<Gdk::Pixbuf> pixbuf_insert_on;
    Glib::RefPtr<Gdk::Pixbuf> pixbuf_insert_off;
    Glib::RefPtr<Gdk::Pixbuf> pixbuf_on;
    Glib::RefPtr<Gdk::Pixbuf> pixbuf_off;
    Glib::RefPtr<Gdk::Pixbuf> pixbuf_bypass;
    Glib::RefPtr<Gdk::Pixbuf> pixbuf_jack_connected;
    Glib::RefPtr<Gdk::Pixbuf> pixbuf_jack_disconnected;
    Glib::RefPtr<Gdk::Pixbuf> pixbuf_log_grey;
    Glib::RefPtr<Gdk::Pixbuf> pixbuf_log_yellow;
    Glib::RefPtr<Gdk::Pixbuf> pixbuf_log_red;
    bool in_session;
    Glib::RefPtr<Gtk::StatusIcon> status_icon;
    KeySwitcher keyswitch;
    ladspa::PluginDisplay *ladspalist_window;

private:
    bool on_my_leave_out(GdkEventCrossing *focus);
    bool on_my_enter_in(GdkEventCrossing *focus);
    void maybe_shrink_horizontally(bool preset_no_rack=false);
    void on_show_tuner();
    void on_move_tuner();
    bool is_variable_size();
    void maybe_change_resizable(void);
    void on_show_rack();
    void on_preset_action();
    void on_compress_all();
    void on_expand_all();
    void on_show_plugin_bar();
    void on_rack_configuration();
    void set_tooltips();
    void set_animations();
    void move_widget(Gtk::Widget& w, Gtk::Box& b1, Gtk::Box& b2);
    int rackbox_stacked_vertical() const;
    void change_expand(Gtk::Widget& w, bool value);
    void on_dir_changed();
    void on_configure_event(GdkEventConfigure *ev);
    void clear_box(Gtk::Container& box);
    void on_show_values();
    void create_actions();
    bool on_visibility_notify(GdkEventVisibility *ev);
    void on_live_play();
    void jack_connection();
    void on_miditable_toggle();
    void on_portmap_activate();
    void on_portmap_response(int);
    bool connect_jack(bool v, Gtk::Window *splash = 0);
    int start_jack();
    void add_skin_menu();
    void change_skin(const Glib::VariantBase& value);
    void on_jack_client_changed();
    void add_latency_menu();
    void change_latency(const Glib::VariantBase& value);
    void user_disable_latency_warn(Gtk::CheckButton* disable_warn);
    int gx_wait_latency_warn();
    void set_latency();
    void set_osc_size();
    void add_osc_size_menu();
    void change_osc_buffer(const Glib::VariantBase& value);
    void on_select_jack_control();
    void on_load_ladspa();
    void delete_select_jack_control();
    void on_select_midi_channel();
    void delete_select_midi_channel();
    void on_log_activate();
    bool on_log_activated(GdkEventButton* ev);
    bool on_log_scrolled(GdkEventScroll* ev);
    void on_engine_toggled();
    void on_engine_state_change(gx_engine::GxEngineState state);
    void set_tuning(Gxw::RackTuner& tuner);
    void set_tuner_tet(Gxw::RackTuner& tuner);
    void set_tuner_ref(Gxw::RackTuner& tuner);
    void setup_tuner_temperament(Gxw::RackTuner& tuner);
    void setup_tuner(Gxw::RackTuner& tuner);
    bool on_toggle_mute(GdkEventButton* ev);
    bool on_scroll_toggle(GdkEventScroll* ev);
    bool on_toggle_insert(GdkEventButton* ev);
    bool on_scroll_toggle_insert(GdkEventScroll* ev);
    void on_insert_jack_changed(bool s);
    bool on_jackserverconnection(GdkEventButton* ev);
    bool on_jackserverconnection_scroll(GdkEventScroll* ev);
    void on_msg_level_changed();
    void on_ampdetail_switch(bool compress, bool setparam);
    bool refresh_meter_level(float falloff);
    bool survive_jack_shutdown();
    void gx_jack_is_down();
    void jack_session_event();
    void jack_session_event_ins();
    void set_in_session();
    void hide_extended_settings();
    void systray_menu(guint button, guint32 activate_time);
    bool on_window_state_changed(GdkEventWindowState* event);
    bool on_meter_button_release(GdkEventButton* ev);
    void show_selected_preset();
    void on_select_preset(const Glib::VariantBase& value);
    void on_next_preset();
    void on_previus_preset();
    void set_next_preset_controller();
    void set_previus_preset_controller();
    void set_switcher_controller();
    void set_bypass_controller();
    void set_vpaned_handle();
    void add_preset_key_accelerators();
    void rebuild_preset_menu();
    bool on_key_press_event(GdkEventKey *event);
    void display_preset_msg(const Glib::ustring& bank, const Glib::ustring& preset);
    void on_livetuner_toggled();
    void on_ladspa_finished(bool reload, bool quit);
    bool delete_ladspalist_window();
    bool on_quit();
    bool on_nsm_quit();
    void amp_controls_visible(Gtk::Range *rr);
    void gx_show_help();
    void show_forum_help();
    void set_midiout();
public:
    Glib::RefPtr<Gtk::SizeGroup> left_column;
    MainWindow(gx_engine::GxMachineBase& machine, gx_system::CmdlineOptions& options, PosixSignals& posixsig, GxTheme& theme,
	       Gtk::Window *splash, const Glib::ustring& title);
    ~MainWindow();
    PluginUI *get_plugin(const std::string& name) { return plugin_dict[name]; }
    PluginDict::iterator plugins_begin() { return plugin_dict.begin(); }
    PluginDict::iterator plugins_end() { return plugin_dict.end(); }
    void run();
    gx_system::CmdlineOptions& get_options() { return options; }
    gx_engine::GxMachineBase& get_machine() { return machine; }
    void set_rackbox_expansion();
    bool use_animations() { return actions.animations->get_active(); }
    void create_default_scratch_preset() { machine.create_default_scratch_preset(); }
    void update_width();
};

inline void RackContainer::reorder(const std::string& name, const std::string& before) {
    plugin_dict.reorder(this, name, before); }

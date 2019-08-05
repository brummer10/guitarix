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

template <class T>
class UiToggleAction: public Gtk::ToggleAction {
private:
    gx_engine::GxMachineBase& machine;
    std::string id;
    void on_toggled();
protected:
    UiToggleAction(
	gx_engine::GxMachineBase& machine_, const std::string& id, const Glib::ustring& name, const Glib::ustring& icon_name,
	const Glib::ustring& label=Glib::ustring(), const Glib::ustring& tooltip=Glib::ustring(),
	bool is_active=false);
    ~UiToggleAction();
public:
    static Glib::RefPtr<UiToggleAction> create(
	gx_engine::GxMachineBase& machine, const std::string& id, const Glib::ustring& name, const Glib::ustring& label=Glib::ustring(),
	const Glib::ustring& tooltip=Glib::ustring(), bool is_active=false) {
	return Glib::RefPtr<UiToggleAction>(
	    new UiToggleAction(machine, id, name, Glib::ustring(), label, tooltip, is_active));
    }
};

typedef UiToggleAction<bool> UiBoolToggleAction;
typedef UiBoolToggleAction UiSwitchToggleAction;


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
    bool process_bank_key(int idx);
    bool process_preset_key(int idx);
    void display_key_error();
    void deactivate();
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
    Gtk::Table *midictrl_table;
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
    static bool do_action(
	GtkAccelGroup *accel_group, GObject *acceleratable,
	guint keyval, GdkModifierType modifier, GtkAction* act);
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
	     const std::string& fname, const GxActions& actions);
    ~Liveplay();
    void on_live_play(Glib::RefPtr<Gtk::ToggleAction> act);
    void display_tuner(bool v);
    Gxw::RackTuner& get_tuner() { return *tuner; }
};


/****************************************************************
 ** class PluginUI
 */

class MainWindow;
class RackBox;

class PluginUI: public sigc::trackable {
private:
    Gtk::UIManager::ui_merge_id merge_id;
    Glib::RefPtr<Gtk::ToggleAction> action;
    void on_action_toggled();
public:
    gx_engine::Plugin *plugin;
    Glib::ustring tooltip;
    const char *shortname;

    // data for ToolPalette entry
    Glib::RefPtr<Gdk::Pixbuf> icon;
    Gtk::ToolItemGroup *group;
    Gtk::ToolItem *toolitem;

    MainWindow& main;
    RackBox *rackbox;
    bool hidden;
    bool hidden_by_move;

    PluginUI(MainWindow& main, const char* id_,
	     const Glib::ustring& tooltip_="");
    virtual ~PluginUI();
    PluginType get_type() const {
	return (plugin->get_pdef()->flags & PGN_STEREO) ? PLUGIN_TYPE_STEREO : PLUGIN_TYPE_MONO;
    }
    const char *get_id() const { return plugin->get_pdef()->id; }
    const char *get_name() const { return plugin->get_pdef()->name; }
    void display(bool v, bool animate);
    void display_new(bool unordered = false);
    void set_ui_merge_id(Gtk::UIManager::ui_merge_id id) { merge_id = id; }
    void unset_ui_merge_id(Glib::RefPtr<Gtk::UIManager> uimanager);
    void set_action(Glib::RefPtr<Gtk::ToggleAction>& act);
    void set_active(bool v) { if (action) action->set_active(v); }
    Glib::RefPtr<Gtk::ToggleAction> get_action() { return action; }
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
    friend bool plugins_by_name_less(PluginUI *a, PluginUI *b);
};

bool plugins_by_name_less(PluginUI *a, PluginUI *b);

/****************************************************************
 ** class PluginDict
 */

class PluginDict: private std::map<std::string, PluginUI*> {
public:
    typedef std::map<std::string, PluginUI*>::iterator iterator;
    PluginDict(): std::map<std::string, PluginUI*>() {}
    ~PluginDict();
    void cleanup();
    void add(PluginUI *p);
    void remove(PluginUI *p);
    PluginUI *operator[](const std::string& s) { return find(s)->second; }
    using std::map<std::string, PluginUI*>::begin;
    using std::map<std::string, PluginUI*>::end;
    void compress(bool state);
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
    DragIcon(const PluginUI& plugin, Glib::RefPtr<Gdk::DragContext> context, gx_system::CmdlineOptions& options, int xoff=0);
    ~DragIcon();
};


/****************************************************************
 ** class RackBox, class MiniRackBox
 */

//#define USE_SZG   // use a SizeGroup instead of predefined width for Gxw::Switch("switchit")

class MiniRackBox;
class RackContainer;

class RackBox: public Gtk::VBox {
private:
#ifdef USE_SZG
    static Glib::RefPtr<Gtk::SizeGroup> szg;
#endif
    PluginUI& plugin;
    MainWindow& main;
    bool config_mode;
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
    bool box_visible;
    Gxw::Switch on_off_switch;
    gx_gui::uiToggle<bool> toggle_on_off;
private:
    static void set_paintbox(Gxw::PaintBox& pb, PluginType tp);
    static void set_paintbox_unit(Gxw::PaintBox& pb, const PluginUI& plugin);
    static void set_paintbox_unit_shrink(Gxw::PaintBox& pb, PluginType tp);
    static Gtk::Widget *make_label(const PluginUI& plugin, gx_system::CmdlineOptions& options, bool useshort=true);
    static Gtk::Widget *make_bar(int left=4, int right=4, bool sens=false);
    Gtk::Widget *wrap_bar(int left=4, int right=4, bool sens=false);
    void init_dnd();
    void enable_drag(bool v);
    bool animate_vanish();
    void animate_remove();
    void on_my_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context);
    bool animate_create();
    bool on_my_leave_out(GdkEventCrossing *focus);
    bool on_my_enter_in(GdkEventCrossing *focus);
    bool on_my_button_press(GdkEventButton* ev);
    void on_my_drag_end(const Glib::RefPtr<Gdk::DragContext>& context);
    void on_my_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp);
    void vis_switch(Gtk::Widget& a, Gtk::Widget& b);
    void set_visibility(bool v);
    Gtk::Button *make_expand_button(bool expand);
    Gtk::Button *make_preset_button();
    Gtk::HBox *make_full_box(gx_system::CmdlineOptions& options);
    Gtk::VBox *switcher_vbox(gx_system::CmdlineOptions& options);
    bool has_delete() const { return delete_button; }
    void do_expand();
public:
    RackBox(PluginUI& plugin, MainWindow& main, Gtk::Widget* bare=0);
    static Gtk::Widget *create_drag_widget(const PluginUI& plugin, gx_system::CmdlineOptions& options);
    RackContainer *get_parent();
    bool can_compress() { return compress; }
    friend class MiniRackBox;
    const char *get_id() const { return plugin.get_id(); }
    void set_config_mode(bool mode);
    void swtch(bool mini);
    void pack(Gtk::Widget *mainbox, Gtk::Widget *minibox, const Glib::RefPtr<Gtk::SizeGroup>& szg);
    void animate_insert();
    static Gtk::Widget *create_icon_widget(const PluginUI& plugin, gx_system::CmdlineOptions& options);
    void setOrder(int pos, int post_pre);
    void display(bool v, bool animate);
    bool get_plug_visible() { return plugin.plugin->get_plug_visible(); }
    bool get_box_visible() { return box_visible; }
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
    gx_gui::uiToggle<bool> toggle_on_off;
private:
    Gtk::Widget *make_delete_button(RackBox& rb);
public:
    MiniRackBox(RackBox& rb, gx_system::CmdlineOptions& options);
    void set_config_mode(bool mode);
    void pack(Gtk::Widget *w);
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
    std::vector<std::string> targets;
    std::vector<std::string> othertargets;
    sigc::connection highlight_connection;
    sigc::connection autoscroll_connection;
private:
    using Gtk::VBox::add;
    bool drag_highlight_draw(const Cairo::RefPtr<Cairo::Context>&, int y0);
    void find_index(int x, int y, int* len, int *ypos);
    void on_my_remove(Gtk::Widget*);
    bool check_targets(const std::vector<std::string>& tgts1, const std::vector<std::string>& tgts2);
    virtual bool on_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp);
    virtual void on_drag_leave(const Glib::RefPtr<Gdk::DragContext>& context, guint timestamp);
    virtual void on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, guint info, guint timestamp);
    virtual void on_add(Widget* ch);
    void unit_order_changed(bool stereo);
    void renumber();
    bool scroll_timeout();
    bool scrollother_timeout();
public:
    typedef Glib::ListHandle<const RackBox*> rackbox_const_list;
    typedef Glib::ListHandle<RackBox*> rackbox_list;
    RackContainer(PluginType tp, MainWindow& main);
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
    inline bool check_if_animate(const RackBox& rackbox);
    void show_entries();
    void hide_entries();
    void set_config_mode(bool mode);
    bool empty() const { return child_count == 0; }
    void add(RackBox& r, int pos=-1);
    void check_order();
    void ensure_visible(RackBox& child);
    void reorder(const std::string& name, unsigned int pos);
    void increment();
    void decrement();
    inline void resize_finished();
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
 ** adds the values of an EnumParameter as Gtk::RadioMenuItem's
 ** to a Gtk::MenuShell
 */

class GxUiRadioMenu {
private:
    gx_engine::GxMachineBase& machine;
    const std::string id;
    Glib::RefPtr<Gtk::RadioAction> action;
    void set_value(unsigned int v);
    void on_changed(Glib::RefPtr<Gtk::RadioAction> act);
public:
    GxUiRadioMenu(gx_engine::GxMachineBase& machine, const std::string& id);
    void setup(const Glib::ustring& prefix, const Glib::ustring& postfix,
	       Glib::RefPtr<Gtk::UIManager>& uimanager, Glib::RefPtr<Gtk::ActionGroup>& actiongroup);
};


struct GxActions {
    // Main Window
    Glib::RefPtr<Gtk::ActionGroup> group;
    Glib::RefPtr<Gtk::AccelGroup> accels;

    Glib::RefPtr<Gtk::Action> quit;
    Glib::RefPtr<Gtk::Action> compress;
    Glib::RefPtr<Gtk::Action> expand;
    Glib::RefPtr<Gtk::Action> jack_latency_menu;
    Glib::RefPtr<Gtk::Action> osc_buffer_menu;
    Glib::RefPtr<Gtk::Action> jackstartup;
    Glib::RefPtr<Gtk::Action> loadladspa;

    Glib::RefPtr<Gtk::ToggleAction> rack_config;
    Glib::RefPtr<Gtk::ToggleAction> live_play;
    Glib::RefPtr<Gtk::ToggleAction> engine_mute;
    sigc::connection engine_mute_conn;
    Glib::RefPtr<Gtk::ToggleAction> engine_bypass;
    sigc::connection engine_bypass_conn;
    Glib::RefPtr<Gtk::ToggleAction> jackserverconnection;
    Glib::RefPtr<Gtk::ToggleAction> jackports;
    Glib::RefPtr<Gtk::ToggleAction> midicontroller;
    Glib::RefPtr<Gtk::ToggleAction> meterbridge;
    Glib::RefPtr<Gtk::ToggleAction> loggingbox;
    Glib::RefPtr<Gtk::ToggleAction> animations;

    Glib::RefPtr<Gtk::ToggleAction> show_plugin_bar;
    Glib::RefPtr<Gtk::ToggleAction> presets;
    Glib::RefPtr<Gtk::ToggleAction> show_rack;
    Glib::RefPtr<UiBoolToggleAction> tuner;
    Glib::RefPtr<UiBoolToggleAction> tunermove;
    Glib::RefPtr<UiBoolToggleAction> livetuner;
    Glib::RefPtr<UiBoolToggleAction> midi_out;
    Glib::RefPtr<UiBoolToggleAction> midi_out_plug;
    Glib::RefPtr<Gtk::ToggleAction> show_values;
    Glib::RefPtr<Gtk::ToggleAction> tooltips;
    Glib::RefPtr<UiSwitchToggleAction> midi_in_presets;
    Glib::RefPtr<Gtk::ToggleAction> rackh;

    Glib::RefPtr<Gtk::RadioAction> skin;
    Glib::RefPtr<Gtk::RadioAction> latency;
    Glib::RefPtr<Gtk::RadioAction> osc_buffer_size;

    // preset window
    Glib::RefPtr<Gtk::Action> new_bank;
    Glib::RefPtr<Gtk::Action> save_changes;
    Glib::RefPtr<Gtk::ToggleAction> organize;
    Glib::RefPtr<Gtk::Action> online_preset_bank;
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



class MainWindow: public sigc::trackable {
private:
    gx_system::CmdlineOptions& options;
    gx_engine::GxMachineBase&  machine;
    Glib::RefPtr<gx_gui::GxBuilder> bld;
    Freezer freezer;
    PluginDict plugin_dict;
    int oldpos;
    int scrl_size_x;
    int scrl_size_y;
    RackContainer monorackcontainer;
    RackContainer stereorackcontainer;
    int pre_act;
    int pool_act;
    bool is_visible;
   // bool ui_sleep();
    DragIcon *drag_icon;
    Glib::ustring preset_list_menu_bank;
    Gtk::UIManager::ui_merge_id preset_list_merge_id;
    Glib::RefPtr<Gtk::ActionGroup> preset_list_actiongroup;
    Glib::RefPtr<Gtk::UIManager> uimanager;
    Liveplay *live_play;
    PresetWindow *preset_window;
    Gxw::WaveView fWaveView;
    Gtk::Label convolver_filename_label;
    Gtk::Label convolver_mono_filename_label;
    Glib::RefPtr<Gdk::Pixbuf> gx_head_icon;
    gx_gui::StackBoxBuilder boxbuilder;
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
    Glib::RefPtr<Gdk::Pixbuf> gx_head_midi;
    Glib::RefPtr<Gdk::Pixbuf> gx_head_warn;
    GxActions actions;
    KeySwitcher keyswitch;
    std::map<Glib::ustring, Gtk::ToolItemGroup*> groupmap;
    ladspa::PluginDisplay *ladspalist_window;
    Glib::RefPtr<Gtk::SizeGroup> szg_rack_units;

    // Widget pointers
    Gxw::PaintBox *tunerbox;
    Gtk::VBox *tuner_box_no_rack;
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
    Gtk::Box *preset_box_no_rack;
    Gxw::PaintBox *effects_frame_paintbox;
    Gtk::Image *insert_image;
    Gtk::Image *status_image;
    Gtk::Image *jackd_image;
    Gtk::Image *logstate_image;
    Gtk::Window *window;
    Gtk::HBox *menubox;
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
    Gtk::Container *midi_out_box;
    Gtk::Container *midi_out_normal;
    Gtk::Container *midi_out_mini;
    Gtk::Button *midi_out_compress;
    Gtk::Button *midi_out_expand;
    Gtk::Button *midi_out_presets_mini;
    Gtk::Button *midi_out_presets_normal;
    Gtk::RadioButton *channel1_button;
    Gtk::Container *channel1_box;
    Gtk::RadioButton *channel2_button;
    Gtk::Container *channel2_box;
    Gtk::RadioButton *channel3_button;
    Gtk::Container *channel3_box;
    Gtk::Alignment *vbam;
    GdkPixbuf *hanl;
    GdkPixbuf *hanr;

private:
    bool on_my_leave_out(GdkEventCrossing *focus);
    bool on_my_enter_in(GdkEventCrossing *focus);
    void load_widget_pointers();
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
    RackBox *add_rackbox_internal(PluginUI& plugin, Gtk::Widget *mainwidget, Gtk::Widget *miniwidget,
				  bool mini=false, int pos=-1, bool animate=false, Gtk::Widget *bare=0);
    void on_show_values();
    void create_actions();
    void add_toolitem(PluginUI& pl, Gtk::ToolItemGroup *gw);
    bool on_visibility_notify(GdkEventVisibility *ev);
    void on_live_play();
    void on_ti_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context, const PluginUI& plugin);
    void on_ti_drag_end(const Glib::RefPtr<Gdk::DragContext>& context);
    void on_ti_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp, const char *effect_id);
    void on_ti_drag_data_delete(const Glib::RefPtr<Gdk::DragContext>& context, const char *effect_id);
    bool on_ti_button_press(GdkEventButton *ev, const char *effect_id);
    void on_tp_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, int info, int timestamp);
    void fill_pluginlist();
    void make_icons(bool force=true);
    void jack_connection();
    void on_miditable_toggle();
    void on_portmap_activate();
    void on_portmap_response(int);
    bool connect_jack(bool v, Gtk::Window *splash = 0);
    int start_jack();
    void add_skin_menu();
    void change_skin(Glib::RefPtr<Gtk::RadioAction> action);
    void on_jack_client_changed();
    void add_latency_menu();
    void change_latency(Glib::RefPtr<Gtk::RadioAction> action);
    void user_disable_latency_warn(Gtk::CheckButton* disable_warn);
    int gx_wait_latency_warn();
    void set_latency();
    void set_osc_size();
    void add_osc_size_menu();
    void change_osc_buffer(Glib::RefPtr<Gtk::RadioAction> action);
    void on_select_jack_control();
    void on_load_ladspa();
    void delete_select_jack_control();
    void on_select_midi_channel();
    void delete_select_midi_channel();
    void on_log_activate();
    bool on_log_activated(GdkEventButton* ev);
    bool on_log_scrolled(GdkEventScroll* ev);
    void do_program_change(int pgm);
    void on_engine_toggled();
    void on_engine_state_change(gx_engine::GxEngineState state);
    void set_new_skin(const Glib::ustring& skin_name);
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
    void on_show_oscilloscope(bool v);
    void set_waveview_buffer(unsigned int size);
    void on_oscilloscope_post_pre(int post_pre);
    int on_oscilloscope_activate(bool start);
    bool on_refresh_oscilloscope();
    bool refresh_meter_level(float falloff);
    bool survive_jack_shutdown();
    void gx_jack_is_down();
    void jack_session_event();
    void jack_session_event_ins();
    void set_in_session();
    void hide_extended_settings();
    void systray_menu(guint button, guint32 activate_time);
    void overload_status_changed(gx_engine::MidiAudioBuffer::Load l);
    bool on_window_state_changed(GdkEventWindowState* event);
    bool on_meter_button_release(GdkEventButton* ev);
    void show_selected_preset();
    void on_select_preset(int idx);
    void on_next_preset();
    void on_previus_preset();
    void set_next_preset_controller();
    void set_previus_preset_controller();
    void set_switcher_controller();
    void set_bypass_controller();
    void set_vpaned_handle();
    void rebuild_preset_menu();
    bool on_key_press_event(GdkEventKey *event);
    void display_preset_msg(const Glib::ustring& bank, const Glib::ustring& preset);
    void on_show_midi_out();
    void on_show_midi_out_plug();
    void on_midi_out_channel_toggled(Gtk::RadioButton *rb, Gtk::Container *c);
    void on_livetuner_toggled();
    Gtk::ToolItemGroup *add_plugin_category(const char *cat, bool collapse = true);
    Glib::ustring add_plugin_menu_entry(PluginUI *pui);
    void register_plugin(PluginUI *pui);
    void on_ladspa_finished(bool reload, bool quit);
    bool delete_ladspalist_window();
    bool on_quit();
    void amp_controls_visible(Gtk::Range *rr);
    void on_plugin_changed(gx_engine::Plugin *pl, gx_engine::PluginChange::pc c);
public:
    GtkSizeGroup *left_column;
    MainWindow(gx_engine::GxMachineBase& machine, gx_system::CmdlineOptions& options,
	       Gtk::Window *splash, const Glib::ustring& title);
    ~MainWindow();
    void hide_effect(const std::string& name);
    RackContainer& get_monorackcontainer() { return monorackcontainer; }
    RackBox *add_rackbox(PluginUI& pl, bool mini=false, int pos=-1, bool animate=false);
    void add_icon(const std::string& name);
    PluginUI *get_plugin(const std::string& name) { return plugin_dict[name]; }
    PluginDict::iterator plugins_begin() { return plugin_dict.begin(); }
    PluginDict::iterator plugins_end() { return plugin_dict.end(); }
    void run();
    gx_system::CmdlineOptions& get_options() { return options; }
    void plugin_preset_popup(const PluginDef *pdef);
    void plugin_preset_popup(const PluginDef *pdef, const Glib::ustring& name);
    gx_engine::GxMachineBase& get_machine() { return machine; }
    void add_plugin(std::vector<PluginUI*>& p, const char *id, const Glib::ustring& tooltip_="");
    void set_rackbox_expansion();
    double stop_at_stereo_bottom(double off, double step_size, double pagesize);
    double stop_at_mono_top(double off, double step_size);
    bool use_animations() { return actions.animations->get_active(); }
    void create_default_scratch_preset() { machine.create_default_scratch_preset(); }
    void resize_finished(RackContainer *ch);
    void update_width();
};

inline bool RackContainer::check_if_animate(const RackBox& rackbox) { return main.use_animations(); }
inline void RackContainer::resize_finished() { main.resize_finished(this); }

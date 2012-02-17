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

/*
#include <gtkmm.h>
#include <gxwmm.h>
using namespace std;
#include <engine.h>
#include <gx_ui.h>
#include <gx_ui_builder.h>
*/
#include <guitarix.h>
#include <gx_preset_window.h> //FIXME


/****************************************************************
 ** class Liveplay
 */

class Liveplay: public sigc::trackable {
private:
    Glib::RefPtr<gx_gui::GxBuilder> bld;
    gx_engine::GxEngine &engine;
    gx_preset::GxSettings& gx_settings;
    gx_ui::GxUI ui;
    bool use_composite;
    Gtk::Adjustment brightness_adj;
    Gtk::Adjustment background_adj;
    sigc::connection key_timeout;
    Glib::ustring last_bank_key;
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
    void on_engine_state_change(gx_engine::GxEngineState state);
    void on_selection_changed();
    static bool do_action(
	GtkAccelGroup *accel_group, GObject *acceleratable,
	guint keyval, GdkModifierType modifier, GtkAction* act);
    static bool on_keyboard_preset_select(
	GtkAccelGroup *accel_group, GObject *acceleratable,
	guint keyval, GdkModifierType modifier, Liveplay& self);
    void process_bank_key(int idx);
    void process_preset_key(int idx);
    void display_empty(const Glib::ustring& s);
    static bool on_keyboard_toggle_mute(
	GtkAccelGroup *accel_group, GObject *acceleratable,
	guint keyval, GdkModifierType modifier, Liveplay& self);
    static bool on_keyboard_arrows(
	GtkAccelGroup *accel_group, GObject *acceleratable,
	guint keyval, GdkModifierType modifier, Liveplay& self);
public:
    Liveplay(const gx_system::CmdlineOptions& options, gx_engine::GxEngine& engine, gx_preset::GxSettings& gx_settings,
	     const std::string& fname, Glib::RefPtr<Gtk::ActionGroup> actiongroup);
    ~Liveplay();
    void on_live_play(Glib::RefPtr<Gtk::ToggleAction> act);
    void display_tuner(bool v);
};


/****************************************************************
 ** class PluginUI
 */

class MainWindow;
class RackBox;

enum PluginType {
    PLUGIN_TYPE_MONO,
    PLUGIN_TYPE_STEREO,
};

class PluginUI: public gx_ui::GxUiItem {
private:
    virtual void reflectZone();
    virtual bool hasChanged();
public:
    gx_engine::Plugin *plugin;
    Glib::ustring fname;
    Glib::ustring tooltip;
    const char *shortname;

    // data for ToolPalette entry
    Glib::RefPtr<Gdk::Pixbuf> icon;
    Gtk::ToolItemGroup *group;
    Gtk::ToolItem *toolitem;

    MainWindow& main;
    RackBox *rackbox;

    PluginUI(MainWindow& main, const gx_engine::PluginList& pl, const char* id_,
	     const Glib::ustring& fname_="", const Glib::ustring& tooltip_="");
    PluginType get_type() const {
	return (plugin->pdef->flags & PGN_STEREO) ? PLUGIN_TYPE_STEREO : PLUGIN_TYPE_MONO;
    }
    const char *get_id() const { return plugin->pdef->id; }
    const char *get_name() const { return plugin->pdef->name; }
    void display(bool v, bool animate);
    void display_new(bool unordered = false);
    inline bool is_displayed();
};


/****************************************************************
 ** class DragIcon
 */

class DragIcon {
private:
    enum { gradient_length = 40 };
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
    bool vis;
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
    int preset_index;
    std::vector<Glib::ustring> presets;
    Gxw::PaintBox box;
    int box_visible;
    int position;
    unsigned int effect_post_pre;
    Gxw::Switch *on_off_switch;
    gx_gui::uiToggle<bool> toggle_on_off;
private:
    static void set_paintbox(Gxw::PaintBox& pb, PluginType tp);
    static Gtk::Widget *make_label(const PluginUI& plugin, gx_system::CmdlineOptions& options, bool useshort=false);
    static Gtk::Widget *make_bar(int left=4, int right=4, bool sens=false);
    Gtk::Widget *wrap_bar(int left=4, int right=4, bool sens=false);
    void init_dnd();
    void enable_drag(bool v);
    bool animate_vanish();
    void animate_remove();
    void on_my_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context);
    bool animate_create();
    void on_my_drag_end(const Glib::RefPtr<Gdk::DragContext>& context);
    void on_my_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp);
    void vis_switch(Gtk::Widget& a, Gtk::Widget& b);
    Gtk::Button *make_expand_button(bool expand);
    void on_preset_popup_destroy(Gtk::Menu *w);
    void preset_popup();
    Gtk::Button *make_preset_button();
    Gtk::HBox *make_full_box(gx_system::CmdlineOptions& options);
    Gtk::VBox *switcher_vbox(gx_system::CmdlineOptions& options);
    bool has_delete() const { return delete_button; }
    friend bool rackboxes_less(RackBox *a, RackBox *b);
public:
    RackBox(PluginUI& plugin, MainWindow& main, Gtk::Widget* bare=0);
    static Gtk::Widget *create_drag_widget(const PluginUI& plugin, gx_system::CmdlineOptions& options);
    RackContainer *get_parent();
    bool can_compress() { return compress; }
    friend class MiniRackBox;
    const char *get_id() const { return plugin.get_id(); }
    void set_config_mode(bool mode);
    void swtch(bool mini);
    void pack(Gtk::Widget *mainbox, Gtk::Widget *minibox);
    void animate_insert();
    static Gtk::Widget *create_icon_widget(const PluginUI& plugin, gx_system::CmdlineOptions& options);
    void setOrder(int pos, unsigned int post_pre) {
	position = plugin.plugin->position = pos;
	effect_post_pre = plugin.plugin->effect_post_pre = post_pre;
    }
    void storeOrder() { position = plugin.plugin->position; effect_post_pre = plugin.plugin->effect_post_pre; }
    bool hasOrderDiff() { return plugin.plugin->position != position || plugin.plugin->effect_post_pre != effect_post_pre; }
    int position_weight() { return plugin.plugin->position_weight(); }
    bool is_displayed() { return box_visible; }
    void display(bool v, bool animate);
};

class MiniRackBox: public Gtk::HBox {
private:
    static Glib::RefPtr<Gtk::SizeGroup> szg_label;
    Gtk::EventBox evbox;
    Gtk::HBox mconbox;
    Gtk::Button *mb_expand_button;
    Gtk::Widget *mb_delete_button;
    Gtk::Button *preset_button;
    Gxw::Switch *on_off_switch;
    gx_gui::uiToggle<bool> toggle_on_off;
private:
    Gtk::Widget *make_delete_button(RackBox& rb);
public:
    MiniRackBox(RackBox& rb, gx_system::CmdlineOptions& options);
    void set_config_mode(bool mode);
    void pack(Gtk::Widget *w);
};

inline bool PluginUI::is_displayed() {
    return rackbox && rackbox->is_displayed();
}

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
    sigc::connection highlight_connection;
    sigc::connection autoscroll_connection;
private:
    bool drag_highlight_expose(GdkEventExpose *event, int y0);
    void find_index(int x, int y, int* len, int *ypos);
    void on_my_remove(Gtk::Widget*);
    bool check_targets(const std::vector<std::string>& targets);
    virtual bool on_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint timestamp);
    virtual void on_drag_leave(const Glib::RefPtr<Gdk::DragContext>& context, guint timestamp);
    virtual void on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, guint info, guint timestamp);
    virtual void on_add(Widget* ch);
    void renumber();
    bool scroll_timeout();
public:
    typedef Glib::ListHandle<const RackBox*> rackbox_const_list;
    typedef Glib::ListHandle<RackBox*> rackbox_list;
    RackContainer(PluginType tp, MainWindow& main);
    rackbox_list get_children() {
	Glib::ListHandle<Widget*> l = Gtk::VBox::get_children();
	void *p = &l;
	return *reinterpret_cast<rackbox_list*>(p);
    }
    rackbox_const_list get_children() const {
	Glib::ListHandle<const Widget*> l = Gtk::VBox::get_children();
	void *p = &l;
	return *reinterpret_cast<rackbox_const_list*>(p);
    }
    bool check_if_animate(const RackBox& rackbox);
    void show_entries();
    void hide_entries();
    void compress_all();
    void expand_all();
    void set_config_mode(bool mode);
    bool empty() const;
    void add(RackBox& r, int pos=-1);
    void check_order();
    void ensure_visible(RackBox& child);
    void reorder(const std::string& name, int pos);
};


/****************************************************************
 ** class StackBoxBuilderNew
 */

class StackBoxBuilderNew: public gx_gui::StackBoxBuilder {
private:
    int                  fTop;
    GtkWidget*           fBox[stackSize];
    int                  fMode[stackSize];
    gx_engine::GxEngine& engine;
    gx_engine::ParamMap& pmap;
    gx_gui::MainMenu&    mainmenu;
    Gxw::WaveView&       fWaveView;
    Gtk::Label&          convolver_filename_label;
    Gtk::VBox           *widget;
private:
    virtual void openMonoRackBox(const char* label, int* posit, const char *id_on_off, const char *id_pre_post, const char *id_dialog);
    virtual void closeMonoRackBox();
    virtual void openStereoRackBox(const char* label, int* posit, const char *id_on_off, const char *id_dialog);
    virtual void closeStereoRackBox();
    virtual void openVerticalMidiBox(const char* label = "");
public:
    StackBoxBuilderNew(gx_engine::GxEngine& engine_, gx_engine::ParamMap& pmap_, gx_gui::MainMenu &mainmenu_,
		       Gxw::WaveView &fWaveView_, Gtk::Label &convolver_filename_label_, gx_ui::GxUI& ui,
		       Glib::RefPtr<Gdk::Pixbuf> window_icon);
    void get_box(const std::string& name, Gtk::Widget*& mainbox, Gtk::Widget*& minibox);
    void prepare();
    void fetch(Gtk::Widget*& mainbox, Gtk::Widget*& minibox);
};


/****************************************************************
 ** class MainWindow
 */

struct PluginDesc {
    Glib::ustring group;
    std::vector<PluginUI*> *plugins;
    PluginDesc(const Glib::ustring& g, std::vector<PluginUI*> *p)
	: group(g), plugins(p) {}
};

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
    gx_gui::MainMenu mainmenu;
    Gxw::WaveView fWaveView;
    Gtk::Label convolver_filename_label;
    StackBoxBuilderNew boxbuilder;

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
    RackBox *add_rackbox_internal(PluginUI& plugin, Gtk::Widget *mainwidget, Gtk::Widget *miniwidget,
				  bool mini=false, int pos=-1, bool animate=false, Gtk::Widget *bare=0);
    void on_show_values();
    Glib::RefPtr<Gtk::UIManager> create_menu(Glib::RefPtr<Gtk::ActionGroup>& actiongroup);
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
    void add_plugin(std::vector<PluginUI*> *p, const char *id, const Glib::ustring& fname_="", const Glib::ustring& tooltip_="");
    bool update_all_gui();
public:
    MainWindow(gx_engine::GxEngine& engine, gx_system::CmdlineOptions& options, gx_engine::ParamMap& pmap);
    ~MainWindow();
    void hide_effect(const std::string& name);
    bool check_if_animate(RackContainer& rb) const;
    RackContainer& get_monorackcontainer() { return monorackcontainer; }
    RackBox *add_rackbox(PluginUI& pl, bool mini=false, int pos=-1, bool animate=false);
    bool check_if_rack_container_size_animate(const RackContainer& rackcontainer) const;
    void add_icon(const std::string& name);
    PluginUI *get_plugin(const std::string& name) { return plugin_dict[name]; }
    void run() { Gtk::Main::run(*window); }
    gx_system::CmdlineOptions& get_options() { return options; }
    gx_ui::GxUI& get_ui() { return ui; }
};

/****************************************************************
 **
 ** Implementation
 **
 ****************************************************************/

/****************************************************************
 ** class Liveplay
 */

bool Liveplay::do_action(GtkAccelGroup *accel_group, GObject *acceleratable,
			 guint keyval, GdkModifierType modifier,
			 GtkAction* act) {
    gtk_action_activate(act);
    return true;
}

void Liveplay::display_empty(const Glib::ustring& s) {
    liveplay_preset->set_text(s);
    key_timeout = Glib::signal_timeout().connect(
	sigc::bind_return(sigc::mem_fun(*this, &Liveplay::on_selection_changed), false), 400);
}

void Liveplay::process_preset_key(int idx) {
    if (last_bank_key.empty()) {
	if (gx_settings.get_current_source() != gx_system::GxSettingsBase::factory) {
	    display_empty(Glib::ustring::compose("?? / %1", idx+1));
	    return;
	}
	last_bank_key = gx_settings.get_current_factory();
    }
    gx_system::PresetFile *f = gx_settings.banks.get_file(last_bank_key);
    if (idx >= f->size()) {
	display_empty(Glib::ustring::compose("%1 / %2?", last_bank_key, idx+1));
    } else {
	gx_settings.load_preset(f, f->get_name(idx));
    }
}

void Liveplay::process_bank_key(int idx) {
    last_bank_key = gx_settings.banks.get_name(idx);
    if (last_bank_key.empty()) {
	display_empty("-- / --");
	return;
    }
    liveplay_preset->set_text(Glib::ustring::compose("%1 /", last_bank_key));
    key_timeout = Glib::signal_timeout().connect(
	sigc::bind_return(sigc::mem_fun(*this, &Liveplay::on_selection_changed), false), 2000);
}

bool Liveplay::on_keyboard_preset_select(GtkAccelGroup *accel_group, GObject *acceleratable,
					 guint keyval, GdkModifierType modifier, Liveplay& self) {
    if (self.key_timeout.connected()) {
	self.key_timeout.disconnect();
    }
    int idx = keyval - GDK_KEY_1;
    if (idx >= 0 && idx <= 9) {
	self.process_preset_key(idx);
	return true;
    }
    idx = keyval - GDK_KEY_a;
    if (idx >= 0 && idx <= (GDK_KEY_z - GDK_KEY_a)) {
	self.process_bank_key(idx);
	return true;
    }
    return false;
}

bool Liveplay::on_keyboard_toggle_mute(GtkAccelGroup *accel_group, GObject *acceleratable,
				       guint keyval, GdkModifierType modifier, Liveplay& self) {
    self.engine.set_state(self.engine.get_state() == gx_engine::kEngineOff ?
		     gx_engine::kEngineOn
		     : gx_engine::kEngineOff);
    return true;
}

bool Liveplay::on_keyboard_arrows(GtkAccelGroup *accel_group, GObject *acceleratable,
				       guint keyval, GdkModifierType modifier, Liveplay& self) {
    if (keyval == GDK_KEY_Left || keyval == GDK_KEY_Right) {
	Gtk::Adjustment *a = self.brightness_slider->get_adjustment();
	double val = a->get_value();
	double step = a->get_step_increment();
	if (keyval == GDK_KEY_Left) {
	    val -= step;
	} else {
	    val += step;
	}
	a->set_value(val);
    } else {
	Gtk::Adjustment *a = self.background_slider->get_adjustment();
	double val = a->get_value();
	double step = a->get_step_increment();
	if (keyval == GDK_KEY_Down) {
	    val -= step;
	} else {
	    val += step;
	}
	a->set_value(val);
    }
    return true;
}

Liveplay::Liveplay(const gx_system::CmdlineOptions& options, gx_engine::GxEngine& engine_, gx_preset::GxSettings& gx_settings_,
		   const std::string& fname, Glib::RefPtr<Gtk::ActionGroup> actiongroup)
    : bld(), engine(engine_), gx_settings(gx_settings_), ui(), use_composite(),
      brightness_adj(1,0.5,1,0.01,0.1), background_adj(0,0,1,0.01,0.1), key_timeout(),
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
    cl = g_cclosure_new(G_CALLBACK(do_action), (gpointer)(act->gobj()), 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_Return, (GdkModifierType)0, (GtkAccelFlags)0, cl);

    act = actiongroup->get_action("QuitAction");
    cl = g_cclosure_new(G_CALLBACK(do_action), (gpointer)(act->gobj()), 0);
    gtk_accel_group_connect_by_path(ag->gobj(), act->get_accel_path().c_str(), cl);

    cl = g_cclosure_new(G_CALLBACK(on_keyboard_toggle_mute), (gpointer)this, 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_space, (GdkModifierType)0, (GtkAccelFlags)0, cl);

    cl = g_cclosure_new(G_CALLBACK(on_keyboard_arrows), (gpointer)this, 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_Left, GDK_CONTROL_MASK, (GtkAccelFlags)0, cl);
    cl = g_cclosure_new(G_CALLBACK(on_keyboard_arrows), (gpointer)this, 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_Right, GDK_CONTROL_MASK, (GtkAccelFlags)0, cl);
    cl = g_cclosure_new(G_CALLBACK(on_keyboard_arrows), (gpointer)this, 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_Up, GDK_CONTROL_MASK, (GtkAccelFlags)0, cl);
    cl = g_cclosure_new(G_CALLBACK(on_keyboard_arrows), (gpointer)this, 0);
    gtk_accel_group_connect(ag->gobj(), GDK_KEY_Down, GDK_CONTROL_MASK, (GtkAccelFlags)0, cl);

    for (int n = GDK_KEY_1; n <= GDK_KEY_9; ++n) {
	cl = g_cclosure_new(G_CALLBACK(on_keyboard_preset_select), (gpointer)this, 0);
	gtk_accel_group_connect(ag->gobj(), n, (GdkModifierType)0, (GtkAccelFlags)0, cl);
    }
    for (int n = GDK_KEY_A; n <= GDK_KEY_Z; ++n) {
	cl = g_cclosure_new(G_CALLBACK(on_keyboard_preset_select), (gpointer)this, 0);
	gtk_accel_group_connect(ag->gobj(), n, (GdkModifierType)0, (GtkAccelFlags)0, cl);
    }
    
    window->add_accel_group(ag);

    engine.signal_state_change().connect(
	sigc::mem_fun(*this, &Liveplay::on_engine_state_change));
    gx_settings.signal_selection_changed().connect(
	sigc::mem_fun(*this, &Liveplay::on_selection_changed));

    on_engine_state_change(engine.get_state());
    on_selection_changed();
}

Liveplay::~Liveplay() {
    delete window;
}

void Liveplay::on_engine_state_change(gx_engine::GxEngineState state) {
    switch (state) {
    case gx_engine::kEngineOff:    bypass_image->hide(); mute_image->show(); break;
    case gx_engine::kEngineOn:     bypass_image->hide(); mute_image->hide(); break;
    case gx_engine::kEngineBypass: bypass_image->show(); mute_image->hide(); break;
    }
}

void Liveplay::on_selection_changed() {
    last_bank_key.clear();
    Glib::ustring s;
    if (gx_settings.get_current_source() == gx_system::GxSettingsBase::state) {
	s = "----";
    } else {
	s = Glib::ustring::compose(
	    "%1 / %2", gx_settings.get_current_factory(), gx_settings.get_current_name());
    }
    liveplay_preset->set_text(s);
}

void Liveplay::on_live_play(Glib::RefPtr<Gtk::ToggleAction> act) {
    if (act->get_active()) {
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
	cout << v << ": " << endl;
        for (gx_engine::midi_controller_list::iterator j = cl.begin(); j != cl.end(); ++j) {
            gx_engine::Parameter& p = j->getParameter();
	    cout << Glib::ustring::compose(" %1/%2", p.l_group(), p.l_name());
	}
	cout << endl;
	Gtk::ProgressBar *b = new Gtk::ProgressBar();
	b->set_size_request(300, 50);
	b->set_fraction(cl.begin()->get());
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
 ** class PluginUI
 */

PluginUI::PluginUI(MainWindow& main_, const gx_engine::PluginList& pl, const char *name,
		   const Glib::ustring& fname_, const Glib::ustring& tooltip_)
    : GxUiItem(), plugin(pl.lookup_plugin(name)), fname(fname_),
      tooltip(tooltip_), shortname(), icon(), group(), toolitem(), main(main_), rackbox() {
}

bool PluginUI::hasChanged() {
    if ((plugin->box_visible || plugin->on_off) != is_displayed()) {
	return true;
    }
    if (!rackbox) {
	return false;
    }
    return rackbox->hasOrderDiff();
}

void PluginUI::reflectZone() {
    if ((plugin->box_visible || plugin->on_off) != is_displayed()) {
	display(plugin->box_visible, false);
    }
    if (rackbox) {
	if (rackbox->hasOrderDiff()) {
	    rackbox->get_parent()->check_order();
	}
    }
}

void PluginUI::display(bool v, bool animate) {
    // this function hides the rackbox. It could also destroy it (or
    // some other function could do it, e.g. when unloading a module),
    // but currently there are too man memory leaks in the stackbased
    // builder.
    plugin->box_visible = v;
    if (v) {
	if (!rackbox) {
	    rackbox = main.add_rackbox(*this, false, -1, animate);
	} else {
	    rackbox->display(true, animate);
	}
	main.hide_effect(get_id());
    } else {
	if (rackbox) {
	    rackbox->display(false, animate);
	    main.add_icon(get_id());
	}
    }
}

void PluginUI::display_new(bool unordered) {
    display(true, true);
    if (!unordered) {
	rackbox->get_parent()->reorder(get_id(), -1);
    }
    rackbox->swtch(false);
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
    int w2 = std::min(w, max(0, xoff-gradient_length/2)) - 4;
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
    Cairo::RefPtr<Cairo::LinearGradient> grad = Cairo::LinearGradient::create(w, 0, w-gradient_length, 0);
    grad->add_color_stop_rgba(0, 1, 1, 1, 1);
    grad->add_color_stop_rgba(1, 1, 1, 1, 0);
    cr->rectangle(w-gradient_length, 0, gradient_length, h);
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
	b->signal_clicked().connect(sigc::bind(sigc::mem_fun(rb.plugin, &PluginUI::display), false, true));
	w = b;
    } else {
	w = new Gtk::Alignment();
    }
    w->set_size_request(20, 15);
    return w;
}

MiniRackBox::MiniRackBox(RackBox& rb, gx_system::CmdlineOptions& options)
    : Gtk::HBox(),
      evbox(),
      mconbox(false, 4),
      mb_expand_button(),
      mb_delete_button(),
      preset_button(),
      on_off_switch(new Gxw::Switch("minitoggle")),
      toggle_on_off(rb.main.get_ui(), *on_off_switch, &rb.plugin.plugin->on_off) {
    if (!szg_label) {
	szg_label = Gtk::SizeGroup::create(Gtk::SIZE_GROUP_HORIZONTAL);
    }
    evbox.set_visible_window(false);
    add(evbox);
    Gtk::HBox *box = new Gtk::HBox();
    evbox.add(*manage(box));
    Gtk::Alignment *al = new Gtk::Alignment(0.5, 0.5, 0.0, 0.0);
    al->add(*on_off_switch);
#ifdef USE_SZG
    RackBox::szg->add_widget(*al);
#else
    al->set_size_request(35, -1);
#endif
    box->pack_start(*manage(al), Gtk::PACK_SHRINK);
    Gtk::Widget *effect_label = RackBox::make_label(rb.plugin, options);
    szg_label->add_widget(*manage(effect_label));
    al = new Gtk::Alignment(0.0, 0.0, 0.0, 0.0);
    al->add(*manage(rb.wrap_bar()));
    box->pack_start(*manage(al), Gtk::PACK_SHRINK);
    box->pack_start(*manage(effect_label), Gtk::PACK_SHRINK);
    box->pack_start(mconbox, Gtk::PACK_EXPAND_WIDGET, 15);
    al = new Gtk::Alignment(0.0, 0.0, 0.0, 0.0);
    Gtk::HBox *hb = new Gtk::HBox();
    al->add(*manage(hb));
    mb_expand_button = rb.make_expand_button(true);
    hb->pack_start(*manage(mb_expand_button), Gtk::PACK_SHRINK);
    mb_delete_button = make_delete_button(rb);
    mb_delete_button->set_no_show_all(true);
    hb->pack_start(*manage(mb_delete_button), Gtk::PACK_SHRINK);
    al->set_padding(1, 0, 4, 4);
    pack_end(*manage(al), Gtk::PACK_SHRINK);
    box->pack_end(*manage(rb.wrap_bar(8)), Gtk::PACK_SHRINK);
    preset_button = rb.make_preset_button();
    box->pack_end(*manage(preset_button), Gtk::PACK_SHRINK);
    show_all();
}

void MiniRackBox::pack(Gtk::Widget *w) {
    if (w) {
	mconbox.pack_start(*manage(w), Gtk::PACK_SHRINK, 4);
    }
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

#ifdef USE_SZG
Glib::RefPtr<Gtk::SizeGroup> RackBox::szg;
#endif

void RackBox::set_paintbox(Gxw::PaintBox& pb, PluginType tp) {
    pb.set_name("rackbox");
    pb.property_paint_func().set_value("rectangle_skin_color_expose");
    pb.set_border_width(4);
}

Gtk::Widget *RackBox::make_label(const PluginUI& plugin, gx_system::CmdlineOptions& options, bool useshort) {
    const char *effect_name;
    if (useshort) {
	effect_name = plugin.shortname;
	if (!effect_name) {
	    effect_name = plugin.get_name();
	}
    } else {
	effect_name = plugin.get_name();
    }
    Gtk::Label *effect_label = new Gtk::Label(effect_name);
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

Gtk::Widget *RackBox::wrap_bar(int left, int right, bool sens) {
    Gtk::EventBox *ev = new Gtk::EventBox;
    ev->set_visible_window(false);
    ev->set_above_child(true);
    ev->add(*manage(make_bar(left, right, sens)));
    ev->signal_drag_begin().connect(sigc::mem_fun(*this, &RackBox::on_my_drag_begin));
    ev->signal_drag_end().connect(sigc::mem_fun(*this, &RackBox::on_my_drag_end));
    ev->signal_drag_data_get().connect(sigc::mem_fun(*this, &RackBox::on_my_drag_data_get));
    std::vector<Gtk::TargetEntry> listTargets;
    listTargets.push_back(Gtk::TargetEntry(target, Gtk::TARGET_SAME_APP, 0));
    ev->drag_source_set(listTargets, Gdk::BUTTON1_MASK, Gdk::ACTION_MOVE);
    return ev;
}

Gtk::Widget *RackBox::create_icon_widget(const PluginUI& plugin, gx_system::CmdlineOptions& options) {
    Gxw::PaintBox *pb = new Gxw::PaintBox(Gtk::ORIENTATION_HORIZONTAL);
    RackBox::set_paintbox(*pb, plugin.get_type());
    Gtk::Widget *effect_label = RackBox::make_label(plugin, options);
    Gtk::Alignment *al = new Gtk::Alignment(0.0, 0.0, 1.0, 1.0);
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
    swtch->set_active(plugin.plugin->on_off);
#ifdef USE_SZG
    RackBox::szg->add_widget(*swtch);
#else
    swtch->set_size_request(35, -1);
#endif
    pb->pack_start(*manage(swtch), Gtk::PACK_SHRINK);
    Gtk::Widget *effect_label = RackBox::make_label(plugin, options);
    Gtk::Alignment *al = new Gtk::Alignment(0.0, 0.0, 0.0, 0.0);
    al->set_padding(0,0,4,20);
    al->add(*manage(RackBox::make_bar(4, 4, true))); // FIXME: fix style and remove sens parameter
    pb->pack_start(*manage(al), Gtk::PACK_SHRINK);
    pb->pack_start(*manage(effect_label), Gtk::PACK_SHRINK);
    al = new Gtk::Alignment(0.0, 0.0, 0.0, 0.0);
    al->set_size_request(50,-1);
    pb->pack_start(*manage(al), Gtk::PACK_SHRINK);
    pb->show_all();
    return pb;
}

void RackBox::display(bool v, bool animate) {
    box_visible = v;
    if (v) {
	if (animate) {
	    animate_insert();
	} else {
	    show();
	}
    } else {
	if (animate) {
	    animate_remove();
	} else {
	    hide();
	}
    }
}

RackBox::RackBox(PluginUI& plugin_, MainWindow& tl, Gtk::Widget* bare)
    : Gtk::VBox(), plugin(plugin_), main(tl), vis(true), config_mode(false), anim_tag(),
      compress(true), delete_button(true), mbox(Gtk::ORIENTATION_HORIZONTAL), minibox(0),
      fbox(0), target(), anim_height(0), anim_step(), drag_icon(), target_height(0), preset_index(-1), presets(),
      box(Gtk::ORIENTATION_HORIZONTAL, 2), box_visible(true), position(), effect_post_pre(), on_off_switch(new Gxw::Switch("switchit")),
      toggle_on_off(tl.get_ui(), *on_off_switch, &plugin.plugin->on_off) {
#ifdef USE_SZG
    if (!szg) {
	szg = Gtk::SizeGroup::create(Gtk::SIZE_GROUP_HORIZONTAL);
    }
#endif
    //FIXME fill presets
    if (bare) {
	compress = false;
	delete_button = false;
    }
    set_paintbox(mbox, plugin.get_type());
    init_dnd();
    minibox = new MiniRackBox(*this, tl.get_options());
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
    anim_height -= anim_step;
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

void RackBox::animate_remove() {
    if (!get_parent()->check_if_animate(*this)) {
	hide();
    } else {
	if (anim_tag.connected()) {
	    //Glib::source_remove(anim_tag);
	    anim_tag.disconnect();
	    set_size_request(-1,-1);
	    show();
	}
	anim_height = size_request().height;
	anim_step = anim_height / 5;
	anim_tag = Glib::signal_timeout().connect(sigc::mem_fun(*this, &RackBox::animate_vanish), 20);
    }
}

RackContainer *RackBox::get_parent() {
    return dynamic_cast<RackContainer*>(Gtk::VBox::get_parent());
}

void RackBox::on_my_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context) {
    int x, y;
    get_pointer(x, y);
    drag_icon = new DragIcon(plugin, context, main.get_options(), x);
    animate_remove();
}

bool RackBox::animate_create() {
    bool ret = true;
    anim_height += anim_step;
    if (anim_height >= target_height) {
	set_size_request(-1,-1);
	//anim_tag.disconnect(); //FIXME
	ret = false;
    } else {
	set_size_request(-1, anim_height);
    }
    get_parent()->ensure_visible(*this);
    return ret;
}

void RackBox::animate_insert() {
    if (!get_parent()->check_if_animate(*this)) {
	show();
	get_parent()->ensure_visible(*this);
    } else {
	if (anim_tag.connected()) {
	    hide();
	    anim_tag.disconnect();
	    set_size_request(-1,-1);
	}
	target_height = size_request().height;
	set_size_request(-1,0);
	show();
	anim_height = 0;
	anim_step = target_height / 5;
	anim_tag = Glib::signal_timeout().connect(mem_fun(*this, &RackBox::animate_create), 20);
    }
}

void RackBox::on_my_drag_end(const Glib::RefPtr<Gdk::DragContext>& context) {
    if (drag_icon) {
	delete drag_icon;
	drag_icon = 0;
    }
    if (box_visible) {
	animate_insert();
    }
}

void RackBox::on_my_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection, int info, int timestamp) {
    selection.set(target, plugin.get_id());
}

void RackBox::vis_switch(Gtk::Widget& a, Gtk::Widget& b) {
    a.hide();
    b.show();
}

void RackBox::swtch(bool mini) {
    if (config_mode) {
	vis = !mini;
    } else {
	if (mini) {
	    vis_switch(*fbox, mbox);
	} else {
	    vis_switch(mbox, *fbox);
	}
    }
}

void RackBox::set_config_mode(bool mode) {
    minibox->set_config_mode(mode);
    if (mode) {
	vis = fbox->get_visible();
	if (vis) {
	    swtch(true);
	}
	config_mode = true;
    } else {
	config_mode = false;
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
    b->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &RackBox::swtch), !expand));
    return b;
}

void RackBox::on_preset_popup_destroy(Gtk::Menu *w) {
    preset_index = w->property_active();
    delete w;
}

void RackBox::preset_popup() {
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
    p->signal_clicked().connect(mem_fun(*this, &RackBox::preset_popup));
    return p;
}

void RackBox::pack(Gtk::Widget *main, Gtk::Widget *mini) {
    if (!main) {
	return;
    }
    box.pack_start(*manage(main));
    minibox->pack(mini);
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
    Gtk::Alignment *al = new Gtk::Alignment(0.0, 0.0, 0.0, 0.7);
    al->add(*manage(vbox));
    al->set_padding(1, 0, 0, 4);
    bx->pack_end(*manage(al), Gtk::PACK_SHRINK);
    bx->pack_end(*manage(wrap_bar(4, 8)), Gtk::PACK_SHRINK);
    bx->show_all();
    return bx;
}

Gtk::VBox *RackBox::switcher_vbox(gx_system::CmdlineOptions& options) {
    Gtk::VBox *vbox = new Gtk::VBox();
    Gtk::Widget *effect_label = make_label(plugin, options, true);
    vbox->pack_start(*manage(effect_label), Gtk::PACK_SHRINK);
    Gtk::HBox *hbox = new Gtk::HBox();
    vbox->pack_start(*manage(hbox));
    Gtk::HBox *hbox2 = new Gtk::HBox();
    hbox->pack_start(*manage(hbox2), Gtk::PACK_SHRINK);
    Gtk::VBox *vbox2 = new Gtk::VBox();
    hbox2->pack_start(*manage(vbox2));
    hbox2->pack_start(*manage(wrap_bar()), Gtk::PACK_SHRINK);
#ifdef USE_SZG
    szg->add_widget(on_off_switch);
#endif
    Gtk::Alignment *al = new Gtk::Alignment(0.5, 0.5, 0.0, 0.0);
    al->add(*on_off_switch);
    vbox2->pack_start(*manage(al));
    return vbox;
}


/****************************************************************
 ** class RackContainer
 */

RackContainer::RackContainer(PluginType tp_, MainWindow& main_)
    : Gtk::VBox(), tp(tp_), main(main_), config_mode(false), in_drag(-2), child_count(0), switch_level(1), targets(),
      highlight_connection(), autoscroll_connection() {
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
        int depth;
        get_window()->get_geometry(x, y, width, height, depth);
	x = 0;
	y = 0;
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
    assert(child_count >= 0);
    renumber();
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
	highlight_connection.disconnect();
    }
    highlight_connection = signal_expose_event().connect(sigc::bind(sigc::mem_fun(*this, &RackContainer::drag_highlight_expose), ind), true);
    queue_draw();
    in_drag = ind;
    if (!autoscroll_connection.connected()) {
	autoscroll_connection = Glib::signal_timeout().connect(sigc::mem_fun(*this, &RackContainer::scroll_timeout), 50);
    }
    return true;
}

void RackContainer::ensure_visible(RackBox& child) {
    Gtk::Allocation alloc = child.get_allocation();
    Gtk::Viewport *p = dynamic_cast<Gtk::Viewport*>(get_ancestor(GTK_TYPE_VIEWPORT));
    p->get_vadjustment()->clamp_page(alloc.get_y(), alloc.get_y()+alloc.get_height());
}

bool RackContainer::scroll_timeout() {
    Gtk::Viewport *p = dynamic_cast<Gtk::Viewport*>(get_ancestor(GTK_TYPE_VIEWPORT));
    Gtk::Adjustment *a = p->get_vadjustment();
    double off = a->get_value();
    Gtk::Allocation alloc = get_allocation();
    int tl = off - alloc.get_y();
    int bl = tl + p->get_allocation().get_height();
    int x, y;
    get_pointer(x, y);
    const double scroll_edge_size = 60.0;
    const int step_size = 20;
    double diff = y - tl - scroll_edge_size;
    if (diff > 0) {
	diff = y + scroll_edge_size - bl;
	if (diff < 0) {
	    return true;
	}
	diff = max(0.0, min(scroll_edge_size, diff));
    } else {
	diff = max(-scroll_edge_size, min(0.0, diff));
    }
    off += step_size * diff/scroll_edge_size;
    if (off < alloc.get_y()) {
	if (diff < 0) {
	    off = alloc.get_y();
	}
    } else {
	int t = alloc.get_y() + alloc.get_height()- a->get_page_size();
	if (off > t) {
	    if (diff > 0) {
		off = t;
	    }
	}
    }
    a->set_value(off);
    return true;
}

void RackContainer::on_drag_leave(const Glib::RefPtr<Gdk::DragContext>& context, guint timestamp) {
    if (in_drag > -2) {
	highlight_connection.disconnect();
	queue_draw();
	in_drag = -2;
    }
    autoscroll_connection.disconnect();
}

void RackContainer::on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, guint info, guint timestamp) {
    int i, ind;
    find_index(x, y, &i, &ind);
    std::string dtype = data.get_data_type();
    if (dtype == "application/x-gtk-tool-palette-item-mono" || dtype == "application/x-gtk-tool-palette-item-stereo") {
	main.get_plugin(data.get_data_as_string())->display_new(true);
    }
    reorder(data.get_data_as_string(), i);
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
	    r = *v;
	    break;
	}
	++i;
    }
    assert(r);
    if (!r) {
	return;
    }
    reorder_child(*r, pos);
    renumber();
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
    renumber();
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

bool rackboxes_less(RackBox *a, RackBox *b) {
    return a->position_weight() < b->position_weight();
}

void RackContainer::check_order() {
    int last_weight = -1;
    bool in_order = true;
    rackbox_list l = get_children();
    for (rackbox_list::iterator c = l.begin(); c != l.end(); ++c) {
	if (in_order) {
	    int w = (*c)->position_weight();
	    if (w < last_weight) {
		in_order = false;
	    }
	    last_weight = w;
	}
	(*c)->storeOrder();
    }
    if (!in_order) {
	std::vector<RackBox*> ol = get_children();
	std::sort(ol.begin(), ol.end(), rackboxes_less);
	int n = 0;
	for (std::vector<RackBox*>::iterator i = ol.begin(); i != ol.end(); ++i) {
	    reorder_child(**i, n++);
	}
    }
}

void RackContainer::renumber() {
    rackbox_list l = get_children();
    int pos = 0;
    unsigned int post_pre = 1;
    for (rackbox_list::iterator c = l.begin(); c != l.end(); ++c, ++pos) {
	if (strcmp((*c)->get_id(), "ampstack") == 0) { // FIXME
	    pos = 0;
	    post_pre = 0;
	    continue;
	}
	(*c)->setOrder(pos, post_pre);
    }
}

/****************************************************************
 ** class StackBoxBuilderNew
 */

StackBoxBuilderNew::StackBoxBuilderNew(
    gx_engine::GxEngine& engine_, gx_engine::ParamMap& pmap_, gx_gui::MainMenu &mainmenu_,
    Gxw::WaveView &fWaveView_, Gtk::Label &convolver_filename_label_, gx_ui::GxUI& ui_,
    Glib::RefPtr<Gdk::Pixbuf> window_icon)
    : StackBoxBuilder(fTop, fBox, engine_, pmap_, fMode, mainmenu_, fWaveView_, convolver_filename_label_, ui_, window_icon),
      engine(engine_), pmap(pmap_), mainmenu(mainmenu_), fWaveView(fWaveView_),
      convolver_filename_label(convolver_filename_label_), widget() {
}

void StackBoxBuilderNew::openMonoRackBox(const char* label, int* posit, const char *id_on_off, const char *id_pre_post, const char *id_dialog) {
}

void StackBoxBuilderNew::closeMonoRackBox() {
}

void StackBoxBuilderNew::openStereoRackBox(const char* label, int* posit, const char *id_on_off, const char *id_dialog) {
}

void StackBoxBuilderNew::closeStereoRackBox() {
}

void StackBoxBuilderNew::openVerticalMidiBox(const char* label) {
    openVerticalBox(label);
}

void StackBoxBuilderNew::prepare() {
    fTop = 0;
    widget = new Gtk::VBox();
    widget->show();
    fBox[fTop] = GTK_WIDGET(widget->gobj());
    fMode[fTop] = kBoxMode;
}

#ifndef NDEBUG
void wnotify(gpointer data, GObject *where_the_object_was) {
    printf("WN %p %p\n", where_the_object_was, data);
}

// check if object will be finalized
void trace_finalize(Glib::Object *o, int n) {
    g_object_weak_ref(o->gobj(), wnotify, (gpointer)n);
}
#endif

void StackBoxBuilderNew::fetch(Gtk::Widget*& mainbox, Gtk::Widget*& minibox) {
    assert(fTop == 0);
    mainbox = widget;
    Glib::ListHandle<Gtk::Widget*> l = widget->get_children();
    if (l.size() == 2) {
	Glib::ListHandle<Gtk::Widget*>::iterator i = l.begin();
	minibox = new Gtk::VBox();
	minibox->show();
	(*i)->show();
	(*i)->reference(); //FIXME can't unmanage widget, reparent unrefs
	(*i)->reparent(*minibox);
    } else {
	minibox = 0;
    }
}

void StackBoxBuilderNew::get_box(const std::string& name, Gtk::Widget*& mainbox, Gtk::Widget*& minibox) {
    struct {
	const char *name;
	void (StackBoxBuilder::*func)();
    } mapping[] = {
	// mono
	{ "ampdetail", &StackBoxBuilder::make_rackbox_ampdetail },
	{ "overdrive", &StackBoxBuilder::make_rackbox_overdrive },
	{ "echo", &StackBoxBuilder::make_rackbox_echo },
	{ "delay", &StackBoxBuilder::make_rackbox_delay },
	{ "freeverb", &StackBoxBuilder::make_rackbox_freeverb },
	{ "oscilloscope", &StackBoxBuilder::make_rackbox_oscilloscope },
	{ "low_highpass", &StackBoxBuilder::make_rackbox_low_highpass },
	{ "eqs", &StackBoxBuilder::make_rackbox_eqs },
	//{ "crybaby", &StackBoxBuilder::make_rackbox_crybaby },
	{ "gx_distortion", &StackBoxBuilder::make_rackbox_gx_distortion },
	{ "IR", &StackBoxBuilder::make_rackbox_IR },
	{ "compressor", &StackBoxBuilder::make_rackbox_compressor },
	{ "biquad", &StackBoxBuilder::make_rackbox_biquad },
	//{ "tremolo", &StackBoxBuilder::make_rackbox_tremolo },
	{ "phaser_mono", &StackBoxBuilder::make_rackbox_phaser_mono },
	{ "chorus_mono", &StackBoxBuilder::make_rackbox_chorus_mono },
	{ "flanger_mono", &StackBoxBuilder::make_rackbox_flanger_mono },
	{ "feedback", &StackBoxBuilder::make_rackbox_feedback },
	//{ "amp.tonestack", &StackBoxBuilder::make_rackbox_amp_tonestack },
	{ "cab", &StackBoxBuilder::make_rackbox_cab },
	{ "midi_out", &StackBoxBuilder::make_rackbox_midi_out },
	// stereo
	{ "chorus", &StackBoxBuilder::make_rackbox_chorus },
	{ "flanger", &StackBoxBuilder::make_rackbox_flanger },
	{ "phaser", &StackBoxBuilder::make_rackbox_phaser },
	{ "stereodelay", &StackBoxBuilder::make_rackbox_stereodelay },
	{ "stereoecho", &StackBoxBuilder::make_rackbox_stereoecho },
	{ "moog", &StackBoxBuilder::make_rackbox_moog },
	{ "ampmodul", &StackBoxBuilder::make_rackbox_ampmodul },
	{ "tonemodul", &StackBoxBuilder::make_rackbox_tonemodul },
	{ "jconv", &StackBoxBuilder::make_rackbox_jconv },
	{ "stereoverb", &StackBoxBuilder::make_rackbox_stereoverb }
    };
    mainbox = minibox = 0;
    for (unsigned int i = 0; i < sizeof(mapping) / sizeof(mapping[0]); ++i) {
	if (name == mapping[i].name) {
	    prepare();
	    (this->*mapping[i].func)();
	    fetch(mainbox, minibox);
	}
    }
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
#ifndef NDEBUG
    gx_system::gx_print_error("freezer", "timeout");
#else
    gx_system::gx_print_warning("freezer", "timeout");
#endif
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
    Gdk::Geometry geom;
    geom.min_width = req.width;
    geom.min_height = req.height;
    w->set_geometry_hints(geom, Gdk::HINT_MIN_SIZE);
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
	window_height = max(window_height, window->size_request().height);
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
    if (freezer.check_thaw(ev->width, ev->height)) {
	if (is_variable_size()) {
	    window_height = ev->height;
	}
    }
}

RackBox *MainWindow::add_rackbox_internal(PluginUI& plugin, Gtk::Widget *mainwidget, Gtk::Widget *miniwidget,
					  bool mini, int pos, bool animate, Gtk::Widget *bare) {
    RackBox *r = new RackBox(plugin, *this, bare);
    if (mini) {
	r->swtch(true);
    }
    r->pack(mainwidget, miniwidget);
    if (plugin.get_type() == PLUGIN_TYPE_MONO) {
	monorackcontainer.add(*manage(r), pos);
	monorackcontainer.set_size_request(-1, -1);
    } else {
	stereorackcontainer.add(*manage(r), pos);
    }
    if (animate) {
	r->animate_insert();
    }
    return r;
}

class UiBuilderImplNew: public gx_gui::UiBuilderImpl {
public:
    virtual bool load(gx_engine::Plugin *p);
    UiBuilderImplNew(StackBoxBuilderNew *i);
};

UiBuilderImplNew::UiBuilderImplNew(StackBoxBuilderNew *i)
    : gx_gui::UiBuilderImpl(i) {
}

bool UiBuilderImplNew::load(gx_engine::Plugin *p) {
    PluginDef *pd = p->pdef;
    if (!pd->load_ui) {
	return false;
    }
    plugin = pd;
    dynamic_cast<StackBoxBuilderNew*>(intf)->prepare();
    if (pd->flags & PGN_STEREO) {
	pd->load_ui(*this);
    } else {
	pd->load_ui(*this);
    }
    return true;
}

void load_rack_ui(const std::string& fname, gx_ui::GxUI& ui, Gtk::Widget*& mainwidget, Gtk::Widget*& miniwidget) {
    const char *id_list[] = {"rackbox", "minibox", 0};
    Glib::RefPtr<gx_gui::GxBuilder> bld = gx_gui::GxBuilder::create_from_file(fname, &ui, id_list);
    bld->get_toplevel("rackbox", mainwidget);
    miniwidget = 0;
    if (bld->has_object("minibox")) {
	bld->get_toplevel("minibox", miniwidget);
    }
}

RackBox *MainWindow::add_rackbox(PluginUI& pl, bool mini, int pos, bool animate) {
    Gtk::Widget *mainwidget = 0;
    Gtk::Widget *miniwidget = 0;
    if (!mainwidget && !pl.fname.empty()) {
	load_rack_ui(pl.fname, ui, mainwidget, miniwidget);
    }
    if (!mainwidget) {
	boxbuilder.get_box(pl.get_id(), mainwidget, miniwidget);
    }
    if (!mainwidget) {
	UiBuilderImplNew builder(&boxbuilder);
	if (builder.load(pl.plugin)) {
	    boxbuilder.fetch(mainwidget, miniwidget);
	}
    }
    if (!mainwidget) {
	std::string gladefile = options.get_builder_filepath(
	    std::string(pl.get_id())+"_ui.glade");
	if (access(gladefile.c_str(), R_OK) == 0) {
	    load_rack_ui(gladefile, ui, mainwidget, miniwidget);
	}
    }
    return add_rackbox_internal(pl, mainwidget, miniwidget, mini, pos, animate);
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
	"style \"ShowValue\" {\n"
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
	get_plugin(effect_id)->display_new();
	return true;
    }
    return false;
}

void MainWindow::on_tp_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& data, int info, int timestamp) {
    Glib::ustring id = data.get_data_as_string();
    PluginUI *p = get_plugin(id);
    p->display(false, false);
    add_icon(id);
    p->group->set_collapsed(false);
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

void MainWindow::add_plugin(std::vector<PluginUI*> *p, const char *id, const Glib::ustring& fname, const Glib::ustring& tooltip) {
    PluginUI *pui = new PluginUI(*this, engine.pluginlist, id, fname, tooltip);
    ui.registerZone(&pui->plugin->box_visible, pui);
    ui.registerZone(&pui->plugin->position, pui);
    ui.registerZone(&pui->plugin->effect_post_pre, pui);
    p->push_back(pui);
}

void MainWindow::fill_pluginlist() {
    std::vector<PluginDesc*> l;
    std::vector<PluginUI*> *p;

    p = new std::vector<PluginUI*>;
    add_plugin(p, "low_highpass");
    add_plugin(p, "eqs");
    add_plugin(p, "IR");
    add_plugin(p, "biquad");
    add_plugin(p, "feedback");
    add_plugin(p, "amp.tonestack");
    add_plugin(p, "cab");
    add_plugin(p, "moog");
    add_plugin(p, "tonemodul");
    l.push_back(new PluginDesc("Tone control", p));

    p = new std::vector<PluginUI*>;
    add_plugin(p, "gx_distortion");
    add_plugin(p, "overdrive");
    add_plugin(p, "ampmodul");
    l.push_back(new PluginDesc("Distortion", p));

    p = new std::vector<PluginUI*>;
    add_plugin(p, "freeverb");
    add_plugin(p, "jconv");
    add_plugin(p, "stereoverb");
    add_plugin(p, "zita_rev1", "", "High Quality Reverb");
    l.push_back(new PluginDesc("Reverb", p));

    p = new std::vector<PluginUI*>;
    add_plugin(p, "echo");
    add_plugin(p, "delay");
    add_plugin(p, "stereodelay");
    add_plugin(p, "stereoecho");
    l.push_back(new PluginDesc("Echo / Delay", p));

    p = new std::vector<PluginUI*>;
    add_plugin(p, "tremolo");
    add_plugin(p, "phaser_mono");
    add_plugin(p, "chorus_mono");
    add_plugin(p, "flanger_mono");
    add_plugin(p, "chorus");
    add_plugin(p, "flanger");
    add_plugin(p, "phaser");
    //add_plugin(p_TYPE_STEREO, "univibe");
    l.push_back(new PluginDesc("Modulation", p));

    p = new std::vector<PluginUI*>;
    add_plugin(p, "crybaby");
    //add_plugin(p, PLUGIN_TYPE_MONO, "crybaby2");
    add_plugin(p, "compressor");
    l.push_back(new PluginDesc("Guitar Effects", p));

    p = new std::vector<PluginUI*>;
    add_plugin(p, "oscilloscope");
    add_plugin(p, "midi_out");
    l.push_back(new PluginDesc("Misc", p));

    for (std::vector<PluginDesc*>::iterator i = l.begin(); i != l.end(); ++i) {
	for (std::vector<PluginUI*>::iterator v = (*i)->plugins->begin(); v != (*i)->plugins->end(); ++v) {
	    PluginUI *pui = *v;
	    plugin_dict[pui->get_id()] = pui;
	}
    }
    make_icons(plugin_dict, options);
    bool collapse = false;
    for (std::vector<PluginDesc*>::iterator i = l.begin(); i != l.end(); ++i) {
	Gtk::ToolItemGroup *gw = new Gtk::ToolItemGroup((*i)->group);
	gw->set_collapsed(collapse);
	collapse = true;
	for (std::vector<PluginUI*>::iterator v = (*i)->plugins->begin(); v != (*i)->plugins->end(); ++v) {
	    add_toolitem(**v, gw);
	}
	effects_toolpalette->add(*manage(gw));
	effects_toolpalette->set_exclusive(*gw, true);
	effects_toolpalette->set_expand(*gw, true);
    }
}

/* Update all user items reflecting zone z */
bool MainWindow::update_all_gui() {
    // the general Gui update handler
    gx_ui::GxUI::updateAllGuis();
    engine.check_module_lists();
    return true;
}

MainWindow::MainWindow(gx_engine::GxEngine& engine_, gx_system::CmdlineOptions& options_, gx_engine::ParamMap& pmap_)
    : sigc::trackable(), window_height(0), freezer(), bld(), oldpos(0), scrl_size_x(-1), scrl_size_y(-1),
      monorackcontainer(PLUGIN_TYPE_MONO, *this), stereorackcontainer(PLUGIN_TYPE_STEREO, *this),
      pre_act(false), is_visible(false), drag_icon(0), plugin_dict(), actiongroup(), uimanager(),
      ui(), options(options_), pmap(pmap_), engine(engine_), jack(engine),
      gx_settings(options, jack, engine.convolver, gx_engine::midi_std_ctr, gx_engine::controller_map, engine, pmap_),
      mainamp_plugin(*this, engine.pluginlist, "ampstack"), live_play(), preset_window(),
      mainmenu(ui, options_, pmap_),
      fWaveView(),
      convolver_filename_label(),
      boxbuilder(engine_, pmap_, mainmenu, fWaveView, convolver_filename_label, ui,
		 Gdk::Pixbuf::create_from_file(options.get_pixmap_filepath("gx_head.png"))) {
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

    fill_pluginlist();
    plugin_dict["gx_distortion"]->shortname = _("Distortion");

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

    live_play = new Liveplay(options, engine, gx_settings, options.get_builder_filepath("mainpanel.glade"), actiongroup);
    preset_window = new PresetWindow(bld, gx_settings, options, actiongroup);


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
    effects_toolpalette->show_all();

    plugin_dict[mainamp_plugin.get_id()] = &mainamp_plugin;
    add_rackbox_internal(mainamp_plugin, 0, 0, false, -1, false, amp_background);
    window->signal_visibility_notify_event().connect(sigc::mem_fun(*this, &MainWindow::on_visibility_notify));
    gx_settings.loadstate();
    gx_ui::GxUI::updateAllGuis(true);
    Glib::signal_timeout().connect(mem_fun(*this, &MainWindow::update_all_gui), 40);
    window->show();
}

MainWindow::~MainWindow() {
    for (std::map<std::string, PluginUI*>::iterator i = plugin_dict.begin(); i != plugin_dict.end(); ++i) {
	ui.unregisterZone(&i->second->plugin->box_visible, i->second);
	ui.unregisterZone(&i->second->plugin->position, i->second);
	ui.unregisterZone(&i->second->plugin->effect_post_pre, i->second);
	if (i->second != &mainamp_plugin) {
	    delete i->second;
	}
    }
    delete live_play;
    delete preset_window;
    delete window;
}

void start_main(gx_engine::GxEngine& engine, gx_system::CmdlineOptions& options, gx_engine::ParamMap& pmap) {
    MainWindow w(engine, options, pmap);
    w.run();
}

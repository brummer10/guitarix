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
 * --------------------------------------------------------------------------
 *
 *    This file is part of the guitarix GUI main class
 *    Note: this header file depends on gx_ui.h 
 *    and is the base for gx_main_boxes.h
 * 
 * ----------------------------------------------------------------------------
 */

/* ------- This is the GUI namespace ------- */

#pragma once

#ifndef SRC_HEADERS_GX_MAIN_INTERFACE_H_
#define SRC_HEADERS_GX_MAIN_INTERFACE_H_

#include <gxwmm/bigknob.h>
#include <gxwmm/smallknob.h>
#include <gxwmm/smallknobr.h>
#include <gxwmm/wheel.h>
#include <gxwmm/hslider.h>
#include <gxwmm/eqslider.h>
#include <gxwmm/levelslider.h>
#include <gxwmm/minislider.h>
#include <gxwmm/switch.h>
#include <gxwmm/selector.h>
#include <gxwmm/valuedisplay.h>
#include <gxwmm/simplevaluedisplay.h>
#include <gxwmm/fastmeter.h>
#include <gxwmm/tuner.h>
#include <gxwmm/waveview.h>
#include <gtkmm/box.h>
#include <gtkmm/alignment.h>
#include <gtkmm/checkmenuitem.h>
#include <gtkmm/radiomenuitem.h>
#include <gtkmm/builder.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace gx_gui {

class GxMainInterface;

class UiBuilderImpl: public gx_engine::UiBuilderBase {
private:
    static GxMainInterface *intf;
    static void openVerticalBox_(const char* label);
    static void openHorizontalBox_(const char* label);
    static void create_small_rackknob_(const char *id, const char *label);
    static void create_selector_(const char *id);
    static void closeBox_();
    static void load_glade_(const char *data);
    void load(gx_engine::Plugin *p);
public:
    UiBuilderImpl(GxMainInterface *i);
};

/****************************************************************
 **
 ** ---------------- the main GUI class ----------------
 **
 */

class GuiVariables {
 public:
    bool                dialogbox[35];
    
    float               show_patch_info;

    /* rack handlig */
    int                 mono_plugs;
    int                 stereo_plugs;
    int                 refresh_size;

    int                 g_threads[14];
    /* for level display */
    int                 meter_display_timeout; // in millisec
    int                 meter_falloff ; // in dB/sec.
    /* midi_in preset switch */
    
    int                 main_xorg;
    int                 main_yorg;
    string              skin;

    void register_gui_parameter(gx_engine::ParamMap& pmap);
};

extern GuiVariables guivar;

/****************************************************************/

/* global GUI widgets */
class GlobalWidgets {
 public:
    /* global GUI widgets */
    GtkWidget*          midibox;
    GtkWidget*          patch_info;
    GtkWidget*          tuner_widget;
    GtkWidget*          rack_widget;
    GtkWidget*          srack_widget;
    GtkWidget*          rack_tool_bar;
};

extern GlobalWidgets gw;

/****************************************************************/

void gx_start_stop_jconv(GtkWidget*, gpointer);

/****************************************************************/

/* ---- linking menu items and parameter ---- */
class MenuCheckItem: public Gtk::CheckMenuItem {
 private:
    gx_engine::SwitchParameter* param;
    void on_my_activate();
 public:
    // FIXME not gtk-2.12: MenuCheckItem() { set_use_underline(); }
    MenuCheckItem(): Gtk::CheckMenuItem("", true), param() {}
    MenuCheckItem(const char *label): Gtk::CheckMenuItem(label, true), param() {}
    void set_parameter(gx_engine::SwitchParameter *p);
    void add_parameter(gx_engine::SwitchParameter *p);
    gx_engine::SwitchParameter * get_parameter();
};

class MenuCheckItemUiBool: public Gtk::CheckMenuItem, gx_ui::GxUiItemBool {
 private:
    virtual void reflectZone();
    void on_my_activate();
 public:
    // FIXME not gtk-2.12: MenuCheckItem() { set_use_underline(); }
    MenuCheckItemUiBool(gx_ui::GxUI* ui, bool* zone);
};

/****************************************************************/

/* ---- linking menu items and parameter ---- */
class RadioCheckItem: public Gtk::RadioMenuItem {
 private:
    gx_engine::SwitchParameter* param;
    void on_my_toggled();
 public:
    // FIXME not gtk-2.12: MenuCheckItem() { set_use_underline(); }
    RadioCheckItem(Gtk::RadioMenuItem::Group& group, const char *label=""):
	Gtk::RadioMenuItem(group, label, true), param() {}
    void set_parameter(gx_engine::SwitchParameter *p);
    gx_engine::SwitchParameter * get_parameter();
};

/****************************************************************/

class ToggleCheckButton: public Gtk::ToggleButton {
 private:
    gx_engine::SwitchParameter* param;
    void on_my_toggled();
 public:
    Gtk::Label m_label;
    void set_parameter(gx_engine::SwitchParameter *p);
    gx_engine::SwitchParameter * get_parameter();
    ToggleCheckButton();
    ~ToggleCheckButton();
};

class ToggleCheckButtonUiBool: public Gtk::ToggleButton, gx_ui::GxUiItemBool {
 private:
    virtual void reflectZone();
    void on_my_toggled();
 public:
    Gtk::Label m_label;
    ToggleCheckButtonUiBool(gx_ui::GxUI* ui, bool* zone);
    ~ToggleCheckButtonUiBool();
};

/****************************************************************/

class UiRegler: gx_ui::GxUiItemFloat, protected Gtk::Adjustment {
 protected:
    Gxw::Regler *m_regler;
    void on_value_changed();
    virtual void reflectZone();
 public:
    static GtkWidget* create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id, bool show_value);
    UiRegler(gx_ui::GxUI &ui, gx_engine::FloatParameter &param, Gxw::Regler *regler, bool show_value);
    virtual ~UiRegler();
    GtkWidget *get_widget() { return GTK_WIDGET(m_regler->gobj()); }
};

/****************************************************************/

class UiSelectorBase {
protected:
    Gxw::Selector m_selector;
public:
    UiSelectorBase(gx_engine::Parameter& param);
    void set_name(Glib::ustring n) { m_selector.set_name(n); }
    GtkWidget *get_widget() { return GTK_WIDGET(m_selector.gobj()); }
};

template <class T>
class UiSelector: public UiSelectorBase, private gx_ui::GxUiItemV<T>, protected Gtk::Adjustment {
private:
    virtual void reflectZone();
    void on_value_changed();
public:
    UiSelector(gx_ui::GxUI& ui, gx_engine::ParameterV<T> &param);
    ~UiSelector();
};

/****************************************************************/

class UiReglerWithCaption: public UiRegler {
 private:
    Gtk::Label m_label;
    Gtk::VBox m_box;
 public:
    static GtkWidget* create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id, bool show_value);
    static GtkWidget* create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id,
                             Glib::ustring label, bool show_value);
    UiReglerWithCaption(gx_ui::GxUI &ui, gx_engine::FloatParameter &param, Gxw::Regler *regler,
                        Glib::ustring label, bool show_value);
    GtkWidget *get_widget() { return GTK_WIDGET(m_box.gobj());}
};

/****************************************************************/

class UiRackReglerWithCaption: public UiRegler {
 private:
    Gtk::Label m_label;
    Gtk::VBox m_box;
 public:
    static GtkWidget* create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id);
    static GtkWidget* create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id,
                             Glib::ustring label);
    UiRackReglerWithCaption(gx_ui::GxUI &ui, gx_engine::FloatParameter &param, Gxw::Regler *regler,
                            Glib::ustring label);
    GtkWidget *get_widget() { return GTK_WIDGET(m_box.gobj());}
};

/****************************************************************/

class UiRackRegler: public UiRegler {
 private:
    Gtk::Label m_label;
    Gtk::VBox m_box;
 public:
    static GtkWidget* create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id);
    static GtkWidget* create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id,
                             Glib::ustring label);
    UiRackRegler(gx_ui::GxUI &ui, gx_engine::FloatParameter &param, Gxw::Regler *regler,
                 Glib::ustring label);
    GtkWidget *get_widget() { return GTK_WIDGET(m_box.gobj());}
};

/****************************************************************/

class UiSwitch: public Gxw::Switch {
 public:
    explicit UiSwitch(const char *sw_type);
    GtkWidget *get_widget() { return GTK_WIDGET(gobj());}
    static UiSwitch *new_switch(gx_ui::GxUI& ui, const char *sw_type, gx_engine::Parameter &param);
    static UiSwitch *new_switch(gx_ui::GxUI& ui, const char *sw_type, string id) {
        if (!gx_engine::parameter_map.hasId(id)) return 0;
        return new_switch(ui, sw_type, gx_engine::parameter_map[id]);
    }
    static GtkWidget *create(gx_ui::GxUI& ui, const char *sw_type, string id) {
        return new_switch(ui, sw_type, id)->get_widget();}
};

/****************************************************************/

class UiSwitchFloat: public UiSwitch, gx_ui::GxUiItemFloat {
 protected:
    void on_toggled();
    virtual void reflectZone();
 public:
    UiSwitchFloat(gx_ui::GxUI& ui, const char *sw_type, gx_engine::FloatParameter &param);
};

/****************************************************************/

class UiSwitchBool: public UiSwitch, gx_ui::GxUiItemBool {
 protected:
    void on_toggled();
    virtual void reflectZone();
 public:
    UiSwitchBool(gx_ui::GxUI& ui, const char *sw_type, gx_engine::BoolParameter &param);
};

/****************************************************************/

class UiSwitchWithCaption {
 private:
    Gtk::Label m_label;
    Gtk::Box *m_box;
 protected:
    UiSwitch *m_switch;
 public:
    static GtkWidget* create(gx_ui::GxUI& ui, const char *sw_type, string id,
                             Gtk::PositionType pos);
    static GtkWidget* create(gx_ui::GxUI& ui, const char *sw_type, string id,
                             Glib::ustring label, Gtk::PositionType pos);
    UiSwitchWithCaption(gx_ui::GxUI &ui, const char *sw_type, gx_engine::Parameter &param,
                        Glib::ustring label, Gtk::PositionType pos);
    ~UiSwitchWithCaption();
    GtkWidget *get_widget() { return GTK_WIDGET(m_box->gobj()); }
};

/****************************************************************/

class UiCabSwitch: public UiSwitchWithCaption {
 private:
    void on_switch_toggled();
 public:
    static GtkWidget* create(gx_ui::GxUI& ui, string id, Glib::ustring label);
    UiCabSwitch(gx_ui::GxUI &ui, gx_engine::Parameter &param, Glib::ustring label);
};

/****************************************************************/

class UiContrastSwitch: public UiSwitchWithCaption {
 private:
    void on_switch_toggled();
 public:
    static GtkWidget* create(gx_ui::GxUI& ui, string id, Glib::ustring label);
    UiContrastSwitch(gx_ui::GxUI &ui, gx_engine::Parameter &param, Glib::ustring label);
};

/****************************************************************/

struct uiTuner : public Gtk::Alignment, private gx_ui::GxUiItemFloat {
 private:
    Gxw::Tuner fTuner;
    Gtk::Fixed fBox;
    Gtk::EventBox eBox;
    Gxw::Wheel wheel;
    float refpitch;
    gx_engine::FloatParameter refpitch_param;
    Gtk::Adjustment adjust;
    gx_engine::TunerAdapter& adapt;
    void freq_changed();
    void reflectZone();
    void on_value_changed();
 public:
    uiTuner(gx_engine::TunerAdapter& a, gx_ui::GxUI& ui);
};

/****************************************************************/

class PToggleButton {
private:
    Gtk::Label m_label;
    void on_clicked();
public:
    Gtk::Button button;
    PToggleButton(const char* label);
    GtkWidget *get_widget() { return GTK_WIDGET(button.gobj()); }
};

/****************************************************************/

class ReportXrun {
private:
    gx_jack::GxJack& jack;
    bool blocked;
    void clear();
public:
    ReportXrun(gx_jack::GxJack& jack_)
	: jack(jack_), blocked(false) {}
    void run();
};

/****************************************************************
 ** KeyFinder
 ** finds next unused Key in a GtkAccelGroup
 */

class KeyFinder {
private:
    typedef list<GtkAccelKey> accel_list;
    unsigned int next_key;
    accel_list l;
    static gboolean add_keys_to_list(GtkAccelKey *key, GClosure *cl, gpointer data);
public:
    KeyFinder(Glib::RefPtr<Gtk::AccelGroup> group);
    ~KeyFinder();
    int operator()();
};

/****************************************************************
 ** GxUiRadioMenu
 ** adds the values of an UEnumParameter as Gtk::RadioMenuItem's
 ** to a Gtk::MenuShell
 */

class GxUiRadioMenu: public gx_ui::GxUiItemUInt {
private:
    vector<Gtk::RadioMenuItem*> items;
    Gtk::RadioButtonGroup group;
    gx_engine::UIntParameter& param;
    virtual void reflectZone();
    void on_activate(int i);
public:
    GxUiRadioMenu(gx_ui::GxUI* ui, gx_engine::UIntParameter& param);
    virtual ~GxUiRadioMenu();
    void setup(Gtk::MenuShell& menucont, Glib::RefPtr<Gtk::AccelGroup>& ag);
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
    Gtk::HBox box;
    Gtk::ScrolledWindow scrollbox;
    Gtk::Expander frame;
    Gtk::TextView tbox;
    static tab_table tagdefs[gx_system::kMessageTypeCount];
    Glib::RefPtr<Gtk::TextTag> tags[gx_system::kMessageTypeCount];
    int highest_unseen_msg_level;
    void set_color();
    bool on_delete_event();
    void set_expander_color(const char *color);
    void show_msg(string msgbuf, gx_system::GxMsgType msgtype, bool plugged);
public:
    TextLoggingBox(const char* label);
    ~TextLoggingBox();
};

#define NJACKLAT (10)

#define stackSize 256
#define kSingleMode 0
#define kBoxMode 1
#define kTabMode 2

class MainMenu: public Gtk::HBox {      // top menu bar box container
public:
    Gtk::MenuBar       menucont; // normal menu (left)
    Gtk::MenuBar       menupix;  // pixmaps on the right
    Gtk::Tooltips      tooltips;

    // menubar images
    Gtk::ImageMenuItem engine_on_image;
    Gtk::Image         engineon;
    Gtk::ImageMenuItem engine_off_image;
    Gtk::Image         engineoff;
    Gtk::ImageMenuItem engine_bypass_image;
    Gtk::Image         engineby;
    Gtk::ImageMenuItem jackd_on_image;
    Gtk::Image         jackstateon;
    Gtk::ImageMenuItem jackd_off_image;
    Gtk::Image         jackstateoff;

    // engine menu
    Gtk::MenuItem      engine_menu_label;
    Gtk::Menu          engine_menu;
    Gtk::CheckMenuItem engine_start_stop_item;
    Gtk::MenuItem      engine_bypass_item;
    Gtk::CheckMenuItem jack_connect_item;
    Gtk::CheckMenuItem portmap_item;
    Gtk::MenuItem      jack_latency_label;
    Gtk::Menu          jack_latency_menu;
    Gtk::RadioMenuItem::Group jack_latency_group;
    Gtk::CheckMenuItem engine_midi_item;
    Gtk::MenuItem      engine_quit_item;

    // preset menu
    Gtk::MenuItem      preset_menu_label;
    Gtk::Menu          preset_menu;
    Gtk::MenuItem      preset_load_item;
    Gtk::MenuItem      preset_save_item;
    Gtk::MenuItem      preset_save_new;
    Gtk::MenuItem      preset_rename_item;
    Gtk::Menu          preset_submenu[GX_NUM_OF_PRESET_LISTS];
    Gtk::MenuItem      preset_factory_settings_label;
    Gtk::Menu          preset_factory_settings_menu;

    // preset more menu
    Gtk::MenuItem      preset_patch_info_item;
    Gtk::MenuItem      preset_load_file_item;
    Gtk::MenuItem      preset_export_file_item;
    Gtk::MenuItem      preset_recall_item;
    Gtk::MenuItem      preset_save_main_item;
    Gtk::MenuItem      preset_more_label;
    Gtk::Menu          preset_more_menu;
    Gtk::MenuItem      preset_next;
    Gtk::MenuItem      preset_previous;
    Gtk::MenuItem      preset_save_active;
    Gtk::MenuItem      preset_rename_active;
    Gtk::MenuItem      preset_delete_active;
    Gtk::MenuItem      preset_delete_all;

    // plugin menu
    Gtk::MenuItem      plugin_menu_label;
    Gtk::Menu          plugin_menu;
    MenuCheckItem      fShowToolBar;
    MenuCheckItem      fShowRRack;
    MenuCheckItem      fShowRack;
    Gtk::MenuItem      plugin_mono_plugins;
    Gtk::Menu          plugin_mono_menu;
    MenuCheckItem      fShowMidiOut;
    MenuCheckItem      fShowSRack;
    Gtk::MenuItem      plugin_stereo_plugins;
    Gtk::Menu          plugin_stereo_menu;
    Gtk::RadioMenuItem::Group rack_order_group;
    RadioCheckItem     fOrdervRack;
    RadioCheckItem     fOrderhRack;

    // amp menu
    Gtk::MenuItem      amp_menu_label;
    Gtk::Menu          amp_menu;
    GxUiRadioMenu      amp_radio_menu;

    // options menu
    Gtk::MenuItem      options_menu_label;
    Gtk::Menu          options_menu;
    Gtk::CheckMenuItem options_meterbridge;
    MenuCheckItem      fShowTuner;
    Gtk::MenuItem      skin_menu_label;
    Gtk::Menu          skin_menu;
    Gtk::RadioMenuItem::Group skingroup;
    MenuCheckItem      fSetMouse;
    MenuCheckItem      fShowLogger;
    MenuCheckItem      fShowTooltips;
    MenuCheckItem      fMidiInPreset;
    Gtk::MenuItem      options_reset_all;

    // about menu
    Gtk::MenuItem      about_menu_label;
    Gtk::Menu          about_menu;
    Gtk::MenuItem      about_about_item;
    Gtk::MenuItem      about_help_item;

    void addEngineMenu(GxMainInterface& intf);
    void addPresetMenu(GxMainInterface& intf);
    void addExtraPresetMenu(GxMainInterface& intf);
    void addPluginMenu(GxMainInterface& intf);
    void addAmpMenu(GxMainInterface& intf);
    void addOptionMenu(GxMainInterface& intf);
    void addGuiSkinMenu(GxMainInterface& intf);
    void addAboutMenu(GxMainInterface& intf);

    void addJackServerMenu(GxMainInterface& intf);

    MainMenu(gx_ui::GxUI& ui, const gx_system::CmdlineOptions& options);
    void setup(GxMainInterface& intf);
};

class GxMainInterface : public sigc::trackable, public gx_ui::GxUI {
    friend class MainMenu;
private:
    static GxMainInterface *instance;
public://FIXME
    Gtk::Window           fWindow;
    gx_system::CmdlineOptions& options;
    // for key acclerators
    Glib::RefPtr<Gtk::AccelGroup> fAccelGroup;
    void portmap_connection_changed(string port1, string port2, bool conn);
private:
    bool                  in_session;
    gx_portmap::PortMapWindow* portmap_window;
    void                  on_portmap_activate();
    void                  on_portmap_response(int);
    /* engine status and switch */
    void refresh_engine_status_display();
    void toggle_engine_switch();
    void toggle_engine_bypass();
    void sync_engine_switch();

    void                  gx_systray_menu(guint button, guint32 activate_time);
    void                  gx_hide_extended_settings();

    void                  addMainMenu();
    void                  addEngineMenu();
    void                  addJackServerMenu();
    void                  addPresetMenu();
    void                  addExtraPresetMenu();
    void                  addPluginMenu();
    void                  addAmpMenu();
    void                  addOptionMenu();
    void                  addGuiSkinMenu();
    void                  addAboutMenu();

    void                  do_program_change(int);
    bool                  on_meter_button_release(GdkEventButton* ev);
    void                  on_tuner_activate();
    void                  gx_show_menu_settings(GtkWidget *widget, gpointer data);
    void                  on_log_activate();
    void                  on_rack_activate();
    void                  on_rrack_activate();
    void                  on_srack_activate();
    void                  on_toolbar_activate();
    void                  on_tube_activate();
    void                  set_mouse_mode();
    void                  on_show_oscilloscope(bool);
    bool                  on_refresh_oscilloscope();
    void                  on_oscilloscope_post_pre(int post_pre);
    int                   on_oscilloscope_activate(bool start);
    void                  on_settings_selection_changed();
    void                  jack_session_event();
    void                  jack_session_event_ins();
    void                  gx_jack_is_down();
    void                  jack_connection_change();
    void                  save_window_position();
    void                  refresh_latency_menu();
    bool                  connect_jack(bool v);
    void                  gx_jack_connection();
    bool                  survive_jack_shutdown();
    void                  set_jack_buffer_size(jack_nframes_t buf_size);
    void                  set_convolver_filename();
    void                  set_in_session();
    Gtk::Label            convolver_filename_label; //FIXME
    int                   fTop;
    GtkWidget*            fBox[stackSize];
    GtkWidget*            rBox;
    GtkWidget*            sBox;
    GtkWidget*            tBox;
    GtkWidget*            fMonoRackContainer;
    GtkWidget*            fStereoRackContainer;
    int                   fMode[stackSize];
    bool                  fStopped;
    TextLoggingBox        fLoggingWindow;
    bool                  on_logger_delete_event(GdkEventAny*);

    Gxw::FastMeter        fLevelMeters[2];
    uiTuner               fTuner;
    Gxw::WaveView         fWaveView;

    GtkWidget*            fSignalLevelBar;

    // jack menu widgets
    Gtk::RadioMenuItem*   fJackLatencyItem[NJACKLAT];

    GtkWidget*            addWidget(const char* label, GtkWidget* w);
    virtual void          pushBox(int mode, GtkWidget* w);
public :
    Glib::RefPtr<Gdk::Pixbuf> gw_ib;
    Glib::RefPtr<Gdk::Pixbuf> gw_ibm;
    Glib::RefPtr<Gdk::Pixbuf> gw_ibr;
    Glib::RefPtr<Gtk::StatusIcon> status_icon;

    gx_engine::GxEngine&  engine;
    gx_jack::GxJack       jack;
    
    MainMenu              mainmenu;  // crash if before GxSettings though not clear why
    Gtk::VBox             toplevel_box;
    gx_preset::GxSettings gx_settings;
private:
    ReportXrun            report_xrun;
public:

    GtkWidget*            RBox;

    static const gboolean expand   = TRUE;
    static const gboolean fill     = TRUE;
    static const gboolean homogene = FALSE;

public:
    explicit GxMainInterface(gx_engine::GxEngine&, gx_system::CmdlineOptions& options);
    ~GxMainInterface();
    static GxMainInterface& get_instance() { assert(instance); return *instance; }
    bool is_in_session() { return in_session; }

    Gtk::RadioMenuItem* const getJackLatencyItem(const jack_nframes_t bufsize) const;
    
    void                  set_waveview_buffer(unsigned int);
    Gxw::WaveView&        getWaveView()               { return fWaveView;        }

    Gxw::FastMeter&       getLevelMeter(unsigned int i) {
            assert(i < sizeof(fLevelMeters)/sizeof(fLevelMeters[0]));
            return fLevelMeters[i];
        }

    // -- layout groups
    void gx_build_mono_rack();
    void gx_build_stereo_rack();
    GtkWidget* openHorizontalOrderBox(const char* label, int* posit);
    void openHorizontalTableBox(const char* label);
    GtkWidget* openHorizontalRestetBox(const char* label, int* posit);
    void openFrameBox(const char* label);
    void openHorizontalBox(const char* label = "");
    void openHorizontalhideBox(const char* label = "");
    void openHorizontalhideBox1(const char* label = "");
    void openVerticalBox(const char* label = "");
    void openVerticalBox1(const char* label = "");
    void openFlipLabelBox(const char* = "");
    void openSetLabelBox();
    void openVerticalSwitchBox(const char* label, int state, int wit, float* zone);
    void openVerticalMidiBox(const char* label = "");
    void openDialogBox(const char *id_dialog, const char *id_switch);
    void opensDialogBox(const char *id_dialog, const char *id_switch);
    void openDialogBox(const char *id_dialog, const char *id_switch, const char *expose_funk, GtkWidget *box);
    void opensDialogBox(const char *id_dialog, const char *id_switch, const char *expose_funk, GtkWidget *box);
    void openPatchInfoBox(float* zone);
    void openWarningBox(const char* label, float* zone);
    void openEventBox(const char* label = "");
    void openMainBox(const char* label = "", const char *expose_funk= NULL);
    void openHandleBox(const char* label = "");
    void openExpanderBox(const char* label, float* zone);
    void openTabBox(const char* label = "");
    void openSpaceBox(const char* label = "");
    void openAmpBox(const char* label = "");
    void openSlooperBox(const char* label = "");
    void openPlugBox(const char* label = "");
    void openpaintampBox(const char* label = "");
    void openPaintBox(const char* label = "", const char* name = NULL);
    void openPaintBox1(const char* label = "");
    void openPaintBox2(const char* label = "");
    void openScrollBox(const char* label = "");
    void openLevelMeterBox(const char* label);
    void openToolBar(const char* label = "");
    void setSkinBox(const char* label, float* zone);
    void openStereoRackBox(const char* label, int* posit, const char *id_on_off, const char *id_dialog);
    void closeStereoRackBox();
    void openMonoRackBox(const char* label, int* posit, const char *id_on_off, const char *id_pre_post, const char *id_dialog);
    void closeMonoRackBox();
    void loadRackFromGladeData(const char *xmldesc);
    void closeBox();

    // -- active widgets
    void addJConvButton(const char* label, float* zone);
    void addJConvFavButton(const char* label);
    void addToggleButton(const char* label, float* zone);
    void addJToggleButton(const char* label, bool* zone);
    void addPToggleButton(const char* label);
    void addMToggleButton(const char* label, bool* zone);
    void addCheckButton(const char* label, bool* zone);
    void addNumEntry(const char* label, float* zone, float init, float min, float max, float step);
    void addNumDisplay();
    void addLiveWaveDisplay(const char* label);
    void addStatusDisplay(const char* label, bool* zone );
    // void addselector(const char* label, float* zone,int maxv, const char* []);
    void addSpinValueBox(string id, const char* label = 0);
    // void addselector(string id, const char* label=0, int nvalues=0, const char **pvalues=0);
    void addCheckButton(string id, const char* label = 0);
    void addNumEntry(string id, const char* label = 0);
    //void addPToggleButton(string id, const char* label = 0);
    void addMToggleButton(string id, const char* label = 0);

    void setup();
    void show();
    void run();

    // widget creation
    void addwidget(GtkWidget *widget) {
            if (widget) gtk_container_add(GTK_CONTAINER(fBox[fTop]), widget);
        }
    void create_bigknob(string id) {
            addwidget(UiReglerWithCaption::create(*this, new Gxw::BigKnob(), id, true));
        }
    void create_bigknob(string id, Glib::ustring label) {
            addwidget(UiReglerWithCaption::create(*this, new Gxw::BigKnob(), id, label, true));
        }
    void create_smallknob(string id) {
            addwidget(UiReglerWithCaption::create(*this, new Gxw::SmallKnob(), id, true));
        }
    void create_smallknob(string id, Glib::ustring label) {
            addwidget(UiReglerWithCaption::create(*this, new Gxw::SmallKnob(), id, label, true));
        }
    void create_smallknob_no_caption(string id) {
            addwidget(UiRegler::create(*this, new Gxw::SmallKnob(), id, true));
        }

    void create_small_rackknob(string id) {
            addwidget(UiRackReglerWithCaption::create(*this, new Gxw::SmallKnob(), id));
        }
    void create_small_rackknob(string id, Glib::ustring label) {
            addwidget(UiRackReglerWithCaption::create(*this, new Gxw::SmallKnob(), id, label));
        }

    void create_smallknob_no_value(string id) {
            addwidget(UiReglerWithCaption::create(*this, new Gxw::SmallKnob(), id, false));
        }
    void create_smallknob_no_value(string id, Glib::ustring label) {
            addwidget(UiReglerWithCaption::create(*this, new Gxw::SmallKnob(), id, label, false));
        }
    void create_smallknob_no_caption_no_value(string id) {
            addwidget(UiRegler::create(*this, new Gxw::SmallKnob(), id, false));
        }

    void create_smallknobr(string id) {
            addwidget(UiReglerWithCaption::create(*this, new Gxw::SmallKnobR(), id, true));
        }
    void create_smallknobr(string id, Glib::ustring label) {
            addwidget(UiReglerWithCaption::create(*this, new Gxw::SmallKnobR(), id, label, true));
        }

    void create_small_rackknobr(string id) {
            addwidget(UiRackReglerWithCaption::create(*this, new Gxw::SmallKnobR(), id));
        }
    void create_small_rackknobr(string id, Glib::ustring label) {
            addwidget(UiRackReglerWithCaption::create(*this, new Gxw::SmallKnobR(), id, label));
        }

    void create_smallknobr_no_caption(string id) {
            addwidget(UiRegler::create(*this, new Gxw::SmallKnobR(), id, true));
        }
    void create_wheel(string id, bool show_value = false) {
            addwidget(UiRegler::create(*this, new Gxw::Wheel(), id, show_value));
        }
    void create_wheel_with_value(string id, bool show_value = true) {
            addwidget(UiRegler::create(*this, new Gxw::Wheel(), id, show_value));
        }
    /* void create_wheel_vertical(string id, bool show_value = false) {
            addwidget(UiRegler::create(*this, new Gxw::WheelVertical(), id, show_value));
        }
    void create_wheel_vertical_with_value(string id, bool show_value = true) {
            addwidget(UiRegler::create(*this, new Gxw::WheelVertical(), id, show_value));
        } */
    void create_hslider(string id) {
            addwidget(UiReglerWithCaption::create(*this, new Gxw::HSlider(), id, true));
        }
    void create_hslider(string id, Glib::ustring(label)) {
            addwidget(UiReglerWithCaption::create(*this, new Gxw::HSlider(), id, label, true));
        }
    void create_minislider(string id) {
            addwidget(UiRegler::create(*this, new Gxw::MiniSlider(), id, false));
        }
    void create_minislider(string id, Glib::ustring(label)) {
            addwidget(UiReglerWithCaption::create(*this, new Gxw::MiniSlider(), id, label, true));
        }

    void create_eqslider_no_caption(string id, bool show_value = true) {
            addwidget(UiRegler::create(*this, new Gxw::EqSlider(), id, show_value));
        }
    void create_eqslider(string id, bool show_value = true) {
            addwidget(UiReglerWithCaption::create(*this, new Gxw::EqSlider(), id, show_value));
        }
    void create_eqslider(string id, Glib::ustring label, bool show_value = true) {
            addwidget(UiReglerWithCaption::create(*this, new Gxw::EqSlider(),
                      id, label, show_value));
        }
    void create_eqslider(string id, const char *label, bool show_value = true) {
            addwidget(UiReglerWithCaption::create(*this, new Gxw::EqSlider(),
                      id, label, show_value));
        }
        // levelslider
    void create_levelslider_no_caption(string id, bool show_value = true) {
            addwidget(UiRegler::create(*this, new Gxw::LevelSlider(), id, show_value));
        }
    void create_levelslider(string id, bool show_value = true) {
            addwidget(UiReglerWithCaption::create(*this, new Gxw::LevelSlider(),
                      id, show_value));
        }
    void create_levelslider(string id, Glib::ustring label, bool show_value = true) {
            addwidget(UiReglerWithCaption::create(*this, new Gxw::LevelSlider(),
                      id, label, show_value));
        }
    void create_levelslider(string id, const char *label, bool show_value = true) {
            addwidget(UiReglerWithCaption::create(*this, new Gxw::LevelSlider(),
                      id, label, show_value));
        }
        // rack
    void create_eq_rackslider_no_caption(string id) {
            addwidget(UiRackRegler::create(*this, new Gxw::EqSlider(), id));
        }
    void create_eq_rackslider(string id) {
            addwidget(UiRackReglerWithCaption::create(*this, new Gxw::EqSlider(), id));
        }
    void create_eq_rackslider(string id, Glib::ustring label) {
            addwidget(UiRackReglerWithCaption::create(*this, new Gxw::EqSlider(), id, label));
        }
    void create_eq_rackslider(string id, const char *label) {
            addwidget(UiRackReglerWithCaption::create(*this, new Gxw::EqSlider(), id, label));
        }

    void create_spin_value(string id) {
            addwidget(UiRegler::create(*this, new Gxw::ValueDisplay(), id, true));
        }
    void create_simple_spin_value(string id) {
            addwidget(UiRegler::create(*this, new Gxw::SimpleValueDisplay(), id, true));
        }
    void create_selector(string id, const char *widget_name=0);
    void create_switch_no_caption(const char *sw_type, string id) {
            addwidget(UiSwitch::create(*this, sw_type, id));
        }
    void create_switch(const char *sw_type, string id, Gtk::PositionType pos = Gtk::POS_TOP) {
            addwidget(UiSwitchWithCaption::create(*this, sw_type, id, pos));
        }
    void create_switch(const char *sw_type, string id, Glib::ustring label,
                       Gtk::PositionType pos = Gtk::POS_TOP) {
            addwidget(UiSwitchWithCaption::create(*this, sw_type, id, label, pos));
        }
    void create_ptoggle_button(const char *label) {
	addwidget((new PToggleButton(label))->get_widget());
    }
};

/****************************************************************/

struct uiAdjustment : public gx_ui::GxUiItemFloat {
    GtkAdjustment* fAdj;
    uiAdjustment(gx_ui::GxUI* ui, float* zone, GtkAdjustment* adj) :
                 gx_ui::GxUiItemFloat(ui, zone), fAdj(adj) {}
    static void changed(GtkAdjustment *adj, gpointer data) {
            float    v = adj->value;
            ((gx_ui::GxUiItemFloat*)data)->modifyZone(v);
        }

    virtual void reflectZone() {
            float     v = *fZone;
            fCache = v;
            gtk_adjustment_set_value(fAdj, v);
        }
};

/****************************************************************/

extern const char *sw_led;
extern const char *sw_switch;
extern const char *sw_switchit;
extern const char *sw_minitoggle;
extern const char *sw_button;
extern const char *sw_pbutton;
extern const char *sw_rbutton;


extern const char *pb_rectangle_skin_color_expose;

gboolean button_press_cb(GtkWidget *widget, GdkEventButton *event, gpointer data);

extern void set_label(MenuCheckItem& item , const char *label);

extern void set_label(RadioCheckItem& item , const char *label);

int gx_set_mx_oriantation();
int gx_set_my_oriantation();

int precision(double n);
string fformat(float value, float step);

/****************************************************************/

#ifndef NDEBUG
// debug_check
inline void check_zone(GtkWidget *w, void *zone) {
    if (!gx_engine::parameter_map.hasZone(zone)) {
        gchar *p;
        gtk_widget_path(w, NULL, &p, NULL);
        cerr << "zone not found in definition of widget: "
             << p << endl;
        g_free(p);
        assert(false);
    }
    gx_engine::parameter_map[zone].setUsed();
}
#endif

/****************************************************************/

inline void connect_midi_controller(GtkWidget *w, void *zone) {
    debug_check(check_zone, w, zone);
    g_signal_connect(w, "button_press_event", G_CALLBACK(button_press_cb),
                    (gpointer)&gx_engine::parameter_map[zone]);
}

/****************************************************************/

void conv_restart();

Glib::RefPtr<Gtk::Builder> load_builder_from_file(Glib::ustring name, gx_ui::GxUI& ui);
Glib::RefPtr<Gtk::Builder> load_builder_from_data(const char *xmldesc, gx_ui::GxUI& ui);

/* -------------------------------------------------------------------------- */
} /* end of gx_gui namespace */

#endif  // SRC_HEADERS_GX_MAIN_INTERFACE_H_


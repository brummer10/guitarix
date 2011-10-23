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

#ifndef SRC_HEADERS_GX_UI_H_
#include "./gx_ui.h"
#endif


#include <gxwmm/bigknob.h>
#include <gxwmm/smallknob.h>
#include <gxwmm/smallknobr.h>
#include <gxwmm/wheel.h>
// #include <gxwmm/wheelvertical.h>
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
    volatile gint       program_change;
    sem_t               program_change_sem;
    
    int                 main_xorg;
    int                 main_yorg;
    string              skin;

    void register_gui_parameter();
};

extern GuiVariables guivar;

/****************************************************************/

/* global GUI widgets */
class GlobalWidgets {
 public:
    /* global GUI widgets */
    GtkWidget*          menuh;
    GtkWidget*          midibox;
    GtkWidget*          patch_info;
    GtkWidget*          tuner_widget;
    GtkWidget*          rack_widget;
    GtkWidget*          srack_widget;
    GtkWidget*          menu_mono_rack;
    GtkWidget*          menu_stereo_rack;
    GtkWidget*          rack_tool_bar;
    GtkWidget*          set_label;

    /* icon widgets */
    GdkPixbuf*          ib;
    GdkPixbuf*          ibm;
    GdkPixbuf*          ibr;

    /* jack server status icons */
    GtkWidget*          gx_jackd_on_image;
    GtkWidget*          gx_jackd_off_image;

    /* engine status images */
    GtkWidget*          gx_engine_on_image;
    GtkWidget*          gx_engine_off_image;
    GtkWidget*          gx_engine_bypass_image;
    GtkWidget*          gx_engine_item;
    GtkStatusIcon*      status_icon;
};

extern GlobalWidgets gw;

/****************************************************************/

void gx_start_stop_jconv(GtkWidget*, gpointer);

/****************************************************************/

/* ---- linking menu items and parameter ---- */
class MenuCheckItem: public Gtk::CheckMenuItem {
 private:
    SwitchParameter* param;
    void on_my_activate();
 public:
    // FIXME not gtk-2.12: MenuCheckItem() { set_use_underline(); }
    MenuCheckItem(): Gtk::CheckMenuItem("", true) {}
    void set_parameter(SwitchParameter *p);
    void add_parameter(SwitchParameter *p);
    SwitchParameter * get_parameter();
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
    SwitchParameter* param;
    void on_my_toggled();
 public:
    //Gtk::RadioMenuItem::Group Group;
    // FIXME not gtk-2.12: MenuCheckItem() { set_use_underline(); }
    RadioCheckItem(Gtk::RadioMenuItem::Group& group):
	Gtk::RadioMenuItem(group, "", true) {}
    void set_parameter(SwitchParameter *p);
    SwitchParameter * get_parameter();
};

/****************************************************************/

class ToggleCheckButton: public Gtk::ToggleButton {
 private:
    SwitchParameter* param;
    void on_my_toggled();
 public:
    Gtk::Label m_label;
    void set_parameter(SwitchParameter *p);
    SwitchParameter * get_parameter();
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
    UiRegler(gx_ui::GxUI &ui, FloatParameter &param, Gxw::Regler *regler, bool show_value);
    virtual ~UiRegler();
    GtkWidget *get_widget() { return GTK_WIDGET(m_regler->gobj()); }
};

/****************************************************************/

class UiSelector {
 protected:
    Gxw::Selector m_selector;
    void init(Parameter& param);
 public:
    UiSelector();
    static GtkWidget* create(gx_ui::GxUI& ui, string id, const char *widget_name);
    GtkWidget *get_widget() { return GTK_WIDGET(m_selector.gobj()); }
};

/****************************************************************/

class UiSelectorFloat: public UiSelector, gx_ui::GxUiItemFloat, protected Gtk::Adjustment {
 protected:
    virtual void reflectZone();
    void on_value_changed();
 public:
    UiSelectorFloat(gx_ui::GxUI& ui, FloatParameter &param);
};

/****************************************************************/

class UiSelectorInt: public UiSelector, gx_ui::GxUiItemInt, protected Gtk::Adjustment {
 protected:
    virtual void reflectZone();
    void on_value_changed();
 public:
    UiSelectorInt(gx_ui::GxUI& ui, IntParameter &param);
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
    UiReglerWithCaption(gx_ui::GxUI &ui, FloatParameter &param, Gxw::Regler *regler,
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
    UiRackReglerWithCaption(gx_ui::GxUI &ui, FloatParameter &param, Gxw::Regler *regler,
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
    UiRackRegler(gx_ui::GxUI &ui, FloatParameter &param, Gxw::Regler *regler,
                 Glib::ustring label);
    GtkWidget *get_widget() { return GTK_WIDGET(m_box.gobj());}
};

/****************************************************************/

class UiSwitch: public Gxw::Switch {
 public:
    explicit UiSwitch(const char *sw_type);
    GtkWidget *get_widget() { return GTK_WIDGET(gobj());}
    static UiSwitch *new_switch(gx_ui::GxUI& ui, const char *sw_type, Parameter &param);
    static UiSwitch *new_switch(gx_ui::GxUI& ui, const char *sw_type, string id) {
        if (!parameter_map.hasId(id)) return 0;
        return new_switch(ui, sw_type, parameter_map[id]);
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
    UiSwitchFloat(gx_ui::GxUI& ui, const char *sw_type, FloatParameter &param);
};

/****************************************************************/

class UiSwitchBool: public UiSwitch, gx_ui::GxUiItemBool {
 protected:
    void on_toggled();
    virtual void reflectZone();
 public:
    UiSwitchBool(gx_ui::GxUI& ui, const char *sw_type, BoolParameter &param);
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
    UiSwitchWithCaption(gx_ui::GxUI &ui, const char *sw_type, Parameter &param,
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
    UiCabSwitch(gx_ui::GxUI &ui, Parameter &param, Glib::ustring label);
};

/****************************************************************/

class UiContrastSwitch: public UiSwitchWithCaption {
 private:
    void on_switch_toggled();
 public:
    static GtkWidget* create(gx_ui::GxUI& ui, string id, Glib::ustring label);
    UiContrastSwitch(gx_ui::GxUI &ui, Parameter &param, Glib::ustring label);
};

/****************************************************************/

struct uiTuner : public gx_ui::GxUiItemFloat, public Gtk::Alignment {
 private:
    Gxw::Tuner fTuner;
 public:
    void set_freq(double freq) { fTuner.set_freq(freq); }
    uiTuner(gx_ui::GxUI* ui, float* zone);
    virtual void reflectZone();
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
    void show_msg(string msgbuf, gx_system::GxMsgType msgtype);
public:
    TextLoggingBox(const char* label);
    ~TextLoggingBox();
};

#define NJACKLAT (9)

#define stackSize 256
#define kSingleMode 0
#define kBoxMode 1
#define kTabMode 2

class GxMainInterface : public sigc::trackable, public gx_ui::GxUI {
 private:
    static GxMainInterface *instance;
public://FIXME
    Gtk::Window           fWindow;
    gx_system::CmdlineOptions& options;
    // for key acclerators
    Glib::RefPtr<Gtk::AccelGroup> fAccelGroup;
    void portmap_connection_changed(string port1, string port2, bool conn);
private:
    gx_portmap::PortMapWindow* portmap_window;
    Gtk::CheckMenuItem    portmap_item;
    void                  on_portmap_activate();
    void                  on_portmap_response(int);

    static void           gx_systray_menu(GtkWidget*, gpointer);
    static void           gx_hide_extended_settings(GtkWidget*, gpointer);

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
    void                  jack_session_event();
    void                  gx_jack_is_down();
    void                  jack_connection_change();
    void                  save_window_position();

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

    // menu items
    map<string, GtkWidget*> fMenuList;
    MenuCheckItem         fMidiInPreset;
    MenuCheckItem         fShowTooltips;
    MenuCheckItem         fShowTuner;
    MenuCheckItem         fSetMouse;

    // jack menu widgets
    GtkWidget*            fJackConnectItem;
    GtkWidget*            fJackLatencyItem[NJACKLAT];

    GtkWidget*            addWidget(const char* label, GtkWidget* w);
    virtual void          pushBox(int mode, GtkWidget* w);

 public :
    gx_engine::GxEngine&  engine;
    gx_jack::GxJack       jack;
    gx_preset::GxSettings gx_settings;

    MenuCheckItem         fShowRack;
    MenuCheckItem         fShowRRack;
    MenuCheckItem         fShowSRack;
    MenuCheckItem         fShowLogger;
    MenuCheckItem         fShowMidiOut;
    MenuCheckItem         fShowToolBar;

    GtkWidget*            RBox;

    static bool           fInitialized;

    static const gboolean expand   = TRUE;
    static const gboolean fill     = TRUE;
    static const gboolean homogene = FALSE;

public:
    explicit GxMainInterface(gx_engine::GxEngine&, gx_system::CmdlineOptions& options);
    ~GxMainInterface();
    static GxMainInterface& get_instance() { assert(instance); return *instance; }

    GtkWidget*   const    getJackConnectItem()  const { return fJackConnectItem; }
    GtkWidget*   const    getJackLatencyItem(const jack_nframes_t bufsize) const;
    GtkWidget*   const    getMenu(const string name) { return fMenuList[name]; }
    
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
    void openSetLabelBox(const char* = "");
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
    void addCheckButton(const char* label, float* zone);
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

    void create_selector(string id, const char *widget_name=0) {
	addwidget(UiSelector::create(*this, id, widget_name));
        }
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
private:
    ReportXrun            report_xrun;
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
    if (!parameter_map.hasZone(zone)) {
        gchar *p;
        gtk_widget_path(w, NULL, &p, NULL);
        cerr << "zone not found in definition of widget: "
             << p << endl;
        g_free(p);
        assert(false);
    }
    parameter_map[zone].setUsed();
}
#endif

/****************************************************************/

inline void connect_midi_controller(GtkWidget *w, void *zone) {
    debug_check(check_zone, w, zone);
    g_signal_connect(w, "button_press_event", G_CALLBACK(button_press_cb),
                    (gpointer)&parameter_map[zone]);
}

/****************************************************************/

void conv_restart();

Glib::RefPtr<Gtk::Builder> load_builder_from_file(Glib::ustring name, gx_ui::GxUI& ui);
Glib::RefPtr<Gtk::Builder> load_builder_from_data(const char *xmldesc, gx_ui::GxUI& ui);

/* -------------------------------------------------------------------------- */
} /* end of gx_gui namespace */

#endif  // SRC_HEADERS_GX_MAIN_INTERFACE_H_


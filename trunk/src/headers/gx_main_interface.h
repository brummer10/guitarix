/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 * --------------------------------------------------------------------------
 */

/* ------- This is the GUI namespace ------- */
// Note: this header file depends on gx_engine.h

#pragma once

#include <iostream>
#include <gxwmm/bigknob.h>
#include <gxwmm/smallknob.h>
#include <gxwmm/wheel.h>
#include <gxwmm/hslider.h>
#include <gxwmm/eqslider.h>
#include <gxwmm/switch.h>
#include <gxwmm/selector.h>
#include <gxwmm/valuedisplay.h>
#include <gxwmm/fastmeter.h>
#include <gxwmm/tuner.h>
#include <gxwmm/waveview.h>
#include <gtkmm/box.h>
#include <gtkmm/alignment.h>

#ifndef NJACKLAT
#define NJACKLAT (9)
#endif

namespace gx_gui
{

/****************************************************************
 ** PortMapWindow
 */

enum {
	number_of_ports = 7
};

struct PortAttr {
	const int client_num;
	const bool is_insert;
	const char *port_name;
	bool is_input;
	const char *port_type;
};

extern PortAttr guitarix_ports[number_of_ports];

struct PortSection
{
	GtkTreeStore *treestore;
	GtkScrolledWindow *scrolled_window;
	GtkExpander *expander;
	GtkLabel *label;
	PortAttr *port_attr;
};

class PortMapWindow
{
private:
	PortSection portsection[number_of_ports];
	GtkCheckMenuItem *menuitem;
	list<string> excluded_clients;
	GtkWidget *monitored_expander_child;
	static void on_expander(GtkWidget *widget, gpointer data);
	static void on_check_resize(GtkWidget *widget, gpointer data);
	static void response_cb(GtkWidget *widget, gint response_id, gpointer data);
	static void destroy_cb(GtkWidget*, gpointer data);
	static void on_cell_toggle(GtkCellRendererToggle *widget, gchar *path, gpointer data);
	static void update_summary(PortSection* p, string *port=0, bool connect=false);
	static gboolean redraw_expander(gpointer data);
	static list<string> walk(GtkTreeStore *ts, string *port, int connect);
	bool walk_remove(GtkTreeStore *ts, bool (*compare)(const string&, const char*), string data);
	void walk_insert(GtkTreeStore *ts, string data);
	void load(int sect, jack_port_t*);
	void load_all();
	PortMapWindow(GtkCheckMenuItem *item);
	~PortMapWindow();
public:
	static GtkWidget *window; // there can only be 1 window
	static PortMapWindow* instance;
	void client_removed(string name);
	void refresh();
	void port_changed(string name, const char *tp, int flags, bool reg);
	void connection_changed(string port1, string port2, bool conn);
	static void toggle(GtkWidget* widget, gpointer data);
};

/****************************************************************
 **
 ** ---------------- the main GUI class ----------------
 **
 */

void gx_start_stop_jconv(GtkWidget*, gpointer);

class UiRegler: gx_ui::GxUiItem, protected Gtk::Adjustment
{
protected:
	Gxw::Regler *m_regler;
	virtual void on_value_changed();
	virtual void reflectZone();
public:
	static GtkWidget* create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id, bool show_value);
	UiRegler(gx_ui::GxUI &ui, FloatParameter &param, Gxw::Regler *regler, bool show_value);
	virtual ~UiRegler();
	GtkWidget *get_widget() { return GTK_WIDGET(m_regler->gobj()); }
};

class UiSelector: UiRegler
{
public:
	static GtkWidget* create(gx_ui::GxUI& ui, string id);
	UiSelector(gx_ui::GxUI& ui, FloatParameter &param, Gxw::Selector* sel);
};

class UiReglerWithCaption: UiRegler
{
private:
	Gtk::Label m_label;
	Gtk::VBox m_box;
public:
	static GtkWidget* create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id, bool show_value);
	static GtkWidget* create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id, Glib::ustring label, bool show_value);
	UiReglerWithCaption(gx_ui::GxUI &ui, FloatParameter &param, Gxw::Regler *regler, Glib::ustring label, bool show_value);
	GtkWidget *get_widget() { return GTK_WIDGET(m_box.gobj()); }
};

class UiSwitch: gx_ui::GxUiItem, public Gxw::Switch
{
private:
	float *get_vp(Parameter &param) { return param.isFloat() ? &param.getFloat().value : (float*)&param.getInt().value; /*FIXME*/}
protected:
	float fparam;
	virtual void on_toggled();
	virtual void reflectZone();
public:
	static GtkWidget* create(gx_ui::GxUI& ui, const char *sw_type, string id);
	UiSwitch(gx_ui::GxUI& ui, const char *sw_type, Parameter &param);
	GtkWidget *get_widget() { return GTK_WIDGET(gobj()); }
};

class UiSwitchWithCaption: UiSwitch
{
private:
	Gtk::Label m_label;
	Gtk::Box *m_box;
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

struct uiTuner : public gx_ui::GxUiItem, public Gtk::Alignment
{
private:
	Gxw::Tuner fTuner;
public:
	void set_freq(double freq) { fTuner.set_freq(freq); }
	uiTuner(gx_ui::GxUI* ui, float* zone);
	virtual void reflectZone();
};

class GxMainInterface : public gx_ui::GxUI
{
private:
	// private constructor
	GxMainInterface(const char* name);

	void addMainMenu();

	void addEngineMenu();
	void addJackServerMenu();

	void addPresetMenu();
	void addExtraPresetMenu();

	//void addPluginMenu();

	void addOptionMenu();
	void addGuiSkinMenu();

	void addAboutMenu();

	bool on_meter_button_release(GdkEventButton* ev);
	void on_tuner_activate();
	void on_show_oscilloscope();
	bool on_refresh_oscilloscope();

protected :
	int			fTop;
	GtkWidget*          fBox[stackSize];
	int 		fMode[stackSize];
	bool		fStopped;
	GtkTextView*        fLoggingWindow;
	GtkExpander*        fLoggingBox;
	GtkAdjustment*      fLoggingVAdjustment;
	Gxw::FastMeter      fLevelMeters[2];
	uiTuner             fTuner;
	Gxw::WaveView       fWaveView;

	GtkWidget*          fSignalLevelBar;

	// menu items
	map<string, GtkWidget*> fMenuList;
	MenuCheckItem       fMidiInPreset;
	MenuCheckItem       fShowTooltips;
	MenuCheckItem       fShowTuner;
	MenuCheckItem       fShowWaveView;
#ifdef EXPERIMENTAL
	MenuCheckItem       fShowExpWindow;
#endif

	// jack menu widgets
	GtkWidget*          fJackConnectItem;
	GtkWidget*          fJackLatencyItem[NJACKLAT];

	GtkWidget* addWidget(const char* label, GtkWidget* w);
	virtual void pushBox(int mode, GtkWidget* w);

public :
	static bool	 fInitialized;
	int          highest_unseen_msg_level;

	static const gboolean expand   = TRUE;
	static const gboolean fill     = TRUE;
	static const gboolean homogene = FALSE;

	static GxMainInterface* instance(const char* name = "");

	// for key acclerators
	GtkAccelGroup* fAccelGroup;

	// -- acquire a pointer to the logging window
	GtkTextView* const getLoggingWindow()    const { return fLoggingWindow;   }
	GtkExpander* const getLoggingBox()       const { return fLoggingBox;      }

	GtkWidget*   const getJackConnectItem()  const { return fJackConnectItem; }

	Gxw::FastMeter& getLevelMeter(unsigned int i)
		{ assert(i < sizeof(fLevelMeters)/sizeof(fLevelMeters[0])); return fLevelMeters[i]; }

	GtkWidget*   const getJackLatencyItem(const jack_nframes_t bufsize) const;

	GtkWidget*   const getMenu(const string name) const { return fMenuList.at(name); }

	// -- layout groups
	void openHorizontalOrderBox(const char* label,  float* posit);
	void openHorizontalTableBox(const char* label);
	void openHorizontalRestetBox(const char* label,  float* posit);
	void openFrameBox(const char* label);
	void openHorizontalBox(const char* label = "");
	void openHorizontalhideBox(const char* label = "");
	void openVerticalBox(const char* label = "");
	void openVerticalBox1(const char* label = "");
	void openFlipLabelBox(const char* = "");
	void openVerticalSwitchBox(const char* label, int state, int wit, float* zone);
	void openVerticalMidiBox(const char* label = "");
	void openDialogBox(const char *id_dialog, const char *id_switch);
	void openPatchInfoBox(float* zone);
	void openWarningBox(const char* label, float* zone);
	void openEventBox(const char* label = "");
	void openHandleBox(const char* label = "");
	void openExpanderBox(const char* label, float* zone);
	void openTabBox(const char* label = "");
	void openSpaceBox(const char* label = "");
	void openAmpBox(const char* label = "");
	void openSlooperBox(const char* label = "");
	void openPlugBox(const char* label = "");
	void openpaintampBox(const char* label = "");
	void openPaintBox(const char* label = "");
	void openPaintBox1(const char* label = "");
	void openPaintBox2(const char* label = "");
	void openScrollBox(const char* label = "");
	void openTextLoggingBox(const char* label = "");
	void openLevelMeterBox(const char* label);
	void openToolBar(const char* label = "");
	void setSkinBox(const char* label, float* zone);
	void closeBox();

	// -- active widgets
	void addJConvButton(const char* label, float* zone);
	void addToggleButton(const char* label, float* zone);
	void addJToggleButton(const char* label, float* zone);
	void addPToggleButton(const char* label, float* zone);
	void addCheckButton(const char* label, float* zone);
	void addNumEntry(const char* label, float* zone, float init, float min, float max, float step);
	void addNumDisplay();
	void addLiveWaveDisplay(const char* label, float* zone , float* zone1);
	void addStatusDisplay(const char* label, float* zone );
	//void addselector(const char* label, float* zone,int maxv, const char* []);
	void addSpinValueBox(string id, const char* label=0);
	//void addselector(string id, const char* label=0, int nvalues=0, const char **pvalues=0);
	void addCheckButton(string id, const char* label=0);
	void addNumEntry(string id, const char* label=0);
	void addPToggleButton(string id, const char* label=0);

	// -- other
	void show_msg(string msgbuf, gx_system::GxMsgType msgtype);
	void set_logging_expander_color(const char *color);

	void setup();
	void show();
	void run();

	// widget creation
	void addwidget(GtkWidget *widget) { gtk_container_add(GTK_CONTAINER(fBox[fTop]), widget); }
	void create_bigknob(string id)
		{
			addwidget(UiReglerWithCaption::create(*this, new Gxw::BigKnob(), id, true));
		}
	void create_bigknob(string id, Glib::ustring label)
		{
			addwidget(UiReglerWithCaption::create(*this, new Gxw::BigKnob(), id, label, true));
		}
	void create_smallknob(string id)
		{
			addwidget(UiReglerWithCaption::create(*this, new Gxw::SmallKnob(), id, true));
		}
	void create_smallknob(string id, Glib::ustring label)
		{
			addwidget(UiReglerWithCaption::create(*this, new Gxw::SmallKnob(), id, label, true));
		}
	void create_smallknob_no_caption(string id)
		{
			addwidget(UiRegler::create(*this, new Gxw::SmallKnob(), id, true));
		}
	void create_wheel(string id, bool show_value = false)
		{
			addwidget(UiRegler::create(*this, new Gxw::Wheel(), id, show_value));
		}
	void create_hslider(string id)
		{
			addwidget(UiReglerWithCaption::create(*this, new Gxw::HSlider(), id, true));
		}
	void create_hslider(string id, Glib::ustring(label))
		{
			addwidget(UiReglerWithCaption::create(*this, new Gxw::HSlider(), id, label, true));
		}
	void create_eqslider_no_caption(string id, bool show_value = true)
		{
			addwidget(UiRegler::create(*this, new Gxw::EqSlider(), id, show_value));
		}
	void create_eqslider(string id, bool show_value = true)
		{
			addwidget(UiReglerWithCaption::create(*this, new Gxw::EqSlider(), id, show_value));
		}
	void create_eqslider(string id, Glib::ustring label, bool show_value = true)
		{
			addwidget(UiReglerWithCaption::create(*this, new Gxw::EqSlider(), id, label, show_value));
		}
	void create_eqslider(string id, const char *label, bool show_value = true)
		{
			addwidget(UiReglerWithCaption::create(*this, new Gxw::EqSlider(), id, label, show_value));
		}
	void create_spin_value(string id)
		{
			addwidget(UiRegler::create(*this, new Gxw::ValueDisplay(), id, true));
		}
	void create_selector(string id)
		{
			addwidget(UiSelector::create(*this, id));
		}
	void create_switch_no_caption(const char *sw_type, string id)
		{
			addwidget(UiSwitch::create(*this, sw_type, id));
		}
	void create_switch(const char *sw_type, string id, Gtk::PositionType pos = Gtk::POS_TOP)
		{
			addwidget(UiSwitchWithCaption::create(*this, sw_type, id, pos));
		}
	void create_switch(const char *sw_type, string id, Glib::ustring label, Gtk::PositionType pos = Gtk::POS_TOP)
		{
			addwidget(UiSwitchWithCaption::create(*this, sw_type, id, label, pos));
		}
};

extern const char *sw_led;
extern const char *sw_switch;
extern const char *sw_switchit;
extern const char *sw_minitoggle;
extern const char *sw_button;
extern const char *sw_pbutton;
extern const char *sw_rbutton;

gboolean button_press_cb (GtkWidget *widget, GdkEventButton *event, gpointer data);

#ifndef NDEBUG
// debug_check
inline void check_zone(GtkWidget *w, void *zone)
{
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

inline void connect_midi_controller(GtkWidget *w, void *zone)
{
	debug_check(check_zone, w, zone);
	g_signal_connect(w, "button_press_event", G_CALLBACK (button_press_cb), (gpointer)&parameter_map[zone]);
}

/* -------------------------------------------------------------------------- */
} /* end of gx_gui namespace */


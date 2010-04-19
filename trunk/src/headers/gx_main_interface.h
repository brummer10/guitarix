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

#ifndef NJACKLAT
#define NJACKLAT (9)
#endif

namespace gx_gui
{

/****************************************************************
 ** PortMapWindow
 */

enum {
	number_of_ports = 5
};

struct PortAttr {
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

class GxMainInterface : public gx_ui::GxUI
{
private:
	// private constructor
	GxMainInterface(const char* name, int* pargc, char*** pargv);

	void addMainMenu();

	void addEngineMenu();
	void addJackServerMenu();

	void addPresetMenu();
	void addExtraPresetMenu();

	void addOptionMenu();
	void addGuiSkinMenu();

	void addAboutMenu();

protected :
	int			fTop;
	GtkWidget*          fBox[stackSize];
	int 		fMode[stackSize];
	bool		fStopped;
	GtkTextView*        fLoggingWindow;
	GtkExpander*        fLoggingBox;
	GtkAdjustment*      fLoggingVAdjustment;
	GtkWidget*          fLevelMeters[2];

	GtkWidget*          fSignalLevelBar;

	// menu items
	map<string, GtkWidget*> fMenuList;
	MenuCheckItem       fMidiInPreset;
	MenuCheckItem       fShowTooltips;

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

	static GxMainInterface* instance(const char* name = "",
	                                 int* pargc = NULL, char*** pargv = NULL);

	// for key acclerators
	GtkAccelGroup* fAccelGroup;

	// -- acquire a pointer to the logging window
	GtkTextView* const getLoggingWindow()    const { return fLoggingWindow;   }
	GtkExpander* const getLoggingBox()       const { return fLoggingBox;      }

	GtkWidget*   const getJackConnectItem()  const { return fJackConnectItem; }

	GtkWidget*   const* getLevelMeters()     const { return fLevelMeters;     }

	GtkWidget*   const getJackLatencyItem(const jack_nframes_t bufsize) const;

	GtkWidget*   const getMenu(const string name) const { return fMenuList.at(name); }

	// -- layout groups
	virtual void openHorizontalOrderBox(const char* label,  float* posit);
	virtual void openHorizontalTableBox(const char* label);
	virtual void openHorizontalRestetBox(const char* label,  float* posit);
	virtual void openFrameBox(const char* label);
	virtual void openHorizontalBox(const char* label = "");
	virtual void openHorizontalhideBox(const char* label = "");
	virtual void openVerticalBox(const char* label = "");
	virtual void openVerticalBox1(const char* label = "");
	virtual void openVerticalMidiBox(const char* label = "");
	virtual void openDialogBox(const char* label, float* zone);
	virtual void openWarningBox(const char* label, float* zone);
	virtual void openEventBox(const char* label = "");
	virtual void openHandleBox(const char* label = "");
	virtual void openExpanderBox(const char* label, float* zone);
	virtual void openTabBox(const char* label = "");
	virtual void openPaintBox(const char* label = "");
	virtual void openPaintBox1(const char* label = "");
	virtual void openPaintBox2(const char* label = "");
	virtual void openScrollBox(const char* label = "");
	virtual void openTextLoggingBox(const char* label = "");
	virtual void openLevelMeterBox(const char* label);
	virtual void openToolBar(const char* label = "");
	virtual void setSkinBox(const char* label, float* zone);
	virtual void closeBox();

	// -- active widgets
	virtual void addJConvButton(const char* label, float* zone);
	virtual void addToggleButton(const char* label, float* zone);
	virtual void addPToggleButton(const char* label, float* zone);
	virtual void addJToggleButton(const char* label, float* zone);
	virtual void addCheckButton(const char* label, float* zone);
	virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step);
	virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step);
	virtual void addHorizontalWheel(const char* label, float* zone, float init, float min, float max, float step);
	virtual void addregler(const char* label, float* zone, float init, float min, float max, float step);
	virtual void addbigregler(const char* label, float* zone, float init, float min, float max, float step);
	virtual void addslider(const char* label, float* zone, float init, float min, float max, float step);
	virtual void addtoggle(const char* label, int* zone);
	virtual void addtoggle(const char* label, float* zone);
	virtual void addbtoggle(const char* label, int* zone);
	virtual void addbtoggle(const char* label, float* zone);
	virtual void addswitch(const char* label, int* zone);
	virtual void addminiswitch(const char* label, int* zone);
	virtual void addminiswitch(const char* label, float* zone);
	virtual void addminieqswitch(const char* label, int* zone);
	virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step);
	virtual void addNumDisplay(const char* label, float* zone);
	virtual void addLiveWaveDisplay(const char* label, float* zone , float* zone1);
	virtual void addStatusDisplay(const char* label, float* zone );
	virtual void addselector(const char* label, float* zone,int maxv, const char* []);
	void addbigregler(string id, const char* label=0);
	void addHorizontalWheel(string id, const char* label=0);
	void addslider(string id, const char* label=0);
	void addregler(string id, const char* label=0);
	void addswitch(string id, const char* label=0);
	void addminiswitch(string id, const char* label=0);
	void addselector(string id, int, const char**, const char* label=0);
	void addtoggle(string id, const char* label=0);
	void addbtoggle(string id, const char* label=0);
	void addminieqswitch(string id, const char* label=0);
	void addVerticalSlider(string id, const char* label=0);
	void addCheckButton(string id, const char* label=0);
	void addNumEntry(string id, const char* label=0);
	void addPToggleButton(string id, const char* label=0);

	// -- other
	void show_msg(string msgbuf, gx_system::GxMsgType msgtype);
	void set_logging_expander_color(const char *color);

	virtual void setup();
	virtual void show();
	virtual void run();
};

/* -------------------------------------------------------------------------- */
} /* end of gx_gui namespace */


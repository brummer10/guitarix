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

#include <cassert>
#include <sigc++/sigc++.h>

#pragma once

#ifndef NJACKLAT
#define NJACKLAT (9)
#endif

#ifndef NUM_PORT_LISTS
#define NUM_PORT_LISTS (4)
#endif

namespace gx_gui
{

/****************************************************************
 **
 ** ---------------- the main GUI class ----------------
 **
 */

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
	GtkNotebook*        fPortMapTabs;
	GtkWindow*          fPortMapWindow;
	GtkWidget*          fLevelMeters[2];

	GtkWidget*          fSignalLevelBar;
	GtkCheckMenuItem*   fMeterBridge;

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

	// list of client portmaps
	set<GtkWidget*> fClientPortMap;

	// -- acquire a pointer to the logging window
	GtkTextView* const getLoggingWindow()    const { return fLoggingWindow;   }
	GtkExpander* const getLoggingBox()       const { return fLoggingBox;      }

	GtkNotebook* const getPortMapTabs()      const { return fPortMapTabs;     }
	GtkWindow*   const getPortMapWindow()    const { return fPortMapWindow;   }

	GtkWidget*   const getJackConnectItem()  const { return fJackConnectItem; }

	GtkWidget*   const* getLevelMeters()     const { return fLevelMeters;     }

	GtkWidget*   const getJackLatencyItem(const jack_nframes_t bufsize) const;

	GtkWidget*   const getMenu(const string name) const { return fMenuList.at(name); }
	void meterbridge_terminated() { gtk_check_menu_item_set_active(fMeterBridge, FALSE); }

	// -- update jack client port lists
	enum { JACK_AUDIO_IN, JACK_AUDIO_OUT, JACK_MIDI_IN };

	void initClientPortMaps      ();

	void addClientPorts          ();
	void addClientPortMap        (const string);

	void deleteClientPorts       ();
	void deleteClientPortMap     (const string);

	void deleteAllClientPortMaps ();

	GtkWidget* getClientPort       (const string, const int);
	GtkWidget* getClientPortTable  (const string, const int);
	GtkWidget* getClientPortMap    (const string);

	// -- create jack portmap window
	void createPortMapWindow(const char* label = "");

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


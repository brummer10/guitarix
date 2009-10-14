/*
 * Copyright (C) 2009 Hermann Meyer and James Warden
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

#pragma once

#ifndef NJACKLAT
#define NJACKLAT (9)
#endif

#ifndef NUM_PORT_LISTS
#define NUM_PORT_LISTS (3)
#endif

namespace gx_gui
{
  /* function declarations */
  gboolean gx_refresh_signal_level(gpointer arg);
  gboolean gx_refresh_jcsignal_level(gpointer arg);
  gboolean gx_survive_jack_shutdown(gpointer arg);
  gboolean gx_monitor_jack_clients(gpointer args);
  gboolean gx_monitor_port_connection(gpointer args);

  unsigned int gx_fetch_available_skins();

  void gx_change_skin(GtkCheckMenuItem *menuitem, gpointer arg);
  void gx_cycle_through_skin(GtkWidget *widget, gpointer arg);
  bool gx_update_skin(const gint idx, const char* calling_func);
  void gx_actualize_skin_index(const string& skin_name);
  bool gx_set_skin(GtkWidget *widget, gpointer data);
  void gx_get_skin_change(float * fskin);
  void gx_set_skin_change(float fskin);
  void gx_refresh_engine_status_display();
  void gx_engine_switch (GtkWidget* widget, gpointer arg);

  /* choice dialog windows */
  void gx_get_text_entry(GtkEntry*, string&);

  gint gx_choice_dialog_with_text_entry (
	const char* window_title,
	const char* msg,
	const char* label1,
	const char* label2,
	const gint  resp1,
	const gint  resp2,
	const gint  default_response,
	GCallback   func
  );

  gint gx_choice_dialog_without_entry (
	const char* window_title,
	const char* msg,
	const char* label1,
	const char* label2,
	const gint  resp1,
	const gint  resp2,
	const gint  default_response
  );

  gint gx_nchoice_dialog_without_entry (
	const char* window_title,
	const char* msg,
	const guint nchoice,
	const char* label[],
	const gint  resp[],
	const gint  default_response
  );

  void gx_show_oscilloscope (GtkCheckMenuItem*, gpointer);
  void gx_tuner (GtkCheckMenuItem*, gpointer);
  void gx_midi_out (GtkCheckMenuItem*, gpointer);
  void gx_log_window (GtkWidget*, gpointer);
  gboolean callUpdateAllGuis(gpointer);

  void gx_show_extended_settings(GtkWidget*, gpointer);
  void gx_hide_extended_settings(GtkWidget*, gpointer);
  void gx_wait_latency_warn();
  int  gx_message_popup(const char*);


  /* ---------------- the main GUI class ---------------- */
  // Note: this header file depends on gx_engine.h

  class GxMainInterface : public gx_ui::GxUI
  {
  private:
    // private constructor
    GxMainInterface(const char* name, int* pargc, char*** pargv);

    void addMainMenu();

    void addEngineMenu();
    void addJackServerMenu();
    void addJackPortMenu();

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
    GtkWidget*          fSignalLevelBar;
    GtkWidget*          fJCSignalLevelBar;

    // menu items
    map<string, GtkWidget*> fMenuList;

    // jack menu widgets
    GtkWidget*          fJackConnectItem;
    GtkWidget*          fJackLatencyItem[NJACKLAT];

    GtkWidget* addWidget(const char* label, GtkWidget* w);
    virtual void pushBox(int mode, GtkWidget* w);

  public :
    static bool	 fInitialized;

    static const gboolean expand = TRUE;
    static const gboolean fill = TRUE;
    static const gboolean homogene = FALSE;

    static GxMainInterface* instance(const char* name = "",
				     int* pargc = NULL, char*** pargv = NULL);

    GtkAccelGroup* fAccelGroup;

    // portmap: pairs of port_name / menuitem widget
    typedef map<const string, GtkWidget*> GxJackPortList;

    // client portmaps: pairs of client name / pointer to portmap 
    map<const string, GxJackPortList*> fJackClientMenu;


    // -- acquire a pointer to the logging window
    GtkTextView* const getLoggingWindow()    const { return fLoggingWindow;   }
    GtkExpander* const getLoggingBox()       const { return fLoggingBox;      }
    GtkWidget*   const getSignalLevelBar()   const { return fSignalLevelBar;  }
    GtkWidget*   const getJCSignalLevelBar() const { return fJCSignalLevelBar;}
    GtkWidget*   const getJackConnectItem()  const { return fJackConnectItem; }

    GtkWidget*   const getJackLatencyItem(const jack_nframes_t bufsize) const;

    // -- update jack client port lists
    void addJackPortItem   (const string, const string, const int);
    void deleteJackPortItem(const string);

    void initJackClientMenus ();
    void addJackClientMenu   (const string, const string);
    void deleteJackClientMenu(const string);
    void deleteAllJackClientMenus();

    GtkWidget* getJackPortItem(const string, const int);

    // -- layout groups
    virtual void openFrameBox(const char* label);
    virtual void openHorizontalBox(const char* label = "");
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
    virtual void openPaintBox2(const char* label = "");
    virtual void openScrollBox(const char* label = "");
    virtual void openTextLoggingBox(const char* label = "");
    virtual void openSignalLevelBox(const char* label = "");
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
    virtual void addtoggle(const char* label, float* zone);
    virtual void addbtoggle(const char* label, float* zone);
    virtual void addswitch(const char* label, float* zone);
    virtual void addminiswitch(const char* label, float* zone);
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step);
    virtual void addNumDisplay(const char* label, float* zone);
    virtual void addLiveWaveDisplay(const char* label, float* zone , float* zone1);
    virtual void addStatusDisplay(const char* label, float* zone );
    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max);
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max);

    virtual void setup();
    virtual void show();
    virtual void run();
  };

  /* -------------------------------------------------------------------------- */
} /* end of gx_gui namespace */


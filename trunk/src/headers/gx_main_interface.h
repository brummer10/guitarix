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

#include <cassert>

#pragma once

#ifndef NJACKLAT
#define NJACKLAT (9)
#endif

#ifndef NUM_PORT_LISTS
#define NUM_PORT_LISTS (3)
#endif

namespace gx_gui
{

class ParameterGroups
{
private:
     map<string,string> groups;
public:
     string operator[](string id) { return groups[id]; }
     void insert(string id, string group)
     {
	  groups.insert(pair<string,string>(id, group));
     }
};

class ParameterNames
{
private:
     map<string,string> names;
public:
     string operator[](string id) { return names[id]; }
     void insert(string id, string name)
     {
	  names.insert(pair<string,string>(id, name));
     }
};

class BaseParameter
{
public:
     enum paramtype { Continuous, floatSwitch, boolSwitch, intEnum };
     string id;
     paramtype p_type;
     union {
	  struct {
	       float *value;
	       float std_value;
	       float lower;
	       float upper;
	       float step;
	  } f;
	  struct {
	       bool *value;
	       bool std_value;
	  } b;
	  struct {
	       int *value;
	       int std_value;
	  } i;
     };

     virtual string group() const;
     virtual string name() const;

     BaseParameter(string i, float *pv, float sv, float l, float u, float s):
	  id(i),
	  p_type(Continuous),
	  f{pv,sv,l,u,s}
     {}

     BaseParameter(string i, float *pv):
	  id(i),
	  p_type(floatSwitch),
	  f{pv,0}
     {}

     BaseParameter(string i, bool *pv, bool sv):
	  id(i),
	  p_type(boolSwitch),
	  b{pv,sv}
     {}

     BaseParameter(string idp, int *pv, int sv):
	  id(idp),
	  p_type(intEnum),
	  i{pv,sv}
     {}

};

class Parameter: public BaseParameter
{
 public:
     string _group;
     string _name;

     virtual string group() const;
     virtual string name() const;

     Parameter(string i, float *pv, float sv, float l, float u, float s):
	  BaseParameter(i, pv, sv, l, u, s)
     {
	  init();
     }
     Parameter(string i, float *pv):
	  BaseParameter(i, pv)
     {
	  init();
     }
     Parameter(string i, bool *pv, bool sv):
	  BaseParameter(i, pv, sv)
     {
	  init();
     }
     Parameter(string idp, int *pv, int sv):
	  BaseParameter(idp, pv, sv)
     {
	  init();
     }
private:
     string group_id() { return id.substr(0, id.find_last_of(".")); }
     void init();
};

class ParamMap
{
private:
     map<string, const BaseParameter*> id_map;
     map<const void*, const BaseParameter*> addr_map;

public:
     const BaseParameter* operator[](const void *p) { return addr_map[p]; }
     const BaseParameter* operator[](string id) { return id_map[id]; }
     void insert(const BaseParameter* param);
};

extern ParamMap parameter_map;

void initParameter(gx_engine::GxEngine* engine);


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
    GtkNotebook*        fPortMapTabs;
    GtkWindow*          fPortMapWindow;
    GtkWidget*          fLevelMeters[2];
    GtkWidget*          fJCLevelMeters[2];

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
    GtkWidget*   const* getJCLevelMeters()   const { return fJCLevelMeters;   }

    GtkWidget*   const getJackLatencyItem(const jack_nframes_t bufsize) const;

    GtkWidget*   const getMenu(const string name) const { return fMenuList.at(name); }

    // -- update jack client port lists
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
    virtual void addbtoggle(const char* label, float* zone);
    virtual void addswitch(const char* label, int* zone);
    virtual void addminiswitch(const char* label, int* zone);
    virtual void addminieqswitch(const char* label, int* zone);
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step);
    virtual void addNumDisplay(const char* label, float* zone);
    virtual void addLiveWaveDisplay(const char* label, float* zone , float* zone1);
    virtual void addStatusDisplay(const char* label, float* zone );
    virtual void addselector(const char* label, float* zone,int maxv, const char* []);

    virtual void setup();
    virtual void show();
    virtual void run();
  };

  /* -------------------------------------------------------------------------- */
} /* end of gx_gui namespace */


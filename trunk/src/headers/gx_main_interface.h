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

#pragma once

#ifndef NJACKLAT
#define NJACKLAT (9)
#endif

#ifndef NUM_PORT_LISTS
#define NUM_PORT_LISTS (3)
#endif

namespace gx_gui
{

#ifndef NDEBUG
#define debug_check(func, ...) func(__VA_ARGS__)
#else
#define debug_check(...)
#endif

/****************************************************************
 **
 **   Parameter
 **
 */

string param_group(string id);

/****************************************************************
 ** Parameter
 */

class FloatParameter;
class IntParameter;
class BoolParameter;

void initGroups();

class Parameter
{
public:
	enum ctrl_type { None, Continuous, Switch, Enum };
protected:
	enum value_type { tp_float, tp_int, tp_bool };
	string _id;
	string _name, _group;
	enum value_type v_type : 2;
	enum ctrl_type c_type : 3;
	bool save_in_preset : 1;
	bool controllable : 1;
#ifndef NDEBUG
	bool used : 1;
public:
	bool isUsed() const { return used; }
	void setUsed() { assert(controllable); used = true; }
#endif

public:
	Parameter(string id, string name, value_type vtp, ctrl_type ctp, bool preset, bool ctrl):
		_id(id), _name(name), _group(param_group(id)), v_type(vtp),
		c_type(ctp), save_in_preset(preset), controllable(ctrl), used(false)
		{}
	bool isFloat() const { return v_type == tp_float; }
	bool isInt() const { return v_type == tp_int; }
	bool isBool() const { return v_type == tp_bool; }
	ctrl_type getControlType() const { return c_type; }
	bool isControllable() const { return controllable; }
	bool isInPreset() const { return save_in_preset; }
	string id() const { return _id; }
	string group() const { return _group; }
	string name() const { return _name; }
	bool operator==(const Parameter& p) const { return &p == this; }
	virtual void *zone() const = 0;
	virtual void set(int n, int high, float llimit, float ulimit) = 0;
	virtual void writeJSON(gx_system::JsonWriter& jw) = 0;
	virtual void readJSON_value(gx_system::JsonParser& jp) = 0;
	const FloatParameter &getFloat() const;
	const IntParameter &getInt() const;
	const BoolParameter &getBool() const;
};

class FloatParameter: public Parameter
{
public:
	float &value;
	float std_value;
	float lower, upper, step;
	virtual void *zone() const;
	virtual void set(int n, int high, float llimit, float ulimit);
	virtual void writeJSON(gx_system::JsonWriter& jw);
	virtual void readJSON_value(gx_system::JsonParser& jp);
	FloatParameter(string id, string name, ctrl_type ctp, bool preset,
	               float &v, float sv, float lv, float uv, float tv, bool ctrl):
		Parameter(id, name, tp_float, ctp, preset, ctrl),
		value(v), std_value(sv), lower(lv), upper(uv), step(tv)
		{}
};

class IntParameter: public Parameter
{
public:
	int &value;
	int std_value;
	int lower, upper;
	virtual void *zone() const;
	virtual void set(int n, int high, float llimit, float ulimit);
	virtual void writeJSON(gx_system::JsonWriter& jw);
	virtual void readJSON_value(gx_system::JsonParser& jp);
	IntParameter(string id, string name, ctrl_type ctp, bool preset,
	             int &v, int sv, int lv, int uv, bool ctrl):
		Parameter(id, name, tp_int, ctp, preset, ctrl),
		value(v), std_value(sv), lower(lv), upper(uv)
		{}
};

class BoolParameter: public Parameter
{
public:
	bool &value;
	bool std_value;
	virtual void *zone() const;
	virtual void set(int n, int high, float llimit, float ulimit);
	virtual void writeJSON(gx_system::JsonWriter& jw);
	virtual void readJSON_value(gx_system::JsonParser& jp);
	BoolParameter(string id, string name, ctrl_type ctp, bool preset,
	              bool &v, bool sv, bool ctrl):
		Parameter(id, name, tp_float, ctp, preset, ctrl),
		value(v), std_value(sv)
		{}
};

inline const FloatParameter &Parameter::getFloat() const
{
	assert(isFloat());
	return static_cast<const FloatParameter&>(*this);
}

inline const IntParameter &Parameter::getInt() const
{
	assert(isInt());
	return static_cast<const IntParameter&>(*this);
}

inline const BoolParameter &Parameter::getBool() const
{
	assert(isBool());
	return static_cast<const BoolParameter&>(*this);
}


/****************************************************************
 ** ParamMap
 */

class ParamMap
{
private:
	map<string, Parameter*> id_map;
	map<const void*, Parameter*> addr_map;

#ifndef NDEBUG
	void unique_zone(Parameter* param);
	void unique_id(Parameter* param);
#endif

public:
	typedef map<string, Parameter*>::iterator iterator;
	iterator begin() { return id_map.begin(); }
	iterator end() { return id_map.end(); }
	Parameter* operator[](const void *p) { return addr_map.find(p)->second; }
	Parameter* operator[](string id) { return id_map.find(id)->second; }
	Parameter* operator[](const char *p) { return id_map.find(p)->second; }
	void insert(Parameter* param);
};

extern ParamMap parameter_map; // map id -> parameter, zone -> parameter

void initParams(gx_engine::GxEngine* engine);


/****************************************************************
 **
 ** Midi
 **
 */


/*
** MidiStandardControllers
*/

class MidiStandardControllers
{
private:
	map<int,const char*> m;
public:
	MidiStandardControllers();
	const char* operator[](int ctr) { return m[ctr]; }
};

extern MidiStandardControllers midi_std_ctr; // map ctrl num -> standard name


/*
** MidiController
*/

class MidiController
{
private:
	Parameter &param;
	float _lower, _upper;
public:
	MidiController(Parameter &p, float l, float u):
		param(p), _lower(l), _upper(u)
		{}
	float lower() const { return _lower; }
	float upper() const { return _upper; }
	void operator=(MidiController m) { param = m.param; _lower = m._lower; _upper = m._upper; }
	bool hasParameter(const Parameter& p) const { return param == p; }
	static MidiController* readJSON(gx_system::JsonParser&);
	void set(int n) { param.set(n, 127, _lower, _upper); }
	void writeJSON(gx_system::JsonWriter& jw) const;
};

typedef std::list<MidiController> midi_controller_list;


/*
** MidiControllerList
*/

class MidiControllerList
{
private:
	typedef std::array<midi_controller_list,128> controller_array;
	controller_array map;
	bool midi_config_mode;
	int last_midi_control;
	int last_midi_control_value;
public:
	MidiControllerList();
	MidiControllerList(gx_system::JsonParser&);
	midi_controller_list operator[](int n) { return map[n]; }
	void set_config_mode(bool mode, int ctl=-1);
	bool get_config_mode() { return midi_config_mode; }
	int get_current_control() { return last_midi_control; }
	void set_current_control(int ctl) { last_midi_control = ctl; }
	void set(int ctr, int val);
	void deleteParameter(Parameter& param);
	void modifyCurrent(Parameter& param, float lower, float upper);
	int param2controller(Parameter& param, const MidiController** p);
	void load_defaults();
	void writeJSON(gx_system::JsonWriter& jw);
	void MidiDef(int ctr, const char* p, float l=0, float u=0);
};

void recall_midi_controller_map();
bool save_midi_controller_map();

extern MidiControllerList controller_map; // map ctrl num -> controlled parameters


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
	void addbigregler(string id);
	void addHorizontalWheel(string id);
};

/* -------------------------------------------------------------------------- */
} /* end of gx_gui namespace */


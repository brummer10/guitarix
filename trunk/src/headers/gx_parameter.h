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

#pragma once

#include <giomm/file.h>

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

string param_group(string id, bool nowarn=false);

/****************************************************************
 ** Parameter
 */

class FloatParameter;
class FloatEnumParameter;
class IntParameter;
class EnumParameter;
class BoolParameter;
class SwitchParameter;
class FileParameter;

class Parameter
{
public:
	enum ctrl_type { None, Continuous, Switch, Enum };

protected:
	enum value_type { tp_float, tp_int, tp_bool, tp_switch, tp_file };
	string _id;
	string _name, _group;
	enum value_type v_type : 3;
	enum ctrl_type c_type : 3;
	bool save_in_preset : 1;
	bool controllable : 1;
	bool used : 1; // debug
	bool experimental : 1; // experimental faust code, suppress warnings

public:
	Parameter(string id, string name, value_type vtp, ctrl_type ctp, bool preset, bool ctrl, bool exp=false):
		_id(id),
		_name(name),
		_group(param_group(id, exp)),
		v_type(vtp),
		c_type(ctp),
		save_in_preset(preset),
		controllable(ctrl),
		used(false),
		experimental(exp)
		{}

#ifndef NDEBUG
	bool isUsed() const { return used; }
	void setUsed() { assert(controllable); used = true; }
#endif

	bool isFloat() const { return v_type == tp_float; }
	bool isInt() const { return v_type == tp_int; }
	bool isBool() const { return v_type == tp_bool; }
	bool isSwitch() const { return v_type == tp_switch; }
	bool isFile() const { return v_type == tp_file; }
	ctrl_type getControlType() const { return c_type; }
	bool isControllable() const { return controllable; }
	bool isInPreset() const { return save_in_preset; }
	bool isExperimental() const { return experimental; }
	string id() const { return _id; }
	string group() const { return _group; }
	string name() const { return _name; }
	bool operator==(const Parameter& p) const { return &p == this; }
	virtual void *zone() = 0;
	virtual void set_std_value() = 0;
	virtual void set(int n, int high, float llimit, float ulimit) = 0;
	virtual void writeJSON(gx_system::JsonWriter& jw) = 0;
	virtual void readJSON_value(gx_system::JsonParser& jp) = 0;
	virtual void setJSON_value() = 0;
	virtual bool hasRange() const;
	virtual float getLowerAsFloat() const;
	virtual float getUpperAsFloat() const;
	virtual float getStepAsFloat() const;
	virtual const char **getValueNames() const;
	FloatParameter& getFloat();
	IntParameter& getInt();
	BoolParameter& getBool();
	SwitchParameter& getSwitch();
	FileParameter &getFile();
};

typedef list<gx_gui::Parameter*> paramlist;


class FloatParameter: public Parameter
{
protected:
	float json_value;
public:
	float &value;
	float std_value;
	float lower, upper, step;
	void set(float val) const { value = min(max(val, lower), upper); }
	virtual void *zone();
	virtual void set_std_value();
	virtual void set(int n, int high, float llimit, float ulimit);
	virtual void writeJSON(gx_system::JsonWriter& jw);
	virtual void readJSON_value(gx_system::JsonParser& jp);
	virtual void setJSON_value();
	virtual bool hasRange() const;
	virtual float getLowerAsFloat() const;
	virtual float getUpperAsFloat() const;
	virtual float getStepAsFloat() const;
	FloatParameter(string id, string name, ctrl_type ctp, bool preset,
	               float &v, float sv, float lv, float uv, float tv, bool ctrl, bool exp=false):
		Parameter(id, name, tp_float, ctp, preset, ctrl, exp),
		value(v), std_value(sv), lower(lv), upper(uv), step(tv)
		{}
};

class FloatEnumParameter: public FloatParameter
{
private:
	const char** value_names;
public:
	virtual void writeJSON(gx_system::JsonWriter& jw);
	virtual void readJSON_value(gx_system::JsonParser& jp);
	virtual const char **getValueNames() const;
	FloatEnumParameter(string id, string name, const char** vn, bool preset, float &v,
	                   int sv, bool ctrl, bool exp=false);
};

class IntParameter: public Parameter
{
protected:
	int json_value;
public:
	int &value;
	int std_value;
	int lower, upper;
	void set(int val) const { value = min(max(val, lower), upper); }
	virtual void *zone();
	virtual void set_std_value();
	virtual void set(int n, int high, float llimit, float ulimit);
	virtual void writeJSON(gx_system::JsonWriter& jw);
	virtual void readJSON_value(gx_system::JsonParser& jp);
	virtual void setJSON_value();
	virtual bool hasRange() const;
	virtual float getLowerAsFloat() const;
	virtual float getUpperAsFloat() const;
	IntParameter(string id, string name, ctrl_type ctp, bool preset,
	             int &v, int sv, int lv, int uv, bool ctrl, bool exp=false):
		Parameter(id, name, tp_int, ctp, preset, ctrl, exp),
		value(v), std_value(sv), lower(lv), upper(uv)
		{}
};

class EnumParameter: public IntParameter
{
private:
	const char** value_names;
public:
	virtual void writeJSON(gx_system::JsonWriter& jw);
	virtual void readJSON_value(gx_system::JsonParser& jp);
	virtual const char **getValueNames() const;
	EnumParameter(string id, string name, const char** vn, bool preset, int &v,
	              int sv, bool ctrl, bool exp=false);
};

class BoolParameter: public Parameter
{
private:
	bool json_value;
public:
	bool &value;
	bool std_value;
	void set(bool val) const { value = val; }
	virtual void *zone();
	virtual void set_std_value();
	virtual void set(int n, int high, float llimit, float ulimit);
	virtual void writeJSON(gx_system::JsonWriter& jw);
	virtual void setJSON_value();
	virtual void readJSON_value(gx_system::JsonParser& jp);
	BoolParameter(string id, string name, ctrl_type ctp, bool preset,
	              bool &v, bool sv, bool ctrl, bool exp=false):
		Parameter(id, name, tp_float, ctp, preset, ctrl, exp),
		value(v), std_value(sv)
		{}
};

class SwitchParameter: public Parameter
{
private:
	bool value;
	bool std_value;
	bool json_value;
public:
	sigc::signal<void, bool> changed;
	void set(bool val);
	bool get() const { return value; }
	virtual void *zone();
	virtual void set_std_value();
	virtual void set(int n, int high, float llimit, float ulimit);
	virtual void writeJSON(gx_system::JsonWriter& jw);
	virtual void readJSON_value(gx_system::JsonParser& jp);
	virtual void setJSON_value();
	SwitchParameter(string id, bool preset=false, bool sv=false):
		Parameter(id, "", tp_switch, Switch, preset, false),
		value(sv), std_value(sv)
		{}
};

class FileParameter: public Parameter
{
private:
	Glib::RefPtr<Gio::File> value;
	Glib::RefPtr<Gio::File> std_value;
	Glib::RefPtr<Gio::File> json_value;
public:
	void set(const Glib::RefPtr<Gio::File>& val);
	void set_path(const string& path);
	const Glib::RefPtr<Gio::File>& get() const { return value; }
	virtual void *zone();
	virtual void set_std_value();
	virtual void set(int n, int high, float llimit, float ulimit);
	virtual void writeJSON(gx_system::JsonWriter& jw);
	virtual void readJSON_value(gx_system::JsonParser& jp);
	virtual void setJSON_value();
	FileParameter(string id, string filename, bool preset=false):
		Parameter(id, "", tp_file, None, preset, false),
		value(Gio::File::create_for_path(filename)),
		std_value(value->dup())
		{}
	FileParameter(string id, bool preset=false):
		Parameter(id, "", tp_file, None, preset, false),
		value(0),
		std_value(0)
		{}
	void set_standard(const string& filename);
	bool is_standard() const;
	string get_path();
	string get_directory_path();
	string get_parse_name();
	string get_display_name();
	void copy(const string& destination);
};

inline FloatParameter &Parameter::getFloat()
{
	assert(isFloat());
	return static_cast<FloatParameter&>(*this);
}

inline IntParameter &Parameter::getInt()
{
	assert(isInt());
	return static_cast<IntParameter&>(*this);
}

inline BoolParameter &Parameter::getBool()
{
	assert(isBool());
	return static_cast<BoolParameter&>(*this);
}

inline SwitchParameter &Parameter::getSwitch()
{
	assert(isSwitch());
	return static_cast<SwitchParameter&>(*this);
}

inline FileParameter &Parameter::getFile()
{
	assert(isFile());
	return static_cast<FileParameter&>(*this);
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
	void check_id(string id);
	void check_p(const char *p);
	void check_addr(const void *p);
#endif

public:
	typedef map<string, Parameter*>::iterator iterator;
	iterator begin() { return id_map.begin(); }
	iterator end() { return id_map.end(); }
	bool hasZone(const void *p) const { return addr_map.find(p) != addr_map.end(); }
	bool hasId(string id) const { return id_map.find(id) != id_map.end(); }
	bool hasId(const char *p) const { return id_map.find(p) != id_map.end(); }
	Parameter& operator[](const void *p) { debug_check(check_addr, p); return *addr_map[p]; }
	Parameter& operator[](string id) { debug_check(check_id, id); return *id_map[id]; }
	Parameter& operator[](const char *p) { debug_check(check_p, p); return *id_map[p]; }
	void insert(Parameter* param);
	void set_init_values();
};

extern ParamMap parameter_map; // map id -> parameter, zone -> parameter

inline void registerParam(const char*a,const char*b,float*c,float std,float lower,float upper,float step)
{
	parameter_map.insert(new FloatParameter(a,b,Parameter::Continuous,true,*c,std,lower,upper,step,true));
}

inline void registerParam(const char*a,const char*b,float*c,float std=0)
{
	parameter_map.insert(new FloatParameter(a,b,Parameter::Switch,true,*c,std,0,1,1,true));
}

// should be bool
inline void registerParam(const char*a,const char*b,int*c,int d)
{
	parameter_map.insert(new IntParameter(a,b,Parameter::Switch,true,*c,d,0,1065353216,true)); //FIXME (see above float/int)
}

inline void registerParam(const char*a,const char*b,bool*c,bool d=false, bool exp=false)
{
	parameter_map.insert(new BoolParameter(a,b,Parameter::Switch,true,*c,d,true,exp));
}

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
	struct modstring {
		string name;
		bool modified;
		const char *std;
		modstring(string n, bool m, const char* s): name(n), modified(m), std(s) {}
		modstring(const char* n): name(n), modified(false), std(n) {}
		modstring(): name(""), modified(false), std(0) {}
	};
	map<int,modstring> m;

public:
	MidiStandardControllers();
	const string operator[](int ctr) { return m[ctr].name; }
	void replace(int ctr, string name);
	void writeJSON(gx_system::JsonWriter& jw) const;
	void readJSON(gx_system::JsonParser& jp);
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
	Parameter& getParameter() const { return param; }
	static MidiController* readJSON(gx_system::JsonParser&);
	void set(int n) { param.set(n, 127, _lower, _upper); }
	void writeJSON(gx_system::JsonWriter& jw) const;
};

typedef list<MidiController> midi_controller_list;


/*
** MidiControllerList
*/

class MidiControllerList
{
public:
	typedef vector<midi_controller_list> controller_array;
	enum { controller_array_size = 128 };
private:
	controller_array map;
	bool midi_config_mode;
	int last_midi_control;
	int last_midi_control_value;
public:
	MidiControllerList();
	midi_controller_list& operator[](int n) { return map[n]; }
	int size() { return map.size(); }
	void set_config_mode(bool mode, int ctl=-1);
	bool get_config_mode() { return midi_config_mode; }
	int get_current_control() { return last_midi_control; }
	void set_current_control(int ctl) { last_midi_control = ctl; }
	void set(int ctr, int val);
	void deleteParameter(Parameter& param, bool quiet=false);
	void modifyCurrent(Parameter& param, float lower, float upper);
	int param2controller(Parameter& param, const MidiController** p);
	void writeJSON(gx_system::JsonWriter& jw);
	void readJSON(gx_system::JsonParser& jp, controller_array& m);
	void set_controller_array(const controller_array& m);
	void remove_controlled_parameters(paramlist& plist, const controller_array *m);
	sigc::signal<void> changed;
};

void recall_midi_controller_map();
bool save_midi_controller_map();

extern MidiControllerList controller_map; // map ctrl num -> controlled parameters


} // namespace gx_gui

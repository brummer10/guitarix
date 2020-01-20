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
 *    Note: this header file depends on gx_system.h 
 * 
 * ----------------------------------------------------------------------------
 */

#pragma once

#ifndef SRC_HEADERS_GX_PARAMETER_H_
#define SRC_HEADERS_GX_PARAMETER_H_

namespace gx_system { class JsonWriter; class JsonParser; }

namespace gx_engine {

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

class ParameterGroups {
 private:
    map<string, string> groups;

#ifndef NDEBUG
    map<string, bool> used;
    void group_exists(const string& id);
    void group_is_new(const string& id);
    friend string param_group(const string& group_id, bool nowarn);
#endif

 public:
    ParameterGroups();
    ~ParameterGroups();

    inline string get(const string& id) { return groups[id]; }
    inline string operator[](const string& id) {
	debug_check(group_exists, id);
	return groups[id];
    }
    inline void insert(const string& id, const string& group) {
	debug_check(group_is_new, id);
	groups.insert(pair<string, string>(id, group));
    }
    bool group_exist(const string& id);
    inline void erase(const string& id) {
#ifndef NDEBUG // avoid unused variable warning in release mode
	size_t n = groups.erase(id);
	assert(n == 1);
#else
	groups.erase(id);
#endif
    }
#ifndef NDEBUG
    void dump();
#endif
};


ParameterGroups& get_group_table();
string param_group(const string& group_id, bool nowarn = false);

/****************************************************************
 ** Parameter
 */

template <class T> class ParameterV;

typedef ParameterV<float> FloatParameter;
typedef ParameterV<int> IntParameter;
typedef ParameterV<bool> BoolParameter;
typedef ParameterV<Glib::ustring> StringParameter;

class FloatEnumParameter;
class EnumParameter;
class FileParameter;

/****************************************************************/

class Parameter: boost::noncopyable {
public:
    enum ctrl_type { None, Continuous, Switch, Enum };
    enum toggle_type { OnOff = 0, Constant = 1, Toggle = 2, _Count = 3 };
private:
    virtual bool midi_set(float n, float high, float llimit, float ulimit); //RT
    virtual bool midi_set_bpm(float n, float high, float llimit, float ulimit); //RT
    virtual void trigger_changed();
    friend class MidiController;
protected:
    enum value_type { tp_float, tp_int, tp_bool, tp_file, tp_string, tp_special };
    enum display_flags { dtp_normal, dtp_log = 1 };
    string _id;
    string _name, _group, _desc;
    enum value_type v_type : 3;
    enum ctrl_type c_type  : 3;
    unsigned int d_flags   : 2;
    bool save_in_preset    : 1;
    bool controllable      : 1;
    bool do_not_save       : 1;
    bool blocked           : 1;
    bool midi_blocked      : 1;
    bool used              : 1; // debug
protected:
    void range_warning(float value, float lower, float upper);
    static gx_system::JsonParser& jp_next(gx_system::JsonParser& jp, const char *key);
public:
    inline std::string group_id() const { return _id.substr(0, _id.find_last_of(".")); }
    Parameter(const string& id, const string& name, value_type vtp, ctrl_type ctp, bool preset,
              bool ctrl):
	boost::noncopyable(),
        _id(id),
        _name(name),
        _group(param_group(group_id())),
        _desc(),
        v_type(vtp),
        c_type(ctp),
	d_flags(0),
        save_in_preset(preset),
        controllable(ctrl),
	do_not_save(false),
	blocked(false),
	midi_blocked(false),
        used(false) {}
    Parameter(gx_system::JsonParser& jp);
    virtual ~Parameter();
    virtual void serializeJSON(gx_system::JsonWriter& jw);

#ifndef NDEBUG
    bool isUsed() const { return used; }
    void setUsed() { used = true; }
    friend void compare_parameter(const char* title, Parameter* p1,
				  Parameter* p2, bool all);
    void dump(gx_system::JsonWriter *jw);
#endif

    const char *get_typename() const;
    bool isFloat() const { return v_type == tp_float; }
    bool isInt() const { return v_type == tp_int; }
    bool isBool() const { return v_type == tp_bool; }
    bool isFile() const { return v_type == tp_file; }
    bool isString() const { return v_type == tp_string; }
    ctrl_type getControlType() const { return c_type; }
    bool isControllable() const { return controllable; }
    bool isInPreset() const { return save_in_preset; }
    bool isSavable() const { return !do_not_save; }
    void setSavable(bool v) { do_not_save = !v; }
    const string& id() const { return _id; }
    const string& group() const { return _group; }
    string l_group() const { return gettext(_group.c_str()); }
    const string& name() const { return _name; }
    string l_name() const { return gettext(_name.c_str()); }
    const string& desc() const { return _desc; }
    void set_desc(const string& desc) { _desc = desc; }
    string l_desc() const { return gettext(_desc.c_str()); }
    void set_log_display() { d_flags |= dtp_log; }
    bool is_log_display() { return d_flags & dtp_log; }
    void set_blocked(bool v) { blocked = v; }
    bool get_blocked() { return blocked; }
    void set_midi_blocked(bool v) { midi_blocked = v; }
    bool get_midi_blocked() { return midi_blocked; }
    bool operator==(const Parameter& p) const { return &p == this; }
    virtual void stdJSON_value() = 0;
    virtual bool on_off_value() = 0; //RT
    virtual void writeJSON(gx_system::JsonWriter& jw) const = 0;
    virtual void readJSON_value(gx_system::JsonParser& jp) = 0;
    virtual void setJSON_value() = 0;
    virtual bool compareJSON_value() = 0;
    virtual bool hasRange() const;
    virtual float getLowerAsFloat() const;
    virtual float getUpperAsFloat() const;
    virtual float getStepAsFloat() const;
    virtual const value_pair *getValueNames() const;
    static inline const char *value_label(const value_pair& vp) {
	return gettext(vp.value_label ? vp.value_label : vp.value_id);
    }
    FloatParameter& getFloat();
    IntParameter& getInt();
    EnumParameter& getEnum();
    BoolParameter& getBool();
    FileParameter &getFile();
    StringParameter &getString();
    sigc::signal<void, float>& signal_changed_float();
    sigc::signal<void, int>& signal_changed_int();
    sigc::signal<void, bool>& signal_changed_bool();
    sigc::signal<void, const Glib::ustring&>& signal_changed_string();
};

#ifndef NDEBUG
void compare_parameter(const char* title, Parameter* p1,
		       Parameter* p2, bool all = false);
#endif

/****************************************************************/

typedef list<Parameter*> paramlist;

/****************************************************************/

template<class T>
class ParameterV: public Parameter {
};

template<>
class ParameterV<float>: public Parameter {
private:
    virtual bool midi_set(float n, float high, float llimit, float ulimit); //RT
    virtual bool midi_set_bpm(float n, float high, float llimit, float ulimit); //RT
    virtual void trigger_changed();
protected:
    float json_value;
    float *value;
    float std_value;
    float lower, upper, step;
    sigc::signal<void, float> changed;
    float value_storage;
    friend class ParamRegImpl;
public:
    bool set(float val) const;
    bool ramp_value(float val);
    float get_value() const { return *value; }
    void convert_from_range(float low, float up);
    virtual void stdJSON_value();
    virtual bool on_off_value();
    virtual void writeJSON(gx_system::JsonWriter& jw) const;
    virtual void readJSON_value(gx_system::JsonParser& jp);
    virtual void rampJSON_value(gx_system::JsonParser& jp);
    virtual bool compareJSON_value();
    virtual void setJSON_value();
    virtual bool hasRange() const;
    virtual float getLowerAsFloat() const;
    virtual float getUpperAsFloat() const;
    virtual float getStepAsFloat() const;
    virtual float idx_from_id(string v_id);
    ParameterV(const string& id, const string& name, ctrl_type ctp, bool preset,
	       float *v, float sv, float lv, float uv, float tv, bool ctrl, bool no_init):
	Parameter(id, name, tp_float, ctp, preset, ctrl),
	value(v ? v : &value_storage), std_value(sv),lower(lv),upper(uv),step(tv) {
	set(no_init ? *value : sv);
    }
#ifndef NDEBUG
    friend void compare_parameter(const char* title, Parameter* p1,
				  Parameter* p2, bool all);
#endif
    ~ParameterV();
    ParameterV(gx_system::JsonParser& jp);
    virtual void serializeJSON(gx_system::JsonWriter& jw);
    sigc::signal<void, float>& signal_changed() { return changed; }
};

/****************************************************************/

class FloatEnumParameter: public FloatParameter {
protected:
    const value_pair* value_names;
    FloatEnumParameter(gx_system::JsonParser& jp): FloatParameter(jp_next(jp, "FloatParameter")), value_names(0) {}
public:
    virtual void writeJSON(gx_system::JsonWriter& jw) const;
    virtual void readJSON_value(gx_system::JsonParser& jp);
    virtual const value_pair *getValueNames() const;
    FloatEnumParameter(const string& id, const string& name, const value_pair* vn, bool preset, float *v,
                       int sv, int low, bool ctrl, bool no_init);
    virtual void serializeJSON(gx_system::JsonWriter& jw);
    virtual float idx_from_id(string v_id);
};

/****************************************************************/

template<>
class ParameterV<int>: public Parameter {
private:
    virtual bool midi_set(float n, float high, float llimit, float ulimit); //RT
    virtual void trigger_changed();
protected:
    int json_value;
    int *value;
    int std_value;
    int lower, upper;
    sigc::signal<void, int> changed;
    int value_storage;
public:
    bool set(int val) const;
    int get_value() const { return *value; }
    virtual void stdJSON_value();
    virtual bool on_off_value();
    virtual void writeJSON(gx_system::JsonWriter& jw) const;
    virtual void readJSON_value(gx_system::JsonParser& jp);
    virtual bool compareJSON_value();
    virtual void setJSON_value();
    virtual bool hasRange() const;
    virtual float getLowerAsFloat() const;
    virtual float getUpperAsFloat() const;
    virtual int idx_from_id(string v_id);
    ParameterV(const string& id, const string& name, ctrl_type ctp, bool preset,
	       int *v, int sv, int lv, int uv, bool ctrl):
	Parameter(id, name, tp_int, ctp, preset, ctrl),
        value(v ? v : &value_storage), std_value(sv), lower(lv), upper(uv) {
	*value = sv;
    }
    ~ParameterV();
    ParameterV(gx_system::JsonParser& jp);
    virtual void serializeJSON(gx_system::JsonWriter& jw);
    sigc::signal<void, int>& signal_changed() { return changed; }
};

/****************************************************************/

class EnumParameter: public IntParameter {
protected:
    const value_pair* value_names;
    EnumParameter(gx_system::JsonParser& jp): IntParameter(jp_next(jp, "IntParameter")), value_names(0) {}
public:
    virtual void writeJSON(gx_system::JsonWriter& jw) const;
    virtual void readJSON_value(gx_system::JsonParser& jp);
    virtual const value_pair *getValueNames() const;
    virtual int idx_from_id(string v_id);
    const value_pair& get_pair() { return getValueNames()[get_value()]; }
    EnumParameter(const string& id, const string& name, const value_pair* vn, bool preset, int *v,
                  int sv, bool ctrl);
    virtual void serializeJSON(gx_system::JsonWriter& jw);
};

/****************************************************************/

template<>
class ParameterV<bool>: public Parameter {
private:
    virtual bool midi_set(float n, float high, float llimit, float ulimit); //RT
    virtual void trigger_changed();
protected:
    bool json_value;
    bool *value;
    bool std_value;
    sigc::signal<void, bool> changed;
    bool value_storage;
public:
    bool set(bool val) const;
    virtual void stdJSON_value();
    bool get_value() const { return *value; }
    virtual bool on_off_value();
    virtual void writeJSON(gx_system::JsonWriter& jw) const;
    virtual bool compareJSON_value();
    virtual void setJSON_value();
    virtual void readJSON_value(gx_system::JsonParser& jp);
    ParameterV(const string& id, const string& name, ctrl_type ctp, bool preset,
                  bool *v, bool sv, bool ctrl):
        Parameter(id, name, tp_bool, ctp, preset, ctrl),
        value(v ? v : &value_storage), std_value(sv) {
	*value = sv;
    }
    ~ParameterV();
    ParameterV(gx_system::JsonParser& jp);
    virtual void serializeJSON(gx_system::JsonWriter& jw);
    sigc::signal<void, bool>& signal_changed() { return changed; }
};

/****************************************************************/

/****************************************************************/

class FileParameter: public Parameter {
protected:
    Glib::RefPtr<Gio::File> value;
    Glib::RefPtr<Gio::File> std_value;
    Glib::RefPtr<Gio::File> json_value;
    sigc::signal<void> changed;
public:
    sigc::signal<void>& signal_changed() { return changed; }
    bool set(const Glib::RefPtr<Gio::File>& val);
    void set_path(const string& path);
    const Glib::RefPtr<Gio::File>& get() const { return value; }
    virtual void stdJSON_value();
    virtual bool on_off_value();
    virtual void writeJSON(gx_system::JsonWriter& jw) const;
    virtual void readJSON_value(gx_system::JsonParser& jp);
    virtual bool compareJSON_value();
    virtual void setJSON_value();
    FileParameter(const string& id, const string& filename, bool preset = false):
        Parameter(id, "", tp_file, None, preset, false),
        value(Gio::File::create_for_path(filename)),
        std_value(value->dup()) {}
    FileParameter(const string& id, bool preset = false):
        Parameter(id, "", tp_file, None, preset, false),
        value(0),
        std_value(0) {}
    FileParameter(gx_system::JsonParser& jp);
    virtual void serializeJSON(gx_system::JsonWriter& jw);
    void set_standard(const string& filename);
    bool is_equal(const Glib::RefPtr<Gio::File>& v) const;
    bool is_standard() const { return is_equal(std_value); }
    string get_path() const;
    string get_directory_path() const;
    string get_parse_name() const;
    string get_display_name() const;
    void copy(const string& destination) const;
};

/****************************************************************/

template<>
class ParameterV<Glib::ustring>: public Parameter {
protected:
    Glib::ustring json_value;
    Glib::ustring *value;
    Glib::ustring std_value;
    sigc::signal<void, const Glib::ustring&> changed;
    Glib::ustring value_storage;
public:
    bool set(const Glib::ustring& val) const;
    const Glib::ustring& get_value() const { return *value; }
    virtual void stdJSON_value();
    virtual bool on_off_value();
    virtual void writeJSON(gx_system::JsonWriter& jw) const;
    virtual bool compareJSON_value();
    virtual void setJSON_value();
    virtual void readJSON_value(gx_system::JsonParser& jp);
    ParameterV(const string& id, const string& name, Glib::ustring *v, const Glib::ustring& sv, bool preset = false)
	: Parameter(id, name, tp_string, None, preset, false),
	  value(v ? v : &value_storage), std_value(sv) {
    }
    ~ParameterV();
    ParameterV(gx_system::JsonParser& jp);
    virtual void serializeJSON(gx_system::JsonWriter& jw);
    sigc::signal<void, const Glib::ustring&>& signal_changed() { return changed; }
};


/****************************************************************/

inline FloatParameter &Parameter::getFloat() {
    assert(isFloat());
    return static_cast<FloatParameter&>(*this);
}

inline IntParameter &Parameter::getInt() {
    assert(isInt());
    return static_cast<IntParameter&>(*this);
}

inline EnumParameter &Parameter::getEnum() {
    EnumParameter *p = dynamic_cast<EnumParameter*>(this);
    assert(p);
    return *p;
}

inline BoolParameter &Parameter::getBool() {
    assert(isBool());
    return static_cast<BoolParameter&>(*this);
}

inline FileParameter &Parameter::getFile() {
    assert(isFile());
    return static_cast<FileParameter&>(*this);
}

inline StringParameter &Parameter::getString() {
    assert(isString());
    return static_cast<StringParameter&>(*this);
}

inline sigc::signal<void, float>& Parameter::signal_changed_float() {
    FloatParameter *p = dynamic_cast<FloatParameter*>(this);
    assert(p);
    return p->signal_changed();
}

inline sigc::signal<void, int>& Parameter::signal_changed_int() {
    IntParameter *p = dynamic_cast<IntParameter*>(this);
    assert(p);
    return p->signal_changed();
}

inline sigc::signal<void, bool>& Parameter::signal_changed_bool() {
    BoolParameter *p = dynamic_cast<BoolParameter*>(this);
    assert(p);
    return p->signal_changed();
}

inline sigc::signal<void, const Glib::ustring&>& Parameter::signal_changed_string() {
    StringParameter *p = dynamic_cast<StringParameter*>(this);
    assert(p);
    return p->signal_changed();
}


/****************************************************************
 ** ParamMap
 */

class ParamMap: boost::noncopyable {
 private:
    map<string, Parameter*> id_map;
    bool replace_mode;
    sigc::signal<void,Parameter*,bool> insert_remove;
#ifndef NDEBUG
    void unique_id(Parameter* param);
    void check_id(const string& id);
    void check_p(const char *p);
#endif
    Parameter *insert(Parameter* param); // private so we can make sure parameters are owned

 public:
    template<class T> friend class ParameterV;
    ParamMap();
    ~ParamMap();
    void writeJSON(gx_system::JsonWriter& jw);
    void readJSON(gx_system::JsonParser& jp);
    Parameter *readJSON_one(gx_system::JsonParser& jp);
    void writeJSON_one(gx_system::JsonWriter& jw, Parameter *p);
    typedef map<string, Parameter*>::const_iterator iterator;
    iterator begin() const { return id_map.begin(); }
    iterator end() const { return id_map.end(); }
    bool hasId(const string& id) const { return id_map.find(id) != id_map.end(); }
    bool hasId(const char *p) const { return id_map.find(p) != id_map.end(); }
    void set_replace_mode(bool mode) { replace_mode = mode; }
    Parameter& operator[](const string& id) {
        debug_check(check_id, id);
        return *id_map[id];
    }
    Parameter& operator[](const char *p) {
        debug_check(check_p, p);
        return *id_map[p];
    }
    void set_init_values();
    void reset_unit(const PluginDef *pdef) const;
    bool unit_has_std_values(const PluginDef *pdef) const;
    sigc::signal<void,Parameter*,bool> signal_insert_remove() { return insert_remove; }
    void unregister(Parameter *p);
    void unregister(const string& id);
    inline FloatParameter *reg_par(const string& id, const string& name, float *var, float std,
				   float lower, float upper, float step) {
	FloatParameter *p = new FloatParameter(id, name, Parameter::Continuous, true, var, std, lower, upper, step, true, replace_mode);
	insert(p);
	return p;
    }
    inline FloatParameter *reg_par_non_preset(
	const string& id, const string& name, float *var, float std, float lower, float upper, float step) {
	FloatParameter *p = new FloatParameter(id, name, Parameter::Continuous, false, var, std, lower, upper, step, false, replace_mode);
	insert(p);
	return p;
    }
    inline FloatParameter *reg_par(const string& id, const string& name, float *var, float std = 0) {
	FloatParameter *p = new FloatParameter(id, name, Parameter::Switch, true, var, std, 0, 1, 1, true, replace_mode);
	insert(p);
	return p;
    }
    inline BoolParameter *reg_par(const string& id, const string& name, bool *var, bool std=false, bool preset=true) {
	BoolParameter * p = new BoolParameter(id, name, Parameter::Switch, preset, var, std, true);
	insert(p);
	return p;
    }
    inline EnumParameter *reg_enum_par(const string& id, const string& name,
				       const value_pair *vl, int *var, int std = 0) {
	EnumParameter *p = new EnumParameter(id, name, vl, true, var, std, true);
	insert(p);
	return p;
    }
    inline EnumParameter *reg_non_midi_enum_par(
	const string& id, const string& name, const value_pair *vl,
	int *var, bool preset, int std = 0) {
	EnumParameter *p = new EnumParameter(id, name, vl, preset, var, std, false);
	insert(p);
	return p;
    }
    inline FloatEnumParameter *reg_enum_par(const string& id, const string& name,
					    const value_pair *vl, float *var,
					    int std = 0, int low = 0) {
	FloatEnumParameter *p = new FloatEnumParameter(id, name, vl, true, var, std, low, true, replace_mode);
	insert(p);
	return p;
    }
    inline BoolParameter *reg_non_midi_par(const string& id, bool *var, bool preset, bool std = false) {
	BoolParameter *p = new BoolParameter(id, "", Parameter::Switch, preset, var, std, false);
	insert(p);
	return p;
    }
    inline IntParameter *reg_non_midi_par(const string& id, int *var, bool preset, int std, int lower, int upper) {
	IntParameter *p = new IntParameter(id, "", Parameter::None, preset, var, std, lower, upper, false);
	insert(p);
	return p;
    }
    inline FloatParameter *reg_non_midi_par(const string& id, float *val, bool preset,
				 float std = 0, float lower = 0, float upper = 1, float step = 0) {
	FloatParameter *p = new FloatParameter(id, "", Parameter::Continuous, preset, val, std, lower, upper, step, false, replace_mode);
	insert(p);
	return p;
    }
    inline FileParameter *reg_filepar(const string& id, bool preset = false) {
	FileParameter *p = new FileParameter(id, preset);
	insert(p);
	return p;
    }
    inline StringParameter *reg_string(const string& id, const string& name, Glib::ustring *var, const string& sv, bool preset=false) {
	StringParameter *p = new StringParameter(id, name, var, sv, preset);
	insert(p);
	return p;
    }
    inline StringParameter *reg_preset_string(const string& id, const string& name, Glib::ustring *var, const string& sv, bool preset=true) {
	StringParameter *p = new StringParameter(id, name, var, sv, preset);
	insert(p);
	return p;
    }

#ifndef NDEBUG
    void dump(const string& fmt);
#endif
};

/****************************************************************
 **
 ** Midi
 **
 */


/*
** MidiStandardControllers
*/

/****************************************************************/

class MidiStandardControllers {
 private:
    struct modstring {
        string name;
        bool modified;
        const char *std;
        modstring(const string& n, bool m, const char* s): name(n), modified(m), std(s) {}
        explicit modstring(const char* n): name(n), modified(false), std(n) {}
        modstring(): name(""), modified(false), std(0) {}
    };
    map<int, modstring> m;
    string midi_to_note(int ctr);
    string ctr_desc(int ctr);
 public:
    MidiStandardControllers();
    const string operator[](int ctr) { return m[ctr].name; }
    void replace(int ctr, const string& name);
    void writeJSON(gx_system::JsonWriter& jw) const;
    void readJSON(gx_system::JsonParser& jp);
};

extern MidiStandardControllers midi_std_ctr; // map ctrl num -> standard name

/****************************************************************
**
** MidiController
**/

class MidiController {
 private:
    Parameter *param; //RT
    float _lower, _upper; //RT
    bool toggle; //RT
    int _toggle_behaviour;

 public:
    MidiController(Parameter& p, float l, float u, bool t=false, int tt=0):
        param(&p), _lower(l), _upper(u), toggle(t), _toggle_behaviour(tt) {}
    float lower() const { return _lower; }
    float upper() const { return _upper; }
    bool is_toggle() const { return toggle; }
    int toggle_behaviour() const { return _toggle_behaviour; }
    bool hasParameter(const Parameter& p) const { return *param == p; }
    Parameter& getParameter() const { return *param; }
    static MidiController *readJSON(gx_system::JsonParser& jp, ParamMap& param);
    bool set_midi(int n, int last_value, bool update); //RT
    bool set_bpm(int n, int last_value); //RT
    bool set_trans(int n, int last_value); //RT
    void set(float v, float high) { param->midi_set(v, high, _lower, _upper); }
    void trigger_changed() { param->trigger_changed(); }
    void writeJSON(gx_system::JsonWriter& jw) const;
};

typedef list<MidiController> midi_controller_list;

/****************************************************************
**
** MidiControllerList
**/


class MidiClockToBpm {
private:
    double                 time1;
    double                 time_diff;
    int                    collect;
    int                    collect_;
    double                 bpm;
    double                 bpm_new;
    bool                   ret;

public:
    MidiClockToBpm();
    ~MidiClockToBpm() {}
    unsigned int rounded(float f);
    bool time_to_bpm(double time, unsigned int* bpm_);
};


class ControllerArray: public vector<midi_controller_list> {
public:
    enum { array_size = 328 };
    ControllerArray(): vector<midi_controller_list>(array_size) {}
    ~ControllerArray() {}
    void writeJSON(gx_system::JsonWriter& jw) const;
    void readJSON(gx_system::JsonParser& jp, ParamMap& param);
    int param2controller(Parameter& param, const MidiController** p);
    bool deleteParameter(Parameter& p);
};

class MidiControllerList: public sigc::trackable {
public:
private:
    ControllerArray        map; //RT
    int                    last_midi_control_value[ControllerArray::array_size]; //RT
    int                    last_midi_control; //RT
    int                    changed_midi_control_value[ControllerArray::array_size]; //RT
    volatile gint          program_change; //RT
    volatile gint          mute_change; //RT
    volatile gint          bank_change; //RT
    int                    channel_select;
    timespec               ts1;
    double                 time0;
    unsigned int           bpm_;
    MidiClockToBpm         mp;
    Glib::Dispatcher       pgm_chg;
    Glib::Dispatcher       mute_chg;
    Glib::Dispatcher       bank_chg;
    Glib::Dispatcher       val_chg;
    sigc::signal<void>     changed;
    sigc::signal<void,int> new_program;
    sigc::signal<void,int> new_mute_state;
    sigc::signal<void,int> new_bank;
    sigc::signal<void, int, int> midi_value_changed;
private:
    void               on_pgm_chg();
    void               on_mute_chg();
    void               on_bank_chg();
    void               on_val_chg();
    bool check_midi_values();
public:
    MidiControllerList();
    midi_controller_list& operator[](int n) { return map[n]; }
    int size() { return map.size(); }
    void set_config_mode(bool mode, int ctl=-1);
    bool get_config_mode() { return last_midi_control != -2; }
    int get_current_control() { return last_midi_control; }
    void set_current_control(int ctl) { last_midi_control = ctl; }
    void set_ctr_val(int ctr, int val); //RT
    void set_bpm_val(unsigned int val); //RT
    void deleteParameter(Parameter& param);
    void modifyCurrent(Parameter& param, float lower, float upper, bool toggle, int toggle_behaviour);
    int param2controller(Parameter& param, const MidiController** p) {
	return map.param2controller(param, p); }
    void writeJSON(gx_system::JsonWriter& jw) const { map.writeJSON(jw); }
    int get_last_midi_control_value(unsigned int n) {
	assert(n < ControllerArray::array_size); return last_midi_control_value[n]; } //RT
    void set_last_midi_control_value(unsigned int n, int v) {
	assert(n < ControllerArray::array_size); last_midi_control_value[n] = v; changed_midi_control_value[n] = 1; } //RT
    void set_controller_array(const ControllerArray& m);
    void remove_controlled_parameters(paramlist& plist, const ControllerArray *m);
    sigc::signal<void>& signal_changed() { return changed; }
    sigc::signal<void,int>& signal_new_program() { return new_program; }
    sigc::signal<void,int>& signal_new_mute_state() { return new_mute_state; }
    sigc::signal<void,int>& signal_new_bank() { return new_bank; }
    void compute_midi_in(void* midi_input_port_buf, void *arg);  //RT
    void process_trans(int transport_state);  //RT
    void update_from_controller(int ctr);
    void update_from_controllers();
    void set_midi_channel(int s);
    sigc::signal<void, int, int>& signal_midi_value_changed() { return midi_value_changed; }
    void request_midi_value_update();
};

} // namespace gx_gui

#endif  // SRC_HEADERS_GX_PARAMETER_H_


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
    friend string param_group(const string& id, bool nowarn);
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
string param_group(const string& id, bool nowarn = false);

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
protected:
    enum value_type { tp_float, tp_int, tp_bool, tp_file, tp_string, tp_special };
    enum display_flags { dtp_normal, dtp_log = 1 };
    string _id;
    string _name, _group, _desc;
    enum value_type v_type : 3;
    enum ctrl_type c_type : 3;
    unsigned int d_flags : 2;
    bool save_in_preset : 1;
    bool controllable : 1;
    bool own_var : 1;
    bool do_not_save : 1;
    bool used : 1; // debug
protected:
    void range_warning(float value, float lower, float upper);
    static gx_system::JsonParser& jp_next(gx_system::JsonParser& jp, const char *key);
public:
    Parameter(const string& id, const string& name, value_type vtp, ctrl_type ctp, bool preset,
              bool ctrl):
        _id(id),
        _name(name),
        _group(param_group(id)),
        _desc(),
        v_type(vtp),
        c_type(ctp),
	d_flags(0),
        save_in_preset(preset),
        controllable(ctrl),
	own_var(false),
	do_not_save(false),
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
    bool operator==(const Parameter& p) const { return &p == this; }
    virtual void *zone() = 0;
    virtual void stdJSON_value() = 0;
    virtual void set(float n, float high, float llimit, float ulimit) = 0;
    virtual bool on_off_value() = 0;
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
protected:
    float json_value;
    float *value;
    float std_value;
    float lower, upper, step;
public:
    void set(float val) const { *value = min(max(val, lower), upper); }
    float& get_value() const { return *value; }
    void convert_from_range(float low, float up);
    virtual void *zone();
    virtual void stdJSON_value();
    virtual bool on_off_value();
    virtual void set(float n, float high, float llimit, float ulimit);
    virtual void writeJSON(gx_system::JsonWriter& jw) const;
    virtual void readJSON_value(gx_system::JsonParser& jp);
    virtual bool compareJSON_value();
    virtual void setJSON_value();
    virtual bool hasRange() const;
    virtual float getLowerAsFloat() const;
    virtual float getUpperAsFloat() const;
    virtual float getStepAsFloat() const;
    ParameterV(const string& id, const string& name, ctrl_type ctp, bool preset,
	       float *v, float sv, float lv, float uv, float tv, bool ctrl, bool no_init):
	Parameter(id, name, tp_float, ctp, preset, ctrl),
	value(v ? v : new float()), std_value(sv),lower(lv),upper(uv),step(tv) {
	own_var = !v;
	set(no_init ? *value : sv);
    }
#ifndef NDEBUG
    friend void compare_parameter(const char* title, Parameter* p1,
				  Parameter* p2, bool all);
#endif
    ~ParameterV();
    ParameterV(gx_system::JsonParser& jp);
    virtual void serializeJSON(gx_system::JsonWriter& jw);
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
    float idx_from_id(string v_id);
};

/****************************************************************/

template<>
class ParameterV<int>: public Parameter {
protected:
    int json_value;
    int *value;
    int std_value;
    int lower, upper;
public:
    void set(int val) const { *value = min(max(val, lower), upper); }
    int& get_value() const { return *value; }
    virtual void *zone();
    virtual void stdJSON_value();
    virtual bool on_off_value();
    virtual void set(float n, float high, float llimit, float ulimit);
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
        value(v ? v : new int()), std_value(sv), lower(lv), upper(uv) {
	own_var = !v;
	*value = sv;
    }
    ~ParameterV();
    ParameterV(gx_system::JsonParser& jp);
    virtual void serializeJSON(gx_system::JsonWriter& jw);
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
    bool json_value;
    bool *value;
    bool std_value;
public:
    void set(bool val) const { *value = val; }
    virtual void *zone();
    virtual void stdJSON_value();
    bool& get_value() const { return *value; }
    virtual bool on_off_value();
    virtual void set(float n, float high, float llimit, float ulimit);
    virtual void writeJSON(gx_system::JsonWriter& jw) const;
    virtual bool compareJSON_value();
    virtual void setJSON_value();
    virtual void readJSON_value(gx_system::JsonParser& jp);
    ParameterV(const string& id, const string& name, ctrl_type ctp, bool preset,
                  bool *v, bool sv, bool ctrl):
        Parameter(id, name, tp_bool, ctp, preset, ctrl),
        value(v ? v : new bool()), std_value(sv) {
	own_var = !v;
	*value = sv;
    }
    ~ParameterV();
    ParameterV(gx_system::JsonParser& jp);
    virtual void serializeJSON(gx_system::JsonWriter& jw);
};

/****************************************************************/

/****************************************************************/

class FileParameter: public Parameter {
private:
    Glib::RefPtr<Gio::File> value;
    Glib::RefPtr<Gio::File> std_value;
    Glib::RefPtr<Gio::File> json_value;
    sigc::signal<void> changed;
public:
    sigc::signal<void>& signal_changed() { return changed; }
    void set(const Glib::RefPtr<Gio::File>& val);
    void set_path(const string& path);
    const Glib::RefPtr<Gio::File>& get() const { return value; }
    virtual void *zone();
    virtual void stdJSON_value();
    virtual bool on_off_value();
    virtual void set(float n, float high, float llimit, float ulimit);
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
private:
    Glib::ustring json_value;
    Glib::ustring *value;
    Glib::ustring std_value;
public:
    void set(const Glib::ustring& val) const { *value = val; }
    Glib::ustring& get_value() const { return *value; }
    virtual void *zone();
    virtual void stdJSON_value();
    virtual bool on_off_value();
    virtual void set(float n, float high, float llimit, float ulimit);
    virtual void writeJSON(gx_system::JsonWriter& jw) const;
    virtual bool compareJSON_value();
    virtual void setJSON_value();
    virtual void readJSON_value(gx_system::JsonParser& jp);
    ParameterV(const string& id, const string& name, Glib::ustring *v, const Glib::ustring& sv, bool preset = false)
	: Parameter(id, name, tp_string, None, preset, false),
	  value(v ? v : new Glib::ustring), std_value(sv) {
	own_var = !v;
    }
    ~ParameterV();
    ParameterV(gx_system::JsonParser& jp);
    virtual void serializeJSON(gx_system::JsonWriter& jw);
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

/****************************************************************
 ** ParamMap
 */

class ParamMap: boost::noncopyable {
 private:
    map<string, Parameter*> id_map;
    map<const void*, Parameter*> addr_map;
    bool replace_mode;
#ifndef NDEBUG
    void unique_zone(Parameter* param);
    void unique_id(Parameter* param);
    void check_id(const string& id);
    void check_p(const char *p);
    void check_addr(const void *p);
#endif
    void insert(Parameter* param); // private so we can make sure parameters are owned

 public:
    template<class T> friend class ParameterV;
    ParamMap();
    ~ParamMap();
    void writeJSON(gx_system::JsonWriter& jw);
    void readJSON(gx_system::JsonParser& jp);
    typedef map<string, Parameter*>::const_iterator iterator;
    iterator begin() const { return id_map.begin(); }
    iterator end() const { return id_map.end(); }
    bool hasZone(const void *p) const { return addr_map.find(p) != addr_map.end(); }
    bool hasId(const string& id) const { return id_map.find(id) != id_map.end(); }
    bool hasId(const char *p) const { return id_map.find(p) != id_map.end(); }
    void set_replace_mode(bool mode) { replace_mode = mode; }
    Parameter& operator[](const void *p) {
        debug_check(check_addr, p);
        return *addr_map[p];
    }
    Parameter& operator[](const string& id) {
        debug_check(check_id, id);
        return *id_map[id];
    }
    Parameter& operator[](const char *p) {
        debug_check(check_p, p);
        return *id_map[p];
    }
    void set_init_values();
    void reset_unit(Glib::ustring group_id, const char **groups) const;
    bool unit_has_std_values(Glib::ustring group_id, const char **groups) const;
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
	FloatParameter *p = new FloatParameter(id, "", Parameter::None, preset, val, std, lower, upper, step, false, replace_mode);
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
    Parameter *param;
    float _lower, _upper;
    bool toggle;
 public:
    MidiController(Parameter& p, float l, float u, bool t=false):
        param(&p), _lower(l), _upper(u), toggle(t) {}
    float lower() const { return _lower; }
    float upper() const { return _upper; }
    bool is_toggle() const { return toggle; }
    bool hasParameter(const Parameter& p) const { return *param == p; }
    Parameter& getParameter() const { return *param; }
    static MidiController* readJSON(gx_system::JsonParser&, ParamMap& param);
    void set_midi(int n, int last_value);
    void set(float v, float high) { param->set(v, high, _lower, _upper); }
    void writeJSON(gx_system::JsonWriter& jw) const;
};

typedef list<MidiController> midi_controller_list;

/****************************************************************
**
** MidiControllerList
**/

class MidiControllerList {
 public:
    typedef vector<midi_controller_list> controller_array;
    enum { controller_array_size = 128 };
 private:
    controller_array       map;
    static int             last_midi_control_value[controller_array_size];
    bool                   midi_config_mode;
    int                    last_midi_control;
    volatile gint          program_change;
    Glib::Dispatcher       pgm_chg;
    sigc::signal<void>     changed;
    sigc::signal<void,int> new_program;
    void               on_pgm_chg();
 public:
    MidiControllerList();
    midi_controller_list& operator[](int n) { return map[n]; }
    int size() { return map.size(); }
    void set_config_mode(bool mode, int ctl=-1);
    bool get_config_mode() { return midi_config_mode; }
    int get_current_control() { return last_midi_control; }
    void set_current_control(int ctl) { last_midi_control = ctl; }
    void set_ctr_val(int ctr, int val);
    void deleteParameter(Parameter& param, bool quiet = false);
    void modifyCurrent(Parameter& param, float lower, float upper, bool toggle);
    int param2controller(Parameter& param, const MidiController** p);
    void writeJSON(gx_system::JsonWriter& jw) const;
    static void readJSON(gx_system::JsonParser& jp, ParamMap& param, controller_array& m);
    static controller_array* create_controller_array() {
	return new controller_array(controller_array_size); }
    static int get_last_midi_control_value(unsigned int n) { assert(n < controller_array_size); return last_midi_control_value[n]; }
    static void set_last_midi_control_value(unsigned int n, int v) { assert(n < controller_array_size); last_midi_control_value[n] = v; }
    static void *get_midi_control_zone(unsigned int n) { assert(n < controller_array_size); return &last_midi_control_value[n]; }
    void set_controller_array(const controller_array& m);
    void remove_controlled_parameters(paramlist& plist, const controller_array *m);
    sigc::signal<void>& signal_changed() { return changed; }
    sigc::signal<void,int>& signal_new_program() { return new_program; }
    void compute_midi_in(void* midi_input_port_buf);
    void update_from_controller(int ctr);
    void update_from_controllers();
};

} // namespace gx_gui

#endif  // SRC_HEADERS_GX_PARAMETER_H_


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

namespace gx_gui {

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
    void group_exists(string id);
    void group_is_new(string id);
    friend string param_group(string id, bool nowarn);
#endif

 public:
    ParameterGroups();
    ~ParameterGroups();

    inline string get(string id) { return groups[id]; }
    inline string operator[](string id) {
            debug_check(group_exists, id);
            return groups[id];
        }
    inline void insert(string id, string group) {
            debug_check(group_is_new, id);
            groups.insert(pair<string, string>(id, group));
        }
#ifndef NDEBUG
    void dump();
#endif
};


ParameterGroups& get_group_table();
string param_group(string id, bool nowarn = false);

/****************************************************************
 ** Parameter
 */

template <class T> class ParameterV;

typedef ParameterV<float> FloatParameter;
typedef ParameterV<int> IntParameter;
typedef ParameterV<unsigned int> UIntParameter;
typedef ParameterV<bool> BoolParameter;
typedef ParameterV<string> StringParameter;

class FloatEnumParameter;
class EnumParameter;
class SwitchParameter;
class FileParameter;

/****************************************************************/

class Parameter {
 public:
    enum ctrl_type { None, Continuous, Switch, Enum };
 protected:
    enum value_type { tp_float, tp_int, tp_uint, tp_bool, tp_switch, tp_file, tp_string };
    string _id;
    string _name, _group, _desc;
    enum value_type v_type : 3;
    enum ctrl_type c_type : 3;
    bool save_in_preset : 1;
    bool controllable : 1;
    bool used : 1; // debug
    bool experimental : 1; // experimental faust code, suppress warnings

 public:
    Parameter(string id, string name, value_type vtp, ctrl_type ctp, bool preset,
              bool ctrl, bool exp = false):
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
    virtual ~Parameter();

#ifndef NDEBUG
    bool isUsed() const { return used; }
    void setUsed() { used = true; }
    friend void compare_parameter(const char* title, Parameter* p1,
				  Parameter* p2, bool all);
#endif

    bool isFloat() const { return v_type == tp_float; }
    bool isInt() const { return v_type == tp_int; }
    bool isUInt() const { return v_type == tp_uint; }
    bool isBool() const { return v_type == tp_bool; }
    bool isSwitch() const { return v_type == tp_switch; }
    bool isFile() const { return v_type == tp_file; }
    bool isString() const { return v_type == tp_string; }
    ctrl_type getControlType() const { return c_type; }
    bool isControllable() const { return controllable; }
    bool isInPreset() const { return save_in_preset; }
    bool isExperimental() const { return experimental; }
    const string& id() const { return _id; }
    const string& group() const { return _group; }
    string l_group() const { return gettext(_group.c_str()); }
    const string& name() const { return _name; }
    string l_name() const { return gettext(_name.c_str()); }
    const string& desc() const { return _desc; }
    void set_desc(string desc) { _desc = desc; }
    string l_desc() const { return gettext(_desc.c_str()); }
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
    virtual const value_pair *getValueNames() const;
    static inline const char *value_label(const value_pair& vp) {
	return gettext(vp.value_label ? vp.value_label : vp.value_id);
    }
    FloatParameter& getFloat();
    IntParameter& getInt();
    UIntParameter& getUInt();
    BoolParameter& getBool();
    SwitchParameter& getSwitch();
    FileParameter &getFile();
    StringParameter &getString();
};

#ifndef NDEBUG
void compare_parameter(const char* title, Parameter* p1,
		       Parameter* p2, bool all = false);
#endif

/****************************************************************/

typedef list<gx_gui::Parameter*> paramlist;

/****************************************************************/

template<class T>
class ParameterV: public Parameter {
};

template<>
class ParameterV<float>: public Parameter {
protected:
    float json_value;
public:
    float &value;
    float std_value;
    float lower, upper, step;
    void set(float val) const { value = min(max(val, lower), upper); }
    void convert_from_range(float low, float up);
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
    ParameterV(string id, string name, ctrl_type ctp, bool preset,
	       float &v, float sv, float lv, float uv, float tv, bool ctrl, bool exp = false):
	Parameter(id, name, tp_float, ctp, preset, ctrl, exp), value(v), std_value(sv), lower(lv),
	upper(uv), step(tv) {}
#ifndef NDEBUG
    friend void compare_parameter(const char* title, Parameter* p1,
				  Parameter* p2, bool all);
#endif
};


/****************************************************************/

class FloatEnumParameter: public FloatParameter {
 private:
    const value_pair* value_names;
 public:
    virtual void writeJSON(gx_system::JsonWriter& jw);
    virtual void readJSON_value(gx_system::JsonParser& jp);
    virtual const value_pair *getValueNames() const;
    FloatEnumParameter(string id, string name, const value_pair* vn, bool preset, float &v,
                       int sv, bool ctrl, bool exp = false);
};

/****************************************************************/

template<>
class ParameterV<int>: public Parameter {
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
    ParameterV(string id, string name, ctrl_type ctp, bool preset,
	       int &v, int sv, int lv, int uv, bool ctrl, bool exp = false):
	Parameter(id, name, tp_int, ctp, preset, ctrl, exp),
        value(v), std_value(sv), lower(lv), upper(uv)
        {}
};

/****************************************************************/

class EnumParameter: public IntParameter {
 private:
    const value_pair* value_names;
 public:
    virtual void writeJSON(gx_system::JsonWriter& jw);
    virtual void readJSON_value(gx_system::JsonParser& jp);
    virtual const value_pair *getValueNames() const;
    EnumParameter(string id, string name, const value_pair* vn, bool preset, int &v,
                  int sv, bool ctrl, bool exp = false);
};

/****************************************************************/

template<>
class ParameterV<unsigned int>: public Parameter {
 protected:
    unsigned int json_value;
 public:
    unsigned int &value;
    unsigned int std_value;
    unsigned int lower, upper;
    void set(unsigned int val) const { value = min(max(val, lower), upper); }
    virtual void *zone();
    virtual void set_std_value();
    virtual void set(int n, int high, float llimit, float ulimit);
    virtual void writeJSON(gx_system::JsonWriter& jw);
    virtual void readJSON_value(gx_system::JsonParser& jp);
    virtual void setJSON_value();
    virtual bool hasRange() const;
    virtual float getLowerAsFloat() const;
    virtual float getUpperAsFloat() const;
    ParameterV(string id, string name, ctrl_type ctp, bool preset,
	       unsigned int &v, unsigned int sv, unsigned int lv,
	       unsigned int uv, bool ctrl, bool exp = false):
        Parameter(id, name, tp_int, ctp, preset, ctrl, exp),
        value(v), std_value(sv), lower(lv), upper(uv)
        {}
};

/****************************************************************/

class UEnumParameter: public UIntParameter {
 private:
    const value_pair* value_names;
 public:
    virtual void writeJSON(gx_system::JsonWriter& jw);
    virtual void readJSON_value(gx_system::JsonParser& jp);
    virtual const value_pair *getValueNames() const;
    UEnumParameter(string id, string name, const value_pair* vn, bool preset, unsigned int &v,
                  unsigned int sv, bool ctrl, bool exp = false);
};

/****************************************************************/

template<>
class ParameterV<bool>: public Parameter {
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
    ParameterV(string id, string name, ctrl_type ctp, bool preset,
                  bool &v, bool sv, bool ctrl, bool exp = false):
        Parameter(id, name, tp_bool, ctp, preset, ctrl, exp),
        value(v), std_value(sv)
        {}
};

/****************************************************************/

class SwitchParameter: public Parameter {
 private:
    bool value;
    bool std_value;
    bool json_value;
    sigc::signal<void, bool> changed;
 public:
    sigc::signal<void, bool>& signal_changed() { return changed; }
    void set(bool val);
    bool get() const { return value; }
    virtual void *zone();
    virtual void set_std_value();
    virtual void set(int n, int high, float llimit, float ulimit);
    virtual void writeJSON(gx_system::JsonWriter& jw);
    virtual void readJSON_value(gx_system::JsonParser& jp);
    virtual void setJSON_value();
    SwitchParameter(string id, bool preset = false, bool sv = false):
        Parameter(id, "", tp_switch, Switch, preset, false),
        value(sv), std_value(sv), json_value(), changed() {}
};

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
    virtual void set_std_value();
    virtual void set(int n, int high, float llimit, float ulimit);
    virtual void writeJSON(gx_system::JsonWriter& jw);
    virtual void readJSON_value(gx_system::JsonParser& jp);
    virtual void setJSON_value();
    FileParameter(string id, string filename, bool preset = false):
        Parameter(id, "", tp_file, None, preset, false),
        value(Gio::File::create_for_path(filename)),
        std_value(value->dup()) {}
    FileParameter(string id, bool preset = false):
        Parameter(id, "", tp_file, None, preset, false),
        value(0),
        std_value(0) {}
    void set_standard(const string& filename);
    bool is_equal(const Glib::RefPtr<Gio::File>& v) const;
    bool is_standard() const { return is_equal(std_value); }
    string get_path();
    string get_directory_path();
    string get_parse_name();
    string get_display_name();
    void copy(const string& destination);
};

/****************************************************************/

template<>
class ParameterV<string>: public Parameter {
 private:
    string json_value;
 public:
    string &value;
    string std_value;
    void set(string val) const { value = val; }
    virtual void *zone();
    virtual void set_std_value();
    virtual void set(int n, int high, float llimit, float ulimit);
    virtual void writeJSON(gx_system::JsonWriter& jw);
    virtual void setJSON_value();
    virtual void readJSON_value(gx_system::JsonParser& jp);
    ParameterV(string id, string name, string &v, string sv):
        Parameter(id, name, tp_bool, None, false, false, false),
        value(v), std_value(sv)
        {}
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

inline UIntParameter &Parameter::getUInt() {
    assert(isInt());
    return static_cast<UIntParameter&>(*this);
}

inline BoolParameter &Parameter::getBool() {
    assert(isBool());
    return static_cast<BoolParameter&>(*this);
}

inline SwitchParameter &Parameter::getSwitch() {
    assert(isSwitch());
    return static_cast<SwitchParameter&>(*this);
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

class ParamMap {
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
    ParamMap();
    ~ParamMap();
    typedef map<string, Parameter*>::iterator iterator;
    iterator begin() { return id_map.begin(); }
    iterator end() { return id_map.end(); }
    bool hasZone(const void *p) const { return addr_map.find(p) != addr_map.end(); }
    bool hasId(string id) const { return id_map.find(id) != id_map.end(); }
    bool hasId(const char *p) const { return id_map.find(p) != id_map.end(); }
    Parameter& operator[](const void *p) {
        debug_check(check_addr, p);
        return *addr_map[p];
    }
    Parameter& operator[](string id) {
        debug_check(check_id, id);
        return *id_map[id];
    }
    Parameter& operator[](const char *p) {
        debug_check(check_p, p);
        return *id_map[p];
    }
    void insert(Parameter* param);
    void set_init_values();
#ifndef NDEBUG
    void dump();
#endif
};

extern ParamMap parameter_map; // map id -> parameter, zone -> parameter

/****************************************************************/

inline void registerParam(const char*a, const char*b, float*c, float std,
                          float lower, float upper, float step) {
    parameter_map.insert(new FloatParameter(a, b, Parameter::Continuous, true, *c, std,
                         lower, upper, step, true));
}

inline void registerParam(const char*a, const char*b, float*c, float std = 0) {
    parameter_map.insert(new FloatParameter(a, b, Parameter::Switch, true, *c, std,
                         0, 1, 1, true));
}

inline void registerParam(const char*a, const char*b, bool*c, bool d = false, bool exp = false) {
    parameter_map.insert(new BoolParameter(a, b, Parameter::Switch, true, *c, d, true, exp));
}

inline void registerEnumParam(const char*a, const char*b, const value_pair* vl, int*c, int std = 0,
                              bool exp = false) {
    gx_gui::parameter_map.insert(new gx_gui::EnumParameter(a, b, vl, true, *c, std,
                                 true, exp)); // false == no_midi_var
}

inline void registerUEnumParam(const char*a, const char*b, const value_pair* vl, unsigned int*c, unsigned int std = 0,
                              bool exp = false) {
    gx_gui::parameter_map.insert(new gx_gui::UEnumParameter(a, b, vl, true, *c, std,
                                 true, exp)); // false == no_midi_var
}

inline void registerNonMidiParam(const char*a, bool*c, bool d, bool std = false) {
    parameter_map.insert(new BoolParameter(a, "", Parameter::None, d, *c, std, false, false));
}

inline void registerNonMidiParam(const char*a, int*c, bool d, int std, int lower, int upper) {
    parameter_map.insert(new IntParameter(a, "", Parameter::None, d, *c, std, lower, upper, false, false));
}

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
        modstring(string n, bool m, const char* s): name(n), modified(m), std(s) {}
        explicit modstring(const char* n): name(n), modified(false), std(n) {}
        modstring(): name(""), modified(false), std(0) {}
    };
    map<int, modstring> m;

 public:
    MidiStandardControllers();
    const string operator[](int ctr) { return m[ctr].name; }
    void replace(int ctr, string name);
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
    Parameter &param;
    float _lower, _upper;
 public:
    MidiController(Parameter &p, float l, float u):
        param(p), _lower(l), _upper(u) {}
    float lower() const { return _lower; }
    float upper() const { return _upper; }
    MidiController& operator = (MidiController m) {
        param = m.param;
        _lower = m._lower;
        _upper = m._upper;
	return *this;
    }
    bool hasParameter(const Parameter& p) const { return param == p; }
    Parameter& getParameter() const { return param; }
    static MidiController* readJSON(gx_system::JsonParser&);
    void set(int n) { param.set(n, 127, _lower, _upper); }
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
    bool                   midi_config_mode;
    int                    last_midi_control;
    int                    last_midi_control_value;
    volatile gint          program_change;
    sem_t                  program_change_sem;
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
    void modifyCurrent(Parameter& param, float lower, float upper);
    int param2controller(Parameter& param, const MidiController** p);
    void writeJSON(gx_system::JsonWriter& jw);
    void readJSON(gx_system::JsonParser& jp, controller_array& m);
    void set_controller_array(const controller_array& m);
    void remove_controlled_parameters(paramlist& plist, const controller_array *m);
    sigc::signal<void>& signal_changed() { return changed; }
    sigc::signal<void,int>& signal_new_program() { return new_program; }
    void compute_midi_in(void* midi_input_port_buf);
};

extern MidiControllerList controller_map; // map ctrl num -> controlled parameters

} // namespace gx_gui

#endif  // SRC_HEADERS_GX_PARAMETER_H_


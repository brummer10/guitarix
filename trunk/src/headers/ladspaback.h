/*
 * Copyright (C) 2012, 2013 Andreas Degert, Hermann Meyer
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
 */

#include <ladspa.h>

namespace ladspa {

/****************************************************************
 ** PortDesc
 */

enum DisplayType {
    tp_scale, tp_scale_log, tp_toggle, tp_enum, tp_display, tp_display_toggle, tp_none, tp_int,
};

class ChangeableValues {
public:
    enum { name_set = 0x01, dflt_set = 0x02, low_set = 0x04, up_set = 0x08, tp_set = 0x10, newrow_set = 0x20 };
private:
    Glib::ustring name;
    float dflt;
    float low;
    float up;
    DisplayType tp;
    std::map<int, Glib::ustring> enumdict;
    bool newrow;
    int set_flags;
    inline void sf(int f) { set_flags |= f; }
    friend bool operator!=(const ChangeableValues& v1, const ChangeableValues& v2);
public:
    ChangeableValues(): name(), dflt(), low(), up(), tp(tp_scale), enumdict(), newrow(), set_flags(0) {}
    ChangeableValues(gx_system::JsonParser& jp);
    void serializeJSON(gx_system::JsonWriter& jw);
    int get_excl_flags(DisplayType tp) const;
    bool has_settings(DisplayType tp) const;
    inline bool is_set(int f) const { return set_flags & f; }
    inline void unset(int f) { set_flags &= ~f; }
    inline void set_name(const Glib::ustring& nm) { name = nm; sf(name_set); }
    inline void set_dflt(float v) { dflt = v; sf(dflt_set); }
    inline void set_low(float v) { low = v; sf(low_set); }
    inline void set_up(float v) { up = v; sf(up_set); }
    inline void set_tp(DisplayType v) { tp = v; sf(tp_set); }
    inline void set_newrow(bool v) { newrow = v; sf(newrow_set); }
    inline const Glib::ustring& get_name() { return name; }
    inline float get_dflt() { return dflt; }
    inline float get_low() { return low; }
    inline float get_up() { return up; }
    inline DisplayType get_tp() { return tp; }
    inline bool get_newrow() { return newrow; }
    inline bool has_enumkey(int k) { return enumdict.find(k) != enumdict.end(); }
    void set_enumvalue(int k, const Glib::ustring& v) { enumdict[k] = v; }
    inline std::map<int, Glib::ustring>::iterator find_enum(int k) { return enumdict.find(k); }
    inline void erase_enum(int k) { enumdict.erase(enumdict.find(k)); }
    inline std::map<int, Glib::ustring>::iterator enum_end() { return enumdict.end(); }
};

enum step_mode {
    stp_coarse,
    stp_normal,
    stp_fine,
};

class PortDesc {
private:
public:
    int idx;
    int pos;
    bool is_output;
    LADSPA_PortRangeHintDescriptor hint_desc;
    bool fake_low;
    bool fake_up;
    bool fake_dflt;
    step_mode step;
    bool use_sr;
    bool has_sr;
    bool has_caption;
    ChangeableValues factory;
    ChangeableValues user;
    static const int SR = 44100;
public:
    void set_range_default(const LADSPA_PortRangeHint& h, ChangeableValues& store);
    void set_default_value(const LADSPA_PortRangeHint& h, ChangeableValues& store);
    void set_tp_default(const LADSPA_PortRangeHint& h, ChangeableValues& store);
    float calc_step();
    void set_default(float value, Glib::ustring label);
    void output(gx_system::JsonWriter& jw);
    friend bool cmp_ctrl_ports(const PortDesc *a, const PortDesc *b);
public:
    PortDesc(int idx_, int pos_, bool is_output_, Glib::ustring name, const LADSPA_PortRangeHint& hint);
    PortDesc(gx_system::JsonParser& jp);
    void serializeJSON(gx_system::JsonWriter& jw);
    void reset();
    void fixup(bool newrow);
    bool check_changed(const PortDesc& vp) const;
    Glib::ustring get_enum(int idx);
    inline DisplayType get_tp() { return user.is_set(ChangeableValues::tp_set) ? user.get_tp() : factory.get_tp(); }
    inline float get_low() { return user.is_set(ChangeableValues::low_set) ? user.get_low() : factory.get_low(); }
    inline float get_up() { return user.is_set(ChangeableValues::up_set) ? user.get_up() : factory.get_up(); }
    inline float get_dflt() { return user.is_set(ChangeableValues::dflt_set) ? user.get_dflt() : factory.get_dflt(); }
    inline bool get_newrow() { return user.is_set(ChangeableValues::newrow_set) ? user.get_newrow() : factory.get_newrow(); }
    const Glib::ustring& get_name() { return user.is_set(ChangeableValues::name_set) ? user.get_name() : factory.get_name(); }
    inline int get_pos() { return pos; }
    void set_low(float v);
    void set_up(float v);
    void set_dflt(float v);
    void set_tp(DisplayType v);
    void set_newrow(bool v);
    bool has_settings();
    bool enumkey_changed(int k) { return user.has_enumkey(k); }
    bool is_set(int f) { return user.is_set(f); }
    void set_state(gx_system::JsonParser& jp, int version);
};


/****************************************************************
 ** class PluginDesc
 */

class PluginDesc {
public:
    unsigned long UniqueID;
    Glib::ustring Label;
    Glib::ustring Name;
    Glib::ustring shortname;
    Glib::ustring Maker;
    int MasterIdx;
    Glib::ustring MasterLabel;
    int tp;
    std::vector<PortDesc*> ctrl_ports;
    std::string path;
    int index;
    Glib::ustring category;
    Glib::ustring deduced_category;
    int quirks;
    int quirks_default;
    std::string ladspa_category;
    bool active;
    bool active_set;
    bool has_settings;
    int add_wet_dry;
    PluginDesc *old;
public:
    int quirks_get();
    void reset();
    bool check_changed();
    bool _i_check_has_settings();
    void check_has_settings();
    int set_active(bool v);
    void fixup();
    void set_add_wet_dry_controller(bool v);
    void copy_ports(PluginDesc *p);
    void set_category(const std::vector<Glib::ustring>& s);
    void set_default(int idx, float value, const Glib::ustring& label);
    void set_state(const Glib::ustring& fname);
private:
    PluginDesc(const LADSPA_Descriptor& desc, int tp_, std::vector<PortDesc*>& ctrl_ports_, const std::string path_, int index_);
    PluginDesc(gx_system::JsonParser& jp);
    ~PluginDesc();
    void serializeJSON(gx_system::JsonWriter& jw);
    friend class LadspaPluginList;
public:
    void set_old();
    void clear_old() { delete old; old = 0; }
    void output_entry(gx_system::JsonWriter& jw);
    void output(gx_system::JsonWriter& jw);
};


/****************************************************************
 ** class LadspaPluginList
 */

class LadspaPluginList: private std::vector<PluginDesc*> {
private:
    typedef std::map<unsigned long, PluginDesc*> pluginmap;
    static void add_plugin(const LADSPA_Descriptor& desc, pluginmap& d, const std::string& path, int index);
    static void load_defs(const std::string& path, pluginmap& d);
    static void set_instances(const char *uri, pluginmap& d, std::vector<Glib::ustring>& label,
			      std::vector<unsigned long>& not_found, std::set<unsigned long>& seen);
    static void descend(const char *uri, pluginmap& d,
			std::vector<unsigned long>& not_found, std::set<unsigned long>& seen,
			std::vector<Glib::ustring>& base);
public:
    LadspaPluginList(): std::vector<PluginDesc*>() {}
    ~LadspaPluginList();
    void readJSON(gx_system::JsonParser& jp);
    void writeJSON(gx_system::JsonWriter& jw);
    void load(gx_system::CmdlineOptions& options, std::vector<unsigned long>& old_not_found);
    void save(gx_system::CmdlineOptions& options);
    using std::vector<PluginDesc*>::begin;
    using std::vector<PluginDesc*>::end;
};

} // namespace ladspa

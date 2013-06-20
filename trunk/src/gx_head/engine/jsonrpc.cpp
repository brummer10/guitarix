/*
 * Copyright (C) 2013 Andreas Degert
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

#include "jsonrpc.h"

#include "jsonrpc_methods.cc"

const char *engine_state_to_string(gx_engine::GxEngineState s) {
    switch (s) {
    case gx_engine::kEngineOff: return "stopped";
    case gx_engine::kEngineOn: return "running";
    case gx_engine::kEngineBypass: return "bypassed";
    }
    assert(false);
    return 0;
}

gx_engine::GxEngineState string_to_engine_state(const std::string& s) {
    if (s == "stopped") {
	return gx_engine::kEngineOff;
    }
    if (s == "running") {
	return gx_engine::kEngineOn;
    }
    if (s == "bypassed") {
	return gx_engine::kEngineBypass;
    }
    assert(false);
    return gx_engine::kEngineOff;
}

class RpcError: public exception {
public:
    int code;
    Glib::ustring message;
public:
    RpcError(int code_, Glib::ustring message_): code(code_), message(message_) {}
    ~RpcError() throw() { }
    virtual const char* what() const throw() { return message.c_str(); }
};


class JsonString: public JsonValue {
private:
    Glib::ustring string;
    JsonString(Glib::ustring s): JsonValue(), string(s) {}
    ~JsonString() {}
    friend class JsonArray;
    virtual const Glib::ustring& getString() const;
};

class JsonFloat: public JsonValue {
private:
    double value;
    JsonFloat(double v): value(v) {}
    ~JsonFloat() {}
    friend class JsonArray;
    virtual double getFloat() const;
};

class JsonInt: public JsonValue {
private:
    int value;
    JsonInt(int v): value(v) {}
    ~JsonInt() {}
    friend class JsonArray;
    virtual double getFloat() const;
    virtual int getInt() const;
};

JsonArray::~JsonArray() {
    for (iterator i = begin(); i != end(); ++i) {
	delete *i;
    }
}

JsonValue *JsonArray::operator[](unsigned int i) {
    if (i >= size()) {
	throw RpcError(-32602, "Invalid param -- wrong argument count");
    }
    return std::vector<JsonValue*>::operator[](i);
}

void JsonArray::append(gx_system::JsonParser& jp) {
    if (jp.peek() == gx_system::JsonParser::value_string) {
	jp.next();
	push_back(new JsonString(jp.current_value()));
    } else if (jp.peek() == gx_system::JsonParser::value_number) {
	jp.next();
	const char *str = jp.current_value().c_str();
	char *endptr;
	int n = strtol(str, &endptr, 10);
	if (*endptr == '\0') {
	    push_back(new JsonInt(n));
	} else {
	    istringstream b(str);
	    float f;
	    b >> f;
	    push_back(new JsonFloat(f));
	}
    } else {
	throw gx_system::JsonException("unexpected token");
    }
}

double JsonValue::getFloat() const {
    throw RpcError(-32602, "Invalid param -- float expected");
}

int JsonValue::getInt() const {
    throw RpcError(-32602, "Invalid param -- int expected");
}

const Glib::ustring& JsonValue::getString() const {
    throw RpcError(-32602, "Invalid param -- string expected");
}

double JsonFloat::getFloat() const {
    return value;
}

double JsonInt::getFloat() const {
    return value;
}

int JsonInt::getInt() const {
    return value;
}

const Glib::ustring& JsonString::getString() const {
    return string;
}


/****************************************************************
 ** class UiBuilderVirt
 */

class CmdConnection;

class UiBuilderVirt: public UiBuilder {
private:
    static gx_system::JsonWriter *jw;
    static void openTabBox_(const char* label);
    static void openVerticalBox_(const char* label);
    static void openVerticalBox1_(const char* label);
    static void openVerticalBox2_(const char* label);
    static void openHorizontalBox_(const char* label);
    static void openHorizontalhideBox_(const char* label);
    static void insertSpacer_();
    static void set_next_flags_(int flags);
    static void create_small_rackknob_(const char *id, const char *label);
    static void create_small_rackknobr_(const char *id, const char *label);
    static void create_master_slider_(const char *id, const char *label);
    static void create_selector_no_caption_(const char *id);
    static void create_selector_(const char *id, const char *label);
    static void create_spin_value_(const char *id, const char *label);
    static void create_switch_no_caption_(const char *sw_type,const char * id);
    static void create_switch_(const char *sw_type,const char * id, const char *label);
    static void create_port_display_(const char *id, const char *label);
    static void closeBox_();
    static void load_glade_(const char *data);
public:
    UiBuilderVirt(gx_system::JsonWriter *jw);
    ~UiBuilderVirt();
};


/****************************************************************
 ** class CmdConnection
 */

const static int InterfaceVersionMajor = 1;
const static int InterfaceVersionMinor = 0;

CmdConnection::CmdConnection(MyService& serv_, const Glib::RefPtr<Gio::SocketConnection>& connection_)
    : serv(serv_),
      connection(connection_),
      parameter_change_notify(false),
      conn_preset_changed(),
      conn_state_changed(),
      conn_freq_changed(),
      conn_display(),
      conn_display_state(),
      conn_selection_done(),
      conn_presetlist_changed(),
      conn_log_message() {
    jp.start_parser();
}

CmdConnection::~CmdConnection() {
}

void CmdConnection::listen(const Glib::ustring& tp) {
    bool all = (tp == "all");
    if (all || tp == "preset") {
	conn_preset_changed = serv.settings.signal_selection_changed().connect(
	    sigc::mem_fun(*this, &CmdConnection::preset_changed));
    }
    if (all || tp == "state") {
	conn_state_changed = serv.jack.get_engine().signal_state_change().connect(
	    sigc::mem_fun(*this, &CmdConnection::on_engine_state_change));
    }
    if (all || tp == "freq") {
	conn_freq_changed = serv.jack.get_engine().tuner.signal_freq_changed().connect(
	    sigc::mem_fun(this, &CmdConnection::on_tuner_freq_changed));
    }
    if (all || tp == "display") {
	conn_display = serv.tuner_switcher.signal_display().connect(
	    sigc::mem_fun(this, &CmdConnection::display));
	conn_display_state = serv.tuner_switcher.signal_set_state().connect(
	    sigc::mem_fun(this, &CmdConnection::set_display_state));
    }
    if (all || tp == "tuner") {
	conn_selection_done = serv.tuner_switcher.signal_selection_done().connect(
	    sigc::mem_fun(this, &CmdConnection::on_selection_done));
    }
    if (all || tp == "presetlist_changed") {
	conn_presetlist_changed = serv.settings.signal_presetlist_changed().connect(
	    sigc::mem_fun(this, &CmdConnection::on_presetlist_changed));
    }
    if (all || tp == "logger") {
	conn_log_message = gx_system::Logger::get_logger().signal_message().connect(
	    sigc::mem_fun(this, &CmdConnection::on_log_message));
	gx_system::Logger::get_logger().unplug_queue();
    }
    if (all || tp == "param") {
	parameter_change_notify = true;
    }
}

void CmdConnection::unlisten(const Glib::ustring& tp) {
    bool all = (tp == "all");
    if (all || tp == "preset") {
	conn_preset_changed.disconnect();
    }
    if (all || tp == "state") {
	conn_state_changed.disconnect();
    }
    if (all || tp == "freq") {
	conn_freq_changed.disconnect();
    }
    if (all || tp == "display") {
	conn_display.disconnect();
	conn_display_state.disconnect();
    }
    if (all || tp == "tuner") {
	conn_selection_done.disconnect();
    }
    if (all || tp == "presetlist_changed") {
	conn_presetlist_changed.disconnect();
    }
    if (all || tp == "logger") {
	conn_log_message.disconnect();
    }
}

void CmdConnection::on_log_message(const string& msg, gx_system::GxMsgType tp, bool plugged) {
    const char *tpname;
    switch (tp) {
    case gx_system::kInfo:    tpname = "info"; break;
    case gx_system::kWarning: tpname = "warning"; break;
    case gx_system::kError:   tpname = "error"; break;
    default: tpname = "unknown"; break;
    }
    if (!plugged) {
	gx_system::JsonStringWriter jw;
	send_notify_begin(jw, "message");
	jw.write(tpname);
	jw.write(msg);
	send_notify_end(jw);
    }
}

void CmdConnection::send_notify_begin(gx_system::JsonWriter& jw, const char *method) {
    jw.begin_object();
    jw.write_key("jsonrpc");
    jw.write("2.0");
    jw.write_key("method");
    jw.write(method);
    jw.write_key("params");
    jw.begin_array();
}

void CmdConnection::send_notify_end(gx_system::JsonStringWriter& jw, bool send_out) {
    jw.end_array();
    jw.end_object();
    if (send_out) {
	send(jw);
    }
}

void CmdConnection::write_engine_state(gx_system::JsonWriter& jw, gx_engine::GxEngineState s) {
    jw.write(engine_state_to_string(s));
}

void CmdConnection::on_selection_done() {
    gx_system::JsonStringWriter jw;
    send_notify_begin(jw, "show_tuner");
    jw.write(serv.tuner_switcher.deactivate());
    send_notify_end(jw);
}

void CmdConnection::on_presetlist_changed() {
    gx_system::JsonStringWriter jw;
    send_notify_begin(jw, "presetlist_changed");
    send_notify_end(jw);
}

void CmdConnection::on_engine_state_change(gx_engine::GxEngineState state) {
    gx_system::JsonStringWriter jw;
    send_notify_begin(jw, "state_changed");
    write_engine_state(jw, state);
    send_notify_end(jw);
}

void CmdConnection::preset_changed() {
    gx_system::JsonStringWriter jw;
    send_notify_begin(jw, "preset_changed");
    if (serv.settings.setting_is_preset()) {
	jw.write(serv.settings.get_current_bank());
	jw.write(serv.settings.get_current_name());
    }
    send_notify_end(jw);
}

void CmdConnection::on_tuner_freq_changed() {
    gx_system::JsonStringWriter jw;
    send_notify_begin(jw, "tuner_changed");
    //jw.write_key("frequency");
    jw.write(serv.jack.get_engine().tuner.get_freq());
    //jw.write_key("note");
    jw.write(serv.jack.get_engine().tuner.get_note());
    send_notify_end(jw);
}

void CmdConnection::display(const Glib::ustring& bank, const Glib::ustring& preset) {
    gx_system::JsonStringWriter jw;
    send_notify_begin(jw, "display_bank_preset");
    jw.write(bank);
    jw.write(preset);
    send_notify_end(jw);
}

void CmdConnection::set_display_state(TunerSwitcher::SwitcherState state) {
    gx_system::JsonStringWriter jw;
    send_notify_begin(jw, "set_display_state");
    switch (state) {
    case TunerSwitcher::normal_mode: jw.write("normal_mode"); break;
    case TunerSwitcher::wait_start: jw.write("wait_start"); break;
    case TunerSwitcher::listening: jw.write("listening"); break;
    case TunerSwitcher::wait_stop: jw.write("wait_stop"); break;
    default: assert(false); break;
    }
    send_notify_end(jw);
}

static void write_plugin_state(gx_system::JsonWriter& jw, gx_engine::Plugin *i) {
    jw.begin_object();
    jw.write_key("id");
    jw.write(i->get_pdef()->id);
    jw.write_key("on_off");
    jw.write(i->get_on_off());
    jw.write_key("box_visible");
    jw.write(i->get_box_visible());
    jw.write_key("position");
    jw.write(i->get_position());
    jw.write_key("post_pre");
    jw.write(i->get_effect_post_pre());
    jw.write_key("stereo");
    jw.write((i->get_pdef()->flags & PGN_STEREO) == PGN_STEREO);
    const char *p;
    p = i->get_pdef()->category;
    if (p) {
	jw.write_key("category");
	jw.write(p);
    }
    p = i->get_pdef()->name;
    if (p) {
	jw.write_key("name");
	jw.write(p);
    }
    p = i->get_pdef()->shortname;
    if (p) {
	jw.write_key("shortname");
	jw.write(p);
    }
    p = i->get_pdef()->description;
    if (p) {
	jw.write_key("description");
	jw.write(p);
    }
    jw.end_object();
}

static void write_parameter_state(gx_system::JsonWriter& jw, const gx_engine::Parameter& p) {
    jw.begin_object();
    if (p.hasRange()) {
	jw.write_key("lower_bound");
	jw.write(p.getLowerAsFloat());
	jw.write_key("upper_bound");
	jw.write(p.getUpperAsFloat());
	jw.write_key("step");
	jw.write(p.getStepAsFloat());
    }
    const value_pair *pairs = p.getValueNames();
    if (pairs) {
	jw.write_key("value_names");
	jw.begin_array();
	for (; pairs->value_id; pairs++) {
	    jw.begin_array();
	    jw.write(pairs->value_id);
	    jw.write(p.value_label(*pairs));
	    jw.end_array();
	}
	jw.end_array();
    }
    jw.write_key("name");
    jw.write(p.l_name());
    jw.write_key("group");
    jw.write(p.l_group());
    jw.write_key("type");
    jw.write(p.get_typename());
    gx_engine::Parameter::ctrl_type t = p.getControlType();
    if (t == gx_engine::Parameter::Continuous) {
	jw.write_key("ctl_continous");
	jw.write(1);
    } else if (t == gx_engine::Parameter::Switch) {
	jw.write_key("ctl_switch");
	jw.write(1);
    } else if (t == gx_engine::Parameter::Enum) {
	jw.write_key("ctl_enum");
	jw.write(1);
    }
    jw.write_key("value");
    jw.begin_object();
    p.writeJSON(jw);
    jw.end_object();
    jw.end_object();
}

static inline bool unit_match(const Glib::ustring& id, const Glib::ustring& prefix, const char** gl) {
    if (id.compare(0, prefix.size(), prefix) == 0) {
	return true;
    }
    if (!gl) {
	return false;
    }
    while (*gl) {
	const char *p = *gl;
	if (p[0] == '.') {
	    p += 1;
	    int n = strlen(p);
	    if (strncmp(id.c_str(), p, n) == 0 && id[n] == '.') {
		return true;
	    }
	}
	gl += 2;
    }
    return false;
}

#define START_FUNCTION_SWITCH(v)    switch (v) {
#define FUNCTION(n)                 break; case RPCM_##n:
#define END_FUNCTION_SWITCH(s)      break; default: s; }

void CmdConnection::call(gx_system::JsonWriter& jw, const methodnames *mn, JsonArray& params) {
    static const char *cmds[] = {
	"get","set","banks","presets","setpreset","getstate","setstate",
	"switch_tuner","get_tuning","get_max_input_level","get_max_output_level",
	"shutdown","stop","rtload","desc","list","get_parameter","help",
	0
    };

    START_FUNCTION_SWITCH(mn->m_id);

    FUNCTION(get) {
	gx_engine::ParamMap& param = serv.settings.get_param();
	jw.begin_object();
	for (JsonArray::iterator i = params.begin(); i != params.end(); ++i) {
	    const Glib::ustring& attr = (*i)->getString();
	    if (!param.hasId(attr)) {
		jw.write_key(attr);
		if (attr == "sys.active_mono_plugins") {
		    list<gx_engine::Plugin*> l;
		    serv.jack.get_engine().pluginlist.ordered_mono_list(l, PGN_MODE_NORMAL);
		    jw.begin_array();
		    for (list<gx_engine::Plugin*>::iterator i = l.begin(); i != l.end(); ++i) {
			write_plugin_state(jw, *i);
		    }
		    jw.end_array();
		} else if (attr == "sys.active_stereo_plugins") {
		    list<gx_engine::Plugin*> l;
		    serv.jack.get_engine().pluginlist.ordered_stereo_list(l, PGN_MODE_NORMAL);
		    jw.begin_array();
		    for (list<gx_engine::Plugin*>::iterator i = l.begin(); i != l.end(); ++i) {
			write_plugin_state(jw, *i);
		    }
		    jw.end_array();
		} else if (attr == "sys.visible_mono_plugins") {
		    list<gx_engine::Plugin*> l;
		    const int bits = (PGN_GUI|gx_engine::PGNI_DYN_POSITION);
		    serv.jack.get_engine().pluginlist.ordered_list(l, false, bits, bits);
		    jw.begin_array();
		    for (list<gx_engine::Plugin*>::iterator i = l.begin(); i != l.end(); ++i) {
			write_plugin_state(jw, *i);
		    }
		    jw.end_array();
		} else if (attr == "sys.visible_stereo_plugins") {
		    list<gx_engine::Plugin*> l;
		    const int bits = (PGN_GUI|gx_engine::PGNI_DYN_POSITION);
		    serv.jack.get_engine().pluginlist.ordered_list(l, true, bits, bits);
		    jw.begin_array();
		    for (list<gx_engine::Plugin*>::iterator i = l.begin(); i != l.end(); ++i) {
			write_plugin_state(jw, *i);
		    }
		    jw.end_array();
		} else {
		    jw.write("unknown");
		}
		continue;
	    }
	    param[attr].writeJSON(jw);
	}
	jw.end_object();
    }

    FUNCTION(parameterlist) {
	serv.settings.get_param().writeJSON(jw);
    }

    FUNCTION(pluginlist) {
	serv.jack.get_engine().pluginlist.writeJSON(jw);
    }

    FUNCTION(plugin_load_ui) {
	PluginDef *pd = serv.jack.get_engine().pluginlist.lookup_plugin(params[0]->getString().c_str())->get_pdef();
	if (!pd->load_ui) {
	    jw.write_null();
	} else {
	    UiBuilderVirt bld(&jw);
	    jw.begin_array();
	    pd->load_ui(bld);
	    jw.end_array();
	}
    }

    FUNCTION(get_rack_unit_order) {
	std::vector<std::string>& ul = serv.settings.get_rack_unit_order(params[0]->getInt());
	jw.begin_array();
	for (std::vector<std::string>::iterator i = ul.begin(); i != ul.end(); ++i) {
	    jw.write(*i);
	}
	jw.end_array();
    }

    FUNCTION(get_parameter) {
	gx_engine::ParamMap& param = serv.settings.get_param();
	jw.begin_object();
	if (params.size() == 0) {
	    for (gx_engine::ParamMap::iterator i = param.begin(); i != param.end(); ++i) {
		jw.write_key(i->first);
		write_parameter_state(jw, *i->second);
	    }
	} else {
	    for (JsonArray::iterator i = params.begin(); i != params.end(); ++i) {
		const Glib::ustring& attr = (*i)->getString();
		if (param.hasId(attr)) {
		    jw.write_key(attr);
		    write_parameter_state(jw, param[attr]);
		}
	    }
	}
	jw.end_object();
    }

    FUNCTION(get_bank) {
	gx_system::PresetFile* pf = serv.settings.banks.get_file(params[0]->getString());
	if (!pf) {
	    throw RpcError(-32602, "Invalid params -- unknown bank");
	}
	pf->writeJSON_remote(jw);
    }

    FUNCTION(banks) {
	gx_system::PresetBanks& banks = serv.settings.banks;
	jw.begin_array();
	for (gx_system::PresetBanks::iterator i = banks.begin(); i != banks.end(); ++i) {
	    (*i)->writeJSON_remote(jw);
	}
	jw.end_array();
    }

    FUNCTION(presets) {
	gx_system::PresetFile* pf = serv.settings.banks.get_file(params[0]->getString());
	if (!pf) {
	    throw RpcError(-32602, "Invalid params -- unknown bank");
	}
	jw.begin_array();
	for (gx_system::PresetFile::iterator i = pf->begin(); i != pf->end(); ++i) {
	    jw.write(i->name);
	}
	jw.end_array();
    }

    FUNCTION(bank_insert_uri) {
	gx_system::PresetFile *f = serv.settings.bank_insert_uri(params[0]->getString(), params[0]->getInt());
	f->writeJSON_remote(jw);
    }

    FUNCTION(bank_insert_new) {
	gx_system::PresetFile *f = serv.settings.bank_insert_new(params[0]->getString());
	f->writeJSON_remote(jw);
    }

    FUNCTION(rename_bank) {
	Glib::ustring newname = params[1]->getString();
	jw.write(serv.settings.rename_bank(params[0]->getString(), newname));
	jw.write(newname);
    }

    FUNCTION(rename_preset) {
	jw.write(
	    serv.settings.rename_preset(
		*serv.settings.banks.get_file(params[0]->getString()), params[1]->getString(), params[2]->getString()));
    }

    FUNCTION(bank_check_reparse) {
	jw.write(serv.settings.banks.check_reparse());
    }

    FUNCTION(bank_get_filename) {
	jw.write(serv.settings.banks.get_file(params[0]->getString())->get_filename());
    }

    FUNCTION(convert_preset) {
	jw.write(serv.settings.convert_preset(*serv.settings.banks.get_file(params[0]->getString())));
    }

    FUNCTION(bank_remove) {
	jw.write(serv.settings.banks.remove(params[0]->getString()));
    }

    FUNCTION(midi_get_config_mode) {
	jw.write(serv.jack.get_engine().controller_map.get_config_mode());
    }

    FUNCTION(midi_size) {
	jw.write(serv.jack.get_engine().controller_map.size());
    }

    FUNCTION(midi_get_current_control) {
	jw.write(serv.jack.get_engine().controller_map.get_current_control());
    }

    FUNCTION(getstate) {
	gx_engine::GxEngineState s = serv.jack.get_engine().get_state();
	write_engine_state(jw, s);
    }

    FUNCTION(getversion) {
	jw.begin_array();
	jw.write(InterfaceVersionMajor);
	jw.write(InterfaceVersionMinor);
	jw.write(GX_VERSION);
	jw.end_array();
    }

    FUNCTION(get_tuning) {
	jw.begin_object();
	jw.write_key("frequency");
	jw.write(serv.jack.get_engine().tuner.get_freq());
	jw.write_key("note");
	jw.write(serv.jack.get_engine().tuner.get_note());
	jw.end_object();
    }

    FUNCTION(get_max_input_level) {
	jw.write(0.0);
    }

    FUNCTION(get_max_output_level) {
	gx_engine::MaxLevel& m = serv.jack.get_engine().maxlevel;
	unsigned int n = params[0]->getInt();
	jw.begin_array();
	for (unsigned int i = 0; i < n; i++) {
	    float v;
	    if (i < m.size()) {
		v = m.get(i);
	    } else {
		v = 0.0;
	    }
	    jw.write(v);
	}
	m.reset();
	jw.end_array();
    }

    FUNCTION(get_tuner_freq) {
	jw.write(serv.jack.get_engine().tuner.get_freq());
    }

    FUNCTION(jack_cpu_load) {
	jw.write(serv.jack.get_jcpu_load());
    }

    FUNCTION(get_jack_load_status) {
	jw.write(serv.jack.get_engine().midiaudiobuffer.jack_load_status());
    }

    FUNCTION(queryunit) {
	if (params.size() != 1) {
	    throw RpcError(-32602, "Invalid params -- 1 parameter expected");
	}
	gx_engine::Plugin *p = serv.jack.get_engine().pluginlist.find_plugin(params[0]->getString().c_str());
	if (!p) {
	    throw RpcError(-32602, "Invalid params -- plugin not found");
	}
	Glib::ustring unitprefix = p->get_pdef()->id;
	unitprefix += ".";
	const char **gl = p->get_pdef()->groups;
	gx_engine::ParamMap& param = serv.settings.get_param();
	jw.begin_object();
	for (gx_engine::ParamMap::iterator i = param.begin(); i != param.end(); ++i) {
	    if (unit_match(i->first, unitprefix, gl)) {
		jw.write_key(i->first);
		write_parameter_state(jw, *i->second);
	    }
	}
	jw.end_object();
    }

    FUNCTION(desc) {
	gx_engine::ParamMap& param = serv.settings.get_param();
	jw.begin_object();
	for (JsonArray::iterator i = params.begin(); i != params.end(); ++i) {
	    const Glib::ustring& attr = (*i)->getString();
	    jw.write_key(attr);
	    if (!param.hasId(attr)) {
		jw.write("unknown");
		continue;
	    }
	    write_parameter_state(jw, param[attr]);
	}
	jw.end_object();
    }

    FUNCTION(list) {
	const Glib::ustring& prefix = params[0]->getString();
	gx_engine::ParamMap& param = serv.settings.get_param();
	jw.begin_array();
	for (gx_engine::ParamMap::iterator i = param.begin(); i != param.end(); ++i) {
	    if (i->first.compare(0, prefix.size(), prefix) == 0) {
		jw.write(i->first);
	    }
	}
	jw.end_array();
    }

    FUNCTION(help) {
	jw.begin_array();
	for (const char **p = &cmds[0]; *p; ++p) {
	    jw.write(*p);
	}
	jw.end_array();
    }

    END_FUNCTION_SWITCH(throw RpcError(-32601, "Method not found"));
}

static void save_preset(gx_preset::GxSettings& settings, const Glib::ustring& bank,
			const Glib::ustring& preset) {
    gx_system::PresetFile *pf = settings.banks.get_file(bank);
    if (!pf) {
	Glib::ustring newbank = bank;
	std::string newfile;
	settings.banks.make_bank_unique(newbank, &newfile);
	pf = new gx_system::PresetFile();
	if (pf->create_file(newbank, newfile, gx_system::PresetFile::PRESET_FILE, 0)) {
	    settings.banks.insert(pf);
	} else {
	    delete pf;
	    throw RpcError(-32001, "bank not found");
	}
    }
    if (!pf->is_mutable()) {
	throw RpcError(-32001, "bank is immutable");
    }
    settings.save(*pf, preset);
}

void CmdConnection::send_rack_changed(bool stereo) {
    std::string s;
    for (std::list<CmdConnection*>::iterator p = serv.connection_list.begin(); p != serv.connection_list.end(); ++p) {
	if (*p == this || !(*p)->parameter_change_notify) {
	    continue;
	}
	if (s.empty()) {
	    gx_system::JsonStringWriter jw;
	    send_notify_begin(jw, "rack_units_changed");
	    std::vector<std::string>& ul = serv.settings.get_rack_unit_order(stereo);
	    jw.begin_array();
	    jw.write(stereo);
	    for (std::vector<std::string>::iterator i = ul.begin(); i != ul.end(); ++i) {
		jw.write(*i);
	    }
	    jw.end_array();
	    send_notify_end(jw, false);
	    jw.finish();
	    s = jw.get_string();
	}
	ssize_t n = write((*p)->connection->get_socket()->get_fd(), s.c_str(), s.size());
	if (n != (ssize_t)s.size()) {
	    cerr << "short write" << endl;
	}
    }
}

void CmdConnection::notify(gx_system::JsonWriter& jw, const methodnames *mn, JsonArray& params) {
    START_FUNCTION_SWITCH(mn->m_id);

    FUNCTION(insert_rack_unit) {
	bool stereo = params[2]->getInt();
	serv.settings.insert_rack_unit(params[0]->getString(), params[1]->getString(), stereo);
	send_rack_changed(stereo);
    }

    FUNCTION(remove_rack_unit) {
	bool stereo = params[1]->getInt();
	serv.settings.remove_rack_unit(params[0]->getString(), stereo);
	send_rack_changed(stereo);
    }

    FUNCTION(bank_reorder) {
	std::vector<Glib::ustring> neworder;
	for (JsonArray::iterator i = params.begin(); i != params.end(); ++i) {
	    neworder.push_back((*i)->getString());
	}
	serv.settings.banks.reorder(neworder);
    }

    FUNCTION(reorder_preset) {
	std::vector<Glib::ustring> neworder;
	for (JsonArray::iterator i = params.begin()+1; i != params.end(); ++i) {
	    neworder.push_back((*i)->getString());
	}
	serv.settings.reorder_preset(*serv.settings.banks.get_file(params[0]->getString()), neworder);
    }

    FUNCTION(erase_preset) {
	serv.settings.erase_preset(*serv.settings.banks.get_file(params[0]->getString()), params[1]->getString());
    }

    FUNCTION(bank_set_flag) {
	serv.settings.banks.get_file(params[0]->getString())->set_flag(params[1]->getInt(), params[2]->getInt());
    }

    FUNCTION(pf_append) {
	serv.settings.append(
	    *serv.settings.banks.get_file(params[0]->getString()), params[1]->getString(),
	    *serv.settings.banks.get_file(params[2]->getString()), params[3]->getString());
    }

    FUNCTION(pf_insert_before) {
	serv.settings.insert_before(
	    *serv.settings.banks.get_file(params[0]->getString()), params[1]->getString(),
	    *serv.settings.banks.get_file(params[2]->getString()), params[3]->getString(),
	    params[4]->getString());
    }

    FUNCTION(pf_insert_after) {
	serv.settings.insert_after(
	    *serv.settings.banks.get_file(params[0]->getString()), params[1]->getString(),
	    *serv.settings.banks.get_file(params[2]->getString()), params[3]->getString(),
	    params[4]->getString());
    }

    FUNCTION(bank_save) {
	serv.settings.banks.save();
    }

    FUNCTION(pf_save) {
	serv.settings.save(*serv.settings.banks.get_file(params[0]->getString()), params[1]->getString());
    }

    FUNCTION(midi_set_config_mode) {
	serv.jack.get_engine().controller_map.set_config_mode(params[0]->getInt(), params[1]->getInt());
    }

    FUNCTION(request_midi_value_update) {
	serv.jack.get_engine().controller_map.request_midi_value_update();
    }

    FUNCTION(midi_deleteParameter) {
	serv.jack.get_engine().controller_map.deleteParameter(serv.settings.get_param()[params[0]->getString()], params[1]->getInt());
    }

    FUNCTION(midi_set_current_control) {
	serv.jack.get_engine().controller_map.set_current_control(params[0]->getInt());
    }

    FUNCTION(midi_modifyCurrent) {
	serv.jack.get_engine().controller_map.modifyCurrent(
	    serv.settings.get_param()[params[0]->getString()], params[1]->getFloat(),
	    params[2]->getFloat(), params[3]->getInt());
    }

    FUNCTION(set) {
	if (params.size() & 1) {
	    throw RpcError(-32602, "Invalid param -- array length must be even");
	}
	gx_engine::ParamMap& param = serv.settings.get_param();
	for (unsigned int i = 0; i < params.size(); i += 2) {
	    const Glib::ustring& attr = params[i]->getString();
	    if (param.hasId(attr)) {
		gx_engine::Parameter& p = param[attr];
		JsonValue *v = params[i+1];
		if (p.isFloat()) {
		    p.getFloat().set(v->getFloat());
		} else if (p.isInt()) {
		    gx_engine::IntParameter& pi = p.getInt();
		    int i;
		    if (p.getControlType() == gx_engine::Parameter::Enum && dynamic_cast<JsonString*>(v)) {
			i = pi.idx_from_id(v->getString());
		    } else {
			i = v->getInt();
		    }
		    pi.set(i);
		} else if (p.isBool()) {
		    p.getBool().set(v->getInt());
		} else if (p.isFile()) {
		    p.getFile().set(Gio::File::create_for_path(v->getString()));
		} else if (p.isString()) {
		    p.getString().set(v->getString());
		} else {
		    throw RpcError(-32602, "Invalid param -- unknown variable");
		}
		//gx_system::JsonWriter jwd(&cerr); p.dump(&jwd);
	    }
	}
	std::string s;

	for (std::list<CmdConnection*>::iterator p = serv.connection_list.begin(); p != serv.connection_list.end(); ++p) {
	    if (*p == this || !(*p)->parameter_change_notify) {
		continue;
	    }
	    if (s.empty()) {
		gx_system::JsonStringWriter jw;
		send_notify_begin(jw, "set");
		for (unsigned int i = 0; i < params.size(); i += 2) {
		    jw.write(params[i]->getString());
		    JsonValue *v = params[i+1];
		    if (dynamic_cast<JsonFloat*>(v)) {
			jw.write(v->getFloat());
		    } else if (dynamic_cast<JsonInt*>(v)) {
			jw.write(v->getInt());
		    } else if (dynamic_cast<JsonString*>(v)) {
			jw.write(v->getString());
		    }
		}
		send_notify_end(jw, false);
		jw.finish();
		s = jw.get_string();
	    }
	    ssize_t n = write((*p)->connection->get_socket()->get_fd(), s.c_str(), s.size());
	    if (n != (ssize_t)s.size()) {
		cerr << "short write" << endl;
	    }
	}
	serv.save_state();
    }

    FUNCTION(setpreset) {
	gx_system::PresetFile* pf = serv.settings.banks.get_file(params[0]->getString());
	serv.settings.load_preset(pf, params[1]->getString());
	serv.save_state();
    }

    FUNCTION(setstate) {
	serv.jack.get_engine().set_state(string_to_engine_state(params[0]->getString()));
	serv.jack.get_engine().check_module_lists();
    }

    FUNCTION(switch_tuner) {
	serv.jack.get_engine().tuner.used_for_livedisplay(params[0]->getInt());
	serv.jack.get_engine().check_module_lists();
    }

    FUNCTION(switch) {
	serv.on_switcher_toggled(true);
    }

    FUNCTION(shutdown) {
	connection->close();
	serv.quit_mainloop();
    }

    FUNCTION(listen) {
	for (JsonArray::iterator i = params.begin(); i != params.end(); ++i) {
	    CmdConnection::listen((*i)->getString());
	}
    }

    FUNCTION(unlisten) {
	for (JsonArray::iterator i = params.begin(); i != params.end(); ++i) {
	    CmdConnection::unlisten((*i)->getString());
	}
    }

    FUNCTION(save_current) {
	if (!serv.settings.setting_is_preset()) {
	    throw RpcError(-32001, "no current preset");
	}
	save_preset(serv.settings, serv.settings.get_current_bank(), serv.settings.get_current_name());
    }

    FUNCTION(save_preset) {
	save_preset(serv.settings, params[0]->getString(), params[1]->getString());
    }

    END_FUNCTION_SWITCH(throw RpcError(-32601, "Method not found"));
}

void CmdConnection::write_error(gx_system::JsonWriter& jw, int code, const char *message) {
    jw.write_key("error");
    jw.begin_object();
    jw.write_key("code");
    jw.write(code);
    jw.write_key("message");
    jw.write(message);
    jw.end_object();
}

bool CmdConnection::request(gx_system::JsonParser& jp, gx_system::JsonWriter& jw, bool batch_start) {
    Glib::ustring method;
    JsonArray params;
    Glib::ustring id;
    jp.next(gx_system::JsonParser::begin_object);
    while (jp.peek() != gx_system::JsonParser::end_object) {
	jp.next(gx_system::JsonParser::value_key);
	if (jp.current_value() == "jsonrpc") {
	    jp.next(gx_system::JsonParser::value_string);
	    if (jp.current_value() != "2.0") {
		throw RpcError(-32600,"Invalid Request");
	    }
	} else if (jp.current_value() == "method") {
	    jp.next(gx_system::JsonParser::value_string);
	    method = jp.current_value();
	} else if (jp.current_value() == "params") {
	    if (jp.peek() == gx_system::JsonParser::begin_array) {
		jp.next(gx_system::JsonParser::begin_array);
		while (jp.peek() != gx_system::JsonParser::end_array) {
		    params.append(jp);
		}
		jp.next(gx_system::JsonParser::end_array);
	    } else if (jp.peek() == gx_system::JsonParser::begin_object) {
		throw RpcError(-32000,"by-name parameters not implemented");
	    } else {
		throw RpcError(-32600,"Invalid Request");
	    }
	} else if (jp.current_value() == "id") {
	    if (jp.peek() != gx_system::JsonParser::value_string &&
		jp.peek() != gx_system::JsonParser::value_number) {
		throw RpcError(-32600,"Invalid Request");
	    }
	    jp.next();
	    id = jp.current_value();
	} else {
	    throw RpcError(-32600,"Invalid Request");
	}
    }
    jp.next(gx_system::JsonParser::end_object);
    const methodnames *p = in_word_set(method.c_str(), method.size());
    if (!p) {
	throw RpcError(-32601, Glib::ustring::compose("Method not found -- '%1'", method));
    }
    if (id.empty()) {
	try {
	    notify(jw, p, params);
	} catch(RpcError& e) {
	    error_response(jw, e.code, e.message);
	}
	return false;
    } else {
	if (batch_start) {
	    jw.begin_array();
	}
	jw.begin_object();
	jw.write_key("jsonrpc");
	jw.write("2.0");
	jw.write_key("id");
	jw.write(id);
	jw.write_key("result");
	try {
	    call(jw, p, params);
	} catch(RpcError& e) {
	    write_error(jw, e.code, e.message);
	}
	jw.end_object();
	return true;
    }
}

void CmdConnection::error_response(gx_system::JsonWriter& jw, int code, const char *message) {
    jw.begin_object();
    jw.write_key("jsonrpc");
    jw.write("2.0");
    jw.write_key("id");
    jw.write_null();
    write_error(jw, code, message);
    jw.end_object();
}

bool CmdConnection::on_data(Glib::IOCondition cond) {
    if (cond != Glib::IO_IN) {
	serv.remove_connection(this);
	return false;
    }
    Glib::RefPtr<Gio::Socket> sock = connection->get_socket();
    char buf[1000];
    while (true) {
	int n;
	try {
	    n = sock->receive(buf, sizeof(buf));
	} catch(Glib::Error e) {
	    if (e.code() == Gio::Error::WOULD_BLOCK) {
		return true;
	    }
	    serv.remove_connection(this);
	    return false;
	}
	if (n <= 0) {
	    serv.remove_connection(this);
	    return false;
	}
	char *p = buf;
	while (n-- > 0) {
	    jp.put(*p);
	    //cerr << *p;
	    if (*p == '\n') {
		//cerr << std::flush;
		process(jp);
		jp.reset();
	    }
	    p++;
	}
    }
}

void CmdConnection::send(gx_system::JsonStringWriter& jw) {
    jw.finish();
    std::string s = jw.get_string();
    ssize_t n = write(connection->get_socket()->get_fd(), s.c_str(), s.size());
    if (n != (ssize_t)s.size()) {
	cerr << "short write" << endl;
    }
}

void CmdConnection::process(gx_system::JsonStringParser& jp) {
    gx_system::JsonStringWriter jw;
    try {
	bool resp = false;
	// jp.peek() doesn't work at start of stream
	if (jp.peek_first_char() == '[') {
	    jp.next(gx_system::JsonParser::begin_array);
	    while (jp.peek() != gx_system::JsonParser::end_array) {
		resp = request(jp, jw, !resp) || resp;
	    }
	    if (resp) {
		jw.end_array();
	    }
	    jp.next(gx_system::JsonParser::end_array);
	} else {
	    resp = request(jp, jw, false);
	}
	if (!resp) {
	    return;
	}
    } catch (gx_system::JsonException& e) {
	gx_system::gx_print_error(
	    "JSON-RPC", Glib::ustring::compose("error: %1, request: '%2'",
					       e.what(), jp.get_string()));
	jw.reset();
	error_response(jw, -32700, "Parse Error");
    } catch (RpcError& e) {
	jw.reset();
	error_response(jw, e.code, e.message);
    }
    send(jw);
}


/****************************************************************
 ** class UiBuilderVirt implementation
 */

gx_system::JsonWriter *UiBuilderVirt::jw = 0;

UiBuilderVirt::UiBuilderVirt(gx_system::JsonWriter *jw_) {
    jw = jw_;
    openTabBox = openTabBox_;
    openVerticalBox = openVerticalBox_;
    openVerticalBox1 = openVerticalBox1_;
    openVerticalBox2 = openVerticalBox2_;
    openHorizontalBox = openHorizontalBox_;
    openHorizontalhideBox = openHorizontalhideBox_;
    closeBox = closeBox_;
    load_glade = load_glade_;
    create_master_slider = create_master_slider_;
    create_small_rackknob = create_small_rackknob_;
    create_small_rackknobr = create_small_rackknobr_;
    create_spin_value = create_spin_value_;
    create_switch = create_switch_;
    create_switch_no_caption = create_switch_no_caption_;
    create_selector = create_selector_;
    create_selector_no_caption = create_selector_no_caption_;
    create_port_display = create_port_display_;
    insertSpacer = insertSpacer_;
    set_next_flags = set_next_flags_;
}

UiBuilderVirt::~UiBuilderVirt() {
}

void UiBuilderVirt::openTabBox_(const char* label) {
    jw->begin_array();
    jw->write("openTabBox");
    jw->write(label);
    jw->end_array();
}

void UiBuilderVirt::openVerticalBox_(const char* label) {
    jw->begin_array();
    jw->write("openVerticalBox");
    jw->write(label);
    jw->end_array();
}

void UiBuilderVirt::openVerticalBox1_(const char* label) {
    jw->begin_array();
    jw->write("openVerticalBox1");
    jw->write(label);
    jw->end_array();
}

void UiBuilderVirt::openVerticalBox2_(const char* label) {
    jw->begin_array();
    jw->write("openVerticalBox2");
    jw->write(label);
    jw->end_array();
}

void UiBuilderVirt::openHorizontalhideBox_(const char* label) {
    jw->begin_array();
    jw->write("openHorizontalhideBox");
    jw->write(label);
    jw->end_array();
}

void UiBuilderVirt::openHorizontalBox_(const char* label) {
    jw->begin_array();
    jw->write("openHorizontalBox");
    jw->write(label);
    jw->end_array();
}

void UiBuilderVirt::insertSpacer_() {
    jw->begin_array();
    jw->write("insertSpacer");
    jw->end_array();
}

void UiBuilderVirt::set_next_flags_(int flags) {
    jw->begin_array();
    jw->write("set_next_flags");
    jw->write(flags);
    jw->end_array();
}

void UiBuilderVirt::create_small_rackknob_(const char *id, const char *label) {
    jw->begin_array();
    jw->write("create_small_rackknob");
    jw->write(id);
    jw->write(label);
    jw->end_array();
}

void UiBuilderVirt::create_small_rackknobr_(const char *id, const char *label) {
    jw->begin_array();
    jw->write("create_small_rackknobr");
    jw->write(id);
    jw->write(label);
    jw->end_array();
}

void UiBuilderVirt::create_master_slider_(const char *id, const char *label) {
    jw->begin_array();
    jw->write("create_master_slider");
    jw->write(id);
    jw->write(label);
    jw->end_array();
}

void UiBuilderVirt::create_selector_no_caption_(const char *id) {
    jw->begin_array();
    jw->write("create_selector_no_caption");
    jw->write(id);
    jw->end_array();
}

void UiBuilderVirt::create_selector_(const char *id, const char *label) {
    jw->begin_array();
    jw->write("create_selector");
    jw->write(id);
    jw->write(label);
    jw->end_array();
}

void UiBuilderVirt::create_spin_value_(const char *id, const char *label) {
    jw->begin_array();
    jw->write("create_spin_value");
    jw->write(id);
    jw->write(label);
    jw->end_array();
}

void UiBuilderVirt::create_switch_no_caption_(const char *sw_type, const char * id) {
    jw->begin_array();
    jw->write("create_switch_no_caption");
    jw->write(sw_type);
    jw->write(id);
    jw->end_array();
}

void UiBuilderVirt::create_switch_(const char *sw_type, const char * id, const char *label) {
    jw->begin_array();
    jw->write("create_switch");
    jw->write(sw_type);
    jw->write(id);
    jw->write(label);
    jw->end_array();
}

void UiBuilderVirt::create_port_display_(const char *id, const char *label) {
    jw->begin_array();
    jw->write("create_port_display");
    jw->write(id);
    jw->write(label);
    jw->end_array();
}

void UiBuilderVirt::closeBox_() {
    jw->begin_array();
    jw->write("closeBox");
    jw->end_array();
}

void UiBuilderVirt::load_glade_(const char *data) {
    jw->begin_array();
    jw->write("load_glade");
    jw->write(data);
    jw->end_array();
}


/****************************************************************
 ** class MyService
 */

MyService::MyService(gx_preset::GxSettings& settings_, gx_jack::GxJack& jack_,
		     sigc::slot<void> quit_mainloop_, int port)
    : Gio::SocketService(),
      settings(settings_),
      jack(jack_),
      quit_mainloop(quit_mainloop_),
      tuner_switcher(settings_, jack_.get_engine()),
      oldest_unsaved(0),
      last_change(0),
      save_conn(),
      connection_list() {
    settings.get_param()["ui.live_play_switcher"].signal_changed_bool().connect(
	sigc::mem_fun(this, &MyService::on_switcher_toggled));
    tuner_switcher.signal_selection_done().connect(sigc::mem_fun(this, &MyService::on_selection_done));
    add_inet_port(port);
}

MyService::~MyService() {
    for (std::list<CmdConnection*>::iterator i = connection_list.begin(); i != connection_list.end(); ++i) {
	delete *i;
    }
}

void MyService::remove_connection(CmdConnection *p) {
    for (std::list<CmdConnection*>::iterator i = connection_list.begin(); i != connection_list.end(); ++i) {
	if (*i == p) {
	    connection_list.erase(i);
	    delete p;
	    return;
	}
    }
    assert(false);
}

//FIXME: this belongs into GxSettings
void MyService::save_state() {
    if (settings.get_options().get_opt_auto_save()) {
	return;
    }
    static const int min_idle = 2;   // seconds; after this idle time save changed state
    static const int max_delay = 15; // seconds; maximum delay for save changed state
    time_t now = time(NULL);
    if (oldest_unsaved == 0) {
	oldest_unsaved = last_change = now;
	save_conn = Glib::signal_timeout().connect(sigc::bind_return(sigc::mem_fun(this, &MyService::save_state),false), 1000*min_idle);
	return;
    }
    if (now - oldest_unsaved >= max_delay || now - last_change >= min_idle) {
	settings.save_to_state();
	sync();
	oldest_unsaved = 0;
	save_conn.disconnect();
    } else {
	last_change = now;
	if (oldest_unsaved == 0) {
	    oldest_unsaved = now;
	}
	save_conn.disconnect();
	save_conn = Glib::signal_timeout().connect(sigc::bind_return(sigc::mem_fun(this, &MyService::save_state),false), 1000*min_idle);
    }
}

bool MyService::on_incoming(const Glib::RefPtr<Gio::SocketConnection>& connection,
			    const Glib::RefPtr<Glib::Object>& source_object) {
    CmdConnection *cc = new CmdConnection(*this, connection);
    connection_list.push_back(cc);
    Glib::RefPtr<Gio::Socket> sock = connection->get_socket();
    sock->set_blocking(false);
    Glib::signal_io().connect(
	sigc::mem_fun(cc, &CmdConnection::on_data),
	sock->get_fd(), Glib::IO_IN|Glib::IO_HUP);
    return true;
}

void MyService::on_switcher_toggled(bool v) {
    if (v) {
	if (tuner_switcher.get_active()) {
	    tuner_switcher.deactivate();
	} else {
	    tuner_switcher.activate(false);
	    if (jack.get_engine().tuner.used_for_livedisplay()) {
		tuner_switcher.deactivate();
	    }
	}
    }
}

void MyService::on_selection_done() {
    if (tuner_switcher.deactivate()) {
	jack.get_engine().set_state(gx_engine::kEngineBypass);
    } else if (jack.get_engine().get_state() == gx_engine::kEngineBypass) {
	jack.get_engine().set_state(gx_engine::kEngineOn);
    }
}

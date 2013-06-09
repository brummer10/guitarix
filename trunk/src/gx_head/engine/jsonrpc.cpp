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
#include <ext/stdio_filebuf.h>

class RpcError: public exception {
public:
    int code;
    Glib::ustring message;
public:
    RpcError(int code_, Glib::ustring message_): code(code_), message(message_) {}
    ~RpcError() throw() { }
    virtual const char* what() const throw() { return message.c_str(); }
};


class JsonValue {
protected:
    JsonValue() {}
    virtual ~JsonValue() {}
    friend class JsonArray;
public:
    virtual double getFloat() const;
    virtual int getInt() const;
    virtual const Glib::ustring& getString() const;
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

class JsonArray: public std::vector<JsonValue*> {
public:
    JsonArray():std::vector<JsonValue*>() {}
    ~JsonArray();
    JsonValue *operator[](unsigned int i);
    void append(gx_system::JsonParser& jp);
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
 ** class CmdConnection
 */

const static int InterfaceVersionMajor = 1;
const static int InterfaceVersionMinor = 0;

class CmdConnection: public sigc::trackable {
private:
    MyService& serv;
    Glib::RefPtr<Gio::SocketConnection> connection;
    std::stringbuf inbuf;
    gx_system::JsonParser jp;
    __gnu_cxx::stdio_filebuf<char> writebuf;
    ostream os;
    gx_system::JsonWriter jw;
    sigc::connection conn_preset_changed;
    sigc::connection conn_state_changed;
    sigc::connection conn_freq_changed;
    sigc::connection conn_display;
    sigc::connection conn_display_state;
    sigc::connection conn_selection_done;
    sigc::connection conn_log_message;
private:
    void exec(Glib::ustring cmd);
    void call(Glib::ustring& method, JsonArray& params);
    void notify(Glib::ustring& method, JsonArray& params);
    bool request(bool batch_start);
    void write_error(int code, const char *message);
    void write_error(int code, Glib::ustring& message) { write_error(code, message.c_str()); }
    void error_response(int code, const char *message);
    void error_response(int code, Glib::ustring& message) { error_response(code, message.c_str()); }
    void preset_changed();
    void send_notify_begin(const char *method);
    void send_notify_end();
    void on_engine_state_change(gx_engine::GxEngineState state);
    void write_engine_state(gx_engine::GxEngineState s);
    void on_tuner_freq_changed();
    void display(const Glib::ustring& bank, const Glib::ustring& preset);
    void set_display_state(TunerSwitcher::SwitcherState newstate);
    void on_selection_done();
    void on_log_message(const string& msg, gx_system::GxMsgType tp, bool plugged);
    void listen(const Glib::ustring& tp);
    void unlisten(const Glib::ustring& tp);
    void process(istringstream& is);

public:
    CmdConnection(MyService& serv, const Glib::RefPtr<Gio::SocketConnection>& connection_);
    ~CmdConnection() {}
    bool on_data(Glib::IOCondition cond);
};

CmdConnection::CmdConnection(MyService& serv_, const Glib::RefPtr<Gio::SocketConnection>& connection_)
    : serv(serv_),
      connection(connection_),
      jp(),
      writebuf(connection->get_socket()->get_fd(), std::ios::out),
      os(&writebuf),
      jw(&os, false),
      conn_preset_changed(),
      conn_state_changed(),
      conn_freq_changed(),
      conn_display(),
      conn_display_state(),
      conn_selection_done(),
      conn_log_message() {
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
    if (all || tp == "logger") {
	conn_log_message = gx_system::Logger::get_logger().signal_message().connect(
	    sigc::mem_fun(this, &CmdConnection::on_log_message));
	gx_system::Logger::get_logger().unplug_queue();
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
    if (all || tp == "logger") {
	conn_log_message.disconnect();
    }
}

void CmdConnection::on_log_message(const string& msg, gx_system::GxMsgType tp, bool plugged) {
    switch (tp) {
    case gx_system::kInfo:    break;
    case gx_system::kWarning: break;
    case gx_system::kError:   break;
    default:       break;
    }
    if (!plugged) {
	send_notify_begin("errormsg");
	jw.write(msg);
	send_notify_end();
    }
}

void CmdConnection::send_notify_begin(const char *method) {
    jw.begin_object();
    jw.write_key("jsonrpc");
    jw.write("2.0");
    jw.write_key("method");
    jw.write(method);
    jw.write_key("params");
    jw.begin_array();
}

void CmdConnection::send_notify_end() {
    jw.end_array();
    jw.end_object();
    os << endl;
    jw.reset();
}

void CmdConnection::write_engine_state(gx_engine::GxEngineState s) {
    const char *p = 0;
    if (s == gx_engine::kEngineOff) {
	p = "stopped";
    } else if (s == gx_engine::kEngineOn) {
	p = "running";
    } else if (s == gx_engine::kEngineBypass) {
	p = "bypassed";
    } else {
	p = "unknown";
    }
    jw.write(p);
}

void CmdConnection::on_selection_done() {
    send_notify_begin("show_tuner");
    jw.write(serv.tuner_switcher.deactivate());
    send_notify_end();
}

void CmdConnection::on_engine_state_change(gx_engine::GxEngineState state) {
    send_notify_begin("state_changed");
    write_engine_state(state);
    send_notify_end();
}

void CmdConnection::preset_changed() {
    send_notify_begin("preset_changed");
    if (serv.settings.setting_is_preset()) {
	jw.write(serv.settings.get_current_bank());
	jw.write(serv.settings.get_current_name());
    }
    send_notify_end();
}

void CmdConnection::on_tuner_freq_changed() {
    send_notify_begin("tuner_changed");
    //jw.write_key("frequency");
    jw.write(serv.jack.get_engine().tuner.get_freq());
    //jw.write_key("note");
    jw.write(serv.jack.get_engine().tuner.get_note());
    send_notify_end();
}

void CmdConnection::display(const Glib::ustring& bank, const Glib::ustring& preset) {
    send_notify_begin("display_bank_preset");
    jw.write(bank);
    jw.write(preset);
    send_notify_end();
}

void CmdConnection::set_display_state(TunerSwitcher::SwitcherState state) {
    send_notify_begin("set_display_state");
    switch (state) {
    case TunerSwitcher::normal_mode: jw.write("normal_mode"); break;
    case TunerSwitcher::wait_start: jw.write("wait_start"); break;
    case TunerSwitcher::listening: jw.write("listening"); break;
    case TunerSwitcher::wait_stop: jw.write("wait_stop"); break;
    default: assert(false); break;
    }
    send_notify_end();
}

static bool do_reset = true;

static void write_plugin_state(gx_system::JsonWriter& jw, gx_engine::Plugin *i) {
    jw.begin_object();
    jw.write_key("id");
    jw.write(i->pdef->id);
    jw.write_key("on_off");
    jw.write(i->on_off);
    jw.write_key("box_visible");
    jw.write(i->box_visible);
    jw.write_key("plug_visible");
    jw.write(i->plug_visible);
    jw.write_key("position");
    jw.write(i->position);
    jw.write_key("post_pre");
    jw.write(i->effect_post_pre);
    jw.write_key("stereo");
    jw.write((i->pdef->flags & PGN_STEREO) == PGN_STEREO);
    const char *p;
    p = i->pdef->category;
    if (p) {
	jw.write_key("category");
	jw.write(p);
    }
    p = i->pdef->name;
    if (p) {
	jw.write_key("name");
	jw.write(p);
    }
    p = i->pdef->shortname;
    if (p) {
	jw.write_key("shortname");
	jw.write(p);
    }
    p = i->pdef->description;
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

static void write_bank_state(gx_system::JsonWriter& jw, const gx_system::PresetFile *pf) {
    jw.begin_object();
    jw.write_key("name");
    jw.write(pf->get_name());
    jw.write_key("mutable");
    jw.write(pf->is_mutable());
    jw.write_key("type");
    switch (pf->get_type()) {
    case gx_system::PresetFile::PRESET_SCRATCH: jw.write("scratch"); break;
    case gx_system::PresetFile::PRESET_FACTORY: jw.write("factory"); break;
    case gx_system::PresetFile::PRESET_FILE: jw.write("file"); break;
    default: jw.write("unknown"); break;
    }
    int flags = pf->get_flags();
    if (flags & gx_system::PRESET_FLAG_INVALID) {
	jw.write_key("flag_invalid");
	jw.write(1);
    }
    if (flags & gx_system::PRESET_FLAG_READONLY) {
	jw.write_key("flag_readonly");
	jw.write(1);
    }
    if (flags & gx_system::PRESET_FLAG_VERSIONDIFF) {
	jw.write_key("flag_versiondiff");
	jw.write(1);
    }
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

void CmdConnection::call(Glib::ustring& method, JsonArray& params) {
    static const char *cmds[] = {
	"get","set","banks","presets","setpreset","getstate","setstate",
	"switch_tuner","get_tuning","get_max_input_level","get_max_output_level",
	"shutdown","stop","rtload","desc","list","get_parameter","help",
	0
    };
    if (method == "get") {
	gx_engine::ParamMap& param = serv.settings.get_param();
	jw.write_key("result");
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
    } else if (method == "get_parameter") {
	gx_engine::ParamMap& param = serv.settings.get_param();
	jw.write_key("result");
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
    } else if (method == "get_bank") {
	gx_system::PresetFile* pf = serv.settings.banks.get_file(params[0]->getString());
	if (!pf) {
	    throw RpcError(-32602, "Invalid params -- unknown bank");
	}
	jw.write_key("result");
	write_bank_state(jw, pf);
    } else if (method == "banks") {
	gx_system::PresetBanks& banks = serv.settings.banks;
	jw.write_key("result");
	jw.begin_array();
	for (gx_system::PresetBanks::iterator i = banks.begin(); i != banks.end(); ++i) {
	    write_bank_state(jw, *i);
	}
	jw.end_array();
    } else if (method == "presets") {
	gx_system::PresetFile* pf = serv.settings.banks.get_file(params[0]->getString());
	if (!pf) {
	    throw RpcError(-32602, "Invalid params -- unknown bank");
	}
	jw.write_key("result");
	jw.begin_array();
	for (gx_system::PresetFile::iterator i = pf->begin(); i != pf->end(); ++i) {
	    jw.write(i->name);
	}
	jw.end_array();
    } else if (method == "getstate") {
	gx_engine::GxEngineState s = serv.jack.get_engine().get_state();
	jw.write_key("result");
	write_engine_state(s);
    } else if (method == "getversion") {
	jw.write_key("result");
	jw.begin_array();
	jw.write(InterfaceVersionMajor);
	jw.write(InterfaceVersionMinor);
	jw.write(GX_VERSION);
	jw.end_array();
    } else if (method == "get_tuning") {
	jw.write_key("result");
	jw.begin_object();
	jw.write_key("frequency");
	jw.write(serv.jack.get_engine().tuner.get_freq());
	jw.write_key("note");
	jw.write(serv.jack.get_engine().tuner.get_note());
	jw.end_object();
    } else if (method == "get_max_input_level") {
	jw.write_key("result");
	jw.write(0.0);
    } else if (method == "get_max_output_level") {
	gx_engine::MaxLevel& m = serv.jack.get_engine().maxlevel;
	jw.write_key("result");
	jw.begin_array();
	jw.write(m.get(0));
	jw.write(m.get(1));
	m.reset();
	jw.end_array();
    } else if (method == "jack_cpu_load") {
	jw.write_key("result");
	jw.write(serv.jack.get_jcpu_load());
    } else if (method == "queryunit") {
	if (params.size() != 1) {
	    throw RpcError(-32602, "Invalid params -- 1 parameter expected");
	}
	gx_engine::Plugin *p = serv.jack.get_engine().pluginlist.find_plugin(params[0]->getString().c_str());
	if (!p) {
	    throw RpcError(-32602, "Invalid params -- plugin not found");
	}
	Glib::ustring unitprefix = p->pdef->id;
	unitprefix += ".";
	const char **gl = p->pdef->groups;
	gx_engine::ParamMap& param = serv.settings.get_param();
	jw.write_key("result");
	jw.begin_object();
	for (gx_engine::ParamMap::iterator i = param.begin(); i != param.end(); ++i) {
	    if (unit_match(i->first, unitprefix, gl)) {
		jw.write_key(i->first);
		write_parameter_state(jw, *i->second);
	    }
	}
	jw.end_object();
    } else if (method == "desc") {
	gx_engine::ParamMap& param = serv.settings.get_param();
	jw.write_key("result");
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
    } else if (method == "list") {
	const Glib::ustring& prefix = params[0]->getString();
	gx_engine::ParamMap& param = serv.settings.get_param();
	jw.write_key("result");
	jw.begin_array();
	for (gx_engine::ParamMap::iterator i = param.begin(); i != param.end(); ++i) {
	    if (i->first.compare(0, prefix.size(), prefix) == 0) {
		jw.write(i->first);
	    }
	}
	jw.end_array();
    } else if (method == "help") {
	jw.write_key("result");
	jw.begin_array();
	for (const char **p = &cmds[0]; *p; ++p) {
	    jw.write(*p);
	}
	jw.end_array();
    } else {
	throw RpcError(-32601, "Method not found");
    }
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

void CmdConnection::notify(Glib::ustring& method, JsonArray& params) {
    if (method == "set") {
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
		    if (p.getControlType() == gx_engine::Parameter::Enum) {
			i = pi.idx_from_id(v->getString());
		    } else {
			i = v->getInt();
		    }
		    pi.set(i);
		} else if (p.isBool()) {
		    p.getBool().set(v->getInt());
		} else if (p.isSwitch()) {
		    p.getSwitch().set(v->getInt());
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
	serv.save_state();
    } else if (method == "setpreset") {
	gx_system::PresetFile* pf = serv.settings.banks.get_file(params[0]->getString());
	serv.settings.load_preset(pf, params[1]->getString());
	serv.save_state();
    } else if (method == "setstate") {
	const Glib::ustring &p = params[0]->getString();
	if (p == "stopped") {
	    serv.jack.get_engine().set_state(gx_engine::kEngineOff);
	} else if (p == "running") {
	    serv.jack.get_engine().set_state(gx_engine::kEngineOn);
	} else if (p == "bypassed") {
	    serv.jack.get_engine().set_state(gx_engine::kEngineBypass);
	} else {
	    // unknown
	}
	serv.jack.get_engine().check_module_lists();
    } else if (method == "switch_tuner") {
	serv.jack.get_engine().tuner.used_for_livedisplay(params[0]->getInt());
	serv.jack.get_engine().check_module_lists();
    } else if (method == "switch") {
	serv.on_switcher_toggled(true);
    } else if (method == "shutdown") {
	connection->close();
	serv.quit_mainloop();
    } else if (method == "stop") {
	do_reset = false;
    } else if (method == "listen") {
	for (JsonArray::iterator i = params.begin(); i != params.end(); ++i) {
	    CmdConnection::listen((*i)->getString());
	}
    } else if (method == "unlisten") {
	for (JsonArray::iterator i = params.begin(); i != params.end(); ++i) {
	    CmdConnection::unlisten((*i)->getString());
	}
    } else if (method == "save_current") {
	if (!serv.settings.setting_is_preset()) {
	    throw RpcError(-32001, "no current preset");
	}
	save_preset(serv.settings, serv.settings.get_current_bank(), serv.settings.get_current_name());
    } else if (method == "save_preset") {
	save_preset(serv.settings, params[0]->getString(), params[1]->getString());
    } else {
	throw RpcError(-32601, "Method not found");
    }
}

void CmdConnection::write_error(int code, const char *message) {
    jw.write_key("error");
    jw.begin_object();
    jw.write_key("code");
    jw.write(code);
    jw.write_key("message");
    jw.write(message);
    jw.end_object();
}

bool CmdConnection::request(bool batch_start) {
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
    if (method.empty()) {
	throw RpcError(-32600,"Invalid Request");
    }
    if (id.empty()) {
	try {
	    notify(method, params);
	} catch(RpcError& e) {
	    error_response(e.code, e.message);
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
	try {
	    call(method, params);
	} catch(RpcError& e) {
	    write_error(e.code, e.message);
	}
	jw.end_object();
	return true;
    }
}

void CmdConnection::error_response(int code, const char *message) {
    jw.begin_object();
    jw.write_key("jsonrpc");
    jw.write("2.0");
    jw.write_key("id");
    jw.write_null();
    write_error(code, message);
    jw.end_object();
    os << endl;
    jw.reset();
}

bool CmdConnection::on_data(Glib::IOCondition cond) {
    if (cond != Glib::IO_IN) {
	delete this;
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
	    delete this;
	    return false;
	}
	if (n <= 0) {
	    delete this;
	    return false;
	}
	char *p = buf;
	while (n-- > 0) {
	    inbuf.sputc(*p);
	    if (*p == '\n') {
		istringstream is;
		is.ios::rdbuf(&inbuf);
		process(is);
	    }
	    p++;
	}
    }
}

void CmdConnection::process(istringstream& is) {
    try {
	jp.set_stream(&is);
	bool resp = false;
	is >> ws; // jp.peek() doesn't work at start of stream
	if (is.peek() == '[') {
	    jp.next(gx_system::JsonParser::begin_array);
	    while (jp.peek() != gx_system::JsonParser::end_array) {
		resp = request(!resp) || resp;
	    }
	    if (resp) {
		jw.end_array();
	    }
	    jp.next(gx_system::JsonParser::end_array);
	} else {
	    resp = request(false);
	}
	jp.reset();
	if (resp) {
	    os << endl;
	    jw.reset();
	}
	return;
    } catch (gx_system::JsonException& e) {
	error_response(-32700, "Parse Error");
    } catch (RpcError& e) {
	error_response(e.code, e.message);
    }
    char buf[101];
    is.seekg(0);
    is.read(buf, sizeof(buf)-1);
    gsize n = is.gcount();
    if (n == 0) {
	return;
    }
    buf[n] = '\0';
    gx_system::gx_print_error("JSON-RPC", Glib::ustring("error: skipped text: ")+buf);
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
      switcher_signal(&jack_.get_engine().get_ui(),
		      &settings_.get_param()["ui.live_play_switcher"].getBool().get_value()), //FIXME
      oldest_unsaved(0),
      last_change(0),
      save_conn() {
    switcher_signal.changed.connect(sigc::mem_fun(this, &MyService::on_switcher_toggled));
    tuner_switcher.signal_selection_done().connect(sigc::mem_fun(this, &MyService::on_selection_done));
    add_inet_port(port);
}

//FIXME: this belongs into GxSettings
void MyService::save_state() {
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

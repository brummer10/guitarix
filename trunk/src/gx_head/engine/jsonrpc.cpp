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
public:
    static boost::shared_ptr<JsonValue> create(gx_system::JsonParser& jp);
    virtual void writeJSON(gx_system::JsonWriter& jw) = 0;
};

typedef std::vector<boost::shared_ptr<JsonValue> > jsonarray;

class JsonString: public JsonValue {
public:
    Glib::ustring string;
    JsonString(Glib::ustring s): JsonValue(), string(s) {}
    virtual void writeJSON(gx_system::JsonWriter& jw);
};

class JsonFloat: public JsonValue {
public:
    double value;
    JsonFloat(double v): value(v) {}
    virtual void writeJSON(gx_system::JsonWriter& jw);
};

class JsonInt: public JsonValue {
public:
    int value;
    JsonInt(int v): value(v) {}
    virtual void writeJSON(gx_system::JsonWriter& jw);
};

boost::shared_ptr<JsonValue> JsonValue::create(gx_system::JsonParser& jp) {
    if (jp.peek() == gx_system::JsonParser::value_string) {
	jp.next();
	return boost::shared_ptr<JsonValue>(new JsonString(jp.current_value()));
    } else if (jp.peek() == gx_system::JsonParser::value_number) {
	jp.next();
	const char *str = jp.current_value().c_str();
	char *endptr;
	int n = strtol(str, &endptr, 10);
	if (*endptr == '\0') {
	    return boost::shared_ptr<JsonValue>(new JsonInt(n));
	} else {
	    return boost::shared_ptr<JsonValue>(new JsonFloat(atof(str)));
	}
    } else {
	throw gx_system::JsonException("unexpected token");
    }
}

void JsonString::writeJSON(gx_system::JsonWriter& jw) {
    jw.write(string);
}

void JsonFloat::writeJSON(gx_system::JsonWriter& jw) {
    jw.write(value);
}

void JsonInt::writeJSON(gx_system::JsonWriter& jw) {
    jw.write(value);
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
    __gnu_cxx::stdio_filebuf<char> filebuf;
    istream is;
    gx_system::JsonParser jp;
    __gnu_cxx::stdio_filebuf<char> writebuf;
    ostream os;
    gx_system::JsonWriter jw;
    void exec(Glib::ustring cmd);
    void call(Glib::ustring& method, jsonarray& params);
    void notify(Glib::ustring& method, jsonarray& params);
    bool request(bool batch_start);
    void write_error(int code, const char *message);
    void write_error(int code, Glib::ustring& message) { write_error(code, message.c_str()); }
    void error_response(int code, const char *message);
    void error_response(int code, Glib::ustring& message) { error_response(code, message.c_str()); }
    void preset_changed();
    void send_notify(bool start, const char *method = 0);
    void on_engine_state_change(gx_engine::GxEngineState state);
    void write_engine_state(gx_engine::GxEngineState s);
    void on_tuner_freq_changed();
    void display(const Glib::ustring& bank, const Glib::ustring& preset);
    void set_display_state(TunerSwitcher::SwitcherState newstate);
    void on_selection_done();
public:
    CmdConnection(MyService& serv, const Glib::RefPtr<Gio::SocketConnection>& connection_);
    ~CmdConnection() {}
    bool on_data(Glib::IOCondition cond);
};

CmdConnection::CmdConnection(MyService& serv_, const Glib::RefPtr<Gio::SocketConnection>& connection_)
    : serv(serv_),
      connection(connection_),
      filebuf(connection->get_socket()->get_fd(), std::ios::in),
      is(&filebuf),
      jp(&is),
      writebuf(connection->get_socket()->get_fd(), std::ios::out),
      os(&writebuf),
      jw(&os) {
    serv.settings.signal_selection_changed().connect(
	sigc::mem_fun(*this, &CmdConnection::preset_changed));
    serv.jack.get_engine().signal_state_change().connect(
	sigc::mem_fun(*this, &CmdConnection::on_engine_state_change));
    serv.jack.get_engine().tuner.signal_freq_changed().connect(
	    sigc::mem_fun(this, &CmdConnection::on_tuner_freq_changed));
    serv.tuner_switcher.signal_display().connect(sigc::mem_fun(this, &CmdConnection::display));
    serv.tuner_switcher.signal_set_state().connect(sigc::mem_fun(this, &CmdConnection::set_display_state));
    serv.tuner_switcher.signal_selection_done().connect(sigc::mem_fun(this, &CmdConnection::on_selection_done));
}

void CmdConnection::send_notify(bool start, const char *method) {
    if (start) {
	jw.begin_object();
	jw.write_key("jsonrpc");
	jw.write("2.0");
	jw.write_key("method");
	jw.write(method);
	jw.write_key("params");
	jw.begin_array();
    } else {
	jw.end_array();
	jw.end_object();
	os << endl;
	jw.reset();
    }
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
    send_notify(true, "show_tuner");
    jw.write(serv.tuner_switcher.deactivate());
    send_notify(false);
}

void CmdConnection::on_engine_state_change(gx_engine::GxEngineState state) {
    send_notify(true, "state_changed");
    write_engine_state(state);
    send_notify(false);
}

void CmdConnection::preset_changed() {
    send_notify(true, "preset_changed");
    if (serv.settings.setting_is_preset()) {
	jw.write(serv.settings.get_current_bank());
	jw.write(serv.settings.get_current_name());
    }
    send_notify(false);
}

void CmdConnection::on_tuner_freq_changed() {
    send_notify(true, "tuner_changed");
    //jw.write_key("frequency");
    jw.write(serv.jack.get_engine().tuner.get_freq());
    //jw.write_key("note");
    jw.write(serv.jack.get_engine().tuner.get_note());
    send_notify(false);
}

void CmdConnection::display(const Glib::ustring& bank, const Glib::ustring& preset) {
    send_notify(true, "display_bank_preset");
    jw.write(bank);
    jw.write(preset);
    send_notify(false);
}

void CmdConnection::set_display_state(TunerSwitcher::SwitcherState state) {
    send_notify(true, "set_display_state");
    switch (state) {
    case TunerSwitcher::normal_mode: jw.write("normal_mode"); break;
    case TunerSwitcher::wait_start: jw.write("wait_start"); break;
    case TunerSwitcher::listening: jw.write("listening"); break;
    case TunerSwitcher::wait_stop: jw.write("wait_stop"); break;
    default: assert(false); break;
    }
    send_notify(false);
}

static bool do_reset = true;

void CmdConnection::call(Glib::ustring& method, jsonarray& params) {
    static const char *cmds[] = {
	"get","set","banks","presets","setpreset","getstate","setstate",
	"switch_tuner","get_tuning","get_max_input_level","get_max_output_level",
	"shutdown","stop","rtload","desc","list","help",
	0
    };
    if (method == "get") {
	gx_engine::ParamMap& param = serv.settings.get_param();
	jw.write_key("result");
	jw.begin_object();
	for (jsonarray::iterator i = params.begin(); i != params.end(); ++i) {
	    Glib::ustring& attr = boost::dynamic_pointer_cast<JsonString>(*i)->string;
	    if (!param.hasId(attr)) {
		jw.write_key(attr);
		if (attr == "sys.active_mono_plugins") {
		    list<gx_engine::Plugin*> l;
		    serv.jack.get_engine().pluginlist.ordered_mono_list(l, PGN_MODE_NORMAL);
		    jw.begin_array();
		    for (list<gx_engine::Plugin*>::iterator i = l.begin(); i != l.end(); ++i) {
			jw.write((*i)->pdef->id);
		    }
		    jw.end_array();
		} else if (attr == "sys.active_stereo_plugins") {
		    list<gx_engine::Plugin*> l;
		    serv.jack.get_engine().pluginlist.ordered_stereo_list(l, PGN_MODE_NORMAL);
		    jw.begin_array();
		    for (list<gx_engine::Plugin*>::iterator i = l.begin(); i != l.end(); ++i) {
			jw.write((*i)->pdef->id);
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
    } else if (method == "banks") {
	gx_system::PresetBanks& banks = serv.settings.banks;
	jw.write_key("result");
	jw.begin_array();
	for (gx_system::PresetBanks::iterator i = banks.begin(); i != banks.end(); ++i) {
	    jw.write(i->get_name());
	}
	jw.end_array();
    } else if (method == "presets") {
	gx_system::PresetFile* pf = serv.settings.banks.get_file(boost::dynamic_pointer_cast<JsonString>(params[0])->string);
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
    } else if (method == "desc") {
	gx_engine::ParamMap& param = serv.settings.get_param();
	jw.write_key("result");
	jw.begin_object();
	for (jsonarray::iterator i = params.begin(); i != params.end(); ++i) {
	    Glib::ustring& attr = boost::dynamic_pointer_cast<JsonString>(*i)->string;
	    jw.write_key(attr);
	    if (!param.hasId(attr)) {
		jw.write("unknown");
		continue;
	    }
	    const gx_engine::Parameter& p = param[attr];
	    jw.begin_object();
	    if (p.hasRange()) {
		jw.write_key("lower_bound");
		jw.write(p.getLowerAsFloat());
		jw.write_key("upper_bound");
		jw.write(p.getUpperAsFloat());
	    }
	    jw.write_key("name");
	    jw.write(p.l_name());
	    jw.write_key("group");
	    jw.write(p.l_group());
	    jw.write_key("type");
	    jw.write(p.get_typename());
	    jw.end_object();
	}
	jw.end_object();
    } else if (method == "list") {
	Glib::ustring prefix = boost::dynamic_pointer_cast<JsonString>(params[0])->string;
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

void CmdConnection::notify(Glib::ustring& method, jsonarray& params) {
    if (method == "set") {
	gx_engine::ParamMap& param = serv.settings.get_param();
	jp.next(gx_system::JsonParser::begin_object);
	Glib::ustring& attr = boost::dynamic_pointer_cast<JsonString>(params[0])->string;
	if (param.hasId(attr)) {
	    gx_engine::Parameter& p = param[attr];
	    if (p.isFloat()) {
		p.getFloat().set(boost::dynamic_pointer_cast<JsonFloat>(params[1])->value);
	    } else if (p.isInt()) {
		p.getInt().set(boost::dynamic_pointer_cast<JsonInt>(params[1])->value);
	    } else if (p.isUInt()) {
		p.getInt().set(boost::dynamic_pointer_cast<JsonInt>(params[1])->value);
	    } else if (p.isBool()) {
		p.getInt().set(boost::dynamic_pointer_cast<JsonInt>(params[1])->value);
	    } else if (p.isSwitch()) {
		p.getInt().set(boost::dynamic_pointer_cast<JsonInt>(params[1])->value);
	    } else if (p.isFile()) {
		p.getInt().set(boost::dynamic_pointer_cast<JsonInt>(params[1])->value);
	    } else if (p.isString()) {
		p.getInt().set(boost::dynamic_pointer_cast<JsonInt>(params[1])->value);
	    }
	}
    } else if (method == "setpreset") {
	gx_system::PresetFile* pf = serv.settings.banks.get_file(boost::dynamic_pointer_cast<JsonString>(params[0])->string);
	serv.settings.load_preset(pf, boost::dynamic_pointer_cast<JsonString>(params[1])->string);
    } else if (method == "setstate") {
	Glib::ustring &p = boost::dynamic_pointer_cast<JsonString>(params[0])->string;
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
	boost::shared_ptr<JsonInt> p = boost::dynamic_pointer_cast<JsonInt>(params[0]);
	if (!p) {
	    throw RpcError(-32602, "Invalid params");
	}
	serv.jack.get_engine().tuner.used_for_livedisplay(p->value);
	serv.jack.get_engine().check_module_lists();
    } else if (method == "switch") {
	serv.on_switcher_toggled(true);
    } else if (method == "shutdown") {
	connection->close();
	serv.loop->quit();
    } else if (method == "stop") {
	do_reset = false;
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
    jsonarray params;
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
		    params.push_back(JsonValue::create(jp));
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
	} catch(RpcError&) {
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
    try {
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
	return true;
    } catch (gx_system::JsonExceptionEOF& e) {
	delete this;
	return false;
    } catch (gx_system::JsonException& e) {
	error_response(-32700, "Parse Error");
    } catch (RpcError& e) {
	error_response(e.code, e.message);
    }
    char buf[101];
    gsize n = connection->get_input_stream()->read(buf, sizeof(buf)-1);
    if (n == 0) {
	delete this;
	return false;
    }
    buf[n] = '\0';
    gx_system::gx_print_error("JSON-RPC", Glib::ustring("error: skipped text: ")+buf);
    return true;
}


/****************************************************************
 ** class MyService
 */

MyService::MyService(gx_preset::GxSettings& settings_, gx_jack::GxJack& jack_,
		     Glib::RefPtr<Glib::MainLoop>& loop_)
    : Gio::SocketService(),
      settings(settings_),
      jack(jack_),
      loop(loop_),
      tuner_switcher(settings_, jack_.get_engine()),
      switcher_signal(&jack_.get_engine().get_ui(),
		      &gx_engine::parameter_map["ui.live_play_switcher"].getBool().get_value()) { //FIXME
    switcher_signal.changed.connect(sigc::mem_fun(this, &MyService::on_switcher_toggled));
    tuner_switcher.signal_selection_done().connect(sigc::mem_fun(this, &MyService::on_selection_done));
    add_inet_port(7000);
}

bool MyService::on_incoming(const Glib::RefPtr<Gio::SocketConnection>& connection,
			    const Glib::RefPtr<Glib::Object>& source_object) {
    CmdConnection *cc = new CmdConnection(*this, connection);
    Glib::signal_io().connect(sigc::mem_fun(cc, &CmdConnection::on_data),
			      connection->get_socket()->get_fd(), Glib::IO_IN);
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

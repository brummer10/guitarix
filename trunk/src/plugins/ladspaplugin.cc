#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <fstream>
#include <dlfcn.h>
#include <ladspa.h>

#include <giomm.h> // for create_list()
#include "gx_plugin.h"

//#define HARD_RT_ONLY

template <class T>
inline std::string to_string(const T& t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

/****************************************************************
 ** JSON reader
 */

class JsonException: public std::exception {
private:
    std::string what_str;
public:
    JsonException(const char* desc);
    ~JsonException() throw() { }
    virtual const char* what() const throw() { return what_str.c_str(); }
};

class JsonParser {
public:
    JsonParser(std::istream* i = 0);
    virtual ~JsonParser();
    virtual void close();
    bool is_closed() { return !is; }
    void set_stream(std::istream* i) { is = i; }
    enum token {
        no_token, end_token, begin_object, end_object, begin_array, end_array,
        value_string, value_number, value_key };
    static const char* token_names[];
    bool good() { return is->good(); }
    token next(token expect = no_token);
    token peek() { return next_tok; }
    std::streampos get_streampos() { return next_pos + std::streamoff(-1); }
    void set_streampos(std::streampos pos);
    void check_expect(token expect) { if (cur_tok != expect) throw_unexpected(expect); }
    inline std::string current_value() const { return str; }
    int current_value_int() { return atoi(str.c_str()); }
    unsigned int current_value_uint() { return atoi(str.c_str()); }
    float current_value_float() {
	std::istringstream b(str);
        float f;
        b >> f;
        return f;
    }
    double current_value_double() {
        std::istringstream b(str);
        double d;
        b >> d;
        return d;
    }
    void skip_object();
private:
    std::istream* is;
    int depth;
    token cur_tok;
    std::string str;
    bool nl;
    int next_depth;
    token next_tok;
    std::string next_str;
    std::streampos next_pos;
    const char* readcode();
    std::string readstring();
    std::string readnumber(char c);
    void read_next();
    void throw_unexpected(token expect);
};

/****************************************************************/

const char* JsonParser::token_names[] = {
    "no_token", "end_token", "begin_object", "end_object",
    "begin_array", "end_array", "value_string", "value_number",
    "value_key" };

JsonException::JsonException(const char* desc) {
    what_str = std::string("Json parse error: ") + desc;
}

JsonParser::JsonParser(std::istream* i)
    : is(i),
      depth(0),
      cur_tok(no_token),
      nl(false),
      next_depth(0),
      next_tok(no_token) {}

JsonParser::~JsonParser() {
    close();
}

void JsonParser::close() {
    if (is_closed()) {
	return;
    }
    is = 0;
}

void JsonParser::throw_unexpected(token expect) {
    std::ostringstream b;
    b << "unexpected token: " << token_names[cur_tok]
      << " (expected: " << token_names[expect] << ")"
      << std::endl;
    throw JsonException(b.str().c_str());
}

const char* unicode2utf8(unsigned int input) {
    const int maskbits   = 0x3F;
    const int maskbyte   = 0x80;
    const int mask2bytes = 0xC0;
    const int mask3bytes = 0xE0;
    static char result[4];
    int n = 0;
    // 0xxxxxxx
    if (input < 0x80) {
        result[n++] = static_cast<char>(input);

	// 110xxxxx 10xxxxxx
    } else if (input < 0x800) {
        result[n++] = (static_cast<char>(mask2bytes | (input >> 6)));
        result[n++] = (static_cast<char>(maskbyte | (input & maskbits)));

	// 1110xxxx 10xxxxxx 10xxxxxx
    } else {
        result[n++] = (static_cast<char>(mask3bytes | (input >> 12)));
        result[n++] = (static_cast<char>(maskbyte | ((input >> 6) & maskbits)));
        result[n++] = (static_cast<char>(maskbyte | (input & maskbits)));
    }
    result[n++] = '\0';
    return result;
}

const char* JsonParser::readcode() {
    int code = 0;
    for (int i = 0; i < 4; i++) {
        int n = is->get();
        if (!is->good())
            throw JsonException("eof");
        if ('0' <= n && n <= '9')
            n = n - '0';
        else
            n = 10 + (toupper(n) - 'A');
        code = code * 16 + n;
    }
    return unicode2utf8(code);
}

std::string JsonParser::readstring() {
    std::ostringstream os("");
    char c;
    do {
        is->get(c);
        if (!is->good())
            return "";
        if (c == '\\') {
            is->get(c);
            if (!is->good())
                return "";
            switch (c) {
            case 'b': os << '\b'; break;
            case 'f': os << '\f'; break;
            case 'n': os << '\n'; break;
            case 'r': os << '\r'; break;
            case 't': os << '\t'; break;
	    case '"': os << '"'; break;
            case 'u': os << readcode(); break;
            default: is->get(c); os << c; break;
            }
        } else if (c == '"') {
            return os.str();
        } else {
            os << c;
        }
    } while (true);
}

std::string JsonParser::readnumber(char c) {
    std::ostringstream os("");
    do {
        os << c;
        c = is->peek();
        switch (c) {
        case '+': case '-': case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': case 'e': case 'E':
        case '.':
            break;
        default:
            return os.str();
        }
        is->get(c);
    } while (is->good());
    return "";
}

void JsonParser::read_next() {
    if (next_tok == end_token)
        return;
    if (next_tok != no_token and next_depth == 0) {
        next_tok = end_token;
        return;
    }
    char c;
    nl = false;
    while (true) {
        do {
            is->get(c);
            if (!is->good())
                throw JsonException("eof");
            if (c == '\n')
                nl = true;
        } while (c == ' ' || c == '\t' || c == '\r' || c == '\n');
	next_pos = is->tellg();
        switch (c) {
        case '[': next_tok = begin_array; next_depth++; break;

        case ']': next_tok = end_array; next_depth--; break;

        case '{': next_tok = begin_object; next_depth++; break;

        case '}': next_tok = end_object; next_depth--; break;

        case ',': continue;

        case '"':
            next_str = readstring();
            *is >> c;
            if (!is->good())
                throw JsonException("eof");
            if (c == ':') {
                next_tok = value_key;
            } else {
                is->unget();
                next_tok = value_string;
            }
            break;

        case '-': case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            next_str = readnumber(c);
            next_tok = value_number;
            break;

        default:
            throw JsonException("bad token");
        }
        break;
    }
}

JsonParser::token JsonParser::next(token expect) {
    if (cur_tok != end_token) {
        if (next_tok == no_token)
            read_next();
        depth = next_depth;
        cur_tok = next_tok;
        str = next_str;
        if (next_tok != end_token)
            read_next();
    }
    if (expect != no_token)
        check_expect(expect);
    return cur_tok;
}

void JsonParser::set_streampos(std::streampos pos) {
    is->seekg(pos);
    depth = 0;
    cur_tok = no_token;
    nl = false;
    next_depth = 0;
    next_tok = no_token;
}

void JsonParser::skip_object() {
    int curdepth = depth;
    do {
        if (next() == end_token) {
            throw JsonException("unexpected eof");
        }
    } while (curdepth != depth);
}


/****************************************************************
 ** LadspaDsp
 */

enum widget_type { tp_scale, tp_scale_log, tp_toggle, tp_enum, tp_display, tp_display_toggle, tp_none };

struct paradesc {
    int index;
    std::string name;
    float dflt;
    float low;
    float up;
    float step;
    widget_type tp;
    bool newrow;
    value_pair* values;
    paradesc(): index(), name(), dflt(), low(), up(), step(), tp(), newrow(), values() {}
};

struct plugdesc {
    std::string path;
    unsigned int index;
    unsigned long UniqueID;
    std::string Label;
    std::string shortname;
    std::string category;
    std::vector<paradesc> names;
};

class port_data {
public:
    LADSPA_Data port;
    std::string id;
    port_data(): port(), id() {}
};

class LadspaDsp: public PluginDef {
private:
    static void init(unsigned int samplingFreq, PluginDef *plugin);
    static void mono_process(int count, float *input, float *output, PluginDef *plugin);
    static void stereo_process(int count, float *input1, float *input2, float *output1, float *output2, PluginDef *plugin);
    static int registerparam(const ParamReg& reg);
    static int uiloader(const UiBuilder& builder);
    static void del_instance(PluginDef *plugin);
    static void write_file(const std::string& path);
    static void make_menu(const LADSPA_Descriptor * psDescriptor, const Glib::ustring& str, unsigned long lPluginIndex);
    //
    const LADSPA_Descriptor *desc;
    void *handle;
    LADSPA_Handle instance;
    port_data *ctrl_ports;
    std::string id_str;
    Glib::ustring name_str;
    const plugdesc& pd;
    void activate();
    void connect(int tp, int i, float *v);
    LadspaDsp(const plugdesc& plug, void *handle_, const LADSPA_Descriptor *desc_, int num_ctrl, bool mono);
    ~LadspaDsp();
public:
    static void create_list();
    static LadspaDsp *create(const plugdesc& plug);
};

LadspaDsp *LadspaDsp::create(const plugdesc& plug) {
    void *handle;
    handle = dlopen(plug.path.c_str(), RTLD_LOCAL|RTLD_NOW);
    if (!handle) {
	printf("Cannot open plugin: %s [%s]\n", plug.path.c_str(), dlerror());
	return NULL;
    }
    LADSPA_Descriptor_Function ladspa_descriptor = (LADSPA_Descriptor_Function)dlsym(handle, "ladspa_descriptor");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
	printf("Cannot load symbol 'ladspa_descriptor': %s\n", dlsym_error);
	dlclose(handle);
	handle = 0;
	return NULL;
    }
    const LADSPA_Descriptor *desc = ladspa_descriptor(plug.index);
    if (!desc) {
	printf("Cannot load ladspa descriptor #%d from %s\n", plug.index, plug.path.c_str());
	dlclose(handle);
	handle = 0;
	return NULL;
    }
    if (desc->UniqueID == 4069 || desc->UniqueID == 4070) {
	printf("ladspa_guitarix not loaded\n");
	dlclose(handle);
	handle = 0;
	return NULL;
    }
#ifdef HARD_RT_ONLY
    if (!LADSPA_IS_HARD_RT_CAPABLE(desc->Properties)) {
	printf("plugin %s is not hard RT capable\n", desc->Label);
	dlclose(handle);
	handle = 0;
	return NULL;
    }
#endif
    int num_ctrl = 0;
    int num_inputs = 0;
    int num_outputs = 0;
    for (unsigned int i = 0; i < desc->PortCount; ++i) {
	if (LADSPA_IS_PORT_CONTROL(desc->PortDescriptors[i])) {
	    num_ctrl += 1;
	} else if (LADSPA_IS_PORT_INPUT(desc->PortDescriptors[i])) {
	    num_inputs += 1;
	} else if (LADSPA_IS_PORT_OUTPUT(desc->PortDescriptors[i])) {
	    num_outputs += 1;
	}
    }
    bool mono;
    if (num_inputs == 1 && num_outputs == 1) {
	mono = true;
    } else if (num_inputs == 2 && num_outputs == 2) {
	mono = false;
    } else {
	printf("cannot use ladspa plugin %s with %d inputs and %d outputs\n", desc->Label, num_inputs, num_outputs);
	dlclose(handle);
	handle = 0;
	return NULL;
    }
    return new LadspaDsp(plug, handle, desc, num_ctrl, mono);
}

LadspaDsp::LadspaDsp(const plugdesc& plug, void *handle_, const LADSPA_Descriptor *desc_, int num_ctrl, bool mono)
    : PluginDef(), desc(desc_), handle(handle_), instance(), ctrl_ports(), id_str(), name_str(), pd(plug) {
    ctrl_ports = new port_data[num_ctrl];
    version = PLUGINDEF_VERSION;
    id_str = "ladspa_";
    id_str += to_string(desc->UniqueID);
    id = id_str.c_str();
    category = pd.category.c_str();
    description = desc->Name;
    name = desc->Name;
    if (!pd.shortname.empty()) {
	shortname = pd.shortname.c_str();
    } else {
	name_str = desc->Name;
	if (name_str.size() > 24) {
	    name_str.erase(24);
	}
	shortname = name_str.c_str();
    }
    set_samplerate = init;
    if (mono) {
	mono_audio = mono_process;
    } else {
	stereo_audio = stereo_process;
    }
    register_params = registerparam;
    load_ui = uiloader;
    delete_instance = del_instance;
}

LadspaDsp::~LadspaDsp() {
    if (instance) {
	//FIXME: deactivate
	desc->cleanup(instance);
    }
    if (handle) {
	dlclose(handle);
    }
    delete[] ctrl_ports;
}

void LadspaDsp::activate() {
    if (desc->activate) {
	desc->activate(instance);
    }
}

void LadspaDsp::connect(int tp, int i, float *v) {
    for (unsigned int n = 0; n < desc->PortCount; ++n) {
	if (!LADSPA_IS_PORT_AUDIO(desc->PortDescriptors[n])) {
	    continue;
	}
	if (desc->PortDescriptors[n] & tp) {
	    if (i == 0) {
		desc->connect_port(instance, n, v);
		return;
	    }
	    i -= 1;
	}
    }
    printf("audio port not found\n");
}

void LadspaDsp::init(unsigned int samplingFreq, PluginDef *plugin) {
    LadspaDsp& self = *static_cast<LadspaDsp*>(plugin);
    if (self.instance) {
	self.desc->cleanup(self.instance);
    }
    self.instance = self.desc->instantiate(self.desc, samplingFreq);
    if (self.pd.names.size() > 0) {
	int n = 0;
	for (std::vector<paradesc>::const_iterator it = self.pd.names.begin(); it != self.pd.names.end(); ++it, ++n) {
	    self.desc->connect_port(self.instance, it->index, &self.ctrl_ports[n].port);
	}
    } else {
	int n = 0;
	for (unsigned int i = 0; i < self.desc->PortCount; ++i) {
	    if (LADSPA_IS_PORT_CONTROL(self.desc->PortDescriptors[i])) {
		self.desc->connect_port(self.instance, i, &self.ctrl_ports[n].port);
		n += 1;
	    }
	}
    }
    self.activate();
}

void LadspaDsp::mono_process(int count, float *input, float *output, PluginDef *plugin) {
    LadspaDsp& self = *static_cast<LadspaDsp*>(plugin);
    self.connect(LADSPA_PORT_INPUT, 0, input);
    self.connect(LADSPA_PORT_OUTPUT, 0, output);
    self.desc->run(self.instance, count);
}

void LadspaDsp::stereo_process(int count, float *input1, float *input2, float *output1, float *output2, PluginDef *plugin) {
    LadspaDsp& self = *static_cast<LadspaDsp*>(plugin);
    self.connect(LADSPA_PORT_INPUT, 0, input1);
    self.connect(LADSPA_PORT_INPUT, 1, input2);
    self.connect(LADSPA_PORT_OUTPUT, 0, output1);
    self.connect(LADSPA_PORT_OUTPUT, 1, output2);
    self.desc->run(self.instance, count);
}

static void get_bounds(const LADSPA_PortRangeHint& pr, float& dflt, float& low, float& up, float& step) {
    const LADSPA_PortRangeHintDescriptor& hd = pr.HintDescriptor;
    if (LADSPA_IS_HINT_TOGGLED(hd)) {
	low = 0;
	up = 1;
	step = 1;
	dflt = 0;
	if (LADSPA_IS_HINT_HAS_DEFAULT(hd) && LADSPA_IS_HINT_DEFAULT_1(hd)) {
	    dflt = 1;
	}
	return;
    }

    /*
    ** bounds
    */
    int samplefreq = 44100; // fixed frequency for rate dependent lower and upper bounds

    if (LADSPA_IS_HINT_BOUNDED_BELOW(hd)) {
	low = pr.LowerBound;
	if (LADSPA_IS_HINT_SAMPLE_RATE(hd)) {
	    low *= samplefreq;
	}
    }
    if (LADSPA_IS_HINT_LOGARITHMIC(hd)) {
	if (low <= 0) {
	    low = up / 1000.0;
	}
    }
    if (LADSPA_IS_HINT_BOUNDED_ABOVE(hd)) {
	up = pr.UpperBound;
	if (LADSPA_IS_HINT_SAMPLE_RATE(hd)) {
	    up *= samplefreq;
	}
	if (low >= up) {
	    low = up - 1;
	}
    }
    if (low >= up) {
	up = low + 1;
    }
    if (LADSPA_IS_HINT_INTEGER(hd)) {
	step = 1.0;
    } else if (LADSPA_IS_HINT_LOGARITHMIC(hd)) {
	step = pow(up/low, 1.0/200);
    } else {
	step = (up - low) / 100;
	if (step > 1.0) {
	    step = 1.0;
	} else {
	    step = pow(10, floor(log10(step)));
	}
    }

    /*
    ** default value
    */
    if (!LADSPA_IS_HINT_HAS_DEFAULT(hd)) {
	dflt = 0;
    } else if (LADSPA_IS_HINT_DEFAULT_MINIMUM(hd)) {
	dflt = low;
    } else if (LADSPA_IS_HINT_DEFAULT_LOW(hd)) {
	if (LADSPA_IS_HINT_LOGARITHMIC(hd)) {
	    dflt = exp(log(low) * 0.75 + log(up) * 0.25);
	} else {
	    dflt = low * 0.75 + up * 0.25;
	}
    } else if (LADSPA_IS_HINT_DEFAULT_MIDDLE(hd)) {
	if (LADSPA_IS_HINT_LOGARITHMIC(hd)) {
	    dflt = exp(log(low) * 0.5 + log(up) * 0.5);
	} else {
	    dflt = low * 0.5 + up * 0.5;
	}
    } else if (LADSPA_IS_HINT_DEFAULT_HIGH(hd)) {
	if (LADSPA_IS_HINT_LOGARITHMIC(hd)) {
	    dflt = exp(log(low) * 0.25 + log(up) * 0.75);
	} else {
	    dflt = low * 0.25 + up * 0.75;
	}
    } else if (LADSPA_IS_HINT_DEFAULT_MAXIMUM(hd)) {
	dflt = up;
    } else if (LADSPA_IS_HINT_DEFAULT_0(hd)) {
	dflt = 0;
    } else if (LADSPA_IS_HINT_DEFAULT_1(hd)) {
	dflt = 1;
    } else if (LADSPA_IS_HINT_DEFAULT_100(hd)) {
	dflt = 100;
    } else if (LADSPA_IS_HINT_DEFAULT_440(hd)) {
	dflt = 440;
    }

    if (dflt < low) {
	low = dflt;
    } else if (dflt > up) {
	dflt = up;
    }
}

static Glib::ustring TrimLabel(const char *label) {
    Glib::ustring pn(label);
    unsigned int rem = pn.find_first_of("([");
    if(rem != Glib::ustring::npos) {
	pn.erase(rem);
    }
    while ((rem = pn.find_last_of(" ")) == pn.size()-1) {
	pn.erase(rem);
    }
    rem = 0;
    unsigned int rem1 = 0;
    unsigned int lastpos = 0;
    while (true) {
	rem1 = pn.find_first_of(" ", rem1);
	if (rem1 == Glib::ustring::npos) {
	    rem1 = pn.size();
	}
	while (rem1 > rem + 8) {
	    if (lastpos > rem) {
		rem = lastpos;
		pn.replace(lastpos, 1, 1, '\n');
	    } else if (rem1 < rem + 13) {
		if (rem1 == pn.size()) {
		    break;
		}
		rem = rem1;
		pn.replace(rem1, 1, 1, '\n');
	    } else {
		rem += 10;
		pn.insert(rem, "\n");
	    }
	    rem += 1;
	}
	lastpos = rem1;
	rem1 += 1;
	if (rem1 >= pn.size()) {
	    break;
	}
    }
    return pn;
}

int LadspaDsp::registerparam(const ParamReg& reg) {
    LadspaDsp& self = *static_cast<LadspaDsp*>(reg.plugin);
    if (self.pd.names.size() > 0) {
	int n = 0;
	for (std::vector<paradesc>::const_iterator it = self.pd.names.begin(); it != self.pd.names.end(); ++it, ++n) {
	    std::string& s = self.ctrl_ports[n].id;
	    s = "ladspa_" + to_string(self.pd.UniqueID) + "." + to_string(it->index);
	    const char *nm = self.desc->PortNames[it->index];
	    Glib::ustring snm(it->name);
	    if (snm.empty()) {
		snm = TrimLabel(nm);
	    }
	    if (it->tp == tp_enum) {
		reg.registerEnumVar(s.c_str(), snm.c_str(), "S", nm, it->values, &self.ctrl_ports[n].port,
				    it->dflt, it->low, it->up, it->step);
	    } else {
		const char *tp = 0;
		switch (it->tp) {
		case tp_none:           tp = "S";  break;
		case tp_scale:          tp = "S";  break;
		case tp_scale_log:      tp = "SL"; break;
		case tp_toggle:         tp = "B";  break;
		case tp_display:        tp = "SO";  break;
		case tp_display_toggle: tp = "BO"; break;
		default: assert(false);
		}
		reg.registerVar(s.c_str(), snm.c_str(), tp, nm, &self.ctrl_ports[n].port,
				it->dflt, it->low, it->up, it->step);
	    }
	}
    } else {
	int n = 0;
	for (unsigned int i = 0; i < self.desc->PortCount; ++i) {
	    if (!LADSPA_IS_PORT_CONTROL(self.desc->PortDescriptors[i])) {
		continue;
	    }
	    
	    float low = -1000;
	    float up = 1000;
	    float dflt = 0.0;
	    float step = 1.0;
	    if (LADSPA_IS_PORT_OUTPUT(self.desc->PortDescriptors[i])) {
		low = 0;
		up = 8192;
	    }
	    get_bounds(self.desc->PortRangeHints[i], dflt, low, up, step);
	    // replace . and cut label
	    Glib::ustring pn = self.desc->PortNames[i];
	    size_t rem = 0;
	    while (true) {
		rem = pn.find_first_of(".", rem);
		if (rem == Glib::ustring::npos) {
		    break;
		}
		pn.replace(rem, 1, 1, '-');
		rem += 1;
		if (rem >= pn.size()) {
		    break;
		}
	    }
	    rem = pn.find_first_of("([");
	    if(rem != Glib::ustring::npos) {
		pn.erase(rem);
	    }
	    while ((rem = pn.find_last_of(" ")) == pn.size()-1) {
		pn.erase(rem);
	    }
	    std::string& s = self.ctrl_ports[n].id;
	    s = self.id_str + "." + to_string(n) + "_" + pn;
	    const char *nm = pn.c_str();
	    rem = 0;
	    unsigned int rem1 = 0;
	    while (true) {
		rem1 = pn.find_first_of(" ", rem1);
		if (rem1 == Glib::ustring::npos) {
		    break;
		}
		if (rem1 - rem > 5) {
		    pn.replace(rem1, 1, 1, '\n');
		    rem = rem1 + 1;
		}
		rem1 += 1;
		if (rem1 >= pn.size()) {
		    break;
		}
	    }

	    std::string tp = "S";
	    if (LADSPA_IS_HINT_TOGGLED(self.desc->PortRangeHints[i].HintDescriptor)) {
		tp = "B";
	    } else if (LADSPA_IS_HINT_LOGARITHMIC(self.desc->PortRangeHints[i].HintDescriptor)) {
		tp = "SL";
	    }
	    if (LADSPA_IS_PORT_OUTPUT(self.desc->PortDescriptors[i])) {
		tp += "O";
	    }
	    reg.registerVar(s.c_str(),nm,tp.c_str(),self.desc->PortNames[i],
			    &self.ctrl_ports[n].port,dflt,low,up,step);
	    n++;
	}
    }
    return 0;
}

int LadspaDsp::uiloader(const UiBuilder& b) {
    LadspaDsp& self = *static_cast<LadspaDsp*>(b.plugin);
    b.openHorizontalhideBox("");
    b.closeBox();
    if (self.pd.names.size() > 0) {
	b.openVerticalBox("");
	b.openHorizontalBox("");
	int n = 0;
	for (std::vector<paradesc>::const_iterator it = self.pd.names.begin(); it != self.pd.names.end(); ++it, ++n) {
	    if (it->newrow) {
		b.closeBox();
		b.openHorizontalBox("");
	    }
	    switch (it->tp) {
	    case tp_scale:
	    case tp_scale_log:
		b.create_small_rackknob(self.ctrl_ports[n].id.c_str(),0);
		break;
	    case tp_toggle:
		b.openVerticalBox2(it->name.c_str());
		b.create_switch("switch",self.ctrl_ports[n].id.c_str(), 0);
		b.closeBox();
		break;
	    case tp_display:
		b.create_port_display(self.ctrl_ports[n].id.c_str());
		break;
	    case tp_display_toggle:
		b.openVerticalBox2(it->name.c_str());
		b.create_switch_no_caption("led",self.ctrl_ports[n].id.c_str());
		b.closeBox();
		break;
	    case tp_enum:
		b.create_selector(self.ctrl_ports[n].id.c_str(), 0);
		break;
	    case tp_none:
		break;
	    default:
		assert(false);
	    }
	}
	b.closeBox();
	b.closeBox();
    } else {
	const unsigned int max_ctrl = 4;
	if (self.desc->PortCount > max_ctrl) {
	    b.openVerticalBox("");
	    b.openHorizontalBox("");
	}
	int n = 0;
	for (unsigned int i = 0; i < self.desc->PortCount; ++i) {
	    if (!LADSPA_IS_PORT_CONTROL(self.desc->PortDescriptors[i])) {
		continue;
	    }
	    if (n > 0 && n % max_ctrl == 0) {
		b.closeBox();
		b.openHorizontalBox("");
	    }
	    if (LADSPA_IS_PORT_INPUT(self.desc->PortDescriptors[i])) {
		if (LADSPA_IS_HINT_TOGGLED(self.desc->PortRangeHints[i].HintDescriptor)) {
		    b.openVerticalBox2(self.desc->PortNames[i]);
		    b.create_switch_no_caption("switchit",self.ctrl_ports[n].id.c_str());
		    b.closeBox();
		} else {
		    b.create_small_rackknob(self.ctrl_ports[n].id.c_str(),0);
		}
	    } else {
		if (LADSPA_IS_HINT_TOGGLED(self.desc->PortRangeHints[i].HintDescriptor)) {
		    b.openVerticalBox2(self.desc->PortNames[i]);
		    b.create_switch_no_caption("led",self.ctrl_ports[n].id.c_str());
		    b.closeBox();
		} else {
		    b.create_port_display(self.ctrl_ports[n].id.c_str());
		}
	    }
	    n++;
	}
	if (self.desc->PortCount > max_ctrl) {
	    b.closeBox();
	    b.closeBox();
	}
    }
    return 0;
}

void LadspaDsp::del_instance(PluginDef *plugin) {
    delete static_cast<LadspaDsp*>(plugin);
}


std::list<Glib::ustring> ladspa_plug_list;


void LadspaDsp::write_file(const std::string& path) {
    std::ofstream ifs(path.c_str());
    std::list<Glib::ustring>::iterator it;
    ifs << "[ \n";
    for ( it=ladspa_plug_list.begin() ; it != ladspa_plug_list.end(); it++ ){
        ifs << *it;       
    }
    ifs << "\n] ";
    ifs.close();
}

void LadspaDsp::make_menu(const LADSPA_Descriptor * psDescriptor,
                          const Glib::ustring& str, unsigned long lPluginIndex) {

    unsigned long lPortIndex;
    int inputports = 0;
    int outputports = 0;

    for (lPortIndex = 0;  lPortIndex < psDescriptor->PortCount; lPortIndex++) {
	// only mono and stereo plugs are supported
        if  (LADSPA_IS_PORT_AUDIO(psDescriptor->PortDescriptors[lPortIndex]) && 
	     LADSPA_IS_PORT_INPUT(psDescriptor->PortDescriptors[lPortIndex])) {
	    inputports ++;
        } else if  (LADSPA_IS_PORT_AUDIO(psDescriptor->PortDescriptors[lPortIndex]) && 
		    LADSPA_IS_PORT_OUTPUT(psDescriptor->PortDescriptors[lPortIndex])) {
	    outputports ++;
        }
    }
    if ((inputports == 1 && outputports == 1) ||
	(inputports == 2 && outputports == 2)) {
        std::string mono_plug = ",\n";
        mono_plug += "    ";
        mono_plug += "[\"";
        mono_plug += str;
        mono_plug += "\", ";
        mono_plug += to_string(lPluginIndex);
        mono_plug += ", {}]";
        ladspa_plug_list.push_back(mono_plug);
    }
    
}

static bool is_blacklisted(unsigned long id) {
    static unsigned long blacklist[] = {
	4069, 4070,		// ladspa_guitarix
	1044, 1045, 1046, 1047,	// sine
	1912,			// jamincont
    };
    for (unsigned int i = 0; i < sizeof(blacklist) / sizeof(blacklist[0]); i++) {
	if (id == blacklist[i]) {
	    return true;
	}
    }
    return false;
}

static bool lib_is_blacklisted(const std::string& name) {
    static const char *blacklist[] = {
	"dssi-vst.so",
    };
    for (unsigned int i = 0; i < sizeof(blacklist) / sizeof(blacklist[0]); i++) {
	if (name == blacklist[i]) {
	    return true;
	}
    }
    return false;
}

class PathList {
public:
    typedef std::list< Glib::RefPtr<Gio::File> > pathlist;
    typedef std::list< Glib::RefPtr<Gio::File> >::const_iterator iterator;
private:
    pathlist dirs;
public:
    PathList(const char *env_name = 0);
    void add(const std::string& d) { dirs.push_back(Gio::File::create_for_path(d)); }
    bool contains(const std::string& d) const;
    bool find_dir(std::string *d, const std::string& filename) const;
    iterator begin() { return dirs.begin(); }
    iterator end() { return dirs.end(); }
    size_t size() { return dirs.size(); }
};

PathList::PathList(const char *env_name): dirs() {
    if (!env_name) {
	return;
    }
    const char *p = getenv(env_name);
    if (!p) {
	return;
    }
    while (true) {
	const char *q = strchr(p, ':');
	if (q) {
	    int n = q - p;
	    if (n) {
		add(std::string(p, n));
	    }
	    p = q;
	} else {
	    if (*p) {
		add(p);
	    }
	    break;
	}
    }
}

void LadspaDsp::create_list() {
    
    std::string if_path = getenv("HOME");
    if_path += "/.config/guitarix/ladspa_defs.js";
    // to avoid rescan the ladspa path activate this
    std::ifstream ifs(if_path.c_str());
    if (!ifs.fail()) {
        ifs.close();
        return;
    }

    PathList pl("LADSPA_PATH");
    if (!pl.size()) {
        pl.add("/usr/lib/ladspa");
        pl.add("/usr/local/lib/ladspa");
    }
    std::vector<Glib::ustring> file_names;
    for (PathList::iterator it = pl.begin(); it != pl.end(); ++it) {
	Glib::RefPtr<Gio::File> file = *it;
	if (!file->query_exists()) {
	    continue;
	}
	Glib::RefPtr<Gio::FileEnumerator> child_enumeration =
	    file->enumerate_children(G_FILE_ATTRIBUTE_STANDARD_NAME
				     "," G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME
				     "," G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE);
	Glib::RefPtr<Gio::FileInfo> file_info;

        while ((file_info = child_enumeration->next_file()) != 0) {
	    if (file_info->get_attribute_string(G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE) == "application/x-sharedlib") {
		std::string nm = file_info->get_attribute_byte_string(G_FILE_ATTRIBUTE_STANDARD_NAME);
		if (lib_is_blacklisted(nm)) {
		    continue;
		}
		file_names.push_back(Glib::build_filename(file->get_path(), nm));
	    }
        }
    }
    // sort the vector
    std::sort(file_names.begin(), file_names.end());
    std::set<unsigned long> seen;
    for (unsigned int i = 0; i < file_names.size(); i++) {
	Glib::ustring str = file_names[i];
	void *pvPluginHandle = dlopen(str.c_str(), RTLD_LOCAL|RTLD_NOW);
	if (!pvPluginHandle) {
	    continue;
	}
	LADSPA_Descriptor_Function pfDescriptorFunction =
	    (LADSPA_Descriptor_Function)dlsym(pvPluginHandle, "ladspa_descriptor");
	if (!pfDescriptorFunction) {
	    continue;
	}
	for (unsigned long lPluginIndex = 0;; lPluginIndex++) {
	    const LADSPA_Descriptor * psDescriptor = pfDescriptorFunction(lPluginIndex);
	    if (!psDescriptor) {
		break;
	    }
	    if (seen.find(psDescriptor->UniqueID) != seen.end()) {
		continue;
	    }
	    if (is_blacklisted(psDescriptor->UniqueID)) {
		continue;
	    }
#ifdef HARD_RT_ONLY
	    if (!LADSPA_IS_HARD_RT_CAPABLE(psDescriptor->Properties)) {
		continue;
	    }
#endif
	    make_menu(psDescriptor, str, lPluginIndex);
	    seen.insert(psDescriptor->UniqueID);
	}
	dlclose(pvPluginHandle);
    }
    write_file(if_path);
}

std::vector<plugdesc> plugins;

void try_read_module_config(const std::string& filename, plugdesc& p) {
    std::ifstream ifs(filename.c_str());
    if (ifs.fail()) {
        return;
    }
    JsonParser jp(&ifs);
    jp.next(JsonParser::begin_array);
    jp.next(JsonParser::value_number); // version
    jp.next(JsonParser::value_string);
    p.shortname = jp.current_value();
    jp.next(JsonParser::value_string);
    p.category = jp.current_value();
    jp.next(JsonParser::begin_array);
    while (jp.peek() != JsonParser::end_array) {
	paradesc para;
	jp.next(JsonParser::begin_array);
	jp.next(JsonParser::value_number);
	para.index = jp.current_value_int();
	jp.skip_object(); // meta data
	jp.next(JsonParser::value_string);
	para.name = jp.current_value();
	jp.next(JsonParser::value_number); // use_sr
	jp.next(JsonParser::value_number);
	para.dflt = jp.current_value_float();
	jp.next(JsonParser::value_number);
	para.low = jp.current_value_float();
	jp.next(JsonParser::value_number);
	para.up = jp.current_value_float();
	jp.next(JsonParser::value_number);
	para.step = jp.current_value_float();
	jp.next(JsonParser::value_number);
	para.tp = static_cast<widget_type>(jp.current_value_int()); //FIXME
	jp.next(JsonParser::value_number);
	para.newrow = jp.current_value_int();
	jp.next(JsonParser::begin_array);
	std::vector<value_pair> v;
	while (jp.peek() != JsonParser::end_array) {
	    jp.next(JsonParser::value_string);
	    const char *s = g_strdup(jp.current_value().c_str());
	    value_pair p = {s, s};
	    v.push_back(p);
	}
	jp.next(JsonParser::end_array);
	para.values = new value_pair[v.size()+1];
	int n = 0;
	for (std::vector<value_pair>::iterator i = v.begin(); i != v.end(); ++i) {
	    para.values[n++] = *i;
	}
	para.values[n].value_id = 0;
	para.values[n].value_label = 0;
	jp.next(JsonParser::end_array);
	p.names.push_back(para);
    }
    jp.next(JsonParser::end_array);
    jp.close();
    ifs.close();
}

void init() {
    //LadspaDsp::create_list();
    std::string path = Glib::build_filename(Glib::get_user_config_dir(), "guitarix");
    std::ifstream ifs(Glib::build_filename(path, "ladspa_defs.js").c_str());
    if (ifs.fail()) {
        return;
    }
    JsonParser jp(&ifs);
    jp.next(JsonParser::begin_array);
    while (jp.peek() != JsonParser::end_array) {
	jp.next(JsonParser::begin_array);
	jp.next(JsonParser::value_string);
	plugdesc p;
	p.path = jp.current_value();
	jp.next(JsonParser::value_number);
	p.index = jp.current_value_int();
	jp.next(JsonParser::value_number);
	p.UniqueID = jp.current_value_int();
	jp.next(JsonParser::value_string);
	p.Label = jp.current_value();
	jp.next(JsonParser::end_array);
	try_read_module_config(Glib::build_filename(path, "plugins", "ladspa"+to_string(p.UniqueID)+".js"), p);
	plugins.push_back(p);
    }
    jp.close();
    ifs.close();
}

extern "C" __attribute__ ((visibility ("default"))) int
get_gx_plugin(unsigned int idx, PluginDef **pplugin)
{
    static bool inited = false;
    if (!inited) {
	inited = true;
	try {
	    init();
	} catch (JsonException &e) {
	    printf("Exception: %s\n", e.what());
	    if (pplugin) {
		*pplugin = 0;
	    }
	    return -1;
	}
    }
    if (!pplugin) {
	return plugins.size();
    }
    if (idx < plugins.size()) {
	*pplugin = LadspaDsp::create(plugins[idx]);
	return *pplugin ? plugins.size() : -1;
    } else {
	*pplugin = 0;
	return -1;
    }
}

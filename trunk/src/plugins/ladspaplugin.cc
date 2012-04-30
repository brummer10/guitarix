#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include <ladspa.h>

#include <stdlib.h>
#include <list>
#include <glibmm.h>
#include <giomm.h>

#include "gx_plugin.h"

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

struct paradesc {
    std::string name;
    bool has_range;
    float dflt;
    float low;
    float up;
    float step;
    paradesc(): name(), has_range(false), dflt(), low(), up(), step() {}
};

struct plugdesc {
    std::string path;
    unsigned int index;
    std::map<int,paradesc> names;
};

class LadspaDsp: public PluginDef {
private:
    static void init(unsigned int samplingFreq, PluginDef *plugin);
    static void mono_process(int count, float *input, float *output, PluginDef *plugin);
    static void stereo_process(int count, float *input1, float *input2, float *output1, float *output2, PluginDef *plugin);
    static int registerparam(const ParamReg& reg);
    static int uiloader(const UiBuilder& builder);
    static void del_instance(PluginDef *plugin);
    static void write_file(std::string path);
    static void make_menu(const LADSPA_Descriptor * psDescriptor, Glib::ustring path, Glib::ustring str, unsigned long lPluginIndex);
    static void *dlopenLADSPA(const char * pcFilename, int iFlag);
    //
    int samplefreq;
    const LADSPA_Descriptor *desc;
    void *handle;
    LADSPA_Handle instance;
    struct port_data {
	LADSPA_Data port;
	std::string id;
    } * ctrl_ports;
    std::string id_str;
    const plugdesc& pd;
    void activate();
    void connect(int tp, int i, float *v);
    LadspaDsp(const plugdesc& plug);
    ~LadspaDsp();
public:
    static void create_list();
    static LadspaDsp *create(const plugdesc& plug) { return new LadspaDsp(plug); }
};

LadspaDsp::LadspaDsp(const plugdesc& plug)
    : PluginDef(), desc(), handle(), instance(), ctrl_ports(), id_str(), pd(plug) {
    handle = dlopen(pd.path.c_str(), RTLD_LOCAL|RTLD_NOW);
    if (!handle) {
	printf("Cannot open plugin: %s [%s]\n", pd.path.c_str(), dlerror());
	return;
    }
   // printf("load plugin: %s \n", pd.path.c_str());
    LADSPA_Descriptor_Function ladspa_descriptor = (LADSPA_Descriptor_Function)dlsym(handle, "ladspa_descriptor");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
	printf("Cannot load symbol 'ladspa_descriptor': %s\n", dlsym_error);
	return;
    }
    desc = ladspa_descriptor(pd.index);

    instance = desc->instantiate(desc, 48000);
    if (!instance) {
	printf("Cannot instanciate %s\n", desc->Label);
	return;
    }
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
    ctrl_ports = new port_data[num_ctrl];
    if (num_inputs == 1 && num_outputs == 1) {
	mono_audio = mono_process;
    } else if (num_inputs == 2 && num_outputs == 2) {
	stereo_audio = stereo_process;
    } else {
	printf("cannot use ladspa plugin %s with %d inputs and %d outputs\n", desc->Label, num_inputs, num_outputs);
	return;
    }
    desc->cleanup(instance);
    instance = 0;

    version = PLUGINDEF_VERSION;
    id_str = "ladspa_";
    id_str += desc->Label;
    id_str += to_string(desc->UniqueID);
    id = id_str.c_str();

    std::string na = desc->Name;
    if(na.length()>24) name = desc->Label;
    else name = desc->Name;
    if (na.compare("Flanger") == 0)
           name = "Flanger1";

    set_samplerate = init;
    register_params = registerparam;
    load_ui = uiloader;
    delete_instance = del_instance;
}

LadspaDsp::~LadspaDsp() {
    if (instance) {
	desc->cleanup(instance);
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
    self.instance = self.desc->instantiate(self.desc, samplingFreq);
    int n = 0;
    self.samplefreq = samplingFreq;
    for (unsigned int i = 0; i < self.desc->PortCount; ++i) {
	if (LADSPA_IS_PORT_CONTROL(self.desc->PortDescriptors[i])) {
	    self.desc->connect_port(self.instance, i, &self.ctrl_ports[n].port);
	    n += 1;
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

int LadspaDsp::registerparam(const ParamReg& reg) {
    LadspaDsp& self = *static_cast<LadspaDsp*>(reg.plugin);
    int n = 0;
    
    for (unsigned int i = 0; i < self.desc->PortCount; ++i) {
	if (LADSPA_IS_PORT_CONTROL(self.desc->PortDescriptors[i])) {
        
        float low = self.desc->PortRangeHints[i].LowerBound;
        float up = self.desc->PortRangeHints[i].UpperBound;
	    float dflt = 0.0;
        
        if (LADSPA_IS_HINT_SAMPLE_RATE(self.desc->PortRangeHints[i].HintDescriptor)) {
        low *= self.samplefreq; //FIXME
        up *= self.samplefreq;  //FIXME
        }
        if (LADSPA_IS_HINT_LOGARITHMIC(self.desc->PortRangeHints[i].HintDescriptor)) {
            if (low < 1.192092896e-07F)
                low = 1.192092896e-07F;
        }
        if (LADSPA_IS_HINT_TOGGLED(self.desc->PortRangeHints[i].HintDescriptor)) {
            low = 0;
            up = 1;
        }
        
	    if (LADSPA_IS_HINT_BOUNDED_BELOW(self.desc->PortRangeHints[i].HintDescriptor)) {
		low = self.desc->PortRangeHints[i].LowerBound;
	    }
	    if (LADSPA_IS_HINT_BOUNDED_ABOVE(self.desc->PortRangeHints[i].HintDescriptor)) {
		up = self.desc->PortRangeHints[i].UpperBound;
	    }
	    float step = (up - low) / 100;
	    if (LADSPA_IS_HINT_INTEGER(self.desc->PortRangeHints[i].HintDescriptor) ||
        LADSPA_IS_HINT_TOGGLED(self.desc->PortRangeHints[i].HintDescriptor)) {
		step = 1.0;
	    } else if (step > 1.0) {
		step = 1.0;
	    } else {
		step = pow(10, floor(log10(step)));
	    }
	    if (LADSPA_IS_HINT_HAS_DEFAULT(self.desc->PortRangeHints[i].HintDescriptor)) {
		if (LADSPA_IS_HINT_DEFAULT_MINIMUM(self.desc->PortRangeHints[i].HintDescriptor)) {
		    dflt = low;
		} else if (LADSPA_IS_HINT_DEFAULT_LOW(self.desc->PortRangeHints[i].HintDescriptor)) {
            if (LADSPA_IS_HINT_LOGARITHMIC(self.desc->PortRangeHints[i].HintDescriptor)) {
                dflt = exp(log(low) * 0.75 + log(up) * 0.25);
            } else {
                dflt = low * 0.75 + up * 0.25;
            }
		    
		} else if (LADSPA_IS_HINT_DEFAULT_MIDDLE(self.desc->PortRangeHints[i].HintDescriptor)) {
            if (LADSPA_IS_HINT_LOGARITHMIC(self.desc->PortRangeHints[i].HintDescriptor)) {
                dflt = exp(log(low) * 0.5 + log(up) * 0.5);
            } else {
                dflt = low * 0.5 + up * 0.5;
            }
		} else if (LADSPA_IS_HINT_DEFAULT_HIGH(self.desc->PortRangeHints[i].HintDescriptor)) {
            if (LADSPA_IS_HINT_LOGARITHMIC(self.desc->PortRangeHints[i].HintDescriptor)) {
                dflt = exp(log(low) * 0.25 + log(up) * 0.75);
            } else {
                dflt = low * 0.25 + up * 0.75;
            }
		} else if (LADSPA_IS_HINT_DEFAULT_MAXIMUM(self.desc->PortRangeHints[i].HintDescriptor)) {
		    dflt = up;
		} else if (LADSPA_IS_HINT_DEFAULT_0(self.desc->PortRangeHints[i].HintDescriptor)) {
            dflt = low;
		} else if (LADSPA_IS_HINT_DEFAULT_1(self.desc->PortRangeHints[i].HintDescriptor)) {
		    dflt = 1;
		} else if (LADSPA_IS_HINT_DEFAULT_100(self.desc->PortRangeHints[i].HintDescriptor)) {
		    dflt = 100;
		} else if (LADSPA_IS_HINT_DEFAULT_440(self.desc->PortRangeHints[i].HintDescriptor)) {
		    dflt = 440;
		}
	    } else if (dflt < low) {
		dflt = low;
	    } else if (dflt > up) {
		dflt = up;
	    } else if (LADSPA_IS_PORT_OUTPUT(self.desc->PortDescriptors[i])) {
            up = 4096;
            
        }
        std::string rep = ".";
        std::string pn = self.desc->PortNames[i];
        if(pn.find(rep) != std::string::npos)
            pn.replace(pn.find(rep),rep.size(),"-");
	    std::string& s = self.ctrl_ports[n].id;
	    s = self.id_str + "." + pn;
	    std::string nm;
	    std::map<int,paradesc>::const_iterator it = self.pd.names.find(n);
	    if (it != self.pd.names.end()) {
		nm = it->second.name;
		if (it->second.has_range) {
		    dflt = it->second.dflt;
		    low = it->second.low;
		    up = it->second.up;
		    step = it->second.step;
		}
	    }
	    const char *tp = "S";
	    if (LADSPA_IS_HINT_TOGGLED(self.desc->PortRangeHints[i].HintDescriptor)) {
		tp = "B";
		//printf("%s.%s: hint toggled: FIXME\n", self.desc->Label, self.desc->PortNames[i]);
	    } 
	    reg.registerVar(s.c_str(),nm.c_str(),tp,"",&self.ctrl_ports[n].port,dflt,low,up,step);
	    n++;
	}
    }
    return 0;
}

int LadspaDsp::uiloader(const UiBuilder& b) {
    LadspaDsp& self = *static_cast<LadspaDsp*>(b.plugin);
    b.openHorizontalhideBox("");
    b.closeBox();
    int n = 0;
    const unsigned int max_ctrl = 3;
    if (self.desc->PortCount > max_ctrl) {
	b.openVerticalBox("");
	b.openHorizontalBox("");
    }
    for (unsigned int i = 0; i < self.desc->PortCount; ++i) {
	if (i > 0 && i % max_ctrl == 0) {
	    b.closeBox();
	    b.openHorizontalBox("");
	}
	if (LADSPA_IS_PORT_CONTROL(self.desc->PortDescriptors[i])) {
        if (LADSPA_IS_HINT_TOGGLED(self.desc->PortRangeHints[i].HintDescriptor)) {
            b.openVerticalBox1(self.desc->PortNames[i]);
            b.create_switch_no_caption("switchit",self.ctrl_ports[n++].id.c_str());
            b.closeBox();
        } else {
            b.create_small_rackknob(self.ctrl_ports[n++].id.c_str(),0);
        }
        
	}
    }
    if (self.desc->PortCount > max_ctrl) {
	b.closeBox();
	b.closeBox();
    }
    return 0;
}

void LadspaDsp::del_instance(PluginDef *plugin) {
    delete static_cast<LadspaDsp*>(plugin);
}


std::list<Glib::ustring> ladspa_plug_list;


void LadspaDsp::write_file(std::string path) {
    std::ofstream ifs(path.c_str());
    std::list<Glib::ustring>::iterator it;
    ifs << "[ \n";
    for ( it=ladspa_plug_list.begin() ; it != ladspa_plug_list.end(); it++ ){
        ifs << *it;       
    }
    ifs << "\n] ";
    ifs.close();
}

void LadspaDsp::make_menu(const LADSPA_Descriptor * psDescriptor, Glib::ustring path,
                          Glib::ustring str, unsigned long lPluginIndex) {

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
        mono_plug += path.c_str();
        mono_plug += "/";
        mono_plug += str.c_str();
        mono_plug += "\", ";
        mono_plug += to_string(lPluginIndex);
        mono_plug += ", {}]";
        ladspa_plug_list.push_back(mono_plug);
    }
    
}

/*  this routine will search the LADSPA_PATH for the file. */
void *LadspaDsp::dlopenLADSPA(const char * pcFilename, int iFlag) {

    char * pcBuffer = NULL;
    const char * pcEnd;
    const char * pcLADSPAPath;
    const char * pcStart;
    int iNeedSlash;
    size_t iFilenameLength;
    void * pvResult;
    iFilenameLength = strlen(pcFilename);
    pvResult = NULL;

    pcLADSPAPath = getenv("LADSPA_PATH");

    if (pcLADSPAPath == NULL) {
        setenv("LADSPA_PATH","/usr/lib/ladspa",0);
        setenv("LADSPA_PATH","/usr/local/lib/ladspa",0);
        pcLADSPAPath = getenv("LADSPA_PATH");
    } 
    pcStart = pcLADSPAPath;
    while (*pcStart != '\0') {
        pcEnd = pcStart;
        while (*pcEnd != ':' && *pcEnd != '\0')
            pcEnd++;
        pcBuffer = (char*)malloc(iFilenameLength + 2 + (pcEnd - pcStart));
        if (pcEnd > pcStart)
            strncpy(pcBuffer, pcStart, pcEnd - pcStart);
        iNeedSlash = 0;
        if (pcEnd > pcStart)
            if (*(pcEnd - 1) != '/') {
                iNeedSlash = 1;
                pcBuffer[pcEnd - pcStart] = '/';
            }
        strcpy(pcBuffer + iNeedSlash + (pcEnd - pcStart), pcFilename);
        pvResult = dlopen(pcBuffer, iFlag);
        free(pcBuffer);
        return pvResult;
    
    }
    return pvResult;
}

void LadspaDsp::create_list() {
    
    std::string if_path = getenv("HOME");
    if_path += "/.config/guitarix/ladspa_defs.js";
    // to avoid rescan the ladspa path activate this
    /*std::ifstream ifs(if_path.c_str());
    if (!ifs.fail()) {
        ifs.close();
        return;
    }*/
    
    Glib::ustring path;
    char * p = getenv ("LADSPA_PATH");
        if (p != NULL) {
            path = getenv ("LADSPA_PATH");
        } else { 
        setenv("LADSPA_PATH","/usr/lib/ladspa",0);
        setenv("LADSPA_PATH","/usr/local/lib/ladspa",0);
        path = getenv("LADSPA_PATH");
	}
    
    Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(path);
    if (file->query_exists()) {
        Glib::RefPtr<Gio::FileEnumerator> child_enumeration =
              file->enumerate_children(G_FILE_ATTRIBUTE_STANDARD_NAME
				       "," G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME
				       "," G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE);
        std::vector<Glib::ustring> file_names;
        Glib::RefPtr<Gio::FileInfo> file_info;

        while ((file_info = child_enumeration->next_file()) != 0) {
             if (file_info->get_attribute_string(G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE) == "application/x-sharedlib")
                    file_names.push_back(file_info->get_attribute_byte_string(G_FILE_ATTRIBUTE_STANDARD_NAME));
        }
        // sort the vector
        std::sort(file_names.begin(), file_names.end());
       
        for (unsigned int i = 0; i < file_names.size(); i++) {
            
            //fprintf(stderr, " %i %s \n", i,file_names[i].c_str());
            if (i != file_names.size() || i == 0) {
                
                Glib::ustring str = file_names[i];
                // unwanted plugs
                if((strcmp(str.c_str(),"bandpass_a_iir_1893.so") !=0) &&
                  (strcmp(str.c_str(),"bandpass_iir_1892.so") !=0) &&
                  (strcmp(str.c_str(),"butterworth_1902.so") !=0) &&
                  (strcmp(str.c_str(),"dssi-vst.so") !=0) &&
                  (strcmp(str.c_str(),"highpass_iir_1890.so") !=0) &&
                  (strcmp(str.c_str(),"ladspa_guitarix.so") !=0) &&
                  (strcmp(str.c_str(),"lowpass_iir_1891.so") !=0) &&
                  (strcmp(str.c_str(),"notch_iir_1894.so") !=0)&&
                  (strcmp(str.c_str(),"decay_1886.so") !=0) &&
                  (strcmp(str.c_str(),"sine.so") !=0)) {

                    const char * plug = str.c_str();
                    void * pvPluginHandle;
                    LADSPA_Descriptor_Function pfDescriptorFunction;
                    const LADSPA_Descriptor * psDescriptor;
                    unsigned long lPluginIndex;
                    pvPluginHandle = dlopenLADSPA(plug, RTLD_LOCAL|RTLD_NOW);
                    dlerror();
                    pfDescriptorFunction 
                        = (LADSPA_Descriptor_Function)dlsym(pvPluginHandle, "ladspa_descriptor");
                    if (pfDescriptorFunction) {
                        for (lPluginIndex = 0;; lPluginIndex++) {
                            psDescriptor = pfDescriptorFunction(lPluginIndex);
                            if (!psDescriptor)
                                break;
                            make_menu(psDescriptor, path, str, lPluginIndex);
                        }
                        dlclose(pvPluginHandle);
                    }
                }
            }
        }
    }
    write_file(if_path);
}

std::vector<plugdesc> plugins;

void init() {
    std::string path = getenv("HOME");
    path += "/.config/guitarix/ladspa_defs.js";
    LadspaDsp::create_list();
    std::ifstream ifs(path.c_str());
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
	jp.next(JsonParser::begin_object);
	while (jp.peek() != JsonParser::end_object) {
	    jp.next(JsonParser::value_key);
	    if (jp.current_value().empty() || jp.current_value()[0] != '#') {
		printf("unknown key '%s' for ladspa plugin '%s/%d'\n", jp.current_value().c_str(), p.path.c_str(), p.index);
		jp.skip_object();
	    } else {
		paradesc para;
		int key = atoi(jp.current_value().c_str()+1);
		if (jp.peek() == JsonParser::begin_array) {
		    jp.next(JsonParser::begin_array);
		    jp.next(JsonParser::value_number);
		    para.dflt = jp.current_value_float();
		    jp.next(JsonParser::value_number);
		    para.low = jp.current_value_float();
		    jp.next(JsonParser::value_number);
		    para.up = jp.current_value_float();
		    jp.next(JsonParser::value_number);
		    para.step = jp.current_value_float();
		    para.has_range = true;
		    if (jp.peek() == JsonParser::value_string) {
			jp.next(JsonParser::value_string);
			para.name = jp.current_value();
		    }
		    jp.next(JsonParser::end_array);
		} else {
		    jp.next(JsonParser::value_string);
		    para.name = jp.current_value();
		}
		p.names[key] = para;
	    }
	}
	jp.next(JsonParser::end_object);
	jp.next(JsonParser::end_array);
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
	return plugins.size();
    } else {
	*pplugin = 0;
	return -1;
    }
}

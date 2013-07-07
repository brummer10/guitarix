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
 */

/* ------- This is the guitarix Engine namespace ------- */

#pragma once

namespace gx_jack { class GxJack; }

namespace gx_engine {

/****************************************************************
 ** MonoMute, StereoMute, MaxLevel, MidiAudioBuffer
 */

class MonoMute: public PluginDef {
private:
    static void process(int count, float *input, float *output, PluginDef*);
public:
    MonoMute();
};

class StereoMute: public PluginDef {
private:
    static void process(int count, float *input0, float *input1,
			float *output0, float *output1, PluginDef*);
public:
    StereoMute();
};

class MaxLevel: public PluginDef {
private:
    static float maxlevel[2];
    static void process(int count, float *input0, float *input1,
			float *output0, float *output1, PluginDef*);
    static int activate(bool start, PluginDef *plugin);
public:
    static unsigned int size() { return sizeof(maxlevel) / sizeof(maxlevel[0]); }
    static float get(unsigned int channel) {
	assert(channel < size()); return maxlevel[channel];
    }
    static void reset() {
	for (unsigned int i = 0; i < size(); i++) {
	    maxlevel[i] = 0;
	}
    }
    MaxLevel();
};


/****************************************************************
 ** class TunerAdapter
 */

class TunerAdapter: public ModuleSelector, private PluginDef, public sigc::trackable {
private:
    static void feed_tuner(int count, float *input, float *output, PluginDef*);
    static int regparam(const ParamReg& reg);
    static int activate(bool start, PluginDef *plugin);
    static void init(unsigned int samplingFreq, PluginDef *plugin);
    PitchTracker pitch_tracker;
    int state;
    ModuleSequencer& engine;
    enum { tuner_use = 0x01, livetuner_use = 0x02, switcher_use = 0x04, midi_use = 0x08 };
    void set_and_check(int use, bool on);
    Plugin* dep_plugin;
public:
    Plugin plugin;
    TunerAdapter(ModuleSequencer& engine);
    void used_for_switching(bool on) { set_and_check(switcher_use, on); }
    void used_for_display(bool on) { set_and_check(tuner_use, on); }
    void used_for_livedisplay(bool on) { set_and_check(livetuner_use, on); }
    bool used_for_livedisplay() { return state & livetuner_use; }
    void used_by_midi(bool on) { set_and_check(midi_use, on); }
    void set_dep_module(Plugin* dep) { dep_plugin = dep; }
    void set_module();
    Glib::Dispatcher& signal_freq_changed() { return pitch_tracker.new_freq; }
    float get_freq() { return pitch_tracker.get_estimated_freq(); }
    float get_note() { return pitch_tracker.get_estimated_note(); }
};


/****************************************************************
 ** class MidiAudioBuffer
 */

class MidiVariables {
private:
    float fslider45;
    float fslider38;
    float fslider31;
    float fslider27;
    float fslider29;
    float fslider30;
    float fslider26;
    float fslider33;
    float fslider34;
    float fslider35;
    float fslider36;
    float fslider42;
    float fslider43;
    float fslider40;
    float fslider41;
    float fslider44;
    float fslider37;
    float fslider39;
    float fslider46;
    float fslider47;
    float fslider48;
    float fConstlog;
    float fConstlog2;
    float beat0;
    float midi_gain;
    float fConstun0;
    float fslider32;
    float BeatFilter1;
    float BeatFilter2;
    float BeatFilterk;
    bool fautogain;
    bool fpitch;
    bool fautogain1;
    bool fpitch1;
    bool fpitch2;
    bool fautogain2;
    bool  midistat;
    bool  midistat1;
    bool  midistat2;
    bool  midistat3;

    int   weg;
    int   program;
    int   program2;
    int   volume2;
    int   Beat_is;
    int   send;
    int   volume;
    int   noten;
    int   program1;
    int   send1;
    int   noten1;
    int   volume1;
    int   send2;
    int   noten2;

    bool  fcheckbox10;
    bool  fcheckbox11;

    unsigned char* midi_send;
    unsigned char* midi_send1;
    unsigned char* midi_send2;

public:
    void register_parameter(const ParamReg& reg);
    void init(int samplingFreq);
    void process_midi(int len, float *audiodata, void *midi_port_buf, float jcpu_load,
		      float fConsta4, float fConsta1t);
    bool get_midistat() { return midistat; }
};


class MidiAudioBuffer: PluginDef {
public:
    enum Load { load_off = -1, load_low = 0, load_high = 1, load_over = 2 };
private:
    MidiVariables midi;
    gx_engine::TunerAdapter& tuner;
    gx_jack::GxJack* jack;
    Load jack_overload;
    Glib::Dispatcher overload_change;
    static void fill_buffer(int count, float *input0, float *output0, PluginDef*);
    static int regparam(const ParamReg& reg);
    static void init(unsigned int samplingFreq, PluginDef *plugin);
    static int activate(bool start, PluginDef *plugin);
public:
    Plugin plugin;
    MidiAudioBuffer(TunerAdapter& t);
    void set_jack(gx_jack::GxJack* jack_) { jack = jack_; }
    bool get_midistat() { return midi.get_midistat(); }
    Load jack_load_status() { return jack_overload; }
    Glib::Dispatcher& signal_jack_load_change() { return overload_change; }
};


/****************************************************************
 ** class NoiseGate
 */

class NoiseGate {
private:
    static PluginDef inputdef;
    static float fnglevel;
    static float ngate;
    static bool off;
    static int noisegate_register(const ParamReg& reg);
    static void inputlevel_compute(int count, float *input0, float *output0, PluginDef*);
    static void outputgate_compute(int count, float *input, float *output, PluginDef*);
    static int outputgate_activate(bool start, PluginDef *pdef);
public:
    static Plugin inputlevel;
    static PluginDef outputgate;
    NoiseGate();
};


/****************************************************************
 ** class OscilloscopeAdapter
 */

class OscilloscopeAdapter: PluginDef {
private:
    static float* buffer;
    static unsigned int size;
    static void fill_buffer(int count, float *input0, float *output0, PluginDef*);
    static int osc_register(const ParamReg& reg);
    static int activate(bool start, PluginDef *p);
    void change_buffersize(unsigned int);
    int mul_buffer;
public:
    Plugin plugin;
    sigc::signal<int, bool>          activation;
    sigc::signal<void, unsigned int> size_change;
    void clear_buffer();
    unsigned int get_size() { return size; }
    inline float *get_buffer() { return buffer; }
    int get_mul_buffer() { return mul_buffer; }
    void set_mul_buffer(int a, unsigned int b) { mul_buffer = a; change_buffersize(b); }
    OscilloscopeAdapter(ModuleSequencer& engine);
};


/****************************************************************
 ** class GxJConvSettings
 */

class GxJConvSettings {
 private:
    // main jconv setting
    std::string     fIRFile;
    std::string     fIRDir;

    float           fGain;       // jconv gain
    guint           fOffset;     // offset in IR where to start comvolution
    guint           fLength;     // length of the IR to use for convolution
    guint           fDelay;      // delay when to apply reverb
    Gainline        gainline;
    bool            fGainCor;
    void read_gainline(gx_system::JsonParser& jp);
    inline void setIRDir(string name)             { fIRDir = name; }
    friend class ConvolverAdapter;
    friend class ParameterV<GxJConvSettings>;
 public:
    GxJConvSettings();
    GxJConvSettings& operator=(GxJConvSettings const& jcset);
    bool operator==(const GxJConvSettings& jcset) const;
    // getters and setters
    inline const std::string& getIRFile() const   { return fIRFile; }
    std::string getFullIRPath() const;
    inline float           getGain() const        { return fGain; }
    inline guint           getOffset() const      { return fOffset; }
    inline guint           getLength() const      { return fLength; }
    inline guint           getDelay() const       { return fDelay; }
    inline bool            getGainCor() const     { return fGainCor; }
    inline const Gainline& getGainline() const    { return gainline; }
    const std::string& getIRDir() const           { return fIRDir; }
    void setFullIRPath(string name);
    inline void setIRFile(string name)            { fIRFile = name; }
    inline void setGain(float gain)               { fGain       = gain; }
    inline void setGainCor(bool gain)             { fGainCor    = gain; }
    inline void setOffset(guint offs)             { fOffset     = offs; }
    inline void setLength(guint leng)             { fLength     = leng; }
    inline void setDelay(guint del)               { fDelay      = del;  }
    inline void setGainline(const Gainline& gain) { gainline    = gain; }

 public:
    void readJSON(gx_system::JsonParser& jp,
		  const gx_system::PathList *search_path);
    void writeJSON(gx_system::JsonWriter& w,
		   const gx_system::PathList *search_path) const;
};

class ConvolverAdapter;

template<>
class ParameterV<GxJConvSettings>: public Parameter {
private:
    const gx_system::PathList *searchpath;
    GxJConvSettings json_value;
    GxJConvSettings *value;
    GxJConvSettings std_value;
    GxJConvSettings value_storage;
    sigc::signal<void, const GxJConvSettings*> changed;
public:
    ParameterV(const string& id, ConvolverAdapter &conv, GxJConvSettings *v);
    ParameterV(gx_system::JsonParser& jp);
    ~ParameterV();
    virtual void serializeJSON(gx_system::JsonWriter& jw);
    sigc::signal<void, const GxJConvSettings*>& signal_changed() { return changed; }
    static ParameterV<GxJConvSettings> *insert_param(
	ParamMap &pmap, const string& id, ConvolverAdapter &conv, GxJConvSettings *v);
    bool set(const GxJConvSettings& val) const;
    const GxJConvSettings& get_value() const { return *value; }
    virtual void stdJSON_value();
    virtual bool on_off_value();
    virtual void writeJSON(gx_system::JsonWriter& jw) const;
    virtual bool compareJSON_value();
    virtual void setJSON_value();
    virtual void readJSON_value(gx_system::JsonParser& jp);
};

typedef ParameterV<GxJConvSettings> JConvParameter;


/****************************************************************
 ** class ConvolverAdapter
 */

class ConvolverAdapter: protected PluginDef, public sigc::trackable {
protected:
    GxConvolver conv;
    boost::mutex activate_mutex;
    EngineControl& engine;
    sigc::slot<void> sync;
    ParamMap& param;
    const gx_system::PathList& pathlist;
    std::string sys_ir_dir;
    bool activated;
    // wrapper for the rack order function pointers
    void change_buffersize(unsigned int size);
    GxJConvSettings jcset;
    JConvParameter *jcp;
public:
    Plugin plugin;
public:
    ConvolverAdapter(EngineControl& engine, sigc::slot<void> sync, ParamMap& param,
		     const gx_system::PathList& pathlist, const std::string& sys_ir_dir);
    ~ConvolverAdapter();
    void restart();
    bool conv_start();
    inline const std::string& getIRFile() const { return jcset.getIRFile(); }
    inline void set_sync(bool val) { conv.set_sync(val); }
    inline std::string getFullIRPath() const { return jcset.getFullIRPath(); }
    inline const std::string& getIRDir() const { return jcset.getIRDir(); }
    bool set(const GxJConvSettings& jcset) const { return jcp->set(jcset); }
    const GxJConvSettings& get_jcset() const { return jcset; }
    const gx_system::PathList& get_pathlist() const { return pathlist; }
    const std::string& get_sys_IR_dir() const { return sys_ir_dir; }
    ParamMap& get_parameter_map() const { return param; }
};


/****************************************************************
 ** class ConvolverStereoAdapter
 */

#include "faust/jconv_post.h"
#include "faust/jconv_post_mono.h"

class ConvolverStereoAdapter: public ConvolverAdapter {
private:
    jconv_post::Dsp jc_post;
    // wrapper for the rack order function pointers
    static void convolver_init(unsigned int samplingFreq, PluginDef *pdef);
    static int activate(bool start, PluginDef *pdef);
    static void convolver(int count, float *input0, float *input1,
			  float *output0, float *output1, PluginDef*);
    static int convolver_register(const ParamReg& reg);
public:
    ConvolverStereoAdapter(EngineControl& engine, sigc::slot<void> sync, ParamMap& param,
		     const gx_system::PathList& pathlist, const std::string& sys_ir_dir);
    ~ConvolverStereoAdapter();
};


/****************************************************************
 ** class ConvolverMonoAdapter
 */

class ConvolverMonoAdapter: public ConvolverAdapter {
private:
    jconv_post_mono::Dsp jc_post_mono;
    // wrapper for the rack order function pointers
    static void convolver_init(unsigned int samplingFreq, PluginDef *pdef);
    static int activate(bool start, PluginDef *pdef);
    static void convolver(int count, float *input, float *output, PluginDef*);
    static int convolver_register(const ParamReg& reg);
public:
    ConvolverMonoAdapter(EngineControl& engine, sigc::slot<void> sync, ParamMap& param,
		     const gx_system::PathList& pathlist, const std::string& sys_ir_dir);
    ~ConvolverMonoAdapter();
};


/****************************************************************
 ** class BaseConvolver
 */


class BaseConvolver: protected PluginDef {
protected:
    GxSimpleConvolver conv;
    boost::mutex activate_mutex;
    EngineControl& engine;
    sigc::slot<void> sync;
    bool activated;
    sigc::connection update_conn;
    static void init(unsigned int samplingFreq, PluginDef *p);
    static int activate(bool start, PluginDef *pdef);
    void change_buffersize(unsigned int);
    int conv_start();
    bool check_update_timeout();
    virtual void check_update() = 0;
    virtual bool start(bool force = false) = 0;
public:
    Plugin plugin;
public:
    BaseConvolver(EngineControl& engine, sigc::slot<void> sync, gx_resample::BufferResampler& resamp);
    virtual ~BaseConvolver();
    inline void set_sync(bool val) { conv.set_sync(val); }
};

/****************************************************************
 ** class CabinetConvolver
 */

#include "faust/cabinet_impulse_former.h"

class CabinetConvolver: public BaseConvolver {
private:
    int current_cab;
    float level;
    int cabinet;
    float bass;
    float treble;
    float sum;
    value_pair *cab_names;
    cabinet_impulse_former::Dsp impf;
    static void run_cab_conf(int count, float *input, float *output, PluginDef*);
    static int register_cab(const ParamReg& reg);
    bool do_update();
    bool do_only_update();
    virtual void check_update();
    virtual bool start(bool force = false);
    bool cabinet_changed() { return current_cab != cabinet; }
    void update_cabinet() { current_cab = cabinet; }
    bool sum_changed() { return abs(sum - (level + bass + treble)) > 0.01; }
    void update_sum() { sum = level + bass + treble; }
public:
    CabinetConvolver(EngineControl& engine, sigc::slot<void> sync, gx_resample::BufferResampler& resamp);
    ~CabinetConvolver();
};


/****************************************************************
 ** class PreampConvolver
 */

#include "faust/preamp_impulse_former.h"

class PreampConvolver: public BaseConvolver {
private:
    int current_pre;
    float level;
    int preamp;
    float bass;
    float treble;
    float sum;
    value_pair *pre_names;
    preamp_impulse_former::Dsp impf;
    static void run_pre_conf(int count, float *input, float *output, PluginDef*);
    static int register_pre(const ParamReg& reg);
    bool do_update();
    bool do_only_update();
    virtual void check_update();
    virtual bool start(bool force = false);
    bool preamp_changed() { return current_pre != preamp; }
    void update_preamp() { current_pre = preamp; }
    bool sum_changed() { return abs(sum - (level + bass + treble)) > 0.01; }
    void update_sum() { sum = level + bass + treble; }
public:
    PreampConvolver(EngineControl& engine, sigc::slot<void> sync, gx_resample::BufferResampler& resamp);
    ~PreampConvolver();
};

/****************************************************************
 ** class ContrastConvolver
 */

#include "faust/presence_level.h"

class ContrastConvolver: public BaseConvolver {
private:
    float level;
    float sum;
    presence_level::Dsp presl;
    static void run_contrast(int count, float *input, float *output, PluginDef*);
    static int register_con(const ParamReg& reg);
    inline void update_sum() { sum = level; }
    virtual void check_update();
    bool do_update();
    bool do_only_update();
    inline bool sum_changed() { return abs(sum - level) > 0.01; }
    virtual bool start(bool force = false);
public:
    ContrastConvolver(EngineControl& engine, sigc::slot<void> sync, gx_resample::BufferResampler& resamp);
    ~ContrastConvolver();
};


/****************************************************************
 ** class LadspaLoader
 */

enum widget_type { tp_scale, tp_scale_log, tp_toggle, tp_enum, tp_display, tp_display_toggle, tp_none, tp_int };

struct paradesc: boost::noncopyable {
    int index;
    std::string name;
    float dflt;
    float low;
    float up;
    float step;
    widget_type tp;
    bool newrow;
    bool has_caption;
    value_pair* values;
    paradesc(): index(), name(), dflt(), low(), up(), step(), tp(), newrow(), has_caption(true), values() {}
    ~paradesc();
    void set_valuelist(const std::vector<std::string>& v);
    void readJSON(gx_system::JsonParser& jp);
    void writeJSON(gx_system::JsonWriter& jw);
};

enum quirkflag { need_activate = 1, no_cleanup = 2 };

class plugdesc {
public:
    std::string path;
    unsigned int index;
    unsigned long UniqueID;
    Glib::ustring Label;
    Glib::ustring shortname;
    Glib::ustring category;
    int quirks; // quirkflag bits
    int add_wet_dry;
    int master_idx;
    Glib::ustring master_label;
    std::vector<paradesc*> names;
    std::string id_str;
private:
    plugdesc() {}
    ~plugdesc();
    friend class LadspaLoader;
public:
    void readJSON(gx_system::JsonParser& jp);
    void writeJSON(gx_system::JsonWriter& jw);
};

class LadspaLoader {
public:
    typedef std::vector<plugdesc*> pluginarray;
private:
    const gx_system::CmdlineOptions& options;
    pluginarray plugins;
private:
    void read_module_config(const std::string& filename, plugdesc *p);
    void read_module_list(pluginarray& p);
public:
    LadspaLoader(const gx_system::CmdlineOptions& options);
    ~LadspaLoader();
    bool load(pluginarray& p);
    unsigned int size() { return plugins.size(); }
    PluginDef *create(unsigned int idx) { return create(plugins[idx]); }
    PluginDef *create(const plugdesc *p);
    pluginarray::iterator begin() { return plugins.begin(); }
    pluginarray::iterator end() { return plugins.end(); }
    pluginarray::iterator find(unsigned long uniqueid);
    void set_plugins(pluginarray& new_plugins);
    void update_instance(PluginDef *pdef, plugdesc *pdesc);
    static std::string get_ladspa_filename(unsigned long uid)
	{ return "ladspa"+gx_system::to_string(uid)+".js"; }
};

} // namespace gx_engine

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
 ** MonoMute, StereoMute, MaxLevel
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
public:
    static const unsigned int channelcount = 2;
private:
    static float maxlevel[channelcount];
    static void process(int count, float *input0, float *input1,
			float *output0, float *output1, PluginDef*);
    static int activate(bool start, PluginDef *plugin);
    static int regparam(const ParamReg& reg);
public:
    static float get(unsigned int channel) {
	assert(channel < channelcount);
	float v = maxlevel[channel];
	maxlevel[channel] = 0;
	return v;
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
    enum { tuner_use = 0x01, switcher_use = 0x02, midi_use = 0x04 };
    void set_and_check(int use, bool on);
    Plugin* dep_plugin;
public:
    Plugin plugin;
    TunerAdapter(ModuleSequencer& engine);
    void used_for_switching(bool on) { set_and_check(switcher_use, on); }
    void used_for_display(bool on) { set_and_check(tuner_use, on); }
    bool used_for_display() { return state & tuner_use; }
    void used_by_midi(bool on) { set_and_check(midi_use, on); }
    void set_dep_module(Plugin* dep) { dep_plugin = dep; }
    void set_module();
    Glib::Dispatcher& signal_freq_changed() { return pitch_tracker.new_freq; }
    float get_freq() { return pitch_tracker.get_estimated_freq(); }
    float get_note() { return pitch_tracker.get_estimated_note(); }
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
    static int osc_load_ui(const UiBuilder& builder, int format);
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
 ** class GxSeqSettings
 */

class GxSeqSettings {
 private:

    std::vector<int>        seqline;
    void read_seqline(gx_system::JsonParser& jp);
    friend class SequencerAdapter;
    friend class ParameterV<GxSeqSettings>;
 public:
    GxSeqSettings();
    GxSeqSettings& operator=(GxSeqSettings const& seqset);
    bool operator==(const GxSeqSettings& seqset) const;
    // getters and setters
    inline const std::vector<int>& getseqline() const    { return seqline; }

    inline void setseqline(const std::vector<int>& seq) { seqline    = seq; }

 public:
    void readJSON(gx_system::JsonParser& jp);
    void writeJSON(gx_system::JsonWriter& w) const;
};

template<>
class ParameterV<GxSeqSettings>: public Parameter {
private:
    GxSeqSettings json_value;
    GxSeqSettings *value;
    GxSeqSettings std_value;
    GxSeqSettings value_storage;
    sigc::signal<void, const GxSeqSettings*> changed;
public:
    ParameterV(const string& id, GxSeqSettings *v);
    ParameterV(gx_system::JsonParser& jp);
    ~ParameterV();
    virtual void serializeJSON(gx_system::JsonWriter& jw);
    sigc::signal<void, const GxSeqSettings*>& signal_changed() { return changed; }
    static ParameterV<GxSeqSettings> *insert_param(
	ParamMap &pmap, const string& id, GxSeqSettings *v);
    bool set(const GxSeqSettings& val) const;
    const GxSeqSettings& get_value() const { return *value; }
    virtual void stdJSON_value();
    virtual bool on_off_value();
    virtual void writeJSON(gx_system::JsonWriter& jw) const;
    virtual bool compareJSON_value();
    virtual void setJSON_value();
    virtual void readJSON_value(gx_system::JsonParser& jp);
};

typedef ParameterV<GxSeqSettings> SeqParameter;

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
    void readJSON(gx_system::JsonParser& jp);
    void writeJSON(gx_system::JsonWriter& w) const;
};

class ConvolverAdapter;

template<>
class ParameterV<GxJConvSettings>: public Parameter {
private:
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
    bool activated;
    // wrapper for the rack order function pointers
    void change_buffersize(unsigned int size);
    GxJConvSettings jcset;
    JConvParameter *jcp;
public:
    Plugin plugin;
public:
    ConvolverAdapter(EngineControl& engine, sigc::slot<void> sync, ParamMap& param);
    ~ConvolverAdapter();
    void restart();
    bool conv_start();
    inline const std::string& getIRFile() const { return jcset.getIRFile(); }
    inline void set_sync(bool val) { conv.set_sync(val); }
    inline std::string getFullIRPath() const { return jcset.getFullIRPath(); }
    inline const std::string& getIRDir() const { return jcset.getIRDir(); }
    bool set(const GxJConvSettings& jcset) const { return jcp->set(jcset); }
    const GxJConvSettings& get_jcset() const { return jcset; }
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
    static int jconv_load_ui(const UiBuilder& builder, int format);
public:
    ConvolverStereoAdapter(EngineControl& engine, sigc::slot<void> sync, ParamMap& param);
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
    static int jconv_load_ui(const UiBuilder& builder, int format);
public:
    ConvolverMonoAdapter(EngineControl& engine, sigc::slot<void> sync, ParamMap& param);
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
 ** class FixedBaseConvolver
 */


class FixedBaseConvolver: protected PluginDef {
protected:
    GxSimpleConvolver conv;
    boost::mutex activate_mutex;
    EngineControl& engine;
    sigc::slot<void> sync;
    bool activated;
    unsigned int SamplingFreq;
    unsigned int buffersize;
    unsigned int bz;
    sigc::connection update_conn;
    static void init(unsigned int samplingFreq, PluginDef *p);
    unsigned int getSamplingFreq() { return SamplingFreq;};
    static int activate(bool start, PluginDef *pdef);
    void change_buffersize(unsigned int);
    int conv_start();
    bool check_update_timeout();
    virtual void check_update() = 0;
    virtual bool start(bool force = false) = 0;
public:
    Plugin plugin;
public:
    FixedBaseConvolver(EngineControl& engine, sigc::slot<void> sync, gx_resample::BufferResampler& resamp);
    virtual ~FixedBaseConvolver();
    inline void set_sync(bool val) { conv.set_sync(val); }
};

/****************************************************************
 ** class CabinetConvolver
 */

#include "faust/cabinet_impulse_former.h"

class CabinetConvolver: public FixedBaseConvolver {
private:
    int current_cab;
    float level;
    int cabinet;
    float bass;
    float treble;
    float sum;
    value_pair *cab_names;
    cabinet_impulse_former::Dsp impf;
    gx_resample::FixedRateResampler smp;
    static void run_cab_conf(int count, float *input, float *output, PluginDef*);
    static int register_cab(const ParamReg& reg);
    bool do_update();
    virtual void check_update();
    virtual bool start(bool force = false);
    bool cabinet_changed() { return current_cab != cabinet; }
    void update_cabinet() { current_cab = cabinet; }
    bool sum_changed() { return std::abs(sum - (level + bass + treble)) > 0.01; }
    void update_sum() { sum = level + bass + treble; }
public:
    CabinetConvolver(EngineControl& engine, sigc::slot<void> sync,
       gx_resample::BufferResampler& resamp);
    ~CabinetConvolver();
};

#include "faust/cabinet_impulse_former_st.h"

class CabinetStereoConvolver: public FixedBaseConvolver {
private:
    int current_cab;
    float level;
    int cabinet;
    float bass;
    float treble;
    float sum;
    value_pair *cab_names;
    cabinet_impulse_former_st::Dsp impf;
    gx_resample::FixedRateResampler smp;
    gx_resample::FixedRateResampler smps;
    static void run_cab_conf(int count, float *input, float *input1, float *output, float *output1, PluginDef*);
    static int register_cab(const ParamReg& reg);
    bool do_update();
    virtual void check_update();
    virtual bool start(bool force = false);
    bool cabinet_changed() { return current_cab != cabinet; }
    void update_cabinet() { current_cab = cabinet; }
    bool sum_changed() { return fabs(sum - (level + bass + treble)) > 0.01; }
    void update_sum() { sum = level + bass + treble; }
public:
    CabinetStereoConvolver(EngineControl& engine, sigc::slot<void> sync,
       gx_resample::BufferResampler& resamp);
    ~CabinetStereoConvolver();
};


/****************************************************************
 ** class PreampConvolver
 */

#include "faust/preamp_impulse_former.h"

class PreampConvolver: public FixedBaseConvolver {
private:
    int current_pre;
    float level;
    int preamp;
    float bass;
    float treble;
    float sum;
    value_pair *pre_names;
    preamp_impulse_former::Dsp impf;
    gx_resample::FixedRateResampler smp;
    static void run_pre_conf(int count, float *input, float *output, PluginDef*);
    static int register_pre(const ParamReg& reg);
    bool do_update();
    virtual void check_update();
    virtual bool start(bool force = false);
    bool preamp_changed() { return current_pre != preamp; }
    void update_preamp() { current_pre = preamp; }
    bool sum_changed() { return std::abs(sum - (level + bass + treble)) > 0.01; }
    void update_sum() { sum = level + bass + treble; }
public:
    PreampConvolver(EngineControl& engine, sigc::slot<void> sync,
       gx_resample::BufferResampler& resamp);
    ~PreampConvolver();
};

#include "faust/preamp_impulse_former_st.h"

class PreampStereoConvolver: public FixedBaseConvolver {
private:
    int current_pre;
    float level;
    int preamp;
    float bass;
    float treble;
    float sum;
    value_pair *pre_names;
    preamp_impulse_former_st::Dsp impf;
    gx_resample::FixedRateResampler smp;
    gx_resample::FixedRateResampler smps;
    static void run_pre_conf(int count, float *input, float *input1, float *output, float *output1, PluginDef*);
    static int register_pre(const ParamReg& reg);
    bool do_update();
    virtual void check_update();
    virtual bool start(bool force = false);
    bool preamp_changed() { return current_pre != preamp; }
    void update_preamp() { current_pre = preamp; }
    bool sum_changed() { return fabs(sum - (level + bass + treble)) > 0.01; }
    void update_sum() { sum = level + bass + treble; }
public:
    PreampStereoConvolver(EngineControl& engine, sigc::slot<void> sync,
       gx_resample::BufferResampler& resamp);
    ~PreampStereoConvolver();
};

/****************************************************************
 ** class ContrastConvolver
 */

#include "faust/presence_level.h"

class ContrastConvolver: public FixedBaseConvolver {
private:
    float level;
    float sum;
    presence_level::Dsp presl;
    gx_resample::FixedRateResampler smp;
    static void run_contrast(int count, float *input, float *output, PluginDef*);
    static int register_con(const ParamReg& reg);
    inline void update_sum() { sum = level; }
    virtual void check_update();
    bool do_update();
    inline bool sum_changed() { return std::abs(sum - level) > 0.01; }
    virtual bool start(bool force = false);
public:
    ContrastConvolver(EngineControl& engine, sigc::slot<void> sync,
       gx_resample::BufferResampler& resamp);
    ~ContrastConvolver();
};

/****************************************************************
 ** class LV2Features
 */

class LV2Features {
private:

    static LV2_Options_Option gx_options[2];
    static LV2_Feature gx_options_feature;

    static LV2_URID lv2_urid_map(LV2_URID_Map_Handle, const char* const uri_);
    static LV2_Feature gx_urid_map_feature;
    
    static uint32_t lv2_uri_to_id(LV2_URI_Map_Callback_Data handle, const char*, const char* uri);
    static LV2_URI_Map_Feature gx_uri_map;
    static LV2_Feature gx_uri_map_feature;
    
    static const char* lv2_urid_unmap(LV2_URID_Unmap_Handle, const LV2_URID urid);
    static LV2_Feature gx_urid_unmap_feature;
    LV2Features() {};

public:
    static LV2Features& getInstance()
        {
            static LV2Features  instance;
            return instance;
        }
    static LV2_Feature* gx_features[];
    static LV2_URID_Map gx_urid_map;
    static LV2_URID_Unmap gx_urid_unmap;

    LV2Features(LV2Features const&)     = delete;
    void operator=(LV2Features const&)  = delete;

};

/****************************************************************
 ** class LadspaLoader
 */

enum widget_type { tp_scale, tp_scale_log, tp_toggle, tp_enum, tp_display, tp_display_toggle, tp_none, tp_int, tp_enabled };

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

enum quirkflag { need_activate = 1, no_cleanup = 2, is_lv2 = 4 };

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
    int stereo_to_mono;
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
    LilvWorld* world;
    ParamMap& param;
    const LilvPlugins* lv2_plugins;
    LilvNode* lv2_AudioPort;
    LilvNode* lv2_ControlPort;
    LilvNode* lv2_InputPort;
    LilvNode* lv2_OutputPort;
private:
    void read_module_config(const std::string& filename, plugdesc *p);
    void read_module_list(pluginarray& p);
public:
    LadspaLoader(const gx_system::CmdlineOptions& options, ParamMap& param);
    ~LadspaLoader();
    bool load(pluginarray& p);
    unsigned int size() { return plugins.size(); }
    PluginDef *create(unsigned int idx) { return create(plugins[idx]); }
    PluginDef *create(const plugdesc *p);
    pluginarray::iterator begin() { return plugins.begin(); }
    pluginarray::iterator end() { return plugins.end(); }
    pluginarray::iterator find(plugdesc* desc);
    void clear_list();
    void set_plugins(pluginarray& new_plugins);
    void update_instance(PluginDef *pdef, plugdesc *pdesc);
    static std::string get_ladspa_filename(unsigned long uid)
	{ return "ladspa"+gx_system::to_string(uid)+".js"; }
    static std::string get_ladspa_filename(std::string uid_key)
	{ return "ladspa"+uid_key.substr(9)+".js"; }
    ParamMap& get_parameter_map() const { return param; }
    friend class Lv2Dsp;
};


/****************************************************************
 ** class Directout
 */

class Directout: public PluginDef {
public:
    float* outdata;
private:
	int fSamplingFreq;
    int 	bsize;
    bool fdfill;
    EngineControl&  engine;
    sigc::slot<void> sync;
    void mem_alloc();
    void mem_free();
    void init(unsigned int samplingFreq);
    void compute(int count,  float *input0, float *input1, float *output0, float *output1);
    void change_buffersize(unsigned int size);

    static void init_static(unsigned int samplingFreq, PluginDef*);
    static void compute_static(int count, float *input0, float *input1, float *output0, float *output1, PluginDef*);
public:
    bool   mem_allocated;
    float* get_buffer() {return outdata;};
    void set_data(bool dfill);
    Plugin plugin;
    static Plugin directoutput;
    Directout( EngineControl& engine, sigc::slot<void> sync);
    ~Directout();
};


/****************************************************************
 ** class LiveLooper
 */

class LiveLooper: public PluginDef {
	
	
class FileResampler {
private:
    Resampler r_file;
    int inputRate, outputRate;
public:
    int setup(int _inputRate, int _outputRate);
    int run(int count, float *input, float *output);
    int max_out_count(int in_count) {
	return static_cast<int>(ceil((in_count*static_cast<double>(outputRate))/inputRate)); }
};

private:
	int fSamplingFreq;
	float 	gain;
	float 	fRec0[2];
	float 	gain_out;
	float 	fclip1;
	float 	fclip2;
	float 	fclip3;
	float 	fclip4;
	float 	fclips1;
	float 	fclips2;
	float 	fclips3;
	float 	fclips4;
	float 	fspeed1;
	float 	fspeed2;
	float 	fspeed3;
	float 	fspeed4;
	float 	rplay1;
	float 	rplay2;
	float 	rplay3;
	float 	rplay4;
	float 	load1;
	float 	load2;
	float 	load3;
	float 	load4;
	float 	od1;
	float 	od2;
	float 	od3;
	float 	od4;
	float 	fod1;
	float 	fod2;
	float 	fod3;
	float 	fod4;
	float 	record1;
	int 	iVec0[2];
	int 	IOTA1;
	int 	IOTA2;
	int 	IOTA3;
	int 	IOTA4;
	float 	IOTAR1;
	float 	IOTAR2;
	float 	IOTAR3;
	float 	IOTAR4;
	float *tape1;
	int 	tape1_size;
	float 	fConst0;
	float 	fConst1;
	float 	fConst2;
	float 	reset1;
	int 	RecSize1[2];
	float 	rectime0;
	float 	fRec1[2];
	float 	fRec2[2];
	int 	iRec3[2];
	int 	iRec4[2];
	float 	play1;
	float 	playh1;
	float 	gain1;
	float 	record2;
	int 	iVec2[2];
	float *tape2;
	int 	tape2_size;
	float 	reset2;
	int 	RecSize2[2];
	float 	rectime1;
	float 	fRec6[2];
	float 	fRec7[2];
	int 	iRec8[2];
	int 	iRec9[2];
	float 	play2;
	float 	playh2;
	float 	gain2;
	float 	record3;
	int 	iVec4[2];
	float *tape3;
	int 	tape3_size;
	float 	reset3;
	int 	RecSize3[2];
	float 	rectime2;
	float 	fRec11[2];
	float 	fRec12[2];
	int 	iRec13[2];
	int 	iRec14[2];
	float 	play3;
	float 	playh3;
	float 	gain3;
	float 	record4;
	int 	iVec6[2];
	float *tape4;
	int 	tape4_size;
	float 	reset4;
	int 	RecSize4[2];
	float 	rectime3;
	float 	fRec16[2];
	float 	fRec17[2];
	int 	iRec18[2];
	int 	iRec19[2];
	float 	play4;
	float 	playh4;
	float 	gain4;
	float 	play_all;
    float 	dout;
    float* outbuffer;
	bool save1;
	bool save2;
	bool save3;
	bool save4;
	bool first1;
	bool first2;
	bool first3;
	bool first4;
	bool RP1;
	bool RP2;
	bool RP3;
	bool RP4;
    Glib::ustring preset_name;
    Glib::ustring load_file1;
    Glib::ustring load_file2;
    Glib::ustring load_file3;
    Glib::ustring load_file4;
    Glib::ustring cur_name;
    Glib::ustring loop_dir;
    bool save_p;
    ParamMap& param;
	bool mem_allocated;
    sigc::slot<void> sync;
	volatile int ready;
    FileResampler smp;
    Directout* d;

    int do_resample(int inrate, int insize, float *input, int maxsize);
    int do_mono(int c, int f, float *oIn, float *tape, int n);
    void play_all_tapes();
    void mem_alloc();
	void mem_free();
	void clear_state_f();
	int activate(bool start);
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int samplingFreq);
	void compute(int count, float *input0, float *output0);
	int register_par(const ParamReg& reg);
    void save_array(std::string name);
    void load_array(std::string name);
    void save_to_wave(std::string fname, float *tape, float fSize, int tape_size);
    int load_from_wave(std::string fname, float **tape, int tape_size);
    void set_p_state();
    void load_tape1();
    void load_tape2();
    void load_tape3();
    void load_tape4();
    
	static void clear_state_f_static(PluginDef*);
	static int activate_static(bool start, PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int samplingFreq, PluginDef*);
	static void compute_static(int count, float *input0, float *output0, PluginDef*);
	static int register_params_static(const ParamReg& reg);
	static void del_instance(PluginDef *p);
public:
    Plugin plugin;
	LiveLooper(ParamMap& param_, sigc::slot<void> sync, const string& loop_dir_);
	~LiveLooper();
};


/****************************************************************
 ** class SCapture
 */


class SCapture: public PluginDef {
private:
    SNDFILE *       recfile;
    EngineControl&  engine;
    int             fSamplingFreq;
    int             channel;
    float           fcheckbox0;
    float           fcheckbox1;
    float           fslider0;
    float           fbargraph0;
    float           fRecC0[2];
    float           fformat;
    int             IOTA;
    int             iA;
    int             savesize;
    int             filesize;
    float           *fRec0;
    float           *fRec1;
    float           *tape;
    sem_t           m_trig;
    pthread_t       m_pthr;
    volatile bool   keep_stream;
    bool            mem_allocated;
    bool            is_wav;
    bool            err;
    float           fConst0;
    float           fRecb0[2];
    int             iRecb1[2];
    float           fRecb2[2];
    void        mem_alloc();
    void        mem_free();
    void        clear_state_f();
    int         activate(bool start);
    int         load_ui_f(const UiBuilder& b, int form);
    void        init(unsigned int samplingFreq);
    void        compute(int count, float *input0, float *output0);
    void        compute_st(int count, float *input0, float *input1, float *output0, float *output1);
    int         register_par(const ParamReg& reg);
    void        save_to_wave(SNDFILE * sf, float *tape, int lSize);
    SNDFILE     *open_stream(std::string fname);
    void        close_stream(SNDFILE **sf);
    void        stop_thread();
    void        start_thread();
    void        disc_stream();
    inline std::string get_ffilename(); 
    
    static void *run_thread(void* p);
    static void clear_state_f_static(PluginDef*);
    static int  activate_static(bool start, PluginDef*);
    static const char *glade_def;
    static const char *glade_def_st;
    static int  load_ui_f_static(const UiBuilder& b, int form);
    static void init_static(unsigned int samplingFreq, PluginDef*);
    static void compute_static(int count, float *input0, float *output0, PluginDef*);
    static void compute_static_st(int count, float *input0, float *input1, float *output0, float *output1, PluginDef*);
    static int  register_params_static(const ParamReg& reg);
    static void del_instance(PluginDef *p);
public:
    Plugin plugin;
    SCapture(EngineControl& engine, int channel_);
    ~SCapture();
};

/****************************************************************
 ** class DrumSequencer
 */

#include "faust/drumseq.h"

class Drumout {
private:
    static float* set;
    static bool mb;
    static float* data;
    static Plugin input_drum;
    static void outputdrum_compute(int count, float *input0, float *input1, float *output0, float *output1, PluginDef*);
public:
    static void set_plugin(Plugin p);
    static void set_data(float* mode, bool ready, float* buf);
    static Plugin output_drum;
    static PluginDef outputdrum;
    Drumout();
};


class DrumSequencer: public PluginDef {
private:
    int fSamplingFreq;
    FAUSTFLOAT 	position;
    FAUSTFLOAT 	ftact;
    FAUSTFLOAT 	fsec;
    FAUSTFLOAT 	fsliderbpm;
    FAUSTFLOAT 	fsliderhum;
    drumseq::Dsp drums;

    int 	counter;
    int 	seq_size;
    int 	bsize;
    FAUSTFLOAT 	step;
    FAUSTFLOAT 	step_orig;
    FAUSTFLOAT 	fSlow1;
    FAUSTFLOAT 	fSlow3;
    FAUSTFLOAT 	fSlow5;
    FAUSTFLOAT 	fSlow7;
    FAUSTFLOAT 	fSlow12;
    FAUSTFLOAT 	fSlow14;
    FAUSTFLOAT 	fSlow16;
    FAUSTFLOAT 	fSlow18;
    FAUSTFLOAT 	fSlow20;
    FAUSTFLOAT 	fSlow22;
    std::vector<int> Vectom;
    std::vector<int> Vectom1;
    std::vector<int> Vectom2;
    std::vector<int> Veckick;
    std::vector<int> Vecsnare;
    std::vector<int> Vechat;

    EngineControl&  engine;
    bool            mem_allocated;
    sigc::slot<void> sync;
    volatile bool ready;
    float *outdata;
    ParamMap& param;
    GxSeqSettings tomset;
    SeqParameter *tomp;
    GxSeqSettings tomset1;
    SeqParameter *tomp1;
    GxSeqSettings tomset2;
    SeqParameter *tomp2;
    GxSeqSettings snareset;
    SeqParameter *snarep;
    GxSeqSettings hatset;
    SeqParameter *hatp;
    GxSeqSettings kickset;
    SeqParameter *kickp;

    void mem_alloc();
    void mem_free();
    void init(unsigned int samplingFreq);
    void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
    void change_buffersize(unsigned int size);
    int register_par(const ParamReg& reg);

    int min_seq_size();
    void reset_tom();
    void reset_tom1();
    void reset_tom2();
    void reset_kick();
    void reset_hat();
    void reset_snare();

    static void init_static(unsigned int samplingFreq, PluginDef*);
    static void compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef*);
    static int register_params_static(const ParamReg& reg);
    static void del_instance(PluginDef *p);
    static int drum_load_ui(const UiBuilder& builder, int format);
public:
    Plugin plugin;
    DrumSequencer(ParamMap& param_, EngineControl& engine, sigc::slot<void> sync);
    ~DrumSequencer();
};

/****************************************************************************
*
* NAME: smbPitchShift.cpp
* VERSION: 1.2
* HOME URL: http://www.dspdimension.com
* KNOWN BUGS: none
* 
*
* COPYRIGHT 1999-2009 Stephan M. Bernsee <smb [AT] dspdimension [DOT] com>
* 
* Modified for guitarix by Hermann Meyer 2014
*
* 						The Wide Open License (WOL)
*
* Permission to use, copy, modify, distribute and sell this software and its
* documentation for any purpose is hereby granted without fee, provided that
* the above copyright notice and this license appear in all source copies. 
* THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY OF
* ANY KIND. See http://www.dspguru.com/wol.htm for more information.
*
*****************************************************************************/ 


#define M_PI 3.14159265358979323846
#define MAX_FRAME_LENGTH 8096

class smbPitchShift : public PluginDef {
private:
    gx_resample::SimpleResampler resamp;
    EngineControl&  engine;
	bool            mem_allocated;
    sigc::slot<void> sync;
	volatile bool ready;
    ParamMap& param;
	float gInFIFO[MAX_FRAME_LENGTH];
	float gOutFIFO[MAX_FRAME_LENGTH];
    float *fpb;
    float *expect;
    float *hanning;
    float *hanningd;
    float *resampin;
    float *resampin2;
    float *resampout;
    float *indata2;
	float gLastPhase[MAX_FRAME_LENGTH/2+1];
	float gSumPhase[MAX_FRAME_LENGTH/2+1];
	float gOutputAccum[2*MAX_FRAME_LENGTH];
	float gAnaFreq[MAX_FRAME_LENGTH];
	float gAnaMagn[MAX_FRAME_LENGTH];
	float gSynFreq[MAX_FRAME_LENGTH];
	float gSynMagn[MAX_FRAME_LENGTH];
	float semitones;
	float a,b,c,d,l;
	float wet;
	float dry;
    float mpi, mpi1;
    float tone;
	int   octave, osamp, numSampsToResamp, numSampsToProcess, fftFrameSize, sampleRate ;
	int latency;
    int ai;
    int aio;
    int ii;
	long  gRover ;
	double magn, phase, tmp, real, imag;
	double freqPerBin, freqPerBin1, freqPerBin2, expct;
    double fftFrameSize3;
    double fftFrameSize4;
    double osamp1,osamp2;
	long   i,k, qpd, index, inFifoLatency, stepSize, fftFrameSize2;
	
    fftwf_complex fftw_in[MAX_FRAME_LENGTH], fftw_out[MAX_FRAME_LENGTH];
    fftwf_plan ftPlanForward, ftPlanInverse;
    
    inline int load_ui_f(const UiBuilder& b, int form);
	int register_par(const ParamReg& reg);
    void change_latency();
   
    void mem_alloc();
	void mem_free();
    void clear_state();
	int activate(bool start);
	bool setParameters( int sampleRate);
	void PitchShift(int count, float *indata, float *outdata);
    void change_buffersize(unsigned int size);
    static int  activate_static(bool start, PluginDef*);
    static void del_instance(PluginDef *p);
    static int registerparam(const ParamReg& reg);
    static int load_ui_f_static(const UiBuilder& b, int form);
	static void init(unsigned int sampleRate, PluginDef *plugin); 
    static void compute_static(int count, float *input0, float *output0, PluginDef *p); 

public:
    Plugin plugin;
	smbPitchShift(ParamMap& param_, EngineControl& engine, sigc::slot<void> sync);
	~smbPitchShift();
};


} // namespace gx_engine

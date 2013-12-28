/*
 * Copyright (C) 2013 Hermann Meyer, Andreas Degert
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
 *
 *    This is part of the Guitarix Audio Engine
 *
 *
 *
 * --------------------------------------------------------------------------
 */



#define MAXRECSIZE 131072
#define MAXFILESIZE INT_MAX-MAXRECSIZE // 2147352576  //2147483648-MAXRECSIZE

SCapture::SCapture(int channel_)
    : PluginDef(),
      recfile(NULL),
      channel(channel_),
      fRec0(0),
      fRec1(0),
      tape(fRec0),
      m_pthr(0),
      keep_stream(false),
      mem_allocated(false),
      err(false) {
    version = PLUGINDEF_VERSION;
    flags = PGN_NO_PRESETS;
    if (channel == 1) {
    id = "recorder";
    name = N_("Recorder");
    groups = 0;
    description = N_("Digital Record"); // description (tooltip)
    category = N_("Misc");       // category
    shortname = "";     // shortname
    mono_audio = compute_static;
    stereo_audio = 0;
    } else {
    id = "st_recorder";
    name = N_("Stereo Recorder");
    groups = 0;
    description = N_("Digital Record"); // description (tooltip)
    category = N_("Misc");       // category
    shortname = N_("St-Recorder");     // shortname
    mono_audio = 0;
    stereo_audio = compute_static_st;
    }
    set_samplerate = init_static;
    activate_plugin = activate_static;
    register_params = register_params_static;
    load_ui = load_ui_f_static;
    clear_state = clear_state_f_static;
    delete_instance = del_instance;
    plugin = this;
    sem_init(&m_trig, 0, 0);
    start_thread();
}

SCapture::~SCapture() {
    stop_thread();
    activate(false);
}

inline std::string SCapture::get_ffilename() {
    struct stat buffer;
    struct stat sb;
    std::string pPath = getenv("HOME");
    is_wav = int(fformat) ? false : true;
    pPath +="/gxrecord/";
    if (!(stat(pPath.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))) {
        mkdir(pPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    std::string name = is_wav ?  "/guitarix_session0.wav" : "/guitarix_session0.ogg" ;
    int i = 0;
    while (stat ((pPath+name).c_str(), &buffer) == 0) {
        name.replace(name.begin()+17,name.end()-4,gx_system::to_string(i)); 
        i+=1;
    }
    return pPath+name;
}

void SCapture::disc_stream() {
    for (;;) {
        sem_wait(&m_trig);
        if (!recfile) {
            std::string fname = get_ffilename();
            recfile = open_stream(fname);
            //fprintf(stderr,"open_stream %s\n",fname.c_str());
        }
        save_to_wave(recfile, tape, savesize);
        filesize +=savesize;
        //fprintf(stderr,"save_to_wave size : %i  max: %i\n",filesize ,MAXFILESIZE);        
        if ((!keep_stream && recfile) || (filesize >MAXFILESIZE && is_wav)) {
            //fprintf(stderr,"close_stream \n");
            close_stream(&recfile);
            filesize = 0;
        }
    }
}

void *SCapture::run_thread(void *p) {
    (reinterpret_cast<SCapture *>(p))->disc_stream();
    return NULL;
}

void SCapture::stop_thread() {
    pthread_cancel (m_pthr);
    pthread_join (m_pthr, NULL);
}

void SCapture::start_thread() {
    pthread_attr_t      attr;
    struct sched_param  spar;
    int prio = 0;
    int priomax = sched_get_priority_max(SCHED_FIFO);
    if ((priomax/5) > 0) prio = priomax/5;
    spar.sched_priority = prio;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE );
    pthread_setcancelstate (PTHREAD_CANCEL_ENABLE, NULL);
    pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    pthread_attr_setschedparam(&attr, &spar);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    // pthread_attr_setstacksize(&attr, 0x10000);
    if (pthread_create(&m_pthr, &attr, run_thread,
                       reinterpret_cast<void*>(this))) {
        err = true;
    }
    pthread_attr_destroy(&attr);
}

inline void SCapture::clear_state_f()
{
    for (int i=0; i<MAXRECSIZE; i++) fRec0[i] = 0;
    for (int i=0; i<MAXRECSIZE; i++) fRec1[i] = 0;
    for (int i=0; i<2; i++) fRecb0[i] = 0;
    for (int i=0; i<2; i++) iRecb1[i] = 0;
    for (int i=0; i<2; i++) fRecb2[i] = 0;
}

void SCapture::clear_state_f_static(PluginDef *p)
{
    static_cast<SCapture*>(p)->clear_state_f();
}

inline void SCapture::init(unsigned int samplingFreq)
{
    fSamplingFreq = samplingFreq;
    IOTA = 0;
    fConst0 = (1.0f / float(fmin(192000, fmax(1, fSamplingFreq))));
}

void SCapture::init_static(unsigned int samplingFreq, PluginDef *p)
{
    static_cast<SCapture*>(p)->init(samplingFreq);
}

inline void SCapture::save_to_wave(SNDFILE * sf, float *tape, int lSize)
{
    if (sf) {
        sf_write_float(sf,tape, lSize);
        sf_write_sync(sf);
    }
}

SNDFILE *SCapture::open_stream(std::string fname)
{
    SF_INFO sfinfo ;
    sfinfo.channels = channel;
    sfinfo.samplerate = fSamplingFreq;
    sfinfo.format = is_wav ? SF_FORMAT_WAV | SF_FORMAT_FLOAT : SF_FORMAT_OGG | SF_FORMAT_VORBIS;
    
    SNDFILE * sf = sf_open(fname.c_str(), SFM_WRITE, &sfinfo);
    if (sf) return sf;
    else return NULL;
}

inline void SCapture::close_stream(SNDFILE **sf)
{
    if (*sf) sf_close(*sf);
    *sf = NULL;
}

void SCapture::mem_alloc()
{
    if (!fRec0) fRec0 = new float[MAXRECSIZE];
    if (!fRec1) fRec1 = new float[MAXRECSIZE];
    //recfile = open_stream("test.ogg");
    mem_allocated = true;
}

void SCapture::mem_free()
{
    mem_allocated = false;
    //close_stream(recfile);
    if (fRec0) { delete fRec0; fRec0 = 0; }
    if (fRec1) { delete fRec1; fRec1 = 0; }
}

int SCapture::activate(bool start)
{
    if (start) {
        if (!mem_allocated) {
            mem_alloc();
            clear_state_f();
        }
    } else if (mem_allocated) {
        mem_free();
    }
    return 0;
}

int SCapture::activate_static(bool start, PluginDef *p)
{
    return static_cast<SCapture*>(p)->activate(start);
}

void always_inline SCapture::compute(int count, float *input0, float *output0)
{
    if (err) fcheckbox0 = 0.0;
    int     iSlow0 = int(fcheckbox0);
    fcheckbox1 = 1-int(fRecb2[0]);
    for (int i=0; i<count; i++) {
        float fTemp0 = (float)input0[i];
        
        float 	fRec3 = fmax(fConst0, fabsf(fTemp0));
        int iTemp1 = int((iRecb1[1] < 4096));
        fRecb0[0] = ((iTemp1)?fmax(fRecb0[1], fRec3):fRec3);
        iRecb1[0] = ((iTemp1)?(1 + iRecb1[1]):1);
        fRecb2[0] = ((iTemp1)?fRecb2[1]:fRecb0[1]);
        
        if (iSlow0) { //record
            if (iA) {
                fRec1[IOTA] = fTemp0;
            } else {
                fRec0[IOTA] = fTemp0;
            }
            IOTA = (IOTA<MAXRECSIZE-1) ? IOTA+1 : 0; 
            if (!IOTA) { // when buffer is full, flush to stream
                iA = iA ? 0 : 1 ;
                tape = iA ? fRec0 : fRec1;
                keep_stream = true;
                savesize = MAXRECSIZE;
                sem_post(&m_trig);
            }
        } else if (IOTA) { // when record stoped, flush the rest to stream
            tape = iA ? fRec1 : fRec0;
            savesize = IOTA;
            keep_stream = false;
            sem_post(&m_trig);
            IOTA = 0;
            iA = 0;
        }
        output0[i] = fTemp0;
        // post processing
        fRecb2[1] = fRecb2[0];
        iRecb1[1] = iRecb1[0];
        fRecb0[1] = fRecb0[0];
    }
}

void __rt_func SCapture::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
    static_cast<SCapture*>(p)->compute(count, input0, output0);
}

void always_inline SCapture::compute_st(int count, float *input0, float *input1, float *output0, float *output1)
{
    if (err) fcheckbox0 = 0.0;
    int iSlow0 = int(fcheckbox0);
    fcheckbox1 = 1-int(fRecb2[0]);
    for (int i=0; i<count; i++) {
        float fTemp0 = (float)input0[i];
        float fTemp1 = (float)input1[i];
        // check if we run into clipping
        float 	fRec3 = fmax(fConst0,fmax(fabsf(fTemp0),fabsf(fTemp1)));
        int iTemp1 = int((iRecb1[1] < 4096));
        fRecb0[0] = ((iTemp1)?fmax(fRecb0[1], fRec3):fRec3);
        iRecb1[0] = ((iTemp1)?(1 + iRecb1[1]):1);
        fRecb2[0] = ((iTemp1)?fRecb2[1]:fRecb0[1]);
        
        if (iSlow0) { //record
            if (iA) {
                fRec1[IOTA] = fTemp0;
                fRec1[IOTA+1] = fTemp1;
            } else {
                fRec0[IOTA] = fTemp0;
                fRec0[IOTA+1] = fTemp1;
            }
            IOTA = (IOTA<MAXRECSIZE-2) ? IOTA+2 : 0; 
            if (!IOTA) { // when buffer is full, flush to stream
                iA = iA ? 0 : 1 ;
                tape = iA ? fRec0 : fRec1;
                keep_stream = true;
                savesize = MAXRECSIZE;
                sem_post(&m_trig);
            }
        } else if (IOTA) { // when record stoped, flush the rest to stream
            tape = iA ? fRec1 : fRec0;
            savesize = IOTA;
            keep_stream = false;
            sem_post(&m_trig);
            IOTA = 0;
            iA = 0;
        }
        output0[i] = fTemp0;
        output1[i] = fTemp1;
        // post processing
        fRecb2[1] = fRecb2[0];
        iRecb1[1] = iRecb1[0];
        fRecb0[1] = fRecb0[0];
    }
}

void SCapture::compute_static_st(int count, float *input0, float *input1, float *output0, float *output1, PluginDef *p)
{
    static_cast<SCapture*>(p)->compute_st(count, input0, input1, output0, output1);
}

int SCapture::register_par(const ParamReg& reg)
{
    static const value_pair fformat_values[] = {{"wav"},{"ogg"},{0}};
    if (channel == 1) {
    reg.registerEnumVar("recorder.file","","S",N_("select file format"),fformat_values,&fformat, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("recorder.rec","","B","",&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
    reg.registerNonMidiFloatVar("recorder.clip",&fcheckbox1, false, true, 0.0, 0.0, 1.0, 1.0);
    } else {
    reg.registerEnumVar("st_recorder.file","","S",N_("select file format"),fformat_values,&fformat, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("st_recorder.rec","","B","",&fcheckbox0, 0.0, 0.0, 1.0, 1.0);
    reg.registerNonMidiFloatVar("st_recorder.clip",&fcheckbox1, false, true, 0.0, 0.0, 1.0, 1.0);
    }
    
    return 0;
}

int SCapture::register_params_static(const ParamReg& reg)
{
    return static_cast<SCapture*>(reg.plugin)->register_par(reg);
}

inline int SCapture::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {

if (channel == 1) {
#define PARAM(p) ("recorder" "." p)
b.openHorizontalhideBox("");
b.create_feedback_switch(sw_rbutton,PARAM("rec"));

b.closeBox();

b.openHorizontalBox("");
b.create_feedback_switch(sw_rbutton,PARAM("rec"));
b.create_feedback_switch(sw_led,PARAM("clip"));
b.create_selector_no_caption(PARAM("file"));

b.closeBox();

#undef PARAM
} else {
#define PARAM(p) ("st_recorder" "." p)
b.openHorizontalhideBox("");
b.create_feedback_switch(sw_rbutton,PARAM("rec"));

b.closeBox();

b.openHorizontalBox("");
b.create_feedback_switch(sw_rbutton,PARAM("rec"));
b.create_feedback_switch(sw_led,PARAM("clip"));
b.create_selector_no_caption(PARAM("file"));

b.closeBox();

}
        return 0;
    }
    return -1;
}

int SCapture::load_ui_f_static(const UiBuilder& b, int form)
{
    return static_cast<SCapture*>(b.plugin)->load_ui_f(b, form);
}

void SCapture::del_instance(PluginDef *p)
{
    delete static_cast<SCapture*>(p);
}


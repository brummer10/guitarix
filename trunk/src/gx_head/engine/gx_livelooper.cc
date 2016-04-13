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



int LiveLooper::FileResampler::setup(int _inputRate, int _outputRate)
{
    const int qual = 16; 
    inputRate = _inputRate;
    outputRate = _outputRate;
    if (inputRate == outputRate) {
    return 0;
    }
    // resampler
    int ret = r_file.setup(inputRate, outputRate, 1, qual);
    if (ret) {
    return ret;
    }
    // k == filtlen() == 2 * qual
    // pre-fill with k-1 zeros
    r_file.inp_count = r_file.filtlen() - 1;
    r_file.out_count = 1;
    r_file.inp_data = r_file.out_data = 0;
    r_file.process();
    return 0;
}

int LiveLooper::FileResampler::run(int count, float *input, float *output)
{
    if (inputRate == outputRate) {
    memcpy(output, input, count*sizeof(float));
    return count;
    }
    r_file.inp_count = count;
    r_file.inp_data = input;
    int m = max_out_count(count);
    r_file.out_count = m;
    r_file.out_data = output;
    r_file.process();
    assert(r_file.inp_count == 0);
    assert(r_file.out_count <= 1);
    return m - r_file.out_count;
}



LiveLooper::LiveLooper(ParamMap& param_, sigc::slot<void> sync_, const string& loop_dir_)
    : PluginDef(),
      tape1(NULL),
      tape1_size(4194304),
      tape2(NULL),
      tape2_size(4194304),
      tape3(NULL),
      tape3_size(4194304),
      tape4(NULL),
      tape4_size(4194304),
      save1(false),
      save2(false),
      save3(false),
      save4(false),
      RP1(false),
      RP2(false),
      RP3(false),
      RP4(false),
      preset_name("tape"),
      cur_name("tape"),
      loop_dir(loop_dir_),
      save_p(false),
      param(param_),
      mem_allocated(false),
      sync(sync_),
      smp(),
      plugin() {
    version = PLUGINDEF_VERSION;
    id = "dubber";
    name = N_("Live Looper");
    groups = 0;
    description = N_("Live Looper"); // description (tooltip)
    category = N_("Misc");       // category
    shortname = "";     // shortname
    mono_audio = compute_static;
    stereo_audio = 0;
    set_samplerate = init_static;
    activate_plugin = activate_static;
    register_params = register_params_static;
    load_ui = load_ui_f_static;
    clear_state = clear_state_f_static;
    delete_instance = del_instance;
    plugin = this;
}

LiveLooper::~LiveLooper() {
    activate(false);
}

inline void LiveLooper::clear_state_f()
{
    for (int i=0; i<2; i++) fRec0[i] = 0;
    for (int i=0; i<2; i++) iVec0[i] = 0;
    for (int i=0; i<tape1_size; i++) tape1[i] = 0;
    for (int i=0; i<2; i++) RecSize1[i] = 0;
    for (int i=0; i<2; i++) fRec1[i] = 0;
    for (int i=0; i<2; i++) fRec2[i] = 0;
    for (int i=0; i<2; i++) iRec3[i] = 0;
    for (int i=0; i<2; i++) iRec4[i] = 0;
    for (int i=0; i<2; i++) iVec2[i] = 0;
    for (int i=0; i<tape2_size; i++) tape2[i] = 0;
    for (int i=0; i<2; i++) RecSize2[i] = 0;
    for (int i=0; i<2; i++) fRec6[i] = 0;
    for (int i=0; i<2; i++) fRec7[i] = 0;
    for (int i=0; i<2; i++) iRec8[i] = 0;
    for (int i=0; i<2; i++) iRec9[i] = 0;
    for (int i=0; i<2; i++) iVec4[i] = 0;
    for (int i=0; i<tape3_size; i++) tape3[i] = 0;
    for (int i=0; i<2; i++) RecSize3[i] = 0;
    for (int i=0; i<2; i++) fRec11[i] = 0;
    for (int i=0; i<2; i++) fRec12[i] = 0;
    for (int i=0; i<2; i++) iRec13[i] = 0;
    for (int i=0; i<2; i++) iRec14[i] = 0;
    for (int i=0; i<2; i++) iVec6[i] = 0;
    for (int i=0; i<tape4_size; i++) tape4[i] = 0;
    for (int i=0; i<2; i++) RecSize4[i] = 0;
    for (int i=0; i<2; i++) fRec16[i] = 0;
    for (int i=0; i<2; i++) fRec17[i] = 0;
    for (int i=0; i<2; i++) iRec18[i] = 0;
    for (int i=0; i<2; i++) iRec19[i] = 0;
}

void LiveLooper::clear_state_f_static(PluginDef *p)
{
    static_cast<LiveLooper*>(p)->clear_state_f();
}

inline void LiveLooper::init(unsigned int samplingFreq)
{
    fSamplingFreq = samplingFreq;
    IOTA1 = 0;
    IOTA2 = 0;
    IOTA3 = 0;
    IOTA4 = 0;
    IOTAR1 = 0;
    IOTAR2 = 0;
    IOTAR3 = 0;
    IOTAR4 = 0;
    fConst0 = (1e+01f / float(fmin(192000, fmax(1, fSamplingFreq))));
    fConst1 = (0 - fConst0);
    fConst2 = (1.0 / float(fmin(192000, fmax(1, fSamplingFreq))));
    load_file1 = "tape1";
    load_file2 = "tape2";
    load_file3 = "tape3";
    load_file4 = "tape4";
    gx_system::atomic_set(&ready,0);
}

void LiveLooper::init_static(unsigned int samplingFreq, PluginDef *p)
{
    static_cast<LiveLooper*>(p)->init(samplingFreq);
}

void LiveLooper::mem_alloc()
{
    try {
        if (!tape1) tape1 = new float[tape1_size];
        if (!tape2) tape2 = new float[tape2_size];
        if (!tape3) tape3 = new float[tape3_size];
        if (!tape4) tape4 = new float[tape4_size];
        } catch(...) {
            gx_print_error("dubber", "out of memory");
            return;
        }
    mem_allocated = true;
    gx_system::atomic_set(&ready,1);
}

void LiveLooper::mem_free()
{
    gx_system::atomic_set(&ready,0);
    mem_allocated = false;
    if (tape1) { delete[] tape1; tape1 = 0; }
    if (tape2) { delete[] tape2; tape2 = 0; }
    if (tape3) { delete[] tape3; tape3 = 0; }
    if (tape4) { delete[] tape4; tape4 = 0; }
}

int LiveLooper::do_resample(int inrate, int insize, float *input, int maxsize) {
    float *getout = 0;
    try {
        getout = new float[maxsize];
        } catch(...) {
            gx_print_error("dubber", "out of memory");
            return 0;
        }  
    smp.run(insize, input, getout);
    memset(input,0,maxsize*sizeof(float));
    for(int i = 0; i < maxsize; i++) {
        input[i] = getout[i];
    }
    delete[] getout;
    gx_print_info("dubber", Glib::ustring::compose(
        _("resampling from %1 to %2"), inrate, fSamplingFreq));

    return maxsize;
}

int LiveLooper::do_mono(int c, int f, float *oIn, float *tape, int n) {
    int p = 0;
    for(int i = 0; i < (c *f)-c; i+=c) {
        for(int j = 0; j < c; j++)
            tape[p] += oIn[i + j];
        tape[p] /= c;
        if ( p >= n) break;
        p++;
    }
    return p;
}

inline int LiveLooper::load_from_wave(std::string fname, float **tape, int tape_size)
{
    SF_INFO sfinfo;
    int n,f,c,r,i;
    int fSize = 0;
    bool res = false;
    sfinfo.format = 0;
    SNDFILE *sf = sf_open(fname.c_str(),SFM_READ,&sfinfo);
    if (sf ) {
        gx_print_info("dubber", Glib::ustring::compose(
           _("load file %1 "), fname));
        f = i = sfinfo.frames;
        c = sfinfo.channels;
        r = sfinfo.samplerate;
        n = min(tape_size,f*c);
        if( c==1 ) {
            if (r != fSamplingFreq) {
                smp.setup(r, fSamplingFreq);
                i = smp.max_out_count(f);
                res = true;
            }
            if(i>n) {
                delete[] *tape;
                *tape = NULL;
                try {
                    *tape = new float[i];
                    } catch(...) {
                    gx_print_error("dubber", "out of memory");
                    return 0;
                    }
                n=i;
            }
            fSize = sf_read_float(sf,*tape,n);
            if (res) fSize = do_resample(r, f, *tape, n);
            sf_close(sf);
            return fSize;
        } else if (c>1) {
            float *oIn = 0;
            try {
                oIn = new float[c * f];
                } catch(...) {
                    gx_print_error("dubber", "out of memory");
                    return 0;
                }
            if (r != fSamplingFreq) {
                smp.setup(r, fSamplingFreq);
                i = smp.max_out_count(f);
                res = true;
            }
            if(i>n) {
                delete[] *tape;
                *tape = NULL;
                try {
                    *tape = new float[i];
                    } catch(...) {
                    gx_print_error("dubber", "out of memory");
                    return 0;
                    }
                n=i;
            }
            sf_read_float(sf, oIn, c * f);
            memset(*tape,0,n*sizeof(float));
            int p = do_mono(c, f, oIn, *tape,  n);
            gx_print_info("dubber", Glib::ustring::compose(
                _("mix down to mono file %1 "), fname));
            delete[] oIn;
            if (res) p = do_resample(r, p, *tape, n);
            sf_close(sf);
            return p;
        }
    }
    return fSize;
}

inline void LiveLooper::load_array(std::string name)
{
    RecSize1[1] = load_from_wave(loop_dir+name+"1.wav", &tape1, tape1_size);
    tape1_size = max(4194304,RecSize1[1]);
    IOTAR1= RecSize1[1] - int(RecSize1[1]*(100-fclips1)*0.01);
    
    RecSize2[1] = load_from_wave(loop_dir+name+"2.wav", &tape2, tape2_size);
    tape2_size = max(4194304,RecSize2[1]);
    IOTAR2= RecSize2[1] - int(RecSize2[1]*(100-fclips2)*0.01);
    
    RecSize3[1] = load_from_wave(loop_dir+name+"3.wav", &tape3, tape3_size);
    tape3_size = max(4194304,RecSize3[1]);
    IOTAR3= RecSize3[1] - int(RecSize3[1]*(100-fclips3)*0.01);
    
    RecSize4[1] = load_from_wave(loop_dir+name+"4.wav", &tape4, tape4_size);
    tape4_size = max(4194304,RecSize4[1]);
    IOTAR4= RecSize4[1] - int(RecSize4[1]*(100-fclips4)*0.01);
    
    cur_name = preset_name;
}

inline void LiveLooper::save_to_wave(std::string fname, float *tape, float fSize, int tape_size)
{
    SF_INFO sfinfo ;
    sfinfo.channels = 1;
    sfinfo.samplerate = fSamplingFreq;
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;
    
    SNDFILE * sf = sf_open(fname.c_str(), SFM_WRITE, &sfinfo);
    if (sf) {
        size_t lSize = tape_size - int(fSize/fConst2);
        sf_write_float(sf,tape, lSize);
        sf_write_sync(sf);
    }
    sf_close(sf);
}

inline void LiveLooper::save_array(std::string name)
{
    if (name.compare("tape")==0 || save_p) {
        if (save1) {
            save_to_wave(loop_dir+name+"1.wav",tape1,rectime0, tape1_size);
            save1 = false;
        }
        if (save2) {
            save_to_wave(loop_dir+name+"2.wav",tape2,rectime1, tape2_size);
            save2 = false;
        }
        if (save3) {
            save_to_wave(loop_dir+name+"3.wav",tape3,rectime2, tape3_size);
            save3 = false;
        }
        if (save4) {
            save_to_wave(loop_dir+name+"4.wav",tape4,rectime3, tape4_size);
            save4 = false;
        }
    }
}

int LiveLooper::activate(bool start)
{
    if (start) {
        if (!mem_allocated) {
            mem_alloc();
            clear_state_f();
            load_array(preset_name);
        }
    } else if (mem_allocated) {
        save_array(cur_name);
        mem_free();
        load_file1 = "tape1";
        load_file2 = "tape2";
        load_file3 = "tape3";
        load_file4 = "tape4";
    }
    return 0;
}

int LiveLooper::activate_static(bool start, PluginDef *p)
{
    return static_cast<LiveLooper*>(p)->activate(start);
}

void LiveLooper::load_tape1() {
    if (!load_file1.empty()) {
        gx_system::atomic_set(&ready,0);
        sync();
        if (cur_name.compare("tape")==0 || save_p) {
            if (save1) {
                save_to_wave(loop_dir+cur_name+"1.wav",tape1,rectime0, tape1_size);
                save1 = false;
            }
        }
        RecSize1[1] = load_from_wave(load_file1, &tape1, tape1_size);
        tape1_size = max(4194304,RecSize1[1]);
        IOTAR1= RecSize1[1] - int(RecSize1[1]*(100-fclips1)*0.01);
        save1 = true;
        load_file1 = "tape1";
        gx_system::atomic_set(&ready,1);
    }
}

void LiveLooper::load_tape2() {
    if (!load_file2.empty()) {
        gx_system::atomic_set(&ready,0);
        sync();
        if (cur_name.compare("tape")==0 || save_p) {
            if (save2) {
                save_to_wave(loop_dir+cur_name+"2.wav",tape2,rectime1,tape2_size);
                save2 = false;
            }
        }
        RecSize2[1] = load_from_wave(load_file2, &tape2, tape2_size);
        tape2_size = max(4194304,RecSize2[1]);
        IOTAR2= RecSize2[1] - int(RecSize2[1]*(100-fclips2)*0.01);
        save2 = true;
        load_file2 = "tape2";
        gx_system::atomic_set(&ready,1);
    }
}

void LiveLooper::load_tape3() {
    if (!load_file3.empty()) {
        gx_system::atomic_set(&ready,0);
        sync();
        if (cur_name.compare("tape")==0 || save_p) {
            if (save3) {
                save_to_wave(loop_dir+cur_name+"3.wav",tape3,rectime2,tape3_size);
                save3 = false;
            }
        }
        RecSize3[1] = load_from_wave(load_file3, &tape3, tape3_size);
        tape3_size = max(4194304,RecSize3[1]);
        IOTAR3= RecSize3[1] - int(RecSize3[1]*(100-fclips3)*0.01);
        save3 = true;
        load_file3 = "tape3";
        gx_system::atomic_set(&ready,1);
    }
}

void LiveLooper::load_tape4() {
    if (!load_file4.empty()) {
        gx_system::atomic_set(&ready,0);
        sync();
        if (cur_name.compare("tape")==0 || save_p) {
            if (save4) {
                save_to_wave(loop_dir+cur_name+"4.wav",tape4,rectime3,tape4_size);
                save4 = false;
            }
        }
        RecSize4[1] = load_from_wave(load_file4, &tape4, tape4_size);
        tape4_size = max(4194304,RecSize4[1]);
        IOTAR4= RecSize4[1] - int(RecSize4[1]*(100-fclips4)*0.01);
        save4 = true;
        load_file4 = "tape4";
        gx_system::atomic_set(&ready,1);
    }
}

void LiveLooper::set_p_state() {
    if (!preset_name.empty() && fSamplingFreq != 0) {
        gx_system::atomic_set(&ready,0);
        sync();
        activate(true);
        if(save_p) {
            save1 = true;
            save2 = true;
            save3 = true;
            save4 = true;
            cur_name = preset_name;
           // fprintf (stderr,"save_p: %s\n",cur_name.c_str());
        }
        activate(false);
        activate(true);
        gx_system::atomic_set(&ready,1);
        save_p = false;
    }
    //fprintf (stderr,"set_p_state: %s\n",preset_name.c_str());
}

void LiveLooper::play_all_tapes() {
    play1=play2=play3=play4=play_all;
}

void always_inline LiveLooper::compute(int count, float *input0, float *output0)
{
    if (!gx_system::atomic_get(ready)) {
        memcpy(output0, input0, count * sizeof(float));
        return;
    }
    // trigger save array on exit
    if(record1 || reset1) save1 = true;
    if(record2 || reset2) save2 = true;
    if(record3 || reset3) save3 = true;
    if(record4 || reset4) save4 = true;
    // make play/ reverse play button act as radio button
    if (rplay1 && !RP1) {play1 = 0.0;RP1=true;}
    else if (play1 && RP1) {rplay1 = 0.0;RP1=false;}
    if (rplay2 && !RP2) {play2 = 0.0;RP2=true;}
    else if (play2 && RP2) {rplay2 = 0.0;RP2=false;}
    if (rplay3 && !RP3) {play3 = 0.0;RP3=true;}
    else if (play3 && RP3) {rplay3 = 0.0;RP3=false;}
    if (rplay4 && !RP4) {play4 = 0.0;RP4=true;}
    else if (play4 && RP4) {rplay4 = 0.0;RP4=false;}
    // switch off record when buffer is full
    record1     = rectime0? record1 : 0.0;
    record2     = rectime1? record2 : 0.0;
    record3     = rectime2? record3 : 0.0;
    record4     = rectime3? record4 : 0.0;
    // reset clip when reset is pressed
    if (reset1) {fclip1=100.0;fclips1=0.0;}
    if (reset2) {fclip2=100.0;fclips2=0.0;}
    if (reset3) {fclip3=100.0;fclips3=0.0;}
    if (reset4) {fclip4=100.0;fclips4=0.0;}
    // switch off reset button when buffer is empty 
    reset1     = (rectime0 < tape1_size*fConst2)? reset1 : 0.0;
    reset2     = (rectime1 < tape2_size*fConst2)? reset2 : 0.0;
    reset3     = (rectime2 < tape3_size*fConst2)? reset3 : 0.0;
    reset4     = (rectime3 < tape4_size*fConst2)? reset4 : 0.0;
    // set play head position
    
    float ph1      = RecSize1[0] ? 1.0/(RecSize1[0] * 0.001) : 0.0;
    playh1 = (1-iVec0[0]) * fmin(1000,fmax(0,float(IOTAR1*ph1)));
    float ph2      = RecSize2[0] ? 1.0/(RecSize2[0] * 0.001) : 0.0;
    playh2 = (1-iVec2[0]) *  fmin(1000,fmax(0,float(IOTAR2*ph2)));
    float ph3      = RecSize3[0] ? 1.0/(RecSize3[0] * 0.001) : 0.0;
    playh3 = (1-iVec4[0]) *  fmin(1000,fmax(0,float(IOTAR3*ph3)));
    float ph4      = RecSize4[0] ? 1.0/(RecSize4[0] * 0.001) : 0.0;
    playh4 = (1-iVec6[0]) *  fmin(1000,fmax(0,float(IOTAR4*ph4)));
    // playback speed
    float speed1 = fspeed1;
    float speed2 = fspeed2;
    float speed3 = fspeed3;
    float speed4 = fspeed4;
    // engine var settings
    float     fSlow0 = (0.0010000000000000009f * powf(10,(0.05f * gain)));
    float     fSlow1 = gain_out;
    int     iSlow3 = int(record1);
    int     iSlow4 = int((1 - reset1));
    float     fSlow5 = (((1 - iSlow3) * gain1) * (play1+rplay1));
    int     iSlow6 = int(record2);
    int     iSlow7 = int((1 - reset2));
    float     fSlow8 = (((1 - iSlow6) * gain2) * (play2+rplay2));
    int     iSlow9 = int(record3);
    int     iSlow10 = int((1 - reset3));
    float     fSlow11 = (((1 - iSlow9) * gain3) * (play3+rplay3));
    int     iSlow12 = int(record4);
    int     iSlow13 = int((1 - reset4));
    float     fSlow14 = (((1 - iSlow12) * gain4) * (play4+rplay4));
    float     fSlow15 = (0.0001f * fSlow1);
    float   iClip1  = fclip1*0.01;
    float   iClip2  = fclip2*0.01;
    float   iClip3  = fclip3*0.01;
    float   iClip4  = fclip4*0.01;
    float   iClips1  = (100-fclips1)*0.01;
    float   iClips2  = (100-fclips2)*0.01;
    float   iClips3  = (100-fclips3)*0.01;
    float   iClips4  = (100-fclips4)*0.01;
    // run loop
    for (int i=0; i<count; i++) {
        fRec0[0] = (fSlow0 + (0.999f * fRec0[1]));
        float fTemp0 = ((float)input0[i] * fRec0[0]);
        iVec0[0] = iSlow3;
        float fTemp1 = (iSlow3 * fTemp0);
        RecSize1[0] = fmin(tape1_size, (int)(iSlow4 * (((iSlow3 - iVec0[1]) <= 0) * (iSlow3 + RecSize1[1]))));
        int iTemp2 = (tape1_size - RecSize1[0]);
        rectime0 = iTemp2*fConst2;
        int iTemp3 = fmin(tape1_size-1, (int)(tape1_size - iTemp2));
        if (iSlow3 == 1) {
        IOTA1 = IOTA1>int(iTemp3*iClip1)? iTemp3 - int(iTemp3*iClips1):IOTA1+1;
        tape1[IOTA1] = fTemp1;
        }
        if (rplay1) {
        IOTAR1 = IOTAR1-speed1< (iTemp3 - int(iTemp3*iClips1))? int(iTemp3*iClip1):(IOTAR1-speed1)-1;
        } else if (play1) {
        IOTAR1 = IOTAR1+speed1>int(iTemp3*iClip1)? iTemp3 - int(iTemp3*iClips1):(IOTAR1+speed1)+1;
        }
        
        float fTemp4 = ((int((fRec1[1] != 0.0f)))?((int(((fRec2[1] > 0.0f) & (fRec2[1] < 1.0f))))?fRec1[1]:0):((int(((fRec2[1] == 0.0f) & (iTemp3 != iRec3[1]))))?fConst0:((int(((fRec2[1] == 1.0f) & (iTemp3 != iRec4[1]))))?fConst1:0)));
        fRec1[0] = fTemp4;
        fRec2[0] = fmax(0.0f, fmin(1.0f, (fRec2[1] + fTemp4)));
        iRec3[0] = ((int(((fRec2[1] >= 1.0f) & (iRec4[1] != iTemp3))))?iTemp3:iRec3[1]);
        iRec4[0] = ((int(((fRec2[1] <= 0.0f) & (iRec3[1] != iTemp3))))?iTemp3:iRec4[1]);
        iVec2[0] = iSlow6;
        float fTemp5 = (iSlow6 * fTemp0);
        RecSize2[0] = fmin(tape2_size, (int)(iSlow7 * (((iSlow6 - iVec2[1]) <= 0) * (iSlow6 + RecSize2[1]))));
        int iTemp6 = (tape2_size - RecSize2[0]);
        rectime1 = iTemp6*fConst2;
        int iTemp7 = fmin(tape2_size-1, (int)(tape2_size - iTemp6));
        if (iSlow6 == 1) {
        IOTA2 = IOTA2>int(iTemp7*iClip2)? iTemp7 - int(iTemp7*iClips2):IOTA2+1;
        tape2[IOTA2] = fTemp5;
        }
        if (rplay2) {
        IOTAR2 = IOTAR2-speed2< (iTemp7 - int(iTemp7*iClips2))? int(iTemp7*iClip2):(IOTAR2-speed2)-1;
        } else if (play2) {
        IOTAR2 = IOTAR2+speed2>int(iTemp7*iClip2)? iTemp7 - int(iTemp7*iClips2):(IOTAR2+speed2)+1;
        }
        
        float fTemp8 = ((int((fRec6[1] != 0.0f)))?((int(((fRec7[1] > 0.0f) & (fRec7[1] < 1.0f))))?fRec6[1]:0):((int(((fRec7[1] == 0.0f) & (iTemp7 != iRec8[1]))))?fConst0:((int(((fRec7[1] == 1.0f) & (iTemp7 != iRec9[1]))))?fConst1:0)));
        fRec6[0] = fTemp8;
        fRec7[0] = fmax(0.0f, fmin(1.0f, (fRec7[1] + fTemp8)));
        iRec8[0] = ((int(((fRec7[1] >= 1.0f) & (iRec9[1] != iTemp7))))?iTemp7:iRec8[1]);
        iRec9[0] = ((int(((fRec7[1] <= 0.0f) & (iRec8[1] != iTemp7))))?iTemp7:iRec9[1]);
        iVec4[0] = iSlow9;
        float fTemp9 = (iSlow9 * fTemp0);
        RecSize3[0] = fmin(tape3_size, (int)(iSlow10 * (((iSlow9 - iVec4[1]) <= 0) * (iSlow9 + RecSize3[1]))));
        int iTemp10 = (tape3_size - RecSize3[0]);
        rectime2 = iTemp10*fConst2;
        int iTemp11 = fmin(tape3_size-1, (int)(tape3_size - iTemp10));
        if (iSlow9 == 1) {
        IOTA3 = IOTA3>int(iTemp11*iClip3)? iTemp11 - int(iTemp11*iClips3):IOTA3+1;
        tape3[IOTA3] = fTemp9;
        }
        if (rplay3) {
        IOTAR3 = IOTAR3-speed3< (iTemp11 - int(iTemp11*iClips3))? int(iTemp11*iClip3):(IOTAR3-speed3)-1;
        } else if (play3) {
        IOTAR3 = IOTAR3+speed3>int(iTemp11*iClip3)? iTemp11 - int(iTemp11*iClips3):(IOTAR3+speed3)+1;
        }
        
        float fTemp12 = ((int((fRec11[1] != 0.0f)))?((int(((fRec12[1] > 0.0f) & (fRec12[1] < 1.0f))))?fRec11[1]:0):((int(((fRec12[1] == 0.0f) & (iTemp11 != iRec13[1]))))?fConst0:((int(((fRec12[1] == 1.0f) & (iTemp11 != iRec14[1]))))?fConst1:0)));
        fRec11[0] = fTemp12;
        fRec12[0] = fmax(0.0f, fmin(1.0f, (fRec12[1] + fTemp12)));
        iRec13[0] = ((int(((fRec12[1] >= 1.0f) & (iRec14[1] != iTemp11))))?iTemp11:iRec13[1]);
        iRec14[0] = ((int(((fRec12[1] <= 0.0f) & (iRec13[1] != iTemp11))))?iTemp11:iRec14[1]);
        iVec6[0] = iSlow12;
        float fTemp13 = (iSlow12 * fTemp0);
        RecSize4[0] = fmin(tape4_size, (int)(iSlow13 * (((iSlow12 - iVec6[1]) <= 0) * (iSlow12 + RecSize4[1]))));
        int iTemp14 = (tape4_size - RecSize4[0]);
        rectime3 = iTemp14*fConst2;
        int iTemp15 = fmin(tape4_size-1, (int)(tape4_size - iTemp14));
        if (iSlow12 == 1) {
        IOTA4 = IOTA4>int(iTemp15*iClip4)? iTemp15 - int(iTemp15*iClips4):IOTA4+1;
        tape4[IOTA4] = fTemp13;
        }
        if (rplay4) {
        IOTAR4 = IOTAR4-speed4< (iTemp15 - int(iTemp15*iClips4))? int(iTemp15*iClip4):(IOTAR4-speed4)-1;
        } else if (play4) {
        IOTAR4 = IOTAR4+speed4>int(iTemp15*iClip4)? iTemp15 - int(iTemp15*iClips4):(IOTAR4+speed4)+1;
        }
        
        float fTemp16 = ((int((fRec16[1] != 0.0f)))?((int(((fRec17[1] > 0.0f) & (fRec17[1] < 1.0f))))?fRec16[1]:0):((int(((fRec17[1] == 0.0f) & (iTemp15 != iRec18[1]))))?fConst0:((int(((fRec17[1] == 1.0f) & (iTemp15 != iRec19[1]))))?fConst1:0)));
        fRec16[0] = fTemp16;
        fRec17[0] = fmax(0.0f, fmin(1.0f, (fRec17[1] + fTemp16)));
        iRec18[0] = ((int(((fRec17[1] >= 1.0f) & (iRec19[1] != iTemp15))))?iTemp15:iRec18[1]);
        iRec19[0] = ((int(((fRec17[1] <= 0.0f) & (iRec18[1] != iTemp15))))?iTemp15:iRec19[1]);
        output0[i] = (float)((fSlow15 * ((fSlow14 * ((fRec17[0] * tape4[int(IOTAR4)]) + ((1.0f - fRec17[0]) * tape4[int(IOTAR4)]))) + ((fSlow11 * ((fRec12[0] * tape3[int(IOTAR3)]) + ((1.0f - fRec12[0]) * tape3[int(IOTAR3)]))) + ((fSlow8 * ((fRec7[0] * tape2[int(IOTAR2)]) + ((1.0f - fRec7[0]) * tape2[int(IOTAR2)]))) + (fSlow5 * ((fRec2[0] * tape1[int(IOTAR1)]) + ((1.0f - fRec2[0]) * tape1[int(IOTAR1)]))))))) + (fTemp0));
        // post processing
        iRec19[1] = iRec19[0];
        iRec18[1] = iRec18[0];
        fRec17[1] = fRec17[0];
        fRec16[1] = fRec16[0];
        RecSize4[1] = RecSize4[0];
        iVec6[1] = iVec6[0];
        iRec14[1] = iRec14[0];
        iRec13[1] = iRec13[0];
        fRec12[1] = fRec12[0];
        fRec11[1] = fRec11[0];
        RecSize3[1] = RecSize3[0];
        iVec4[1] = iVec4[0];
        iRec9[1] = iRec9[0];
        iRec8[1] = iRec8[0];
        fRec7[1] = fRec7[0];
        fRec6[1] = fRec6[0];
        RecSize2[1] = RecSize2[0];
        iVec2[1] = iVec2[0];
        iRec4[1] = iRec4[0];
        iRec3[1] = iRec3[0];
        fRec2[1] = fRec2[0];
        fRec1[1] = fRec1[0];
        RecSize1[1] = RecSize1[0];
        iVec0[1] = iVec0[0];
        fRec0[1] = fRec0[0];
    }
}

void __rt_func LiveLooper::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
    static_cast<LiveLooper*>(p)->compute(count, input0, output0);
}

int LiveLooper::register_par(const ParamReg& reg)
{
    reg.registerVar("dubber.clip1","","S",N_("percentage clip at the delay length "),&fclip1, 1e+02f, 0.0f, 1e+02f, 1.0f);
    reg.registerVar("dubber.clip2","","S",N_("percentage clip at the delay length "),&fclip2, 1e+02f, 0.0f, 1e+02f, 1.0f);
    reg.registerVar("dubber.clip3","","S",N_("percentage clip at the delay length "),&fclip3, 1e+02f, 0.0f, 1e+02f, 1.0f);
    reg.registerVar("dubber.clip4","","S",N_("percentage clip at the delay length "),&fclip4, 1e+02f, 0.0f, 1e+02f, 1.0f);
    reg.registerVar("dubber.clips1","","S",N_("percentage cut on the delay start "),&fclips1, 0.0f, 0.0f, 1e+02f, 1.0f);
    reg.registerVar("dubber.clips2","","S",N_("percentage cut on the delay start "),&fclips2, 0.0f, 0.0f, 1e+02f, 1.0f);
    reg.registerVar("dubber.clips3","","S",N_("percentage cut on the delay start "),&fclips3, 0.0f, 0.0f, 1e+02f, 1.0f);
    reg.registerVar("dubber.clips4","","S",N_("percentage cut on the delay start "),&fclips4, 0.0f, 0.0f, 1e+02f, 1.0f);
    reg.registerVar("dubber.speed1","","S",N_("playback speed "),&fspeed1, 0.0f, -0.9f, 0.9f, 0.01f);
    reg.registerVar("dubber.speed2","","S",N_("playback speed "),&fspeed2, 0.0f, -0.9f, 0.9f, 0.01f);
    reg.registerVar("dubber.speed3","","S",N_("playback speed "),&fspeed3, 0.0f, -0.9f, 0.9f, 0.01f);
    reg.registerVar("dubber.speed4","","S",N_("playback speed "),&fspeed4, 0.0f, -0.9f, 0.9f, 0.01f);
    reg.registerNonMidiFloatVar("dubber.bar1",&rectime0, false, true, 0.0, 0.0, 96.0, 1.0);
    reg.registerNonMidiFloatVar("dubber.bar2",&rectime1, false, true, 0.0, 0.0, 96.0, 1.0);
    reg.registerNonMidiFloatVar("dubber.bar3",&rectime2, false, true, 0.0, 0.0, 96.0, 1.0);
    reg.registerNonMidiFloatVar("dubber.bar4",&rectime3, false, true, 0.0, 0.0, 96.0, 1.0);
    reg.registerVar("dubber.gain","","S",N_("overall gain of the input"),&gain, 0.0f, -2e+01f, 12.0f, 0.1f);
    reg.registerVar("dubber.level1","","S",N_("percentage of the delay gain level"),&gain1, 5e+01f, 0.0f, 1e+02f, 1.0f);
    reg.registerVar("dubber.level2","","S",N_("percentage of the delay gain level"),&gain2, 5e+01f, 0.0f, 1e+02f, 1.0f);
    reg.registerVar("dubber.level3","","S",N_("percentage of the delay gain level"),&gain3, 5e+01f, 0.0f, 1e+02f, 1.0f);
    reg.registerVar("dubber.level4","","S",N_("percentage of the delay gain level"),&gain4, 5e+01f, 0.0f, 1e+02f, 1.0f);
    reg.registerVar("dubber.mix","","S",N_("overall gain_out of the delay line in percent"),&gain_out, 1e+02f, 0.0f, 1.5e+02f, 1.0f);
    reg.registerVar("dubber.play1","","B",N_("play tape 1"),&play1, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("dubber.play2","","B",N_("play tape 2"),&play2, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("dubber.play3","","B",N_("play tape 3"),&play3, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("dubber.play4","","B",N_("play tape 4"),&play4, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("dubber.rplay1","","B",N_("play reverse"),&rplay1, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("dubber.rplay2","","B",N_("play reverse"),&rplay2, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("dubber.rplay3","","B",N_("play reverse"),&rplay3, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("dubber.rplay4","","B",N_("play reverse"),&rplay4, 0.0, 0.0, 1.0, 1.0);
    reg.registerNonMidiFloatVar("dubber.playh1",&playh1, false, true, 0.0, 0.0, 1000.0, 1.0);
    reg.registerNonMidiFloatVar("dubber.playh2",&playh2, false, true, 0.0, 0.0, 1000.0, 1.0);
    reg.registerNonMidiFloatVar("dubber.playh3",&playh3, false, true, 0.0, 0.0, 1000.0, 1.0);
    reg.registerNonMidiFloatVar("dubber.playh4",&playh4, false, true, 0.0, 0.0, 1000.0, 1.0);
    reg.registerVar("dubber.rec1","","B",N_("record"),&record1, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("dubber.rec2","","B",N_("record"),&record2, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("dubber.rec3","","B",N_("record"),&record3, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("dubber.rec4","","B",N_("record"),&record4, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("dubber.reset1","","B",N_("erase"),&reset1, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("dubber.reset2","","B",N_("erase"),&reset2, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("dubber.reset3","","B",N_("erase"),&reset3, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("dubber.reset4","","B",N_("erase"),&reset4, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("dubber.load1","","B",N_("import file"),&load1, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("dubber.load2","","B",N_("import file"),&load2, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("dubber.load3","","B",N_("import file"),&load3, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("dubber.load4","","B",N_("import file"),&load4, 0.0, 0.0, 1.0, 1.0);
    reg.registerVar("dubber.playall","","B",N_("play all tapes "),&play_all, 0.0, 0.0, 1.0, 1.0);
    param["dubber.playall"].signal_changed_float().connect(
        sigc::hide(sigc::mem_fun(this, &LiveLooper::play_all_tapes)));
    param.reg_non_midi_par("dubber.savefile", &save_p, false);
    param.reg_preset_string("dubber.filename", "", &preset_name, "tape");
    param["dubber.filename"].signal_changed_string().connect(
        sigc::hide(sigc::mem_fun(this, &LiveLooper::set_p_state)));
    param.reg_string("dubber.loadfile1", "", &load_file1, "tape1");
    param.reg_string("dubber.loadfile2", "", &load_file2, "tape2");
    param.reg_string("dubber.loadfile3", "", &load_file3, "tape3");
    param.reg_string("dubber.loadfile4", "", &load_file4, "tape4");
    param["dubber.loadfile1"].signal_changed_string().connect(
        sigc::hide(sigc::mem_fun(this, &LiveLooper::load_tape1)));
    param["dubber.loadfile2"].signal_changed_string().connect(
        sigc::hide(sigc::mem_fun(this, &LiveLooper::load_tape2)));
    param["dubber.loadfile3"].signal_changed_string().connect(
        sigc::hide(sigc::mem_fun(this, &LiveLooper::load_tape3)));
    param["dubber.loadfile4"].signal_changed_string().connect(
        sigc::hide(sigc::mem_fun(this, &LiveLooper::load_tape4)));
    return 0;
}

int LiveLooper::register_params_static(const ParamReg& reg)
{
    return static_cast<LiveLooper*>(reg.plugin)->register_par(reg);
}

inline int LiveLooper::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("dubber" "." p)
b.openHorizontalhideBox("");
b.create_switch_no_caption(sw_pbutton,PARAM("playall"));
b.closeBox();

b.openHorizontalBox("");
    b.create_mid_rackknob(PARAM("gain"), "Gain");
    
    b.openTabBox("");
    
        b.openHorizontalBox(N_("Tape 1"));
        
            b.openVerticalBox("");
                b.openHorizontalBox("");
                    b.insertSpacer();
                    b.openVerticalBox("");
                        b.insertSpacer();
                        b.create_p_display(PARAM("playh1"),PARAM("clips1"),PARAM("clip1"));
                        b.insertSpacer();
                        b.openHorizontalBox("");
                        b.create_feedback_switch(sw_rbutton,PARAM("rec1"));
                        b.create_feedback_switch(sw_pbutton,PARAM("play1"));
                        b.create_feedback_switch(sw_prbutton,PARAM("rplay1"));
                        b.create_feedback_switch(sw_button,PARAM("reset1"));
                        b.create_fload_switch(sw_fbutton,PARAM("load1"),PARAM("loadfile1"));
                        b.closeBox();
                        b.closeBox();
                        
                        b.insertSpacer();
                        b.create_port_display(PARAM("bar1"), "Buffer");
                        b.insertSpacer();
                        b.closeBox();
                        
                        b.openHorizontalBox("");
                        b.insertSpacer();
                        b.openVerticalBox("");
                        
                        b.create_feedback_slider(PARAM("clips1"), "Cut");
                        b.create_feedback_slider(PARAM("clip1"), "Clip");
                        b.create_master_slider(PARAM("speed1"), "Speed");
                        
                    b.closeBox();
                    b.insertSpacer();
                b.closeBox();
            
            b.closeBox();
            b.openVerticalBox("");
                b.insertSpacer();
                b.create_small_rackknobr(PARAM("level1"), "Level");
            b.closeBox();
        b.closeBox();
            
        b.openHorizontalBox(N_("Tape 2"));
            b.openVerticalBox("");
            
                b.openHorizontalBox("");
                    b.insertSpacer();
                    b.openVerticalBox("");
                        b.insertSpacer();
                        b.create_p_display(PARAM("playh2"),PARAM("clips2"),PARAM("clip2"));
                        b.insertSpacer();
                        b.openHorizontalBox("");
                        b.create_feedback_switch(sw_rbutton,PARAM("rec2"));
                        b.create_feedback_switch(sw_pbutton,PARAM("play2"));
                        b.create_feedback_switch(sw_prbutton,PARAM("rplay2"));
                        b.create_feedback_switch(sw_button,PARAM("reset2"));
                        b.create_fload_switch(sw_fbutton,PARAM("load2"),PARAM("loadfile2"));
                        b.closeBox();
                        b.closeBox();
                        b.insertSpacer();
                        b.create_port_display(PARAM("bar2"), "Buffer");
                        b.insertSpacer();
                        b.closeBox();
                        b.openHorizontalBox("");
                        b.insertSpacer();
                        b.openVerticalBox("");
                        b.create_feedback_slider(PARAM("clips2"), "Cut");
                        b.create_feedback_slider(PARAM("clip2"), "Clip");
                        b.create_master_slider(PARAM("speed2"), "Speed");
                    b.closeBox();
                    b.insertSpacer();
                b.closeBox();
                
            b.closeBox();
            
            b.openVerticalBox("");
                b.insertSpacer();
                b.create_small_rackknobr(PARAM("level2"), "Level");
            b.closeBox();
        b.closeBox();
        
        b.openHorizontalBox(N_("Tape 3"));
            b.openVerticalBox("");
            
                b.openHorizontalBox("");
                    b.insertSpacer();
                    b.openVerticalBox("");
                        b.insertSpacer();
                        b.create_p_display(PARAM("playh3"),PARAM("clips3"),PARAM("clip3"));
                        b.insertSpacer();
                        b.openHorizontalBox("");
                        b.create_feedback_switch(sw_rbutton,PARAM("rec3"));
                        b.create_feedback_switch(sw_pbutton,PARAM("play3"));
                        b.create_feedback_switch(sw_prbutton,PARAM("rplay3"));
                        b.create_feedback_switch(sw_button,PARAM("reset3"));
                        b.create_fload_switch(sw_fbutton,PARAM("load3"),PARAM("loadfile3"));
                        b.closeBox();
                        b.closeBox();
                        b.insertSpacer();
                        b.create_port_display(PARAM("bar3"), "Buffer");
                        b.insertSpacer();
                        b.closeBox();
                        b.openHorizontalBox("");
                        b.insertSpacer();
                        b.openVerticalBox("");
                        b.create_feedback_slider(PARAM("clips3"), "Cut");
                        b.create_feedback_slider(PARAM("clip3"), "Clip");
                        b.create_master_slider(PARAM("speed3"), "Speed");
                    b.closeBox();
                    b.insertSpacer();
                b.closeBox();
                
            b.closeBox();
            b.openVerticalBox("");
                b.insertSpacer();
                b.create_small_rackknobr(PARAM("level3"), "Level");
            b.closeBox();
        b.closeBox();
        
        b.openHorizontalBox(N_("Tape 4"));
            b.openVerticalBox("");
            
                b.openHorizontalBox("");
                    b.insertSpacer();
                    b.openVerticalBox("");
                        b.insertSpacer();
                        b.create_p_display(PARAM("playh4"),PARAM("clips4"),PARAM("clip4"));
                        b.insertSpacer();
                        b.openHorizontalBox("");
                        b.create_feedback_switch(sw_rbutton,PARAM("rec4"));
                        b.create_feedback_switch(sw_pbutton,PARAM("play4"));
                        b.create_feedback_switch(sw_prbutton,PARAM("rplay4"));
                        b.create_feedback_switch(sw_button,PARAM("reset4"));
                        b.create_fload_switch(sw_fbutton,PARAM("load4"),PARAM("loadfile4"));
                        b.closeBox();
                        b.closeBox();
                        b.insertSpacer();
                        b.create_port_display(PARAM("bar4"), "Buffer");
                        b.insertSpacer();
                        b.closeBox();
                        b.openHorizontalBox("");
                        b.insertSpacer();
                        b.openVerticalBox("");
                        b.create_feedback_slider(PARAM("clips4"), "Cut");
                        b.create_feedback_slider(PARAM("clip4"), "Clip");
                        b.create_master_slider(PARAM("speed4"), "Speed");
                    b.closeBox();
                    b.insertSpacer();
                b.closeBox();
                
            b.closeBox();
            b.openVerticalBox("");
                b.insertSpacer();
                b.create_small_rackknobr(PARAM("level4"), "Level");
            b.closeBox();
        b.closeBox();
        
    b.closeBox();
    
    b.create_mid_rackknob(PARAM("mix"), "Mix");
b.closeBox();

#undef PARAM
        return 0;
    }
    return -1;
}

int LiveLooper::load_ui_f_static(const UiBuilder& b, int form)
{
    return static_cast<LiveLooper*>(b.plugin)->load_ui_f(b, form);
}

void LiveLooper::del_instance(PluginDef *p)
{
    delete static_cast<LiveLooper*>(p);
}

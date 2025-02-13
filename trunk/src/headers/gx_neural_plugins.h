/*
 * Copyright (C) 2024 Hermann Meyer
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


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreorder"
#pragma GCC diagnostic ignored "-Winfinite-recursion"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "dsp.h"
#include "get_dsp.h"
#include "activations.h"
#include "RTNeural.h"
#pragma GCC diagnostic pop

namespace gx_jack { class GxJack; }

namespace gx_engine {

/****************************************************************
 ** class Neural Amp Modeler
 */

class NeuralAmp: public PluginDef {
private:
    nam::DSP* model;
    ParamMap& param;
    gx_resample::FixedRateResampler smp;
    sigc::slot<void> sync;
    volatile int ready;
    int fSampleRate;
    int mSampleRate;
    float fVslider0;
    float fVslider1;
    double fRec0[2];
    double fRec1[2];
    int need_resample;
    float loudness;
    bool is_inited;
    bool do_ramp;
    float filelist;
    float ramp;
    float ramp_step;
    Glib::ustring load_file;
    Glib::ustring load_path;
    std::vector<Glib::ustring> nam_file_names;
    std::string idstring;

    void clear_state_f();
    int load_ui_f(const UiBuilder& b, int form);
    void init(unsigned int sample_rate);
    void compute(int count, float *input0, float *output0);
    void load_nam_file();
    void create_nam_filelist();
    int register_par(const ParamReg& reg);

    static void clear_state_f_static(PluginDef*);
    static void init_static(unsigned int sample_rate, PluginDef*);
    static int load_ui_f_static(const UiBuilder& b, int form);
    static void compute_static(int count, float *input0, float *output0, PluginDef*);
    static int register_params_static(const ParamReg& reg);
    static void del_instance(PluginDef *p);
public:
    Plugin plugin;
    NeuralAmp(ParamMap& param_, std::string id, sigc::slot<void> sync);
    ~NeuralAmp();
};

/****************************************************************
 ** class NeuralAmpMulti 
 */

class NeuralAmpMulti: public PluginDef {
private:
    nam::DSP* modela;
    nam::DSP* modelb;
    ParamMap& param;
    ParallelThread* pro;
    gx_resample::FixedRateResampler smpa;
    gx_resample::FixedRateResampler smpb;
    sigc::slot<void> sync;
    volatile int ready;
    int fSampleRate;
    int maSampleRate;
    int mbSampleRate;
    float *buf;
    int nframes;
    float fVslider0;
    float fVslider01;
    float fVslider1;
    float fVslider2;
    int IOTA0;
    double fDec0[16384];
    float fVslider02;
    double fDel4[2];
    double fDel0[2];
    double fDel1[2];
    double fDel2[2];
    double fDel3[2];
    double fRec0[2];
    double fRec01[2];
    double fRec1[2];
    double fRec2[2];
    int need_aresample;
    int need_bresample;
    float loudnessa;
    float loudnessb;
    bool is_inited;
    bool do_ramp;
    float afilelist;
    float bfilelist;
    float ramp;
    float ramp_step;
    Glib::ustring load_afile;
    Glib::ustring load_bfile;
    Glib::ustring load_apath;
    Glib::ustring load_bpath;
    std::vector<Glib::ustring> nam_afile_names;
    std::vector<Glib::ustring> nam_bfile_names;
    std::string idstring;

    void clear_state_f();
    int load_ui_f(const UiBuilder& b, int form);
    void init(unsigned int sample_rate);
    void compute(int count, float *input0, float *output0);
    void processDelay(int count, float *buf);
    void processModelA(int count, float *buf);
    void processModelB();
    void load_nam_afile();
    void load_nam_bfile();
    void create_nam_afilelist();
    void create_nam_bfilelist();
    int register_par(const ParamReg& reg);

    static void clear_state_f_static(PluginDef*);
    static void init_static(unsigned int sample_rate, PluginDef*);
    static int load_ui_f_static(const UiBuilder& b, int form);
    static void compute_static(int count, float *input0, float *output0, PluginDef*);
    static int register_params_static(const ParamReg& reg);
    static void del_instance(PluginDef *p);
public:
    Plugin plugin;
    NeuralAmpMulti(ParamMap& param_, std::string id, ParallelThread *pro_, sigc::slot<void> sync);
    ~NeuralAmpMulti();
};

/****************************************************************
 ** class RTNeural 
 */

class RtNeural: public PluginDef {
private:
    RTNeural::Model<float> *model;
    ParamMap& param;
    gx_resample::FixedRateResampler smp;
    sigc::slot<void> sync;
    volatile int ready;
    int fSampleRate;
    int mSampleRate;
    float fVslider0;
    float fVslider1;
    double fRec0[2];
    double fRec1[2];
    int need_resample;
    bool is_inited;
    float filelist;
    Glib::ustring load_file;
    Glib::ustring load_path;
    std::vector<Glib::ustring> rtneural_file_names;
    std::string idstring;

    void clear_state_f();
    int load_ui_f(const UiBuilder& b, int form);
    void init(unsigned int sample_rate);
    void compute(int count, float *input0, float *output0);
    void get_samplerate(std::string config_file);
    void load_json_file();
    void create_rtneural_filelist();
    int register_par(const ParamReg& reg);

    static void clear_state_f_static(PluginDef*);
    static void init_static(unsigned int sample_rate, PluginDef*);
    static int load_ui_f_static(const UiBuilder& b, int form);
    static void compute_static(int count, float *input0, float *output0, PluginDef*);
    static int register_params_static(const ParamReg& reg);
    static void del_instance(PluginDef *p);
public:
    Plugin plugin;
    RtNeural(ParamMap& param_, std::string id, sigc::slot<void> sync);
    ~RtNeural();
};

/****************************************************************
 ** class RTNeuralMulti
 */

class RtNeuralMulti: public PluginDef {
private:
    RTNeural::Model<float> *modela;
    RTNeural::Model<float> *modelb;
    ParamMap& param;
    ParallelThread* pro;
    gx_resample::FixedRateResampler smpa;
    gx_resample::FixedRateResampler smpb;
    sigc::slot<void> sync;
    volatile int ready;
    int fSampleRate;
    int maSampleRate;
    int mbSampleRate;
    float *buf;
    int nframes;
    float fVslider0;
    float fVslider01;
    float fVslider1;
    float fVslider2;
    int IOTA0;
    double fDec0[16384];
    float fVslider02;
    double fDel4[2];
    double fDel0[2];
    double fDel1[2];
    double fDel2[2];
    double fDel3[2];
    double fRec0[2];
    double fRec01[2];
    double fRec1[2];
    double fRec2[2];
    int need_aresample;
    int need_bresample;
    bool is_inited;
    float afilelist;
    float bfilelist;
    Glib::ustring load_afile;
    Glib::ustring load_bfile;
    Glib::ustring load_apath;
    Glib::ustring load_bpath;
    std::vector<Glib::ustring> rtneural_afile_names;
    std::vector<Glib::ustring> rtneural_bfile_names;
    std::string idstring;

    void clear_state_f();
    int load_ui_f(const UiBuilder& b, int form);
    void init(unsigned int sample_rate);
    void processDelay(int count, float *buf);
    void processModelA(int count, float *buf);
    void processModelB();
    void compute(int count, float *input0, float *output0);
    void get_samplerate(std::string config_file, int *mSampleRate);
    void load_json_afile();
    void load_json_bfile();
    void create_rtneural_afilelist();
    void create_rtneural_bfilelist();
    int register_par(const ParamReg& reg);

    static void clear_state_f_static(PluginDef*);
    static void init_static(unsigned int sample_rate, PluginDef*);
    static int load_ui_f_static(const UiBuilder& b, int form);
    static void compute_static(int count, float *input0, float *output0, PluginDef*);
    static int register_params_static(const ParamReg& reg);
    static void del_instance(PluginDef *p);
public:
    Plugin plugin;
    RtNeuralMulti(ParamMap& param_, std::string id, ParallelThread *pro_, sigc::slot<void> sync);
    ~RtNeuralMulti();
};

} // namespace gx_engine

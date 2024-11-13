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
 *
 *
 *    This is part of the Guitarix Audio Engine
 *
 *
 *
 * --------------------------------------------------------------------------
 */

#include "engine.h"
#include "gx_faust_support.h"

namespace gx_engine {

/****************************************************************
 ** class Neural Amp Modeler
 */

NeuralAmp::NeuralAmp(ParamMap& param_, std::string id_, sigc::slot<void> sync_)
    : PluginDef(), model(nullptr), param(param_), smp(), sync(sync_), idstring(id_), plugin() {
    version = PLUGINDEF_VERSION;
    flags = 0;
    id = idstring.c_str();
    name = N_("Neural Amp Modeler");
    groups = 0;
    description = N_("Neural Amp Modeler by Steven Atkinson"); // description (tooltip)
    category = N_("Neural");       // category
    shortname = "NAM";     // shortname
    mono_audio = compute_static;
    stereo_audio = 0;
    set_samplerate = init_static;
    activate_plugin = 0;
    register_params = register_params_static;
    load_ui = load_ui_f_static;
    clear_state = clear_state_f_static;
    delete_instance = del_instance;
    plugin = this;
    need_resample = 0;
    is_inited = false;
    loudness = 0.0;
    gx_system::atomic_set(&ready, 0);
 }

NeuralAmp::~NeuralAmp() {
    delete model;
}

inline void NeuralAmp::clear_state_f()
{
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec1[l0] = 0.0;
    for (int l0 = 0; l0 < 127; l0 = l0 + 1) nam_file_names.push_back("None");
}

void NeuralAmp::clear_state_f_static(PluginDef *p)
{
    static_cast<NeuralAmp*>(p)->clear_state_f();
}

inline void NeuralAmp::init(unsigned int sample_rate)
{
    fSampleRate = sample_rate;
    clear_state_f();
    is_inited = true;
    load_nam_file();
}

void NeuralAmp::init_static(unsigned int sample_rate, PluginDef *p)
{
    static_cast<NeuralAmp*>(p)->init(sample_rate);
}

void always_inline NeuralAmp::compute(int count, float *input0, float *output0)
{
    if (output0 != input0)
        memcpy(output0, input0, count*sizeof(float));
    if (!model) return;
    double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
    double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider1));
    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        fRec0[0] = fSlow0 + 0.999 * fRec0[1];
        output0[i0] = float(double(output0[i0]) * fRec0[0]);
        fRec0[1] = fRec0[0];
    }
    if (model && gx_system::atomic_get(ready)) {
        if (need_resample) {
            int ReCount = count;
            if (need_resample == 1) {
                ReCount = smp.max_out_count(count);
            } else if (need_resample == 2) {
                ReCount = static_cast<int>(ceil((count*static_cast<double>(mSampleRate))/fSampleRate));
            }

            float buf[ReCount];
            memset(buf, 0, ReCount*sizeof(float));

            if (need_resample == 1) {
                ReCount = smp.up(count, output0, buf);
            } else if (need_resample == 2) {
                smp.down(output0, buf);
            } else {
                memcpy(buf, output0, ReCount * sizeof(float));
            }

            model->process(buf, buf, ReCount);

            if (need_resample == 1) {
                smp.down(buf, output0);
            } else if (need_resample == 2) {
                smp.up(ReCount, buf, output0);
            }
        } else {
            model->process(output0, output0, count);
        }
    }
    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        fRec1[0] = fSlow1 + 0.999 * fRec1[1];
        output0[i0] = float(double(output0[i0]) * fRec1[0]);
        fRec1[1] = fRec1[0];
    }
}

void NeuralAmp::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
    static_cast<NeuralAmp*>(p)->compute(count, input0, output0);
}

// non rt callback
void NeuralAmp::load_nam_file() {
    if (!load_file.empty() && is_inited) {
        if (nam_file_names.size() < 1 || filelist < 1.0) return;
        gx_system::atomic_set(&ready, 0);
        sync();
        delete model;
        model = nullptr;
        need_resample = 0;
        clear_state_f();
        int32_t warmUpSize = 4096;
        try {
            load_file = load_path + "/" + nam_file_names[filelist];
            model = nam::get_dsp(std::string(load_file)).release();
        } catch (const std::exception&) {
            gx_print_info("Neural Amp Modeler", "fail to load " + load_file);
            load_file = "None";
        }
        
        if (model) {
            if (model->HasLoudness()) loudness = model->GetLoudness();
            mSampleRate = static_cast<int>(model->GetExpectedSampleRate());
            //model->SetLoudness(-15.0);
            if (mSampleRate <= 0) mSampleRate = 48000;
            if (mSampleRate > fSampleRate) {
                smp.setup(fSampleRate, mSampleRate);
                need_resample = 1;
            } else if (mSampleRate < fSampleRate) {
                smp.setup(mSampleRate, fSampleRate);
                need_resample = 2;
            } 
            float* buffer = new float[warmUpSize];
            memset(buffer, 0, warmUpSize * sizeof(float));

            model->process(buffer, buffer, warmUpSize);

            delete[] buffer;
            //fprintf(stderr, "sample rate = %i file = %i l = %f\n",fSampleRate, mSampleRate, loudness);
            //fprintf(stderr, "%s\n", load_file.c_str());
        } 
        gx_system::atomic_set(&ready, 1);
    }
}

// non rt callback
void NeuralAmp::create_nam_filelist() {
    if (load_path.empty()) return;
    Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(load_path);
    nam_file_names.clear();
    int i = 0;
    if (file->query_exists()) {
        Glib::RefPtr<Gio::FileEnumerator> child_enumeration =
              file->enumerate_children(G_FILE_ATTRIBUTE_STANDARD_NAME
                        "," G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME
                        "," G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE);
        Glib::RefPtr<Gio::FileInfo> file_info;
        nam_file_names.push_back("None");
        while ((file_info = child_enumeration->next_file())) {
            std::string name = file_info->get_name();
            if (name.compare(std::max<int>(0, name.size()-4), 4, ".nam") == 0) {
                nam_file_names.push_back(file_info->get_name());
                i++;
            }
        }
    }
    for (;i<127;i++) nam_file_names.push_back("None");
}

int NeuralAmp::register_par(const ParamReg& reg)
{
    reg.registerFloatVar((idstring + ".input").c_str(),N_("Input"),"S",N_("gain (dB)"),&fVslider0, 0.0, -40.0, 20.0, 0.1, 0);
    reg.registerFloatVar((idstring + ".output").c_str(),N_("Output"),"S",N_("gain (dB)"),&fVslider1, 0.0, -40.0, 20.0, 0.1, 0);
    param.reg_string((idstring + ".loadfile").c_str(), "", &load_file, "*.nam", true)->set_desc(N_("import *.nam file"));
    param.reg_string((idstring + ".loadpath").c_str(), "", &load_path, "", true)->set_desc(N_("load path for *.nam files"));
    reg.registerFloatVar((idstring + ".flist").c_str(),N_("select NAM File"),"S",N_("Select NAM file"),&filelist, 0, 0, 127, 1, 0);

    param[(idstring + ".loadpath").c_str()].signal_changed_string().connect(
        sigc::hide(sigc::mem_fun(this, &NeuralAmp::create_nam_filelist)));
    param[(idstring + ".flist").c_str()].signal_changed_float().connect(
        sigc::hide(sigc::mem_fun(this, &NeuralAmp::load_nam_file)));
    
//    param[(idstring + ".loadfile").c_str()].signal_changed_string().connect(
//        sigc::hide(sigc::mem_fun(this, &NeuralAmp::load_nam_file)));
    return 0;
}

int NeuralAmp::register_params_static(const ParamReg& reg)
{
    return static_cast<NeuralAmp*>(reg.plugin)->register_par(reg);
}

inline int NeuralAmp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade_file((idstring + "_ui.glade").c_str());
        return 0;
    }
    if (form & UI_FORM_STACK) {

        b.openHorizontalhideBox("");
            b.create_master_slider((idstring + ".input").c_str(), "Input");
        b.closeBox();
        b.openHorizontalBox("");

            b.create_mid_rackknob((idstring + ".input").c_str(), "Input");
            b.create_fload_switch(sw_button, nullptr, (idstring + ".loadfile").c_str());
            b.create_mid_rackknob((idstring + ".output").c_str(), "Output");

        b.closeBox();

        return 0;
    }
    return -1;
}

int NeuralAmp::load_ui_f_static(const UiBuilder& b, int form)
{
    return static_cast<NeuralAmp*>(b.plugin)->load_ui_f(b, form);
}

void NeuralAmp::del_instance(PluginDef *p)
{
    delete static_cast<NeuralAmp*>(p);
}

/****************************************************************
 ** class NeuralAmpMulti
 */

NeuralAmpMulti::NeuralAmpMulti(ParamMap& param_, std::string id_, ParallelThread* pro_, sigc::slot<void> sync_)
    : PluginDef(), modela(nullptr), modelb(nullptr), param(param_), pro(pro_), smpa(), smpb(), sync(sync_), idstring(id_), plugin() {
    version = PLUGINDEF_VERSION;
    flags = 0;
    id = idstring.c_str();
    name = N_("Neural Multi Amp Modeler");
    groups = 0;
    description = N_("Neural Amp Modeler by Steven Atkinson"); // description (tooltip)
    category = N_("Neural");       // category
    shortname = "NAM Multi";     // shortname
    mono_audio = compute_static;
    stereo_audio = 0;
    set_samplerate = init_static;
    activate_plugin = 0;
    register_params = register_params_static;
    load_ui = load_ui_f_static;
    clear_state = clear_state_f_static;
    delete_instance = del_instance;
    plugin = this;
    loudnessa = 0.0;
    loudnessb = 0.0;
    need_aresample = 0;
    need_bresample = 0;
    is_inited = false;
    gx_system::atomic_set(&ready, 0);
 }

NeuralAmpMulti::~NeuralAmpMulti() {
    delete modela;
    delete modelb;
}

inline void NeuralAmpMulti::clear_state_f()
{
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec01[l0] = 0.0;
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec1[l0] = 0.0;
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec2[l0] = 0.0;
    for (int l0 = 0; l0 < 16384; l0 = l0 + 1) fDec0[l0] = 0.0;
    for (int l1 = 0; l1 < 2; l1 = l1 + 1) fDel4[l1] = 0.0;
    for (int l2 = 0; l2 < 2; l2 = l2 + 1) fDel0[l2] = 0.0;
    for (int l3 = 0; l3 < 2; l3 = l3 + 1) fDel1[l3] = 0.0;
    for (int l4 = 0; l4 < 2; l4 = l4 + 1) fDel2[l4] = 0.0;
    for (int l5 = 0; l5 < 2; l5 = l5 + 1) fDel3[l5] = 0.0;
    for (int l0 = 0; l0 < 127; l0 = l0 + 1) nam_afile_names.push_back("None");
    for (int l0 = 0; l0 < 127; l0 = l0 + 1) nam_bfile_names.push_back("None");
}

void NeuralAmpMulti::clear_state_f_static(PluginDef *p)
{
    static_cast<NeuralAmpMulti*>(p)->clear_state_f();
}

inline void NeuralAmpMulti::init(unsigned int sample_rate)
{
    fSampleRate = sample_rate;
    clear_state_f();
    is_inited = true;
    buf = nullptr;
    IOTA0 = 0;
    nframes = 1;
    load_nam_afile();
    load_nam_bfile();
    pro->set<1, NeuralAmpMulti, &NeuralAmpMulti::processModelB>(this);
    
}

void NeuralAmpMulti::init_static(unsigned int sample_rate, PluginDef *p)
{
    static_cast<NeuralAmpMulti*>(p)->init(sample_rate);
}

void always_inline NeuralAmpMulti::processDelay(int count, float *buf)
{
    double fSlow0 = 0.0010000000000000009 * double(fVslider02);
    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        double fTemp0 = double(buf[i0]);
        fDec0[IOTA0 & 16383] = fTemp0;
        fDel4[0] = fSlow0 + 0.999 * fDel4[1];
        double fTemp1 = ((fDel0[1] != 0.0) ? (((fDel1[1] > 0.0) & (fDel1[1] < 1.0)) ? fDel0[1] : 0.0) : (((fDel1[1] == 0.0) & (fDel4[0] != fDel2[1])) ? 0.0009765625 : (((fDel1[1] == 1.0) & (fDel4[0] != fDel3[1])) ? -0.0009765625 : 0.0)));
        fDel0[0] = fTemp1;
        fDel1[0] = std::max<double>(0.0, std::min<double>(1.0, fDel1[1] + fTemp1));
        fDel2[0] = (((fDel1[1] >= 1.0) & (fDel3[1] != fDel4[0])) ? fDel4[0] : fDel2[1]);
        fDel3[0] = (((fDel1[1] <= 0.0) & (fDel2[1] != fDel4[0])) ? fDel4[0] : fDel3[1]);
        double fTemp2 = fDec0[(IOTA0 - int(std::min<double>(8192.0, std::max<double>(0.0, fDel2[0])))) & 16383];
        buf[i0] = float(fTemp2 + fDel1[0] * (fDec0[(IOTA0 - int(std::min<double>(8192.0, std::max<double>(0.0, fDel3[0])))) & 16383] - fTemp2));
        IOTA0 = IOTA0 + 1;
        fDel4[1] = fDel4[0];
        fDel0[1] = fDel0[0];
        fDel1[1] = fDel1[0];
        fDel2[1] = fDel2[0];
        fDel3[1] = fDel3[0];
    }
}

void always_inline NeuralAmpMulti::processModelA(int count, float *bufa) {
    if (!modela ) return;
    double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        fRec0[0] = fSlow0 + 0.999 * fRec0[1];
        bufa[i0] = float(double(bufa[i0]) * fRec0[0]);
        fRec0[1] = fRec0[0];
    }

    if (modela && gx_system::atomic_get(ready)) {
        if (need_aresample) {
            int ReCounta = count;
            if (need_aresample == 1) {
                ReCounta = smpa.max_out_count(count);
            } else if (need_aresample == 2) {
                ReCounta = static_cast<int>(ceil((count*static_cast<double>(maSampleRate))/fSampleRate));
            }

            float bufa1[ReCounta];
            memset(bufa1, 0, ReCounta*sizeof(float));

            if (need_aresample == 1) {
                ReCounta = smpa.up(count, bufa, bufa1);
            } else if (need_aresample == 2) {
                smpa.down(bufa, bufa1);
            } else {
                memcpy(bufa1, bufa, ReCounta * sizeof(float));
            }

            modela->process(bufa1, bufa1, ReCounta);

            if (need_aresample == 1) {
                smpa.down(bufa1, bufa);
            } else if (need_aresample == 2) {
                smpa.up(ReCounta, bufa1, bufa);
            }
        } else {
            modela->process(bufa, bufa, count);
        }
    }
}

void always_inline NeuralAmpMulti::processModelB() {
    if (!modelb) return;
    double fSlow01 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider01));
    for (int i0 = 0; i0 < nframes; i0 = i0 + 1) {
        fRec01[0] = fSlow01 + 0.999 * fRec01[1];
        buf[i0] = float(double(buf[i0]) * fRec01[0]);
        fRec01[1] = fRec01[0];
    }

    if (modelb && gx_system::atomic_get(ready)) {
        if (need_bresample) {
            int ReCountb = nframes;
            if (need_bresample == 1) {
                ReCountb = smpb.max_out_count(nframes);
            } else if (need_bresample == 2) {
                ReCountb = static_cast<int>(ceil((nframes*static_cast<double>(mbSampleRate))/fSampleRate));
            }

            float buf1[ReCountb];
            memset(buf1, 0, ReCountb*sizeof(float));

            if (need_bresample == 1) {
                ReCountb = smpb.up(nframes, buf, buf1);
            } else if (need_bresample == 2) {
                smpb.down(buf, buf1);
            } else {
                memcpy(buf1, buf, ReCountb * sizeof(float));
            }

            modelb->process(buf1, buf1, ReCountb);

            if (need_bresample == 1) {
                smpb.down(buf1, buf);
            } else if (need_bresample == 2) {
                smpb.up(ReCountb, buf1, buf);
            }
        } else {
            modelb->process(buf, buf, nframes);
        }
    }
}


void always_inline NeuralAmpMulti::compute(int count, float *input0, float *output0)
{
    if (output0 != input0)
        memcpy(output0, input0, count*sizeof(float));
    if (!modela && !modelb) return;
    double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider1));
    double fSlow2 = 0.0010000000000000009 * double(fVslider2);

    float bufa[count];
    memcpy(bufa, output0, count*sizeof(float));
    float bufb[count];
    memcpy(bufb, output0, count*sizeof(float));

    if (int(fVslider02) > 0) processDelay(count, bufb);
    else processDelay(count, bufa);

    nframes = count;
    buf = bufb;

    if (pro->getProcess()) {
        pro->setProcessor(1);
        pro->runProcess();
    } else {
        processModelB();
    }

    processModelA(count, bufa);

    pro->processWait();

    if (modela && modelb && gx_system::atomic_get(ready)) {
        for (int i0 = 0; i0 < count; i0 = i0 + 1) {
            fRec2[0] = fSlow2 + 0.999 * fRec2[1];
            output0[i0] = bufa[i0] * (1.0 - fRec2[0]) + bufb[i0] * fRec2[0];
            fRec2[1] = fRec2[0];
        }
    } else if (modela && gx_system::atomic_get(ready)) {
        memcpy(output0, bufa, count*sizeof(float));
    } else if (modelb && gx_system::atomic_get(ready)) {
        memcpy(output0, bufb, count*sizeof(float));
    }
    
    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        fRec1[0] = fSlow1 + 0.999 * fRec1[1];
        output0[i0] = float(double(output0[i0]) * fRec1[0]);
        fRec1[1] = fRec1[0];
    }
}

void NeuralAmpMulti::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
    static_cast<NeuralAmpMulti*>(p)->compute(count, input0, output0);
}

// non rt callback
void NeuralAmpMulti::load_nam_afile() {
    if (!load_afile.empty() && is_inited) {
        if (nam_afile_names.size() < 1 || afilelist < 1.0) return;
        gx_system::atomic_set(&ready, 0);
        sync();
        delete modela;
        modela = nullptr;
        need_aresample = 0;
        clear_state_f();
        int32_t warmUpSize = 4096;
        try {
            load_afile = load_apath + "/" + nam_afile_names[afilelist];
            modela = nam::get_dsp(std::string(load_afile)).release();
        } catch (const std::exception&) {
            gx_print_info("Neural Multi Amp Modeler", "fail to load " + load_afile);
            load_afile = "None";
        }
        
        if (modela) {
            if (modela->HasLoudness()) loudnessa = modela->GetLoudness();
            maSampleRate = static_cast<int>(modela->GetExpectedSampleRate());
            //model->SetLoudness(-15.0);
            if (maSampleRate <= 0) maSampleRate = 48000;
            if (maSampleRate > fSampleRate) {
                smpa.setup(fSampleRate, maSampleRate);
                need_aresample = 1;
            } else if (maSampleRate < fSampleRate) {
                smpa.setup(maSampleRate, fSampleRate);
                need_aresample = 2;
            } 
            float* buffer = new float[warmUpSize];
            memset(buffer, 0, warmUpSize * sizeof(float));

            modela->process(buffer, buffer, warmUpSize);

            delete[] buffer;
            //fprintf(stderr, "sample rate = %i file = %i l = %f\n",fSampleRate, maSampleRate, loudness);
            //fprintf(stderr, "%s\n", load_file.c_str());
        } 
        gx_system::atomic_set(&ready, 1);
    }
}

// non rt callback
void NeuralAmpMulti::load_nam_bfile() {
    if (!load_bfile.empty() && is_inited) {
        if (nam_bfile_names.size() < 1 || bfilelist < 1.0) return;
        gx_system::atomic_set(&ready, 0);
        sync();
        delete modelb;
        modelb = nullptr;
        need_bresample = 0;
        clear_state_f();
        int32_t warmUpSize = 4096;
        try {
            load_bfile = load_bpath + "/" + nam_bfile_names[bfilelist];
            modelb = nam::get_dsp(std::string(load_bfile)).release();
        } catch (const std::exception&) {
            gx_print_info("Neural Multi Amp Modeler", "fail to load " + load_bfile);
            load_bfile = "None";
        }
        
        if (modelb) {
            if (modelb->HasLoudness()) loudnessb = modelb->GetLoudness();
            mbSampleRate = static_cast<int>(modelb->GetExpectedSampleRate());
            //model->SetLoudness(-15.0);
            if (mbSampleRate <= 0) mbSampleRate = 48000;
            if (mbSampleRate > fSampleRate) {
                smpb.setup(fSampleRate, mbSampleRate);
                need_bresample = 1;
            } else if (mbSampleRate < fSampleRate) {
                smpb.setup(maSampleRate, fSampleRate);
                need_bresample = 2;
            } 
            float* buffer = new float[warmUpSize];
            memset(buffer, 0, warmUpSize * sizeof(float));

            modelb->process(buffer, buffer, warmUpSize);

            delete[] buffer;
            //fprintf(stderr, "sample rate = %i file = %i l = %f\n",fSampleRate, mbSampleRate, loudness);
            //fprintf(stderr, "%s\n", load_file.c_str());
        } 
        gx_system::atomic_set(&ready, 1);
    }
}

// non rt callback
void NeuralAmpMulti::create_nam_afilelist() {
    if (load_apath.empty()) return;
    Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(load_apath);
    nam_afile_names.clear();
    int i = 0;
    if (file->query_exists()) {
        Glib::RefPtr<Gio::FileEnumerator> child_enumeration =
              file->enumerate_children(G_FILE_ATTRIBUTE_STANDARD_NAME
                        "," G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME
                        "," G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE);
        Glib::RefPtr<Gio::FileInfo> file_info;
        nam_afile_names.push_back("None");
        while ((file_info = child_enumeration->next_file())) {
            std::string name = file_info->get_name();
            if (name.compare(std::max<int>(0, name.size()-4), 4, ".nam") == 0) {
                nam_afile_names.push_back(file_info->get_name());
                i++;
            }
        }
    }
    for (;i<127;i++) nam_afile_names.push_back("None");
}

// non rt callback
void NeuralAmpMulti::create_nam_bfilelist() {
    if (load_bpath.empty()) return;
    Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(load_bpath);
    nam_bfile_names.clear();
    int i = 0;
    if (file->query_exists()) {
        Glib::RefPtr<Gio::FileEnumerator> child_enumeration =
              file->enumerate_children(G_FILE_ATTRIBUTE_STANDARD_NAME
                        "," G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME
                        "," G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE);
        Glib::RefPtr<Gio::FileInfo> file_info;
        nam_bfile_names.push_back("None");
        while ((file_info = child_enumeration->next_file())) {
            std::string name = file_info->get_name();
            if (name.compare(std::max<int>(0, name.size()-4), 4, ".nam") == 0) {
                nam_bfile_names.push_back(file_info->get_name());
                i++;
            }
        }
    }
    for (;i<127;i++) nam_bfile_names.push_back("None");
}

int NeuralAmpMulti::register_par(const ParamReg& reg)
{
    reg.registerFloatVar((idstring + ".input").c_str(),N_("Input A"),"S",N_("gain (dB)"),&fVslider0, 0.0, -20.0, 20.0, 0.1, 0);
    reg.registerFloatVar((idstring + ".inputb").c_str(),N_("Input B"),"S",N_("gain (dB)"),&fVslider01, 0.0, -20.0, 20.0, 0.1, 0);
    reg.registerFloatVar((idstring + ".cdelay").c_str(),N_("Delta Delay"),"S",N_("Delay A/B"),&fVslider02, 0.0, -4096.0, 4096.0, 1.0, 0);
    reg.registerFloatVar((idstring + ".output").c_str(),N_("Output"),"S",N_("gain (dB)"),&fVslider1, 0.0, -20.0, 20.0, 0.1, 0);
    reg.registerFloatVar((idstring + ".mix").c_str(),N_("Mix"),"S",N_("mix models"),&fVslider2, 0.5, 0.0, 1.0, 0.01, 0);
    param.reg_string((idstring + ".loadafile").c_str(), "", &load_afile, "*.nam", true)->set_desc(N_("import *.nam file"));
    param.reg_string((idstring + ".loadbfile").c_str(), "", &load_bfile, "*.nam", true)->set_desc(N_("import *.nam file"));
    param.reg_string((idstring + ".loadapath").c_str(), "", &load_apath, "", true)->set_desc(N_("load path for A *.nam files"));
    param.reg_string((idstring + ".loadbpath").c_str(), "", &load_bpath, "", true)->set_desc(N_("load path for B *.nam files"));
    reg.registerFloatVar((idstring + ".falist").c_str(),N_("select NAM File"),"S",N_("Select NAM file"),&afilelist, 0, 0, 127, 1, 0);
    reg.registerFloatVar((idstring + ".fblist").c_str(),N_("select NAM File"),"S",N_("Select NAM file"),&bfilelist, 0, 0, 127, 1, 0);

    param[(idstring + ".loadapath").c_str()].signal_changed_string().connect(
        sigc::hide(sigc::mem_fun(this, &NeuralAmpMulti::create_nam_afilelist)));
    param[(idstring + ".loadbpath").c_str()].signal_changed_string().connect(
        sigc::hide(sigc::mem_fun(this, &NeuralAmpMulti::create_nam_bfilelist)));
    param[(idstring + ".falist").c_str()].signal_changed_float().connect(
        sigc::hide(sigc::mem_fun(this, &NeuralAmpMulti::load_nam_afile)));
    param[(idstring + ".fblist").c_str()].signal_changed_float().connect(
        sigc::hide(sigc::mem_fun(this, &NeuralAmpMulti::load_nam_bfile)));

//    param[(idstring + ".loadafile").c_str()].signal_changed_string().connect(
//        sigc::hide(sigc::mem_fun(this, &NeuralAmpMulti::load_nam_afile)));
//    param[(idstring + ".loadbfile").c_str()].signal_changed_string().connect(
//        sigc::hide(sigc::mem_fun(this, &NeuralAmpMulti::load_nam_bfile)));
    return 0;
}

int NeuralAmpMulti::register_params_static(const ParamReg& reg)
{
    return static_cast<NeuralAmpMulti*>(reg.plugin)->register_par(reg);
}

inline int NeuralAmpMulti::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade_file((idstring + "_ui.glade").c_str());
        return 0;
    }
    if (form & UI_FORM_STACK) {

        b.openHorizontalhideBox("");
            b.create_master_slider((idstring + "output").c_str(), "output");
        b.closeBox();
        b.openHorizontalBox("");
            b.openVerticalBox("");
            b.create_mid_rackknob((idstring + ".input").c_str(), "Input A");
            b.create_mid_rackknob((idstring + ".inputb").c_str(), "Input B");
            b.closeBox();
            b.openVerticalBox("");
                b.create_fload_switch(sw_button, nullptr, (idstring + ".loadafile").c_str());
                b.create_fload_switch(sw_button, nullptr, (idstring + ".loadbfile").c_str());
            b.closeBox();
            b.create_mid_rackknob((idstring + ".output").c_str(), "Output");
            b.create_mid_rackknob((idstring + ".mix").c_str(), "Mix");

        b.closeBox();

        return 0;
    }
    return -1;
}

int NeuralAmpMulti::load_ui_f_static(const UiBuilder& b, int form)
{
    return static_cast<NeuralAmpMulti*>(b.plugin)->load_ui_f(b, form);
}

void NeuralAmpMulti::del_instance(PluginDef *p)
{
    delete static_cast<NeuralAmpMulti*>(p);
}

/****************************************************************
 ** class RtNeural
 */

RtNeural::RtNeural(ParamMap& param_, std::string id_, sigc::slot<void> sync_)
    : PluginDef(), model(nullptr), param(param_), smp(), sync(sync_), idstring(id_), plugin() {
    version = PLUGINDEF_VERSION;
    flags = 0;
    id = idstring.c_str();
    name = N_("RTNeural Network Engine");
    groups = 0;
    description = N_("Neural network engine written by Jatin Chowdhury"); // description (tooltip)
    category = N_("Neural");       // category
    shortname = "RTNeural";     // shortname
    mono_audio = compute_static;
    stereo_audio = 0;
    set_samplerate = init_static;
    activate_plugin = 0;
    register_params = register_params_static;
    load_ui = load_ui_f_static;
    clear_state = clear_state_f_static;
    delete_instance = del_instance;
    plugin = this;
    need_resample = 0;
    is_inited = false;
    gx_system::atomic_set(&ready, 0);
 }

RtNeural::~RtNeural() {
    delete model;
}

inline void RtNeural::clear_state_f()
{
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec1[l0] = 0.0;
    for (int l0 = 0; l0 < 127; l0 = l0 + 1) rtneural_file_names.push_back("None");
}

void RtNeural::clear_state_f_static(PluginDef *p)
{
    static_cast<RtNeural*>(p)->clear_state_f();
}

inline void RtNeural::init(unsigned int sample_rate)
{
    fSampleRate = sample_rate;
    clear_state_f();
    is_inited = true;
    load_json_file();
}

void RtNeural::init_static(unsigned int sample_rate, PluginDef *p)
{
    static_cast<RtNeural*>(p)->init(sample_rate);
}

void always_inline RtNeural::compute(int count, float *input0, float *output0)
{
    if (output0 != input0)
        memcpy(output0, input0, count*sizeof(float));
    if (!model) return;
    double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));
    double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider1));
    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        fRec0[0] = fSlow0 + 0.999 * fRec0[1];
        output0[i0] = float(double(output0[i0]) * fRec0[0]);
        fRec0[1] = fRec0[0];
    }
    if (model && gx_system::atomic_get(ready)) {
        if (need_resample) {
            int ReCount = count;
            if (need_resample == 1) {
                ReCount = smp.max_out_count(count);
            } else if (need_resample == 2) {
                ReCount = static_cast<int>(ceil((count*static_cast<double>(mSampleRate))/fSampleRate));
            }

            float buf[ReCount];
            memset(buf, 0, ReCount*sizeof(float));

            if (need_resample == 1) {
                ReCount = smp.up(count, output0, buf);
            } else if (need_resample == 2) {
                smp.down(output0, buf);
            } else {
                memcpy(buf, output0, ReCount * sizeof(float));
            }

            for (int i0 = 0; i0 < ReCount; i0 = i0 + 1) {
                 buf[i0] = model->forward (&buf[i0]);
            }

            if (need_resample == 1) {
                smp.down(buf, output0);
            } else if (need_resample == 2) {
                smp.up(ReCount, buf, output0);
            }
        } else {
            for (int i0 = 0; i0 < count; i0 = i0 + 1) {
                 output0[i0] = model->forward (&output0[i0]);
            }
        }
    }
    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        fRec1[0] = fSlow1 + 0.999 * fRec1[1];
        output0[i0] = float(double(output0[i0]) * fRec1[0]);
        fRec1[1] = fRec1[0];
    }
}

void RtNeural::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
    static_cast<RtNeural*>(p)->compute(count, input0, output0);
}

void RtNeural::get_samplerate(std::string config_file) {
    std::ifstream infile(config_file);
    infile.imbue(std::locale::classic());
    std::string line;
    std::string key;
    std::string value;
    if (infile.is_open()) {
        while (std::getline(infile, line)) {
            std::istringstream buf(line);
            buf >> key;
            buf >> value;
            if (key.compare("\"samplerate\":") == 0) {
                value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());
                mSampleRate = std::stoi(value);
                break;
            }
            key.clear();
            value.clear();
        }
        infile.close();
    }
}

// non rt callback
void RtNeural::load_json_file() {
    if (!load_file.empty() && is_inited) {
        if (rtneural_file_names.size() < 1 || filelist < 1.0) return;
        gx_system::atomic_set(&ready, 0);
        sync();
        delete model;
        model = nullptr;
        mSampleRate = 0;
        need_resample = 0;
        clear_state_f();
        try {
            load_file = load_path + "/" + rtneural_file_names[filelist];
            get_samplerate(std::string(load_file));
            std::ifstream jsonStream(std::string(load_file), std::ifstream::binary);
            model = RTNeural::json_parser::parseJson<float>(jsonStream).release();
        } catch (const std::exception&) {
            gx_print_info("RTNeural Amp Modeler", "fail to load " + load_file);
            load_file = "None";
        }
        
        if (model) {
            model->reset();
            if (mSampleRate <= 0) mSampleRate = 48000;
            if (mSampleRate > fSampleRate) {
                smp.setup(fSampleRate, mSampleRate);
                need_resample = 1;
            } else if (mSampleRate < fSampleRate) {
                smp.setup(mSampleRate, fSampleRate);
                need_resample = 2;
            } 
        } 
        gx_system::atomic_set(&ready, 1);
    }
}

// non rt callback
void RtNeural::create_rtneural_filelist() {
    if (load_path.empty()) return;
    Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(load_path);
    rtneural_file_names.clear();
    int i = 0;
    if (file->query_exists()) {
        Glib::RefPtr<Gio::FileEnumerator> child_enumeration =
              file->enumerate_children(G_FILE_ATTRIBUTE_STANDARD_NAME
                        "," G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME
                        "," G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE);
        Glib::RefPtr<Gio::FileInfo> file_info;
        rtneural_file_names.push_back("None");
        while ((file_info = child_enumeration->next_file())) {
            std::string name = file_info->get_name();
            if ((name.compare(std::max<int>(0, name.size()-4), 4, "idax") == 0) ||
                (name.compare(std::max<int>(0, name.size()-4), 4, "json") == 0)) {
                rtneural_file_names.push_back(file_info->get_name());
                i++;
            }
        }
    }
    for (;i<127;i++) rtneural_file_names.push_back("None");
}

int RtNeural::register_par(const ParamReg& reg)
{
    reg.registerFloatVar((idstring + ".input").c_str(),N_("Input"),"S",N_("gain (dB)"),&fVslider0, 0.0, -20.0, 20.0, 0.1, 0);
    reg.registerFloatVar((idstring + ".output").c_str(),N_("Output"),"S",N_("gain (dB)"),&fVslider1, 0.0, -20.0, 20.0, 0.1, 0);
    param.reg_string((idstring + ".loadfile").c_str(), "", &load_file, "*.json", true)->set_desc(N_("import *.json file"));
    param.reg_string((idstring + ".loadpath").c_str(), "", &load_path, "", true)->set_desc(N_("load path for *.json files"));
    reg.registerFloatVar((idstring + ".flist").c_str(),N_("select json/aidax File"),"SA",N_("Select json/aidax file"),&filelist, 0, 0, 127, 1, 0);

    param[(idstring + ".loadpath").c_str()].signal_changed_string().connect(
        sigc::hide(sigc::mem_fun(this, &RtNeural::create_rtneural_filelist)));
    param[(idstring + ".flist").c_str()].signal_changed_float().connect(
        sigc::hide(sigc::mem_fun(this, &RtNeural::load_json_file)));

//    param[(idstring + ".loadfile").c_str()].signal_changed_string().connect(
//        sigc::hide(sigc::mem_fun(this, &RtNeural::load_json_file)));
    return 0;
}

int RtNeural::register_params_static(const ParamReg& reg)
{
    return static_cast<RtNeural*>(reg.plugin)->register_par(reg);
}

inline int RtNeural::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade_file((idstring + "_ui.glade").c_str());
        return 0;
    }
    if (form & UI_FORM_STACK) {

        b.openHorizontalhideBox("");
            b.create_master_slider((idstring + "input").c_str(), "Input");
        b.closeBox();
        b.openHorizontalBox("");

            b.create_mid_rackknob((idstring + "input").c_str(), "Input");
            b.create_fload_switch(sw_button, nullptr, (idstring + "loadfile").c_str());
            b.create_mid_rackknob((idstring + "output").c_str(), "Output");

        b.closeBox();

        return 0;
    }
    return -1;
}

int RtNeural::load_ui_f_static(const UiBuilder& b, int form)
{
    return static_cast<RtNeural*>(b.plugin)->load_ui_f(b, form);
}

void RtNeural::del_instance(PluginDef *p)
{
    delete static_cast<RtNeural*>(p);
}

/****************************************************************
 ** class RtNeuralMulti
 */

RtNeuralMulti::RtNeuralMulti(ParamMap& param_, std::string id_, ParallelThread *pro_, sigc::slot<void> sync_)
    : PluginDef(), modela(nullptr), modelb(nullptr), param(param_), pro(pro_), smpa(), smpb(), sync(sync_), idstring(id_), plugin() {
    version = PLUGINDEF_VERSION;
    flags = 0;
    id = idstring.c_str();
    name = N_("RTNeural Multi Engine");
    groups = 0;
    description = N_("Neural network engine written by Jatin Chowdhury"); // description (tooltip)
    category = N_("Neural");       // category
    shortname = "RTNeuralMulti";     // shortname
    mono_audio = compute_static;
    stereo_audio = 0;
    set_samplerate = init_static;
    activate_plugin = 0;
    register_params = register_params_static;
    load_ui = load_ui_f_static;
    clear_state = clear_state_f_static;
    delete_instance = del_instance;
    plugin = this;
    need_aresample = 0;
    need_bresample = 0;
    is_inited = false;
    gx_system::atomic_set(&ready, 0);
 }

RtNeuralMulti::~RtNeuralMulti() {
    delete modela;
    delete modelb;
}

inline void RtNeuralMulti::clear_state_f()
{
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec01[l0] = 0.0;
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec1[l0] = 0.0;
    for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec2[l0] = 0.0;
    for (int l0 = 0; l0 < 16384; l0 = l0 + 1) fDec0[l0] = 0.0;
    for (int l1 = 0; l1 < 2; l1 = l1 + 1) fDel4[l1] = 0.0;
    for (int l2 = 0; l2 < 2; l2 = l2 + 1) fDel0[l2] = 0.0;
    for (int l3 = 0; l3 < 2; l3 = l3 + 1) fDel1[l3] = 0.0;
    for (int l4 = 0; l4 < 2; l4 = l4 + 1) fDel2[l4] = 0.0;
    for (int l5 = 0; l5 < 2; l5 = l5 + 1) fDel3[l5] = 0.0;
    for (int l0 = 0; l0 < 127; l0 = l0 + 1) rtneural_afile_names.push_back("None");
    for (int l0 = 0; l0 < 127; l0 = l0 + 1) rtneural_bfile_names.push_back("None");
}

void RtNeuralMulti::clear_state_f_static(PluginDef *p)
{
    static_cast<RtNeuralMulti*>(p)->clear_state_f();
}

inline void RtNeuralMulti::init(unsigned int sample_rate)
{
    fSampleRate = sample_rate;
    clear_state_f();
    IOTA0 = 0;
    is_inited = true;
    buf = nullptr;
    nframes = 1;
    load_json_afile();
    load_json_bfile();
    pro->set<0, RtNeuralMulti, &RtNeuralMulti::processModelB>(this);
}

void RtNeuralMulti::init_static(unsigned int sample_rate, PluginDef *p)
{
    static_cast<RtNeuralMulti*>(p)->init(sample_rate);
}

void always_inline RtNeuralMulti::processDelay(int count, float *buf)
{
	double fSlow0 = 0.0010000000000000009 * double(fVslider02);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(buf[i0]);
		fDec0[IOTA0 & 16383] = fTemp0;
		fDel4[0] = fSlow0 + 0.999 * fDel4[1];
		double fTemp1 = ((fDel0[1] != 0.0) ? (((fDel1[1] > 0.0) & (fDel1[1] < 1.0)) ? fDel0[1] : 0.0) : (((fDel1[1] == 0.0) & (fDel4[0] != fDel2[1])) ? 0.0009765625 : (((fDel1[1] == 1.0) & (fDel4[0] != fDel3[1])) ? -0.0009765625 : 0.0)));
		fDel0[0] = fTemp1;
		fDel1[0] = std::max<double>(0.0, std::min<double>(1.0, fDel1[1] + fTemp1));
		fDel2[0] = (((fDel1[1] >= 1.0) & (fDel3[1] != fDel4[0])) ? fDel4[0] : fDel2[1]);
		fDel3[0] = (((fDel1[1] <= 0.0) & (fDel2[1] != fDel4[0])) ? fDel4[0] : fDel3[1]);
		double fTemp2 = fDec0[(IOTA0 - int(std::min<double>(8192.0, std::max<double>(0.0, fDel2[0])))) & 16383];
		buf[i0] = float(fTemp2 + fDel1[0] * (fDec0[(IOTA0 - int(std::min<double>(8192.0, std::max<double>(0.0, fDel3[0])))) & 16383] - fTemp2));
		IOTA0 = IOTA0 + 1;
		fDel4[1] = fDel4[0];
		fDel0[1] = fDel0[0];
		fDel1[1] = fDel1[0];
		fDel2[1] = fDel2[0];
		fDel3[1] = fDel3[0];
	}
}

void always_inline RtNeuralMulti::processModelA(int count, float *bufa) {
    if (!modela) return;
    double fSlow0 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider0));

    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        fRec0[0] = fSlow0 + 0.999 * fRec0[1];
        bufa[i0] = float(double(bufa[i0]) * fRec0[0]);
        fRec0[1] = fRec0[0];
    }

    if (modela && gx_system::atomic_get(ready)) {
        if (need_aresample ) {
            int ReCounta = count;

            if (need_aresample == 1) {
                ReCounta = smpa.max_out_count(count);
            } else if (need_aresample == 2) {
                ReCounta = static_cast<int>(ceil((count*static_cast<double>(maSampleRate))/fSampleRate));
            }

            float bufa1[ReCounta];
            memset(bufa1, 0, ReCounta*sizeof(float));

            if (need_aresample == 1) {
                ReCounta = smpa.up(count, bufa, bufa1);
            } else if (need_aresample == 2) {
                smpa.down(bufa, bufa1);
            } else {
                memcpy(bufa1, bufa, ReCounta * sizeof(float));
            }

            for (int i0 = 0; i0 < ReCounta; i0 = i0 + 1) {
                 bufa1[i0] = modela->forward (&bufa1[i0]);
            }

            if (need_aresample == 1) {
                smpa.down(bufa1, bufa);
            } else if (need_aresample == 2) {
                smpa.up(ReCounta, bufa1, bufa);
            }
        } else {
            for (int i0 = 0; i0 < count; i0 = i0 + 1) {
                 bufa[i0] = modela->forward (&bufa[i0]);
            }
        }
    }
}

void always_inline RtNeuralMulti::processModelB() {
    if (!modelb) return;
    double fSlow01 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider01));

    for (int i0 = 0; i0 < nframes; i0 = i0 + 1) {
        fRec01[0] = fSlow01 + 0.999 * fRec01[1];
        buf[i0] = float(double(buf[i0]) * fRec01[0]);
        fRec01[1] = fRec01[0];
    }
    if (modelb && gx_system::atomic_get(ready)) {
        if (need_bresample) {
            int ReCountb = nframes;

            if (need_bresample == 1) {
                ReCountb = smpb.max_out_count(nframes);
            } else if (need_bresample == 2) {
                ReCountb = static_cast<int>(ceil((nframes*static_cast<double>(mbSampleRate))/fSampleRate));
            }

            float buf1[ReCountb];
            memset(buf1, 0, ReCountb*sizeof(float));

            if (need_bresample == 1) {
                ReCountb = smpb.up(nframes, buf, buf1);
            } else if (need_bresample == 2) {
                smpb.down(buf, buf1);
            } else {
                memcpy(buf1, buf, ReCountb * sizeof(float));
            }

            for (int i0 = 0; i0 < ReCountb; i0 = i0 + 1) {
                 buf1[i0] = modelb->forward (&buf1[i0]);
            }

            if (need_bresample == 1) {
                smpb.down(buf1, buf);
            } else if (need_bresample == 2) {
                smpb.up(ReCountb, buf1, buf);
            }
        } else {
            for (int i0 = 0; i0 < nframes; i0 = i0 + 1) {
                 buf[i0] = modelb->forward (&buf[i0]);
            }
        }
    }
}

void always_inline RtNeuralMulti::compute(int count, float *input0, float *output0)
{
    if (output0 != input0)
        memcpy(output0, input0, count*sizeof(float));
    if (!modela || !modelb) return;
    double fSlow1 = 0.0010000000000000009 * std::pow(1e+01, 0.05 * double(fVslider1));
    double fSlow2 = 0.0010000000000000009 * double(fVslider2);

    float bufa[count];
    memcpy(bufa, output0, count*sizeof(float));
    float bufb[count];
    memcpy(bufb, output0, count*sizeof(float));

    if (int(fVslider02) > 0) processDelay(count, bufb);
    else processDelay(count, bufa);

    nframes = count;
    buf = bufb;

    if (pro->getProcess()) {
        pro->setProcessor(0);
        pro->runProcess();
    } else {
        processModelB();
    }

    processModelA(count, bufa);

    pro->processWait();

    if (modela && modelb && gx_system::atomic_get(ready)) {
        for (int i0 = 0; i0 < count; i0 = i0 + 1) {
            fRec2[0] = fSlow2 + 0.999 * fRec2[1];
            output0[i0] = bufa[i0] * (1.0 - fRec2[0]) + bufb[i0] * fRec2[0];
            fRec2[1] = fRec2[0];
        }
    } else if (modela && gx_system::atomic_get(ready)) {
        memcpy(output0, bufa, count*sizeof(float));
    } else if (modelb && gx_system::atomic_get(ready)) {
        memcpy(output0, bufb, count*sizeof(float));
    }
    
    for (int i0 = 0; i0 < count; i0 = i0 + 1) {
        fRec1[0] = fSlow1 + 0.999 * fRec1[1];
        output0[i0] = float(double(output0[i0]) * fRec1[0]);
        fRec1[1] = fRec1[0];
    }
}

void RtNeuralMulti::compute_static(int count, float *input0, float *output0, PluginDef *p)
{
    static_cast<RtNeuralMulti*>(p)->compute(count, input0, output0);
}

void RtNeuralMulti::get_samplerate(std::string config_file, int *mSampleRate) {
    std::ifstream infile(config_file);
    infile.imbue(std::locale::classic());
    std::string line;
    std::string key;
    std::string value;
    if (infile.is_open()) {
        while (std::getline(infile, line)) {
            std::istringstream buf(line);
            buf >> key;
            buf >> value;
            if (key.compare("\"samplerate\":") == 0) {
                value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());
                (*mSampleRate) = std::stoi(value);
                break;
            }
            key.clear();
            value.clear();
        }
        infile.close();
    }
}

// non rt callback
void RtNeuralMulti::load_json_afile() {
    if (!load_afile.empty() && is_inited) {
        if (rtneural_afile_names.size() < 1 || afilelist < 1.0) return;
        gx_system::atomic_set(&ready, 0);
        sync();
        delete modela;
        modela = nullptr;
        maSampleRate = 0;
        need_aresample = 0;
        clear_state_f();
        try {
            load_afile = load_apath + "/" + rtneural_afile_names[afilelist];
            get_samplerate(std::string(load_afile), &maSampleRate);
            std::ifstream jsonStream(std::string(load_afile), std::ifstream::binary);
            modela = RTNeural::json_parser::parseJson<float>(jsonStream).release();
        } catch (const std::exception&) {
            gx_print_info("RTNeural Multi Amp Modeler", "fail to load " + load_afile);
            load_afile = "None";
        }
        
        if (modela) {
            modela->reset();
            if (maSampleRate <= 0) maSampleRate = 48000;
            if (maSampleRate > fSampleRate) {
                smpa.setup(fSampleRate, maSampleRate);
                need_aresample = 1;
            } else if (maSampleRate < fSampleRate) {
                smpa.setup(maSampleRate, fSampleRate);
                need_aresample = 2;
            } 
             //fprintf(stderr, "A: %s\n", load_afile.c_str());
       } 
        gx_system::atomic_set(&ready, 1);
    }
}

// non rt callback
void RtNeuralMulti::load_json_bfile() {
    if (!load_bfile.empty() && is_inited) {
        if (rtneural_bfile_names.size() < 1 || bfilelist < 1.0) return;
        gx_system::atomic_set(&ready, 0);
        sync();
        delete modelb;
        modelb = nullptr;
        mbSampleRate = 0;
        need_bresample = 0;
        clear_state_f();
        try {
            load_bfile = load_apath + "/" + rtneural_bfile_names[bfilelist];
            get_samplerate(std::string(load_bfile), &mbSampleRate);
            std::ifstream jsonStream(std::string(load_bfile), std::ifstream::binary);
            modelb = RTNeural::json_parser::parseJson<float>(jsonStream).release();
        } catch (const std::exception&) {
            gx_print_info("RTNeural Amp Modeler", "fail to load " + load_bfile);
            load_bfile = "None";
        }
        
        if (modelb) {
            modelb->reset();
            if (mbSampleRate <= 0) mbSampleRate = 48000;
            if (mbSampleRate > fSampleRate) {
                smpb.setup(fSampleRate, mbSampleRate);
                need_bresample = 1;
            } else if (mbSampleRate < fSampleRate) {
                smpb.setup(mbSampleRate, fSampleRate);
                need_bresample = 2;
            } 
             //fprintf(stderr, "B: %s\n", load_bfile.c_str());
        } 
        gx_system::atomic_set(&ready, 1);
    }
}

// non rt callback
void RtNeuralMulti::create_rtneural_afilelist() {
    if (load_apath.empty()) return;
    Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(load_apath);
    rtneural_afile_names.clear();
    int i = 0;
    if (file->query_exists()) {
        Glib::RefPtr<Gio::FileEnumerator> child_enumeration =
              file->enumerate_children(G_FILE_ATTRIBUTE_STANDARD_NAME
                        "," G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME
                        "," G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE);
        Glib::RefPtr<Gio::FileInfo> file_info;
        rtneural_afile_names.push_back("None");
        while ((file_info = child_enumeration->next_file())) {
            std::string name = file_info->get_name();
            if ((name.compare(std::max<int>(0, name.size()-4), 4, "idax") == 0) ||
                (name.compare(std::max<int>(0, name.size()-4), 4, "json") == 0)) {
                rtneural_afile_names.push_back(file_info->get_name());
                i++;
            }
        }
    }
    for (;i<127;i++) rtneural_afile_names.push_back("None");
}

// non rt callback
void RtNeuralMulti::create_rtneural_bfilelist() {
    if (load_bpath.empty()) return;
    Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(load_bpath);
    rtneural_bfile_names.clear();
    int i = 0;
    if (file->query_exists()) {
        Glib::RefPtr<Gio::FileEnumerator> child_enumeration =
              file->enumerate_children(G_FILE_ATTRIBUTE_STANDARD_NAME
                        "," G_FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME
                        "," G_FILE_ATTRIBUTE_STANDARD_FAST_CONTENT_TYPE);
        Glib::RefPtr<Gio::FileInfo> file_info;
        rtneural_bfile_names.push_back("None");
        while ((file_info = child_enumeration->next_file())) {
            std::string name = file_info->get_name();
            if ((name.compare(std::max<int>(0, name.size()-4), 4, "idax") == 0) ||
                (name.compare(std::max<int>(0, name.size()-4), 4, "json") == 0)) {
                rtneural_bfile_names.push_back(file_info->get_name());
                i++;
            }
        }
    }
    for (;i<127;i++) rtneural_bfile_names.push_back("None");
}

int RtNeuralMulti::register_par(const ParamReg& reg)
{
    reg.registerFloatVar((idstring + ".input").c_str(),N_("Input A"),"S",N_("gain (dB)"),&fVslider0, 0.0, -20.0, 20.0, 0.1, 0);
    reg.registerFloatVar((idstring + ".inputb").c_str(),N_("Input B"),"S",N_("gain (dB)"),&fVslider01, 0.0, -20.0, 20.0, 0.1, 0);
    reg.registerFloatVar((idstring + ".cdelay").c_str(),N_("Delta Delay"),"S",N_("Delay A/B"),&fVslider02, 0.0, -4096.0, 4096.0, 1.0, 0);
    reg.registerFloatVar((idstring + ".output").c_str(),N_("Output"),"S",N_("gain (dB)"),&fVslider1, 0.0, -20.0, 20.0, 0.1, 0);
    reg.registerFloatVar((idstring + ".mix").c_str(),N_("Mix"),"S",N_("mix models"),&fVslider2, 0.5, 0.0, 1.0, 0.01, 0);
    param.reg_string((idstring + ".loadafile").c_str(), "", &load_afile, "*.json", true)->set_desc(N_("import *.json file"));
    param.reg_string((idstring + ".loadbfile").c_str(), "", &load_bfile, "*.json", true)->set_desc(N_("import *.json file"));
    param.reg_string((idstring + ".loadapath").c_str(), "", &load_apath, "", true)->set_desc(N_("load path for A *.json files"));
    param.reg_string((idstring + ".loadbpath").c_str(), "", &load_bpath, "", true)->set_desc(N_("load path for B *.json files"));
    reg.registerFloatVar((idstring + ".falist").c_str(),N_("select json/aidax File"),"S",N_("Select json/aidax file"),&afilelist, 0, 0, 127, 1, 0);
    reg.registerFloatVar((idstring + ".fblist").c_str(),N_("select json/aidax File"),"S",N_("Select json/aidax file"),&bfilelist, 0, 0, 127, 1, 0);

    param[(idstring + ".loadapath").c_str()].signal_changed_string().connect(
        sigc::hide(sigc::mem_fun(this, &RtNeuralMulti::create_rtneural_afilelist)));
    param[(idstring + ".loadbpath").c_str()].signal_changed_string().connect(
        sigc::hide(sigc::mem_fun(this, &RtNeuralMulti::create_rtneural_bfilelist)));
    param[(idstring + ".falist").c_str()].signal_changed_float().connect(
        sigc::hide(sigc::mem_fun(this, &RtNeuralMulti::load_json_afile)));
    param[(idstring + ".fblist").c_str()].signal_changed_float().connect(
        sigc::hide(sigc::mem_fun(this, &RtNeuralMulti::load_json_bfile)));


//    param[(idstring + ".loadafile").c_str()].signal_changed_string().connect(
//        sigc::hide(sigc::mem_fun(this, &RtNeuralMulti::load_json_afile)));
//    param[(idstring + ".loadbfile").c_str()].signal_changed_string().connect(
//        sigc::hide(sigc::mem_fun(this, &RtNeuralMulti::load_json_bfile)));
    return 0;
}

int RtNeuralMulti::register_params_static(const ParamReg& reg)
{
    return static_cast<RtNeuralMulti*>(reg.plugin)->register_par(reg);
}

inline int RtNeuralMulti::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade_file((idstring + "_ui.glade").c_str());
        return 0;
    }
    if (form & UI_FORM_STACK) {

        b.openHorizontalhideBox("");
            b.create_master_slider((idstring + "output").c_str(), "Output");
        b.closeBox();
        b.openHorizontalBox("");
            b.openVerticalBox("");
                b.create_mid_rackknob((idstring + ".input").c_str(), "Input A");
                b.create_mid_rackknob((idstring + ".inputb").c_str(), "Input B");
            b.closeBox();
            b.openVerticalBox("");
                b.create_fload_switch(sw_button, nullptr, (idstring + ".loadafile").c_str());
                b.create_fload_switch(sw_button, nullptr, (idstring + ".loadbfile").c_str());
            b.closeBox();
            b.create_mid_rackknob((idstring + ".output").c_str(), "Output");
            b.create_mid_rackknob((idstring + ".mix").c_str(), "Mix");

        b.closeBox();

        return 0;
    }
    return -1;
}

int RtNeuralMulti::load_ui_f_static(const UiBuilder& b, int form)
{
    return static_cast<RtNeuralMulti*>(b.plugin)->load_ui_f(b, form);
}

void RtNeuralMulti::del_instance(PluginDef *p)
{
    delete static_cast<RtNeuralMulti*>(p);
}

} // namespace gx_engine

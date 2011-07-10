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
 * --------------------------------------------------------------------------
 */



/****************************************************************
 **  definitions for code generated with faust / dsp2cc
 */

typedef void (*inifunc)(int);  //  NOLINT

typedef struct {
    inifunc func;
    const char *name;
} inidef;


static list<inidef>& get_inilist() {
    static list<inidef> inilist;
    return inilist;
}

static list<gx_gui::Parameter*>& get_paramlist() {
    static list<gx_gui::Parameter*> paramlist;
    return paramlist;
}

void register_faust_parameters() {
    list<gx_gui::Parameter*>& paramlist = get_paramlist();
    for (list<gx_gui::Parameter*>::iterator i = paramlist.begin(); i != paramlist.end(); i++) {
        gx_gui::parameter_map.insert(*i);
        // fprintf(stderr, "%s \n",(*i)->id().c_str() );
    }
    paramlist.clear();
}

static gx_gui::Parameter *find_parameter(const char *id) {
    list<gx_gui::Parameter*>& paramlist = get_paramlist();
    for (list<gx_gui::Parameter*>::iterator i = paramlist.begin(); i != paramlist.end(); i++) {
        if ((*i)->id() == id) {
            return *i;
        }
    }
    return 0;
}

static float& get_alias(const char *id) {
    static float dummy;
    gx_gui::Parameter *p = find_parameter(id);
    if (!p) {
        gx_system::gx_print_error("engine", string
                 ("can't define alias for unknown (or not yet defined) parameter id: ") + id);
        return dummy;
    } else {
        return p->getFloat().value;
    }
}

static void registerVar(const char* id, const char* name, const char* tp,
                        const char* tooltip, float* var, float val = 0,
                        float low = 0, float up = 0, float step = 0, bool exp = false) {
    if (!name[0]) {
        assert(strrchr(id, '.'));
        name = strrchr(id, '.')+1;
    }
    gx_gui::Parameter *p = new gx_gui::FloatParameter(
        id, name, gx_gui::Parameter::Continuous, true, *var, val, low, up, step, true, exp);
    if (tooltip) {
        p->set_desc(tooltip);
    }
    get_paramlist().push_back(p);
}

static void registerEnumVar(const char *id, const char* name, const char* tp,
                            const char* tooltip, const char** values, float *var, float val,
                            float low = 0, float up = 0, float step = 1, bool exp = false) {
    if (!name[0]) {
        assert(strrchr(id, '.'));
        name = strrchr(id, '.')+1;
    }
    assert(low == 0.0 && step == 1.0);
    gx_gui::FloatEnumParameter *p = new gx_gui::FloatEnumParameter(
        id, name, values, true, *var,
        static_cast<int>(round(val)), true, exp); // false == no_midi_var
    assert(up == p->upper); // calculated by constructor
    get_paramlist().push_back(p);
}

static inline void registerIntParam(const char*a, const char*b, int*c, int std = 0,
                                    int lower = 0, int upper = 1, bool exp = false) {
     get_paramlist().push_back(
         new gx_gui::IntParameter(a , b, gx_gui::Parameter::Enum, true, *c, std,
                                  lower, upper, true, exp));
}

static void registerInit(const char *name, inifunc f) {
    inidef i;
    i.func = f;
    i.name = name;
    // fprintf(stderr, "%s \n", i.name);
    get_inilist().push_back(i);
}

static void jack_sync() {
    while (sem_wait(&gx_jack::jack_sync_sem) == EINTR);
}

/****************************************************************
**  definitions for ffunction(float Ftube(int,float), "valve.h", "");
**  in gx_amp.dsp - gx_ampmodul.dsp
**/

inline float Ftube(int table, float Vgk) {
    struct gx_tubes::tabled& tab = gx_tubes::tubetable[table];
    float f = (Vgk - tab.low) * tab.istep;
    int i = static_cast<int>(f);
    if (i < 0)
        return tab.data[0];
    if (i >= TAB_SIZE-1)
        return tab.data[TAB_SIZE-1];
    f -= i;
    return tab.data[i]*(1-f) + tab.data[i+1]*f;
}

inline float Ftube2(int table, float Vgk) {
    struct gx_tubes::tabled& tab = gx_tubes::tubetable2[table];
    float f = (Vgk - tab.low) * tab.istep;
    int i = static_cast<int>(f);
    if (i < 0)
        return tab.data[0];
    if (i >= TAB_SIZE-1)
        return tab.data[TAB_SIZE-1];
    f -= i;
    return tab.data[i]*(1-f) + tab.data[i+1]*f;
}

inline float Ftube3(int table, float Vgk) {
    struct gx_tubes::tabled& tab = gx_tubes::tubetable3[table];
    float f = (Vgk - tab.low) * tab.istep;
    int i = static_cast<int>(f);
    if (i < 0)
        return tab.data[0];
    if (i >= TAB_SIZE-1)
        return tab.data[TAB_SIZE-1];
    f -= i;
    return tab.data[i]*(1-f) + tab.data[i+1]*f;
}

inline float Ftube4(int table, float Vgk) {
    struct gx_tubes::tabled& tab = gx_tubes::tubetable4[table];
    float f = (Vgk - tab.low) * tab.istep;
    int i = static_cast<int>(f);
    if (i < 0)
        return tab.data[0];
    if (i >= TAB_SIZE-1)
        return tab.data[TAB_SIZE-1];
    f -= i;
    return tab.data[i]*(1-f) + tab.data[i+1]*f;
}

/****************************************************************/

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

// FIXME (temporary)hack to support older compiler versions
inline float  pow(float b, float e) {return ::powf(b, e);}
inline double pow(double b, double e) {return ::pow(b, e);}
inline double pow(double b, int e)  {return ::pow(b, static_cast<double>(e));}
inline double pow(int b, double e)  {return ::pow(static_cast<double>(b), e);}
inline double pow(double b, float e) {return ::pow(b, static_cast<double>(e));}
inline double pow(float b, double e) {return ::pow(static_cast<double>(b), e);}
inline float  pow(float b, int e)   {return ::powf(b, static_cast<float>(e));}
inline float  pow(int b, float e)   {return ::powf(static_cast<float>(b),  e);}

template <int N> inline float faustpower(float x)       {return powf(x, N);}
template <int N> inline double faustpower(double x)     {return pow(x, N);}
template <int N> inline int faustpower(int x) {return faustpower<N/2>(x) * faustpower<N-N/2>(x);}
template <>      inline int faustpower<0>(int x)        {return 1;}
template <>      inline int faustpower<1>(int x)        {return x;}

#define FAUSTFLOAT float

/****************************************************************
 **  include faust/dsp2cc generated files
 */

// gxdistortion
static struct GxDistortionParams { GxDistortionParams();}
GxDistortionParams;
GxDistortionParams::GxDistortionParams() {
    static FAUSTFLOAT v1, v2;
    registerVar("gxdistortion.drive", "", "S", "", &v1, 0.35, 0.0, 1.0, 0.01);
    registerVar("gxdistortion.wet_dry", "", "S", "", &v2, 100.0, 0.0, 100.0, 1.0);
}

namespace gx_amps {
#include "faust/gxamp.cc"
#include "faust/gxamp2.cc"
#include "faust/gxamp3.cc"
#include "faust/gxamp4.cc"
#include "faust/gxamp5.cc"
#include "faust/gxamp6.cc"
#include "faust/gxamp7.cc"
#include "faust/gxamp8.cc"
#include "faust/gxamp9.cc"
#include "faust/gxamp10.cc"
#include "faust/gxamp11.cc"
#include "faust/gxamp12.cc"
#include "faust/gxamp13.cc"
#include "faust/gx_ampmodul.cc"
}

// effects
namespace gx_effects {
// foreign variable added to faust module feed
// it's set in process_buffers()
namespace noisegate { float ngate = 1;}  // noise-gate, modifies output gain

static struct CabParams { CabParams();}
CabParams;
CabParams::CabParams() {
    registerVar("cab.Level", "", "S", "", &audio.cab_level, 1.0, 0.5, 5.0, 0.5);
    registerVar("cab.bass", "", "S", "", &audio.cab_bass, 0.0, -10.0, 10.0, 0.5);
    registerVar("cab.treble", "", "S", "", &audio.cab_treble, 0.0, -10.0, 10.0, 0.5);
}

#include "faust/bassbooster.cc"
#include "faust/gxfeed.cc"
#include "faust/gx_feedback.cc"
#include "faust/balance.cc"
#include "faust/jconv_post.cc"
#include "faust/balance1.cc"
#include "faust/gx_outputlevel.cc"
#include "faust/gx_ampout.cc"
#include "faust/overdrive.cc"
#include "faust/compressor.cc"
#include "faust/crybaby.cc"
#include "faust/autowah.cc"
#include "faust/echo.cc"
#include "faust/delay.cc"
#include "faust/stereodelay.cc"
#include "faust/stereoecho.cc"
#include "faust/noise_shaper.cc"
#include "faust/gx_distortion.cc"
#include "faust/freeverb.cc"
#include "faust/impulseresponse.cc"
#include "faust/chorus.cc"
#include "faust/moog.cc"
#include "faust/biquad.cc"
#include "faust/flanger.cc"
#include "faust/selecteq.cc"
#include "faust/phaser.cc"
#include "faust/low_high_pass.cc"
#include "faust/noisegate.cc"
#include "faust/softclip.cc"
#include "faust/tonecontroll.cc"
#include "faust/tremolo.cc"
#include "faust/phaser_mono.cc"
#include "faust/chorus_mono.cc"
#include "faust/flanger_mono.cc"
#include "cabinet_impulse_former.cc"
}

// init cabinet impulse former to 48000 Hz, the buffer will resampled
// afterwards whe needed.
void init_non_rt_processing() {
    gx_effects::cabinet_impulse_former::init(48000);
}

void non_rt_processing(int count, float* input, float* output0) {
    gx_effects::cabinet_impulse_former::compute(count, input, output0);
}

// tone stack


namespace gx_tonestacks {

static struct ToneStackParams { ToneStackParams(); }
ToneStackParams;
ToneStackParams::ToneStackParams() {
    static FAUSTFLOAT v1, v2, v3;
    registerVar("amp.tonestack.Treble", "", "S", "", &v1, 0.5, 0.0, 1.0, 0.01);
    registerVar("amp.tonestack.Bass", "", "S", "", &v2, 0.5, 0.0, 1.0, 0.01);
    registerVar("amp.tonestack.Middle", "", "S", "", &v3, 0.5, 0.0, 1.0, 0.01);
}

#include "faust/tonestack_default.cc"
#include "faust/tonestack_bassman.cc"
#include "faust/tonestack_twin.cc"
#include "faust/tonestack_princeton.cc"
#include "faust/tonestack_jcm800.cc"
#include "faust/tonestack_jcm2000.cc"
#include "faust/tonestack_mlead.cc"
#include "faust/tonestack_m2199.cc"
#include "faust/tonestack_ac30.cc"
#include "faust/tonestack_mesa.cc"
#include "faust/tonestack_soldano.cc"
#include "faust/tonestack_jtm45.cc"
#include "faust/tonestack_ac15.cc"
#include "faust/tonestack_peavey.cc"
#include "faust/tonestack_ibanez.cc"
#include "faust/tonestack_roland.cc"
#include "faust/tonestack_ampeg.cc"
}

/****************************************************************
 **  engine helpers and working threads
 */

// pointer to the default tonestack
void (*tonestack_ptr)(int count, float *output, float *output1) =
                   &gx_tonestacks::tonestack_default::compute;

// pointer to the default tube/amp
void (*amp_ptr)(int count, float *output, float *output1) =
                   &gx_amps::gxamp::compute;


// working thread to set the pointer to the selected tonestack and tube/amp
gboolean gx_check_engine_state(gpointer) {

    // only run when tonestack selection have changed
    if (audio.cur_tonestack != audio.tonestack) {
        jack_sync();
        switch (audio.tonestack) {
        case 0: // "default"
            tonestack_ptr = &gx_tonestacks::tonestack_default::compute;
            break;
        case 1: // "Bassman"
            tonestack_ptr = &gx_tonestacks::tonestack_bassman::compute;
            break;
        case 2: // "Twin Reverb"
            tonestack_ptr = &gx_tonestacks::tonestack_twin::compute;
            break;
        case 3: // "Princeton"
            tonestack_ptr = &gx_tonestacks::tonestack_princeton::compute;
            break;
        case 4: // "JCM-800"
            tonestack_ptr = &gx_tonestacks::tonestack_jcm800::compute;
            break;
        case 5: // "JCM-2000"
            tonestack_ptr = &gx_tonestacks::tonestack_jcm2000::compute;
            break;
        case 6: // "M-Lead"
            tonestack_ptr = &gx_tonestacks::tonestack_mlead::compute;
            break;
        case 7: // "M2199"
            tonestack_ptr = &gx_tonestacks::tonestack_m2199::compute;
            break;
        case 8: // "AC-30"
            tonestack_ptr = &gx_tonestacks::tonestack_ac30::compute;
            break;
        case 9: // "Mesa"
            tonestack_ptr = &gx_tonestacks::tonestack_mesa::compute;
            break;
        case 10: // "Soldano"
            tonestack_ptr = &gx_tonestacks::tonestack_soldano::compute;
            break;
        case 11: // "jtm45"
            tonestack_ptr = &gx_tonestacks::tonestack_jtm45::compute;
            break;
        case 12: // "ac15"
            tonestack_ptr = &gx_tonestacks::tonestack_ac15::compute;
            break;
        case 13: // "peavey"
            tonestack_ptr = &gx_tonestacks::tonestack_peavey::compute;
            break;
        case 14: // "ibanez"
            tonestack_ptr = gx_tonestacks::tonestack_ibanez::compute;
            break;
        case 15: // "roland"
            tonestack_ptr = &gx_tonestacks::tonestack_roland::compute;
            break;
        case 16: // "ampeg"
            tonestack_ptr = &gx_tonestacks::tonestack_ampeg::compute;
            break;
        case 17: // "Off"
            break;
        }
        audio.cur_tonestack = audio.tonestack;
    }

    // only run when tube/amp selection have changed
    if (audio.cur_gxtube != audio.gxtube) {
        jack_sync();
         switch (audio.gxtube) {
        case 0: // "never"
            amp_ptr = &gx_amps::gxamp::compute;
            break;
        case 1: // "default"
            amp_ptr = &gx_amps::gxamp::compute;
            break;
        case 2:
            amp_ptr = &gx_amps::gxamp3::compute;
            break;
        case 3:
            amp_ptr = &gx_amps::gxamp2::compute;
            break;
        case 4:
            amp_ptr = &gx_amps::gxamp4::compute;
            break;
        case 5:
            amp_ptr = &gx_amps::gxamp5::compute;
            break;
        case 6:
            amp_ptr = &gx_amps::gxamp10::compute;
            break;
        case 7:
            amp_ptr = &gx_amps::gxamp12::compute;
            break;
        case 8:
            amp_ptr = &gx_amps::gxamp6::compute;
            break;
        case 9:
            amp_ptr = &gx_amps::gxamp7::compute;
            break;
        case 10:
            amp_ptr = &gx_amps::gxamp8::compute;
            break;
        case 11:
            amp_ptr = &gx_amps::gxamp9::compute;
            break;
        case 12:
            amp_ptr = &gx_amps::gxamp11::compute;
            break;
        case 13:
            amp_ptr = &gx_amps::gxamp13::compute;
            break;
        default:
            amp_ptr = &gx_amps::gxamp::compute;
            break;
        }
        audio.cur_gxtube = audio.gxtube;
    }
    return TRUE;
}

// reduce gain to compensate the increased gain by the cabinet
inline void compensate_cab(int count, float *input0, float *output0) {
    double fSlow0 = (0.0010000000000000009 * pow(10, (0.05 * (-audio.cab_level*2.0))));
    static double fRec0[2] = {0, 0};
    for (int i = 0; i < count; i++) {
        fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
        output0[i] = (FAUSTFLOAT)(static_cast<double>(input0[i]) * fRec0[0]);
        // post processing
        fRec0[1] = fRec0[0];
    }
}

// wraper for the rack order function pointers
inline void set_osc_buffer(int count, float *input0, float *output0) {
    (void)memcpy(result, output0, sizeof(float)*count);
}

// wraper for the rack order function pointers 
inline void run_cab_conf(int count, float *input0, float *output0) {
    compensate_cab(count, output0, output0);
    if (!cab_conv.compute(count, output0))
        std::cout << "overload" << endl;
}

// empty mono pointer 
inline void just_return(int count, float *input0, float *output0) {
    return;
}

// empty stereo pointer
inline void just2_return(int count, float *input0, float *input1, float *output0, float *output1) {
    return;
}

// mono rack order pointer
chainorder pre_rack_order_ptr[24];
chainorder post_rack_order_ptr[24];

// stereo rack order pointer
stereochainorder stereo_rack_order_ptr[10];

// working thread to set the order in the all racks
gboolean gx_reorder_rack(gpointer args) {

    // sync to jack_buffer_callback
    jack_sync();

    // set all pointers to just return
    for (int m = 1; m < audio.mono_plug_counter; m++) {
        pre_rack_order_ptr[m] = just_return;
    }

    for (int m = 1; m < audio.mono_plug_counter; m++) {
        post_rack_order_ptr[m] = just_return;
    }

    for (int m = 1; m < audio.stereo_plug_counter; m++) {
        stereo_rack_order_ptr[m] = just2_return;
    }

    // set order and activate pointer for the pre mono rack
    for (int m = 1; m < audio.mono_plug_counter; m++) {
        if (audio.posit[0] == m && audio.fcheckbox5 && !audio.fautowah
                              && audio.effect_pre_post[1]) {
            pre_rack_order_ptr[m] = &gx_effects::crybaby::compute;
        } else if (audio.posit[0] == m && audio.fcheckbox5 && audio.fautowah
                                     && audio.effect_pre_post[1]) {
            pre_rack_order_ptr[m] = &gx_effects::autowah::compute;
        } else if (audio.posit[5] == m && audio.fcheckboxcom1 && audio.effect_pre_post[0]) {
            pre_rack_order_ptr[m] = &gx_effects::compressor::compute;
        } else if (audio.posit[1] == m && audio.foverdrive4 && audio.effect_pre_post[2]) {
            pre_rack_order_ptr[m] = &gx_effects::overdrive::compute;
        } else if (audio.posit[2] == m && audio.fcheckbox4 && audio.effect_pre_post[3]) {
             pre_rack_order_ptr[m] = &gx_effects::gx_distortion::compute;
        } else if (audio.posit[3] == m && audio.fcheckbox6 && audio.effect_pre_post[4]) {
            pre_rack_order_ptr[m] = &gx_effects::freeverb::compute;
        } else if (audio.posit[6] == m && audio.fcheckbox7 && gx_effects::echo::is_inited()
                                     && audio.effect_pre_post[6]) {
            pre_rack_order_ptr[m] = &gx_effects::echo::compute;
        } else if (audio.posit[4] == m && audio.fcheckbox8 && audio.effect_pre_post[5]) {
            pre_rack_order_ptr[m] = &gx_effects::impulseresponse::compute;
        } else if (audio.posit[7] == m && audio.fdelay && gx_effects::delay::is_inited()
                                     && audio.effect_pre_post[7]) {
            pre_rack_order_ptr[m] = &gx_effects::delay::compute;
        } else if (audio.posit[10] == m && audio.feq && audio.effect_pre_post[8]) {
            pre_rack_order_ptr[m] = &gx_effects::selecteq::compute;
        } else if (audio.posit[14] == m && audio.flh && audio.effect_pre_post[9]) {
            pre_rack_order_ptr[m] = &gx_effects::low_high_pass::compute;
        } else if (audio.posit[17] == m && audio.fwv && audio.effect_pre_post[10]) {
            pre_rack_order_ptr[m] = &set_osc_buffer;
        } else if (audio.posit[18] == m && audio.fbiquad && audio.effect_pre_post[11]) {
            pre_rack_order_ptr[m] = &gx_effects::biquad::compute;
        } else if (audio.posit[21] == m && audio.ftremolo && audio.effect_pre_post[12]) {
            pre_rack_order_ptr[m] = &gx_effects::tremolo::compute;
        } else if (audio.posit[22] == m && audio.fpm && audio.effect_pre_post[13]) {
            pre_rack_order_ptr[m] = &gx_effects::phaser_mono::compute;
        } else if (audio.posit[23] == m && audio.fchorus_mono && audio.effect_pre_post[14]
                                      && gx_effects::chorus_mono::is_inited()) {
            pre_rack_order_ptr[m] = &gx_effects::chorus_mono::compute;
        } else if (audio.posit[24] == m && audio.fflanger_mono && audio.effect_pre_post[15]) {
            pre_rack_order_ptr[m] = &gx_effects::flanger_mono::compute;
        } else if (audio.posit[25] == m && audio.ffeedback && audio.effect_pre_post[16]) {
            pre_rack_order_ptr[m] = &gx_effects::gx_feedback::compute;
        } else if (audio.posit[26] == m && audio.ftonestack && audio.effect_pre_post[17]) {
            pre_rack_order_ptr[m] = tonestack_ptr;
        } else if (audio.posit[27] == m && audio.fcab && audio.effect_pre_post[18]) {
            pre_rack_order_ptr[m] = &run_cab_conf;

        }
    }

    // set order and activate pointer for the post mono rack
    for (int m = 1; m < audio.mono_plug_counter; m++) {
        if (audio.posit[0] == m && audio.fcheckbox5 && !audio.fautowah
                              && !audio.effect_pre_post[1]) {
            post_rack_order_ptr[m] = &gx_effects::crybaby::compute;
        } else if (audio.posit[0] == m && audio.fcheckbox5 && audio.fautowah
                                     && !audio.effect_pre_post[1]) {
            post_rack_order_ptr[m] = &gx_effects::autowah::compute;
        } else if (audio.posit[5] == m && audio.fcheckboxcom1 && !audio.effect_pre_post[0]) {
            post_rack_order_ptr[m] = &gx_effects::compressor::compute;
        } else if (audio.posit[1] == m && audio.foverdrive4 && !audio.effect_pre_post[2]) {
            post_rack_order_ptr[m] = &gx_effects::overdrive::compute;
        } else if (audio.posit[2] == m && audio.fcheckbox4 && !audio.effect_pre_post[3]) {
            post_rack_order_ptr[m] = &gx_effects::gx_distortion::compute;
        } else if (audio.posit[3] == m && audio.fcheckbox6 && !audio.effect_pre_post[4]) {
            post_rack_order_ptr[m] = &gx_effects::freeverb::compute;
        } else if (audio.posit[6] == m && audio.fcheckbox7 && gx_effects::echo::is_inited()
                                     && !audio.effect_pre_post[6]) {
            post_rack_order_ptr[m] = &gx_effects::echo::compute;
        } else if (audio.posit[4] == m && audio.fcheckbox8 && !audio.effect_pre_post[5]) {
            post_rack_order_ptr[m] = &gx_effects::impulseresponse::compute;
        } else if (audio.posit[7] == m && audio.fdelay && gx_effects::delay::is_inited()
                                     && !audio.effect_pre_post[7]) {
            post_rack_order_ptr[m] = &gx_effects::delay::compute;
        } else if (audio.posit[10] == m && audio.feq && !audio.effect_pre_post[8]) {
            post_rack_order_ptr[m] = &gx_effects::selecteq::compute;
        } else if (audio.posit[14] == m && audio.flh && !audio.effect_pre_post[9]) {
            post_rack_order_ptr[m] = &gx_effects::low_high_pass::compute;
        } else if (audio.posit[17] == m && audio.fwv && !audio.effect_pre_post[10]) {
            post_rack_order_ptr[m] = &set_osc_buffer;
        } else if (audio.posit[18] == m && audio.fbiquad && !audio.effect_pre_post[11]) {
            post_rack_order_ptr[m] = &gx_effects::biquad::compute;
        } else if (audio.posit[21] == m && audio.ftremolo && !audio.effect_pre_post[12]) {
            post_rack_order_ptr[m] = &gx_effects::tremolo::compute;
        } else if (audio.posit[22] == m && audio.fpm && !audio.effect_pre_post[13]) {
            post_rack_order_ptr[m] = &gx_effects::phaser_mono::compute;
        } else if (audio.posit[23] == m && audio.fchorus_mono && !audio.effect_pre_post[14]
                                      && gx_effects::chorus_mono::is_inited()) {
            post_rack_order_ptr[m] = &gx_effects::chorus_mono::compute;
        } else if (audio.posit[24] == m && audio.fflanger_mono && !audio.effect_pre_post[15]) {
            post_rack_order_ptr[m] = &gx_effects::flanger_mono::compute;
        } else if (audio.posit[25] == m && audio.ffeedback && !audio.effect_pre_post[16]) {
            post_rack_order_ptr[m] = &gx_effects::gx_feedback::compute;
        } else if (audio.posit[26] == m && audio.ftonestack && !audio.effect_pre_post[17]) {
            post_rack_order_ptr[m] = tonestack_ptr;
        } else if (audio.posit[27] == m && audio.fcab && !audio.effect_pre_post[18]) {
            post_rack_order_ptr[m] = &run_cab_conf;
        }
    }

    // get position of mem sensible mono effects
    audio.effect_buffer[0] = static_cast<int>(audio.posit[6]);
    audio.effect_buffer[1] = static_cast<int>(audio.posit[7]);
    audio.effect_buffer[2] = static_cast<int>(audio.posit[23]);

    // set order and activate pointer for the stereo rack
    for (int m = 1; m < audio.stereo_plug_counter; m++) {
        if (audio.posit[8] == m && audio.fchorus && gx_effects::chorus::is_inited()) {
            stereo_rack_order_ptr[m] = gx_effects::chorus::compute;
        } else if (audio.posit[9] == m && audio.fflanger) {
            stereo_rack_order_ptr[m] = gx_effects::flanger::compute;
        } else if (audio.posit[11] == m && audio.fmoog) {
            stereo_rack_order_ptr[m] = gx_effects::moog::compute;
        } else if (audio.posit[12] == m && audio.fphaser) {
            stereo_rack_order_ptr[m] = gx_effects::phaser::compute;
        } else if (audio.posit[15] == m && audio.fsd && gx_effects::stereodelay::is_inited()) {
            stereo_rack_order_ptr[m] = gx_effects::stereodelay::compute;
        } else if (audio.posit[16] == m && audio.fse && gx_effects::stereoecho::is_inited()) {
            stereo_rack_order_ptr[m] = gx_effects::stereoecho::compute;
        } else if (audio.posit[19] == m && audio.famp) {
            stereo_rack_order_ptr[m] = gx_amps::gx_ampmodul::compute;
        } else if (audio.posit[20] == m && audio.ftone) {
            stereo_rack_order_ptr[m] = gx_effects::tonecontroll::compute;
        }
    }

    // get position of mem sensible stereo effects
    audio.effect_buffer[3] = static_cast<int>(audio.posit[8]);
    audio.effect_buffer[4] = static_cast<int>(audio.posit[15]);
    audio.effect_buffer[5] = static_cast<int>(audio.posit[16]);

    return TRUE;
}

/****************************************************************
 **  free memory when effects are unused, load with jack_sync
 */

static void activate_callback(float val, void *data) {
    ((void (*)(bool, int))data)(!(val == 0.0), gx_jack::gxjack.jack_sr);
}

static void faust_add_callback(const char* id, void (*func)(bool, int)) {
    new gx_ui::GxUiCallbackItemFloat(gx_gui::GxMainInterface::instance(),
                                     reinterpret_cast<float*>(gx_gui::parameter_map[id].zone()),
                                     activate_callback, reinterpret_cast<void*>(func));
}

void faust_init(int samplingFreq) {
    // faust_add_callback("SampleLooper.on_off", sloop::activate);
    faust_add_callback("delay.on_off", gx_effects::delay::activate);
    faust_add_callback("echo.on_off", gx_effects::echo::activate);
    faust_add_callback("chorus.on_off", gx_effects::chorus::activate);
    faust_add_callback("chorus_mono.on_off", gx_effects::chorus::activate);
    faust_add_callback("stereodelay.on_off", gx_effects::stereodelay::activate);
    faust_add_callback("stereoecho.on_off", gx_effects::stereoecho::activate);
    list<inidef>& inilist = get_inilist();
    for (list<inidef>::iterator i = inilist.begin(); i != inilist.end(); i++) {
        try {
            i->func(samplingFreq);
        } catch(bad_alloc) {
            string name = gx_gui::param_group(i->name, true);
            gx_system::gx_print_error("DSP Module", (boost::format
                      ("not enough memory to initialize module %1%") % i->name).str());
        }
    }
}


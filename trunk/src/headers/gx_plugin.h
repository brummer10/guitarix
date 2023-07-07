/*
 * Copyright (C) 2011, 2013 Hermann Meyer, James Warden, Andreas Degert, Pete Shorthose
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
 *    This file is part of the guitarix GUI main class
 *    Note: this header file depends on gx_system.h 
 * 
 * ----------------------------------------------------------------------------
 */

#pragma once

#ifndef _GX_PLUGIN_H
#define _GX_PLUGIN_H

#include "gx_compiler.h"

// forward declarations (need not be resolved for plugin definition)
struct PluginDef;

/*
** helper class for PluginDef::load_ui
*/

#define UI_NUM_TOP           0x01
#define UI_NUM_BOTTOM        0x03
#define UI_NUM_LEFT          0x05
#define UI_NUM_RIGHT         0x07
#define UI_NUM_POSITION_MASK 0x07
#define UI_NUM_SHOW_ALWAYS   0x08
#define UI_LABEL_INVERSE     0x02

// Stock Items for Gxw::Switch

#define sw_led        "led"
#define sw_switch     "switch"
#define sw_switchit   "switchit"
#define sw_minitoggle "minitoggle"
#define sw_button     "button"
#define sw_pbutton    "pbutton"
#define sw_rbutton    "rbutton"
#define sw_prbutton   "prbutton"
#define sw_fbutton    "fbutton"
#define sw_frbutton   "frbutton"

#define UI_FORM_STACK 0x01
#define UI_FORM_GLADE 0x02

struct UiBuilder {
    PluginDef *plugin;
    void (*load_glade)(const char *data);
    void (*load_glade_file)(const char *fname);
    void (*openTabBox)(const char* label);
    void (*openVerticalBox)(const char* label);
    void (*openVerticalBox1)(const char* label);
    void (*openVerticalBox2)(const char* label);
    void (*openHorizontalBox)(const char* label);
    void (*openHorizontalhideBox)(const char* label);
    void (*openHorizontalTableBox)(const char *label);
    void (*openFrameBox)(const char *label);
    void (*openFlipLabelBox)(const char* label);
    void (*openpaintampBox)(const char* label);
    void (*closeBox)();
    void (*insertSpacer)();
    void (*set_next_flags)(int flags);
    // methods creating UI elements connected to parameter_id's.
    // the check_parameter function in dsp2cc identifies these
    // functions by the prefix create_ so please stick to this
    // prefix or change the checker
    void (*create_master_slider)(const char *id, const char *label);
    void (*create_feedback_slider)(const char *id, const char *label);
    void (*create_small_rackknob)(const char *id, const char *label);
    void (*create_big_rackknob)(const char *id, const char *label);
    void (*create_selector_no_caption)(const char *id);
    void (*create_switch_no_caption)(const char *sw_type,const char * id);
    void (*create_feedback_switch)(const char *sw_type,const char * id);
    void (*create_spin_value)(const char * id, const char *label);
    void (*create_port_display)(const char * id, const char *label);
    void (*create_p_display)(const char * id, const char * idl, const char * idh);
    void (*create_switch)(const char *sw_type,const char * id, const char *label);
    void (*create_selector)(const char *id, const char *label);
    void (*create_simple_meter)(const char *id);
    void (*create_simple_c_meter)(const char *id, const char *idl, const char *label);
    void (*create_small_rackknobr)(const char *id, const char *label);
    void (*create_wheel)(const char *id, const char *label);
    void (*create_simple_spin_value)(const char *id);
    void (*create_eq_rackslider_no_caption)(const char *id);
    void (*create_fload_switch)(const char *sw_type,const char * id,const char * idf);
    void (*create_mid_rackknob)(const char *id, const char *label);
    // adding additional functions:
    // If possible don't change the order of the current definition.
    // new functions need to be added at the following places:
    //  StackBoxBuilder: decl, real implementation
    //  UiBuilderImpl: decl, assign to pointer, call real implementation
    //  UiBuilderVirt: decl, assign to pointer, write json
    //  GxMachineRemote::load_remote_ui(): call real implementation
};

/*
** helper class for PluginDef::registerfunc
*/

struct value_pair {
    const char *value_id;
    const char *value_label;
};

/**
 * Parameter registration function pointers
 *
 * All functions expect a character string parameter tp:
 *
 * first char:
 * - S: continuous values, float (Faust vslider, hslider, nentry, vbargraph, hbargraph)
 * - B: 2 values: 0/1, false/true (Faust checkbox, button)
 *
 * following chars (order doesn't matter, there should not be duplicate chars):
 * - A: aliased (parameter id used by several plugins), (Faust: [alias])
 * - L: logarithmic input / output, (Faust: [log])
 * - N: no midi controller connection possible, (Faust: [nomidi])
 * - o: output parameter (will be polled for changes by plugin)
 * - s: parameter not saveable in preset / state file
 * - w: no warning (if a non saveable parameter is found in a preset / state file)
 * - O: non-savable, no-midi output parameter (same as "Nos"), (Faust: vbargraph, hbargraph)
 * - M: maxlevel output variable (max value since last poll)
 */
struct ParamReg {
    PluginDef *plugin;
    float *(*registerFloatVar)(
        const char* id, const char* name, const char* tp,
        const char* tooltip, float* var, float val,
        float low, float up, float step, const value_pair* values);
    int *(*registerIntVar)(
        const char* id, const char* name, const char* tp,
        const char* tooltip, int* var, int val,
        int low, int up, const value_pair* values);
    bool *(*registerBoolVar)(
        const char* id, const char* name, const char* tp,
        const char* tooltip, bool* var, bool val);
};

/*
** structure for plugin definition
*/

typedef void (*inifunc)(unsigned int samplingFreq, PluginDef *plugin);
typedef int (*activatefunc)(bool start, PluginDef *plugin);
typedef void (*clearstatefunc)(PluginDef *plugin);
// in-place would be a tad more efficient but some plugins have to be cleaned up before
//typedef void (*process_mono_audio) (int count, float *buffer, PluginDef *plugin);
//typedef void (*process_stereo_audio) (int count, float *buffer1, float *buffer2, PluginDef *plugin);
typedef void (*process_mono_audio) (int count, float *input, float *output, PluginDef *plugin);
typedef void (*process_stereo_audio) (int count, float *input1, float *input2,
                                      float *output1, float *output2, PluginDef *plugin);
typedef int (*registerfunc)(const ParamReg& reg);
typedef int (*uiloader)(const UiBuilder& builder, int format);
typedef void (*deletefunc)(PluginDef *plugin);

enum {
    PGN_STEREO      = 0x0001, // stereo plugin (auto set when stereo_audio)
    PGN_PRE         = 0x0002, // (mono) always "pre" position
    PGN_POST        = 0x0004, // (mono) always "post" position
    PGN_GUI         = 0x0008, // register variables for gui (auto set when load_ui)
    PGN_POST_PRE    = 0x0010, // (mono) register post/pre variable (auto set when
                              // gui and not always pre or post)
    PGN_ALTERNATIVE = 0x0020, // plugin is part of a group of modules
                              // managed by a ModuleSelector
    PGN_SNOOP       = 0x0040, // does not alter audio stream
    PGN_MODE_NORMAL = 0x0100, // plugin is active in normal mode (default)
    PGN_MODE_BYPASS = 0x0200, // plugin is active in bypass mode
    PGN_MODE_MUTE   = 0x0400, // plugin is active in mute mode
    PGN_FIXED_GUI   = 0x0800, // user cannot hide plugin GUI
    PGN_NO_PRESETS  = 0x1000,
    // For additional flags see struct Plugin
};

#define PLUGINDEF_VERMAJOR_MASK 0xff00
#define PLUGINDEF_VERMINOR_MASK 0x00ff
#define PLUGINDEF_VERSION       0x0700

struct PluginDef {
    int version;         // = PLUGINDEF_VERSION
    int flags;           // PGN_xx flags

    const char* id;      // must be unique
    const char* name;    // displayed name (not translated) (may be 0)
    const char** groups; // list of alternating group_id, group_name (not translated)
                         // may be 0 (else end with 0 entry)
    const char* description; // description (tooltip)
    const char* category;
    const char* shortname;

    // maximal one of mono_audio, stereo_audio must be set
    // all function pointers in PluginDef can be independently set to 0
    process_mono_audio mono_audio; // function for mono audio processing
    process_stereo_audio stereo_audio; //function for stereo audio processing

    inifunc set_samplerate; // called before audio processing and when rate changes
    activatefunc activate_plugin; // called when taking in / out of pressing chain
    registerfunc register_params; // called once after module loading (register parameter ids)
    uiloader load_ui; // called once after module loading (define user interface)
    clearstatefunc clear_state; // clear internal audio state; may be called
                                // before calling the process function
    deletefunc delete_instance; // delete this plugin instance
};

// shared libraries with plugin modules must define
// a function "get_gx_plugin" of type plugin_inifunc
// return != 0 for error
extern "C" typedef int (*plugin_inifunc)(unsigned int idx, PluginDef **p);

#endif /* !_GX_PLUGIN_H */

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

#ifndef SRC_HEADERS_GX_ENGINE_H_
#define SRC_HEADERS_GX_ENGINE_H_

namespace gx_engine {

/* -- guitarix main engine -- */

/****************************************************************
 ** class ModuleSelectorFromList
 */

class ModuleSelectorFromList: public ModuleSelector, private PluginDef {
private:
    int selector;
    const char* select_id;
    const char* select_name;
    Plugin* current_plugin;
    PluginDef **modules;
    unsigned int size;
    value_pair *values;

    static int static_register(const ParamReg& reg);
    int register_parameter(const ParamReg& reg);
public:
    Plugin plugin;
    ModuleSelectorFromList(
	EngineControl& seq, const char* id, const char* name,
	const char *category, plugindef_creator module_ids[], const char* select_id,
	const char* select_name, uiloader loader, const char** groups = 0, int flags = 0);
    ~ModuleSelectorFromList();
    void set_module();
};


/****************************************************************
 ** class GxEngine
 */

struct PluginChange {
    Plugin *pl;
    enum pc { remove, update, update_category, add } status;
    PluginChange(Plugin *pl_, pc status_): pl(pl_), status(status_) {}
};

class GxEngine: public ModuleSequencer {
private:
    gx_resample::BufferResampler resamp;
    sigc::signal<void,Plugin*,PluginChange::pc> plugin_changed;
    LadspaLoader ladspaloader;
    void load_static_plugins();
public:
    MidiControllerList controller_map;
    // ModuleSelector's
    ModuleSelectorFromList crybaby;
    ModuleSelectorFromList wah;
    ModuleSelectorFromList tonestack;
    ModuleSelectorFromList ampstack;
    ModuleSelectorFromList poweramps;
    // internal audio modules
    //NoiseGate noisegate;
    OutPutGate outputgate;
    MonoMute monomute;
    StereoMute stereomute;
    TunerAdapter tuner;
#ifndef GUITARIX_AS_PLUGIN
    Drumout drumout;
    Directout directout;
#endif
    MaxLevel maxlevel;
    OscilloscopeAdapter oscilloscope;
    ConvolverMonoAdapter mono_convolver;
    ConvolverStereoAdapter stereo_convolver;
    CabinetConvolver cabinet;
    CabinetStereoConvolver cabinet_st;
    PreampConvolver preamp;
    PreampStereoConvolver preamp_st;
    ContrastConvolver contrast;
    LiveLooper loop;
#ifndef GUITARIX_AS_PLUGIN
    SCapture record;
    SCapture record_st;
#endif
    DrumSequencer dseq;
    smbPitchShift detune;
    //
public:
    GxEngine(const string& plugin_dir, ParameterGroups& groups, const gx_system::CmdlineOptions& options);
    ~GxEngine();
    void ladspaloader_update_plugins();
    sigc::signal<void,Plugin*,PluginChange::pc>& signal_plugin_changed() { return plugin_changed; }
};

/* ------------------------------------------------------------------- */
} /* end of gx_engine namespace */
#endif  // SRC_HEADERS_GX_ENGINE_H_


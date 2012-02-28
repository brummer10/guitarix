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

namespace gx_jack { class GxJack; }

namespace gx_engine {

/* -- guitarix main engine -- */

/****************************************************************
 ** class ModuleSelectorFromList
 */

class ModuleSelectorFromList: public ModuleSelector, private PluginDef, private gx_ui::GxUiItemUInt {
private:
    unsigned int selector;
    const char* select_id;
    const char* select_name;
    Plugin* current_plugin;
    PluginDef **modules;
    unsigned int size;
    static int static_register(const ParamReg& reg);
    int register_parameter(const ParamReg& reg);
    void reflectZone();
public:
    Plugin plugin;
    ModuleSelectorFromList(
	EngineControl& seq, gx_ui::GxUI& ui, const char* id, const char* name,
	plugindef_creator module_ids[],	const char* select_id,
	const char* select_name, const char** groups = 0, int flags = 0);
    ~ModuleSelectorFromList();
    void set_module();
};


/****************************************************************
 ** class GxEngine
 */

class GxEngine: public ModuleSequencer {
private:
    gx_resample::BufferResampler resamp;
    void load_static_plugins();
public:
    // ModuleSelector's
    ModuleSelectorFromList crybaby;
    ModuleSelectorFromList tonestack;
    ModuleSelectorFromList ampstack;
    // internal audio modules
    NoiseGate noisegate;
    MonoMute monomute;
    StereoMute stereomute;
    TunerAdapter tuner;
    MidiAudioBuffer midiaudiobuffer;
    MaxLevel maxlevel;
    OscilloscopeAdapter oscilloscope;
    ConvolverAdapter convolver;
    CabinetConvolver cabinet;
    ContrastConvolver contrast;
public:
    GxEngine(const string& plugin_dir, ParamMap& param, ParameterGroups& groups);
    ~GxEngine();
    void set_jack(gx_jack::GxJack *jack) { midiaudiobuffer.set_jack(jack); }
};

/* ------------------------------------------------------------------- */
} /* end of gx_engine namespace */
#endif  // SRC_HEADERS_GX_ENGINE_H_


/*
 * Copyright (C) 2011 Hermann Meyer, James Warden, Andreas Degert, Pete Shorthose
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
 *
 * 
 * ----------------------------------------------------------------------------
 */

#pragma once

#ifndef _GX_PLUGINLV2_H
#define _GX_PLUGINLV2_H

// forward declarations (need not be resolved for plugin definition)
struct PluginLV2;

struct value_pair {
    const char *value_id;
    const char *value_label;
};

/*
** structure for plugin definition
*/

typedef void (*inifunc)(uint32_t samplingFreq, PluginLV2 *plugin);
typedef int (*activatefunc)(bool start, PluginLV2 *plugin);
typedef void (*clearstatefunc)(PluginLV2 *plugin);
typedef void (*process_mono_audio) (int count, float *input, float *output, PluginLV2 *plugin);
typedef void (*process_stereo_audio) (int count, float *input1, float *input2,
				      float *output1, float *output2, PluginLV2 *plugin);
typedef void (*registerfunc)(uint32_t port,void* data, PluginLV2 *plugin);
typedef void (*deletefunc)(PluginLV2 *plugin);

typedef PluginLV2 *(*plug) ();

#define PLUGINLV2_VERMAJOR_MASK 0xff00
#define PLUGINLV2_VERSION       0x0500

struct PluginLV2 {
    int version;	 // = PLUGINLV2_VERSION

    const char* id;	 // must be unique
    const char* name;	 // displayed name (not translated) (may be 0)
    // maximal one of mono_audio, stereo_audio must be set
    // all function pointers in PluginLV2 can be independently set to 0
    process_mono_audio mono_audio; // function for mono audio processing
    process_stereo_audio stereo_audio; //function for stereo audio processing

    inifunc set_samplerate; // called before audio processing and when rate changes
    activatefunc activate_plugin; // called when taking in / out of pressing chain
    registerfunc connect_ports; // called once after module loading (register parameter ids)
    clearstatefunc clear_state;	// clear internal audio state; may be called
				// before calling the process function
    deletefunc delete_instance; // delete this plugin instance
};

#endif /* !_GX_PLUGINLV2_H */

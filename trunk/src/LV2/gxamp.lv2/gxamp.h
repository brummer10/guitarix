/*
 * Copyright (C) 2012 Hermann Meyer, Andreas Degert, Pete Shorthose
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

#pragma once

#ifndef SRC_HEADERS_GXAMP_H_
#define SRC_HEADERS_GXAMP_H_

#include <lv2.h>
#include <lv2/lv2plug.in/ns/ext/buf-size/buf-size.h>
#include <lv2/lv2plug.in/ns/ext/options/options.h>
#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/atom/forge.h>
#include <lv2/lv2plug.in/ns/ext/urid/urid.h>
#include <lv2/lv2plug.in/ns/ext/log/log.h>
#include <lv2/lv2plug.in/ns/ext/worker/worker.h>
#include <lv2/lv2plug.in/ns/ext/patch/patch.h>

#define GXPLUGIN_URI "http://guitarix.sourceforge.net/plugins/gxamp"
#define GXPLUGIN_UI_URI "http://guitarix.sourceforge.net/plugins/gxamp/gui"

#define GXPlugin__on         GXPLUGIN_URI "#on"
#define GXPlugin__off        GXPLUGIN_URI "#off"
#define GXPlugin__cab        GXPLUGIN_URI "#cab"
#define GXPlugin__pre        GXPLUGIN_URI "#pre"

typedef enum
{
  AMP_MASTERGAIN = 0,
  AMP_PREGAIN,
  AMP_WET_DRY,
  AMP_DRIVE,
  MID,
  BASS,
  TREBLE,
  CLevel,
  ALevel,
  AMP_OUTPUT,
  AMP_INPUT,
  AMP_CONTROL,
  AMP_NOTIFY,
} PortIndex;


typedef struct
{
  LV2_URID atom_Blank;
  LV2_URID atom_Float;
  LV2_URID atom_Int;
  LV2_URID atom_eventTransfer;
  LV2_URID gx_on;
  LV2_URID gx_off;
  LV2_URID gx_cab;
  LV2_URID gx_pre;
} GXPluginURIs;

static inline void
map_gx_uris(LV2_URID_Map* map, GXPluginURIs* uris)
{
  uris->atom_Blank          = map->map(map->handle, LV2_ATOM__Blank);
  uris->atom_Float          = map->map(map->handle, LV2_ATOM__Float);
  uris->atom_Int            = map->map(map->handle, LV2_ATOM__Int);
  uris->atom_eventTransfer  = map->map(map->handle, LV2_ATOM__eventTransfer);
  uris->gx_on               = map->map(map->handle, GXPlugin__on);
  uris->gx_off              = map->map(map->handle, GXPlugin__off);
  uris->gx_cab              = map->map(map->handle, GXPlugin__cab);
  uris->gx_pre              = map->map(map->handle, GXPlugin__pre);
}

static inline LV2_Atom*
write_set_cab(LV2_Atom_Forge*    forge,
              const GXPluginURIs* uris)
{
  LV2_Atom_Forge_Frame set_frame;
  LV2_Atom* set = (LV2_Atom*)lv2_atom_forge_blank(
                    forge, &set_frame, 1, uris->gx_cab);
  lv2_atom_forge_pop(forge, &set_frame);
  return set;
}

static inline LV2_Atom*
write_set_pre(LV2_Atom_Forge*    forge,
              const GXPluginURIs* uris)
{
  LV2_Atom_Forge_Frame set_frame;
  LV2_Atom* set = (LV2_Atom*)lv2_atom_forge_blank(
                    forge, &set_frame, 1, uris->gx_pre);
  lv2_atom_forge_pop(forge, &set_frame);
  return set;
}

static inline LV2_Atom*
write_set_float(LV2_Atom_Forge*    forge,
                const GXPluginURIs* uris,
                float        value)
{
  LV2_Atom_Forge_Frame set_frame;
  LV2_Atom* set = (LV2_Atom*)lv2_atom_forge_resource(
                    forge, &set_frame, 1, uris->atom_Float);
  lv2_atom_forge_float(forge, value);
  lv2_atom_forge_pop(forge, &set_frame);

  return set;
}

static inline LV2_Atom*
write_set_int(LV2_Atom_Forge*    forge,
              const GXPluginURIs* uris,
              int        value)
{
  LV2_Atom_Forge_Frame set_frame;
  LV2_Atom* set = (LV2_Atom*)lv2_atom_forge_resource(
                    forge, &set_frame, 1, uris->atom_Int);
  lv2_atom_forge_int(forge, value);
  lv2_atom_forge_pop(forge, &set_frame);

  return set;
}

#endif //SRC_HEADERS_GXAMP_H_

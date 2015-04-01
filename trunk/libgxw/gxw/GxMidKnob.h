/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
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
 */

#ifndef __GX_MID_KNOB_H__
#define __GX_MID_KNOB_H__


#include "GxKnob.h"

G_BEGIN_DECLS

#define GX_TYPE_MID_KNOB          (gx_mid_knob_get_type())
#define GX_MID_KNOB(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GX_TYPE_MID_KNOB, GxMidKnob))
#define GX_MID_KNOB_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass),  GX_TYPE_MID_KNOB, GxMidKnobClass))
#define GX_IS_MID_KNOB(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GX_TYPE_MID_KNOB))
#define GX_IS_MID_KNOB_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GX_TYPE_MID_KNOB))
#define GX_MID_KNOB_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GX_TYPE_MID_KNOB, GxMidKnobClass))

typedef struct _GxMidKnob GxMidKnob;
typedef struct _GxMidKnobClass GxMidKnobClass; 

struct _GxMidKnob {
	GxKnob parent;
};

struct _GxMidKnobClass {
	GxKnobClass parent_class;
};

GType gx_mid_knob_get_type(void);

G_END_DECLS

#endif /* __GX_MID_KNOB_H__ */

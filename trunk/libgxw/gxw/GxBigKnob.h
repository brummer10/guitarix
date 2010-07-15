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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __GX_BIG_KNOB_H__
#define __GX_BIG_KNOB_H__


#include "GxKnob.h"

G_BEGIN_DECLS

#define GX_TYPE_BIG_KNOB          (gx_big_knob_get_type())
#define GX_BIG_KNOB(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GX_TYPE_BIG_KNOB, GxBigKnob))
#define GX_BIG_KNOB_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass),  GX_TYPE_BIG_KNOB, GxBigKnobClass))
#define GX_IS_BIG_KNOB(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GX_TYPE_BIG_KNOB))
#define GX_IS_BIG_KNOB_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GX_TYPE_BIG_KNOB))
#define GX_BIG_KNOB_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GX_TYPE_BIG_KNOB, GxBigKnobClass))

typedef struct {
	GxKnob parent;
} GxBigKnob;

typedef struct {
	GxKnobClass parent_class;
} GxBigKnobClass;

GType gx_big_knob_get_type(void);

G_END_DECLS

#endif /* __GX_BIG_KNOB_H__ */

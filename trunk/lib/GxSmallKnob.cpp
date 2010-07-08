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

#include "GxSmallKnob.h"

G_DEFINE_TYPE(GxSmallKnob, gx_small_knob, GX_TYPE_KNOB);

static void gx_small_knob_class_init(GxSmallKnobClass *klass)
{
	klass->parent_class.stock_id = "smallknob";
}

static void gx_small_knob_init(GxSmallKnob *small_knob)
{
}

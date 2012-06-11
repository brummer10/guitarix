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

#include <glibmm_generate_extra_defs/generate_extra_defs.h>
#include <gxw.h>

int main(int argc, char** argv)
{
	gtk_init(&argc, &argv);
	std::cout << get_defs(GX_TYPE_CONTROL_PARAMETER)
	          << get_defs(GX_TYPE_SWITCH)
	          << get_defs(GX_TYPE_REGLER)
	          << get_defs(GX_TYPE_KNOB)
	          << get_defs(GX_TYPE_BIG_KNOB)
	          << get_defs(GX_TYPE_SMALL_KNOB)
	          << get_defs(GX_TYPE_TUNER)
	          << get_defs(GX_TYPE_RACK_TUNER)
	          << get_defs(GX_TYPE_FAST_METER)
	          << get_defs(GX_TYPE_WAVE_VIEW)
	          << get_defs(GX_TYPE_SELECTOR)
	          << get_defs(GX_TYPE_SWITCH)
	          << get_defs(GX_TYPE_TOGGLE_IMAGE)
	          << get_defs(GX_TYPE_IR_EDIT)
	          << get_defs(GX_TYPE_RADIO_BUTTON)
	          << get_defs(GX_TYPE_WHEEL)
	          << get_defs(GX_TYPE_HSLIDER)
	          << get_defs(GX_TYPE_VSLIDER)
	          << get_defs(GX_TYPE_MINI_SLIDER)
	          << get_defs(GX_TYPE_EQ_SLIDER)
	          << get_defs(GX_TYPE_PAINT_BOX)
	          << get_defs(GX_TYPE_METER_SCALE)
	          << get_defs(GX_TYPE_GRADIENT)
		;
	return 0;
}

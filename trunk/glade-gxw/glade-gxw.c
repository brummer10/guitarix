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

#include <gxw/gxinit.h>
#include "config.h"

/* Catalog init function */
void glade_gx_init (const char *name)
{
	gxw_init();
	gtk_icon_theme_append_search_path(
		gtk_icon_theme_get_default(), GX_ICON_DIR);
}

GType gx_paint_func_get_type(void)
{
	static GType etype = 0;
	if (G_UNLIKELY(etype == 0)) {
		static const GEnumValue values[] = {
			{ 0, "amp_expose", "amp_expose" },
			{ 1, "conv_widget_expose", "conv_widget_expose" },
			{ 2, "upper_widget_expose", "upper_widget_expose" },
			{ 3, "rectangle_expose", "rectangle_expose" },
			{ 4, "box_uni_2_expose", "box_uni_2_expose" },
			{ 5, "convolver_icon_expose", "convolver_icon_expose" },
			{ 6, "AmpBox_expose", "AmpBox_expose" },
			{ 7, "tribal_box_expose", "tribal_box_expose" },
			{ 8, "vbox_expose", "vbox_expose" },
			{ 9, "filter_box_expose", "filter_box_expose" },
			{10, "plug_box_expose", "plug_box_expose" },
			{11, "info_box_expose_on", "info_box_expose on" },
			{12, "info_box_expose_off", "info_box_expose off" },
			{13, "slooper_expose", "slooper_expose" },
			{14, "zac_expose", "zac expose" },
			{15, "gxhead_expose", "gxhead_expose" },
			{16, "RackBox_expose", "RackBox_expose"},
			{17, "gxrack_expose", "gxrack_expose" },
			{18, "lhfilter_expose", "lhfilter_expose" },
			{19, "crybaby_expose", "crybaby_expose" },
			{20, "compressor_expose", "compressor_expose" },
			{21, "eq_expose", "eq_expose" },
			{22, "led_expose", "led_expose" },
			{23, "seq_expose", "seq_expose" },
			{24, "ir_expose", "ir_expose" },
			{25, "main_expose", "main_expose" },
			{26, "level_meter_expose", "level_meter_expose" },
            {27, "cab_expose", "cab_expose" },
            
            {28, "rack_expose", "rack_expose" },
            {29, "rack_amp_expose", "rack_amp_expose" },
            {30, "rack_unit_expose", "rack_unit_expose" },
            {31, "rack_unit_shrink_expose", "rack_unit_shrink_expose" },
            
			{ 0, NULL, NULL }
		};
		etype = g_enum_register_static (g_intern_static_string ("GxPaintFunc"), values);
	}
	return etype;
}

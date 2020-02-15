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
			{ 0, "", "" },
			{ 1, "rectangle_skin_color_expose", "rectangle_skin_color_expose" },
            { 2, "rack_unit_expose", "rack_unit_expose" },
            { 3, "rack_unit_shrink_expose", "rack_unit_shrink_expose" },
            { 4, "rack_amp_expose", "rack_amp_expose" },
			{ 5, "zac_expose", "zac expose" },
			{ 6, "gxhead_expose", "gxhead_expose" },
			{ 7, "RackBox_expose", "RackBox_expose"},
			{ 8, "gxrack_expose", "gxrack_expose" },
			{ 9, "compressor_expose", "compressor_expose" },
			{10, "simple_level_meter_expose", "simple_level_meter_expose" },
			{11, "level_meter_expose", "level_meter_expose" },
            {12, "amp_skin_expose", "amp_skin_expose" },
            {13, "gx_rack_unit_expose", "gx_rack_unit_expose" },
            {14, "gx_rack_unit_shrink_expose", "gx_rack_unit_shrink_expose" },
            {15, "gx_rack_amp_expose", "gx_rack_amp_expose" },
            {16, "draw_skin", "draw_skin" },
            {17, "rack_expose", "rack_expose" },
            {18, "box_uni_1_expose", "box_uni_1_expose" },
            {19, "box_uni_2_expose", "box_uni_2_expose" },
            {20, "box_skin_expose", "box_skin_expose" },
            {21, "live_box_expose", "live_box_expose" },
            {22, "logo_expose", "logo_expose" },
			{ 0, NULL, NULL }
		};
		etype = g_enum_register_static (g_intern_static_string ("GxPaintFunc"), values);
	}
	return etype;
}

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

#include <gtk/gtk.h>
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
			{ 0, "amp_expose", "amp expose" },
			{ 1, "conv_widget_expose", "conv widget expose" },
			{ 2, "upper_widget_expose", "upper widget expose" },
			{ 3, "rectangle_expose", "rectangle expose" },
			{ 4, "rectangle_skin_color_expose", "rectangle skin color expose" },
			{ 5, "convolver_icon_expose", "convolver icon expose" },
			{ 6, "AmpBox_expose", "AmpBox expose" },
			{ 7, "tribal_box_expose", "tribal box expose" },
			{ 8, "vbox_expose", "vbox expose" },
			{ 9, "filter_box_expose", "filter box expose" },
			{10, "plug_box_expose", "plug box expose" },
			{11, "info_box_expose_on", "info box expose on" },
			{12, "info_box_expose_off", "info box expose off" },
			{13, "slooper_expose", "slooper expose" },
			{14, "zac_expose", "zac expose" },
			{ 0, NULL, NULL }
		};
		etype = g_enum_register_static (g_intern_static_string ("GxPaintFunc"), values);
	}
	return etype;
}

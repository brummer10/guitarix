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

#include <gtk/gtkiconfactory.h>
#include "gxinit.h"

#include "gximages.cc"

typedef struct {
	const char *icon_name;
	const guint8 *icon_data;
} image_entry;

static image_entry image_data[] = {
	{ "button_off", pb_button_off },
	{ "button_on", pb_button_on },
	{ "eqslider", pb_eqslider },
	{ "bigknob", pb_knob1 },
	{ "led_off", pb_led_off },
	{ "led_on", pb_led_on },
	{ "minislider", pb_minislider },
	{ "minitoggle_off", pb_minitoggle_off },
	{ "minitoggle_on", pb_minitoggle_on },
	{ "hslider", pb_hslider },
	{ "smallknob", pb_smallknob1 },
	{ "smallknobr", pb_smallknob1 },
	{ "switchit_off", pb_switchit_off },
	{ "switchit_on", pb_switchit_on },
	{ "switch_off", pb_switch_off },
	{ "switch_on", pb_switch_on },
	{ "pbutton_on", pb_pbutton_on },
	{ "pbutton_off", pb_pbutton_off },
	{ "rbutton_on", pb_rbutton_on },
	{ "rbutton_off", pb_rbutton_off },
	{ "vslider", pb_vslider },
	{ "wheel_back", pb_wheel_back },
	{ "wheel_fringe", pb_wheel_fringe },
	{ "wheel_pointer", pb_wheel_pointer },
	{ "tribe", pb_tribe },
	{ "guitar", pb_guitar },
	{ "gxhead", pb_gxhead },
	{ "gxhead_face", pb_gxhead_face },
	{ NULL, NULL },
};

void gxw_init()
{
	g_type_init();
	GtkIconFactory *factory = gtk_icon_factory_new();
	for (image_entry *p = image_data; p->icon_name; p++) {
		gtk_icon_factory_add(
			factory, p->icon_name,
			gtk_icon_set_new_from_pixbuf(
				gdk_pixbuf_new_from_inline(
					-1, p->icon_data, FALSE, NULL)));
	}
	gtk_icon_factory_add_default(factory);
}

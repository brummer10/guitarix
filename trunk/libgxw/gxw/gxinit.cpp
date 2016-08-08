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

#include "gxinit.h"

#include "gximages.cc"

typedef struct {
	const char *icon_name;

} image_entry;

static image_entry image_data[] = {
	{ "button_off" },
	{ "button_on" },
	{ "eqslider" },
	{ "levelslider" },
	{ "bigknob" },
	{ "midknob" },
	{ "led_off" },
	{ "led_on" },
	{ "minislider" },
	{ "minitoggle_off" },
	{ "minitoggle_on" },
	{ "hslider" },
	{ "smallknob" },
	{ "smallknobr" },
	{ "switchit_off" },
	{ "switchit_on" },
	{ "switch_off" },
	{ "switch_on" },
	{ "switch_mid_off" },
	{ "switch_mid_on" },
	{ "switch_min_off" },
	{ "switch_min_on" },
	{ "pbutton_on" },
	{ "pbutton_off" },
	{ "rbutton_on" },
	{ "rbutton_off" },
	{ "prbutton_on" },
	{ "prbutton_off" },
	{ "fbutton_on" },
	{ "fbutton_off" },
    { "frbutton_on" },
	{ "frbutton_off" },
	{ "vslider" },
	{ "wheel_back" },
    { "wheel_vertical_back" },
	{ "wheel_fringe" },
	{ "wheel_pointer" },
	{ "gxhead" },
    { "gxplate" },
    { "gxplate2" },
    { "gxplate3" },
    { "portdisplay" },
	{ "guitarix" },
    { "screw" },
    { "logo" },

    { "background1" },
    { "background2" },
    { "handle_left" },
    { "handle_right" },
    { "selector_icon" },
    { "insert" },
    { "watermark" },
	{ NULL },
};

void gxw_init()
{
#if !GLIB_CHECK_VERSION(2, 36, 0) 
	g_type_init();
#endif
    gchar *path =NULL;

	GtkIconFactory *factory = gtk_icon_factory_new();
	for (image_entry *p = image_data; p->icon_name; p++) {
		path = g_strdup_printf ("/icons/%s.png", p->icon_name);
		gtk_icon_factory_add(
			factory, p->icon_name,
			gtk_icon_set_new_from_pixbuf(
				gdk_pixbuf_new_from_resource(
					path, NULL)));
	}
	gtk_icon_factory_add_default(factory);
}

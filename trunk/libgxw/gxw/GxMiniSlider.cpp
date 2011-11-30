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

#include "GxMiniSlider.h"
#include <gtk/gtkprivate.h>

#define P_(s) (s)   // FIXME -> gettext

G_DEFINE_TYPE(GxMiniSlider, gx_mini_slider, GX_TYPE_HSLIDER);

static void gx_mini_slider_class_init(GxMiniSliderClass *klass)
{
	GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;
	klass->parent_class.stock_id = "minislider";
	klass->parent_class.mouse_scale_factor = 0.4;
	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("slider-width",P_("size of slider"),
		                   P_("Width of movable part of vslider"),
		                 0, 100, 6, GParamFlags(GTK_PARAM_READABLE)));
}

static void gx_mini_slider_init(GxMiniSlider *mini_slider)
{
}

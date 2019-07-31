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

#include "GxSimpleValueDisplay.h"

#define P_(s) (s)   // FIXME -> gettext

static gboolean gx_simple_value_display_draw (GtkWidget *widget, cairo_t *cr);
static void gx_simple_value_display_get_preferred_width (GtkWidget *widget, gint *min_width, gint *natural_width);
static void gx_simple_value_display_get_preferred_height (GtkWidget *widget, gint *min_height, gint *natural_height);
static void gx_simple_value_display_size_request (GtkWidget *widget, gint *width, gint *height);
static gboolean gx_simple_value_display_button_press (GtkWidget *widget, GdkEventButton *event);

G_DEFINE_TYPE(GxSimpleValueDisplay, gx_simple_value_display, GX_TYPE_REGLER);

static void gx_simple_value_display_class_init(GxSimpleValueDisplayClass *klass)
{
	GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;
	widget_class->draw = gx_simple_value_display_draw;
	widget_class->get_preferred_width = gx_simple_value_display_get_preferred_width;
	widget_class->get_preferred_height = gx_simple_value_display_get_preferred_height;
	widget_class->button_press_event = gx_simple_value_display_button_press;
}

static void gx_simple_value_display_get_preferred_width (GtkWidget *widget, gint *min_width, gint *natural_width)
{
	gint width, height;
	gx_simple_value_display_size_request(widget, &width, &height);

	if (min_width) {
		*min_width = width;
	}
	if (natural_width) {
		*natural_width = width;
	}
}

static void gx_simple_value_display_get_preferred_height (GtkWidget *widget, gint *min_height, gint *natural_height)
{
	gint width, height;
	gx_simple_value_display_size_request(widget, &width, &height);

	if (min_height) {
		*min_height = height;
	}
	if (natural_height) {
		*natural_height = height;
	}
}


static void gx_simple_value_display_size_request(GtkWidget *widget, gint *width, gint *height)
{
	g_assert(GX_IS_SIMPLE_VALUE_DISPLAY(widget));
	*width = 0;
	*height = 0;
	_gx_regler_calc_size_request(GX_REGLER(widget), width, height);
}

#define FILL_ALLOCATION_WIDTH

static gboolean gx_simple_value_display_draw(GtkWidget *widget, cairo_t *cr)
{
	g_assert(GX_IS_SIMPLE_VALUE_DISPLAY(widget));
	GdkRectangle image_rect, value_rect;
	image_rect.width = 0;
	image_rect.height = 0;
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, &value_rect);
#ifdef FILL_ALLOCATION_WIDTH
	GtkAllocation allocation;
	gtk_widget_get_allocation(widget, &allocation);
	value_rect.x = allocation.x;
	value_rect.width = allocation.width;
#endif
	_gx_regler_simple_display_value(GX_REGLER(widget), cr, &value_rect);
	return FALSE;
}

static gboolean gx_simple_value_display_button_press (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_SIMPLE_VALUE_DISPLAY(widget));
	gtk_widget_grab_focus(widget);
	if (event->button != 3) {
		return FALSE;
	}
	GdkRectangle image_rect, value_rect;
	image_rect.width = 0;
	image_rect.height = 0;
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, &value_rect);
	GtkAllocation allocation;
	gtk_widget_get_allocation(widget, &allocation);
	if (_approx_in_rectangle(event->x + allocation.x, event->y + allocation.y, &value_rect)) {
		gboolean ret;
		g_signal_emit_by_name(GX_REGLER(widget), "value-entry", &value_rect, event, &ret);
	}
	return FALSE;
}

static void gx_simple_value_display_init(GxSimpleValueDisplay *simple_value_display)
{
	gx_regler_set_show_value(&simple_value_display->parent, TRUE);
}

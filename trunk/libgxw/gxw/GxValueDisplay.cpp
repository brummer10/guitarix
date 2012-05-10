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

#include "GxValueDisplay.h"
#include <gtk/gtkmain.h>
#include <gtk/gtkprivate.h>

#define P_(s) (s)   // FIXME -> gettext

static gboolean gx_value_display_expose (GtkWidget *widget, GdkEventExpose *event);
static void gx_value_display_size_request (GtkWidget *widget, GtkRequisition *requisition);
static gboolean gx_value_display_button_press (GtkWidget *widget, GdkEventButton *event);

G_DEFINE_TYPE(GxValueDisplay, gx_value_display, GX_TYPE_REGLER);

static void gx_value_display_class_init(GxValueDisplayClass *klass)
{
	GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;
	widget_class->expose_event = gx_value_display_expose;
	widget_class->size_request = gx_value_display_size_request;
	widget_class->button_press_event = gx_value_display_button_press;
}

static void gx_value_display_size_request(GtkWidget *widget, GtkRequisition *requisition)
{
	g_assert(GX_IS_VALUE_DISPLAY(widget));
	requisition->width = 0;
	requisition->height = 0;
	_gx_regler_calc_size_request(GX_REGLER(widget), requisition);
}

#define FILL_ALLOCATION_WIDTH

static gboolean gx_value_display_expose(GtkWidget *widget, GdkEventExpose *event)
{
	g_assert(GX_IS_VALUE_DISPLAY(widget));
	GdkRectangle image_rect, value_rect;
	image_rect.width = 0;
	image_rect.height = 0;
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, &value_rect);
#ifdef FILL_ALLOCATION_WIDTH
	value_rect.x = widget->allocation.x;
	value_rect.width = widget->allocation.width;
#endif
	_gx_regler_display_value(GX_REGLER(widget), &value_rect);
	return FALSE;
}

static gboolean gx_value_display_button_press (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_VALUE_DISPLAY(widget));
	gtk_widget_grab_focus(widget);
	if (event->button != 3) {
		return FALSE;
	}
	GdkRectangle image_rect, value_rect;
	image_rect.width = 0;
	image_rect.height = 0;
	_gx_regler_get_positions(GX_REGLER(widget), &image_rect, &value_rect);
	if (_approx_in_rectangle(event->x + widget->allocation.x, event->y + widget->allocation.y, &value_rect)) {
		gboolean ret;
		g_signal_emit_by_name(GX_REGLER(widget), "value-entry", &value_rect, event, &ret);
	}
	return FALSE;
}

static void gx_value_display_init(GxValueDisplay *value_display)
{
	value_display->parent.show_value = TRUE;
}

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
 * -------------------------------------------------------------------------
 *
 * Code shamelessly stolen from Ardour by Paul Davis, thanks man!
 * This is actually an adaptation of the C++ gtkmm2ext class in the
 * GTK C style.
 *
 * -------------------------------------------------------------------------
 */
#include <math.h>
#include <stdlib.h>
#include <gtk/gtkprivate.h>
#include "GxFastMeter.h"

#ifndef max
#define max(x,y) (((x)>(y)) ? (x) : (y))
#endif

#ifndef min
#define min(x,y) (((x)<(y)) ? (x) : (y))
#endif

#define P_(s) (s)   // FIXME -> gettext

enum {
	PROP_HOLD = 1,
	PROP_DIMEN
};

static const int min_size = 10;

static void gx_fast_meter_class_init(GxFastMeterClass*);
static void gx_fast_meter_init(GxFastMeter*);

static gboolean gx_fast_meter_expose_event(GtkWidget*, GdkEventExpose*);
static void gx_fast_meter_size_allocate(GtkWidget *widget, GtkAllocation *allocation);
static void gx_fast_meter_size_request(GtkWidget*, GtkRequisition*);
static void gx_fast_meter_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gx_fast_meter_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static void queue_vertical_redraw(GxFastMeter*, GdkWindow*);
static void request_vertical_meter(GtkWidget *widget);
static void gx_fast_meter_style_set (GtkWidget *widget, GtkStyle  *previous_style);

G_DEFINE_TYPE(GxFastMeter, gx_fast_meter, GTK_TYPE_DRAWING_AREA);

/* ----- fast meter class init ----- */
void gx_fast_meter_class_init(GxFastMeterClass* klass)
{
	GtkWidgetClass* widget_class = (GtkWidgetClass*)klass;
	GObjectClass *gobject_class = G_OBJECT_CLASS(klass);

	widget_class->size_request  = gx_fast_meter_size_request;
	widget_class->size_allocate = gx_fast_meter_size_allocate;
	widget_class->expose_event  = gx_fast_meter_expose_event;
	widget_class->style_set = gx_fast_meter_style_set;
	gobject_class->set_property = gx_fast_meter_set_property;
	gobject_class->get_property = gx_fast_meter_get_property;

	g_object_class_install_property(
		gobject_class, PROP_HOLD, g_param_spec_int(
			"hold", P_("Hold"),
			P_("Count of cycles for which the peak value is held on display"),
			0, 1000, 5, GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property(
		gobject_class, PROP_DIMEN, g_param_spec_int(
			"dimen", P_("Dimen"),
			P_("Horizontal size of meter"),
			0, 100, 20, GParamFlags(GTK_PARAM_READWRITE)));
	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_boxed("clr-bottom",P_("bottom color"),
		                   P_("indicator color gradient: value at the bottom"),
		                   GDK_TYPE_COLOR,
		                   GParamFlags(GTK_PARAM_READABLE)));
	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_boxed("clr-middle",P_("middle color"),
		                   P_("indicator color gradient: value in the middle"),
		                   GDK_TYPE_COLOR,
		                   GParamFlags(GTK_PARAM_READABLE)));
	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_boxed("clr-top",P_("top color"),
		                   P_("indicator color gradient: value near the top"),
		                   GDK_TYPE_COLOR,
		                   GParamFlags(GTK_PARAM_READABLE)));
	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_boxed("over",P_("clip warn color"),
		                   P_("indicator color for values > 0 dbFS"),
		                   GDK_TYPE_COLOR,
		                   GParamFlags(GTK_PARAM_READABLE)));
	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("dimen",P_("width of indicator"),
		                   P_("width of (vertical) indicator"),
		                 0, 100, 5, GParamFlags(GTK_PARAM_READABLE)));
}

/* ----- fast meter init ----- */
void gx_fast_meter_init(GxFastMeter* fm)
{
	fm->pixbuf = 0;
	fm->top_of_meter = 0;
	fm->last_peak_rect.width = 0;
	fm->last_peak_rect.height = 0;
	fm->hold_cnt = 0;
	fm->hold_state = 0;
	fm->current_peak = 0;
	fm->current_level = 0;
	gtk_widget_set_events(GTK_WIDGET(fm),
	                      GDK_BUTTON_PRESS_MASK|GDK_BUTTON_RELEASE_MASK);
}

/* -------------- */
GtkWidget* gtk_fast_meter_new (int hold)
{
	GxFastMeter* fm;
	fm = GX_FAST_METER(g_object_new(GX_TYPE_FAST_METER, NULL));
	fm->hold_cnt = hold;
	return GTK_WIDGET (fm);
}

#define grad_size 4

GdkColor default_gradient_color[grad_size] = {
	//   red     green   blue
	{ 0, 0x0000, 0xffff, 0x0000 }, // clr-bottom
	{ 0, 0xffff, 0xffff, 0x0000 }, // clr-middle
	{ 0, 0xffff, 0xaa00, 0x0000 }, // clr-top
	{ 0, 0xffff, 0x0000, 0x0000 }  // over
};

#define CVALUE(i,c,y,mx) (guint8)floor(((int)rgb[i]->c + (((int)rgb[i+1]->c - (int)rgb[i]->c) * (y)) / (float)(mx))/256)

/* ----- create pixbuf for vertical meter ------ */
static void request_vertical_meter(GtkWidget *widget)
{
	GxFastMeter* fm = GX_FAST_METER(widget);
	if (fm->pixbuf) {
		g_object_unref(G_OBJECT(fm->pixbuf));
	}
	int dimen = fm->dimen;
	if (dimen == 0) {
		gtk_widget_style_get(widget, "dimen", &dimen, NULL);
	}
	int width = min(widget->allocation.width, dimen);
	int height = widget->allocation.height;
	fm->pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, width, widget->allocation.height);
	if (!fm->pixbuf) {
		return;
	}
	guint8* data = gdk_pixbuf_get_pixels(fm->pixbuf);
	int rowstride = gdk_pixbuf_get_rowstride(fm->pixbuf);

	guint8 r = 0, g = 0, b = 0;
    GdkColor *rgb[4];
    unsigned int i;
    gtk_widget_style_get(widget, "clr-bottom", &rgb[0], "clr-middle", &rgb[1], "clr-top", &rgb[2], "over", &rgb[3], NULL);
	for (i = 0; i < sizeof(rgb)/sizeof(rgb[0]); i++) {
		if (!rgb[i]) {
			rgb[i] = gdk_color_copy(&default_gradient_color[i]);
		}
	}

	int knee = (int)floor((float)height * 0.996);
	int y;

	for (y = 0; y < knee/2; y++) {
		r = CVALUE(0, red, y, knee/2);
		g = CVALUE(0, green, y, knee/2);
		b = CVALUE(0, blue, y, knee/2);
		for (int x = 0; x < width; x++) {
			data[(height-y-1) * rowstride + x * 3 + 0] = r;
			data[(height-y-1) * rowstride + x * 3 + 1] = g;
			data[(height-y-1) * rowstride + x * 3 + 2] = b;
		}
	}

	int offset = knee - y;
	for (int i=0; i < offset; i++,y++) {
		r = CVALUE(1, red, i, offset);
		g = CVALUE(1, green, i, offset);
		b = CVALUE(1, blue, i, offset);
		for (int x = 0; x < width; x++) {
			data[(height-y-1) * rowstride + x * 3 + 0] = r;
			data[(height-y-1) * rowstride + x * 3 + 1] = g;
			data[(height-y-1) * rowstride + x * 3 + 2] = b;
		}
	}

	for (; y < height; y++) {
		for (int x = 0; x < width; x++) {
			data[(height-y-1) * rowstride + x * 3 + 0] = rgb[3]->red;
			data[(height-y-1) * rowstride + x * 3 + 1] = rgb[3]->green;
			data[(height-y-1) * rowstride + x * 3 + 2] = rgb[3]->blue;
		}
	}
	for (i = 0; i < sizeof(rgb)/sizeof(rgb[0]); i++) {
		gdk_color_free(rgb[i]);
	}
}

/* ------ hold count ----- */
void gx_fast_meter_set_hold_count(GxFastMeter* fm, int val)
{
	if (val < 1) val = 1;

	fm->hold_cnt     = val;
	fm->hold_state   = 0;
	fm->current_peak = 0;

	gtk_widget_queue_draw(GTK_WIDGET(fm));
}

static void gx_fast_meter_size_request (GtkWidget* wd, GtkRequisition* req)
{
	req->height = min_size;
	req->width  = GX_FAST_METER(wd)->dimen;
	if (req->width == 0) {
		gtk_widget_style_get(wd, "dimen", &req->width, NULL);
	}
}

static void gx_fast_meter_size_allocate (GtkWidget *widget, GtkAllocation *allocation)
{
	GTK_WIDGET_CLASS(gx_fast_meter_parent_class)->size_allocate(widget, allocation);
	request_vertical_meter(widget);
}

static void gx_fast_meter_set_property(GObject *object, guint prop_id,
                                           const GValue *value, GParamSpec *pspec)
{
	GxFastMeter *fm = GX_FAST_METER(object);
	switch(prop_id) {
	case PROP_HOLD:
		fm->hold_cnt = g_value_get_int(value);
		g_object_notify(object, "hold");
		fm->hold_state = 0;
		break;
	case PROP_DIMEN:
		fm->dimen = g_value_get_int(value);
		g_object_notify(object, "dimen");
		gtk_widget_queue_resize(GTK_WIDGET(object));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void gx_fast_meter_get_property(GObject *object, guint prop_id,
                                           GValue *value, GParamSpec *pspec)
{
	GxFastMeter *fm = GX_FAST_METER(object);

	switch(prop_id) {
	case PROP_HOLD:
		g_value_set_int(value, fm->hold_cnt);
		break;
	case PROP_DIMEN:
		g_value_set_int(value, fm->dimen);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void gx_fast_meter_style_set(GtkWidget *widget, GtkStyle  *previous_style)
{
	request_vertical_meter(widget);
}

/* ------- expose event -------- */
static gboolean gx_fast_meter_expose_event (GtkWidget* wd, GdkEventExpose* ev)
{
	GxFastMeter* fm = GX_FAST_METER(wd);
	gint         top_of_meter;
	GdkRectangle intersection;
	GdkRectangle rect;

	if (!fm->pixbuf) {
		return FALSE;
	}
	int height = gdk_pixbuf_get_height(fm->pixbuf);
	int width = gdk_pixbuf_get_width(fm->pixbuf);
	fm->top_of_meter = top_of_meter = (gint) floor (height * fm->current_level);

	/* reset the height & origin of the rect that needs to show the pixbuf */

	rect.x = 0;
	rect.y = 0;
	rect.width  = width;
	rect.height = height - top_of_meter;

	if (gdk_rectangle_intersect (&rect, &ev->area, &intersection)) {
		GdkWindow* window = GTK_WIDGET(fm)->window;/*gtk_widget_get_window(GTK_WIDGET(fm));*/
		GtkStyle*  style  = gtk_widget_get_style (GTK_WIDGET(fm));

		gdk_draw_rectangle(GDK_DRAWABLE(window),
		                   style->black_gc,
		                   TRUE,
		                   intersection.x,
		                   intersection.y,
		                   intersection.width,
		                   intersection.height);
	}

	rect.x = 0;
	rect.y = height - top_of_meter;
	rect.width  = width;
	rect.height = height - rect.y;
	if (gdk_rectangle_intersect(&rect, &ev->area, &intersection)) {
		// draw the part of the meter image that we need.
		// the area we draw is bounded "in reverse" (top->bottom)
		GdkWindow*   window = GTK_WIDGET(fm)->window;/*gtk_widget_get_window(GTK_WIDGET(fm));*/
		GtkStyle*    style  = gtk_widget_get_style (GTK_WIDGET(fm));
		gdk_draw_pixbuf(GDK_DRAWABLE(window),
		                style->fg_gc[GTK_WIDGET_STATE(GTK_WIDGET(fm))],
		                fm->pixbuf,
		                intersection.x, intersection.y,
		                intersection.x, intersection.y,
		                intersection.width, intersection.height,
		                GDK_RGB_DITHER_NONE, 0, 0);
	}

	// draw peak bar

	if (fm->hold_state) {
		fm->last_peak_rect.x     = 0;
		fm->last_peak_rect.width = width;
		fm->last_peak_rect.y     = height -	(gint)floor(height * fm->current_peak);

		fm->last_peak_rect.height = min(3, height - fm->last_peak_rect.y);

		GdkWindow*   window = GTK_WIDGET(fm)->window;
		GtkStyle*    style  = gtk_widget_get_style (GTK_WIDGET(fm));

		gdk_draw_pixbuf(GDK_DRAWABLE(window),
		                style->fg_gc[GTK_WIDGET_STATE(GTK_WIDGET(fm))],
		                fm->pixbuf,
		                0, fm->last_peak_rect.y,
		                0, fm->last_peak_rect.y,
		                width, fm->last_peak_rect.height,
		                GDK_RGB_DITHER_NONE, 0, 0);
	} else {
		fm->last_peak_rect.width  = 0;
		fm->last_peak_rect.height = 0;
	}

	return FALSE;
}

/* ------- setting meter level ----------- */
void gx_fast_meter_set(GxFastMeter* fm, gdouble lvl)
{
	float old_level = fm->current_level;
	float old_peak  = fm->current_peak;

	lvl = max(0.0, min(1.0, lvl));
	fm->current_level = lvl;

	if (lvl >= fm->current_peak) {
	    fm->current_peak = lvl;
	    fm->hold_state   = fm->hold_cnt;
	}
	if (fm->hold_state > 0) {
	    --fm->hold_state;
	}
	if (fm->hold_state == 0) {
	    fm->current_peak = lvl;
	}
	if (fm->current_level == old_level &&
	    (fm->hold_state == 0 || fm->current_peak  == old_peak)) {
		return;
	}
	GdkWindow* window = gtk_widget_get_window(GTK_WIDGET(fm));
	if (window) {
		queue_vertical_redraw(fm, window);
	}
}

/* ------------- clear fast meter object ------------ */
void gx_fast_meter_clear(GxFastMeter* fm)
{
	fm->current_level = 0;
	fm->current_peak  = 0;
	fm->hold_state    = 0;
	gtk_widget_queue_draw(GTK_WIDGET(fm));
}

/* ------------------------------ static functions ------------------------- */

/* --------- vertical drawing queue ----------- */
void queue_vertical_redraw (GxFastMeter* fm, GdkWindow* win)
{
	GdkRectangle rect;
	if (!fm->pixbuf) {
		return;
	}
	int height = gdk_pixbuf_get_height(fm->pixbuf);
	int width = gdk_pixbuf_get_width(fm->pixbuf);
	gint new_top = (gint)floor(height * fm->current_level);

	rect.x      = 0;
	rect.width  = width;
	rect.height = new_top;
	rect.y      = height - new_top;

	if (new_top >= fm->top_of_meter) {
		/* colored/pixbuf got larger, just draw the new section */
		/* rect.y stays where it is because of X coordinates */
		/* height of invalidated area is between new.y (smaller) and old.y
		   (larger).
		   X coordinates just make my brain hurt.
		*/
		rect.height = height - fm->top_of_meter - rect.y;
	} else {
		/* it got smaller, compute the difference */
		/* rect.y becomes old.y (the smaller value) */
		rect.y = height - fm->top_of_meter;
		/* rect.height is the old.y (smaller) minus the new.y (larger) */
		rect.height = height - rect.height;
	}

	GdkRegion* region = 0;
	bool queue = false;

	if (rect.height != 0) {
		/* ok, first region to draw ... */
		region = gdk_region_rectangle (&rect);
		queue = true;
	}

	/* redraw the last place where the last peak hold bar was;
	   the next expose will draw the new one whether its part of
	   expose region or not. */

	if (fm->last_peak_rect.width * fm->last_peak_rect.height != 0) {
		if (!queue) {
			region = gdk_region_new ();
			queue = true;
		}

		gdk_region_union_with_rect (region, &fm->last_peak_rect);
	}
	if (queue) {
		gdk_window_invalidate_region (win, region, TRUE);
	}
	if (region) {
		gdk_region_destroy(region);
		region = 0;
	}
}

/* -------------- */
/* EOF */

/*
 * Copyright (C) 2009 Hermann Meyer and James Warden
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
 * -------------------------------------------------------------------------
 *
 * Code shamelessly stolen from Ardour by Paul Davis, thanks man!
 * This is actually an adaptation of the C++ gtkmm2ext class in the
 * GTK C style.
 *
 * -------------------------------------------------------------------------
 */
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <iostream>

#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include "GtkFastMeter.h"

#ifndef max
#define max(x,y) (((x)>(y)) ? (x) : (y))
#endif

#ifndef min
#define min(x,y) (((x)<(y)) ? (x) : (y))
#endif

#define UINT_TO_RGB(u,r,g,b) { (*(r)) = ((u)>>16)&0xff; (*(g)) = ((u)>>8)&0xff; (*(b)) = (u)&0xff; }
#define UINT_TO_RGBA(u,r,g,b,a) { UINT_TO_RGB(((u)>>8),r,g,b); (*(a)) = (u)&0xff; }

int         GtkFastMeter::min_v_pixbuf_size = 10;
int         GtkFastMeter::max_v_pixbuf_size = 1024;

int GtkFastMeter::rgb0 = 0;
int GtkFastMeter::rgb1 = 0;
int GtkFastMeter::rgb2 = 0;
int GtkFastMeter::rgb3 = 0;

static void      gtk_fast_meter_class_init       (GtkFastMeterClass*);
static void      gtk_fast_meter_init	         (GtkFastMeter*);

extern gboolean  gtk_fast_meter_expose_event  (GtkWidget*, GdkEventExpose*);
static void      gtk_fast_meter_size_request  (GtkWidget*, GtkRequisition*);
static void      gtk_fast_meter_size_allocate (GtkWidget*, GtkAllocation*);
static void      gtk_fast_meter_realize       (GtkWidget*);

static gboolean   vertical_expose         (GtkFastMeter*, GdkEventExpose*);
static void       queue_vertical_redraw   (GtkFastMeter*, GdkWindow*, float);
static GdkPixbuf* request_vertical_meter  (int w, int h);

static GtkWidgetClass* parent_class = NULL;

/* ----- fast meter widget type ----- */
GType gtk_fast_meter_get_type(void)
{
	static GType fm_type = 0;

	if (!fm_type)
	{
		static const GTypeInfo fm_info =
			{
				sizeof(GtkFastMeterClass),
				NULL,
				NULL,
				(GClassInitFunc)gtk_fast_meter_class_init,
				NULL,
				NULL,
				sizeof(GtkFastMeter),
				0,
				(GInstanceInitFunc)gtk_fast_meter_init
			};

		fm_type =
			g_type_register_static(GTK_TYPE_WIDGET,
			                       "GtkFastMeter", &fm_info, (GTypeFlags)0);
	}

	return fm_type;
}

/* ----- fast meter class init ----- */
void gtk_fast_meter_class_init(GtkFastMeterClass* klass)
{
	GtkObjectClass* object_class;
	GtkWidgetClass* widget_class;

	object_class = (GtkObjectClass*)klass;
	widget_class = (GtkWidgetClass*)klass;

	parent_class =
		(GtkWidgetClass*)gtk_type_class(gtk_widget_get_type());

	object_class->destroy = gtk_fast_meter_destroy;

	widget_class->realize       = gtk_fast_meter_realize;
	widget_class->size_request  = gtk_fast_meter_size_request;
	widget_class->expose_event  = gtk_fast_meter_expose_event;
	widget_class->size_allocate = gtk_fast_meter_size_allocate;
}

/* ----- fast meter init ----- */
void gtk_fast_meter_init (GtkFastMeter* fm)
{
	fm->hold_cnt              = 0;
	fm->hold_state            = 0;

	fm->current_peak          = 0;
	fm->current_level         = 0;

	fm->last_peak_rect.width  = 0;
	fm->last_peak_rect.height = 0;

	GtkFastMeter::rgb0 = 0x00ff00;
	GtkFastMeter::rgb1 = 0xffff00;
	GtkFastMeter::rgb2 = 0xffaa00;
	GtkFastMeter::rgb3 = 0xff0000;
}

/* -------------- */
GtkWidget* gtk_fast_meter_new (long hold,
                               unsigned long dimen,
                               int len,
                               int clr0,
                               int clr1,
                               int clr2,
                               int clr3)
{
	GtkFastMeter* fm;
	fm = GTK_FAST_METER(g_object_new(GTK_TYPE_FAST_METER, NULL));

	fm->hold_cnt      = hold;

	GtkFastMeter::rgb0 = clr0;
	GtkFastMeter::rgb1 = clr1;
	GtkFastMeter::rgb2 = clr2;
	GtkFastMeter::rgb3 = clr0;

	gtk_widget_set_events(GTK_WIDGET(fm),
	                      GDK_BUTTON_PRESS_MASK|GDK_BUTTON_RELEASE_MASK);

	fm->pixrect.x = 0;
	fm->pixrect.y = 0;

	if (len == 0) len = 140;
	fm->pixbuf = request_vertical_meter(dimen, len);

	fm->pixheight = gdk_pixbuf_get_height(fm->pixbuf);
	fm->pixwidth  = gdk_pixbuf_get_width(fm->pixbuf);

	fm->pixrect.width  = min(fm->pixwidth, (gint)dimen);
	fm->pixrect.height = fm->pixheight;

	fm->request_width  = fm->pixrect.width;
	fm->request_height = fm->pixrect.height;

	return GTK_WIDGET (fm);
}

/* ----- create pixbuf for vertical meter ------ */
static GdkPixbuf* request_vertical_meter(int width, int height)
{
	if (height < GtkFastMeter::min_v_pixbuf_size)
		height = GtkFastMeter::min_v_pixbuf_size;

	if (height > GtkFastMeter::max_v_pixbuf_size)
		height = GtkFastMeter::max_v_pixbuf_size;

	GdkPixbuf* ret;
	guint8*    data = (guint8*)malloc(width*height * 3);

	guint8 r,g,b,r0,g0,b0,r1,g1,b1,r2,g2,b2,r3,g3,b3,a;

	UINT_TO_RGBA (GtkFastMeter::rgb0, &r0, &g0, &b0, &a);
	UINT_TO_RGBA (GtkFastMeter::rgb1, &r1, &g1, &b1, &a);
	UINT_TO_RGBA (GtkFastMeter::rgb2, &r2, &g2, &b2, &a);
	UINT_TO_RGBA (GtkFastMeter::rgb3, &r3, &g3, &b3, &a);

	int knee = (int)floor((float)height *0.996f );
	int y;

	for (y = 0; y < knee/2; y++)
	{
		r = (guint8)floor((float)abs(r1 - r0) * (float)y / (float)(knee/2));
		(r0 >= r1) ? r = r0 - r : r += r0;

		g = (guint8)floor((float)abs(g1 - g0) * (float)y / (float)(knee/2));
		(g0 >= g1) ? g = g0 - g : g += g0;

		b = (guint8)floor((float)abs(b1 - b0) * (float)y / (float)(knee/2));
		(b0 >= b1) ? b = b0 - b : b += b0;

		for (int x = 0; x < width; x++)
		{
			data[ (x+(height-y-1)*width) * 3 + 0 ] = r;
			data[ (x+(height-y-1)*width) * 3 + 1 ] = g;
			data[ (x+(height-y-1)*width) * 3 + 2 ] = b;
		}
	}


	int offset = knee - y;
	for (int i=0; i < offset; i++,y++)
	{

		r = (guint8)floor((float)abs(r2 - r1) * (float)i / (float)offset);
		(r1 >= r2) ? r = r1 - r : r += r1;

		g = (guint8)floor((float)abs(g2 - g1) * (float)i / (float)offset);
		(g1 >= g2) ? g = g1 - g : g += g1;

		b = (guint8)floor((float)abs(b2 - b1) * (float)i / (float)offset);
		(b1 >= b2) ? b = b1 - b : b += b1;

		for (int x = 0; x < width; x++)
		{
			data[ (x+(height-y-1)*width) * 3 + 0 ] = r;
			data[ (x+(height-y-1)*width) * 3 + 1 ] = g;
			data[ (x+(height-y-1)*width) * 3 + 2 ] = b;
		}
	}

	for (; y < height; y++)
	{
		for (int x = 0; x < width; x++) {
			data[ (x+(height-y-1)*width) * 3 + 0 ] = r3;
			data[ (x+(height-y-1)*width) * 3 + 1 ] = g3;
			data[ (x+(height-y-1)*width) * 3 + 2 ] = b3;
		}
	}

	ret = gdk_pixbuf_new_from_data(data, GDK_COLORSPACE_RGB, false, 8, width, height, width * 3, NULL, NULL);
	return ret;
}

/* ------ hold count ----- */
void gtk_fast_meter_set_hold_count(GtkFastMeter* fm, long val)
{
	if (val < 1) val = 1;

	fm->hold_cnt     = val;
	fm->hold_state   = 0;
	fm->current_peak = 0;

	gtk_widget_queue_draw(GTK_WIDGET(fm));
}

/* ------- on size request ------- */
void gtk_fast_meter_size_request (GtkWidget* wd, GtkRequisition* req)
{
	GtkFastMeter* fm = GTK_FAST_METER(wd);

	req->height = fm->request_height;
	req->height = max(req->height, GtkFastMeter::min_v_pixbuf_size);
	req->height = min(req->height, GtkFastMeter::max_v_pixbuf_size);

	req->width  = fm->request_width;
}

/* ------- on size allocate ------- */
void gtk_fast_meter_size_allocate (GtkWidget* wd, GtkAllocation* alloc)
{
	g_return_if_fail (wd != NULL);
	g_return_if_fail (GTK_IS_FAST_METER (wd));
	g_return_if_fail (alloc != NULL);

	GtkFastMeter* fm = GTK_FAST_METER(wd);

	if (alloc->width != fm->request_width)
		alloc->width = fm->request_width;

	int h = alloc->height;
	h = max(h, GtkFastMeter::min_v_pixbuf_size);
	h = min(h, GtkFastMeter::max_v_pixbuf_size);

	if (h != alloc->height)
		alloc->height = h;

	if (fm->pixheight != h)
		fm->pixbuf = request_vertical_meter(fm->request_width, h);

	fm->pixheight = gdk_pixbuf_get_height(fm->pixbuf);
	fm->pixwidth  = gdk_pixbuf_get_width (fm->pixbuf);

	wd->allocation = *alloc;

	if (GTK_WIDGET_REALIZED (wd))
		gdk_window_move_resize (wd->window,
		                        alloc->x, alloc->y, alloc->width, alloc->height);
}


/* ------- widget realize -------- */
void gtk_fast_meter_realize (GtkWidget* wd)
{

	g_return_if_fail (wd != NULL);
	g_return_if_fail (GTK_IS_FAST_METER (wd));

	GdkWindowAttr attributes;
	gint attributes_mask;

	GTK_WIDGET_SET_FLAGS (wd, GTK_REALIZED);

	attributes.x = wd->allocation.x;
	attributes.y = wd->allocation.y;
	attributes.width  = wd->allocation.width;
	attributes.height = wd->allocation.height;
	attributes.wclass = GDK_INPUT_OUTPUT;
	attributes.window_type = GDK_WINDOW_CHILD;
	attributes.event_mask = gtk_widget_get_events (wd) | GDK_EXPOSURE_MASK;
	attributes.visual = gtk_widget_get_visual (wd);

	attributes_mask = GDK_WA_X | GDK_WA_Y | GDK_WA_VISUAL;
	wd->window = gdk_window_new(wd->parent->window, &attributes, attributes_mask);
	wd->style  = gtk_style_attach (wd->style, wd->window);

	gdk_window_set_user_data (wd->window, wd);

	gtk_style_set_background (wd->style, wd->window, GTK_STATE_ACTIVE);
}

/* ------- expose event -------- */
gboolean gtk_fast_meter_expose_event (GtkWidget* wd, GdkEventExpose* ev)
{
	GtkFastMeter* fm = GTK_FAST_METER(wd);
	return vertical_expose (fm ,ev);
}

/* ------- setting meter level ----------- */
void gtk_fast_meter_set(GtkFastMeter* fm, float lvl)
{
	float old_level = fm->current_level;
	float old_peak  = fm->current_peak;

	fm->current_level = lvl;

	if (lvl > fm->current_peak)
	{
		fm->current_peak = lvl;
		fm->hold_state   = fm->hold_cnt;
	}

	if (fm->hold_state > 0)
		if (--fm->hold_state == 0)
			fm->current_peak = lvl;

	if (fm->current_level == old_level &&
	    fm->current_peak  == old_peak  &&
	    fm->hold_state == 0)
		return;

	GdkWindow* window = GTK_WIDGET(fm)->window;/*gtk_widget_get_window(GTK_WIDGET(fm));*/;
	if (window == 0)
	{
		gtk_widget_queue_draw(GTK_WIDGET(fm));
		return;
	}

	queue_vertical_redraw(fm, window, old_level);
}

/* ------------- clear fast meter object ------------ */
void gtk_fast_meter_clear(GtkFastMeter* fm)
{
	fm->current_level = 0;
	fm->current_peak  = 0;
	fm->hold_state    = 0;
	gtk_widget_queue_draw(GTK_WIDGET(fm));
}



/* -------------- */
void gtk_fast_meter_destroy(GtkObject* object)
{
	GtkFastMeter* fm;

	g_return_if_fail(object != NULL);
	g_return_if_fail(GTK_IS_FAST_METER (object));

	fm = GTK_FAST_METER(object);

	if (GTK_WIDGET(object)->parent &&
	    GTK_WIDGET_MAPPED(object))
		gtk_widget_unmap(GTK_WIDGET(object));

	if (GTK_OBJECT_CLASS(parent_class)->destroy)
		(*GTK_OBJECT_CLASS(parent_class)->destroy) (object);
}

/* ------------------------------ static functions ------------------------- */

/* ------- vertical expose event ----------- */
gboolean vertical_expose (GtkFastMeter* fm, GdkEventExpose* ev)
{
	gint         top_of_meter;
	GdkRectangle intersection;
	GdkRectangle background;

	top_of_meter = (gint) floor (fm->pixheight * fm->current_level);

	/* reset the height & origin of the rect that needs to show the pixbuf */

	fm->pixrect.height = top_of_meter;
	fm->pixrect.y = fm->pixheight - top_of_meter;

	background.x = 0;
	background.y = 0;
	background.width  = fm->pixrect.width;
	background.height = fm->pixheight - top_of_meter;

	if (gdk_rectangle_intersect (&background, &ev->area, &intersection))
	{
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

	if (gdk_rectangle_intersect(&fm->pixrect, &ev->area, &intersection))
	{
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

	if (fm->hold_state)
	{
		fm->last_peak_rect.x     = 0;
		fm->last_peak_rect.width = fm->pixwidth;
		fm->last_peak_rect.y     = fm->pixheight -
			(gint)floor(fm->pixheight * fm->current_peak);

		fm->last_peak_rect.height = min(3, fm->pixheight - fm->last_peak_rect.y);

		GdkWindow*   window = GTK_WIDGET(fm)->window;
		GtkStyle*    style  = gtk_widget_get_style (GTK_WIDGET(fm));

		gdk_draw_pixbuf(GDK_DRAWABLE(window),
		                style->fg_gc[GTK_WIDGET_STATE(GTK_WIDGET(fm))],
		                fm->pixbuf,
		                0, fm->last_peak_rect.y,
		                0, fm->last_peak_rect.y,
		                fm->pixwidth, fm->last_peak_rect.height,
		                GDK_RGB_DITHER_NONE, 0, 0);
	}
	else
	{
		fm->last_peak_rect.width  = 0;
		fm->last_peak_rect.height = 0;
	}

	return TRUE;
}

/* --------- vertical drawing queue ----------- */
void queue_vertical_redraw (GtkFastMeter* fm,
                            GdkWindow*    win,
                            float         old_level)
{
	GdkRectangle rect;

	gint new_top = (gint)floor(fm->pixheight * fm->current_level);

	rect.x      = 0;
	rect.width  = fm->pixwidth;
	rect.height = new_top;
	rect.y      = fm->pixheight - new_top;

	if (fm->current_level > old_level)
	{
		/* colored/pixbuf got larger, just draw the new section */
		/* rect.y stays where it is because of X coordinates */
		/* height of invalidated area is between new.y (smaller) and old.y
		   (larger).
		   X coordinates just make my brain hurt.
		*/
		rect.height = fm->pixrect.y - rect.y;
	}
	else
	{
		/* it got smaller, compute the difference */
		/* rect.y becomes old.y (the smaller value) */
		rect.y = fm->pixrect.y;
		/* rect.height is the old.y (smaller) minus the new.y (larger) */
		rect.height = fm->pixrect.height - rect.height;
	}


	GdkRegion* region = 0;
	bool queue = false;

	if (rect.height != 0)
	{
		/* ok, first region to draw ... */
		region = gdk_region_rectangle (&rect);
		queue = true;
	}

	/* redraw the last place where the last peak hold bar was;
	   the next expose will draw the new one whether its part of
	   expose region or not. */

	if (fm->last_peak_rect.width * fm->last_peak_rect.height != 0)
	{
		if (!queue)
		{
			region = gdk_region_new ();
			queue = true;
		}

		gdk_region_union_with_rect (region, &fm->last_peak_rect);
	}

	if (queue)
		gdk_window_invalidate_region (win, region, TRUE);

	// avoid mem leak
	if (region)
	{
		gdk_region_destroy(region);
		region = 0;
	}
}

/* -------------- */
/* EOF */


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
 *
 * --------------------------------------------------------------------------
 *
 * Class declaration for a level display
 *
 * (Code shamelessly stolen from Ardour by Paul Davis, thanks man!)
 *
 * --------------------------------------------------------------------------
 */

#ifndef __GTK_FAST_METER_H__
#define __GTK_FAST_METER_H__


#include <gdk/gdk.h>
#include <gtk/gtkdrawingarea.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define GTK_TYPE_FAST_METER            (gtk_fast_meter_get_type())
#define GTK_FAST_METER(obj)	       (G_TYPE_CHECK_INSTANCE_CAST((obj), GTK_TYPE_FAST_METER, GtkFastMeter))
#define GTK_IS_FAST_METER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj), GTK_TYPE_FAST_METER))
#define GTK_FAST_METER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass),  GTK_TYPE_FAST_METER, GtkFastMeterClass))
#define GTK_IS_FAST_METER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),  GTK_TYPE_FAST_METER))


	typedef struct _GtkFastMeter       GtkFastMeter;
	typedef struct _GtkFastMeterClass  GtkFastMeterClass;

	struct _GtkFastMeter
	{
		GtkWidget     widget;

		GdkPixbuf*    pixbuf;
		gint          pixheight;
		gint          pixwidth;

		GdkRectangle  pixrect;
		GdkRectangle  last_peak_rect;

		gint          request_width;
		gint          request_height;

		unsigned long hold_cnt;
		unsigned long hold_state;

		float         current_level;
		float         current_peak;
		float         current_user_level;

		static int    min_v_pixbuf_size;
		static int    max_v_pixbuf_size;
		static int    rgb0, rgb1, rgb2, rgb3;

	};

	struct _GtkFastMeterClass
	{
		GtkWidgetClass parent_class;
	};

	GType	   gtk_fast_meter_get_type    (void);

	/* --------- public exposed API ---------  */
	GtkWidget* gtk_fast_meter_new       (long,
	                                     unsigned long,
	                                     int,
	                                     int,
	                                     int,
	                                     int,
	                                     int);

	void  gtk_fast_meter_destroy	      (GtkObject*      object);

	void  gtk_fast_meter_set            (GtkFastMeter*, float);
	void  gtk_fast_meter_clear          (GtkFastMeter*);

	float gtk_fast_meter_get_level      (GtkFastMeter*);
	float gtk_fast_meter_get_user_level (GtkFastMeter*);
	float gtk_fast_meter_get_peak       (GtkFastMeter*);

	long  gtk_fast_meter_hold_count     (GtkFastMeter*);
	void  gtk_fast_meter_set_hold_count (GtkFastMeter*, long);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __GTK_FAST_METER_H__ */

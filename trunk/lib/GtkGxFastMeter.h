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

#ifndef __GTK_GX_FAST_METER_H__
#define __GTK_GX_FAST_METER_H__

#include <gtk/gtkdrawingarea.h>

G_BEGIN_DECLS

#define GTK_TYPE_GX_FAST_METER            (gtk_gx_fast_meter_get_type())
#define GTK_GX_FAST_METER(obj)	           (G_TYPE_CHECK_INSTANCE_CAST((obj), GTK_TYPE_GX_FAST_METER, GtkGxFastMeter))
#define GTK_IS_GX_FAST_METER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj), GTK_TYPE_GX_FAST_METER))
#define GTK_GX_FAST_METER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass),  GTK_TYPE_GX_FAST_METER, GtkGxFastMeterClass))
#define GTK_IS_GX_FAST_METER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),  GTK_TYPE_GX_FAST_METER))

typedef struct {
	GtkDrawingArea parent;

	GdkPixbuf*    pixbuf;
	gint          top_of_meter;
	GdkRectangle  last_peak_rect;

	unsigned long hold_cnt;
	unsigned long hold_state;

	float         current_level;
	float         current_peak;
	gint dimen, clr0, clr1, clr2, clr3;
} GtkGxFastMeter;

typedef struct {
	GtkDrawingAreaClass parent_class;
} GtkGxFastMeterClass;

GType gtk_gx_fast_meter_get_type(void);

/* --------- public exposed API ---------  */
GtkWidget* gtk_gx_fast_meter_new(long hold, gulong dimen, int clr0, int clr1, int clr2, int clr3);

void  gtk_gx_fast_meter_set            (GtkGxFastMeter* fastmeter, float lvl);
void  gtk_gx_fast_meter_clear          (GtkGxFastMeter* fastmeter);

void  gtk_gx_fast_meter_set_hold_count (GtkGxFastMeter* fastmeter, long val);

G_END_DECLS

#endif /* __GTK_GX_FAST_METER_H__ */

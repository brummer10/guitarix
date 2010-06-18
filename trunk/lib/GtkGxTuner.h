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

#ifndef __GTK_GX_TUNER_H__
#define __GTK_GX_TUNER_H__

#include <gtk/gtkdrawingarea.h>

G_BEGIN_DECLS

#define GTK_TYPE_GX_TUNER          (gtk_gx_tuner_get_type())
#define GTK_GX_TUNER(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_GX_TUNER, GtkGxTuner))
#define GTK_IS_GX_TUNER(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_GX_TUNER))
#define GTK_GX_TUNER_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass),  GTK_TYPE_GX_TUNER, GtkGxTunerClass))
#define GTK_IS_GX_TUNER_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GTK_TYPE_GX_TUNER))

typedef struct
{
	GtkDrawingArea parent;
	double GSEAL (freq);
} GtkGxTuner;

typedef struct
{
	GtkDrawingAreaClass parent_class;
	/*< private >*/
	cairo_surface_t *surface_tuner;
} GtkGxTunerClass;


GType gtk_gx_tuner_get_type();

void gtk_gx_tuner_set_freq(GtkGxTuner *tuner, double freq);
GtkWidget *gtk_gx_tuner_new(void);

G_END_DECLS

#endif /* __GTK_GX_TUNER_H__ */

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

#ifndef __GX_TUNER_H__
#define __GX_TUNER_H__

#include <gtk/gtkdrawingarea.h>
#include "compat2-12.h"

G_BEGIN_DECLS

#define GX_TYPE_TUNER          (gx_tuner_get_type())
#define GX_TUNER(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GX_TYPE_TUNER, GxTuner))
#define GX_IS_TUNER(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GX_TYPE_TUNER))
#define GX_TUNER_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass),  GX_TYPE_TUNER, GxTunerClass))
#define GX_IS_TUNER_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GX_TYPE_TUNER))

typedef struct _GxTuner GxTuner;
typedef struct _GxTunerClass GxTunerClass;

struct _GxTuner
{
	GtkDrawingArea parent;
	double GSEAL (freq);
};

struct _GxTunerClass
{
	GtkDrawingAreaClass parent_class;
	/*< private >*/
	cairo_surface_t *surface_tuner;
};


GType gx_tuner_get_type();

void gx_tuner_set_freq(GxTuner *tuner, double freq);
GtkWidget *gx_tuner_new(void);

G_END_DECLS

#endif /* __GX_TUNER_H__ */

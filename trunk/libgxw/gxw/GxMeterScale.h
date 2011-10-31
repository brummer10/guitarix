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

#ifndef __GX_METER_SCALE_H__
#define __GX_METER_SCALE_H__

#include <gtk/gtkwidget.h>
#include "compat2-12.h"

G_BEGIN_DECLS

#define GX_TYPE_METER_SCALE            (gx_meter_scale_get_type ())
#define GX_METER_SCALE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GX_TYPE_METER_SCALE, GxMeterScale))
#define GX_METER_SCALE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GX_TYPE_METER_SCALE, GxMeterScaleClass))
#define GX_IS_METER_SCALE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GX_TYPE_METER_SCALE))
#define GX_IS_METER_SCALE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GX_TYPE_METER_SCALE))
#define GX_METER_SCALE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GX_TYPE_METER_SCALE, GxMeterScaleClass))

typedef enum {
	GX_TICK_LEFT,
	GX_TICK_RIGHT,
	GX_TICK_BOTH,
	GX_TICK_BELOW
} GxTickPosition;

typedef struct _GxMeterScale GxMeterScale;
typedef struct _GxMeterScaleClass GxMeterScaleClass;
typedef struct _GxMeterScalePrivate GxMeterScalePrivate;

struct _GxMeterScale {
	GtkWidget parent;
	GxMeterScalePrivate *priv;
	GxTickPosition GSEAL (tick_pos);
};

struct _GxMeterScaleClass {
	GtkWidgetClass parent_class;
};

#define GX_TYPE_TICK_POSITION (gx_tick_position_get_type())

GType gx_meter_scale_get_type(void) G_GNUC_CONST;
GType gx_tick_position_get_type(void) G_GNUC_CONST;
GtkWidget *gx_meter_scale_new();
void gx_meter_scale_add_mark(GxMeterScale *meter_scale, gdouble value, const gchar *markup);
void gx_meter_scale_clear_marks(GxMeterScale *meter_scale);

G_END_DECLS

#endif /* __GX_METER_SCALE_H__ */

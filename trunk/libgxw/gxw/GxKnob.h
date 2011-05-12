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

#ifndef __GX_KNOB_H__
#define __GX_KNOB_H__


#include "GxRegler.h"

G_BEGIN_DECLS

#define GX_TYPE_KNOB          (gx_knob_get_type())
#define GX_KNOB(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GX_TYPE_KNOB, GxKnob))
#define GX_KNOB_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass),  GX_TYPE_KNOB, GxKnobClass))
#define GX_IS_KNOB(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GX_TYPE_KNOB))
#define GX_IS_KNOB_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GX_TYPE_KNOB))
#define GX_KNOB_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GX_TYPE_KNOB, GxKnobClass))

typedef struct _GxKnob GxKnob;
typedef struct _GxKnobClass GxKnobClass;
typedef struct _GxKnobPrivate GxKnobPrivate;

struct _GxKnob {
	GxRegler parent;
	GxKnobPrivate *priv;
};

struct _GxKnobClass {
	GxReglerClass parent_class;
	const gchar *stock_id;
};

GType gx_knob_get_type(void);

void _gx_knob_expose(GtkWidget *widget, GdkRectangle *image_rect, gdouble reglerstate,
                     GdkPixbuf *regler_image);
gboolean _gx_knob_pointer_event(GtkWidget *widget, gdouble x, gdouble y, const gchar *icon,
                                gboolean drag, int state, int button);
void _gx_knob_draw_arc(GtkWidget *widget, GdkRectangle *rect, gdouble reglerstate,
                       gboolean has_focus);
void _gx_knob_draw_indicator(GtkWidget *widget, GdkRectangle *image_rect, gdouble knobstate);
void gx_set_knob_jump_to_mouse(gboolean value);
gboolean gx_get_knob_jump_to_mouse();

G_END_DECLS

#endif /* __GX_KNOB_H__ */

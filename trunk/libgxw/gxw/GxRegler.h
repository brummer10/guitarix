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

/******************************************************************************
part of guitarix, use  knobs with Gtk
******************************************************************************/

#ifndef __GX_REGLER_H__
#define __GX_REGLER_H__


#include <gtk/gtkrange.h>
#include <gtk/gtklabel.h>

G_BEGIN_DECLS

#define GX_TYPE_REGLER          (gx_regler_get_type())
#define GX_REGLER(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GX_TYPE_REGLER, GxRegler))
#define GX_REGLER_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass),  GX_TYPE_REGLER, GxReglerClass))
#define GX_IS_REGLER(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GX_TYPE_REGLER))
#define GX_IS_REGLER_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GX_TYPE_REGLER))
#define GX_REGLER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GX_TYPE_REGLER, GxReglerClass))

typedef struct _GxRegler GxRegler;
typedef struct _GxReglerClass GxReglerClass;

struct _GxRegler
{
	GtkRange parent;
	gchar *GSEAL(var_id);
	GtkLabel *GSEAL(label);
	gboolean GSEAL(show_value):1;
	GtkPositionType GSEAL(value_position):2;
	gdouble GSEAL(value_xalign);
	PangoLayout *GSEAL(value_layout);
};

struct _GxReglerClass {
	GtkRangeClass parent_class;
	guint change_value_id;
	gboolean (*value_entry)(GxRegler *regler, GdkRectangle *rect, GdkEventButton *event);
};

GType gx_regler_get_type(void);
void _gx_regler_calc_size_request(GxRegler *regler, GtkRequisition *requisition);
gdouble _gx_regler_get_step_pos(GxRegler *regler, gint step);
void _gx_regler_get_positions(GxRegler *regler, GdkRectangle *image_rect,
                              GdkRectangle *value_rect);
void _gx_regler_display_value(GxRegler *regler, GdkRectangle *value_rect);
void _gx_regler_simple_display_value(GxRegler *regler, GdkRectangle *value_rect);
gboolean _approx_in_rectangle(gdouble x, gdouble y, GdkRectangle *rect);

void gx_regler_set_show_value(GxRegler *regler, gboolean value);
gboolean gx_regler_get_show_value(GxRegler *regler);
void gx_regler_set_value_position(GxRegler *regler, GtkPositionType pos);
GtkPositionType gx_regler_get_value_position(GxRegler *regler);
void gx_regler_set_label_ref(GxRegler *regler, GtkLabel* label);
GtkLabel *gx_regler_get_label_ref(GxRegler *regler);

G_END_DECLS

#endif /* __GX_REGLER_H__ */

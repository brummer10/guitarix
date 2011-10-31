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

#ifndef __GX_PAINT_BOX_H__
#define __GX_PAINT_BOX_H__

#include <gtk/gtkbox.h>

G_BEGIN_DECLS

#define GX_TYPE_PAINT_BOX            (gx_paint_box_get_type ())
#define GX_PAINT_BOX(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GX_TYPE_PAINT_BOX, GxPaintBox))
#define GX_PAINT_BOX_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GX_TYPE_PAINT_BOX, GxPaintBoxClass))
#define GX_IS_PAINT_BOX(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GX_TYPE_PAINT_BOX))
#define GX_IS_PAINT_BOX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GX_TYPE_PAINT_BOX))
#define GX_PAINT_BOX_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GX_TYPE_PAINT_BOX, GxPaintBoxClass))

typedef struct _GxPaintBox GxPaintBox;
typedef struct _GxPaintBoxClass GxPaintBoxClass;



struct _GxPaintBox {
	GtkBox box;

	gchar *paint_func;
	gboolean (*expose_func)(GtkWidget*, GdkEventExpose*);

	guint GSEAL (border_width) : 16;
	GList *GSEAL (children);
	gint16 GSEAL (spacing);
	guint GSEAL (homogeneous) : 1;
	guint GSEAL (icon_set) : 16;
	guint GSEAL (width) : 16;
	guint GSEAL (height) : 16;

};

struct _GxPaintBoxClass {
	GtkBoxClass parent_class;

	GdkPixbuf *gxh_image;
	GdkPixbuf *gxr_image;
	const gchar *stock_id;
	const gchar *main_image_id;
};


GType gx_paint_box_get_type(void) G_GNUC_CONST;
GtkWidget *gx_paint_box_new(gboolean homogeneous, gint spacing);

void gx_box_pack_start (GxPaintBox *box, GtkWidget *child,
	gboolean expand, gboolean fill, guint padding);
                                         
void gx_box_pack_end (GxPaintBox *box, GtkWidget *child,
	gboolean expand, gboolean fill, guint padding);

void gx_box_set_border_width (GxPaintBox *container, guint border_width);

void gx_box_add (GxPaintBox *container, GtkWidget *widget);

void gx_box_remove (GxPaintBox *container, GtkWidget *widget);

GList*   gx_box_get_children(GxPaintBox *container);



G_END_DECLS

#endif /* __GX_PAINT_BOX_H__ */

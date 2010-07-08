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

typedef enum {
	GX_REGLER_TYPE_SMALL_KNOB,
	GX_REGLER_TYPE_BIG_KNOB,
	GX_REGLER_TYPE_HSLIDER,
	GX_REGLER_TYPE_MINI_SLIDER,
	GX_REGLER_TYPE_WHEEL,
	GX_REGLER_TYPE_VSLIDER,
	GX_REGLER_TYPE_EQ_SLIDER,
} GxReglerType;

#define GX_REGLER_TYPE_COUNT (7)

typedef struct
{
	GtkRange parent;
	int GSEAL(regler_type);
	gchar *GSEAL(var_id);
	GtkLabel *GSEAL(label);
	gboolean GSEAL(show_value):1;
	GtkPositionType GSEAL(value_position):2;
	PangoLayout *GSEAL(value_layout);
} GxRegler;

typedef struct {
	GtkRangeClass parent_class;
	GdkPixbuf *regler_image;
	GdkPixbuf *bigregler_image;
	GdkPixbuf *slider_image;
	GdkPixbuf *slider_image1;
	GdkPixbuf *vslider_image;
	GdkPixbuf *vslider_image1;
	GdkPixbuf *minislider_image;
	GdkPixbuf *minislider_image1;
	GdkPixbuf *eqslider_image;
	GdkPixbuf *eqslider_image1;
	GdkPixbuf *wheel_image;
	GdkPixbuf *wheel_image1;
	GdkPixbuf *pointer_image1;
	gint current_theme;
} GxReglerClass;

GType regler_type_get_type(void) G_GNUC_CONST;
#define GX_TYPE_REGLER_TYPE (regler_type_get_type())

GType gx_regler_get_type(void);
gchar *gx_regler_get_var(GxRegler* regler);

void _gx_regler_calc_size_request(GxRegler *regler, GtkRequisition *requisition);
gdouble _gx_regler_get_step_pos(GxRegler *regler, gint step);
void _gx_regler_get_positions(GxRegler *regler, GdkRectangle *image_rect,
                              GdkRectangle *value_rect);
void _gx_regler_display_value(GxRegler *regler, GdkRectangle *value_rect);
double _gx_regler_get_value(GtkAdjustment *adj,double pos);

/*
GtkWidget *gtk_regler_new_with_adjustment(GtkAdjustment *_adjustment);
GtkWidget *gtk_big_regler_new_with_adjustment(GtkAdjustment *_adjustment);
GtkWidget *gtk_hslider_new_with_adjustment(GtkAdjustment *_adjustment);
GtkWidget *gtk_vslider_new_with_adjustment(GtkAdjustment *_adjustment);
GtkWidget *gtk_mini_slider_new_with_adjustment(GtkAdjustment *_adjustment);
GtkWidget *gtk_eq_slider_new_with_adjustment(GtkAdjustment *_adjustment);
GtkWidget *gtk_wheel_new_with_adjustment(GtkAdjustment *_adjustment);
*/

G_END_DECLS

#endif /* __GX_REGLER_H__ */

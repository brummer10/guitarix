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

#ifndef __GX_IR_EDIT_H__
#define __GX_IR_EDIT_H__


#include <gtk/gtkdrawingarea.h>

G_BEGIN_DECLS

#define GX_TYPE_IR_EDIT          (gx_ir_edit_get_type())
#define GX_IR_EDIT(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GX_TYPE_IR_EDIT, GxIREdit))
#define GX_IR_EDIT_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass),  GX_TYPE_IR_EDIT, GxIREditClass))
#define GX_IS_IR_EDIT(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GX_TYPE_IR_EDIT))
#define GX_IS_IR_EDIT_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GX_TYPE_IR_EDIT))
#define GX_IR_EDIT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GX_TYPE_IR_EDIT, GxIREditClass))

typedef struct {
	int i;
	double g;
} gain_points;

struct _GxIREdit;

typedef void (*cairo_paint_function)(struct _GxIREdit*,cairo_t*,GdkEventExpose*);

typedef struct _GxIREdit
{
	GtkDrawingArea parent;
	// wave file
	float *odata;
	gint odata_len;
	gint fs;
	gchar *enc;
	gchar *filename;
	// display configuration
	gint width;
	gint height;
	gint text_width;
	gint text_height;
	gdouble label_width;
	gchar *no_data_text;
	// drawing area
	gint x_off;
	gint y_off;
	gint graph_x;
	gint graph_y;
	gdouble scale_height;
	// mouse interface state variables
	gint button;
	gint mode;
	gint mode_arg;
	gint mode_arg2;
	GdkCursor *cursor[6]; //FIXME
	GdkPixmap *surface;
	gint scale_num;
	// coordinate axes
	gint y_border_top;
	gint y_border_bottom;
	gint x_border;
	gdouble label_sep;
	gdouble dot_diameter;
	gdouble segment_distance;
	gdouble limit;
	gdouble min_y;
	gdouble max_y;
	gint y_lines;
	const gchar *fmt_y;
	gchar *fmt;
	gdouble tick;
	gdouble scale_a[2];
	gdouble min_scale;
	gdouble max_scale_fact;
	gdouble scale;
	// intermediate data representation
	float *data; // odata_len samples
	float *bdata;
	gint bdata_len;
	cairo_paint_function locked;
	gboolean buffered;
	// output parameters
	gint cutoff_low;
	gint cutoff_high;
	gdouble offset;
	gain_points *gains;
	gint gains_len;
	// presentation parameters
	gint chan;
	gint current_offset;
	gboolean linear;
	gint scroll_center;
} GxIREdit;

typedef struct {
	GtkDrawingAreaClass parent_class;
} GxIREditClass;

GType gx_ir_edit_get_type(void);
void gx_ir_edit_set_ir_data(GxIREdit *ir_edit, float *data, int chan, int len, int samplerate);


G_END_DECLS

#endif /* __GX_IR_EDIT_H__ */

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

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#include "GxRegler.h"
#include "GxControlParameter.h"
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <gtk/gtkprivate.h>

#define P_(s) (s)   // FIXME -> gettext

/****************************************************************
 ** GxRegler
 */

#define GX_REGLER_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), GX_TYPE_REGLER, GxReglerPrivate))

typedef struct
{
	gint last_quadrant;
	gint decimals;
	gint current_theme;
	GtkRequisition value_req;
} GxReglerPrivate;

enum {
	PROP_TYPE = 1,
	PROP_VAR_ID,
	PROP_SHOW_VALUE,
	PROP_SHOW_LABEL,
	PROP_LABEL_FROM_VAR,
	PROP_LABEL_TEXT,
	PROP_LABEL_POSITION,
};

static void gx_regler_class_init(GxReglerClass *klass);
static void gx_regler_init(GxRegler *regler);
static void gx_control_parameter_interface_init (GxControlParameterIface *iface);
static void gx_regler_base_class_finalize(GxReglerClass *klass);
static void gx_regler_finalize(GObject*);
static void gx_regler_init_pixmaps(GxReglerClass *klass);
static void gx_regler_style_set (GtkWidget *widget, GtkStyle  *previous_style);
static void gx_regler_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gx_regler_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static gboolean gx_regler_enter_in (GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_regler_leave_out (GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_regler_expose (GtkWidget *widget, GdkEventExpose *event);
static void gx_regler_size_request (GtkWidget *widget, GtkRequisition *requisition);
static gboolean gx_regler_button_press (GtkWidget *widget, GdkEventButton *event);
static gboolean gx_regler_button_release (GtkWidget *widget, GdkEventButton *event);
static gboolean gx_regler_pointer_motion (GtkWidget *widget, GdkEventMotion *event);
static gboolean gx_regler_key_press (GtkWidget *widget, GdkEventKey *event);
static gboolean gx_regler_scroll (GtkWidget *widget, GdkEventScroll *event);

static gpointer gx_regler_parent_class = NULL;

GType gx_regler_get_type(void)
{
	static GType regler_type = 0;

	if (!regler_type) {
		const GTypeInfo regler_info = {
			sizeof (GxReglerClass),
			NULL,				/* base_class_init */
			(GBaseFinalizeFunc) gx_regler_base_class_finalize,
			(GClassInitFunc) gx_regler_class_init,
			NULL,				/* class_finalize */
			NULL,				/* class_data */
			sizeof (GxRegler),
			0,					/* n_preallocs */
			(GInstanceInitFunc) gx_regler_init,
			NULL,				/* value_table */
		};
		regler_type = g_type_register_static(
			GTK_TYPE_RANGE, "GxRegler", &regler_info, (GTypeFlags)0);
		static const GInterfaceInfo g_implement_interface_info = {
			(GInterfaceInitFunc)gx_control_parameter_interface_init
		};
        g_type_add_interface_static(regler_type, GX_TYPE_CONTROL_PARAMETER, &g_implement_interface_info);
	}
	return regler_type;
}


GType regler_type_get_type(void)
{
	static GType etype = 0;
	if (G_UNLIKELY(etype == 0)) {
		static const GEnumValue values[] = {
			{ GX_REGLER_TYPE_SMALL_KNOB, "REGLER_TYPE_SMALL_KNOB", "small knob" },
			{ GX_REGLER_TYPE_BIG_KNOB, "REGLER_TYPE_BIG_KNOB", "big knob" },
			{ GX_REGLER_TYPE_HSLIDER, "REGLER_TYPE_HSLIDER", "horizontal slider" },
			{ GX_REGLER_TYPE_MINI_SLIDER, "REGLER_TYPE_MINI_SLIDER", "mini slider" },
			{ GX_REGLER_TYPE_WHEEL, "REGLER_TYPE_WHEEL", "wheel" },
			{ GX_REGLER_TYPE_VSLIDER, "REGLER_TYPE_VSLIDER", "vslider" },
			{ GX_REGLER_TYPE_EQ_SLIDER, "REGLER_TYPE_EQ_SLIDER", "eq slider" },
			{ 0, NULL, NULL }
		};
		etype = g_enum_register_static (g_intern_static_string ("GxReglerType"), values);
	}
	return etype;
}

static void gx_regler_set_label(GxRegler *self, const gchar *text)
{
	g_free(self->label);
	self->label = g_strdup(text);
	if (self->label_layout) {
		pango_layout_set_text(self->label_layout, self->label, -1);
	}
	gtk_widget_queue_resize(GTK_WIDGET(self));
	g_object_notify(G_OBJECT(self), "label-text");
}

static void
gx_regler_cp_configure(GxControlParameter *self, gchar* group, gchar *name, gdouble lower, gdouble upper, gdouble step)
{
	gx_regler_set_label(GX_REGLER(self), name);
}

static gdouble
gx_regler_cp_get_value(GxControlParameter *self)
{
	return gtk_range_get_value(GTK_RANGE(self));
}

static void
gx_regler_cp_set_value(GxControlParameter *self, gdouble value)
{
	gtk_range_set_value(GTK_RANGE(self), value);
}

static void
gx_control_parameter_interface_init(GxControlParameterIface *iface)
{
  iface->cp_configure = gx_regler_cp_configure;
  iface->cp_set_value = gx_regler_cp_set_value;
  iface->cp_get_value = gx_regler_cp_get_value;
}

static void gx_regler_class_init(GxReglerClass *klass)
{
	GObjectClass   *gobject_class = G_OBJECT_CLASS(klass);
	GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;
	gx_regler_parent_class = g_type_class_peek_parent(klass);
	gobject_class->finalize = gx_regler_finalize;
	gobject_class->set_property = gx_regler_set_property;
	gobject_class->get_property = gx_regler_get_property;

	widget_class->style_set = gx_regler_style_set;
	widget_class->enter_notify_event = gx_regler_enter_in;
	widget_class->leave_notify_event = gx_regler_leave_out;
	widget_class->expose_event = gx_regler_expose;
	widget_class->size_request = gx_regler_size_request;
	widget_class->button_press_event = gx_regler_button_press;
	widget_class->button_release_event = gx_regler_button_release;
	widget_class->motion_notify_event = gx_regler_pointer_motion;
	widget_class->key_press_event = gx_regler_key_press;
	widget_class->scroll_event = gx_regler_scroll;

	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("image-theme-number",P_("image theme number"),
		                 P_("Number of image theme"),
		                 0, 5, 0, GParamFlags(GTK_PARAM_READABLE)));
	g_object_class_install_property(
		gobject_class, PROP_TYPE,
		g_param_spec_enum("regler-type",
		                  P_("Type"),
		                  P_("The type of the control"),
		                  regler_type_get_type(),
		                  GX_REGLER_TYPE_SMALL_KNOB,
		                  GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property(
		gobject_class, PROP_SHOW_VALUE,
		g_param_spec_boolean("show-value",
		                     P_("show value"),
		                     P_("display the value"),
		                     TRUE,
		                     GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property(
		gobject_class, PROP_SHOW_LABEL,
		g_param_spec_boolean("show-label",
		                     P_("show label"),
		                     P_("display a label"),
		                     TRUE,
		                     GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property(
		gobject_class, PROP_LABEL_FROM_VAR,
		g_param_spec_boolean("label-from-var",
		                     P_("label from variable"),
		                     P_("label will be set to the name of the variable"),
		                     TRUE,
		                     GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property(
		gobject_class, PROP_LABEL_TEXT,
		g_param_spec_string("label-text",
		                    P_("Label Text"),
		                    P_("The text of the label"),
		                    "",
		                    GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property(
		gobject_class, PROP_LABEL_POSITION,
		g_param_spec_enum("label-position",
		                  P_("Label Position"),
		                  P_("The position of the label"),
		                  GTK_TYPE_POSITION_TYPE,
		                  GTK_POS_TOP,
		                  GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_override_property(gobject_class, PROP_VAR_ID, "var-id");

	g_type_class_add_private(klass, sizeof (GxReglerPrivate));
	klass->current_theme = -1;
	gx_regler_init_pixmaps(klass);
}

static void gx_regler_base_class_finalize(GxReglerClass *klass)
{
#define IMAGE_UNREF(image) if (G_IS_OBJECT(klass->image)) g_object_unref(klass->image)
	IMAGE_UNREF(bigregler_image);
	IMAGE_UNREF(regler_image);
	IMAGE_UNREF(slider_image);
	IMAGE_UNREF(slider_image1);
	IMAGE_UNREF(vslider_image);
	IMAGE_UNREF(vslider_image1);
	IMAGE_UNREF(minislider_image);
	IMAGE_UNREF(minislider_image1);
	IMAGE_UNREF(eqslider_image);
	IMAGE_UNREF(eqslider_image1);
	IMAGE_UNREF(wheel_image);
	IMAGE_UNREF(wheel_image1);
	IMAGE_UNREF(pointer_image1);
#undef IMAGE_UNREF
}

static void gx_regler_finalize(GObject *object)
{
	GxRegler *regler = GX_REGLER(object);
	g_free(regler->label);
	g_free(regler->var_id);
	if (regler->label_layout) {
		g_object_unref(regler->label_layout);
	}
	if (regler->value_layout) {
		g_object_unref(regler->value_layout);
	}
	G_OBJECT_CLASS(gx_regler_parent_class)->finalize(object);
}

/****************************************************************
 ** Constants
 */

static const struct {
	gint width;
	gint height;
	gint step;
} base_size[] = {
	{ 25, 25, 1 },				// GX_REGLER_TYPE_SMALL_KNOB
	{ 51, 51, 1 },				// GX_REGLER_TYPE_BIG_KNOB
	{ 120, 10, 100 },			// GX_REGLER_TYPE_HSLIDER
	{ 34, 6, 28 },				// GX_REGLER_TYPE_MINI_SLIDER
	{ 40, 8, 100 },				// GX_REGLER_TYPE_WHEEL
	{ 10, 70, 50 },				// GX_REGLER_TYPE_VSLIDER
	{ 13, 55, 50 },				// GX_REGLER_TYPE_EQ_SLIDER
};

/****************************************************************
 ** calculate the knop pointer with dead zone
 */

static void gx_regler_ensure_layout(GxRegler *regler)
{
	if (regler->show_label && !regler->label_layout) {
		regler->label_layout = gtk_widget_create_pango_layout(GTK_WIDGET(regler), regler->label);
		pango_layout_set_font_description(
			regler->label_layout, pango_font_description_from_string("Sans 8"));
	}
	if (regler->show_value && !regler->value_layout) {
		regler->value_layout = gtk_widget_create_pango_layout(GTK_WIDGET(regler), NULL);
		pango_layout_set_font_description(
			regler->value_layout, pango_font_description_from_string("Sans 8"));
	}
}

static const double scale_zero = 20 * (M_PI/180); // defines "dead zone" for knobs

//------------ calculate needed precision
static int precision(GtkAdjustment *adj)
{
	gdouble n = gtk_adjustment_get_step_increment(adj);
	if (n < 0.009999) {
		return 3;
	} else if (n < 0.099999) {
		return 2;
	} else if (n < 0.999999) {
		return 1;
	} else {
		return 0;
	}
}

#ifndef min
#define min(x, y) ((x) < (y) ? (x) : (y))
#endif
#ifndef max
#define max(x, y) ((x) < (y) ? (y) : (x))
#endif

static gdouble get_positions(GtkWidget *widget, GdkRectangle *image_rect,
                             GdkRectangle *value_rect, GdkPoint *text_pos)
{
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	GxRegler *regler = GX_REGLER(widget);
	gint text_width = 0;
	gint text_height = 0;
	gint x = widget->allocation.x;
	gint y = widget->allocation.y;
	if (regler->show_label) {
		PangoRectangle logical_rect;
		gx_regler_ensure_layout(regler);
		pango_layout_get_pixel_extents(regler->label_layout, NULL, &logical_rect);
		text_width = logical_rect.width;
		text_height = logical_rect.height;
	}
	if (regler->show_value) {
		GxReglerPrivate *priv = GX_REGLER_GET_PRIVATE(regler);
		value_rect->width = priv->value_req.width;
		value_rect->height = priv->value_req.height;
	} else {
		value_rect->width = value_rect->height = 0;
	}
	gint width = image_rect->width = base_size[regler->regler_type].width;
	image_rect->height = base_size[regler->regler_type].height;
	gint height =  image_rect->height + value_rect->height;
	switch (regler->label_position) {
	case GTK_POS_LEFT:
		text_pos->x = x + (widget->allocation.width - width - text_width) / 2;
		text_pos->y = y + (widget->allocation.height - text_height) / 2;
		image_rect->x = x + (widget->allocation.width - width + text_width) / 2;
		image_rect->y = y + (widget->allocation.height - height) / 2;
		break;
	case GTK_POS_RIGHT:
		text_pos->x = x + (widget->allocation.width + width - text_width) / 2;
		text_pos->y = y + (widget->allocation.height - text_height) / 2;
		image_rect->x = x + (widget->allocation.width - width - text_width) / 2;
		image_rect->y = y + (widget->allocation.height - height) / 2;
		break;
	case GTK_POS_TOP:
		text_pos->x = x + (widget->allocation.width - text_width) / 2;
		text_pos->y = y + (widget->allocation.height - height - text_height) / 2;
		image_rect->x = x + (widget->allocation.width - width) / 2;
		image_rect->y = y + (widget->allocation.height - height + text_height) / 2;
		break;
	case GTK_POS_BOTTOM:
		text_pos->x = x + (widget->allocation.width - text_width) / 2;
		text_pos->y = y + (widget->allocation.height + height - text_height) / 2;
		image_rect->x = x + (widget->allocation.width - width) / 2;
		image_rect->y = y + (widget->allocation.height - height - text_height) / 2;
		break;
	}
	value_rect->x = image_rect->x + (image_rect->width - value_rect->width) / 2;
	value_rect->y = image_rect->y + image_rect->height;
	double df = adj->upper - adj->lower;
	if (df == 0.0) {
		return 0.0;
	} else {
		return (adj->value - adj->lower) * base_size[regler->regler_type].step / df;
	}
}

static void display_value(GtkWidget *widget, GdkRectangle *rect)
{
	if (!GX_REGLER(widget)->show_value) {
		return;
	}
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	char s[64];
	snprintf(s, sizeof(s), "%.*f", precision(adj), gtk_adjustment_get_value(adj));

	cairo_t *cr = gdk_cairo_create(widget->window);
	double x0 = rect->x + 1;
	double y0 = rect->y + 1;
	double rect_width  =  rect->width - 2;
	double rect_height =  rect->height - 2;

    cairo_rectangle (cr, x0-1,y0-1,rect_width+2,rect_height+2);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_fill (cr);

    cairo_pattern_t*pat =
	    cairo_pattern_create_radial (-50, y0, 5,rect_width-10,  rect_height, 20.0);
    cairo_pattern_add_color_stop_rgba (pat, 1, 0., 0., 0., 0.8);
    cairo_pattern_add_color_stop_rgba (pat, 0, 0, 0, 0, 0.4);
    cairo_set_source (cr, pat);
    cairo_rectangle (cr, x0+2,y0+2,rect_width-4,rect_height-4);
    cairo_fill (cr);

    cairo_set_source_rgb(cr,  0.2, 0.2, 0.2);
    cairo_set_line_width(cr, 2.0);
    cairo_move_to(cr,x0+rect_width-3, y0+3);
    cairo_line_to(cr, x0+rect_width-3, y0+rect_height-2);
    cairo_line_to(cr, x0+2, y0+rect_height-2);
    cairo_stroke(cr);

    cairo_set_source_rgb(cr,  0.1, 0.1, 0.1);
    cairo_set_line_width(cr, 2.0);
    cairo_move_to(cr,x0+3, y0+rect_height-1);
    cairo_line_to(cr, x0+3, y0+3);
    cairo_line_to(cr, x0+rect_width-3, y0+3);
    cairo_stroke(cr);

    cairo_set_source_rgba (cr, 0.4, 1, 0.2, 0.8);
    PangoLayout *l = GX_REGLER(widget)->value_layout;
    pango_layout_set_text(l, s, -1);
    PangoRectangle logical_rect;
    pango_layout_get_pixel_extents(l, NULL, &logical_rect);
    cairo_move_to (cr, x0-1+(rect->width - logical_rect.width)/2, y0+3);
    pango_cairo_show_layout(cr, l);

	cairo_destroy(cr);
}

static void knob_draw_arc(GtkWidget *widget, GdkRectangle *rect, gdouble reglerstate, int arc_offset, gboolean has_focus)
{
	GdkGC *line = gdk_gc_new(GDK_DRAWABLE(widget->window));
	GdkColor color;
	if (has_focus) {
		// linear color change in RGB space from (52480, 0, 5120) to (8448, 46004, 5120)
		color.red = 52480 - (int)(44032 * reglerstate);
		color.green = (int)(46004 * reglerstate);
		color.blue = 5120;
	} else {
		color.red = 5120;
		color.green = 742;
		color.blue = 52480;
	}
	gdk_gc_set_rgb_fg_color(line, &color);
	gdk_gc_set_line_attributes(line, 1,GDK_LINE_SOLID,GDK_CAP_BUTT,GDK_JOIN_ROUND);
	gdk_draw_arc(GDK_DRAWABLE(widget->window), line, FALSE,
	             rect->x+arc_offset, rect->y+arc_offset,
	             rect->width-1-2*arc_offset, rect->height-1-2*arc_offset,-90*64,360*64);
	g_object_unref(line);
}

static void knob_expose(GtkWidget *widget, GdkRectangle *image_rect, gdouble reglerstate,
                        GdkPixbuf *regler_image, int arc_offset)
{
	double angle = scale_zero + reglerstate * 2 * (M_PI - scale_zero);
	const double pointer_off = 5;
	double radius = min(image_rect->width-pointer_off, image_rect->height-pointer_off) / 2;
	double lengh_x = (image_rect->x+radius+pointer_off/2) - radius * sin(angle);
	double lengh_y = (image_rect->y+radius+pointer_off/2) + radius * cos(angle);
	double radius1 = min(image_rect->width, image_rect->height) / 2;
	int has_focus = GTK_WIDGET_HAS_FOCUS(widget);

	if (has_focus) {
		gtk_paint_focus(widget->style, widget->window, GTK_STATE_NORMAL, NULL, widget, NULL,
		                image_rect->x, image_rect->y, image_rect->width, image_rect->height);
	}
	gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
	                regler_image, 0,0, image_rect->x, image_rect->y,
	                image_rect->width, image_rect->height, GDK_RGB_DITHER_NORMAL, 0, 0);

	/** this is to create a pointer rotating on the knob with painting funktions **/
	cairo_t *cr = gdk_cairo_create(GDK_DRAWABLE(widget->window));
	cairo_set_source_rgb(cr,  0.1, 0.1, 0.1);
	cairo_set_line_width(cr, 5.0);
	cairo_move_to(cr, image_rect->x+radius1, image_rect->y+radius1);
	cairo_line_to(cr,lengh_x,lengh_y);
	cairo_stroke(cr);
	cairo_set_source_rgb(cr,  0.9, 0.9, 0.9);
	cairo_set_line_width(cr, 1.0);
	cairo_move_to(cr, image_rect->x+radius1, image_rect->y+radius1);
	cairo_line_to(cr,lengh_x,lengh_y);
	cairo_stroke(cr);
	cairo_destroy(cr);

	knob_draw_arc(widget, image_rect, reglerstate, arc_offset, has_focus);
}

static void hslider_expose(
	GtkWidget *widget, GdkRectangle *rect, gdouble reglerstate, GdkPixbuf *image,
	GdkPixbuf *image1, gint w, gdouble sat, gboolean has_focus, gboolean paint_focus)
{
	gdk_pixbuf_copy_area(image, 0, 0, rect->width, rect->height, image1, 0, 0);
	gdk_pixbuf_copy_area(image, rect->width, 0, w, rect->height, image1, reglerstate, 0);
	if (has_focus) {
		gdk_pixbuf_saturate_and_pixelate(image1, image1, sat, FALSE);
		if (paint_focus) {
			gtk_paint_focus(widget->style, widget->window, GTK_STATE_NORMAL, NULL, widget, NULL,
			                rect->x, rect->y, rect->width, rect->height);
		}
	}
	gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
	                image1, 0, 0, rect->x, rect->y,
	                rect->width, rect->height, GDK_RGB_DITHER_NORMAL, 0, 0);
}

static void vslider_expose(GtkWidget *widget, GdkRectangle *rect, gdouble reglerstate,
                           gboolean has_focus, gboolean paint_focus)
{
	GxReglerClass *klass =  GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget));
	gdk_pixbuf_copy_area(klass->vslider_image,0,20, rect->width, rect->height,
	                     klass->vslider_image1,0,0);
	gdk_pixbuf_copy_area(klass->vslider_image,0,0,rect->width,20,
	                     klass->vslider_image1,0,50-reglerstate);
	if (has_focus) {
		if (paint_focus) {
			gtk_paint_focus(widget->style, widget->window, GTK_STATE_NORMAL, NULL, widget, NULL,
			                rect->x, rect->y, rect->width, rect->height);
		}
		gdk_pixbuf_saturate_and_pixelate(klass->vslider_image1,
		                                 klass->vslider_image1,70.0,FALSE);
	}
	gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
	                klass->vslider_image1, 0, 0, rect->x, rect->y,
	                rect->width, rect->height, GDK_RGB_DITHER_NORMAL, 0, 0);
}

static void eq_slider_expose(GtkWidget *widget, GdkRectangle *rect, gdouble reglerstate)
{
	GxReglerClass *klass =  GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget));
	gdk_pixbuf_copy_area(klass->eqslider_image,0,reglerstate+8,
	                     rect->width, rect->height,
	                     klass->eqslider_image1,0,0);
	gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->eqslider_image1, 0, 0, rect->x, rect->y,
		                rect->width, rect->height, GDK_RGB_DITHER_NORMAL, 0, 0);
}

static void wheel_expose(GtkWidget *widget, GdkRectangle *rect, gdouble reglerstate)
{
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	GxReglerClass *klass =  GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget));
	int smoth_pointer = 0;
	if (reglerstate > (adj->upper - adj->lower)) {
		smoth_pointer = -4;
	}
	gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
	                klass->wheel_image1, 0, 0, rect->x, rect->y,
	                rect->width, rect->height, GDK_RGB_DITHER_NORMAL, 0, 0);
	gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
	                klass->wheel_image, reglerstate + rect->width, 0,
	                rect->x, rect->y, rect->width, rect->height, GDK_RGB_DITHER_NORMAL, 0, 0);
	gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
	                klass->pointer_image1,0, 0, rect->x+smoth_pointer+reglerstate*0.4,
	                rect->y, 2, rect->height, GDK_RGB_DITHER_NORMAL, 0, 0);
}

/****************************************************************
 ** general expose events for all "regler" controllers
 */

static gboolean gx_regler_expose (GtkWidget *widget, GdkEventExpose *event)
{
	g_assert(GX_IS_REGLER(widget));
	GxReglerClass *klass =  GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget));
	GdkRectangle image_rect, value_rect;
	GdkPoint text_pos;
	gdouble reglerstate = get_positions(widget, &image_rect, &value_rect, &text_pos);

	switch (GX_REGLER(widget)->regler_type) {
	case GX_REGLER_TYPE_SMALL_KNOB:
		knob_expose(widget, &image_rect, reglerstate, klass->regler_image, 0);
		break;
	case GX_REGLER_TYPE_BIG_KNOB:
		knob_expose(widget, &image_rect, reglerstate, klass->bigregler_image, 2);
		break;
	case GX_REGLER_TYPE_HSLIDER:
		hslider_expose(
			widget, &image_rect, reglerstate, klass->slider_image,
			klass->slider_image1, 20, 70.0, GTK_WIDGET_HAS_FOCUS(widget), TRUE);
		break;
	case GX_REGLER_TYPE_MINI_SLIDER:
		hslider_expose(
			widget, &image_rect, reglerstate, klass->minislider_image,
			klass->minislider_image1, 6, 99.0, GTK_WIDGET_HAS_FOCUS(widget), FALSE);
		break;
	case GX_REGLER_TYPE_WHEEL:
		wheel_expose(widget, &image_rect, reglerstate);
		break;
	case GX_REGLER_TYPE_VSLIDER:
		vslider_expose(widget, &image_rect, reglerstate, GTK_WIDGET_HAS_FOCUS(widget), TRUE);
		break;
	case GX_REGLER_TYPE_EQ_SLIDER:
		eq_slider_expose(widget, &image_rect, reglerstate);
		break;
	default:
		g_assert(FALSE);
	}
	display_value(widget, &value_rect);
	if (GX_REGLER(widget)->show_label) {
		gtk_paint_layout(
			widget->style, widget->window, gtk_widget_get_state(widget), FALSE, &event->area,
			widget, "label", text_pos.x, text_pos.y, GX_REGLER(widget)->label_layout);
	}
	return TRUE;
}

/****************************************************************
 ** redraw when leave
 */

static gboolean gx_regler_leave_out (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_REGLER(widget));
	GxReglerClass *klass =  GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget));
	GdkRectangle image_rect;
	GdkRectangle value_rect;
	GdkPoint text_pos;
	gdouble reglerstate = get_positions(widget, &image_rect, &value_rect, &text_pos);

	switch (GX_REGLER(widget)->regler_type) {
	case GX_REGLER_TYPE_SMALL_KNOB:
		if (GTK_WIDGET_HAS_GRAB(widget) || GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
			return TRUE;
		}
		knob_draw_arc(widget, &image_rect, reglerstate, 0, FALSE);
		break;
	case GX_REGLER_TYPE_BIG_KNOB:
		if (GTK_WIDGET_HAS_GRAB(widget) || GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
			return TRUE;
		}
		knob_draw_arc(widget, &image_rect, reglerstate, 2, FALSE);
		break;
	case GX_REGLER_TYPE_HSLIDER:
		hslider_expose(widget, &image_rect, reglerstate, klass->slider_image,
		               klass->slider_image1, 20, 70.0, FALSE, FALSE);
		break;
	case GX_REGLER_TYPE_MINI_SLIDER:
		hslider_expose(widget, &image_rect, reglerstate, klass->minislider_image,
		               klass->minislider_image1, 6, 99.0, FALSE, FALSE);
		break;
	case GX_REGLER_TYPE_VSLIDER:
		vslider_expose(widget, &image_rect, reglerstate, FALSE, FALSE);
		break;
	}
	return TRUE;
}

/****************************************************************
 ** redraw when enter
 */

static gboolean gx_regler_enter_in (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_REGLER(widget));
	GxReglerClass *klass =  GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget));
	GdkRectangle image_rect;
	GdkRectangle value_rect;
	GdkPoint text_pos;
	gdouble reglerstate = get_positions(widget, &image_rect, &value_rect, &text_pos);

	switch (GX_REGLER(widget)->regler_type) {
	case GX_REGLER_TYPE_SMALL_KNOB:
		knob_draw_arc(widget, &image_rect, reglerstate, 0, TRUE);
		break;
	case GX_REGLER_TYPE_BIG_KNOB:
		if (GTK_WIDGET_HAS_GRAB(widget) || GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
			return TRUE;
		}
		knob_draw_arc(widget, &image_rect, reglerstate, 2, TRUE);
		break;
	case GX_REGLER_TYPE_HSLIDER:
		hslider_expose(widget, &image_rect, reglerstate, klass->slider_image,
		               klass->slider_image1, 20, 70.0, TRUE, FALSE);
		break;
	case GX_REGLER_TYPE_MINI_SLIDER:
		hslider_expose(widget, &image_rect, reglerstate, klass->minislider_image,
		               klass->minislider_image1, 6, 99.0, TRUE, FALSE);
		break;
	case GX_REGLER_TYPE_VSLIDER:
		vslider_expose(widget, &image_rect, reglerstate, TRUE, FALSE);
		break;
	}
	return TRUE;
}

/****************************************************************
 ** set size for GdkDrawable per type
 */

static void gx_regler_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
	g_assert(GX_IS_REGLER(widget));
	GxRegler *regler = GX_REGLER(widget);

	requisition->width = base_size[regler->regler_type].width;
	requisition->height = base_size[regler->regler_type].height;
	gx_regler_ensure_layout(regler);
	if (regler->show_value) {
		PangoRectangle logical_rect1, logical_rect2;
		GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
		int p = precision(adj);
		char buf[20];
		int borderx = 12, bordery = 6;
		snprintf(buf, sizeof(buf), "%.*f", p, gtk_adjustment_get_lower(adj));
		pango_layout_set_text(regler->value_layout, buf, -1);
		pango_layout_get_pixel_extents(regler->value_layout, NULL, &logical_rect1);
		snprintf(buf, sizeof(buf), "%.*f", p, gtk_adjustment_get_upper(adj));
		pango_layout_set_text(regler->value_layout, buf, -1);
		pango_layout_get_pixel_extents(regler->value_layout, NULL, &logical_rect2);
		gint height = max(logical_rect1.height,logical_rect2.height) + bordery;
		requisition->height += height;
		int width = max(logical_rect1.width,logical_rect2.width) + borderx;
		if (requisition->width < width) {
			requisition->width = width;
		}
		GxReglerPrivate *priv = GX_REGLER_GET_PRIVATE(regler);
		priv->value_req.width = width;
		priv->value_req.height = height;
	}
	if (regler->show_label) {
		PangoRectangle logical_rect;
		pango_layout_get_pixel_extents(regler->label_layout, NULL, &logical_rect);
		switch (regler->label_position) {
		case GTK_POS_LEFT:
		case GTK_POS_RIGHT:
			requisition->width += logical_rect.width;
			if (logical_rect.height > requisition->height) {
				requisition->height = logical_rect.height;
			}
			break;
		case GTK_POS_TOP:
		case GTK_POS_BOTTOM:
			requisition->height += logical_rect.height;
			if (logical_rect.width > requisition->width) {
				requisition->width = logical_rect.width;
			}
			break;
		}
	}
}

/****************************************************************
 ** set value from key bindings
 */

static void gx_regler_set_value (GtkWidget *widget, int dir_down)
{
	g_assert(GX_IS_REGLER(widget));

	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));

	int oldstep = (int)(0.5f + (adj->value - adj->lower) / adj->step_increment);
	int step;
	int nsteps = (int)(0.5f + (adj->upper - adj->lower) / adj->step_increment);
	if (dir_down)
		step = oldstep - 1;
	else
		step = oldstep + 1;
	float value = adj->lower + step * (double)(adj->upper - adj->lower) / nsteps;
	gtk_widget_grab_focus(widget);
	gtk_range_set_value(GTK_RANGE(widget), value);
}

/****************************************************************
 ** keyboard bindings
 */

static gboolean gx_regler_key_press (GtkWidget *widget, GdkEventKey *event)
{
	g_assert(GX_IS_REGLER(widget));

	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	switch (event->keyval) {
	case GDK_Home:
		gtk_range_set_value(GTK_RANGE(widget), adj->lower);
		return TRUE;
	case GDK_End:
		gtk_range_set_value(GTK_RANGE(widget), adj->upper);
		return TRUE;
	case GDK_Up:
		gx_regler_set_value(widget, 0);
		return TRUE;
	case GDK_Right:
		gx_regler_set_value(widget, 0);
		return TRUE;
	case GDK_Down:
		gx_regler_set_value(widget, 1);
		return TRUE;
	case GDK_Left:
		gx_regler_set_value(widget, 1);
		return TRUE;
	}

	return FALSE;
}

//------------ calculate value for display
static double gx_regler_get_value(GtkAdjustment *adj,double pos)
{
    if (adj->step_increment < 0.009999) pos = (floor (pos*1000))*0.001;
    else if (adj->step_increment < 0.099999) pos = (floor (pos*100))*0.01;
    else if (adj->step_increment < 0.999999) pos = (floor (pos*10))*0.1;
    else pos = floor (pos);
    return pos;

}

/****************************************************************
 ** alternative knob motion mode (ctrl + mouse pressed)
 */

static void knob_pointer_event(GtkWidget *widget, gdouble x, gdouble y, int knob_x, int knob_y,
                               gboolean drag, int state)
{
	static double last_x = 2e20;
	GxRegler *regler = GX_REGLER(widget);
	GxReglerPrivate *priv = GX_REGLER_GET_PRIVATE(regler);
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	double radius =  min(knob_x, knob_y) / 2;
	int  reglerx = (widget->allocation.width - knob_x) / 2;
	int  reglery = (widget->allocation.height - knob_y) / 2;
	double posx = (reglerx + radius) - x; // x axis right -> left
	double posy = (reglery + radius) - y; // y axis top -> bottom
	double value;
	if (!drag) {
		if (state & GDK_CONTROL_MASK) {
			last_x = posx;
			return;
		} else {
			last_x = 2e20;
		}
	}
	if (last_x < 1e20) { // in drag started with Control Key
		const double scaling = 0.005;
		double scal = (state & GDK_CONTROL_MASK ? scaling : scaling*0.1);
		value = (last_x - posx) * scal;
		last_x = posx;
		gtk_range_set_value(GTK_RANGE(widget), adj->value + value * (adj->upper - adj->lower));
		return;
	}

	double angle = atan2(-posx, posy) + M_PI; // clockwise, zero at 6 o'clock, 0 .. 2*M_PI
	if (drag) {
		// block "forbidden zone" and direct moves between quadrant 1 and 4
		int quadrant = 1 + (int)(angle/M_PI_2);
		if (priv->last_quadrant == 1 && (quadrant == 3 || quadrant == 4)) {
			angle = scale_zero;
		} else if (priv->last_quadrant == 4 && (quadrant == 1 || quadrant == 2)) {
			angle = 2*M_PI - scale_zero;
		} else {
			if (angle < scale_zero) {
				angle = scale_zero;
			} else if (angle > 2*M_PI - scale_zero) {
				angle = 2*M_PI - scale_zero;
			}
			priv->last_quadrant = quadrant;
		}
	} else {
		if (angle < scale_zero) {
			angle = scale_zero;
		} else if (angle > 2*M_PI - scale_zero) {
			angle = 2*M_PI - scale_zero;
		}
		priv->last_quadrant = 0;
	}
	angle = (angle - scale_zero) / (2 * (M_PI-scale_zero)); // normalize to 0..1
	gtk_range_set_value(GTK_RANGE(widget), adj->lower + angle * (adj->upper - adj->lower));
}

/****************************************************************
 ** mouse button pressed set value
 */

static gboolean gx_regler_button_press (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_REGLER(widget));
	GxRegler *regler = GX_REGLER(widget);
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	GtkWidget * dialog,* spinner, *ok_button, *vbox, *toplevel;

	if (event->button == 3) {
		// right button show num entry
		dialog = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		spinner = gtk_spin_button_new (GTK_ADJUSTMENT(adj), adj->step_increment,
		                               precision(adj));
		gtk_entry_set_activates_default(GTK_ENTRY(spinner), TRUE);
		ok_button  = gtk_button_new_from_stock(GTK_STOCK_OK);
		GTK_WIDGET_SET_FLAGS (GTK_WIDGET(ok_button), GTK_CAN_DEFAULT);
		vbox = gtk_vbox_new (FALSE, 4);
		gtk_container_add (GTK_CONTAINER(vbox), spinner);
		gtk_container_add (GTK_CONTAINER(vbox), ok_button);
		gtk_container_add (GTK_CONTAINER(dialog), vbox);
		gtk_window_set_decorated(GTK_WINDOW(dialog), FALSE);
		gtk_window_set_title (GTK_WINDOW (dialog), "set");
		gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
		gtk_window_set_gravity(GTK_WINDOW(dialog), GDK_GRAVITY_SOUTH);
		gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);
		gtk_window_set_keep_below (GTK_WINDOW(dialog), FALSE);
		gtk_widget_grab_default(ok_button);
		toplevel = gtk_widget_get_toplevel (widget);
        if (GTK_WIDGET_TOPLEVEL (toplevel)) {
	        gtk_window_set_transient_for (GTK_WINDOW(dialog), GTK_WINDOW(toplevel));
        }

		gtk_window_set_destroy_with_parent(GTK_WINDOW(dialog), TRUE);
		g_signal_connect_swapped (ok_button, "clicked",
		                          G_CALLBACK (gtk_widget_destroy), dialog);
		gtk_widget_show_all(dialog);
		return TRUE;
	}

	if (event->button != 1) {
		return FALSE;
	}

	gtk_widget_grab_focus(widget);
	gtk_widget_grab_default (widget);
	gtk_grab_add(widget);
	gint width = base_size[regler->regler_type].width;
	gint height = base_size[regler->regler_type].height;

	switch (regler->regler_type) {
	case GX_REGLER_TYPE_SMALL_KNOB:
		knob_pointer_event(widget, event->x, event->y, width, height, FALSE, event->state);
		break;
	case GX_REGLER_TYPE_BIG_KNOB:
		knob_pointer_event(widget, event->x, event->y, width, height, FALSE, event->state);
		break;
	case GX_REGLER_TYPE_HSLIDER: {
		int  reglerx = (widget->allocation.width - width) / 2;
		double pos = adj->lower + (((event->x - reglerx-10)*0.01)* (adj->upper - adj->lower));
		gtk_range_set_value(GTK_RANGE(widget), gx_regler_get_value(adj,pos));
		break;
	}
	case GX_REGLER_TYPE_MINI_SLIDER: {
		int  reglerx = (widget->allocation.width - width) / 2;
		double pos = adj->lower + (((event->x - reglerx-3)*0.03575)* (adj->upper - adj->lower));
		gtk_range_set_value(GTK_RANGE(widget), gx_regler_get_value(adj,pos));
		break;
	}
	case GX_REGLER_TYPE_WHEEL: {
		int  wheelx = (widget->allocation.width - width) / 2;
		double pos = adj->lower + (((event->x - wheelx)*0.03)* (adj->upper - adj->lower));
		gtk_range_set_value(GTK_RANGE(widget), gx_regler_get_value(adj,pos));
		break;
	}
	case GX_REGLER_TYPE_VSLIDER: {
		int  reglery = (widget->allocation.height - height) / 2;
		double pos = adj->upper - (((event->y - reglery-10)*0.02)* (adj->upper - adj->lower));
		gtk_range_set_value(GTK_RANGE(widget), gx_regler_get_value(adj,pos));
		break;
	}
	case GX_REGLER_TYPE_EQ_SLIDER: {
		int  reglery = (widget->allocation.height - width) / 2;
		double pos = adj->upper - (((event->y - reglery+18)*0.02)* (adj->upper - adj->lower));
		gtk_range_set_value(GTK_RANGE(widget), gx_regler_get_value(adj,pos));
		break;
	}
	default:
		g_assert(FALSE);
	}
	return TRUE;
}

/****************************************************************
 ** mouse button release
 */

static gboolean gx_regler_button_release (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_REGLER(widget));
	if (GTK_WIDGET_HAS_GRAB(widget))
		gtk_grab_remove(widget);
	return FALSE;
}

/****************************************************************
 ** set the value from mouse movement
 */

static gboolean gx_regler_pointer_motion (GtkWidget *widget, GdkEventMotion *event)
{
	g_assert(GX_IS_REGLER(widget));
	if (!GTK_WIDGET_HAS_GRAB(widget)) {
		return FALSE;
	}
	GxRegler *regler = GX_REGLER(widget);
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));

	gdk_event_request_motions (event);

	gint width = base_size[regler->regler_type].width;
	gint height = base_size[regler->regler_type].height;

	switch (regler->regler_type) {

	case GX_REGLER_TYPE_SMALL_KNOB:
		knob_pointer_event(widget, event->x, event->y, width, height, TRUE, event->state);
		break;
	case GX_REGLER_TYPE_BIG_KNOB:
		knob_pointer_event(widget, event->x, event->y, width, height, TRUE, event->state);
		break;
	case GX_REGLER_TYPE_HSLIDER:
		if (event->x > 0) {
			int  sliderx = (widget->allocation.width - width) / 2;
			double pos = adj->lower + (((event->x - sliderx-10)*0.01)* (adj->upper - adj->lower));
			gtk_range_set_value(GTK_RANGE(widget), gx_regler_get_value(adj,pos));
		}
		break;
	case GX_REGLER_TYPE_MINI_SLIDER:
		if (event->x > 0) {
			int  sliderx = (widget->allocation.width - width) / 2;
			double pos = adj->lower + (((event->x - sliderx-3)*0.03575)* (adj->upper - adj->lower));
			gtk_range_set_value(GTK_RANGE(widget), gx_regler_get_value(adj,pos));
		}
		break;
	case GX_REGLER_TYPE_WHEEL:
		if (event->x > 0) {
			int  wheelx = (widget->allocation.width - width) / 2;
			double pos = adj->lower + (((event->x - wheelx)*0.03)* (adj->upper - adj->lower));
			gtk_range_set_value(GTK_RANGE(widget), gx_regler_get_value(adj,pos));
		}
		break;
	case GX_REGLER_TYPE_VSLIDER:
		if (event->y > 0) {
			int  slidery = (widget->allocation.height - height) / 2;
			double pos = adj->upper - (((event->y - slidery-10)*0.02)* (adj->upper - adj->lower));
			gtk_range_set_value(GTK_RANGE(widget), gx_regler_get_value(adj,pos));
		}
		break;
	case GX_REGLER_TYPE_EQ_SLIDER:
		if (event->y > 0) {
			int  slidery = (widget->allocation.height - width) / 2;
			double pos = adj->upper - (((event->y - slidery+18)*0.02)* (adj->upper - adj->lower));
			gtk_range_set_value(GTK_RANGE(widget), gx_regler_get_value(adj,pos));
		}
		break;
	default:
		g_assert(FALSE);
	}
	return FALSE;
}

/****************************************************************
 ** set value from mouseweel
 */

static gboolean gx_regler_scroll (GtkWidget *widget, GdkEventScroll *event)
{
	usleep(5000);
	gx_regler_set_value(widget, event->direction);
	return FALSE;
}

/****************************************************************
 ** init the used background images to the used skins
 */

//---------- here are the inline pixmaps for regler
#include "GxReglerPix.cpp"

static void gx_change_pixmaps(GxReglerClass *klass)
{
	const char **xpm;
	GtkSettings *settings = gtk_settings_get_default();
	int theme = 0;
	if (settings) {
		GtkStyle *style = gtk_rc_get_style_by_paths(
			settings,NULL,"GxRegler",gx_regler_get_type());
		if (style) {
			GValue v = { 0 };
			g_value_init(&v, G_TYPE_INT);
			gtk_style_get_style_property(style, gx_regler_get_type(), "image-theme-number", &v);
			theme = g_value_get_int(&v);
		}
	}
	if (theme == klass->current_theme) {
		return;
	}
	klass->current_theme = theme;
	switch (theme) {
	case 0: xpm = knob1_xpm; break;
	case 1: xpm = knob2_xpm; break;
	case 2: xpm = knob3_xpm; break;
	case 3: xpm = knob4_xpm; break;
	case 4: xpm = knob5_xpm; break;
	case 5: xpm = knob6_xpm; break;
	default: xpm = knob1_xpm; break;
	}
	if (klass->bigregler_image) {
		g_object_unref(klass->bigregler_image);
	}
	klass->bigregler_image = gdk_pixbuf_new_from_xpm_data(xpm);
	g_assert(klass->bigregler_image != NULL);
	//----------- small knob
	if (klass->regler_image) {
		g_object_unref(klass->regler_image);
	}
	klass->regler_image = gdk_pixbuf_scale_simple(klass->bigregler_image,25,25,GDK_INTERP_HYPER);
	g_assert(klass->regler_image != NULL);
}

void gx_regler_init_pixmaps(GxReglerClass *klass)
{
	klass->bigregler_image = NULL;
	klass->regler_image = NULL;
	gx_change_pixmaps(klass);
	//----------- horizontal slider
	klass->slider_image = gdk_pixbuf_new_from_xpm_data(slidersm_xpm);
	g_assert(klass->slider_image != NULL);
	klass->slider_image1 = gdk_pixbuf_copy(klass->slider_image );
	g_assert(klass->slider_image1 != NULL);
	//----------- vertical slider
	klass->vslider_image = gdk_pixbuf_rotate_simple(
		klass->slider_image, GDK_PIXBUF_ROTATE_COUNTERCLOCKWISE);
	g_assert(klass->vslider_image != NULL);
	klass->vslider_image1 = gdk_pixbuf_copy( klass->vslider_image );
	g_assert(klass->vslider_image1 != NULL);
	//----------- mini slider
	klass->minislider_image = gdk_pixbuf_scale_simple(klass->slider_image,40,6,GDK_INTERP_HYPER);
	g_assert(klass->minislider_image != NULL);
	klass->minislider_image1 = gdk_pixbuf_copy( klass->minislider_image );
	g_assert(klass->minislider_image1 != NULL);
	//----------- eq slider
	klass->eqslider_image = gdk_pixbuf_new_from_xpm_data(eqslider_xpm);
	g_assert(klass->eqslider_image != NULL);
	klass->eqslider_image1 = gdk_pixbuf_copy( klass->eqslider_image );
	g_assert(klass->eqslider_image1 != NULL);
	//----------- horizontal wheel
	klass->wheel_image = gdk_pixbuf_new_from_xpm_data(wheel_xpm);
	g_assert(klass->wheel_image != NULL);
	klass->wheel_image1 = gdk_pixbuf_new_from_xpm_data(wheel_s_xpm);
	g_assert(klass->wheel_image1 != NULL);
	klass->pointer_image1 = gdk_pixbuf_new_from_xpm_data(pointer_xpm);
	g_assert(klass->pointer_image1 != NULL);
}

static void gx_regler_style_set(GtkWidget *widget, GtkStyle  *previous_style)
{
	gx_change_pixmaps(GX_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget)));
}

/****************************************************************
 ** init the Regler type/size
 */

static void gx_regler_init(GxRegler *regler)
{
	GxReglerPrivate *priv;
	gtk_widget_set_has_window (GTK_WIDGET (regler), FALSE);
	GTK_WIDGET_SET_FLAGS (GTK_WIDGET(regler), GTK_CAN_FOCUS);
	GTK_WIDGET_SET_FLAGS (GTK_WIDGET(regler), GTK_CAN_DEFAULT);
	priv = GX_REGLER_GET_PRIVATE(regler);
}

/****************************************************************
 ** Properties
 */

static void gx_regler_set_var_id(GxRegler *regler, const gchar *str)
{
	g_free(regler->var_id);
	regler->var_id = g_strdup(str ? str : "");
	g_object_notify(G_OBJECT(regler), "var-id");
}

gchar *gx_regler_get_var(GxRegler *regler)
{
	return regler->var_id;
}

static void gx_regler_set_property (
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	GxRegler *regler;

	regler = GX_REGLER (object);

	switch(prop_id) {
	case PROP_TYPE:
		regler->regler_type = g_value_get_enum(value);
		gtk_widget_queue_resize(GTK_WIDGET(object));
		g_object_notify(object, "show-value");
		break;
	case PROP_VAR_ID:
		gx_regler_set_var_id (regler, g_value_get_string (value));
		break;
	case PROP_SHOW_VALUE:
		regler->show_value = g_value_get_boolean(value);
		gtk_widget_queue_resize(GTK_WIDGET(object));
		g_object_notify(object, "show-value");
		break;
	case PROP_SHOW_LABEL:
		regler->show_label = g_value_get_boolean(value);
		gtk_widget_queue_resize(GTK_WIDGET(object));
		g_object_notify(object, "show-label");
		break;
	case PROP_LABEL_FROM_VAR:
		regler->label_from_var = g_value_get_boolean(value);
		g_object_notify(object, "label-from-var");
		break;
	case PROP_LABEL_TEXT:
		gx_regler_set_label(regler, g_value_get_string(value));
		break;
	case PROP_LABEL_POSITION:
		regler->label_position = GtkPositionType(g_value_get_enum(value));
		gtk_widget_queue_resize(GTK_WIDGET(object));
		g_object_notify(object, "label-position");
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void gx_regler_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec*pspec)
{
	GxRegler *regler;

	regler = GX_REGLER(object);

	switch(prop_id) {
	case PROP_TYPE:
		g_value_set_enum(value, regler->regler_type);
		break;
	case PROP_VAR_ID:
		g_value_set_string (value, regler->var_id);
	case PROP_SHOW_VALUE:
		g_value_set_boolean(value, regler->show_value);
		break;
	case PROP_SHOW_LABEL:
		g_value_set_boolean(value, regler->show_label);
		break;
	case PROP_LABEL_FROM_VAR:
		g_value_set_boolean(value, regler->label_from_var);
		break;
	case PROP_LABEL_TEXT:
		g_value_set_string(value, regler->label);
		break;
	case PROP_LABEL_POSITION:
		g_value_set_enum(value, regler->label_position);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

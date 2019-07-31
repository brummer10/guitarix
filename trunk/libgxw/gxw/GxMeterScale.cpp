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


#include "GxMeterScale.h"
#include <cmath>

#define P_(s) (s)   // FIXME -> gettext

enum {
	PROP_TICK_POS = 1,
};

typedef struct {
	gdouble          value;
	gchar           *markup;
} GxMeterScaleMark;

struct _GxMeterScalePrivate {
	GxTickPosition tick_pos;
	GSList      *marks;
};

G_DEFINE_TYPE_WITH_PRIVATE(GxMeterScale, gx_meter_scale, GTK_TYPE_WIDGET)

GType gx_tick_position_get_type(void)
{
	static GType etype = 0;
	if (G_UNLIKELY(etype == 0)) {
		static const GEnumValue values[] = {
			{ GX_TICK_LEFT, "TICK_LEFT", "tick left" },
			{ GX_TICK_RIGHT,"TICK_RIGHT","tick right"},
			{ GX_TICK_BOTH, "TICK_BOTH", "tick both" },
			{ GX_TICK_BELOW,"TICK_BELOW","tick below"},
			{ 0, NULL, NULL }
		};
		etype = g_enum_register_static (g_intern_static_string ("GxTickPosition"), values);
	}
	return etype;
}

static void gx_meter_scale_destroy(GtkWidget *object);
static void meter_scale_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void meter_scale_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static gboolean gx_meter_scale_draw(GtkWidget *widget, cairo_t *cr);
static void gx_meter_scale_get_preferred_width(GtkWidget* wd, gint *min_width, gint *natural_width);
static void gx_meter_scale_get_preferred_height(GtkWidget* wd, gint *min_height, gint *natural_height);
static void gx_meter_scale_size_request(GtkWidget* wd, gint *width, gint *height);

static void gx_meter_scale_class_init (GxMeterScaleClass *klass)
{
	GObjectClass   *gobject_class = G_OBJECT_CLASS(klass);
	GtkWidgetClass *widget_class = (GtkWidgetClass*)klass;
	gobject_class->set_property = meter_scale_set_property;
	gobject_class->get_property = meter_scale_get_property;
	widget_class->destroy = gx_meter_scale_destroy;
	widget_class->get_preferred_width = gx_meter_scale_get_preferred_width;
	widget_class->get_preferred_height = gx_meter_scale_get_preferred_height;
	widget_class->draw = gx_meter_scale_draw;
	// properties
	g_object_class_install_property(
		gobject_class, PROP_TICK_POS, g_param_spec_enum(
			"tick-pos", P_("tick position"),
			P_("Position of the tick relativ to the tick text"),
			GX_TYPE_TICK_POSITION, GX_TICK_RIGHT,
			GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	// style properties
	gtk_widget_class_install_style_property(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_int("tick-size",
		                 P_("Tick size"),
		                 P_("Size of ticks"),
		                 0, 100, 5,
		                 GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
	gtk_widget_class_install_style_property(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_int("tick-space",
		                 P_("Tick space"),
		                 P_("Space between tick and text"),
		                 0, 100, 2,
		                 GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
}

static void gx_meter_scale_get_preferred_width(GtkWidget* wd, gint *min_width, gint *natural_width)
{
	gint width, height;
	gx_meter_scale_size_request(wd, &width, &height);

	if (min_width) {
		*min_width = width;
	}
	if (natural_width) {
		*natural_width = width;
	}
}

static void gx_meter_scale_get_preferred_height(GtkWidget* wd, gint *min_height, gint *natural_height)
{
	gint width, height;
	gx_meter_scale_size_request(wd, &width, &height);

	if (min_height) {
		*min_height = height;
	}
	if (natural_height) {
		*natural_height = height;
	}
}

static void gx_meter_scale_size_request(GtkWidget* wd, gint *width, gint *height)
{
	GxMeterScale *meter_scale = GX_METER_SCALE(wd);
	GxMeterScalePrivate *priv = meter_scale->priv;
	PangoContext *ctx = gtk_widget_get_pango_context(wd);
	pango_font_description_set_absolute_size(pango_context_get_font_description(ctx), 8000);
	PangoLayout *layout = pango_layout_new (ctx);
	gint tick_size, tick_space;
	gtk_widget_style_get(wd, "tick-size", &tick_size, "tick-space", &tick_space, NULL);
	gint w = 0;
	gint h = 1;
	GSList *m;
	for (m = priv->marks; m; m = m->next) {
		PangoRectangle logical_rect;
		GxMeterScaleMark *mark = (GxMeterScaleMark*)(m->data);
		pango_layout_set_markup (layout, mark->markup, -1);
		pango_layout_get_pixel_extents (layout, NULL, &logical_rect);
		if (w < logical_rect.width) {
			w = logical_rect.width;
		}
		h += logical_rect.width;
	}
	g_object_unref(layout);
	switch (meter_scale->priv->tick_pos) {
	case GX_TICK_LEFT:
	case GX_TICK_RIGHT:
		w += tick_size + 2*tick_space;
		break;
	case GX_TICK_BOTH:
	case GX_TICK_BELOW:
		w += 2 * (tick_size + tick_space);
		break;
	}
	*width = w;
	*height = h;
}

static gint compare_marks(gpointer a, gpointer b)
{
	return (gint)(((GxMeterScaleMark*)a)->value - ((GxMeterScaleMark*)b)->value);
}

void gx_meter_scale_add_mark(GxMeterScale *meter_scale, gdouble value, const gchar *markup)
{
	GxMeterScalePrivate *priv = meter_scale->priv;
	GxMeterScaleMark *mark;

	mark = g_new(GxMeterScaleMark, 1);
	mark->value = value;
	mark->markup = g_strdup(markup);
 
	priv->marks = g_slist_insert_sorted(
		priv->marks, mark, (GCompareFunc)compare_marks);
	gtk_widget_queue_resize(GTK_WIDGET(meter_scale));
}

static void gx_meter_scale_mark_free(GxMeterScaleMark *mark)
{
  g_free(mark->markup);
  g_free(mark);
}

void gx_meter_scale_clear_marks(GxMeterScale *meter_scale)
{
	GxMeterScalePrivate *priv = meter_scale->priv;
	g_return_if_fail(GX_IS_METER_SCALE(meter_scale));
	g_slist_foreach(priv->marks, (GFunc)gx_meter_scale_mark_free, NULL);
	g_slist_free(priv->marks);
	priv->marks = NULL;
	gtk_widget_queue_resize(GTK_WIDGET(meter_scale));
}

static void gx_meter_scale_init(GxMeterScale *meter_scale)
{
	meter_scale->priv = G_TYPE_INSTANCE_GET_PRIVATE (meter_scale, GX_TYPE_METER_SCALE, GxMeterScalePrivate);
	gtk_widget_set_has_window(GTK_WIDGET(meter_scale), FALSE);
	meter_scale->priv->tick_pos = GX_TICK_RIGHT;
}

static void gx_meter_scale_destroy(GtkWidget *object)
{
	GxMeterScale *meter_scale = GX_METER_SCALE(object);
	gx_meter_scale_clear_marks(meter_scale);
	GTK_WIDGET_CLASS(gx_meter_scale_parent_class)->destroy(object);
}

static gboolean gx_meter_scale_draw(GtkWidget *widget, cairo_t *cr)
{
	GxMeterScale *meter_scale = GX_METER_SCALE(widget);
	GxMeterScalePrivate *priv = meter_scale->priv;
	GSList *m;
	gint tick_size, tick_space;
	gtk_widget_style_get(widget, "tick-size", &tick_size, "tick-space", &tick_space, NULL);

	/* create a cairo context */
	cairo_set_font_size (cr, 7.0);

	GtkAllocation allocation;
	gtk_widget_get_allocation(widget, &allocation);

	double x0      = allocation.x;
	double y0      = allocation.y;
	double rect_width  = allocation.width;
	double rect_height = allocation.height;

	cairo_rectangle (cr, x0,y0,rect_width,rect_height);
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_fill (cr);

	cairo_pattern_t*pat =
		cairo_pattern_create_radial (-50, y0, 5,rect_width-10,  rect_height, 20.0);
	cairo_pattern_add_color_stop_rgb (pat, 0, 0.2, 0.2, 0.3);
	cairo_pattern_add_color_stop_rgb (pat, 1, 0.05, 0.05, 0.05);
	cairo_set_source (cr, pat);
	cairo_rectangle (cr, x0+1,y0+1,rect_width-2,rect_height-2);
	cairo_fill (cr);

	PangoContext *ctx = gtk_widget_get_pango_context(widget);
	pango_font_description_set_absolute_size(pango_context_get_font_description(ctx), 8000);
	PangoLayout *layout = pango_layout_new (ctx);
	int sign_size = 0;
	for (m = priv->marks; m; m = m->next) {
		PangoRectangle logical_rect;
		GxMeterScaleMark *mark = (GxMeterScaleMark*)(m->data);
		int sign_offset = 0;
		char *text;
		if (meter_scale->priv->tick_pos != GX_TICK_RIGHT) {
			// bit of a hack: for center and left alignment try to compensate for
			// the "-" sign by adding space in front of positive numbers
			if (pango_parse_markup(mark->markup, -1, 0, NULL, &text, NULL, NULL)) {
				if (*text != '-') {
					if (!sign_size) {
						PangoRectangle ink_rect;
						pango_layout_set_markup (layout, "-", -1);
						pango_layout_get_pixel_extents (layout, &ink_rect, NULL);
						sign_size = ink_rect.x + ink_rect.width;
					}
					sign_offset = sign_size;
				}
			}
		}
		pango_layout_set_markup (layout, mark->markup, -1);
		pango_layout_get_pixel_extents (layout, NULL, &logical_rect);
		gdouble y = y0 + rect_height - int(round(rect_height * mark->value)) + 0.5;
		switch (meter_scale->priv->tick_pos) {
		case GX_TICK_LEFT:
			cairo_move_to(cr, x0, y);
			cairo_rel_line_to(cr, tick_size, 0);
			cairo_rel_move_to(cr, tick_space + sign_offset, -logical_rect.height/2);
			break;
		case GX_TICK_RIGHT:
			cairo_move_to(cr, x0 + rect_width, y);
			cairo_rel_line_to(cr, -tick_size, 0);
			cairo_rel_move_to(cr, -(tick_space + logical_rect.width),
			                  -logical_rect.height/2);
			break;
		case GX_TICK_BOTH:
			cairo_move_to(cr, x0, y);
			cairo_rel_line_to(cr, tick_size, 0);
			cairo_move_to(cr, x0 + rect_width, y);
			cairo_rel_line_to(cr, -tick_size, 0);
			cairo_move_to(cr, x0 + (rect_width - logical_rect.width + sign_offset) / 2,
			              y - logical_rect.height/2);
			break;
		case GX_TICK_BELOW:
			cairo_move_to(cr, x0, y);
			cairo_rel_line_to(cr, rect_width, 0);
			cairo_move_to(cr, x0 + (rect_width - logical_rect.width + sign_offset) / 2,
			              y - logical_rect.height);
			break;
		}
		cairo_set_source_rgb (cr, mark->value, 1, 0.1);
		pango_cairo_show_layout(cr, layout);
	}
	g_object_unref (layout);

	cairo_set_source_rgb (cr, 0.4, 0.8, 0.4);
	cairo_set_line_width (cr, 0.5);
	cairo_stroke (cr);

	cairo_pattern_destroy (pat);

	return FALSE;
}

/****************************************************************
 ** Properties
 */
static void meter_scale_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	GxMeterScale *meter_scale = GX_METER_SCALE(object);

	switch(prop_id) {
	case PROP_TICK_POS:
		meter_scale->priv->tick_pos = (GxTickPosition)g_value_get_enum(value);
		gtk_widget_queue_resize(GTK_WIDGET(object));
		g_object_notify(object, "tick-pos");
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void meter_scale_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
	GxMeterScale *meter_scale = GX_METER_SCALE(object);

	switch(prop_id) {
	case PROP_TICK_POS:
		g_value_set_enum(value, meter_scale->priv->tick_pos);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

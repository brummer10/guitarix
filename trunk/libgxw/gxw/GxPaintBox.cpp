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


#include "GxPaintBox.h"
#include "GxGradient.h"
#include "GxLevelSlider.h"
#include <cmath>
#include <cstring>

#define P_(s) (s)   // FIXME -> gettext

struct _GxPaintBoxPrivate {
	gchar *paint_func;
	void (*draw_func)(GtkWidget*, cairo_t*);
	GdkPixbuf *gxh_image;
	GdkPixbuf *gxr_image;
	GdkPixbuf *logo_image;
	guint icon_set;
	guint force_reload;
};

enum {
	PROP_PAINT_FUNC = 1,
	PROP_ICON_SET = 2,
    PROP_FORCE_RELOAD = 3,
};

static void gx_paint_box_destroy(GtkWidget *object);
static void gx_paint_box_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gx_paint_box_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static gboolean gx_paint_box_draw(GtkWidget *widget, cairo_t *cr);
static void gx_paint_box_style_set (GtkWidget *widget, GtkStyle  *previous_style);

G_DEFINE_TYPE_WITH_PRIVATE(GxPaintBox, gx_paint_box, GTK_TYPE_BOX)

#define GX_PAINT_BOX_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), GX_TYPE_PAINT_BOX, GxPaintBoxPrivate))

#define get_stock_id(widget) (GX_PAINT_BOX_CLASS(GTK_WIDGET_GET_CLASS(widget))->stock_id)
#define get_widget_id(widget) (GX_PAINT_BOX_CLASS(GTK_WIDGET_GET_CLASS(widget))->widget_id)
#define get_widget_id2(widget) (GX_PAINT_BOX_CLASS(GTK_WIDGET_GET_CLASS(widget))->widget_id2)
#define get_widget_id3(widget) (GX_PAINT_BOX_CLASS(GTK_WIDGET_GET_CLASS(widget))->widget_id3)
#define get_amp_id(widget) (GX_PAINT_BOX_CLASS(GTK_WIDGET_GET_CLASS(widget))->amp_id)
#define get_logo_id(widget) (GX_PAINT_BOX_CLASS(GTK_WIDGET_GET_CLASS(widget))->logo_id)


static void gx_paint_box_class_init (GxPaintBoxClass *klass)
{
	GObjectClass   *gobject_class = G_OBJECT_CLASS(klass);
	GtkWidgetClass *widget_class = (GtkWidgetClass*)klass;
	gobject_class->set_property = gx_paint_box_set_property;
	gobject_class->get_property = gx_paint_box_get_property;
	widget_class->destroy = gx_paint_box_destroy;
	widget_class->style_set = gx_paint_box_style_set;
	widget_class->draw = gx_paint_box_draw;
	klass->stock_id = "gxhead";
    klass->widget_id = "gxplate";
    klass->widget_id2 = "gxplate2";
    klass->widget_id3 = "gxplate3";
    klass->amp_id = "gxhead";
    klass->logo_id = "logo";

	gtk_widget_class_set_css_name(widget_class, "gx-paint-box");

	g_object_class_install_property(
		gobject_class, PROP_PAINT_FUNC,
		g_param_spec_string("paint-func",
		                    P_("Paint Type"),
		                    P_("Type of paint function for background"),
		                    "",
		                    GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	gtk_widget_class_install_style_property_parser(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_boxed("skin-gradient",
		                   P_("Skin color"),
		                   P_("Color gradient defined as part of skin"),
		                   GX_TYPE_GRADIENT,
		                   GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)),
		gx_parse_gradient);
	gtk_widget_class_install_style_property_parser(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_boxed("box-gradient",
		                   P_("Skin color"),
		                   P_("Color gradient defined as part of skin"),
		                   GX_TYPE_GRADIENT,
		                   GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)),
		gx_parse_gradient);
	gtk_widget_class_install_style_property_parser(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_boxed("rack-gradient",
		                   P_("Skin color"),
		                   P_("Color gradient defined as part of skin"),
		                   GX_TYPE_GRADIENT,
		                   GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)),
		gx_parse_gradient);
	gtk_widget_class_install_style_property(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_string("paint-func",
		                    P_("Paint Type"),
		                    P_("Type of paint function for background"),
		                    NULL,
		                    GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class,PROP_ICON_SET,
	    g_param_spec_int ("icon-set",
			      P_("Icon Set"),
			      P_("Type of Icon function for background"),
			      0,
			      G_MAXINT,
			      0,
			      GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	gtk_widget_class_install_style_property(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_int("icon-set",
		                 P_("Icon Set"),
		                 P_("Type of Icon function for background"),
		                 0,
                         G_MAXINT,
                         0,
		                 GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class,PROP_FORCE_RELOAD,
	    g_param_spec_int ("force-reload",
			      P_("Force Reload"),
			      P_("Reload Image for background"),
			      0,
			      G_MAXINT,
			      0,
			      GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	gtk_widget_class_install_style_property(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_int("force-reload",
		                 P_("Force Reload"),
		                 P_("Reload Image for background"),
		                 0,
                         G_MAXINT,
                         0,
		                 GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
	gtk_widget_class_install_style_property(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_int("width",
		                 P_("Width"),
		                 P_("size.width request for paintbox"),
		                 0,
				 G_MAXINT,
				 0,
		                 GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
	gtk_widget_class_install_style_property(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_int("height",
		                 P_("Height"),
		                 P_("size.height request for paintbox"),
		                 0,
				 G_MAXINT,
				 0,
		                 GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));

    gtk_widget_class_install_style_property(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_float("bevel",
            P_("Bevel"),
            P_("The bevel effect"),
            -1.0, 1.0, 0.0,
            GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
    gtk_widget_class_install_style_property(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_int("border-radius",
            P_("Border Radius"),
            P_("The radius of the corners"),
            0, 100, 0,
            GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
    gtk_widget_class_install_style_property(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_int("inverse",
            P_("Inverse"),
            P_("When drawn by draw_skin, choose if colors are inverted"),
            0, 1, 0,
            GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
    gtk_widget_class_install_style_property(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_boxed("alternate-box",
            P_("Alternate Box"),
            P_("A box definition { left, right, top, bottom } for the alternate color in percent"),
            GTK_TYPE_BORDER,
            GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
}

void gx_paint_box_call_paint_func(GxPaintBox *paint_box, cairo_t *cr)
{
	g_return_if_fail(GX_IS_PAINT_BOX(paint_box));
	if (paint_box->priv->draw_func) {
		paint_box->priv->draw_func(GTK_WIDGET(paint_box), cr);
	}
}

static void set_expose_func(GxPaintBox *paint_box, const gchar *paint_func);

static void set_paint_func(GxPaintBox *paint_box, const gchar *paint_func)
{
	gchar *spf;
	gtk_widget_style_get(GTK_WIDGET(paint_box), "paint-func", &spf, NULL);
	if (spf) {
		if (paint_box->priv->paint_func && strcmp(paint_box->priv->paint_func, spf) == 0) {
			return;
		}
	} else {
		if (!paint_func) {
			paint_func = "";
		}
		if (paint_box->priv->paint_func && strcmp(paint_box->priv->paint_func, paint_func) == 0) {
			return;
		}
		spf = g_strdup(paint_func);
	}
	g_free(paint_box->priv->paint_func);
	paint_box->priv->paint_func = spf;
	set_expose_func(paint_box, spf);
	g_object_notify(G_OBJECT(paint_box), "paint-func");
	gtk_widget_queue_draw(GTK_WIDGET(paint_box));
}

static void gx_paint_box_style_set(GtkWidget *widget, GtkStyle  *previous_style)
{
	GxPaintBox *paint_box = GX_PAINT_BOX(widget);
	set_paint_func(paint_box, paint_box->priv->paint_func);
}

static void gx_paint_box_init (GxPaintBox *paint_box)
{
	paint_box->priv = GX_PAINT_BOX_GET_PRIVATE(paint_box);
	gtk_widget_set_redraw_on_allocate(GTK_WIDGET(paint_box), TRUE);
	paint_box->priv->paint_func = g_strdup("");
	set_paint_func(paint_box, NULL);
	paint_box->priv->gxh_image = NULL;
	paint_box->priv->gxr_image = NULL;
	paint_box->priv->logo_image = NULL;
	paint_box->priv->icon_set = 0;
	paint_box->priv->force_reload = 0;
}

static void gx_paint_box_destroy(GtkWidget *object)
{
	GxPaintBox *paint_box = GX_PAINT_BOX(object);
	if (paint_box->priv->paint_func) {
		g_free(paint_box->priv->paint_func);
		paint_box->priv->paint_func = NULL;
	}
	while (G_IS_OBJECT(paint_box->priv->gxh_image)) {
        g_object_unref(paint_box->priv->gxh_image);
	}
	paint_box->priv->gxh_image = NULL;
	while (G_IS_OBJECT(paint_box->priv->gxr_image)) {
        g_object_unref(paint_box->priv->gxr_image);
	}
	paint_box->priv->gxr_image = NULL;
	while (G_IS_OBJECT(paint_box->priv->logo_image)) {
        g_object_unref(paint_box->priv->logo_image);
	}
	paint_box->priv->logo_image = NULL;
	GTK_WIDGET_CLASS(gx_paint_box_parent_class)->destroy(object);
}

static gboolean gx_paint_box_draw(GtkWidget *widget, cairo_t *cr)
{
	GxPaintBox *paint_box = GX_PAINT_BOX(widget);
	if (paint_box->priv->draw_func) {
		paint_box->priv->draw_func(widget, cr);
	}
	GTK_WIDGET_CLASS(gx_paint_box_parent_class)->draw(widget, cr);
	return FALSE;
}

static void set_reload(GxPaintBox *paint_box, int value)
{
	int spf;
	gtk_widget_style_get(GTK_WIDGET(paint_box), "force-reload", &spf, NULL);
	paint_box->priv->force_reload = spf;
}

static void set_icon(GxPaintBox *paint_box, int value)
{
	int spf;
	gtk_widget_style_get(GTK_WIDGET(paint_box), "icon-set", &spf, NULL);
	paint_box->priv->icon_set = spf;
}

static void gx_paint_box_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	GxPaintBox *paint_box = GX_PAINT_BOX(object);
	switch (prop_id) {
	case PROP_PAINT_FUNC:
		set_paint_func(paint_box, g_value_get_string(value));
		break;
	case PROP_ICON_SET:
		set_icon(paint_box, g_value_get_int(value));
		break;
	case PROP_FORCE_RELOAD:
		set_reload(paint_box, g_value_get_int(value));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void gx_paint_box_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
	switch (prop_id) {
	case PROP_PAINT_FUNC:
		g_value_set_string(value, GX_PAINT_BOX(object)->priv->paint_func);
		break;
	case PROP_ICON_SET:
		g_value_set_int (value, GX_PAINT_BOX(object)->priv->icon_set);
		break;
	case PROP_FORCE_RELOAD:
		g_value_set_int (value, GX_PAINT_BOX(object)->priv->force_reload);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

GtkWidget *gx_paint_box_new (GtkOrientation orientation, gboolean homogeneous, gint spacing)
{
	return (GtkWidget*)g_object_new(
		GX_TYPE_PAINT_BOX,
		"orientation", orientation,
		"spacing",     spacing,
		"homogeneous", homogeneous ? TRUE : FALSE,
		NULL);
}

/****************************************************************
 ** Paint functions
 */

inline double cairo_clr(guint16 clr)
{
	return clr / 65535.0;
}

// set cairo color related to the used skin
static void set_skin_color(GtkWidget *wi, cairo_pattern_t *pat)
{
	GxGradient *grad;
	gtk_widget_style_get(wi, "skin-gradient", &grad, NULL);
	if (!grad) {
		GtkStyle* style = gtk_widget_get_style(wi);
		GdkColor *p1 = &style->bg[GTK_STATE_NORMAL];
		cairo_pattern_add_color_stop_rgba(
			pat, 0, cairo_clr(p1->red), cairo_clr(p1->green),
			cairo_clr(p1->blue), 0.8);
		GdkColor *p2 = &style->fg[GTK_STATE_NORMAL];
		cairo_pattern_add_color_stop_rgba(
			pat, 1, (cairo_clr(p1->red)+cairo_clr(p2->red))/2,
			(cairo_clr(p1->green)+cairo_clr(p2->green))/2,
			(cairo_clr(p1->blue)+cairo_clr(p2->blue))/2, 0.8);
		return;
	}
	GSList *p;
	for (p = grad->colors; p; p = g_slist_next(p)) {
		GxGradientElement *el = (GxGradientElement*)p->data;
		cairo_pattern_add_color_stop_rgba(pat, el->offset, el->red, el->green, el->blue, el->alpha);
	}
	gx_gradient_free(grad);
}

// set cairo color related to the used skin
static void set_box_color(GtkWidget *wi, cairo_pattern_t *pat)
{
	GxGradient *grad;
	gtk_widget_style_get(wi, "box-gradient", &grad, NULL);
	if (!grad) {
		GtkStyle* style = gtk_widget_get_style(wi);
		GdkColor *p1 = &style->bg[GTK_STATE_NORMAL];
		cairo_pattern_add_color_stop_rgba(
			pat, 0, cairo_clr(p1->red), cairo_clr(p1->green),
			cairo_clr(p1->blue), 0.8);
		GdkColor *p2 = &style->fg[GTK_STATE_NORMAL];
		cairo_pattern_add_color_stop_rgba(
			pat, 1, (cairo_clr(p1->red)+cairo_clr(p2->red))/2,
			(cairo_clr(p1->green)+cairo_clr(p2->green))/2,
			(cairo_clr(p1->blue)+cairo_clr(p2->blue))/2, 0.8);
		return;
	}
	GSList *p;
	for (p = grad->colors; p; p = g_slist_next(p)) {
		GxGradientElement *el = (GxGradientElement*)p->data;
		cairo_pattern_add_color_stop_rgba(pat, el->offset, el->red, el->green, el->blue, el->alpha);
	}
	gx_gradient_free(grad);
}

static void draw_skin (GtkWidget *wi, cairo_t *cr)
{
    int spf;
	gtk_widget_style_get(GTK_WIDGET(wi), "icon-set", &spf, NULL);
    if (spf == 1000)
        return;
    GxPaintBox *pb = GX_PAINT_BOX(wi);
	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);

	double x0 = 0;
	double y0 = 0;
	double w  = allocation.width;
	double h  = allocation.height;
    double h_ = h - 4;
    
    gint inverse;
    GtkBorder * alt;
    float bevel;
    float left, right, top, bottom;
    left = right = top = bottom = 0;
    
    gtk_widget_style_get(wi, "inverse", &inverse, "alternate_box", &alt, "bevel", &bevel, NULL);
    
    if (h > 64 and alt) {
        // only draw alternate color if height > 64 pixels
        left   = alt->left / 100.;
        right  = alt->right / 100.;
        top    = alt->top / 100.;
        bottom = alt->bottom / 100.;
    }
    
    // draw main color
    GdkPixbuf * bg = gtk_widget_render_icon_pixbuf(GTK_WIDGET(pb),
        inverse ? "background2" : "background1", (GtkIconSize)-1);
	gdk_cairo_set_source_pixbuf(cr, bg, x0, y0);
	cairo_pattern_set_extend(cairo_get_source(cr), CAIRO_EXTEND_REPEAT);
    
    cairo_rectangle(cr, x0, y0, w, h_);
	cairo_fill(cr);
    
    // draw alternate color
    if (top > 0 or bottom > 0 or left > 0 or right > 0) {
        bg = gtk_widget_render_icon_pixbuf(GTK_WIDGET(pb),
            inverse ? "background1" : "background2", (GtkIconSize)-1);
        gdk_cairo_set_source_pixbuf(cr, bg, x0, y0);
        cairo_pattern_set_extend(cairo_get_source(cr), CAIRO_EXTEND_REPEAT);
        cairo_rectangle(cr, x0 + int(w * left),
                            y0 + int(h_ * top),
                            int(w * (1 - right - left)) + 1,
                            int(h_ * (1 - bottom - top)) + 1);
        cairo_fill(cr);
    }
    
    // draw bevel
    gx_bevel(cr, x0, y0, w, h_, 0, bevel);
    
    // draw shadow beneath
    cairo_pattern_t * pat = cairo_pattern_create_linear (x0, y0 + h_, x0, y0 + h);
	cairo_pattern_add_color_stop_rgba(pat, 0.0, 0, 0, 0, 0.8);
	cairo_pattern_add_color_stop_rgba(pat, 1.0, 0, 0, 0, 0.0);
    cairo_set_source(cr, pat);
    cairo_rectangle(cr, x0, y0 + h_, w, h - h_);
    cairo_fill(cr);
    
    // clean up
    cairo_pattern_destroy(pat);
    g_object_unref(bg);
}

static void draw_tiled (GtkWidget *wi, cairo_t *cr, const gchar * id )
{
    GxPaintBox *pb = GX_PAINT_BOX(wi);

	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);

	double x0 = 0;
	double y0 = 0;
	double w  = allocation.width;
	double h  = allocation.height;

    GdkPixbuf * bg = gtk_widget_render_icon_pixbuf(GTK_WIDGET(pb), id, (GtkIconSize)-1);
	gdk_cairo_set_source_pixbuf(cr, bg, x0, y0);
	cairo_pattern_set_extend(cairo_get_source(cr), CAIRO_EXTEND_REPEAT);
    cairo_rectangle(cr, x0, y0, w, h);
	cairo_fill(cr);
    g_object_unref(bg);
}

static void draw_handles (GtkWidget *wi, cairo_t *cr)
{
    GxPaintBox *pb = GX_PAINT_BOX(wi);

	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);

	double x0 = 0;
	double y0 = 0;
	double w  = allocation.width;
	double h  = allocation.height - 4;
    
    // left
    GdkPixbuf * bg = gtk_widget_render_icon_pixbuf(GTK_WIDGET(pb), "handle_left", (GtkIconSize)-1);
    gint wl = gdk_pixbuf_get_width(bg);
	gdk_cairo_set_source_pixbuf(cr, bg, x0, y0);
	cairo_pattern_set_extend(cairo_get_source(cr), CAIRO_EXTEND_REPEAT);
    cairo_rectangle(cr, x0, y0, wl, h);
	cairo_fill(cr);
    cairo_rectangle(cr, x0 + wl - 1, y0, 1, h);
    cairo_set_source_rgba(cr, 0, 0, 0, 0.8);
    cairo_fill(cr);
    cairo_rectangle(cr, x0 + wl, y0, 1, h);
    cairo_set_source_rgba(cr, 1, 1, 1, 0.15);
    cairo_fill(cr);
    
    // right
    bg = gtk_widget_render_icon_pixbuf(GTK_WIDGET(pb), "handle_right", (GtkIconSize)-1);
    wl = gdk_pixbuf_get_width(bg);
	gdk_cairo_set_source_pixbuf(cr, bg, x0 + w - wl, y0);
	cairo_pattern_set_extend(cairo_get_source(cr), CAIRO_EXTEND_REPEAT);
    cairo_rectangle(cr, x0 + w - wl, y0, wl, h);
	cairo_fill(cr);
    cairo_rectangle(cr, x0 + w - wl - 1, y0, 1, h);
    cairo_set_source_rgba(cr, 0, 0, 0, 0.5);
    cairo_fill(cr);
    cairo_rectangle(cr, x0 + w - wl, y0, 1, h);
    cairo_set_source_rgba(cr, 1, 1, 1, 0.05);
    cairo_fill(cr);

    g_object_unref(bg);
}

static void draw_screws (GtkWidget *wi, cairo_t *cr)
{
	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);
	double x0 = 0;
	double y0 = 0;
	double w  = allocation.width;
	double h  = allocation.height - 3;

	GdkPixbuf  *stock_image = gtk_widget_render_icon_pixbuf(wi,"screw",(GtkIconSize)-1);
	double x1 = gdk_pixbuf_get_height(stock_image);
	double y1 = gdk_pixbuf_get_width(stock_image);
	if (h > 2 * y1) {
		gdk_cairo_set_source_pixbuf(cr, stock_image, x0, y0);
		cairo_paint(cr);
		gdk_cairo_set_source_pixbuf(cr, stock_image, x0, y0 + h - y1);
		cairo_paint(cr);
		gdk_cairo_set_source_pixbuf(cr, stock_image, x0 + w - x1, y0 + h - y1);
		cairo_paint(cr);
		gdk_cairo_set_source_pixbuf(cr, stock_image, x0 + w - x1, y0);
		cairo_paint(cr);
	} else if (h > y1) {
		gdk_cairo_set_source_pixbuf(cr, stock_image, x0, y0 + int(h / 2) - int(y1 / 2));
		cairo_paint(cr);
		gdk_cairo_set_source_pixbuf(cr, stock_image, x0 + w - x1,
					    y0 + int(h / 2) - int(y1 / 2));
		cairo_paint(cr);
	}
	g_object_unref(stock_image);
}

static void draw_watermark(GtkWidget *wi, cairo_t *cr)
{
	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);

	double x0 = 0;
	double y0 = 0;
	double w  = allocation.width;
	double h  = allocation.height;
    
    GdkPixbuf * wm  = gtk_widget_render_icon_pixbuf(wi, "watermark", (GtkIconSize)-1);
    gint wwm = gdk_pixbuf_get_width(wm);
    gint hwm = gdk_pixbuf_get_height(wm);
    GdkPixbuf * wm_ = gdk_pixbuf_scale_simple(wm, int(wwm * 0.89), int(hwm * 0.9), GDK_INTERP_BILINEAR);
    gint wwm_ = gdk_pixbuf_get_width(wm_);
    gint hwm_ = gdk_pixbuf_get_height(wm_);
    gdk_cairo_set_source_pixbuf(cr, wm_, x0 + w - wwm_ - 10, y0 + h - hwm_ - 10);
    cairo_rectangle(cr, x0 + w - wwm_ - 10, y0 + h - hwm_ - 10, wwm_, hwm_);
    cairo_fill(cr);

    g_object_unref(wm);
    g_object_unref(wm_);
}
// Expose Callbacks

static void box_skin_expose(GtkWidget *wi, cairo_t *cr)
{
	draw_skin(wi, cr);
}

static void box_uni_1_expose(GtkWidget *wi, cairo_t *cr)
{
	draw_tiled(wi, cr, "background1");
}

static void box_uni_2_expose(GtkWidget *wi, cairo_t *cr)
{
	draw_tiled(wi, cr, "background2");
}

static void gx_rack_unit_expose (GtkWidget *wi, cairo_t *cr) {
    draw_skin(wi, cr);
    draw_handles(wi, cr);
    draw_screws(wi, cr);
}

static void gx_rack_unit_shrink_expose(GtkWidget *wi, cairo_t *cr)
{
	draw_skin(wi, cr);
	draw_handles(wi, cr);
    draw_screws(wi, cr);
}

static void gx_rack_amp_expose(GtkWidget *wi, cairo_t *cr)
{
    draw_skin(wi, cr);
    draw_screws(wi, cr);
}

static void gx_lv2_unit_expose(GtkWidget *wi, cairo_t *cr)
{
    draw_tiled(wi, cr, "background2");
    draw_handles(wi, cr);
    draw_screws(wi, cr);
}


static void rectangle_skin_color_expose(GtkWidget *wi, cairo_t *cr)
{
    cairo_pattern_t*pat;
	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);

	double x0      = 1;
	double y0      = 1;
	double rect_width  = allocation.width-2;
	double rect_height = allocation.height-2;
    
    double radius = 12.;
	if (rect_width<12) radius = rect_width;
	else if (rect_height<12) radius = rect_height;
	double x1,y1;

	x1=x0+rect_width-2;
	y1=y0+rect_height-2;
    x0+=1;
    y0+=1;
    
    int spf;
	gtk_widget_style_get(GTK_WIDGET(wi), "icon-set", &spf, NULL);
    if (spf == 1000)  {
	cairo_move_to  (cr, x0, y0 + radius);
	cairo_curve_to (cr, x0 , y0, x0 , y0, x0 + radius, y0);
	cairo_line_to (cr, x1 - radius, y0);
	cairo_curve_to (cr, x1, y0, x1, y0, x1, y0 + radius);
	cairo_line_to (cr, x1 , y1 - radius);
	cairo_curve_to (cr, x1, y1, x1, y1, x1 - radius, y1);
	cairo_line_to (cr, x0 + radius, y1);
	cairo_curve_to (cr, x0, y1, x0, y1, x0, y1- radius);
	cairo_close_path (cr);
	cairo_stroke (cr);
	return;
    }


	cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
	cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.0);
	cairo_paint(cr);
	cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
	
	GdkPixbuf * stock_image =
		gtk_widget_render_icon_pixbuf(wi,get_widget_id(wi),(GtkIconSize)-1);

	guchar *pb_pixel = gdk_pixbuf_get_pixels (stock_image);
	gint pixbuf_rowstride = gdk_pixbuf_get_rowstride (stock_image);
	gint width = gdk_pixbuf_get_width (stock_image);
	gint height = gdk_pixbuf_get_height (stock_image);
	cairo_surface_t *s_image =
		cairo_image_surface_create_for_data
		(pb_pixel,CAIRO_FORMAT_RGB24 ,width, height,pixbuf_rowstride);

	pat = cairo_pattern_create_for_surface(s_image);
	cairo_set_source (cr, pat);
	cairo_pattern_set_extend(cairo_get_source(cr), CAIRO_EXTEND_REPEAT);
	
	cairo_move_to  (cr, x0, y0 + radius);
	cairo_curve_to (cr, x0 , y0, x0 , y0, x0 + radius, y0);
	cairo_line_to (cr, x1 - radius, y0);
	cairo_curve_to (cr, x1, y0, x1, y0, x1, y0 + radius);
	cairo_line_to (cr, x1 , y1 - radius);
	cairo_curve_to (cr, x1, y1, x1, y1, x1 - radius, y1);
	cairo_line_to (cr, x0 + radius, y1);
	cairo_curve_to (cr, x0, y1, x0, y1, x0, y1- radius);
	cairo_close_path (cr);
	
	cairo_fill(cr);
	g_object_unref(stock_image);
	cairo_surface_destroy(s_image);
	
	pat = cairo_pattern_create_linear (x0, y0, x0, y0+rect_height);
    //cairo_pattern_create_radial (-50, y0, 5,rect_width-10,  rect_height, 20.0);
	set_skin_color(wi, pat);
	cairo_set_source (cr, pat);
    
    
    x1+=2;
	y1+=2;
    x0-=1;
    y0-=1;
	cairo_move_to  (cr, x0, y0 + radius);
	cairo_curve_to (cr, x0 , y0, x0 , y0, x0 + radius, y0);
	cairo_line_to (cr, x1 - radius, y0);
	cairo_curve_to (cr, x1, y0, x1, y0, x1, y0 + radius);
	cairo_line_to (cr, x1 , y1 - radius);
	cairo_curve_to (cr, x1, y1, x1, y1, x1 - radius, y1);
	cairo_line_to (cr, x0 + radius, y1);
	cairo_curve_to (cr, x0, y1, x0, y1, x0, y1- radius);
	cairo_close_path (cr);
    
    
	//cairo_rectangle (cr, x0+1,y0+1,rect_width-2,rect_height-1);
	cairo_fill (cr);
	cairo_pattern_destroy (pat);
}

static void rack_expose (GtkWidget *wi, cairo_t *cr) {
    //rectangle_skin_color_expose(wi, cr);
    draw_watermark(wi, cr);
}

static void live_box_expose (GtkWidget *wi, cairo_t *cr) {
	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);
	GxPaintBox *paintbox = GX_PAINT_BOX(wi);
	gint w	    = allocation.width;
	gint h	    = allocation.height;
	static int spf, opf, rel = 0;
	gtk_widget_style_get(GTK_WIDGET(wi), "icon-set", &spf, NULL);
	gtk_widget_style_get(GTK_WIDGET(wi), "force-reload", &rel, NULL);

	static double ne_w = 0.;
	if (rel || spf != opf || ne_w != w*h || !(GDK_IS_PIXBUF (paintbox->priv->gxr_image))) {
		ne_w = w*h;
		opf = spf;
		while (G_IS_OBJECT(paintbox->priv->gxr_image)) {
			g_object_unref(paintbox->priv->gxr_image);
		}
		GdkPixbuf  *stock_image = gtk_widget_render_icon_pixbuf(
			wi,get_amp_id(wi),(GtkIconSize)-1);
		paintbox->priv->gxr_image = gdk_pixbuf_scale_simple(
			stock_image, allocation.width, allocation.height, GDK_INTERP_NEAREST);
		g_object_unref(stock_image);
	}
	//cairo_set_operator(cr, CAIRO_OPERATOR_OVER);

	gdk_cairo_set_source_pixbuf(cr, paintbox->priv->gxr_image, 0, 0);

	cairo_paint (cr);
}

static void rack_handle_expose(GtkWidget *wi, cairo_t *cr)
{
	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);

	double x0      = 1;
	double y0      = 1;
	double rect_width  = allocation.width-2;
	double rect_height = allocation.height-2;
    
    double radius = 12.;
	if (rect_width<12) radius = rect_width;
	else if (rect_height<12) radius = rect_height;
	double x1,y1;

	x1=x0+rect_width-2;
	y1=y0+rect_height-2;
    x0+=1;
    y0+=1;
    cairo_pattern_t*pat3;
	pat3 = cairo_pattern_create_linear (x0, y0, x0+50, y0);
	cairo_pattern_add_color_stop_rgba(pat3, 0, 0.1, 0.1, 0.1, 0.69);
	cairo_pattern_add_color_stop_rgba(pat3, 0.2, 0.3, 0.3, 0.3, 0.0);
	cairo_pattern_add_color_stop_rgba(pat3, 0.9, 0.3, 0.3, 0.3, 0.0);
	cairo_pattern_add_color_stop_rgba(pat3, 1, 0.1, 0.1, 0.1, 0.89);
    cairo_pattern_t*pat2;
	pat2 = cairo_pattern_create_linear (x1-42, y0, x1, y0);
	cairo_pattern_add_color_stop_rgba(pat2, 1, 0.1, 0.1, 0.1, 0.89);
	cairo_pattern_add_color_stop_rgba(pat2, 0.8, 0.3, 0.3, 0.3, 0.0);
	cairo_pattern_add_color_stop_rgba(pat2, 0.1, 0.3, 0.3, 0.3, 0.0);
	cairo_pattern_add_color_stop_rgba(pat2, 0, 0.1, 0.1, 0.1, 0.69);

    cairo_pattern_t*pat1;
	pat1 = cairo_pattern_create_linear (x0, y0, x0, y0+rect_height);
	cairo_pattern_add_color_stop_rgba(pat1, 1, 0.3, 0.3, 0.3, 0.49);
	cairo_pattern_add_color_stop_rgba(pat1, 0, 0.6, 0.6, 0.6, 0.49);
	cairo_set_source (cr, pat1);
	//left handle
	cairo_move_to  (cr, x0, y0 + radius);
	cairo_curve_to (cr, x0 , y0, x0 , y0, x0 + radius, y0);
	cairo_line_to (cr, x0 +50, y0);
	cairo_line_to (cr, x0 +50, y1);
	cairo_line_to (cr, x0 + radius, y1);
	cairo_curve_to (cr, x0, y1, x0, y1, x0, y1- radius);
	cairo_close_path (cr);
	cairo_fill_preserve (cr);
	cairo_set_source (cr, pat3);
	cairo_fill_preserve (cr);
	cairo_set_source_rgba (cr, 0.1, 0.1, 0.1, 0.8);
	cairo_set_line_width (cr, 2.0);
	cairo_stroke (cr);

	// right handle
	cairo_set_source (cr, pat1);
	cairo_move_to (cr, x1 - radius, y0);
	cairo_curve_to (cr, x1, y0, x1, y0, x1, y0 + radius);
	cairo_line_to (cr, x1 , y1 - radius);
	cairo_curve_to (cr, x1, y1, x1, y1, x1 - radius, y1);
	cairo_line_to (cr, x1 -42, y1);
	cairo_line_to (cr, x1 -42, y0);
	cairo_close_path (cr);
	cairo_fill_preserve (cr);
	cairo_set_source (cr, pat2);
	cairo_fill_preserve (cr);
	
	cairo_set_source_rgba (cr, 0.1, 0.1, 0.1, 0.7);
	cairo_set_line_width (cr, 2.0);
	cairo_stroke (cr);

	cairo_pattern_destroy (pat1);
	cairo_pattern_destroy (pat2);
	cairo_pattern_destroy (pat3);
}

static void rack_unit_expose(GtkWidget *wi, cairo_t *cr)
{
	rectangle_skin_color_expose(wi, cr);
	rack_handle_expose(wi, cr);

	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);
	double x0      = 1;
	double y0      = 1;
	double rect_width  = allocation.width-2;
	double rect_height = allocation.height-2;

	GdkPixbuf  *stock_image = gtk_widget_render_icon_pixbuf(wi,"screw",(GtkIconSize)-1);
	double x1 = gdk_pixbuf_get_height(stock_image);
	double y1 = gdk_pixbuf_get_width(stock_image);
	gdk_cairo_set_source_pixbuf(cr, stock_image, x0 + 3, y0 + 5);
	cairo_paint(cr);
	gdk_cairo_set_source_pixbuf(cr, stock_image, x0 + 3, y0 + rect_height - (5 + y1));
	cairo_paint(cr);
	gdk_cairo_set_source_pixbuf(cr, stock_image, x0 + rect_width - (6 + x1),
				    y0 + rect_height - (5 + y1));
	cairo_paint(cr);
	gdk_cairo_set_source_pixbuf(cr, stock_image, x0 + rect_width - (6 + x1), y0 + 5);
	cairo_paint(cr);
	g_object_unref(stock_image);
}

static void rack_unit_shrink_expose(GtkWidget *wi, cairo_t *cr)
{
	rectangle_skin_color_expose(wi, cr);
	rack_handle_expose(wi, cr);
}

static void logo_expose(GtkWidget *wi, cairo_t *cr)
{
	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);
	GxPaintBox *paintbox = GX_PAINT_BOX(wi);
	gint x0	     = 0;
	gint y0	     = 0;
	gint w	    = allocation.width;
	gint h	    = allocation.height;
	static double x1 ;
	static double align_right; ;

	static int spf, opf, rel = 0;
	gtk_widget_style_get(GTK_WIDGET(wi), "icon-set", &spf, NULL);
	gtk_widget_style_get(GTK_WIDGET(wi), "force-reload", &rel, NULL);

	static double ne_w = 0.;
	if (rel || spf != opf || ne_w != w*h || !(GDK_IS_PIXBUF (paintbox->priv->logo_image))) {
		ne_w = w*h;
		opf = spf;
		if (G_IS_OBJECT(paintbox->priv->logo_image)) {
			g_object_unref(paintbox->priv->logo_image);
		}
		paintbox->priv->logo_image = NULL;
		paintbox->priv->logo_image = gtk_widget_render_icon_pixbuf(
			wi,get_logo_id(wi),(GtkIconSize)-1);
		x1 = gdk_pixbuf_get_width(paintbox->priv->logo_image);
		align_right = x0+w-x1;
	}
	gdk_cairo_set_source_pixbuf(cr, paintbox->priv->logo_image, align_right, y0);
	cairo_paint(cr);
}

static void rack_amp_expose(GtkWidget *wi, cairo_t *cr)
{
	rectangle_skin_color_expose(wi, cr);
	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);

	double x0      = 1;
	double y0      = 1;
	double rect_width  = allocation.width-2;
	double rect_height = allocation.height-2;
    
    double radius = 12.;
	if (rect_width<12) radius = rect_width;
	else if (rect_height<12) radius = rect_height;
	double x1,y1;

	x1=x0+rect_width-4;
	y1=y0+rect_height-4;
    x0+=2;
    y0+=2;

    cairo_pattern_t*pat1;
	pat1 = cairo_pattern_create_linear (x0, y0, x0, y0+rect_height);
	//set_box_color(wi, pat1);
	cairo_pattern_add_color_stop_rgba(pat1, 1, 0.3, 0.3, 0.3, 0.49);
	cairo_pattern_add_color_stop_rgba(pat1, 0, 0.6, 0.6, 0.6, 0.49);
	cairo_set_source (cr, pat1);
	cairo_move_to  (cr, x0, y0 + radius);
	cairo_curve_to (cr, x0 , y0, x0 , y0, x0 + radius, y0);
	cairo_line_to (cr, x0 +30, y0);
	cairo_line_to (cr, x0 +30, y1);
	cairo_line_to (cr, x0 + radius, y1);
	cairo_curve_to (cr, x0, y1, x0, y1, x0, y1- radius);
	cairo_close_path (cr);
	cairo_fill (cr);
	
	cairo_move_to  (cr, x0+30, y0);
	cairo_line_to (cr, x1-30 , y0);
	cairo_line_to (cr, x1-30 , y0+10);
	cairo_line_to (cr, x1-rect_width/3 , y0+10);
	cairo_line_to (cr, x0+30 , y0+10);
	cairo_close_path (cr);
	cairo_fill (cr);

	cairo_move_to (cr, x1 - radius, y0);
	cairo_curve_to (cr, x1, y0, x1, y0, x1, y0 + radius);
	cairo_line_to (cr, x1 , y1 - radius);
	cairo_curve_to (cr, x1, y1, x1, y1, x1 - radius, y1);
	cairo_line_to (cr, x1 -30, y1);
	cairo_line_to (cr, x1 -30, y0);
	cairo_close_path (cr);
	cairo_fill (cr);
	
	cairo_move_to  (cr, x0+30, y1);
	cairo_line_to (cr, x1-30 , y1);
	cairo_line_to (cr, x1-30 , y1-10);
	cairo_line_to (cr, x0+30 , y1-10);
	cairo_close_path (cr);
	cairo_fill (cr);
	
	cairo_rectangle(cr,x0+30, y0+10, rect_width-66 , rect_height-26);
	cairo_set_source_rgba (cr, 0.1, 0.1, 0.1, 0.7);
	cairo_set_line_width (cr, 2.0);
	cairo_stroke (cr);

	cairo_pattern_destroy (pat1);
}

static void zac_expose(GtkWidget *wi, cairo_t *cr)
{
	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);

	double x0      = 1;
	double y0      = 1;
	double rect_width  = allocation.width-2;
	double rect_height = allocation.height-3;

	cairo_rectangle (cr, x0,y0,rect_width,rect_height+3);
	cairo_pattern_t*pat =
		cairo_pattern_create_radial (200, rect_height*0.5, 5,200,  rect_height*0.5, 200.0);
	cairo_pattern_add_color_stop_rgb (pat, 0, 0.8, 0.8, 0.8);
	cairo_pattern_add_color_stop_rgb (pat, 1, 0.3, 0.3, 0.3);
	cairo_set_source (cr, pat);
	cairo_fill (cr);

	cairo_pattern_destroy (pat);
}

static void RackBox_expose(GtkWidget *wi, cairo_t *cr)
{
    int spf;
	gtk_widget_style_get(GTK_WIDGET(wi), "icon-set", &spf, NULL);
    if(spf == 7) return;
    if(spf == 1000) return;
	cairo_text_extents_t extents;
    cairo_pattern_t*pat;

	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);
	const gchar * title = gtk_widget_get_name(GTK_WIDGET(wi));

	double x0      = 0;
	double y0      = 0;
	double rect_width  = allocation.width;
	double rect_height = allocation.height;
	double x,y;

    if (spf == 6 || spf == 8) {
	if(strcmp(title,"oscilloscope")==0) return;
	GdkPixbuf * stock_image;
	if (spf == 6) {
	    stock_image =gtk_widget_render_icon_pixbuf(wi,get_widget_id2(wi),(GtkIconSize)-1);
	} else {
	    stock_image =gtk_widget_render_icon_pixbuf(wi,get_widget_id3(wi),(GtkIconSize)-1);
	}
	guchar *pb_pixel = gdk_pixbuf_get_pixels (stock_image);
	gint pixbuf_rowstride = gdk_pixbuf_get_rowstride (stock_image);
	gint width = gdk_pixbuf_get_width (stock_image);
	gint height = gdk_pixbuf_get_height (stock_image);
	cairo_surface_t *s_image = cairo_image_surface_create_for_data (pb_pixel,CAIRO_FORMAT_RGB24 ,width, height,pixbuf_rowstride);

	pat = cairo_pattern_create_for_surface(s_image);
	cairo_set_source (cr, pat);
	cairo_pattern_set_extend(cairo_get_source(cr), CAIRO_EXTEND_REPEAT);
	
	cairo_rectangle(cr,x0+4,y0+4,rect_width-8,rect_height-8);
	cairo_fill(cr);
	g_object_unref(stock_image);
	cairo_surface_destroy(s_image);
    }


	cairo_select_font_face (cr, "URW Chancery L", CAIRO_FONT_SLANT_NORMAL,
                               CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size (cr, rect_width/12);
	cairo_text_extents (cr,title , &extents);
	x = x0+rect_width/2-extents.width/2 ;
	y = y0+rect_height/2+extents.height/2 ;
	cairo_move_to(cr,x, y);
	cairo_text_path (cr,title);
	cairo_set_source_rgba (cr, 0., 0., 0., 0.1);
	cairo_fill_preserve (cr);
	cairo_set_source_rgba (cr, 0.7, 0.7, 0.7, 0.05);
    cairo_stroke (cr);

    cairo_rectangle (cr, x0,y0,rect_width,rect_height);
    cairo_set_line_width(cr, 3.0);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_stroke (cr);
    
	cairo_rectangle (cr, x0+4,y0+4,rect_width-8,rect_height-8);
	pat = cairo_pattern_create_linear (0, y0, 0, y0+rect_height);
	//set_rack_color(title, pat);
	set_box_color(wi, pat);
	//cairo_pattern_add_color_stop_rgba (pat, 1, 0, 0, 0.2, 0.8);
	//cairo_pattern_add_color_stop_rgba (pat, 0.8, 0, 0, 0, 0.8);
	
	//cairo_pattern_add_color_stop_rgba (pat, 0.2, 0, 0, 0.2, 0.2);
	cairo_set_source (cr, pat);
	cairo_fill(cr);

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

    cairo_pattern_destroy (pat);
}

static void compressor_expose(GtkWidget *wi, cairo_t *cr)
{
	cairo_text_extents_t extents;

	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);
	const gchar * title = gtk_widget_get_name(GTK_WIDGET(wi));

	double x0      = 0;
	double y0      = 0;
	double rect_width  = allocation.width;
	double rect_height = allocation.height;
	double x,y;
	
	
	

    cairo_rectangle (cr, x0,y0,rect_width,rect_height);
    cairo_set_line_width(cr, 3.0);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_stroke (cr);
    
	cairo_rectangle (cr, x0+4,y0+4,rect_width-8,rect_height-8);
	cairo_pattern_t*pat = cairo_pattern_create_linear (0, y0, 0, y0+rect_height);
	//set_rack_color(title, pat);
	cairo_pattern_add_color_stop_rgb (pat, 1, 0, 0, 0.2);
	cairo_pattern_add_color_stop_rgb (pat, 0.8, 0., 0, 0);
	cairo_pattern_add_color_stop_rgb (pat, 0.2, 0.5, 0.5, 0.5);
	cairo_pattern_add_color_stop_rgb (pat, 0, 0., 0., 0.);
	cairo_set_source (cr, pat);
	cairo_fill(cr);
	

    cairo_set_line_width(cr, 2.0);
	cairo_move_to  (cr, x0+rect_width*0.09, y0+4 );
	cairo_curve_to (cr, x0+rect_width*0.07 , y0+rect_height*0.5, x0+rect_width*0.07  , y0+rect_height*0.5, x0+rect_width*0.09 , y0+rect_height-6);
	cairo_line_to(cr, x0+rect_width*0.92, y0+rect_height-6);
	cairo_curve_to (cr, x0+rect_width*0.94 , y0+rect_height*0.5, x0+rect_width*0.94  , y0+rect_height*0.5, x0+rect_width*0.92  , y0+4);
	
	//cairo_line_to(cr, x0+rect_width-3, y0+4);
	cairo_line_to(cr, x0+rect_width*0.92, y0+4);
	pat = cairo_pattern_create_linear (0, y0, 0, y0+rect_height);
	//set_rack_color(title, pat);
	cairo_pattern_add_color_stop_rgba (pat, 1, 0, 0, 0.2, 0.8);
	cairo_pattern_add_color_stop_rgba (pat, 0.8, 0, 0, 0, 0.8);
	cairo_pattern_add_color_stop_rgba (pat, 0, 0, 0, 0, 0);
	cairo_pattern_add_color_stop_rgba (pat, 0, 0, 0, 0.2, 0.2);
	cairo_set_source (cr, pat);
	cairo_fill_preserve(cr);
	cairo_set_source_rgb (cr, 0., 0., 0.);
    cairo_stroke (cr);
    
    cairo_set_line_width(cr, 1.0);
	cairo_move_to  (cr, x0+2+rect_width*0.09, y0+4 );
	cairo_curve_to (cr, x0+2+rect_width*0.07 , y0+rect_height*0.5, x0+2+rect_width*0.07  , y0+rect_height*0.5, x0+2+rect_width*0.09 , y0+rect_height-6);
	cairo_line_to(cr, x0-2+rect_width*0.92, y0+rect_height-6);
	cairo_curve_to (cr, x0-2+rect_width*0.94 , y0+rect_height*0.5, x0-2+rect_width*0.94  , y0+rect_height*0.5, x0-2+rect_width*0.92  , y0+4);
	cairo_set_source_rgb (cr, 0.2, 0.2, 0.2);
    cairo_stroke (cr);
    
    cairo_select_font_face (cr, "URW Chancery L", CAIRO_FONT_SLANT_NORMAL,
                               CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size (cr, 12);
	cairo_text_extents (cr,title , &extents);
	x = x0+21 ;
	y = y0+rect_height*0.8+extents.height/2 ;
	
	

	cairo_move_to(cr,x, y);
	cairo_rotate (cr,270* M_PI/180);
	cairo_text_path (cr,title);
	
	cairo_set_line_width(cr, 1.0);
	cairo_set_source_rgb (cr, 0.9, 0.9, 1);
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

    cairo_pattern_destroy (pat);
}

static void line_expose(GtkWidget *wi, cairo_t *cr)
{
	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);

	gint x0      = 3;
	gint y0      = 3;
	gint rect_width  = allocation.width-6;
	gint rect_height = allocation.height-6;


	double radius = 12.;
	if (rect_width<12) radius = rect_width;
	else if (rect_height<12) radius = rect_height;
	double x1,y1;

	x1=x0+rect_width;
	y1=y0+rect_height;

	cairo_move_to  (cr, x0, y0 + radius);
	cairo_curve_to (cr, x0 , y0, x0 , y0, x0 + radius, y0);
	cairo_line_to (cr, x1 - radius, y0);
	cairo_curve_to (cr, x1, y0, x1, y0, x1, y0 + radius);
	cairo_line_to (cr, x1 , y1 - radius);
	cairo_curve_to (cr, x1, y1, x1, y1, x1 - radius, y1);
	cairo_line_to (cr, x0 + radius, y1);
	cairo_curve_to (cr, x0, y1, x0, y1, x0, y1- radius);
	cairo_close_path (cr);
    cairo_set_line_width(cr, 4.0);
    cairo_set_source_rgb(cr, 0.2, 0.2, 0.2);
    cairo_stroke_preserve(cr);
    cairo_set_line_width(cr, 1.0);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_stroke(cr);
}

static void gxhead_expose(GtkWidget *wi, cairo_t *cr)
{
	GxPaintBox *paintbox =  GX_PAINT_BOX(wi);
	
	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);
	gint x0      = 1;
	gint y0      = 1;
	gint rect_width  = allocation.width-2;
	gint rect_height = allocation.height-3;

	static int nf = 0;
	static double ne_w1 = 0.;
	int spf;

	gtk_widget_style_get(GTK_WIDGET(wi), "icon-set", &spf, NULL);
    if (spf == 1000) return;
    if (spf >= 7) {
        rack_amp_expose(wi, cr);
        line_expose(wi, cr);
        if ( spf <10) {
        paintbox->priv->gxh_image = gtk_widget_render_icon_pixbuf(wi,"guitarix",(GtkIconSize)-1);
        gdk_cairo_set_source_pixbuf(cr, paintbox->priv->gxh_image, x0 + 38, y0 + 20);
        cairo_rectangle(cr, x0 + 38, y0 + 20, 131, 26);
        cairo_fill(cr);
        g_object_unref(paintbox->priv->gxh_image);
        paintbox->priv->gxh_image = NULL;
        }
        GdkPixbuf  *stock_image = gtk_widget_render_icon_pixbuf(wi,"screw",(GtkIconSize)-1);
        double x1 = gdk_pixbuf_get_height(stock_image);
        double y1 = gdk_pixbuf_get_width(stock_image);
        gdk_cairo_set_source_pixbuf(cr, stock_image, x0 + 5, y0 + 5);
        cairo_paint(cr);
        gdk_cairo_set_source_pixbuf(cr, stock_image, x0 + 5, y0 + rect_height - (5 + y1));
        cairo_paint(cr);
        gdk_cairo_set_source_pixbuf(cr, stock_image, x0 + rect_width - (5 + x1),
                                    y0 + rect_height -(5 + y1));
        cairo_paint(cr);
        gdk_cairo_set_source_pixbuf(cr, stock_image, x0 + rect_width - (5 + x1), y0 + 5);
        cairo_paint(cr);
        g_object_unref(stock_image);
        return;
    }

	if (nf != spf || ne_w1 != rect_width*rect_height || !(GDK_IS_PIXBUF (paintbox->priv->gxh_image))) {
		ne_w1 = rect_width*rect_height;
		nf = spf;
		if (G_IS_OBJECT(paintbox->priv->gxh_image)) {
			g_object_unref(paintbox->priv->gxh_image);
            paintbox->priv->gxh_image = NULL;
		}
		GdkPixbuf  *stock_image, *frame;
		stock_image = gtk_widget_render_icon_pixbuf(wi,get_stock_id(wi),(GtkIconSize)-1);
		double scalew = rect_width/double(gdk_pixbuf_get_width(stock_image)-48);
		double scaleh = rect_height/double(gdk_pixbuf_get_height(stock_image)-48);
		
		paintbox->priv->gxh_image = gdk_pixbuf_scale_simple(
			stock_image, rect_width, rect_height, GDK_INTERP_NEAREST);
		// upper border
		frame = gdk_pixbuf_new_subpixbuf(
			stock_image,24,0,gdk_pixbuf_get_width(stock_image)-48,12);
		gdk_pixbuf_scale (
			frame, paintbox->priv->gxh_image,0,0,rect_width,12,0,0,scalew,1,GDK_INTERP_BILINEAR);
		// under border
		frame = gdk_pixbuf_new_subpixbuf(
			stock_image,24,gdk_pixbuf_get_height(stock_image)-12,
			gdk_pixbuf_get_width(stock_image)-48,12);
		gdk_pixbuf_scale (
			frame,paintbox->priv->gxh_image,0,gdk_pixbuf_get_height(paintbox->priv->gxh_image)-12,
			rect_width,12,0,gdk_pixbuf_get_height(paintbox->priv->gxh_image)-12,
			scalew,1,GDK_INTERP_BILINEAR);
		// left border
		frame = gdk_pixbuf_new_subpixbuf(
			stock_image,0,24,12,gdk_pixbuf_get_height(stock_image)-48);	
		gdk_pixbuf_scale(
			frame, paintbox->priv->gxh_image,0,12,12,rect_height-24,0,0,1,scaleh,GDK_INTERP_BILINEAR);
		// right border	
		frame = gdk_pixbuf_new_subpixbuf(
			stock_image,gdk_pixbuf_get_width(stock_image)-12,
			24,12,gdk_pixbuf_get_height(stock_image)-48);
		gdk_pixbuf_scale(
			frame,paintbox->priv->gxh_image,gdk_pixbuf_get_width(paintbox->priv->gxh_image)-12,
			12,12,rect_height-24,gdk_pixbuf_get_width(paintbox->priv->gxh_image)-12,
			0,1,scaleh,GDK_INTERP_BILINEAR);
		//left upper corner
		frame = gdk_pixbuf_new_subpixbuf(
			stock_image,0,0,20,20);
		gdk_pixbuf_scale (
			frame, paintbox->priv->gxh_image,0,0,20,20,0,0,1,1,GDK_INTERP_BILINEAR);
		//right upper corner
		frame = gdk_pixbuf_new_subpixbuf(
			stock_image,gdk_pixbuf_get_width(stock_image)-20,0,20,20);
		gdk_pixbuf_scale (
			frame, paintbox->priv->gxh_image,gdk_pixbuf_get_width(paintbox->priv->gxh_image)-20,
			0,20,20,gdk_pixbuf_get_width(paintbox->priv->gxh_image)-20,0,1,1,
			GDK_INTERP_BILINEAR);
		//left under corner
		frame = gdk_pixbuf_new_subpixbuf(
			stock_image,0,gdk_pixbuf_get_height(stock_image)-20,20,20);
		gdk_pixbuf_scale (
			frame, paintbox->priv->gxh_image,0,gdk_pixbuf_get_height(paintbox->priv->gxh_image)-20,
			20,20,0,gdk_pixbuf_get_height(paintbox->priv->gxh_image)-20,1,1,
			GDK_INTERP_BILINEAR);
		//right under corner
		frame = gdk_pixbuf_new_subpixbuf(
			stock_image,gdk_pixbuf_get_width(stock_image)-20,
			gdk_pixbuf_get_height(stock_image)-20,20,20);
		gdk_pixbuf_scale (
			frame, paintbox->priv->gxh_image,gdk_pixbuf_get_width(paintbox->priv->gxh_image)-20,
			gdk_pixbuf_get_height(paintbox->priv->gxh_image)-20,
			20,20,gdk_pixbuf_get_width(paintbox->priv->gxh_image)-20,
			gdk_pixbuf_get_height(paintbox->priv->gxh_image)-20,1,1,
			GDK_INTERP_BILINEAR);
				
		// base 
		frame = gdk_pixbuf_new_subpixbuf(
			stock_image,32,24,gdk_pixbuf_get_width(stock_image)-68,
			gdk_pixbuf_get_height(stock_image)-48);
		gdk_pixbuf_scale (
			frame, paintbox->priv->gxh_image,12,12,rect_width-24,rect_height-24,
			12,12,scalew,scaleh,GDK_INTERP_TILES);
		//g_object_unref(_image);
		g_object_unref(stock_image);
		g_object_unref(frame);
	}
	// draw to display
	gdk_cairo_set_source_pixbuf(cr, paintbox->priv->gxh_image, x0, y0);
	cairo_rectangle(cr, x0, y0, rect_width, rect_height);
	cairo_fill(cr);
}

static void gxrack_expose(GtkWidget *wi, cairo_t *cr)
{
    int spf;
	gtk_widget_style_get(GTK_WIDGET(wi), "icon-set", &spf, NULL);
    if (spf == 1000)  return;
	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);
	gint rect_width  = allocation.width-2;
	gint rect_height = allocation.height-3;
	if (rect_width <= 0 || rect_height <= 0) {
	    return;
	}
	GxPaintBox *paintbox = GX_PAINT_BOX(wi);

	gint x0      = 1;
	gint y0      = 1;

	static double ne_w = 0.;
	if (ne_w != rect_width*rect_height || !(GDK_IS_PIXBUF (paintbox->priv->gxr_image))) {
		ne_w = rect_width*rect_height;
		if (G_IS_OBJECT(paintbox->priv->gxr_image)) {
			g_object_unref(paintbox->priv->gxr_image);
		}
		GdkPixbuf  *stock_image, *frame;
		stock_image = gtk_widget_render_icon_pixbuf(wi,get_stock_id(wi),(GtkIconSize)-1);
		double scalew = rect_width/double(gdk_pixbuf_get_width(stock_image)-48);
		double scaleh = rect_height/double(gdk_pixbuf_get_height(stock_image)-48);
		
		paintbox->priv->gxr_image = gdk_pixbuf_scale_simple(
			stock_image, rect_width, rect_height, GDK_INTERP_NEAREST);
		// upper border
		frame = gdk_pixbuf_new_subpixbuf(
			stock_image,24,0,gdk_pixbuf_get_width(stock_image)-48,12);
		gdk_pixbuf_scale (
			frame, paintbox->priv->gxr_image,0,0,rect_width,12,0,0,scalew,1,GDK_INTERP_BILINEAR);
		// under border
		frame = gdk_pixbuf_new_subpixbuf(
			stock_image,24,gdk_pixbuf_get_height(stock_image)-12,
			gdk_pixbuf_get_width(stock_image)-48,12);
		gdk_pixbuf_scale (
			frame,paintbox->priv->gxr_image,0,gdk_pixbuf_get_height(paintbox->priv->gxr_image)-12,
			rect_width,12,0,gdk_pixbuf_get_height(paintbox->priv->gxr_image)-12,
			scalew,1,GDK_INTERP_BILINEAR);
		// left border
		frame = gdk_pixbuf_new_subpixbuf(
			stock_image,0,24,12,gdk_pixbuf_get_height(stock_image)-48);
		gdk_pixbuf_scale(
			frame, paintbox->priv->gxr_image,0,12,12,rect_height-24,0,0,1,scaleh,GDK_INTERP_BILINEAR);
		// right border	
		frame = gdk_pixbuf_new_subpixbuf(
			stock_image,gdk_pixbuf_get_width(stock_image)-12,
			24,12,gdk_pixbuf_get_height(stock_image)-48);
		gdk_pixbuf_scale(
			frame,paintbox->priv->gxr_image,gdk_pixbuf_get_width(paintbox->priv->gxr_image)-12,
			12,12,rect_height-24,gdk_pixbuf_get_width(paintbox->priv->gxr_image)-12,
			0,1,scaleh,GDK_INTERP_BILINEAR);
		//left upper corner
		frame = gdk_pixbuf_new_subpixbuf(
			stock_image,0,0,20,20);
		gdk_pixbuf_scale (
			frame, paintbox->priv->gxr_image,0,0,20,20,0,0,1,1,GDK_INTERP_BILINEAR);
		//right upper corner
		frame = gdk_pixbuf_new_subpixbuf(
			stock_image,gdk_pixbuf_get_width(stock_image)-20,0,20,20);
		gdk_pixbuf_scale (
			frame, paintbox->priv->gxr_image,gdk_pixbuf_get_width(paintbox->priv->gxr_image)-20,
			0,20,20,gdk_pixbuf_get_width(paintbox->priv->gxr_image)-20,0,1,1,
			GDK_INTERP_BILINEAR);
		//left under corner
		frame = gdk_pixbuf_new_subpixbuf(
			stock_image,0,gdk_pixbuf_get_height(stock_image)-20,20,20);
		gdk_pixbuf_scale (
			frame, paintbox->priv->gxr_image,0,gdk_pixbuf_get_height(paintbox->priv->gxr_image)-20,
			20,20,0,gdk_pixbuf_get_height(paintbox->priv->gxr_image)-20,1,1,
			GDK_INTERP_BILINEAR);
		//right under corner
		frame = gdk_pixbuf_new_subpixbuf(
			stock_image,gdk_pixbuf_get_width(stock_image)-20,
			gdk_pixbuf_get_height(stock_image)-20,20,20);
		gdk_pixbuf_scale (
			frame, paintbox->priv->gxr_image,gdk_pixbuf_get_width(paintbox->priv->gxr_image)-20,
			gdk_pixbuf_get_height(paintbox->priv->gxr_image)-20,
			20,20,gdk_pixbuf_get_width(paintbox->priv->gxr_image)-20,
			gdk_pixbuf_get_height(paintbox->priv->gxr_image)-20,1,1,
			GDK_INTERP_BILINEAR);
		g_object_unref(stock_image);
		g_object_unref(frame);
	}
	
	// draw to display
	gdk_cairo_set_source_pixbuf (cr, paintbox->priv->gxr_image, x0, y0);
	cairo_rectangle(cr, x0, y0, rect_width, rect_height);
	cairo_fill(cr);

	// base 
	x0      += 12;
	y0      += 12;
	rect_width  -= 24;
	rect_height -= 24;
	
	cairo_rectangle (cr, x0-1,y0-1,rect_width+2,rect_height+2);
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_fill (cr);

	cairo_pattern_t*pat =
	cairo_pattern_create_linear (0, y0, 0, y0+rect_height);
	//cairo_pattern_create_radial (-50, y0, 5,rect_width-10,  rect_height, 20.0);
	set_skin_color(wi, pat);
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

	cairo_pattern_destroy (pat);
}

static void amp_skin_expose(GtkWidget *wi, cairo_t *cr)
{
	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);
    GxPaintBox *paintbox = GX_PAINT_BOX(wi);
	gint x0      = 0;
	gint y0      = 0;
	gint w      = allocation.width;
	gint h      = allocation.height;
    static int spf, opf, rel = 0;
    gtk_widget_style_get(GTK_WIDGET(wi), "icon-set", &spf, NULL);
    gtk_widget_style_get(GTK_WIDGET(wi), "force-reload", &rel, NULL);
    
    static double ne_w = 0.;
	if (rel || spf != opf || ne_w != w*h || !(GDK_IS_PIXBUF (paintbox->priv->gxr_image))) {
		ne_w = w*h;
        opf = spf;
        while (G_IS_OBJECT(paintbox->priv->gxr_image)) {
			g_object_unref(paintbox->priv->gxr_image);
		}
        GdkPixbuf  *stock_image = gtk_widget_render_icon_pixbuf(
            wi,get_amp_id(wi),(GtkIconSize)-1);
        paintbox->priv->gxr_image = gdk_pixbuf_scale_simple(
			stock_image, allocation.width, allocation.height , GDK_INTERP_NEAREST);
        g_object_unref(stock_image);
    }
    GdkPixbuf *pixbuf = gdk_pixbuf_scale_simple(paintbox->priv->gxr_image, w, h,
                                                GDK_INTERP_NEAREST);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, x0, y0);
    cairo_paint(cr);
    g_object_unref(pixbuf);
}

static void level_meter_expose(GtkWidget *wi, cairo_t *cr)
{
	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);
	cairo_set_font_size (cr, 7.0);

	double x0      = 1;
	double y0      = 2;
	double rect_width  = allocation.width-2;
	double rect_height = allocation.height-4;

	int  db_points[] = { -50, -40, -30, -20, -10, -3, 0, 4 };
	char  buf[32];

	cairo_rectangle (cr, x0,y0,rect_width,rect_height+2);
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_fill (cr);

	cairo_pattern_t*pat = cairo_pattern_create_linear (0, y0, 0, y0+rect_height);
		//cairo_pattern_create_radial (-50, y0, 5,rect_width-10,  rect_height, 20.0);
	cairo_pattern_add_color_stop_rgb (pat, 0, 0.1, 0.1, 0.2);
	cairo_pattern_add_color_stop_rgb (pat, 0.3, 0.06, 0.06, 0.07);
	cairo_pattern_add_color_stop_rgb (pat, 1, 0.03, 0.03, 0.03);
	cairo_set_source (cr, pat);
	cairo_rectangle (cr, x0+1,y0+1,rect_width-2,rect_height-2);
	cairo_fill_preserve (cr);
	
	pat = cairo_pattern_create_linear (x0, 0, x0+rect_width, 0);
	cairo_pattern_add_color_stop_rgba (pat, 0.3, 0.01, 0.01, 0.02, 0.3);
	cairo_pattern_add_color_stop_rgba (pat, 0.5, 0.6, 0.6, 0.7, 0.5);
	cairo_pattern_add_color_stop_rgba (pat, 0.7, 0.01, 0.01, 0.01, 0.3);
	cairo_set_source (cr, pat);
	cairo_rectangle (cr, x0+1,y0+1,rect_width-2,rect_height-2);
	cairo_fill (cr);

	for (unsigned int i = 0; i < sizeof (db_points)/sizeof (db_points[0]); ++i)
	{
		float fraction = log_meter(db_points[i]);
		cairo_set_source_rgb (cr,0.32 + 0.22*i/2,0.5 +  0.1*i/2, 0.1);

		cairo_move_to (cr, x0+rect_width*0.2,y0+rect_height - (rect_height * fraction));
		cairo_line_to (cr, x0+rect_width*0.8 ,y0+rect_height -  (rect_height * fraction));
		if (i<6)
		{
			snprintf (buf, sizeof (buf), "%d", db_points[i]);
			cairo_move_to (cr, x0+rect_width*0.32,y0+rect_height - (rect_height * fraction));
		}
		else
		{
			snprintf (buf, sizeof (buf), " %d", db_points[i]);
			cairo_move_to (cr, x0+rect_width*0.34,y0+rect_height - (rect_height * fraction));
		}
		cairo_show_text (cr, buf);
	}

	cairo_set_source_rgb (cr, 0.4, 0.8, 0.4);
	cairo_set_line_width (cr, 0.5);
	cairo_stroke (cr);

	cairo_pattern_destroy (pat);
}

static void simple_level_meter_expose(GtkWidget *wi, cairo_t *cr)
{
	GtkAllocation allocation;
	gtk_widget_get_allocation(wi, &allocation);
	cairo_set_font_size (cr, 7.0);

	double x0      = 1;
	double y0      = 2;
	double rect_width  = allocation.width-2;
	double rect_height = allocation.height-4;

	int  db_points[] = { -50, -40, -30, -20, -10, -3, 0, 4 };
	char  buf[32];

	int rad = 6;
	gx_draw_inset(cr, x0, y0, rect_width,rect_height, rad, 1);

	gx_draw_glass(cr, x0, y0, rect_width,rect_height, rad);

	cairo_pattern_t*pat = cairo_pattern_create_linear (x0, 0, x0+rect_width, 0);
	cairo_pattern_add_color_stop_rgba (pat, 0.3, 0.01, 0.01, 0.02, 0.3);
	cairo_pattern_add_color_stop_rgba (pat, 0.5, 0.2, 0.2, 0.2, 0.3);
	cairo_pattern_add_color_stop_rgba (pat, 1, 0.01, 0.01, 0.01, 0.3);
	cairo_set_source (cr, pat);
	cairo_rectangle (cr, x0+1,y0+1,rect_width-2,rect_height-2);
	cairo_fill (cr);

	for (unsigned int i = 0; i < sizeof (db_points)/sizeof (db_points[0]); ++i)
	{
		float fraction = log_meter(db_points[i]);
		cairo_set_source_rgb (cr,0.32 + 0.22*i/2,0.5 +  0.1*i/2, 0.1);

		cairo_move_to (cr, x0+rect_width*0.2,y0+rect_height - (rect_height * fraction));
		cairo_line_to (cr, x0+rect_width ,y0+rect_height -  (rect_height * fraction));
		if (i<6)
		{
			snprintf (buf, sizeof (buf), "%d", db_points[i]);
			cairo_move_to (cr, x0+rect_width*0.46,y0+rect_height - (rect_height * fraction));
		}
		else
		{
			snprintf (buf, sizeof (buf), " %d", db_points[i]);
			cairo_move_to (cr, x0+rect_width*0.48,y0+rect_height - (rect_height * fraction));
		}
		cairo_show_text (cr, buf);
	}

	cairo_set_source_rgb (cr, 0.4, 0.8, 0.4);
	cairo_set_line_width (cr, 0.5);
	cairo_stroke (cr);

	cairo_pattern_destroy (pat);
}

static void set_expose_func(GxPaintBox *paint_box, const gchar *paint_func)
{
	if (strcmp(paint_func, "rectangle_skin_color_expose") == 0) {
		paint_box->priv->draw_func = rectangle_skin_color_expose;
	} else if (strcmp(paint_func, "rack_unit_expose") == 0) {
		paint_box->priv->draw_func = rack_unit_expose;
	} else if (strcmp(paint_func, "rack_unit_shrink_expose") == 0) {
		paint_box->priv->draw_func = rack_unit_shrink_expose;
	} else if (strcmp(paint_func, "rack_amp_expose") == 0) {
		paint_box->priv->draw_func = rack_amp_expose;
	} else if (strcmp(paint_func, "zac_expose") == 0) {
		paint_box->priv->draw_func = zac_expose;
	} else if (strcmp(paint_func, "gxhead_expose") == 0) {
		paint_box->priv->draw_func = gxhead_expose;
	} else if (strcmp(paint_func, "RackBox_expose") == 0) {
		paint_box->priv->draw_func = RackBox_expose;
	} else if (strcmp(paint_func, "gxrack_expose") == 0) {
		paint_box->priv->draw_func = gxrack_expose;
	} else if (strcmp(paint_func, "compressor_expose") == 0) {
		paint_box->priv->draw_func = compressor_expose;
	} else if (strcmp(paint_func, "simple_level_meter_expose") == 0) {
	    paint_box->priv->draw_func = simple_level_meter_expose;
	} else if (strcmp(paint_func, "level_meter_expose") == 0) {
	    paint_box->priv->draw_func = level_meter_expose;
	} else if (strcmp(paint_func, "amp_skin_expose") == 0) {
	    paint_box->priv->draw_func = amp_skin_expose;
	} else if (strcmp(paint_func, "gx_rack_unit_expose") == 0) {
		paint_box->priv->draw_func = gx_rack_unit_expose;
	} else if (strcmp(paint_func, "gx_rack_unit_shrink_expose") == 0) {
		paint_box->priv->draw_func = gx_rack_unit_shrink_expose;
	} else if (strcmp(paint_func, "gx_rack_amp_expose") == 0) {
		paint_box->priv->draw_func = gx_rack_amp_expose;
	} else if (strcmp(paint_func, "gx_lv2_unit_expose") == 0) {
		paint_box->priv->draw_func = gx_lv2_unit_expose;
	} else if (strcmp(paint_func, "draw_skin") == 0) {
		paint_box->priv->draw_func = draw_skin;
	} else if (strcmp(paint_func, "rack_expose") == 0) {
		paint_box->priv->draw_func = rack_expose;
	} else if (strcmp(paint_func, "box_uni_1_expose") == 0) {
		paint_box->priv->draw_func = box_uni_1_expose;
    } else if (strcmp(paint_func, "box_uni_2_expose") == 0) {
		paint_box->priv->draw_func = box_uni_2_expose;
    } else if (strcmp(paint_func, "box_skin_expose") == 0) {
		paint_box->priv->draw_func = box_skin_expose;
    } else if (strcmp(paint_func, "live_box_expose") == 0) {
		paint_box->priv->draw_func = live_box_expose;
    } else if (strcmp(paint_func, "logo_expose") == 0) {
		paint_box->priv->draw_func = logo_expose;
    } else {
		paint_box->priv->draw_func = 0;
	}
}

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

#include "GxToggleImage.h"

#define P_(s) (s)   // FIXME -> gettext

struct _GxToggleImagePrivate {
	gchar *var_id;
	gchar *base_name;
};

enum {
	PROP_BASE_NAME = 1,
	PROP_VAR_ID ,
};

G_DEFINE_TYPE_WITH_PRIVATE(GxToggleImage, gx_toggle_image, GTK_TYPE_WIDGET)

#define GX_TOGGLE_IMAGE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), GX_TYPE_TOGGLE_IMAGE, GxToggleImagePrivate))

static void gx_toggle_image_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gx_toggle_image_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static void gx_toggle_image_destroy (GtkWidget *obj);
static void gx_toggle_image_get_preferred_width (GtkWidget *widget, gint *min_width, gint *natural_width);
static void gx_toggle_image_get_preferred_height (GtkWidget *widget, gint *min_height, gint *natural_height);
static void gx_toggle_image_size_request (GtkWidget *widget, gint *width, gint *height);
static gint gx_toggle_image_draw (
	GtkWidget * widget, cairo_t * cr);

static void gx_toggle_image_class_init(GxToggleImageClass *klass)
{
	GObjectClass   *gobject_class = G_OBJECT_CLASS (klass);
	GtkWidgetClass *widget_class = (GtkWidgetClass*)klass;

	gobject_class->set_property = gx_toggle_image_set_property;
	gobject_class->get_property = gx_toggle_image_get_property;
	widget_class->destroy = gx_toggle_image_destroy;
	widget_class->get_preferred_width = gx_toggle_image_get_preferred_width;
	widget_class->get_preferred_height = gx_toggle_image_get_preferred_height;
	widget_class->draw = gx_toggle_image_draw;

	g_object_class_install_property(
		gobject_class, PROP_BASE_NAME,
		g_param_spec_string("base-name",
		                    P_("Image base name"),
		                    P_("Base name of the image, append \"_on\" and \"_off\" for the stock names"),
		                    "switch",
		                    GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property (
		gobject_class, PROP_VAR_ID, g_param_spec_string(
			"var-id", P_("Variable"),
			P_("The id of the linked variable"),
			NULL, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
}

static void gx_toggle_image_init(GxToggleImage *toggle_image)
{
	toggle_image->priv = GX_TOGGLE_IMAGE_GET_PRIVATE(toggle_image);
	toggle_image->priv->base_name = g_strdup("switch");
	gtk_widget_set_has_window(GTK_WIDGET(toggle_image), FALSE);
}

static void gx_toggle_image_destroy (GtkWidget *obj)
{
	GxToggleImage *toggle_image = GX_TOGGLE_IMAGE(obj);
	g_free(toggle_image->priv->base_name);
	toggle_image->priv->base_name = 0;
	GTK_WIDGET_CLASS(gx_toggle_image_parent_class)->destroy(obj);
}

static void gx_toggle_image_get_preferred_width (GtkWidget *widget, gint *min_width, gint *natural_width)
{
	gint width, height;
	gx_toggle_image_size_request(widget, &width, &height);

	if (min_width) {
		*min_width = width;
	}
	if (natural_width) {
		*natural_width = width;
	}
}

static void gx_toggle_image_get_preferred_height (GtkWidget *widget, gint *min_height, gint *natural_height)
{
	gint width, height;
	gx_toggle_image_size_request(widget, &width, &height);

	if (min_height) {
		*min_height = height;
	}
	if (natural_height) {
		*natural_height = height;
	}
}

static void gx_toggle_image_size_request (GtkWidget *widget, gint *width, gint *height)
{
	GxToggleImage *toggle_image = GX_TOGGLE_IMAGE(widget);
	char *s = g_strconcat(toggle_image->priv->base_name, "_on", NULL);
	GdkPixbuf *img = gtk_icon_theme_load_icon(gtk_icon_theme_get_default(), s, -1,
											  GTK_ICON_LOOKUP_GENERIC_FALLBACK, nullptr);
	g_free(s);
	if (GDK_IS_PIXBUF (img)) {
		gint xpad, ypad;
		xpad = gtk_widget_get_margin_start(widget) + gtk_widget_get_margin_end(widget);
		ypad = gtk_widget_get_margin_top(widget) + gtk_widget_get_margin_bottom(widget);
		*width = gdk_pixbuf_get_width(img) + xpad * 2;
		*height = gdk_pixbuf_get_height(img) + ypad * 2;
		g_object_unref(img);
	}
}

static gboolean gx_toggle_image_draw(GtkWidget *widget, cairo_t *cr)
{
	GxToggleImage *toggle_image = GX_TOGGLE_IMAGE(widget);
	const char *s = "_off";
	GtkWidget *p = gtk_widget_get_ancestor(widget, GTK_TYPE_TOGGLE_BUTTON);
	if (p && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(p))) {
		s = "_on";
	}
	char *nm = g_strconcat(toggle_image->priv->base_name, s, NULL);
	GdkPixbuf *img = gtk_icon_theme_load_icon(gtk_icon_theme_get_default(), nm, -1,
											  GTK_ICON_LOOKUP_GENERIC_FALLBACK, nullptr);
	g_free(nm);
	if (!img) {
		return FALSE;
	}
	GtkAllocation allocation;
	gtk_widget_get_allocation(widget, &allocation);
	int x = (allocation.width - gdk_pixbuf_get_width(img)) / 2;
	int y = (allocation.height - gdk_pixbuf_get_height(img)) / 2;
	gdk_cairo_set_source_pixbuf (cr, img, x, y);
	cairo_paint (cr);
	g_object_unref(img);
	return FALSE;
}

const char *gx_toggle_image_get_base_name(GxToggleImage *toggle_image)
{
	g_return_val_if_fail(GX_IS_TOGGLE_IMAGE(toggle_image), "");
	return toggle_image->priv->base_name;
}

void gx_toggle_image_set_base_name(GxToggleImage *toggle_image, const char *base_name)
{
	g_free(toggle_image->priv->base_name);
	toggle_image->priv->base_name = g_strdup(base_name ? base_name : "");
	gtk_widget_queue_resize(GTK_WIDGET(toggle_image));
	g_object_notify(G_OBJECT(toggle_image), "base-name");
}

static void
gx_toggle_image_set_property (GObject *object, guint prop_id, const GValue *value,
                              GParamSpec *pspec)
{
	GxToggleImage *toggle_image = GX_TOGGLE_IMAGE (object);

	switch(prop_id) {
	case PROP_BASE_NAME:
		gx_toggle_image_set_base_name(toggle_image, g_value_get_string(value));
		break;
	case PROP_VAR_ID: {
		const char *str = g_value_get_string(value);
		g_free(toggle_image->priv->var_id);
		toggle_image->priv->var_id = g_strdup(str ? str : "");
		g_object_notify(object, "var-id");
		break;
	}
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
gx_toggle_image_get_property(GObject *object, guint prop_id, GValue *value,
                             GParamSpec *pspec)
{
	GxToggleImage *toggle_image = GX_TOGGLE_IMAGE(object);

	switch(prop_id) {
	case PROP_BASE_NAME:
		g_value_set_string(value, toggle_image->priv->base_name);
		break;
	case PROP_VAR_ID:
		g_value_set_string(value, toggle_image->priv->var_id);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

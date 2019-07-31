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

/****************************************************************
 ** GxRadioButton
 */

#include "GxRadioButton.h"

#define P_(s) (s)   // FIXME -> gettext

struct _GxRadioButtonPrivate
{
	gchar *base_name;
};

enum {
	PROP_BASE_NAME = 1,
};

static void gx_radio_button_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gx_radio_button_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static void gx_radio_button_destroy (GtkWidget *obj);
static void draw_indicator(GtkCheckButton *check_button, cairo_t *cr);

G_DEFINE_TYPE_WITH_PRIVATE(GxRadioButton, gx_radio_button, GTK_TYPE_RADIO_BUTTON);

#define GX_RADIO_BUTTON_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), GX_TYPE_RADIO_BUTTON, GxRadioButtonPrivate))

static void gx_radio_button_class_init(GxRadioButtonClass *klass)
{
	GObjectClass   *gobject_class = G_OBJECT_CLASS (klass);
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);
	gobject_class->set_property = gx_radio_button_set_property;
	gobject_class->get_property = gx_radio_button_get_property;
	widget_class->destroy = gx_radio_button_destroy;
	((GtkCheckButtonClass*)klass)->draw_indicator = draw_indicator;
	g_object_class_install_property(
		gobject_class, PROP_BASE_NAME,
		g_param_spec_string("base-name",
		                    P_("Indicator"),
		                    P_("Base name of the indicator image, append \"_on\" and \"_off\" for the stock names"),
		                    "switch",
		                    GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
}

static void gx_radio_button_init(GxRadioButton *radio_button)
{
	radio_button->priv = GX_RADIO_BUTTON_GET_PRIVATE(radio_button);
	radio_button->priv->base_name = g_strdup("switch");
}

static void gx_radio_button_destroy (GtkWidget *obj)
{
	GxRadioButton *radio_button = GX_RADIO_BUTTON(obj);
	g_free(radio_button->priv->base_name);
	radio_button->priv->base_name = 0;
	GTK_WIDGET_CLASS(gx_radio_button_parent_class)->destroy(obj);
}

static void draw_indicator(GtkCheckButton *check_button, cairo_t *cr)
{
	GtkWidget *child;
	gint x, y;
	gint indicator_size;
	gint indicator_spacing;
	GtkWidget *widget = GTK_WIDGET(check_button);
	gboolean interior_focus;
	gint focus_width;
	gint focus_pad;
	gtk_widget_style_get(widget, 
	                     "interior-focus", &interior_focus,
	                     "focus-line-width", &focus_width, 
	                     "focus-padding", &focus_pad,
	                     "indicator-size", &indicator_size,
	                     "indicator-spacing", &indicator_spacing,
	                     NULL);
	GtkAllocation allocation;
	gtk_widget_get_allocation(widget, &allocation);
	x = allocation.x + indicator_spacing + gtk_container_get_border_width(GTK_CONTAINER (widget));
	y = allocation.y + (allocation.height - indicator_size) / 2;
	child = gtk_bin_get_child(GTK_BIN (check_button));
	if (!interior_focus || !(child && gtk_widget_get_visible (child))) {
		x += focus_width + focus_pad;      
	}
	if (gtk_widget_get_direction (widget) == GTK_TEXT_DIR_RTL) {
		x = allocation.x + allocation.width - (indicator_size + x - allocation.x);
	}
	const char *s;
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button))) {
		s = "_on";
	} else {
		s = "_off";
	}
	char *nm = g_strconcat(GX_RADIO_BUTTON(check_button)->priv->base_name, s, NULL);
	GdkPixbuf *pb = gtk_widget_render_icon(widget, nm, GtkIconSize(-1), NULL);
	g_free(nm);
	gdk_cairo_set_source_pixbuf (cr, pb, x, y);
	cairo_paint (cr);
	g_object_unref(pb);
}

static void
gx_radio_button_set_property (GObject *object, guint prop_id, const GValue *value,
                              GParamSpec *pspec)
{
	GxRadioButton *radio_button = GX_RADIO_BUTTON (object);

	switch(prop_id) {
	case PROP_BASE_NAME: {
		const char *str = g_value_get_string(value);
		g_free(radio_button->priv->base_name);
		radio_button->priv->base_name = g_strdup(str ? str : "");
		g_object_notify(object, "base-name");
		break;
	}
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
gx_radio_button_get_property(GObject *object, guint prop_id, GValue *value,
                             GParamSpec *pspec)
{
	GxRadioButton *radio_button = GX_RADIO_BUTTON(object);

	switch(prop_id) {
	case PROP_BASE_NAME:
		g_value_set_string(value, radio_button->priv->base_name);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

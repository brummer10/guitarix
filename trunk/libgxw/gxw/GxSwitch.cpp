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

#include "GxSwitch.h"
#include "GxToggleImage.h"
#include "GxControlParameter.h"
#include <gdk/gdkkeysyms.h>
#include <unistd.h>
#include <string.h>

#define P_(s) (s)   // FIXME -> gettext

struct _GxSwitchPrivate {
	gchar *var_id;
	GtkLabel *label;
};

enum {
	PROP_VAR_ID = 1,
	PROP_LABEL_REF,
	PROP_BASE_NAME,
	PROP_IMAGE,
};

static void gx_control_parameter_interface_init (GxControlParameterIface *iface);

G_DEFINE_TYPE_WITH_CODE(GxSwitch, gx_switch, GTK_TYPE_TOGGLE_BUTTON,
                        G_ADD_PRIVATE(GxSwitch)
                        G_IMPLEMENT_INTERFACE(GX_TYPE_CONTROL_PARAMETER,
                                              gx_control_parameter_interface_init));

#define GX_SWITCH_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), GX_TYPE_SWITCH, GxSwitchPrivate))

static void gx_switch_destroy(GtkWidget *object);
static void gx_switch_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gx_switch_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static gboolean gx_switch_draw(GtkWidget *widget, cairo_t* cr);
static gboolean gx_switch_scroll_event(GtkWidget *widget, GdkEventScroll *event);
static void gx_switch_style_set(GtkWidget *widget, GtkStyle *previous_style);

static void
gx_switch_cp_configure(GxControlParameter *self, gchar* group, gchar *name, gdouble lower, gdouble upper, gdouble step)
{
	GxSwitch *swtch = GX_SWITCH(self);
	if (swtch->priv->label) {
		gtk_label_set_text(swtch->priv->label, name);
	}
}

static gdouble
gx_switch_cp_get_value(GxControlParameter *self)
{
	return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(self));
}

static void
gx_switch_cp_set_value(GxControlParameter *self, gdouble value)
{
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(self), value != 0.0);
}

static void
gx_control_parameter_interface_init(GxControlParameterIface *iface)
{
  iface->cp_configure = gx_switch_cp_configure;
  iface->cp_set_value = gx_switch_cp_set_value;
  iface->cp_get_value = gx_switch_cp_get_value;
}

static void gx_switch_class_init(GxSwitchClass *klass)
{
	GObjectClass   *gobject_class = G_OBJECT_CLASS (klass);
	GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;

	gobject_class->set_property = gx_switch_set_property;
	gobject_class->get_property = gx_switch_get_property;
	widget_class->draw = gx_switch_draw;
	widget_class->scroll_event = gx_switch_scroll_event;
	widget_class->destroy = gx_switch_destroy;
	widget_class->style_set = gx_switch_style_set;

	g_object_class_install_property (
		gobject_class, PROP_VAR_ID, g_param_spec_string(
			"var-id", P_("Variable"),
			P_("The id of the linked variable"),
			NULL, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_LABEL_REF,
		g_param_spec_object("label-ref",
		                    P_("Label ref"),
		                    P_("GtkLabel for caption"),
		                    GTK_TYPE_LABEL,
		                    GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_BASE_NAME,
		g_param_spec_string("base-name",
		                    P_("Image base name"),
		                    P_("Base name of the image, append \"_on\" and \"_off\" for the stock names"),
		                    "",
		                    GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	//g_object_class_override_property(gobject_class, PROP_VAR_ID, "var-id");
	g_object_class_override_property(gobject_class, PROP_IMAGE, "image");
}

/*
** GtkButton always wants to draw a shadow, so some
** of this is a copy of the code of GtkButton/GtkToggleButton with
** the shadow removed and default borders tweaked
*/
static const GtkBorder default_default_border = { 1, 1, 1, 1 };
static const GtkBorder default_default_outside_border = { 0, 0, 0, 0 };
static const GtkBorder default_inner_border = { 0, 0, 0, 0 };

static void
gtk_button_get_props (GtkButton *button,
		      GtkBorder *default_border,
		      GtkBorder *default_outside_border,
                      GtkBorder *inner_border,
		      gboolean  *interior_focus)
{
  GtkWidget *widget =  GTK_WIDGET (button);
  GtkBorder *tmp_border;

  if (default_border)
    {
      gtk_widget_style_get (widget, "default-border", &tmp_border, NULL);

      if (tmp_border)
	{
	  *default_border = *tmp_border;
	  gtk_border_free (tmp_border);
	}
      else
	*default_border = default_default_border;
    }

  if (default_outside_border)
    {
      gtk_widget_style_get (widget, "default-outside-border", &tmp_border, NULL);

      if (tmp_border)
	{
	  *default_outside_border = *tmp_border;
	  gtk_border_free (tmp_border);
	}
      else
	*default_outside_border = default_default_outside_border;
    }

  if (inner_border)
    {
      gtk_widget_style_get (widget, "inner-border", &tmp_border, NULL);

      if (tmp_border)
	{
	  *inner_border = *tmp_border;
	  gtk_border_free (tmp_border);
	}
      else
	*inner_border = default_inner_border;
    }

  if (interior_focus)
    gtk_widget_style_get (widget, "interior-focus", interior_focus, NULL);
}

static void button_paint(
	cairo_t *cr, GtkButton *button, GtkStateFlags state_flags,
	GtkShadowType shadow_type, const gchar *main_detail,
	const gchar *default_detail)
{
	GtkWidget *widget;
	gint width, height;
	gint x, y;
	gint border_width;
	GtkBorder default_border;
	GtkBorder default_outside_border;
	gboolean interior_focus;
	gint focus_width;
	gint focus_pad;

	widget = GTK_WIDGET (button);

	if (gtk_widget_is_drawable (widget)) {
		border_width = gtk_container_get_border_width(GTK_CONTAINER (widget));

		gtk_button_get_props (
			button, &default_border, &default_outside_border,
			NULL, &interior_focus);
		gtk_widget_style_get (
			widget, "focus-line-width", &focus_width,
			"focus-padding", &focus_pad, NULL);

		GtkAllocation allocation;
		gtk_widget_get_allocation(widget, &allocation);
		x = border_width;
		y = border_width;
		width = allocation.width - border_width * 2;
		height = allocation.height - border_width * 2;

		GtkStyleContext* sc = gtk_widget_get_style_context(widget);
		if (gtk_widget_has_default (widget) &&
		    gtk_button_get_relief(GTK_BUTTON (widget)) == GTK_RELIEF_NORMAL) {
			gtk_render_frame(sc, cr, x, y, width, height);
			x += default_border.left;
			y += default_border.top;
			width -= default_border.left + default_border.right;
			height -= default_border.top + default_border.bottom;
		} else if (gtk_widget_get_can_default (widget)) {
			x += default_outside_border.left;
			y += default_outside_border.top;
			width -= default_outside_border.left + default_outside_border.right;
			height -= default_outside_border.top + default_outside_border.bottom;
		}

		if (!interior_focus && gtk_widget_has_focus (widget)) {
			x += focus_width + focus_pad;
			y += focus_width + focus_pad;
			width -= 2 * (focus_width + focus_pad);
			height -= 2 * (focus_width + focus_pad);
		}

		if (gtk_button_get_relief(button) != GTK_RELIEF_NONE) {
			gtk_render_frame(sc, cr, x, y, width, height);
		}
		if (gtk_widget_has_focus (widget)) {
			gint child_displacement_x;
			gint child_displacement_y;
			gboolean displace_focus;
	  
			gtk_widget_style_get (
				widget, "child-displacement-y", &child_displacement_y,
				"child-displacement-x", &child_displacement_x,
				"displace-focus", &displace_focus, NULL);

			if (interior_focus) {
				GtkBorder border;
				gtk_style_context_get_border(sc, state_flags, &border);
				x += border.left + border.right + focus_pad;
				y += border.top + border.bottom + focus_pad;
				width -= 2 * (border.left + border.right + focus_pad);
				height -=  2 * (border.top + border.bottom + focus_pad);
			} else {
				x -= focus_width + focus_pad;
				y -= focus_width + focus_pad;
				width += 2 * (focus_width + focus_pad);
				height += 2 * (focus_width + focus_pad);
			}

			GtkStateFlags state = gtk_widget_get_state_flags(widget);
			if (state == GTK_STATE_FLAG_ACTIVE && displace_focus) {
				x += child_displacement_x;
				y += child_displacement_y;
			}

			gtk_render_focus(sc, cr, x, y, width, height);
		}
	}
}

static gboolean gx_switch_draw(GtkWidget *widget, cairo_t *cr)
{
	if (gtk_widget_is_drawable (widget)) {
		GtkWidget *child = gtk_bin_get_child(GTK_BIN (widget));
		GtkButton *button = GTK_BUTTON (widget);
		GtkStateFlags state_flags;
		GtkShadowType shadow_type;

		state_flags = gtk_widget_get_state_flags(widget);

		if (gtk_toggle_button_get_inconsistent(GTK_TOGGLE_BUTTON (widget))) {
			if (state_flags == GTK_STATE_FLAG_ACTIVE) {
				state_flags = GTK_STATE_FLAG_NORMAL;
			}
			shadow_type = GTK_SHADOW_ETCHED_IN;
		} else {
			shadow_type = state_flags == GTK_STATE_FLAG_ACTIVE ? GTK_SHADOW_IN : GTK_SHADOW_OUT;
		}
		button_paint(cr, button, state_flags, shadow_type,
		             "togglebutton", "togglebuttondefault");

		if (child) {
			gtk_container_propagate_draw(GTK_CONTAINER(widget), child, cr);
		}
	}

	return FALSE;
}

/****************************************************************
 ** init the Switch type/size
 */

static void gx_switch_init(GxSwitch *swtch)
{
	swtch->priv = GX_SWITCH_GET_PRIVATE(swtch);
	swtch->priv->var_id = NULL;
	swtch->priv->label = NULL;
	//GTK_BUTTON(swtch)->relief = GTK_RELIEF_NONE;
}

/****************************************************************
 */
static void gx_switch_destroy(GtkWidget *object)
{
	GxSwitch *swtch = GX_SWITCH(object);
	if (swtch->priv->label) {
		g_object_unref(swtch->priv->label);
		swtch->priv->label = 0;
	}
	g_free(swtch->priv->var_id);
	swtch->priv->var_id = 0;
	GTK_WIDGET_CLASS(gx_switch_parent_class)->destroy (object);
}

/****************************************************************
 */
static void gx_switch_style_set(GtkWidget *widget, GtkStyle *previous_style) {
    GTK_WIDGET_CLASS(gx_switch_parent_class)->style_set(widget, previous_style);
    gtk_widget_queue_resize(widget); // glade-gtk2 bug?
}

/****************************************************************
 */
gboolean gx_switch_scroll_event(GtkWidget *widget, GdkEventScroll *event)
{
	gtk_toggle_button_set_active(
		GTK_TOGGLE_BUTTON(widget),
		event->direction == GDK_SCROLL_UP || event->direction == GDK_SCROLL_RIGHT);
	return TRUE;
}

/****************************************************************
 ** Properties
 */

void gx_switch_set_label_ref(GxSwitch *swtch, GtkLabel *label)
{
	g_return_if_fail(GX_IS_SWITCH(swtch));
	if (swtch->priv->label) {
		g_object_unref(swtch->priv->label);
		swtch->priv->label = 0;
	}
	if (label) {
		g_return_if_fail(GTK_IS_LABEL(label));
		swtch->priv->label = label;
		g_object_ref(label);
	}
	g_object_notify(G_OBJECT(swtch), "label-ref");
}

GtkLabel *gx_switch_get_label_ref(GxSwitch *swtch)
{
	g_return_val_if_fail(GX_IS_SWITCH(swtch), 0);
	return swtch->priv->label;
}

void gx_switch_set_base_name(GxSwitch *swtch, const char *base_name)
{
	g_return_if_fail(GX_IS_SWITCH(swtch));
	GtkWidget *img = gtk_button_get_image(GTK_BUTTON(swtch));
	if (img && GX_IS_TOGGLE_IMAGE(img)) {
		const gchar *old = gx_toggle_image_get_base_name(GX_TOGGLE_IMAGE(img));
		if (!base_name || !*base_name) {
			gtk_button_set_image(GTK_BUTTON(swtch), NULL);
		} else if (old && strcmp(old, base_name) == 0) {
			return;
		}
		gx_toggle_image_set_base_name(GX_TOGGLE_IMAGE(img), base_name);
	} else {
		if (!base_name || !*base_name) {
			return;
		}
		gtk_button_set_image(GTK_BUTTON(swtch),
		                     GTK_WIDGET(g_object_new(GX_TYPE_TOGGLE_IMAGE, "base-name",
		                                             base_name, NULL)));
	}
	gtk_widget_queue_resize(GTK_WIDGET(swtch));
	g_object_notify(G_OBJECT(swtch), "base-name");
}

const char *gx_switch_get_base_name(GxSwitch *swtch)
{
	GtkWidget *img = gtk_button_get_image(GTK_BUTTON(swtch));
	if (img && GX_IS_TOGGLE_IMAGE(img)) {
		return gx_toggle_image_get_base_name(GX_TOGGLE_IMAGE(img));
	} else {
		return g_strdup("");
	}
}

static void
gx_switch_set_property (GObject *object, guint prop_id, const GValue *value,
                        GParamSpec *pspec)
{
	GxSwitch *swtch = GX_SWITCH (object);

	switch(prop_id) {
	case PROP_VAR_ID: {
		const char *str = g_value_get_string(value);
		g_free(swtch->priv->var_id);
		swtch->priv->var_id = g_strdup(str ? str : "");
		g_object_notify(object, "var-id");
		break;
	}
	case PROP_LABEL_REF:
		gx_switch_set_label_ref(swtch, GTK_LABEL(g_value_get_object(value)));
		break;
	case PROP_BASE_NAME:
		gx_switch_set_base_name(swtch, g_value_get_string(value));
		break;
	case PROP_IMAGE:
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
gx_switch_get_property(GObject *object, guint prop_id, GValue *value,
                       GParamSpec *pspec)
{
	GxSwitch *swtch = GX_SWITCH(object);

	switch(prop_id) {
	case PROP_VAR_ID:
		g_value_set_string(value, swtch->priv->var_id);
		break;
	case PROP_LABEL_REF:
		g_value_set_object(value, swtch->priv->label);
		break;
	case PROP_BASE_NAME: {
		GtkWidget *img = gtk_button_get_image(GTK_BUTTON(object));
		if (img && GX_IS_TOGGLE_IMAGE(img)) {
			g_object_get_property(G_OBJECT(img), pspec->name, value);
		} else {
			g_value_set_string(value, "");
		}
		break;
	}
	case PROP_IMAGE:
		g_value_set_object(value, 0);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

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
	gchar *base_name;
	GtkLabel *label;
};

enum {
	PROP_VAR_ID = 1,
	PROP_BASE_NAME,
	PROP_LABEL_REF,
};

static void gx_control_parameter_interface_init (GxControlParameterIface *iface);

G_DEFINE_TYPE_WITH_CODE(GxSwitch, gx_switch, GTK_TYPE_CHECK_BUTTON,
                        G_ADD_PRIVATE(GxSwitch)
                        G_IMPLEMENT_INTERFACE(GX_TYPE_CONTROL_PARAMETER,
                                              gx_control_parameter_interface_init));

static void gx_switch_destroy(GtkWidget *object);
static void gx_switch_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gx_switch_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static gboolean gx_switch_scroll_event(GtkWidget *widget, GdkEventScroll *event);
static void gx_switch_style_set(GtkWidget *widget, GtkStyle *previous_style);

static void
gx_switch_cp_configure(GxControlParameter *self, const gchar* group, const gchar *name, gdouble lower, gdouble upper, gdouble step)
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
	widget_class->scroll_event = gx_switch_scroll_event;
	widget_class->destroy = gx_switch_destroy;
	widget_class->style_set = gx_switch_style_set;

	g_object_class_install_property (
		gobject_class, PROP_VAR_ID, g_param_spec_string(
			"var-id", P_("Variable"),
			P_("The id of the linked variable"),
			NULL, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property (
		gobject_class, PROP_BASE_NAME,
		g_param_spec_string("base-name",
							P_("css class name"),
							P_("button image should be set in css"),
							NULL,
							GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_LABEL_REF,
		g_param_spec_object("label-ref",
		                    P_("Label ref"),
		                    P_("GtkLabel for caption"),
		                    GTK_TYPE_LABEL,
		                    GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
}

/****************************************************************
 ** init the Switch type/size
 */

static void gx_switch_init(GxSwitch *swtch)
{
	swtch->priv = (GxSwitchPrivate*)gx_switch_get_instance_private(swtch);
	swtch->priv->var_id = NULL;
	swtch->priv->base_name = 0;
	swtch->priv->label = NULL;
	gx_switch_set_base_name(swtch, "switch");
	//GTK_BUTTON(swtch)->relief = GTK_RELIEF_NONE;
	gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(swtch)), "gx_switch");
	gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(swtch), TRUE);
}

/****************************************************************
 */
static void gx_switch_destroy(GtkWidget *object)
{
	GxSwitch *swtch = GX_SWITCH(object);
	if (swtch->priv->label) {
		g_clear_object(&swtch->priv->label);
	}
	g_free(swtch->priv->base_name);
	swtch->priv->base_name = 0;
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
		g_clear_object(&swtch->priv->label);
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
	if (!base_name) {
		base_name = "";
	}
	if (swtch->priv->base_name && strcmp(swtch->priv->base_name, base_name) == 0) {
		return;
	}
	char *old = swtch->priv->base_name;
	GtkStyleContext *context = gtk_widget_get_style_context(GTK_WIDGET(swtch));
	swtch->priv->base_name = g_strdup(base_name);
	if (*base_name) {
		char buffer[100] = "gx_sw_";
		strncat(buffer, base_name, sizeof buffer - 1);
		gtk_style_context_add_class(context, buffer);
	}
	if (!old) {
		return;
	}
	if (*old) {
		char buffer[100] = "gx_sw_";
		strncat(buffer, old, sizeof buffer - 1);
		gtk_style_context_remove_class(context, buffer);
	}
	g_free(old);
	gtk_widget_queue_resize(GTK_WIDGET(swtch));
	g_object_notify(G_OBJECT(swtch), "base-name");
}

const char *gx_switch_get_base_name(GxSwitch *swtch)
{
	g_return_val_if_fail(GX_IS_SWITCH(swtch), "");
	return swtch->priv->base_name;
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
	case PROP_BASE_NAME:
		gx_switch_set_base_name(swtch, g_value_get_string(value));
		break;
	case PROP_LABEL_REF:
		gx_switch_set_label_ref(swtch, GTK_LABEL(g_value_get_object(value)));
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
	case PROP_BASE_NAME:
		g_value_set_string(value, swtch->priv->base_name);
		break;
	case PROP_LABEL_REF:
		g_value_set_object(value, swtch->priv->label);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

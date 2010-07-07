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

#include "GxSwitch.h"
#include "GxToggleImage.h"
#include "GxControlParameter.h"
#include <gtk/gtk.h>
#include <gtk/gtkprivate.h>
#include <gdk/gdkkeysyms.h>
#include <unistd.h>

#define P_(s) (s)   // FIXME -> gettext

enum {
	PROP_VAR_ID = 1,
	PROP_LABEL,
	PROP_BASE_NAME,
};

static void gx_control_parameter_interface_init (GxControlParameterIface *iface);

G_DEFINE_TYPE_WITH_CODE(GxSwitch, gx_switch, GTK_TYPE_TOGGLE_BUTTON,
                        G_IMPLEMENT_INTERFACE(GX_TYPE_CONTROL_PARAMETER,
                                              gx_control_parameter_interface_init));

static void gx_switch_destroy(GtkObject *object);
static void gx_switch_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gx_switch_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);

static void
gx_switch_cp_configure(GxControlParameter *self, gchar* group, gchar *name, gdouble lower, gdouble upper, gdouble step)
{
	GxSwitch *swtch = GX_SWITCH(self);
	if (swtch->label) {
		gtk_label_set_text(swtch->label, name);
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
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(self), value == 0.0);
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
	GtkObjectClass *object_class = (GtkObjectClass*) klass;

	gobject_class->set_property = gx_switch_set_property;
	gobject_class->get_property = gx_switch_get_property;
	object_class->destroy = gx_switch_destroy;

	g_object_class_install_property(
		gobject_class, PROP_LABEL,
		g_param_spec_object("label",
		                    P_("Label ref"),
		                    P_("GtkLabel for caption"),
		                    GTK_TYPE_LABEL,
		                    GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property(
		gobject_class,
		PROP_BASE_NAME,
		g_param_spec_string("base-name",
		                    P_("Image base name"),
		                    P_("Base name of the image, append \"_on\" and \"_off\" for the stock names"),
		                    "",
		                    GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_override_property(gobject_class, PROP_VAR_ID, "var-id");
}

/****************************************************************
 ** init the Switch type/size
 */

static void gx_switch_init(GxSwitch *swtch)
{
}

/****************************************************************
 */
static void gx_switch_destroy(GtkObject *object)
{
	GxSwitch *swtch = GX_SWITCH(object);
	if (swtch->label) {
		g_object_unref(swtch->label);
		swtch->label = 0;
	}
	g_free(swtch->var_id);
	swtch->var_id = 0;
	GTK_OBJECT_CLASS(gx_switch_parent_class)->destroy (object);
}


/****************************************************************
 ** Properties
 */

static void gx_switch_set_label(GxSwitch *swtch, GObject *object)
{
	if (swtch->label) {
		g_object_unref(swtch->label);
		swtch->label = 0;
	}
	if (object) {
		swtch->label = GTK_LABEL(object);
		g_object_ref(object);
	}
	g_object_notify(G_OBJECT(swtch), "label");
}

static void
gx_switch_set_property (GObject *object, guint prop_id, const GValue *value,
                        GParamSpec *pspec)
{
	GxSwitch *swtch = GX_SWITCH (object);

	switch(prop_id) {
	case PROP_VAR_ID: {
		const char *str = g_value_get_string(value);
		g_free(swtch->var_id);
		swtch->var_id = g_strdup(str ? str : "");
		g_object_notify(object, "var-id");
		break;
	}
	case PROP_LABEL:
		gx_switch_set_label(swtch, G_OBJECT(g_value_get_object(value)));
		break;
	case PROP_BASE_NAME:
		gtk_button_set_image(GTK_BUTTON(object),
		                     GTK_WIDGET(g_object_new(GX_TYPE_TOGGLE_IMAGE, "base-name",
		                                             g_value_get_string(value), NULL)));
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
		g_value_set_string(value, swtch->var_id);
		break;
	case PROP_LABEL:
		g_value_set_object(value, swtch->label);
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
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

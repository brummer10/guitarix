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
static gboolean gx_switch_expose(GtkWidget *widget, GdkEventExpose *event);

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
	GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;

	gobject_class->set_property = gx_switch_set_property;
	gobject_class->get_property = gx_switch_get_property;
	widget_class->expose_event = gx_switch_expose;
	object_class->destroy = gx_switch_destroy;

	g_object_class_install_property(
		gobject_class, PROP_LABEL,
		g_param_spec_object("label",
		                    P_("Label ref"),
		                    P_("GtkLabel for caption"),
		                    GTK_TYPE_LABEL,
		                    GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property(
		gobject_class, PROP_BASE_NAME,
		g_param_spec_string("base-name",
		                    P_("Image base name"),
		                    P_("Base name of the image, append \"_on\" and \"_off\" for the stock names"),
		                    "",
		                    GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_override_property(gobject_class, PROP_VAR_ID, "var-id");
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

void
_gtk_button_paint (GtkButton          *button,
		   const GdkRectangle *area,
		   GtkStateType        state_type,
		   GtkShadowType       shadow_type,
		   const gchar        *main_detail,
		   const gchar        *default_detail)
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

  if (gtk_widget_is_drawable (widget))
    {
      border_width = GTK_CONTAINER (widget)->border_width;

      gtk_button_get_props (button, &default_border, &default_outside_border, NULL, &interior_focus);
      gtk_widget_style_get (widget,
			    "focus-line-width", &focus_width,
			    "focus-padding", &focus_pad,
			    NULL); 
	
      x = widget->allocation.x + border_width;
      y = widget->allocation.y + border_width;
      width = widget->allocation.width - border_width * 2;
      height = widget->allocation.height - border_width * 2;

      if (gtk_widget_has_default (widget) &&
	  GTK_BUTTON (widget)->relief == GTK_RELIEF_NORMAL)
	{
	  gtk_paint_box (widget->style, widget->window,
			 GTK_STATE_NORMAL, GTK_SHADOW_IN,
			 area, widget, "buttondefault",
			 x, y, width, height);

	  x += default_border.left;
	  y += default_border.top;
	  width -= default_border.left + default_border.right;
	  height -= default_border.top + default_border.bottom;
	}
      else if (gtk_widget_get_can_default (widget))
	{
	  x += default_outside_border.left;
	  y += default_outside_border.top;
	  width -= default_outside_border.left + default_outside_border.right;
	  height -= default_outside_border.top + default_outside_border.bottom;
	}
       
      if (!interior_focus && gtk_widget_has_focus (widget))
	{
	  x += focus_width + focus_pad;
	  y += focus_width + focus_pad;
	  width -= 2 * (focus_width + focus_pad);
	  height -= 2 * (focus_width + focus_pad);
	}

      if (button->relief != GTK_RELIEF_NONE)
	gtk_paint_box (widget->style, widget->window,
		       state_type,
		       shadow_type, area, widget, "button",
		       x, y, width, height);
       
      if (gtk_widget_has_focus (widget))
	{
	  gint child_displacement_x;
	  gint child_displacement_y;
	  gboolean displace_focus;
	  
	  gtk_widget_style_get (widget,
				"child-displacement-y", &child_displacement_y,
				"child-displacement-x", &child_displacement_x,
				"displace-focus", &displace_focus,
				NULL);

	  if (interior_focus)
	    {
	      x += widget->style->xthickness + focus_pad;
	      y += widget->style->ythickness + focus_pad;
	      width -= 2 * (widget->style->xthickness + focus_pad);
	      height -=  2 * (widget->style->ythickness + focus_pad);
	    }
	  else
	    {
	      x -= focus_width + focus_pad;
	      y -= focus_width + focus_pad;
	      width += 2 * (focus_width + focus_pad);
	      height += 2 * (focus_width + focus_pad);
	    }

	  if (button->depressed && displace_focus)
	    {
	      x += child_displacement_x;
	      y += child_displacement_y;
	    }

	  gtk_paint_focus (widget->style, widget->window, gtk_widget_get_state (widget),
			   area, widget, "button",
			   x, y, width, height);
	}
    }
}

static gboolean gx_switch_expose(GtkWidget *widget, GdkEventExpose *event)
{
  if (gtk_widget_is_drawable (widget))
    {
      GtkWidget *child = GTK_BIN (widget)->child;
      GtkButton *button = GTK_BUTTON (widget);
      GtkStateType state_type;
      GtkShadowType shadow_type;

      state_type = gtk_widget_get_state (widget);
      
      if (GTK_TOGGLE_BUTTON (widget)->inconsistent)
        {
          if (state_type == GTK_STATE_ACTIVE)
            state_type = GTK_STATE_NORMAL;
          shadow_type = GTK_SHADOW_ETCHED_IN;
        }
      else
	shadow_type = button->depressed ? GTK_SHADOW_IN : GTK_SHADOW_OUT;

      _gtk_button_paint (button, &event->area, state_type, shadow_type,
			 "togglebutton", "togglebuttondefault");

      if (child)
	gtk_container_propagate_expose (GTK_CONTAINER (widget), child, event);
    }
  
  return FALSE;
}

/****************************************************************
 ** init the Switch type/size
 */

static void gx_switch_init(GxSwitch *swtch)
{
	GTK_BUTTON(swtch)->relief = GTK_RELIEF_NONE;
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

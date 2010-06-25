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
#include "GxControlParameter.h"
#include <gtk/gtk.h>
#include <gtk/gtkprivate.h>
#include <gdk/gdkkeysyms.h>
#include <unistd.h>

#include "GxSwitchPix.cpp"

#define P_(s) (s)   // FIXME -> gettext

enum {
	PROP_TYPE = 1,
	PROP_VAR_ID,
	PROP_SHOW_LABEL,
	PROP_LABEL_FROM_VAR,
	PROP_LABEL_TEXT,
	PROP_LABEL_POSITION,
};

static void gx_switch_class_init(GxSwitchClass *klass);
static void gx_switch_init(GxSwitch *swtch);
static void gx_switch_base_class_finalize(GxSwitchClass *klass);
static void gx_switch_finalize(GObject*);
static void gx_switch_init_pixmaps(GxSwitchClass *klass);
static void gx_switch_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gx_switch_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static gboolean gx_switch_enter_in (GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_switch_leave_out (GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_switch_expose (GtkWidget *widget, GdkEventExpose *event);
static void gx_switch_size_request (GtkWidget *widget, GtkRequisition *requisition);
static gboolean gx_switch_button_press (GtkWidget *widget, GdkEventButton *event);
static gboolean gx_switch_button_release (GtkWidget *widget, GdkEventButton *event);
static gboolean gx_switch_key_press (GtkWidget *widget, GdkEventKey *event);
static gboolean gx_switch_scroll (GtkWidget *widget, GdkEventScroll *event);
static void gx_control_parameter_interface_init (GxControlParameterIface *iface);

static gpointer gx_switch_parent_class = NULL;

GType gx_switch_get_type(void)
{
	static GType switch_type = 0;

	if (!switch_type) {
		const GTypeInfo switch_info = {
			sizeof (GxSwitchClass),
			NULL,				/* base_class_init */
			(GBaseFinalizeFunc) gx_switch_base_class_finalize,
			(GClassInitFunc) gx_switch_class_init,
			NULL,				/* class_finalize */
			NULL,				/* class_data */
			sizeof (GxSwitch),
			0,					/* n_preallocs */
			(GInstanceInitFunc) gx_switch_init,
			NULL,				/* value_table */
		};
		switch_type = g_type_register_static(
			GTK_TYPE_TOGGLE_BUTTON, "GxSwitch", &switch_info, (GTypeFlags)0);
		static const GInterfaceInfo g_implement_interface_info = {
			(GInterfaceInitFunc)gx_control_parameter_interface_init
		};
        g_type_add_interface_static (switch_type, GX_TYPE_CONTROL_PARAMETER, &g_implement_interface_info);
	}
	return switch_type;
}

GType switch_type_get_type(void)
{
	static GType etype = 0;
	if (G_UNLIKELY(etype == 0)) {
		static const GEnumValue values[] = {
			{ GX_SWITCH_TYPE_SWITCH, "SWITCH_TYPE_SWITCH", "switch" },
			{ GX_SWITCH_TYPE_SWITCH_II, "SWITCH_TYPE_SWITCH_II", "switch II" },
			{ GX_SWITCH_TYPE_MINI_TOGGLE, "SWITCH_TYPE_MINI_TOGGLE", "mini toggle" },
			{ GX_SWITCH_TYPE_TOGGLE_BUTTON, "SWITCH_TYPE_TOGGLE_BUTTON", "toggle button" },
			{ GX_SWITCH_TYPE_LED, "SWITCH_TYPE_LED", "led" },
			//{ GX_SWITCH_TYPE_VALUE_DISPLAY, "GX_SWITCH_TYPE_VALUE_DISPLAY", "value display" }, //FIXME
			{ 0, NULL, NULL }
		};
		etype = g_enum_register_static (g_intern_static_string ("GxSwitchType"), values);
	}
	return etype;
}


static void gx_switch_set_label(GxSwitch *self, const gchar *text)
{
	g_free(self->label);
	self->label = g_strdup(text);
	if (self->layout) {
		pango_layout_set_text(self->layout, self->label, -1);
	}
	gtk_widget_queue_resize(GTK_WIDGET(self));
	g_object_notify(G_OBJECT(self), "label-text");
}

static void
gx_switch_cp_configure(GxControlParameter *self, gchar* group, gchar *name, gdouble lower, gdouble upper, gdouble step)
{
	gx_switch_set_label(GX_SWITCH(self), name);
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
	GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;
	gx_switch_parent_class = g_type_class_peek_parent(klass);
	gobject_class->finalize = gx_switch_finalize;
	gobject_class->set_property = gx_switch_set_property;
	gobject_class->get_property = gx_switch_get_property;

	widget_class->enter_notify_event = gx_switch_enter_in;
	widget_class->leave_notify_event = gx_switch_leave_out;
	widget_class->expose_event = gx_switch_expose;
	widget_class->size_request = gx_switch_size_request;
	widget_class->button_press_event = gx_switch_button_press;
	widget_class->button_release_event = gx_switch_button_release;
	widget_class->key_press_event = gx_switch_key_press;
	widget_class->scroll_event = gx_switch_scroll;

	g_object_class_install_property(
		gobject_class, PROP_TYPE,
		g_param_spec_enum("switch-type",
		                  P_("Type"),
		                  P_("The type of the control"),
		                  switch_type_get_type(),
		                  GX_SWITCH_TYPE_SWITCH,
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

	gx_switch_init_pixmaps(klass);
}

static const GtkRequisition base_size[GX_SWITCH_TYPE_COUNT] = {
		{ 37, 28 }, // GX_SWITCH_TYPE_SWITCH
		{ 20, 10 }, // GX_SWITCH_TYPE_SWITCH_II
		{ 10, 10 }, // GX_SWITCH_TYPE_MINI_TOGGLE
		{ 25, 15 }, // GX_SWITCH_TYPE_TOGGLE_BUTTON
		{ 20, 20 }, // GX_SWITCH_TYPE_LED
		//{ -1, 25 }, //class_vd_y         GX_SWITCH_TYPE_VALUE_DISPLAY //FIXME
};


static void gx_switch_ensure_layout(GxSwitch *swtch)
{
	if (swtch->layout) {
		return;
	}
	swtch->layout = gtk_widget_create_pango_layout(GTK_WIDGET(swtch), swtch->label);
}

static void get_positions(GtkWidget *widget, gint *text_x, gint *text_y, gint *image_x, gint *image_y)
{
	GxSwitch *swtch = GX_SWITCH(widget);
	gint x = widget->allocation.x, y = widget->allocation.y;
	gint text_width = 0, text_height = 0;
	if (swtch->show_label) {
		PangoRectangle logical_rect;
		gx_switch_ensure_layout(swtch);
		pango_layout_get_pixel_extents(swtch->layout, NULL, &logical_rect);
		text_width = logical_rect.width;
		text_height = logical_rect.height;
	}
	gint width = base_size[swtch->switch_type].width;
	gint height = base_size[swtch->switch_type].height;
	switch (swtch->label_position) {
	case GTK_POS_LEFT:
		*text_x = x + (widget->allocation.width - width - text_width) / 2;
		*text_y = y + (widget->allocation.height - text_height) / 2;
		*image_x = x + (widget->allocation.width - width + text_width) / 2;
		*image_y = y + (widget->allocation.height - height) / 2;
		break;
	case GTK_POS_RIGHT:
		*text_x = x + (widget->allocation.width + width - text_width) / 2;
		*text_y = y + (widget->allocation.height - text_height) / 2;
		*image_x = x + (widget->allocation.width - width - text_width) / 2;
		*image_y = y + (widget->allocation.height - height) / 2;
		break;
	case GTK_POS_TOP:
		*text_x = x + (widget->allocation.width - text_width) / 2;
		*text_y = y + (widget->allocation.height - height - text_height) / 2;
		*image_x = x + (widget->allocation.width - width) / 2;
		*image_y = y + (widget->allocation.height - height + text_height) / 2;
		break;
	case GTK_POS_BOTTOM:
		*text_x = x + (widget->allocation.width - text_width) / 2;
		*text_y = y + (widget->allocation.height + height - text_height) / 2;
		*image_x = x + (widget->allocation.width - width) / 2;
		*image_y = y + (widget->allocation.height - height - text_height) / 2;
		break;
	}
}

static void draw_image(GtkWidget *widget, gint image_x, gint image_y, gboolean highlight)
{
	GxSwitch *swtch = GX_SWITCH(widget);
	GxSwitchClass *klass =  GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget));
	gint width = base_size[swtch->switch_type].width;
	gint height = base_size[swtch->switch_type].height;
	gboolean switchstate = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	gint xoff = 0, yoff = 0;
	GdkPixbuf *image = NULL;
	switch (swtch->switch_type) {
	case GX_SWITCH_TYPE_SWITCH:
		image = (highlight ? klass->toggle_image1 : klass->toggle_image);
		if (switchstate) {
			xoff = width;
		}
		break;
	case GX_SWITCH_TYPE_MINI_TOGGLE:
		image = (highlight ? klass->switch_image1 : klass->switch_image);
		if (switchstate) {
			xoff = 2*width;
		}
		break;
	case GX_SWITCH_TYPE_SWITCH_II:
		image = (highlight ? klass->switch_image1 : klass->switch_image);
		if (switchstate) {
			xoff = width;
		}
		break;
	case GX_SWITCH_TYPE_TOGGLE_BUTTON:
		image = (highlight ? klass->b_toggle_image1 : klass->b_toggle_image);
		if (switchstate) {
			yoff = height;
		}
		break;
	case GX_SWITCH_TYPE_LED:
		image = klass->led_image;
		if (switchstate) {
			yoff = height;
		}
		break;
	}
	gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
	                image, xoff, yoff, image_x, image_y, width, height,
	                GDK_RGB_DITHER_NORMAL, 0, 0);
}

static gboolean gx_switch_expose (GtkWidget *widget, GdkEventExpose *event)
{
	g_assert(GX_IS_SWITCH(widget));
	GxSwitch *swtch = GX_SWITCH(widget);
	gint text_x, text_y, image_x, image_y;
	get_positions(widget, &text_x, &text_y, &image_x, &image_y);
	if (swtch->show_label) {
		gtk_paint_layout(widget->style,
		                 widget->window,
		                 gtk_widget_get_state (widget),
		                 FALSE,
		                 &event->area,
		                 widget,
		                 "label",
		                 text_x, text_y,
		                 swtch->layout);
	}
	draw_image(widget, image_x, image_y, GTK_WIDGET_HAS_FOCUS(widget));
	return TRUE;
}

/****************************************************************
 ** redraw when leave
 */

static gboolean gx_switch_leave_out (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_SWITCH(widget));
	if (GX_SWITCH(widget)->switch_type != GX_SWITCH_TYPE_LED) {
		gint text_x, text_y, image_x, image_y;
		get_positions(widget, &text_x, &text_y, &image_x, &image_y);
		draw_image(widget, image_x, image_y, FALSE);
	}
	return TRUE;
}

/****************************************************************
 ** redraw when enter
 */

static gboolean gx_switch_enter_in (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_SWITCH(widget));
	if (GX_SWITCH(widget)->switch_type != GX_SWITCH_TYPE_LED) {
		gint text_x, text_y, image_x, image_y;
		get_positions(widget, &text_x, &text_y, &image_x, &image_y);
		draw_image(widget, image_x, image_y, TRUE);
	}
	return TRUE;
}

/****************************************************************
 ** set size for GdkDrawable per type
 */

static void gx_switch_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
	g_assert(GX_IS_SWITCH(widget));
	GxSwitch *swtch = GX_SWITCH(widget);
	//GxSwitchClass *klass =  GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget));

	*requisition = base_size[swtch->switch_type];
	if (swtch->show_label) {
		PangoRectangle logical_rect;
		gx_switch_ensure_layout(swtch);
		pango_layout_get_pixel_extents(swtch->layout, NULL, &logical_rect);
		switch (swtch->label_position) {
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
 ** keyboard bindings
 */

static gboolean gx_switch_key_press (GtkWidget *widget, GdkEventKey *event)
{
	g_assert(GX_IS_SWITCH(widget));

	switch (event->keyval) {
	case GDK_End:
	case GDK_Up:
	case GDK_Right:
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), TRUE);
		return TRUE;
	case GDK_Home:
	case GDK_Down:
	case GDK_Left:
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), FALSE);
		return TRUE;
	}

	return FALSE;
}


/****************************************************************
 ** mouse button pressed set value
 */

static gboolean gx_switch_button_press (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_SWITCH(widget));
	if (event->button == 1) {
		gtk_widget_grab_focus(widget);
		gtk_widget_grab_default (widget);
		gtk_grab_add(widget);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), !gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)));
	}
	return TRUE;
}

/****************************************************************
 ** mouse button release
 */

static gboolean gx_switch_button_release (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_SWITCH(widget));
	if (GTK_WIDGET_HAS_GRAB(widget))
		gtk_grab_remove(widget);
	return FALSE;
}

/****************************************************************
 ** set value from mouseweel
 */

static gboolean gx_switch_scroll (GtkWidget *widget, GdkEventScroll *event)
{
	usleep(5000);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), event->direction);
	return FALSE;
}

/****************************************************************
 ** init the used background images to the used skins
 */

void gx_switch_init_pixmaps(GxSwitchClass *klass)
{
//----------- switch
	klass->toggle_image = gdk_pixbuf_new_from_xpm_data (switchit_xpm);
	g_assert(klass->toggle_image != NULL);
	klass->toggle_image1 = gdk_pixbuf_copy( klass->toggle_image );
	g_assert(klass->toggle_image1 != NULL);
	gdk_pixbuf_saturate_and_pixelate(klass->toggle_image1,klass->toggle_image1,10.0,FALSE);
//----------- switchII
	klass->switch_image = gdk_pixbuf_new_from_xpm_data (switch_xpm);
	g_assert(klass->switch_image != NULL);
	klass->switch_image1 = gdk_pixbuf_copy( klass->switch_image );
	g_assert(klass->switch_image1 != NULL);
	gdk_pixbuf_saturate_and_pixelate(klass->switch_image1,klass->switch_image1,10.0,FALSE);
//----------- led
	klass->led_image = gdk_pixbuf_new_from_xpm_data (led_xpm);
	g_assert(klass->led_image != NULL);
//----------- toggle_button
	klass->b_toggle_image = gdk_pixbuf_new_from_xpm_data (button_xpm);
	g_assert(klass->b_toggle_image != NULL);
	klass->b_toggle_image1 = gdk_pixbuf_new_from_xpm_data (button1_xpm);
	g_assert(klass->b_toggle_image1 != NULL);
}

/****************************************************************
 ** init the Switch type/size
 */

static void gx_switch_init(GxSwitch *swtch)
{
	GtkWidget *widget = GTK_WIDGET(swtch);

	gtk_widget_set_has_window (GTK_WIDGET (swtch), FALSE);
	GTK_WIDGET_SET_FLAGS (GTK_WIDGET(swtch), GTK_CAN_FOCUS);
	GTK_WIDGET_SET_FLAGS (GTK_WIDGET(swtch), GTK_CAN_DEFAULT);
	widget->requisition = base_size[swtch->switch_type];
}

/****************************************************************
 */
static void gx_switch_base_class_finalize(GxSwitchClass *klass)
{
	if (G_IS_OBJECT(klass-> toggle_image))
		g_object_unref(klass->toggle_image);
	if (G_IS_OBJECT(klass-> toggle_image1))
		g_object_unref(klass->toggle_image1);

	if (G_IS_OBJECT(klass-> switch_image))
		g_object_unref(klass->switch_image);
	if (G_IS_OBJECT(klass-> switch_image1))
		g_object_unref(klass->switch_image1);

	if (G_IS_OBJECT(klass-> led_image))
		g_object_unref(klass->led_image);

	if (G_IS_OBJECT(klass-> b_toggle_image))
		g_object_unref(klass->b_toggle_image);
	if (G_IS_OBJECT(klass-> b_toggle_image1))
		g_object_unref(klass->b_toggle_image1);
}

static void gx_switch_finalize(GObject *object)
{
	GxSwitch *swtch = GX_SWITCH(object);
	g_free(swtch->label);
	g_free(swtch->var_id);
	if (swtch->layout) {
		g_object_unref(swtch->layout);
	}
	G_OBJECT_CLASS(gx_switch_parent_class)->finalize(object);
}


/****************************************************************
 ** Properties
 */

static switch_connect_func *p_switch_connect_func;

void set_switch_connect_func(switch_connect_func f)
{
	p_switch_connect_func = f;
}

static gboolean gx_switch_connect_var(GxSwitch *swtch, const gchar *var)
{
	if (p_switch_connect_func) {
		return p_switch_connect_func(swtch, var);
	}
	return TRUE;
}

static void gx_switch_set_var_id (GxSwitch *swtch, const gchar *str)
{
	g_free(swtch->var_id);
	swtch->var_id = g_strdup (str ? str : "");
	gx_switch_connect_var(swtch, swtch->var_id);
}

gchar *gx_switch_get_var(GxSwitch *swtch)
{
	return swtch->var_id;
}

static void
gx_switch_set_property (GObject *object, guint prop_id, const GValue *value,
                        GParamSpec *pspec)
{
	GxSwitch *swtch = GX_SWITCH (object);

	switch(prop_id) {
	case PROP_TYPE:
		swtch->switch_type = g_value_get_enum(value);
		break;
	case PROP_VAR_ID:
		gx_switch_set_var_id (swtch, g_value_get_string (value));
		break;
	case PROP_SHOW_LABEL:
		swtch->show_label = g_value_get_boolean(value);
		gtk_widget_queue_resize(GTK_WIDGET(object));
		g_object_notify(object, "show-label");
		break;
	case PROP_LABEL_FROM_VAR:
		swtch->label_from_var = g_value_get_boolean(value);
		g_object_notify(object, "label-from-var");
		break;
	case PROP_LABEL_TEXT:
		gx_switch_set_label(swtch, g_value_get_string(value));
		break;
	case PROP_LABEL_POSITION:
		swtch->label_position = GtkPositionType(g_value_get_enum(value));
		gtk_widget_queue_resize(GTK_WIDGET(object));
		g_object_notify(object, "label-position");
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
	case PROP_TYPE:
		g_value_set_enum(value, swtch->switch_type);
		break;
	case PROP_VAR_ID:
		g_value_set_string(value, swtch->var_id);
		break;
	case PROP_SHOW_LABEL:
		g_value_set_boolean(value, swtch->show_label);
		break;
	case PROP_LABEL_FROM_VAR:
		g_value_set_boolean(value, swtch->label_from_var);
		break;
	case PROP_LABEL_TEXT:
		g_value_set_string(value, swtch->label);
		break;
	case PROP_LABEL_POSITION:
		g_value_set_enum(value, swtch->label_position);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

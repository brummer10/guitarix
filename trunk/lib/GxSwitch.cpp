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
};

static void gx_switch_buildable_interface_init(GtkBuildableIface *iface);
static void gx_switch_parser_finished(GtkBuildable *buildable, GtkBuilder *builder);
static void gx_switch_destroy(GtkObject*);
static void gx_switch_init_pixmaps(int change_knob);
static void
gx_switch_set_property(GObject      *object,
                        guint         prop_id,
                        const GValue *value,
                        GParamSpec   *pspec);
static void
gx_switch_get_property(GObject      *object,
                        guint         prop_id,
                        GValue       *value,
                        GParamSpec   *pspec);
static gboolean gx_switch_enter_in (GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_switch_leave_out (GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_switch_expose (GtkWidget *widget, GdkEventExpose *event);
static void gx_switch_size_request (GtkWidget *widget, GtkRequisition *requisition);
static gboolean gx_switch_button_press (GtkWidget *widget, GdkEventButton *event);
static gboolean gx_switch_button_release (GtkWidget *widget, GdkEventButton *event);
static gboolean gx_switch_key_press (GtkWidget *widget, GdkEventKey *event);
static gboolean gx_switch_scroll (GtkWidget *widget, GdkEventScroll *event);
static void gx_control_parameter_interface_init (GxControlParameterIface *iface);

G_DEFINE_TYPE_WITH_CODE (GxSwitch, gx_switch, GTK_TYPE_TOGGLE_BUTTON,
                         G_IMPLEMENT_INTERFACE (GTK_TYPE_BUILDABLE,
                                                gx_switch_buildable_interface_init)
                         G_IMPLEMENT_INTERFACE (GX_TYPE_CONTROL_PARAMETER,
                                                gx_control_parameter_interface_init));

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
			{ GX_SWITCH_TYPE_VALUE_DISPLAY, "GX_SWITCH_TYPE_VALUE_DISPLAY", "value display" },
			{ 0, NULL, NULL }
		};
		etype = g_enum_register_static (g_intern_static_string ("GxSwitchType"), values);
	}
	return etype;
}


static void
gx_switch_do_action (GxControlParameter *self)
{
	GtkToggleButton *b = GTK_TOGGLE_BUTTON(self);
	int a = gtk_toggle_button_get_active(b);
	gtk_toggle_button_set_active(b, !a);
}

static void
gx_control_parameter_interface_init(GxControlParameterIface *iface)
{
  iface->do_action = gx_switch_do_action;
}

static void gx_switch_class_init(GxSwitchClass *klass)
{
	GObjectClass   *gobject_class;
	GtkObjectClass *object_class;
	GtkWidgetClass *widget_class;

	gobject_class = G_OBJECT_CLASS (klass);
	object_class = (GtkObjectClass*) klass;
	widget_class = (GtkWidgetClass*) klass;

	gobject_class->set_property = gx_switch_set_property;
	gobject_class->get_property = gx_switch_get_property;

	object_class->destroy = gx_switch_destroy;


//--------- init pixmaps
	klass->pix_is = 0;

//--------- connect the events with funktions
	widget_class->enter_notify_event = gx_switch_enter_in;
	widget_class->leave_notify_event = gx_switch_leave_out;
	widget_class->expose_event = gx_switch_expose;
	widget_class->size_request = gx_switch_size_request;
	widget_class->button_press_event = gx_switch_button_press;
	widget_class->button_release_event = gx_switch_button_release;
	widget_class->key_press_event = gx_switch_key_press;
	widget_class->scroll_event = gx_switch_scroll;

	g_object_class_install_property(gobject_class,
	                                PROP_TYPE,
	                                g_param_spec_enum("switch-type",
	                                                  P_("Type"),
	                                                  P_("The type of the control"),
	                                                  switch_type_get_type(),
	                                                  GX_SWITCH_TYPE_SWITCH,
	                                                  GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property(gobject_class,
	                                PROP_VAR_ID,
	                                g_param_spec_string("var-id",
	                                                    P_("Variable"),
	                                                    P_("The id of the linked variable"),
	                                                    NULL,
	                                                    GParamFlags(GTK_PARAM_READWRITE)));

	gx_switch_init_pixmaps(0);
}

/****************************************************************
 ** Constants
 */

/** set here the sizes and steps for the used switch **/
//--------- switch size and steps
gint class_toggle_x = 37 ;
gint class_toggle_y = 28 ;
gint class_toggle_step = 1;

//--------- switchII size and steps
gint class_switch_x = 20 ;
gint class_switch_y = 10 ;
gint class_switch_step = 1;

//--------- switch minitoggle and steps
gint class_minitoggle_x = 10 ;
gint class_minitoggle_y = 10 ;
gint class_minitoggle_step = 1;

//--------- switch size and steps
gint class_b_toggle_x = 25 ;
gint class_b_toggle_y = 15 ;
gint class_b_toggle_step = 1;

//--------- led
gint class_led_x = 20 ;
gint class_led_y = 20 ;

//--------- led
gint class_vd_x = -1 ;
gint class_vd_y = 25 ;


/****************************************************************
 ** general expose events for all "switch" controllers
 */

//----------- draw the Switch when moved
static gboolean gx_switch_expose (GtkWidget *widget, GdkEventExpose *event)
{
	g_assert(GX_IS_SWITCH(widget));
	GxSwitch *swtch = GX_SWITCH(widget);
	GxSwitchClass *klass =  GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget));

	int switchx = widget->allocation.x, switchy = widget->allocation.y;

//---------- switch
	if (swtch->switch_type == GX_SWITCH_TYPE_SWITCH) {
		switchx += (widget->allocation.width -
		            class_toggle_x) *0.5;
		switchy += (widget->allocation.height -
		            class_toggle_y) *0.5;
		int switchstate = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
		if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
			gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			                klass->toggle_image1, switchstate *
			                class_toggle_x, 0, switchx, switchy,
			                class_toggle_x,
			                class_toggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
		} else {
			gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			                klass->toggle_image, switchstate *
			                class_toggle_x, 0, switchx, switchy,
			                class_toggle_x,
			                class_toggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
		}
	}

//---------- switchII
	else if (swtch->switch_type == GX_SWITCH_TYPE_SWITCH_II) {
		switchx += (widget->allocation.width -
		            class_switch_x) *0.5;
		switchy += (widget->allocation.height -
		            class_switch_y) *0.5;
		int switchstate = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
		if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
			gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			                klass->switch_image1, switchstate *
			                class_switch_x, 0, switchx, switchy,
			                class_switch_x,
			                class_switch_y, GDK_RGB_DITHER_NORMAL, 0, 0);
		} else {
			gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			                klass->switch_image, switchstate *
			                class_switch_x, 0, switchx, switchy,
			                class_switch_x,
			                class_switch_y, GDK_RGB_DITHER_NORMAL, 0, 0);
		}
	}

//---------- minitoggle
	else if (swtch->switch_type == GX_SWITCH_TYPE_MINI_TOGGLE) {
		switchx += (widget->allocation.width -
		            class_minitoggle_x) *0.5;
		switchy += (widget->allocation.height -
		            class_minitoggle_y) *0.5;
		int switchstate = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
		if (switchstate > 0) switchstate =2;
		if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
			gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			                klass->switch_image1, switchstate *
			                class_minitoggle_x, 0, switchx, switchy,
			                class_minitoggle_x,
			                class_minitoggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
		} else {
			gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			                klass->switch_image, switchstate *
			                class_minitoggle_x, 0, switchx, switchy,
			                class_minitoggle_x,
			                class_minitoggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
		}
	}

//---------- toggle button
	else if (swtch->switch_type == GX_SWITCH_TYPE_TOGGLE_BUTTON) {
		switchx += (widget->allocation.width -
		            class_b_toggle_x) *0.5;
		switchy += (widget->allocation.height -
		            class_b_toggle_y) *0.5;
		int switchstate = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
		if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
			gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			                klass->b_toggle_image1, 0,
			                switchstate * class_b_toggle_y, switchx, switchy,
			                class_b_toggle_x,
			                class_b_toggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
		} else {
			gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			                klass->b_toggle_image, 0,
			                switchstate * class_b_toggle_y,
			                switchx, switchy, class_b_toggle_x,
			                class_b_toggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
		}
	}

//---------- led
	else if (swtch->switch_type == GX_SWITCH_TYPE_LED) {
		int switchstate = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->led_image, 0,
		                switchstate * class_led_y, 8, 12, //left upper corner, else use reglex,switchy
		                class_led_x,
		                class_led_y, GDK_RGB_DITHER_NORMAL, 0, 0);
	}

	//---------- value display
	else if (swtch->switch_type == GX_SWITCH_TYPE_VALUE_DISPLAY) {
		switchx += (widget->allocation.x);
		switchy += (widget->allocation.height -
		            class_vd_y) *0.5;
		/*FIXME
		float adj->value;

			char s[64];

			if (adj->step_increment < 0.009999)
			{
				const char* format[] = {"%.1f", "%.2f", "%.3f"};
				snprintf(s, 63, format[3-1], v);
			}
			else if (adj->step_increment < 0.09999)
			{
				const char* format[] = {"%.1f", "%.2f", "%.3f"};
				snprintf(s, 63, format[2-1], v);
			}
			else if (adj->step_increment < 0.9999)
			{
				const char* format[] = {"%.1f", "%.2f", "%.3f"};
				snprintf(s, 63, format[1-1], v);
			}
			else if (adj->step_increment < 9.9999)
			{
				snprintf(s, 63, "%d", (int)v);
			}
			else
				snprintf(s, 63, "%d", (int)v);
		*/
		const char *s = "bla";

		cairo_t *cr;
	/* create a cairo context */
	cr = gdk_cairo_create(widget->window);

	double x0      = widget->allocation.x+2;
	double y0      = widget->allocation.y+2;

	double rect_width  =  widget->allocation.width-4;
	double rect_height =  widget->allocation.height-4;

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
		cairo_set_font_size (cr, 10.0);
		cairo_move_to (cr, x0+5, y0+rect_height-4);
		cairo_show_text(cr, s);
		cairo_stroke (cr);

	cairo_destroy(cr);
	}

	return TRUE;
}

/****************************************************************
 ** redraw when leave
 */

static gboolean gx_switch_leave_out (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_SWITCH(widget));
	GxSwitch *swtch = GX_SWITCH(widget);
	GxSwitchClass *klass =  GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget));

	int switchx = widget->allocation.x, switchy = widget->allocation.y;

	if (swtch->switch_type == GX_SWITCH_TYPE_SWITCH) {
		switchx += (widget->allocation.width -
		            class_toggle_x) *0.5;
		switchy += (widget->allocation.height -
		            class_toggle_y) *0.5;
		int switchstate = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->toggle_image,
		                switchstate * class_toggle_x, 0,
		                switchx, switchy, class_toggle_x,
		                class_toggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
	}

//----------- switchII
	else if (swtch->switch_type == GX_SWITCH_TYPE_SWITCH_II) {
		switchx += (widget->allocation.width -
		            class_switch_x) *0.5;
		switchy += (widget->allocation.height -
		            class_switch_y) *0.5;
		int switchstate = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->switch_image,
		                switchstate * class_switch_x, 0,
		                switchx, switchy, class_switch_x,
		                class_switch_y, GDK_RGB_DITHER_NORMAL, 0, 0);
	}

//----------- minitoggle
	else if (swtch->switch_type == GX_SWITCH_TYPE_MINI_TOGGLE) {
		switchx += (widget->allocation.width -
		            class_minitoggle_x) *0.5;
		switchy += (widget->allocation.height -
		            class_minitoggle_y) *0.5;
		int switchstate = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
		if (switchstate > 0) switchstate =2;
		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->switch_image,
		                switchstate * class_minitoggle_x, 0,
		                switchx, switchy, class_minitoggle_x,
		                class_minitoggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
	}

//---------- toggle button
	else if (swtch->switch_type == GX_SWITCH_TYPE_TOGGLE_BUTTON) {
		switchx += (widget->allocation.width -
		            class_b_toggle_x) *0.5;
		switchy += (widget->allocation.height -
		            class_b_toggle_y) *0.5;
		int switchstate = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->b_toggle_image, 0,
		                switchstate * class_b_toggle_y,
		                switchx, switchy, class_b_toggle_x,
		                class_b_toggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);

	}

	return TRUE;
}

/****************************************************************
 ** redraw when enter
 */

static gboolean gx_switch_enter_in (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_SWITCH(widget));
	GxSwitch *swtch = GX_SWITCH(widget);
	GxSwitchClass *klass =  GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget));

	int switchx = widget->allocation.x, switchy = widget->allocation.y;

//----------- switch
	if (swtch->switch_type == GX_SWITCH_TYPE_SWITCH) {
		switchx += (widget->allocation.width -
		            class_toggle_x) *0.5;
		switchy += (widget->allocation.height -
		            class_toggle_y) *0.5;
		int switchstate = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->toggle_image1,
		                switchstate * class_toggle_x, 0,
		                switchx, switchy, class_toggle_x,
		                class_toggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
	}

//----------- switch
	else if (swtch->switch_type == GX_SWITCH_TYPE_SWITCH_II) {
		switchx += (widget->allocation.width -
		            class_switch_x) *0.5;
		switchy += (widget->allocation.height -
		            class_switch_y) *0.5;
		int switchstate = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->switch_image1,
		                switchstate * class_switch_x, 0,
		                switchx, switchy, class_switch_x,
		                class_switch_y, GDK_RGB_DITHER_NORMAL, 0, 0);
	}

//----------- minitoggle
	else if (swtch->switch_type == GX_SWITCH_TYPE_MINI_TOGGLE) {
		switchx += (widget->allocation.width -
		            class_minitoggle_x) *0.5;
		switchy += (widget->allocation.height -
		            class_minitoggle_y) *0.5;
		int switchstate = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
		if (switchstate > 0) switchstate =2;
		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->switch_image1, switchstate *
		                class_minitoggle_x, 0, switchx, switchy,
		                class_minitoggle_x,
		                class_minitoggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
	}

//---------- toggle button
	else if (swtch->switch_type == GX_SWITCH_TYPE_TOGGLE_BUTTON) {
		switchx += (widget->allocation.width -
		            class_b_toggle_x) *0.5;
		switchy += (widget->allocation.height -
		            class_b_toggle_y) *0.5;
		int switchstate = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
		gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
		                klass->b_toggle_image1, 0,
		                switchstate * class_b_toggle_y,
		                switchx, switchy, class_b_toggle_x,
		                class_b_toggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);

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

//----------- switch
	if (swtch->switch_type == GX_SWITCH_TYPE_SWITCH) {
		requisition->width = class_toggle_x;
		requisition->height = class_toggle_y;
	}
//----------- switch2
	else if (swtch->switch_type == GX_SWITCH_TYPE_SWITCH_II) {
		requisition->width = class_switch_x;
		requisition->height = class_switch_y;
	}
//----------- minitoggle
	else if (swtch->switch_type == GX_SWITCH_TYPE_MINI_TOGGLE) {
		requisition->width = class_minitoggle_x;
		requisition->height = class_minitoggle_y;
	}
//----------- togglebutton
	else if (swtch->switch_type == GX_SWITCH_TYPE_TOGGLE_BUTTON) {
		requisition->width = class_b_toggle_x;
		requisition->height = class_b_toggle_y;
	}
//-----------  led
	else if (swtch->switch_type == GX_SWITCH_TYPE_LED) {
		requisition->width = class_led_x;
		requisition->height = class_led_y;
	}
//-----------  led
	else if (swtch->switch_type == GX_SWITCH_TYPE_VALUE_DISPLAY) {
		requisition->width = class_vd_x;
		requisition->height = class_vd_y;
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

void gx_switch_init_pixmaps(int change_knob)
{
	GtkWidget *widget = GTK_WIDGET(g_object_new(GX_TYPE_SWITCH, NULL));
	g_assert(GX_IS_SWITCH(widget));
	GxSwitchClass *klass =  GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget));

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
	klass->pix_is = 1;
}

/****************************************************************
 ** init the Switch type/size
 */

static void gx_switch_init(GxSwitch *swtch)
{
	GtkWidget *widget = GTK_WIDGET(swtch);
	//GxSwitchClass *klass =  GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget));

	gtk_widget_set_has_window (GTK_WIDGET (swtch), FALSE);
	GTK_WIDGET_SET_FLAGS (GTK_WIDGET(swtch), GTK_CAN_FOCUS);
	GTK_WIDGET_SET_FLAGS (GTK_WIDGET(swtch), GTK_CAN_DEFAULT);

	if (swtch->switch_type == GX_SWITCH_TYPE_SWITCH) {
		widget->requisition.width = class_toggle_x;
		widget->requisition.height = class_toggle_y;
	} else if (swtch->switch_type == GX_SWITCH_TYPE_SWITCH_II) {
		widget->requisition.width = class_switch_x;
		widget->requisition.height = class_switch_y;
	} else if (swtch->switch_type == GX_SWITCH_TYPE_MINI_TOGGLE) {
		widget->requisition.width = class_minitoggle_x;
		widget->requisition.height = class_minitoggle_y;
	} else if (swtch->switch_type == GX_SWITCH_TYPE_TOGGLE_BUTTON) {
		widget->requisition.width = class_b_toggle_x;
		widget->requisition.height = class_b_toggle_y;
	} else if (swtch->switch_type == GX_SWITCH_TYPE_LED) {
		widget->requisition.width = class_led_x;
		widget->requisition.height = class_led_y;
	} else if (swtch->switch_type == GX_SWITCH_TYPE_VALUE_DISPLAY) {
		widget->requisition.width = class_vd_x;
		widget->requisition.height = class_vd_y;
	}
}

/****************************************************************
 ** redraw when value changed
 */

/*
static gboolean gx_switch_value_changed(gpointer obj)
{
	GtkWidget *widget = (GtkWidget *)obj;
	gtk_widget_queue_draw(widget);
	return FALSE;
}
*/

/****************************************************************
 */
void gx_switch_destroy(GtkObject *object)
{
/*
	if (G_IS_OBJECT(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))-> switch_image))
		g_object_unref(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))-> switch_image);
	if (G_IS_OBJECT(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))-> bigswitch_image))
		g_object_unref(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))-> bigswitch_image);
	if (G_IS_OBJECT(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))-> toggle_image))
		g_object_unref(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_image);
	if (G_IS_OBJECT(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))-> toggle_image1))
		g_object_unref(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_image1);
	if (G_IS_OBJECT(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))-> slider_image))
		g_object_unref(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image);
	if (G_IS_OBJECT(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))-> slider_image1))
		g_object_unref(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1);
	if (G_IS_OBJECT(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))-> minislider_image))
		g_object_unref(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image);
	if (G_IS_OBJECT(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))-> minislider_image1))
		g_object_unref(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image1);
	if (G_IS_OBJECT(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))-> switch_image))
		g_object_unref(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_image);
	if (G_IS_OBJECT(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))-> switch_image1))
		g_object_unref(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_image1);
	if (G_IS_OBJECT(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))-> wheel_image))
		g_object_unref(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_image);
	if (G_IS_OBJECT(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))-> wheel_image1))
		g_object_unref(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_image1);
	if (G_IS_OBJECT(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))-> b_toggle_image))
		g_object_unref(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_image);
	if (G_IS_OBJECT(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))-> vslider_image))
		g_object_unref(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image);
	if (G_IS_OBJECT(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))-> vslider_image1))
		g_object_unref(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image1);
	if (G_IS_OBJECT(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))-> eqslider_image))
		g_object_unref(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))->eqslider_image);
	if (G_IS_OBJECT(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))-> eqslider_image1))
		g_object_unref(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))->eqslider_image1);
	if (G_IS_OBJECT(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))-> led_image))
		g_object_unref(GX_SWITCH_CLASS(GTK_OBJECT_GET_CLASS(widget))->led_image);
*/
	GTK_OBJECT_CLASS (gx_switch_parent_class)->destroy (object);
}


/****************************************************************
 ** get the Switch type
 */

/*
GType gx_switch_get_type (void)
{
	static GType kn_type = 0;
	if (!kn_type) {
		static const GTypeInfo kn_info = {
			sizeof(GxSwitchClass), NULL,  NULL, (GClassInitFunc)gx_switch_class_init, NULL, NULL, sizeof (GxSwitch), 0, (GInstanceInitFunc)gx_switch_init
		};
		kn_type = g_type_register_static(GTK_TYPE_RANGE,  "GxSwitch", &kn_info, (GTypeFlags)0);
	}
	return kn_type;
}
*/

/****************************************************************
 ** GtkBuildable Interface
 */

 //static GtkBuildableIface *buildable_parent_iface = NULL;

static void gx_switch_buildable_interface_init(GtkBuildableIface *iface)
{
	//buildable_parent_iface = g_type_interface_peek_parent(iface);
	iface->parser_finished = gx_switch_parser_finished;
}

static void gx_switch_parser_finished(GtkBuildable *buildable, GtkBuilder *builder)
{
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
gx_switch_set_property (GObject      *object,
                           guint         prop_id,
                           const GValue *value,
                           GParamSpec   *pspec)
{
	GxSwitch *swtch;

	swtch = GX_SWITCH (object);

	switch(prop_id) {
	case PROP_TYPE:
		swtch->switch_type = g_value_get_enum(value);
		break;
	case PROP_VAR_ID:
		gx_switch_set_var_id (swtch, g_value_get_string (value));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
gx_switch_get_property(GObject      *object,
                        guint         prop_id,
                        GValue       *value,
                        GParamSpec   *pspec)
{
	GxSwitch *swtch;

	swtch = GX_SWITCH(object);

	switch(prop_id) {
	case PROP_TYPE:
		g_value_set_enum(value, swtch->switch_type);
		break;
	case PROP_VAR_ID:
		g_value_set_string (value, swtch->var_id);
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

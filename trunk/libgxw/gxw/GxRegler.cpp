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

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#include "GxRegler.h"
#include "GxControlParameter.h"
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <gtk/gtkprivate.h>
#include <gtk/gtkbindings.h>
#include <gtk/gtkmarshal.h>

#define P_(s) (s)   // FIXME -> gettext
#define I_(s) (s)   // FIXME -> gettext

/****************************************************************
 ** GxRegler
 */

#define GX_REGLER_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), GX_TYPE_REGLER, GxReglerPrivate))

typedef struct
{
	GtkRequisition value_req;
	gdouble last_step;
} GxReglerPrivate;

enum {
  VALUE_ENTRY,
  LAST_SIGNAL
};

enum {
	PROP_VAR_ID = 1,
	PROP_SHOW_VALUE,
	PROP_VALUE_POSITION,
	PROP_LABEL,
};

static guint signals[LAST_SIGNAL] = {0,};

static void gx_regler_class_init(GxReglerClass *klass);
static void gx_regler_init(GxRegler *regler);
static void gx_control_parameter_interface_init (GxControlParameterIface *iface);
static void gx_regler_finalize(GObject*);
static void gx_regler_style_set (GtkWidget *widget, GtkStyle  *previous_style);
static void gx_regler_destroy(GtkObject *object);
static void gx_regler_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gx_regler_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static gboolean gx_regler_button_release (GtkWidget *widget, GdkEventButton *event);
static gboolean gx_regler_scroll (GtkWidget *widget, GdkEventScroll *event);
static gboolean gx_regler_change_value(GtkRange *range, GtkScrollType scroll, gdouble value);
static void gx_regler_value_changed(GtkRange *range);
static gboolean gx_regler_value_entry(GxRegler *regler, GdkRectangle *rect);

G_DEFINE_ABSTRACT_TYPE_WITH_CODE(GxRegler, gx_regler, GTK_TYPE_RANGE,
                                 G_IMPLEMENT_INTERFACE(GX_TYPE_CONTROL_PARAMETER,
                                                       gx_control_parameter_interface_init));

static void gx_regler_value_changed(GtkRange *range)
{
	gtk_widget_queue_draw(GTK_WIDGET(range));
}


static void
gx_regler_cp_configure(GxControlParameter *self, gchar* group, gchar *name, gdouble lower, gdouble upper, gdouble step)
{
	GxRegler *regler = GX_REGLER(self);
	if (regler->label) {
		gtk_label_set_text(regler->label, name);
	}
}

static gdouble
gx_regler_cp_get_value(GxControlParameter *self)
{
	return gtk_range_get_value(GTK_RANGE(self));
}

static void
gx_regler_cp_set_value(GxControlParameter *self, gdouble value)
{
	gtk_range_set_value(GTK_RANGE(self), value);
}

static void
gx_control_parameter_interface_init(GxControlParameterIface *iface)
{
  iface->cp_configure = gx_regler_cp_configure;
  iface->cp_set_value = gx_regler_cp_set_value;
  iface->cp_get_value = gx_regler_cp_get_value;
}

gboolean gx_boolean_handled_accumulator(
	GSignalInvocationHint *ihint, GValue *return_accu,
	const GValue *handler_return, gpointer dummy)
{
  gboolean continue_emission;
  gboolean signal_handled;
  
  signal_handled = g_value_get_boolean (handler_return);
  g_value_set_boolean (return_accu, signal_handled);
  continue_emission = !signal_handled;
  
  return continue_emission;
}

static void marshal_BOOLEAN__BOXED(
	GClosure *closure, GValue *return_value G_GNUC_UNUSED,
	guint n_param_values, const GValue *param_values,
	gpointer invocation_hint G_GNUC_UNUSED, gpointer marshal_data)
{
	typedef gboolean (*GMarshalFunc_BOOLEAN__BOXED) (
		gpointer data1, gpointer arg_1, gpointer data2);
	register GMarshalFunc_BOOLEAN__BOXED callback;
	register GCClosure *cc = (GCClosure*) closure;
	register gpointer data1, data2;
	gboolean v_return;

	g_return_if_fail (return_value != NULL);
	g_return_if_fail (n_param_values == 2);

	if (G_CCLOSURE_SWAP_DATA(closure)) {
		data1 = closure->data;
		data2 = g_value_peek_pointer (param_values + 0);
	} else {
		data1 = g_value_peek_pointer (param_values + 0);
		data2 = closure->data;
	}
	callback = (GMarshalFunc_BOOLEAN__BOXED)(
		marshal_data ? marshal_data : cc->callback);
	v_return = callback(
		data1, g_value_get_boxed(param_values + 1), data2);
	g_value_set_boolean(return_value, v_return);
}


#define add_slider_binding(binding_set, keyval, mask, scroll)              \
  gtk_binding_entry_add_signal (binding_set, keyval, mask,                 \
                                I_("move-slider"), 1, \
                                GTK_TYPE_SCROLL_TYPE, scroll)

static void gx_regler_class_init(GxReglerClass *klass)
{
	GObjectClass   *gobject_class = G_OBJECT_CLASS(klass);
	GtkObjectClass *object_class = (GtkObjectClass*) klass;
	GtkRangeClass *range_class = (GtkRangeClass*)klass;
	GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;
	GtkBindingSet  *binding_set;

	klass->change_value_id = g_signal_lookup("change-value", GTK_TYPE_RANGE);

	gobject_class->finalize = gx_regler_finalize;
	gobject_class->set_property = gx_regler_set_property;
	gobject_class->get_property = gx_regler_get_property;

	object_class->destroy = gx_regler_destroy;

	widget_class->style_set = gx_regler_style_set;
	widget_class->button_release_event = gx_regler_button_release;
	widget_class->scroll_event = gx_regler_scroll;

	range_class->value_changed = gx_regler_value_changed;
	range_class->change_value = gx_regler_change_value;

	klass->value_entry = gx_regler_value_entry;

	signals[VALUE_ENTRY] =
		g_signal_new (I_("value-entry"),
		              G_OBJECT_CLASS_TYPE (klass),
		              G_SIGNAL_RUN_LAST,
		              G_STRUCT_OFFSET (GxReglerClass, value_entry),
		              gx_boolean_handled_accumulator, NULL,
		              marshal_BOOLEAN__BOXED,
		              G_TYPE_BOOLEAN, 1, GDK_TYPE_RECTANGLE);

	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("value-spacing",P_("Value spacing"),
		                 P_("Distance of value display"),
		                 0, 100, 5, GParamFlags(GTK_PARAM_READABLE)));

	g_object_class_install_property(
		gobject_class, PROP_SHOW_VALUE,
		g_param_spec_boolean("show-value",
		                     P_("show value"),
		                     P_("display the value"),
		                     TRUE,
		                     GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property(
		gobject_class, PROP_LABEL,
		g_param_spec_boolean("label",
		                     P_("Label reference"),
		                     P_("Label for caption display"),
		                     TRUE,
		                     GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property(
		gobject_class, PROP_VALUE_POSITION,
		g_param_spec_enum("value-position",
		                  P_("Value Position"),
		                  P_("The position of the value display"),
		                  GTK_TYPE_POSITION_TYPE,
		                  GTK_POS_BOTTOM,
		                  GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_override_property(gobject_class, PROP_VAR_ID, "var-id");

	binding_set = gtk_binding_set_by_class(klass);

	add_slider_binding (binding_set, GDK_Left, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_LEFT);

	add_slider_binding (binding_set, GDK_Left, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_LEFT);

	add_slider_binding (binding_set, GDK_KP_Left, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_LEFT);

	add_slider_binding (binding_set, GDK_KP_Left, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_LEFT);

	add_slider_binding (binding_set, GDK_Right, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_RIGHT);

	add_slider_binding (binding_set, GDK_Right, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_RIGHT);

	add_slider_binding (binding_set, GDK_KP_Right, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_RIGHT);

	add_slider_binding (binding_set, GDK_KP_Right, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_RIGHT);

	add_slider_binding (binding_set, GDK_Up, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_UP);

	add_slider_binding (binding_set, GDK_Up, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_UP);

	add_slider_binding (binding_set, GDK_KP_Up, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_UP);

	add_slider_binding (binding_set, GDK_KP_Up, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_UP);

	add_slider_binding (binding_set, GDK_Down, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_DOWN);

	add_slider_binding (binding_set, GDK_Down, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_DOWN);

	add_slider_binding (binding_set, GDK_KP_Down, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_DOWN);

	add_slider_binding (binding_set, GDK_KP_Down, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_DOWN);

	add_slider_binding (binding_set, GDK_Page_Up, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_LEFT);

	add_slider_binding (binding_set, GDK_KP_Page_Up, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_LEFT);

	add_slider_binding (binding_set, GDK_Page_Up, (GdkModifierType)0,
	                    GTK_SCROLL_PAGE_UP);

	add_slider_binding (binding_set, GDK_KP_Page_Up, (GdkModifierType)0,
	                    GTK_SCROLL_PAGE_UP);

	add_slider_binding (binding_set, GDK_Page_Down, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_RIGHT);

	add_slider_binding (binding_set, GDK_KP_Page_Down, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_RIGHT);

	add_slider_binding (binding_set, GDK_Page_Down, (GdkModifierType)0,
	                    GTK_SCROLL_PAGE_DOWN);

	add_slider_binding (binding_set, GDK_KP_Page_Down, (GdkModifierType)0,
	                    GTK_SCROLL_PAGE_DOWN);

	/* Logical bindings (vs. visual bindings above) */

	add_slider_binding (binding_set, GDK_plus, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_FORWARD);

	add_slider_binding (binding_set, GDK_minus, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_BACKWARD);

	add_slider_binding (binding_set, GDK_plus, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_FORWARD);

	add_slider_binding (binding_set, GDK_minus, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_BACKWARD);


	add_slider_binding (binding_set, GDK_KP_Add, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_FORWARD);

	add_slider_binding (binding_set, GDK_KP_Subtract, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_BACKWARD);

	add_slider_binding (binding_set, GDK_KP_Add, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_FORWARD);

	add_slider_binding (binding_set, GDK_KP_Subtract, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_BACKWARD);


	add_slider_binding (binding_set, GDK_Home, (GdkModifierType)0,
	                    GTK_SCROLL_START);

	add_slider_binding (binding_set, GDK_KP_Home, (GdkModifierType)0,
	                    GTK_SCROLL_START);

	add_slider_binding (binding_set, GDK_End, (GdkModifierType)0,
	                    GTK_SCROLL_END);

	add_slider_binding (binding_set, GDK_KP_End, (GdkModifierType)0,
	                    GTK_SCROLL_END);

	g_type_class_add_private(klass, sizeof (GxReglerPrivate));
}

static void gx_regler_destroy(GtkObject *object)
{
	GxRegler *regler = GX_REGLER(object);
	if (regler->label) {
		g_object_unref(regler->label);
		regler->label = 0;
	}
	GTK_OBJECT_CLASS(gx_regler_parent_class)->destroy(object);
}

static void gx_regler_finalize(GObject *object)
{
	GxRegler *regler = GX_REGLER(object);
	g_free(regler->var_id);
	if (regler->value_layout) {
		g_object_unref(regler->value_layout);
	}
	G_OBJECT_CLASS(gx_regler_parent_class)->finalize(object);
}

static gint get_digits(GtkRange *range)
{
	GxReglerPrivate *priv = GX_REGLER_GET_PRIVATE(range);
	GtkAdjustment *adj = range->adjustment;
	if (!adj) {
		return range->round_digits;
	}
	gdouble v = adj->step_increment;
	if (v == priv->last_step) {
		return range->round_digits;
	}
	if (v == 0.0) {
		priv->last_step = 0.0;
		return range->round_digits;
	}
	gint n = 0;
	while (v < 1.0 - 1e-3) {
		v *= 10;
		n++;
	}
	range->round_digits = n;
	return range->round_digits;
}

static gboolean gx_regler_change_value(GtkRange *range, GtkScrollType scroll, gdouble value)
{
	g_assert(GX_IS_REGLER(range));
	get_digits(range);
	return GTK_RANGE_CLASS(gx_regler_parent_class)->change_value(range, scroll, value);
}

/****************************************************************
 ** calculate the knop pointer with dead zone
 */

static void gx_regler_ensure_layout(GxRegler *regler)
{
	if (regler->show_value && !regler->value_layout) {
		regler->value_layout = gtk_widget_create_pango_layout(GTK_WIDGET(regler), NULL);
		pango_layout_set_font_description(
			regler->value_layout, pango_font_description_from_string("Sans 8"));
	}
}

static const double scale_zero = 20 * (M_PI/180); // defines "dead zone" for knobs

#ifndef min
#define min(x, y) ((x) < (y) ? (x) : (y))
#endif
#ifndef max
#define max(x, y) ((x) < (y) ? (y) : (x))
#endif

gdouble _gx_regler_get_step_pos(GxRegler *regler, gint step)
{
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(regler));
	double df = adj->upper - adj->lower;
	if (df == 0.0) {
		return 0.0;
	} else {
		return (adj->value - adj->lower) * step / df;
	}
}

void _gx_regler_get_positions(GxRegler *regler, GdkRectangle *image_rect,
                              GdkRectangle *value_rect)
{
	GtkWidget *widget = GTK_WIDGET(regler);
	gint x = widget->allocation.x;
	gint y = widget->allocation.y;
	gint width = image_rect->width;
	gint height =  image_rect->height;
	if (regler->show_value) {
		GxReglerPrivate *priv = GX_REGLER_GET_PRIVATE(regler);
		gint text_width = priv->value_req.width;
		gint text_height = priv->value_req.height;
		gint text_x, text_y;
		gint value_spacing;
		gtk_widget_style_get(widget, "value-spacing", &value_spacing, NULL);
		switch (regler->value_position) {
		case GTK_POS_LEFT:
			text_x = x + (widget->allocation.width - width - text_width - value_spacing) / 2;
			text_y = y + (widget->allocation.height - text_height) / 2;
			image_rect->x = x + (widget->allocation.width - width + text_width + value_spacing) / 2;
			image_rect->y = y + (widget->allocation.height - height) / 2;
			break;
		case GTK_POS_RIGHT:
			text_x = x + value_spacing + (widget->allocation.width + width - text_width - value_spacing) / 2;
			text_y = y + (widget->allocation.height - text_height) / 2;
			image_rect->x = x + (widget->allocation.width - width - text_width - value_spacing) / 2;
			image_rect->y = y + (widget->allocation.height - height) / 2;
			break;
		case GTK_POS_TOP:
			text_x = x + (widget->allocation.width - text_width) / 2;
			text_y = y + (widget->allocation.height - height - text_height - value_spacing) / 2;
			image_rect->x = x + (widget->allocation.width - width) / 2;
			image_rect->y = y + (widget->allocation.height - height + text_height + value_spacing) / 2;
			break;
		case GTK_POS_BOTTOM:
			text_x = x + (widget->allocation.width - text_width) / 2;
			text_y = y + value_spacing + (widget->allocation.height + height - text_height - value_spacing) / 2;
			image_rect->x = x + (widget->allocation.width - width) / 2;
			image_rect->y = y + (widget->allocation.height - height - text_height - value_spacing) / 2;
			break;
		}
		if (value_rect) {
			value_rect->x = text_x;
			value_rect->y = text_y;
			value_rect->width = text_width;
			value_rect->height = text_height;
		}
	} else {
		image_rect->x = x + (widget->allocation.width - width) / 2;
		image_rect->y = y + (widget->allocation.height - height) / 2;
		if (value_rect) {
			value_rect->x = value_rect->y = value_rect->width = value_rect->height = 0;
		}
	}
}

void _gx_regler_display_value(GxRegler *regler, GdkRectangle *rect)
{
	if (!regler->show_value) {
		return;
	}
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(regler));
	char s[64];
	snprintf(s, sizeof(s), "%.*f", get_digits(GTK_RANGE(regler)), gtk_adjustment_get_value(adj));

	cairo_t *cr = gdk_cairo_create(GTK_WIDGET(regler)->window);
	double x0 = rect->x + 1;
	double y0 = rect->y + 1;
	double rect_width  =  rect->width - 2;
	double rect_height =  rect->height - 2;

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
    PangoLayout *l = regler->value_layout;
    pango_layout_set_text(l, s, -1);
    PangoRectangle logical_rect;
    pango_layout_get_pixel_extents(l, NULL, &logical_rect);
    cairo_move_to (cr, x0-1+(rect->width - logical_rect.width)/2, y0+3);
    pango_cairo_show_layout(cr, l);

	cairo_destroy(cr);
}

void _gx_regler_calc_size_request(GxRegler *regler, GtkRequisition *requisition)
{
	gx_regler_ensure_layout(regler);
	if (regler->show_value) {
		PangoRectangle logical_rect1, logical_rect2;
		GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(regler));
		gint value_spacing;
		int p = get_digits(GTK_RANGE(regler));
		char buf[20];
		int borderx = 12, bordery = 6;
		gtk_widget_style_get(GTK_WIDGET(regler), "value-spacing", &value_spacing, NULL);
		snprintf(buf, sizeof(buf), "%.*f", p, gtk_adjustment_get_lower(adj));
		pango_layout_set_text(regler->value_layout, buf, -1);
		pango_layout_get_pixel_extents(regler->value_layout, NULL, &logical_rect1);
		snprintf(buf, sizeof(buf), "%.*f", p, gtk_adjustment_get_upper(adj));
		pango_layout_set_text(regler->value_layout, buf, -1);
		pango_layout_get_pixel_extents(regler->value_layout, NULL, &logical_rect2);
		gint height = max(logical_rect1.height,logical_rect2.height) + bordery;
		gint width = max(logical_rect1.width,logical_rect2.width) + borderx;
		GxReglerPrivate *priv = GX_REGLER_GET_PRIVATE(regler);
		priv->value_req.width = width;
		priv->value_req.height = height;
		switch (regler->value_position) {
		case GTK_POS_LEFT:
		case GTK_POS_RIGHT:
			requisition->width += width + value_spacing;
			if (height > requisition->height) {
				requisition->height = height;
			}
			break;
		case GTK_POS_TOP:
		case GTK_POS_BOTTOM:
			requisition->height += height + value_spacing;
			if (width > requisition->width) {
				requisition->width = width;
			}
			break;
		}
	}
}

/****************************************************************
 ** set value from key bindings
 */

static void gx_regler_set_value (GtkWidget *widget, int dir_down)
{
	g_assert(GX_IS_REGLER(widget));

	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));

	int oldstep = (int)(0.5f + (adj->value - adj->lower) / adj->step_increment);
	int step;
	int nsteps = (int)(0.5f + (adj->upper - adj->lower) / adj->step_increment);
	if (dir_down)
		step = oldstep - 1;
	else
		step = oldstep + 1;
	float value = adj->lower + step * (double)(adj->upper - adj->lower) / nsteps;
	gtk_widget_grab_focus(widget);
	gtk_range_set_value(GTK_RANGE(widget), value);
}

/****************************************************************
 ** mouse button pressed set value
 */

static gboolean dialog_button_press_event(
	GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	if (event->type == GDK_BUTTON_PRESS) {
		gtk_widget_destroy(GTK_WIDGET(data));
	}
	return TRUE;
}

static gboolean spinner_button_press_event(
	GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	if (event->button == 3) {
		return TRUE;
	}
	return FALSE;
}

static gboolean dialog_key_press_event(
	GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	if (event->is_modifier) {
		return FALSE;
	}
	gtk_widget_destroy(GTK_WIDGET(data));
	return FALSE;
}

static gboolean dialog_key_press_before(
	GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	if (event->keyval == GDK_Escape) {
		// spinbutton to current adjustment value
		gtk_adjustment_value_changed(GTK_SPIN_BUTTON(widget)->adjustment);
		gtk_widget_destroy(GTK_WIDGET(data));
		return TRUE;
	}
	return FALSE;
}

static gboolean dialog_grab_broken(
	GtkWidget *widget, GdkEvent *event, gpointer data)
{
	gtk_widget_destroy(GTK_WIDGET(data));
	return FALSE;
}

static gboolean map_check(
	GtkWidget *widget, GdkEvent *event, gpointer data)
{
	GtkWidget *dialog = GTK_WIDGET(widget);
	GdkWindow *window = gtk_widget_get_window(dialog);
	int rc;
	GdkCursor *c = gdk_cursor_new(GDK_RIGHT_PTR);
	rc = gdk_pointer_grab(window, TRUE,
	                      (GdkEventMask)(GDK_BUTTON_PRESS_MASK|
	                                     GDK_BUTTON_MOTION_MASK),
	                      NULL, c, GDK_CURRENT_TIME);
	gdk_cursor_unref(c);
	if (rc != GDK_GRAB_SUCCESS) {
		gtk_widget_destroy(dialog);
		return TRUE;
	}
	rc = gdk_keyboard_grab(window, TRUE, GDK_CURRENT_TIME);
	if (rc != GDK_GRAB_SUCCESS) {
		gdk_display_pointer_ungrab(gdk_drawable_get_display(window),
		                           GDK_CURRENT_TIME);
		gtk_widget_destroy(dialog);
		return TRUE;
	}
	gtk_grab_add(dialog);
	return FALSE;
}

static gboolean gx_regler_value_entry(GxRegler *regler, GdkRectangle *rect)
{
	g_assert(GX_IS_REGLER(regler));
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(regler));
	GtkWidget *dialog = gtk_window_new(GTK_WINDOW_POPUP);
	gtk_widget_add_events(dialog, GDK_BUTTON_PRESS_MASK|GDK_BUTTON_MOTION_MASK);
	GtkWidget *spinner = gtk_spin_button_new(
		GTK_ADJUSTMENT(adj), adj->step_increment,
		get_digits(GTK_RANGE(regler)));
	gtk_container_add (GTK_CONTAINER(dialog), spinner);
	g_signal_connect(spinner, "button-press-event", G_CALLBACK(spinner_button_press_event), NULL);
	g_signal_connect(dialog, "button-press-event", G_CALLBACK(dialog_button_press_event), dialog);
	g_signal_connect(spinner, "key-press-event", G_CALLBACK(dialog_key_press_before), dialog);
	g_signal_connect_after(spinner, "key-press-event", G_CALLBACK(dialog_key_press_event), dialog);
	g_signal_connect_object(spinner, "activate", G_CALLBACK(gtk_widget_destroy), dialog, (GConnectFlags)(G_CONNECT_AFTER|G_CONNECT_SWAPPED));
	g_signal_connect(dialog, "grab-broken-event", G_CALLBACK(dialog_grab_broken), dialog);
	g_signal_connect(dialog, "map-event", G_CALLBACK(map_check), GTK_WIDGET(regler));
	gtk_window_move(GTK_WINDOW(dialog), -100, -100); // trick so its not visible
	gtk_widget_show_all(dialog);
	GtkRequisition rq;
	gtk_widget_get_requisition(dialog, &rq);
	gint xorg, yorg;
	gdk_window_get_origin(GTK_WIDGET(regler)->window, &xorg, &yorg);
	gtk_window_move(GTK_WINDOW(dialog), xorg+rect->x+(rect->width-rq.width)/2, yorg+rect->y+(rect->height-rq.height)/2);
	return TRUE;
}

/****************************************************************
 ** mouse button release
 */

static gboolean gx_regler_button_release (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_REGLER(widget));
	if (gtk_widget_has_grab(widget))
		gtk_grab_remove(widget);
	return FALSE;
}

/****************************************************************
 ** set value from mouseweel
 */

static gboolean gx_regler_scroll (GtkWidget *widget, GdkEventScroll *event)
{
	usleep(5000);
	gx_regler_set_value(widget, event->direction);
	return FALSE;
}


static void gx_regler_style_set(GtkWidget *widget, GtkStyle  *previous_style)
{
	//FIXME: value_req need recalc
}

/****************************************************************
 ** init the Regler type/size
 */

static void gx_regler_init(GxRegler *regler)
{
	regler->value_position = GTK_POS_BOTTOM;
	gtk_widget_set_can_focus(GTK_WIDGET(regler), TRUE);
	gtk_widget_set_receives_default(GTK_WIDGET(regler), TRUE);
	gtk_widget_set_has_window(GTK_WIDGET(regler), FALSE);
}

/****************************************************************
 ** Properties
 */

static void gx_regler_set_var_id(GxRegler *regler, const gchar *str)
{
	g_free(regler->var_id);
	regler->var_id = g_strdup(str ? str : "");
	g_object_notify(G_OBJECT(regler), "var-id");
}

static void gx_regler_set_property (
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	GxRegler *regler;

	regler = GX_REGLER (object);

	switch(prop_id) {
	case PROP_VAR_ID:
		gx_regler_set_var_id (regler, g_value_get_string (value));
		break;
	case PROP_SHOW_VALUE:
		gx_regler_set_show_value(regler, g_value_get_boolean(value));
		break;
	case PROP_VALUE_POSITION:
		gx_regler_set_value_position(regler, GtkPositionType(g_value_get_enum(value)));
		break;
	case PROP_LABEL:
		gx_regler_set_label_ref(regler, GTK_LABEL(g_value_get_object(value)));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void gx_regler_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec*pspec)
{
	GxRegler *regler;

	regler = GX_REGLER(object);

	switch(prop_id) {
	case PROP_VAR_ID:
		g_value_set_string (value, regler->var_id);
	case PROP_SHOW_VALUE:
		g_value_set_boolean(value, regler->show_value);
		break;
	case PROP_VALUE_POSITION:
		g_value_set_enum(value, regler->value_position);
		break;
	case PROP_LABEL:
		g_value_set_object(value, regler->label);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

/*
** getter / setter
*/

void gx_regler_set_show_value(GxRegler *regler, gboolean value)
{
	g_return_if_fail(GX_IS_REGLER(regler));
	regler->show_value = value;
	gtk_widget_queue_resize(GTK_WIDGET(regler));
	g_object_notify(G_OBJECT(regler), "show-value");
}

gboolean gx_regler_get_show_value(GxRegler *regler)
{
	g_return_val_if_fail(GX_IS_REGLER(regler), 0);
	return regler->show_value;
}

void gx_regler_set_value_position(GxRegler *regler, GtkPositionType value)
{
	g_return_if_fail(GX_IS_REGLER(regler));
	regler->value_position = value;
	gtk_widget_queue_resize(GTK_WIDGET(regler));
	g_object_notify(G_OBJECT(regler), "value-position");
}

GtkPositionType gx_regler_get_value_position(GxRegler *regler)
{
	g_return_val_if_fail(GX_IS_REGLER(regler), GTK_POS_BOTTOM);
	return regler->value_position;
}

void gx_regler_set_label_ref(GxRegler *regler, GtkLabel *label)
{
	g_return_if_fail(GX_IS_REGLER(regler));
	g_return_if_fail(GTK_IS_LABEL(label));
	if (regler->label) {
		g_object_unref(regler->label);
		regler->label = 0;
	}
	if (label) {
		regler->label = label;
		g_object_ref(label);
	}
	g_object_notify(G_OBJECT(regler), "label");
}


GtkLabel *gx_regler_get_label_ref(GxRegler *regler)
{
	g_return_val_if_fail(GX_IS_REGLER(regler), 0);
	return regler->label;
}

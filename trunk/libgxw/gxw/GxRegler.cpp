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

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#include "GxRegler.h"
#include "GxControlParameter.h"
#include <gdk/gdkkeysyms.h>

#include "regler_marshal.cc"


#define P_(s) (s)   // FIXME -> gettext
#define I_(s) (s)   // FIXME -> gettext

/****************************************************************
 ** GxRegler
 */

struct _GxReglerPrivate
{
	GtkRequisition value_req;
	gdouble last_step;
	GtkAdjustment *adjustment;
	gchar *var_id;
	GtkLabel *label;
	gboolean show_value:1;
	GtkPositionType value_position:2;
	gdouble value_xalign;
	PangoLayout *value_layout;
};

enum {
  VALUE_ENTRY,
  FORMAT_VALUE,
  INPUT_VALUE,
  LAST_SIGNAL
};

enum {
	PROP_VAR_ID = 1,
	PROP_SHOW_VALUE,
	PROP_VALUE_POSITION,
	PROP_VALUE_XALIGN,
	PROP_LABEL_REF,
	PROP_DIGITS,
};

static guint signals[LAST_SIGNAL];

static void gx_regler_class_init(GxReglerClass *klass);
static void gx_regler_init(GxRegler *regler);
static void gx_control_parameter_interface_init (GxControlParameterIface *iface);
static void gx_regler_finalize(GObject*);
static void gx_regler_destroy(GtkWidget *object);
static void gx_regler_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gx_regler_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static gboolean gx_regler_button_release (GtkWidget *widget, GdkEventButton *event);
static gboolean gx_regler_scroll (GtkWidget *widget, GdkEventScroll *event);
static gboolean gx_regler_change_value(GtkRange *range, GtkScrollType scroll, gdouble value);
static void gx_regler_value_changed(GtkRange *range);
static gboolean gx_regler_value_entry(GxRegler *regler, GdkRectangle *rect, GdkEventButton *event);
static void gx_regler_change_adjustment(GxRegler *regler, GtkAdjustment *adjustment);
static void gx_regler_adjustment_notified(GObject *gobject, GParamSpec *pspec);
static void gx_regler_move_slider(GtkRange *range, GtkScrollType scroll);

G_DEFINE_ABSTRACT_TYPE_WITH_CODE(GxRegler, gx_regler, GTK_TYPE_RANGE,
								 G_ADD_PRIVATE(GxRegler)
                                 G_IMPLEMENT_INTERFACE(GX_TYPE_CONTROL_PARAMETER,
                                                       gx_control_parameter_interface_init));

static void gx_regler_value_changed(GtkRange *range)
{
	gtk_widget_queue_draw(GTK_WIDGET(range));
}


static void
gx_regler_cp_configure(GxControlParameter *self, const gchar* group, const gchar *name, gdouble lower, gdouble upper, gdouble step)
{
	g_return_if_fail(GX_IS_REGLER(self));
	GxRegler *regler = GX_REGLER(self);
	if (regler->priv->label) {
		gtk_label_set_text(regler->priv->label, name);
	}
	GtkRange *range = GTK_RANGE(self);
	gtk_range_set_range(range, lower, upper);
	gtk_range_set_increments(range, step, 10*step);
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

static gboolean single_string_accumulator(
	GSignalInvocationHint *ihint, GValue *return_accu,
	const GValue *handler_return, gpointer dummy)
{
	gboolean continue_emission;
	const gchar *str;

	str = g_value_get_string(handler_return);
	g_value_set_string(return_accu, str);
	continue_emission = str == NULL;
	return continue_emission;
}

#define add_slider_binding(binding_set, keyval, mask, scroll)              \
  gtk_binding_entry_add_signal (binding_set, keyval, mask,                 \
                                I_("move-slider"), 1, \
                                GTK_TYPE_SCROLL_TYPE, scroll)

static void gx_regler_class_init(GxReglerClass *klass)
{
	GObjectClass   *gobject_class = G_OBJECT_CLASS(klass);
	GtkRangeClass *range_class = (GtkRangeClass*)klass;
	GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;
	GtkBindingSet  *binding_set;

	gobject_class->finalize = gx_regler_finalize;
	gobject_class->set_property = gx_regler_set_property;
	gobject_class->get_property = gx_regler_get_property;

	widget_class->destroy = gx_regler_destroy;
	widget_class->button_release_event = gx_regler_button_release;
	widget_class->scroll_event = gx_regler_scroll;

	range_class->value_changed = gx_regler_value_changed;
	range_class->change_value = gx_regler_change_value;
	range_class->move_slider = gx_regler_move_slider;

	klass->value_entry = gx_regler_value_entry;

	gtk_widget_class_set_css_name(widget_class, "gx-regler");

	signals[VALUE_ENTRY] =
		g_signal_new (I_("value-entry"),
		              G_OBJECT_CLASS_TYPE (klass),
		              G_SIGNAL_RUN_LAST,
		              G_STRUCT_OFFSET (GxReglerClass, value_entry),
		              gx_boolean_handled_accumulator, NULL,
		              marshal_BOOLEAN__BOXED_BOXED,
		              G_TYPE_BOOLEAN, 2, GDK_TYPE_RECTANGLE,
		              GDK_TYPE_EVENT | G_SIGNAL_TYPE_STATIC_SCOPE);

	signals[FORMAT_VALUE] =
		g_signal_new (I_("format-value"),
					  G_TYPE_FROM_CLASS (gobject_class),
					  G_SIGNAL_RUN_LAST,
					  G_STRUCT_OFFSET (GxReglerClass, format_value),
					  single_string_accumulator, NULL,
					  marshal_STRING__DOUBLE,
					  G_TYPE_STRING, 1,
					  G_TYPE_DOUBLE);

	signals[INPUT_VALUE] =
		g_signal_new (I_("input-value"),
					  G_TYPE_FROM_CLASS (gobject_class),
					  G_SIGNAL_RUN_LAST,
					  G_STRUCT_OFFSET (GxReglerClass, input_value),
					  NULL, NULL,
					  NULL,
					  G_TYPE_INT, 2,
					  G_TYPE_POINTER, //FIXME: GtkEntry*, gdouble*
					  G_TYPE_POINTER);
    
    gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("border-radius",
            P_("Border Radius"),
            P_("The radius of the corners in pixels"),
            0, 100, 0,
            GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
    
    gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_float("bevel",
            P_("Bevel"),
            P_("The bevel effect"),
            -1.0, 1.0, 0.0,
            GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
            
	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_boolean("show-value",
		                     P_("show value"),
		                     P_("display the value"),
		                     TRUE,
		                     GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("value-spacing",P_("Value spacing"),
		                 P_("Distance of value display"),
		                 0, 100, 5, GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_boxed("value-border",
		                   P_("Value Spacing"),
		                   P_("Extra space for value display"),
		                   GTK_TYPE_BORDER,
		                   GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));

	g_object_class_install_property(
		gobject_class, PROP_SHOW_VALUE,
		g_param_spec_boolean("show-value",
		                     P_("show value"),
		                     P_("display the value"),
		                     TRUE,
		                     GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_LABEL_REF,
		g_param_spec_object("label-ref",
		                    P_("Label ref"),
		                    P_("GtkLabel for caption"),
		                    GTK_TYPE_LABEL,
		                    GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_VALUE_POSITION,
		g_param_spec_enum("value-position",
		                  P_("Value Position"),
		                  P_("The position of the value display"),
		                  GTK_TYPE_POSITION_TYPE,
		                  GTK_POS_BOTTOM,
		                  GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_VALUE_XALIGN,
		g_param_spec_double("value-xalign",
		                    P_("Value Alignment"),
		                    P_("The horizontal position of the value (0..1)"),
		                    0, 1, 0.5,
		                    GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_DIGITS,
		g_param_spec_int("digits",
		                 P_("Digits"),
		                 P_("Number of digits for display"),
		                 0, 10, 1,
		                 GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
	g_object_class_override_property(gobject_class, PROP_VAR_ID, "var-id");

	binding_set = gtk_binding_set_by_class(klass);

	add_slider_binding (binding_set, GDK_KEY_Left, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_LEFT);

	add_slider_binding (binding_set, GDK_KEY_Left, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_LEFT);

	add_slider_binding (binding_set, GDK_KEY_KP_Left, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_LEFT);

	add_slider_binding (binding_set, GDK_KEY_KP_Left, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_LEFT);

	add_slider_binding (binding_set, GDK_KEY_Right, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_RIGHT);

	add_slider_binding (binding_set, GDK_KEY_Right, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_RIGHT);

	add_slider_binding (binding_set, GDK_KEY_KP_Right, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_RIGHT);

	add_slider_binding (binding_set, GDK_KEY_KP_Right, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_RIGHT);

	add_slider_binding (binding_set, GDK_KEY_Up, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_UP);

	add_slider_binding (binding_set, GDK_KEY_Up, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_UP);

	add_slider_binding (binding_set, GDK_KEY_KP_Up, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_UP);

	add_slider_binding (binding_set, GDK_KEY_KP_Up, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_UP);

	add_slider_binding (binding_set, GDK_KEY_Down, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_DOWN);

	add_slider_binding (binding_set, GDK_KEY_Down, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_DOWN);

	add_slider_binding (binding_set, GDK_KEY_KP_Down, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_DOWN);

	add_slider_binding (binding_set, GDK_KEY_KP_Down, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_DOWN);

	add_slider_binding (binding_set, GDK_KEY_Page_Up, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_LEFT);

	add_slider_binding (binding_set, GDK_KEY_KP_Page_Up, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_LEFT);

	add_slider_binding (binding_set, GDK_KEY_Page_Up, (GdkModifierType)0,
	                    GTK_SCROLL_PAGE_UP);

	add_slider_binding (binding_set, GDK_KEY_KP_Page_Up, (GdkModifierType)0,
	                    GTK_SCROLL_PAGE_UP);

	add_slider_binding (binding_set, GDK_KEY_Page_Down, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_RIGHT);

	add_slider_binding (binding_set, GDK_KEY_KP_Page_Down, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_RIGHT);

	add_slider_binding (binding_set, GDK_KEY_Page_Down, (GdkModifierType)0,
	                    GTK_SCROLL_PAGE_DOWN);

	add_slider_binding (binding_set, GDK_KEY_KP_Page_Down, (GdkModifierType)0,
	                    GTK_SCROLL_PAGE_DOWN);

	/* Logical bindings (vs. visual bindings above) */

	add_slider_binding (binding_set, GDK_KEY_plus, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_FORWARD);

	add_slider_binding (binding_set, GDK_KEY_minus, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_BACKWARD);

	add_slider_binding (binding_set, GDK_KEY_plus, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_FORWARD);

	add_slider_binding (binding_set, GDK_KEY_minus, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_BACKWARD);


	add_slider_binding (binding_set, GDK_KEY_KP_Add, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_FORWARD);

	add_slider_binding (binding_set, GDK_KEY_KP_Subtract, (GdkModifierType)0,
	                    GTK_SCROLL_STEP_BACKWARD);

	add_slider_binding (binding_set, GDK_KEY_KP_Add, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_FORWARD);

	add_slider_binding (binding_set, GDK_KEY_KP_Subtract, GDK_CONTROL_MASK,
	                    GTK_SCROLL_PAGE_BACKWARD);


	add_slider_binding (binding_set, GDK_KEY_Home, (GdkModifierType)0,
	                    GTK_SCROLL_START);

	add_slider_binding (binding_set, GDK_KEY_KP_Home, (GdkModifierType)0,
	                    GTK_SCROLL_START);

	add_slider_binding (binding_set, GDK_KEY_End, (GdkModifierType)0,
	                    GTK_SCROLL_END);

	add_slider_binding (binding_set, GDK_KEY_KP_End, (GdkModifierType)0,
	                    GTK_SCROLL_END);
}


static void gx_regler_destroy(GtkWidget *object)
{
	GxRegler *regler = GX_REGLER(object);
	if (regler->priv->label) {
		g_object_unref(regler->priv->label);
		regler->priv->label = NULL;
	}
	gx_regler_change_adjustment(regler, NULL);
	g_signal_handlers_disconnect_by_func(
		regler, (gpointer)gx_regler_adjustment_notified, NULL);
	GTK_WIDGET_CLASS(gx_regler_parent_class)->destroy(object);
}

static void gx_regler_finalize(GObject *object)
{
	GxRegler *regler = GX_REGLER(object);
	g_free(regler->priv->var_id);
	if (regler->priv->value_layout) {
		g_object_unref(regler->priv->value_layout);
	}
	G_OBJECT_CLASS(gx_regler_parent_class)->finalize(object);
}

static void step_back(GtkRange *range)
{
	gdouble newval;
	gboolean handled;

	GtkAdjustment *adjustment = gtk_range_get_adjustment(range);
	newval = gtk_adjustment_get_value(adjustment) - gtk_adjustment_get_step_increment(adjustment);
	g_signal_emit_by_name(range, "change-value", GTK_SCROLL_STEP_BACKWARD, newval, &handled);
}

static void step_forward(GtkRange *range)
{
	gdouble newval;
	gboolean handled;

	GtkAdjustment *adjustment = gtk_range_get_adjustment(range);
	newval = gtk_adjustment_get_value(adjustment) + gtk_adjustment_get_step_increment(adjustment);
	g_signal_emit_by_name(range, "change-value", GTK_SCROLL_STEP_FORWARD, newval, &handled);
}


static void page_back(GtkRange *range)
{
	gdouble newval;
	gboolean handled;

	GtkAdjustment *adjustment = gtk_range_get_adjustment(range);
	newval = gtk_adjustment_get_value(adjustment) - gtk_adjustment_get_page_increment(adjustment);
	g_signal_emit_by_name(range, "change-value", GTK_SCROLL_PAGE_BACKWARD, newval, &handled);
}

static void page_forward(GtkRange *range)
{
	gdouble newval;
	gboolean handled;

	GtkAdjustment *adjustment = gtk_range_get_adjustment(range);
	newval = gtk_adjustment_get_value(adjustment) + gtk_adjustment_get_page_increment(adjustment);
	g_signal_emit_by_name(range, "change-value", GTK_SCROLL_PAGE_FORWARD, newval, &handled);
}

static void scroll_begin(GtkRange *range)
{
	gboolean handled;
	g_signal_emit_by_name(range, "change-value", GTK_SCROLL_START,
	              gtk_adjustment_get_lower(gtk_range_get_adjustment(range)),
	              &handled);
}

static void scroll_end(GtkRange *range)
{
	gdouble newval;
	gboolean handled;

	GtkAdjustment *adjustment = gtk_range_get_adjustment(range);
	newval = gtk_adjustment_get_upper(adjustment) - gtk_adjustment_get_page_size(adjustment);
	g_signal_emit_by_name(range, "change-value", GTK_SCROLL_END, newval, &handled);
}

static gboolean should_invert(GtkRange *range)
{
	gboolean inverted = gtk_range_get_inverted(range);
	if (gtk_orientable_get_orientation(GTK_ORIENTABLE(range)) == GTK_ORIENTATION_HORIZONTAL) {
		gboolean flippable = gtk_range_get_flippable(range);
		return
			(inverted && !flippable) ||
			(inverted && flippable && gtk_widget_get_direction (GTK_WIDGET (range)) == GTK_TEXT_DIR_LTR) ||
			(!inverted && flippable && gtk_widget_get_direction (GTK_WIDGET (range)) == GTK_TEXT_DIR_RTL);
	} else {
		return inverted;
	}
}

static gboolean gx_regler_scroll(GtkRange *range, GtkScrollType scroll)
{
	gdouble old_value = gtk_adjustment_get_value(gtk_range_get_adjustment(range));

	switch (scroll) {
    case GTK_SCROLL_STEP_DOWN:
	case GTK_SCROLL_STEP_LEFT:
      if (should_invert (range))
        step_forward (range);
      else
        step_back (range);
      break;

    case GTK_SCROLL_STEP_UP:
    case GTK_SCROLL_STEP_RIGHT:
      if (should_invert (range))
        step_back (range);
      else
        step_forward (range);
      break;


    case GTK_SCROLL_STEP_BACKWARD:
      step_back (range);
      break;

    case GTK_SCROLL_STEP_FORWARD:
      step_forward (range);
      break;

    case GTK_SCROLL_PAGE_DOWN:
    case GTK_SCROLL_PAGE_LEFT:
      if (should_invert (range))
        page_forward (range);
      else
        page_back (range);
      break;

    case GTK_SCROLL_PAGE_UP:
    case GTK_SCROLL_PAGE_RIGHT:
      if (should_invert (range))
        page_back (range);
      else
        page_forward (range);
      break;

    case GTK_SCROLL_PAGE_BACKWARD:
      page_back (range);
      break;

    case GTK_SCROLL_PAGE_FORWARD:
      page_forward (range);
      break;

    case GTK_SCROLL_START:
      scroll_begin (range);
      break;

    case GTK_SCROLL_END:
      scroll_end (range);
      break;

    case GTK_SCROLL_JUMP:
    case GTK_SCROLL_NONE:
      break;
    }

    return gtk_adjustment_get_value(gtk_range_get_adjustment(range)) != old_value;
}

static void gx_regler_move_slider(GtkRange *range, GtkScrollType scroll)
{
	gboolean cursor_only;
	g_object_get(gtk_widget_get_settings(GTK_WIDGET(range)),
	             "gtk-keynav-cursor-only", &cursor_only,
	             NULL);
	if (cursor_only) {
		GtkWidget *toplevel = gtk_widget_get_toplevel(GTK_WIDGET(range));
		if (gtk_orientable_get_orientation(GTK_ORIENTABLE(range)) == GTK_ORIENTATION_HORIZONTAL) {
			if (scroll == GTK_SCROLL_STEP_UP || scroll == GTK_SCROLL_STEP_DOWN) {
				if (toplevel) {
					gtk_widget_child_focus(toplevel,
					                       scroll == GTK_SCROLL_STEP_UP ?
					                       GTK_DIR_UP : GTK_DIR_DOWN);
				}
				return;
			}
		} else {
			if (scroll == GTK_SCROLL_STEP_LEFT || scroll == GTK_SCROLL_STEP_RIGHT) {
				if (toplevel) {
					gtk_widget_child_focus(toplevel,
					                       scroll == GTK_SCROLL_STEP_LEFT ?
					                       GTK_DIR_LEFT : GTK_DIR_RIGHT);
				}
				return;
			}
		}
	}
	if (!gx_regler_scroll (range, scroll)) {
		gtk_widget_error_bell(GTK_WIDGET(range));
	}
}

static void ensure_digits(GxRegler *regler)
{
	GxReglerPrivate *priv = regler->priv;
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(regler));
	if (!adj) {
		return;
	}
	gdouble v = gtk_adjustment_get_step_increment(adj);
	if (v == priv->last_step) {
		return;
	}
	if (v == 0.0) {
		priv->last_step = 0.0;
		return;
	}
	gint n = 0;
	while (v < 1.0 - 1e-3) {
		v *= 10;
		n++;
	}
	gtk_range_set_round_digits(GTK_RANGE(regler), n);
}

static gboolean gx_regler_change_value(GtkRange *range, GtkScrollType scroll, gdouble value)
{
	g_assert(GX_IS_REGLER(range));
	ensure_digits(GX_REGLER(range));
	return GTK_RANGE_CLASS(gx_regler_parent_class)->change_value(range, scroll, value);
}

/****************************************************************
 ** calculate the knop pointer with dead zone
 */

/*
** when this function gets inlined (e.g. -O3) in GxKnob.c:_gx_knob_pointer_event
** bad things will happen, at least with g++ (Ubuntu 4.4.3-4ubuntu5) 4.4.3 (funny
** lockup in malloc semaphore after returning from first signal handler...)
** I'm don't know how to generate assembler output commented with original C code,
** without its rather unreadable, and anyhow I don't really want to debug the
** compiler. Inlining for this function can also be prevented with
**  __attribute__((noinline)) for the function definition in the header file. /ad
*/
gboolean _approx_in_rectangle(gdouble x, gdouble y, GdkRectangle *rect)
{
	const int off = 5;
	if (rect->width == 0 || rect->height == 0) {
		return FALSE;
	}
	else if (x >= rect->x-off && x < rect->x + rect->width + off &&
	    y >= rect->y-off && y < rect->y + rect->height + off) {
		return TRUE;
	}
	return FALSE;
}

static void gx_regler_ensure_layout(GxRegler *regler)
{
	if (regler->priv->show_value && !regler->priv->value_layout) {
		regler->priv->value_layout = gtk_widget_create_pango_layout(GTK_WIDGET(regler), NULL);
	}
}

#ifndef min
#define min(x, y) ((x) < (y) ? (x) : (y))
#endif
#ifndef max
#define max(x, y) ((x) < (y) ? (y) : (x))
#endif

gdouble _gx_regler_get_step_pos(GxRegler *regler, gint step)
{
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(regler));
	gdouble lower = gtk_adjustment_get_lower(adj);
	double df = gtk_adjustment_get_upper(adj) - lower;
	if (df == 0.0) {
		return 0.0;
	} else {
		return (gtk_adjustment_get_value(adj) - lower) * step / df;
	}
}

void _gx_regler_get_positions(GxRegler *regler, GdkRectangle *image_rect,
                              GdkRectangle *value_rect, gboolean hfill)
{
	GtkWidget *widget = GTK_WIDGET(regler);
	GtkStyleContext *style = gtk_widget_get_style_context(widget);
	GtkAllocation allocation;
	gtk_widget_get_allocation(widget, &allocation);
	gint x = 0;
	gint y = 0;
	gint width = 0;
	gint height =  0;
	if (image_rect) {
	    width = image_rect->width;
	    height = image_rect->height;
	}
	gboolean show_value;
	gtk_style_context_get_style(style, "show-value", &show_value, NULL);
	if (regler->priv->show_value && show_value) {
		GxReglerPrivate *priv = regler->priv;
		gint text_width = priv->value_req.width;
		gint text_height = priv->value_req.height;
		gint text_x = 0, text_y = 0;
		gint value_spacing;
		gtk_style_context_get_style(style, "value-spacing", &value_spacing, NULL);
		switch (priv->value_position) {
		case GTK_POS_LEFT:
			text_x = x + (allocation.width - width - text_width - value_spacing) / 2;
			text_y = y + (allocation.height - text_height) / 2;
			if (image_rect) {
			    image_rect->x = x + (allocation.width - width + text_width + value_spacing) / 2;
			    image_rect->y = y + (allocation.height - height) / 2;
			}
			break;
		case GTK_POS_RIGHT:
			text_x = x + value_spacing + (allocation.width + width - text_width - value_spacing) / 2;
			text_y = y + (allocation.height - text_height) / 2;
			if (image_rect) {
			    image_rect->x = x + (allocation.width - width - text_width - value_spacing) / 2;
			    image_rect->y = y + (allocation.height - height) / 2;
			}
			break;
		case GTK_POS_TOP:
			text_x = x + (allocation.width - text_width) / 2;
			text_y = y + (allocation.height - height - text_height - value_spacing) / 2;
			if (image_rect) {
			    image_rect->x = x + (allocation.width - width) / 2;
			    image_rect->y = y + (allocation.height - height + text_height + value_spacing) / 2;
			}
			break;
		case GTK_POS_BOTTOM:
			text_x = x + (allocation.width - text_width) / 2;
			text_y = y + value_spacing + (allocation.height + height - text_height - value_spacing) / 2;
			if (image_rect) {
			    image_rect->x = x + (allocation.width - width) / 2;
			    image_rect->y = y + (allocation.height - height - text_height - value_spacing) / 2;
			}
			break;
		}
		if (value_rect) {
		    if (hfill) {
			value_rect->x = 0;
			value_rect->width = allocation.width;
		    } else {
			value_rect->x = text_x;
			value_rect->width = text_width;
		    }
		    value_rect->y = text_y;
		    value_rect->height = text_height;
		}
	} else {
	    if (image_rect) {
		image_rect->x = x + (allocation.width - width) / 2;
		image_rect->y = y + (allocation.height - height) / 2;
	    }
		if (value_rect) {
			value_rect->x = value_rect->y = value_rect->width = value_rect->height = 0;
		}
	}
}

gboolean _gx_regler_check_display_popup(GxRegler *regler, GdkRectangle *image_rect,
					GdkRectangle *value_rect, GdkEventButton *event)
{
	// check if value entry popup requested
	gdouble x = event->x;
	gdouble y = event->y;
	GdkRectangle *rect = NULL;
	if (image_rect && _approx_in_rectangle(x, y, image_rect)) {
		if (event->button == 3) {
			rect = image_rect;
		}
	} else if (value_rect && _approx_in_rectangle(x, y, value_rect)) {
		if (event->button == 1 || event->button == 3) {
			rect = value_rect;
		} else {
			return TRUE;
		}
	} else {
		return TRUE;
	}
	if (rect) {
		gboolean ret;
		g_signal_emit_by_name(regler, "value-entry", rect, event, &ret);
		return TRUE;
	}
	return FALSE;
}

static gchar* _gx_regler_format_value(GxRegler *regler, gdouble value)
{
	gchar *fmt = NULL;
	g_signal_emit(regler, signals[FORMAT_VALUE], 0, value, &fmt);
	if (fmt) {
		return fmt;
	} else {
		int rd = gtk_range_get_round_digits(GTK_RANGE(regler));
		if (rd < 0) {
			rd = 0;
		}
		return g_strdup_printf ("%0.*f", rd, value);
	}
}


static const GtkBorder default_value_border = { 6, 6, 3, 3 };

static void get_value_border(GtkStyleContext *style, GtkBorder *value_border)
{
    GtkBorder *tmp_border;
    gtk_style_context_get_style(style, "value-border", &tmp_border, NULL);
    if (tmp_border) {
	*value_border = *tmp_border;
	gtk_border_free(tmp_border);
    } else {
	*value_border = default_value_border;
    }
}

void _gx_regler_simple_display_value(GxRegler *regler, cairo_t *cr, GdkRectangle *rect)
{
	if (!regler->priv->show_value) {
		return;
	}
	GtkStyleContext *style = gtk_widget_get_style_context(GTK_WIDGET(regler));
	gboolean show_value;
	gtk_style_context_get_style(style, "show-value", &show_value, NULL);
	if (!show_value) {
		return;
	}
    GtkAdjustment* adjustment = gtk_range_get_adjustment(GTK_RANGE(regler));
    PangoLayout *l = regler->priv->value_layout;
    PangoRectangle logical_rect;
	gchar *txt;
	ensure_digits(regler);
	txt = _gx_regler_format_value(regler, gtk_adjustment_get_value(adjustment));
    pango_layout_set_text(l, txt, -1);
    g_free (txt);
    pango_layout_get_pixel_extents(l, NULL, &logical_rect);
    GtkBorder border;
    get_value_border(style, &border);
    gtk_render_layout(style, cr,
                      rect->x + (rect->width - logical_rect.width + border.left - border.right) / 2,
                      rect->y + border.top, regler->priv->value_layout);
}

#define DISPLAY_BORDER_SIZE 2

void _gx_regler_display_value(GxRegler *regler, cairo_t *cr, GdkRectangle *rect)
{
	if (!regler->priv->show_value) {
		return;
	}
	gboolean show_value;
    GtkWidget * widget = GTK_WIDGET(regler);
	GtkStyleContext *style = gtk_widget_get_style_context(widget);
	GtkStateFlags state_flags = gtk_widget_get_state_flags(widget);
	gtk_style_context_get_style(style, "show-value", &show_value, NULL);
	if (!show_value) {
		return;
	}
	double x0 = rect->x + DISPLAY_BORDER_SIZE;
	double y0 = rect->y + DISPLAY_BORDER_SIZE;
	double w  = rect->width - 2 * DISPLAY_BORDER_SIZE;
	double h  = rect->height - 2 * DISPLAY_BORDER_SIZE;
    gint rad;
    GtkStyleContext *sc = gtk_widget_get_style_context(widget);
    gtk_widget_style_get(widget, "border-radius", &rad, NULL);

    gx_draw_inset(cr, x0, y0, w, h, rad, DISPLAY_BORDER_SIZE);
    gtk_render_background(sc, cr, x0, y0, w, h);
    gx_draw_glass(cr, x0, y0, w, h, rad);

	gchar *txt;
	ensure_digits(regler);
	txt = _gx_regler_format_value(regler, gtk_adjustment_get_value(gtk_range_get_adjustment(GTK_RANGE(regler))));
    GdkRGBA color;
    gtk_style_context_get_color(style, state_flags, &color);
    cairo_set_source_rgba(cr, color.red, color.green, color.blue, color.alpha);

    PangoLayout *l = regler->priv->value_layout;
    pango_layout_set_text(l, txt, -1);
    g_free(txt);
    PangoRectangle logical_rect;
    pango_layout_get_pixel_extents(l, NULL, &logical_rect);
    GtkBorder border;
    get_value_border(style, &border);
    gdouble off = border.left + regler->priv->value_xalign *
		(w - logical_rect.width - (border.left + border.right));
    cairo_move_to(cr, x0+off, y0+border.top);
    pango_cairo_show_layout(cr, l);
}

/*
 * _gx_regler_calc_size_request()
 * calculate size of value display and add it to *out_width and *out_height
 *
 * setting of with_border when using
 *   _gx_regler_simple_display_value: false
 *   _gx_regler_display_value():      true
 *
 * value-spacing shifts the displayed value (padding between regler and value display)
 * to make acts as padding around the displayed value between border
 *
 * value-border is the padding around the displayed value (and inside the border when with_border is set)
 */
void _gx_regler_calc_size_request(GxRegler *regler, gint *out_width, gint *out_height, gboolean with_border)
{
	if (!regler->priv->show_value) {
		return;
	}
	GtkStyleContext *style = gtk_widget_get_style_context(GTK_WIDGET(regler));
	gboolean show_value;
	gtk_style_context_get_style(style, "show-value", &show_value, NULL);
	if (!show_value) {
		return;
	}
	gx_regler_ensure_layout(regler);
	PangoRectangle logical_rect1, logical_rect2;
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(regler));
	gchar *txt;
	ensure_digits(regler);
	txt = _gx_regler_format_value(regler, gtk_adjustment_get_lower(adj));
	pango_layout_set_text(regler->priv->value_layout, txt, -1);
	g_free(txt);
	pango_layout_get_pixel_extents(regler->priv->value_layout, NULL, &logical_rect1);
	txt = _gx_regler_format_value(regler, gtk_adjustment_get_upper(adj));
	pango_layout_set_text(regler->priv->value_layout, txt, -1);
	g_free(txt);
	pango_layout_get_pixel_extents(regler->priv->value_layout, NULL, &logical_rect2);
	GtkBorder border;
	get_value_border(style, &border);
	gint height = max(logical_rect1.height,logical_rect2.height)
	    + border.top + border.bottom + 2 * DISPLAY_BORDER_SIZE;
	gint width = max(logical_rect1.width,logical_rect2.width)
	    + border.left + border.right + 2 * DISPLAY_BORDER_SIZE;
	GxReglerPrivate *priv = regler->priv;
	priv->value_req.width = width;
	priv->value_req.height = height;
	gint value_spacing;
	gtk_style_context_get_style(style, "value-spacing", &value_spacing, NULL);
	switch (regler->priv->value_position) {
	case GTK_POS_LEFT:
	case GTK_POS_RIGHT:
		*out_width += width + value_spacing;
		if (height > *out_height) {
			*out_height = height;
		}
		break;
	case GTK_POS_TOP:
	case GTK_POS_BOTTOM:
		*out_height += height + value_spacing;
		if (width > *out_width) {
			*out_width = width;
		}
		break;
	}
}

/****************************************************************
 ** set value from key bindings
 */

static void gx_regler_set_value (GtkWidget *widget, GdkScrollDirection dir_down)
{
	g_assert(GX_IS_REGLER(widget));

	if (dir_down != GDK_SCROLL_DOWN && dir_down != GDK_SCROLL_UP) {
		return;
	}
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	gdouble adj_value = gtk_adjustment_get_value(adj);
	gdouble lower = gtk_adjustment_get_lower(adj);
	gdouble upper = gtk_adjustment_get_upper(adj);
	gdouble step_increment = gtk_adjustment_get_step_increment(adj);

	int oldstep = (int)(0.5f + (adj_value - lower) / step_increment);
	int step;
	int nsteps = (int)(0.5f + (upper - lower) / step_increment);
	if (dir_down == GDK_SCROLL_DOWN)
		step = oldstep - 1;
	else
		step = oldstep + 1;
	gdouble value = lower + step * (upper - lower) / nsteps;
	gtk_widget_grab_focus(widget);
	gtk_range_set_value(GTK_RANGE(widget), value);
}

/****************************************************************
 ** mouse button pressed set value
 */

static gboolean spinner_button_press_event(
	GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	if (event->button == 3) {
		return TRUE;
	}
	if (event->type == GDK_2BUTTON_PRESS) {
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
	if (event->keyval == GDK_KEY_Escape) {
		// spinbutton to current adjustment value
		g_signal_emit_by_name(gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(widget)),
							  "value-changed");
		gtk_widget_destroy(GTK_WIDGET(data));
		return TRUE;
	}
	return FALSE;
}

static void gx_regler_relay_value(GtkAdjustment *src, GtkAdjustment *dst) {
	gtk_adjustment_set_value(dst, gtk_adjustment_get_value(src));
}

static gint gx_regler_spinner_input(GtkSpinButton *spin_button, gdouble *new_val, GxRegler *regler)
{
	gint ret;
	g_signal_emit(regler, signals[INPUT_VALUE], 0, spin_button, new_val, &ret);
	return ret;
}

static gboolean gx_regler_spinner_output(GtkSpinButton *spinner, GxRegler *regler) {
	gchar *fmt;
	gdouble value = gtk_adjustment_get_value(gtk_spin_button_get_adjustment(spinner));
	fmt = _gx_regler_format_value(regler, value);
	gtk_entry_set_text (GTK_ENTRY(spinner), fmt);
	g_free(fmt);
    return TRUE;
}

static int gx_regler_get_nchars(GxRegler *regler, gdouble value)
{
    gchar *txt = _gx_regler_format_value(regler, value);
    int nchars = strlen(txt);
    g_free(txt);
    return nchars;
}

static gboolean gx_regler_value_entry(GxRegler *regler, GdkRectangle *rect, GdkEventButton *event)
{
	if (event->type == GDK_2BUTTON_PRESS || event->type == GDK_3BUTTON_PRESS) {
		return FALSE;
	}
	g_assert(GX_IS_REGLER(regler));
	GtkAdjustment *dst_adj = gtk_range_get_adjustment(GTK_RANGE(regler));
	GtkWidget *popover = gtk_popover_new(GTK_WIDGET(regler));
	gtk_widget_add_events(popover, GDK_BUTTON_PRESS_MASK|GDK_BUTTON_MOTION_MASK);
	ensure_digits(regler);
    gdouble lower = gtk_adjustment_get_lower(dst_adj);
    gdouble upper = gtk_adjustment_get_upper(dst_adj);
	GtkAdjustment *src_adj = GTK_ADJUSTMENT(
		gtk_adjustment_new(
			gtk_adjustment_get_value(dst_adj), lower, upper,
			gtk_adjustment_get_step_increment(dst_adj),
			gtk_adjustment_get_page_increment(dst_adj),
			gtk_adjustment_get_page_size(dst_adj)));
	GtkWidget *spinner = gtk_spin_button_new(
		src_adj, gtk_adjustment_get_step_increment(src_adj), 0);
    gtk_entry_set_width_chars(GTK_ENTRY(spinner), max(gx_regler_get_nchars(regler, lower),
                                                      gx_regler_get_nchars(regler, upper)));
	g_signal_connect(spinner, "output", G_CALLBACK(gx_regler_spinner_output), regler);
	g_signal_connect(spinner, "input", G_CALLBACK(gx_regler_spinner_input), regler);
	g_signal_connect(src_adj, "value-changed", G_CALLBACK(gx_regler_relay_value), dst_adj);
	gtk_container_add(GTK_CONTAINER(popover), spinner);

	g_signal_connect(spinner, "button-press-event", G_CALLBACK(spinner_button_press_event), NULL);
	g_signal_connect(spinner, "key-press-event", G_CALLBACK(dialog_key_press_before), popover);
	g_signal_connect_after(spinner, "key-press-event", G_CALLBACK(dialog_key_press_event), popover);
	g_signal_connect_object(spinner, "activate", G_CALLBACK(gtk_widget_destroy),
				popover, (GConnectFlags)(G_CONNECT_AFTER|G_CONNECT_SWAPPED));

	gtk_widget_show(spinner);
	gtk_widget_realize(popover);
	gtk_popover_set_pointing_to(GTK_POPOVER(popover), rect);

	gtk_widget_show(popover);
	return FALSE;
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

	GdkScrollDirection direction;
	gdouble delta_x, delta_y;
	if (event->direction != GDK_SCROLL_SMOOTH) {
		gx_regler_set_value(widget, event->direction);
	} else if (gdk_event_get_scroll_direction((GdkEvent*)event, &direction)) {
		gx_regler_set_value(widget, direction);
	} else if (gdk_event_get_scroll_deltas((GdkEvent*)event, &delta_x, &delta_y)) {
		GdkScrollDirection vdir = delta_y > 0.0 ? GDK_SCROLL_UP : GDK_SCROLL_DOWN;
		if (abs(delta_y) > abs(delta_x)) {
			gx_regler_set_value(widget, vdir);
		}
	}

	return TRUE;
}

/****************************************************************
 ** init the Regler type/size
 */

static void gx_regler_adjustment_changed(GtkAdjustment *adjustment, gpointer data)
{
	gtk_widget_queue_resize(GTK_WIDGET(data));
}

static void gx_regler_change_adjustment(GxRegler *regler, GtkAdjustment *adjustment)
{
	GxReglerPrivate *priv = regler->priv;
	if (adjustment == priv->adjustment) {
		return;
	}
	if (priv->adjustment) {
      g_signal_handlers_disconnect_by_func(
	      priv->adjustment, (gpointer)gx_regler_adjustment_changed, regler);
      g_object_unref(priv->adjustment);
      priv->adjustment = NULL;
	}
	if (!adjustment) {
		return;
	}
	priv->adjustment = adjustment;
	g_object_ref_sink(adjustment);
	g_signal_connect(adjustment, "changed", G_CALLBACK(gx_regler_adjustment_changed), regler);
	gtk_widget_queue_resize(GTK_WIDGET(regler));
}

static void gx_regler_adjustment_notified(GObject *gobject, GParamSpec *pspec)
{
	GxRegler *regler = GX_REGLER(gobject);
	gx_regler_change_adjustment(regler, gtk_range_get_adjustment(&regler->parent));
}

static void gx_regler_init(GxRegler *regler)
{
	regler->priv = (GxReglerPrivate*)gx_regler_get_instance_private(regler);
	gtk_range_set_round_digits(GTK_RANGE(regler), -1);
	regler->priv->value_position = GTK_POS_BOTTOM;
	regler->priv->show_value = TRUE;
	regler->priv->value_xalign = 0.5;
	gtk_widget_set_can_focus(GTK_WIDGET(regler), TRUE);
	gtk_widget_set_receives_default(GTK_WIDGET(regler), TRUE);
	gtk_widget_set_has_window(GTK_WIDGET(regler), FALSE);
	g_signal_connect(regler, "notify::adjustment", G_CALLBACK(gx_regler_adjustment_notified), NULL);
}

/****************************************************************
 ** Properties
 */

static void gx_regler_set_var_id(GxRegler *regler, const gchar *str)
{
	g_free(regler->priv->var_id);
	regler->priv->var_id = g_strdup(str ? str : "");
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
	case PROP_VALUE_XALIGN:
		regler->priv->value_xalign = g_value_get_double(value);
		gtk_widget_queue_draw(GTK_WIDGET(object));
		g_object_notify(object, "value-xalign");
		break;
	case PROP_LABEL_REF:
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
		g_value_set_string (value, regler->priv->var_id);
		break;
	case PROP_SHOW_VALUE:
		g_value_set_boolean(value, regler->priv->show_value);
		break;
	case PROP_VALUE_POSITION:
		g_value_set_enum(value, regler->priv->value_position);
		break;
	case PROP_VALUE_XALIGN:
		g_value_set_double(value, regler->priv->value_xalign);
		break;
	case PROP_LABEL_REF:
		g_value_set_object(value, regler->priv->label);
		break;
	case PROP_DIGITS:
		g_value_set_int(value, gtk_range_get_round_digits(GTK_RANGE(object)));
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
	regler->priv->show_value = value;
	gtk_widget_queue_resize(GTK_WIDGET(regler));
	g_object_notify(G_OBJECT(regler), "show-value");
}

gboolean gx_regler_get_show_value(GxRegler *regler)
{
	g_return_val_if_fail(GX_IS_REGLER(regler), 0);
	return regler->priv->show_value;
}

void gx_regler_set_value_position(GxRegler *regler, GtkPositionType value)
{
	g_return_if_fail(GX_IS_REGLER(regler));
	regler->priv->value_position = value;
	gtk_widget_queue_resize(GTK_WIDGET(regler));
	g_object_notify(G_OBJECT(regler), "value-position");
}

GtkPositionType gx_regler_get_value_position(GxRegler *regler)
{
	g_return_val_if_fail(GX_IS_REGLER(regler), GTK_POS_BOTTOM);
	return regler->priv->value_position;
}

void gx_regler_set_label_ref(GxRegler *regler, GtkLabel *label)
{
	g_return_if_fail(GX_IS_REGLER(regler));
	if (regler->priv->label) {
		g_object_unref(regler->priv->label);
		regler->priv->label = NULL;
	}
	if (label) {
		g_return_if_fail(GTK_IS_LABEL(label));
		regler->priv->label = label;
		g_object_ref(label);
	}
	g_object_notify(G_OBJECT(regler), "label-ref");
}


GtkLabel *gx_regler_get_label_ref(GxRegler *regler)
{
	g_return_val_if_fail(GX_IS_REGLER(regler), 0);
	return regler->priv->label;
}

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

#define gtk_widget_get_requisition(w, r) (*r = (w)->requisition)

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
	GtkAdjustment *adjustment;
} GxReglerPrivate;

enum {
  VALUE_ENTRY,
  FORMAT_VALUE,
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
static gboolean gx_regler_value_entry(GxRegler *regler, GdkRectangle *rect, GdkEventButton *event);
static void gx_regler_change_adjustment(GxRegler *regler, GtkAdjustment *adjustment);
static void gx_regler_adjustment_notified(GObject *gobject, GParamSpec *pspec);
static void gx_regler_move_slider(GtkRange *range, GtkScrollType scroll);

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
	g_return_if_fail(GX_IS_REGLER(self));
	GxRegler *regler = GX_REGLER(self);
	if (regler->label) {
		gtk_label_set_text(regler->label, name);
	}
	GtkRange *range = GTK_RANGE(self);
	gtk_range_set_range(range, lower, upper);
	gtk_range_set_increments(range, step, 0);
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

/*
** marshalers generated with
** echo -e 'STRING:DOUBLE\nBOOLEAN:BOXED,BOXED' | \
**   glib-genmarshal --prefix='marshal' --skip-source --nostdinc --body
**
** manually added static to funktion definitions
** this should be put into a separate source/header file when
** definitions are used at other places
*/
// begin generated marshalers
#ifdef G_ENABLE_DEBUG
#define g_marshal_value_peek_boolean(v)  g_value_get_boolean (v)
#define g_marshal_value_peek_char(v)     g_value_get_char (v)
#define g_marshal_value_peek_uchar(v)    g_value_get_uchar (v)
#define g_marshal_value_peek_int(v)      g_value_get_int (v)
#define g_marshal_value_peek_uint(v)     g_value_get_uint (v)
#define g_marshal_value_peek_long(v)     g_value_get_long (v)
#define g_marshal_value_peek_ulong(v)    g_value_get_ulong (v)
#define g_marshal_value_peek_int64(v)    g_value_get_int64 (v)
#define g_marshal_value_peek_uint64(v)   g_value_get_uint64 (v)
#define g_marshal_value_peek_enum(v)     g_value_get_enum (v)
#define g_marshal_value_peek_flags(v)    g_value_get_flags (v)
#define g_marshal_value_peek_float(v)    g_value_get_float (v)
#define g_marshal_value_peek_double(v)   g_value_get_double (v)
#define g_marshal_value_peek_string(v)   (char*) g_value_get_string (v)
#define g_marshal_value_peek_param(v)    g_value_get_param (v)
#define g_marshal_value_peek_boxed(v)    g_value_get_boxed (v)
#define g_marshal_value_peek_pointer(v)  g_value_get_pointer (v)
#define g_marshal_value_peek_object(v)   g_value_get_object (v)
#else /* !G_ENABLE_DEBUG */
/* WARNING: This code accesses GValues directly, which is UNSUPPORTED API.
 *          Do not access GValues directly in your code. Instead, use the
 *          g_value_get_*() functions
 */
#define g_marshal_value_peek_boolean(v)  (v)->data[0].v_int
#define g_marshal_value_peek_char(v)     (v)->data[0].v_int
#define g_marshal_value_peek_uchar(v)    (v)->data[0].v_uint
#define g_marshal_value_peek_int(v)      (v)->data[0].v_int
#define g_marshal_value_peek_uint(v)     (v)->data[0].v_uint
#define g_marshal_value_peek_long(v)     (v)->data[0].v_long
#define g_marshal_value_peek_ulong(v)    (v)->data[0].v_ulong
#define g_marshal_value_peek_int64(v)    (v)->data[0].v_int64
#define g_marshal_value_peek_uint64(v)   (v)->data[0].v_uint64
#define g_marshal_value_peek_enum(v)     (v)->data[0].v_long
#define g_marshal_value_peek_flags(v)    (v)->data[0].v_ulong
#define g_marshal_value_peek_float(v)    (v)->data[0].v_float
#define g_marshal_value_peek_double(v)   (v)->data[0].v_double
#define g_marshal_value_peek_string(v)   (v)->data[0].v_pointer
#define g_marshal_value_peek_param(v)    (v)->data[0].v_pointer
#define g_marshal_value_peek_boxed(v)    (v)->data[0].v_pointer
#define g_marshal_value_peek_pointer(v)  (v)->data[0].v_pointer
#define g_marshal_value_peek_object(v)   (v)->data[0].v_pointer
#endif /* !G_ENABLE_DEBUG */


/* STRING:DOUBLE */
void
marshal_STRING__DOUBLE (GClosure     *closure,
                        GValue       *return_value G_GNUC_UNUSED,
                        guint         n_param_values,
                        const GValue *param_values,
                        gpointer      invocation_hint G_GNUC_UNUSED,
                        gpointer      marshal_data)
{
  typedef gchar* (*GMarshalFunc_STRING__DOUBLE) (gpointer     data1,
                                                 gdouble      arg_1,
                                                 gpointer     data2);
  register GMarshalFunc_STRING__DOUBLE callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gchar* v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 2);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_STRING__DOUBLE) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_double (param_values + 1),
                       data2);

  g_value_take_string (return_value, v_return);
}

/* BOOLEAN:BOXED,BOXED */
void
marshal_BOOLEAN__BOXED_BOXED (GClosure     *closure,
                              GValue       *return_value G_GNUC_UNUSED,
                              guint         n_param_values,
                              const GValue *param_values,
                              gpointer      invocation_hint G_GNUC_UNUSED,
                              gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__BOXED_BOXED) (gpointer     data1,
                                                         gpointer     arg_1,
                                                         gpointer     arg_2,
                                                         gpointer     data2);
  register GMarshalFunc_BOOLEAN__BOXED_BOXED callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__BOXED_BOXED) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_boxed (param_values + 1),
                       g_marshal_value_peek_boxed (param_values + 2),
                       data2);

  g_value_set_boolean (return_value, v_return);
}
// end generated marshalers


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
	range_class->move_slider = gx_regler_move_slider;

	klass->value_entry = gx_regler_value_entry;

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

	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("value-spacing",P_("Value spacing"),
		                 P_("Distance of value display"),
		                 0, 100, 5, GParamFlags(GTK_PARAM_READABLE)));
	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_boxed("value-border",
		                   P_("Value Spacing"),
		                   P_("Extra space for value display"),
		                   GTK_TYPE_BORDER,
		                   GParamFlags(GTK_PARAM_READABLE)));

	g_object_class_install_property(
		gobject_class, PROP_SHOW_VALUE,
		g_param_spec_boolean("show-value",
		                     P_("show value"),
		                     P_("display the value"),
		                     TRUE,
		                     GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property(
		gobject_class, PROP_LABEL_REF,
		g_param_spec_object("label-ref",
		                    P_("Label ref"),
		                    P_("GtkLabel for caption"),
		                    GTK_TYPE_LABEL,
		                    GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property(
		gobject_class, PROP_VALUE_POSITION,
		g_param_spec_enum("value-position",
		                  P_("Value Position"),
		                  P_("The position of the value display"),
		                  GTK_TYPE_POSITION_TYPE,
		                  GTK_POS_BOTTOM,
		                  GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property(
		gobject_class, PROP_VALUE_XALIGN,
		g_param_spec_double("value-xalign",
		                    P_("Value Alignment"),
		                    P_("The horizontal position of the value (0..1)"),
		                    0, 1, 0.5,
		                    GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property(
		gobject_class, PROP_DIGITS,
		g_param_spec_int("digits",
		                 P_("Digits"),
		                 P_("Number of digits for display"),
		                 0, 10, 1,
		                 GParamFlags(GTK_PARAM_READABLE)));
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

gboolean gx_get_arch()
{
	char os[32];
	sprintf(os, "%i", LONG_BIT);
	if(strcmp(os,"32")!=0) return true;
	return false;
}

static void gx_regler_destroy(GtkObject *object)
{
	GxRegler *regler = GX_REGLER(object);
	if (regler->label) {
		g_object_unref(regler->label);
		regler->label = 0;
	}
	gx_regler_change_adjustment(regler, NULL);
	g_signal_handlers_disconnect_by_func(
		regler, (gpointer)gx_regler_adjustment_notified, NULL);
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

static void step_back(GtkRange *range)
{
	gdouble newval;
	gboolean handled;

	newval = range->adjustment->value - range->adjustment->step_increment;
	g_signal_emit_by_name(range, "change-value", GTK_SCROLL_STEP_BACKWARD, newval, &handled);
}

static void step_forward(GtkRange *range)
{
	gdouble newval;
	gboolean handled;

	newval = range->adjustment->value + range->adjustment->step_increment;
	g_signal_emit_by_name(range, "change-value", GTK_SCROLL_STEP_FORWARD, newval, &handled);
}


static void page_back(GtkRange *range)
{
	gdouble newval;
	gboolean handled;

	newval = range->adjustment->value - range->adjustment->page_increment;
	g_signal_emit_by_name(range, "change-value", GTK_SCROLL_PAGE_BACKWARD, newval, &handled);
}

static void page_forward(GtkRange *range)
{
	gdouble newval;
	gboolean handled;

	newval = range->adjustment->value + range->adjustment->page_increment;
	g_signal_emit_by_name(range, "change-value", GTK_SCROLL_PAGE_FORWARD, newval, &handled);
}

static void scroll_begin(GtkRange *range)
{
	gboolean handled;
	g_signal_emit_by_name(range, "change-value", GTK_SCROLL_START, range->adjustment->lower,
	              &handled);
}

static void scroll_end(GtkRange *range)
{
	gdouble newval;
	gboolean handled;

	newval = range->adjustment->upper - range->adjustment->page_size;
	g_signal_emit_by_name(range, "change-value", GTK_SCROLL_END, newval, &handled);
}

static gboolean should_invert(GtkRange *range)
{
	if (range->orientation == GTK_ORIENTATION_HORIZONTAL) {
		return
			(range->inverted && !range->flippable) ||
			(range->inverted && range->flippable && gtk_widget_get_direction (GTK_WIDGET (range)) == GTK_TEXT_DIR_LTR) ||
			(!range->inverted && range->flippable && gtk_widget_get_direction (GTK_WIDGET (range)) == GTK_TEXT_DIR_RTL);
	} else {
		return range->inverted;
	}
}

static gboolean gx_regler_scroll(GtkRange *range, GtkScrollType scroll)
{
	gdouble old_value = range->adjustment->value;

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

  return range->adjustment->value != old_value;
}

static void gx_regler_move_slider(GtkRange *range, GtkScrollType scroll)
{
	gboolean cursor_only;
	g_object_get(gtk_widget_get_settings(GTK_WIDGET(range)),
	             "gtk-keynav-cursor-only", &cursor_only,
	             NULL);
	if (cursor_only) {
		GtkWidget *toplevel = gtk_widget_get_toplevel(GTK_WIDGET(range));
		if (range->orientation == GTK_ORIENTATION_HORIZONTAL) {
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
	GxReglerPrivate *priv = GX_REGLER_GET_PRIVATE(regler);
	GtkAdjustment *adj = GTK_RANGE(regler)->adjustment;
	if (!adj) {
		return;
	}
	gdouble v = adj->step_increment;
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
	GTK_RANGE(regler)->round_digits = n;
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
	if (regler->show_value && !regler->value_layout) {
		regler->value_layout = gtk_widget_create_pango_layout(GTK_WIDGET(regler), NULL);
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
		gint text_x = 0, text_y = 0;
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

static gchar* _gx_regler_format_value(GxRegler *regler, gdouble value)
{
	gchar *fmt = NULL;
	g_signal_emit(regler, signals[FORMAT_VALUE], 0, value, &fmt);
	if (fmt) {
		return fmt;
	} else {
		/* insert a LRM, to prevent -20 to come out as 20- in RTL locales */
		return g_strdup_printf ("\342\200\216%0.*f", GTK_RANGE(regler)->round_digits, value);
	}
}

void _gx_regler_simple_display_value(GxRegler *regler, GdkRectangle *rect)
{
	if (!regler->show_value) {
		return;
	}
    GtkWidget *widget = GTK_WIDGET(regler);
    PangoLayout *l = regler->value_layout;
    PangoRectangle logical_rect;
	gchar *txt;
	ensure_digits(regler);
	txt = _gx_regler_format_value(regler, GTK_RANGE(regler)->adjustment->value);
    pango_layout_set_text(l, txt, -1);
    g_free (txt);
    pango_layout_get_pixel_extents(l, NULL, &logical_rect);
    gtk_paint_layout(widget->style, widget->window, gtk_widget_get_state(widget),
                     FALSE, rect, widget, "label", rect->x+(rect->width - logical_rect.width)/2,
                     rect->y, regler->value_layout);
}

void _gx_regler_display_value(GxRegler *regler, GdkRectangle *rect)
{
	if (!regler->show_value) {
		return;
	}
	cairo_t *cr = gdk_cairo_create(GTK_WIDGET(regler)->window);
	double x0 = rect->x + 1;
	double y0 = rect->y + 1;
	double rect_width  =  rect->width - 2;
	double rect_height =  rect->height - 2;
	gint border_width = 8;

    cairo_rectangle (cr, x0-1,y0-1,rect_width+2,rect_height+2);
    cairo_set_source_rgba(cr, 0, 0, 0, 0.4);
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

	gchar *txt;
	ensure_digits(regler);
	txt = _gx_regler_format_value(regler, GTK_RANGE(regler)->adjustment->value);
    cairo_set_source_rgba (cr, 0.4, 1, 0.2, 0.8);
    PangoLayout *l = regler->value_layout;
    pango_layout_set_text(l, txt, -1);
    g_free(txt);
    PangoRectangle logical_rect;
    pango_layout_get_pixel_extents(l, NULL, &logical_rect);
    gdouble off = border_width + (rect->width - 2*border_width
                                  - logical_rect.width) * regler->value_xalign;
    cairo_move_to(cr, x0-1+off, y0+3);
    pango_cairo_show_layout(cr, l);

	cairo_destroy(cr);
}

static const GtkBorder default_value_border = { 6, 6, 3, 3 };

static void get_value_border(GtkWidget *widget, GtkBorder *value_border)
{
	GtkBorder *tmp_border;

	gtk_widget_style_get(widget, "value-border", &tmp_border, NULL);
	if (tmp_border) {
		*value_border = *tmp_border;
		gtk_border_free(tmp_border);
	} else {
		*value_border = default_value_border;
    }
}

void _gx_regler_calc_size_request(GxRegler *regler, GtkRequisition *requisition)
{
	gx_regler_ensure_layout(regler);
	if (regler->show_value) {
		PangoRectangle logical_rect1, logical_rect2;
		GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(regler));
		gint value_spacing;
		ensure_digits(regler);
		GtkBorder border;
		get_value_border(GTK_WIDGET(regler), &border);
		gtk_widget_style_get(GTK_WIDGET(regler), "value-spacing", &value_spacing, NULL);
		gchar *txt;
		ensure_digits(regler);
		txt = _gx_regler_format_value(regler, gtk_adjustment_get_lower(adj));
		pango_layout_set_text(regler->value_layout, txt, -1);
		g_free(txt);
		pango_layout_get_pixel_extents(regler->value_layout, NULL, &logical_rect1);
		txt = _gx_regler_format_value(regler, gtk_adjustment_get_upper(adj));
		pango_layout_set_text(regler->value_layout, txt, -1);
		g_free(txt);
		pango_layout_get_pixel_extents(regler->value_layout, NULL, &logical_rect2);
		gint height = max(logical_rect1.height,logical_rect2.height) + border.top + border.bottom;
		gint width = max(logical_rect1.width,logical_rect2.width) + border.left + border.right;
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
	if (GTK_IS_WIDGET(data));
		gtk_widget_destroy(GTK_WIDGET(data));
	return FALSE;
}

static gboolean dialog_key_press_before(
	GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	if (event->keyval == GDK_Escape) {
		// spinbutton to current adjustment value
		gtk_adjustment_value_changed(GTK_SPIN_BUTTON(widget)->adjustment);
		if (GTK_IS_WIDGET(data));
			gtk_widget_destroy(GTK_WIDGET(data));
		return TRUE;
	}
	return FALSE;
}

static gboolean dialog_grab_broken(
	GtkWidget *widget, GdkEvent *event, gpointer data)
{
	if (GTK_IS_WIDGET(data));
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

static gboolean gx_regler_value_entry(GxRegler *regler, GdkRectangle *rect, GdkEventButton *event)
{
	if(OS_IS_64_BIT) return TRUE;
	g_assert(GX_IS_REGLER(regler));
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(regler));
	GtkWidget *dialog = gtk_window_new(GTK_WINDOW_POPUP);
	gtk_widget_add_events(dialog, GDK_BUTTON_PRESS_MASK|GDK_BUTTON_MOTION_MASK);
	ensure_digits(regler);
	GtkWidget *spinner = gtk_spin_button_new(
		GTK_ADJUSTMENT(adj), adj->step_increment,
		GTK_RANGE(regler)->round_digits);
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
	
	gx_regler_set_value(widget, event->direction);
	
	return TRUE;
}


static void gx_regler_style_set(GtkWidget *widget, GtkStyle  *previous_style)
{
	//FIXME: value_req need recalc
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
	GxReglerPrivate *priv = GX_REGLER_GET_PRIVATE(regler);
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
	gx_regler_change_adjustment(regler, regler->parent.adjustment);
}

static void gx_regler_init(GxRegler *regler)
{
	GTK_RANGE(regler)->round_digits = 0;
	regler->value_position = GTK_POS_BOTTOM;
	regler->show_value = TRUE;
	regler->value_xalign = 0.5;
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
	case PROP_VALUE_XALIGN:
		regler->value_xalign = g_value_get_double(value);
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
		g_value_set_string (value, regler->var_id);
		break;
	case PROP_SHOW_VALUE:
		g_value_set_boolean(value, regler->show_value);
		break;
	case PROP_VALUE_POSITION:
		g_value_set_enum(value, regler->value_position);
		break;
	case PROP_VALUE_XALIGN:
		g_value_set_double(value, regler->value_xalign);
		break;
	case PROP_LABEL_REF:
		g_value_set_object(value, regler->label);
		break;
	case PROP_DIGITS:
		g_value_set_int(value, GTK_RANGE(object)->round_digits);
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
	if (regler->label) {
		g_object_unref(regler->label);
		regler->label = 0;
	}
	if (label) {
		g_return_if_fail(GTK_IS_LABEL(label));
		regler->label = label;
		g_object_ref(label);
	}
	g_object_notify(G_OBJECT(regler), "label-ref");
}


GtkLabel *gx_regler_get_label_ref(GxRegler *regler)
{
	g_return_val_if_fail(GX_IS_REGLER(regler), 0);
	return regler->label;
}

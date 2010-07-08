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

#include "GxSelector.h"
#include <gtk/gtk.h>
#include <gtk/gtkprivate.h>

#define P_(s) (s)   // FIXME -> gettext

/****************************************************************
 ** GxSelector
 */

enum {
	PROP_MODEL = 1,
};

static gboolean gx_selector_enter_in (GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_selector_leave_out (GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_selector_expose (GtkWidget *widget, GdkEventExpose *event);
static void gx_selector_size_request (GtkWidget *widget, GtkRequisition *requisition);
static gboolean gx_selector_button_press (GtkWidget *widget, GdkEventButton *event);
static void
gx_selector_set_property(GObject      *object,
                            guint         prop_id,
                            const GValue *value,
                            GParamSpec   *pspec);
static void
gx_selector_get_property(GObject      *object,
                            guint         prop_id,
                            GValue       *value,
                            GParamSpec   *pspec);

G_DEFINE_TYPE(GxSelector, gx_selector, GX_TYPE_REGLER);

static void gx_selector_class_init(GxSelectorClass *klass)
{
	GObjectClass   *gobject_class;
	GtkObjectClass *object_class;
	GtkWidgetClass *widget_class;

	gobject_class = G_OBJECT_CLASS (klass);
	object_class = (GtkObjectClass*) klass;
	widget_class = (GtkWidgetClass*) klass;

	gobject_class->set_property = gx_selector_set_property;
	gobject_class->get_property = gx_selector_get_property;

//--------- connect the events with funktions
	widget_class->enter_notify_event = gx_selector_enter_in;
	widget_class->leave_notify_event = gx_selector_leave_out;
	widget_class->expose_event = gx_selector_expose;
	widget_class->size_request = gx_selector_size_request;
	widget_class->button_press_event = gx_selector_button_press;

	g_object_class_install_property(gobject_class,
	                                PROP_MODEL,
	                                g_param_spec_object("model",
	                                                    P_("Selector model"),
	                                                    P_("The model for the selector"),
	                                                    GTK_TYPE_TREE_MODEL,
	                                                    GParamFlags(GTK_PARAM_READWRITE)));
}

//--------- selector size
static const gint class_selector_x = 55 ;
static const gint class_selector_y = 15 ;

static gboolean gx_selector_expose (GtkWidget *widget, GdkEventExpose *event)
{
	g_assert(GX_IS_SELECTOR(widget));
	GxSelector *selector = GX_SELECTOR(widget);

	int selectorx = widget->allocation.x + (widget->allocation.width - class_selector_x) / 2;
	int selectory = widget->allocation.y + (widget->allocation.height - class_selector_y) / 2;
	int n = gtk_tree_model_iter_n_children(selector->model, NULL);
	int selectorstate = gtk_range_get_value(GTK_RANGE(selector));
	if (selectorstate < 0 || selectorstate >= n) {
		selectorstate =  0 ;
		gtk_range_set_value(GTK_RANGE(widget), 0);
	}

	cairo_t*cr = gdk_cairo_create(GDK_DRAWABLE(widget->window));
	cairo_set_line_width (cr, 2.0);

	cairo_rectangle (cr, selectorx+1,selectory+1,class_selector_x-4,class_selector_y-2);
	cairo_set_source_rgba (cr, 0, 0, 0, 0.5);
	cairo_fill_preserve (cr);
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_stroke (cr);

	cairo_rectangle (cr, selectorx+42,selectory+2,9,class_selector_y-4);
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_fill_preserve (cr);
	cairo_set_line_width (cr, 1.0);
	cairo_set_source_rgb (cr, 0.2, 0.2, 0.2);
	cairo_stroke (cr);

	cairo_set_source_rgba (cr, 0.4, 1, 0.2, 0.8);
	cairo_set_font_size (cr, 10.0);
	cairo_move_to (cr, selectorx+1, selectory+11);
	const char *s;
	if (selector->model) {
		GtkTreeIter iter;
		gtk_tree_model_iter_nth_child(selector->model, &iter, NULL, selectorstate);
		gtk_tree_model_get(selector->model, &iter, 0, &s, -1);
	} else {
		s = "";
	}
	cairo_show_text(cr, s);
	cairo_stroke (cr);
	cairo_destroy(cr);
	return TRUE;
}

static gboolean gx_selector_leave_out (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_SELECTOR(widget));
	int selectorx = widget->allocation.x + (widget->allocation.width - class_selector_x) / 2;
	int selectory = widget->allocation.y + (widget->allocation.height - class_selector_y) / 2;
	cairo_t*cr = gdk_cairo_create(GDK_DRAWABLE(widget->window));
	cairo_rectangle (cr, selectorx+42,selectory+2,9,class_selector_y-4);
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_fill_preserve (cr);
	cairo_set_line_width (cr, 1.0);
	cairo_set_source_rgb (cr, 0.2, 0.2, 0.2);
	cairo_stroke (cr);
	cairo_destroy(cr);
	return TRUE;
}

static gboolean gx_selector_enter_in (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_SELECTOR(widget));
	int selectorx = widget->allocation.x + (widget->allocation.width - class_selector_x) / 2;
	int selectory = widget->allocation.y + (widget->allocation.height - class_selector_y) / 2;
	cairo_t*cr = gdk_cairo_create(GDK_DRAWABLE(widget->window));
	cairo_rectangle (cr, selectorx+42,selectory+2,9,class_selector_y-4);
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_fill_preserve (cr);
	cairo_move_to(cr,selectorx+43,selectory+10);
	cairo_line_to (cr,selectorx+47 , selectory+4);
	cairo_line_to (cr,selectorx+51 , selectory+10);
	cairo_set_line_width (cr, 1.0);
	cairo_set_source_rgb (cr, 0.3, 0.3, 0.3);
	cairo_stroke (cr);
	cairo_destroy(cr);
	return TRUE;
}

static void gx_selector_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
	g_assert(GX_IS_SELECTOR(widget));
	requisition->width = class_selector_x;
	requisition->height = class_selector_y;
}

static gboolean gx_selector_button_press (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_SELECTOR(widget));
	GtkWidget * dialog,* spinner, *ok_button, *vbox, *toplevel;
	GxSelector *selector = GX_SELECTOR(widget);
	GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
	int i, n;

	switch (event->button) {
	case 1:  // left button
		gtk_widget_grab_focus(widget);
		gtk_grab_add(widget);
		n = gtk_tree_model_iter_n_children(selector->model, NULL);
		i = gtk_range_get_value(GTK_RANGE(widget)) + 1;
		gtk_range_set_range(GTK_RANGE(widget), 0, n-1);
		if (i >= n) {
			i = 0;
		}
		gtk_range_set_value(GTK_RANGE(widget), i);
		break;
	case 3: // right button show num entry
		dialog = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		spinner = gtk_spin_button_new(
			GTK_ADJUSTMENT(adj), adj->step_increment, 0);
		gtk_entry_set_activates_default(GTK_ENTRY(spinner), TRUE);
		ok_button  = gtk_button_new_from_stock(GTK_STOCK_OK);
		GTK_WIDGET_SET_FLAGS (GTK_WIDGET(ok_button), GTK_CAN_DEFAULT);
		vbox = gtk_vbox_new (FALSE, 4);
		gtk_container_add (GTK_CONTAINER(vbox), spinner);
		gtk_container_add (GTK_CONTAINER(vbox), ok_button);
		gtk_container_add (GTK_CONTAINER(dialog), vbox);
		gtk_window_set_decorated(GTK_WINDOW(dialog), FALSE);
		gtk_window_set_title (GTK_WINDOW (dialog), "set");
		gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
		gtk_window_set_gravity(GTK_WINDOW(dialog), GDK_GRAVITY_SOUTH);
		gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);
		gtk_window_set_keep_below (GTK_WINDOW(dialog), FALSE);
		gtk_widget_grab_default(ok_button);
		toplevel = gtk_widget_get_toplevel (widget);
		if (GTK_WIDGET_TOPLEVEL (toplevel)) {
			gtk_window_set_transient_for (GTK_WINDOW(dialog), GTK_WINDOW(toplevel));
		}

		gtk_window_set_destroy_with_parent(GTK_WINDOW(dialog), TRUE);
		g_signal_connect_swapped (ok_button, "clicked",
		                          G_CALLBACK (gtk_widget_destroy), dialog);
		gtk_widget_show_all(dialog);
		break;
	}
	return TRUE;
}

static void gx_selector_init(GxSelector *selector)
{
	GtkWidget *widget = GTK_WIDGET(selector);
	gtk_widget_set_has_window (GTK_WIDGET (selector), FALSE);
	GTK_WIDGET_SET_FLAGS (GTK_WIDGET(selector), GTK_CAN_FOCUS);
	GTK_WIDGET_SET_FLAGS (GTK_WIDGET(selector), GTK_CAN_DEFAULT);
	widget->requisition.width = class_selector_x;
	widget->requisition.height = class_selector_y;
}

static void
gx_selector_unset_model (GxSelector *selector)
{
	/*
	if (selector->model) {
		g_signal_handler_disconnect (priv->model,
		                             priv->inserted_id);
		g_signal_handler_disconnect (priv->model,
		                             priv->deleted_id);
		g_signal_handler_disconnect (priv->model,
		                             priv->reordered_id);
		g_signal_handler_disconnect (priv->model,
		                             priv->changed_id);
	}
	*/

	if (selector->model) {
		g_object_unref (selector->model);
		selector->model = NULL;
	}
}

static void
gx_selector_set_model(GxSelector *selector, GtkTreeModel *model)
{
	g_return_if_fail(GX_IS_SELECTOR(selector));
	g_return_if_fail(model == NULL || GTK_IS_TREE_MODEL (model));

	if (model == selector->model)
		return;
  
	gx_selector_unset_model(selector);

	if (model != NULL) {
		selector->model = model;
		g_object_ref (selector->model);
	}
	int n = gtk_tree_model_iter_n_children(model, NULL) - 1;
	if (n < 0) {
		n = 0;
	}
	gtk_adjustment_configure(gtk_range_get_adjustment(GTK_RANGE(selector)), 0.0, 0.0, n, 1.0, 1.0, 0.0);
	g_object_notify(G_OBJECT(selector), "model");
}

static void
gx_selector_set_property (GObject      *object,
                             guint         prop_id,
                             const GValue *value,
                             GParamSpec   *pspec)
{
	GxSelector *selector = GX_SELECTOR(object);
	switch(prop_id) {
	case PROP_MODEL:
		gx_selector_set_model(selector, (GtkTreeModel*)g_value_get_object (value));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
gx_selector_get_property(GObject      *object,
                            guint         prop_id,
                            GValue       *value,
                            GParamSpec   *pspec)
{
	GxSelector *selector = GX_SELECTOR(object);
	switch(prop_id) {
	case PROP_MODEL:
		g_value_set_object (value, selector->model);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

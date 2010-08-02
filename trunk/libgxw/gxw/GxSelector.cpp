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
#include <string.h>

#define P_(s) (s)   // FIXME -> gettext

/****************************************************************
 ** GxSelector
 */

#define GX_SELECTOR_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), GX_TYPE_SELECTOR, GxSelectorPrivate))

typedef struct
{
	GtkMenu *menu;
	GtkRequisition textsize;
	gboolean req_ok;
	gboolean inside;
} GxSelectorPrivate;

enum {
	PROP_MODEL = 1,
};

static gboolean gx_selector_enter_in (GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_selector_leave_out (GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_selector_expose (GtkWidget *widget, GdkEventExpose *event);
static void gx_selector_size_request (GtkWidget *widget, GtkRequisition *requisition);
static gboolean gx_selector_button_press (GtkWidget *widget, GdkEventButton *event);
static void gx_selector_destroy(GtkObject *object);
static void gx_selector_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gx_selector_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static gboolean gx_selector_value_entry(GxRegler *regler, GdkRectangle *rect, GdkEventButton *event);
static void gx_selector_style_set(GtkWidget *widget, GtkStyle *previous_style);

G_DEFINE_TYPE(GxSelector, gx_selector, GX_TYPE_REGLER);

static void gx_selector_class_init(GxSelectorClass *klass)
{
	GObjectClass   *gobject_class = G_OBJECT_CLASS(klass);
	GtkObjectClass *object_class = (GtkObjectClass*)klass;
	GtkWidgetClass *widget_class = (GtkWidgetClass*)klass;
	GxReglerClass *regler_class = (GxReglerClass*)klass;

	gobject_class->set_property = gx_selector_set_property;
	gobject_class->get_property = gx_selector_get_property;
	object_class->destroy = gx_selector_destroy;
	widget_class->enter_notify_event = gx_selector_enter_in;
	widget_class->leave_notify_event = gx_selector_leave_out;
	widget_class->expose_event = gx_selector_expose;
	widget_class->size_request = gx_selector_size_request;
	widget_class->style_set = gx_selector_style_set;
	widget_class->button_press_event = gx_selector_button_press;
	regler_class->value_entry = gx_selector_value_entry;
	g_object_class_install_property(
		gobject_class, PROP_MODEL,
		g_param_spec_object(
			"model", P_("Selector model"),
			P_("The model for the selector"),
			GTK_TYPE_TREE_MODEL, GParamFlags(GTK_PARAM_READWRITE)));
	g_type_class_add_private(klass, sizeof (GxSelectorPrivate));
}

static int get_selector_state(GxSelector *selector)
{
	if (!selector->model) {
		return 0;
	}
	int n = gtk_tree_model_iter_n_children(selector->model, NULL);
	int selectorstate = gtk_range_get_value(GTK_RANGE(selector));
	if (selectorstate < 0 || selectorstate >= n) {
		selectorstate =  0 ;
		gtk_range_set_value(GTK_RANGE(selector), 0);
	}
	return selectorstate;
}

static const GtkBorder default_selector_border = { 10, 10, 3, 3 };

static void get_selector_border(GtkWidget *widget, GtkBorder *selector_border)
{
	GtkBorder *tmp_border;

	gtk_widget_style_get(widget, "value-border", &tmp_border, NULL);
	if (tmp_border) {
		*selector_border = *tmp_border;
		gtk_border_free(tmp_border);
	} else {
		*selector_border = default_selector_border;
    }
}

static void gx_selector_get_positions(
	GtkWidget *widget, GdkRectangle *arrow, gint *yborder, GdkRectangle *text, gint *off_x, gint *off_y)
{
	gint arrow_width, arrow_height, arrow_sep, border;
	GtkBorder selector_border;
	gtk_widget_style_get(widget,
	                     "trough-border", &border,
	                     "stepper-size", &arrow_width,
	                     "stepper-spacing", &arrow_sep,
	                     NULL);
	arrow_height = (arrow_width * 3) / 4;
	get_selector_border(widget, &selector_border);
	int width = widget->allocation.width; // fill allocated width
	int height = widget->requisition.height;
	int x = widget->allocation.x + widget->style->xthickness +(widget->allocation.width - width) / 2;
	int y = widget->allocation.y + widget->style->ythickness + (widget->allocation.height - height) / 2;
	arrow->x = x + width - 2 * widget->style->xthickness - selector_border.right - arrow_width;
	arrow->y = y + selector_border.bottom - widget->style->ythickness +
		(height - selector_border.bottom - selector_border.top - arrow_height - border) / 2;
	arrow->width = arrow_width;
	arrow->height = arrow_height + 2*border;
	*yborder = border;
	if (text) {
		text->x = x;
		text->y = y;
		text->width = width - 2 * widget->style->xthickness;
		text->height = height - 2 * widget->style->ythickness;
		*off_x = selector_border.left;
		*off_y = selector_border.bottom;
	}
}

static void gx_selector_draw_arrow(const GdkRectangle *rect, gint yborder, cairo_t *cr, gboolean has_focus)
{
	cairo_rectangle(cr, rect->x, rect->y, rect->width, rect->height);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_fill_preserve(cr);
	cairo_set_line_width(cr, 1.0);
	if (has_focus) {
		cairo_move_to(cr, rect->x, rect->y + rect->height - yborder);
		cairo_line_to(cr, rect->x + rect->width / 2.0, rect->y + yborder);
		cairo_line_to(cr, rect->x + rect->width, rect->y + rect->height - yborder);
		cairo_set_source_rgb(cr, 0.3, 0.3, 0.3);
	} else {
		cairo_set_source_rgb(cr, 0.2, 0.2, 0.2);
	}
	cairo_stroke (cr);
}

static gboolean gx_selector_expose (GtkWidget *widget, GdkEventExpose *event)
{
	g_assert(GX_IS_SELECTOR(widget));
	GxSelector *selector = GX_SELECTOR(widget);
	GxSelectorPrivate *priv = GX_SELECTOR_GET_PRIVATE(selector);
	int selectorstate = get_selector_state(selector);
	PangoLayout *layout = gtk_widget_create_pango_layout(widget, NULL);
	GdkRectangle arrow, text;
	gint yborder, off_x, off_y;
	gx_selector_get_positions(widget, &arrow, &yborder, &text, &off_x, &off_y);

	cairo_t*cr = gdk_cairo_create(GDK_DRAWABLE(widget->window));
	cairo_set_line_width(cr, 2.0);

	cairo_rectangle(cr, text.x, text.y, text.width, text.height);
	cairo_set_source_rgba(cr, 0, 0, 0, 0.5);
	cairo_fill_preserve(cr);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_stroke(cr);

	gx_selector_draw_arrow(&arrow, yborder, cr, priv->inside);
	cairo_destroy(cr);
	if (selector->model) {
		gint x, y;
		PangoRectangle logical;
		char *s;
		GtkTreeIter iter;
		gtk_tree_model_iter_nth_child(selector->model, &iter, NULL, selectorstate);
		gtk_tree_model_get(selector->model, &iter, 0, &s, -1);
		pango_layout_set_text(layout, s, -1);
		pango_layout_get_pixel_extents(layout, NULL, &logical);
		x = text.x + off_x + (priv->textsize.width - logical.width) / 2;
		y = text.y + off_y + (priv->textsize.height- logical.height)/ 2;
		gtk_paint_layout(widget->style, widget->window, gtk_widget_get_state(widget),
		                 FALSE, NULL, widget, "label", x, y, layout);
		g_free(s);
	}
	g_object_unref(layout);
	return TRUE;
}

static gboolean gx_selector_leave_out (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_SELECTOR(widget));
	GxSelectorPrivate *priv = GX_SELECTOR_GET_PRIVATE(GX_SELECTOR(widget));
	priv->inside = FALSE;
	cairo_t*cr = gdk_cairo_create(GDK_DRAWABLE(widget->window));
	GdkRectangle rect;
	gint yborder;
	gx_selector_get_positions(widget, &rect, &yborder, NULL, NULL, NULL);
	gx_selector_draw_arrow(&rect, yborder, cr, FALSE);
	cairo_destroy(cr);
	return TRUE;
}

static gboolean gx_selector_enter_in (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_SELECTOR(widget));
	GxSelectorPrivate *priv = GX_SELECTOR_GET_PRIVATE(GX_SELECTOR(widget));
	priv->inside = TRUE;
	cairo_t*cr = gdk_cairo_create(GDK_DRAWABLE(widget->window));
	GdkRectangle rect;
	gint yborder;
	gx_selector_get_positions(widget, &rect, &yborder, NULL, NULL, NULL);
	gx_selector_draw_arrow(&rect, yborder, cr, TRUE);
	cairo_destroy(cr);
	return TRUE;
}

static void gx_selector_style_set(GtkWidget *widget, GtkStyle *previous_style)
{
	GxSelectorPrivate *priv = GX_SELECTOR_GET_PRIVATE(widget);
	priv->req_ok = FALSE;
}

static void gx_selector_size_request(GtkWidget *widget, GtkRequisition *requisition)
{
	g_assert(GX_IS_SELECTOR(widget));
	GxSelector *selector = GX_SELECTOR(widget);
	if (!selector->model) {
		return;
	}
	GxSelectorPrivate *priv = GX_SELECTOR_GET_PRIVATE(selector);
	if (priv->req_ok) {
		gtk_widget_get_child_requisition(widget, requisition);
	} else {
		GtkTreeIter iter;
		gint width = 0;
		gint height = 0;
		gint arrow_width, arrow_sep, border;
		GtkBorder selector_border;
		gtk_widget_style_get(widget,
		                     "trough-border", &border,
		                     "stepper-size", &arrow_width,
		                     "stepper-spacing", &arrow_sep,
		                     NULL);
		get_selector_border(widget, &selector_border);
		PangoLayout *l = gtk_widget_create_pango_layout(widget, NULL);
		gboolean found = gtk_tree_model_get_iter_first(selector->model, &iter);
		while (found) {
			PangoRectangle logical_rect;
			gchar *s;
			gtk_tree_model_get(selector->model, &iter, 0, &s, -1);
			pango_layout_set_text(l, s, -1);
			g_free(s);
			pango_layout_get_pixel_extents(l, NULL, &logical_rect);
			if (width < logical_rect.width) {
				width = logical_rect.width;
			}
			if (height < logical_rect.height) {
				height = logical_rect.height;
			}
			found = gtk_tree_model_iter_next(selector->model, &iter);
		}
		priv->textsize.width = width;
		priv->textsize.height = height;
		requisition->width = width + arrow_sep + arrow_width + 2*border +
			selector_border.left + selector_border.right + 2 * widget->style->xthickness;
		requisition->height = height + selector_border.top + selector_border.bottom +
			2 * widget->style->ythickness;
		priv->req_ok = TRUE;
		g_object_unref(l);
	}
}

static void posfunc(GtkMenu *menu, gint *x, gint *y, gboolean *push_in, gpointer user_data)
{
	GtkWidget *w = GTK_WIDGET(user_data);
	GdkWindow *win = gtk_widget_get_window(w);
	int i = get_selector_state(GX_SELECTOR(w));
	gint n = g_list_length(gtk_container_get_children(GTK_CONTAINER(menu)));
	GtkRequisition req;
	gtk_widget_get_requisition(GTK_WIDGET(menu), &req);
	gdk_window_get_origin(win, x, y);
	*x += w->allocation.x;
	*y += w->allocation.y - (req.height * i) / n;
	*push_in = TRUE;
}

static void selection_done(GtkMenu *menu, gpointer data)
{
	GxSelector *selector = GX_SELECTOR(data);
	GtkTreeIter iter;
	gboolean found;
	int n;
	const char *label = gtk_menu_item_get_label(GTK_MENU_ITEM(gtk_menu_get_active(menu)));
	n = 0;
	found = gtk_tree_model_get_iter_first(selector->model, &iter);
	while (found) {
		gchar *s;
		gtk_tree_model_get(selector->model, &iter, 0, &s, -1);
		if (strcmp(label, s) == 0) {
			g_free(s);
			if (n != get_selector_state(selector)) {
				gtk_range_set_value(GTK_RANGE(selector), n);
				gtk_widget_queue_draw(GTK_WIDGET(selector));
			}
			return;
		}
		g_free(s);
		n += 1;
		found = gtk_tree_model_iter_next(selector->model, &iter);
		}
	g_assert(FALSE);
}

static gboolean gx_selector_value_entry(GxRegler *regler, GdkRectangle *rect, GdkEventButton *event)
{
	GxSelector *selector = GX_SELECTOR(regler);
	GxSelectorPrivate *priv = GX_SELECTOR_GET_PRIVATE(selector);
	GtkMenu *m = priv->menu;
	if (!m) {
		GtkTreeIter iter;
		gboolean found;
		char *s;
		m = GTK_MENU(gtk_menu_new());
		gtk_widget_set_name(GTK_WIDGET(m), "selector-value-popup");
		g_signal_connect(m, "selection-done", G_CALLBACK(selection_done), selector);
		found = gtk_tree_model_get_iter_first(selector->model, &iter);
		while (found) {
			gtk_tree_model_get(selector->model, &iter, 0, &s, -1);
			GtkWidget *item = gtk_menu_item_new_with_label(s);
			gtk_menu_append(m, item);
			gtk_widget_show(item);
			g_free(s);
			found = gtk_tree_model_iter_next(selector->model, &iter);
		}
		priv->menu = m;
	}
	gtk_menu_set_active(m, get_selector_state(selector));
	gtk_menu_popup(m, NULL, NULL, posfunc, regler, event->button, event->time);
	return TRUE;
}

static gboolean gx_selector_button_press (GtkWidget *widget, GdkEventButton *event)
{
	g_assert(GX_IS_SELECTOR(widget));
	GxSelector *selector = GX_SELECTOR(widget);
	int i, n;
	gboolean ret;
	GdkRectangle rect;

	switch (event->button) {
	case 1:  // left button
		if (event->type != GDK_BUTTON_PRESS) {
			return TRUE;
		}
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
		rect.width = widget->requisition.width;
		rect.height = widget->requisition.height;
		rect.x = widget->allocation.x + (widget->allocation.width - widget->requisition.width) / 2;
		rect.y = widget->allocation.y + (widget->allocation.height - widget->requisition.height) / 2;
		g_signal_emit_by_name(GX_REGLER(widget), "value-entry", &rect, event, &ret);
		return ret;
		break;
	}
	return TRUE;
}

static void gx_selector_init(GxSelector *selector)
{
	gtk_widget_set_has_window(GTK_WIDGET(selector), FALSE);
	gtk_widget_set_can_focus(GTK_WIDGET(selector), TRUE);
}

static void gx_selector_unset_model(GxSelector *selector)
{
	if (selector->model) {
		g_object_unref (selector->model);
		selector->model = NULL;
	}
}

static void gx_selector_destroy(GtkObject *object)
{
	gx_selector_unset_model(GX_SELECTOR(object));
	GTK_OBJECT_CLASS(gx_selector_parent_class)->destroy(object);
}


void gx_selector_set_model(GxSelector *selector, GtkTreeModel *model)
{
	g_return_if_fail(GX_IS_SELECTOR(selector));
	g_return_if_fail(model == NULL || GTK_IS_TREE_MODEL (model));
	GxSelectorPrivate *priv;
	if (model == selector->model)
		return;
    priv = GX_SELECTOR_GET_PRIVATE(selector);
	gx_selector_unset_model(selector);
	int n = 0;
	if (model != NULL) {
		selector->model = model;
		g_object_ref (selector->model);
		n = gtk_tree_model_iter_n_children(model, NULL) - 1;
		if (n < 0) {
			n = 0;
		}
	}
	gtk_adjustment_configure(gtk_range_get_adjustment(GTK_RANGE(selector)), 0.0, 0.0, n, 1.0, 1.0, 0.0);
	priv->req_ok = FALSE;
	gtk_widget_queue_resize(GTK_WIDGET(selector));
	g_object_notify(G_OBJECT(selector), "model");
}

GtkTreeModel *gx_selector_get_model(GxSelector *selector)
{
	g_return_val_if_fail(GX_IS_SELECTOR(selector), 0);
	return selector->model;
}

static void gx_selector_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
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

static void gx_selector_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
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

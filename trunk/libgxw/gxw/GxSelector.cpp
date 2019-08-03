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

#include "GxSelector.h"
#include <string.h>
#include <algorithm>

#define P_(s) (s)   // FIXME -> gettext

/****************************************************************
 ** GxSelector
 */

struct _GxSelectorPrivate
{
	GtkMenu *menu;
	GtkRequisition textsize;
	gboolean req_ok;
	gint req_width;
	gint req_height;
	gboolean inside;
};

enum {
	PROP_MODEL = 1,
    PROP_BORDER_RADIUS
};

static gboolean gx_selector_enter_in (GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_selector_leave_out (GtkWidget *widget, GdkEventCrossing *event);
static gboolean gx_selector_draw (GtkWidget *widget, cairo_t *cr);
static void gx_selector_get_preferred_width(GtkWidget *widget, gint *minimal_width,
                                            gint *natural_width);
static void gx_selector_get_preferred_height(GtkWidget *widget, gint *minimal_height,
                                             gint *natural_height);
static void gx_selector_size_request (GtkWidget *widget, gint *out_width, gint *out_height);
static gboolean gx_selector_button_press (GtkWidget *widget, GdkEventButton *event);
static void gx_selector_destroy(GtkWidget *widget);
static void gx_selector_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gx_selector_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static gboolean gx_selector_value_entry(GxRegler *regler, GdkRectangle *rect, GdkEventButton *event);
static void gx_selector_style_set(GtkWidget *widget, GtkStyle *previous_style);

G_DEFINE_TYPE_WITH_PRIVATE(GxSelector, gx_selector, GX_TYPE_REGLER);

static void gx_selector_class_init(GxSelectorClass *klass)
{
	GObjectClass   *gobject_class = G_OBJECT_CLASS(klass);
	GtkWidgetClass *widget_class = (GtkWidgetClass*)klass;
	GxReglerClass *regler_class = (GxReglerClass*)klass;

	gobject_class->set_property = gx_selector_set_property;
	gobject_class->get_property = gx_selector_get_property;
	widget_class->destroy = gx_selector_destroy;
	widget_class->enter_notify_event = gx_selector_enter_in;
	widget_class->leave_notify_event = gx_selector_leave_out;
	widget_class->draw = gx_selector_draw;
	widget_class->get_preferred_width = gx_selector_get_preferred_width;
	widget_class->get_preferred_height = gx_selector_get_preferred_height;
	widget_class->style_set = gx_selector_style_set;
	widget_class->button_press_event = gx_selector_button_press;
	regler_class->value_entry = gx_selector_value_entry;
	g_object_class_install_property(
		gobject_class, PROP_MODEL,
		g_param_spec_object(
			"model", P_("Selector model"),
			P_("The model for the selector"),
			GTK_TYPE_TREE_MODEL, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
}

static int get_selector_state(GxSelector *selector)
{
	if (!selector->model) {
		return 0;
	}
	int n = gtk_tree_model_iter_n_children(selector->model, NULL);
	int lower = gtk_adjustment_get_lower(gtk_range_get_adjustment(GTK_RANGE(selector)));
	int selectorstate = (int)gtk_range_get_value(GTK_RANGE(selector)) - lower;
	if (selectorstate < 0 || selectorstate >= n) {
		selectorstate = 0;
		gtk_range_set_value(GTK_RANGE(selector), lower);
	}
	return selectorstate;
}

static void set_value_from_selector_state(GxSelector *selector, int selectorstate)
{
	if (!selector->model) {
		return;
	}
	int n = gtk_tree_model_iter_n_children(selector->model, NULL);
	if (selectorstate < 0 || selectorstate >= n) {
		selectorstate = 0;
	}
	int lower = gtk_adjustment_get_lower(gtk_range_get_adjustment(GTK_RANGE(selector)));
	gtk_range_set_value(GTK_RANGE(selector), lower + selectorstate);
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
	GtkWidget *widget, GdkRectangle *arrow, GdkRectangle *text, gint *off_x, gint *off_y)
{
	GtkBorder selector_border;
	get_selector_border(widget, &selector_border);
    gint iwidth = GX_SELECTOR(widget)->icon_width;
    gint iheight = GX_SELECTOR(widget)->icon_height;
	GtkAllocation allocation;
	gint min_height;
	gtk_widget_get_allocation(widget, &allocation);
	gtk_widget_get_preferred_height(widget, &min_height, nullptr);
	GtkStyle *style = gtk_widget_get_style(widget);
	int width = allocation.width; // fill allocated width
	int height = min_height;
	int x = style->xthickness;
	int y = style->ythickness + (allocation.height - height) / 2;
	arrow->x = x + width - 2 * style->xthickness - iwidth;
	arrow->y = y + selector_border.bottom - style->ythickness +
		(height - selector_border.bottom - selector_border.top - iheight) / 2;
	arrow->width = iwidth;
	arrow->height = iheight;
	if (text) {
		text->x = x;
		text->y = y;
		text->width = width - 3 * style->xthickness - iwidth;
		text->height = height - 2 * style->ythickness;
		*off_x = selector_border.left;
		*off_y = selector_border.bottom;
	}
}

static void gx_selector_create_icon(GxSelector *selector) {
    if (selector->icon)
        return;
    selector->icon = gtk_widget_render_icon(GTK_WIDGET(selector), "selector_icon", (GtkIconSize)-1, NULL);
    selector->icon_width = gdk_pixbuf_get_width(selector->icon);
    selector->icon_height = gdk_pixbuf_get_height(selector->icon);
}

static gboolean gx_selector_draw (GtkWidget *widget, cairo_t *cr)
{
	g_assert(GX_IS_SELECTOR(widget));
	GxSelector *selector = GX_SELECTOR(widget);
	GxSelectorPrivate *priv = selector->priv;
	int selectorstate = get_selector_state(selector);
    
    gx_selector_create_icon(selector);
    
	PangoLayout *layout = gtk_widget_create_pango_layout(widget, NULL);
	GdkRectangle arrow, text;
	gint off_x, off_y;
	gx_selector_get_positions(widget, &arrow, &text, &off_x, &off_y);
    gint rad;
    float bevel;
    gtk_widget_style_get(widget, "border-radius", &rad, "bevel", &bevel, NULL);
    if (!rad)
        rad = 0;
    if (!bevel)
        bevel = 0;

    GtkAllocation allocation;
    gint natural_height;
    gtk_widget_get_allocation(widget, &allocation);
    gtk_widget_get_preferred_height(widget, nullptr, &natural_height);
    gx_draw_rect(cr, widget, "bg", NULL, 0,
        (allocation.height - natural_height) / 2,
        allocation.width,
        natural_height,
        rad,
        bevel);

    GtkStyle* style = gtk_widget_get_style(widget);
    if (style->ythickness >= 3)
        gx_draw_inset(cr, text.x, text.y, text.width, text.height,
            std::max(rad - std::max(style->ythickness, style->ythickness), 0), 1);

    gx_draw_rect(cr, widget, "base", NULL, text.x,
        text.y,
        text.width,
        text.height,
        std::max(rad - std::max(style->ythickness, style->ythickness), 0),
        0);

    gx_draw_glass(cr, text.x, text.y, text.width, text.height,
        std::max(rad - std::max(style->ythickness, style->ythickness), 0));

    gdk_cairo_set_source_pixbuf(cr, selector->icon, arrow.x, arrow.y);
    cairo_rectangle(cr, arrow.x, arrow.y, arrow.width, arrow.height);
    cairo_fill(cr);

	if (selector->model) {
		gint x, y;
		PangoRectangle logical;
		char *s;
		GtkTreeIter iter;
		gtk_tree_model_iter_nth_child(selector->model, &iter, NULL, selectorstate);
		gtk_tree_model_get(selector->model, &iter, 0, &s, -1);
		pango_layout_set_text(layout, s, -1);
		pango_layout_get_pixel_extents(layout, NULL, &logical);
		x = text.x + (text.width - logical.width) / 2;
		y = text.y + off_y + (priv->textsize.height - logical.height)/ 2;
		gtk_paint_layout(style, cr,
		                 gtk_widget_get_state(widget),
		                 FALSE, widget, "label", x, y, layout);
		g_free(s);
	}
	g_object_unref(layout);
	return TRUE;
}

static gboolean gx_selector_leave_out (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_SELECTOR(widget));
    gtk_widget_set_state(widget, GTK_STATE_NORMAL);
    gtk_widget_queue_draw(widget);
	return TRUE;
}

static gboolean gx_selector_enter_in (GtkWidget *widget, GdkEventCrossing *event)
{
	g_assert(GX_IS_SELECTOR(widget));
    gtk_widget_set_state(widget, GTK_STATE_PRELIGHT);
    gtk_widget_queue_draw(widget);
	return TRUE;
}

static void gx_selector_style_set(GtkWidget *widget, GtkStyle *previous_style)
{
	GxSelectorPrivate *priv = GX_SELECTOR(widget)->priv;
	priv->req_ok = FALSE;
}

static void gx_selector_get_preferred_width(GtkWidget *widget, gint *minimal_width,
                                            gint *natural_width)
{
	gint width, height;
	gx_selector_size_request(widget, &width, &height);

	if (minimal_width) {
		*minimal_width = width;
	}
	if (natural_width) {
		*natural_width = width;
	}
}

static void gx_selector_get_preferred_height(GtkWidget *widget, gint *minimal_height,
                                             gint *natural_height)
{
	gint width, height;
	gx_selector_size_request(widget, &width, &height);

	if (minimal_height) {
		*minimal_height = height;
	}
	if (natural_height) {
		*natural_height = height;
	}
}

static void gx_selector_size_request(GtkWidget *widget, gint *out_width, gint *out_height)
{
	g_assert(GX_IS_SELECTOR(widget));
	GxSelector *selector = GX_SELECTOR(widget);
	GxSelectorPrivate *priv = selector->priv;

    gx_selector_create_icon(selector);

	if (!priv->req_ok) {
		GtkTreeIter iter;
		gint width = selector->icon_width;
		gint height = selector->icon_height;
		GtkBorder selector_border;
		get_selector_border(widget, &selector_border);
		PangoLayout *l = gtk_widget_create_pango_layout(widget, NULL);
		gboolean found = !!selector->model &&
			gtk_tree_model_get_iter_first(selector->model, &iter);
		while (found) {
			PangoRectangle logical_rect;
			gchar *s;
			gtk_tree_model_get(selector->model, &iter, 0, &s, -1);
			pango_layout_set_text(l, s, -1);
			g_free(s);
			pango_layout_get_pixel_extents(l, NULL, &logical_rect);
            width = std::max(logical_rect.width, width);
            height = std::max(logical_rect.height, height);
			found = gtk_tree_model_iter_next(selector->model, &iter);
		}
		priv->textsize.width = width;
		priv->textsize.height = height;
        height = std::max(height, selector->icon_height);
		GtkStyle* style = gtk_widget_get_style(widget);
		priv->req_width = width + selector->icon_width +
			selector_border.left + selector_border.right + 3 * style->xthickness;
		priv->req_height = height + selector_border.top + selector_border.bottom +
			2 * style->ythickness;
		priv->req_ok = TRUE;
		g_object_unref(l);
	}
	*out_width = priv->req_width;
	*out_height = priv->req_height;
}

static void posfunc(GtkMenu *menu, gint *x, gint *y, gboolean *push_in, gpointer user_data)
{
	GtkWidget *w = GTK_WIDGET(user_data);
	GdkWindow *win = gtk_widget_get_window(w);
	int i = get_selector_state(GX_SELECTOR(w));
	gint n = g_list_length(gtk_container_get_children(GTK_CONTAINER(menu)));
	gint min_height;
	gtk_widget_get_preferred_height(GTK_WIDGET(menu), nullptr, &min_height);
	gdk_window_get_origin(win, x, y);
	GtkAllocation allocation;
	gtk_widget_get_allocation(w, &allocation);
	*y -= (min_height * i) / n;
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
				set_value_from_selector_state(selector, n);
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
	GxSelectorPrivate *priv = selector->priv;
	GtkMenu *m = priv->menu;
	if (!m) {
		GtkTreeIter iter;
		gboolean found;
		char *s;
		m = GTK_MENU(gtk_menu_new());
		//gtk_menu_set_reserve_toggle_size(m, false);  // for narrow menus
		gtk_widget_set_name(GTK_WIDGET(m), "selector-value-popup");
		g_signal_connect(m, "selection-done", G_CALLBACK(selection_done), selector);
		found = gtk_tree_model_get_iter_first(selector->model, &iter);
		while (found) {
			gtk_tree_model_get(selector->model, &iter, 0, &s, -1);
			GtkWidget *item = gtk_menu_item_new_with_label(s);
			gtk_menu_shell_append(GTK_MENU_SHELL(m), item);
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
		n = GTK_IS_TREE_MODEL(selector->model) ?
			gtk_tree_model_iter_n_children(selector->model, NULL) : 0;
		i = get_selector_state(GX_SELECTOR(widget)) + 1;
		if (i >= n) {
			i = 0;
		}
		set_value_from_selector_state(GX_SELECTOR(widget), i);
		break;
	case 3: // right button show num entry
		GtkRequisition requisition;
		gtk_widget_get_requisition(widget, &requisition);
		rect.width = requisition.width;
		rect.height = requisition.height;
		GtkAllocation allocation;
		gtk_widget_get_allocation(widget, &allocation);
		rect.x = (allocation.width - requisition.width) / 2;
		rect.y = (allocation.height - requisition.height) / 2;
		g_signal_emit_by_name(GX_REGLER(widget), "value-entry", &rect, event, &ret);
		return ret;
		break;
	}
	return TRUE;
}

static void gx_selector_init(GxSelector *selector)
{
	selector->priv = G_TYPE_INSTANCE_GET_PRIVATE(selector, GX_TYPE_SELECTOR, GxSelectorPrivate);
	gtk_widget_set_has_window(GTK_WIDGET(selector), FALSE);
	gtk_widget_set_can_focus(GTK_WIDGET(selector), TRUE);
    selector->icon = NULL;
}

static void gx_selector_unset_model(GxSelector *selector)
{
	if (selector->model) {
		g_object_unref (selector->model);
		selector->model = NULL;
	}
}

static void gx_selector_unset_icon(GxSelector *selector)
{
	if (selector->icon) {
		g_object_unref (selector->icon);
		selector->icon = NULL;
	}
}

static void gx_selector_destroy(GtkWidget *object)
{
	gx_selector_unset_model(GX_SELECTOR(object));
	gx_selector_unset_icon(GX_SELECTOR(object));
	GTK_WIDGET_CLASS(gx_selector_parent_class)->destroy(object);
}


void gx_selector_set_model(GxSelector *selector, GtkTreeModel *model)
{
	g_return_if_fail(GX_IS_SELECTOR(selector));
	g_return_if_fail(model == NULL || GTK_IS_TREE_MODEL (model));
	GxSelectorPrivate *priv = selector->priv;
	if (model == selector->model)
		return;
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

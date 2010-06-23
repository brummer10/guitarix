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

// ***** GxWaveView.cpp *****
/******************************************************************************
part of guitarix, show a wave with Gtk
******************************************************************************/

#include "GxWaveView.h"
#include <gtk/gtkprivate.h>
#include <math.h>

#define P_(s) (s)   // FIXME -> gettext

enum {
	PROP_TEXT_NW = 1,
	PROP_TEXT_NE,
	PROP_TEXT_SW,
	PROP_TEXT_SE,
	PROP_TEXT_POS_W,
	PROP_TEXT_POS_E
};

static void gx_wave_view_destroy(GtkObject*);
static gboolean gx_wave_view_expose(GtkWidget *widget, GdkEventExpose *event);
static void gx_wave_view_size_request(GtkWidget *widget, GtkRequisition *requisition);
static void gx_wave_view_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gx_wave_view_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);

G_DEFINE_TYPE(GxWaveView, gx_wave_view, GTK_TYPE_DRAWING_AREA);

static const int liveview_x = 300;
static const int liveview_y = 80;
static const int background_width = 282;
static const int background_height = 52;

static void wave_view_background(GxWaveView *waveview, cairo_t *cr,
                                 int liveviewx, int liveviewy)
{
	waveview->liveview_image = gdk_pixbuf_new(
		GDK_COLORSPACE_RGB,FALSE,8,background_width,background_height);
	g_assert(waveview->liveview_image != NULL);
	cairo_pattern_t*pat =
		cairo_pattern_create_radial (-130.4, -270.4, 1.6, -1.4,  -4.4, 300.0);

	cairo_pattern_add_color_stop_rgba (pat, 0, 0.2, 0.2, 0.3, 1);
	cairo_pattern_add_color_stop_rgba (pat, 1, 0.05, 0.05, 0.05, 1);
	cairo_set_source_rgb(cr, 0.05, 0.05, 0.05);
	cairo_rectangle (cr, liveviewx, liveviewy, 280, 50);
	cairo_set_source (cr, pat);
	cairo_fill (cr);
	cairo_pattern_destroy (pat);

	/*
	cairo_set_line_width (cr, 10.0);
	cairo_set_source_rgba (cr, 0, 0, 0,0.4);
	cairo_rectangle (cr, liveviewx-5, liveviewy-5, 286, 60);
	cairo_stroke (cr);

	cairo_set_line_width (cr, 1.0);
	cairo_set_source_rgba (cr, 0.1, 0.1, 0.1,0.7);
	cairo_rectangle (cr, liveviewx-6, liveviewy-6, 288, 62);
	cairo_stroke (cr);

	cairo_set_line_width (cr, 1.0);
	cairo_set_source_rgba (cr, 0.5, 0.5, 0.5,0.1);
	cairo_rectangle (cr, liveviewx-12, liveviewy-12, 302, 74);
	cairo_rectangle (cr, liveviewx-2, liveviewy-2, 302, 54);
	cairo_stroke (cr);
	*/

	cairo_set_line_width (cr, 1.5);
	cairo_set_source_rgba (cr,0.2, 1.0, 0.2, 0.4);
	cairo_move_to (cr, liveviewx, liveviewy+25);
	cairo_line_to (cr, liveviewx+280, liveviewy+25);
	cairo_stroke (cr);

	cairo_set_source_rgba (cr,0.2, 1.0, 0.2, 0.4);
	cairo_rectangle (cr, liveviewx, liveviewy, 280.0, 50.0);
	cairo_stroke (cr);

	int gitter = 0;
	for (int i=0; i<28; i++)
	{
		gitter += 10;
		cairo_move_to (cr, liveviewx+gitter-5, liveviewy);
		cairo_line_to (cr, liveviewx+gitter-5, liveviewy+50);
	}

	gitter = 0;
	for (int i=0; i<5; i++)
	{
		gitter += 10;
		cairo_move_to (cr, liveviewx, liveviewy+gitter-5);
		cairo_line_to (cr, liveviewx+280, liveviewy+gitter-5);
	}

	cairo_set_source_rgba (cr,0.2,  1.0, 0.2, 0.05);
	cairo_stroke (cr);

	gdk_pixbuf_get_from_drawable(
		waveview->liveview_image,
		GDK_DRAWABLE(GTK_WIDGET(waveview)->window), gdk_colormap_get_system(),
		liveviewx-1, liveviewy-1,0,0,background_width,background_height);
}

static void draw_text(cairo_t *cr, GdkEventExpose *event, gchar *str,
                      int xorg, int yorg, GtkAnchorType anchor)
{
	if (!str || !*str) {
		return;
	}
	cairo_set_source_rgba (cr, 0.8, 0.8, 0.2,0.6);
	PangoLayout *layout = pango_cairo_create_layout(cr);
	PangoContext *ctx = pango_layout_get_context(layout);
	PangoFontDescription *desc = pango_context_get_font_description(ctx);
	pango_font_description_set_absolute_size(desc, 8000);
	pango_layout_set_markup(layout, str, -1);
	int width, height;
	pango_layout_get_pixel_size(layout, &width, &height);
	if (anchor == GTK_ANCHOR_SW || anchor == GTK_ANCHOR_SE) {
		yorg += background_height - height - 2;
	}
	cairo_move_to(cr, xorg, yorg);
	pango_cairo_show_layout(cr, layout);
}

static gboolean gx_wave_view_expose (GtkWidget *widget, GdkEventExpose *event)
{
	g_assert(GX_IS_WAVE_VIEW(widget));
	GxWaveView *waveview = GX_WAVE_VIEW(widget);

	int liveviewx = (widget->allocation.width  - liveview_x) * 0.5 + 10;
	int liveviewy = (widget->allocation.height - liveview_y) * 0.5 + 15;

	cairo_t*cr = gdk_cairo_create(GDK_DRAWABLE(widget->window));

	if (!waveview->liveview_image) {
		wave_view_background(waveview, cr, liveviewx, liveviewy);
	} else {
		gdk_draw_pixbuf(
			GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
			waveview->liveview_image, 0, 0, liveviewx-1, liveviewy-1,
			background_width, background_height, GDK_RGB_DITHER_NORMAL, 0, 0);
	}

	cairo_set_source_rgb(cr, 1, 1, 1);
	draw_text(cr, event, waveview->text_nw, liveviewx + background_width * waveview->text_pos_w / 100, liveviewy, GTK_ANCHOR_NW);
	draw_text(cr, event, waveview->text_ne, liveviewx + background_width * waveview->text_pos_e / 100, liveviewy, GTK_ANCHOR_NE);
	draw_text(cr, event, waveview->text_sw, liveviewx + background_width * waveview->text_pos_w / 100, liveviewy, GTK_ANCHOR_SW);
	draw_text(cr, event, waveview->text_se, liveviewx + background_width * waveview->text_pos_e / 100, liveviewy, GTK_ANCHOR_SE);

	cairo_move_to (cr, liveviewx+280, liveviewy+25);

	float wave_go = 0;
	float sc = 280.0/waveview->frame_size;
	float sc1 = liveviewx+280+sc;
	float sc2 = liveviewy+25;
	//----- draw the frame
	for (int i = 0; i < waveview->frame_size; i++)
	{
		float x_in = waveview->frame[i];
		cairo_line_to (cr, sc1 - sc*(i+1), sc2 + x_in*75.0);
		wave_go = fmax(wave_go, fabs(x_in));
	}

	//----- get the sample, for display the gain value

	float wave_db = log(fabs( wave_go))*6/log(2);
	double xl     = floor(exp(log(1.055)*2.1*wave_db)*150);

	if (xl > 125.0) xl = 125.0;
	else if (xl < -125.0) xl = -125.0;

	cairo_set_line_width (cr, 1.0);
	cairo_line_to (cr, liveviewx, liveviewy+25);
	cairo_pattern_t* linpat =
		cairo_pattern_create_linear (liveviewx, liveviewy-15,liveviewx, liveviewy+25);

	cairo_pattern_set_extend(linpat, CAIRO_EXTEND_REFLECT);
	cairo_pattern_add_color_stop_rgba (linpat, 0.4, 1, 0.2, 0,0.8);
	cairo_pattern_add_color_stop_rgba (linpat, 0.8, 0.2, 1, 0.2,0.8);
	cairo_set_source (cr, linpat);
	cairo_close_path (cr);

	cairo_fill_preserve (cr);
	cairo_stroke (cr);
	cairo_pattern_destroy (linpat);

	//----- draw the gain value
	double dashes[] = {5.0, 1.0 };
	cairo_set_dash (cr, dashes, 2, -0.25);
	cairo_move_to (cr, liveviewx+140-xl, liveviewy);
	cairo_line_to (cr, liveviewx+140+xl, liveviewy);
	cairo_move_to (cr, liveviewx+140-xl, liveviewy+50);
	cairo_line_to (cr, liveviewx+140+xl, liveviewy+50);
	//cairo_set_source_rgba (cr,  redline, greenline, 0.2,0.8);
	linpat =
		cairo_pattern_create_linear (liveviewx, liveviewy,liveviewx+140, liveviewy);

	cairo_pattern_set_extend(linpat, CAIRO_EXTEND_REFLECT);
	cairo_pattern_add_color_stop_rgba (linpat, 0.2, 1, 0.2, 0,0.8);
	cairo_pattern_add_color_stop_rgba (linpat, 0.8, 0.2, 1, 0.2,0.8);
	cairo_set_source (cr, linpat);
	cairo_set_line_width (cr, 3.0);
	cairo_stroke (cr);
	cairo_destroy(cr);

	return FALSE;
}

static void gx_wave_view_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
	g_assert(GX_IS_WAVE_VIEW(widget));
	requisition->width = liveview_x;
	requisition->height = liveview_y;
}

static void gx_wave_view_class_init (GxWaveViewClass *klass)
{
	GtkObjectClass *object_class = GTK_OBJECT_CLASS(klass);
	GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);

	object_class->destroy = gx_wave_view_destroy;
	gobject_class->set_property = gx_wave_view_set_property;
	gobject_class->get_property = gx_wave_view_get_property;
	widget_class->expose_event = gx_wave_view_expose;
	widget_class->size_request = gx_wave_view_size_request;
	g_object_class_install_property (gobject_class,
	                                 PROP_TEXT_NW,
	                                 g_param_spec_string ("text-nw",
	                                                      P_("Text NW"),
	                                                      P_("Text to be displayed at the top left"),
	                                                      "",
	                                                      GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property (gobject_class,
	                                 PROP_TEXT_NE,
	                                 g_param_spec_string ("text-ne",
	                                                      P_("Text NE"),
	                                                      P_("Text to be displayed at the top right"),
	                                                      "",
	                                                      GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property (gobject_class,
	                                 PROP_TEXT_SW,
	                                 g_param_spec_string ("text-sw",
	                                                      P_("Text SW"),
	                                                      P_("Text to be displayed at the bottom left"),
	                                                      "",
	                                                      GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property (gobject_class,
	                                 PROP_TEXT_SE,
	                                 g_param_spec_string ("text-se",
	                                                      P_("Text SE"),
	                                                      P_("Text to be displayed at the bottom right"),
	                                                      "",
	                                                      GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property (gobject_class,
	                                 PROP_TEXT_POS_W,
	                                 g_param_spec_double ("text-pos-w",
	                                                      P_("Left Position"),
	                                                      P_("Text to be displayed at the bottom right"),
	                                                      0, 100, 5,
	                                                      GParamFlags(GTK_PARAM_READWRITE)));
	g_object_class_install_property (gobject_class,
	                                 PROP_TEXT_POS_E,
	                                 g_param_spec_double ("text-pos-e",
	                                                      P_("Right Position"),
	                                                      P_("Text to be displayed at the bottom right"),
	                                                      0, 100, 70,
	                                                      GParamFlags(GTK_PARAM_READWRITE)));
}

static void gx_wave_view_init(GxWaveView *waveview)
{
	GtkWidget *widget = GTK_WIDGET(waveview);
	waveview->frame = NULL;
	waveview->frame_size = 0;
	waveview->text_nw = NULL;
	waveview->text_ne = NULL;
	waveview->text_sw = NULL;
	waveview->text_se = NULL;
	waveview->text_pos_w = 5;
	waveview->text_pos_e = 70;
	widget->requisition.width = liveview_x;
	widget->requisition.height = liveview_y;
}

static void gx_wave_view_destroy (GtkObject *obj)
{
	GxWaveView *waveview = GX_WAVE_VIEW(obj);
	if (G_IS_OBJECT(waveview->liveview_image)) {
		g_object_unref(waveview->liveview_image);
	}
}

GtkWidget* gx_wave_view_new()
{
	GtkWidget* widget = GTK_WIDGET(g_object_new(GX_TYPE_WAVE_VIEW, NULL));
	return widget;
}

void gx_wave_view_set_frame(GxWaveView *waveview, const float *frame, int frame_size)
{
	g_assert(GX_IS_WAVE_VIEW(waveview));
	waveview->frame = frame;
	waveview->frame_size = frame_size;
	gtk_widget_queue_draw(GTK_WIDGET(waveview));
}

void gx_wave_view_set_text(GxWaveView *waveview, const gchar *text, GtkAnchorType pos)
{
	char **f;
	const char *p;
	g_assert(GX_IS_WAVE_VIEW(waveview));
	switch (pos) {
	case GTK_ANCHOR_NW:
		f = &waveview->text_nw;
		p = "text_nw";
		break;
	case GTK_ANCHOR_NE:
		f = &waveview->text_ne;
		p = "text_ne";
		break;
	case GTK_ANCHOR_SW:
		f = &waveview->text_sw;
		p = "text_sw";
		break;
	case GTK_ANCHOR_SE:
		f = &waveview->text_se;
		p = "text_se";
		break;
	default:
		g_warning("gx_wave_view_set_text: unsupported GtkAnchor");
		return;
	}
	g_free(*f);
	*f = g_strdup(text);
	gtk_widget_queue_draw(GTK_WIDGET(waveview));
	g_object_notify(G_OBJECT(waveview), p);
}

static void gx_wave_view_set_property(GObject *object, guint prop_id,
                                          const GValue *value, GParamSpec *pspec)
{
	GxWaveView *wv = GX_WAVE_VIEW(object);
	switch(prop_id) {
	case PROP_TEXT_NW:
		gx_wave_view_set_text(wv, g_value_get_string(value), GTK_ANCHOR_NW);
		break;
	case PROP_TEXT_NE:
		gx_wave_view_set_text(wv, g_value_get_string(value), GTK_ANCHOR_NE);
		break;
	case PROP_TEXT_SW:
		gx_wave_view_set_text(wv, g_value_get_string(value), GTK_ANCHOR_SW);
		break;
	case PROP_TEXT_SE:
		gx_wave_view_set_text(wv, g_value_get_string(value), GTK_ANCHOR_SE);
		break;
	case PROP_TEXT_POS_W:
		wv->text_pos_w = g_value_get_double(value);
		g_object_notify(object, "text-pos-w");
		break;
	case PROP_TEXT_POS_E:
		wv->text_pos_e = g_value_get_double(value);
		g_object_notify(object, "text-pos-e");
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void gx_wave_view_get_property(GObject *object, guint prop_id,
                                          GValue *value, GParamSpec *pspec)
{
	GxWaveView *wv = GX_WAVE_VIEW(object);

	switch(prop_id) {
	case PROP_TEXT_NW:
		g_value_set_string (value, wv->text_nw);
		break;
	case PROP_TEXT_NE:
		g_value_set_string (value, wv->text_ne);
		break;
	case PROP_TEXT_SW:
		g_value_set_string (value, wv->text_sw);
		break;
	case PROP_TEXT_SE:
		g_value_set_string (value, wv->text_se);
		break;
	case PROP_TEXT_POS_W:
		g_value_set_double (value, wv->text_pos_w);
		break;
	case PROP_TEXT_POS_E:
		g_value_set_double (value, wv->text_pos_e);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

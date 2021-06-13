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

// ***** GxWaveView.cpp *****
/******************************************************************************
part of guitarix, show a wave with Gtk
******************************************************************************/

#include "GxWaveView.h"
#include <math.h>

#define P_(s) (s)   // FIXME -> gettext

struct _GxWaveViewPrivate
{
	cairo_pattern_t *liveview_image;
	const float *frame;
	int frame_size;
	gchar *text_top_left;
	gchar *text_top_right;
	gchar *text_bottom_left;
	gchar *text_bottom_right;
	double text_pos_left;
	double text_pos_right;
	double m_wave;
	double m_loud;
};

enum {
	PROP_TEXT_TOP_LEFT = 1,
	PROP_TEXT_TOP_RIGHT,
	PROP_TEXT_BOTTOM_LEFT,
	PROP_TEXT_BOTTOM_RIGHT,
	PROP_TEXT_POS_LEFT,
	PROP_TEXT_POS_RIGHT
};

static void gx_wave_view_destroy(GtkWidget*);
static gboolean gx_wave_view_draw(GtkWidget *widget, cairo_t *cr);
static void gx_wave_view_get_preferred_width (GtkWidget *widget, gint *min_width, gint *natural_width);
static void gx_wave_view_get_preferred_height (GtkWidget *widget, gint *min_height, gint *natural_height);
static void gx_wave_view_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gx_wave_view_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);

G_DEFINE_TYPE_WITH_PRIVATE(GxWaveView, gx_wave_view, GTK_TYPE_DRAWING_AREA)

static const int background_width = 282;
static const int background_height = 82;
static const int liveview_x = background_width+1;
static const int liveview_y = background_height+1;

inline double cairo_clr(guint16 clr)
{
	return clr / 65535.0;
}

// set cairo color related to the used skin
static cairo_pattern_t *set_box_color(GtkWidget *wi, cairo_t *cr, int x, int y, gboolean rotate)
{
    GtkStyleContext *style = gtk_widget_get_style_context(wi);
    cairo_push_group(cr);
    cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
    if (rotate) {
	cairo_save(cr);
	cairo_translate(cr, x+background_width/2, y+background_height/2);
	cairo_rotate(cr, M_PI/2);
	cairo_translate(cr, -x-background_height/2, -y-background_width/2);
	gtk_render_background(style, cr, x, y, background_height, background_width);
	cairo_restore(cr);
    } else {
	gtk_render_background(style, cr, x, y, background_width, background_height);
    }
    return cairo_pop_group(cr);
}

static cairo_pattern_t *wave_view_background()
{
    cairo_surface_t *surface = cairo_image_surface_create(
        CAIRO_FORMAT_RGB24, liveview_x, liveview_y);
    cairo_t *crp = cairo_create(surface);
    gx_draw_inset(crp, -1, 0, 284,82, 0, 4);
    gx_draw_glass(crp, 1, 0, 280,82, 0);
    cairo_rectangle(crp, 0, 0, background_width, background_height);
    cairo_clip(crp);

    cairo_pattern_t *pat =
	cairo_pattern_create_radial (-130.4, -270.4, 1.6, -1.4,  -4.4, 300.0);

    cairo_pattern_add_color_stop_rgba (pat, 0, 0.2, 0.2, 0.3, 0);
    cairo_pattern_add_color_stop_rgba (pat, 1, 0.05, 0.05, 0.05, 1);
    cairo_set_source_rgb(crp, 0.05, 0.05, 0.05);
    cairo_rectangle (crp, 0, 0, 282, 82);
    cairo_set_source (crp, pat);
    cairo_fill (crp);
    cairo_pattern_destroy (pat);

	/*
	cairo_set_line_width (cr, 10.0);
	cairo_set_source_rgba (cr, 0, 0, 0,0.4);
	cairo_rectangle (cr, -5, -5, 286, 60);
	cairo_stroke (cr);

	cairo_set_line_width (cr, 1.0);
	cairo_set_source_rgba (cr, 0.1, 0.1, 0.1,0.7);
	cairo_rectangle (cr, -6, -6, 288, 62);
	cairo_stroke (cr);

	cairo_set_line_width (cr, 1.0);
	cairo_set_source_rgba (cr, 0.5, 0.5, 0.5,0.1);
	cairo_rectangle (cr, -12, -12, 302, 74);
	cairo_rectangle (cr, -2, -2, 302, 54);
	cairo_stroke (cr);
	*/

	cairo_set_line_width (crp, 1);
	//cairo_set_source_rgba (crp,1.0, 0.85, 0.0, 0.4);
	//cairo_move_to (crp, 0, 40);
	//cairo_line_to (crp, 280, 40);
	//cairo_stroke (crp);
    
	//cairo_set_source_rgba (crp,0.46, 0.6, 0.31, 0.4);
	//cairo_rectangle (crp, 0, 0, 280.0, 80.0);
	//cairo_stroke (crp);

	float gitter = 0.5;
	for (int i=0; i<28; i++)
	{
		gitter += 10;
		cairo_move_to (crp, gitter-5, 2);
		cairo_line_to (crp, gitter-5, background_height-1);
	}

	gitter = 0.5;
	for (int i=0; i<7; i++)
	{
		gitter += 10;
		cairo_move_to (crp, 2, gitter);
		cairo_line_to (crp, background_width-1, gitter);
	}

	cairo_set_source_rgba (crp,1, 1, 1, 0.1);
	cairo_stroke (crp);

    cairo_destroy(crp);
    pat = cairo_pattern_create_for_surface(surface);
    cairo_surface_destroy(surface);
    return pat;
}

static void draw_text(GtkWidget *widget, cairo_t *cr, gchar *str,
                      int xorg, int yorg, GtkCornerType corner)
{
	if (!str || !*str) {
		return;
	}
	PangoLayout *layout = gtk_widget_create_pango_layout(widget, NULL);
	pango_layout_set_markup(layout, str, -1);
	int width, height;
	pango_layout_get_pixel_size(layout, &width, &height);
	if (corner == GTK_CORNER_BOTTOM_LEFT || corner == GTK_CORNER_BOTTOM_RIGHT) {
		yorg += background_height - height - 3;
	} else {
		yorg += 1;
	}
	gtk_render_layout(gtk_widget_get_style_context(widget), cr, xorg, yorg, layout);
	g_object_unref(layout);
}

static gboolean gx_wave_view_draw (GtkWidget *widget, cairo_t *cr)
{
	g_assert(GX_IS_WAVE_VIEW(widget));
	GxWaveView *waveview = GX_WAVE_VIEW(widget);
	GtkAllocation allocation;
	gtk_widget_get_allocation(widget, &allocation);
	int liveviewx = (allocation.width - liveview_x) / 2 + 1;
	int liveviewy = (allocation.height - liveview_y) / 2 + 1;

    if (!waveview->priv->liveview_image) {
        waveview->priv->liveview_image = wave_view_background();
    }
    cairo_set_source(cr, waveview->priv->liveview_image);
    cairo_paint(cr);
    if (!gtk_widget_get_sensitive(widget)) {
        return FALSE;
    }
    cairo_rectangle(cr, liveviewx-1, liveviewy-1, background_width, background_height);
    cairo_clip(cr);
	cairo_set_source_rgb(cr, 1, 1, 1);
	draw_text(widget, cr, waveview->priv->text_top_left, liveviewx + (int)(background_width * waveview->priv->text_pos_left / 100),
	          liveviewy, GTK_CORNER_TOP_LEFT);
	draw_text(widget, cr, waveview->priv->text_top_right, liveviewx + (int)(background_width * waveview->priv->text_pos_right / 100),
	          liveviewy, GTK_CORNER_TOP_RIGHT);
	draw_text(widget, cr, waveview->priv->text_bottom_left, liveviewx + (int)(background_width * waveview->priv->text_pos_left / 100),
	          liveviewy, GTK_CORNER_BOTTOM_LEFT);
	draw_text(widget, cr, waveview->priv->text_bottom_right, liveviewx + (int)(background_width * waveview->priv->text_pos_right / 100),
	          liveviewy, GTK_CORNER_BOTTOM_RIGHT);

	cairo_pattern_t* linpat = set_box_color(widget, cr, liveviewx, liveviewy, FALSE);
	cairo_move_to (cr, liveviewx+280, liveviewy+40);

	float wave_go = 0;
	float sc = 280.0/waveview->priv->frame_size;
	float sc1 = liveviewx+280+sc;
	float sc2 = liveviewy+40;
	//----- draw the frame
	for (int i = 0; i < waveview->priv->frame_size; i++)
	{
		float x_in = waveview->priv->frame[i];
		cairo_line_to (cr, sc1 - sc*(i+1), sc2 - x_in*waveview->priv->m_wave);
		//cairo_line_to (cr, sc1 - sc*(i+1), sc2 + x_in*waveview->priv->m_wave);
		wave_go = fmax(wave_go, fabs(x_in));
	}

	//----- get the sample, for display the gain value

	float wave_db = log(fabs( wave_go))*6/log(2);
	double xl     = floor(exp(log(1.055)*2.1*wave_db)*waveview->priv->m_loud);

	if (xl > 125.0) xl = 125.0;
	else if (xl < -125.0) xl = -125.0;

	cairo_set_line_width (cr, 1.0);
	cairo_line_to (cr, liveviewx, liveviewy+40);
	cairo_set_source(cr, linpat);
	cairo_close_path (cr);

	cairo_fill_preserve (cr);
	cairo_stroke (cr);

	cairo_pattern_destroy (linpat);
	linpat = set_box_color(widget, cr, liveviewx, liveviewy, TRUE);
	cairo_set_source (cr, linpat);

	//----- draw the gain value
	static const double dashes[] = {5.0, 1.0 };
	cairo_set_dash (cr, dashes, 2, -0.25);
	cairo_set_line_width (cr, 3.0);
	cairo_move_to (cr, liveviewx+140-xl, liveviewy+1);
	cairo_line_to (cr, liveviewx+140+xl, liveviewy+1);
	cairo_move_to (cr, liveviewx+140-xl, liveviewy+80);
	cairo_line_to (cr, liveviewx+140+xl, liveviewy+80);
	//cairo_set_source_rgba (cr,  redline, greenline, 0.2,0.8);
	//cairo_pattern_add_color_stop_rgba (linpat, 0.2, 1, 0.2, 0,0.8);
	//cairo_pattern_add_color_stop_rgba (linpat, 0.8, 0.2, 1, 0.2,0.8);
	cairo_stroke (cr);
	cairo_pattern_destroy (linpat);
	return FALSE;
}

static void gx_wave_view_get_preferred_width (GtkWidget *widget, gint *min_width, gint *natural_width)
{
	g_assert(GX_IS_WAVE_VIEW(widget));
	if (min_width) {
		*min_width = liveview_x;
	}
	if (natural_width) {
		*natural_width = liveview_x;
	}
}

static void gx_wave_view_get_preferred_height (GtkWidget *widget, gint *min_height, gint *natural_height)
{
	g_assert(GX_IS_WAVE_VIEW(widget));
	if (min_height) {
		*min_height = liveview_y;
	}
	if (natural_height) {
		*natural_height = liveview_y;
	}
}

static void gx_wave_view_class_init (GxWaveViewClass *klass)
{
	GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);

	gobject_class->set_property = gx_wave_view_set_property;
	gobject_class->get_property = gx_wave_view_get_property;
	widget_class->destroy = gx_wave_view_destroy;
	widget_class->draw = gx_wave_view_draw;
	widget_class->get_preferred_width = gx_wave_view_get_preferred_width;
	widget_class->get_preferred_height = gx_wave_view_get_preferred_height;

	gtk_widget_class_set_css_name(widget_class, "gx-wave-view");

	g_object_class_install_property (gobject_class,
	                                 PROP_TEXT_TOP_LEFT,
	                                 g_param_spec_string ("text-top-left",
	                                                      P_("Text top left"),
	                                                      P_("Text to be displayed at the top left"),
	                                                      "",
	                                                      GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property (gobject_class,
	                                 PROP_TEXT_TOP_RIGHT,
	                                 g_param_spec_string ("text-top-right",
	                                                      P_("Text top right"),
	                                                      P_("Text to be displayed at the top right"),
	                                                      "",
	                                                      GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property (gobject_class,
	                                 PROP_TEXT_BOTTOM_LEFT,
	                                 g_param_spec_string ("text-bottom-left",
	                                                      P_("Text bottom left"),
	                                                      P_("Text to be displayed at the bottom left"),
	                                                      "",
	                                                      GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property (gobject_class,
	                                 PROP_TEXT_BOTTOM_RIGHT,
	                                 g_param_spec_string ("text-bottom-right",
	                                                      P_("Text bottom right"),
	                                                      P_("Text to be displayed at the bottom right"),
	                                                      "",
	                                                      GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property (gobject_class,
	                                 PROP_TEXT_POS_LEFT,
	                                 g_param_spec_double ("text-pos-left",
	                                                      P_("Left Position"),
	                                                      P_("Text to be displayed at the bottom right"),
	                                                      0, 100, 5,
	                                                      GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property (gobject_class,
	                                 PROP_TEXT_POS_RIGHT,
	                                 g_param_spec_double ("text-pos-right",
	                                                      P_("Right Position"),
	                                                      P_("Text to be displayed at the bottom right"),
	                                                      0, 100, 70,
	                                                      GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
}

static void gx_wave_view_init(GxWaveView *waveview)
{
	waveview->priv = (GxWaveViewPrivate*)gx_wave_view_get_instance_private(waveview);
	waveview->priv->liveview_image = NULL;
	waveview->priv->frame = NULL;
	waveview->priv->frame_size = 0;
	waveview->priv->text_top_left = NULL;
	waveview->priv->text_top_right = NULL;
	waveview->priv->text_bottom_left = NULL;
	waveview->priv->text_bottom_right = NULL;
	waveview->priv->text_pos_left = 5;
	waveview->priv->text_pos_right = 70;
	waveview->priv->m_wave = 75;
	waveview->priv->m_loud = 150;
	gtk_widget_set_size_request(GTK_WIDGET(waveview), liveview_x, liveview_y);
}

static void gx_wave_view_destroy (GtkWidget *obj)
{
	GxWaveView *waveview = GX_WAVE_VIEW(obj);
	if (waveview->priv->liveview_image) {
		cairo_pattern_destroy(waveview->priv->liveview_image);
		waveview->priv->liveview_image = NULL;
	}
	GTK_WIDGET_CLASS(gx_wave_view_parent_class)->destroy(obj);
}

GtkWidget* gx_wave_view_new()
{
	GtkWidget* widget = GTK_WIDGET(g_object_new(GX_TYPE_WAVE_VIEW, NULL));
	return widget;
}

void gx_wave_view_set_frame(GxWaveView *waveview, const float *frame, int frame_size)
{
	g_assert(GX_IS_WAVE_VIEW(waveview));
	waveview->priv->frame = frame;
	waveview->priv->frame_size = frame_size;
	gtk_widget_queue_draw(GTK_WIDGET(waveview));
}

void gx_wave_view_set_multiplicator(GxWaveView *waveview, double m_wave, double m_loud)
{
	g_assert(GX_IS_WAVE_VIEW(waveview));
	waveview->priv->m_wave = m_wave;
	waveview->priv->m_loud = m_loud;
}

void gx_wave_view_set_text(GxWaveView *waveview, const gchar *text, GtkCornerType pos)
{
	char **f;
	const char *p;
	g_assert(GX_IS_WAVE_VIEW(waveview));
	switch (pos) {
	case GTK_CORNER_TOP_LEFT:
		f = &waveview->priv->text_top_left;
		p = "text-top-left";
		break;
	case GTK_CORNER_TOP_RIGHT:
		f = &waveview->priv->text_top_right;
		p = "text-top-right";
		break;
	case GTK_CORNER_BOTTOM_LEFT:
		f = &waveview->priv->text_bottom_left;
		p = "text-bottom-left";
		break;
	case GTK_CORNER_BOTTOM_RIGHT:
		f = &waveview->priv->text_bottom_right;
		p = "text-bottom-right";
		break;
	default:
		g_assert(FALSE);
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
	case PROP_TEXT_TOP_LEFT:
		gx_wave_view_set_text(wv, g_value_get_string(value), GTK_CORNER_TOP_LEFT);
		break;
	case PROP_TEXT_TOP_RIGHT:
		gx_wave_view_set_text(wv, g_value_get_string(value), GTK_CORNER_TOP_RIGHT);
		break;
	case PROP_TEXT_BOTTOM_LEFT:
		gx_wave_view_set_text(wv, g_value_get_string(value), GTK_CORNER_BOTTOM_LEFT);
		break;
	case PROP_TEXT_BOTTOM_RIGHT:
		gx_wave_view_set_text(wv, g_value_get_string(value), GTK_CORNER_BOTTOM_RIGHT);
		break;
	case PROP_TEXT_POS_LEFT:
		wv->priv->text_pos_left = g_value_get_double(value);
		g_object_notify(object, "text-pos-left");
		break;
	case PROP_TEXT_POS_RIGHT:
		wv->priv->text_pos_right = g_value_get_double(value);
		g_object_notify(object, "text-pos-right");
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
	case PROP_TEXT_TOP_LEFT:
		g_value_set_string (value, wv->priv->text_top_left);
		break;
	case PROP_TEXT_TOP_RIGHT:
		g_value_set_string (value, wv->priv->text_top_right);
		break;
	case PROP_TEXT_BOTTOM_LEFT:
		g_value_set_string (value, wv->priv->text_bottom_left);
		break;
	case PROP_TEXT_BOTTOM_RIGHT:
		g_value_set_string (value, wv->priv->text_bottom_right);
		break;
	case PROP_TEXT_POS_LEFT:
		g_value_set_double (value, wv->priv->text_pos_left);
		break;
	case PROP_TEXT_POS_RIGHT:
		g_value_set_double (value, wv->priv->text_pos_right);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

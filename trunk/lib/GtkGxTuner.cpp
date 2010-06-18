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

#include "GtkGxTuner.h"
#include <gtk/gtkprivate.h>
#include <math.h>

#define P_(s) (s)   // FIXME -> gettext

enum {
	PROP_FREQ = 1,
};

static gboolean gtk_tuner_expose (GtkWidget *widget, GdkEventExpose *event);
static void draw_background(cairo_surface_t *surface_tuner);
static void gtk_gx_tuner_class_init (GtkGxTunerClass *klass);
static void gtk_gx_tuner_base_class_finalize(GtkGxTunerClass *klass);
static void gtk_gx_tuner_init(GtkGxTuner *tuner);
static void gtk_gx_tuner_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gtk_gx_tuner_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);

static const int tuner_width = 102;
static const int tuner_height = 92;
static const double rect_width = 100;
static const double rect_height = 60;

static const double dashes[] = {
	0.0,					/* ink  */
	rect_height,			/* skip */
	10.0,					/* ink  */
	10.0					/* skip */
};

static const double dash_ind[] = {
	0,						/* ink  */
	5,						/* skip */
	rect_height-20,			/* ink  */
	100.0					/* skip */
};

GType gtk_gx_tuner_get_type(void)
{
	static GType tuner_type = 0;

	if (!tuner_type) {
		const GTypeInfo tuner_info = {
			sizeof (GtkGxTunerClass),
			NULL,				/* base_class_init */
			(GBaseFinalizeFunc) gtk_gx_tuner_base_class_finalize,
			(GClassInitFunc) gtk_gx_tuner_class_init,
			NULL,				/* class_finalize */
			NULL,				/* class_data */
			sizeof (GtkGxTunerClass),
			0,					/* n_preallocs */
			(GInstanceInitFunc) gtk_gx_tuner_init,
			NULL,				/* value_table */
		};
		tuner_type = g_type_register_static(
			GTK_TYPE_DRAWING_AREA, "GtkGxTuner", &tuner_info, (GTypeFlags)0);
	}
	return tuner_type;
}

static void gtk_gx_tuner_class_init(GtkGxTunerClass *klass)
{
	GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
	GTK_WIDGET_CLASS(klass)->expose_event = gtk_tuner_expose;
	gobject_class->set_property = gtk_gx_tuner_set_property;
	gobject_class->get_property = gtk_gx_tuner_get_property;
	g_object_class_install_property(
		gobject_class, PROP_FREQ, g_param_spec_double (
			"freq", P_("Frequency"),
			P_("The frequency for which tuning is displayed"),
			0.0, 1000.0, 0.0, GParamFlags(GTK_PARAM_READWRITE)));
	klass->surface_tuner = cairo_image_surface_create(
		CAIRO_FORMAT_ARGB32, tuner_width, tuner_height);
	g_assert(klass->surface_tuner != NULL);
	draw_background(klass->surface_tuner);
}

static void gtk_gx_tuner_base_class_finalize(GtkGxTunerClass *klass)
{
	if (G_IS_OBJECT(klass->surface_tuner)) {
		g_object_unref(klass->surface_tuner);
	}
}

static void gtk_gx_tuner_init (GtkGxTuner *tuner)
{
	GtkWidget *widget = GTK_WIDGET(tuner);
	widget->requisition.width = tuner_width;
	widget->requisition.height = tuner_height;
}

void gtk_gx_tuner_set_freq(GtkGxTuner *tuner, double freq)
{
	g_assert(GTK_IS_GX_TUNER(tuner));
	tuner->freq = freq;
	gtk_widget_queue_draw(GTK_WIDGET(tuner));
	g_object_notify(G_OBJECT(tuner), "freq");
}

GtkWidget *gtk_gx_tuner_new(void)
{
	return (GtkWidget*)g_object_new(GTK_TYPE_GX_TUNER, NULL);
}

static void gtk_gx_tuner_set_property(GObject *object, guint prop_id,
                                      const GValue *value, GParamSpec *pspec)
{
	GtkGxTuner *tuner = GTK_GX_TUNER(object);

	switch(prop_id) {
	case PROP_FREQ:
		gtk_gx_tuner_set_freq(tuner, g_value_get_double(value));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void gtk_gx_tuner_get_property(GObject *object, guint prop_id,
                                      GValue *value, GParamSpec *pspec)
{
	GtkGxTuner *tuner = GTK_GX_TUNER(object);

	switch(prop_id) {
	case PROP_FREQ:
		g_value_set_double(value, tuner->freq);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static gboolean gtk_tuner_expose (GtkWidget *widget, GdkEventExpose *event)
{
	static const char* note[12] = {"A ","A#","B ","C ","C#","D ","D#","E ","F ","F#","G ","G#"};
	GtkGxTuner *tuner = GTK_GX_TUNER(widget);
	cairo_t *cr;

	double x0      = (widget->allocation.width - 100) * 0.5;
	double y0      = (widget->allocation.height - 90) * 0.5;

	cr = gdk_cairo_create(widget->window);
	cairo_set_source_surface(cr, GTK_GX_TUNER_CLASS(GTK_OBJECT_GET_CLASS(widget))->surface_tuner, x0, y0);
	cairo_paint (cr);
	if (!tuner->freq) {
		cairo_destroy(cr);
		return FALSE;
	}
	float fvis = 12 * log2f(tuner->freq/440.0);
	int vis = round(fvis);
	float scale = (fvis-vis) / 2;
	vis = vis % 12;
	if (vis < 0) {
		vis += 12;
	}

	// display note
	cairo_set_source_rgba(cr, scale*scale*4, 1-(scale*scale*4), 0.2,1-(scale*scale*4));
	cairo_set_font_size(cr, 18.0);
	cairo_move_to(cr,x0+50 -9 , y0+30 +9 );
	cairo_show_text(cr, note[vis]);

	// display frequency
	char s[10];
	snprintf(s, sizeof(s), "%.0f Hz", tuner->freq);
	cairo_set_source_rgba (cr, 0.8, 0.8, 0.2,0.6);
	cairo_set_font_size (cr, 8.0);
	cairo_text_extents_t ex;
	cairo_text_extents(cr, s, &ex);
	cairo_move_to (cr, x0+90-ex.width, y0+58);
	cairo_show_text(cr, s);

	// indicator (line)
	cairo_move_to(cr,x0+50, y0+rect_height-5);
	cairo_set_dash (cr, dash_ind, sizeof(dash_ind)/sizeof(dash_ind[0]), 0);
	cairo_line_to(cr, (scale*2*rect_width)+x0+50, y0+(scale*scale*30)+2);
	cairo_set_source_rgb(cr,  0.5, 0.1, 0.1);
	cairo_stroke(cr);

	cairo_destroy(cr);

	return FALSE;
}

/*
** paint tuner background picture (the non-changing parts)
*/
static void draw_background(cairo_surface_t *surface)
{
	cairo_t *cr;

	double x0      = 0;
	double y0      = 0;

	cr = cairo_create(surface);

	// bottom part of gauge
	cairo_rectangle (cr, x0,y0+60,rect_width+1,30);
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_fill (cr);
	cairo_set_source_rgb(cr,  0.2, 0.2, 0.2);
	cairo_set_line_width(cr, 5.0);
	cairo_move_to(cr,x0+2, y0+63);
	cairo_line_to(cr, x0+99, y0+63);
	cairo_stroke(cr);

	// upper part
	cairo_rectangle (cr, x0-1,y0-1,rect_width+2,rect_height+2);
	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_fill (cr);

	cairo_pattern_t*pat =
		cairo_pattern_create_radial (-50, y0, 5,rect_width-10,  rect_height, 20.0);
	cairo_pattern_add_color_stop_rgb (pat, 0, 1, 1, 1);
	cairo_pattern_add_color_stop_rgb (pat, 0.3, 0.4, 0.4, 0.4);
	cairo_pattern_add_color_stop_rgb (pat, 0.6, 0.05, 0.05, 0.05);
	cairo_pattern_add_color_stop_rgb (pat, 1, 0.0, 0.0, 0.0);
	cairo_set_source (cr, pat);
	cairo_rectangle (cr, x0+2,y0+2,rect_width-3,rect_height-3);
	cairo_fill (cr);

	cairo_set_source_rgb(cr,  0.2, 0.2, 0.2);
	cairo_set_line_width(cr, 2.0);
	cairo_move_to(cr,x0+98, y0+3);
	cairo_line_to(cr, x0+98, y0+64);
	cairo_stroke(cr);

	cairo_set_source_rgb(cr,  0.1, 0.1, 0.1);
	cairo_set_line_width(cr, 2.0);
	cairo_move_to(cr,x0+3, y0+64);
	cairo_line_to(cr, x0+3, y0+3);
	cairo_line_to(cr, x0+98, y0+3);
	cairo_stroke(cr);

	pat = cairo_pattern_create_linear (x0+50, y0,x0, y0);
	cairo_pattern_set_extend(pat, CAIRO_EXTEND_REFLECT);
	cairo_pattern_add_color_stop_rgb (pat, 0, 0.1, 0.8, 0.1);
	cairo_pattern_add_color_stop_rgb (pat, 1, 1, 0.1, 0.1);
	cairo_set_source (cr, pat);

	// division scale
	cairo_set_dash (cr, dashes, sizeof (dashes)/sizeof(dashes[0]), 100.0);
	cairo_set_line_width(cr, 3.0);
	for (int i = -5; i < 6; i++) {
		cairo_move_to(cr,x0+50, y0+rect_height-5);
		cairo_line_to(cr, (((i*0.08))*rect_width)+x0+50, y0+(((i*0.1*i*0.1))*30)+2);
	}
	cairo_stroke(cr);

	cairo_set_source_rgb(cr,  0.1, 1, 0.1);
	cairo_move_to(cr,x0+50, y0+rect_height-5);
	cairo_line_to(cr, x0+50, y0+2);
	cairo_stroke(cr);

	// indicator shaft (circle)
	cairo_set_dash (cr, 0, 0, 0);
	cairo_move_to(cr, x0+50, y0+rect_height-5);
	cairo_arc(cr, x0+50, y0+rect_height-5, 2.0, 0, 2*M_PI);
	cairo_set_source_rgb(cr,  0.5, 0.1, 0.1);
	cairo_set_line_width(cr, 2.0);
	cairo_stroke(cr);

	cairo_destroy(cr);
}

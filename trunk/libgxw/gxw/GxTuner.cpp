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

#include "GxTuner.h"
#include <math.h>

#define P_(s) (s)   // FIXME -> gettext

struct _GxTunerPrivate
{
	double freq;
	double reference_pitch;
	double scale;
	cairo_surface_t *surface_tuner;
};

enum {
	PROP_FREQ = 1,
	PROP_REFERENCE_PITCH = 2,
	PROP_SCALE = 3
};

static gboolean gx_tuner_draw (GtkWidget *widget, cairo_t *cr);
static void draw_background(GxTuner *tuner);
static void gx_tuner_class_init (GxTunerClass *klass);
static void gx_tuner_init(GxTuner *tuner);
static void gx_tuner_finalize(GObject *object);
static void gx_tuner_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gx_tuner_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);

static const int tuner_width = 100;
static const int tuner_height = 90;
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

G_DEFINE_TYPE_WITH_PRIVATE(GxTuner, gx_tuner, GTK_TYPE_DRAWING_AREA);

#define GX_TUNER_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), GX_TYPE_TUNER, GxTunerPrivate))

static void gx_tuner_class_init(GxTunerClass *klass)
{
	GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);
	widget_class->draw = gx_tuner_draw;
	gobject_class->finalize = gx_tuner_finalize;
	gobject_class->set_property = gx_tuner_set_property;
	gobject_class->get_property = gx_tuner_get_property;

	gtk_widget_class_set_css_name(widget_class, "gx-tuner");

	g_object_class_install_property(
		gobject_class, PROP_FREQ, g_param_spec_double (
			"freq", P_("Frequency"),
			P_("The frequency for which tuning is displayed"),
			0.0, 1000.0, 0.0, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_REFERENCE_PITCH, g_param_spec_double (
			"reference-pitch", P_("Reference Pitch"),
			P_("The frequency for which tuning is displayed"),
			400.0, 500.0, 440.0, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_SCALE, g_param_spec_double (
			"scale", P_("Image Scale"),
			P_("scale the tuner area to make it bigger or smaller"),
			0.5, 10.0, 1.0, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
}

static void tuner_surface_init(GxTuner *tuner)
{
	tuner->priv->surface_tuner = cairo_image_surface_create(
		CAIRO_FORMAT_ARGB32,
		tuner_width * tuner->priv->scale, tuner_height * tuner->priv->scale);
	g_assert(cairo_surface_status(tuner->priv->surface_tuner) == CAIRO_STATUS_SUCCESS);
	draw_background(tuner);
}

static void tuner_surface_finalize(GxTuner *tuner)
{
	if (tuner->priv->surface_tuner) {
		cairo_surface_destroy(tuner->priv->surface_tuner);
		tuner->priv->surface_tuner = NULL;
	}
}

static void gx_tuner_init (GxTuner *tuner)
{
	g_assert(GX_IS_TUNER(tuner));
	tuner->priv = GX_TUNER_GET_PRIVATE(tuner);
	tuner->priv->freq = 0;
	tuner->priv->reference_pitch = 440.0;
	tuner->priv->scale = 1.0;
	tuner_surface_init(tuner);
	gtk_widget_set_size_request(GTK_WIDGET(tuner), tuner_width * tuner->priv->scale,
	                            tuner_height * tuner->priv->scale);
}

static void gx_tuner_finalize(GObject *object)
{
	tuner_surface_finalize(GX_TUNER(object));
	G_OBJECT_CLASS(gx_tuner_parent_class)->finalize(object);
}

void gx_tuner_set_freq(GxTuner *tuner, double freq)
{
	g_assert(GX_IS_TUNER(tuner));
	tuner->priv->freq = freq;
	gtk_widget_queue_draw(GTK_WIDGET(tuner));
	g_object_notify(G_OBJECT(tuner), "freq");
}

double gx_tuner_get_freq(GxTuner *tuner)
{
	g_assert(GX_IS_TUNER(tuner));
	return tuner->priv->freq;
}

void gx_tuner_set_reference_pitch(GxTuner *tuner, double reference_pitch)
{
	g_assert(GX_IS_TUNER(tuner));
	tuner->priv->reference_pitch = reference_pitch;
	gtk_widget_queue_draw(GTK_WIDGET(tuner));
	g_object_notify(G_OBJECT(tuner), "reference-pitch");
}

double gx_tuner_get_reference_pitch(GxTuner *tuner)
{
	g_assert(GX_IS_TUNER(tuner));
	return tuner->priv->reference_pitch;
}

void gx_tuner_set_scale(GxTuner *tuner, double scale)
{
	g_assert(GX_IS_TUNER(tuner));
	tuner_surface_finalize(tuner);
	tuner->priv->scale = scale;
	gtk_widget_set_size_request(GTK_WIDGET(tuner), tuner_width * tuner->priv->scale,
	                            tuner_height * tuner->priv->scale);
	tuner_surface_init(tuner);
	gtk_widget_queue_resize(GTK_WIDGET(tuner));
	g_object_notify(G_OBJECT(tuner), "scale");
}

double gx_tuner_get_scale(GxTuner *tuner)
{
	g_assert(GX_IS_TUNER(tuner));
	return tuner->priv->scale;
}

GtkWidget *gx_tuner_new(void)
{
	return (GtkWidget*)g_object_new(GX_TYPE_TUNER, NULL);
}

static void gx_tuner_set_property(GObject *object, guint prop_id,
                                      const GValue *value, GParamSpec *pspec)
{
	GxTuner *tuner = GX_TUNER(object);

	switch(prop_id) {
	case PROP_FREQ:
		gx_tuner_set_freq(tuner, g_value_get_double(value));
		break;
	case PROP_REFERENCE_PITCH:
		gx_tuner_set_reference_pitch(tuner, g_value_get_double(value));
		break;
	case PROP_SCALE:
		gx_tuner_set_scale(tuner, g_value_get_double(value));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void gx_tuner_get_property(GObject *object, guint prop_id,
                                      GValue *value, GParamSpec *pspec)
{
	GxTuner *tuner = GX_TUNER(object);

	switch(prop_id) {
	case PROP_FREQ:
		g_value_set_double(value, tuner->priv->freq);
		break;
	case PROP_REFERENCE_PITCH:
		g_value_set_double(value, tuner->priv->reference_pitch);
		break;
	case PROP_SCALE:
		g_value_set_double(value, tuner->priv->scale);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static gboolean gx_tuner_draw (GtkWidget *widget, cairo_t *cr)
{
	static const char* note[12] = {"F#","G ","G#","A ","A#","B ","C ","C#","D ","D#","E ","F "};
	static const char* octave[] = {"0","1","2","3","4","5"," "};
	GxTuner *tuner = GX_TUNER(widget);
	GtkAllocation allocation;
	gtk_widget_get_allocation(widget, &allocation);

	double x0      = (allocation.width - 100 * tuner->priv->scale) * 0.5;
	double y0      = (allocation.height - 90 * tuner->priv->scale) * 0.5;

	cairo_set_source_surface(cr, tuner->priv->surface_tuner, x0, y0);
	cairo_scale(cr, tuner->priv->scale, tuner->priv->scale);
	cairo_paint (cr);

	float scale = -0.5;
	if (tuner->priv->freq) {
		float fvis = 12 * (log2f(tuner->priv->freq/tuner->priv->reference_pitch) + 4) + 3;
		float fvisr = round(fvis);
		int vis = fvisr;
		int indicate_oc = round(fvisr/12);
		const int octsz = sizeof(octave) / sizeof(octave[0]);
		if (indicate_oc < 0 || indicate_oc >= octsz) {
			// just safety, should not happen with current parameters
			// (pitch tracker output 23 .. 999 Hz)
			indicate_oc = octsz - 1;
		}
		scale = (fvis-vis) / 2;
		vis = vis % 12;
		if (vis < 0) {
			vis += 12;
		}

		// display note
		float pitch_add = fabsf(tuner->priv->reference_pitch - 440.00);
		cairo_set_source_rgba(cr, fabsf(scale)*2+(pitch_add*0.1), 1-(scale*scale*4+(pitch_add*0.1)), 0.2,1-(fabsf(scale)*2));
		cairo_set_font_size(cr, 18.0);
		cairo_move_to(cr,x0+50 -9 , y0+30 +9 );
		cairo_show_text(cr, note[vis]);
        cairo_set_font_size(cr, 8.0);
        cairo_move_to(cr,x0+54  , y0+30 +16 );
        cairo_show_text(cr, octave[indicate_oc]);
	}

	// display frequency
	char s[10];
	snprintf(s, sizeof(s), "%.0f Hz", tuner->priv->freq);
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

	return FALSE;
}

/*
** paint tuner background picture (the non-changing parts)
*/
static void draw_background(GxTuner *tuner)
{
	cairo_t *cr;

	double x0      = 0;
	double y0      = 0;

	cr = cairo_create(tuner->priv->surface_tuner);
	cairo_scale(cr, tuner->priv->scale, tuner->priv->scale);

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
	cairo_set_dash (cr, dash_ind, sizeof(dash_ind)/sizeof(dash_ind[0]), 0);
	//cairo_set_dash (cr, 0, 0, 0); // (for full circle)
	cairo_move_to(cr, x0+50, y0+rect_height-5);
	cairo_arc(cr, x0+50, y0+rect_height-5, 2.0, 0, 2*M_PI);
	cairo_set_source_rgb(cr,  0.5, 0.1, 0.1);
	cairo_set_line_width(cr, 2.0);
	cairo_stroke(cr);

	cairo_destroy(cr);
}

cairo_surface_t *gx_tuner_get_surface_tuner(GxTuner *tuner)
{
	return tuner->priv->surface_tuner;
}

void gx_tuner_set_surface_tuner(GxTuner *tuner, cairo_surface_t *surface_tuner)
{
	if (tuner->priv->surface_tuner) {
		cairo_surface_destroy(tuner->priv->surface_tuner);
	}
	tuner->priv->surface_tuner = surface_tuner;
}

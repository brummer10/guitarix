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

#include "GxRackTuner.h"

#include <math.h>
#include <string.h>

#define I_(x)  x  //FIXME whats this??
#define P_(s) (s)   // FIXME -> gettext

struct _GxRackTunerPrivate
{
	// properties
	double   scale_lim;
	double   speed;
	gboolean display_flat;
	gboolean streaming;
	gint     timestep;
	gint     in_limit_timestep;
	gint     n_targets;
	gint     targets[RACKTUNER_MAXTARGETS];
	gint     temperament;
	// state
	double   pos; // led lighted position
	gboolean in_limit;
	gint     indicate_oc;
	gint     vis;
	double   scale_val;
	const char **note;
	double   last_freq;
	guint    freqpoll_id;
	guint    in_limit_id;
	gint     target_oc;
	gint     target_note;
	gint     target_temperament;
	gint     target_adjust;
	gint     strng;   // number of current string (1 == string with highest pitch)
	// caculated layout
	gint    led_count;
	gint    width;
	gint    padding;
};

enum {
	PROP_FREQ = 1,
	PROP_SCALE_LIM,
	PROP_SPEED,
	PROP_DISPLAY_FLAT,
	PROP_STREAMING,
	PROP_TIMESTEP,
	PROP_LIMIT_TIMESTEP,
	PROP_TEMPERAMENT
};

enum {
	FREQUENCY_POLL,
	POLL_STATUS_CHANGED,
	LAST_SIGNAL
};

static guint signals[LAST_SIGNAL];

static void gx_rack_tuner_class_init (GxRackTunerClass *klass);
static void gx_rack_tuner_init(GxRackTuner *tuner);
static void gx_rack_tuner_destroy(GtkWidget *object);
static void gx_rack_tuner_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gx_rack_tuner_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static void gx_rack_tuner_get_preferred_width(GtkWidget *widget, gint *min_width, gint *natural_width);
static void gx_rack_tuner_get_preferred_height(GtkWidget *widget, gint *min_height, gint *natural_height);
static void gx_rack_tuner_size_request(GtkWidget *widget, gint *width, gint *height);
static void gx_rack_tuner_remove_handler(GxRackTuner *tuner);

static const int led_spacing = 7;
static const int led_width = 3;
static const int led_y0 = 5;
static const int led_height = 5;
static const int pad = 4;
static const int tri_y0 = 25;  // center line of triangles
static const int min_led = 32;

G_DEFINE_TYPE_WITH_PRIVATE(GxRackTuner, gx_rack_tuner, GX_TYPE_TUNER);

#define GX_RACK_TUNER_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), GX_TYPE_RACK_TUNER, GxRackTunerPrivate))

static void gx_rack_tuner_map(GtkWidget*);
static void gx_rack_tuner_unmap(GtkWidget*);
static void gx_rack_tuner_state_changed(GtkWidget*, GtkStateType);
static gboolean gx_rack_tuner_freq_poll_handler(gpointer);
static gboolean gx_rack_tuner_configure_event(GtkWidget*, GdkEventConfigure*);
static gboolean gx_rack_tuner_draw(GtkWidget*, cairo_t*);

static void gx_rack_tuner_class_init(GxRackTunerClass *klass)
{
	GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
	GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);
	gobject_class->set_property = gx_rack_tuner_set_property;
	gobject_class->get_property = gx_rack_tuner_get_property;
	widget_class->destroy = gx_rack_tuner_destroy;
	widget_class->draw = gx_rack_tuner_draw;
	widget_class->get_preferred_width = gx_rack_tuner_get_preferred_width;
	widget_class->get_preferred_height = gx_rack_tuner_get_preferred_height;
	widget_class->map = gx_rack_tuner_map;
	widget_class->unmap = gx_rack_tuner_unmap;
	widget_class->state_changed = gx_rack_tuner_state_changed;
	widget_class->configure_event = gx_rack_tuner_configure_event;
	klass->frequency_poll = 0;
	klass->poll_status_changed = 0;

	// properties
	g_object_class_install_property(
		gobject_class, PROP_FREQ, g_param_spec_double (
			"freq", P_("Frequency"),
			P_("The frequency for which tuning is displayed"),
			0.0, 1000.0, 0.0, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_SCALE_LIM, g_param_spec_double (
			"scale-lim", P_("Scale Limit"),
			P_("The threshold for display of tune match (0.01 = 1 cent)"),
			0.005, 0.3, 0.03, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_SPEED, g_param_spec_double (
			"speed", P_("Streaming Speed"),
			P_("Speed of streaming mode display (led positions per msec)"),
			0.0001, 1.0, 0.15, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_DISPLAY_FLAT, g_param_spec_boolean (
			"display-flat", P_("Display Flat Notes"),
			P_("select flat enharmonic equivalents instead of sharp"),
			FALSE, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_STREAMING, g_param_spec_boolean (
			"streaming", P_("Streaming"),
			P_("use streaming display"),
			FALSE, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_TIMESTEP, g_param_spec_int (
			"timestep", P_("Time Step"),
			P_("time interval in msec for refreshing the streaming display"),
			1, 1000, 50, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_LIMIT_TIMESTEP, g_param_spec_int (
			"limit-timestep", P_("In-Limit Time Step"),
			P_("time interval in msec for refreshing the streaming match display"),
			1, 100, 8, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_TEMPERAMENT, g_param_spec_int (
			"temperament", P_("Temperament"),
			P_("Division of the octave into temperament steps"),
			1, 1000, 50, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	/* new signals */
	signals[FREQUENCY_POLL] =
		g_signal_new(I_("frequency-poll"),
			     G_OBJECT_CLASS_TYPE (klass),
		             GSignalFlags(G_SIGNAL_RUN_LAST),
		             G_STRUCT_OFFSET (GxRackTunerClass, frequency_poll),
		             NULL, NULL,
		             g_cclosure_marshal_VOID__VOID,
		             G_TYPE_NONE, 0);
	signals[POLL_STATUS_CHANGED] =
		g_signal_new(I_("poll-status-changed"),
			     G_OBJECT_CLASS_TYPE (klass),
		             GSignalFlags(G_SIGNAL_RUN_LAST),
		             G_STRUCT_OFFSET (GxRackTunerClass, poll_status_changed),
		             NULL, NULL,
		             g_cclosure_marshal_VOID__BOOLEAN,
		             G_TYPE_NONE, 1, G_TYPE_BOOLEAN);
}

static const char *note_sharp[] = {"A","A#","B","C","C#","D","D#","E","F","F#","G","G#"};
static const char *note_flat[] = {"A","Bb","B","C","Db","D","Eb","E","F","Gb","G","Ab"};
static const char* note_19[19] = {"A","A♯","B♭","B","B♯","C","C♯","D♭","D","D♯","E♭","E","E♯","F","F♯","G♭","G","G♯","A♭"};
static const char* note_24[24] = {"A","A¼♯","A♯","A¾♯","B","B¼♯","C","C¼♯","C♯","C¾♯","D","D¼♯","D♯","D¾♯","E","E¼♯","F","F¼♯","F♯","F¾♯","G","G¼♯","G♯","G¾♯"};
static const char* note_31[31] = {"A","B♭♭","A♯","B♭","A♯♯","B","C♭","B♯","C ","D♭♭","C♯","D♭","C♯♯","D","E♭♭","D♯","E♭","D♯♯","E","F♭","E♯","F","G♭♭","F♯","G♭","F♯♯","G","A♭♭","G♯","A♭","G♯♯"};
static const char* note_53[53] = {"la","laa","lo","law","ta","teh","te","tu","tuh","ti","tih","to","taw","da","do","di","daw","ro","rih","ra","ru","ruh","reh","re ","ri","raw","ma","meh","me","mu","muh","mi","maa","mo","maw","fe","fa","fih","fu","fuh","fi","se","suh","su","sih","sol","si","saw","lo","leh","le","lu","luh"};
static const char *octave[] = {"0","1","2","3","4","5"," "};

static void gx_rack_tuner_init (GxRackTuner *tuner)
{
	g_assert(GX_IS_RACK_TUNER(tuner));
	tuner->priv = GX_RACK_TUNER_GET_PRIVATE(tuner);
	tuner->priv->scale_lim = 0.03;
	tuner->priv->speed = 0.15;
	tuner->priv->display_flat = FALSE;
	tuner->priv->streaming = FALSE;
	tuner->priv->timestep = 50;
	tuner->priv->in_limit_timestep = 8;
	tuner->priv->n_targets = 0;
	tuner->priv->temperament = 0;
	// state
	tuner->priv->pos = 0.0;
	tuner->priv->in_limit = FALSE;
	tuner->priv->indicate_oc = 0;
	tuner->priv->vis = 0;
	tuner->priv->scale_val = 0.0;
	tuner->priv->note = note_sharp;
	tuner->priv->last_freq = 0.0;
	tuner->priv->freqpoll_id = 0;
	tuner->priv->in_limit_id = 0;
	tuner->priv->target_oc = 0;
	tuner->priv->target_note = 0;
	tuner->priv->target_temperament = 12;
	tuner->priv->target_adjust = 3;
	tuner->priv->strng = 0;
	// caculated layout
	tuner->priv->led_count = 0;
	tuner->priv->width = 0;
	tuner->priv->padding = 0;
}

static void gx_rack_tuner_destroy(GtkWidget *object)
{
	gx_rack_tuner_remove_handler(GX_RACK_TUNER(object));
	GTK_WIDGET_CLASS(gx_rack_tuner_parent_class)->destroy(object);
}

void gx_rack_tuner_set_freq(GxRackTuner *tuner, double freq)
{
	g_assert(GX_IS_RACK_TUNER(tuner));
	gx_tuner_set_freq(&tuner->parent, freq);
	g_object_notify(G_OBJECT(tuner), "freq");
}


void gx_rack_tuner_set_scale_lim(GxRackTuner *tuner, double scale_lim)
{
	g_assert(GX_IS_RACK_TUNER(tuner));
	tuner->priv->scale_lim = scale_lim;
	g_object_notify(G_OBJECT(tuner), "scale_lim");
}

double gx_rack_tuner_get_scale_lim(GxRackTuner *tuner)
{
	g_assert(GX_IS_TUNER(tuner));
	return tuner->priv->scale_lim;
}

void gx_rack_tuner_set_speed(GxRackTuner *tuner, double speed)
{
	g_assert(GX_IS_RACK_TUNER(tuner));
	tuner->priv->speed = speed;
	g_object_notify(G_OBJECT(tuner), "speed");
}

double gx_rack_tuner_get_speed(GxRackTuner *tuner)
{
	g_assert(GX_IS_TUNER(tuner));
	return tuner->priv->speed;
}

void gx_rack_tuner_set_streaming(GxRackTuner *tuner, gboolean streaming)
{
	g_assert(GX_IS_RACK_TUNER(tuner));
	tuner->priv->streaming = streaming;
	g_object_notify(G_OBJECT(tuner), "streaming");
}

gboolean gx_rack_tuner_get_streaming(GxRackTuner *tuner)
{
	g_assert(GX_IS_TUNER(tuner));
	return tuner->priv->streaming;
}

void gx_rack_tuner_set_display_flat(GxRackTuner *tuner, gboolean display_flat)
{
	g_assert(GX_IS_RACK_TUNER(tuner));
	tuner->priv->display_flat = display_flat;
    if (tuner->priv->temperament == 0) {
        if (display_flat) {
            tuner->priv->note = note_flat;
        } else {
            tuner->priv->note = note_sharp;
        }
	}
	g_object_notify(G_OBJECT(tuner), "display_flat");
}

gboolean gx_rack_tuner_get_display_flat(GxRackTuner *tuner)
{
	g_assert(GX_IS_TUNER(tuner));
	return tuner->priv->display_flat;
}

void gx_rack_tuner_set_timestep(GxRackTuner *tuner, gint timestep)
{
	g_assert(GX_IS_RACK_TUNER(tuner));
	tuner->priv->timestep = timestep;
	g_object_notify(G_OBJECT(tuner), "timestep");
}

gint gx_rack_tuner_get_timestep(GxRackTuner *tuner)
{
	g_assert(GX_IS_TUNER(tuner));
	return tuner->priv->timestep;
}

void gx_rack_tuner_set_limit_timestep(GxRackTuner *tuner, gint in_limit_timestep)
{
	g_assert(GX_IS_RACK_TUNER(tuner));
	tuner->priv->in_limit_timestep = in_limit_timestep;
	g_object_notify(G_OBJECT(tuner), "limit_timestep");
}

gint gx_rack_tuner_get_limit_timestep(GxRackTuner *tuner)
{
	g_assert(GX_IS_TUNER(tuner));
	return tuner->priv->in_limit_timestep;
}

void gx_rack_tuner_set_temperament(GxRackTuner *tuner, gint temperament)
{
    g_assert(GX_IS_RACK_TUNER(tuner));
    tuner->priv->temperament = temperament;
    switch(tuner->priv->temperament) {
    case  0:
        tuner->priv->target_temperament = 12;
        tuner->priv->target_adjust = 3;
        if (tuner->priv->display_flat) {
            tuner->priv->note = note_flat;
        } else {
            tuner->priv->note = note_sharp;
        }
        break;
    case 1: 
        tuner->priv->target_temperament = 19;
        tuner->priv->target_adjust = 6;
        tuner->priv->note = note_19;
        break;
    case 2: 
        tuner->priv->target_temperament = 24;
        tuner->priv->target_adjust = 7;
        tuner->priv->note = note_24;
        break;
    case 3: 
        tuner->priv->target_temperament = 31;
        tuner->priv->target_adjust = 9;
        tuner->priv->note = note_31;
        break;
    case 4:
        tuner->priv->target_temperament = 53;
        tuner->priv->target_adjust = 15;
        tuner->priv->note = note_53;
        break;
    default:
        tuner->priv->target_temperament = 12;
        tuner->priv->target_adjust = 3;
        tuner->priv->note = note_sharp;
        break;
    }
    g_object_notify(G_OBJECT(tuner), "temperament");
}

gint gx_rack_tuner_get_temperament(GxRackTuner *tuner)
{
	g_assert(GX_IS_TUNER(tuner));
	return tuner->priv->temperament;
}

void gx_rack_tuner_clear_notes(GxRackTuner *tuner)
{
	g_assert(GX_IS_RACK_TUNER(tuner));
	tuner->priv->n_targets = 0;
}




gboolean gx_rack_tuner_push_note(GxRackTuner *tuner, gint note, gint A, gint TET)
{
	g_assert(GX_IS_RACK_TUNER(tuner));
	if (tuner->priv->n_targets >= RACKTUNER_MAXTARGETS) {
		return FALSE;
	}
    double note2freq = 440.00*pow(2.0, double(note-A)/TET);
    gint freq2note = round(tuner->priv->target_temperament*(log2(note2freq/440.00)+4));
    tuner->priv->targets[tuner->priv->n_targets++] = freq2note ;
	return TRUE;
}

GtkWidget *gx_rack_tuner_new(void)
{
	return (GtkWidget*)g_object_new(GX_TYPE_RACK_TUNER, NULL);
}

static void gx_rack_tuner_set_property(GObject *object, guint prop_id,
									   const GValue *value, GParamSpec *pspec)
{
	GxRackTuner *tuner = GX_RACK_TUNER(object);

	switch(prop_id) {
	case PROP_FREQ:
		gx_rack_tuner_set_freq(tuner, g_value_get_double(value));
		break;
	case PROP_SCALE_LIM:
		gx_rack_tuner_set_scale_lim(tuner, g_value_get_double(value));
		break;
	case PROP_SPEED:
		gx_rack_tuner_set_speed(tuner, g_value_get_double(value));
		break;
	case PROP_DISPLAY_FLAT:
		gx_rack_tuner_set_display_flat(tuner, g_value_get_boolean(value));
		break;
	case PROP_STREAMING:
		gx_rack_tuner_set_streaming(tuner, g_value_get_boolean(value));
		break;
	case PROP_TIMESTEP:
		gx_rack_tuner_set_timestep(tuner, g_value_get_int(value));
		break;
	case PROP_LIMIT_TIMESTEP:
		gx_rack_tuner_set_limit_timestep(tuner, g_value_get_int(value));
		break;
	case PROP_TEMPERAMENT:
		gx_rack_tuner_set_temperament(tuner, g_value_get_int(value));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void gx_rack_tuner_get_property(GObject *object, guint prop_id,
									   GValue *value, GParamSpec *pspec)
{
	GxRackTuner *tuner = GX_RACK_TUNER(object);

	switch(prop_id) {
	case PROP_FREQ:
		g_value_set_double(value, gx_tuner_get_freq(&tuner->parent));
		break;
	case PROP_SCALE_LIM:
		g_value_set_double(value, tuner->priv->scale_lim);
		break;
	case PROP_SPEED:
		g_value_set_double(value, tuner->priv->speed);
		break;
	case PROP_DISPLAY_FLAT:
		g_value_set_boolean(value, tuner->priv->display_flat);
		break;
	case PROP_STREAMING:
		g_value_set_boolean(value, tuner->priv->streaming);
		break;
	case PROP_TIMESTEP:
		g_value_set_int(value, tuner->priv->timestep);
		break;
	case PROP_LIMIT_TIMESTEP:
		g_value_set_int(value, tuner->priv->in_limit_timestep);
		break;
	case PROP_TEMPERAMENT:
		g_value_set_int(value, tuner->priv->temperament);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void gx_rack_tuner_get_preferred_width(GtkWidget *widget, gint *min_width, gint *natural_width)
{
	gint width, height;
	gx_rack_tuner_size_request(widget, &width, &height);

	if (min_width) {
		*min_width = width;
	}
	if (natural_width) {
		*natural_width = width;
	}
}

static void gx_rack_tuner_get_preferred_height(GtkWidget *widget, gint *min_height, gint *natural_height)
{
	gint width, height;
	gx_rack_tuner_size_request(widget, &width, &height);

	if (min_height) {
		*min_height = height;
	}
	if (natural_height) {
		*natural_height = height;
	}
}

static void gx_rack_tuner_size_request(GtkWidget *widget, gint *width, gint *height)
{
	double s = gx_tuner_get_scale(&GX_RACK_TUNER(widget)->parent);
	*width = ((min_led-1) * led_spacing + led_width + 2 * pad) * s;
	*height = 40 * s;
}

static void gx_rack_tuner_pitch_to_note(GxRackTuner *tuner, double fnote, int *oc, int *note, double *scale)
{
	double fnoter = round(fnote);
	*note = int(fnoter);
	if (scale) {
		*scale = fnote - *note;
	}

	*oc = int(round((fnoter+tuner->priv->target_adjust)/tuner->priv->target_temperament));
	int octsz = sizeof(octave) / sizeof(octave[0]);
	if (*oc < 0 || *oc >= octsz) {
		*oc = octsz - 1;
	}
	*note = *note % tuner->priv->target_temperament;
	if (*note < 0) {
		*note += tuner->priv->target_temperament;
	}
}

static void gx_rack_tuner_calc(GxRackTuner *tuner)
{
	double fvis = tuner->priv->target_temperament * (log2(gx_tuner_get_freq(&tuner->parent)/gx_tuner_get_reference_pitch(&tuner->parent)) + 4);
	gx_rack_tuner_pitch_to_note(tuner, fvis, &tuner->priv->indicate_oc, &tuner->priv->vis, &tuner->priv->scale_val);
	if (tuner->priv->n_targets == 0) {
		return;
	}
	double m0 = 1e10;
	int i0 = 0;
	for (int i = 0; i < tuner->priv->n_targets; ++i) {
		double t = fabs(fvis-tuner->priv->targets[i]);
		if (t < m0) {
			m0 = t;
			i0 = i;
		}
        tuner->priv->strng = tuner->priv->n_targets - i0;
        int val = tuner->priv->targets[i0];
		gx_rack_tuner_pitch_to_note(tuner, val, &tuner->priv->target_oc, &tuner->priv->target_note, NULL);
		tuner->priv->scale_val = fvis - val;
		if (tuner->priv->scale_val > 0.5) {
			tuner->priv->scale_val = 0.5;
		} else if (tuner->priv->scale_val < -0.5) {
			tuner->priv->scale_val = -0.5;
		}
	}
}

gboolean gx_rack_tuner_get_poll_status(GxRackTuner *tuner) {
	return (tuner->priv->freqpoll_id != 0);
}

static void gx_rack_tuner_remove_handler(GxRackTuner *tuner)
{
	if (tuner->priv->freqpoll_id) {
		g_source_remove(tuner->priv->freqpoll_id);
		tuner->priv->freqpoll_id = 0;
		g_signal_emit_by_name(tuner, "poll-status-changed", FALSE);
	}
	if (tuner->priv->in_limit_id) {
		g_source_remove(tuner->priv->in_limit_id);
		tuner->priv->in_limit_id = 0;
	}
}

static void gx_rack_tuner_check_poll(GxRackTuner *tuner) 
{
	if (gtk_widget_get_sensitive(GTK_WIDGET(tuner)) && gtk_widget_get_mapped(GTK_WIDGET(tuner))) {
		if (!tuner->priv->freqpoll_id) {
			tuner->priv->freqpoll_id = gdk_threads_add_timeout(
				tuner->priv->timestep, gx_rack_tuner_freq_poll_handler, tuner);
			g_signal_emit_by_name(tuner, "poll-status-changed", TRUE);
			gx_rack_tuner_freq_poll_handler(tuner);
		}
	} else {
		gx_rack_tuner_remove_handler(tuner);
	}
}

static void gx_rack_tuner_map(GtkWidget *widget)
{
	GTK_WIDGET_CLASS(gx_rack_tuner_parent_class)->map(widget);
	gx_rack_tuner_check_poll(GX_RACK_TUNER(widget));
}

static void gx_rack_tuner_unmap(GtkWidget *widget)
{
	GTK_WIDGET_CLASS(gx_rack_tuner_parent_class)->unmap(widget);
	gx_rack_tuner_remove_handler(GX_RACK_TUNER(widget));
}

static void gx_rack_tuner_state_changed(GtkWidget *widget, GtkStateType oldstate)
{
	gx_rack_tuner_check_poll(GX_RACK_TUNER(widget));
}

static gboolean gx_rack_tuner_show_in_limit(gpointer data)
{
	GxRackTuner *tuner = GX_RACK_TUNER(data);
	if (!tuner->priv->in_limit || tuner->priv->pos >= tuner->priv->led_count/2-2) {
		tuner->priv->in_limit_id = 0;
		return FALSE;
	}
	tuner->priv->pos += 1;
	GdkWindow *w = gtk_widget_get_window(GTK_WIDGET(tuner));
	gint width = gdk_window_get_width(w);
	gtk_widget_queue_draw_area(
	    GTK_WIDGET(tuner), 0, floor(led_y0* gx_tuner_get_scale(&tuner->parent)),
	    width, ceil(led_height* gx_tuner_get_scale(&tuner->parent)));
	return TRUE;
}

static gboolean gx_rack_tuner_freq_poll_handler(gpointer data)
{
	GxRackTuner *tuner = GX_RACK_TUNER(data);
	g_signal_emit_by_name(tuner, "frequency-poll");

	double freq = gx_tuner_get_freq(&tuner->parent);
	if (freq != tuner->priv->last_freq) {
		tuner->priv->last_freq = freq;
		gx_rack_tuner_calc(tuner);
	} else {
		if (freq == 0.0 || fabs(tuner->priv->scale_val) < tuner->priv->scale_lim) {
			return TRUE;
		}
	}
	if (tuner->priv->streaming) {
		if (fabs(tuner->priv->scale_val) >= tuner->priv->scale_lim) {
			tuner->priv->in_limit = FALSE;
			double step = tuner->priv->speed * tuner->priv->timestep;
			double step_lim = tuner->priv->led_count/8;
			if (step > step_lim) {
				step = step_lim;
			}
			tuner->priv->pos += step * tuner->priv->scale_val;
			if (tuner->priv->pos >= tuner->priv->led_count) {
				tuner->priv->pos = 0.0;
			} else if (tuner->priv->pos < 0) {
				tuner->priv->pos = tuner->priv->led_count-1;
			}
		} else if (!tuner->priv->in_limit) {
			tuner->priv->in_limit = TRUE;
			tuner->priv->pos = 0;
			if (!tuner->priv->in_limit_id) {
				tuner->priv->in_limit_id = gdk_threads_add_timeout(tuner->priv->in_limit_timestep, gx_rack_tuner_show_in_limit, tuner);
			}
		}
    }
	gtk_widget_queue_draw(GTK_WIDGET(tuner));
	return TRUE;
}

static void gx_rack_tuner_triangle(GxRackTuner *tuner, cairo_t *cr, double posx, double posy, double width, double height)
{
	double h2 = height/2.0;
    cairo_move_to(cr, posx, posy-h2);
    if (width > 0) {
        cairo_curve_to(cr,posx, posy-h2, posx+10, posy, posx, posy+h2);
    } else {
        cairo_curve_to(cr,posx, posy-h2, posx-10, posy, posx, posy+h2);
    }
    cairo_curve_to(cr,posx, posy+h2, posx+width/2, posy+h2, posx+width, posy);
    cairo_curve_to(cr, posx+width, posy, posx+width/2, posy-h2, posx, posy-h2);
	cairo_fill(cr);
}

static void gx_rack_tuner_display_note(GxRackTuner *tuner, cairo_t *cr, double center, double y0, int indicate_oc, int vis, double scale)
{
	if (vis > tuner->priv->target_temperament) return;
	cairo_text_extents_t ex, ex_oct;
	double pitch_add = fabs(gx_tuner_get_reference_pitch(&tuner->parent) - 440.00);
	cairo_set_source_rgba(cr, fabs(scale)+(pitch_add*0.1), 1-(scale*scale+(pitch_add*0.1)), 0.2, 1-fabs(scale));
	cairo_set_font_size(cr, 18.0);
	cairo_text_extents(cr, "M", &ex);
	double g_height = ex.height;
	double g_step = ex.x_advance;
	cairo_set_font_size(cr, 12);
	cairo_text_extents(cr, "##", &ex);
	double sharp_width = ex.width;
	cairo_set_font_size(cr, 9.0);
	cairo_text_extents(cr, octave[indicate_oc], &ex_oct);
	cairo_set_font_size(cr, 18.0);
	double wdt = g_step + sharp_width;
	double x0 = center-wdt/2+1;
	y0 += g_height/2;
	cairo_move_to(cr, x0, y0);
	const char *nt = tuner->priv->note[vis];
	char buf[2];
	buf[0] = nt[0];
	buf[1] = 0;
	cairo_show_text(cr,buf);
	if (strlen(nt) > 1) {
	    cairo_set_font_size(cr,12);
		cairo_move_to(cr,x0+g_step, y0-4);
		cairo_show_text(cr,&nt[1]);
    }
    cairo_set_font_size(cr,9.0);
	cairo_move_to(cr,x0+g_step, y0-ex_oct.y_bearing/2+2);
	cairo_show_text(cr,octave[indicate_oc]);
}

static void gx_rack_tuner_paint(GxRackTuner *tuner, cairo_t *cr, gboolean paint_bg)
{
	double scale = gx_tuner_get_scale(&tuner->parent);
	cairo_scale(cr, scale, scale);
	cairo_set_line_width(cr,1);
	double center = tuner->priv->padding + tuner->priv->width/2;
	double dist = 20;
	double tri0 = center-15-dist;
	double tri1 = center+15+dist;
    cairo_pattern_t* pat = cairo_pattern_create_linear (0, 0,center, 0);
    cairo_pattern_set_extend(pat, CAIRO_EXTEND_REFLECT);
    cairo_pattern_add_color_stop_rgb (pat, 1, 0.1, 0.8, 0.1);
    cairo_pattern_add_color_stop_rgb (pat, 0.7, 0.8, 0.8, 0.1);
    cairo_pattern_add_color_stop_rgb (pat, 0, 1, 0.1, 0.1);
	if (paint_bg) {
		cairo_set_source_rgb(cr, 0, 0, 0);
		cairo_paint(cr);
		for (int i = 0; i < tuner->priv->led_count; ++i) {
			cairo_set_source_rgb(cr,0.1,0.1,0.1);
			cairo_rectangle(cr,tuner->priv->padding+i*led_spacing, led_y0, led_width, led_height);
			cairo_fill(cr);
		}
		cairo_set_source_rgb(cr,0.1,0.1,0.1);
		gx_rack_tuner_triangle(tuner, cr, tri0, 25, 15, 10);
		gx_rack_tuner_triangle(tuner, cr, tri1, 25, -15, 10);
		return;
	}
	if (tuner->priv->streaming) {
        
        cairo_set_source (cr, pat);
		if (tuner->priv->in_limit) {
			//cairo_set_source_rgb(cr,1, 0, 0);
            
			int n = tuner->priv->led_count/2-tuner->priv->pos;
			if (n > 4) {
				n = 4;
			}
			for (int i = 0; i < n; ++i) {
				cairo_rectangle(cr,tuner->priv->padding+(tuner->priv->pos+i)*led_spacing, led_y0, led_width, led_height);
				cairo_rectangle(cr,tuner->priv->padding+(tuner->priv->led_count-1-i-tuner->priv->pos)*led_spacing, led_y0, led_width, led_height);
			}
			cairo_fill(cr);
            
		} else {
			// led display: 2 .. tuner->priv->led_count/8+1
			int lim = 1+int(1+(fabs(tuner->priv->scale_val)-tuner->priv->scale_lim)*tuner->priv->led_count/4.0);
			//cairo_set_source_rgb(cr,1, 0, 0);
			if (fabs(tuner->priv->scale_val) >= tuner->priv->scale_lim) {
				for (int i = 0; i < tuner->priv->led_count; ++i) {
					int j = int(tuner->priv->led_count+i-tuner->priv->pos) % (tuner->priv->led_count/2);
					if (j < 0) {
						j = -j;
					}
					if (lim <= j) {
						continue;
					}
					cairo_rectangle(cr,tuner->priv->padding+i*led_spacing, led_y0, led_width, led_height);
				}
			}
			cairo_fill(cr);
		}
	} else {
		double s = 0.5+tuner->priv->scale_val;
		if (s < 0) {
			s = 0;
		} else if (s > 1) {
			s = 1;
		}
		double sz = 2 * tuner->priv->width * tuner->priv->scale_lim;
		cairo_rectangle(cr,tuner->priv->padding+s*(tuner->priv->width-sz), led_y0, sz, led_height);
		cairo_set_source_rgb(cr,1, 0, 0);
        cairo_set_source (cr, pat);
		cairo_fill(cr);
		if (fabs(tuner->priv->scale_val) < 0.4) {
			cairo_set_source_rgb(cr,1, 1, 0);
			cairo_rectangle(cr,tuner->priv->padding+0.5*(tuner->priv->width-led_width), led_y0, led_width, led_height);
			cairo_fill(cr);
		}
	}
	double ex_x, ex_y, ex_w, ex_h;
	cairo_clip_extents(cr, &ex_x, &ex_y, &ex_w, &ex_h);
	if (ex_y + ex_h <= 10) {
		return;
	}
	if (tuner->priv->scale_val < tuner->priv->scale_lim) {
		cairo_set_source_rgb(cr,0.80,0.79,0.01);
		gx_rack_tuner_triangle(tuner, cr, tri0, tri_y0, 15, 10);
	}
	if (tuner->priv->scale_val > -tuner->priv->scale_lim) {
		cairo_set_source_rgb(cr,0.80,0.79,0.01);
		gx_rack_tuner_triangle(tuner, cr, tri1, tri_y0, -15, 10);
	}
	gx_rack_tuner_display_note(tuner, cr, center, tri_y0, tuner->priv->indicate_oc, tuner->priv->vis, tuner->priv->scale_val);

	if (tuner->priv->n_targets > 0) {
		cairo_set_font_size(cr,12.0);
		char sd[10];
		int n = snprintf(sd, sizeof(sd), "%d: %s", tuner->priv->strng, tuner->priv->note[tuner->priv->target_note]);
		char c = sd[n-1];
		if (c == '#' || c == 'b') {
			sd[n-1] = 0;
			n -= 1;
		}
		cairo_text_extents_t ex;
		cairo_text_extents(cr, sd, &ex);
		sd[n] = '#';
		sd[n+1] = 0;
		cairo_text_extents(cr, sd, &ex);
		cairo_move_to(cr,pad + (tri0-pad) / 2 - ex.width/2, tri_y0 - ex.y_bearing/2);
		cairo_set_source_rgb(cr,0.95,0.95,0.3);
		sd[n] = 0;
		cairo_show_text(cr, sd);
		double pt_x, pt_y;
		cairo_get_current_point(cr, &pt_x, &pt_y);
		cairo_set_font_size(cr,9.0);
		cairo_rel_move_to(cr,0,-ex.y_bearing/2);
		cairo_show_text(cr, octave[tuner->priv->target_oc]);
		if (c == '#' || c == 'b') {
			cairo_move_to(cr,pt_x, tri_y0);
			sd[0] = c;
			sd[1] = 0;
			cairo_show_text(cr, sd);
		}
	}
	// display frequency
	cairo_set_source_rgba(cr,0.8, 0.8, 0.2,0.6);
	cairo_set_font_size(cr,8.0);
	char buf[12];
	snprintf(buf, sizeof(buf), "%.1f Hz", gx_tuner_get_freq(&tuner->parent));
	cairo_text_extents_t ex;
	cairo_text_extents(cr,buf, &ex);
	gint width = gdk_window_get_width(gtk_widget_get_window(GTK_WIDGET(tuner)));
	cairo_move_to(
		cr, width/ gx_tuner_get_scale(&tuner->parent) -pad-ex.width-10, tri_y0-ex.y_bearing);
	cairo_show_text(cr,buf);
    cairo_pattern_destroy(pat);
}

static gboolean gx_rack_tuner_configure_event(GtkWidget *widget, GdkEventConfigure *ev)
{
	GxRackTuner *tuner = GX_RACK_TUNER(widget);
	double swidth = ev->width / gx_tuner_get_scale(&tuner->parent);
	tuner->priv->led_count = (int(1 + (swidth - 2 * pad - led_width) / led_spacing) / 4) * 4;
	tuner->priv->width = (tuner->priv->led_count-1) * led_spacing + led_width;
	tuner->priv->padding = (swidth - tuner->priv->width) / 2;
	if (tuner->priv->streaming && tuner->priv->in_limit && !tuner->priv->in_limit_id) {
		tuner->priv->pos = tuner->priv->led_count/2-2;
	}
	cairo_surface_t *surface_tuner = cairo_image_surface_create(
		CAIRO_FORMAT_RGB24, ev->width, ev->height);
	gx_tuner_set_surface_tuner(&tuner->parent, surface_tuner);
	cairo_t *cr = cairo_create(surface_tuner);
	gx_rack_tuner_paint(tuner, cr, TRUE);
	cairo_destroy(cr);
	return FALSE;
}

static gboolean gx_rack_tuner_draw(GtkWidget *widget, cairo_t *cr)
{
	GxRackTuner *tuner = GX_RACK_TUNER(widget);
	cairo_set_source_surface(cr, gx_tuner_get_surface_tuner(&tuner->parent), 0, 0);
	cairo_paint(cr);
	if (gtk_widget_get_sensitive(widget) && gx_tuner_get_freq(&tuner->parent)) {
		gx_rack_tuner_paint(tuner, cr, FALSE);
	}
	return FALSE;
}

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
 * -------------------------------------------------------------------------
 *
 * Code shamelessly stolen from Ardour by Paul Davis, thanks man!
 * This is actually an adaptation of the C++ gtkmm2ext class in the
 * GTK C style.
 *
 * -------------------------------------------------------------------------
 */
#include <math.h>
#include <stdlib.h>
#include "GxFastMeter.h"
#include "GxControlParameter.h"
#include "log_meter.h"

#ifndef max
#define max(x,y) (((x)>(y)) ? (x) : (y))
#endif

#ifndef min
#define min(x,y) (((x)<(y)) ? (x) : (y))
#endif

#define P_(s) (s)   // FIXME -> gettext

#define FALLOFF_DURATION 500  // time in ms for linear falloff (max scale -> 0)
#define FALLOFF_UPDATE_RATE 60  // time in ms between falloff updates

#define FALLOFF_VALUE (FALLOFF_UPDATE_RATE/(float)FALLOFF_DURATION)

struct _GxFastMeterPrivate {
	cairo_surface_t *surface, *overlay;
	gint	      top_of_meter;
	GdkRectangle  last_peak_rect, bar;

	gchar *var_id;
	int hold_cnt;
	int hold_state;                    // countdown for peak bar display
	float falloff;
	guint falloff_timer_id;
	bool horiz;

	float	      target_level;         // target deflection (0 .. 1)
	float	      current_level;        // current deflection (with falloff)
	float         min_level, max_level; // range for linear display
	float	      current_peak;         // for display of peak bar
	gboolean      is_power;
	gint dimen, clr0, clr1, clr2, clr3, type;
};

enum {
	PROP_HOLD = 1,
	PROP_DIMEN,
	PROP_VAR_ID,
	PROP_ORIENTATION,
	PROP_FALLOFF,
	PROP_POWER,
};

static const int min_size = 1;

static void gx_fast_meter_class_init(GxFastMeterClass*);
static void gx_fast_meter_init(GxFastMeter*);
static void gx_fast_meter_destroy(GtkWidget *object);

static void gx_control_parameter_interface_init (GxControlParameterIface *iface);

static gboolean gx_fast_meter_draw(GtkWidget*, cairo_t *);
static void gx_fast_meter_size_allocate(GtkWidget *widget, GtkAllocation *allocation);
static void gx_fast_meter_state_changed(GtkWidget*, GtkStateType);
static void gx_fast_meter_get_preferred_width(GtkWidget*, gint *min_width, gint *natural_width);
static void gx_fast_meter_get_preferred_height(GtkWidget*, gint *min_height, gint *natural_height);
static void gx_fast_meter_size_request(GtkWidget*, gint *width, gint *height);
static void gx_fast_meter_set_is_power(GxFastMeter *fm, bool state);
static void gx_fast_meter_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void gx_fast_meter_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);
static void queue_redraw(GxFastMeter*);
static void request_meter(GtkWidget *widget);
static void remove_handler(GxFastMeter *fm);
static void gx_fast_meter_style_updated(GtkWidget *widget);
static void orientation_set_css_class(GxFastMeter *fm);

G_DEFINE_TYPE_WITH_CODE(GxFastMeter, gx_fast_meter, GTK_TYPE_DRAWING_AREA,
                        G_ADD_PRIVATE(GxFastMeter)
                        G_IMPLEMENT_INTERFACE(GX_TYPE_CONTROL_PARAMETER,
                                              gx_control_parameter_interface_init)
						G_IMPLEMENT_INTERFACE (GTK_TYPE_ORIENTABLE, NULL));

static void
gx_fast_meter_cp_configure(GxControlParameter *self, const gchar* group, const gchar *name, gdouble lower, gdouble upper, gdouble step)
{
	g_return_if_fail(GX_IS_FAST_METER(self));
	GxFastMeter *fm = GX_FAST_METER(self);
	fm->priv->min_level = lower;
	fm->priv->max_level = upper;
	gx_fast_meter_set_is_power(fm, step != 0);
}

static gdouble
gx_fast_meter_cp_get_value(GxControlParameter *self)
{
	return GX_FAST_METER(self)->priv->current_level;
}

static void
gx_fast_meter_cp_set_value(GxControlParameter *self, gdouble value)
{
	GxFastMeter *fm = GX_FAST_METER(self);
	if (!gtk_widget_get_sensitive(GTK_WIDGET(self))) { //FIXME
		return;
	}
	if (fm->priv->is_power) {
		gx_fast_meter_set_by_power(fm, value);
	} else {
		gx_fast_meter_set(fm, value);
	}
}

static void
gx_control_parameter_interface_init(GxControlParameterIface *iface)
{
  iface->cp_configure = gx_fast_meter_cp_configure;
  iface->cp_set_value = gx_fast_meter_cp_set_value;
  iface->cp_get_value = gx_fast_meter_cp_get_value;
}

/* ----- fast meter class init ----- */
void gx_fast_meter_class_init(GxFastMeterClass* klass)
{
	GtkWidgetClass* widget_class = (GtkWidgetClass*)klass;
	GObjectClass *gobject_class = G_OBJECT_CLASS(klass);

	widget_class->get_preferred_width = gx_fast_meter_get_preferred_width;
	widget_class->get_preferred_height = gx_fast_meter_get_preferred_height;
	widget_class->size_allocate = gx_fast_meter_size_allocate;
	widget_class->draw  = gx_fast_meter_draw;
	widget_class->destroy = gx_fast_meter_destroy;
	widget_class->style_updated = gx_fast_meter_style_updated;
	widget_class->state_changed = gx_fast_meter_state_changed;
	gobject_class->set_property = gx_fast_meter_set_property;
	gobject_class->get_property = gx_fast_meter_get_property;

	gtk_widget_class_set_css_name(widget_class, "gx-fast-meter");

	g_object_class_install_property (
		gobject_class, PROP_VAR_ID, g_param_spec_string(
			"var-id", P_("Variable"),
			P_("The id of the linked variable"),
			NULL, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_HOLD, g_param_spec_int(
			"hold", P_("Hold"),
			P_("Count of cycles for which the peak value is held on display"),
			0, 1000, 2, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_DIMEN, g_param_spec_int(
			"dimen", P_("Dimension"),
			P_("Size of meter"),
			0, 100, 2, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
    g_object_class_install_property(
		gobject_class, PROP_FALLOFF, g_param_spec_boolean(
			"falloff", P_("Falloff"),
			P_("Meter peak falloff"),
			FALSE, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
    g_object_class_install_property(
		gobject_class, PROP_POWER, g_param_spec_boolean(
			"power", P_("Powermeter"),
			P_("Meter is showing signal power (input range: 0 .. 2)"),
			FALSE, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_override_property(gobject_class, PROP_ORIENTATION, "orientation");
	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_boxed("clr-bottom",P_("bottom color"),
		                   P_("indicator color gradient: value at the bottom"),
		                   GDK_TYPE_RGBA,
		                   GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_boxed("clr-middle",P_("middle color"),
		                   P_("indicator color gradient: value in the middle"),
		                   GDK_TYPE_RGBA,
		                   GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_boxed("clr-top",P_("top color"),
		                   P_("indicator color gradient: value near the top"),
		                   GDK_TYPE_RGBA,
		                   GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_boxed("over",P_("clip warn color"),
		                   P_("indicator color for values > 0 dbFS"),
		                   GDK_TYPE_RGBA,
		                   GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
	gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("dimen",P_("width of indicator"),
		                   P_("width of (vertical) indicator"),
		                 0, 100, 2, GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
    gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("led-border",P_("LED Border"),
		                   P_("Border around LED"),
		                 0, 100, 1, GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
    gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("led-width",P_("LED Width"),
		                   P_("Width of LED"),
		                 0, 100, 2, GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
    gtk_widget_class_install_style_property(
		widget_class,
		g_param_spec_int("led-height",P_("LED Height"),
		                   P_("Height of LED"),
		                 0, 100, 2, GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
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
		g_param_spec_float("mid-pos",
            P_("Mid-Position"),
            P_("Position of the middle color"),
            0, 1, 0.5,
            GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
}

/* ----- fast meter init ----- */
void gx_fast_meter_init(GxFastMeter* fm)
{
	GtkWidget *widget = GTK_WIDGET(fm);
	fm->priv = (GxFastMeterPrivate*)gx_fast_meter_get_instance_private(fm);
	fm->priv->surface = 0;
	fm->priv->overlay = 0;
	fm->priv->top_of_meter = 0;
	fm->priv->last_peak_rect.width = 0;
	fm->priv->last_peak_rect.height = 0;
	fm->priv->var_id = NULL;
	fm->priv->hold_cnt = 0;
	fm->priv->hold_state = 0;
	fm->priv->falloff = 0;
	fm->priv->falloff_timer_id = 0;
	fm->priv->horiz = TRUE;
	orientation_set_css_class(fm);
	fm->priv->current_peak = 0;
	fm->priv->target_level = 0;
	fm->priv->min_level = 0;
	fm->priv->max_level = 1;
	fm->priv->is_power = FALSE;
	fm->priv->current_level =  0;
	gtk_widget_set_events(widget,
						  GDK_BUTTON_PRESS_MASK|GDK_BUTTON_RELEASE_MASK);
    GdkScreen *screen = gdk_screen_get_default();
    GdkVisual *visual = gdk_screen_get_rgba_visual(screen);
    if (visual && gdk_screen_is_composited (screen))
        gtk_widget_set_visual(widget, visual);
}

static void gx_fast_meter_destroy(GtkWidget *object)
{
	GxFastMeter *fm = GX_FAST_METER(object);
	remove_handler(fm);
	if (fm->priv->surface) {
		cairo_surface_destroy(fm->priv->surface);
		fm->priv->surface = nullptr;
	}
	if (fm->priv->overlay) {
        cairo_surface_destroy(fm->priv->overlay);
		fm->priv->overlay = nullptr;
	}
	g_free(fm->priv->var_id);
	fm->priv->var_id = nullptr;
	GTK_WIDGET_CLASS(gx_fast_meter_parent_class)->destroy (object);
}

/* -------------- */
GtkWidget* gtk_fast_meter_new (int hold)
{
	GxFastMeter* fm;
	fm = GX_FAST_METER(g_object_new(GX_TYPE_FAST_METER, NULL));
	fm->priv->hold_cnt = hold;
	return GTK_WIDGET (fm);
}


/* ------ hold count ----- */
void gx_fast_meter_set_hold_count(GxFastMeter* fm, int val)
{
	if (val < 1) val = 1;

	fm->priv->hold_cnt     = val;
	fm->priv->hold_state   = 0;
	fm->priv->current_peak = 0;

	gtk_widget_queue_draw(GTK_WIDGET(fm));
}

static void gx_fast_meter_size_allocate (GtkWidget *widget, GtkAllocation *allocation)
{
	GTK_WIDGET_CLASS(gx_fast_meter_parent_class)->size_allocate(widget, allocation);
	request_meter(widget);
}

static void gx_fast_meter_set_is_power(GxFastMeter *fm, bool state)
{
	fm->priv->is_power = state;
	g_object_notify(G_OBJECT(fm), "power");
}

static void gx_fast_meter_set_var_id(GxFastMeter *fm, const gchar *str)
{
	g_free(fm->priv->var_id);
	fm->priv->var_id = g_strdup(str ? str : "");
	g_object_notify(G_OBJECT(fm), "var-id");
}

static void orientation_set_css_class(GxFastMeter *fm)
{
	GtkStyleContext *context = gtk_widget_get_style_context(GTK_WIDGET(fm));
	if (fm->priv->horiz) {
		gtk_style_context_add_class (context, GTK_STYLE_CLASS_HORIZONTAL);
		gtk_style_context_remove_class (context, GTK_STYLE_CLASS_VERTICAL);
	} else {
      gtk_style_context_add_class (context, GTK_STYLE_CLASS_VERTICAL);
      gtk_style_context_remove_class (context, GTK_STYLE_CLASS_HORIZONTAL);
    }
}

static void gx_fast_meter_set_property(GObject *object, guint prop_id,
                                           const GValue *value, GParamSpec *pspec)
{
	GxFastMeter *fm = GX_FAST_METER(object);
	switch(prop_id) {
	case PROP_HOLD:
		fm->priv->hold_cnt = g_value_get_int(value);
		g_object_notify(object, "hold");
		fm->priv->hold_state = 0;
		break;
	case PROP_DIMEN:
		fm->priv->dimen = g_value_get_int(value);
		g_object_notify(object, "dimen");
		gtk_widget_queue_resize(GTK_WIDGET(object));
		break;
    case PROP_ORIENTATION:
		if (fm->priv->horiz != (g_value_get_enum (value) == GTK_ORIENTATION_HORIZONTAL)) {
			fm->priv->horiz = !fm->priv->horiz;
			orientation_set_css_class(fm);
			gtk_widget_queue_resize (GTK_WIDGET (object));
			g_object_notify_by_pspec (object, pspec);
        }
		break;
	case PROP_FALLOFF:
		fm->priv->falloff = g_value_get_boolean(value) ? FALLOFF_VALUE : 0;
		g_object_notify(object, "falloff");
		break;
	case PROP_POWER:
		gx_fast_meter_set_is_power(fm, g_value_get_boolean(value));
		break;
	case PROP_VAR_ID:
		gx_fast_meter_set_var_id (fm, g_value_get_string (value));
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void gx_fast_meter_get_property(GObject *object, guint prop_id,
                                           GValue *value, GParamSpec *pspec)
{
	GxFastMeter *fm = GX_FAST_METER(object);

	switch(prop_id) {
	case PROP_HOLD:
		g_value_set_int(value, fm->priv->hold_cnt);
		break;
	case PROP_DIMEN:
		g_value_set_int(value, fm->priv->dimen);
		break;
    case PROP_ORIENTATION:
		g_value_set_enum (value, fm->priv->horiz ? GTK_ORIENTATION_HORIZONTAL : GTK_ORIENTATION_VERTICAL);
		break;
	case PROP_FALLOFF:
		g_value_set_boolean(value, fm->priv->falloff != 0);
		break;
	case PROP_POWER:
		g_value_set_boolean(value, fm->priv->is_power);
		break;
	case PROP_VAR_ID:
		g_value_set_string (value, fm->priv->var_id);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void gx_fast_meter_style_updated(GtkWidget *widget)
{
	request_meter(widget);
}

/* ------- setting meter level ----------- */
static gboolean falloff_handler(gpointer data)
{
	GxFastMeter *fm = GX_FAST_METER(data);
	bool hold_redraw = false;
	bool falloff_redraw = false;
	float falloff = fm->priv->falloff;
	float target_level = fm->priv->target_level;

	if (!gtk_widget_get_sensitive(GTK_WIDGET(fm))) {
		target_level = 0;
		fm->priv->hold_state = 0;
		falloff = 2 * falloff;
	}
	if (fm->priv->hold_state > 0) {
		fm->priv->hold_state--;
		if (!fm->priv->hold_state) {
			hold_redraw = true;
		}
	}
	if (falloff) {
		if (fm->priv->current_level > target_level) {
			fm->priv->current_level = max(
				target_level, fm->priv->current_level - falloff);
			falloff_redraw = true;
		}
	}
	if (hold_redraw || falloff_redraw) {
		queue_redraw(fm);
	}
	if (!fm->priv->hold_state && fm->priv->current_level == target_level) {
		fm->priv->falloff_timer_id = 0;
		return FALSE;
	}
	return TRUE;
}

static void remove_handler(GxFastMeter *fm)
{
	if (fm->priv->falloff_timer_id) {
		g_source_remove(fm->priv->falloff_timer_id);
		fm->priv->falloff_timer_id = 0;
	}
}

static void check_falloff_timer(GxFastMeter *fm)
{
	if (!fm->priv->falloff_timer_id && (
			fm->priv->hold_state || fm->priv->current_level > fm->priv->target_level)) {
		fm->priv->falloff_timer_id = g_timeout_add(FALLOFF_UPDATE_RATE, falloff_handler, fm);
	}
}

static void _meter_set(GxFastMeter* fm, float lvl)
{
	float old_level = fm->priv->current_level;
	float old_peak  = fm->priv->current_peak;

	fm->priv->target_level = lvl;
	if (fm->priv->falloff && lvl < fm->priv->current_level) {
		lvl = fm->priv->current_level;
	} else {
		fm->priv->current_level = lvl;
	}
	if (fm->priv->hold_cnt) {
		if (lvl > fm->priv->current_peak) {
			fm->priv->current_peak = lvl;
			fm->priv->hold_state   = fm->priv->hold_cnt;
		} else if (fm->priv->hold_state == 0) {
			fm->priv->current_peak = lvl;
		}
	}
	check_falloff_timer(fm);
	if (fm->priv->current_level == old_level &&
	    (fm->priv->hold_state == 0 || fm->priv->current_peak  == old_peak)) {
		return;
	}
	queue_redraw(fm);
}

void gx_fast_meter_set(GxFastMeter* fm, gdouble lvl)
{
	float minl = fm->priv->min_level;
	float maxl = fm->priv->max_level;
	_meter_set(fm, (max(minl, min(maxl, lvl)) - minl) / (maxl - minl));
}

inline float power2db(float power) {
    return  20.*log10(power);
}

static float meter_level_by_power(GxFastMeter* fm, float new_level) {
    // calculate peak dB and translate into meter
    float peak_db = 0;
    if (new_level > 0) {
        peak_db = log_meter(power2db(new_level));
    }
    return peak_db;
}


/* ------- setting meter level ----------- */
void gx_fast_meter_set_by_power(GxFastMeter* fm, gdouble lvl)
{
	_meter_set(fm, meter_level_by_power(fm,lvl));
}

/* ------- setting compressor meter level ----------- */
void gx_fast_meter_set_c_level(GxFastMeter* fm, gdouble lvl)
{
	gx_fast_meter_set(fm, lvl*0.25);
}
/* ------------- clear fast meter object ------------ */
void gx_fast_meter_clear(GxFastMeter* fm)
{
	fm->priv->target_level  = 0;
	fm->priv->current_level = 0;
	fm->priv->current_peak  = 0;
	fm->priv->hold_state    = 0;
	gtk_widget_queue_draw(GTK_WIDGET(fm));
}

static void gx_fast_meter_state_changed(GtkWidget *widget, GtkStateType oldstate)
{
	if (!gtk_widget_get_sensitive(widget)) {
		GxFastMeter *fm = GX_FAST_METER(widget);
		fm->priv->hold_state = 0;
		fm->priv->target_level = 0;
		if (gtk_widget_is_visible(widget)) {
			check_falloff_timer(fm);
		} else {
			fm->priv->current_level = 0;
		}
	}
}

/* ------------------------------ static functions ------------------------- */

static void gx_fast_meter_get_preferred_width(GtkWidget* wd, gint *min_width, gint *natural_width)
{
	gint width, height;
	gx_fast_meter_size_request(wd, &width, &height);

	if (min_width) {
		*min_width = width;
	}
	if (natural_width) {
		*natural_width = width;
	}
}

static void gx_fast_meter_get_preferred_height(GtkWidget* wd, gint *min_height, gint *natural_height)
{
	gint width, height;
	gx_fast_meter_size_request(wd, &width, &height);

	if (min_height) {
		*min_height = height;
	}
	if (natural_height) {
		*natural_height = height;
	}
}

static void gx_fast_meter_size_request (GtkWidget* wd, gint *width, gint *height)
{
    GxFastMeter * fm = GX_FAST_METER(wd);
    int lw, lh, lb, dim_, dim;
    gtk_widget_style_get(wd, "led-width", &lw, "led-height", &lh,
						 "led-border", &lb, "dimen", &dim_, NULL);
    dim = fm->priv->dimen ? fm->priv->dimen : dim_;
	// vertical layout
	int w = lb + dim * (lw + lb);
	int h = lb + min_size * (lh + lb);
    if (fm->priv->horiz) {
        *width  = h;
        *height = w;
    } else {
        *width  =  w;
        *height =  h;
    }
	// min-width / -height
	GtkStateFlags state_flags = gtk_widget_get_state_flags(wd);
    GtkStyleContext *sc = gtk_widget_get_style_context(wd);
	int min_width, min_height;
	gtk_style_context_get(
		sc, state_flags, "min-width", &min_width, "min-height", &min_height, NULL);
	*width = max(min_width, *width);
	*height = max(min_height, *height);
	// add border and margin
    GtkBorder margin, border;
    gtk_style_context_get_margin(sc, state_flags, &margin);
    gtk_style_context_get_border(sc, state_flags, &border);
	*width += margin.left + margin.right + border.left + border.right;
	*height += margin.top + margin.bottom + border.top + border.bottom;
}

/* --------- drawing queue ----------- */

inline int calc_top(float level, bool hrz, GdkRectangle& b, int lh, int lb)
{
    // number of led positions (add missing first led border)
    int sz = ((hrz ? b.width : b.height) + lb) / (lh+lb);
	int pos = (int)round(sz * level);
    if (pos == 0) {
        return 0;
    }
    return pos * (lh + lb) - lb; // substract missing first led border
}

void queue_redraw (GxFastMeter* fm)
{
    if (!fm->priv->surface)
		return;
	GtkWidget *widget = GTK_WIDGET(fm);
	GdkRectangle rect;
    GdkRectangle& b = fm->priv->bar;
	int lw, lh, lb;
    gtk_widget_style_get(widget, "led-width", &lw, "led-height", &lh, "led-border", &lb, NULL);

	cairo_region_t* region = nullptr;

    bool hrz   = fm->priv->horiz;
    int tom    = fm->priv->top_of_meter;

	int new_top = calc_top(fm->priv->current_level, hrz, b, lh, lb);

	if (new_top != tom) {
		GtkStateFlags state_flags = gtk_widget_get_state_flags(widget);
		GtkStyleContext *sc = gtk_widget_get_style_context(widget);
		GtkBorder margin;
		gtk_style_context_get_margin(sc, state_flags, &margin);
		rect = b;
		rect.x += margin.left;
		rect.y += margin.top;
		int df = new_top - tom;
		if (df < 0) {
			tom += df;
			df = -df;
		}
		// tom is now start of update region, df is size
		if (hrz) {
			rect.x += tom;
			rect.width = df;
		} else {
			rect.y += rect.height - tom - df;
			rect.height = df;
		}

		if (rect.height + rect.width != 0) {
			/* ok, first region to draw ... */
			region = cairo_region_create_rectangle (&rect);
		}
	}

	/* redraw the last place where the last peak hold bar was;
	   the next expose will draw the new one whether its part of
	   expose region or not. */

	if (fm->priv->last_peak_rect.width + fm->priv->last_peak_rect.height != 0) {
		if (!region) {
			region = cairo_region_create();
		}
		rect = fm->priv->last_peak_rect;
		cairo_region_union_rectangle (region, &rect);
	}

	if (region) {
		gtk_widget_queue_draw_region (widget, region);
		cairo_region_destroy(region);
	}
}


/* ------- expose event -------- */
static gboolean gx_fast_meter_draw (GtkWidget* wd, cairo_t *cr)
{
	GxFastMeter* fm = GX_FAST_METER(wd);
    GdkRectangle b = fm->priv->bar;
	gint         top_of_meter;
    int lw, lh, lb;
    gtk_widget_style_get(wd, "led-width", &lw, "led-height", &lh, "led-border", &lb, NULL);

	if (!fm->priv->surface) {
		return FALSE;
	}
    bool hrz   = fm->priv->horiz;
    int height = cairo_image_surface_get_height(fm->priv->surface);
    int width  = cairo_image_surface_get_width(fm->priv->surface);
	GtkStateFlags state_flags = gtk_widget_get_state_flags(wd);
    GtkStyleContext *sc = gtk_widget_get_style_context(wd);
    GtkBorder margin;
    gtk_style_context_get_margin(sc, state_flags, &margin);
    int x = margin.left;
    int y = margin.top;

	top_of_meter = calc_top(fm->priv->current_level, hrz, b, lh, lb);
    fm->priv->top_of_meter = top_of_meter;

    cairo_set_source_surface(cr, fm->priv->surface, x, y);
	cairo_rectangle(cr, x, y, width, height);
	cairo_fill(cr);

	x += b.x;
	y += b.y;
    cairo_set_source_surface(cr, fm->priv->overlay, x, y);
	if (hrz) {
		cairo_rectangle(cr, x, y, top_of_meter, b.height);
	} else {
		cairo_rectangle(cr, x, y + b.height - top_of_meter, b.width, top_of_meter);
	}
	cairo_fill(cr);

	// draw peak bar
	if (fm->priv->hold_state) {
        GdkRectangle *r = &fm->priv->last_peak_rect;
		int t = calc_top(fm->priv->current_peak, hrz, b, lh, lb);
		if (t > 0) {
			if (hrz) {
				r->width = lb + lh;
				r->x = x + t - r->width;
				r->y = y;
				r->height = b.height;
			} else {
				r->x = x;
				r->y = y + b.height - t;
				r->width = b.width;
				r->height = lb + lh;
			}
			cairo_rectangle(cr, r->x, r->y, r->width, r->height);
			cairo_fill(cr);
		}
		return FALSE;
	}
	fm->priv->last_peak_rect.width  = 0;
	fm->priv->last_peak_rect.height = 0;
	return FALSE;
}



#define grad_size 4

GdkRGBA default_gradient_color[grad_size] = {
	// red green  blue alpha
	{ 0.0, 1.0,   0.0, 1.0 }, // clr-bottom
	{ 1.0, 1.0,   0.0, 1.0 }, // clr-middle
	{ 1.0, 0.664, 0.0, 1.0 }, // clr-top
	{ 1.0, 0.0,   0.0, 1.0 }  // over
};

#define CVALUE(i,c,y,mx) (guint8)floor(((int)rgb[i]->c + (((int)rgb[i+1]->c - (int)rgb[i]->c) * (y)) / (float)(mx))/256)

/* ----- create pixbuf for meter (content + border, without margin) ------ */
static void request_meter(GtkWidget *widget)
{
	GxFastMeter* fm = GX_FAST_METER(widget);
	if (fm->priv->surface) {
		cairo_surface_destroy(fm->priv->surface);
        cairo_surface_destroy(fm->priv->overlay);
	}
    int lw, lh, lb, dim_, dim, rad;
    float bevel;
    gtk_widget_style_get(widget, "led-width", &lw, "led-height", &lh, "led-border",
						 &lb, "dimen", &dim_, "border-radius", &rad, "bevel", &bevel, NULL);
    dim = fm->priv->dimen ? fm->priv->dimen : dim_;
    bool hrz = fm->priv->horiz;
    
	GtkStateFlags state_flags = gtk_widget_get_state_flags(widget);
    GtkStyleContext *sc = gtk_widget_get_style_context(widget);
    GtkBorder margin, border;
    gtk_style_context_get_margin(sc, state_flags, &margin);
    gtk_style_context_get_border(sc, state_flags, &border);
	int xmargin = margin.left + margin.right;
	int ymargin = margin.top + margin.bottom;
    int xborder = border.left + border.right;
	int yborder = border.top + border.bottom;

    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);
	// vertical layout
	int b = lb + dim * (lw + lb);
	int width, height;
	// width, height: content + border (without margin)
    if (hrz) {
		width = allocation.width - xmargin;
		height = b + yborder;
	} else {
		width = b + xborder;
		height = allocation.height - ymargin;
	}

    cairo_t *cr;
    fm->priv->surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	if (cairo_surface_status(fm->priv->surface) != CAIRO_STATUS_SUCCESS) {
		fm->priv->surface = nullptr;
		return;
	}
    cr = cairo_create(fm->priv->surface);
    //gtk_render_background(sc, cr, 0, 0, width, height);
    gtk_render_frame(sc, cr, 0, 0, width, height);
    if (bevel) {
        gx_bevel(cr, 0, 0, width, height, rad, bevel);
	}
    gtk_render_background(sc, cr, border.left, -rad, width, height+yborder+2*rad);

	int x = border.left;
	int y = border.top;
	width -= xborder;
	height -= yborder;
	// width, height: just content

	// don't display clipped led's
    if (hrz) {
        width -= (width - lb) % (lh + lb);
    } else {
        height -= (height - lb) % (lh + lb);
    }
	// width, height: led bar

    // gradient for led bar
    GdkRGBA *rgb[4];
    unsigned int i;
    float midpos;
    gtk_widget_style_get(widget, "clr-bottom", &rgb[0], "clr-middle", &rgb[1], "clr-top", &rgb[2],
						 "over", &rgb[3], "mid-pos", &midpos, NULL);
	for (i = 0; i < sizeof(rgb)/sizeof(rgb[0]); i++) {
		if (!rgb[i]) {
			rgb[i] = gdk_rgba_copy(&default_gradient_color[i]);
		}
	}

	// draw surface with led's switched on
    float bars = hrz ? width - 2*lb : height - 2*lb; // size of only the leds
    float lpos = (bars - lh) / bars;
    cairo_pattern_t *pat = cairo_pattern_create_linear(
        x + lb,
        y + height - lb,
        hrz ? x + width - lb : x + lb,
        hrz ? y + height - lb : y + lb);
    cairo_pattern_add_color_stop_rgb(pat, 0, rgb[0]->red, rgb[0]->green, rgb[0]->blue);
    cairo_pattern_add_color_stop_rgb(pat, midpos, rgb[1]->red, rgb[1]->green, rgb[1]->blue);
    cairo_pattern_add_color_stop_rgb(pat, lpos, rgb[2]->red, rgb[2]->green, rgb[2]->blue);
    cairo_pattern_add_color_stop_rgb(pat, lpos + 0.0001, rgb[3]->red, rgb[3]->green, rgb[3]->blue);

    cairo_rectangle(cr, x + lb, y + lb, width - 2*lb, height - 2*lb);
    cairo_set_source(cr, pat);
    cairo_fill(cr);

	// bar dimension (without led borders)
	GdkRectangle& bar = fm->priv->bar;
    bar.x      = x + lb;
    bar.y      = y + lb;
    bar.width  = width - 2*lb;
    bar.height = height - 2*lb;

    // led borders
    GtkStyleContext *entry_context = gx_get_entry_style_context(); //FIXME
    int max = hrz ? width : height;
    for (int j = 0; j < max; j += lh + lb) {
        gtk_render_background(entry_context, cr,
            x + (hrz ? j : 0),
            y + (hrz ? 0 : j),
            hrz ? lb : width,
            hrz ? height : lb);
    }
    for (int j = 1; j < dim; j++) {
        gtk_render_background(entry_context, cr,
            x + (hrz ? 0 : j * (lb + lw)),
            y + (hrz ? j * (lb + lw) : 0),
            hrz ? width : lb,
            hrz ? lb : height);
    }

    // inset
    if (hrz) {
        gx_draw_inset(cr, x, y, width, height, rad, 1);
    } else {
        gx_draw_inset(cr, x + 1, y + 1, width, height, rad, 0.5);
	}
    // copy bar to overlay
    fm->priv->overlay = cairo_image_surface_create(
		CAIRO_FORMAT_ARGB32, bar.width, bar.height);
	if (cairo_surface_status(fm->priv->overlay) != CAIRO_STATUS_SUCCESS) {
		cairo_surface_destroy(fm->priv->surface);
		fm->priv->surface = nullptr;
		fm->priv->overlay = nullptr;
		return;
	}
    cairo_t *co;
    co = cairo_create(fm->priv->overlay);
    cairo_set_source_surface(co, fm->priv->surface, -bar.x, -bar.y);
    cairo_paint(co);

	// dim the bar on the surface (not on the overlay)
    cairo_rectangle(cr, x, y, width, height);
    cairo_set_source_rgba(cr, 0., 0., 0., 0.8);
    cairo_fill(cr);

	for (i = 0; i < sizeof(rgb)/sizeof(rgb[0]); i++) {
        gdk_rgba_free(rgb[i]);
	}
    g_object_unref(entry_context);
    cairo_destroy(cr);
    cairo_destroy(co);
    cairo_pattern_destroy(pat);
}

/* -------------- */
/* EOF */

// Local Variables:
// tab-width: 4
// End:

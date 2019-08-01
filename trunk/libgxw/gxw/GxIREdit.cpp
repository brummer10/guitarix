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

#include "GxIREdit.h"
#include "GxGradient.h"

#include <math.h>
#include <assert.h>
#include <string.h>

#define I_(x)  x  //FIXME whats this??
#define P_(s) (s)   // FIXME -> gettext

#ifndef min
#define min(x, y) ((x) < (y) ? (x) : (y))
#endif
#ifndef max
#define max(x, y) ((x) < (y) ? (y) : (x))
#endif
#ifndef abs
#define abs(x) ((x) < 0 ? -(x) : (x))
#endif

/* Inspired by GLib */
void gx_cclosure_marshal_VOID__INT_INT(GClosure *closure,
									   GValue *return_value,
									   guint n_param_values,
									   const GValue *param_values,
									   gpointer invocation_hint,
									   gpointer marshal_data)
{
	typedef void (*GMarshalFunc_VOID__INT_INT)(gpointer data1,
												gint arg_1,
												gint arg_2,
												gpointer data2);
	GMarshalFunc_VOID__INT_INT callback;
	GCClosure *cc = (GCClosure*)closure;
	gpointer data1, data2;

	g_return_if_fail(n_param_values == 3);

	if (G_CCLOSURE_SWAP_DATA(closure)) {
		data1 = closure->data;
		data2 = g_value_peek_pointer(param_values + 0);
    } else {
		data1 = g_value_peek_pointer(param_values + 0);
		data2 = closure->data;
    }
	callback = (GMarshalFunc_VOID__INT_INT)(marshal_data ? marshal_data : cc->callback);

	callback(data1,
			 g_value_get_int(param_values + 1),
			 g_value_get_int(param_values + 2),
			 data2);
}


G_DEFINE_TYPE(GxIREdit, gx_ir_edit, GTK_TYPE_DRAWING_AREA);

static void gx_ir_edit_destroy(GtkWidget*);
static gboolean ir_edit_event_draw(GtkWidget*, cairo_t*);
static gboolean ir_edit_button_press(GtkWidget *widget, GdkEventButton *event);
static gboolean ir_edit_button_release(GtkWidget *widget, GdkEventButton *event);
static gboolean ir_edit_motion_notify(GtkWidget *widget, GdkEventMotion *event);
static gboolean ir_edit_scroll(GtkWidget *widget, GdkEventScroll *event);
static gboolean ir_edit_configure(GtkWidget *widget, GdkEventConfigure *event);
static void ir_edit_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec);
static void ir_edit_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec);

static void ir_edit_set_scale(GxIREdit *ir_edit, gdouble scale, gint scroll_center);
static void next_regular_tick(GxIREdit *ir_edit, gdouble calc_tick);
static void ir_edit_precalc(GxIREdit *ir_edit);

#define FP_EQUAL(x, y) (fabs((x)-(y)) < 1e-14)

enum {
	MODE_NONE,
	MODE_BODY,
	MODE_SHIFT,
	MODE_SCROLL,
	MODE_LINE,
	MODE_MARKER,
};

enum {
	DELAY_CHANGED,
	OFFSET_CHANGED,
	LENGTH_CHANGED,
	SCALE_MAX_REACHED,
	SCALE_MIN_REACHED,
	LAST_SIGNAL
};

enum {
	PROP_Y_BORDER_TOP = 1,
	PROP_Y_BORDER_BOTTOM,
	PROP_X_BORDER,
	PROP_LABEL_SEP,
	PROP_DOT_DIAMETER,
	PROP_SEGMENT_DISTANCE,
	PROP_LIMIT,
	PROP_FS,
	PROP_MAX_SCALE_FACT,
	PROP_MIN_SCALE,
	PROP_SCALE,
	PROP_NO_DATA_TEXT,
};

static guint signals[LAST_SIGNAL];

static void gx_ir_edit_class_init(GxIREditClass* klass)
{
	GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
	GtkWidgetClass* widget_class = (GtkWidgetClass*)klass;

	/* class signal handler */
	gobject_class->set_property = ir_edit_set_property;
	gobject_class->get_property = ir_edit_get_property;

	widget_class->destroy = gx_ir_edit_destroy;
	widget_class->configure_event = ir_edit_configure;
	widget_class->draw = ir_edit_event_draw;
	widget_class->motion_notify_event = ir_edit_motion_notify;
	widget_class->button_press_event = ir_edit_button_press;
	widget_class->button_release_event = ir_edit_button_release;
	widget_class->scroll_event = ir_edit_scroll;

	/* new signals */
	signals[DELAY_CHANGED] =
		g_signal_new(I_("delay-changed"),
		             G_TYPE_FROM_CLASS(gobject_class),
		             GSignalFlags(G_SIGNAL_RUN_FIRST | G_SIGNAL_NO_RECURSE),
		             0,
		             NULL, NULL,
		             gx_cclosure_marshal_VOID__INT_INT,
		             G_TYPE_NONE, 2,
		             G_TYPE_INT, G_TYPE_INT);
	signals[OFFSET_CHANGED] =
		g_signal_new(I_("offset-changed"),
		             G_TYPE_FROM_CLASS(gobject_class),
		             GSignalFlags(G_SIGNAL_RUN_FIRST | G_SIGNAL_NO_RECURSE),
		             0,
		             NULL, NULL,
		             gx_cclosure_marshal_VOID__INT_INT,
		             G_TYPE_NONE, 2,
		             G_TYPE_INT, G_TYPE_INT);
	signals[LENGTH_CHANGED] =
		g_signal_new(I_("length-changed"),
		             G_TYPE_FROM_CLASS(gobject_class),
		             GSignalFlags(G_SIGNAL_RUN_FIRST | G_SIGNAL_NO_RECURSE),
		             0,
		             NULL, NULL,
		             gx_cclosure_marshal_VOID__INT_INT,
		             G_TYPE_NONE, 2,
		             G_TYPE_INT, G_TYPE_INT);
	signals[SCALE_MAX_REACHED] =
		g_signal_new(I_("scale-max-reached"),
		             G_TYPE_FROM_CLASS(gobject_class),
		             G_SIGNAL_RUN_LAST,
		             0,
		             NULL, NULL,
		             g_cclosure_marshal_VOID__BOOLEAN,
		             G_TYPE_NONE, 1,
		             G_TYPE_BOOLEAN);
	signals[SCALE_MIN_REACHED] =
		g_signal_new(I_("scale-min-reached"),
		             G_TYPE_FROM_CLASS(gobject_class),
		             G_SIGNAL_RUN_LAST,
		             0,
		             NULL, NULL,
		             g_cclosure_marshal_VOID__BOOLEAN,
		             G_TYPE_NONE, 1,
		             G_TYPE_BOOLEAN);

	/* properties */
	g_object_class_install_property(
		gobject_class, PROP_Y_BORDER_TOP, g_param_spec_int(
			"y-border-top", P_("top border"),
			P_("area above x axis at the top of the window"),
			0, G_MAXINT, 5, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_Y_BORDER_BOTTOM, g_param_spec_int(
			"y-border-bottom", P_("bottom border"),
			P_(NULL),
			0, G_MAXINT, 10, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_X_BORDER, g_param_spec_int(
			"x-border", P_("right border"),
			P_(NULL),
			0, G_MAXINT, 5, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_LABEL_SEP, g_param_spec_int(
			"label-sep", P_("label sep"),
			P_(NULL),
			0, G_MAXINT, 4, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_DOT_DIAMETER, g_param_spec_double(
			"dot-diameter", P_("dot diameter"),
			P_(NULL),
			0, G_MAXDOUBLE, 5.0, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_SEGMENT_DISTANCE, g_param_spec_double(
			"segment-distance", P_("hit distance"),
			P_(NULL),
			0, G_MAXDOUBLE, 2.0, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_LIMIT, g_param_spec_double(
			"limit", P_("limit"),
			P_(NULL),
			0, G_MAXDOUBLE, 5.0, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_FS, g_param_spec_int(
			"fs", P_("samplerate"),
			P_(NULL),
			0, G_MAXINT, 4, GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_MAX_SCALE_FACT, g_param_spec_double(
			"max-scale-fact", P_("max scale fact"),
			P_(NULL),
			0, G_MAXDOUBLE, 50.0, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_MIN_SCALE, g_param_spec_double(
			"min-scale", P_("min scale"),
			P_(NULL),
			0, G_MAXDOUBLE, 0.02, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_SCALE, g_param_spec_double(
			"scale", P_("scale"),
			P_(NULL),
			0, G_MAXDOUBLE, 1.0, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
	g_object_class_install_property(
		gobject_class, PROP_NO_DATA_TEXT,
		g_param_spec_string("no-data-text",
		                    P_("no data text"),
		                    P_("text displayed when no data is available"),
		                    "NO DATA",
		                    GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));

	/* style properties */
	gtk_widget_class_install_style_property(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_boxed ("zoom-marker-color",
		                    P_("Zoom marker color"),
		                    P_("Color of zoom marker"),
		                    GDK_TYPE_COLOR,
		                    GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)));
	gtk_widget_class_install_style_property_parser(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_boxed ("no-data-color",
		                    P_("No data color"),
		                    P_("Color of graph background when no data is available"),
		                    GX_TYPE_RGBA,
		                    GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)),
		gx_parse_rgba);
	gtk_widget_class_install_style_property_parser(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_boxed ("sample-graph-color",
		                    P_("Sample graph color"),
		                    P_("Color of graph with sampled values"),
		                    GX_TYPE_RGBA,
		                    GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)),
		gx_parse_rgba);
	gtk_widget_class_install_style_property_parser(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_boxed ("sample-graph-color-out",
		                    P_("Sample graph color outside"),
		                    P_("Color of graph outside of cut region"),
		                    GX_TYPE_RGBA,
		                    GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)),
		gx_parse_rgba);
	gtk_widget_class_install_style_property_parser(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_boxed ("gain-line-color",
		                    P_("Gain line color"),
		                    P_("Color of gain line"),
		                    GX_TYPE_RGBA,
		                    GParamFlags(G_PARAM_READABLE|G_PARAM_STATIC_STRINGS)),
		gx_parse_rgba);
	gtk_widget_class_install_style_property(
		GTK_WIDGET_CLASS(klass),
		g_param_spec_double(
			"shade-alpha", P_("Shade alpha value"),
			P_("Alpha Value for shading outside of cut region"),
			0, 1, 0.1, GParamFlags(G_PARAM_READWRITE|G_PARAM_STATIC_STRINGS)));
}

static gdouble ir_edit_get_default_scale(GxIREdit *ir_edit)
{
	if (!ir_edit->graph_x) {
		return 0.0;
	}
	return (ir_edit->odata_len+max(0.0,ir_edit->offset)) / (double)(ir_edit->graph_x);
}

static void ir_edit_set_default_scale(GxIREdit *ir_edit)
{
	gdouble s = ir_edit_get_default_scale(ir_edit);
	ir_edit->scale_a[0] = s;
	ir_edit->scale_a[1] = s/10;
	ir_edit->scale_num = 0;
	if (ir_edit->scale != s) {
		ir_edit_set_scale(ir_edit, s, -1);
		next_regular_tick(ir_edit, ir_edit->label_width*ir_edit->scale/ir_edit->fs);
		ir_edit_precalc(ir_edit);
	}
}

static void next_regular_tick(GxIREdit *ir_edit, gdouble calc_tick)
{
	calc_tick = fabs(calc_tick);
	gdouble p = floor(log10(calc_tick));
	gchar s[20];
	snprintf(s, sizeof(s), "%%.%df", max(0, int(-p) - 3));
	gdouble e = pow(10,p);
	calc_tick /= e;
	if (calc_tick < 1.5) {
		;
	} else if (calc_tick < 3.0) {
		e = 2*e;
	} else if (calc_tick < 7.0) {
		e = 5*e;
	} else {
		snprintf(s, sizeof(s), "%%.%df", max(0, int(-p) - 4));
		e = 10*e;
	}
	ir_edit->tick = e;
	if (ir_edit->fmt) {
		g_free(ir_edit->fmt);
	}
	ir_edit->fmt = g_strdup(s);
}

static void ir_edit_precalc(GxIREdit *ir_edit)
{
	if (!ir_edit->width) {
		return;
	}
	if (ir_edit->scale <= ir_edit->limit) {
		ir_edit->bdata = NULL;
		ir_edit->bdata_len = 0;
		return;
	}
	int n = (int)(ceil(ir_edit->odata_len/ir_edit->scale));
	float *l = (float*)g_malloc(sizeof(float)*2*n);
	int t = 0;
	int j = 0;
	for (int i = 0; i < n; i++) {
		float mn = 1000000.0;
		float mx = -1000000.0;
		while (t < ir_edit->odata_len) {
			if (t >= (i+0.5)*ir_edit->scale) {
				break;
			}
			float v = (ir_edit->data[t]-ir_edit->max_y)*ir_edit->scale_height;
			if (v < mn) {
					mn = v;
				}
				if (v > mx) {
				mx = v;
			}
			t += 1;
		}
		assert(j < 2*n);
		l[j] = mn;
		l[j+1] = mx;
		j += 2;
	}
	assert(j == 2*n);
	if (ir_edit->bdata) {
		g_free(ir_edit->bdata);
	}
	ir_edit->bdata = l;
	ir_edit->bdata_len = n;
}

static void ir_edit_reconfigure(GxIREdit *ir_edit)
{
	if (!ir_edit->width) {
		return;
	}
	gboolean home_pos = (FP_EQUAL(ir_edit->scale, ir_edit_get_default_scale(ir_edit)) &&
	                     ir_edit->current_offset == min(0, int(floor(-ir_edit->offset/ir_edit->scale))));
	ir_edit->x_off = (int)(ir_edit->text_width+ir_edit->label_sep+ir_edit->x_border);
	ir_edit->y_off = ir_edit->text_height+ir_edit->y_border_top;
	ir_edit->graph_x = ir_edit->width-ir_edit->x_off-ir_edit->x_border;
	ir_edit->graph_y = ir_edit->height-ir_edit->y_off-ir_edit->y_border_bottom;
	ir_edit->scale_height = -ir_edit->graph_y/(ir_edit->max_y-ir_edit->min_y);
	if (ir_edit->data) {
		if (!ir_edit->scale) {
			gx_ir_edit_home(ir_edit);
		} else {
			next_regular_tick(ir_edit, ir_edit->label_width*ir_edit->scale/ir_edit->fs);
			ir_edit_precalc(ir_edit);
			if (home_pos) {
				gx_ir_edit_home(ir_edit);
			}
		}
	}
}

static void ir_edit_set_scale(GxIREdit *ir_edit, gdouble scale, gint scroll_center)
{
	if (FP_EQUAL(scale, ir_edit->scale)) {
		return;
	}
	gdouble mx = ir_edit->odata_len / ir_edit->max_scale_fact;
	if (scale == 0.0) {
		g_signal_emit_by_name(ir_edit,"scale-min-reached", TRUE);
		g_signal_emit_by_name(ir_edit,"scale-max-reached", TRUE);
		ir_edit->scale = scale;
		return;
	}
	if (ir_edit->scale == 0.0) {
		g_signal_emit_by_name(ir_edit,"scale-min-reached", FALSE);
		g_signal_emit_by_name(ir_edit,"scale-max-reached", FALSE);
	}
	if (scale <= ir_edit->min_scale) {
		scale = ir_edit->min_scale;
		g_signal_emit_by_name(ir_edit,"scale-min-reached", TRUE);
	} else if (scale >= mx) {
		scale = mx;
		g_signal_emit_by_name(ir_edit,"scale-max-reached", TRUE);
	}
	if (FP_EQUAL(ir_edit->scale, scale)) {
		return;
	}
	if (FP_EQUAL(ir_edit->scale, ir_edit->min_scale)) {
		g_signal_emit_by_name(ir_edit,"scale-min-reached", FALSE);
	} else if (FP_EQUAL(ir_edit->scale, mx)) {
		g_signal_emit_by_name(ir_edit,"scale-max-reached", FALSE);
	}
	if (scroll_center > -1) {
		ir_edit->scroll_center = scroll_center;
	}
	if (ir_edit->scale != 0) {
		ir_edit->current_offset += int(ir_edit->scroll_center*(1/scale-1/ir_edit->scale));
	}
	ir_edit->scale = scale;
	ir_edit_reconfigure(ir_edit);
	gtk_widget_queue_draw(GTK_WIDGET(ir_edit));
	g_object_notify(G_OBJECT(ir_edit), "scale");
}


static void ir_edit_set_cutoff_low(GxIREdit *ir_edit, gint cutoff_low)
{
	gint old = ir_edit->cutoff_low;
	ir_edit->cutoff_low = cutoff_low;
	if (max(old, -ir_edit->offset) != max(cutoff_low, -ir_edit->offset)) {
		g_signal_emit_by_name(ir_edit,"offset-changed", max(ir_edit->cutoff_low,-ir_edit->offset), ir_edit->fs);
		g_signal_emit_by_name(ir_edit,"length-changed", ir_edit->cutoff_high-max(ir_edit->cutoff_low,-ir_edit->offset), ir_edit->fs);
	}
	if (ir_edit->offset+ir_edit->cutoff_low > 0) {
		g_signal_emit_by_name(ir_edit,"delay-changed", ir_edit->offset+ir_edit->cutoff_low, ir_edit->fs);
	}
}

static void ir_edit_set_cutoff_high(GxIREdit *ir_edit, gint cutoff_high)
{
	ir_edit->cutoff_high = cutoff_high;
	g_signal_emit_by_name(
		ir_edit, "length-changed",
		ir_edit->cutoff_high-max(ir_edit->cutoff_low,-ir_edit->offset),
		ir_edit->fs);
}

static void ir_edit_set_offset(GxIREdit *ir_edit, int v)
{
	if (ir_edit->offset == v) {
		return;
	}
	int old = ir_edit->offset;
	ir_edit->offset = v;
	if (v+ir_edit->cutoff_low >= 0 || old+ir_edit->cutoff_low > 0) {
		g_signal_emit_by_name(ir_edit,"delay-changed", max(v+ir_edit->cutoff_low,0), ir_edit->fs);
	}
	if (max(ir_edit->cutoff_low, -old) != max(ir_edit->cutoff_low, -v)) {
		int off = max(ir_edit->cutoff_low, -v);
		g_signal_emit_by_name(ir_edit,"offset-changed", off, ir_edit->fs);
		g_signal_emit_by_name(ir_edit,"length-changed", ir_edit->cutoff_high - off, ir_edit->fs);
	}
}

static void ir_edit_reset(GxIREdit *ir_edit)
{
	// presentation parameters
	ir_edit->chan = -1;
	ir_edit->current_offset = 0;
	ir_edit->linear = FALSE;
	ir_edit->scroll_center = 0;
	ir_edit_set_scale(ir_edit, 0.0, -1);
	// output parameters
	ir_edit->cutoff_high = 0;
	ir_edit->offset = 0;
	ir_edit_set_cutoff_low(ir_edit, 0);
	g_free(ir_edit->gains);
	ir_edit->gains = NULL;
	ir_edit->gains_len = 0;
}

static void ir_edit_configure_axes(GxIREdit *ir_edit)
{
	if (ir_edit->linear) {
		ir_edit->min_y = -1.0;
		ir_edit->max_y = 1.0;
		ir_edit->y_lines = 5;
		ir_edit->fmt_y = "%.1f";
	} else {
		ir_edit->min_y = -120.0;
		ir_edit->max_y = 0.0;
		ir_edit->y_lines = 7;
		ir_edit->fmt_y = "%.0f";
	}
}

static void gx_ir_edit_init(GxIREdit *ir_edit)
{
	ir_edit->y_border_top = 5;
	ir_edit->y_border_bottom = 10;
	ir_edit->x_border = 5;
	ir_edit->label_sep = 4;
	ir_edit->dot_diameter = 5.0;
	ir_edit->segment_distance = 2.0;
	ir_edit->limit = 5.0;
	ir_edit->max_scale_fact = 50.0;
	ir_edit->min_scale = 0.02;
	ir_edit->no_data_text = g_strdup("");
	ir_edit->button = -1;
	ir_edit->buffered = TRUE;
	ir_edit_reset(ir_edit);
	ir_edit_configure_axes(ir_edit);
	gtk_widget_set_double_buffered(GTK_WIDGET(ir_edit), FALSE);
	gtk_widget_add_events(GTK_WIDGET(ir_edit), GDK_POINTER_MOTION_MASK|GDK_POINTER_MOTION_HINT_MASK|GDK_BUTTON_PRESS_MASK|GDK_BUTTON_RELEASE_MASK);
	GdkDisplay *disp = gtk_widget_get_display(GTK_WIDGET(ir_edit));
	ir_edit->cursor[MODE_NONE] = NULL;
	ir_edit->cursor[MODE_BODY] = NULL;
	ir_edit->cursor[MODE_SCROLL] = NULL;
	ir_edit->cursor[MODE_MARKER] = gdk_cursor_new_for_display(disp, GDK_FLEUR);
	ir_edit->cursor[MODE_LINE] = gdk_cursor_new_for_display(disp, GDK_PLUS);
	ir_edit->cursor[MODE_SHIFT] = gdk_cursor_new_for_display(disp, GDK_SB_H_DOUBLE_ARROW);
}

static void gx_ir_edit_destroy(GtkWidget* object)
{
	GxIREdit *ir_edit = GX_IR_EDIT(object);
	unsigned int i;
	for (i = 0; i < sizeof(ir_edit->cursor)/sizeof(ir_edit->cursor[0]); i++) {
		if (ir_edit->cursor[i]) {
			gdk_cursor_unref(ir_edit->cursor[i]);
			ir_edit->cursor[i] = NULL;
		}
	}
	GTK_WIDGET_CLASS(gx_ir_edit_parent_class)->destroy(object);
}

static void get_color(GxIREdit *ir_edit, GxRgba *clr, const char *name, GxRgba *dflt)
{
	GxRgba *tmp;
	gtk_widget_style_get(GTK_WIDGET(ir_edit), name, &tmp, NULL);
	if (tmp) {
		*clr = *tmp;
		gx_rgba_free(tmp);
	} else {
		*clr = *dflt;
	}
}

static GxRgba sample_graph_color = { 1.0, 0.0, 0.0, 1.0 };
static GxRgba sample_graph_color_out = { 0.0, 0.0, 0.0, 0.3 };
static GxRgba no_data_color = { 1.0, 1.0, 1.0, 0.6 };

#define COLOR_BG 0
#define COLOR_FG 1
#define COLOR_TEXT 2

static void set_color_from_style(cairo_t *c, GxIREdit *ir_edit, gint type, double alpha)
{
	GtkStyle *s = gtk_widget_get_style(GTK_WIDGET(ir_edit));
	GdkColor *clr;
	switch (type) {
	case COLOR_BG: clr = s->bg; break;
	case COLOR_FG: clr = s->fg; break;
	case COLOR_TEXT: clr = s->text; break;
	default:
		assert(FALSE);
		return;
	}
	cairo_set_source_rgba(
		c, clr->red / 65535., clr->green / 65535., clr->blue / 65535., alpha);
}

static void ir_edit_paint_no_data(GxIREdit *ir_edit, cairo_t *c)
{
	GxRgba clr;
	cairo_save(c);
	get_color(ir_edit, &clr, "no-data-color", &no_data_color);
	cairo_set_source_rgba(c, clr.red, clr.green, clr.blue, clr.alpha);
	cairo_paint(c);
	set_color_from_style(c, ir_edit, COLOR_TEXT, 1.0);
	PangoLayout *l = pango_cairo_create_layout(c);
	pango_layout_set_markup(l,ir_edit->no_data_text,-1);
	pango_layout_set_width(l,(ir_edit->graph_x)*PANGO_SCALE);
	pango_layout_set_alignment(l,PANGO_ALIGN_CENTER);
	gint width, height;
	pango_layout_get_pixel_size(l,&width,&height);
	cairo_move_to(c,0,max(0,(ir_edit->graph_y-height)/2.0));
	pango_cairo_show_layout(c,l);
	g_object_unref(l);
	cairo_restore(c);
}

static void ir_edit_draw_direct(GxIREdit *ir_edit, cairo_t *c, int start, int end)
{
	GxRgba clr, clr_out;
	get_color(ir_edit, &clr, "sample-graph-color", &sample_graph_color);
	get_color(ir_edit, &clr_out, "sample-graph-color-out", &sample_graph_color_out);
	start = int(round(start * ir_edit->scale)) - 1;
	end = int(round(end * ir_edit->scale)) + 2;
	if (end > ir_edit->odata_len) {
		end = ir_edit->odata_len;
	}
	if (start < 0) {
		start = 0;
	}
	gboolean out = (start < ir_edit->cutoff_low || start >= ir_edit->cutoff_high);
	if (out) {
		cairo_set_source_rgba(c, clr_out.red, clr_out.green, clr_out.blue, clr_out.alpha);
	} else {
		cairo_set_source_rgba(c, clr.red, clr.green, clr.blue, clr.alpha);
	}
	gboolean first = TRUE;
	for (int i = start; i <= end; i++) {
		double j = round(i / ir_edit->scale) - ir_edit->current_offset + 0.5;
		double v;
		if (i >= ir_edit->odata_len) {
			v = ir_edit->data[ir_edit->odata_len-1];
		} else {
			v = ir_edit->data[i];
		}
		v = (v-ir_edit->max_y)*ir_edit->scale_height;
		if (first) {
			cairo_move_to(c, j, v);
			first = FALSE;
		} else {
			cairo_line_to(c, j, v);
		}
		if (out != (i < ir_edit->cutoff_low || i >= ir_edit->cutoff_high)) {
			cairo_stroke(c);
			cairo_move_to(c, j, v);
			out = !out;
			if (out) {
				cairo_set_source_rgba(c, clr_out.red, clr_out.green, clr_out.blue, clr_out.alpha);
			} else {
				cairo_set_source_rgba(c, clr.red, clr.green, clr.blue, clr.alpha);
			}
		}
	}
	cairo_stroke(c);
}

static void ir_edit_draw_accum(GxIREdit *ir_edit, cairo_t *c, int start, int end)
{
	GxRgba clr, clr_out;
	get_color(ir_edit, &clr, "sample-graph-color", &sample_graph_color);
	get_color(ir_edit, &clr_out, "sample-graph-color-out", &sample_graph_color_out);
	cairo_set_source_rgba(c, clr.red, clr.green, clr.blue, clr.alpha);
	start -= 1;
	end += 1;
	if (end > ir_edit->bdata_len) {
		end = ir_edit->bdata_len;
	}
	if (start < 0) {
		start = 0;
	}
	double cutoff_low = ir_edit->cutoff_low / ir_edit->scale;
	double cutoff_high = ir_edit->cutoff_high / ir_edit->scale;
	gboolean out = (start < cutoff_low || start >= cutoff_high);
	if (out) {
		cairo_set_source_rgba(c, clr_out.red, clr_out.green, clr_out.blue, clr_out.alpha);
	} else {
		cairo_set_source_rgba(c, clr.red, clr.green, clr.blue, clr.alpha);
	}
	gboolean first = TRUE;
	int n = 2*start;
	for (int i = start; i < end; i++) {
		double mn = ir_edit->bdata[n++];
		double mx = ir_edit->bdata[n++];
		double j = i - ir_edit->current_offset + 0.5;
		if (first) {
			cairo_move_to(c, j, mn);
			first = FALSE;
		} else {
			cairo_line_to(c, j, mn);
		}
		if (out != (i < cutoff_low || i >= cutoff_high)) {
			cairo_stroke(c);
			cairo_move_to(c, j, mn);
			out = !out;
			if (out) {
				cairo_set_source_rgba(c, clr_out.red, clr_out.green, clr_out.blue, clr_out.alpha);
			} else {
				cairo_set_source_rgba(c, clr.red, clr.green, clr.blue, clr.alpha);
			}
		}
		cairo_line_to(c, j, mx);
	}
	cairo_stroke(c);
}

static void ir_edit_draw(GxIREdit *ir_edit, cairo_t *c)
{
	if (!ir_edit->data) {
		return;
	}
	cairo_rectangle(c, 0, 0, ir_edit->graph_x, ir_edit->graph_y);
	cairo_save(c);
	cairo_clip(c);
	double x1, y1, x2, y2;
	cairo_clip_extents(c, &x1, &y1, &x2, &y2);
	if (x2 > x1 && y2 > y1) {
		int start = int(floor(x1 + ir_edit->current_offset));
		int end = start + int(ceil(x2-x1));
		if (ir_edit->scale <= ir_edit->limit) {
			ir_edit_draw_direct(ir_edit, c, start, end);
		} else {
			ir_edit_draw_accum(ir_edit, c, start, end);
		}
	}
	cairo_restore(c);
}

static double text_width(cairo_t *c, const char *t)
{
	cairo_text_extents_t ext;
	cairo_text_extents(c, t, &ext);
	return int(ceil(ext.width+ext.x_bearing));
}

static void ir_edit_vertical_ticks(GxIREdit *ir_edit, cairo_t *c)
{
	// vertical lines with labels
	double shade_alpha;
	gtk_widget_style_get(GTK_WIDGET(ir_edit), "shade-alpha", &shade_alpha, NULL);
	cairo_save(c);
	cairo_rectangle(c,-ir_edit->label_width/2.0, -ir_edit->y_off,
	                ir_edit->graph_x+ir_edit->label_width/2.0+ir_edit->x_border,
	                ir_edit->graph_y+ir_edit->y_off);
	cairo_clip(c);
	double x1, y1, x2, y2;
	cairo_clip_extents(c, &x1, &y1, &x2, &y2);
	if (x1 >= x2 || y1 >= y2) {
		cairo_restore(c);
		return;
	}
	int start = max(0, (int)(x1-ir_edit->label_width/2.0));
	int end = max(ir_edit->graph_x, (int)x2);
	double d = ir_edit->tick * ir_edit->fs;
	if (d == 0.0) {
		d = 50.0;
	}
	double scale = ir_edit->scale;
	if (scale == 0.0) {
		scale = 1.0;
	}
	const char *fmt = ir_edit->fmt;
	if (!fmt) {
		fmt = "%.0f";
	}
	double tick = ir_edit->tick;
	if (!tick) {
		tick = 0.05;
	}
	double off = ((ir_edit->current_offset+start)*scale+ir_edit->offset)/d;
	int tt = int(ceil(off));
	while (TRUE) {
		double ttt = (tt*d-ir_edit->offset)/scale - ir_edit->current_offset;
		if (ttt > end) {
			break;
		}
		//cairo_set_source_rgba(c,0.0, 0.0, 0.0, 0.4);
		set_color_from_style(c, ir_edit, COLOR_TEXT, 0.4);
		if (tt == 0) {
			//cairo_set_source_rgb(c,0.0,0.0,0.0);
			set_color_from_style(c, ir_edit, COLOR_TEXT, 1.0);
		}
		ttt = int(ttt)+0.5;
		cairo_move_to(c,ttt, 0.0);
		cairo_line_to(c,ttt, ir_edit->scale_height*(ir_edit->min_y-ir_edit->max_y));
		cairo_stroke(c);
		char t[100];
		snprintf(t, sizeof(t), fmt, tt*tick*1000);
		double tw = text_width(c, t)+1;
		cairo_move_to(c,ttt-tw/2.0, -2.0);
		//cairo_set_source_rgb(c,0.0,0.0,0.0);
		set_color_from_style(c, ir_edit, COLOR_TEXT, 1.0);
		cairo_show_text(c,t);
		tt += 1;
	}
	cairo_restore(c);
	cairo_save(c);
	cairo_rectangle(c,0, 0, ir_edit->graph_x, ir_edit->graph_y);
	cairo_clip(c);
	int s = int(round(ir_edit->cutoff_low/scale));
	cairo_move_to(c,s - ir_edit->current_offset + 0.5, 0);
	cairo_rel_line_to(c,0, ir_edit->graph_y);
	//cairo_set_source_rgb(c,0,0,0);
	set_color_from_style(c, ir_edit, COLOR_TEXT, 1.0);
	cairo_stroke(c);
	cairo_rectangle(c,0, 0, -ir_edit->offset/scale - ir_edit->current_offset, ir_edit->graph_y);
	//cairo_set_source_rgba(c,0,0,0,0.1);
	set_color_from_style(c, ir_edit, COLOR_BG, shade_alpha);
	cairo_fill(c);
	s = int(round(ir_edit->cutoff_high/scale));
	cairo_move_to(c,s-ir_edit->current_offset+0.5, 0);
	cairo_rel_line_to(c,0, ir_edit->graph_y);
	//cairo_set_source_rgb(c,0,0,0);
	set_color_from_style(c, ir_edit, COLOR_TEXT, 1.0);
	cairo_stroke(c);
	cairo_restore(c);
}

static void ir_edit_horizontal_ticks(GxIREdit *ir_edit, cairo_t *c)
{
	// horizontal lines with labels
	cairo_rectangle(c,-ir_edit->x_off+ir_edit->x_border, -ir_edit->text_height/2.0,
	                ir_edit->graph_x+ir_edit->x_off-ir_edit->x_border,
	                ir_edit->graph_y+ir_edit->text_height);
	cairo_save(c);
	cairo_clip(c);
	double x1, y1, x2, y2;
	cairo_clip_extents(c, &x1, &y1, &x2, &y2);
	if (x1 < 0) {
		//cairo_set_source_rgb(c,1.0,1.0,1.0);
		set_color_from_style(c, ir_edit, COLOR_BG, 1.0);
		cairo_rectangle(c,-ir_edit->x_off, 0, ir_edit->x_off, ir_edit->height - ir_edit->y_off);
		cairo_fill(c);
		if (!ir_edit->linear) {
			//cairo_set_source_rgb(c,0.0,0.0,0.0);
			set_color_from_style(c, ir_edit, COLOR_TEXT, 1.0);
			double tw = text_width(c, "dB");
			cairo_move_to(c,ir_edit->x_border-ir_edit->x_off+(ir_edit->text_width-tw)/2.0, -10.0*ir_edit->scale_height);
			cairo_show_text(c,"dB");
		}
	}
	for (int i = 0; i < ir_edit->y_lines; i++) {
		double pos = double(ir_edit->graph_y)/(ir_edit->y_lines-1)*i;
		if (ir_edit->max_y+i*(ir_edit->min_y-ir_edit->max_y)/(ir_edit->y_lines-1) == 0) {
			//cairo_set_source_rgb(c,0, 0, 0);
			set_color_from_style(c, ir_edit, COLOR_TEXT, 1.0);
		} else {
			//cairo_set_source_rgba(c,0.0, 0.0, 0.0, 0.4);
			set_color_from_style(c, ir_edit, COLOR_TEXT, 0.4);
		}
		pos = int(pos) + 0.5;
		cairo_move_to(c,0.0, pos);
		cairo_line_to(c,ir_edit->graph_x, pos);
		cairo_stroke(c);
		if (x1 >= 0) {
			if (i == 0) {
				//cairo_set_source_rgb(c,1.0,1.0,1.0);
				set_color_from_style(c, ir_edit, COLOR_BG, 1.0);
				cairo_rectangle(c,ir_edit->x_border-ir_edit->x_off, -ir_edit->text_height/2.0, ir_edit->text_width+1, ir_edit->text_height+1);
				cairo_fill(c);
			} else {
				continue;
			}
		}
		char t[100];
		snprintf(t, sizeof(t), ir_edit->fmt_y, ir_edit->max_y+i*(ir_edit->min_y-ir_edit->max_y)/(ir_edit->y_lines-1));
		double tw = text_width(c, t);
		cairo_move_to(c,ir_edit->x_border-ir_edit->x_off+ir_edit->text_width-tw, pos+ir_edit->text_height/2.0);
		//cairo_set_source_rgb(c,0.0,0.0,0.0);
		set_color_from_style(c, ir_edit, COLOR_TEXT, 1.0);
		cairo_show_text(c,t);
	}
	cairo_restore(c);
}

static void ir_edit_show_scroll_center(GxIREdit *ir_edit, cairo_t *c)
{
	if (!ir_edit->data) {
		return;
	}
	double y = ir_edit->height-ir_edit->y_off-1;
	double x = ir_edit->scroll_center / ir_edit->scale - ir_edit->current_offset;
	if (x < 0) {
		return;
	}
	if (x > ir_edit->graph_x) {
		return;
	}
	x += 0.5;
	double dx = ir_edit->y_border_bottom/2.0;
	cairo_move_to(c,x-dx, y);
	cairo_line_to(c,x+dx, y);
	cairo_line_to(c,x, ir_edit->graph_y+1);
	cairo_close_path(c);
	GdkColor *clr;
	gtk_widget_style_get(GTK_WIDGET(ir_edit), "zoom-marker-color", &clr, NULL);
	if (!clr) {
		GdkColor blue = { 0, 0, 0, 65535 };
		clr = &blue;
	}
	gdk_cairo_set_source_color(c,clr);
	cairo_stroke(c);
}

static GxRgba gain_line_color = { 0.0, 1.0, 0.0, 0.8 };

static void ir_edit_gainline(GxIREdit *ir_edit, cairo_t *c)
{
	GxRgba clr;
	get_color(ir_edit, &clr, "gain-line-color", &gain_line_color);
	double j, g;
	int n;
	gain_points *p;
	if (ir_edit->linear || !ir_edit->data) {
		return;
	}
	cairo_save(c);
	cairo_rectangle(c,0, 0, ir_edit->graph_x, ir_edit->graph_y);
	cairo_clip(c);
	cairo_set_line_width(c,1.0);
	cairo_set_source_rgba(c, clr.red, clr.green, clr.blue, clr.alpha);
	gboolean first = TRUE;
	for (p = ir_edit->gains, n = 0; n < ir_edit->gains_len; n++, p++) {
		j = int(p->i / ir_edit->scale) - ir_edit->current_offset;
		g = (p->g - ir_edit->max_y) * ir_edit->scale_height;
		if (first) {
			first = FALSE;
			cairo_move_to(c,j, g);
		} else {
			cairo_line_to(c,j, g);
		}
	}
	cairo_stroke(c);
	for (p = ir_edit->gains, n = 0; n < ir_edit->gains_len; n++, p++) {
		j = int(p->i / ir_edit->scale) - ir_edit->current_offset + 0.5;
		g = (p->g - ir_edit->max_y) * ir_edit->scale_height + 0.5;
		cairo_arc(c,j, g, ir_edit->dot_diameter, 0.0, 2.0*M_PI);
		cairo_fill(c);
	}
	cairo_restore(c);
}

static const cairo_paint_function draw_funcs[] = {
	ir_edit_draw,
	ir_edit_vertical_ticks,
	ir_edit_horizontal_ticks,
	ir_edit_show_scroll_center,
	ir_edit_gainline,
	NULL,
};

static void ir_edit_paint_area(GxIREdit *ir_edit, cairo_t *c, cairo_paint_function excl)
{
	//cairo_set_source_rgb(c, 1.0, 1.0, 1.0);
	set_color_from_style(c, ir_edit, COLOR_BG, 1.0);
	cairo_paint(c);
	cairo_set_line_width(c, 1.0);
	cairo_translate(c, ir_edit->x_off, ir_edit->y_off);
	for (const cairo_paint_function *f = draw_funcs; *f; f++) {
		if (*f != excl)
			(*f)(ir_edit, c);
	}
	if (!ir_edit->data) {
		ir_edit_paint_no_data(ir_edit, c);
	}
}

static void ir_edit_lock_surface(GxIREdit *ir_edit, cairo_paint_function excl)
{
	if (ir_edit->surface) {
		cairo_surface_destroy(ir_edit->surface);
	}
	ir_edit->surface = cairo_image_surface_create(CAIRO_FORMAT_A1, ir_edit->width, ir_edit->height);
	cairo_t *c = cairo_create(ir_edit->surface);
	ir_edit_paint_area(ir_edit, c, excl);
	cairo_destroy(c);
	ir_edit->locked = excl;
}

static gboolean ir_edit_event_draw(GtkWidget *widget, cairo_t *c)
{
	GxIREdit *ir_edit = GX_IR_EDIT(widget);
	GdkWindow *window = gtk_widget_get_window(widget);
	cairo_region_t *rgn = nullptr;
	if (ir_edit->buffered) {
		rgn = cairo_region_create();
		gdk_window_begin_paint_region(window, rgn);
	}
	cairo_save(c);
	if (ir_edit->locked) {
		gint width, height;
		width = cairo_image_surface_get_width(ir_edit->surface);
		height = cairo_image_surface_get_height(ir_edit->surface);
		if (width !=  ir_edit->width && height != ir_edit->height) {
			ir_edit_lock_surface(ir_edit, ir_edit->locked);
		}
		cairo_set_source_surface(c, ir_edit->surface, 0, 0);
		cairo_set_operator(c, CAIRO_OPERATOR_SOURCE);
		cairo_paint(c);
		cairo_set_operator(c, CAIRO_OPERATOR_OVER);
		cairo_set_line_width(c, 1.0);
		cairo_translate(c, ir_edit->x_off, ir_edit->y_off);
		ir_edit->locked(ir_edit, c);
	} else {
		ir_edit_paint_area(ir_edit, c, NULL);
	}
	if (ir_edit->buffered) {
		gdk_window_end_paint(window);
		cairo_region_destroy(rgn);
	}
	cairo_restore(c);
	return FALSE;
}

static void ir_edit_gains_delete(GxIREdit *ir_edit, int i)
{
	assert(i >= 0 && i < ir_edit->gains_len);
	ir_edit->gains_len -= 1;
	if (i == ir_edit->gains_len) {
		return;
	}
	memcpy(ir_edit->gains+i, ir_edit->gains+i+1, (ir_edit->gains_len - i) * sizeof(ir_edit->gains[0]));
}

static void ir_edit_gains_insert(GxIREdit *ir_edit, int n, int i, double g)
{
	int j = ir_edit->gains_len - n;
	assert(n >= 0 && j >= 0);
	ir_edit->gains_len += 1;
	gain_points *p = (gain_points*)g_malloc(ir_edit->gains_len * sizeof(gain_points));
	if (n) {
		memcpy(p, ir_edit->gains, n * sizeof(gain_points));
	}
	p[n].i = i;
	p[n].g = g;
	if (j) {
		memcpy(p+n+1, ir_edit->gains+n, j * sizeof(gain_points));
	}
	g_free(ir_edit->gains);
	ir_edit->gains = p;
}


// Button Event Helper

static void ir_edit_invalidate_gain_rect(GxIREdit *ir_edit, int i)
{
	if (i < 0 || i >= ir_edit->gains_len-1) {
		return;
	}
	int x1 = ir_edit->gains[i].i;
	double y1 = ir_edit->gains[i].g;
	int x2 = ir_edit->gains[i+1].i;
	double y2 = ir_edit->gains[i+1].g;
	x1 = int(floor(x1/ir_edit->scale-ir_edit->dot_diameter))-ir_edit->current_offset;
	x2 = int(ceil(x2/ir_edit->scale+ir_edit->dot_diameter))-ir_edit->current_offset;
	if (x1 < 0) {
		x1 = 0;
	}
	if (x2 > ir_edit->graph_x) {
		x2 = ir_edit->graph_x;
	}
	if (y1 < y2) {
		double t = y1;
		y1 = y2;
		y2 = t;
	}
	y1 = int(floor(y1*ir_edit->scale_height-ir_edit->max_y-ir_edit->dot_diameter));
	y2 = int(ceil(y2*ir_edit->scale_height-ir_edit->max_y+ir_edit->dot_diameter));
	if (y1 < 0) {
		y1 = 0;
	}
	if (y2 > ir_edit->graph_y) {
		y2 = ir_edit->graph_y;
	}
	GdkRectangle rect = {ir_edit->x_off+(int)x1, ir_edit->y_off+(int)y1, x2-x1, int(y2-y1)+1 };
	gdk_window_invalidate_rect(gtk_widget_get_window(GTK_WIDGET(ir_edit)), &rect, FALSE);
}

static void ir_edit_set_scroll_center_mark(GxIREdit *ir_edit, int x)
{
	if (x < ir_edit->x_off) {
		x = ir_edit->x_off;
	}
	if (x > ir_edit->width - ir_edit->x_border) {
		x = ir_edit->width - ir_edit->x_border;
	}
	x = (int)((x - ir_edit->x_off + ir_edit->current_offset) * ir_edit->scale);
	if (x < 0) {
		x = 0;
	}
	if (x >= ir_edit->odata_len) {
		x = ir_edit->odata_len - 1;
	}
	ir_edit->scroll_center = x;
	int dy = ir_edit->y_border_bottom;
	gtk_widget_queue_draw_area(GTK_WIDGET(ir_edit), ir_edit->x_off-dy, ir_edit->y_off+ir_edit->graph_y,
	                           ir_edit->graph_x+2*dy, ir_edit->y_border_bottom);
}

static void ir_edit_offset_changed(GxIREdit *ir_edit, int offset)
{
	GdkWindow *window = gtk_widget_get_window(GTK_WIDGET(ir_edit));
	int df = ir_edit->current_offset - offset;
	ir_edit->current_offset = offset;
	int sz = ir_edit->graph_x - abs(df);
	if (sz <= 0) {
		GdkRectangle rect = { 0,0,ir_edit->width,ir_edit->height };
		gdk_window_invalidate_rect(window, &rect,FALSE);
		return;
	}
	int xo = ir_edit->x_off;
	cairo_region_t *r;
	if (df > 0) {
		GdkRectangle rect = { xo, 0, sz, ir_edit->height };
		r = cairo_region_create_rectangle(&rect);
		gdk_window_move_region(window, r, df, 0);
	} else {
		GdkRectangle rect = { xo-df, 0, sz, ir_edit->height };
		r = cairo_region_create_rectangle(&rect);
		gdk_window_move_region(window, r, df, 0);
	}
	cairo_region_destroy(r);
	GdkRectangle rect1 = { xo-(int)(ir_edit->label_width/2),0,(int)ir_edit->label_width,ir_edit->y_off };
	gdk_window_invalidate_rect(window, &rect1, FALSE);
	GdkRectangle rect2 = { ir_edit->width-(int)(ir_edit->label_width/2),0,(int)ir_edit->label_width,ir_edit->y_off };
	gdk_window_invalidate_rect(window, &rect2, FALSE);
	GdkRectangle rect3 = { xo-ir_edit->y_border_bottom,ir_edit->y_off+ir_edit->graph_y,2*ir_edit->y_border_bottom,ir_edit->y_border_bottom };
	gdk_window_invalidate_rect(window, &rect3, FALSE);
	GdkRectangle rect4 = { ir_edit->width-ir_edit->x_border-ir_edit->y_border_bottom,
	                       ir_edit->y_off+ir_edit->graph_y,
	                       2*ir_edit->y_border_bottom,
	                       ir_edit->y_border_bottom };
	gdk_window_invalidate_rect(window, &rect4, FALSE);
}

static int ir_edit_hit_detect(GxIREdit *ir_edit, double x, double y, gboolean ctrl)
{
	y -= ir_edit->y_off;
	if (y < 0.0) {
		if (ctrl) {
			return MODE_NONE;
		}
		return  MODE_SHIFT;
	}
	x -= ir_edit->x_off;
	if (y > ir_edit->graph_y) {
		if (x >= -ir_edit->y_border_bottom) {
			return MODE_SCROLL;
		}
		return MODE_NONE;
	}
	if (x < 0.0 || x > ir_edit->graph_x) {
		return MODE_NONE;
	}
	if (ir_edit->linear || ctrl) {
		return MODE_BODY;
	}
	x += ir_edit->current_offset;
	y += ir_edit->max_y * ir_edit->scale_height;
	double dd = ir_edit->dot_diameter * ir_edit->dot_diameter;
	double d2 = ir_edit->segment_distance * ir_edit->segment_distance;
	double d1 = max(ir_edit->dot_diameter, ir_edit->segment_distance);
	double i0 = -1.0;
	double g0 = 0.0; // silence compiler
	int n;
	double i;
	double g;
	gain_points *p;
	for (n = 0, p = ir_edit->gains; n < ir_edit->gains_len; n++, p++) {
		// scale to (max_y-shifted) device coordinates
		i = p->i / ir_edit->scale;
		g = p->g * ir_edit->scale_height;
		double tx = i - x;
		if (tx < -d1) {
			// pointer is further to the right
			i0 = i;
			g0 = g;
			continue;
		}
		double ty = g - y;
		if (tx*tx + ty*ty <= dd) { // distance from marker
			ir_edit->mode_arg = n;
			return MODE_MARKER;
		}
		if (i0 >= 0) {
			double di = i - i0;
			double dg = g - g0;
			double num = di*ty - tx*dg;
			double den2 = di*di + dg*dg;
			if (num*num <= den2 * d2) {
				// close to line
				num = di*tx + dg*ty;
				if (num > 0) {
					den2 = di*di + dg*dg;
					if (num < den2) {
						// inside segment
						ir_edit->mode_arg = n-1;
						ir_edit->mode_arg2 = (int)(num/den2);
						return MODE_LINE;
					}
				}
			}
		}
		if (tx > d1) {
			// pointer is left of remaining segments
			break;
		}
		i0 = i;
		g0 = g;
	}
	return MODE_BODY;
}

// Button Events

static gboolean ir_edit_button_press(GtkWidget *widget, GdkEventButton *event)
{
	GxIREdit *ir_edit = GX_IR_EDIT(widget);
	if (!ir_edit->data) {
		return TRUE;
	}
	if (ir_edit->button >= 0) {
		if (! (event->type == GDK_2BUTTON_PRESS && (int)event->button == ir_edit->button)) {
			return TRUE;
		}
	}
	int r = ir_edit_hit_detect(ir_edit, event->x, event->y, event->state & GDK_CONTROL_MASK);
	ir_edit->button = event->button;
	gdk_window_set_cursor(gtk_widget_get_window(GTK_WIDGET(ir_edit)), ir_edit->cursor[r]);
	ir_edit->mode = MODE_NONE;
	if (r == MODE_LINE) {
		if (event->button == 1) {
			gain_points *p0 = &ir_edit->gains[ir_edit->mode_arg];
			gain_points *p1 = &ir_edit->gains[ir_edit->mode_arg+1];
			int u = ir_edit->mode_arg2;
			ir_edit_gains_insert(ir_edit, ir_edit->mode_arg+1, p1->i+u*(p0->i-p1->i),p1->g+u*(p0->g-p1->g));
			gdk_window_set_cursor(gtk_widget_get_window(GTK_WIDGET(ir_edit)), ir_edit->cursor[MODE_MARKER]);
			ir_edit->mode = MODE_MARKER;
			ir_edit->mode_arg += 1;
			ir_edit_lock_surface(ir_edit, ir_edit_gainline);
		}
	} else if (r == MODE_MARKER) {
		if (event->button == 1) {
			ir_edit->mode = MODE_MARKER;
			ir_edit_lock_surface(ir_edit, ir_edit_gainline);
		} else if (event->button == 3) {
			int i = ir_edit->mode_arg;
			if (i != 0 && i != ir_edit->gains_len-1) {
				ir_edit_gains_delete(ir_edit, i);
			}
			gtk_widget_queue_draw(GTK_WIDGET(ir_edit));
		}
	} else if (r == MODE_SHIFT) {
		if (event->button == 1) {
			ir_edit->mode = MODE_SHIFT;
			ir_edit->mode_arg = (int)(event->x + ir_edit->offset/ir_edit->scale);
			ir_edit_lock_surface(ir_edit, ir_edit_vertical_ticks);
		}
	} else if (r == MODE_BODY) {
		if (event->button == 1) {
			if (event->state & GDK_CONTROL_MASK) {
				int c = (int)round((event->x - ir_edit->x_off + ir_edit->current_offset) * ir_edit->scale);
				if (c >= ir_edit->cutoff_high) {
					c = ir_edit->cutoff_high - 1;
				}
				if (c < 0) {
					c = 0;
				}
				if (c != ir_edit->cutoff_low) {
					ir_edit_set_cutoff_low(ir_edit, c);
					gtk_widget_queue_draw(GTK_WIDGET(ir_edit));
				}
			} else if (event->type == GDK_2BUTTON_PRESS) {
				gx_ir_edit_home(ir_edit);
			} else {
				ir_edit->mode = MODE_BODY;
				ir_edit->mode_arg = (int)(event->x + ir_edit->current_offset);
				ir_edit->buffered = FALSE;
			}
		} else if (event->button == 3 && event->type == GDK_BUTTON_PRESS) {
			if (event->state & GDK_CONTROL_MASK) {
				int c = (int)round((event->x - ir_edit->x_off + ir_edit->current_offset) * ir_edit->scale);
				if (c <= ir_edit->cutoff_low) {
					c = ir_edit->cutoff_low + 1;
				}
				if (c > ir_edit->odata_len) {
					c = ir_edit->odata_len;
				}
				if (c != ir_edit->cutoff_high) {
					ir_edit_set_cutoff_high(ir_edit,c);
					gtk_widget_queue_draw(GTK_WIDGET(ir_edit));
				}
			} else {
				ir_edit->scale_num = !ir_edit->scale_num;
				double scale = ir_edit->scale_a[ir_edit->scale_num];
				ir_edit_set_scale(ir_edit, scale, (int)((event->x - ir_edit->x_off + ir_edit->current_offset)*ir_edit->scale));
			}
		}
	} else if (r == MODE_SCROLL) {
		ir_edit->mode = MODE_SCROLL;
		ir_edit_set_scroll_center_mark(ir_edit, (int)(event->x));
	}
	return TRUE;
}

static void ir_edit_unlock_surface(GxIREdit *ir_edit)
{
	if (ir_edit->locked) {
		ir_edit->locked = NULL;
		assert(ir_edit->surface);
		g_object_unref(ir_edit->surface);
		ir_edit->surface = NULL;
		gtk_widget_queue_draw(GTK_WIDGET(ir_edit));
	}
}

static gboolean ir_edit_button_release(GtkWidget *widget, GdkEventButton *event)
{
	GxIREdit *ir_edit = GX_IR_EDIT(widget);
	if (ir_edit->button == (int)event->button) {
		//if (ir_edit->mode == MODE_BODY) {
		//	gtk_widget_queue_draw(widget); // redraw to check for bugs in gdk_window_move_region
		//}
		ir_edit->button = -1;
		ir_edit_unlock_surface(ir_edit);
		ir_edit->mode = MODE_NONE;
		ir_edit->buffered = TRUE;
	}
	return TRUE;
}

static void ir_edit_do_motion(GxIREdit *ir_edit, GdkWindow *window, int x, int y, int state)
{
	if (ir_edit->mode == MODE_MARKER) {
		int i = ir_edit->mode_arg;
		if (i != 0 && i != ir_edit->gains_len-1) {
			x = min(max(0, x - ir_edit->x_off), ir_edit->graph_x);
			x = (int)((x + ir_edit->current_offset) * ir_edit->scale);
			if (i > 0 && ir_edit->gains[i-1].i >= x) {
				x = ir_edit->gains[i-1].i + 1;
			}
			if (i < ir_edit->gains_len-1 && ir_edit->gains[i+1].i <= x) {
				x = ir_edit->gains[i+1].i - 1;
			}
		} else {
			x = ir_edit->gains[i].i;
		}
		y = min(max(0, y - ir_edit->y_off), ir_edit->graph_y);
		ir_edit_invalidate_gain_rect(ir_edit, i-1);
		ir_edit_invalidate_gain_rect(ir_edit, i);
		ir_edit->gains[i].i = x;
		ir_edit->gains[i].g = (y + ir_edit->max_y) / ir_edit->scale_height;
	} else if (ir_edit->mode == MODE_SHIFT) {
		int offset = max(int(round((ir_edit->mode_arg - x) * ir_edit->scale)), -ir_edit->cutoff_high+1);
		if (offset != ir_edit->offset) {
			ir_edit_set_offset(ir_edit, offset);
			gtk_widget_queue_draw(GTK_WIDGET(ir_edit));
		}
	} else if (ir_edit->mode == MODE_BODY) {
		ir_edit_offset_changed(ir_edit, int(ir_edit->mode_arg - x));
	} else if (ir_edit->mode == MODE_SCROLL) {
		ir_edit_set_scroll_center_mark(ir_edit, x);
	}
	if (ir_edit->button < 0) {
		int r = ir_edit_hit_detect(ir_edit, x, y, state & GDK_CONTROL_MASK);
		gdk_window_set_cursor(window, ir_edit->cursor[r]);
	}

}

static gboolean ir_edit_motion_notify(GtkWidget *widget, GdkEventMotion *event)
{
	GdkWindow *window = gtk_widget_get_window(widget);
	GxIREdit *ir_edit = GX_IR_EDIT(widget);
	if (!ir_edit->data) {
		gdk_event_request_motions(event);
		return TRUE;
	}

	// POINTER_MOTION_HINT_MASK does not really seem to work,
	// so lets make this work-around (not clean for the general case)
	gint x, y;
	GdkModifierType m;
	gdk_window_get_pointer(window, &x, &y, &m);
	if (x != event->x || y != event->y) {
		// there shound be another event in the queue which updates
		// to the aktual pointer position, so skip this one
		gdk_event_request_motions(event);
		return TRUE;
	}

	/* skip duplicate events (due to bug?) */
	static int last_x = -1, last_y = -1;
	if (last_x == x && last_y == y) {
		gdk_event_request_motions(event);
		return TRUE;
	}
	last_x = x;
	last_y = y;

	ir_edit_do_motion(ir_edit, window, x, y, event->state);
	gdk_event_request_motions(event);
	return TRUE;
}

static gboolean ir_edit_scroll(GtkWidget *widget, GdkEventScroll *event)
{
	GxIREdit *ir_edit = GX_IR_EDIT(widget);
	if (!ir_edit->data) {
		return TRUE;
	}
	if (event->y < ir_edit->y_off || event->y > ir_edit->graph_y + ir_edit->y_off) {
		return TRUE;
	}
	int x = (int)(event->x) - ir_edit->x_off;
	if (x < 0.0 || x > ir_edit->graph_x) {
		return TRUE;
	}
	x = (int)((x + ir_edit->current_offset) * ir_edit->scale);
	double f;
	if (event->direction == GDK_SCROLL_UP) {
		f = 1.25;
	} else {
		f = 1/1.25;
	}
	ir_edit_set_scale(ir_edit, ir_edit->scale * f, x);
	return TRUE;
}

static gboolean ir_edit_configure(GtkWidget *widget, GdkEventConfigure *event)
{
	GxIREdit *ir_edit = GX_IR_EDIT(widget);
	ir_edit->width = event->width;
	ir_edit->height = event->height;
	if (!ir_edit->text_width) {
		cairo_t *c = gdk_cairo_create(gtk_widget_get_window(widget));
		cairo_text_extents_t ext;
		cairo_text_extents(c, "-100", &ext);
		cairo_destroy(c);
		ir_edit->text_height = int(ceil(ext.height));
		ir_edit->text_width = int(ceil(ext.width));
		ir_edit->label_width = 2 * ir_edit->text_width;
	}
	ir_edit_reconfigure(ir_edit);
	return TRUE;
}

static void ir_edit_set_fs(GxIREdit *ir_edit, int fs)
{
	if (ir_edit->fs == fs) {
		return;
	}
	ir_edit->fs = fs;
	g_object_notify(G_OBJECT(ir_edit),"fs");
	g_signal_emit_by_name(ir_edit,"delay-changed", max(0, ir_edit->offset+ir_edit->cutoff_low), fs);
	int off = max(ir_edit->cutoff_low,-ir_edit->offset);
	g_signal_emit_by_name(ir_edit,"offset-changed", off, fs);
	g_signal_emit_by_name(ir_edit,"length-changed", ir_edit->cutoff_high - off, fs);
}

static void ir_edit_prepare_data(GxIREdit *ir_edit)
{
	int i;
	if (ir_edit->odata_len) {
		g_free(ir_edit->data);
		ir_edit->data = (float*)g_malloc(ir_edit->odata_len*sizeof(float));
	} else {
		if (ir_edit->data) {
			gtk_widget_queue_draw(GTK_WIDGET(ir_edit));
		}
		g_free(ir_edit->data);
		ir_edit->data = NULL;
	}
	if (ir_edit->linear) {
		if (ir_edit->chan < 0) {
			for (i = 0; i < ir_edit->odata_len; i++) {
				ir_edit->data[i] = 0;
				for (int j = 0; j < ir_edit->odata_chan; j++) {
					ir_edit->data[i] += ir_edit->odata[i*ir_edit->odata_chan+j];
				}
				ir_edit->data[i] /= ir_edit->odata_chan;
			}
		} else {
			for (i = 0; i < ir_edit->odata_len; i++) {
				ir_edit->data[i] = ir_edit->odata[i*ir_edit->odata_chan+ir_edit->chan];
			}
		}
	} else {
		float mx = 0.0;
		if (ir_edit->chan < 0) {
			for (i = 0; i < ir_edit->odata_len; i++) {
				float s = 0.0;
				for (int j = 0; j < ir_edit->odata_chan; j++) {
					float v = ir_edit->odata[i*ir_edit->odata_chan+j];
					s += v*v;
				}
				if (s > mx) {
					mx = s;
				}
				ir_edit->data[i] = s;
			}
		} else {
			for (i = 0; i < ir_edit->odata_len; i++) {
				float v = ir_edit->odata[i*ir_edit->odata_chan+ir_edit->chan];
				float s = v*v;
				if (s > mx) {
					mx = s;
				}
				ir_edit->data[i] = s;
			}
		}
		if (mx == 0.0) {
			mx = 1.0;
		}
		for (i = 0; i < ir_edit->odata_len; i++) {
			ir_edit->data[i] = 10*log10(ir_edit->data[i]/mx+1e-20);
		}
	}
}

/****************************************************************
 ** Properties
 */
static void ir_edit_set_property(
	GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	GxIREdit *ir_edit = GX_IR_EDIT(object);

	switch(prop_id) {
	case PROP_Y_BORDER_TOP:
		ir_edit->y_border_top = g_value_get_int(value);
		gtk_widget_queue_draw(GTK_WIDGET(object));
		g_object_notify(object, "y-border-top");
		break;
	case PROP_Y_BORDER_BOTTOM:
		ir_edit->y_border_bottom = g_value_get_int(value);
		gtk_widget_queue_draw(GTK_WIDGET(object));
		g_object_notify(object, "y-border-bottom");
		break;
	case PROP_X_BORDER:
		ir_edit->x_border = g_value_get_int(value);
		gtk_widget_queue_draw(GTK_WIDGET(object));
		g_object_notify(object, "x-border");
		break;
	case PROP_LABEL_SEP:
		ir_edit->label_sep = g_value_get_int(value);
		gtk_widget_queue_draw(GTK_WIDGET(object));
		g_object_notify(object, "label-sep");
		break;
	case PROP_DOT_DIAMETER:
		ir_edit->dot_diameter = g_value_get_double(value);
		gtk_widget_queue_draw(GTK_WIDGET(object));
		g_object_notify(object, "dot-diameter");
		break;
	case PROP_SEGMENT_DISTANCE:
		ir_edit->segment_distance = g_value_get_double(value);
		gtk_widget_queue_draw(GTK_WIDGET(object));
		g_object_notify(object, "segment-distance");
		break;
	case PROP_LIMIT:
		ir_edit->limit = g_value_get_double(value);
		break;
	case PROP_FS:
		ir_edit_set_fs(ir_edit, g_value_get_int(value));
		break;
	case PROP_MAX_SCALE_FACT: {
		gdouble f = g_value_get_double(value);
		if (f != ir_edit->max_scale_fact) {
			gdouble mx = ir_edit->odata_len / f;
			if (ir_edit->scale > mx) {
				ir_edit->max_scale_fact = f;
				ir_edit_set_scale(ir_edit, mx, -1);
			} else if (ir_edit->scale == mx) {
				ir_edit->max_scale_fact = f;
				g_signal_emit_by_name(ir_edit,"scale-max-reached", TRUE);
			} else if (ir_edit->scale == ir_edit->odata_len / ir_edit->max_scale_fact) {
				ir_edit->max_scale_fact = f;
				g_signal_emit_by_name(ir_edit,"scale-max-reached", FALSE);
			}
			g_object_notify(object, "max-scale-fact");
		}
		break;
	}
	case PROP_MIN_SCALE: {
		gdouble f = g_value_get_double(value);
		if (f != ir_edit->min_scale) {
			if (ir_edit->scale < f) {
				ir_edit->min_scale = f;
				ir_edit_set_scale(ir_edit, f, -1);
			} else if (ir_edit->scale == f) {
				ir_edit->min_scale = f;
				g_signal_emit_by_name(ir_edit,"scale-min-reached", TRUE);
			} else if (ir_edit->scale == ir_edit->min_scale) {
				ir_edit->min_scale = f;
				g_signal_emit_by_name(ir_edit,"scale-min-reached", FALSE);
			}
			g_object_notify(object, "min-scale");
		}
		break;
	}
	case PROP_SCALE:
		ir_edit_set_scale(ir_edit, g_value_get_double(value), -1);
		break;
	case PROP_NO_DATA_TEXT:
		g_free(ir_edit->no_data_text);
		ir_edit->no_data_text = g_strdup(g_value_get_string(value));
		if (ir_edit->data) {
			gtk_widget_queue_draw(GTK_WIDGET(object));
		}
		g_object_notify(object,"no-data-text");
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

static void ir_edit_get_property(
	GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
	GxIREdit *ir_edit = GX_IR_EDIT(object);

	switch(prop_id) {
	case PROP_Y_BORDER_TOP:
		g_value_set_int(value, ir_edit->y_border_top);
		break;
	case PROP_Y_BORDER_BOTTOM:
		g_value_set_int(value, ir_edit->y_border_bottom);
		break;
	case PROP_X_BORDER:
		g_value_set_int(value, ir_edit->x_border);
		break;
	case PROP_LABEL_SEP:
		g_value_set_int(value, ir_edit->label_sep);
		break;
	case PROP_DOT_DIAMETER:
		g_value_set_double(value, ir_edit->dot_diameter);
		break;
	case PROP_SEGMENT_DISTANCE:
		g_value_set_double(value, ir_edit->segment_distance);
		break;
	case PROP_LIMIT:
		g_value_set_double(value, ir_edit->limit);
		break;
	case PROP_FS:
		g_value_set_int(value, ir_edit->fs);
		break;
	case PROP_MAX_SCALE_FACT:
		g_value_set_double(value, ir_edit->max_scale_fact);
		break;
	case PROP_MIN_SCALE:
		g_value_set_double(value, ir_edit->min_scale);
		break;
	case PROP_SCALE:
		g_value_set_double(value, ir_edit->scale);
		break;
	case PROP_NO_DATA_TEXT:
		g_value_set_string(value, ir_edit->no_data_text);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
		break;
	}
}

/****************************************************************
 ** external API
 */

void gx_ir_edit_set_ir_data(GxIREdit *ir_edit, float *data, int chan, int len, int samplerate)
{
	g_assert(GX_IS_IR_EDIT(ir_edit));
	ir_edit_reset(ir_edit);
	ir_edit->odata = data;
	ir_edit->odata_chan = chan;
	ir_edit->odata_len = len;
	ir_edit->cutoff_high = len;
	g_free(ir_edit->gains);
	ir_edit->gains = (gain_points*)g_malloc(2 * sizeof(gain_points));
	ir_edit->gains[0].i = 0;
	ir_edit->gains[0].g = 0.0;
	ir_edit->gains[1].i = len-1;
	ir_edit->gains[1].g = 0.0;
	ir_edit->gains_len = 2;
	ir_edit_set_fs(ir_edit, samplerate);
	//FIXME signal
	ir_edit_prepare_data(ir_edit);
	ir_edit_configure_axes(ir_edit);
	if (ir_edit->scale) {
		gx_ir_edit_home(ir_edit);
	} else if (ir_edit->width) {
		ir_edit_reconfigure(ir_edit);
	}
}

void gx_ir_edit_set_state(
	GxIREdit *ir_edit, float *data, int chan, int data_len, int samplerate,
	int cutoff_low, int cutoff_high, int offset, const gain_points *gains, int gains_len)
{
	g_assert(GX_IS_IR_EDIT(ir_edit));
	ir_edit_reset(ir_edit);
	gx_ir_edit_set_ir_data(ir_edit, data, chan, data_len, samplerate);
	ir_edit->cutoff_high = cutoff_high;
	ir_edit->offset = offset;
	ir_edit_set_cutoff_low(ir_edit, cutoff_low);
	if (gains_len) {
	    gx_ir_edit_set_gain(ir_edit, gains, gains_len);
	}
	ir_edit_prepare_data(ir_edit);
	ir_edit_configure_axes(ir_edit);
	gx_ir_edit_home(ir_edit);
	g_signal_emit_by_name(ir_edit,"delay-changed", ir_edit->offset+ir_edit->cutoff_low, ir_edit->fs);
	g_signal_emit_by_name(ir_edit,"offset-changed", ir_edit->cutoff_low, ir_edit->fs);
	g_signal_emit_by_name(ir_edit,"length-changed", ir_edit->cutoff_high - ir_edit->cutoff_low, ir_edit->fs);
}

void gx_ir_edit_home(GxIREdit *ir_edit)
{
	g_assert(GX_IS_IR_EDIT(ir_edit));
	if (!ir_edit->odata) {
		return;
	}
	ir_edit_set_default_scale(ir_edit);
	ir_edit->current_offset = min(0, int(floor(-ir_edit->offset/ir_edit->scale)));
	gtk_widget_queue_draw(GTK_WIDGET(ir_edit));
}

void gx_ir_edit_jump_zoom_mark(GxIREdit *ir_edit)
{
	g_assert(GX_IS_IR_EDIT(ir_edit));
	if (!ir_edit->odata) {
		return;
	}
	ir_edit->current_offset = int(ir_edit->scroll_center/ir_edit->scale - ir_edit->graph_x/2);
	gtk_widget_queue_draw(GTK_WIDGET(ir_edit));
}

void gx_ir_edit_set_channel(GxIREdit *ir_edit, int chan)
{
	g_assert(GX_IS_IR_EDIT(ir_edit));
	chan = min(max(chan, -1), ir_edit->odata_chan);
	if (ir_edit->chan == chan) {
		return;
	}
	ir_edit->chan = chan;
	if (!ir_edit->odata) {
		return;
	}
	ir_edit_prepare_data(ir_edit);
	ir_edit_precalc(ir_edit);
	gtk_widget_queue_draw(GTK_WIDGET(ir_edit));
}

void gx_ir_edit_incr_scale(GxIREdit *ir_edit, gdouble f)
{
	g_assert(GX_IS_IR_EDIT(ir_edit));
	if (f == 0.0) {
		f = 2.0;
	}
	ir_edit_set_scale(ir_edit, ir_edit->scale * f, -1);
}

void gx_ir_edit_decr_scale(GxIREdit *ir_edit, gdouble f)
{
	g_assert(GX_IS_IR_EDIT(ir_edit));
	if (f == 0.0) {
		f = 2.0;
	}
	ir_edit_set_scale(ir_edit, ir_edit->scale / f, -1);
}

void gx_ir_edit_set_log(GxIREdit *ir_edit, gboolean m)
{
	g_assert(GX_IS_IR_EDIT(ir_edit));
	if (ir_edit->linear != m) {
		return;
	}
	ir_edit->linear = !m;
	if (!ir_edit->odata) {
		return;
	}
	ir_edit_configure_axes(ir_edit);
	ir_edit_prepare_data(ir_edit);
	ir_edit_reconfigure(ir_edit);
	gtk_widget_queue_draw(GTK_WIDGET(ir_edit));
}

gint gx_ir_edit_get_delay(GxIREdit *ir_edit)
{
	g_return_val_if_fail(GX_IS_IR_EDIT(ir_edit), 0);
	return max(0, ir_edit->offset + ir_edit->cutoff_low);
}

void gx_ir_edit_set_delay(GxIREdit *ir_edit, gint delay)
{
	g_return_if_fail(GX_IS_IR_EDIT(ir_edit));
	if (delay == gx_ir_edit_get_delay(ir_edit)) {
		return;
	}
	ir_edit_set_offset(ir_edit, max(delay, 0) - ir_edit->cutoff_low);
	gtk_widget_queue_draw(GTK_WIDGET(ir_edit));
}

gint gx_ir_edit_get_offset(GxIREdit *ir_edit)
{
	g_assert(GX_IS_IR_EDIT(ir_edit));
	return max(-ir_edit->offset, ir_edit->cutoff_low);
}

void gx_ir_edit_set_offset(GxIREdit *ir_edit, gint offset)
{
	g_return_if_fail(GX_IS_IR_EDIT(ir_edit));
	if (offset == gx_ir_edit_get_offset(ir_edit)) {
		return;
	}
	offset = min(ir_edit->odata_len-1, offset);
	offset = max(0, offset);
	ir_edit_set_cutoff_low(ir_edit, offset);
	if (offset < -ir_edit->offset) {
		ir_edit_set_offset(ir_edit, -offset);
	}
	gtk_widget_queue_draw(GTK_WIDGET(ir_edit));
}

gint gx_ir_edit_get_length(GxIREdit *ir_edit)
{
	g_return_val_if_fail(GX_IS_IR_EDIT(ir_edit), 0);
	return ir_edit->cutoff_high - gx_ir_edit_get_offset(ir_edit);
}

void gx_ir_edit_set_length(GxIREdit *ir_edit, gint length)
{
	g_return_if_fail(GX_IS_IR_EDIT(ir_edit));
	if (length == gx_ir_edit_get_length(ir_edit)) {
		return;
	}
	length = max(1, length);
	gint low = max(ir_edit->cutoff_low,-ir_edit->offset);
	length = min(ir_edit->odata_len - low, length);
	ir_edit_set_cutoff_high(ir_edit, length + low);
	gtk_widget_queue_draw(GTK_WIDGET(ir_edit));
}

void gx_ir_edit_get_gain(GxIREdit *ir_edit, gain_points **gains, gint *len)
{
	*gains = ir_edit->gains;
	*len = ir_edit->gains_len;
}

void gx_ir_edit_set_gain(GxIREdit *ir_edit, const gain_points *gains, gint len)
{
	g_return_if_fail(GX_IS_IR_EDIT(ir_edit));
	if (!ir_edit->odata) {
		g_warning("skipped setting gain line without sample data");
		return;
	}
	if (len < 2) {
		g_warning("gain line must have at least 2 points");
		return;
	}
	if (gains[0].i != 0 and gains[len-1].i != ir_edit->odata_len) {
		g_warning("gain line must have points at start and end of interval");
	}
	g_free(ir_edit->gains);
	int size = len * sizeof(gain_points);
	ir_edit->gains = (gain_points*)g_malloc(size);
	memcpy(ir_edit->gains, gains, size);
	ir_edit->gains_len = len;
	gtk_widget_queue_draw(GTK_WIDGET(ir_edit));
}

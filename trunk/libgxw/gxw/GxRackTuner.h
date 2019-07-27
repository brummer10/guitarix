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

#ifndef __GX_RACK_TUNER_H__
#define __GX_RACK_TUNER_H__

#include "GxTuner.h"

G_BEGIN_DECLS

#define GX_TYPE_RACK_TUNER          (gx_rack_tuner_get_type())
#define GX_RACK_TUNER(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GX_TYPE_RACK_TUNER, GxRackTuner))
#define GX_IS_RACK_TUNER(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GX_TYPE_RACK_TUNER))
#define GX_RACK_TUNER_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass),  GX_TYPE_RACK_TUNER, GxRackTunerClass))
#define GX_IS_RACK_TUNER_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GX_TYPE_RACK_TUNER))

typedef struct _GxRackTuner GxRackTuner;
typedef struct _GxRackTunerPrivate GxRackTunerPrivate;
typedef struct _GxRackTunerClass GxRackTunerClass;

#define RACKTUNER_MAXTARGETS (12)
struct _GxRackTuner
{
	GxTuner        parent;
	GxRackTunerPrivate *priv;
};

struct _GxRackTunerClass
{
	GtkDrawingAreaClass parent_class;
	void (*frequency_poll)(GxRackTuner *tuner);
	void (*poll_status_changed)(GxRackTuner *tuner, gboolean status);
};


GType gx_rack_tuner_get_type();

gboolean gx_rack_tuner_get_poll_status(GxRackTuner *tuner);
void gx_rack_tuner_set_freq(GxRackTuner *tuner, double freq);
void gx_rack_tuner_set_scale_lim(GxRackTuner *tuner, double scale_lim);
double gx_rack_tuner_get_scale_lim(GxRackTuner *tuner);
void gx_rack_tuner_set_speed(GxRackTuner *tuner, double speed);
double gx_rack_tuner_get_speed(GxRackTuner *tuner);
void gx_rack_tuner_set_streaming(GxRackTuner *tuner, gboolean streaming);
gboolean gx_rack_tuner_get_streaming(GxRackTuner *tuner);
void gx_rack_tuner_set_display_flat(GxRackTuner *tuner, gboolean display_flat);
gboolean gx_rack_tuner_get_display_flat(GxRackTuner *tuner);
void gx_rack_tuner_set_timestep(GxRackTuner *tuner, gint timestep);
gint gx_rack_tuner_get_timestep(GxRackTuner *tuner);
void gx_rack_tuner_set_limit_timestep(GxRackTuner *tuner, gint in_limit_timestep);
gint gx_rack_tuner_get_limit_timestep(GxRackTuner *tuner);
void gx_rack_tuner_clear_notes(GxRackTuner *tuner);
gboolean gx_rack_tuner_push_note(GxRackTuner *tuner, gint note, gint A, gint TET);
void gx_rack_tuner_set_temperament(GxRackTuner *tuner, gint temperament);
gint gx_rack_tuner_get_temperament(GxRackTuner *tuner);

GtkWidget *gx_rack_tuner_new(void);

G_END_DECLS

#endif /* __GX_RACK_TUNER_H__ */

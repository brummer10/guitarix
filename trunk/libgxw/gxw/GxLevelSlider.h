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

#ifndef __GX_LEVEL_SLIDER_H__
#define __GX_LEVEL_SLIDER_H__


#include "GxVSlider.h"

G_BEGIN_DECLS

#define GX_TYPE_LEVEL_SLIDER          (gx_level_slider_get_type())
#define GX_LEVEL_SLIDER(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GX_TYPE_LEVEL_SLIDER, GxLevelSlider))
#define GX_LEVEL_SLIDER_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass),  GX_TYPE_LEVEL_SLIDER, GxLevelSliderClass))
#define GX_IS_LEVEL_SLIDER(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GX_TYPE_LEVEL_SLIDER))
#define GX_IS_LEVEL_SLIDER_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GX_TYPE_LEVEL_SLIDER))
#define GX_LEVEL_SLIDER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GX_TYPE_LEVEL_SLIDER, GxLevelSliderClass))

typedef struct _GxLevelSlider GxLevelSlider;
typedef struct _GxLevelSliderClass GxLevelSliderClass;

struct _GxLevelSlider {
	GxVSlider parent;
};

struct _GxLevelSliderClass {
	GxVSliderClass parent_class;
};

GType gx_level_slider_get_type(void);

inline double log_meter (double db)
{
	// keep log_meter_inv in sync when changing anying!
	gfloat def = 0.0f; /* Meter deflection %age */

	if (db < -70.0f) {
		def = 0.0f;
	} else if (db < -60.0f) {
		def = (db + 70.0f) * 0.25f;
	} else if (db < -50.0f) {
		def = (db + 60.0f) * 0.5f + 2.5f;
	} else if (db < -40.0f) {
		def = (db + 50.0f) * 0.75f + 7.5f;
	} else if (db < -30.0f) {
		def = (db + 40.0f) * 1.5f + 15.0f;
	} else if (db < -20.0f) {
		def = (db + 30.0f) * 2.0f + 30.0f;
	} else if (db < 6.0f) {
		def = (db + 20.0f) * 2.5f + 50.0f;
	} else {
		def = 115.0f;
	}

	/* 115 is the deflection %age that would be
	   when db=6.0. this is an arbitrary
	   endpoint for our scaling.
	*/

	return def/115.0f;
}

G_END_DECLS

#endif /* __GX_LEVEL_SLIDER_H__ */

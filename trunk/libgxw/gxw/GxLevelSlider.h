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

G_END_DECLS

#endif /* __GX_LEVEL_SLIDER_H__ */

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

#ifndef __GX_HSLIDER_H__
#define __GX_HSLIDER_H__


#include "GxRegler.h"

G_BEGIN_DECLS

#define GX_TYPE_HSLIDER          (gx_hslider_get_type())
#define GX_HSLIDER(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GX_TYPE_HSLIDER, GxHSlider))
#define GX_HSLIDER_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass),  GX_TYPE_HSLIDER, GxHSliderClass))
#define GX_IS_HSLIDER(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GX_TYPE_HSLIDER))
#define GX_IS_HSLIDER_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GX_TYPE_HSLIDER))
#define GX_HSLIDER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GX_TYPE_HSLIDER, GxHSliderClass))

typedef struct _GxHSlider GxHSlider;
typedef struct _GxHSliderClass GxHSliderClass;

struct _GxHSlider {
	GxRegler parent;
    GdkPixbuf *image;
    int slider_width;
    int width;
    int height;
    int hover;
    GdkRectangle image_rect;
};

struct _GxHSliderClass {
	GxReglerClass parent_class;
	const gchar *stock_id;
	gfloat mouse_scale_factor;
};

GType gx_hslider_get_type(void);

G_END_DECLS

#endif /* __GX_HSLIDER_H__ */

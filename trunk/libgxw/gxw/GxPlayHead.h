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

#ifndef __GX_PLAYHEAD_H__
#define __GX_PLAYHEAD_H__


#include "GxRegler.h"

G_BEGIN_DECLS

#define GX_TYPE_PLAYHEAD          (gx_play_head_get_type())
#define GX_PLAYHEAD(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GX_TYPE_PLAYHEAD, GxPlayHead))
#define GX_PLAYHEAD_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass),  GX_TYPE_PLAYHEAD, GxPlayHeadClass))
#define GX_IS_PLAYHEAD(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GX_TYPE_PLAYHEAD))
#define GX_IS_PLAYHEAD_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GX_TYPE_PLAYHEAD))
#define GX_PLAYHEAD_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GX_TYPE_PLAYHEAD, GxPlayHeadClass))

typedef struct _GxPlayHead GxPlayHead;
typedef struct _GxPlayHeadClass GxPlayHeadClass;

struct _GxPlayHead {
	GxRegler parent;
    GdkPixbuf *image;
    GdkPixbuf *scaled_image;
    int phead_width;
    int width;
    int height;
    int hover;
    GdkRectangle image_rect;
};

struct _GxPlayHeadClass {
	GxReglerClass parent_class;
	const gchar *stock_id;
};

GType gx_play_head_get_type(void);

G_END_DECLS

#endif /* __GX_PLAYHEAD_H__ */


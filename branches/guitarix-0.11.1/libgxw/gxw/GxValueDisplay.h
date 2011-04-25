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

#ifndef __GX_VALUE_DISPLAY_H__
#define __GX_VALUE_DISPLAY_H__


#include "GxRegler.h"

G_BEGIN_DECLS

#define GX_TYPE_VALUE_DISPLAY          (gx_value_display_get_type())
#define GX_VALUE_DISPLAY(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GX_TYPE_VALUE_DISPLAY, GxValueDisplay))
#define GX_VALUE_DISPLAY_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass),  GX_TYPE_VALUE_DISPLAY, GxValueDisplayClass))
#define GX_IS_VALUE_DISPLAY(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GX_TYPE_VALUE_DISPLAY))
#define GX_IS_VALUE_DISPLAY_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GX_TYPE_VALUE_DISPLAY))
#define GX_VALUE_DISPLAY_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GX_TYPE_VALUE_DISPLAY, GxValueDisplayClass))

typedef struct _GxValueDisplay GxValueDisplay;
typedef struct _GxValueDisplayClass GxValueDisplayClass;

struct _GxValueDisplay {
	GxRegler parent;
};

struct _GxValueDisplayClass {
	GxReglerClass parent_class;
};

GType gx_value_display_get_type(void);

G_END_DECLS

#endif /* __GX_VALUE_DISPLAY_H__ */

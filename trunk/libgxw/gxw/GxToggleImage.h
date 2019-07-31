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

#ifndef __GX_TOGGLE_IMAGE_H__
#define __GX_TOGGLE_IMAGE_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GX_TYPE_TOGGLE_IMAGE          (gx_toggle_image_get_type())
#define GX_TOGGLE_IMAGE(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GX_TYPE_TOGGLE_IMAGE, GxToggleImage))
#define GX_TOGGLE_IMAGE_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass),  GX_TYPE_TOGGLE_IMAGE, GxToggleImageClass))
#define GX_IS_TOGGLE_IMAGE(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GX_TYPE_TOGGLE_IMAGE))
#define GX_IS_TOGGLE_IMAGE_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GX_TYPE_TOGGLE_IMAGE))
#define GX_TOGGLE_IMAGE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GX_TYPE_TOGGLE_IMAGE, GxToggleImageClass))

typedef struct _GxToggleImage GxToggleImage;
typedef struct _GxToggleImagePrivate GxToggleImagePrivate;
typedef struct _GxToggleImageClass GxToggleImageClass;

struct _GxToggleImage {
	GtkWidget parent;
	GxToggleImagePrivate* priv;
};

struct _GxToggleImageClass {
	GtkMiscClass parent_class;
};

GType gx_toggle_image_get_type(void);
const char *gx_toggle_image_get_base_name(GxToggleImage *toggle_image);
void gx_toggle_image_set_base_name(GxToggleImage *toggle_image, const char *base_name);

G_END_DECLS

#endif /* __GX_TOGGLE_IMAGE_H__ */

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

/******************************************************************************
part of guitarix, use  knobs with Gtk
******************************************************************************/

#ifndef __GX_SELECTOR_H__
#define __GX_SELECTOR_H__

#include "GxRegler.h"
#include "drawingutils.h"

G_BEGIN_DECLS

//----------------------------------------------------------------

#define GX_TYPE_SELECTOR          (gx_selector_get_type())
#define GX_SELECTOR(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GX_TYPE_SELECTOR, GxSelector))
#define GX_SELECTOR_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass),  GX_TYPE_SELECTOR, GxSelectorClass))
#define GX_IS_SELECTOR(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GX_TYPE_SELECTOR))
#define GX_IS_SELECTOR_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GX_TYPE_SELECTOR))
#define GX_SELECTOR_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GX_TYPE_SELECTOR, GxSelectorClass))

typedef struct _GxSelector GxSelector;
typedef struct _GxSelectorClass GxSelectorClass;
typedef struct _GxSelectorPrivate GxSelectorPrivate;

struct _GxSelector
{
	GxRegler parent;
	GxSelectorPrivate *priv;
	GtkTreeModel *model;
};

struct _GxSelectorClass {
	GxReglerClass parent_class;
};

GType gx_selector_get_type(void);
void gx_selector_set_model(GxSelector *selector, GtkTreeModel *model);
GtkTreeModel *gx_selector_get_model(GxSelector *selector);

G_END_DECLS

#endif /* __GX_SELECTOR_H__ */

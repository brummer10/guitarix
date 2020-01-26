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

#ifndef __GX_SWITCH_H__
#define __GX_SWITCH_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GX_TYPE_SWITCH          (gx_switch_get_type())
#define GX_SWITCH(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GX_TYPE_SWITCH, GxSwitch))
#define GX_SWITCH_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass),  GX_TYPE_SWITCH, GxSwitchClass))
#define GX_IS_SWITCH(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GX_TYPE_SWITCH))
#define GX_IS_SWITCH_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GX_TYPE_SWITCH))
#define GX_SWITCH_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GX_TYPE_SWITCH, GxSwitchClass))

typedef struct _GxSwitch GxSwitch;
typedef struct _GxSwitchPrivate GxSwitchPrivate;
typedef struct _GxSwitchClass GxSwitchClass;

struct _GxSwitch {
	GtkCheckButton parent;
	GxSwitchPrivate* priv;
};

struct _GxSwitchClass {
	GtkCheckButtonClass parent_class;
};

GType gx_switch_get_type(void);
void gx_switch_set_label_ref(GxSwitch *swtch, GtkLabel* label);
GtkLabel *gx_switch_get_label_ref(GxSwitch *swtch);
void gx_switch_set_base_name(GxSwitch *swtch, const char *base_name);
const char *gx_switch_get_base_name(GxSwitch *swtch);

G_END_DECLS

#endif /* __GX_SWITCH_H__ */

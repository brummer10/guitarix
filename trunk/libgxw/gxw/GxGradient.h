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

#ifndef __GX_GRADIENT_H__
#define __GX_GRADIENT_H__

#include <glib-object.h>

G_BEGIN_DECLS

typedef struct _GxGradientElement GxGradientElement;
typedef struct _GxGradient GxGradient;

struct _GxGradientElement {
	gdouble offset, red, green, blue, alpha;
};

struct _GxGradient {
	GSList *colors;
};

gboolean gx_parse_rgba(const GParamSpec *pspec, const GString *rc_string,
                       GValue *property_value);

#define GX_TYPE_GRADIENT (gx_gradient_get_type())
GType gx_gradient_get_type(void) G_GNUC_CONST;
gboolean gx_parse_gradient(const GParamSpec *pspec, const GString *rc_string,
                           GValue *property_value);
GxGradient *gx_gradient_copy(const GxGradient *grad);
void gx_gradient_free(GxGradient *grad);
GxGradient *gx_gradient_new(void);

G_END_DECLS

#endif /* __GX_GRADIENT_H__ */

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

#include "GxGradient.h"
#include <gtk/gtk.h>

/*
 ** Gtk seems to have a bug with rc parsing and locales:
 ** value strings are parsed and reassembled, with floats
 ** formatted according to the current locate, which can
 ** lead to a transformation like this:
 **
 ** "{1.1, 2.4}" -> "{1,1, 2,4}"
 **
 ** so we just use int's in the rc files and scale them
 ** to 0..1 by dividing through COLOR_SCALING (2**16)
 */
#define COLOR_SCALING (65536)

static gboolean get_braced_number(
	GScanner *scanner, gboolean  first, gboolean  last, gdouble *value)
{
	if (first) {
		g_scanner_get_next_token(scanner);
		if (scanner->token != '{') {
			return FALSE;
		}
	}
	g_scanner_get_next_token(scanner);
	if (scanner->token != G_TOKEN_INT) {
		return FALSE;
	}
	*value = (gdouble)scanner->value.v_int/COLOR_SCALING;
	g_scanner_get_next_token(scanner);
	if (last) {
		if (scanner->token != '}') {
			return FALSE;
		}
	} else {
		if (scanner->token != ',') {
			return FALSE;
		}
	}
	return TRUE;
}

gboolean gx_parse_rgba(const GParamSpec *pspec,
                           const GString *rc_string,
                           GValue *property_value)
{
	GdkRGBA rgba;
	GScanner *scanner;
	gboolean success = FALSE;

	g_return_val_if_fail(G_IS_PARAM_SPEC (pspec), FALSE);
	g_return_val_if_fail(G_VALUE_HOLDS_BOXED(property_value), FALSE);

	scanner = gtk_rc_scanner_new();
	g_scanner_input_text(scanner, rc_string->str, rc_string->len);

	if (get_braced_number(scanner, TRUE, FALSE, &rgba.red) &&
	    get_braced_number(scanner, FALSE, FALSE, &rgba.green) &&
	    get_braced_number(scanner, FALSE, FALSE, &rgba.blue) &&
	    get_braced_number(scanner, FALSE, TRUE, &rgba.alpha)) {
		g_value_set_boxed(property_value, &rgba);
		success = TRUE;
	}
	g_scanner_destroy(scanner);
	return success;
}

static void element_free(gpointer el, gpointer)
{
	g_slice_free(GxGradientElement, el);
}

void gx_gradient_free(GxGradient *grad)
{
	g_return_if_fail (grad != NULL);
	g_slist_foreach(grad->colors, (GFunc)element_free, NULL);
	g_slist_free(grad->colors);
	g_slice_free(GxGradient, grad);
}

GxGradient *gx_gradient_new()
{
	GxGradient *p = g_slice_new(GxGradient);
	p->colors = NULL;
	return p;
}

static gpointer element_copy(const gpointer el)
{
	GxGradientElement *new_el;
  
	new_el = g_slice_new(GxGradientElement);
	*new_el = *(GxGradientElement*)el;
	return new_el;
}

GxGradient *gx_gradient_copy(const GxGradient *grad)
{
	GxGradient *new_grad;
	g_return_val_if_fail(grad != NULL, NULL);
	new_grad = g_slice_new(GxGradient);
	new_grad->colors = g_slist_copy(grad->colors);
	for (GSList *p = new_grad->colors; p; p = g_slist_next(p)) {
		p->data = element_copy(p->data);
	}
	return new_grad;
}

GType gx_gradient_get_type(void)
{
	static GType our_type = 0;
  
	if (our_type == 0) {
		our_type = g_boxed_type_register_static(
			g_intern_static_string("GxGradient"),
			(GBoxedCopyFunc)gx_gradient_copy,
			(GBoxedFreeFunc)gx_gradient_free);
	}
	return our_type;
}

gboolean gx_parse_gradient(const GParamSpec *pspec,
                                  const GString *rc_string,
                                  GValue *property_value)
{
	GxGradient* grad = gx_gradient_new();
	GxGradientElement el;
	GScanner *scanner;
	gboolean success = FALSE;

	g_return_val_if_fail(G_IS_PARAM_SPEC (pspec), FALSE);
	g_return_val_if_fail(G_VALUE_HOLDS_BOXED(property_value), FALSE);
	scanner = gtk_rc_scanner_new();
	g_scanner_input_text(scanner, rc_string->str, rc_string->len);

	g_scanner_get_next_token (scanner);
	if (scanner->token != '{') {
		return FALSE;
	}
	grad->colors = NULL;
	success = TRUE;
	while (TRUE) {
		if (get_braced_number(scanner, TRUE, FALSE, &el.offset) &&
		    get_braced_number(scanner, FALSE, FALSE, &el.red) &&
		    get_braced_number(scanner, FALSE, FALSE, &el.green) &&
		    get_braced_number(scanner, FALSE, FALSE, &el.blue) &&
		    get_braced_number(scanner, FALSE, TRUE, &el.alpha)) {
			grad->colors = g_slist_append(grad->colors, element_copy(&el));
		} else {
			success = FALSE;
			break;
		}
		g_scanner_get_next_token (scanner);
		if (scanner->token == '}') {
			break;
		} else if (scanner->token != ',') {
			success = FALSE;
			break;
		}
	}
	if (success) {
		g_value_set_boxed(property_value, grad);
	}
	gx_gradient_free(grad);
	g_scanner_destroy(scanner);
	return success;
}

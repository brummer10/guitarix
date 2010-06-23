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

/******************************************************************************
part of guitarix, use  knobs with Gtk
******************************************************************************/

#ifndef __GX_SWITCH_H__
#define __GX_SWITCH_H__

#include <gtk/gtktogglebutton.h>

G_BEGIN_DECLS

#define GX_TYPE_SWITCH          (gx_switch_get_type())
#define GX_SWITCH(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GX_TYPE_SWITCH, GxSwitch))
#define GX_SWITCH_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass),  GX_TYPE_SWITCH, GxSwitchClass))
#define GX_IS_SWITCH(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GX_TYPE_SWITCH))
#define GX_IS_SWITCH_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GX_TYPE_SWITCH))
#define GX_SWITCH_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GX_TYPE_SWITCH, GxSwitchClass))

typedef struct
{
	GtkToggleButton parent;
	int GSEAL(switch_type);
	gchar *GSEAL(var_id);
	double start_x, start_y, start_value, max_value;
} GxSwitch;

typedef struct {
	GtkToggleButtonClass parent_class;
	GdkPixbuf *toggle_image;
	GdkPixbuf *toggle_image1;
	GdkPixbuf *switch_image;
	GdkPixbuf *switch_image1;
	GdkPixbuf *b_toggle_image;
	GdkPixbuf *b_toggle_image1;
	GdkPixbuf *led_image;
	int pix_is;
	int pix_switch;
} GxSwitchClass;

typedef enum {
	GX_SWITCH_TYPE_SWITCH,
	GX_SWITCH_TYPE_SWITCH_II,
	GX_SWITCH_TYPE_MINI_TOGGLE,
	GX_SWITCH_TYPE_TOGGLE_BUTTON,
	GX_SWITCH_TYPE_LED,
	GX_SWITCH_TYPE_VALUE_DISPLAY,
} GxSwitchType;

GType switch_type_get_type(void) G_GNUC_CONST;
#define GX_TYPE_SWITCH_TYPE (switch_type_get_type())

GType gx_switch_get_type(void);
typedef gboolean switch_connect_func(GxSwitch *swtch, const gchar *var);
void set_switch_connect_func(switch_connect_func f);
gchar *gx_switch_get_var(GxSwitch* swtch);

/*
GtkWidget *gtk_toggle_new_with_adjustment(GtkAdjustment *_adjustment);
GtkWidget *gtk_switch_new_with_adjustment(GtkAdjustment *_adjustment);
GtkWidget *gtk_mini_toggle_new_with_adjustment(GtkAdjustment *_adjustment);
GtkWidget *gtk_button_toggle_new_with_adjustment(GtkAdjustment *_adjustment);
GtkWidget *gtk_led_new_with_adjustment(GtkAdjustment *_adjustment);
GtkWidget *gtk_value_display(GtkAdjustment *_adjustment);
*/

G_END_DECLS

#endif /* __GX_SWITCH_H__ */

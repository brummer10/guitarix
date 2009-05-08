/*
  * Copyright (C) 2009 Hermann Meyer
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

// ***** GtkRegler.h *****
/******************************************************************************
part of guitarix, use  knobs with Gtk
******************************************************************************/

#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>

#ifndef GtkReglerH
#define GtkReglerH

class GtkRegler
{
private:

public:
    GtkRange parent;
    int regler_type;
    double start_x, start_y, start_value;

  GtkRegler();
  ~GtkRegler();
 
virtual void gtk_regler_destroy ( );
virtual GtkWidget *gtk_hslider_new_with_adjustment(GtkAdjustment *_adjustment);
virtual GtkWidget *gtk_mini_slider_new_with_adjustment(GtkAdjustment *_adjustment);
virtual GtkWidget *gtk_toggle_new_with_adjustment(GtkAdjustment *_adjustment);
virtual GtkWidget *gtk_regler_new_with_adjustment(GtkAdjustment *_adjustment);
virtual GtkWidget *gtk_big_regler_new_with_adjustment(GtkAdjustment *_adjustment);
};
#endif


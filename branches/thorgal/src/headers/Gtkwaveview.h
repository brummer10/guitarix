/*
  * Copyright (C) 2009 Hermann Meyer and James Warden
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

// ***** GtkWaveView.h *****
/******************************************************************************
part of guitarix, plot a wave with Gtk
******************************************************************************/

#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>
#include <sndfile.hh>

#ifndef GtkWaveViewH
#define GtkWaveViewH

class GtkWaveView
{
private:

public:
    GtkRange parent;
    int waveview_type;
    double start_x, start_y, start_value;

    GtkWaveView();
    ~GtkWaveView();

    virtual void gtk_waveview_destroy (GtkWidget *widget, gpointer data );
    virtual gboolean gtk_waveview_set_value (GtkWidget *widget, gpointer data );
    virtual GtkWidget *gtk_wave_view(const char* file);
    virtual GtkWidget *gtk_wave_live_view(float* outfloat, float* infloat,GtkAdjustment *_adjustment);
};
#endif


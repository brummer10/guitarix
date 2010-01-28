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
#pragma once

/* internal enum sets */
typedef enum {
  kWvTypeJConv = 0,
  kWvTypeLive
} GxWaveviewType;

class GtkWaveView
{
 private:

 public:
  inline GtkWaveView() {};
  inline ~GtkWaveView() {};

  GtkRange parent;
  double start_x, start_y, start_value;
  GxWaveviewType waveview_type;


  virtual void     gtk_waveview_destroy   (GtkWidget*, gpointer);
  virtual gboolean gtk_waveview_refresh   (GtkWidget*, gpointer);
  virtual gboolean gtk_waveview_set_value (GtkWidget*, gpointer);


  virtual GtkWidget* gtk_wave_view();
  virtual GtkWidget* gtk_wave_live_view(float*, float*, GtkAdjustment*);
};


/* prototype functions wrapping around class methods */
void gx_waveview_set_value(GtkWidget*, gpointer);
void gx_waveview_destroy(GtkWidget*, gpointer);
void gx_waveview_refresh(GtkWidget*, gpointer);

GtkWidget* gx_wave_view();
GtkWidget* gx_wave_live_view(float*, float*, GtkAdjustment*);


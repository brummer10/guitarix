
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
virtual GtkWidget *gtk_wave_live_view(float* infloat,GtkAdjustment *_adjustment);

};
#endif


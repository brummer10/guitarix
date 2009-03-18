
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
 
virtual GtkWidget *gtk_hslider_new_with_adjustment(GtkAdjustment *_adjustment);
virtual GtkWidget *gtk_toggle_new_with_adjustment(GtkAdjustment *_adjustment);
virtual GtkWidget *gtk_regler_new_with_adjustment(GtkAdjustment *_adjustment);
virtual GtkWidget *gtk_big_regler_new_with_adjustment(GtkAdjustment *_adjustment);
};
#endif


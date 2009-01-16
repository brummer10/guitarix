
// ***** GtkRegler.h *****
/******************************************************************************
part of guitarix, use  knobs with Gtk
******************************************************************************/

#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>

#ifndef GtkReglerH
#define GtkReglerrH

class GtkRegler
{
private:

public:
    GtkRange parent;
    int regler_type;
    double start_x, start_y, start_value;

  GtkRegler();
  ~GtkRegler();
 
virtual GtkWidget *gtk_regler_new_with_adjustment(GtkAdjustment *_adjustment, int x, int y,int step,const char *reglerpix, const char *reglerpix1);
};
#endif


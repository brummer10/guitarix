
// ***** GtkRegler.cpp *****
/******************************************************************************
part of guitarix, use  reglers with Gtk
******************************************************************************/

#include"GtkRegler.h"

#define GTK_TYPE_REGLER          (gtk_regler_get_type())
#define GTK_REGLER(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_REGLER, GtkRegler))
#define GTK_IS_REGLER(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_REGLER))
#define GTK_REGLER_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass),  GTK_TYPE_REGLER, GtkReglerClass))
#define GTK_IS_REGLER_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GTK_TYPE_REGLER))

GtkRegler::GtkRegler()
// GtkRegler constructor
{
 
}

GtkRegler::~GtkRegler()
{
  // Nothing specific to do...
}

struct GtkReglerClass
{
    GtkRangeClass parent_class;
    GdkPixbuf *regler_image;
    GdkPixbuf *regler_image1;
    GdkPixbuf *bigregler_image;
    GdkPixbuf *bigregler_image1;
    GdkPixbuf *toggle_image;
    GdkPixbuf *toggle_image1;
    GdkPixbuf *slider_image;
    GdkPixbuf *slider_image1;
};

GType gtk_regler_get_type ();

int regler_x = 25;
int regler_y = 25;
int regler_step = 88; 
const char *reglerpix = "knobgrs.png";
const char *reglerpix1 = "knobgrs1.png";
int bigregler_x = 50;
int bigregler_y = 50;
int bigregler_step = 88; 
const char *bigreglerpix = "knobgr.png";
const char *bigreglerpix1 = "knobgr1.png";
int toggle_x = 37 ;
int toggle_y = 28 ;
int toggle_step = 1; 
const char *togglepix = "switchit.png";
const char *togglepix1 = "switchit1.png";
int slider_x = 120 ;
int slider_y = 10 ;
int slider_step = 96; 
const char *sliderpix = "sliderblacks.png";
const char *sliderpix1 = "sliderblacks1.png";

static bool Existstogglepix() 
    {
    struct stat my_stat;
    char          rcfilename[256];
    snprintf(rcfilename, 256, "%s", "/usr/local/share/guitarix/switchit.png");
    char          rcfilename1[256];
    snprintf(rcfilename1, 256, "%s", "/usr/share/guitarix/switchit.png");
    char          rcfilename2[256];
    snprintf(rcfilename2, 256, "%s", "/usr/local/share/guitarix/switchit1.png");
    char          rcfilename3[256];
    snprintf(rcfilename3, 256, "%s", "/usr/share/guitarix/switchit1.png");
    if (( stat(rcfilename, &my_stat) == 0) & ( stat(rcfilename2, &my_stat) == 0))
    {
    togglepix = "/usr/local/share/guitarix/switchit.png";
    togglepix1 = "/usr/local/share/guitarix/switchit1.png";
    }
    else if (( stat(rcfilename1, &my_stat) == 0) & ( stat(rcfilename3, &my_stat) == 0))
    {
    togglepix = "/usr/share/guitarix/switchit.png";
    togglepix1 = "/usr/share/guitarix/switchit1.png";
    }
    else
    {
    togglepix = "./rcstyles/switchit.png";
    togglepix1 = "./rcstyles/switchit1.png";
    }
    }

static bool Existsreglerpix() 
    {
    struct stat my_stat;
    char          rcfilename[256];
    snprintf(rcfilename, 256, "%s", "/usr/local/share/guitarix/knobgrs.png");
    char          rcfilename1[256];
    snprintf(rcfilename1, 256, "%s", "/usr/share/guitarix/knobgrs.png");
    char          rcfilename2[256];
    snprintf(rcfilename2, 256, "%s", "/usr/local/share/guitarix/knobgrs1.png");
    char          rcfilename3[256];
    snprintf(rcfilename3, 256, "%s", "/usr/share/guitarix/knobgrs1.png");
    if (( stat(rcfilename, &my_stat) == 0) & ( stat(rcfilename2, &my_stat) == 0))
    {
    reglerpix = "/usr/local/share/guitarix/knobgrs.png";
    reglerpix1 = "/usr/local/share/guitarix/knobgrs1.png";
    }
    else if (( stat(rcfilename1, &my_stat) == 0) & ( stat(rcfilename3, &my_stat) == 0))
    {
    reglerpix = "/usr/share/guitarix/knobgrs.png";
    reglerpix1 = "/usr/share/guitarix/knobgrs1.png";
    }
    else
    {
    reglerpix = "./rcstyles/knobgrs.png";
    reglerpix1 = "./rcstyles/knobgrs1.png";
    }
}

static bool Existsbigreglerpix() 
    {
    struct stat my_stat;
    char          rcfilename[256];
    snprintf(rcfilename, 256, "%s", "/usr/local/share/guitarix/knobgr.png");
    char          rcfilename1[256];
    snprintf(rcfilename1, 256, "%s", "/usr/share/guitarix/knobgr.png");
    char          rcfilename2[256];
    snprintf(rcfilename2, 256, "%s", "/usr/local/share/guitarix/knobgr1.png");
    char          rcfilename3[256];
    snprintf(rcfilename3, 256, "%s", "/usr/share/guitarix/knobgr1.png");
    if (( stat(rcfilename, &my_stat) == 0) & ( stat(rcfilename2, &my_stat) == 0))
    {
    bigreglerpix = "/usr/local/share/guitarix/knobgr.png";
    bigreglerpix1 = "/usr/local/share/guitarix/knobgr1.png";
    }
    else if (( stat(rcfilename1, &my_stat) == 0) & ( stat(rcfilename3, &my_stat) == 0))
    {
    bigreglerpix = "/usr/share/guitarix/knobgr.png";
    bigreglerpix1 = "/usr/share/guitarix/knobgr1.png";
    }
    else
    {
    bigreglerpix = "./rcstyles/knobgr.png";
    bigreglerpix1 = "./rcstyles/knobgr1.png";
    }
}

static bool Existssliderpix() 
    {
    struct stat my_stat;
    char          rcfilename[256];
    snprintf(rcfilename, 256, "%s", "/usr/local/share/guitarix/sliderblacks.png");
    char          rcfilename1[256];
    snprintf(rcfilename1, 256, "%s", "/usr/share/guitarix/sliderblacks.png");
    char          rcfilename2[256];
    snprintf(rcfilename2, 256, "%s", "/usr/local/share/guitarix/sliderblacks1.png");
    char          rcfilename3[256];
    snprintf(rcfilename3, 256, "%s", "/usr/share/guitarix/sliderblacks1.png");
    if (( stat(rcfilename, &my_stat) == 0) & ( stat(rcfilename2, &my_stat) == 0))
    {
    sliderpix = "/usr/local/share/guitarix/sliderblacks.png";
    sliderpix1 = "/usr/local/share/guitarix/sliderblacks1.png";
    }
    else if (( stat(rcfilename1, &my_stat) == 0) & ( stat(rcfilename3, &my_stat) == 0))
    {
    sliderpix = "/usr/share/guitarix/sliderblacks.png";
    sliderpix1 = "/usr/share/guitarix/sliderblacks1.png";
    }
    else
    {
    sliderpix = "./rcstyles/sliderblacks.png";
    sliderpix1 = "./rcstyles/sliderblacks1.png";
    }
}

static gboolean gtk_regler_expose (GtkWidget *widget, GdkEventExpose *event)
{
    g_assert(GTK_IS_REGLER(widget));
    
    GtkRegler *regler = GTK_REGLER(widget);
    GdkWindow *window = widget->window;
    GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
    int reglerx = widget->allocation.x, reglery = widget->allocation.y; 
if (regler->regler_type == 0) {
    reglerx += (widget->allocation.width - regler_x) / 2;
    reglery += (widget->allocation.height - regler_y) / 2;
    int reglerstate = (int)((adj->value - adj->lower) * regler_step / (adj->upper - adj->lower));

    if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
        gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_image1, reglerstate * regler_x, 0, reglerx, reglery, regler_x, regler_y, GDK_RGB_DITHER_NORMAL, 0, 0);
 gtk_paint_focus(widget->style, window, GTK_STATE_NORMAL, NULL, widget, NULL, reglerx, reglery, regler_x, regler_y);
    }
    else {
        gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_image, reglerstate * regler_x, 0, reglerx, reglery,regler_x, regler_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }
    }

else if (regler->regler_type == 1) {
    reglerx += (widget->allocation.width - bigregler_x) / 2;
    reglery += (widget->allocation.height - bigregler_y) / 2;
    int reglerstate = (int)((adj->value - adj->lower) * bigregler_step / (adj->upper - adj->lower));

    if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
        gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigregler_image1, reglerstate * bigregler_x,0, reglerx, reglery, bigregler_x, bigregler_y, GDK_RGB_DITHER_NORMAL, 0, 0);
 gtk_paint_focus(widget->style, window, GTK_STATE_NORMAL, NULL, widget, NULL, reglerx, reglery, bigregler_x, bigregler_y);
    }
    else {
        gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigregler_image, reglerstate * bigregler_x, 0, reglerx, reglery, bigregler_x, bigregler_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }
    }

 else if (regler->regler_type == 2) {
    reglerx += (widget->allocation.width - toggle_x) / 2;
    reglery += (widget->allocation.height - toggle_y) / 2;
    int reglerstate = (int)((adj->value - adj->lower) * toggle_step / (adj->upper - adj->lower));
    if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
        gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_image1, reglerstate * toggle_x, 0, reglerx, reglery, toggle_x, toggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
// gtk_paint_focus(widget->style, window, GTK_STATE_NORMAL, NULL, widget, NULL, reglerx, reglery, toggle_x, toggle_y);
    }
    else {
        gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_image, reglerstate * toggle_x, 0, reglerx, reglery, toggle_x, toggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }
    }

 else if (regler->regler_type == 3) {
    reglerx += (widget->allocation.width - slider_x) / 2;
    reglery += (widget->allocation.height - slider_y) / 2;
    int reglerstate = (int)((adj->value - adj->lower) * slider_step / (adj->upper - adj->lower));
    if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
        gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1, 0, reglerstate * slider_y, reglerx, reglery, slider_x, slider_y, GDK_RGB_DITHER_NORMAL, 0, 0);
 gtk_paint_focus(widget->style, window, GTK_STATE_NORMAL, NULL, widget, NULL, reglerx, reglery, slider_x, slider_y);
    }
    else {
        gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image, 0,reglerstate * slider_y, reglerx, reglery, slider_x, slider_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }
    }


    return TRUE;
}

static gboolean gtk_regler_leave_out (GtkWidget *widget, GdkEventCrossing *event)
{
    g_assert(GTK_IS_REGLER(widget));
    GtkRegler *regler = GTK_REGLER(widget);
    GdkWindow *window = widget->window;
    GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
    int reglerx = widget->allocation.x, reglery = widget->allocation.y;
if (regler->regler_type == 0) {
    reglerx += (widget->allocation.width - regler_x) / 2;
    reglery += (widget->allocation.height - regler_y) / 2;
    int reglerstate = (int)((adj->value - adj->lower) * regler_step / (adj->upper - adj->lower));
    gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_image, reglerstate * regler_x, regler->regler_type * regler_y, reglerx, reglery, regler_x, regler_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }

else if (regler->regler_type == 1) {
    reglerx += (widget->allocation.width - bigregler_x) / 2;
    reglery += (widget->allocation.height - bigregler_y) / 2;
    int reglerstate = (int)((adj->value - adj->lower) * bigregler_step / (adj->upper - adj->lower));
        gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigregler_image, reglerstate * bigregler_x,0, reglerx, reglery, bigregler_x, bigregler_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }

 else if (regler->regler_type == 2) {
    reglerx += (widget->allocation.width - toggle_x) / 2;
    reglery += (widget->allocation.height - toggle_y) / 2;
   int reglerstate = (int)((adj->value - adj->lower) * toggle_step / (adj->upper - adj->lower));
        gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_image, reglerstate * toggle_x, 0, reglerx, reglery, toggle_x, toggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }

 else if (regler->regler_type == 3) {
    reglerx += (widget->allocation.width - slider_x) / 2;
    reglery += (widget->allocation.height - slider_y) / 2;
    int reglerstate = (int)((adj->value - adj->lower) * slider_step / (adj->upper - adj->lower));
        gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image, 0, reglerstate * slider_y, reglerx, reglery, slider_x, slider_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }

    return TRUE;
}

static gboolean gtk_regler_enter_in (GtkWidget *widget, GdkEventCrossing *event)
{
    g_assert(GTK_IS_REGLER(widget));   
    GtkRegler *regler = GTK_REGLER(widget);
    GdkWindow *window = widget->window;
    GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
    int reglerx = widget->allocation.x, reglery = widget->allocation.y;
if (regler->regler_type == 0) {
    reglerx += (widget->allocation.width - regler_x) / 2;
    reglery += (widget->allocation.height - regler_y) / 2;
    int reglerstate = (int)((adj->value - adj->lower) * regler_step / (adj->upper - adj->lower));
    gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_image1, reglerstate * regler_x, regler->regler_type * regler_y, reglerx, reglery, regler_x, regler_y, GDK_RGB_DITHER_NORMAL, 0, 0);
   }

else if (regler->regler_type == 1) {
    reglerx += (widget->allocation.width - bigregler_x) / 2;
    reglery += (widget->allocation.height - bigregler_y) / 2;
    int reglerstate = (int)((adj->value - adj->lower) * bigregler_step / (adj->upper - adj->lower));
        gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigregler_image1, reglerstate * bigregler_x,0, reglerx, reglery, bigregler_x, bigregler_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }

 else if (regler->regler_type == 2) {
    reglerx += (widget->allocation.width - toggle_x) / 2;
    reglery += (widget->allocation.height - toggle_y) / 2;
  int reglerstate = (int)((adj->value - adj->lower) * toggle_step / (adj->upper - adj->lower));
        gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_image1, reglerstate * toggle_x, 0, reglerx, reglery, toggle_x, toggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }

 else if (regler->regler_type == 3) {
    reglerx += (widget->allocation.width - slider_x) / 2;
    reglery += (widget->allocation.height - slider_y) / 2;
    int reglerstate = (int)((adj->value - adj->lower) * slider_step / (adj->upper - adj->lower));
        gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1, 0, reglerstate * slider_y, reglerx, reglery, slider_x, slider_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }

    return TRUE;
}

static void gtk_regler_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
    g_assert(GTK_IS_REGLER(widget));
    GtkRegler *regler = GTK_REGLER(widget);
if (regler->regler_type == 0) {
    requisition->width = regler_x;
    requisition->height = regler_y;
    }
else if (regler->regler_type == 1) {
    requisition->width = bigregler_x;
    requisition->height = bigregler_y;
    }
else if (regler->regler_type == 2) {
    requisition->width = toggle_x;
    requisition->height = toggle_y;
   }
else if (regler->regler_type == 3) {
    requisition->width = slider_x;
    requisition->height = slider_y;
   }
}

static void gtk_regler_set_value (GtkWidget *widget, int dir_down)
{
    g_assert(GTK_IS_REGLER(widget));
    GtkRegler *regler = GTK_REGLER(widget);
    GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));

    int oldstep = (int)(0.5f + (adj->value - adj->lower) / adj->step_increment);
    int step;
    int nsteps = (int)(0.5f + (adj->upper - adj->lower) / adj->step_increment); 
    if (dir_down)
        step = oldstep - 1;
    else
        step = oldstep + 1;    
    float value = adj->lower + step * double(adj->upper - adj->lower) / nsteps;
    gtk_widget_grab_focus(widget);
    gtk_range_set_value(GTK_RANGE(widget), value);
}

static gboolean gtk_regler_key_press (GtkWidget *widget, GdkEventKey *event)
{
    g_assert(GTK_IS_REGLER(widget));
    GtkRegler *regler = GTK_REGLER(widget);
    GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
    switch(event->keyval)
    {
        case GDK_Home:
            gtk_range_set_value(GTK_RANGE(widget), adj->lower);
            return TRUE;
        case GDK_End:
            gtk_range_set_value(GTK_RANGE(widget), adj->upper);
            return TRUE; 
        case GDK_Up:
            gtk_regler_set_value(widget, 0);
            return TRUE;
        case GDK_Right:
            gtk_regler_set_value(widget, 0);
            return TRUE;
        case GDK_Down:
            gtk_regler_set_value(widget, 1);
            return TRUE;
        case GDK_Left:
            gtk_regler_set_value(widget, 1);
            return TRUE;
    }
    
    return FALSE;
}

static gboolean gtk_regler_button_press (GtkWidget *widget, GdkEventButton *event)
{
    g_assert(GTK_IS_REGLER(widget));
    GtkRegler *regler = GTK_REGLER(widget);
    gtk_widget_grab_focus(widget);
    gtk_widget_grab_default (widget);
    gtk_grab_add(widget);
if (regler->regler_type == 0) {
    regler->start_x = event->x;
    regler->start_y = event->y;
    regler->start_value = gtk_range_get_value(GTK_RANGE(widget));
    }
else if (regler->regler_type == 1) {
    regler->start_x = event->x;
    regler->start_y = event->y;
    regler->start_value = gtk_range_get_value(GTK_RANGE(widget));
    }
else if (regler->regler_type == 2) {
 
    regler->start_value = gtk_range_get_value(GTK_RANGE(widget));
    if ( regler->start_value == 0) gtk_range_set_value(GTK_RANGE(widget), 1);
    else gtk_range_set_value(GTK_RANGE(widget), 0);
    }
else if (regler->regler_type == 3) {
    regler->start_x = event->x;
    regler->start_y = event->y;
    regler->start_value = gtk_range_get_value(GTK_RANGE(widget));
    }
    return TRUE;
}

static gboolean gtk_regler_button_release (GtkWidget *widget, GdkEventButton *event)
{
    g_assert(GTK_IS_REGLER(widget));
    if (GTK_WIDGET_HAS_GRAB(widget))
        gtk_grab_remove(widget);
    return FALSE;
}

static gboolean gtk_regler_pointer_motion (GtkWidget *widget, GdkEventMotion *event)
{
    g_assert(GTK_IS_REGLER(widget));
    GtkRegler *regler = GTK_REGLER(widget);
    GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
    if (GTK_WIDGET_HAS_GRAB(widget)) {
        double mal;
	if (event->x-regler->start_x < 0) mal = 1.0;
        else mal = -1.0;
        gtk_range_set_value(GTK_RANGE(widget), regler->start_value - (event->y+(pow((event->x-regler->start_x)/2,2.0)*mal) - regler->start_y) *adj->step_increment); 
}
    return FALSE;
}

static gboolean gtk_regler_scroll (GtkWidget *widget, GdkEventScroll *event)
{
    gtk_regler_set_value(widget, event->direction);
    return FALSE;
}

static void gtk_regler_class_init (GtkReglerClass *klass)
{
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);
    widget_class->enter_notify_event = gtk_regler_enter_in;
    widget_class->leave_notify_event = gtk_regler_leave_out;
    widget_class->expose_event = gtk_regler_expose;
    widget_class->size_request = gtk_regler_size_request;
    widget_class->button_press_event = gtk_regler_button_press;
    widget_class->button_release_event = gtk_regler_button_release;
    widget_class->motion_notify_event = gtk_regler_pointer_motion;
    widget_class->key_press_event = gtk_regler_key_press;
    widget_class->scroll_event = gtk_regler_scroll;
Existsreglerpix();
Existsbigreglerpix();
Existstogglepix();
Existssliderpix();
    GError *error = NULL;
    klass->regler_image = gdk_pixbuf_new_from_file( reglerpix, &error);
    g_assert(klass->regler_image != NULL);
    klass->regler_image1 = gdk_pixbuf_new_from_file( reglerpix1, &error);
    g_assert(klass->regler_image1 != NULL);
    klass->bigregler_image = gdk_pixbuf_new_from_file( bigreglerpix, &error);
    g_assert(klass->bigregler_image != NULL);
    klass->bigregler_image1 = gdk_pixbuf_new_from_file( bigreglerpix1, &error);
    g_assert(klass->bigregler_image1 != NULL);
    klass->toggle_image = gdk_pixbuf_new_from_file( togglepix, &error);
    g_assert(klass->toggle_image != NULL);
    klass->toggle_image1 = gdk_pixbuf_new_from_file( togglepix1, &error);
    g_assert(klass->toggle_image1 != NULL);
    klass->slider_image = gdk_pixbuf_new_from_file( sliderpix, &error);
    g_assert(klass->slider_image != NULL);
    klass->slider_image1 = gdk_pixbuf_new_from_file( sliderpix1, &error);
    g_assert(klass->slider_image1 != NULL);
}

static void gtk_regler_init (GtkRegler *regler)
{
    GtkWidget *widget = GTK_WIDGET(regler);
    GTK_WIDGET_SET_FLAGS (GTK_WIDGET(regler), GTK_CAN_FOCUS);
    GTK_WIDGET_SET_FLAGS (GTK_WIDGET(regler), GTK_CAN_DEFAULT);
if (regler->regler_type == 0) {
    widget->requisition.width = regler_x;
    widget->requisition.height = regler_y;
    }
else if (regler->regler_type == 1) {
    widget->requisition.width = bigregler_x;
    widget->requisition.height = bigregler_y;
    }
else if (regler->regler_type == 2) {
    widget->requisition.width = toggle_x;
    widget->requisition.height = toggle_y;
    }
else if (regler->regler_type == 3) {
    widget->requisition.width = slider_x;
    widget->requisition.height = slider_y;
    }
}

static gboolean gtk_regler_value_changed(gpointer obj)
{
    GtkWidget *widget = (GtkWidget *)obj;
    gtk_widget_queue_draw(widget);
    return FALSE;
}

 GtkWidget *GtkRegler::gtk_regler_new_with_adjustment(GtkAdjustment *_adjustment)
{
    GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_REGLER, NULL ));
    GtkRegler *regler = GTK_REGLER(widget);
    regler->regler_type = 0;
    if (widget) {
        gtk_range_set_adjustment(GTK_RANGE(widget), _adjustment);
        gtk_signal_connect(GTK_OBJECT(widget), "value-changed", G_CALLBACK(gtk_regler_value_changed), widget);
    }
    return widget;
}

 GtkWidget *GtkRegler::gtk_big_regler_new_with_adjustment(GtkAdjustment *_adjustment)
{
    GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_REGLER, NULL ));
    GtkRegler *regler = GTK_REGLER(widget);
    regler->regler_type = 1;
    if (widget) {
        gtk_range_set_adjustment(GTK_RANGE(widget), _adjustment);
        gtk_signal_connect(GTK_OBJECT(widget), "value-changed", G_CALLBACK(gtk_regler_value_changed), widget);
    }
    return widget;
}

 GtkWidget *GtkRegler::gtk_toggle_new_with_adjustment(GtkAdjustment *_adjustment)
{
    GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_REGLER, NULL ));
    GtkRegler *regler = GTK_REGLER(widget);
    regler->regler_type = 2;
    if (widget) {
        gtk_range_set_adjustment(GTK_RANGE(widget), _adjustment);
        gtk_signal_connect(GTK_OBJECT(widget), "value-changed", G_CALLBACK(gtk_regler_value_changed), widget);
    }
    return widget;
}

 GtkWidget *GtkRegler::gtk_hslider_new_with_adjustment(GtkAdjustment *_adjustment)
{
    GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_REGLER, NULL ));
    GtkRegler *regler = GTK_REGLER(widget);
    regler->regler_type = 3;
    if (widget) {
        gtk_range_set_adjustment(GTK_RANGE(widget), _adjustment);
        gtk_signal_connect(GTK_OBJECT(widget), "value-changed", G_CALLBACK(gtk_regler_value_changed), widget);
    }
    return widget;
}

GType gtk_regler_get_type (void)
{
    static GType kn_type = 0;
    if (!kn_type) {
        
        static const GTypeInfo kn_info = {
            sizeof(GtkReglerClass), NULL,  NULL, (GClassInitFunc)gtk_regler_class_init, NULL, NULL, sizeof (GtkRegler), 0, (GInstanceInitFunc)gtk_regler_init
        };
            kn_type = g_type_register_static(GTK_TYPE_RANGE,  "GtkRegler", &kn_info, (GTypeFlags)0);
    }
    return kn_type;
}


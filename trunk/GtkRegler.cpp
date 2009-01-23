
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
};

GType gtk_regler_get_type ();

int regler_x ;
int regler_y ;
int regler_step; 
const char *reglerpix;
const char *reglerpix1;

static gboolean gtk_regler_expose (GtkWidget *widget, GdkEventExpose *event)
{
    g_assert(GTK_IS_REGLER(widget));
    
    GtkRegler *regler = GTK_REGLER(widget);
    GdkWindow *window = widget->window;
    GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
    int reglerx = widget->allocation.x, reglery = widget->allocation.y; 
    reglerx += (widget->allocation.width - regler_x) / 2;
    reglery += (widget->allocation.height - regler_y) / 2;
    int reglerstate = (int)((adj->value - adj->lower) * regler_step / (adj->upper - adj->lower));

    if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE) {
        gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_image1, reglerstate * regler_x, regler->regler_type * regler_y, reglerx, reglery, regler_x, regler_y, GDK_RGB_DITHER_NORMAL, 0, 0);
 gtk_paint_focus(widget->style, window, GTK_STATE_NORMAL, NULL, widget, NULL, reglerx, reglery, regler_x, regler_y);
    }
    else {
        gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_image, reglerstate * regler_x, regler->regler_type * regler_y, reglerx, reglery, regler_x, regler_y, GDK_RGB_DITHER_NORMAL, 0, 0);
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
    reglerx += (widget->allocation.width - regler_x) / 2;
    reglery += (widget->allocation.height - regler_y) / 2;
    int reglerstate = (int)((adj->value - adj->lower) * regler_step / (adj->upper - adj->lower));
    gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_image, reglerstate * regler_x, regler->regler_type * regler_y, reglerx, reglery, regler_x, regler_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    return TRUE;
}

static gboolean gtk_regler_enter_in (GtkWidget *widget, GdkEventCrossing *event)
{
    g_assert(GTK_IS_REGLER(widget));   
    GtkRegler *regler = GTK_REGLER(widget);
    GdkWindow *window = widget->window;
    GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
    int reglerx = widget->allocation.x, reglery = widget->allocation.y;
    reglerx += (widget->allocation.width - regler_x) / 2;
    reglery += (widget->allocation.height - regler_y) / 2;
    int reglerstate = (int)((adj->value - adj->lower) * regler_step / (adj->upper - adj->lower));
    gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_image1, reglerstate * regler_x, regler->regler_type * regler_y, reglerx, reglery, regler_x, regler_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    return TRUE;
}

static void gtk_regler_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
    g_assert(GTK_IS_REGLER(widget));
    GtkRegler *regler = GTK_REGLER(widget);
    requisition->width = regler_x;
    requisition->height = regler_y;
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
    regler->start_x = event->x;
    regler->start_y = event->y;
    regler->start_value = gtk_range_get_value(GTK_RANGE(widget));
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
        gtk_range_set_value(GTK_RANGE(widget), regler->start_value - (event->y+(pow(event->x-regler->start_x,2.0)*mal) - regler->start_y) *adj->step_increment); 
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
    GError *error = NULL;
    klass->regler_image = gdk_pixbuf_new_from_file( reglerpix, &error);
    g_assert(klass->regler_image != NULL);
    klass->regler_image1 = gdk_pixbuf_new_from_file( reglerpix1, &error);
    g_assert(klass->regler_image1 != NULL);
}

static void gtk_regler_init (GtkRegler *regler)
{
    GtkWidget *widget = GTK_WIDGET(regler);
    GTK_WIDGET_SET_FLAGS (GTK_WIDGET(regler), GTK_CAN_FOCUS);
    GTK_WIDGET_SET_FLAGS (GTK_WIDGET(regler), GTK_CAN_DEFAULT);
    widget->requisition.width = regler_x;
    widget->requisition.height = regler_y;
}

static gboolean gtk_regler_value_changed(gpointer obj)
{
    GtkWidget *widget = (GtkWidget *)obj;
    gtk_widget_queue_draw(widget);
    return FALSE;
}

 GtkWidget *GtkRegler::gtk_regler_new_with_adjustment(GtkAdjustment *_adjustment,int x, int y,int step, const char *reglerp, const char *reglerp1)
{
    regler_x = x;
    regler_y = y;
    regler_step = step-1;
    reglerpix = reglerp;
    reglerpix1 = reglerp1;
    GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_REGLER, NULL ));
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


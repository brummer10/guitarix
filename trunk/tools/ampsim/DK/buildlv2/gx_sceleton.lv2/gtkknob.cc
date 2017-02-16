/*
 * Copyright (C) 2011 Hermann Meyer, Andreas Degert
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
 * ---------------------------------------------------------------------------
 *
 *        file: gtkkob.cc 
 *
 * ----------------------------------------------------------------------------
 */

#include "gtkknob.h"

#include <gdk/gdkkeysyms.h>
#include <math.h>


#ifndef min
#define min(x, y) ((x) < (y) ? (x) : (y))
#endif
#ifndef max
#define max(x, y) ((x) < (y) ? (y) : (x))
#endif


#define GTK_EFNAME_KNOB_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), GTK_TYPE_EFNAME_KNOB, GtkefnameKnobPrivate))

G_DEFINE_TYPE(GtkefnameKnob, gtk_knob, GTK_TYPE_RANGE);

typedef struct _GtkefnameKnobPrivate GtkefnameKnobPrivate;

struct _GtkefnameKnobPrivate
{
    int knob_x;
    int knob_y;
    int knob_step;
    int button_is;
    double start_x, start_y, max_value;
    int last_quadrant;
    int show_value;
    int model;   
};

const double scale_zero = 20 * (M_PI/180); // defines "dead zone" for knobs

static void print_value(GObject *widget, char* s)
{
    
    //GtkWidget * label = (GTK_WIDGET(obj));
    float v = gtk_adjustment_get_value(GTK_ADJUSTMENT(widget));
    //char s[64];
    if (gtk_adjustment_get_step_increment(GTK_ADJUSTMENT(widget)) < 0.009999)
    {
        const char* format[] = {"%.1f", "%.2f", "%.3f"};
        snprintf(s, 63, format[3-1], v);
    }
    else if (gtk_adjustment_get_step_increment(GTK_ADJUSTMENT(widget)) < 0.09999)
    {
        const char* format[] = {"%.1f", "%.2f", "%.3f"};
        snprintf(s, 63, format[2-1], v);
    }
    else if (gtk_adjustment_get_step_increment(GTK_ADJUSTMENT(widget)) < 0.9999)
    {
        const char* format[] = {"%.1f", "%.2f", "%.3f"};
        snprintf(s, 63, format[1-1], v);
    }
    else if (gtk_adjustment_get_step_increment(GTK_ADJUSTMENT(widget)) < 9.9999)
    {
        snprintf(s, 63, "%d", (int)v);
    }
    else
        snprintf(s, 63, "%d", (int)v);
    //return s;
}

static void knob_expose(GtkWidget *widget, int knob_x, int knob_y, GdkEventExpose *event, int arc_offset)
{
    /** check resize **/
    int grow;
    GtkefnameKnobPrivate *priv = GTK_EFNAME_KNOB_GET_PRIVATE(widget);
    GtkAllocation *allocation = g_new0 (GtkAllocation, 1);
    gtk_widget_get_allocation(GTK_WIDGET(widget), allocation); 
    if(allocation->width > allocation->height) {
        grow = allocation->height;
    } else {
        grow =  allocation->width;
    }
    if (priv->model == 1) {
        knob_x = grow-24;
        knob_y = grow-24; 
    } else {
        knob_x = grow-4;
        knob_y = grow-4;
    }
    /** get values for the knob **/
    GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));

    int knobx = (allocation->x+2 + (allocation->width-4 - knob_x) * 0.5);
    int knobx1 = (allocation->x+2 + (allocation->width-4)* 0.5);

     int knoby = (allocation->y+2 + (allocation->height-4 - knob_y) * 0.5);
    int knoby1 = (allocation->y+2 + (allocation->height-4) * 0.5);

    double knobstate = (gtk_adjustment_get_value(adj) - gtk_adjustment_get_lower(adj)) / (gtk_adjustment_get_upper(adj) - gtk_adjustment_get_lower(adj));
    double angle = scale_zero + knobstate * 2 * (M_PI - scale_zero);
    
    double pointer_off =knob_x/6;
    double radius = min(knob_x-pointer_off, knob_y-pointer_off) / 2;
    double lengh_x = (knobx+radius+pointer_off/2) - radius * sin(angle);
    double lengh_y = (knoby+radius+pointer_off/2) + radius * cos(angle);
    //double radius1 = min(knob_x, knob_y) / 2 ; // center
    double radius_x = (knobx+radius+pointer_off/2) - radius/ 1.18 * sin(angle);
    double radius_y = (knoby+radius+pointer_off/2) + radius/ 1.18 * cos(angle);

    /** create knobs with cairo **/
    cairo_t *cr = gdk_cairo_create(GDK_DRAWABLE(gtk_widget_get_window(widget)));
    GdkRegion *region;
    region = gdk_region_rectangle (allocation);
    gdk_region_intersect (region, event->region);
    gdk_cairo_region (cr, region);
    cairo_clip (cr);
    
    if (priv->model != 3) {
        cairo_arc(cr,knobx1+arc_offset, knoby1+arc_offset, knob_x/2.1, 0, 2 * M_PI );
        cairo_pattern_t*pat =
            cairo_pattern_create_radial (knobx1+arc_offset-knob_x/6,knoby1+arc_offset-knob_x/6, 1,knobx1+arc_offset,knoby1+arc_offset,knob_x/2.1 );
            cairo_pattern_add_color_stop_rgb (pat, 0.5, 0.15, 0.15, 0.15);
            cairo_pattern_add_color_stop_rgb (pat, 0.7, 0.2, 0.2, 0.2);
            cairo_pattern_add_color_stop_rgb (pat, 0.9, 0.1, 0.1,0.1);
            cairo_pattern_add_color_stop_rgb (pat, 1, 0.1, 0.1,0.1);
        
        cairo_set_source (cr, pat);
        cairo_fill_preserve (cr);
        cairo_set_source_rgb (cr, 0., 0., 0.);
        cairo_set_line_width(cr, 1.0);
        cairo_stroke(cr);

        cairo_arc(cr,knobx1+arc_offset, knoby1+arc_offset, knob_x/3.1, 0, 2 * M_PI );
        pat =
            cairo_pattern_create_radial (knobx1+arc_offset-knob_x/6,knoby1+arc_offset-knob_x/6, 1,knobx1+arc_offset,knoby1+arc_offset,knob_x/2.1 );
         if (priv->model == 1) {
            if (knobstate) {
                cairo_pattern_add_color_stop_rgb (pat, 0, 0.2, 0.2, 0.2);
                cairo_pattern_add_color_stop_rgb (pat, 0.7, 0.3, 0.3, 0.3);
                cairo_pattern_add_color_stop_rgb (pat, 1, 0.2, 0.2,0.2);  
            } else {
                cairo_pattern_add_color_stop_rgb (pat, 0, 0.1, 0.1, 0.1);
                cairo_pattern_add_color_stop_rgb (pat, 0.7, 0.2, 0.2, 0.2);
                cairo_pattern_add_color_stop_rgb (pat, 1, 0.1, 0.1,0.1); 
            }
        } else {
            cairo_pattern_add_color_stop_rgb (pat, 0, 0.1, 0.1, 0.1);
            cairo_pattern_add_color_stop_rgb (pat, 0.7, 0.2, 0.2, 0.2);
            cairo_pattern_add_color_stop_rgb (pat, 1, 0.1, 0.1,0.1);
        } 
        
        cairo_set_source (cr, pat);
        cairo_fill_preserve (cr);
        cairo_set_source_rgb (cr, 0.1, 0.1, 0.1);
        cairo_set_line_width(cr, 4.0);
        cairo_stroke_preserve(cr);
        cairo_arc(cr,knobx1+arc_offset, knoby1+arc_offset, knob_x/3.1, 0, 2 * M_PI );
        cairo_set_source_rgb (cr, 0., 0., 0.);
        cairo_set_line_width(cr, 1.0);
        cairo_stroke(cr);

        /** create a rotating pointer on the kob**/
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND); 
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_BEVEL);
        cairo_move_to(cr, radius_x, radius_y);
        cairo_line_to(cr,lengh_x,lengh_y);
        cairo_set_line_width(cr,min(5, max(2,knob_x/30)));
        cairo_set_source_rgb (cr,0.63,0.63,0.63);
        cairo_stroke(cr);
        
        /** show value on the kob**/
        char s[64];
        print_value(G_OBJECT(adj),s);
        cairo_set_source_rgba (cr, 0.6, 0.6, 0.6,0.6);
        cairo_set_font_size (cr, 11.0);
        cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
                                   CAIRO_FONT_WEIGHT_BOLD);
        cairo_text_extents_t extents;
        cairo_text_extents(cr, s, &extents);
        if (( priv->show_value || gtk_widget_has_focus(widget)== TRUE)& !priv->model) {
            cairo_move_to (cr, knobx1-extents.width/2, knoby1+extents.height/2);
            cairo_show_text(cr, s);
            //cairo_move_to (cr, knobx1+15., knoby1+5.);
        }
        
        if (priv->model == 1) {
            cairo_text_extents(cr,"Off", &extents);
            cairo_move_to (cr, knobx1-knob_x/2.4-extents.width/1.4, knoby1+knob_y/2+extents.height/1.4);
            cairo_show_text(cr, "Off");

            cairo_text_extents(cr,"On", &extents);
            cairo_move_to (cr, knobx1+knob_x/2.6-extents.width/2.3, knoby1+knob_y/2+extents.height/1.4);
            cairo_show_text(cr, "On");
        }
        cairo_pattern_destroy (pat);

    } else {
        GtkefnameKnob *knob = GTK_EFNAME_KNOB(widget);
        int switch_state = (int)knobstate;
        static int sw_state = 0;
        gint rect_width  = allocation->width-2;
        gint rect_height = allocation->height-3;
        if (rect_width <= 0 || rect_height <= 0) {
            return;
        }
        gint x0      = allocation->x+1;
        gint y0      = allocation->y+1;

        static double ne_w = 0.;
        if (ne_w != rect_width*rect_height || !(GDK_IS_PIXBUF (knob->pswitch_image))
            || sw_state != switch_state) {
            ne_w = rect_width*rect_height;
            sw_state = switch_state;
            if (G_IS_OBJECT(knob->pswitch_image)) {
                g_object_unref(knob->pswitch_image);
            }
            if (!sw_state) {
                knob->pswitch_image = gdk_pixbuf_scale_simple(
                  knob->switch_off_image, allocation->width ,allocation->height, GDK_INTERP_NEAREST);
                //g_object_unref(knob->switch_on_image);
            } else {
                knob->pswitch_image = gdk_pixbuf_scale_simple(
                  knob->switch_on_image, allocation->width ,allocation->height, GDK_INTERP_NEAREST);
                //g_object_unref(knob->switch_off_image);
                
            }
        }

        // base 
        gdk_cairo_set_source_pixbuf(cr,knob->pswitch_image, x0, y0);
        cairo_rectangle (cr, x0,y0,rect_width,rect_height);
        cairo_fill (cr);

    }


    g_free (allocation); 
    gdk_region_destroy (region);
    cairo_destroy(cr);
}

/****************************************************************
 ** general expose events for all "knob" controllers
 */

//----------- draw the Knob when moved
static gboolean gtk_knob_expose (GtkWidget *widget, GdkEventExpose *event)
{
    g_assert(GTK_IS_EFNAME_KNOB(widget));
    GtkefnameKnob *knob = GTK_EFNAME_KNOB(widget);
    GtkefnameKnobPrivate *priv = GTK_EFNAME_KNOB_GET_PRIVATE(knob);
    knob_expose(widget, priv->knob_x, priv->knob_y, event, 0);
    return TRUE;
}

/****************************************************************
 ** set initial size for GdkDrawable per type
 */

static void gtk_knob_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
    g_assert(GTK_IS_EFNAME_KNOB(widget));
    GtkefnameKnob *knob = GTK_EFNAME_KNOB(widget);
    GtkefnameKnobPrivate *priv = GTK_EFNAME_KNOB_GET_PRIVATE(knob);
    requisition->width = priv->knob_x;
    requisition->height = priv->knob_y;
}

/****************************************************************
 ** set value from key bindings
 */

static void gtk_knob_set_value (GtkWidget *widget, int dir_down)
{
    g_assert(GTK_IS_EFNAME_KNOB(widget));

    GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));

    int oldstep = (int)(0.5f + (gtk_adjustment_get_value(adj) - gtk_adjustment_get_lower(adj)) / gtk_adjustment_get_step_increment(adj));
    int step;
    int nsteps = (int)(0.5f + (gtk_adjustment_get_upper(adj) - gtk_adjustment_get_lower(adj)) / gtk_adjustment_get_step_increment(adj));
    if (dir_down)
        step = oldstep - 1;
    else
        step = oldstep + 1;
    float value = gtk_adjustment_get_lower(adj) + step * (double)(gtk_adjustment_get_upper(adj) - gtk_adjustment_get_lower(adj)) / nsteps;
    gtk_widget_grab_focus(widget);
    gtk_range_set_value(GTK_RANGE(widget), value);
}

/****************************************************************
 ** keyboard bindings
 */

static gboolean gtk_knob_key_press (GtkWidget *widget, GdkEventKey *event)
{
    g_assert(GTK_IS_EFNAME_KNOB(widget));

    GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
    switch (event->keyval) {
    case GDK_KEY_Home:
        gtk_range_set_value(GTK_RANGE(widget), gtk_adjustment_get_lower(adj));
        return TRUE;
    case GDK_KEY_End:
        gtk_range_set_value(GTK_RANGE(widget), gtk_adjustment_get_upper(adj));
        return TRUE;
    case GDK_KEY_Up:
        gtk_knob_set_value(widget, 0);
        return TRUE;
    case GDK_KEY_Right:
        gtk_knob_set_value(widget, 0);
        return TRUE;
    case GDK_KEY_Down:
        gtk_knob_set_value(widget, 1);
        return TRUE;
    case GDK_KEY_Left:
        gtk_knob_set_value(widget, 1);
        return TRUE;
    }

    return FALSE;
}


/****************************************************************
 ** alternative (radial) knob motion mode (ctrl + mouse pressed)
 */

static void knob_pointer_event(GtkWidget *widget, gdouble x, gdouble y, int knob_x, int knob_y,
                               gboolean drag, int state)
{
    static double last_y = 2e20;
    GtkefnameKnob *knob = GTK_EFNAME_KNOB(widget);
    GtkefnameKnobPrivate *priv = GTK_EFNAME_KNOB_GET_PRIVATE(knob);
    GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
    GtkAllocation *allocation = g_new0 (GtkAllocation, 1);
    gtk_widget_get_allocation(GTK_WIDGET(widget), allocation); 
    double radius =  min(knob_x, knob_y) / 2;
    int  knobx = (allocation->width - knob_x) / 2;
    int  knoby = (allocation->height - knob_y) / 2;
    double posx = (knobx + radius) - x; // x axis right -> left
    double posy = (knoby + radius) - y; // y axis top -> bottom
    double value;
    if (!drag) {
        if (state & GDK_CONTROL_MASK) {
            last_y = 2e20;
            return;
        } else {
            last_y = posy;
        }
    }
    if (last_y < 1e20) { // in drag started with Control Key
        const double scaling = 0.005;
        double scal = (state & GDK_SHIFT_MASK ? scaling*0.1 : scaling);
        if (priv->model == 1 || priv->model == 3) scal = 1;
        value = (last_y - posy) * scal;
        last_y = posy;
        gtk_range_set_value(GTK_RANGE(widget), gtk_adjustment_get_value(adj) - value * (gtk_adjustment_get_upper(adj) - gtk_adjustment_get_lower(adj)));
        return;
    }

    double angle = atan2(-posx, posy) + M_PI; // clockwise, zero at 6 o'clock, 0 .. 2*M_PI
    if (drag) {
        // block "forbidden zone" and direct moves between quadrant 1 and 4
        int quadrant = 1 + (int)(angle/M_PI_2);
        if (priv->last_quadrant == 1 && (quadrant == 3 || quadrant == 4)) {
            angle = scale_zero;
        } else if (priv->last_quadrant == 4 && (quadrant == 1 || quadrant == 2)) {
            angle = 2*M_PI - scale_zero;
        } else {
            if (angle < scale_zero) {
                angle = scale_zero;
            } else if (angle > 2*M_PI - scale_zero) {
                angle = 2*M_PI - scale_zero;
            }
            priv->last_quadrant = quadrant;
        }
    } else {
        if (angle < scale_zero) {
            angle = scale_zero;
        } else if (angle > 2*M_PI - scale_zero) {
            angle = 2*M_PI - scale_zero;
        }
        priv->last_quadrant = 0;
    }
    angle = (angle - scale_zero) / (2 * (M_PI-scale_zero)); // normalize to 0..1
    gtk_range_set_value(GTK_RANGE(widget), gtk_adjustment_get_lower(adj) + angle * (gtk_adjustment_get_upper(adj) - gtk_adjustment_get_lower(adj)));
    g_free (allocation); 
}

/****************************************************************
 ** mouse button pressed set value
 */

static gboolean gtk_knob_button_press (GtkWidget *widget, GdkEventButton *event)
{
    g_assert(GTK_IS_EFNAME_KNOB(widget));
    GtkefnameKnob *knob = GTK_EFNAME_KNOB(widget);
    GtkefnameKnobPrivate *priv = GTK_EFNAME_KNOB_GET_PRIVATE(knob);
    
    switch (event->button) {
    case 1:  // left button
        gtk_widget_grab_focus(widget);
        gtk_widget_grab_default (widget);
        gtk_grab_add(widget);
        priv->button_is = 1;
        if (priv->model == 1 || priv->model == 3) {
            float value = gtk_range_get_value(GTK_RANGE(widget));
            if(value) gtk_range_set_value(GTK_RANGE(widget),0);
            else gtk_range_set_value(GTK_RANGE(widget),1);
        }
        knob_pointer_event(widget, event->x, event->y, priv->knob_x, priv->knob_y,
                           FALSE, event->state);
        break;
    case 2: //wheel
        priv->button_is = 2;
        break;
    case 3:  // right button 
        priv->button_is = 3;
        break;
    default: // do nothing
        break;
    }
    return TRUE;
}

/****************************************************************
 ** mouse button release
 */

static gboolean gtk_knob_button_release (GtkWidget *widget, GdkEventButton *event)
{
    g_assert(GTK_IS_EFNAME_KNOB(widget));
    GtkefnameKnob *knob = GTK_EFNAME_KNOB(widget);
    GtkefnameKnobPrivate *priv = GTK_EFNAME_KNOB_GET_PRIVATE(knob);
    priv->button_is = 0;
    if (gtk_widget_has_grab(widget))
        gtk_grab_remove(widget);
    return FALSE;
}

/****************************************************************
 ** set the value from mouse movement
 */

static gboolean gtk_knob_pointer_motion (GtkWidget *widget, GdkEventMotion *event)
{
    g_assert(GTK_IS_EFNAME_KNOB(widget));
    GtkefnameKnob *knob = GTK_EFNAME_KNOB(widget);
    GtkefnameKnobPrivate *priv = GTK_EFNAME_KNOB_GET_PRIVATE(knob);
    gdk_event_request_motions (event);
    
    if (gtk_widget_has_grab(widget)) {
        knob_pointer_event(widget, event->x, event->y, priv->knob_x, priv->knob_y,
                           TRUE, event->state);
    }
    return FALSE;
}

/****************************************************************
 ** set value from mouseweel
 */

static gboolean gtk_knob_scroll (GtkWidget *widget, GdkEventScroll *event)
{
    gtk_knob_set_value(widget, event->direction);
    return FALSE;
}

/****************************************************************
 ** show value when enter the knob
 */

static gboolean gtk_knob_enter_in (GtkWidget *widget, GdkEventCrossing *event)
{
    GtkefnameKnob *knob = GTK_EFNAME_KNOB(widget);
    GtkefnameKnobPrivate *priv = GTK_EFNAME_KNOB_GET_PRIVATE(knob);
    priv->show_value = 1;
    gtk_widget_queue_draw(widget);
    return FALSE;

}

/****************************************************************
 ** hide value when leave the knob
 */

static gboolean gtk_knob_leave_out (GtkWidget *widget, GdkEventCrossing *event)
{
    GtkefnameKnob *knob = GTK_EFNAME_KNOB(widget);
    GtkefnameKnobPrivate *priv = GTK_EFNAME_KNOB_GET_PRIVATE(knob);
    priv->show_value = 0;
    gtk_widget_queue_draw(widget);
    return FALSE;
    
}

/****************************************************************
 ** destroy the knob
 */

static void gtk_knob_destroy(GtkObject *object)
{
    GtkefnameKnob *knob = GTK_EFNAME_KNOB(object);
    if (G_IS_OBJECT(knob->switch_on_image)) {
        g_object_unref(knob->switch_on_image);
    }
    knob->switch_on_image = NULL;
     if (G_IS_OBJECT(knob->switch_off_image)) {
        g_object_unref(knob->switch_off_image);
    }
    knob->switch_off_image = NULL;
    if (G_IS_OBJECT(knob->pswitch_image)) {
        g_object_unref(knob->pswitch_image);
    }
    knob->pswitch_image = NULL;
    GTK_OBJECT_CLASS(gtk_knob_parent_class)->destroy(object);
}

/****************************************************************
 ** init the GtkefnameKnobClass
 */

static void gtk_knob_class_init (GtkefnameKnobClass *klass)
{
    GObjectClass *obj_class = G_OBJECT_CLASS (klass);

    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);

    GtkObjectClass *object_class = (GtkObjectClass*) klass;

//--------- connect the events with funktions
    widget_class->enter_notify_event = gtk_knob_enter_in;
    widget_class->leave_notify_event = gtk_knob_leave_out;
    widget_class->expose_event = gtk_knob_expose;
    widget_class->size_request = gtk_knob_size_request;
    widget_class->button_press_event = gtk_knob_button_press;
    widget_class->button_release_event = gtk_knob_button_release;
    widget_class->motion_notify_event = gtk_knob_pointer_motion;
    widget_class->key_press_event = gtk_knob_key_press;
    widget_class->scroll_event = gtk_knob_scroll;
    object_class->destroy = gtk_knob_destroy;
    
    g_type_class_add_private(obj_class, sizeof (GtkefnameKnobPrivate));
}

/****************************************************************
 ** init the Knob type/size
 */

static void gtk_knob_init (GtkefnameKnob *knob)
{
    GtkWidget *widget = GTK_WIDGET(knob);
    GtkefnameKnobPrivate *priv = GTK_EFNAME_KNOB_GET_PRIVATE(knob);
    priv->knob_x = 62;
    priv->knob_y = 62;
    priv->knob_step = 86;
    priv->button_is = 0;
    priv->show_value = 0;
    priv->model = 0;

    knob->pswitch_image = NULL;
    knob->switch_on_image = gdk_pixbuf_new_from_resource("/gxplug/pswitch_on.png", NULL);
    knob->switch_off_image = gdk_pixbuf_new_from_resource("/gxplug/pswitch_off.png", NULL);
    
    gtk_widget_set_can_focus (GTK_WIDGET(knob), true);
    gtk_widget_set_can_default(GTK_WIDGET(knob), true);

    GtkRequisition requisition;
    gtk_widget_get_requisition(GTK_WIDGET(widget), &requisition); 
    requisition.width = priv->knob_x;
    requisition.height = priv->knob_y;
}

/****************************************************************
 ** redraw when value changed
 */

static gboolean gtk_knob_value_changed(gpointer obj)
{
    GtkWidget *widget = (GtkWidget *)obj;
    gtk_widget_queue_draw(widget);
    return FALSE;
}

/****************************************************************
 ** create small knob
 */

GtkWidget *gtk_knob_new_with_adjustment(GtkAdjustment *_adjustment)
{
    GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_EFNAME_KNOB, NULL ));
 
    GtkefnameKnobPrivate *priv = GTK_EFNAME_KNOB_GET_PRIVATE(widget);
    priv->model = 0;

    if (widget) {
        gtk_range_set_adjustment(GTK_RANGE(widget), _adjustment);
        g_signal_connect(G_OBJECT(widget), "value-changed",
                         G_CALLBACK(gtk_knob_value_changed), widget);
    }
    return widget;
}

GtkWidget *gtk_switch_new_with_adjustment(GtkAdjustment *_adjustment)
{
    GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_EFNAME_KNOB, NULL ));
 
    GtkefnameKnobPrivate *priv = GTK_EFNAME_KNOB_GET_PRIVATE(widget);
    priv->model = 1;

    if (widget) {
        gtk_range_set_adjustment(GTK_RANGE(widget), _adjustment);
        g_signal_connect(G_OBJECT(widget), "value-changed",
                         G_CALLBACK(gtk_knob_value_changed), widget);
    }
    return widget;
}

GtkWidget *gtk_trimmpot_new_with_adjustment(GtkAdjustment *_adjustment)
{
    GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_EFNAME_KNOB, NULL ));
 
    GtkefnameKnobPrivate *priv = GTK_EFNAME_KNOB_GET_PRIVATE(widget);
    priv->model = 2;
    priv->knob_x = 32;
    priv->knob_y = 32;

    if (widget) {
        gtk_range_set_adjustment(GTK_RANGE(widget), _adjustment);
        g_signal_connect(G_OBJECT(widget), "value-changed",
                         G_CALLBACK(gtk_knob_value_changed), widget);
    }
    return widget;
}

GtkWidget *gtk_power_switch_new_with_adjustment(GtkAdjustment *_adjustment)
{
    GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_EFNAME_KNOB, NULL ));
 
    GtkefnameKnobPrivate *priv = GTK_EFNAME_KNOB_GET_PRIVATE(widget);
    priv->model = 3;
    //priv->knob_x = 16;
    //priv->knob_y = 31;

    if (widget) {
        gtk_range_set_adjustment(GTK_RANGE(widget), _adjustment);
        g_signal_connect(G_OBJECT(widget), "value-changed",
                         G_CALLBACK(gtk_knob_value_changed), widget);
    }
    return widget;
}

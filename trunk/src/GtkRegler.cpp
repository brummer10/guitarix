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

// ***** GtkRegler.cpp *****
/******************************************************************************
part of guitarix, use  reglers with Gtk
******************************************************************************/

#include <cmath>
#include <iostream>

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdk/gdkkeysyms.h>

#include "GtkRegler.h"

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
    GdkPixbuf *bigregler_image;
    GdkPixbuf *toggle_image;
    GdkPixbuf *toggle_image1;
    GdkPixbuf *switch_image;
    GdkPixbuf *switch_image1;
    GdkPixbuf *slider_image;
    GdkPixbuf *slider_image1;
    GdkPixbuf *vslider_image;
    GdkPixbuf *vslider_image1;
    GdkPixbuf *minislider_image;
    GdkPixbuf *minislider_image1;
    GdkPixbuf *wheel_image;
    GdkPixbuf *wheel_image1;
    GdkPixbuf *pointer_image1;
    GdkPixbuf *b_toggle_image;
    GdkPixbuf *b_toggle_image1;

//----------- small knob
    int regler_x;
    int regler_y;
    int regler_step;
//----------- Big knob
    int bigknob_x;
    int bigknob_y;
    int bigknob_step;
//----------- switcher
    int toggle_x;
    int toggle_y ;
    int toggle_step;
//----------- switcherII
    int switch_x;
    int switch_y ;
    int switch_step;
//----------- minitoggle
    int minitoggle_x;
    int minitoggle_y ;
    int minitoggle_step;
//----------- horizontal slider
    int slider_x;
    int slider_y;
    int vslider_x;
    int slider_step;
    int vslider_step;
//----------- horizontal slider
    int minislider_x;
    int minislider_y;
    int minislider_step;
//----------- horizontal slider
    int wheel_x;
    int wheel_y;
    int wheel_step;
//-----------in or outline graphic
    int in_regler;
    int in_knob;
    int in_toggle;
    int in_switch;
    int in_slider;
    int in_minislider;
//----------- toggle button
    int b_toggle_x;
    int b_toggle_y ;
    int b_toggle_step;
//----------- event button
    int button_is;
    int pix_is;
    int pix_switch;

  };

GType gtk_regler_get_type ();

//----------- draw the Regler when moved
static gboolean gtk_regler_expose (GtkWidget *widget, GdkEventExpose *event)
{
  g_assert(GTK_IS_REGLER(widget));
  GtkRegler *regler = GTK_REGLER(widget);
  GdkWindow *window = widget->window;
  GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
  int reglerx = widget->allocation.x, reglery = widget->allocation.y;

//----------- small knob
  if (regler->regler_type == 0)
    {
      reglerx += (widget->allocation.width - GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_x) *0.5;
      reglery += (widget->allocation.height - GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) * GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_step / (adj->upper - adj->lower));

      if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE)
        {
          gtk_paint_focus(widget->style, window, GTK_STATE_NORMAL, NULL, widget, NULL,
                          reglerx, reglery, GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_x, GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_y);

          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_image, 0,0,
                          reglerx, reglery, GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_y, GDK_RGB_DITHER_NORMAL, 0, 0);

          /** this is to create a pointer rotating on the knob with painting funktions **/
          GdkGC * line = gdk_gc_new(GDK_DRAWABLE(widget->window));
          GdkColor color ;

          double radius = MIN (GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_x-5.,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_y-5.) * 0.5;
          double lengh_x = (reglerx+2.5)+radius*(1+cos(((reglerstate*3.6)+115.)*0.017453278));// 3.14159/180.)) ;
          double lengh_y = (reglery+2.5)+radius*(1+sin(((reglerstate*3.6)+115.)*0.017453278));//3.14159/180.)) ;

          double radius1 = MIN (GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_x,
                                GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_y) * 0.5;

          cairo_t *     cr =       gdk_cairo_create(GDK_DRAWABLE(widget->window));
          cairo_set_source_rgb (cr,  0.1, 0.1, 0.1);
          cairo_set_line_width (cr, 5.0);
          cairo_move_to (cr, reglerx+radius1, reglery+radius1);
          cairo_line_to (cr,lengh_x,lengh_y);
          cairo_stroke (cr);
          cairo_set_source_rgb (cr,  0.9, 0.9, 0.9);
          cairo_set_line_width (cr, 1.0);
          cairo_move_to (cr, reglerx+radius1, reglery+radius1);
          cairo_line_to (cr,lengh_x,lengh_y);
          cairo_stroke (cr);
          cairo_destroy(cr);

          color.red = (205-reglerstate*2) * 256;
          color.blue = 20 * 256;
          color.green = reglerstate*742;
          gdk_gc_set_rgb_fg_color(line, &color);
          gdk_gc_set_line_attributes (line, 1,GDK_LINE_SOLID,GDK_CAP_BUTT,GDK_JOIN_ROUND);
          gdk_draw_arc(GDK_DRAWABLE(widget->window), line, FALSE,reglerx, reglery,
                       GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_x-1 ,
                       GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_y-1,-90*64,360*64);
          g_object_unref(line );
          /** pointer ready  **/
        }
      else
        {
          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_image, 0,0, reglerx, reglery,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_y, GDK_RGB_DITHER_NORMAL, 0, 0);

          /** this is to create a pointer rotating on the knob with painting funktions **/
          GdkGC * line = gdk_gc_new(GDK_DRAWABLE(widget->window));
          GdkColor color ;

          double radius = MIN (GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_x-5.,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_y-5.) * 0.5;
          double lengh_x = (reglerx+2.5)+radius*(1+cos(((reglerstate*3.6)+115.)*0.017453278));//3.14159/180.)) ;
          double lengh_y = (reglery+2.5)+radius*(1+sin(((reglerstate*3.6)+115.)*0.017453278));//3.14159/180.)) ;

          double radius1 = MIN (GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_x,
                                GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_y) * 0.5;

          cairo_t *     cr =       gdk_cairo_create(GDK_DRAWABLE(widget->window));
          cairo_set_source_rgb (cr,  0.1, 0.1, 0.1);
          cairo_set_line_width (cr, 5.0);
          cairo_move_to (cr, reglerx+radius1, reglery+radius1);
          cairo_line_to (cr,lengh_x,lengh_y);
          cairo_stroke (cr);
          cairo_set_source_rgb (cr,  0.9, 0.9, 0.9);
          cairo_set_line_width (cr, 1.0);
          cairo_move_to (cr, reglerx+radius1, reglery+radius1);
          cairo_line_to (cr,lengh_x,lengh_y);
          cairo_stroke (cr);
          cairo_destroy(cr);

          color.red = 20 * 256;
          color.blue = 205 * 256;
          color.green = 742;
          gdk_gc_set_rgb_fg_color(line, &color);
          gdk_gc_set_line_attributes (line, 1,GDK_LINE_SOLID,GDK_CAP_BUTT,GDK_JOIN_ROUND);
          gdk_draw_arc(GDK_DRAWABLE(widget->window), line, FALSE,reglerx, reglery,
                       GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_x-1 ,
                       GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_y-1,-90*64,360*64);
          g_object_unref(line );
          /** pointer ready  **/
        }
    }
//--------- Big knob
  else if (regler->regler_type == 1)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_step / (adj->upper - adj->lower));

      if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE)
        {
          gtk_paint_focus(widget->style, window, GTK_STATE_NORMAL, NULL, widget, NULL,
                          reglerx, reglery, GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_y);

          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigregler_image, 0,0, reglerx, reglery,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_y, GDK_RGB_DITHER_NORMAL, 0, 0);

          /** this is to create a pointer rotating on the knob with painting funktions **/
          GdkGC * line = gdk_gc_new(GDK_DRAWABLE(widget->window));
          GdkColor color ;

          double radius = MIN (GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_x-5.,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_y-5.) * 0.5;
          double lengh_x = (reglerx+2.5)+radius*(1+cos(((reglerstate*3.6)+115.)*0.017453278));//3.14159/180.)) ;
          double lengh_y = (reglery+2.5)+radius*(1+sin(((reglerstate*3.6)+115.)*0.017453278));//3.14159/180.)) ;

          double radius1 = MIN (GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_x,
                                GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_y) * 0.5;

          cairo_t *     cr =       gdk_cairo_create(GDK_DRAWABLE(widget->window));
          cairo_set_source_rgb (cr,  0.1, 0.1, 0.1);
          cairo_set_line_width (cr, 5.0);
          cairo_move_to (cr, reglerx+radius1, reglery+radius1);
          cairo_line_to (cr,lengh_x,lengh_y);
          cairo_stroke (cr);
          cairo_set_source_rgb (cr,  0.9, 0.9, 0.9);
          cairo_set_line_width (cr, 1.0);
          cairo_move_to (cr, reglerx+radius1, reglery+radius1);
          cairo_line_to (cr,lengh_x,lengh_y);
          cairo_stroke (cr);
          cairo_destroy(cr);

          color.red = (205-reglerstate*2) * 256;
          color.blue = 20 * 256;
          color.green = reglerstate*742;
          gdk_gc_set_rgb_fg_color(line, &color);
          gdk_gc_set_line_attributes (line, 1,GDK_LINE_SOLID,GDK_CAP_BUTT,GDK_JOIN_ROUND);
          gdk_draw_arc(GDK_DRAWABLE(widget->window), line, FALSE,reglerx+2, reglery+2,
                       GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_x-5 ,
                       GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_y-5,-90*64,360*64);
          g_object_unref(line );
          /** pointer ready  **/

        }
      else
        {
          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigregler_image, 0,0, reglerx, reglery,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_y, GDK_RGB_DITHER_NORMAL, 0, 0);

          /** this is to create a pointer rotating on the knob with painting funktions **/
          GdkGC * line = gdk_gc_new(GDK_DRAWABLE(widget->window));
          GdkColor color ;

          double radius = MIN (GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_x-5.,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_y-5.) * 0.5;
          double lengh_x = (reglerx+2.5)+radius*(1+cos(((reglerstate*3.6)+115.)*0.017453278));//3.14159/180.)) ;
          double lengh_y = (reglery+2.5)+radius*(1+sin(((reglerstate*3.6)+115.)*0.017453278));//3.14159/180.)) ;

          double radius1 = MIN (GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_x,
                                GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_y) * 0.5;

          cairo_t *     cr =       gdk_cairo_create(GDK_DRAWABLE(widget->window));
          cairo_set_source_rgb (cr,  0.1, 0.1, 0.1);
          cairo_set_line_width (cr, 5.0);
          cairo_move_to (cr, reglerx+radius1, reglery+radius1);
          cairo_line_to (cr,lengh_x,lengh_y);
          cairo_stroke (cr);
          cairo_set_source_rgb (cr,  0.9, 0.9, 0.9);
          cairo_set_line_width (cr, 1.0);
          cairo_move_to (cr, reglerx+radius1, reglery+radius1);
          cairo_line_to (cr,lengh_x,lengh_y);
          cairo_stroke (cr);
          cairo_destroy(cr);

          color.red = 20 * 256;
          color.blue = 205 * 256;
          color.green = 742;
          gdk_gc_set_rgb_fg_color(line, &color);
          gdk_gc_set_line_attributes (line, 1,GDK_LINE_SOLID,GDK_CAP_BUTT,GDK_JOIN_ROUND);
          gdk_draw_arc(GDK_DRAWABLE(widget->window), line, FALSE,reglerx+2, reglery+2,
                       GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_x-5 ,
                       GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_y-5,-90*64,360*64);
          g_object_unref(line );
          /** pointer ready  **/
        }
    }

//---------- switch
  else if (regler->regler_type == 2)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_step / (adj->upper - adj->lower));
      if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE)
        {
          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_image1, reglerstate *
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_x, 0, reglerx, reglery,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
        }
      else
        {
          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_image, reglerstate *
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_x, 0, reglerx, reglery,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
        }
    }

//---------- switchII
  else if (regler->regler_type == 5)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_step / (adj->upper - adj->lower));
      if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE)
        {
          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_image1, reglerstate *
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_x, 0, reglerx, reglery,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_y, GDK_RGB_DITHER_NORMAL, 0, 0);
        }
      else
        {
          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_image, reglerstate *
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_x, 0, reglerx, reglery,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_y, GDK_RGB_DITHER_NORMAL, 0, 0);
        }
    }

//---------- minitoggle
  else if (regler->regler_type == 6)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_step / (adj->upper - adj->lower));
      if (reglerstate > 0) reglerstate =2;
      if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE)
        {
          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_image1, reglerstate *
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_x, 0, reglerx, reglery,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
        }
      else
        {
          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_image, reglerstate *
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_x, 0, reglerx, reglery,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
        }
    }

//--------- horizontal slider
  else if (regler->regler_type == 3)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y) *0.5;

      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_step / (adj->upper - adj->lower));

      if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE)
        {
          gtk_paint_focus(widget->style, window, GTK_STATE_NORMAL, NULL, widget, NULL,
                          reglerx, reglery, GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y);

          gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image,0,0,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1,0,0);

          gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x,0,20,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1, reglerstate,0);

          gdk_pixbuf_saturate_and_pixelate(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1,
                                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1,70.0,FALSE);

          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1, 0, 0, reglerx, reglery,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y, GDK_RGB_DITHER_NORMAL, 0, 0);
        }
      else
        {

          gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image,0,0,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1,0,0);

          gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x,0,20,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1, reglerstate,0);

          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1, 0, 0, reglerx, reglery,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y, GDK_RGB_DITHER_NORMAL, 0, 0);
        }
    }

  //--------- vertical slider
  else if (regler->regler_type == 9)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_x) *0.5;

      int reglerstate = (int)((adj->upper - adj->value ) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_step / (adj->upper - adj->lower));

      if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE)
        {
          gtk_paint_focus(widget->style, window, GTK_STATE_NORMAL, NULL, widget, NULL,
                          reglerx, reglery, GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_x);

          gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image,0,20,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_x,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image1,0,0);

          gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image,0,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x,10,20,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image1,0, reglerstate);

          gdk_pixbuf_saturate_and_pixelate(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image1,
                                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image1,70.0,FALSE);

          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image1, 0, 0, reglerx, reglery,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_x, GDK_RGB_DITHER_NORMAL, 0, 0);
        }
      else
        {

          gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image,0,20,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_x,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image1,0,0);

          gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image,0,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x,10,20,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image1, 0,reglerstate);

          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image1, 0, 0, reglerx, reglery,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_x, GDK_RGB_DITHER_NORMAL, 0, 0);
        }
    }

//--------- mini slider
  else if (regler->regler_type == 4)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_y) *0.5;

      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_step / (adj->upper - adj->lower));

      if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE)
        {
          gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image,0,0,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_x,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_y,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image1,0,0);

          gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_x,0,6,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_y,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image1, reglerstate,0);

          gdk_pixbuf_saturate_and_pixelate(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image1,
                                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image1,99.0,FALSE);

          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image1, 0, 0, reglerx, reglery,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_y, GDK_RGB_DITHER_NORMAL, 0, 0);
        }
      else
        {

          gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image,0,0,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_x,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_y,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image1,0,0);

          gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_x,0,6,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_y,
                               GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image1, reglerstate,0);

          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image1, 0, 0, reglerx, reglery,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_y, GDK_RGB_DITHER_NORMAL, 0, 0);
        }
    }
//----------- wheel
  else if (regler->regler_type == 7)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_step / (adj->upper - adj->lower));
      int smoth_pointer = 0;
      if (reglerstate>(adj->upper - adj->lower))smoth_pointer=-4;
      if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE)
        {
          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_image1, 0, 0, reglerx, reglery,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);
          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_image,
                          reglerstate + GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_x, 0,
                          reglerx, reglery, GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);
          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->pointer_image1,0, 0,
                          reglerx+smoth_pointer+reglerstate*0.4, reglery, 2,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);

        }
      else
        {
          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_image1, 0, 0, reglerx, reglery,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);
          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_image,
                          reglerstate + GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_x, 0,
                          reglerx, reglery, GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);
          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->pointer_image1,0, 0,
                          reglerx+smoth_pointer+reglerstate*0.4, reglery, 2,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);

        }
    }
  //---------- toggle button
  else if (regler->regler_type == 8)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_step / (adj->upper - adj->lower));
      if (GTK_WIDGET_HAS_FOCUS(widget)== TRUE)
        {
          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_image1, 0,
                          reglerstate * GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_y, reglerx, reglery,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
        }
      else
        {
          gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_image, 0,
                          reglerstate * GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_y,
                          reglerx, reglery, GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_x,
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
        }
    }

  return TRUE;
}
//-------------- redraw when leave
static gboolean gtk_regler_leave_out (GtkWidget *widget, GdkEventCrossing *event)
{
  g_assert(GTK_IS_REGLER(widget));
  GtkRegler *regler = GTK_REGLER(widget);

  GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
  int reglerx = widget->allocation.x, reglery = widget->allocation.y;

//----------- small knob
  if (regler->regler_type == 0)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_y) *0.5;

      GdkGC * line = gdk_gc_new(GDK_DRAWABLE(widget->window));
      GdkColor color ;

      color.red = 20 * 256;
      color.blue = 205 * 256;
      color.green = 742;
      gdk_gc_set_rgb_fg_color(line, &color);
      gdk_gc_set_line_attributes (line, 1,GDK_LINE_SOLID,GDK_CAP_BUTT,GDK_JOIN_ROUND);
      gdk_draw_arc(GDK_DRAWABLE(widget->window), line, FALSE,reglerx, reglery,
                   GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_x-1 ,
                   GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_y-1,-90*64,360*64);
      g_object_unref(line );
    }

//----------- Big knob
  else if (regler->regler_type == 1)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_y) *0.5;

      GdkGC * line = gdk_gc_new(GDK_DRAWABLE(widget->window));
      GdkColor color ;

      color.red = 20 * 256;
      color.blue = 205 * 256;
      color.green = 742;
      gdk_gc_set_rgb_fg_color(line, &color);
      gdk_gc_set_line_attributes (line, 1,GDK_LINE_SOLID,GDK_CAP_BUTT,GDK_JOIN_ROUND);
      gdk_draw_arc(GDK_DRAWABLE(widget->window), line, FALSE,reglerx+2, reglery+2,
                   GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_x-5 ,
                   GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_y-5,-90*64,360*64);
      g_object_unref(line );
    }

//----------- switch
  else if (regler->regler_type == 2)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_step / (adj->upper - adj->lower));

      gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_image,
                      reglerstate * GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_x, 0,
                      reglerx, reglery, GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_x,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }

//----------- switchII
  else if (regler->regler_type == 5)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_step / (adj->upper - adj->lower));

      gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_image,
                      reglerstate * GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_x, 0,
                      reglerx, reglery, GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_x,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }

//----------- minitoggle
  else if (regler->regler_type == 6)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_step / (adj->upper - adj->lower));
      if (reglerstate > 0) reglerstate =2;
      gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_image,
                      reglerstate * GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_x, 0,
                      reglerx, reglery, GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_x,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }

//----------- horizontal slider
  else if (regler->regler_type == 3)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_step / (adj->upper - adj->lower));

      gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image,0,0,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1,0,0);

      gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x,0,20,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1, reglerstate,0);

      gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1, 0, 0, reglerx, reglery,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }

  //----------- vertical slider
  else if (regler->regler_type == 9)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_x) *0.5;
      int reglerstate = (int)((adj->upper -adj->value ) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_step / (adj->upper - adj->lower));

      gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image,0,20,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_x,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image1,0,0);

      gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image,0,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x,10,20,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image1, 0,reglerstate);

      gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image1, 0, 0, reglerx, reglery,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_x, GDK_RGB_DITHER_NORMAL, 0, 0);
    }
//----------- mini slider
  else if (regler->regler_type == 4)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_step / (adj->upper - adj->lower));

      gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image,0,0,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_x,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_y,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image1,0,0);

      gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_x,0,6,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_y,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image1, reglerstate,0);

      gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image1, 0, 0, reglerx, reglery,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_x,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }
//----------- wheel
  else if (regler->regler_type == 7)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_step / (adj->upper - adj->lower));
      int smoth_pointer = 0;
      if (reglerstate>(adj->upper - adj->lower))smoth_pointer=-4;
      gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_image1, 0, 0, reglerx, reglery,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_x,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);
      gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_image,
                      reglerstate + GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_x, 0, reglerx, reglery,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_x,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);
      gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->pointer_image1,0, 0,
                      reglerx+smoth_pointer+reglerstate*0.4, reglery, 2,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);

    }
  //---------- toggle button
  else if (regler->regler_type == 8)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_step / (adj->upper - adj->lower));

      gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_image, 0,
                      reglerstate * GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_y,
                      reglerx, reglery, GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_x,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);

    }

  return TRUE;
}

//----------- redraw when enter
static gboolean gtk_regler_enter_in (GtkWidget *widget, GdkEventCrossing *event)
{
  g_assert(GTK_IS_REGLER(widget));
  GtkRegler *regler = GTK_REGLER(widget);

  GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
  int reglerx = widget->allocation.x, reglery = widget->allocation.y;

//----------- small knob
  if (regler->regler_type == 0)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_step / (adj->upper - adj->lower));

      GdkGC * line = gdk_gc_new(GDK_DRAWABLE(widget->window));
      GdkColor color ;

      color.red = (205-reglerstate*2) * 256;
      color.blue = 20 * 256;
      color.green = reglerstate*742;
      gdk_gc_set_rgb_fg_color(line, &color);
      gdk_gc_set_line_attributes (line, 1,GDK_LINE_SOLID,GDK_CAP_BUTT,GDK_JOIN_ROUND);
      gdk_draw_arc(GDK_DRAWABLE(widget->window), line, FALSE,reglerx, reglery,
                   GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_x-1 ,
                   GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_y-1,
                   (-reglerstate-90)*64,(-reglerstate-360)*64);
      g_object_unref(line );

    }

//----------- Big knob
  else if (regler->regler_type == 1)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_step / (adj->upper - adj->lower));

      GdkGC * line = gdk_gc_new(GDK_DRAWABLE(widget->window));
      GdkColor color ;

      color.red = (205-reglerstate*2) * 256;
      color.blue = 20 * 256;
      color.green = reglerstate*742;
      gdk_gc_set_rgb_fg_color(line, &color);
      gdk_gc_set_line_attributes (line, 1,GDK_LINE_SOLID,GDK_CAP_BUTT,GDK_JOIN_ROUND);
      gdk_draw_arc(GDK_DRAWABLE(widget->window), line, FALSE,reglerx+2, reglery+2,
                   GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_x-5 ,
                   GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_y-5,
                   (-reglerstate-90)*64,(-reglerstate-360)*64);
      g_object_unref(line );

    }

//----------- switch
  else if (regler->regler_type == 2)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_step / (adj->upper - adj->lower));

      gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_image1,
                      reglerstate * GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_x, 0,
                      reglerx, reglery, GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_x,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }

//----------- switch
  else if (regler->regler_type == 5)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_step / (adj->upper - adj->lower));

      gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_image1,
                      reglerstate * GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_x, 0,
                      reglerx, reglery, GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_x,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }

//----------- minitoggle
  else if (regler->regler_type == 6)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_step / (adj->upper - adj->lower));
      if (reglerstate > 0) reglerstate =2;
      gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_image1, reglerstate *
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_x, 0, reglerx, reglery,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_x,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }

//----------- horizontal slider
  else if (regler->regler_type == 3)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_step / (adj->upper - adj->lower));

      gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image,0,0,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1,0,0);

      gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x,0,20,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1, reglerstate,0);

      gdk_pixbuf_saturate_and_pixelate(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1,
                                       GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1,70.0,FALSE);

      gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1, 0, 0,
                      reglerx, reglery, GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }

  //----------- vertical slider
  else if (regler->regler_type == 9)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_x) *0.5;
      int reglerstate = (int)((adj->upper -adj->value ) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_step / (adj->upper - adj->lower));

      gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image,0,20,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_x,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image1,0,0);

      gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image,0,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x,10,20,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image1, 0,reglerstate);

      gdk_pixbuf_saturate_and_pixelate(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image1,
                                       GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image1,70.0,FALSE);

      gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image1, 0, 0,
                      reglerx, reglery, GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_x, GDK_RGB_DITHER_NORMAL, 0, 0);
    }
//----------- mini slider
  else if (regler->regler_type == 4)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_step / (adj->upper - adj->lower));

      gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image,0,0,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_x,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_y,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image1,0,0);

      gdk_pixbuf_copy_area(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_x,0,6,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_y,
                           GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image1, reglerstate,0);

      gdk_pixbuf_saturate_and_pixelate(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image1,
                                       GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image1,99.0,FALSE);

      gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image1, 0, 0,
                      reglerx, reglery, GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_x,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_y, GDK_RGB_DITHER_NORMAL, 0, 0);
    }
//----------- wheel
  else if (regler->regler_type == 7)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_step / (adj->upper - adj->lower));
      int smoth_pointer = 0;
      if (reglerstate>(adj->upper - adj->lower))smoth_pointer=-4;
      gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_image1, 0, 0, reglerx, reglery,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_x,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);
      gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_image,
                      reglerstate + GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_x, 0,
                      reglerx, reglery, GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_x,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);
      gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->pointer_image1,0, 0,
                      reglerx+smoth_pointer+reglerstate*0.4, reglery, 2,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_y, GDK_RGB_DITHER_NORMAL, 0, 0);

    }
  //---------- toggle button
  else if (regler->regler_type == 8)
    {
      reglerx += (widget->allocation.width -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_x) *0.5;
      reglery += (widget->allocation.height -
                  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_y) *0.5;
      int reglerstate = (int)((adj->value - adj->lower) *
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_step / (adj->upper - adj->lower));

      gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0],
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_image1, 0,
                      reglerstate * GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_y,
                      reglerx, reglery, GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_x,
                      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_y, GDK_RGB_DITHER_NORMAL, 0, 0);

    }

  return TRUE;
}

//----------- set size for GdkDrawable per type
static void gtk_regler_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
  g_assert(GTK_IS_REGLER(widget));
  GtkRegler *regler = GTK_REGLER(widget);
//----------- small knob
  if (regler->regler_type == 0)
    {
      requisition->width = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_x;
      requisition->height = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_y;
    }
//----------- Big knob
  else if (regler->regler_type == 1)
    {
      requisition->width = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_x;
      requisition->height = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_y;
    }
//----------- switch
  else if (regler->regler_type == 2)
    {
      requisition->width = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_x;
      requisition->height = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_y;
    }
//----------- horizontal slider
  else if (regler->regler_type == 3)
    {
      requisition->width = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x;
      requisition->height = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y;
    }
//----------- mini slider
  else if (regler->regler_type == 4)
    {
      requisition->width = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_x;
      requisition->height = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_y;
    }
//----------- switch//
  else if (regler->regler_type == 5)
    {
      requisition->width = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_x;
      requisition->height = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_y;
    }
  //----------- minitoggle
  else if (regler->regler_type == 6)
    {
      requisition->width = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_x;
      requisition->height = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_y;
    }
//----------- horizontal slider
  else if (regler->regler_type == 7)
    {
      requisition->width = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_x;
      requisition->height = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_y;
    }
  //----------- switch
  else if (regler->regler_type == 8)
    {
      requisition->width = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_x;
      requisition->height = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_y;
    }
  //----------- vertical slider
  else if (regler->regler_type == 9)
    {
      requisition->width = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y;
      requisition->height = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_x;
    }

}

//----------- set value
static void gtk_regler_set_value (GtkWidget *widget, int dir_down)
{
  g_assert(GTK_IS_REGLER(widget));

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

//----------- keyboard bindings
static gboolean gtk_regler_key_press (GtkWidget *widget, GdkEventKey *event)
{
  g_assert(GTK_IS_REGLER(widget));

  GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
  switch (event->keyval)
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

int precision(double n)
{
  if (n < 0.009999) return 3;
  else if (n < 0.099999) return 2;
  else if (n < 0.999999) return 1;
  else return 0;
}

//----------- mouse button pressed set value
static gboolean gtk_regler_button_press (GtkWidget *widget, GdkEventButton *event)
{
  g_assert(GTK_IS_REGLER(widget));
  GtkRegler *regler = GTK_REGLER(widget);
  GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
  GtkWidget * dialog,* spinner, *ok_button, *vbox;


  switch (event->button)
    {
    case 1:  // left button

      gtk_widget_grab_focus(widget);
      gtk_widget_grab_default (widget);
      gtk_grab_add(widget);
      //----------- knobs

      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->button_is = 1;
      if (regler->regler_type == 0)   //| (regler->regler_type < 2))
        {
          double radius1 = MIN (GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_x,
                                GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_y) * 0.5;
          int  reglerx = (widget->allocation.width -
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_x) *0.5;
          int  reglery = (widget->allocation.height -
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_y) *0.5;
          double posx = (( reglerx+radius1 - event->x )) ;
          double posy = ((reglery+radius1 - event->y ));
          double angle = acos(posy/sqrt(posx*posx+posy*posy))* 57.295828; //180.0 / 3.14159;
          if (posx<0) angle =  170+angle;
          else angle = 170-angle;
          if ((angle > 0) && (angle < 340))
            {
              int pause;
              if (angle < 335 ) pause = -10;
              else pause = 10;
              gtk_range_set_value(GTK_RANGE(widget),adj->lower +
                                  ((angle+pause)*0.003030303) *(adj->upper - adj->lower) );
            }
        }
      else if (regler->regler_type == 1)
        {
          double radius1 = MIN (GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_x,
                                GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_y) * 0.5;
          int  reglerx = (widget->allocation.width -
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_x) * 0.5;
          int  reglery = (widget->allocation.height -
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_y) * 0.5;
          double posx = (( reglerx+radius1 - event->x ));
          double posy = ((reglery+radius1 - event->y ));
          double angle = acos(posy/sqrt(posx*posx+posy*posy))*57.295828; // 180.0 / 3.14159;
          if (posx<0) angle =  170+angle;
          else angle = 170-angle;
          if ((angle > 0) && (angle < 340))
            {
              int pause;
              if (angle < 335 ) pause = -10;
              else pause = 10;
              gtk_range_set_value(GTK_RANGE(widget),adj->lower +
                                  ((angle+pause)*0.003030303) *(adj->upper - adj->lower) );
            }
        }

//----------- slider
      else if (regler->regler_type == 3)
        {

          int  reglerx = (widget->allocation.width -
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x) *0.5;
          double pos = adj->lower + (((event->x - reglerx-10)*0.01)* (adj->upper - adj->lower));
          if (adj->step_increment < 0.009999) pos = (floor (pos*1000))*0.001;
          else if (adj->step_increment < 0.099999) pos = (floor (pos*100))*0.01;
          else if (adj->step_increment < 0.999999) pos = (floor (pos*10))*0.1;
          else pos = floor (pos);
          gtk_range_set_value(GTK_RANGE(widget),  pos);
        }
      //----------- slider
      else if (regler->regler_type == 9)
        {

          int  reglery = (widget->allocation.height -
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_x) *0.5;
          double pos = adj->upper - (((event->y - reglery-10)*0.02)* (adj->upper - adj->lower));
          if (adj->step_increment < 0.009999) pos = (floor (pos*1000))*0.001;
          else if (adj->step_increment < 0.099999) pos = (floor (pos*100))*0.01;
          else if (adj->step_increment < 0.999999) pos = (floor (pos*10))*0.1;
          else pos = floor (pos);
          gtk_range_set_value(GTK_RANGE(widget),  pos);
        }
//----------- minislider
      else if (regler->regler_type == 4)
        {

          int  reglerx = (widget->allocation.width -
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_x) *0.5;
          double pos = adj->lower + (((event->x - reglerx-3)*0.03575)* (adj->upper - adj->lower));
          if (adj->step_increment < 0.009999) pos = (floor (pos*1000))*0.001;
          else if (adj->step_increment < 0.099999) pos = (floor (pos*100))*0.01;
          else if (adj->step_increment < 0.999999) pos = (floor (pos*10))*0.1;
          else pos = floor (pos);
          gtk_range_set_value(GTK_RANGE(widget),  pos);
        }
//----------- wheel
      else if (regler->regler_type == 7)
        {

          int  wheelx = (widget->allocation.width -
                         GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_x) *0.5;
          double pos = adj->lower + (((event->x - wheelx)*0.03)* (adj->upper - adj->lower));
          if (adj->step_increment < 0.009999) pos = (floor (pos*1000))*0.001;
          else if (adj->step_increment < 0.099999) pos = (floor (pos*100))*0.01;
          else if (adj->step_increment < 0.999999) pos = (floor (pos*10))*0.1;
          else pos = floor (pos);
          gtk_range_set_value(GTK_RANGE(widget),  pos);
        }

      //----------- switch
      else // if ((regler->regler_type == 2) || (regler->regler_type == 5) || (regler->regler_type == 6)|| (regler->regler_type == 8))
        {
          regler->start_value = gtk_range_get_value(GTK_RANGE(widget));
          if ( regler->start_value == 0) gtk_range_set_value(GTK_RANGE(widget), 1);
          else gtk_range_set_value(GTK_RANGE(widget), 0);
        }

      break;

    case 2: //wheel
      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->button_is = 2;
      break;

    case 3:  // right button show num entry
      GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->button_is = 3;
      dialog = gtk_window_new (GTK_WINDOW_TOPLEVEL);
      spinner = gtk_spin_button_new (GTK_ADJUSTMENT(adj), adj->step_increment,
                                     precision(adj->step_increment));
      ok_button  = gtk_button_new_from_stock(GTK_STOCK_OK);
      vbox = gtk_vbox_new (false, 4);
      gtk_container_add (GTK_CONTAINER(vbox), spinner);
      gtk_container_add (GTK_CONTAINER(vbox), ok_button);
      gtk_container_add (GTK_CONTAINER(dialog), vbox);
      gtk_window_set_decorated(GTK_WINDOW(dialog), false);
      gtk_window_set_title (GTK_WINDOW (dialog), "set");
      gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
      gtk_window_set_gravity(GTK_WINDOW(dialog), GDK_GRAVITY_SOUTH);
      gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);
      gtk_window_set_keep_below (GTK_WINDOW(dialog), FALSE);

      gtk_window_set_destroy_with_parent(GTK_WINDOW(dialog), TRUE);
      g_signal_connect_swapped (ok_button, "clicked",
                                G_CALLBACK (gtk_widget_destroy), dialog);

      gtk_widget_show_all(dialog);
      break;

    default: // do nothing
      break;
    }
  return TRUE;
}

//----------- mouse button release
static gboolean gtk_regler_button_release (GtkWidget *widget, GdkEventButton *event)
{
  g_assert(GTK_IS_REGLER(widget));
  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->button_is = 0;
  if (GTK_WIDGET_HAS_GRAB(widget))
    gtk_grab_remove(widget);
  return FALSE;
}

//----------- set the value from mouse movement
static gboolean gtk_regler_pointer_motion (GtkWidget *widget, GdkEventMotion *event)
{
  g_assert(GTK_IS_REGLER(widget));
  GtkRegler *regler = GTK_REGLER(widget);
  GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(widget));
  if (GTK_WIDGET_HAS_GRAB(widget))
    {
      usleep(50000);
      if (regler->regler_type == 0)
        {
          double radius1 = MIN (GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_x,
                                GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_y) * 0.5;
          int  reglerx = (widget->allocation.width -
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_x) *0.5;
          int  reglery = (widget->allocation.height -
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_y) *0.5;
          double posx = (( reglerx+radius1 - event->x )) ;
          double posy = ((reglery+radius1 - event->y ));
          double angle = acos(posy/sqrt(posx*posx+posy*posy))* 57.295828 ; //180.0 / 3.14159;
          if (posx<0) angle =  170+angle;
          else angle = 170-angle;
          if ((angle > 0) && (angle < 340))
            {
              int pause;
              if (angle < 335 ) pause = -10;
              else pause = 10;
              gtk_range_set_value(GTK_RANGE(widget),adj->lower +
                                  ((angle+pause)*0.003030303) *(adj->upper - adj->lower) );
            }
          else gtk_grab_remove(widget);
        }
      else if (regler->regler_type == 1)
        {
          double radius1 = MIN (GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_x,
                                GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_y) * 0.5;
          int  reglerx = (widget->allocation.width -
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_x) *0.5;
          int  reglery = (widget->allocation.height -
                          GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_y) *0.5;
          double posx = (( reglerx+radius1 - event->x ));
          double posy = ((reglery+radius1 - event->y ));
          double angle = acos(posy/sqrt(posx*posx+posy*posy))*57.295828 ; // 180.0 / 3.14159;
          if (posx<0) angle =  170+angle;
          else angle = 170-angle;
          if ((angle > 0) && (angle < 340))
            {
              int pause;
              if (angle < 335 ) pause = -10;
              else pause = 10;
              gtk_range_set_value(GTK_RANGE(widget),adj->lower +
                                  ((angle+pause)*0.003030303) *(adj->upper - adj->lower) );
            }
          else gtk_grab_remove(widget);
        }
//----------- slider
      else if (regler->regler_type == 3)
        {
          if (event->x > 0)
            {
              int  sliderx = (widget->allocation.width -
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x)*0.5;
              double pos = adj->lower + (((event->x - sliderx-10)*0.01)* (adj->upper - adj->lower));
              if (adj->step_increment < 0.009999) pos = (floor (pos*1000))*0.001;
              else if (adj->step_increment < 0.099999) pos = (floor (pos*100))*0.01;
              else if (adj->step_increment < 0.999999) pos = (floor (pos*10))*0.1;
              else pos = floor (pos);
              gtk_range_set_value(GTK_RANGE(widget),  pos);
            }
        }
      //----------- slider
      else if (regler->regler_type == 9)
        {
          if (event->y > 0)
            {
              int  slidery = (widget->allocation.height -
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_x)*0.5;
              double pos = adj->upper - (((event->y - slidery-10)*0.02)* (adj->upper - adj->lower));
              if (adj->step_increment < 0.009999) pos = (floor (pos*1000))*0.001;
              else if (adj->step_increment < 0.099999) pos = (floor (pos*100))*0.01;
              else if (adj->step_increment < 0.999999) pos = (floor (pos*10))*0.1;
              else pos = floor (pos);
              gtk_range_set_value(GTK_RANGE(widget),  pos);
            }
        }
//----------- minislider
      else if (regler->regler_type == 4)
        {
          if (event->x > 0)
            {
              int  sliderx = (widget->allocation.width -
                              GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_x)*0.5;
              double pos = adj->lower + (((event->x - sliderx-3)*0.03575)* (adj->upper - adj->lower));
              if (adj->step_increment < 0.009999) pos = (floor (pos*1000))*0.001;
              else if (adj->step_increment < 0.099999) pos = (floor (pos*100))*0.01;
              else if (adj->step_increment < 0.999999) pos = (floor (pos*10))*0.1;
              else pos = floor (pos);
              gtk_range_set_value(GTK_RANGE(widget),  pos);
            }
        }
//----------- wheel
      else if (regler->regler_type == 7)
        {
          if (event->x > 0)
            {
              int  wheelx = (widget->allocation.width -
                             GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_x)*0.5;
              double pos = adj->lower + (((event->x - wheelx)*0.03)* (adj->upper - adj->lower));
              if (adj->step_increment < 0.009999) pos = (floor (pos*1000))*0.001;
              else if (adj->step_increment < 0.099999) pos = (floor (pos*100))*0.01;
              else if (adj->step_increment < 0.999999) pos = (floor (pos*10))*0.1;
              else pos = floor (pos);
              gtk_range_set_value(GTK_RANGE(widget),  pos);
            }
        }
    }
  return FALSE;
}

//----------- set value from mouseweel
static gboolean gtk_regler_scroll (GtkWidget *widget, GdkEventScroll *event)
{
  usleep(5000);
  gtk_regler_set_value(widget, event->direction);
  return FALSE;
}

void GtkRegler::gtk_regler_init_pixmaps(int change_knob)
{
  GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_REGLER, NULL ));
  g_assert(GTK_IS_REGLER(widget));
  GtkReglerClass *klass =  GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget));

  //---------- here are the inline pixmaps for regler
#include "GtkReglerpix.cpp"
  klass->pix_switch = change_knob;
  if (klass->pix_switch != 1)
    {
      //----------- Big knob
      klass->bigregler_image = gdk_pixbuf_new_from_xpm_data (knob1_xpm);
      g_assert(klass->bigregler_image != NULL);

//----------- small knob
      klass->regler_image = gdk_pixbuf_scale_simple(klass->bigregler_image,25,25,GDK_INTERP_HYPER);
      g_assert(klass->regler_image != NULL);
      klass->pix_switch = 1;
    }
  else
    {
      //----------- Big knob
      klass->bigregler_image = gdk_pixbuf_new_from_xpm_data (knob2_xpm);
      g_assert(klass->bigregler_image != NULL);

//----------- small knob
      klass->regler_image = gdk_pixbuf_scale_simple(klass->bigregler_image,25,25,GDK_INTERP_HYPER);
      g_assert(klass->regler_image != NULL);
      klass->pix_switch = 0;
    }

  if (klass->pix_is != 1)
    {
//----------- switch
      klass->toggle_image = gdk_pixbuf_new_from_xpm_data (switchit_xpm);
      g_assert(klass->toggle_image != NULL);
      klass->toggle_image1 = gdk_pixbuf_copy( klass->toggle_image );
      g_assert(klass->toggle_image1 != NULL);
      gdk_pixbuf_saturate_and_pixelate(klass->toggle_image1,klass->toggle_image1,10.0,FALSE);

//----------- switchII
      klass->switch_image = gdk_pixbuf_new_from_xpm_data (switch_xpm);
      g_assert(klass->toggle_image != NULL);
      klass->switch_image1 = gdk_pixbuf_copy( klass->switch_image );
      g_assert(klass->switch_image1 != NULL);
      gdk_pixbuf_saturate_and_pixelate(klass->switch_image1,klass->switch_image1,10.0,FALSE);

//----------- horizontal slider
      klass->slider_image = gdk_pixbuf_new_from_xpm_data(slidersm_xpm);
      g_assert(klass->slider_image != NULL);
      klass->slider_image1 = gdk_pixbuf_copy( klass->slider_image );
      g_assert(klass->slider_image1 != NULL);

//----------- vertical slider
      klass->vslider_image = gdk_pixbuf_rotate_simple(klass->slider_image,
                             GDK_PIXBUF_ROTATE_CLOCKWISE);
      g_assert(klass->vslider_image != NULL);
      klass->vslider_image = gdk_pixbuf_flip(klass->vslider_image, TRUE);
      klass->vslider_image1 = gdk_pixbuf_copy( klass->vslider_image );
      g_assert(klass->vslider_image1 != NULL);

//----------- mini slider
      klass->minislider_image = gdk_pixbuf_scale_simple(klass->slider_image,40,6,GDK_INTERP_HYPER);
      g_assert(klass->minislider_image != NULL);
      klass->minislider_image1 = gdk_pixbuf_copy( klass->minislider_image );
      g_assert(klass->minislider_image1 != NULL);
//----------- horizontal wheel
      klass->wheel_image = gdk_pixbuf_new_from_xpm_data(wheel_xpm);
      g_assert(klass->wheel_image != NULL);
      klass->wheel_image1 = gdk_pixbuf_new_from_xpm_data(wheel_s_xpm);
      g_assert(klass->wheel_image1 != NULL);
      klass->pointer_image1 = gdk_pixbuf_new_from_xpm_data(pointer_xpm);
      g_assert(klass->pointer_image1 != NULL);
//----------- toggle_button
      klass->b_toggle_image = gdk_pixbuf_new_from_xpm_data (button_xpm);
      g_assert(klass->b_toggle_image != NULL);
      klass->b_toggle_image1 = gdk_pixbuf_new_from_xpm_data (button1_xpm);
      //klass->b_toggle_image1 = gdk_pixbuf_copy( klass->b_toggle_image );
      g_assert(klass->b_toggle_image1 != NULL);
      // gdk_pixbuf_saturate_and_pixelate(klass->b_toggle_image1,klass->b_toggle_image1,3.0,FALSE);
      klass->pix_is = 1;
    }
}

//----------- init the GtkReglerClass
static void gtk_regler_class_init (GtkReglerClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);



  /** set here the sizes and steps for the used regler **/
//--------- small knob size and steps
  klass->regler_x = 25;
  klass->regler_y = 25;
  klass->regler_step = 86;

//--------- big knob size and steps
  klass->bigknob_x = 51;
  klass->bigknob_y = 51;
  klass->bigknob_step = 86;

//--------- switch size and steps
  klass->toggle_x = 37 ;
  klass->toggle_y = 28 ;
  klass->toggle_step = 1;

//--------- switchII size and steps
  klass->switch_x = 20 ;
  klass->switch_y = 10 ;
  klass->switch_step = 1;

//--------- switch minitoggle and steps
  klass->minitoggle_x = 10 ;
  klass->minitoggle_y = 10 ;
  klass->minitoggle_step = 1;

//--------- horizontal slider size and steps
  klass->slider_x = 120 ;  //this is the scale size
  klass->vslider_x = 70 ;  //this is the scale size
  klass->slider_y = 10 ;   // this is the knob size x and y be the same
  klass->slider_step = 100;
  klass->vslider_step = 50;

//--------- mini slider size and steps
  klass->minislider_x = 34 ;  //this is the scale size
  klass->minislider_y = 6 ;   // this is the knob size x and y be the same
  klass->minislider_step = 28;

//--------- horizontal wheel size and steps
  klass->wheel_x = 40 ;  //this is the scale size
  klass->wheel_y = 8 ;   // this is the knob size x and y be the same
  klass->wheel_step = 100;

//--------- switch size and steps
  klass->b_toggle_x = 25 ;
  klass->b_toggle_y = 15 ;
  klass->b_toggle_step = 1;

//--------- event button
  klass->button_is = 0;


//--------- connect the events with funktions
  widget_class->enter_notify_event = gtk_regler_enter_in;
  widget_class->leave_notify_event = gtk_regler_leave_out;
  widget_class->expose_event = gtk_regler_expose;
  widget_class->size_request = gtk_regler_size_request;
  widget_class->button_press_event = gtk_regler_button_press;
  widget_class->button_release_event = gtk_regler_button_release;
  widget_class->motion_notify_event = gtk_regler_pointer_motion;
  widget_class->key_press_event = gtk_regler_key_press;
  widget_class->scroll_event = gtk_regler_scroll;

  GtkRegler::gtk_regler_init_pixmaps(0);

}

//----------- init the Regler type
static void gtk_regler_init (GtkRegler *regler)
{
  GtkWidget *widget = GTK_WIDGET(regler);
  GTK_WIDGET_SET_FLAGS (GTK_WIDGET(regler), GTK_CAN_FOCUS);
  GTK_WIDGET_SET_FLAGS (GTK_WIDGET(regler), GTK_CAN_DEFAULT);
  if (regler->regler_type == 0)
    {
      widget->requisition.width = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_x;
      widget->requisition.height = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->regler_y;
    }
  else if (regler->regler_type == 1)
    {
      widget->requisition.width = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_x;
      widget->requisition.height = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigknob_y;
    }
  else if (regler->regler_type == 2)
    {
      widget->requisition.width = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_x;
      widget->requisition.height = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_y;
    }
  else if (regler->regler_type == 3)
    {
      widget->requisition.width = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_x;
      widget->requisition.height = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y;
    }
  else if (regler->regler_type == 4)
    {
      widget->requisition.width = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_x;
      widget->requisition.height = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_y;
    }
  else if (regler->regler_type == 5)
    {
      widget->requisition.width = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_x;
      widget->requisition.height = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_y;
    }
  else if (regler->regler_type == 6)
    {
      widget->requisition.width = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_x;
      widget->requisition.height = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minitoggle_y;
    }
  else if (regler->regler_type == 7)
    {
      widget->requisition.width = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_x;
      widget->requisition.height = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_y;
    }
  else if (regler->regler_type == 8)
    {
      widget->requisition.width = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_x;
      widget->requisition.height = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_y;
    }
  else if (regler->regler_type == 9)
    {
      widget->requisition.width = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_y;
      widget->requisition.height = GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_x;
    }
}

//----------- redraw when value changed
static gboolean gtk_regler_value_changed(gpointer obj)
{
  GtkWidget *widget = (GtkWidget *)obj;
  gtk_widget_queue_draw(widget);
  return FALSE;
}

//-------- the destructer doesen't work in virtual mode, so we need this destroy funktion
//-------- to clean up when exit. This must call in the destroy funktion of the main app.
void GtkRegler::gtk_regler_destroy ( )
{
  GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_REGLER, NULL ));
  g_assert(GTK_IS_REGLER(widget));
  if (G_IS_OBJECT(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> regler_image))
    g_object_unref(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> regler_image);
  if (G_IS_OBJECT(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> bigregler_image))
    g_object_unref(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> bigregler_image);
  if (G_IS_OBJECT(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> toggle_image))
    g_object_unref(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_image);
  if (G_IS_OBJECT(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> toggle_image1))
    g_object_unref(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->toggle_image1);
  if (G_IS_OBJECT(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> slider_image))
    g_object_unref(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image);
  if (G_IS_OBJECT(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> slider_image1))
    g_object_unref(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->slider_image1);
  if (G_IS_OBJECT(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> minislider_image))
    g_object_unref(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image);
  if (G_IS_OBJECT(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> minislider_image1))
    g_object_unref(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->minislider_image1);
  if (G_IS_OBJECT(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> switch_image))
    g_object_unref(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_image);
  if (G_IS_OBJECT(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> switch_image1))
    g_object_unref(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->switch_image1);
  if (G_IS_OBJECT(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> wheel_image))
    g_object_unref(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_image);
  if (G_IS_OBJECT(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> wheel_image1))
    g_object_unref(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->wheel_image1);
  if (G_IS_OBJECT(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> b_toggle_image))
    g_object_unref(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->b_toggle_image);
  if (G_IS_OBJECT(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> vslider_image))
    g_object_unref(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image);
  if (G_IS_OBJECT(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))-> vslider_image1))
    g_object_unref(GTK_REGLER_CLASS(GTK_OBJECT_GET_CLASS(widget))->vslider_image1);
}


//----------- create small knob
GtkWidget *GtkRegler::gtk_regler_new_with_adjustment(GtkAdjustment *_adjustment)
{
  GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_REGLER, NULL ));
  GtkRegler *regler = GTK_REGLER(widget);
  regler->regler_type = 0;
  if (widget)
    {
      gtk_range_set_adjustment(GTK_RANGE(widget), _adjustment);
      g_signal_connect(GTK_OBJECT(widget), "value-changed",
                       G_CALLBACK(gtk_regler_value_changed), widget);
    }
  return widget;
}

//----------- create Big knob
GtkWidget *GtkRegler::gtk_big_regler_new_with_adjustment(GtkAdjustment *_adjustment)
{
  GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_REGLER, NULL ));
  GtkRegler *regler = GTK_REGLER(widget);
  regler->regler_type = 1;
  if (widget)
    {
      gtk_range_set_adjustment(GTK_RANGE(widget), _adjustment);
      g_signal_connect(GTK_OBJECT(widget), "value-changed",
                       G_CALLBACK(gtk_regler_value_changed), widget);
    }
  return widget;
}

//----------- create a switcher
GtkWidget *GtkRegler::gtk_toggle_new_with_adjustment(GtkAdjustment *_adjustment)
{
  GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_REGLER, NULL ));
  GtkRegler *regler = GTK_REGLER(widget);
  regler->regler_type = 2;
  if (widget)
    {
      gtk_range_set_adjustment(GTK_RANGE(widget), _adjustment);
      g_signal_connect(GTK_OBJECT(widget), "value-changed",
                       G_CALLBACK(gtk_regler_value_changed), widget);
    }
  return widget;
}

//----------- create a horizontal slider
GtkWidget *GtkRegler::gtk_hslider_new_with_adjustment(GtkAdjustment *_adjustment)
{
  GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_REGLER, NULL ));
  GtkRegler *regler = GTK_REGLER(widget);
  regler->regler_type = 3;
  if (widget)
    {
      gtk_range_set_adjustment(GTK_RANGE(widget), _adjustment);
      g_signal_connect(GTK_OBJECT(widget), "value-changed",
                       G_CALLBACK(gtk_regler_value_changed), widget);
    }
  return widget;
}

//----------- create a horizontal mini slider
GtkWidget *GtkRegler::gtk_mini_slider_new_with_adjustment(GtkAdjustment *_adjustment)
{
  GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_REGLER, NULL ));
  GtkRegler *regler = GTK_REGLER(widget);
  regler->regler_type = 4;
  if (widget)
    {
      gtk_range_set_adjustment(GTK_RANGE(widget), _adjustment);
      g_signal_connect(GTK_OBJECT(widget), "value-changed",
                       G_CALLBACK(gtk_regler_value_changed), widget);
    }
  return widget;
}

//----------- create a switcher
GtkWidget *GtkRegler::gtk_switch_new_with_adjustment(GtkAdjustment *_adjustment)
{
  GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_REGLER, NULL ));
  GtkRegler *regler = GTK_REGLER(widget);
  regler->regler_type = 5;
  if (widget)
    {
      gtk_range_set_adjustment(GTK_RANGE(widget), _adjustment);
      g_signal_connect(GTK_OBJECT(widget), "value-changed",
                       G_CALLBACK(gtk_regler_value_changed), widget);
    }
  return widget;
}

//----------- create a minitoggle
GtkWidget *GtkRegler::gtk_mini_toggle_new_with_adjustment(GtkAdjustment *_adjustment)
{
  GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_REGLER, NULL ));
  GtkRegler *regler = GTK_REGLER(widget);
  regler->regler_type = 6;
  if (widget)
    {
      gtk_range_set_adjustment(GTK_RANGE(widget), _adjustment);
      g_signal_connect(GTK_OBJECT(widget), "value-changed",
                       G_CALLBACK(gtk_regler_value_changed), widget);
    }
  return widget;
}

//----------- create a horizontal wheel
GtkWidget *GtkRegler::gtk_wheel_new_with_adjustment(GtkAdjustment *_adjustment)
{
  GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_REGLER, NULL ));
  GtkRegler *regler = GTK_REGLER(widget);
  regler->regler_type = 7;
  if (widget)
    {
      gtk_range_set_adjustment(GTK_RANGE(widget), _adjustment);
      g_signal_connect(GTK_OBJECT(widget), "value-changed",
                       G_CALLBACK(gtk_regler_value_changed), widget);
    }
  return widget;
}

//----------- create a toggle button
GtkWidget *GtkRegler::gtk_button_toggle_new_with_adjustment(GtkAdjustment *_adjustment)
{
  GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_REGLER, NULL ));
  GtkRegler *regler = GTK_REGLER(widget);
  regler->regler_type = 8;
  if (widget)
    {
      gtk_range_set_adjustment(GTK_RANGE(widget), _adjustment);
      g_signal_connect(GTK_OBJECT(widget), "value-changed",
                       G_CALLBACK(gtk_regler_value_changed), widget);
    }
  return widget;
}

//----------- create a vertical slider
GtkWidget *GtkRegler::gtk_vslider_new_with_adjustment(GtkAdjustment *_adjustment)
{
  GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_REGLER, NULL ));
  GtkRegler *regler = GTK_REGLER(widget);
  regler->regler_type = 9;
  if (widget)
    {
      gtk_range_set_adjustment(GTK_RANGE(widget), _adjustment);
      g_signal_connect(GTK_OBJECT(widget), "value-changed",
                       G_CALLBACK(gtk_regler_value_changed), widget);
    }
  return widget;
}

//----------- get the Regler type
GType gtk_regler_get_type (void)
{
  static GType kn_type = 0;
  if (!kn_type)
    {
      static const GTypeInfo kn_info =
      {
        sizeof(GtkReglerClass), NULL,  NULL, (GClassInitFunc)gtk_regler_class_init, NULL, NULL, sizeof (GtkRegler), 0, (GInstanceInitFunc)gtk_regler_init
      };
      kn_type = g_type_register_static(GTK_TYPE_RANGE,  "GtkRegler", &kn_info, (GTypeFlags)0);
    }
  return kn_type;
}


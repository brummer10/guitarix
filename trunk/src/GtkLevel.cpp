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
  * -------------------------------------------------------------------------
  * 
  * Code greatly inspired by the LED bars found in gnome_wave_cleaner,
  * by Jeff Welty (jeff@redhawk.org)
  *
  * -------------------------------------------------------------------------
*/
#include <gtk/gtk.h>
#include "GtkLevel.h"

#define	LEVEL_WIDTH	(7)
#define	LEVEL_HEIGHT	(5)
#define	BOTTOM_SPACE	(2)

static void gtk_level_class_init   (GtkLevelClass*  klass);
static void gtk_level_init	   (GtkLevel*       level);
static void gtk_level_destroy	   (GtkObject*      object);
static void gtk_level_size_request (GtkWidget*      widget,
				    GtkRequisition* requisition);
static gint gtk_level_expose	   (GtkWidget*      widget,
				    GdkEventExpose* event);
static void gtk_level_realize      (GtkWidget*      widget);

static GtkMiscClass* parent_class = NULL;

enum {
  LEVEL_COLOR_ON,
  LEVEL_COLOR_OFF
};


GType gtk_level_get_type(void)
{
  static GType level_type = 0;
  
  if (!level_type)
  {
    static const GTypeInfo level_info =
    {
      sizeof(GtkLevelClass),
      NULL,
      NULL,
      (GClassInitFunc)gtk_level_class_init,
      NULL,
      NULL,
      sizeof(GtkLevel),
      0,
      (GInstanceInitFunc)gtk_level_init
    };
    
    level_type = g_type_register_static(GTK_TYPE_MISC, "GtkLevel", &level_info, (GTypeFlags)0);
  }
  
  return level_type;
}

void gtk_level_class_init(GtkLevelClass* klass)
{
  GtkObjectClass* object_class;
  GtkWidgetClass* widget_class;
  
  object_class = (GtkObjectClass*)klass;
  widget_class = (GtkWidgetClass*)klass;
  
  parent_class = (GtkMiscClass*)gtk_type_class(gtk_misc_get_type());
  
  object_class->destroy = gtk_level_destroy;
  
  widget_class->size_request  = gtk_level_size_request;
  widget_class->expose_event  = gtk_level_expose;
  widget_class->realize       = gtk_level_realize;
}

void gtk_level_init (GtkLevel *level)
{
  GtkMisc *misc;
  
  misc = GTK_MISC(level);

  GTK_WIDGET_SET_FLAGS(level, GTK_NO_WINDOW);
  
  level->is_on = FALSE;
  level->gc    = NULL;
}

/* -------------- */
GtkWidget* gtk_level_new ()
{
  GtkLevel* level = GTK_LEVEL(g_object_new(GTK_TYPE_LEVEL, NULL));
  return GTK_WIDGET (level);
}

/* -------------- */
void gtk_level_set_colors (GtkLevel* level, 
			   GdkColor* active, 
			   GdkColor* inactive)
{
  g_return_if_fail(level != NULL);
  g_return_if_fail(GTK_IS_LEVEL (level));

  level->fg[LEVEL_COLOR_ON]  = *(active);
  level->fg[LEVEL_COLOR_OFF] = *(inactive);
}

/* -------------- */
void gtk_level_set_state(GtkLevel*    level,
			 GtkStateType widget_state,
			 gboolean     on_off)
{
  g_return_if_fail(level != NULL);
  g_return_if_fail(GTK_IS_LEVEL (level));

  gtk_widget_set_state(GTK_WIDGET (level), widget_state);
  gtk_level_switch(level, on_off);
}

/* -------------- */
void gtk_level_switch(GtkLevel* level,
		      gboolean on_off)
{
  g_return_if_fail(level != NULL);
  g_return_if_fail(GTK_IS_LEVEL (level));

  level->is_on = on_off != FALSE;
  gtk_widget_draw (GTK_WIDGET (level), NULL);
}

/* -------------- */
gboolean gtk_level_is_on (GtkLevel *level)
{
  g_return_val_if_fail(level != NULL, FALSE);
  g_return_val_if_fail(GTK_IS_LEVEL (level), FALSE);
  
  return level->is_on;
}

/* -------------- */
static void gtk_level_destroy(GtkObject* object)
{
  GtkLevel* level;
  
  g_return_if_fail(object != NULL);
  g_return_if_fail(GTK_IS_LEVEL (object));
  
  level = GTK_LEVEL(object);
  
  if (GTK_WIDGET(object)->parent &&
      GTK_WIDGET_MAPPED(object))
    gtk_widget_unmap(GTK_WIDGET(object));
  
  if (GTK_OBJECT_CLASS(parent_class)->destroy)
    (* GTK_OBJECT_CLASS(parent_class)->destroy) (object);
}

/* -------------- */
static void gtk_level_size_request(GtkWidget*      widget,
				   GtkRequisition* requisition)
{
  GtkLevel* level;
  
  g_return_if_fail(widget != NULL);
  g_return_if_fail(GTK_IS_LEVEL (widget));
  g_return_if_fail(requisition != NULL);
  
  level = GTK_LEVEL(widget);
  
  requisition->width  = LEVEL_WIDTH  + level->misc.xpad * 2;
  requisition->height = LEVEL_HEIGHT + level->misc.ypad * 2 + BOTTOM_SPACE;
}

/* -------------- */
static void gtk_level_realize(GtkWidget *widget)
{
  GtkLevel*    level;
  GdkColormap* cmap;

  g_return_if_fail(widget != NULL);
  g_return_if_fail(GTK_IS_LEVEL(widget));

  GTK_WIDGET_SET_FLAGS(widget, GTK_REALIZED);

  level = GTK_LEVEL(widget);
  widget->window = gtk_widget_get_parent_window(widget);

  gdk_window_ref(widget->window);
  widget->style = gtk_style_attach (widget->style, widget->window);

  if (!level->gc)
  {
    cmap = gtk_widget_get_colormap (widget);
    
    if (!(&(level->fg[LEVEL_COLOR_ON])))
      gdk_color_parse ("#00F100", &(level->fg[LEVEL_COLOR_ON]));

    gdk_color_alloc (cmap, &(level->fg[LEVEL_COLOR_ON]));

    if (!(&(level->fg[LEVEL_COLOR_OFF])))
      gdk_color_parse ("#008C00", &(level->fg[LEVEL_COLOR_OFF]));

    gdk_color_alloc (cmap, &(level->fg[LEVEL_COLOR_OFF]));
    level->gc = gdk_gc_new (widget->window);
    gdk_gc_copy (level->gc, widget->style->white_gc);
  }
}

/* -------------- */
static gint gtk_level_expose(GtkWidget*      widget,
			     GdkEventExpose* event)
{
  GtkLevel* level;
  GtkMisc*  misc;
  GdkColor* win_bg;

  g_return_val_if_fail(widget != NULL, FALSE);
  g_return_val_if_fail(GTK_IS_LEVEL (widget), FALSE);
  g_return_val_if_fail(event  != NULL, FALSE);
  
  level = GTK_LEVEL (widget);
  misc  = GTK_MISC (widget);

  if (GTK_WIDGET_DRAWABLE (widget))
  {
    if ((widget->allocation.width >= widget->requisition.width) &&
	(widget->allocation.height >= widget->requisition.height))
    {
      guint x, y;

      win_bg = (level->is_on) ? &(level->fg[LEVEL_COLOR_ON]) : 
	&(level->fg[LEVEL_COLOR_OFF]);

      gdk_gc_set_foreground (level->gc, win_bg);

      x = widget->allocation.x + misc->xpad +
	(widget->allocation.width - widget->requisition.width) * 
	misc->xalign + 0.5;

      y = widget->allocation.y + misc->ypad + LEVEL_HEIGHT/2 +
	(widget->allocation.height - widget->requisition.height) * 
	misc->yalign + 0.5 - BOTTOM_SPACE;
      
      gdk_draw_rectangle (widget->window,
			  level->gc,
			  TRUE,
			  x, y,
			  LEVEL_WIDTH,
			  LEVEL_HEIGHT);
    }
  }
  
  return TRUE;
}
/* EOF */


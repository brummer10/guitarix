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
#include <gtk/gtktable.h>
#include "GtkLevelBar.h"

static void gtk_level_bar_class_init (GtkLevelBarClass* klass);
static void gtk_level_bar_init       (GtkLevelBar*      lbar);

/* GTK type and class definition */
GType gtk_level_bar_get_type(void)
{
  static GType lbar_type = 0;
  
  if (!lbar_type)
  {
    static const GTypeInfo lbar_info =
    {
      sizeof(GtkLevelBarClass),
      NULL,
      NULL,
      (GClassInitFunc)gtk_level_bar_class_init,
      NULL,
      NULL,
      sizeof(GtkLevelBar),
      0,
      (GInstanceInitFunc)gtk_level_bar_init,
    };
    
    lbar_type = g_type_register_static(GTK_TYPE_VBOX, "GtkLevelBar", &lbar_info, (GTypeFlags)0);
  }
  
  return lbar_type;


}

static void gtk_level_bar_class_init (GtkLevelBarClass* klass)
{
  GtkObjectClass* object_class;

  object_class = (GtkObjectClass*)klass;
}

static void gtk_level_bar_init (GtkLevelBar* lbar)
{
  lbar->num_segments = 0;
  lbar->lit_segments = 0;
  lbar->seq_segment  = 0;
  lbar->seq_dir      = 1;
}

/* create a new GtkLevelBar object */
GtkWidget* gtk_level_bar_new(gint segments, gint orientation )
{
  GtkLevelBar* lbar;
  GtkWidget*   table;
  GdkColor     active;
  GdkColor     inactive;

  lbar = GTK_LEVEL_BAR(g_object_new(GTK_TYPE_LEVEL_BAR, NULL));

  if (segments > MAX_SEGMENTS)
    segments = MAX_SEGMENTS;

  lbar->num_segments = segments;
  lbar->orientation  = orientation;

  if (orientation) /* vertical */
      table = gtk_table_new(segments, 1, FALSE);

  else /* horizontal */
    table = gtk_table_new(1, segments, FALSE);

  gtk_container_add(GTK_CONTAINER(lbar), table);
  gtk_widget_show(table);

  gint half = .50 * segments;
  gint full = .75 * segments;
  gdk_color_parse ("#00F100", &active);
  gdk_color_parse ("#004C00", &inactive);

  for (gint i = 0; i < segments; i++) 
  {
    if (i >= half && i <= full)
    {
      gdk_color_parse("#F1EE00", &active);
      gdk_color_parse("#6C6A00", &inactive);
    }
    else
      if (i >= full)
      {
	gdk_color_parse("#Ff0000", &active);
	gdk_color_parse("#6C0000", &inactive);
      }

    lbar->segments[i] = gtk_level_new ();
    gtk_level_set_colors(GTK_LEVEL(lbar->segments[i]), 
			 &active, &inactive);

    if (!orientation ) /* horizontal */
      gtk_table_attach(GTK_TABLE(table), lbar->segments[i],
		       i, (i + 1), 0, 1, 
		       GTK_EXPAND, GTK_EXPAND, 0, 0);
    else /* vertical */
      gtk_table_attach(GTK_TABLE(table), lbar->segments[i],
		       0, 1, (segments - i - 1), (segments - i), 
		       GTK_EXPAND, GTK_EXPAND, 10, 10);

    gtk_widget_show (lbar->segments[i]);
  }

  return GTK_WIDGET (lbar);
}

/* -------------- */
gint gtk_level_bar_get_num_segments(GtkWidget* bar)
{
  g_return_val_if_fail (bar != NULL, 0);
  g_return_val_if_fail (GTK_IS_LEVEL_BAR(bar), 0);

  return (GTK_LEVEL_BAR(bar)->num_segments);
}


/* -------------- */
void gtk_level_bar_light_segments(GtkWidget* bar, gint num)
{
  GtkLevelBar* lbar;
  gint i;

  g_return_if_fail(bar != NULL);
  g_return_if_fail(GTK_IS_LEVEL_BAR(bar));

  lbar = GTK_LEVEL_BAR (bar);

  if (num == 0 && lbar->lit_segments == 0)
    return;

  if (num < lbar->lit_segments)
  {
    for (i = 0; i < num; i++) 
    {
      gtk_level_set_state (GTK_LEVEL(lbar->segments[i]), 
			   GTK_STATE_SELECTED,
			   TRUE);
    }
  }
  else
  {
    for (i = lbar->lit_segments; i < num; i++)
      gtk_level_set_state(GTK_LEVEL(lbar->segments[i]),
			  GTK_STATE_SELECTED,
			  TRUE);
  }

  lbar->lit_segments = i;
}

/* -------------- */
void gtk_level_bar_unlight_segments(GtkWidget* bar, gint num)
{
  GtkLevelBar* lbar;

  g_return_if_fail(bar != NULL);
  g_return_if_fail(GTK_IS_LEVEL_BAR(bar));

  lbar = GTK_LEVEL_BAR(bar);
  if (lbar->lit_segments == 0)
    return;

  for (gint i = 0; i < num; i++) 
  {
    gtk_level_set_state(GTK_LEVEL(lbar->segments[i]),
			GTK_STATE_SELECTED,
			FALSE);
  }

  lbar->lit_segments -= num;
  if (lbar->lit_segments < 0)
    lbar->lit_segments = 0;
}

/* -------------- */
void gtk_level_bar_light_segment(GtkWidget* bar, gint segment)
{
  GtkLevelBar* lbar;

  g_return_if_fail(bar != NULL);
  g_return_if_fail(GTK_IS_LEVEL_BAR(bar));

  lbar = GTK_LEVEL_BAR(bar);
  gtk_level_set_state (GTK_LEVEL(lbar->segments[segment]),
		       GTK_STATE_SELECTED,
		       TRUE);
}

/* -------------- */
void gtk_level_bar_unlight_segment(GtkWidget* bar, gint segment)
{
  GtkLevelBar* lbar;

  g_return_if_fail (bar != NULL);
  g_return_if_fail (GTK_IS_LEVEL_BAR(bar));

  lbar = GTK_LEVEL_BAR(bar);
  gtk_level_set_state(GTK_LEVEL(lbar->segments[segment]),
		      GTK_STATE_SELECTED,
		      FALSE);
}

/* -------------- */
void gtk_level_bar_light_percent(GtkWidget* bar, gfloat percent)
{
  GtkLevelBar* lbar;

  g_return_if_fail(bar != NULL);
  g_return_if_fail(GTK_IS_LEVEL_BAR(bar));

  lbar = GTK_LEVEL_BAR(bar);

  gint num = percent * lbar->num_segments;
  lbar->lit_segments = num;

  for (gint i = 0; i < lbar->num_segments; i++) 
  {
    if (num > 0 ) 
    {
      if (! (GTK_LEVEL(lbar->segments[i])->is_on))
	gtk_level_set_state(GTK_LEVEL(lbar->segments[i]),
			    GTK_STATE_SELECTED,
			    TRUE);
      num--;
    } 
    else 
    {
      if (GTK_LEVEL(lbar->segments[i])->is_on)
	gtk_level_set_state(GTK_LEVEL(lbar->segments[i]),
			    GTK_STATE_SELECTED,
			    FALSE);
    }
  }
}

/* -------------- */
void gtk_level_bar_clear(GtkWidget *bar)
{
  GtkLevelBar* lbar;

  g_return_if_fail(bar != NULL);
  g_return_if_fail(GTK_IS_LEVEL_BAR(bar));

  lbar = GTK_LEVEL_BAR (bar);

  for (gint i = 0; i < lbar->num_segments; i++) 
  {
    if (GTK_LEVEL(lbar->segments[i])->is_on)
      gtk_level_set_state(GTK_LEVEL(lbar->segments[i]),
			  GTK_STATE_SELECTED,
			  FALSE);
  }
}

/* -------------- */
void
gtk_level_bar_sequence_step(GtkWidget *bar)
{
  GtkLevelBar* lbar;

  g_return_if_fail(bar != NULL);
  g_return_if_fail(GTK_IS_LEVEL_BAR (bar));

  lbar = GTK_LEVEL_BAR(bar);

  if (lbar->seq_segment >= (lbar->num_segments - 1))
    lbar->seq_dir = -1;

  else if (lbar->seq_segment <= 0)
    lbar->seq_dir = 1;

  gtk_level_bar_unlight_segment(GTK_WIDGET(lbar), lbar->seq_segment);
  lbar->seq_segment += lbar->seq_dir;

  gtk_level_bar_light_segment(GTK_WIDGET(lbar), lbar->seq_segment);
}

/* EOF */




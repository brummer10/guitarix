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
#include <iostream>
#include <cmath>
#include <gtk/gtk.h>
#include <gtk/gtktable.h>
#include "GtkLevelBar.h"

#define MIN_DB       (-40.)
#define MAX_DB       (6.)
#define PERCENT2DB(x)     (20.*log10((x)))
#define DB2HEIGHT(x) (((x) - MIN_DB)/(MAX_DB - MIN_DB)) 

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
  lbar->num_segments    = 0;
  lbar->lit_segments[0] = 0;
  lbar->lit_segments[1] = 0;
  lbar->seq_segment     = 0;
  lbar->seq_dir         = 1;
  lbar->orientation     = 0;
  lbar->nchan           = 1;
}

/* create a new GtkLevelBar object */
GtkWidget* gtk_level_bar_new(gint segments, gint orientation, int nchan)
{
  GtkLevelBar* lbar;
  GtkWidget*   table;
  GdkColor     active;
  GdkColor     inactive;
  
  /* create object */
  lbar = GTK_LEVEL_BAR(g_object_new(GTK_TYPE_LEVEL_BAR, NULL));

  /* impose limit if input value crazy */
  if (segments >  MAX_SEGMENTS) segments = MAX_SEGMENTS;
  if (segments <= 0) segments = MAX_SEGMENTS;

  /* set basic stuff */
  lbar->num_segments = segments;
  lbar->orientation  = orientation;
  lbar->nchan        = nchan;
  if (nchan < 1 || nchan > MAX_CHANS)
    lbar->nchan      = 1;

  /* create segment table */
  if (orientation) /* vertical */
      table = gtk_table_new(segments, nchan, FALSE);

  else /* horizontal */
    table = gtk_table_new(nchan, segments, FALSE);

  gtk_container_add(GTK_CONTAINER(lbar), table);
  gtk_widget_show(table);

  /* initialize segment color with idle colors */
  gint half = .648 * segments; // -10 dB
  gint full = .870 * segments; //   0 dB

  for (int c = 0; c < nchan; c++)
  {
    gdk_color_parse ("#00F100", &active);
    gdk_color_parse ("#004C00", &inactive);

    for (gint i = 0; i < segments; i++) 
    {
      if (i >= half && i <= full)
      {
	gdk_color_parse("#F1EE00", &active);
	gdk_color_parse("#6C6A00", &inactive);
      }
      else if (i >= full)
      {
	gdk_color_parse("#Ff0000", &active);
	gdk_color_parse("#6C0000", &inactive);
      }

      lbar->segments[c][i] = gtk_level_new();
      gtk_level_set_colors(GTK_LEVEL(lbar->segments[c][i]), 
			   &active, &inactive);

      if (!orientation ) /* horizontal */
	gtk_table_attach(GTK_TABLE(table), lbar->segments[c][i],
			 i, (i + 1), c, c+1, 
			 GTK_EXPAND, GTK_FILL, 0, 2);
      else /* vertical */
	gtk_table_attach(GTK_TABLE(table), lbar->segments[c][i],
			 c, c+1, (segments - i - 1), (segments - i), 
			 GTK_FILL, GTK_EXPAND, 2, 0);

      gtk_widget_show (lbar->segments[c][i]);
    }
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

  for (int c = 0; c < lbar->nchan; c++)
  {
    if (num == 0 && lbar->lit_segments[c] == 0)
      continue;

    if (num < lbar->lit_segments[c])
    {
      for (i = 0; i < num; i++) 
      {
	gtk_level_set_state (GTK_LEVEL(lbar->segments[c][i]), 
			     GTK_STATE_SELECTED,
			     TRUE);
      }
    }
    else
    {
      for (i = lbar->lit_segments[c]; i < num; i++)
	gtk_level_set_state(GTK_LEVEL(lbar->segments[c][i]),
			    GTK_STATE_SELECTED,
			    TRUE);
    }

    lbar->lit_segments[c] = i;
  }
}

/* -------------- */
void gtk_level_bar_unlight_segments(GtkWidget* bar, gint num)
{
  GtkLevelBar* lbar;

  g_return_if_fail(bar != NULL);
  g_return_if_fail(GTK_IS_LEVEL_BAR(bar));

  lbar = GTK_LEVEL_BAR(bar);

  for (int c = 0; c < lbar->nchan; c++)
  {
    if (lbar->lit_segments[c] == 0)
      continue;

    for (gint i = 0; i < num; i++) 
    {
      gtk_level_set_state(GTK_LEVEL(lbar->segments[c][i]),
			  GTK_STATE_SELECTED,
			  FALSE);
    }

    lbar->lit_segments[c] -= num;
    if (lbar->lit_segments[c] < 0)
      lbar->lit_segments[c] = 0;
  }
}

/* -------------- */
void gtk_level_bar_light_segment(GtkWidget* bar, gint segment)
{
  GtkLevelBar* lbar;

  g_return_if_fail(bar != NULL);
  g_return_if_fail(GTK_IS_LEVEL_BAR(bar));

  lbar = GTK_LEVEL_BAR(bar);

  for (int c = 0; c < lbar->nchan; c++)
    gtk_level_set_state (GTK_LEVEL(lbar->segments[c][segment]),
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

  for (int c = 0; c < lbar->nchan; c++)
    gtk_level_set_state(GTK_LEVEL(lbar->segments[c][segment]),
			GTK_STATE_SELECTED,
			FALSE);
}

/* -------------- */
void gtk_level_bar_light_percent(GtkWidget* bar, 
				 float percent[])
{
  GtkLevelBar* lbar;

  g_return_if_fail(bar != NULL);
  g_return_if_fail(GTK_IS_LEVEL_BAR(bar));

  lbar = GTK_LEVEL_BAR(bar);

  for (int c = 0; c < lbar->nchan; c++)
  {
    float db = PERCENT2DB(percent[c]);
    if (db < MIN_DB)
    {
      for (int i = 0; i < lbar->num_segments; i++)
	if (gtk_level_is_on(GTK_LEVEL(lbar->segments[c][i])) == TRUE)
	  gtk_level_set_state(GTK_LEVEL(lbar->segments[c][i]),
			      GTK_STATE_SELECTED,
			      FALSE);
      continue;
    }

    gint num = DB2HEIGHT(db) * lbar->num_segments;

    if (num >= lbar->num_segments)
      num = (lbar->num_segments-1);

    lbar->lit_segments[c] = num;

    for (int i = 0; i <= num; i++)
      if (gtk_level_is_on(GTK_LEVEL(lbar->segments[c][i])) == FALSE)
	gtk_level_set_state(GTK_LEVEL(lbar->segments[c][i]),
			    GTK_STATE_SELECTED,
			    TRUE);
    
    for (int i = num + 1; i < lbar->num_segments; i++)
      if (gtk_level_is_on(GTK_LEVEL(lbar->segments[c][i])) == TRUE)
	gtk_level_set_state(GTK_LEVEL(lbar->segments[c][i]),
			    GTK_STATE_SELECTED,
			    FALSE);
  }
}

/* -------------- */
void gtk_level_bar_light_percent_max(GtkWidget* bar, float percent[])
{
  GtkLevelBar* lbar;

  g_return_if_fail(bar != NULL);
  g_return_if_fail(GTK_IS_LEVEL_BAR(bar));

  lbar = GTK_LEVEL_BAR(bar);

  static gint old_num[MAX_CHANS] = {0, 0};

  for (int c = 0; c < lbar->nchan; c++)
  {
    float db = PERCENT2DB(percent[c]);
    if (db < MIN_DB)
    {
      for (int i = 0; i < lbar->num_segments; i++)
	if (gtk_level_is_on(GTK_LEVEL(lbar->segments[c][i])) == TRUE)
	  gtk_level_set_state(GTK_LEVEL(lbar->segments[c][i]),
			      GTK_STATE_SELECTED,
			      FALSE);
      continue;
    }

    gint num = DB2HEIGHT(db) * lbar->num_segments;
    if (num >= lbar->num_segments)
      num = (lbar->num_segments-1);

    lbar->lit_segments[c] = num;

    gtk_level_set_state(GTK_LEVEL(lbar->segments[c][num]),
			GTK_STATE_SELECTED,
			TRUE);
      
    if (old_num[c] != num) 
      gtk_level_set_state(GTK_LEVEL(lbar->segments[c][old_num[c]]),
			  GTK_STATE_SELECTED,
			  FALSE);
    old_num[c] = num;
  }
}

/* -------------- */
void gtk_level_bar_clear(GtkWidget *bar)
{
  GtkLevelBar* lbar;

  g_return_if_fail(bar != NULL);
  g_return_if_fail(GTK_IS_LEVEL_BAR(bar));

  lbar = GTK_LEVEL_BAR (bar);

  for (int c = 0; c < lbar->nchan; c++)
    for (gint i = 0; i < lbar->num_segments; i++) 
      if (GTK_LEVEL(lbar->segments[c][i])->is_on)
	gtk_level_set_state(GTK_LEVEL(lbar->segments[c][i]),
			    GTK_STATE_SELECTED,
			    FALSE);
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




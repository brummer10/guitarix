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

#ifndef __GTKLEVELBAR_H__
#define __GTKLEVELBAR_H__

#include <gdk/gdk.h>
#include <gtk/gtkvbox.h>
#include "GtkLevel.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GTK_TYPE_LEVEL_BAR            (gtk_level_bar_get_type())
#define GTK_LEVEL_BAR(obj)	      (G_TYPE_CHECK_INSTANCE_CAST((obj), GTK_TYPE_LEVEL_BAR, GtkLevelBar))
#define GTK_IS_LEVEL_BAR(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj), GTK_TYPE_LEVEL_BAR))
#define GTK_LEVEL_BAR_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass),  GTK_TYPE_LEVEL_BAR, GtkLevelBarClass))
#define GTK_IS_LEVEL_BAR_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),  GTK_TYPE_LEVEL_BAR))

#define MAX_SEGMENTS         100
#define MAX_CHANS            2

typedef struct _GtkLevelBar       GtkLevelBar;
typedef struct _GtkLevelBarClass  GtkLevelBarClass;

struct _GtkLevelBar
{
  GtkVBox   vbox;

  GtkWidget* segments[MAX_CHANS][MAX_SEGMENTS];

  gint      num_segments;            /* How many segmanets in this bar */
  gint      lit_segments[MAX_CHANS]; /* last segment that is lit */
  gint      seq_segment;             /* which led in the sequence we are at */
  gint      seq_dir;                 /* direction */
  gint      orientation;             /* vertical (1), or horizontal (0) */
  gint      nchan;                   /* number of audio channels */
};

struct _GtkLevelBarClass
{
  GtkVBoxClass   parent_class;
};

GType         gtk_level_bar_get_type        (void);
GtkWidget*    gtk_level_bar_new             (gint segments,
					     gint orientation,
					     gint nchan);
gint          gtk_level_bar_get_num_segments(GtkWidget* bar);
void          gtk_level_bar_light_segments  (GtkWidget* bar,
					     gint       num);
void          gtk_level_bar_unlight_segments(GtkWidget* bar,
					     gint       num);
void          gtk_level_bar_light_segment   (GtkWidget* bar,
					     gint       segment);
void          gtk_level_bar_unlight_segment (GtkWidget*bar,
					     gint       segment);
void          gtk_level_bar_light_percent   (GtkWidget*bar,
					     float     percent[]);
void          gtk_level_bar_light_percent_max(GtkWidget*bar,
					      float     percent[]);
void          gtk_level_bar_sequence_step   (GtkWidget* bar);
void          gtk_level_bar_clear           (GtkWidget* bar);

#ifdef __cplusplus
}
#endif

#endif

/* EOF */


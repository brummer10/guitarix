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

#ifndef __GTK_LEVEL_H__
#define __GTK_LEVEL_H__


#include <gdk/gdk.h>
#include <gtk/gtkmisc.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define GTK_TYPE_LEVEL            (gtk_level_get_type())
#define GTK_LEVEL(obj)	          (G_TYPE_CHECK_INSTANCE_CAST((obj), GTK_TYPE_LEVEL, GtkLevel))
#define GTK_IS_LEVEL(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj), GTK_TYPE_LEVEL))
#define GTK_LEVEL_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass),  GTK_TYPE_LEVEL, GtkLevelClass))
#define GTK_IS_LEVEL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),  GTK_TYPE_LEVEL))


typedef struct _GtkLevel       GtkLevel;
typedef struct _GtkLevelClass  GtkLevelClass;

struct _GtkLevel
{
  GtkMisc  misc;
  GdkColor fg[2];
  GdkColor bg[2];

  GdkGC    *gc;

  guint is_on;
};

struct _GtkLevelClass
{
  GtkMiscClass parent_class;
};


GType	   gtk_level_get_type    (void);

GtkWidget* gtk_level_new	 (void);

void	   gtk_level_set_state   (GtkLevel*    level,
				  GtkStateType widget_state,
				  gboolean     on_off);

void	   gtk_level_switch      (GtkLevel     *level,
				  gboolean     on_off);

gboolean   gtk_level_is_on       (GtkLevel     *level);

void       gtk_level_set_colors  (GtkLevel     *level,
				  GdkColor     *active,
				  GdkColor     *inactive);





#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __GTK_LEVEL_H__ */

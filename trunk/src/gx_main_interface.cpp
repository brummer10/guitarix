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
 * ---------------------------------------------------------------------------
 *
 *    This is the guitarix GUI main class
 *
 * ----------------------------------------------------------------------------
 */
#include <errno.h>

#include <assert.h>
#include <cstring>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstdio>

using namespace std;

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <jack/jack.h>
#include <sndfile.h>
//#include <fftw3.h>

#include "guitarix.h"

using namespace gx_system;
using namespace gx_child_process;
using namespace gx_preset;
using namespace gx_cairo;
using namespace gx_threads;

namespace gx_gui
  {

    // -------------------------------------------------------------
    // GxMainInterface widget and method definitions
    //
    // static member
    bool GxMainInterface::fInitialized = false;

    GxMainInterface::GxMainInterface(const char * name, int* pargc, char*** pargv)
    {
      gtk_init(pargc, pargv);

      /*-- set rc file overwrite it with export--*/
      gtk_rc_parse(rcpath.c_str());

      /*-- Declare the GTK Widgets --*/
      fWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);

      /*---------------- set window defaults ----------------*/
      gtk_window_set_resizable(GTK_WINDOW (fWindow) , FALSE);
      gtk_window_set_title (GTK_WINDOW (fWindow), name);
      gtk_window_set_gravity(GTK_WINDOW(fWindow), GDK_GRAVITY_NORTH_EAST);

      /*---------------- singnals ----------------*/
      g_signal_connect (GTK_OBJECT (fWindow), "destroy",
                        G_CALLBACK (gx_clean_exit), NULL);

      /*---------------- status icon ----------------*/
      if (gx_pixmap_check() == 0)
        {
          status_icon =    gtk_status_icon_new_from_pixbuf (GDK_PIXBUF(ib));
          gtk_window_set_icon(GTK_WINDOW (fWindow), GDK_PIXBUF(ib));
          g_signal_connect (G_OBJECT (status_icon), "activate", G_CALLBACK (gx_hide_extended_settings), NULL);
          g_signal_connect (G_OBJECT (status_icon), "popup-menu", G_CALLBACK (gx_systray_menu), NULL);
        }
      else
        {
          gx_print_error("Main Interface Constructor",
                         "pixmap check failed, giving up");
          gx_clean_exit(NULL, (gpointer)1);
        }

      /*-- create accelerator group for keyboard shortcuts --*/
      fAccelGroup = gtk_accel_group_new();
      gtk_window_add_accel_group(GTK_WINDOW(fWindow), fAccelGroup);

      /*---------------- create boxes ----------------*/
      fTop = 0;
      fBox[fTop] = gtk_vbox_new (homogene, 4);
      fMode[fTop] = kBoxMode;

      /*---------------- add mainbox to main window ---------------*/
      gtk_container_add (GTK_CONTAINER (fWindow), fBox[fTop]);

      fStopped = false;
    }

    //------- create or retrieve unique instance
    GxMainInterface* GxMainInterface::instance(const char* name, int* pargc, char*** pargv)
    {
      static GxMainInterface maingui(name, pargc, pargv);
      return &maingui;
    }


    //------- retrieve jack latency menu item
    GtkWidget* const
    GxMainInterface::getJackLatencyItem(const jack_nframes_t bufsize) const
      {
        int index = (int)(log((float)bufsize)/log(2)) - 5;

        if (index >= 0 && index < NJACKLAT)
          return fJackLatencyItem[index];

        return NULL;
      }

    //------- box stacking up
    void GxMainInterface::pushBox(int mode, GtkWidget* w)
    {
      assert(++fTop < stackSize);
      fMode[fTop] 	= mode;
      fBox[fTop] 		= w;
    }

    void GxMainInterface::closeBox()
    {
      assert(--fTop >= 0);
    }

    //-------- different box styles
    void GxMainInterface::openFrameBox(const char* label)
    {
      GtkWidget * box = gtk_hbox_new (homogene, 2);
      gtk_container_set_border_width (GTK_CONTAINER (box), 2);
      g_signal_connect(box, "expose-event", G_CALLBACK(box10_expose), NULL);
      if (fMode[fTop] != kTabMode && label[0] != 0)
        {
          GtkWidget * frame = addWidget(label, gtk_frame_new (label));
          gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_NONE);
          gtk_container_add (GTK_CONTAINER(frame), box);
          gtk_widget_show(box);
          pushBox(kBoxMode, box);
        }
      else
        {
          pushBox(kBoxMode, addWidget(label, box));
        }

    }

    void GxMainInterface::openTabBox(const char* label)
    {
      pushBox(kTabMode, addWidget(label, gtk_notebook_new ()));
    }

    void GxMainInterface::openTextLoggingBox(const char* label)
    {
      GtkWidget* box = gtk_hbox_new (homogene, 0);
      gtk_container_set_border_width (GTK_CONTAINER (box), 0);

      GtkWidget * scrollbox = gtk_scrolled_window_new(NULL,NULL);
      gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrollbox),
                                      GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);

      GtkWidget* frame = addWidget(label, gtk_expander_new(label));
      gtk_container_add (GTK_CONTAINER(frame), box);
      gtk_widget_show(frame);
      gtk_expander_set_expanded(GTK_EXPANDER(frame), FALSE);
      fLoggingBox = GTK_EXPANDER(frame);

      // create text buffer
      GtkTextBuffer* buffer = gtk_text_buffer_new(NULL);
      gtk_text_buffer_set_text(buffer, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", -1);

      GtkWidget* tbox = gtk_text_view_new_with_buffer(buffer);
      gtk_container_set_border_width (GTK_CONTAINER (tbox), 0);
      gtk_text_view_set_editable(GTK_TEXT_VIEW(tbox), FALSE);
      gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(tbox), FALSE);
      gtk_text_view_set_pixels_above_lines (GTK_TEXT_VIEW(tbox), 0);
      gtk_text_view_set_pixels_below_lines (GTK_TEXT_VIEW(tbox), 2);
      gtk_text_view_set_justification(GTK_TEXT_VIEW(tbox), GTK_JUSTIFY_LEFT);
      gtk_text_view_set_left_margin(GTK_TEXT_VIEW(tbox), 5);
      gtk_text_view_set_indent(GTK_TEXT_VIEW(tbox), 0);

      gtk_container_add (GTK_CONTAINER(box), scrollbox);
      gtk_container_add(GTK_CONTAINER(scrollbox),GTK_WIDGET(tbox));
      gtk_widget_show(tbox);
      gtk_widget_show(scrollbox);
      fLoggingWindow = GTK_TEXT_VIEW(tbox);

      gtk_widget_show(box);
    }

    void GxMainInterface::openLevelMeterBox(const char* label)
    {
      GtkWidget* box = addWidget(label, gtk_hbox_new (FALSE, 0));

      gint boxheight = 135;
      gint boxwidth  = 36;

      gtk_container_set_border_width (GTK_CONTAINER (box), 3);
      gtk_box_set_spacing(GTK_BOX(box), 1);

      gtk_widget_set_size_request (GTK_WIDGET(box), boxwidth, boxheight);
      g_signal_connect(box, "expose-event", G_CALLBACK(box7_expose), NULL);
      g_signal_connect(GTK_CONTAINER(box), "check-resize",
                       G_CALLBACK(box7_expose), NULL);

      // meter level colors
      int base = 0x00380800;
      int mid  = 0x00ff0000;
      int top  = 0xff000000;
      int clip = 0xff000000;

      // width of meter
      int width    = 4;

      // how long we hold the peak bar = hold * thread call timeout

      // Note: 30 * 80 = 2.4 sec
      int hold     = 20;

      // guitarix output levels
      GtkWidget* gxbox = gtk_hbox_new (FALSE, 0);
      gtk_container_set_border_width (GTK_CONTAINER (gxbox), 0);
      gtk_box_set_spacing(GTK_BOX(gxbox), 1);

      for (int i = 0; i < 2; i++)
        {
          fLevelMeters[i] = 0;

          GtkWidget* meter =
            gtk_fast_meter_new(hold, width, boxheight,
                               base, mid, top, clip);

          gtk_widget_add_events(meter, GDK_BUTTON_RELEASE_MASK);
          g_signal_connect(G_OBJECT(meter), "button-release-event",
                           G_CALLBACK(gx_meter_button_release), 0);

          gtk_box_pack_start(GTK_BOX(gxbox), meter, FALSE, TRUE, 0);
          gtk_widget_show(meter);

          GtkTooltips* tooltips = gtk_tooltips_new ();
          gtk_tooltips_set_tip(tooltips, meter, "guitarix output", " ");
          fLevelMeters[i] = meter;
        }

      gtk_box_pack_start(GTK_BOX(box), gxbox, FALSE, TRUE, 0);
      gtk_widget_show(gxbox);


      // jconv output levels
      GtkWidget* jcbox = gtk_hbox_new (FALSE, 0);
      gtk_container_set_border_width (GTK_CONTAINER (jcbox), 1);
      gtk_box_set_spacing(GTK_BOX(jcbox), 1);

      for (int i = 0; i < 2; i++)
        {
          fJCLevelMeters[i] = 0;

          GtkWidget* meter =
            gtk_fast_meter_new(hold, width, boxheight,
                               base, mid, top, clip);

          gtk_widget_add_events(meter, GDK_BUTTON_RELEASE_MASK);
          g_signal_connect(G_OBJECT(meter), "button-release-event",
                           G_CALLBACK(gx_meter_button_release), 0);

          gtk_box_pack_end(GTK_BOX(box), meter, FALSE, FALSE, 0);

          GtkTooltips* tooltips = gtk_tooltips_new ();
          gtk_tooltips_set_tip(tooltips, meter, "jconv output", " ");

          gtk_widget_hide(meter);
          fJCLevelMeters[i] = meter;
        }

      gtk_box_pack_end(GTK_BOX(box), jcbox, FALSE, TRUE, 0);
      gtk_widget_show(jcbox);

      // show main box
      gtk_widget_show(box);
    }

    /* --- create the portmap window with tabbed client port tables --- */
    void GxMainInterface::createPortMapWindow(const char* label)
    {
      // static box containing all
      GtkWidget* vbox = gtk_vbox_new(FALSE, 2);
      gtk_container_set_border_width (GTK_CONTAINER (vbox), 8);
      g_signal_connect(vbox, "expose-event", G_CALLBACK(box4_expose), NULL);
      gtk_widget_show(vbox);

      // static hbox containing guitarix port names
      GtkWidget* hbox = gtk_hbox_new(FALSE, 2);
      for (int i = gx_jack::kAudioInput; i <= gx_jack::kAudioOutput2; i++)
        {
          string pname =
            gx_jack::client_name + string(" : ") +
            gx_jack::gx_port_names[i];

          GtkWidget* label = gtk_label_new(pname.c_str());
          gtk_box_pack_start(GTK_BOX(hbox), label, TRUE, FALSE, 2);
          gtk_widget_show(label);
        }

      gtk_widget_show(hbox);
      gtk_box_pack_start(GTK_BOX(vbox), hbox,   FALSE, FALSE, 2);

      // add seperator
      GtkWidget* sep = gtk_hseparator_new();
      gtk_box_pack_start(GTK_BOX(vbox), sep, FALSE, FALSE, 0);
      gtk_widget_show(sep);

      // notebook
      GtkWidget* nb = gtk_notebook_new();
      gtk_notebook_set_scrollable(GTK_NOTEBOOK(nb), TRUE);

      fPortMapTabs = GTK_NOTEBOOK(nb);

      // scrolled window
      GtkWidget* scrlwd = gtk_scrolled_window_new(NULL, NULL);
      gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrlwd),
                                     GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
      gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrlwd),
                                          GTK_SHADOW_IN);

      gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrlwd), nb);
      gtk_widget_show(nb);
      gtk_widget_show(scrlwd);

      // add scrolled window in vbox
      gtk_box_pack_start(GTK_BOX(vbox), scrlwd, TRUE, TRUE, 2);

      // main window
      GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
      gtk_window_set_title(GTK_WINDOW (window), label);
      gtk_window_set_transient_for(GTK_WINDOW(window), GTK_WINDOW(fWindow));
      gtk_window_set_destroy_with_parent(GTK_WINDOW(window), TRUE);
      gtk_window_add_accel_group(GTK_WINDOW(window), fAccelGroup);
      gtk_window_set_gravity(GTK_WINDOW(window), GDK_GRAVITY_NORTH_WEST);

      gtk_container_add(GTK_CONTAINER(window), vbox);
      gtk_widget_hide(window);

      fPortMapWindow = GTK_WINDOW(window);
    }

    void GxMainInterface::openHorizontalBox(const char* label)
    {
      GtkWidget * box = gtk_hbox_new (homogene, 0);
      gtk_container_set_border_width (GTK_CONTAINER (box), 0);

      if (fMode[fTop] != kTabMode && label[0] != 0)
        {
          GtkWidget * frame = addWidget(label, gtk_frame_new (label));
          gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_NONE);
          gtk_container_add (GTK_CONTAINER(frame), box);
          gtk_widget_show(box);
          pushBox(kBoxMode, box);
        }
      else
        {
          pushBox(kBoxMode, addWidget(label, box));
        }
    }

    void GxMainInterface::openHorizontalhideBox(const char* label)
    {
      GtkWidget * box = gtk_hbox_new (homogene, 0);
      gtk_container_set_border_width (GTK_CONTAINER (box), 0);
      // gtk_widget_set_size_request (box, 270, 75);
      if (fMode[fTop] != kTabMode && label[0] != 0)
        {
          GtkWidget * frame = addWidget(label, gtk_frame_new (label));
          gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_NONE);
          gtk_container_add (GTK_CONTAINER(frame), box);

          pushBox(kBoxMode, box);
          gtk_widget_hide(box);
        }
      else
        {

          pushBox(kBoxMode, addWidget(label, box));
          gtk_widget_hide(box);
        }
    }

    void GxMainInterface::openHorizontalTableBox(const char* label)
    {
      GtkWidget * box = gtk_hbox_new (TRUE, 0);
      gtk_container_set_border_width (GTK_CONTAINER (box), 0);

      if (fMode[fTop] != kTabMode && label[0] != 0)
        {
          GtkWidget * frame = addWidget(label, gtk_frame_new (label));
          gtk_frame_set_shadow_type(GTK_FRAME(frame),GTK_SHADOW_NONE);
          gtk_container_add (GTK_CONTAINER(frame), box);
          gtk_widget_show(box);
          pushBox(kBoxMode, box);
        }
      else
        {
          pushBox(kBoxMode, addWidget(label, box));
        }
    }



    struct uiOrderButton : public gx_ui::GxUiItem
      {
        GtkButton* 	fButton;
        uiOrderButton (gx_ui::GxUI* ui, float* zone, GtkButton* b) : gx_ui::GxUiItem(ui, zone), fButton(b) {}

        // box move to the right
        static void pressed_right( GtkWidget *widget, gpointer   data )
        {
          GtkWidget *box1 = gtk_widget_get_parent(GTK_WIDGET(widget));
          GtkWidget * box = gtk_widget_get_parent(GTK_WIDGET(box1));
          GtkWidget * parent = gtk_widget_get_parent(GTK_WIDGET(box));
          GValue  pos = {0};
          g_value_init (&pos, G_TYPE_INT);

          gtk_container_child_get_property(GTK_CONTAINER(parent),GTK_WIDGET(box),"position", &pos);
          guint per = g_value_get_int(&pos);
          if (per<7)
            {
              GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(parent));
              GtkWidget *obi = (GtkWidget *) g_list_nth_data(child_list,per+1);
              child_list =  gtk_container_get_children(GTK_CONTAINER(obi));
              GtkWidget *obib = (GtkWidget *) g_list_nth_data(child_list,1);
              child_list =  gtk_container_get_children(GTK_CONTAINER(obib));
              GtkWidget *obibi = (GtkWidget *) g_list_nth_data(child_list,0);

              gtk_box_reorder_child (GTK_BOX(parent),GTK_WIDGET(box),per +1);
              ((gx_ui::GxUiItem*)data)->modifyZone(per+1);
              gtk_button_clicked(GTK_BUTTON(obibi));

              g_list_free(child_list);
            }

        }
        // box move to the left
        static void pressed_left( GtkWidget *widget, gpointer   data )
        {

          GtkWidget *box1 = gtk_widget_get_parent(GTK_WIDGET(widget));
          GtkWidget * box = gtk_widget_get_parent(GTK_WIDGET(box1));
          GtkWidget * parent = gtk_widget_get_parent(GTK_WIDGET(box));
          GValue  pos = {0};
          g_value_init (&pos, G_TYPE_INT);

          gtk_container_child_get_property(GTK_CONTAINER(parent),GTK_WIDGET(box),"position", &pos);
          guint per = g_value_get_int(&pos);
          if (per>0)
            {
              GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(parent));
              GtkWidget *obi = (GtkWidget *) g_list_nth_data(child_list,per-1);
              child_list =  gtk_container_get_children(GTK_CONTAINER(obi));
              GtkWidget *obib = (GtkWidget *) g_list_nth_data(child_list,1);
              child_list =  gtk_container_get_children(GTK_CONTAINER(obib));
              GtkWidget *obibi = (GtkWidget *) g_list_nth_data(child_list,1);

              gtk_box_reorder_child (GTK_BOX(parent),GTK_WIDGET(box),per -1);
              ((gx_ui::GxUiItem*)data)->modifyZone(per-1);
              gtk_button_clicked(GTK_BUTTON(obibi));

              g_list_free(child_list);
            }


        }
        // resize the effect box
        static void resize( GtkWidget *widget, gpointer   data )
        {
          GtkWidget *box1 = gtk_widget_get_parent(GTK_WIDGET(widget));
          GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
          GtkWidget *parent = (GtkWidget *) g_list_nth_data(child_list,1);
          child_list =  gtk_container_get_children(GTK_CONTAINER(parent));
          box1 = (GtkWidget *) g_list_nth_data(child_list,0);
          child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
          box1 = (GtkWidget *) g_list_nth_data(child_list,0);
          child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
          box1 = (GtkWidget *) g_list_nth_data(child_list,0);
          child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
          box1 = (GtkWidget *) g_list_nth_data(child_list,0);
          child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
          box1 = (GtkWidget *) g_list_nth_data(child_list,0);
          g_list_free(child_list);

          int width, height;
          gtk_widget_get_size_request (parent, &width, &height);
          if (width!=-1)
            {
              gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(parent),GTK_POLICY_NEVER,GTK_POLICY_NEVER);
              gtk_widget_set_size_request (parent, -1, -1);
            }
          else
            {
              width= box1->allocation.width;
              gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(parent),GTK_POLICY_AUTOMATIC,GTK_POLICY_NEVER);
              gtk_widget_set_size_request (parent, width*5, -1);
            }
        }

        // save order for neigbor box
        static void clicked( GtkWidget *widget, gpointer   data )
        {
          GtkWidget *box1 = gtk_widget_get_parent(GTK_WIDGET(widget));
          GtkWidget * box = gtk_widget_get_parent(GTK_WIDGET(box1));
          GtkWidget * parent = gtk_widget_get_parent(GTK_WIDGET(box));
          GValue  pos = {0};
          g_value_init (&pos, G_TYPE_INT);

          gtk_container_child_get_property(GTK_CONTAINER(parent),GTK_WIDGET(box),"position", &pos);
          guint per = g_value_get_int(&pos);
          gtk_box_reorder_child (GTK_BOX(parent),GTK_WIDGET(box),per);

          ((gx_ui::GxUiItem*)data)->modifyZone(per);
        }
        // set the init order
        virtual void reflectZone()
        {

          float 	v = *fZone;
          fCache = v;
          GValue  pos = {0};

          g_value_init (&pos, G_TYPE_INT);
          g_value_set_int(&pos,(gint)fCache);

          GtkWidget *box1 = gtk_widget_get_parent(GTK_WIDGET(fButton));
          GtkWidget * box = gtk_widget_get_parent(GTK_WIDGET(box1));
          GtkWidget * parent = gtk_widget_get_parent(GTK_WIDGET(box));

          gtk_container_child_set_property(GTK_CONTAINER(parent),GTK_WIDGET(box),"position", &pos);
          guint per = g_value_get_int(&pos);
          gtk_box_reorder_child (GTK_BOX(parent),GTK_WIDGET(box),per);

        }
      };

    //----- boxes to move inside a other box
    void GxMainInterface::openHorizontalOrderBox(const char* label, float* posit)
    {
      GtkWidget * box = gtk_vbox_new (homogene, 0);
      GtkWidget * box1 = gtk_fixed_new ();
      gtk_container_set_border_width (GTK_CONTAINER (box), 0);
      g_signal_connect(box, "expose-event", G_CALLBACK(box9_expose), NULL);

      GtkWidget* 	button = gtk_button_new ();
      GtkWidget* 	button1 = gtk_button_new ();
      GtkWidget* lw = gtk_label_new(">");
      GtkWidget* lw1 = gtk_label_new("<");
      gtk_container_add (GTK_CONTAINER(button), lw);
      gtk_container_add (GTK_CONTAINER(button1), lw1);
      gtk_widget_set_size_request (GTK_WIDGET(button), 20.0, 15.0);
      gtk_widget_set_size_request (GTK_WIDGET(button1), 20.0, 15.0);

      gtk_widget_set_name (lw,"effekt_label");
      gtk_widget_set_name (lw1,"effekt_label");
      GtkStyle *style = gtk_widget_get_style(lw);
      pango_font_description_set_size(style->font_desc, 6*PANGO_SCALE);
      pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
      gtk_widget_modify_font(lw, style->font_desc);
      gtk_widget_modify_font(lw1, style->font_desc);

      uiOrderButton* c = new uiOrderButton(this, posit, GTK_BUTTON(button));

      g_signal_connect (box, "expose-event",
                        G_CALLBACK(box10_expose), NULL);
      g_signal_connect (GTK_OBJECT (button), "pressed",
                        G_CALLBACK (uiOrderButton::pressed_right), (gpointer) c);
      g_signal_connect (GTK_OBJECT (button1), "pressed",
                        G_CALLBACK (uiOrderButton::pressed_left), (gpointer) c);
      g_signal_connect (GTK_OBJECT (button), "clicked",
                        G_CALLBACK (uiOrderButton::clicked), (gpointer) c);
      g_signal_connect (GTK_OBJECT (button1), "clicked",
                        G_CALLBACK (uiOrderButton::clicked), (gpointer) c);


      gtk_box_pack_start (GTK_BOX(fBox[fTop]), box, expand, fill, 0);
      gtk_fixed_put (GTK_FIXED(box1), button1, 15, 1);
      gtk_fixed_put (GTK_FIXED(box1), button, 35, 1);
      gtk_box_pack_end (GTK_BOX(box), box1, expand, fill, 0);
      gtk_widget_show_all(button);
      gtk_widget_show_all(button1);
      gtk_widget_show(box);
      gtk_widget_show(box1);
      pushBox(kBoxMode, box);

    }

    void GxMainInterface::openHorizontalRestetBox(const char* label,float* posit)
    {
      GtkWidget * box = gtk_vbox_new (homogene, 0);
      g_signal_connect(box, "expose-event", G_CALLBACK(box9_expose), NULL);
      GtkWidget * box1 = gtk_fixed_new ();
      gtk_container_set_border_width (GTK_CONTAINER (box), 0);
      GtkWidget* 	button = gtk_button_new ();
      GtkWidget* lw = gtk_label_new("");
      gtk_container_add (GTK_CONTAINER(button), lw);

      gtk_widget_set_name (lw,"effekt_label");
      GtkStyle *style = gtk_widget_get_style(lw);
      pango_font_description_set_size(style->font_desc, 6*PANGO_SCALE);
      pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
      gtk_widget_modify_font(lw, style->font_desc);

      gtk_widget_set_size_request (GTK_WIDGET(button), 45.0, 15.0);

      uiOrderButton* c = new uiOrderButton(this, posit, GTK_BUTTON(button));


      g_signal_connect (GTK_OBJECT (button), "clicked",
                        G_CALLBACK (uiOrderButton::clicked), (gpointer) c);
      /***FIXME***/
      /*  g_signal_connect  (GTK_OBJECT (button), "pressed",
                          G_CALLBACK (gx_reset_effects), (gpointer) c); */

      gtk_box_pack_start (GTK_BOX(fBox[fTop]), box, expand, fill, 0);
      gtk_fixed_put (GTK_FIXED(box1), button, 10, 1);
      gtk_box_pack_end (GTK_BOX(box), box1, expand, fill, 0);

      gtk_widget_show_all(button);
      gtk_widget_show(box);
      gtk_widget_show(box1);
      pushBox(kBoxMode, box);

    }

    void GxMainInterface::openHandleBox(const char* label)
    {
      GtkWidget * box = gtk_hbox_new (homogene, 4);
      gtk_container_set_border_width (GTK_CONTAINER (box), 2);
      if (fMode[fTop] != kTabMode && label[0] != 0)
        {
          GtkWidget * frame = addWidget(label, gtk_handle_box_new ());
          gtk_container_add (GTK_CONTAINER(frame), box);
          gtk_widget_show(box);
          pushBox(kBoxMode, box);
        }
      else
        {
          pushBox(kBoxMode, addWidget(label, box));
        }
    }

    void GxMainInterface::openEventBox(const char* label)
    {
      GtkWidget * box = gtk_hbox_new (homogene, 4);

      gtk_container_set_border_width (GTK_CONTAINER (box), 2);
      if (fMode[fTop] != kTabMode && label[0] != 0)
        {
          GtkWidget * e_box =  gtk_event_box_new ();
          GtkWidget * frame = addWidget(label, e_box);
          gtk_widget_set_name (e_box,"osc_box");
          gtk_container_add (GTK_CONTAINER(frame), box);
          gtk_widget_show(box);
          pushBox(kBoxMode, box);
        }
      else
        {
          pushBox(kBoxMode, addWidget(label, box));
        }
    }

    struct uiExpanderBox : public gx_ui::GxUiItem
      {
        GtkExpander* fButton;
        uiExpanderBox(gx_ui::GxUI* ui, float* zone, GtkExpander* b) : gx_ui::GxUiItem(ui, zone), fButton(b) {}
        static void expanded (GtkWidget *widget, gpointer data)
        {
          float v = gtk_expander_get_expanded  (GTK_EXPANDER(widget));

          if (v == 1.000000)
            v = 0;
          else v = 1;

          ((gx_ui::GxUiItem*)data)->modifyZone(v);
        }

        virtual void reflectZone()
        {
          float 	v = *fZone;
          fCache = v;
          gtk_expander_set_expanded(GTK_EXPANDER(fButton), v);
        }
      };

    void GxMainInterface::openExpanderBox(const char* label, float* zone)
    {
      *zone = 0.0;
      GtkWidget * box = gtk_hbox_new (homogene, 0);
      gtk_container_set_border_width (GTK_CONTAINER (box), 0);
      if (fMode[fTop] != kTabMode && label[0] != 0)
        {
          GtkWidget * frame = addWidget(label, gtk_expander_new (label));
          gtk_container_add (GTK_CONTAINER(frame), box);
          uiExpanderBox* c = new uiExpanderBox(this, zone, GTK_EXPANDER(frame));
          g_signal_connect (GTK_OBJECT (frame), "activate", G_CALLBACK (uiExpanderBox::expanded), (gpointer)c);
          gtk_widget_show(box);
          pushBox(kBoxMode, box);
        }
      else
        {
          pushBox(kBoxMode, addWidget(label, box));
        }
    }

    void GxMainInterface::openVerticalBox(const char* label)
    {
      GtkWidget * box = gtk_vbox_new (homogene, 0);
      gtk_container_set_border_width (GTK_CONTAINER (box), 0);
      g_signal_connect(box, "expose-event", G_CALLBACK(box10_expose), NULL);

      if (fMode[fTop] != kTabMode && label[0] != 0)
        {
          GtkWidget* lw = gtk_label_new(label);


          gtk_widget_set_name (lw,"beffekt_label");
          GtkStyle *style = gtk_widget_get_style(lw);
          pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
          pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
          gtk_widget_modify_font(lw, style->font_desc);

          gtk_container_add (GTK_CONTAINER(box), lw);
          gtk_box_pack_start (GTK_BOX(fBox[fTop]), box, expand, fill, 0);
          gtk_widget_show(lw);
          gtk_widget_show(box);
          pushBox(kBoxMode, box);
        }
      else
        {
          pushBox(kBoxMode, addWidget(label, box));
        }
    }

    void GxMainInterface::openPaintBox(const char* label)
    {
      GtkWidget * box = gtk_vbox_new (homogene, 2);
      gtk_container_set_border_width (GTK_CONTAINER (box), 4);
      g_signal_connect(box, "expose-event", G_CALLBACK(box12_expose), NULL);

      if (fMode[fTop] != kTabMode && label[0] != 0)
        {
          gtk_box_pack_start (GTK_BOX(fBox[fTop]), box, expand, fill, 0);
          gtk_widget_show(box);
          pushBox(kBoxMode, box);
        }
      else
        {
          pushBox(kBoxMode, addWidget(label, box));
        }
    }

    void GxMainInterface::openPaintBox1(const char* label)
    {
      GtkWidget * box = gtk_vbox_new (homogene, 2);
      gtk_container_set_border_width (GTK_CONTAINER (box), 8);
      g_signal_connect(box, "expose-event", G_CALLBACK(box_expose), NULL);

      if (fMode[fTop] != kTabMode && label[0] != 0)
        {
          gtk_box_pack_start (GTK_BOX(fBox[fTop]), box, expand, fill, 0);
          gtk_widget_show(box);
          pushBox(kBoxMode, box);
        }
      else
        {
          pushBox(kBoxMode, addWidget(label, box));
        }
    }

    void GxMainInterface::openPaintBox2(const char* label)
    {
      GtkWidget * box = gtk_vbox_new (homogene, 2);
      gtk_container_set_border_width (GTK_CONTAINER (box), 2);
      g_signal_connect(box, "expose-event", G_CALLBACK(box2_expose), NULL);

      if (fMode[fTop] != kTabMode && label[0] != 0)
        {
          gtk_box_pack_start (GTK_BOX(fBox[fTop]), box, expand, fill, 0);
          gtk_widget_show(box);
          pushBox(kBoxMode, box);
        }
      else
        {
          pushBox(kBoxMode, addWidget(label, box));
        }
    }

    void GxMainInterface::openVerticalBox1(const char* label)
    {
      GtkWidget * box = gtk_vbox_new (homogene, 0);
      gtk_container_set_border_width (GTK_CONTAINER (box), 0);
      if (fMode[fTop] != kTabMode && label[0] != 0)
        {
          GtkWidget* lw = gtk_label_new(label);

          gtk_widget_set_name (lw,"effekt_label");
          GtkStyle *style = gtk_widget_get_style(lw);
          pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
          pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
          gtk_widget_modify_font(lw, style->font_desc);
          gtk_container_add (GTK_CONTAINER(box), lw);
          gtk_box_pack_start (GTK_BOX(fBox[fTop]), box, expand, fill, 0);
          gtk_widget_show(lw);
          gtk_widget_show(box);
          pushBox(kBoxMode, box);
        }
      else
        {
          pushBox(kBoxMode, addWidget(label, box));
        }
    }

    void GxMainInterface::openVerticalMidiBox(const char* label)
    {
      midibox = gtk_vbox_new (homogene, 4);
      gtk_container_set_border_width (GTK_CONTAINER (midibox), 2);
      if (fMode[fTop] != kTabMode && label[0] != 0)
        {
          GtkWidget * frame = addWidget(label, gtk_frame_new (label));
          gtk_container_add (GTK_CONTAINER(frame), midibox);
          gtk_widget_show(midibox);
          pushBox(kBoxMode, midibox);
        }
      else
        {
          pushBox(kBoxMode, addWidget(label, midibox));
        }
      gtk_widget_hide(midibox);
    }

    void GxMainInterface::openToolBar(const char* label)
    {
      GtkWidget * box = gtk_toolbar_new  ();


      if (fMode[fTop] != kTabMode && label[0] != 0)
        {
          GtkWidget* lw = gtk_label_new(label);

          gtk_widget_set_name (lw,"effekt_label");
          GtkStyle *style = gtk_widget_get_style(lw);
          pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
          pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
          gtk_widget_modify_font(lw, style->font_desc);
          gtk_container_add (GTK_CONTAINER(box), lw);
          gtk_box_pack_start (GTK_BOX(fBox[fTop]), box, expand, fill, 0);
          gtk_widget_show(lw);
          gtk_widget_show(box);
          pushBox(kBoxMode, box);
        }
      else
        {
          pushBox(kBoxMode, addWidget(label, box));
        }
    }

    void GxMainInterface::openScrollBox(const char* label)
    {
      GtkWidget * scrollbox = gtk_scrolled_window_new(NULL,NULL);
      gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrollbox),GTK_POLICY_AUTOMATIC,GTK_POLICY_NEVER);
      gtk_widget_set_size_request (scrollbox, 338, -1);
      GtkWidget * box = gtk_vbox_new (homogene, 0);
      GtkWidget * box1 = gtk_hbox_new (homogene, 0);
      gtk_container_set_border_width (GTK_CONTAINER (box), 0);
      g_signal_connect(box, "expose-event", G_CALLBACK(box4_expose), NULL);

      GtkWidget* 	button = gtk_button_new ();

      g_signal_connect (GTK_OBJECT (button), "clicked",
                        G_CALLBACK (uiOrderButton::resize), NULL);

      gtk_widget_set_size_request (GTK_WIDGET(button), 10.0, -1.0);
      gtk_container_add (GTK_CONTAINER(box1), button);
      gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrollbox),GTK_WIDGET(box));
      gtk_container_add (GTK_CONTAINER(box1), scrollbox);
      gtk_container_add (GTK_CONTAINER(fBox[fTop]), box1);
      gtk_widget_show_all(box1);
      pushBox(kBoxMode, box);

    }

    GtkWidget* GxMainInterface::addWidget(const char* label, GtkWidget* w)
    {
      switch (fMode[fTop])
        {
        case kSingleMode	:
          gtk_container_add (GTK_CONTAINER(fBox[fTop]), w);
          break;
        case kBoxMode 		:
          gtk_box_pack_start (GTK_BOX(fBox[fTop]), w, expand, fill, 0);
          break;
        case kTabMode 		:
          gtk_notebook_append_page (GTK_NOTEBOOK(fBox[fTop]), w, gtk_label_new(label));
          break;
        }
      gtk_widget_show (w);
      return w;
    }

    // --------------------------- Press button ---------------------------

    struct uiButton : public gx_ui::GxUiItem
      {
        GtkButton* 	fButton;
        uiButton (gx_ui::GxUI* ui, float* zone, GtkButton* b) : gx_ui::GxUiItem(ui, zone), fButton(b) {}
        static void pressed( GtkWidget *widget, gpointer   data )
        {
          gx_ui::GxUiItem* c = (gx_ui::GxUiItem*) data;
          c->modifyZone(1.0);
        }

        static void released( GtkWidget *widget, gpointer   data )
        {
          gx_ui::GxUiItem* c = (gx_ui::GxUiItem*) data;
          c->modifyZone(0.0);
        }

        virtual void reflectZone()
        {
          float 	v = *fZone;
          fCache = v;
          if (v > 0.0) gtk_button_pressed(fButton);
          else gtk_button_released(fButton);
        }
      };

    void GxMainInterface::addJConvButton(const char* label, float* zone)
    {
      *zone = 0.0;
      GtkWidget* 	button = gtk_button_new ();

      GtkWidget* 	lab = gtk_label_new(label);
      GtkStyle *style = gtk_widget_get_style(lab);
      pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
      pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
      gtk_widget_modify_font(lab, style->font_desc);
      gtk_container_add (GTK_CONTAINER(button), lab);

      gtk_widget_set_name (lab,"beffekt_label");
      addWidget(label, button);
      gtk_widget_show (lab);

      uiButton* c = new uiButton(this, zone, GTK_BUTTON(button));
      g_signal_connect (GTK_OBJECT (button), "clicked",
                        G_CALLBACK (gx_jconv::gx_show_jconv_dialog_gui),
                        (gpointer) c);

    }

    // ---------------------------	Toggle Buttons ---------------------------

    struct uiToggleButton : public gx_ui::GxUiItem
      {
        GtkToggleButton* fButton;
        uiToggleButton(gx_ui::GxUI* ui, float* zone, GtkToggleButton* b) : gx_ui::GxUiItem(ui, zone), fButton(b) {}
        static void toggled (GtkWidget *widget, gpointer data)
        {
          float	v = (GTK_TOGGLE_BUTTON (widget)->active) ? 1.0 : 0.0;
          ((gx_ui::GxUiItem*)data)->modifyZone(v);
        }

        virtual void reflectZone()
        {
          float v = *fZone;
          fCache = v;
          gtk_toggle_button_set_active(fButton, v > 0.0);
        }
      };

    void GxMainInterface::addToggleButton(const char* label, float* zone)
    {
      GdkColor colorRed;
      GdkColor colorOwn;
      gdk_color_parse ("#d56161", &colorRed);
      gdk_color_parse ("#7f7f7f", &colorOwn);
      float local_zone = 0.0;
      if (zone) local_zone = *zone;
      GtkWidget* 	button = gtk_toggle_button_new();
      GtkWidget* 	lab = gtk_label_new(label);
      GtkStyle *style = gtk_widget_get_style(lab);
      pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
      pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
      gtk_widget_modify_font(lab, style->font_desc);
      gtk_container_add (GTK_CONTAINER(button), lab);

      gtk_widget_set_name (lab,"beffekt_label");
      addWidget(label, button);

      gtk_widget_modify_bg (button, GTK_STATE_NORMAL, &colorOwn);
      gtk_widget_modify_bg (button, GTK_STATE_ACTIVE, &colorRed);

      g_signal_connect (GTK_OBJECT (button), "toggled", G_CALLBACK (gx_start_stop_jack_capture), NULL);
      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), FALSE);
      gtk_widget_add_accelerator(button, "activate", fAccelGroup, GDK_r, GDK_NO_MOD_MASK, GTK_ACCEL_VISIBLE);
      gtk_widget_show (lab);
      record_button = button;
    }

    void GxMainInterface::addPToggleButton(const char* label, float* zone)
    {
      GdkColor colorRed;
      GdkColor colorOwn;
      GdkColor colorwn;
      gdk_color_parse ("#58b45e", &colorRed);
      gdk_color_parse ("#000000", &colorwn);
      gdk_color_parse ("#7f7f7f", &colorOwn);
      *zone = 0.0;
      GtkWidget* 	button = gtk_toggle_button_new();
      GtkWidget* 	lab = gtk_label_new(label);
      GtkStyle *style = gtk_widget_get_style(lab);
      pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
      gtk_widget_modify_font(lab, style->font_desc);
      gtk_container_add (GTK_CONTAINER(button), lab);
      gtk_widget_set_size_request (GTK_WIDGET(button), 60.0, 20.0);
      GtkWidget * box = gtk_hbox_new (homogene, 4);
      GtkWidget * box1 = gtk_vbox_new (homogene, 4);
      gtk_container_set_border_width (GTK_CONTAINER (box), 0);
      gtk_container_set_border_width (GTK_CONTAINER (box1), 0);
      gtk_container_add (GTK_CONTAINER(box), box1);
      GtkWidget * box2 = gtk_vbox_new (homogene, 4);
      gtk_container_set_border_width (GTK_CONTAINER (box2), 0);
      gtk_widget_set_size_request (GTK_WIDGET(box2), 6.0, 20.0);
      gtk_container_add (GTK_CONTAINER(box), button);
      gtk_container_add (GTK_CONTAINER(box), box2);
      gtk_widget_set_size_request (GTK_WIDGET(box1), 6.0, 20.0);
      gtk_widget_show (button);
      gtk_widget_show (box1);
      gtk_widget_show (box2);
      gtk_widget_show (lab);
      gtk_widget_show (box);
      gtk_container_add (GTK_CONTAINER(fBox[fTop]), box);
      uiToggleButton* c = new uiToggleButton(this, zone, GTK_TOGGLE_BUTTON(button));
      gtk_widget_modify_bg (button, GTK_STATE_NORMAL, &colorOwn);
      gtk_widget_modify_bg (button, GTK_STATE_ACTIVE, &colorRed);
      gtk_widget_set_name (lab,"beffekt_label");
      g_signal_connect (GTK_OBJECT (button), "toggled", G_CALLBACK (uiToggleButton::toggled), (gpointer) c);
    }

    void GxMainInterface::addJToggleButton(const char* label, float* zone)
    {
      GdkColor colorRed;
      GdkColor colorOwn;


      gdk_color_parse ("#58b45e", &colorRed);

      gdk_color_parse ("#7f7f7f", &colorOwn);

      *zone = 0.0;

      GtkWidget* 	button = gtk_toggle_button_new();
      GtkWidget* 	lab = gtk_label_new(label);
      gtk_widget_set_name (lab,"beffekt_label");
      GtkStyle *style = gtk_widget_get_style(lab);

      pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
      pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
      gtk_widget_modify_font(lab, style->font_desc);
      gtk_container_add (GTK_CONTAINER(button), lab);
      addWidget(label, button);
      gtk_widget_show (lab);

      uiToggleButton* c =
        new uiToggleButton(this, zone, GTK_TOGGLE_BUTTON(button));

      gtk_widget_modify_bg (button, GTK_STATE_NORMAL, &colorOwn);
      gtk_widget_modify_bg (button, GTK_STATE_ACTIVE, &colorRed);


      g_signal_connect (GTK_OBJECT (button), "toggled",
                        G_CALLBACK (uiToggleButton::toggled), (gpointer) c);

      g_signal_connect (GTK_OBJECT (button), "toggled",
                        G_CALLBACK (gx_child_process::gx_start_stop_jconv), (gpointer)c);
    }

    // ---------------------------	Check Button ---------------------------

    struct uiCheckButton : public gx_ui::GxUiItem
      {
        GtkToggleButton* fButton;
        uiCheckButton(gx_ui::GxUI* ui, float* zone, GtkToggleButton* b) : gx_ui::GxUiItem(ui, zone), fButton(b) {}
        static void toggled (GtkWidget *widget, gpointer data)
        {
          float	v = (GTK_TOGGLE_BUTTON (widget)->active) ? 1.0 : 0.0;
          ((gx_ui::GxUiItem*)data)->modifyZone(v);
        }

        virtual void reflectZone()
        {
          float 	v = *fZone;
          fCache = v;
          gtk_toggle_button_set_active(fButton, v > 0.0);
        }
      };

    void GxMainInterface::addCheckButton(const char* label, float* zone)
    {
      GdkColor   colorRed;
      GdkColor   colorOwn;
      GdkColor   colorba;
      gdk_color_parse ("#000000", &colorRed);
      gdk_color_parse ("#4c5159", &colorOwn);
      gdk_color_parse ("#c4c0c0", &colorba);
      GtkWidget* 	lab = gtk_label_new(label);
      GtkWidget* 	button = gtk_check_button_new ();
      gtk_container_add (GTK_CONTAINER(button), lab);
      addWidget(label, button);
      gtk_widget_modify_bg (button, GTK_STATE_PRELIGHT, &colorOwn);
      gtk_widget_modify_fg (button, GTK_STATE_PRELIGHT, &colorRed);
      gtk_widget_modify_text (button, GTK_STATE_NORMAL, &colorRed);
      gtk_widget_modify_base (button, GTK_STATE_NORMAL, &colorba);
      GtkStyle *style = gtk_widget_get_style(lab);
      pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
      pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
      gtk_widget_modify_font(lab, style->font_desc);
      uiCheckButton* c = new uiCheckButton(this, zone, GTK_TOGGLE_BUTTON(button));
      g_signal_connect (GTK_OBJECT (button), "toggled", G_CALLBACK(uiCheckButton::toggled), (gpointer) c);
      gtk_widget_show (lab);
    }

    // ---------------------------	Adjustmenty based widgets ---------------------------

    struct uiAdjustment : public gx_ui::GxUiItem
      {
        GtkAdjustment* fAdj;
        uiAdjustment(gx_ui::GxUI* ui, float* zone, GtkAdjustment* adj) : gx_ui::GxUiItem(ui, zone), fAdj(adj) {}
        static void changed (GtkWidget *widget, gpointer data)
        {
          float	v = GTK_ADJUSTMENT (widget)->value;
          ((gx_ui::GxUiItem*)data)->modifyZone(v);
        }

        virtual void reflectZone()
        {
          float 	v = *fZone;
          fCache = v;
          gtk_adjustment_set_value(fAdj, v);
        }
      };

    int precision(double n)
    {
      if (n < 0.009999) return 3;
      else if (n < 0.099999) return 2;
      else if (n < 0.999999) return 1;
      else return 0;
    }


    // -------------------------- Horizontal Slider -----------------------------------


    void GxMainInterface::addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
    {
      *zone = init;
      GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
      uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
      g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
      GtkRegler myGtkRegler;
      GtkWidget* slider = myGtkRegler.gtk_mini_slider_new_with_adjustment (GTK_ADJUSTMENT(adj));
      gtk_range_set_inverted (GTK_RANGE(slider), TRUE);
      addWidget(label, slider);
    }

    void GxMainInterface::addHorizontalWheel(const char* label, float* zone, float init, float min, float max, float step)
    {
      *zone = init;
      GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
      uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
      g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
      GtkRegler myGtkRegler;
      GtkWidget* slider = myGtkRegler.gtk_wheel_new_with_adjustment (GTK_ADJUSTMENT(adj));
      gtk_range_set_inverted (GTK_RANGE(slider), TRUE);
      addWidget(label, slider);
    }

    struct uiValueDisplay : public gx_ui::GxUiItem
      {
        GtkLabel* fLabel;
        int	fPrecision ;

        uiValueDisplay(gx_ui::GxUI* ui, float* zone, GtkLabel* label, int precision)
            : gx_ui::GxUiItem(ui, zone), fLabel(label), fPrecision(precision) {}

        virtual void reflectZone()
        {
          float v = *fZone;
          fCache = v;
          char s[64];
          if (fPrecision <= 0)
            snprintf(s, 63, "%d", int(v));

          else if (fPrecision > 3)
            snprintf(s, 63, "%f", v);

          else if (fPrecision == 1)
            {
              const char* format[] = {"%.1f", "%.2f", "%.3f"};
              snprintf(s, 63, format[1-1], v);
            }
          else if (fPrecision == 2)
            {
              const char* format[] = {"%.1f", "%.2f", "%.3f"};
              snprintf(s, 63, format[2-1], v);
            }
          else
            {
              const char* format[] = {"%.1f", "%.2f", "%.3f"};
              snprintf(s, 63, format[3-1], v);
            }
          gtk_label_set_text(fLabel, s);
        }
      };

    // -------------------------- Vertical Slider -----------------------------------

    void GxMainInterface::addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
    {
      *zone = init;
      GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
      uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
      g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
      GtkRegler myGtkRegler;
      GtkWidget* slider = myGtkRegler.gtk_eq_slider_new_with_adjustment (GTK_ADJUSTMENT(adj));
      gtk_range_set_inverted (GTK_RANGE(slider), TRUE);
      GtkWidget* lw = gtk_label_new("");

      gtk_widget_set_name (lw,"value_label");

      GtkStyle *style = gtk_widget_get_style(lw);
      pango_font_description_set_size(style->font_desc, 6*PANGO_SCALE);
      pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
      gtk_widget_modify_font(lw, style->font_desc);

      new uiValueDisplay(this, zone, GTK_LABEL(lw),precision(step));

      openVerticalBox1(label);
      addWidget(label, slider);
      addWidget(label, lw);
      closeBox();
    }


    void GxMainInterface::addregler(const char* label, float* zone, float init, float min, float max, float step)
    {
      *zone = init;
      GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
      uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
      g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
      GtkWidget* lw = gtk_label_new("");
      GtkWidget* lwl = gtk_label_new(label);
      gtk_widget_set_name (lw,"value_label");
      gtk_widget_set_name (lwl,"effekt_label");
      GtkStyle *style = gtk_widget_get_style(lw);
      pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
      pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
      gtk_widget_modify_font(lw, style->font_desc);
      gtk_widget_modify_font(lwl, style->font_desc);
      new uiValueDisplay(this, zone, GTK_LABEL(lw),precision(step));
      GtkRegler myGtkRegler;
      GtkWidget* slider = myGtkRegler.gtk_regler_new_with_adjustment(GTK_ADJUSTMENT(adj));
      gtk_range_set_inverted (GTK_RANGE(slider), TRUE);
      openVerticalBox("");
      addWidget(label, lwl);
      addWidget(label, slider);
      addWidget(label, lw);
      closeBox();
    }

    void GxMainInterface::addbigregler(const char* label, float* zone, float init, float min, float max, float step)
    {
      *zone = init;
      GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
      uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
      g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
      GtkWidget* lw = gtk_label_new("");
      GtkWidget* lwl = gtk_label_new(label);

      gtk_widget_set_name (lw,"value_label");
      gtk_widget_set_name (lwl,"effekt_label");

      GtkStyle *style = gtk_widget_get_style(lw);
      pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
      pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
      gtk_widget_modify_font(lw, style->font_desc);
      gtk_widget_modify_font(lwl, style->font_desc);

      new uiValueDisplay(this, zone, GTK_LABEL(lw),precision(step));
      GtkRegler myGtkRegler;
      GtkWidget* slider = myGtkRegler.gtk_big_regler_new_with_adjustment(GTK_ADJUSTMENT(adj));
      gtk_range_set_inverted (GTK_RANGE(slider), TRUE);
      openVerticalBox("");
      addWidget(label, lwl);
      addWidget(label, slider);
      addWidget(label, lw);
      closeBox();
    }

    void GxMainInterface::addslider(const char* label, float* zone, float init, float min, float max, float step)
    {
      *zone = init;
      GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
      uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
      g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
      GtkWidget* lw = gtk_label_new("");
      gtk_widget_set_name (lw,"value_label");

      GtkStyle *style = gtk_widget_get_style(lw);
      pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
      pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
      gtk_widget_modify_font(lw, style->font_desc);
      new uiValueDisplay(this, zone, GTK_LABEL(lw),precision(step));
      GtkRegler myGtkRegler;
      GtkWidget* slider = myGtkRegler.gtk_hslider_new_with_adjustment(GTK_ADJUSTMENT(adj));
      gtk_range_set_inverted (GTK_RANGE(slider), TRUE);
      openVerticalBox(label);
      addWidget(label, slider);
      addWidget(label, lw);

      closeBox();
    }

    void GxMainInterface::addtoggle(const char* label, int* zone)
    {
      GtkObject* adj = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
      uiAdjustment* c = new uiAdjustment(this,(float*) zone, GTK_ADJUSTMENT(adj));
      g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
      GtkRegler myGtkRegler;
      GtkWidget* slider = myGtkRegler.gtk_toggle_new_with_adjustment(GTK_ADJUSTMENT(adj));
      addWidget(label, slider);
    }

    void GxMainInterface::addbtoggle(const char* label, float* zone)
    {
      GtkObject* adj = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
      uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
      g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
      GtkRegler myGtkRegler;
      GtkWidget* slider = myGtkRegler.gtk_button_toggle_new_with_adjustment(GTK_ADJUSTMENT(adj));
      addWidget(label, slider);
    }

    void GxMainInterface::addswitch(const char* label, int* zone)
    {
      GtkObject* adj = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
      uiAdjustment* c = new uiAdjustment(this,(float*) zone, GTK_ADJUSTMENT(adj));
      g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
      GtkRegler myGtkRegler;
      GtkWidget* slider = myGtkRegler.gtk_switch_new_with_adjustment(GTK_ADJUSTMENT(adj));
      GtkWidget* lw = gtk_label_new(label);
      gtk_widget_set_name (lw,"effekt_label");

      GtkStyle *style = gtk_widget_get_style(lw);
      pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
      pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
      gtk_widget_modify_font(lw, style->font_desc);
      openVerticalBox("");
      string laba = label;
      if (laba !="")addWidget(label, lw);
      addWidget(label, slider);
      closeBox();
    }

    void GxMainInterface::addminiswitch(const char* label, int* zone)
    {
      GtkObject* adj = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
      uiAdjustment* c = new uiAdjustment(this,(float*) zone, GTK_ADJUSTMENT(adj));
      g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
      GtkRegler myGtkRegler;
      GtkWidget* slider = myGtkRegler.gtk_mini_toggle_new_with_adjustment(GTK_ADJUSTMENT(adj));
      GtkWidget* lw = gtk_label_new(label);
      gtk_widget_set_name (lw,"effekt_label");

      GtkStyle *style = gtk_widget_get_style(lw);
      pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
      pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
      gtk_widget_modify_font(lw, style->font_desc);
      openHorizontalBox("");
      addWidget(label, slider);
      addWidget(label, lw);
      closeBox();
    }

    void GxMainInterface::addminieqswitch(const char* label, int* zone)
    {
      GtkObject* adj = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
      uiAdjustment* c = new uiAdjustment(this,(float*) zone, GTK_ADJUSTMENT(adj));
      g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);


      GtkRegler myGtkRegler;
      GtkWidget* slider = myGtkRegler.gtk_mini_toggle_new_with_adjustment(GTK_ADJUSTMENT(adj));
      g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (gx_hide_eq), (gpointer) slider);
      GtkWidget* lw = gtk_label_new(label);
      gtk_widget_set_name (lw,"effekt_label");

      GtkStyle *style = gtk_widget_get_style(lw);
      pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
      pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
      gtk_widget_modify_font(lw, style->font_desc);
      openHorizontalBox("");
      addWidget(label, slider);
      addWidget(label, lw);
      closeBox();
    }

    void GxMainInterface::addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
    {
      *zone = init;
      GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
      uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
      g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
      GtkWidget* spinner = gtk_spin_button_new (GTK_ADJUSTMENT(adj), step, precision(step));
      openFrameBox(label);
      addWidget(label, spinner);
      closeBox();
    }

    void GxMainInterface::openWarningBox(const char* label, float* zone)
    {
      GtkWidget* 	button = gtk_check_button_new ();
      uiCheckButton* c = new uiCheckButton(this, zone, GTK_TOGGLE_BUTTON(button));
      g_signal_connect (GTK_OBJECT (button), "toggled", G_CALLBACK(uiCheckButton::toggled), (gpointer) c);
    }

    void GxMainInterface::setSkinBox(const char* label, float* zone)
    {
      GtkObject* adj = gtk_adjustment_new(99, 0, 100, 1, 10*1, 0);
      uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));

      g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
      g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (gx_set_skin),  (gpointer) c);
    }

    void GxMainInterface::openDialogBox(const char* label, float* zone)
    {
      GtkWidget * dialog = gtk_window_new (GTK_WINDOW_TOPLEVEL);
      gtk_window_set_decorated(GTK_WINDOW(dialog), TRUE);
      gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
      gtk_window_set_gravity(GTK_WINDOW(dialog), GDK_GRAVITY_SOUTH);
      gtk_window_set_transient_for (GTK_WINDOW(dialog), GTK_WINDOW(fWindow));
      gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);
      gtk_window_set_keep_below (GTK_WINDOW(dialog), FALSE);
      gtk_window_set_title (GTK_WINDOW (dialog), label);

      gtk_window_set_destroy_with_parent(GTK_WINDOW(dialog), TRUE);
      GtkWidget * box = gtk_hbox_new (homogene, 8);
      GtkWidget * box4 = gtk_vbox_new (homogene, 4);
      GtkWidget * box5 = gtk_hbox_new (homogene, 4);
      gtk_container_set_border_width (GTK_CONTAINER (box), 2);
      gtk_container_set_border_width (GTK_CONTAINER (box4), 8);
      g_signal_connect(box4, "expose-event", G_CALLBACK(box3_expose), NULL);
      GdkColor colorRed;
      GdkColor colorOwn;
      gdk_color_parse ("#000094", &colorRed);
      gdk_color_parse ("#7f7f7f", &colorOwn);
      *zone = 0.0;

      GtkObject* adj = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
      uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
      g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
      GtkRegler myGtkRegler;
      GtkWidget* button = myGtkRegler.gtk_button_toggle_new_with_adjustment(GTK_ADJUSTMENT(adj));

      GtkWidget * box3 = gtk_hbox_new (homogene, 0);
      gtk_container_set_border_width (GTK_CONTAINER (box3), 0);
      gtk_container_add (GTK_CONTAINER(box3), button);
      gtk_widget_show (button);
      gtk_widget_show (box3);
      gtk_container_add (GTK_CONTAINER(fBox[fTop]), box3);
      gtk_widget_modify_bg (button, GTK_STATE_NORMAL, &colorOwn);
      gtk_widget_modify_bg (button, GTK_STATE_ACTIVE, &colorRed);
      g_signal_connect (GTK_OBJECT (button), "value-changed", G_CALLBACK (gx_show_extended_settings), (gpointer) dialog);
      g_signal_connect_swapped (G_OBJECT (dialog), "delete_event", G_CALLBACK (gx_delete_event), (gpointer) button);
      GtkWidget * frame =  gtk_frame_new (label);
      GtkWidget* 	lab = gtk_label_new("reset");
      GtkWidget* 	button1 = gtk_button_new();
      gtk_container_add (GTK_CONTAINER(button1), lab);

      GtkStyle *style = gtk_widget_get_style(lab);
      pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
      pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
      gtk_widget_modify_font(lab, style->font_desc);

      gtk_container_add (GTK_CONTAINER(box5), frame);
      gtk_container_add (GTK_CONTAINER(box5), button1);
      g_signal_connect  (GTK_OBJECT (button1), "pressed", G_CALLBACK (gx_reset_units), (gpointer) dialog);
      gtk_container_add (GTK_CONTAINER(box4), box5);
      gtk_container_add (GTK_CONTAINER(box4), box);
      gtk_container_add (GTK_CONTAINER(dialog), box4);
      // gtk_widget_show(dialog);
      gtk_widget_show(lab);
      gtk_widget_show(frame);
      gtk_widget_show(button1);
      gtk_widget_show(box);
      gtk_widget_show(box4);
      gtk_widget_show(box5);
      pushBox(kBoxMode, box);
    }

    // ------------------------------ Num Display -----------------------------------

    struct uiNumDisplay : public gx_ui::GxUiItem
      {
        GtkWidget* fLabel;

        uiNumDisplay(gx_ui::GxUI* ui, float* zone, GtkWidget* label)
            : gx_ui::GxUiItem(ui, zone), fLabel(label) {}

        virtual void reflectZone()
        {
          float v = *fZone;
          fCache = v;
          char s[64];
          int vis = round(v);
          float scale = ((v-vis)-(-1.0))/(1.0-(-1.0));
          if ((scale <= 0.0) || (scale > 1.0)) scale = 0.0;
          vis += 9;
          const char* note[] = {"C ","C#","D ","D#","E ","F ","F#","G ","G#","A ","A#","B "};
          if (shownote == 1)
            {
              if ((vis>=0)&&(vis<=11)) snprintf(s, 63, "%s",  note[vis]);
              else if ((vis>=-24)&&(vis<=-13)) snprintf(s, 63, "%s", note[vis+24]);
              else if ((vis>=-12)&&(vis<=-1)) snprintf(s, 63, "%s", note[vis+12]);
              else if ((vis>=12)&&(vis<=23)) snprintf(s, 63, "%s", note[vis-12]);
              else if ((vis>=24)&&(vis<=35)) snprintf(s, 63,"%s", note[vis-24]);
              else if ((vis>=36)&&(vis<=47)) snprintf(s, 63,"%s", note[vis-36]);
              else
                {
                  snprintf(s, 63, "%s", "");
                  scale = 0.0;
                }
              if ((scale >= 0.0) && (scale < 1.0)) gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pb), scale);
              gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pb), s);
            }
          else if (shownote == 0)
            {
              gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pb), scale);
              snprintf(s, 63, "%s", "");
              gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pb), s);
              shownote = -1;
            }
        }
      };


    void GxMainInterface::addNumDisplay(const char* label, float* zone )
    {
      openVerticalBox(label);
      pb = gtk_progress_bar_new();
      gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(pb), GTK_PROGRESS_LEFT_TO_RIGHT);
      new uiNumDisplay(this, zone, GTK_WIDGET(pb));
      gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pb), label);
      gtk_widget_set_size_request(pb, 40.0, 20.0);
      GtkStyle *style = gtk_widget_get_style(pb);
      pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
      gtk_widget_modify_font(pb, style->font_desc);
      addWidget(label, pb);
      gtk_widget_hide(pb);
      closeBox();
    }

    struct uiStatusDisplay : public gx_ui::GxUiItem
      {
        GtkLabel* fLabel;
        int	fPrecision;

        uiStatusDisplay(gx_ui::GxUI* ui, float* zone, GtkLabel* label)
            : gx_ui::GxUiItem(ui, zone), fLabel(label) {}

        virtual void reflectZone()
        {
          float 	v = *fZone;
          fCache = v;
          if ((gx_engine::dsp::isMidiOn() == true) &&
              (gx_jack::jcpu_load < 65.0))
            {
              if (v > 0.0f) gtk_status_icon_set_from_pixbuf ( GTK_STATUS_ICON(status_icon), GDK_PIXBUF(ibm));
              else  gtk_status_icon_set_from_pixbuf ( GTK_STATUS_ICON(status_icon), GDK_PIXBUF(ib));
            }
          else if (gx_engine::dsp::isMidiOn() == false)
            {
              gtk_status_icon_set_from_pixbuf ( GTK_STATUS_ICON(status_icon), GDK_PIXBUF(ib));
            }
          else gtk_status_icon_set_from_pixbuf ( GTK_STATUS_ICON(status_icon), GDK_PIXBUF(ibr));
        }
      };

    void GxMainInterface::addStatusDisplay(const char* label, float* zone )
    {
      GtkWidget* lw = gtk_label_new("");
      new uiStatusDisplay(this, zone, GTK_LABEL(lw));
      openFrameBox(label);
      addWidget(label, lw);
      closeBox();
      gtk_widget_hide(lw);
    };

    void GxMainInterface::addLiveWaveDisplay(const char* label, float* zone , float* zone1)
    {
      GtkObject* adj = gtk_adjustment_new(0.0, -1.0, 1.0, 0.0009, 10*0.0009, 0);
      new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));

      livewa = gx_wave_live_view(zone,zone1,GTK_ADJUSTMENT(adj));
      GtkWidget * box      = gtk_vbox_new (false, 4);
      GtkWidget * e_box =  gtk_event_box_new ();
      g_signal_connect(box, "expose-event", G_CALLBACK(box1_expose), NULL);
      gtk_widget_set_size_request (box, 303, 82);
      gtk_widget_set_size_request (e_box, 280, 50);
      gtk_container_set_border_width (GTK_CONTAINER (box), 12);
      gtk_container_add (GTK_CONTAINER(e_box),livewa );
      gtk_container_add (GTK_CONTAINER(box),e_box );
      addWidget(label, box);
      gtk_widget_show(box);
      gtk_widget_hide(e_box);
      gtk_widget_hide(livewa);
    };

    //----------------------------- main menu ----------------------------
    void GxMainInterface::addMainMenu()
    {
      /*-- Declare the GTK Widgets used in the menu --*/
      GtkWidget* menucont;  // menu container
      GtkWidget* menupix;  // menu container
      GtkWidget* hbox;      // top menu bar box container

      /*------------------ TOP Menu BAR ------------------*/
      hbox = gtk_hbox_new(FALSE, 0);

      /*-- Create the menu bar --*/
      menucont = gtk_menu_bar_new();
      gtk_box_pack_start(GTK_BOX(hbox), menucont, TRUE, TRUE, 0);

      /*-- Create the pixmap menu bar --*/
      menupix = gtk_menu_bar_new();
      gtk_box_pack_end(GTK_BOX(hbox), menupix, TRUE, TRUE, 0);

      /*-- set packdirection for pixmaps from right to left --*/
      gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(menupix),GTK_PACK_DIRECTION_RTL);

      /*-- Engine on/off and status --*/
      // set up ON image: shown by default
      string img_path = gx_pixmap_dir + "gx_on.png";

      gx_engine_on_image =  gtk_image_menu_item_new_with_label("");
      GtkWidget* engineon = gtk_image_new_from_file(img_path.c_str());
      gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(gx_engine_on_image),engineon);
      gtk_menu_bar_append (GTK_MENU_BAR(menupix), gx_engine_on_image);
      GtkTooltips* comandlin = gtk_tooltips_new ();

      gtk_tooltips_set_tip(GTK_TOOLTIPS (comandlin),
                           gx_engine_on_image, "engine is on", "engine state.");
      gtk_widget_show(gx_engine_on_image);

      // set up OFF image: hidden by default
      img_path = gx_pixmap_dir + "gx_off.png";

      gx_engine_off_image =  gtk_image_menu_item_new_with_label("");
      GtkWidget* engineoff = gtk_image_new_from_file(img_path.c_str());
      gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(gx_engine_off_image),engineoff);
      gtk_menu_bar_append (GTK_MENU_BAR(menupix), gx_engine_off_image);
      gtk_tooltips_set_tip(GTK_TOOLTIPS (comandlin),
                           gx_engine_off_image, "engine is off", "engine state.");
      gtk_widget_hide(gx_engine_off_image);

      // set up BYPASS image: hidden by default
      img_path = gx_pixmap_dir + "gx_bypass.png";

      gx_engine_bypass_image  =  gtk_image_menu_item_new_with_label("");
      GtkWidget* engineby = gtk_image_new_from_file(img_path.c_str());
      gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(gx_engine_bypass_image),engineby);
      gtk_menu_bar_append (GTK_MENU_BAR(menupix), gx_engine_bypass_image);
      gtk_tooltips_set_tip(GTK_TOOLTIPS (comandlin),
                           gx_engine_bypass_image, "engine is in bypass mode", "engine state.");
      gtk_widget_hide(gx_engine_bypass_image);


      /*-- Jack server status image --*/
      // jackd ON image
      img_path = gx_pixmap_dir + "jackd_on.png";

      gx_jackd_on_image =  gtk_image_menu_item_new_with_label("");
      GtkWidget*   jackstateon = gtk_image_new_from_file(img_path.c_str());
      gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(gx_jackd_on_image),jackstateon);
      gtk_menu_bar_append (GTK_MENU_BAR(menupix), gx_jackd_on_image);

      GtkTooltips* comandline = gtk_tooltips_new ();

      gtk_tooltips_set_tip(GTK_TOOLTIPS (comandline),
                           gx_jackd_on_image, "jack server is connectet", "jack server state.");

      gtk_widget_show(gx_jackd_on_image);

      // jackd OFF image: hidden by default
      img_path = gx_pixmap_dir + "jackd_off.png";

      gx_jackd_off_image =  gtk_image_menu_item_new_with_label("");
      GtkWidget*   jackstateoff = gtk_image_new_from_file(img_path.c_str());
      gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(gx_jackd_off_image),jackstateoff);
      gtk_menu_bar_append (GTK_MENU_BAR(menupix), gx_jackd_off_image);
      gtk_tooltips_set_tip(GTK_TOOLTIPS (comandline),
                           gx_jackd_off_image, "jack server is unconnectet", "jack server state.");
      gtk_widget_hide(gx_jackd_off_image);


      /* ----------------------------------------------------------- */
      fMenuList["Top"] = menucont;

      addEngineMenu();
      addPresetMenu();
      addOptionMenu();
      addAboutMenu();

      /*---------------- add menu to main window box----------------*/
      gtk_box_pack_start (GTK_BOX (fBox[fTop]), hbox , FALSE, FALSE, 0);
      gtk_widget_show(menucont);
      gtk_widget_show(menupix);
      gtk_widget_show(hbox);
    }

    //----------------------------- engine menu ----------------------------
    void GxMainInterface::addEngineMenu()
    {
      GtkWidget* menulabel;   // menu label
      //GtkWidget* menucont;    // menu container use menuh for systray menu here
      GtkWidget* menuitem;    // menu item
      GSList   * group = NULL;

      /*---------------- Create Engine menu items ------------------*/
      menuh = fMenuList["Top"];

      menulabel = gtk_menu_item_new_with_mnemonic ("_Engine");
      gtk_menu_bar_append (GTK_MENU_BAR(menuh), menulabel);
      gtk_widget_show(menulabel);

      /*-- Create Engine submenu  --*/
      menuh = gtk_menu_new();
      gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menuh);
      gtk_widget_show(menuh);
      fMenuList["Engine"] = menuh;

      /*-- Create Engine start / stop item  --*/
      group = NULL;

      menuitem = gtk_check_menu_item_new_with_mnemonic ("Engine _Start / _Stop");
      gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
                                 GDK_space, GDK_NO_MOD_MASK, GTK_ACCEL_VISIBLE);

      gtk_menu_shell_append(GTK_MENU_SHELL(menuh), menuitem);
      gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), TRUE);
      g_signal_connect (GTK_OBJECT (menuitem), "activate",
                        G_CALLBACK (gx_engine_switch), (gpointer)0);
      gx_engine_item = menuitem; // save into global var
      gtk_widget_show (menuitem);

      /*-- Create Engine bypass item  --*/
      menuitem = gtk_menu_item_new_with_mnemonic ("Engine _Bypass");
      gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
                                 GDK_b, GDK_NO_MOD_MASK, GTK_ACCEL_VISIBLE);

      gtk_menu_shell_append(GTK_MENU_SHELL(menuh), menuitem);
      g_signal_connect (GTK_OBJECT (menuitem), "activate",
                        G_CALLBACK (gx_engine_switch), (gpointer)1);
      gtk_widget_show (menuitem);

      /*-- add a separator line --*/
      GtkWidget* sep = gtk_separator_menu_item_new();
      gtk_menu_shell_append(GTK_MENU_SHELL(menuh), sep);
      gtk_widget_show (sep);

      /*---------------- Create Jack Server menu --------------------*/
      addJackServerMenu();

      /*---------------- End Jack server menu declarations ----------------*/

      /*-- add a separator line --*/
      sep = gtk_separator_menu_item_new();
      gtk_menu_shell_append(GTK_MENU_SHELL(menuh), sep);
      gtk_widget_show (sep);

      /*-- Create Open check menu item under Engine submenu --*/
      menuitem = gtk_check_menu_item_new_with_mnemonic ("_Midi Out ");
      gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
                                 GDK_m, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
      g_signal_connect (GTK_OBJECT (menuitem), "activate",
                        G_CALLBACK (gx_midi_out), NULL);
      gtk_menu_shell_append(GTK_MENU_SHELL(menuh), menuitem);
      gtk_widget_show (menuitem);

      /*-- add a separator line --*/
      sep = gtk_separator_menu_item_new();
      gtk_menu_shell_append(GTK_MENU_SHELL(menuh), sep);
      gtk_widget_show (sep);

      /*-- Create Exit menu item under Engine submenu --*/
      menuitem = gtk_menu_item_new_with_mnemonic ("_Quit");
      gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
                                 GDK_q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
      g_signal_connect(G_OBJECT (menuitem), "activate",
                       G_CALLBACK (gx_clean_exit), NULL);
      gtk_menu_shell_append(GTK_MENU_SHELL(menuh), menuitem);
      gtk_widget_show (menuitem);

      /*---------------- End Engine menu declarations ----------------*/
    }

    //----------------------------- preset menu ----------------------------
    void GxMainInterface::addPresetMenu()
    {
      GtkWidget* menulabel; // menu label
      GtkWidget* menucont;  // menu container
      GtkWidget* menuitem;  // menu item

      menucont = fMenuList["Top"];

      /*---------------- Create Presets menu items --------------------*/
      menulabel = gtk_menu_item_new_with_mnemonic ("_Presets");
      gtk_menu_bar_append (GTK_MENU_BAR(menucont), menulabel);
      gtk_widget_show(menulabel);

      /*-- Create Presets submenus --*/
      menucont = gtk_menu_new();
      gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menucont);
      gtk_widget_show(menucont);
      fMenuList["Presets"] = menucont;

      /* special treatment of preset lists, from gx_preset namespace */
      for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; i++)
        {
          GtkWidget* menuItem =
            gtk_menu_item_new_with_mnemonic (preset_menu_name[i]);
          gtk_menu_shell_append (GTK_MENU_SHELL(menucont), menuItem);

          GtkWidget* menu = gtk_menu_new();
          gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), menu);

          gtk_menu_set_accel_path(GTK_MENU(menu), preset_accel_path[i]);

          presmenu[i] = menu;
          presMenu[i] = menuItem;
        }


      /*-- add New Preset saving under Save Presets menu */
      menuitem = gtk_menu_item_new_with_mnemonic ("New _Preset");
      g_signal_connect (GTK_OBJECT (menuitem), "activate",
                        G_CALLBACK (gx_save_newpreset_dialog), NULL);
      gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
                                 GDK_p, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
      gtk_menu_shell_insert(GTK_MENU_SHELL(presmenu[SAVE_PRESET_LIST]), menuitem, 0);
      gtk_widget_show (menuitem);

      /*-- add a separator line --*/
      GtkWidget* sep = gtk_separator_menu_item_new();
      gtk_menu_shell_insert(GTK_MENU_SHELL(presmenu[SAVE_PRESET_LIST]), sep, 1);
      gtk_widget_show (sep);

      /*-- initial preset list --*/
      gx_preset::gx_build_preset_list();

      vector<string>::iterator it;
      for (it = gx_preset::plist.begin() ; it < gx_preset::plist.end(); it++ )
        {
          const string presname = *it;
          gx_add_preset_to_menus(presname);
        }

      for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; i++)
        gtk_widget_show(presMenu[i]);

      /* ------------------- */

      /*-- add a separator line --*/
      sep = gtk_separator_menu_item_new();
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), sep);
      gtk_widget_show (sep);

      /*-- Create  Main setting submenu --*/
      menuitem = gtk_menu_item_new_with_mnemonic ("Recall Main _Setting");
      g_signal_connect (GTK_OBJECT (menuitem), "activate",
                        G_CALLBACK (gx_recall_main_setting), NULL);
      gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
                                 GDK_s, GDK_NO_MOD_MASK, GTK_ACCEL_VISIBLE);
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
      gtk_widget_show (menuitem);

      menuitem = gtk_menu_item_new_with_mnemonic ("_Save As Main _Setting");
      g_signal_connect (GTK_OBJECT (menuitem), "activate",
                        G_CALLBACK (gx_save_main_setting), NULL);
      gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
                                 GDK_s, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
      gtk_widget_show (menuitem);


      /*-- add a separator line --*/
      sep = gtk_separator_menu_item_new();
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), sep);
      gtk_widget_show (sep);

      /*-- Create sub menu More Preset Action --*/
      menulabel = gtk_menu_item_new_with_mnemonic("More Preset Options...");
      gtk_menu_shell_append (GTK_MENU_SHELL(menucont), menulabel);
      gtk_widget_show(menulabel);

      menucont = gtk_menu_new();
      gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menucont);
      gtk_widget_show(menucont);
      fMenuList["ExtraPresets"] = menucont;

      /*--------------- Extra preset menu */
      addExtraPresetMenu();
    }


    //------------------------ extra preset menu ----------------------------
    void GxMainInterface::addExtraPresetMenu()
    {
      GtkWidget* menucont;  // menu container
      GtkWidget* menuitem;  // menu item

      menucont = fMenuList["ExtraPresets"];

      /*---------------- Create Presets menu items --------------------*/

      /* forward preset */
      menuitem = gtk_menu_item_new_with_mnemonic("Next _Preset");
      g_signal_connect (GTK_OBJECT (menuitem), "activate",
                        G_CALLBACK (gx_next_preset), NULL);
      gtk_widget_add_accelerator(menuitem, "activate",
                                 fAccelGroup, GDK_Page_Down,
                                 GDK_NO_MOD_MASK, GTK_ACCEL_VISIBLE);
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
      gtk_widget_show(menuitem);

      /* rewind preset */
      menuitem = gtk_menu_item_new_with_mnemonic("Previous _Preset");
      g_signal_connect (GTK_OBJECT (menuitem), "activate",
                        G_CALLBACK (gx_previous_preset), NULL);
      gtk_widget_add_accelerator(menuitem, "activate",
                                 fAccelGroup, GDK_Page_Up,
                                 GDK_NO_MOD_MASK, GTK_ACCEL_VISIBLE);
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
      gtk_widget_show(menuitem);

      /*-- add a separator line --*/
      GtkWidget* sep = gtk_separator_menu_item_new();
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), sep);
      gtk_widget_show (sep);

      /*-- Create  menu item Delete Active preset --*/
      menuitem = gtk_menu_item_new_with_mnemonic ("_Save _Active Preset");
      g_signal_connect (GTK_OBJECT (menuitem), "activate",
                        G_CALLBACK (gx_save_oldpreset), (gpointer)1);
      gtk_widget_add_accelerator(menuitem, "activate",
                                 fAccelGroup, GDK_s,
                                 GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
      gtk_widget_show (menuitem);

      menuitem = gtk_menu_item_new_with_mnemonic ("_Rename _Active Preset");
      g_signal_connect (GTK_OBJECT (menuitem), "activate",
                        G_CALLBACK (gx_rename_active_preset_dialog), NULL);
      gtk_widget_add_accelerator(menuitem, "activate",
                                 fAccelGroup, GDK_r,
                                 GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
      gtk_widget_show (menuitem);

      menuitem = gtk_menu_item_new_with_mnemonic ("_Delete Active Preset");
      g_signal_connect (GTK_OBJECT (menuitem), "activate",
                        G_CALLBACK (gx_delete_active_preset_dialog), NULL);
      gtk_widget_add_accelerator(menuitem, "activate",
                                 fAccelGroup, GDK_Delete,
                                 GDK_NO_MOD_MASK, GTK_ACCEL_VISIBLE);
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
      gtk_widget_show (menuitem);

      /*-- add a separator line --*/
      sep = gtk_separator_menu_item_new();
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), sep);
      gtk_widget_show (sep);

      /*-- Create  menu item Delete All presets --*/
      menuitem = gtk_menu_item_new_with_mnemonic ("_Delete All Presets");
      g_signal_connect (GTK_OBJECT (menuitem), "activate",
                        G_CALLBACK (gx_delete_all_presets_dialog), NULL);
      gtk_widget_add_accelerator(menuitem, "activate",
                                 fAccelGroup, GDK_d,
                                 GdkModifierType(GDK_CONTROL_MASK|GDK_SHIFT_MASK), GTK_ACCEL_VISIBLE);
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
      gtk_widget_show (menuitem);

    }

    //----------------------------- option menu ----------------------------
    void GxMainInterface::addOptionMenu()
    {
      GtkWidget* menulabel; // menu label
      GtkWidget* menucont;  // menu container
      GtkWidget* menuitem;  // menu item

      menucont = fMenuList["Top"];

      /*---------------- Create Options menu items ------------------*/
      menulabel = gtk_menu_item_new_with_mnemonic ("_Options");
      gtk_menu_bar_append (GTK_MENU_BAR(menucont), menulabel);
      gtk_widget_show(menulabel);

      /*-- Create Options submenu  --*/
      menucont = gtk_menu_new();
      gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menucont);
      gtk_widget_show(menucont);
      fMenuList["Options"] = menucont;

      /*-- Create oscilloscope check menu item under Options submenu --*/
      menuitem = gtk_check_menu_item_new_with_mnemonic ("_Oscilloscope");
      gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
                                 GDK_o, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
      g_signal_connect (GTK_OBJECT (menuitem), "activate",
                        G_CALLBACK (gx_show_oscilloscope), NULL);
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
      gtk_widget_show (menuitem);

      /*-- Create tuner check menu item under Options submenu --*/
      menuitem = gtk_check_menu_item_new_with_mnemonic ("_Tuner");
      gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
                                 GDK_t, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
      g_signal_connect (GTK_OBJECT (menuitem), "activate",
                        G_CALLBACK (gx_tuner), NULL);
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
      gtk_widget_show (menuitem);

      /*-- Create log window check menu item under Options submenu --*/
      menuitem = gtk_check_menu_item_new_with_mnemonic ("Open/Close _Log message");
      gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
                                 GDK_l, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
      g_signal_connect (GTK_OBJECT (menuitem), "activate",
                        G_CALLBACK (gx_log_window), NULL);
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
      gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM (menuitem), FALSE);
      gtk_widget_show (menuitem);

      /*-- add a separator line --*/
      GtkWidget* sep = gtk_separator_menu_item_new();
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), sep);
      gtk_widget_show (sep);

      /*-- Create Open check menu item under Options submenu --*/
      menuitem = gtk_check_menu_item_new_with_mnemonic ("_Meterbridge");
      gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
                                 GDK_m, GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);
      g_signal_connect (GTK_OBJECT (menuitem), "activate",
                        G_CALLBACK (gx_start_stop_meterbridge), NULL);
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
      gtk_widget_show (menuitem);

      /*-- Create Open check menu item under Options submenu --*/
      menuitem = gtk_menu_item_new_with_mnemonic ("_Jack Capture Settings");
      gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
                                 GDK_j, GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
      g_signal_connect(GTK_OBJECT (menuitem), "activate",
                       G_CALLBACK (gx_child_process::gx_show_jack_capture_gui), NULL);
      gtk_widget_show (menuitem);

      /*-- add a separator line --*/
      sep = gtk_separator_menu_item_new();
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), sep);
      gtk_widget_show (sep);

      /*-- Create skin menu under Options submenu--*/
      addGuiSkinMenu();
    }


    //----------------------------- skin menu ----------------------------
    void GxMainInterface::addGuiSkinMenu()
    {
      GtkWidget* menulabel; // menu label
      GtkWidget* menucont;  // menu container
      GtkWidget* menuitem;  // menu item
      GSList   * group = NULL;

      menucont = fMenuList["Options"];

      /*---------------- Create skin menu items ------------------*/
      menulabel = gtk_menu_item_new_with_mnemonic ("_Skin...");
      gtk_menu_append (GTK_MENU(menucont), menulabel);
      gtk_widget_show(menulabel);

      menucont = gtk_menu_new();
      gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menucont);
      gtk_widget_show(menucont);
      fMenuList["Skin"] = menucont;

      /* Create black skin item under skin submenu --*/
      guint idx = 0;

      while (idx < skin_list.size())
        {
          menuitem =
            gtk_radio_menu_item_new_with_label (group, skin_list[idx].c_str());

          group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (menuitem));

          gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM (menuitem), FALSE);
          g_signal_connect (GTK_OBJECT (menuitem), "activate",
                            G_CALLBACK (gx_change_skin), GINT_TO_POINTER(idx));
          gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
          gtk_widget_show (menuitem);
          idx++;
        }

      menucont = fMenuList["Options"];

      menuitem = gtk_menu_item_new();
      gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
                                 GDK_s, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
      g_signal_connect (GTK_OBJECT (menuitem), "activate",
                        G_CALLBACK (gx_cycle_through_skin), NULL);
      gtk_menu_append (GTK_MENU(menucont), menuitem);
      gtk_widget_show (menuitem);

      /*-- End skin menu declarations --*/
    }

    //----------------------------- about menu ----------------------------
    void GxMainInterface::addAboutMenu()
    {
      GtkWidget* menulabel; // menu label
      GtkWidget* menucont;  // menu container
      GtkWidget* menuitem;  // menu item

      menucont = fMenuList["Top"];

      /*---------------- Start About menu declarations ----------------*/
      menulabel = gtk_menu_item_new_with_mnemonic ("_About");
      gtk_menu_bar_append (GTK_MENU_BAR(menucont), menulabel);
      gtk_widget_show(menulabel);

      /*-- Create About submenu --*/
      menucont = gtk_menu_new();
      gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menucont);

      /*-- Create About menu item under About submenu --*/
      menuitem = gtk_menu_item_new_with_mnemonic ("_About");
      gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
                                 GDK_a, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
      g_signal_connect(GTK_OBJECT (menuitem), "activate",
                       G_CALLBACK (gx_show_about), NULL);
      gtk_widget_show (menuitem);

      /*-- Create Help menu item under About submenu --*/
      menuitem = gtk_menu_item_new_with_mnemonic ("_Help");
      gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
                                 GDK_h, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
      //    g_signal_connect(GTK_OBJECT (menuitem), "activate", G_CALLBACK (gx_show_about), NULL);
      gtk_widget_show (menuitem);

      /*---------------- End About menu declarations ----------------*/
    }

    /*---------------- Jack Server Menu ----------------*/
    void GxMainInterface::addJackServerMenu()
    {
      GtkWidget* menulabel; // menu label
      GtkWidget* menucont;  // menu container
      GtkWidget* menuitem;  // menu item
      GSList   * group = NULL;

      menucont = fMenuList["Engine"];

      /*-- Create Jack Connection toggle button --*/
      menuitem = gtk_check_menu_item_new_with_mnemonic ("Jack Server _Connection ");
      gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
                                 GDK_c, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
      g_signal_connect (GTK_OBJECT (menuitem), "activate",
                        G_CALLBACK (gx_jack::gx_jack_connection), NULL);
      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);

      gtk_widget_show (menuitem);
      fJackConnectItem = menuitem;

      /*-- create Jack Ports menu item --*/
      menuitem = gtk_check_menu_item_new_with_mnemonic ("Jack _Ports ");
      gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
                                 GDK_p, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
      g_signal_connect (GTK_OBJECT (menuitem), "activate",
                        G_CALLBACK (gx_show_portmap_window), NULL);

      g_signal_connect_swapped(G_OBJECT(fPortMapWindow), "delete_event",
                               G_CALLBACK(gx_hide_portmap_window), menuitem);


      gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
      gtk_widget_show (menuitem);

      menucont = fMenuList["Engine"];

      /* add item for client tab cycling through */
      menuitem = gtk_menu_item_new_with_mnemonic("Next Client _Tab");
      gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
                                 GDK_t, GDK_NO_MOD_MASK, GTK_ACCEL_VISIBLE);
      g_signal_connect (GTK_OBJECT (menuitem), "activate",
                        G_CALLBACK (gx_cycle_through_client_tabs), NULL);
      gtk_menu_append (GTK_MENU_SHELL(menucont), menuitem);
      gtk_widget_show (menuitem);


      /*-- Create  Latency submenu under Jack Server submenu --*/
      menulabel = gtk_menu_item_new_with_mnemonic ("_Latency");
      gtk_menu_append (GTK_MENU(menucont), menulabel);
      gtk_widget_show(menulabel);

      menucont = gtk_menu_new();
      gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menucont);

      /*-- Create  menu item under Latency submenu --*/
      gchar buf_size[8];
      const int min_pow = 5;  // 2**5  = 32
      const int max_pow = 13; // 2**13 = 8192
      group = NULL;

      for (int i = min_pow; i <= max_pow; i++)
        {
          int jack_buffer_size = (int)pow(2.,i);
          (void)snprintf(buf_size, 5, "%d", jack_buffer_size);
          menuitem = gtk_radio_menu_item_new_with_label (group, buf_size);
          group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (menuitem));
          gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), FALSE);

          g_signal_connect (GTK_OBJECT (menuitem), "activate",
                            G_CALLBACK (gx_jack::gx_set_jack_buffer_size),
                            GINT_TO_POINTER(jack_buffer_size));

          // display actual buffer size as default
          gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
          gtk_widget_show (menuitem);

          fJackLatencyItem[i-min_pow] = menuitem;
        }
    }

    /* -------- init jack client menus ---------- */
    void GxMainInterface::initClientPortMaps()
    {
      // make sure everything is reset
      deleteAllClientPortMaps();

      gx_client_port_dequeue.clear();
      gx_client_port_queue.clear();

      // if jack down, no bother
      // (should not be called when jack is down anyway)
      if (!gx_jack::client)
        return;

      // get all existing port names (no MIDI stuff for now)
      const char** iportnames =
        jack_get_ports(gx_jack::client, NULL,
                       JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput);

      const char** oportnames =
        jack_get_ports(gx_jack::client, NULL,
                       JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput);

      // populating output port menus
      int p = 0;
      while (oportnames[p] != 0)
        {
          string pname = oportnames[p];
          if (pname.substr(0, pname.find(":")) != gx_jack::client_name)
            gx_client_port_queue.insert(pair<string, int>(pname, JackPortIsOutput));

          p++;
        }

      // populating input port menus
      p = 0;
      while (iportnames[p] != 0)
        {
          string pname = iportnames[p];
          if (pname.substr(0, pname.find(":")) != gx_jack::client_name)
            gx_client_port_queue.insert(pair<string, int>(pname, JackPortIsInput));
          p++;
        }

      // free port name lists (cf. JACK API doc)
      jack_free(iportnames);
      jack_free(oportnames);
    }

    /* -------- add  jack client item ---------- */
    void GxMainInterface::addClientPortMap(const string clname)
    {
      // no need to bother if are not a jack client
      if (gx_jack::client == NULL)
        {
          gx_print_warning("Jack Client", "Connect back to jack first");
          return;
        }

      // we don't want these guys here :)
      if (clname == gx_jack::client_name ||
          clname == "ardourprobe"        ||
          clname == "freewheel"          ||
          clname == "qjackctl"           ||
          clname == "Patchage")
        return;

      // add tab in client notebook if needed
      // Note: one-to-one mapping: only ONE tab per client
      if (getClientPortMap(clname))
        return;

      GtkWidget* label   = gtk_label_new(clname.c_str());

      GtkWidget* mapbox  = gtk_hbox_new(TRUE, 10);
      gtk_widget_set_name(mapbox, clname.c_str());

      for (int t = gx_jack::kAudioInput; t <= gx_jack::kAudioOutput2; t++)
        {
          GtkWidget* table  = gtk_vbox_new(FALSE, 0);
          gtk_box_pack_start(GTK_BOX(mapbox), table, TRUE, FALSE, 0);

          g_signal_connect(table, "expose-event", G_CALLBACK(box6_expose), NULL);
          gtk_widget_show(table);
        }

      gtk_notebook_append_page(fPortMapTabs, mapbox, label);
      gtk_widget_show(label);
      gtk_widget_show(mapbox);
      fClientPortMap.insert(mapbox);

      // move focus back to guitarix main window
      gtk_widget_grab_focus(fWindow);

      gx_print_info("Jack Client",  clname + " added to port map");
    }

    /* -------- add port to a given jack client portmap  ---------- */
    void GxMainInterface::addClientPorts()
    {

      // no need to bother if are not a jack client
      if (gx_jack::client == NULL)
        {
          gx_print_warning("Jack Client Port Add",
                           "we are not yet a jack client");
          gx_client_port_queue.clear();
          return;
        }

      // go through list
      multimap<string, int>::iterator pn;
      for (pn  = gx_client_port_queue.begin();
           pn != gx_client_port_queue.end();
           pn++)
        {
          string port_name = pn->first;

          // retrieve the client name from the port name
          string client_name = port_name.substr(0, port_name.find(':'));
          string short_name  = port_name.substr(port_name.find(':')+1);

          // if client portmap does not exist, create it
          if (!getClientPortMap(client_name))
            addClientPortMap(client_name);

          if (!getClientPortMap(client_name))
            continue;

          // port flags
          int flags          = pn->second;

          // set up how many port tables we should deal with:
          // 1 for guitarix input (mono)
          // 2 for guitarix outputs (stereo)

          int table_index = gx_jack::kAudioInput, ntables = 1;
          if ((flags & JackPortIsOutput) == 0)
            {
              table_index = gx_jack::kAudioOutput1;
              ntables = 2;
            }

          // add port item
          for (int i = table_index; i < table_index + ntables; i++)
            {
              // retrieve port table
              GtkVBox* portbox =
                GTK_VBOX(getClientPortTable(client_name, i));
              gtk_container_set_border_width (GTK_CONTAINER (portbox), 8);
              // create checkbutton
              GtkWidget* button =
                gtk_check_button_new_with_label(short_name.c_str());
              GtkWidget *button_text = gtk_bin_get_child(GTK_BIN(button));


              GdkColor colorGreen;
              GdkColor color1;
              GdkColor color2;
              gdk_color_parse("#000000", &colorGreen);
              gtk_widget_modify_fg (button_text, GTK_STATE_NORMAL, &colorGreen);
              gdk_color_parse("#292995", &color1);
              gtk_widget_modify_fg (button_text, GTK_STATE_ACTIVE, &color1);
              gdk_color_parse("#444444", &color2);
              gtk_widget_modify_fg (button_text, GTK_STATE_PRELIGHT, &color2);
              GtkStyle *style = gtk_widget_get_style(button_text);
              pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
              pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
              gtk_widget_modify_font(button_text, style->font_desc);

              gtk_widget_set_name(button,  (gchar*)port_name.c_str());
              gtk_box_pack_start(GTK_BOX(portbox), button, FALSE, FALSE, 0);
              g_signal_connect(GTK_OBJECT (button), "toggled",
                               G_CALLBACK (gx_jack::gx_jack_port_connect),
                               GINT_TO_POINTER(i));
              gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), FALSE);
              gtk_widget_show_all(button);
            }
        }

      // empty queue
      gx_client_port_queue.clear();

      // move focus back to guitarix main window
      gtk_widget_grab_focus(fWindow);
    }

    /* -------- delete port lists for a given jack client ---------- */
    void GxMainInterface::deleteClientPorts()

    {
      // no need to bother if are not a jack client
      if (gx_jack::client == NULL)
        {
          gx_print_warning("Jack Client Port Add",
                           "we are not yet a jack client");
          gx_client_port_dequeue.clear();
          return;
        }

      if (gx_client_port_dequeue.empty())
        return;

      // go through list
      string clname;

      multimap<string, int>::iterator pn;
      for (pn = gx_client_port_dequeue.begin(); pn != gx_client_port_dequeue.end(); pn++)
        {
          string port_name = pn->first;

          // delete port item to be displayed as a submenu if some ports exist
          clname = port_name.substr(0, port_name.find(':'));

          // check that portmap does exists, otherwise, no point
          if (!getClientPortMap(clname))
            break;

          // lookup port tables
          for (int l = 0; l < NUM_PORT_LISTS; l++)
            {
              GtkWidget* wd = getClientPort(port_name, l);
              if (wd)
                gtk_widget_destroy(wd);
            }
        }

      // we could delete the tab if needed
      bool mapempty = true;
      if (getClientPortMap(clname))
        {
          for (int l = 0; l < NUM_PORT_LISTS; l++)
            {
              GtkWidget* wd = getClientPortMap(clname);
              if (wd)
                {
                  GList* list =
                    gtk_container_get_children(GTK_CONTAINER(wd));

                  if (g_list_length(list) > 0)
                    {
                      mapempty = false;
                      g_list_free(list);
                      break;
                    }
                  g_list_free(list);
                }
            }
        }

      if (mapempty)
        deleteClientPortMap(clname);

      // empty queue
      gx_client_port_dequeue.clear();

      // move focus back to guitarix main window
      gtk_widget_grab_focus(fWindow);


    }

    /* -------- delete jack client item ---------- */
    void GxMainInterface::deleteClientPortMap(string clname)
    {
      // no need to delete it if nothing to delete
      GtkWidget* tab = getClientPortMap(clname);
      if (!tab)
        return;

      // remove it from our list
      fClientPortMap.erase(fClientPortMap.find(tab));

      // remove the notebook tab
      int page = gtk_notebook_page_num(fPortMapTabs, tab);
      gtk_notebook_remove_page(fPortMapTabs, page);

      // destroy the widget
      if (GTK_IS_WIDGET(tab))
        gtk_widget_destroy(tab);

      // move focus back to guitarix main window
      gtk_widget_grab_focus(fWindow);

      // print warning
      gx_print_warning("Jack Client Delete", clname + " portmap deleted");
    }

    /* -------- delete all jack client menus ---------- */
    void GxMainInterface::deleteAllClientPortMaps()
    {
      // don't do it if nothing to do
      if (fClientPortMap.empty())
        return;

      set<GtkWidget*>::iterator it;

      // all port maps deletion
      for (it = fClientPortMap.begin(); it != fClientPortMap.end(); it++)
        {
          GtkWidget* mapbox = *it;

          int page = gtk_notebook_page_num(fPortMapTabs, mapbox);
          gtk_notebook_remove_page(fPortMapTabs, page);

          if (GTK_IS_WIDGET(mapbox))
            gtk_widget_destroy(mapbox);
        }

      fClientPortMap.clear();

      // move focus back to guitarix main window
      gtk_widget_grab_focus(fWindow);

      // print warning
      gx_print_warning("Jack Client Delete All",
                       "All client portmaps have been deleted");
    }

    /* ---------------- retrieve a client port widget --------------- */
    GtkWidget* GxMainInterface::getClientPort(const string port_name,
        const int    tab_index)
    {

      // client name
      string clname = port_name.substr(0, port_name.find(':'));

      // get client port table
      GtkWidget* table = getClientPortTable(clname, tab_index);
      if (!table)
        return NULL;

      // get list of elements
      GList* list = gtk_container_get_children(GTK_CONTAINER(table));

      // retrieve element
      for (guint p = 0; p < g_list_length(list); p++)
        {
          GtkWidget* wd = (GtkWidget*)g_list_nth_data(list, p);
          if (port_name == gtk_widget_get_name(wd))
            {
              g_list_free(list);
              return wd;
            }
        }
      g_list_free(list);
      return NULL;
    }

    /* --------------- retrieve a client port table widget -------------- */
    GtkWidget* GxMainInterface::getClientPortTable(const string clname,
        const int    index)
    {

      // get port map
      GtkWidget* portmap = getClientPortMap(clname);
      if (!portmap)
        return NULL;

      // look up list of vboxes in portmap
      GList* list = gtk_container_get_children(GTK_CONTAINER(portmap));
      GtkWidget * glnd = (GtkWidget*)g_list_nth_data(list, index);
      g_list_free(list);
      return (GtkWidget*)glnd;
    }

    /* ----------------- retrieve a client portmap widget --------------- */
    GtkWidget* GxMainInterface::getClientPortMap(const string clname)
    {
      // try to find a match
      set<GtkWidget*>::iterator it;

      for (it = fClientPortMap.begin(); it != fClientPortMap.end(); it++)
        if (clname == gtk_widget_get_name(*it))
          return *it; // got it

      return NULL;
    }



    //---- show main GUI
    void GxMainInterface::show()
    {
      assert(fTop == 0);
      gx_init_pixmaps();
      fInitialized = true;

      if (gx_jack::client)
        {
          // refresh some GUI stuff
          gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(fJackConnectItem), TRUE);

          GtkWidget* wd = getJackLatencyItem(gx_jack::jack_bs);
          if (wd) gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(wd), TRUE);

          gtk_window_set_title(GTK_WINDOW(fWindow), gx_jack::client_name.c_str());

          // build port menus for existing jack clients
          initClientPortMaps();

        }
      else
        {
          gtk_widget_hide(gx_gui::gx_jackd_on_image);
          gtk_widget_show(gx_gui::gx_jackd_off_image);
        }


      gtk_widget_show  (fBox[0]);
      gtk_widget_show  (fWindow);
      gx_jconv::gx_setting_jconv_dialog_gui(NULL,NULL);
    }

    //---- show main GUI thread and more
    void GxMainInterface::run()
    {
      //  string previous_state = gx_user_dir + gx_jack::client_name + "rc";
      //  recallState(previous_state.c_str());

      //----- set the state for the latency change warning widget
      gx_engine::GxEngine::instance()->set_latency_warning_change();

      //----- set the last used skin when no cmd is given
      int skin_index = gx_current_skin;
      if (no_opt_skin == 1)
        skin_index = gx_engine::GxEngine::instance()->fskin;

      gx_set_skin_change(skin_index);
      gx_update_skin_menu_item(skin_index);


      /* timeout in milliseconds */
      g_timeout_add(40, gx_update_all_gui, 0);
      g_timeout_add_full(G_PRIORITY_DEFAULT_IDLE, 60,  gx_refresh_oscilloscope, 0, NULL);
      // g_timeout_add_full(G_PRIORITY_LOW,2000, gx_survive_jack_shutdown, 0, NULL);
      g_timeout_add_full(G_PRIORITY_LOW,2200, gx_monitor_jack_ports,0, NULL);
      g_timeout_add_full(G_PRIORITY_LOW,200, gx_refresh_tuner,0, NULL);
      g_timeout_add(750, gx_check_startup, 0);
      // Note: meter display timeout is a global var in gx_gui namespace
      g_timeout_add(meter_display_timeout, gx_refresh_meter_level,   0);

      // -------------- start helper thread for jack shutdown survive ------------
      sem_init (&jack_change_sem, 0, 0);
      GError* err = NULL;
      if (g_thread_create(gx_jack_change_helper_thread, NULL, FALSE, &err)  == NULL)
        {
          printf("Thread create failed: %s!!\n", err->message );
          g_error_free(err);
          err = NULL;
          //FIXME: abort program
        }

      // -------------- start helper thread for ladi signal USR1 ------------
      if (g_thread_create(gx_signal_helper_thread, NULL, FALSE, &err)  == NULL)
        {
          printf("Thread create failed: %s!!\n", err->message );
          g_error_free(err);
          err = NULL;
          //FIXME: abort program
        }

      // -------------- start helper thread for midi control ------------
      sem_init (&program_change_sem, 0, 0);

      if (g_thread_create(gx_program_change_helper_thread, NULL, FALSE, &err)  == NULL)
        {
          printf("Thread create failed: %s!!\n", err->message );
          g_error_free(err);
          err = NULL;
          //FIXME: abort program
        }

      gtk_main();
      gdk_threads_leave ();   // Add this line
      stop();
    }

  } /* end of gx_gui namespace */

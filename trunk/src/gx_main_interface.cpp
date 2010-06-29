/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
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
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstdio>

#include <array>
#include <zita-convolver.h>
#include <fftw3.h>
#include <zita-resampler.h>

#include <cassert>
#include <sigc++/sigc++.h>
#include <semaphore.h>

using namespace std;

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <jack/jack.h>
#include <sndfile.h>

#include "guitarix.h"

using namespace gx_system;
using namespace gx_child_process;
using namespace gx_preset;
using namespace gx_cairo;
using namespace gx_threads;

namespace gx_gui
{

/****************************************************************
 ** format controller values
 */

int precision(double n)
{
	if (n < 0.009999) return 3;
	else if (n < 0.099999) return 2;
	else if (n < 0.999999) return 1;
	else return 0;
}

string fformat(float value, float step)
{
	ostringstream buf;
	buf << fixed << setprecision(precision(step)) << value;
	return buf.str();
}

/****************************************************************
 ** GxMidiController definitions and connecting method
 */

#include "gx_main_midi.cc"

/****************************************************************
 ** GxMainInterface widget and method definitions
 */

// static member
bool GxMainInterface::fInitialized = false;
#ifndef NDEBUG
static pthread_t ui_thread;
#endif

GxMainInterface::GxMainInterface(const char * name, int* pargc, char*** pargv)
{
	highest_unseen_msg_level = -1;
	gtk_init(pargc, pargv);

	/*-- set rc file overwrite it with export--*/
	gtk_rc_parse(rcpath.c_str());

	/*-- Declare the GTK Widgets --*/
	fWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);

	/*---------------- set window defaults ----------------*/
	gtk_window_set_resizable(GTK_WINDOW (fWindow) , FALSE);
	gtk_window_set_title (GTK_WINDOW (fWindow), name);
	gtk_window_set_gravity(GTK_WINDOW(fWindow), GDK_GRAVITY_NORTH_WEST);

	/*---------------- singnals ----------------*/
	g_signal_connect (GTK_OBJECT (fWindow), "destroy",
	                  G_CALLBACK (gx_clean_exit), NULL);

	/*---------------- status icon ----------------*/
	if (gx_pixmap_check() == 0) {
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

/****************************************************************
 ** virtual GUI discriptions
 */

//------- retrieve jack latency menu item
GtkWidget* const
GxMainInterface::getJackLatencyItem(jack_nframes_t bufsize) const
{
	if (bufsize & (bufsize-1)) {
		return NULL; // not power of 2
	}
	const int minbuf = 5; // 2**5 = 32 //FIXME magic value
	int index = -(minbuf+1);
	while (bufsize) {
		bufsize >>= 1;
		index++;
	}
	if (index >= 0 && index < NJACKLAT) {
		return fJackLatencyItem[index];
	}
	return NULL;
}

//------- box stacking up
void GxMainInterface::pushBox(int mode, GtkWidget* w)
{
	++fTop;
	assert(fTop < stackSize);
	fMode[fTop] 	= mode;
	fBox[fTop] 		= w;
}

void GxMainInterface::closeBox()
{
	--fTop;
	assert(fTop >= 0);
}

//-------- different box styles
void GxMainInterface::openFrameBox(const char* label)
{
	GtkWidget * box = gtk_hbox_new (homogene, 2);
	gtk_container_set_border_width (GTK_CONTAINER (box), 2);
	g_signal_connect(box, "expose-event", G_CALLBACK(vbox_expose), NULL);
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

static void logging_set_color(GtkWidget *w, gpointer data)
{
	GxMainInterface *p = (GxMainInterface*)data;
	if (gtk_expander_get_expanded(GTK_EXPANDER(w)) == FALSE) {
		// expander will be opened
		p->highest_unseen_msg_level = kMessageTypeCount;
		p->set_logging_expander_color("#ffffff");
	} else {
		p->highest_unseen_msg_level = -1;
	}
}

void GxMainInterface::openTextLoggingBox(const char* label)
{
	GtkWidget* box = gtk_hbox_new (homogene, 0);
	gtk_container_set_border_width (GTK_CONTAINER (box), 0);

	GtkWidget * scrollbox = gtk_scrolled_window_new(NULL,NULL);
	fLoggingVAdjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scrollbox));
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrollbox),
	                                GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);

	GtkWidget* frame = addWidget(label, gtk_expander_new(label));
	gtk_container_add (GTK_CONTAINER(frame), box);
	gtk_widget_show(frame);
	gtk_expander_set_expanded(GTK_EXPANDER(frame), FALSE);
	fLoggingBox = GTK_EXPANDER(frame);

	// create text buffer
	GtkTextBuffer* buffer = gtk_text_buffer_new(NULL);

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
	gtk_widget_set_size_request(tbox, -1, 100);
	g_signal_connect(fLoggingBox, "activate", G_CALLBACK(logging_set_color), this);

	gtk_widget_show(box);
}

void GxMainInterface::set_logging_expander_color(const char *color)
{
	GtkExpander* exbox = getLoggingBox();
	if (gtk_expander_get_expanded(exbox) == FALSE) {
		GdkColor c;
		gdk_color_parse(color, &c);
		gtk_widget_modify_fg(GTK_WIDGET(exbox), GTK_STATE_NORMAL, &c);
		gtk_widget_modify_fg(gtk_expander_get_label_widget(exbox), GTK_STATE_NORMAL, &c);
	}
}

void GxMainInterface::show_msg(string msgbuf, gx_system::GxMsgType msgtype)
{
	// color depending on msg type
	// initialize static tag table
	static struct tab_table {
		const char *tagname;
		const char *tag_color;
		GtkTextTag *tag;
	} tags[kMessageTypeCount] = {
		{"colinfo", "#00ced1"},
		{"colwarn", "#ff8800"},
		{"colerr", "#ff0000"},
	};

	assert(0 <= msgtype && msgtype < kMessageTypeCount);
	assert(pthread_equal(pthread_self(), ui_thread));

	// retrieve gtk text buffer
	GtkTextBuffer* buffer = gtk_text_view_get_buffer(getLoggingWindow());

	if (!tags[0].tag) { // fill static table
		for (int i = 0; i < kMessageTypeCount; i++) {
			tags[i].tag = gtk_text_buffer_create_tag(buffer, tags[i].tagname, "foreground",
			                                         tags[i].tag_color, NULL);
		}
	}

	// how many lines to keep
	const int nlines = 50;

	// delete first line when window filled up
	int linecount = gtk_text_buffer_get_line_count(buffer); // empty buffer == 1 line
	if (linecount >= nlines) {
		GtkTextIter iter1;
		GtkTextIter iter2;
		gtk_text_buffer_get_iter_at_line(buffer, &iter1, 0);
		gtk_text_buffer_get_iter_at_line(buffer, &iter2, 1);
		gtk_text_buffer_delete(buffer, &iter1, &iter2);
	}
	GtkTextIter iter;
	gtk_text_buffer_get_end_iter(buffer, &iter);
	if (gtk_text_buffer_get_char_count(buffer) > 0) {
		gtk_text_buffer_insert(buffer, &iter, "\n", -1);
	}

	gtk_text_buffer_insert_with_tags(buffer, &iter, msgbuf.c_str(), -1,
	                                 tags[msgtype].tag, NULL);
	gtk_adjustment_set_value(fLoggingVAdjustment, 10000); // scroll to end (big value, gets clamped to max)

	// modify expander bg color is closed
	if (msgtype > highest_unseen_msg_level) {
		set_logging_expander_color(tags[msgtype].tag_color);
		highest_unseen_msg_level = msgtype;
	}
}


void GxMainInterface::openLevelMeterBox(const char* label)
{
	GtkWidget* box1 = addWidget(label, gtk_alignment_new (0.5, 0.5, 0, 0));
	GtkWidget* box = gtk_hbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER(box1), box);

	gint boxheight = 135;
	gint boxwidth  = 47;

	gtk_container_set_border_width (GTK_CONTAINER (box), 3);
	gtk_box_set_spacing(GTK_BOX(box), 1);

	gtk_widget_set_size_request (GTK_WIDGET(box), boxwidth, boxheight);
	g_signal_connect(box, "expose-event", G_CALLBACK(level_meter_expose), NULL);
	g_signal_connect(GTK_CONTAINER(box), "check-resize",
	                 G_CALLBACK(level_meter_expose), NULL);

	// meter level colors
	int base = 0x00380800;
	int mid  = 0x00ff0000;
	int top  = 0xff000000;
	int clip = 0xff000000;

	// width of meter
	int width    = 8;

	// how long we hold the peak bar = hold * thread call timeout

	// Note: 30 * 80 = 2.4 sec
	int hold     = 20;

	// guitarix output levels
	GtkWidget* gxbox = gtk_hbox_new (FALSE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (gxbox), 0);
	gtk_box_set_spacing(GTK_BOX(gxbox), 25);

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

	// show main box
	gtk_widget_show(box);
	gtk_widget_show(box1);
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
			if (per<7) //FIXME (magic value)
			{
				GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(parent));
				GtkWidget *obi = (GtkWidget *) g_list_nth_data(child_list,per+1);
				child_list =  gtk_container_get_children(GTK_CONTAINER(obi));
				GtkWidget *obib = (GtkWidget *) g_list_nth_data(child_list,1);
				child_list =  gtk_container_get_children(GTK_CONTAINER(obib));
				GtkWidget *obibi = (GtkWidget *) g_list_nth_data(child_list,0);

				gtk_box_reorder_child (GTK_BOX(parent),GTK_WIDGET(box),per +1);
				((gx_ui::GxUiItem*)data)->modifyZone(per+1);
				if(GTK_IS_BUTTON (obibi))
                    gtk_button_clicked(GTK_BUTTON(obibi));
				else {
				    child_list =  gtk_container_get_children(GTK_CONTAINER(obi));
				    obib = (GtkWidget *) g_list_nth_data(child_list,2);
				    child_list =  gtk_container_get_children(GTK_CONTAINER(obib));
				    obibi = (GtkWidget *) g_list_nth_data(child_list,0);
				    if(GTK_IS_BUTTON (obibi))
                        gtk_button_clicked(GTK_BUTTON(obibi));
				}

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
				if(GTK_IS_BUTTON (obibi))
                    gtk_button_clicked(GTK_BUTTON(obibi));
				else {
				    child_list =  gtk_container_get_children(GTK_CONTAINER(obi));
				    obib = (GtkWidget *) g_list_nth_data(child_list,2);
				    child_list =  gtk_container_get_children(GTK_CONTAINER(obib));
				    obibi = (GtkWidget *) g_list_nth_data(child_list,0);
				    if(GTK_IS_BUTTON (obibi))
                        gtk_button_clicked(GTK_BUTTON(obibi));
				}

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
	g_signal_connect(box, "expose-event", G_CALLBACK(tribal_box_expose), NULL);

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
	                  G_CALLBACK(vbox_expose), NULL);
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
	g_signal_connect(box, "expose-event", G_CALLBACK(tribal_box_expose), NULL);
	GtkWidget * box1 = gtk_fixed_new ();
	g_signal_connect(box1, "expose-event", G_CALLBACK(vbox_expose), NULL);
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
	g_signal_connect  (GTK_OBJECT (button), "pressed",
	                   G_CALLBACK (gx_reset_effects), (gpointer) c);

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
	g_signal_connect(box, "expose-event", G_CALLBACK(vbox_expose), NULL);

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

void GxMainInterface::openSlooperBox(const char* label)
{
	GtkWidget * box = gtk_vbox_new (homogene, 0);
	gtk_container_set_border_width (GTK_CONTAINER (box), 0);
	g_signal_connect(box, "expose-event", G_CALLBACK(slooper_expose), NULL);

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

void GxMainInterface::openFlipLabelBox(const char* label)
{
	GtkWidget * box = gtk_vbox_new (homogene, 0);
	gtk_container_set_border_width (GTK_CONTAINER (box), 0);
	g_signal_connect(box, "expose-event", G_CALLBACK(vbox_expose), NULL);

	if (fMode[fTop] != kTabMode && label[0] != 0)
	{
	    GtkWidget * hbox = gtk_hbox_new (homogene, 0);
	    GtkWidget * vbox = gtk_vbox_new (homogene, 0);
		GtkWidget* lw = gtk_label_new(label);
        gtk_label_set_angle (GTK_LABEL(lw),90);

		gtk_widget_set_name (lw,"beffekt_label");
		GtkStyle *style = gtk_widget_get_style(lw);
		pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
		pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
		gtk_widget_modify_font(lw, style->font_desc);

		gtk_container_add (GTK_CONTAINER(hbox), lw);
		gtk_container_add (GTK_CONTAINER(hbox), vbox);
		gtk_container_add (GTK_CONTAINER(box), hbox);
		gtk_box_pack_start (GTK_BOX(fBox[fTop]), box, expand, fill, 0);

		gtk_widget_show_all(box);
		pushBox(kBoxMode, vbox);
	}
	else
	{
		pushBox(kBoxMode, addWidget(label, box));
	}
}

void GxMainInterface::openSpaceBox(const char* label)
{
	GtkWidget * box = gtk_vbox_new (homogene, 2);
	gtk_container_set_border_width (GTK_CONTAINER (box), 4);


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

void GxMainInterface::openAmpBox(const char* label)
{
	GtkWidget * box = gtk_vbox_new (homogene, 2);
	gtk_container_set_border_width (GTK_CONTAINER (box), 4);
	g_signal_connect(box, "expose-event", G_CALLBACK(AmpBox_expose), NULL);

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

void GxMainInterface::openPlugBox(const char* label)
{
	GtkWidget * box = gtk_vbox_new (homogene, 4);
	gtk_container_set_border_width (GTK_CONTAINER (box), 10);
	g_signal_connect(box, "expose-event", G_CALLBACK(plug_box_expose), NULL);

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

void GxMainInterface::openPaintBox(const char* label)
{
	GtkWidget * box = gtk_vbox_new (homogene, 2);
	gtk_container_set_border_width (GTK_CONTAINER (box), 4);
	g_signal_connect(box, "expose-event", G_CALLBACK(filter_box_expose), NULL);

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

void GxMainInterface::openpaintampBox(const char* label)
{
	GtkWidget * box = gtk_vbox_new (homogene, 2);
	gtk_container_set_border_width (GTK_CONTAINER (box), 4);
	g_signal_connect(box, "expose-event", G_CALLBACK(eq_expose), NULL);

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
	g_signal_connect(box, "expose-event", G_CALLBACK(amp_expose), NULL);

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
	g_signal_connect(box, "expose-event", G_CALLBACK(upper_widget_expose), NULL);

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
	g_signal_connect(box, "expose-event", G_CALLBACK(rectangle_skin_color_expose), NULL);

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

struct uiSwitchDISTBox : public gx_ui::GxUiItem
{
	GtkWidget* fbox;

	uiSwitchDISTBox(gx_ui::GxUI* ui, float* zone, GtkWidget* box)
		: gx_ui::GxUiItem(ui, zone), fbox(box) {}

	virtual void reflectZone()
		{
            GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(fbox));

			GtkWidget *box0 = (GtkWidget *) g_list_nth_data(child_list,0);
			GtkWidget *box1 = (GtkWidget *) g_list_nth_data(child_list,1);
			fCache = *fZone;
			if (fCache == 1)
			{
			    if(gx_engine::audio.fdialogbox1 ==1)
                    gx_engine::audio.fdis1 = 1;
                gtk_widget_hide(box0);

                gx_engine::audio.fdialogbox1 = 0;
                gtk_widget_show(box1);
			}
			else if (fCache == 0)
			{
			    if(gx_engine::audio.fdis1 ==1)
                    gx_engine::audio.fdialogbox1 = 1;
				gtk_widget_hide(box1);

				gx_engine::audio.fdis1 = 0;
                gtk_widget_show(box0);
			}
		}
};

struct uiSwitchEQBox : public gx_ui::GxUiItem
{
	GtkWidget* fbox;

	uiSwitchEQBox(gx_ui::GxUI* ui, float* zone, GtkWidget* box)
		: gx_ui::GxUiItem(ui, zone), fbox(box) {}

	virtual void reflectZone()
		{
            GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(fbox));

			GtkWidget *box0 = (GtkWidget *) g_list_nth_data(child_list,0);
			GtkWidget *box1 = (GtkWidget *) g_list_nth_data(child_list,1);
			if(fCache != *fZone) {
			fCache = *fZone;
			if (fCache == 1)
			{
			    if(gx_engine::audio.fdialogbox_eq ==1)
                    gx_engine::audio.fdialogbox_eqs = 1;
                gtk_widget_hide(box0);

                gx_engine::audio.fdialogbox_eq = 0;
                gtk_widget_show(box1);
			}
			else if (fCache == 0)
			{
			    if(gx_engine::audio.fdialogbox_eqs ==1)
                    gx_engine::audio.fdialogbox_eq = 1;
				gtk_widget_hide(box1);

				gx_engine::audio.fdialogbox_eqs = 0;
                gtk_widget_show(box0);
			}
			}
		}
};

void GxMainInterface::openVerticalSwitchBox(const char* label, int state, int wit, float* zone)
{
	GtkWidget * box = gtk_vbox_new (homogene, 0);
	gtk_container_set_border_width (GTK_CONTAINER (box), 0);
	g_signal_connect(box, "expose-event", G_CALLBACK(vbox_expose), NULL);

	if (fMode[fTop] != kTabMode && label[0] != 0)
	{

       if(wit == 0) new uiSwitchDISTBox(this, zone, GTK_WIDGET(box));
       else if(wit == 1) new uiSwitchEQBox(this, zone, GTK_WIDGET(box));
		//GtkWidget* lw = gtk_label_new(label);
        GtkWidget * box0 = gtk_vbox_new (homogene, 0);
        GtkWidget * box1 = gtk_vbox_new (homogene, 0);
        gtk_container_set_border_width (GTK_CONTAINER (box0), 0);
        gtk_container_set_border_width (GTK_CONTAINER (box1), 0);
		//gtk_container_add (GTK_CONTAINER(box), lw);
		gtk_box_pack_start (GTK_BOX(fBox[fTop]), box, expand, fill, 0);
		gtk_container_add (GTK_CONTAINER(box), box0);
		gtk_container_add (GTK_CONTAINER(box), box1);

		gtk_widget_hide(box0);
		gtk_widget_hide(box1);
		gtk_widget_show(box);
		//addWidget(label,  box);
		if(state == 0) pushBox(kBoxMode, box0);
		else pushBox(kBoxMode, box1);
	}
	else
	{
		pushBox(kBoxMode, addWidget(label, box));
	}
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

	g_signal_connect (GTK_OBJECT (button), "toggled", G_CALLBACK (JackCapture::start_stop), NULL);
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
	connect_midi_controller(button, zone);
}

void gx_start_stop_jconv(GtkWidget *widget, gpointer data)
{
	if (gx_jconv::GxJConvSettings::checkbutton7 == 0) {
		gx_engine::conv.stop();
	} else {
		gx_jconv::GxJConvSettings* jcset = gx_jconv::GxJConvSettings::instance();
		bool rc = gx_engine::conv.configure(
			gx_jack::jack_bs, gx_jack::jack_sr, jcset->getIRDir()+"/"+jcset->getIRFile(),
			jcset->getGain(), jcset->getlGain(), jcset->getDelay(), jcset->getlDelay(),
			jcset->getOffset(), jcset->getLength(), jcset->getMem(), jcset->getBufferSize());
		if (!rc || !gx_engine::conv.start()) {
			gx_jconv::GxJConvSettings::checkbutton7 = 0;
		}
	}
	//if(GDK_WINDOW(gx_gui::patch_info->window)) gdk_window_invalidate_rect(GDK_WINDOW(patch_info->window),NULL,false);
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
	                  G_CALLBACK (gx_start_stop_jconv), (gpointer)c);
	connect_midi_controller(button, zone);
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
	connect_midi_controller(button, zone);
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

// -------------------------- Horizontal Slider -----------------------------------

void GxMainInterface::addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
{
	*zone = init;
	GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
	uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
	g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
	GtkRegler myGtkRegler;
	GtkWidget* slider = myGtkRegler.gtk_mini_slider_new_with_adjustment (GTK_ADJUSTMENT(adj));
	connect_midi_controller(slider, zone);
	gtk_range_set_inverted (GTK_RANGE(slider), TRUE);
	addWidget(label, slider);
}

void GxMainInterface::addHorizontalWheel(string id, const char* label)
{
	if (!parameter_map.hasId(id)) {
		return;
	}
	const FloatParameter &p = parameter_map[id].getFloat();
	if (!label) {
		label = p.name().c_str();
	}
	addHorizontalWheel(label, &p.value, p.std_value, p.lower, p.upper, p.step);
}


void GxMainInterface::addHorizontalWheel(const char* label, float* zone, float init, float min, float max, float step)
{
	*zone = init;
	GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
	uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
	g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
	GtkRegler myGtkRegler;
	GtkWidget* slider = myGtkRegler.gtk_wheel_new_with_adjustment (GTK_ADJUSTMENT(adj));
	connect_midi_controller(slider, zone);
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
	connect_midi_controller(slider, zone);
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
	//GtkWidget* lw = gtk_label_new("");
	GtkRegler myGtkRegler;
	GtkWidget* lw = myGtkRegler.gtk_value_display(GTK_ADJUSTMENT(adj));

	GtkWidget* lwl = gtk_label_new(label);
	gtk_widget_set_name (lw,"value_label");
	gtk_widget_set_name (lwl,"effekt_label");
	GtkStyle *style = gtk_widget_get_style(lwl);
	pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
	pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);

	gtk_widget_modify_font(lwl, style->font_desc);

	GtkWidget* slider = myGtkRegler.gtk_regler_new_with_adjustment(GTK_ADJUSTMENT(adj));
	connect_midi_controller(slider, zone);
	gtk_range_set_inverted (GTK_RANGE(slider), TRUE);

	GtkWidget* box1 = addWidget(label, gtk_alignment_new (0.5, 0.5, 0, 0));
	GtkWidget* box = gtk_vbox_new (FALSE, 0);
	GtkWidget* box2 = gtk_hbox_new (FALSE, 0);
	GtkWidget* box3 = gtk_vbox_new (FALSE, 0);
	GtkWidget* box4 = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER(box1), box);
	gtk_container_add (GTK_CONTAINER(box), lwl);
	gtk_container_add (GTK_CONTAINER(box), slider);
	gtk_container_add (GTK_CONTAINER(box2), box3);
	gtk_container_add (GTK_CONTAINER(box2), lw);
	gtk_container_add (GTK_CONTAINER(box2), box4);
	gtk_container_add (GTK_CONTAINER(box), box2);
	gtk_widget_show_all(box1);

}

void GxMainInterface::addSpinValueBox(const char* label, float* zone, float init, float min, float max, float step)
{
	*zone = init;
	GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
	uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
	g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);

	GtkRegler myGtkRegler;
	GtkWidget* lw = myGtkRegler.gtk_value_display(GTK_ADJUSTMENT(adj));

	GtkWidget* lwl = gtk_label_new(label);
	gtk_widget_set_name (lwl,"effekt_label");
	GtkStyle *style = gtk_widget_get_style(lwl);
	pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
	pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
	gtk_widget_modify_font(lwl, style->font_desc);

	connect_midi_controller(lw, zone);
	gtk_range_set_inverted (GTK_RANGE(lw), TRUE);

	GtkWidget* box1 = addWidget(label, gtk_alignment_new (0.5, 0.5, 0, 0));
	GtkWidget* box = gtk_vbox_new (FALSE, 0);
	GtkWidget* box2 = gtk_hbox_new (FALSE, 0);
	GtkWidget* box3 = gtk_vbox_new (FALSE, 0);
	GtkWidget* box4 = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER(box1), box);
	gtk_container_add (GTK_CONTAINER(box), lwl);
	gtk_container_add (GTK_CONTAINER(box2), box3);
	gtk_container_add (GTK_CONTAINER(box2), lw);
	gtk_container_add (GTK_CONTAINER(box2), box4);
	gtk_container_add (GTK_CONTAINER(box), box2);
	gtk_widget_show_all(box1);

}

void GxMainInterface::addbigregler(string id, const char* label)
{
	if (!parameter_map.hasId(id)) {
		return;
	}
	const FloatParameter &p = parameter_map[id].getFloat();
	if (!label) {
		label = p.name().c_str();
	}
	addbigregler(label, &p.value, p.std_value, p.lower, p.upper, p.step);
}

void GxMainInterface::addslider(string id, const char* label)
{
	if (!parameter_map.hasId(id)) {
		return;
	}
	const FloatParameter &p = parameter_map[id].getFloat();
	if (!label) {
		label = p.name().c_str();
	}
	addslider(label, &p.value, p.std_value, p.lower, p.upper, p.step);
}

void GxMainInterface::addregler(string id, const char* label)
{
	if (!parameter_map.hasId(id)) {
		return;
	}
	const FloatParameter &p = parameter_map[id].getFloat();
	if (!label) {
		label = p.name().c_str();
	}
	addregler(label, &p.value, p.std_value, p.lower, p.upper, p.step);
}

void GxMainInterface::addSpinValueBox(string id, const char* label)
{
	if (!parameter_map.hasId(id)) {
		return;
	}
	const FloatParameter &p = parameter_map[id].getFloat();
	if (!label) {
		label = p.name().c_str();
	}
	addSpinValueBox(label, &p.value, p.std_value, p.lower, p.upper, p.step);
}

void GxMainInterface::addswitch(string id, const char* label)
{
	if (!parameter_map.hasId(id)) {
		return;
	}
	const IntParameter &p = parameter_map[id].getInt();
	if (!label) {
		label = p.name().c_str();
	}
	addswitch(label, &p.value);
}

void GxMainInterface::addminiswitch(string id, const char* label)
{
	if (!parameter_map.hasId(id)) {
		return;
	}
	Parameter& p = parameter_map[id];
	if (!label) {
		label = p.name().c_str();
	}
	if (p.isFloat()) {
		addminiswitch(label, &p.getFloat().value);
	} else {
		addminiswitch(label, &p.getInt().value);
	}
}

void GxMainInterface::addselector(string id, int nvalues, const char** pvalues, const char* label)
{
	if (!parameter_map.hasId(id)) {
		return;
	}
	const FloatParameter &p = parameter_map[id].getFloat();
	if (!label) {
		label = p.name().c_str();
	}
	addselector(label, &p.value, nvalues, pvalues);
}

void GxMainInterface::addtoggle(string id, const char* label)
{
	if (!parameter_map.hasId(id)) {
		return;
	}
	Parameter& p = parameter_map[id];
	if (!label) {
		label = p.name().c_str();
	}
	if (p.isFloat()) {
		addtoggle(label, &p.getFloat().value);
	} else {
		addtoggle(label, &p.getInt().value);
	}
}

void GxMainInterface::addbtoggle(string id, const char* label)
{
	if (!parameter_map.hasId(id)) {
		return;
	}
	Parameter& p = parameter_map[id];
	if (!label) {
		label = p.name().c_str();
	}
	if (p.isFloat()) {
		addbtoggle(label, &p.getFloat().value);
	} else {
		addbtoggle(label, &p.getInt().value);
	}
}

void GxMainInterface::addRecButton(string id, const char* label)
{
	if (!parameter_map.hasId(id)) {
		return;
	}
	Parameter& p = parameter_map[id];
	if (!label) {
		label = p.name().c_str();
	}

		addRecButton(label, &p.getFloat().value);

}

void GxMainInterface::addPlayButton(string id, const char* label)
{
	if (!parameter_map.hasId(id)) {
		return;
	}
	Parameter& p = parameter_map[id];
	if (!label) {
		label = p.name().c_str();
	}

		addPlayButton(label, &p.getFloat().value);

}

void GxMainInterface::addminieqswitch(string id, const char* label)
{
	if (!parameter_map.hasId(id)) {
		return;
	}
	const IntParameter &p = parameter_map[id].getInt();
	if (!label) {
		label = p.name().c_str();
	}
	addminieqswitch(label, &p.value);
}

void GxMainInterface::addminicabswitch(string id, const char* label)
{
	if (!parameter_map.hasId(id)) {
		return;
	}
	const IntParameter &p = parameter_map[id].getInt();
	if (!label) {
		label = p.name().c_str();
	}
	addminicabswitch(label, &p.value);
}

void GxMainInterface::addVerticalSlider(string id, const char* label)
{
	if (!parameter_map.hasId(id)) {
		return;
	}
	const FloatParameter &p = parameter_map[id].getFloat();
	if (!label) {
		label = p.name().c_str();
	}
	addVerticalSlider(label, &p.value, p.std_value, p.lower, p.upper, p.step);
}

void GxMainInterface::addCheckButton(string id, const char* label)
{
	if (!parameter_map.hasId(id)) {
		return;
	}
	const FloatParameter &p = parameter_map[id].getFloat();
	if (!label) {
		label = p.name().c_str();
	}
	addCheckButton(label, &p.value);
}

void GxMainInterface::addNumEntry(string id, const char* label)
{
	if (!parameter_map.hasId(id)) {
		return;
	}
	const FloatParameter &p = parameter_map[id].getFloat();
	if (!label) {
		label = p.name().c_str();
	}
	addNumEntry(label, &p.value, p.std_value, p.lower, p.upper, p.step);
}

void GxMainInterface::addPToggleButton(string id, const char* label)
{
	if (!parameter_map.hasId(id)) {
		return;
	}
	const FloatParameter &p = parameter_map[id].getFloat();
	if (!label) {
		label = p.name().c_str();
	}
	addPToggleButton(label, &p.value);
}

void GxMainInterface::addbigregler(const char* label, float* zone, float init, float min, float max, float step)
{
	*zone = init;
	GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
	uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
	g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);

	GtkRegler myGtkRegler;
	GtkWidget* lw = myGtkRegler.gtk_value_display(GTK_ADJUSTMENT(adj));
	GtkWidget* lwl = gtk_label_new(label);

	gtk_widget_set_name (lw,"value_label");
	gtk_widget_set_name (lwl,"effekt_label");

	GtkStyle *style = gtk_widget_get_style(lwl);
	pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
	pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
	gtk_widget_modify_font(lwl, style->font_desc);

	GtkWidget* slider = myGtkRegler.gtk_big_regler_new_with_adjustment(GTK_ADJUSTMENT(adj));
	connect_midi_controller(slider, zone);
	gtk_range_set_inverted (GTK_RANGE(slider), TRUE);
	GtkWidget* box1 = addWidget(label, gtk_alignment_new (0.5, 0.5, 0, 0));
	GtkWidget* box = gtk_vbox_new (FALSE, 0);
	GtkWidget* box2 = gtk_hbox_new (FALSE, 4);
	GtkWidget* box3 = gtk_vbox_new (FALSE, 0);
	GtkWidget* box4 = gtk_vbox_new (FALSE, 0);
	gtk_container_add (GTK_CONTAINER(box1), box);
	gtk_container_add (GTK_CONTAINER(box), lwl);
	gtk_container_add (GTK_CONTAINER(box), slider);
	gtk_container_add (GTK_CONTAINER(box2), box3);
	gtk_container_add (GTK_CONTAINER(box2), lw);
	gtk_container_add (GTK_CONTAINER(box2), box4);
	gtk_container_add (GTK_CONTAINER(box), box2);
	gtk_widget_show_all(box1);
}

void GxMainInterface::addslider(const char* label, float* zone, float init, float min, float max, float step)
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
	GtkWidget* slider = myGtkRegler.gtk_hslider_new_with_adjustment(GTK_ADJUSTMENT(adj));
	connect_midi_controller(slider, zone);
	gtk_range_set_inverted (GTK_RANGE(slider), TRUE);
	GtkWidget* box = addWidget(label,gtk_vbox_new (FALSE, 0));
	gtk_container_add (GTK_CONTAINER(box), lwl);
	gtk_container_add (GTK_CONTAINER(box), slider);
	gtk_container_add (GTK_CONTAINER(box), lw);
	gtk_widget_show_all(box);
}

void GxMainInterface::addtoggle(const char* label, int* zone)
{
	GtkObject* adj = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
	uiAdjustment* c = new uiAdjustment(this,(float*) zone, GTK_ADJUSTMENT(adj));
	g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
	GtkRegler myGtkRegler;
	GtkWidget* slider = myGtkRegler.gtk_toggle_new_with_adjustment(GTK_ADJUSTMENT(adj));
	connect_midi_controller(slider, zone);
	addWidget(label, slider);
}

void GxMainInterface::addtoggle(const char* label, float* zone)
{
	GtkObject* adj = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
	uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
	g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
	GtkRegler myGtkRegler;
	GtkWidget* slider = myGtkRegler.gtk_toggle_new_with_adjustment(GTK_ADJUSTMENT(adj));
	connect_midi_controller(slider, zone);
	addWidget(label, slider);
}

void GxMainInterface::addbtoggle(const char* label, int* zone)
{
	GtkObject* adj = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
	uiAdjustment* c = new uiAdjustment(this,(float*) zone, GTK_ADJUSTMENT(adj));
	g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
	GtkRegler myGtkRegler;
	GtkWidget* slider = myGtkRegler.gtk_button_toggle_new_with_adjustment(GTK_ADJUSTMENT(adj));
	connect_midi_controller(slider, zone);
	addWidget(label, slider);
}

void GxMainInterface::addbtoggle(const char* label, float* zone)
{
	GtkObject* adj = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
	uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
	g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
	GtkRegler myGtkRegler;
	GtkWidget* slider = myGtkRegler.gtk_button_toggle_new_with_adjustment(GTK_ADJUSTMENT(adj));
	connect_midi_controller(slider, zone);
	addWidget(label, slider);
}

void GxMainInterface::addRecButton(const char* label, float* zone)
{
	GtkObject* adj = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
	uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
	g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
	GtkRegler myGtkRegler;
	GtkWidget* slider = myGtkRegler.gtk_button_rec_new_with_adjustment(GTK_ADJUSTMENT(adj));
	connect_midi_controller(slider, zone);
	addWidget(label, slider);
}

void GxMainInterface::addPlayButton(const char* label, float* zone)
{
	GtkObject* adj = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
	uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
	g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
	GtkRegler myGtkRegler;
	GtkWidget* slider = myGtkRegler.gtk_button_play_new_with_adjustment(GTK_ADJUSTMENT(adj));
	connect_midi_controller(slider, zone);
	addWidget(label, slider);
}

void GxMainInterface::addswitch(const char* label, int* zone)
{
	GtkObject* adj = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
	uiAdjustment* c = new uiAdjustment(this,(float*) zone, GTK_ADJUSTMENT(adj));
	g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
	GtkRegler myGtkRegler;
	GtkWidget* slider = myGtkRegler.gtk_switch_new_with_adjustment(GTK_ADJUSTMENT(adj));
	connect_midi_controller(slider, zone);
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

void GxMainInterface::addselector(const char* label, float* zone, int maxv, const char** labels)
{
	GtkObject* adjs = gtk_adjustment_new(0, 0, maxv, 1, 10*1, 0);
	uiAdjustment* cs = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adjs));
	g_signal_connect (GTK_OBJECT (adjs), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) cs);

	GtkRegler myGtkRegler;
	GtkWidget* ser = myGtkRegler.gtk_selector_new_with_adjustment(GTK_ADJUSTMENT(adjs), maxv, labels);
	connect_midi_controller(ser, zone);

	openHorizontalBox("");
	addWidget(label, ser);
	closeBox();
}

void GxMainInterface::addminiswitch(const char* label, int* zone)
{
	GtkObject* adj = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
	uiAdjustment* c = new uiAdjustment(this,(float*) zone, GTK_ADJUSTMENT(adj));
	g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
	GtkRegler myGtkRegler;
	GtkWidget* slider = myGtkRegler.gtk_mini_toggle_new_with_adjustment(GTK_ADJUSTMENT(adj));
	connect_midi_controller(slider, zone);
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

void GxMainInterface::addminiswitch(const char* label, float* zone)
{
	GtkObject* adj = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
	uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
	g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);
	GtkRegler myGtkRegler;
	GtkWidget* slider = myGtkRegler.gtk_mini_toggle_new_with_adjustment(GTK_ADJUSTMENT(adj));
	connect_midi_controller(slider, zone);
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
	connect_midi_controller(slider, zone);
	//g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (gx_hide_eq), (gpointer) slider);
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

void GxMainInterface::addminicabswitch(const char* label, int* zone)
{
	GtkObject* adj = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
	uiAdjustment* c = new uiAdjustment(this,(float*) zone, GTK_ADJUSTMENT(adj));
	g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) c);


	GtkRegler myGtkRegler;
	GtkWidget* slider = myGtkRegler.gtk_mini_toggle_new_with_adjustment(GTK_ADJUSTMENT(adj));
	connect_midi_controller(slider, zone);
	g_signal_connect (GTK_OBJECT (adj), "value-changed", G_CALLBACK (gx_cab_res), (gpointer) slider);
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
	connect_midi_controller(spinner, zone);
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

void GxMainInterface::openDialogBox(const char* id, float* zone, int * z1)
{
	const char *label = param_group(id).c_str();
	GtkWidget * dialog = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated(GTK_WINDOW(dialog), TRUE);
	gtk_window_set_icon(GTK_WINDOW (dialog), GDK_PIXBUF(ib));
	gtk_window_set_resizable(GTK_WINDOW(dialog), FALSE);
	gtk_window_set_gravity(GTK_WINDOW(dialog), GDK_GRAVITY_SOUTH);
	gtk_window_set_transient_for (GTK_WINDOW(dialog), GTK_WINDOW(fWindow));
	gtk_window_set_position (GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);
	gtk_window_set_keep_below (GTK_WINDOW(dialog), FALSE);
	gtk_window_set_title (GTK_WINDOW (dialog), label);
	gtk_window_set_type_hint (GTK_WINDOW (dialog), GDK_WINDOW_TYPE_HINT_UTILITY);
	gtk_window_set_destroy_with_parent(GTK_WINDOW(dialog), TRUE);
	GtkWidget * box = gtk_hbox_new (homogene, 8);
	GtkWidget * box4 = gtk_vbox_new (homogene, 4);
	GtkWidget * box5 = gtk_hbox_new (homogene, 4);
	gtk_container_set_border_width (GTK_CONTAINER (box), 2);
	gtk_container_set_border_width (GTK_CONTAINER (box4), 8);
	g_signal_connect(box4, "expose-event", G_CALLBACK(rectangle_expose), NULL);
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

    GtkObject* adjl = gtk_adjustment_new(0, 0, 1, 1, 10*1, 0);
	uiAdjustment* cl = new uiAdjustment(this,(float*) z1, GTK_ADJUSTMENT(adjl));
	g_signal_connect (GTK_OBJECT (adjl), "value-changed", G_CALLBACK (uiAdjustment::changed), (gpointer) cl);



	GtkWidget* led = myGtkRegler.gtk_led_new_with_adjustment(GTK_ADJUSTMENT(adjl));

	//connect_midi_controller(slider, zone);
    gtk_container_add (GTK_CONTAINER(box5), led);
	gtk_container_add (GTK_CONTAINER(box5), frame);
	gtk_container_add (GTK_CONTAINER(box5), button1);
	g_signal_connect  (GTK_OBJECT (button1), "pressed", G_CALLBACK (gx_reset_units), (gpointer) id);
	gtk_container_add (GTK_CONTAINER(box4), box5);
	gtk_container_add (GTK_CONTAINER(box4), box);
	gtk_container_add (GTK_CONTAINER(dialog), box4);
	// gtk_widget_show(dialog);
	gtk_widget_show(lab);
	gtk_widget_show(led);
	gtk_widget_show(frame);
	gtk_widget_show(button1);
	gtk_widget_show(box);
	gtk_widget_show(box4);
	gtk_widget_show(box5);
	pushBox(kBoxMode, box);
}
//-------- collect patch info for stage display
struct uiPatchDisplay : public gx_ui::GxUiItem
{
	GtkWidget* fdialog;

	uiPatchDisplay(gx_ui::GxUI* ui, float* zone, GtkWidget* dialog)
		: gx_ui::GxUiItem(ui, zone), fdialog(dialog) {}

	virtual void reflectZone()
		{
		    GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(fdialog));
			GtkWidget *parent = (GtkWidget *) g_list_nth_data(child_list,0);
			if(GDK_WINDOW(parent->window)) {
                if (fCache != *fZone) {
                    char s[64];
                    gdk_window_invalidate_rect(GDK_WINDOW(parent->window),NULL,false);
                    child_list =  gtk_container_get_children(GTK_CONTAINER(parent));
                    parent = (GtkWidget *) g_list_nth_data(child_list,1);
                    GtkWidget *pchild = (GtkWidget *) g_list_nth_data(child_list,2);
                    gx_jconv::GxJConvSettings* jcset = gx_jconv::GxJConvSettings::instance();

                    if(gx_jconv::GxJConvSettings::checkbutton7 == 1) {
                        snprintf(s, 63, "convolve %s",jcset->getIRFile().c_str());
                        gtk_label_set_text(GTK_LABEL(pchild),s);
                    }else {
                        snprintf(s, 63, "convolver off");
                        gtk_label_set_text(GTK_LABEL(pchild),s);
                    }

                    if(setting_is_preset ) {
                        snprintf(s, 63, " %i%s%s ", int(show_patch_info),". ",gx_current_preset.c_str());
                        gtk_label_set_text(GTK_LABEL(parent), s);
                    }
                    else {
                        show_patch_info = 0;
                        snprintf(s, 63, " %i%sMain Setting ", int(show_patch_info),". ");
                        gtk_label_set_text(GTK_LABEL(parent), s);
                    }
                    fCache = *fZone;
                }
            }
		}
};

//----- hide the jconv settings widget
gboolean gx_delete_pi( GtkWidget *widget, gpointer   data )
{
	gtk_widget_hide(patch_info);
	return TRUE;
}

void GxMainInterface::openPatchInfoBox(float* zone)
{
	patch_info = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_decorated(GTK_WINDOW(patch_info), TRUE);
	gtk_window_set_icon(GTK_WINDOW (patch_info), GDK_PIXBUF(ib));
	gtk_window_set_resizable(GTK_WINDOW(patch_info), FALSE);
	gtk_window_set_gravity(GTK_WINDOW(patch_info), GDK_GRAVITY_SOUTH);
	gtk_window_set_transient_for (GTK_WINDOW(patch_info), GTK_WINDOW(fWindow));
	gtk_window_set_position (GTK_WINDOW(patch_info), GTK_WIN_POS_MOUSE);
	gtk_window_set_keep_below (GTK_WINDOW(patch_info), FALSE);
	gtk_window_set_title (GTK_WINDOW (patch_info), "Patch Info");
	gtk_window_set_type_hint (GTK_WINDOW (patch_info), GDK_WINDOW_TYPE_HINT_UTILITY);
	gtk_window_set_destroy_with_parent(GTK_WINDOW(patch_info), TRUE);
	GtkWidget * box = gtk_vbox_new (homogene, 8);
	const char *labe = "";
    GtkWidget* 	la = gtk_label_new(labe);
	GtkWidget* 	lab = gtk_label_new(labe);
	GtkWidget* 	label = gtk_label_new(labe);
	new uiPatchDisplay(this, zone, GTK_WIDGET(patch_info));
	g_signal_connect_swapped (G_OBJECT (patch_info), "delete_event", G_CALLBACK (gx_delete_pi), NULL);
	g_signal_connect(box, "expose-event", G_CALLBACK(info_box_expose), NULL);
	gtk_container_set_border_width (GTK_CONTAINER (box), 8);

	GtkStyle *style = gtk_widget_get_style(lab);
	pango_font_description_set_size(style->font_desc, 30*PANGO_SCALE);
	pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
	gtk_widget_modify_font(lab, style->font_desc);

    gtk_container_add (GTK_CONTAINER(box), la);
    gtk_container_add (GTK_CONTAINER(box), lab);
    gtk_container_add (GTK_CONTAINER(box), label);
	gtk_container_add (GTK_CONTAINER(patch_info), box);

    gtk_widget_hide(patch_info);
}

// ------------------------------ Num Display -----------------------------------

struct uiNumDisplay : public gx_ui::GxUiItem
{
	GtkWidget* fLabel;

	uiNumDisplay(gx_ui::GxUI* ui, float* zone, GtkWidget* label)
		: gx_ui::GxUiItem(ui, zone), fLabel(label) {}

	virtual void reflectZone()
		{

			fCache = *fZone;
			if (shownote == 1)
			{
			    /*static int tx      =  pb->allocation.x + (pb->allocation.width - 100) * 0.5;
                static int ty      =  pb->allocation.y + (pb->allocation.height - 90) * 0.5;
			    static const GdkRectangle rect = {tx,ty,100,60};
                gdk_window_invalidate_rect(GDK_WINDOW(pb->window),&rect,TRUE);*/
                gx_tuner_refresh(pb,NULL);
			}
			else if (shownote == 0)
			{
				shownote = -1;
			}
		}
};


void GxMainInterface::addNumDisplay(const char* label, float* zone )
{
	openEventBox(label);

	pb = gx_tuner_view ();
   // g_signal_connect(pb, "expose-event", G_CALLBACK(tuner_expose), NULL);

	new uiNumDisplay(this, zone, GTK_WIDGET(pb));
	gtk_widget_set_size_request(pb, 100.0, 90.0);

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
			if ((gx_engine::isMidiOn() == true) &&
			    (gx_jack::jcpu_load < 65.0))
			{
				if (v > 0.0f) gtk_status_icon_set_from_pixbuf ( GTK_STATUS_ICON(status_icon), GDK_PIXBUF(ibm));
				else  gtk_status_icon_set_from_pixbuf ( GTK_STATUS_ICON(status_icon), GDK_PIXBUF(ib));
			}
			else if (gx_engine::isMidiOn() == false)
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
}

void GxMainInterface::addLiveWaveDisplay(const char* label, float* zone , float* zone1)
{
	GtkObject* adj = gtk_adjustment_new(0.0, -1.0, 1.0, 0.0009, 10*0.0009, 0);
	new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));

	livewa = gx_wave_live_view(zone,zone1,GTK_ADJUSTMENT(adj));
	GtkWidget * box      = gtk_vbox_new (false, 4);
	GtkWidget * e_box =  gtk_event_box_new ();
	g_signal_connect(box, "expose-event", G_CALLBACK(conv_widget_expose), NULL);
	gtk_widget_set_size_request (box, 303, 82);
	gtk_widget_set_size_request (e_box, 280, 50);
	gtk_container_set_border_width (GTK_CONTAINER (box), 12);
	gtk_container_add (GTK_CONTAINER(e_box),livewa );
	gtk_container_add (GTK_CONTAINER(box),e_box );
	addWidget(label, box);
	gtk_widget_show(box);
	gtk_widget_hide(e_box);
	gtk_widget_hide(livewa);
}

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
	//addPluginMenu();
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

#ifdef EXPERIMENTAL
	sep = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menuh), sep);
	gtk_widget_show (sep);
	menuitem = gtk_check_menu_item_new_with_mnemonic ("_Experimental");
	gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
	                           GDK_e, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
	gtk_widget_show(menuitem);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuh), menuitem);
	SwitchParameter *p = new SwitchParameter("system.show_exp_window");
	fShowExpWindow.init(GTK_CHECK_MENU_ITEM(menuitem), p);
	p->changed.connect(ptr_fun(gx_engine::toggle_exp_window));
#endif

	/*-- add a separator line --*/
	sep = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menuh), sep);
	gtk_widget_show (sep);

	/*-- create Midi Controller Table menu item --*/
	menuitem = gtk_check_menu_item_new_with_mnemonic ("M_idi Controller");
	gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
	                           GDK_i, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect (
		GTK_OBJECT (menuitem), "activate",
		G_CALLBACK (MidiControllerTable::toggle), menuitem);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuh), menuitem);
	gtk_widget_show (menuitem);

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

	/*-- Create patch info menu item under Options submenu --*/
	menuitem = gtk_menu_item_new_with_mnemonic ("P_atch Info");
	gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
	                           GDK_a, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect (GTK_OBJECT (menuitem), "activate",
	                  G_CALLBACK (gx_patch), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
	gtk_widget_show (menuitem);

	/*-- add a separator line --*/
	sep = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menucont), sep);
	gtk_widget_show (sep);

	/*-- Create load presetfile menu --*/
	menuitem = gtk_menu_item_new_with_mnemonic ("Inport Pr_eset-file");
	gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
	                           GDK_e, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect (GTK_OBJECT (menuitem), "activate",
	                  G_CALLBACK (gx_load_preset_file), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
    gtk_widget_show (menuitem);

	/*-- Create save as presetfile menu--*/
	menuitem = gtk_menu_item_new_with_mnemonic ("E_xport Preset-file");
	gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
	                           GDK_x, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect (GTK_OBJECT (menuitem), "activate",
	                  G_CALLBACK (gx_save_preset_file), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
    gtk_widget_show (menuitem);

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

void reset_all_parameters(GtkWidget*, gpointer)
{
	for (ParamMap::iterator i = parameter_map.begin(); i != parameter_map.end(); i++) {
		i->second->set_std_value();
	}
}
/*
void GxMainInterface::addPluginMenu()
{
	GtkWidget* menulabel; // menu label
	GtkWidget* menucont;  // menu container
	GtkWidget* menuitem;  // menu item

	menucont = fMenuList["Top"];


	menulabel = gtk_menu_item_new_with_mnemonic ("Plu_gins");
	gtk_menu_bar_append (GTK_MENU_BAR(menucont), menulabel);
	gtk_widget_show(menulabel);

	menucont = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menucont);
	gtk_widget_show(menucont);
	fMenuList["Plugins"] = menucont;

	menuitem = gtk_menu_item_new_with_mnemonic ("_add");
	gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
	                           GDK_a, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);

	gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
	gtk_widget_show (menuitem);

	menucont = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem), menucont);
	gtk_widget_show(menucont);
	fMenuList["Plugins_add"] = menucont;

    menucont =fMenuList["Plugins"];
	menuitem = gtk_menu_item_new_with_mnemonic ("_remove");
	gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
	                           GDK_r, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);

	gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
	gtk_widget_show (menuitem);

	menucont = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem), menucont);
	gtk_widget_show(menucont);
	fMenuList["Plugins_remove"] = menucont;


}*/

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
	                  G_CALLBACK (Meterbridge::start_stop), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
	gtk_widget_show (menuitem);

	/*-- Create Open check menu item under Options submenu --*/
	menuitem = gtk_check_menu_item_new_with_mnemonic ("_Jack Capture Settings");
	gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
	                           GDK_j, GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);
	gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
	g_signal_connect(GTK_OBJECT (menuitem), "activate",
	                 G_CALLBACK (JackCaptureGui::start_stop), NULL);
	gtk_widget_show (menuitem);

	/*-- add a separator line --*/
	sep = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menucont), sep);
	gtk_widget_show (sep);

	/*-- Create skin menu under Options submenu--*/
	addGuiSkinMenu();

	/*-- create option for saving midi controller settings in presets --*/
	menuitem = gtk_check_menu_item_new_with_mnemonic ("Include MIDI in _presets");
	gtk_widget_show (menuitem);
	gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
	fMidiInPreset.init(
		GTK_CHECK_MENU_ITEM(menuitem), new SwitchParameter("system.midi_in_preset"));

	/*-- create option for resetting guitarix settings --*/
	menuitem = gtk_menu_item_new_with_mnemonic ("Reset _All Parameters");
	gtk_widget_show (menuitem);
	gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
	g_signal_connect(GTK_OBJECT(menuitem), "activate",
	                 G_CALLBACK(reset_all_parameters), NULL);
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
static void set_tooltips(bool v)
{
	gtk_settings_set_long_property(
		gtk_settings_get_default(),"gtk-enable-tooltips",v,
		"guitarix menu-option");
}

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

	/*-- Create menu item to control tooltip display --*/
	menuitem = gtk_check_menu_item_new_with_mnemonic ("Show _Tooltips");
	gtk_widget_show (menuitem);
	gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
	SwitchParameter *p = new SwitchParameter("system.show_tooltips");
	fShowTooltips.init(GTK_CHECK_MENU_ITEM(menuitem), p);
	p->changed.connect(ptr_fun(set_tooltips));

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
	                  G_CALLBACK (PortMapWindow::toggle), menuitem);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuh), menuitem);
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

//---- show main GUI
void GxMainInterface::show()
{
#ifndef NDEBUG
	ui_thread = pthread_self();
#endif
	assert(fTop == 0);
	gx_init_pixmaps();
	fInitialized = true;

	if (gx_jack::client) {
		// refresh some GUI stuff
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(fJackConnectItem), TRUE);

		GtkWidget* wd = getJackLatencyItem(gx_jack::jack_bs);
		if (wd) gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(wd), TRUE);

		string window_name = "guitarix";
		gtk_window_set_title (GTK_WINDOW (fWindow), window_name.c_str());

	} else {
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
	//----- set the state for the latency change warning widget
	gx_engine::set_latency_warning_change();

	//----- set the last used skin when no cmd is given
	int skin_index = gx_current_skin;
	if (no_opt_skin == 1)
		skin_index = gx_engine::audio.fskin;

	gx_set_skin_change(skin_index);
	gx_update_skin_menu_item(skin_index);

	/* timeout in milliseconds */
	g_threads[0] = g_timeout_add(40, gx_update_all_gui, 0);
	// Note: meter display timeout is a global var in gx_gui namespace
	g_threads[1] = g_timeout_add(meter_display_timeout, gx_refresh_meter_level,   0);

	GError* err = NULL;
	// -------------- start helper thread for ladi signal USR1 ------------
	if (g_thread_create(gx_signal_helper_thread, NULL, FALSE, &err)  == NULL) {
		gx_print_fatal("system startup", string("Thread create failed (signal): ") + err->message);
		g_error_free(err);
		return;
	}

	// -------------- start helper thread for midi control ------------
	sem_init (&program_change_sem, 0, 0);

	if (g_thread_create(gx_program_change_helper_thread, NULL, FALSE, &err)  == NULL) {
		gx_print_fatal("system startup", string("Thread create failed (midi): ") + err->message);
		g_error_free(err);
		return;
	}

	gtk_main();

	stop();
}

} /* end of gx_gui namespace */

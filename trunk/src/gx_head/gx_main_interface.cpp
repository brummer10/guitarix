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
 *    This is the gx_head GUI main class
 *
 * ----------------------------------------------------------------------------
 */

#include <iomanip>
#include <cstring>
#include <gdk/gdkkeysyms.h>
#include "guitarix.h"
#include <gtkmm/liststore.h>
#include <gtkmm/window.h>
#include <gtkmm/frame.h>
#include <gtkmm/accelgroup.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/fixed.h>

#include <gxwmm/paintbox.h>
#include <gxwmm/waveview.h>
#include <libgxw/gxw/GxKnob.h>

using namespace gx_system;
using namespace gx_child_process;
using namespace gx_preset;
using namespace gx_cairo;
using namespace gx_threads;

#define _(x) (x) //FIXME

namespace gx_gui
{

// Stock Items for Gxw::Switch

const char *sw_led = "led";
const char *sw_switch = "switch";
const char *sw_switchit = "switchit";
const char *sw_minitoggle = "minitoggle";
const char *sw_button = "button";
const char *sw_pbutton = "pbutton";
const char *sw_rbutton = "rbutton";

// Paint Functions for Gxw::PaintBox

const char *pb_amp_expose =                  "amp_expose";
const char *pb_conv_widget_expose =          "conv_widget_expose";
const char *pb_upper_widget_expose =         "upper_widget_expose";
const char *pb_rectangle_expose =            "rectangle_expose";
const char *pb_rectangle_skin_color_expose = "rectangle_skin_color_expose";
const char *pb_convolver_icon_expose =       "convolver_icon_expose";
const char *pb_AmpBox_expose =               "AmpBox_expose";
const char *pb_tribal_box_expose =           "tribal_box_expose";
const char *pb_vbox_expose =                 "vbox_expose";
const char *pb_filter_box_expose =           "filter_box_expose";
const char *pb_plug_box_expose =             "plug_box_expose";
const char *pb_info_box_expose_on =          "info_box_expose_on";
const char *pb_info_box_expose_off =         "info_box_expose_off";
const char *pb_slooper_expose =              "slooper_expose";
const char *pb_zac_expose =                  "zac_expose";
const char *pb_gxhead_expose =               "gxhead_expose";
const char *pb_RackBox_expose =              "RackBox_expose";
const char *pb_gxrack_expose =               "gxrack_expose";

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

int gx_set_mx_oriantation()
{
	return (gint) gx_gui::main_xorg;
}

int gx_set_my_oriantation()
{
	return (gint) gx_gui::main_yorg;
}

GxMainInterface::GxMainInterface(const char * name):
	fTuner(this, &gx_engine::audio.fConsta1t)
{
	highest_unseen_msg_level = -1;

	/*-- set rc file overwrite it with export--*/
	gtk_rc_parse(rcpath.c_str());

	/*-- Declare the GTK Widgets --*/
	fWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);

	/*---------------- set window defaults ----------------*/
	//gtk_widget_set_size_request (GTK_WIDGET (fWindow) , 600,205);
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
GxMainInterface* GxMainInterface::instance(const char* name)
{
	static GxMainInterface maingui(name);
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
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(tbox), GTK_WRAP_WORD_CHAR);
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

	gint boxheight = 125;
	gint boxwidth  = 47;

	gtk_container_set_border_width (GTK_CONTAINER (box), 3);
	gtk_box_set_spacing(GTK_BOX(box), 1);

	gtk_widget_set_size_request (GTK_WIDGET(box), boxwidth, boxheight);
	g_signal_connect(box, "expose-event", G_CALLBACK(level_meter_expose), NULL);
	g_signal_connect(GTK_CONTAINER(box), "check-resize",
	                 G_CALLBACK(level_meter_expose), NULL);

	// width of meter
	int width    = 8;

	// how long we hold the peak bar = hold * thread call timeout
	// Note: 30 * 80 = 2.4 sec
	int hold     = 20;

	// gx_head output levels
	GtkWidget* gxbox = gtk_hbox_new (FALSE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (gxbox), 0);
	gtk_box_set_spacing(GTK_BOX(gxbox), 25);

	for (int i = 0; i < 2; i++) {
		Gxw::FastMeter& fastmeter = fLevelMeters[i];
		fastmeter.set_hold_count(hold);
		fastmeter.property_dimen() = width;
		fastmeter.set_size_request(width, boxheight);
		fastmeter.signal_button_release_event().connect(
			sigc::mem_fun(*this, &GxMainInterface::on_meter_button_release));
		gtk_box_pack_start(GTK_BOX(gxbox), GTK_WIDGET(fastmeter.gobj()), FALSE, TRUE, 0);
		fastmeter.show();
		fastmeter.set_tooltip_text("gx_head output");
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



struct uiOrderButton : public gx_ui::GxUiItemFloat
{
	GtkButton* 	fButton;
	uiOrderButton (gx_ui::GxUI* ui, float* zone, GtkButton* b) : gx_ui::GxUiItemFloat(ui, zone), fButton(b) {}

	// box move to the right
	static void pressed_right( GtkWidget *widget, gpointer   data )
		{
			GtkWidget *box1 = gtk_widget_get_parent(GTK_WIDGET(widget));
			GtkWidget * box = gtk_widget_get_parent(GTK_WIDGET(box1));
			GtkWidget * parent = gtk_widget_get_parent(GTK_WIDGET(box));
			GValue  pos = {0};
			g_value_init (&pos, G_TYPE_INT);
			static int move = 0;
			gtk_container_child_get_property(GTK_CONTAINER(parent),GTK_WIDGET(box),"position", &pos);
			GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(parent));
			guint max_client = g_list_length (child_list)-1;
			guint per = g_value_get_int(&pos);
			if (per<max_client) 
			{
				GtkWidget *obi = (GtkWidget *) g_list_nth_data(child_list,per+1);

				child_list =  gtk_container_get_children(GTK_CONTAINER(obi));
				GtkWidget *obib = (GtkWidget *) g_list_nth_data(child_list,1);
				child_list =  gtk_container_get_children(GTK_CONTAINER(obib));
				GtkWidget *obibi = (GtkWidget *) g_list_nth_data(child_list,0);

				gtk_box_reorder_child (GTK_BOX(parent),GTK_WIDGET(box),per +1);
				((gx_ui::GxUiItemFloat*)data)->modifyZone(per+1);
				/*child_list =  gtk_container_get_children(GTK_CONTAINER(box));
				GtkWidget *plug = (GtkWidget *) g_list_nth_data(child_list,1);
				string name = gtk_widget_get_name(plug);
				fprintf(stderr, " %i %s .pressed right\n",per,name.c_str()); */
				if(GTK_IS_BUTTON (obibi)) {
                    gtk_button_clicked(GTK_BUTTON(obibi));
				} else {
				    child_list =  gtk_container_get_children(GTK_CONTAINER(obi));
				    obib = (GtkWidget *) g_list_nth_data(child_list,1);
				   // name = gtk_widget_get_name(obib);
					//fprintf(stderr, " %i %s .next child right\n",per,name.c_str()); 
					if(!GDK_IS_WINDOW (obib->window)) {
						//fprintf(stderr, " %i %s.hidden\n",per,name.c_str()); 
						move =1;
					} else move= 0;
					obib = (GtkWidget *) g_list_nth_data(child_list,3);
					  
					if(GTK_IS_CONTAINER(obib)){
					child_list =  gtk_container_get_children(GTK_CONTAINER(obib));
					obibi = (GtkWidget *) g_list_nth_data(child_list,0);
						if(GTK_IS_BUTTON (obibi)) {
							gtk_button_clicked(GTK_BUTTON(obibi));
							if(move) gtk_button_pressed(GTK_BUTTON(widget));
							
						}
					} 
				}
			}
			g_list_free(child_list);
		}
	// box move to the left
	static void pressed_left( GtkWidget *widget, gpointer   data )
		{

			GtkWidget *box1 = gtk_widget_get_parent(GTK_WIDGET(widget));
			GtkWidget * box = gtk_widget_get_parent(GTK_WIDGET(box1));
			GtkWidget * parent = gtk_widget_get_parent(GTK_WIDGET(box));
			GValue  pos = {0};
			g_value_init (&pos, G_TYPE_INT);
			static int move = 0;
			gtk_container_child_get_property(GTK_CONTAINER(parent),GTK_WIDGET(box),"position", &pos);
			guint per = g_value_get_int(&pos);
			if (per>1)
			{
				GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(parent));
				GtkWidget *obi = (GtkWidget *) g_list_nth_data(child_list,per-1);
				
				child_list =  gtk_container_get_children(GTK_CONTAINER(obi));
				GtkWidget *obib = (GtkWidget *) g_list_nth_data(child_list,1);
				child_list =  gtk_container_get_children(GTK_CONTAINER(obib));
				GtkWidget *obibi = (GtkWidget *) g_list_nth_data(child_list,1);

				gtk_box_reorder_child (GTK_BOX(parent),GTK_WIDGET(box),per -1);
				((gx_ui::GxUiItemFloat*)data)->modifyZone(per-1);
				/*child_list =  gtk_container_get_children(GTK_CONTAINER(box));
				GtkWidget *plug = (GtkWidget *) g_list_nth_data(child_list,1);
				string name = gtk_widget_get_name(plug);
				fprintf(stderr, " %i %s .pressed left\n",per,name.c_str()); */
				if(GTK_IS_BUTTON (obibi)){
                    gtk_button_clicked(GTK_BUTTON(obibi));
				} else {
					child_list =  gtk_container_get_children(GTK_CONTAINER(obi));
					obib = (GtkWidget *) g_list_nth_data(child_list,1);
					//name = gtk_widget_get_name(obib);
					//fprintf(stderr, " %i %s .next child left\n",per,name.c_str()); 
					if(!GDK_IS_WINDOW (obib->window)) {
						//fprintf(stderr, " %i %s.hidden\n",per,name.c_str()); 
						move =1;
					} else move= 0;
					obib = (GtkWidget *) g_list_nth_data(child_list,3);
					
				    if(GTK_IS_CONTAINER(obib)){
						child_list =  gtk_container_get_children(GTK_CONTAINER(obib));
						obibi = (GtkWidget *) g_list_nth_data(child_list,1);
						if(GTK_IS_BUTTON (obibi)) {
							gtk_button_clicked(GTK_BUTTON(obibi));
							if(move)
							gtk_button_pressed(GTK_BUTTON(widget));
							
						}
					}
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
			if(GDK_IS_WINDOW (box->window))
			 gdk_window_invalidate_rect(box->window,NULL,true);

			((gx_ui::GxUiItemFloat*)data)->modifyZone(per);
			/*GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(box));
			GtkWidget *plug = (GtkWidget *) g_list_nth_data(child_list,1);
			const gchar *name = gtk_widget_get_name(plug);
			fprintf(stderr, " %i %s .clicked\n",per,name); 
			
			 g_list_free(child_list);*/
		}
	// set the init order
	virtual void reflectZone()
		{

			float 	v = *fZone;
			fCache = v;
			GValue  pos = {0};

			g_value_init (&pos, G_TYPE_INT);
			g_value_set_int(&pos,(gint)v);

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
	GtkWidget * box = gtk_hbox_new (homogene, 0);
	GtkWidget * box1 = gtk_fixed_new ();
	gtk_container_set_border_width (GTK_CONTAINER (box), 4);
	//gtk_widget_set_size_request (GTK_WIDGET (box) , 500,40);
	g_signal_connect(box, "expose-event", G_CALLBACK(zac_expose), NULL);

	GtkWidget* 	button = gtk_button_new ();
	GtkWidget* 	button1 = gtk_button_new ();
	GtkWidget* lw = gtk_label_new("▼");
	GtkWidget* lw1 = gtk_label_new("▲");
	//GtkWidget* lw2 = gtk_label_new(label);
	gtk_container_add (GTK_CONTAINER(button), lw);
	gtk_container_add (GTK_CONTAINER(button1), lw1);
	//gtk_container_add (GTK_CONTAINER(box), lw2);
	gtk_widget_set_size_request (GTK_WIDGET(button), 20, 15);
	gtk_widget_set_size_request (GTK_WIDGET(button1), 20, 15);

	gtk_widget_set_name (lw,"rack_label");
	gtk_widget_set_name (lw1,"rack_label");
	gtk_widget_set_name (button,"effect_reset");
	gtk_widget_set_name (button1,"effect_reset");
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

	gtk_box_pack_start (GTK_BOX(rBox), box, expand, fill, 0);
	
	GValue  pos = {0};
	float z = *posit;
	gint poset = int(z);
	//fprintf(stderr, " %i .monobox\n",poset);
	g_value_init (&pos, G_TYPE_INT);
	g_value_set_int(&pos,poset);
	gtk_container_child_set_property(GTK_CONTAINER(rBox),GTK_WIDGET(box),"position", &pos);
	
	gtk_fixed_put (GTK_FIXED(box1), button1, 5, 5);
	gtk_fixed_put (GTK_FIXED(box1), button, 5, 20);
	gtk_box_pack_end (GTK_BOX(box), box1, false, fill, 0);
	gtk_widget_show_all(button);
	gtk_widget_show_all(button1);
	//gtk_widget_show(box);
	gtk_widget_show(box1);
	pushBox(kBoxMode, box);

}

void GxMainInterface::openHorizontalRestetBox(const char* label,float* posit)
{
	GtkWidget * box = gtk_hbox_new (homogene, 0);
	GtkWidget * box1 = gtk_fixed_new ();
	gtk_container_set_border_width (GTK_CONTAINER (box), 4);
	//gtk_widget_set_size_request (GTK_WIDGET (box) , 500,40);
	g_signal_connect(box, "expose-event", G_CALLBACK(zac_expose), NULL);

	GtkWidget* 	button = gtk_button_new ();
	GtkWidget* 	button1 = gtk_button_new ();
	GtkWidget* lw = gtk_label_new("▼");
	GtkWidget* lw1 = gtk_label_new("▲");
	//GtkWidget* lw2 = gtk_label_new(label);
	gtk_container_add (GTK_CONTAINER(button), lw);
	gtk_container_add (GTK_CONTAINER(button1), lw1);
	//gtk_container_add (GTK_CONTAINER(box), lw2);
	gtk_widget_set_size_request (GTK_WIDGET(button), 20, 15);
	gtk_widget_set_size_request (GTK_WIDGET(button1), 20, 15);

	gtk_widget_set_name (lw,"rack_label");
	gtk_widget_set_name (lw1,"rack_label");
	gtk_widget_set_name (button,"effect_reset");
	gtk_widget_set_name (button1,"effect_reset");
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


	gtk_box_pack_start (GTK_BOX(sBox), box, expand, fill, 0);
	
	GValue  pos = {0};
	float z = *posit;
	gint poset = int(z);
	//fprintf(stderr, " %i .stereo box\n",poset);
	g_value_init (&pos, G_TYPE_INT);
	g_value_set_int(&pos, poset);
	
	gtk_container_child_set_property(GTK_CONTAINER(sBox),GTK_WIDGET(box),"position", &pos);
	
	gtk_fixed_put (GTK_FIXED(box1), button1, 5, 5);
	gtk_fixed_put (GTK_FIXED(box1), button, 5, 20);
	gtk_box_pack_end (GTK_BOX(box), box1, false, fill, 0);
	gtk_widget_show_all(button);
	gtk_widget_show_all(button1);
	//gtk_widget_show(box);
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
	gtk_widget_set_size_request (GTK_WIDGET (box) , 600,182);

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

struct uiExpanderBox : public gx_ui::GxUiItemFloat
{
	GtkExpander* fButton;
	uiExpanderBox(gx_ui::GxUI* ui, float* zone, GtkExpander* b) : gx_ui::GxUiItemFloat(ui, zone), fButton(b) {}
	static void expanded (GtkWidget *widget, gpointer data)
		{
			float v = gtk_expander_get_expanded  (GTK_EXPANDER(widget));

			if (v == 1.000000)
				v = 0;
			else v = 1;

			((gx_ui::GxUiItemFloat*)data)->modifyZone(v);
		}

	virtual void reflectZone()
		{
			float 	v = *fZone;
			fCache = v;
			gtk_expander_set_expanded(GTK_EXPANDER(fButton), (int)v);
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
	//g_signal_connect(box, "expose-event", G_CALLBACK(vbox_expose), NULL);

	if (fMode[fTop] != kTabMode && label[0] != 0)
	{
		GtkWidget* lw = gtk_label_new(label);


		gtk_widget_set_name (lw,"rack_label");
		GtkStyle *style = gtk_widget_get_style(lw);
		pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
		pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
		gtk_widget_modify_font(lw, style->font_desc);

		gtk_box_pack_start(GTK_BOX(box), lw, false, false, 0);
		gtk_box_pack_start (GTK_BOX(fBox[fTop]), box, false, fill, 0);
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
		gtk_widget_set_size_request (GTK_WIDGET (lw) , 15,-1);

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



void GxMainInterface::openPaintBox(const char* label, const char* name)
{
	GtkWidget *box = gtk_hbox_new(homogene, 2);
	if (name) {
		gtk_widget_set_name(box, name);
	}
	gtk_container_set_border_width(GTK_CONTAINER (box), 4);
	g_signal_connect(box, "expose-event", G_CALLBACK(zac_expose), NULL);

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
	GtkWidget * box = gtk_vbox_new (homogene, 0);
	gtk_container_set_border_width (GTK_CONTAINER (box), 2);
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

void GxMainInterface::openPaintBox1(const char* label)
{
	GtkWidget * box = gtk_vbox_new (homogene, 0);
	gtk_container_set_border_width (GTK_CONTAINER (box), 0);
	//g_signal_connect(box, "expose-event", G_CALLBACK(amp_expose), NULL);

	
		gtk_box_pack_start (GTK_BOX(fBox[fTop]), box, false, false, 0);
		gtk_widget_show(box);
		pushBox(kBoxMode, box);
	
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
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrollbox),GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);
	gtk_widget_set_size_request (scrollbox, -1, -1);
	GtkWidget * box = gtk_vbox_new (homogene, 0);
	GtkWidget * box1 = gtk_hbox_new (homogene, 0);
	gtk_container_set_border_width (GTK_CONTAINER (box), 0);
	g_signal_connect(box, "expose-event", G_CALLBACK(rectangle_skin_color_expose), NULL);

	//GtkWidget* 	button = gtk_button_new ();

	//g_signal_connect (GTK_OBJECT (button), "clicked",
	//                  G_CALLBACK (uiOrderButton::resize), NULL);

	//gtk_widget_set_size_request (GTK_WIDGET(button), 10, -1);
	//gtk_container_add (GTK_CONTAINER(box1), button);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrollbox),GTK_WIDGET(box));
	gtk_container_add (GTK_CONTAINER(box1), scrollbox);
	gtk_container_add (GTK_CONTAINER(fBox[fTop]), box1);
	gtk_widget_show_all(box1);
	pushBox(kBoxMode, box);

}

struct uiSwitchDISTBox : public gx_ui::GxUiItemFloat
{
	GtkWidget* fbox;

	uiSwitchDISTBox(gx_ui::GxUI* ui, float* zone, GtkWidget* box)
		: gx_ui::GxUiItemFloat(ui, zone), fbox(box) {}

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
			g_list_free(child_list);
		}
};

struct uiSwitchEQBox : public gx_ui::GxUiItemFloat
{
	GtkWidget* fbox;

	uiSwitchEQBox(gx_ui::GxUI* ui, float* zone, GtkWidget* box)
		: gx_ui::GxUiItemFloat(ui, zone), fbox(box) {}

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
			g_list_free(child_list);
		}
};

struct uiSwitchAMPBox : public gx_ui::GxUiItemFloat
{
	GtkWidget* fbox;

	uiSwitchAMPBox(gx_ui::GxUI* ui, float* zone, GtkWidget* box)
		: gx_ui::GxUiItemFloat(ui, zone), fbox(box) {}

	virtual void reflectZone()
		{
            GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(fbox));

			GtkWidget *box0 = (GtkWidget *) g_list_nth_data(child_list,0);
			GtkWidget *box1 = (GtkWidget *) g_list_nth_data(child_list,1);
			if(fCache != *fZone) {
			fCache = *fZone;
			if (fCache == 1)
			{
			    //if(gx_engine::audio.fdialogbox_eq ==1)
                //    gx_engine::audio.fdialogbox_eqs = 1;
                gtk_widget_hide(box0);
                gx_engine::audio.famp2 = 1;
               // gx_engine::audio.fdialogbox_eq = 0;
                gtk_widget_show(box1);
			}
			else if (fCache == 0)
			{
			   // if(gx_engine::audio.fdialogbox_eqs ==1)
               //     gx_engine::audio.fdialogbox_eq = 1;
				gtk_widget_hide(box1);
                gx_engine::audio.famp2 = 0;
			//	gx_engine::audio.fdialogbox_eqs = 0;
                gtk_widget_show(box0);
			}
			}
			g_list_free(child_list);
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
       else if(wit == 2) new uiSwitchAMPBox(this, zone, GTK_WIDGET(box));
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

struct uiButton : public gx_ui::GxUiItemFloat
{
	GtkButton* 	fButton;
	uiButton(gx_ui::GxUI* ui, float* zone, GtkButton* b) : gx_ui::GxUiItemFloat(ui, zone), fButton(b) {}
	static void pressed( GtkWidget *widget, gpointer   data )
		{
			gx_ui::GxUiItemFloat* c = (gx_ui::GxUiItemFloat*)data;
			c->modifyZone(1.0);
		}

	static void released( GtkWidget *widget, gpointer   data )
		{
			gx_ui::GxUiItemFloat* c = (gx_ui::GxUiItemFloat*) data;
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

struct uiToggleButton : public gx_ui::GxUiItemFloat
{
	GtkToggleButton* fButton;
	uiToggleButton(gx_ui::GxUI* ui, float* zone, GtkToggleButton* b) : gx_ui::GxUiItemFloat(ui, zone), fButton(b) {}
	static void toggled (GtkWidget *widget, gpointer data)
		{
			float	v = (GTK_TOGGLE_BUTTON (widget)->active) ? 1.0 : 0.0;
			((gx_ui::GxUiItemFloat*)data)->modifyZone(v);
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

#if 1
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
	gtk_widget_set_size_request (GTK_WIDGET(button), 60, 20);
	GtkWidget * box = gtk_hbox_new (homogene, 4);
	GtkWidget * box1 = gtk_vbox_new (homogene, 4);
	gtk_container_set_border_width (GTK_CONTAINER (box), 0);
	gtk_container_set_border_width (GTK_CONTAINER (box1), 0);
	gtk_container_add (GTK_CONTAINER(box), box1);
	GtkWidget * box2 = gtk_vbox_new (homogene, 4);
	gtk_container_set_border_width (GTK_CONTAINER (box2), 0);
	gtk_widget_set_size_request (GTK_WIDGET(box2), 6, 20);
	gtk_container_add (GTK_CONTAINER(box), button);
	gtk_container_add (GTK_CONTAINER(box), box2);
	gtk_widget_set_size_request (GTK_WIDGET(box1), 6, 20);
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
#endif

static bool conv_start()
{
	gx_jconv::GxJConvSettings* jcset = gx_jconv::GxJConvSettings::instance();
	string path = jcset->getFullIRPath();
	if (path.empty()) {
		gx_system::gx_print_warning("convolver", "no impulseresponse file");
		return false;
	}
	while (!gx_engine::conv.checkstate());
	if (!gx_engine::conv.configure(
		    gx_jack::jack_bs, gx_jack::jack_sr, path,
		    jcset->getGain(), jcset->getGain(), jcset->getDelay(), jcset->getDelay(),
		    jcset->getOffset(), jcset->getLength(), 0, 0, jcset->getGainline())) {
		return false;
	}
	return gx_engine::conv.start();
}

void conv_restart()
{
	gx_engine::conv.stop();
	conv_start();
}

void gx_start_stop_jconv(GtkWidget *widget, gpointer data)
{
	if (gx_jconv::GxJConvSettings::checkbutton7 == 0) {
		gx_engine::conv.stop();
	} else {
		gx_jconv::gx_save_jcgui();
		if (!conv_start()) {
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

struct uiCheckButton : public gx_ui::GxUiItemFloat
{
	GtkToggleButton* fButton;
	uiCheckButton(gx_ui::GxUI* ui, float* zone, GtkToggleButton* b) : gx_ui::GxUiItemFloat(ui, zone), fButton(b) {}
	static void toggled (GtkWidget *widget, gpointer data)
		{
			float	v = (GTK_TOGGLE_BUTTON (widget)->active) ? 1.0 : 0.0;
			((gx_ui::GxUiItemFloat*)data)->modifyZone(v);
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

// -------------------------- Horizontal Slider -----------------------------------

struct uiValueDisplay : public gx_ui::GxUiItemFloat
{
	GtkLabel* fLabel;
	int	fPrecision ;

	uiValueDisplay(gx_ui::GxUI* ui, float* zone, GtkLabel* label, int precision)
		: gx_ui::GxUiItemFloat(ui, zone), fLabel(label), fPrecision(precision) {}

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

#if 1
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
#endif

/****************************************************************
 ** UiRegler, UiSwitch
 */

void UiRegler::on_value_changed()
{
	modifyZone(get_value());
}

void UiRegler::reflectZone()
{
	float 	v = *fZone;
	fCache = v;
	set_value(v);
}

GtkWidget *UiRegler::create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id, bool show_value)
{
	if (!parameter_map.hasId(id)) {
		return 0;
	}
	return (new UiRegler(ui, parameter_map[id].getFloat(), regler, show_value))->get_widget();
}

UiRegler::UiRegler(gx_ui::GxUI &ui, FloatParameter &param, Gxw::Regler *regler, bool show_value):
	gx_ui::GxUiItemFloat(&ui, &param.value),
	Gtk::Adjustment(param.std_value, param.lower, param.upper, param.step, 10*param.step, 0),
	m_regler(regler)
{
	m_regler->set_show_value(show_value);
	m_regler->cp_set_var(param.id());
	m_regler->set_adjustment(*this);
	m_regler->show();
	param.value = param.std_value;
	connect_midi_controller(GTK_WIDGET(m_regler->gobj()), &param.value);
}

UiRegler::~UiRegler()
{
	delete m_regler;
}

UiSelector::UiSelector()
{
	m_selector.show();
}

void UiSelectorFloat::on_value_changed()
{
	modifyZone(get_value());
}

void UiSelectorInt::on_value_changed()
{
	modifyZone((int)get_value());
}

GtkWidget* UiSelector::create(gx_ui::GxUI& ui, string id)
{
	Parameter& p = parameter_map[id];
	UiSelector *s;
	if (p.isFloat()) {
		s = new UiSelectorFloat(ui, p.getFloat());
	} else {
		s = new UiSelectorInt(ui, p.getInt());
	}
	return s->get_widget();
}

void UiSelector::init(Parameter& param)
{
	m_selector.cp_set_var(param.id());
	Gtk::TreeModelColumn<Glib::ustring> label;
	Gtk::TreeModelColumnRecord rec;
	rec.add(label);
	Glib::RefPtr<Gtk::ListStore> ls = Gtk::ListStore::create(rec);
	for (const char **p = param.getValueNames(); *p; p++) {
		ls->append()->set_value(0, Glib::ustring(*p));
	}
	m_selector.set_model(ls);
}

UiSelectorFloat::UiSelectorFloat(gx_ui::GxUI& ui, FloatParameter &param):
	gx_ui::GxUiItemFloat(&ui, &param.value),
	Gtk::Adjustment(param.std_value, param.lower, param.upper, param.step, 10*param.step, 0)
{
	m_selector.set_adjustment(*this);
	init(param);
}

void UiSelectorFloat::reflectZone()
{
	float v = *fZone;
	fCache = v;
	set_value(v);
}

void UiSelectorInt::reflectZone()
{
	int v = *fZone;
	fCache = v;
	set_value(v);
}

UiSelectorInt::UiSelectorInt(gx_ui::GxUI& ui, IntParameter &param):
	gx_ui::GxUiItemInt(&ui, &param.value),
	Gtk::Adjustment(param.std_value, param.lower, param.upper, 1, 5, 0)
{
	m_selector.set_adjustment(*this);
	init(param);
}

GtkWidget* UiReglerWithCaption::create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id, bool show_value)
{
	if (!parameter_map.hasId(id)) {
		return 0;
	}
	return create(ui, regler, id, parameter_map[id].name(), show_value);
}

GtkWidget* UiReglerWithCaption::create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id, Glib::ustring label, bool show_value)
{
	if (!parameter_map.hasId(id)) {
		return 0;
	}
	return (new UiReglerWithCaption(ui, parameter_map[id].getFloat(), regler, label, show_value))->get_widget();
}

GtkWidget* UiRackReglerWithCaption::create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id)
{
	if (!parameter_map.hasId(id)) {
		return 0;
	}
	return create(ui, regler, id, parameter_map[id].name());
}

GtkWidget* UiRackReglerWithCaption::create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id, Glib::ustring label)
{
	if (!parameter_map.hasId(id)) {
		return 0;
	}
	return (new UiRackReglerWithCaption(ui, parameter_map[id].getFloat(), regler, label))->get_widget();
}

GtkWidget* UiRackRegler::create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id)
{
	if (!parameter_map.hasId(id)) {
		return 0;
	}
	return create(ui, regler, id, parameter_map[id].name());
}

GtkWidget* UiRackRegler::create(gx_ui::GxUI& ui, Gxw::Regler *regler, string id, Glib::ustring label)
{
	if (!parameter_map.hasId(id)) {
		return 0;
	}
	return (new UiRackRegler(ui, parameter_map[id].getFloat(), regler, label))->get_widget();
}
UiReglerWithCaption::UiReglerWithCaption(gx_ui::GxUI &ui, FloatParameter &param, Gxw::Regler *regler,
                                         Glib::ustring label, bool show_value):
	UiRegler(ui, param, regler, show_value)
{
	m_label.set_text(label);
	m_label.set_name("effekt_label");
	m_box.set_name(param.id());
	m_box.pack_start(m_label, Gtk::PACK_SHRINK);
	m_box.pack_start(*m_regler, Gtk::PACK_SHRINK);
	m_box.show_all();
}

UiRackReglerWithCaption::UiRackReglerWithCaption(gx_ui::GxUI &ui, FloatParameter &param, Gxw::Regler *regler,
                                         Glib::ustring label):
	UiRegler(ui, param, regler, true)
{
	m_label.set_text(label);
	m_label.set_name("rack_label");
	m_box.set_name(param.id());
	m_box.pack_start(m_label, Gtk::PACK_SHRINK);
	m_box.pack_start(*m_regler, Gtk::PACK_SHRINK);
	m_box.show_all();
}

UiRackRegler::UiRackRegler(gx_ui::GxUI &ui, FloatParameter &param, Gxw::Regler *regler,
                                         Glib::ustring label):
	UiRegler(ui, param, regler, true)
{
	m_box.set_name(param.id());
	m_box.pack_start(*m_regler, Gtk::PACK_SHRINK);
	m_box.show_all();
}

UiSwitch::UiSwitch(const char *sw_type):
	Switch(sw_type)
{
}

UiSwitch *UiSwitch::new_switch(gx_ui::GxUI& ui, const char* sw_type, Parameter& param)
{
	if (param.isFloat()) {
		return new UiSwitchFloat(ui, sw_type, param.getFloat());
	} else {
		return new UiSwitchBool(ui, sw_type, param.getBool());
	}
}

void UiSwitchFloat::on_toggled()
{
	modifyZone(get_active());
}

void UiSwitchFloat::reflectZone()
{
	float v = *fZone;
	fCache = v;
	set_active(v != 0.0);
}

UiSwitchFloat::UiSwitchFloat(gx_ui::GxUI& ui, const char *sw_type, FloatParameter &param):
	UiSwitch(sw_type),
	gx_ui::GxUiItemFloat(&ui, &param.value)
{
	param.set_std_value();
	set_active(param.value != 0.0);
	cp_set_var(param.id());
	connect_midi_controller(GTK_WIDGET(gobj()), fZone);
	show();
}

void UiSwitchBool::on_toggled()
{
	modifyZone(get_active());
}

void UiSwitchBool::reflectZone()
{
	bool v = *fZone;
	fCache = v;
	set_active(v != 0);
}

UiSwitchBool::UiSwitchBool(gx_ui::GxUI& ui, const char *sw_type, BoolParameter &param):
	UiSwitch(sw_type),
	gx_ui::GxUiItemBool(&ui, &param.value)
{
	param.set_std_value();
	set_active(param.value);
	cp_set_var(param.id());
	connect_midi_controller(GTK_WIDGET(gobj()), fZone);
	show();
}

GtkWidget* UiSwitchWithCaption::create(
	gx_ui::GxUI& ui, const char *sw_type, string id, Gtk::PositionType pos)
{
	if (!parameter_map.hasId(id)) {
		return 0;
	}
	return create(ui, sw_type, id, parameter_map[id].name(), pos);
}

GtkWidget* UiSwitchWithCaption::create(
	gx_ui::GxUI& ui, const char *sw_type, string id, Glib::ustring label, Gtk::PositionType pos)
{
	if (!parameter_map.hasId(id)) {
		return 0;
	}
	return (new UiSwitchWithCaption(ui, sw_type, parameter_map[id], label, pos))->get_widget();
}

UiSwitchWithCaption::UiSwitchWithCaption(gx_ui::GxUI &ui, const char *sw_type, Parameter &param,
                                         Glib::ustring label, Gtk::PositionType pos):
	m_switch(UiSwitch::new_switch(ui, sw_type, param))
{
	m_label.set_text(label);
	m_label.set_name("effekt_label");
	if (pos == Gtk::POS_LEFT || pos == Gtk::POS_RIGHT) {
		m_box = new Gtk::HBox();
	} else {
		m_box = new Gtk::VBox();
	}
	if (pos == Gtk::POS_LEFT || pos == Gtk::POS_TOP) {
		m_box->pack_start(m_label, Gtk::PACK_SHRINK);
		m_box->pack_start(*m_switch, Gtk::PACK_SHRINK);
	} else {
		m_box->pack_start(*m_switch, Gtk::PACK_SHRINK);
		m_box->pack_start(m_label, Gtk::PACK_SHRINK);
	}
	m_box->set_name(param.id());
	m_box->show_all();
}

UiSwitchWithCaption::~UiSwitchWithCaption()
{
	delete m_switch;
	delete m_box;
}

UiCabSwitch::UiCabSwitch(gx_ui::GxUI &ui, Parameter &param, Glib::ustring label):
	UiSwitchWithCaption(ui, sw_minitoggle, param, label, Gtk::POS_RIGHT)
{
	m_switch->signal_toggled().connect(sigc::mem_fun(*this, &UiCabSwitch::on_switch_toggled));
}

GtkWidget* UiCabSwitch::create(gx_ui::GxUI& ui, string id, Glib::ustring label)
{
	if (!parameter_map.hasId(id)) {
		return 0;
	}
	return (new UiCabSwitch(ui, parameter_map[id], label))->get_widget();
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

static void set_label(MenuCheckItem& item , const char *label)
{
	dynamic_cast<Gtk::Label*>(item.get_child())->set_text_with_mnemonic(label);
}

/****************************************************************
 ** Effect Dialog Boxes
 */
class GxDialogButtonBox
{
public:
	Gtk::HBox box;
	UiSwitchBool show_dialog;
	
	GxDialogButtonBox(gx_ui::GxUI& ui, Parameter& param_dialog);
};

GxDialogButtonBox::GxDialogButtonBox(gx_ui::GxUI& ui, Parameter& param_dialog):
	box(false, 0),
	show_dialog(ui, sw_button, param_dialog.getBool())
{
	//show_dialog.modify_bg(Gtk::STATE_NORMAL, Gdk::Color("#7f7f7f"));
	//show_dialog.modify_bg(Gtk::STATE_ACTIVE, Gdk::Color("#000094"));
	box.set_border_width(0);
	//box.add(show_dialog);
	box.show_all();
}

class GxDialogWindowBox
{
private:
	void on_dialog_button_toggled();
	void on_reset_button_pressed();
	void on_dialog_menu_activate();
	bool on_window_delete_event(GdkEventAny* event);
	Glib::ustring group_id;
public:
	
	Gtk::HBox box;
	Gxw::PaintBox paintbox;
	Gtk::HBox box4;
	Gtk::HBox box5;
	Gtk::HBox box6;
	UiSwitch* unit_on_off;
	MenuCheckItem menuitem;
	//Gtk::Label label;
	Gtk::Button reset_button;
	Gtk::Button reset_button1;
	Gtk::ToggleButton& dialog_button;
	GxDialogWindowBox(gx_ui::GxUI& ui, const char *expose_funk, Parameter& param_dialog, Parameter& param_switch, Gtk::ToggleButton& button,GtkWidget * Caller);
	~GxDialogWindowBox();
};

GxDialogWindowBox::~GxDialogWindowBox()
{
	delete unit_on_off;
}

void GxDialogWindowBox::on_dialog_button_toggled()
{
	gx_show_extended_settings(GTK_WIDGET(dialog_button.gobj()), (gpointer)paintbox.gobj());
	GtkWidget *box = gtk_widget_get_parent(GTK_WIDGET(paintbox.gobj()));
	if(GDK_IS_WINDOW(box->window))
		gdk_window_invalidate_rect(box->window,NULL,true);
}

void GxDialogWindowBox::on_dialog_menu_activate()
{
	gx_show_menu_settings(GTK_WIDGET(menuitem.gobj()), (gpointer)paintbox.gobj());
	GtkWidget *box = gtk_widget_get_parent(GTK_WIDGET(paintbox.gobj()));
	if(GDK_IS_WINDOW(box->window)){
		gdk_window_invalidate_rect(box->window,NULL,true);
	} 
	if (!menuitem.get_active()){
		string group = group_id;
		group += ".on_off";
		parameter_map[group].set_std_value();
	}
}

void GxDialogWindowBox::on_reset_button_pressed()
{
	gx_reset_units(group_id);
}

GxDialogWindowBox::GxDialogWindowBox(gx_ui::GxUI& ui,const char *expose_funk, Parameter& param_dialog,
                                     Parameter& param_switch, Gtk::ToggleButton& button,GtkWidget * Caller):
	
	box(false, 0),
	unit_on_off( UiSwitch::new_switch(ui, sw_led, param_switch)),
	dialog_button(button)
{
	group_id = param_dialog.id().substr(0, param_dialog.id().find_last_of(".")).c_str();
	Glib::ustring title = param_dialog.group();
	
	box.set_border_width(2);
	box4.set_spacing(2);
	box4.set_border_width(2);
	box5.set_border_width(4);
	box6.set_border_width(4);
	paintbox.property_paint_func() = expose_funk;
	paintbox.set_name(title);
	//Pango::FontDescription font = label.get_style()->get_font();
	//font.set_size(10*Pango::SCALE);
	//font.set_weight(Pango::WEIGHT_NORMAL);
	//label.modify_font(font);
	//label.set_angle(90);
	//label.set_text("reset");
	//reset_button.add(label);
	reset_button.set_name("effect_reset");
	reset_button1.set_name("effect_reset");
	//label.set_name("label_reset");
	//box5.put(*unit_on_off,6,5);
	box5.add(reset_button);
	box6.add(reset_button1);
	box5.set_size_request(15,-1); 
	box6.set_size_request(15,-1); 
	reset_button.signal_pressed().connect(
		sigc::mem_fun(*this, &GxDialogWindowBox::on_reset_button_pressed));
	reset_button1.signal_pressed().connect(
		sigc::mem_fun(*this, &GxDialogWindowBox::on_reset_button_pressed));
	box4.pack_start(box6,false,false,0);
	box4.pack_start(box,true,true,0);	
	box4.pack_end(box5,false,false,0);
	paintbox.add(box4);
	dialog_button.signal_toggled().connect(
		sigc::mem_fun(*this, &GxDialogWindowBox::on_dialog_button_toggled));
	menuitem.signal_activate().connect(
		sigc::mem_fun(*this, &GxDialogWindowBox::on_dialog_menu_activate));
}

void GxMainInterface::openDialogBox(const char *id_dialog, const char *id_switch, const char *expose_funk )
{
	Parameter& param_dialog = parameter_map[id_dialog];
	Parameter& param_switch = parameter_map[id_switch];
	
	
	GxDialogButtonBox *bbox = new GxDialogButtonBox(*this, param_dialog);

	GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(rBox));
	GtkWidget *child = (GtkWidget *) g_list_nth_data(child_list,mono_plugs);
	mono_plugs++;
	g_list_free(child_list);
	gtk_box_pack_end (GTK_BOX(child),GTK_WIDGET(bbox->box.gobj()) , false, false, 0);
	GxDialogWindowBox *dialog = new GxDialogWindowBox(*this, expose_funk, param_dialog, param_switch, bbox->show_dialog, rack_widget);
	gtk_box_pack_start (GTK_BOX(child),GTK_WIDGET(dialog->paintbox.gobj()) , true, fill, 0);
	pushBox(kBoxMode, GTK_WIDGET(dialog->box.gobj()));
	
	const gchar * title = gtk_widget_get_name(GTK_WIDGET(dialog->paintbox.gobj()));
	string p = "ui.";
	p +=title;
	set_label(dialog->menuitem,title );
	//guint accel_key = GDK_1  + mono_plugs - 3;
	//dialog->menuitem.add_accelerator("activate", Glib::wrap(fAccelGroup, true),
	//                           accel_key, Gdk::ModifierType(GDK_CONTROL_MASK|GDK_SHIFT_MASK), Gtk::ACCEL_VISIBLE);  //FIXME MOD1_MASK 
	gtk_menu_shell_append(GTK_MENU_SHELL(fMenuList["PluginsMono"]), GTK_WIDGET(dialog->menuitem.gobj()));
	dialog->menuitem.show();
	dialog->menuitem.set_parameter(new SwitchParameter(p,true,false));
	
	
	
	
}

void GxMainInterface::opensDialogBox(const char *id_dialog, const char *id_switch, const char *expose_funk )
{
	Parameter& param_dialog = parameter_map[id_dialog];
	Parameter& param_switch = parameter_map[id_switch];
	GxDialogButtonBox *bbox = new GxDialogButtonBox(*this, param_dialog);
	
	GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(sBox));
	GtkWidget *child = (GtkWidget *) g_list_nth_data(child_list,stereo_plugs);
	stereo_plugs++;
	g_list_free(child_list);
	gtk_box_pack_end (GTK_BOX(child),GTK_WIDGET(bbox->box.gobj()) , false, false, 0);
	GxDialogWindowBox *bdialog = new GxDialogWindowBox(*this, expose_funk, param_dialog, param_switch, bbox->show_dialog, srack_widget);
	gtk_box_pack_start (GTK_BOX(child),GTK_WIDGET(bdialog->paintbox.gobj()) , true, fill, 0);
	pushBox(kBoxMode, GTK_WIDGET(bdialog->box.gobj()));
	
	const gchar * title = gtk_widget_get_name(GTK_WIDGET(bdialog->paintbox.gobj()));
	set_label(bdialog->menuitem,title );
	string p = "ui.";
	p +=title;
	string s;
	
	//guint accel_key = GDK_1  + stereo_plugs - 3;
	//bdialog->menuitem.add_accelerator("activate", Glib::wrap(fAccelGroup, true),
	//                           accel_key, Gdk::SHIFT_MASK, Gtk::ACCEL_VISIBLE);  //FIXME 
	gtk_menu_shell_append(GTK_MENU_SHELL(fMenuList["PluginsStereo"]), GTK_WIDGET(bdialog->menuitem.gobj()));
	bdialog->menuitem.show();
	bdialog->menuitem.set_parameter(new SwitchParameter(p,true,false));
}

//-------- collect patch info for stage display
struct uiPatchDisplay : public gx_ui::GxUiItemFloat
{
	GtkWidget* fdialog;

	uiPatchDisplay(gx_ui::GxUI* ui, float* zone, GtkWidget* dialog)
		: gx_ui::GxUiItemFloat(ui, zone), fdialog(dialog) {}

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
            g_list_free(child_list);
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

uiTuner::uiTuner(gx_ui::GxUI* ui, float* zone):
	gx_ui::GxUiItemFloat(ui, zone),
	Gtk::Alignment(0.5,0.5,0,0)
{
	add(fTuner);
	fTuner.show();
}

void uiTuner::reflectZone()
{
	fCache = *fZone;
	if (shownote == 1) {
		set_freq(gx_engine::midi.fConsta4);
	} else if (shownote == 0) {
		shownote = -1;
	}
}

class GxWindowBox
{
private:
	bool on_window_delete_event(GdkEventAny* event,gpointer d );
	void on_check_resize();
public:
	Gtk::Window window;
	Gtk::ScrolledWindow           m_scrolled_window; 
	Gtk::HBox box;
	Gxw::PaintBox paintbox1;
	Gtk::VBox rbox;
	GxWindowBox(gx_ui::GxUI& ui, 
		const char *pb_2, Glib::ustring titl,GtkWidget * d);
	~GxWindowBox();
};

bool GxWindowBox::on_window_delete_event(GdkEventAny*, gpointer d)
{
	gtk_check_menu_item_set_active(
				GTK_CHECK_MENU_ITEM(GTK_WIDGET(d)), FALSE
				);
	return false;
}

void GxWindowBox::on_check_resize()
{
	if(window.get_events() == Gdk::BUTTON_PRESS_MASK){
		int y_org = window.get_height();
		if(y_org >=81)
			window.set_size_request (-1 , y_org-5 );
		usleep(50);
	}
}

GxWindowBox::GxWindowBox(gx_ui::GxUI& ui, 
	const char *pb_2, Glib::ustring titl,GtkWidget * d):
	window(Gtk::WINDOW_TOPLEVEL),
	rbox(false, 4)
{
	Glib::ustring title = titl;
	window.set_decorated(true);
	window.add_events(Gdk::BUTTON_PRESS_MASK);
	window.set_icon(Glib::wrap(ib));
	window.set_gravity(Gdk::GRAVITY_SOUTH);
	window.set_title(title);
	window.property_destroy_with_parent() = true;
	
	m_scrolled_window.set_policy(Gtk::POLICY_NEVER,Gtk::POLICY_AUTOMATIC); 
	paintbox1.set_border_width(18);
	
	paintbox1.property_paint_func() = pb_2;
	window.signal_delete_event().connect(
		 sigc::bind<gpointer>(sigc::mem_fun(*this, &GxWindowBox::on_window_delete_event),d));
	box.add(rbox);
	paintbox1.add(box);
	m_scrolled_window.add(paintbox1);
	window.add(m_scrolled_window);
	window.signal_check_resize().connect(
		sigc::mem_fun(*this, &GxWindowBox::on_check_resize));
	
	paintbox1.show();
	box.show();
	m_scrolled_window.show();
	rbox.show();
}

void GxMainInterface::addNumDisplay()
{
	GxWindowBox *box =  new GxWindowBox(*this, 
		pb_gxrack_expose, "tuner", GTK_WIDGET(fShowTuner.gobj()));
	box->rbox.add(fTuner);
	box->window.set_size_request(200,140); 
	tuner_widget = GTK_WIDGET(box->window.gobj());
}

void GxMainInterface::openPlugBox(const char* label)
{
	GxWindowBox *box =  new GxWindowBox(*this, 
		pb_gxrack_expose, label, GTK_WIDGET(fShowRack.gobj()));
	rack_widget = GTK_WIDGET(box->window.gobj());
	box->window.set_size_request(-1,310); 
	box->window.set_name("MonoRack");
	rBox = GTK_WIDGET(box->rbox.gobj());
	pushBox(kBoxMode, GTK_WIDGET(rBox));
}

void GxMainInterface::openAmpBox(const char* label)
{
	GxWindowBox *box =  new GxWindowBox(*this, 
		pb_gxrack_expose, label, GTK_WIDGET(fShowSRack.gobj()));
	srack_widget = GTK_WIDGET(box->window.gobj());
	box->window.set_size_request(-1,310); 
	box->window.set_name("StereoRack");
	sBox = GTK_WIDGET(box->rbox.gobj());
	pushBox(kBoxMode, GTK_WIDGET(sBox));
}

struct uiStatusDisplay : public gx_ui::GxUiItemFloat
{
	GtkLabel* fLabel;
	int	fPrecision;

	uiStatusDisplay(gx_ui::GxUI* ui, float* zone, GtkLabel* label)
		: gx_ui::GxUiItemFloat(ui, zone), fLabel(label) {}

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




bool GxMainInterface::on_refresh_oscilloscope()
{
	static struct  {
		int load, frames;
		jack_nframes_t bsize;
		bool rt;
	} oc;
	int load = int(round(gx_jack::jcpu_load));
	if (!oc.bsize || oc.load != load) {
		oc.load = load;
		fWaveView.set_text(
			(boost::format(_("dsp load  %1% %%")) % oc.load).str().c_str(),
			Gtk::CORNER_TOP_LEFT);
	}
	int frames = gx_jack::time_is/100000;
	if (!oc.bsize || oc.frames != frames) {
		oc.frames = frames;
		fWaveView.set_text(
			(boost::format(_("ht frames %1%")) % oc.frames).str().c_str(),
			Gtk::CORNER_BOTTOM_LEFT);
	}
	if (!oc.bsize || oc.rt != gx_jack::is_rt) {
		oc.rt = gx_jack::is_rt;
		fWaveView.set_text(
			oc.rt ? _("RT mode  yes ") : _("RT mode  <span color=\"#cc1a1a\">NO</span>"),
			Gtk::CORNER_BOTTOM_RIGHT);
	}
	if (!oc.bsize || oc.bsize != gx_jack::jack_bs) {
		oc.bsize = gx_jack::jack_bs;
		fWaveView.set_text(
			(boost::format(_("latency    %1%")) % oc.bsize).str().c_str(),
			Gtk::CORNER_TOP_RIGHT);
	}
	fWaveView.queue_draw();
	if (showwave) {
		return TRUE;
	} else {
		return FALSE;
	}
}


void GxMainInterface::addLiveWaveDisplay(const char* label, float* zone , float* zone1)
{
	GtkWidget * box      = gtk_vbox_new(false, 4);
	GtkWidget * e_box =  gtk_event_box_new();
	g_signal_connect(box, "expose-event", G_CALLBACK(conv_widget_expose), NULL);
	gtk_widget_set_size_request(box, 303, 82);
	gtk_widget_set_size_request(e_box, 280, 50);
	gtk_container_set_border_width(GTK_CONTAINER (box), 12);
	gtk_container_add(GTK_CONTAINER(e_box), GTK_WIDGET(fWaveView.gobj()));
	gtk_container_add(GTK_CONTAINER(box),e_box );
	addWidget(label, box);
	fWaveView.hide(); // was show()'n by addWidget
	fWaveView.property_text_pos_left() = 1.5;
	fWaveView.property_text_pos_right() = 77;
	gtk_widget_show(box);
	gtk_widget_hide(e_box);
}

void GxMainInterface::set_mouse_mode()
{
	if (fSetMouse.get_active()) {
		gx_set_knob_jump_to_mouse(false);
	} else {
		gx_set_knob_jump_to_mouse(true);
	}
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
	                     gx_jackd_on_image, "jack server is connected", "jack server state.");

	gtk_widget_show(gx_jackd_on_image);

	// jackd OFF image: hidden by default
	img_path = gx_pixmap_dir + "jackd_off.png";

	gx_jackd_off_image =  gtk_image_menu_item_new_with_label("");
	GtkWidget*   jackstateoff = gtk_image_new_from_file(img_path.c_str());
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(gx_jackd_off_image),jackstateoff);
	gtk_menu_bar_append (GTK_MENU_BAR(menupix), gx_jackd_off_image);
	gtk_tooltips_set_tip(GTK_TOOLTIPS (comandline),
	                     gx_jackd_off_image, "jack server is unconnected", "jack server state.");
	gtk_widget_hide(gx_jackd_off_image);


	/* ----------------------------------------------------------- */
	fMenuList["Top"] = menucont;

	addEngineMenu();
	addPresetMenu();
	addPluginMenu();
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

	/*-- create Midi Controller Table menu item --*/
	menuitem = gtk_check_menu_item_new_with_mnemonic ("M_idi Controller");
	gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
	                           GDK_i, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect (
		GTK_OBJECT (menuitem), "activate",
		G_CALLBACK (MidiControllerTable::toggle), menuitem);
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
	//gx_preset::gx_refresh_preset_menus(); //FIXME: will be done in gx_engine_init()?

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
	menuitem = gtk_menu_item_new_with_mnemonic ("Load Preset-_file");
	gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
	                           GDK_f, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
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

//----------------------------- preset menu ----------------------------
void GxMainInterface::addPluginMenu()
{
	GtkWidget* menulabel; // menu label
	GtkWidget* menucont;  // menu container
	GtkWidget* menucontin;  // menu container

	menucont = fMenuList["Top"];

	/*---------------- Create Options menu items ------------------*/
	menulabel = gtk_menu_item_new_with_mnemonic ("_Plugins");
	gtk_menu_bar_append (GTK_MENU_BAR(menucont), menulabel);
	gtk_widget_show(menulabel);

	/*-- Create Options submenu  --*/
	menucont = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menucont);
	gtk_widget_show(menucont);
	
	/*-- Create mono rack check menu item under Options submenu --*/
	set_label(fShowRack, "show Mono_Rack");
	fShowRack.add_accelerator("activate", Glib::wrap(fAccelGroup, true),
	                           GDK_r, Gdk::SHIFT_MASK, Gtk::ACCEL_VISIBLE);
	fShowRack.signal_activate().connect(
		sigc::mem_fun(*this, &GxMainInterface::on_rack_activate));
	gtk_menu_shell_append(GTK_MENU_SHELL(menucont), GTK_WIDGET(fShowRack.gobj()));
	fShowRack.show();
	fShowRack.set_parameter(new SwitchParameter("system.show_rack"));
	
	/*-- Create mono plugin menu soket item under Options submenu --*/
	menulabel = gtk_menu_item_new_with_mnemonic ("_Mono Plugins");
	gtk_menu_append (GTK_MENU(menucont), menulabel);
	gtk_widget_show(menulabel);
	
	menucontin = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menucontin);
	gtk_widget_show(menucontin);
	
	fMenuList["PluginsMono"] = menucontin;
	
	/*-- add a separator line --*/
	GtkWidget* sep = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menuh), sep);
	gtk_widget_show (sep);
	
	/*-- Create stereo rack check menu item under Options submenu --*/
	set_label(fShowSRack, "show _StereoRack");
	fShowSRack.add_accelerator("activate", Glib::wrap(fAccelGroup, true),
	                           GDK_s, Gdk::SHIFT_MASK, Gtk::ACCEL_VISIBLE);
	fShowSRack.signal_activate().connect(
		sigc::mem_fun(*this, &GxMainInterface::on_srack_activate));
	gtk_menu_shell_append(GTK_MENU_SHELL(menucont), GTK_WIDGET(fShowSRack.gobj()));
	fShowSRack.show();
	fShowSRack.set_parameter(new SwitchParameter("system.show_Srack"));
	
	/*-- Create stereo plugin menu soket item under Options submenu --*/
	menulabel = gtk_menu_item_new_with_mnemonic ("_Stereo Plugins");
	gtk_menu_append (GTK_MENU(menucont), menulabel);
	gtk_widget_show(menulabel);
	
	menucontin = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menucontin);
	gtk_widget_show(menucontin);
	
	fMenuList["PluginsStereo"] = menucontin;
}

//----------------------------- option menu ----------------------------

void reset_all_parameters(GtkWidget*, gpointer)
{
	for (ParamMap::iterator i = parameter_map.begin(); i != parameter_map.end(); i++) {
		i->second->set_std_value();
	}
}

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

	/*-- Create Open check menu item under Options submenu --*/
	menuitem = gtk_check_menu_item_new_with_mnemonic ("_Meterbridge");
	gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup,
	                           GDK_m, GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect (GTK_OBJECT (menuitem), "activate",
	                  G_CALLBACK (Meterbridge::start_stop), NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
	gtk_widget_show (menuitem);
	
	/*-- Create tuner check menu item under Options submenu --*/
	set_label(fShowTuner, "_Tuner");
	fShowTuner.add_accelerator("activate", Glib::wrap(fAccelGroup, true),
	                           GDK_t, Gdk::SHIFT_MASK, Gtk::ACCEL_VISIBLE);
	fShowTuner.signal_activate().connect(
		sigc::mem_fun(*this, &GxMainInterface::on_tuner_activate));
	gtk_menu_shell_append(GTK_MENU_SHELL(menucont), GTK_WIDGET(fShowTuner.gobj()));
	fShowTuner.show();
	fShowTuner.set_parameter(new SwitchParameter("system.show_tuner"));
	

	/*-- Create skin menu under Options submenu--*/
	addGuiSkinMenu();
	
	set_label(fSetMouse, "set _Knobs linear");
	fSetMouse.add_accelerator("activate", Glib::wrap(fAccelGroup, true),
	                           GDK_k, Gdk::SHIFT_MASK, Gtk::ACCEL_VISIBLE);
	fSetMouse.signal_activate().connect(
		sigc::mem_fun(*this, &GxMainInterface::set_mouse_mode));
	gtk_menu_shell_append(GTK_MENU_SHELL(menucont), GTK_WIDGET(fSetMouse.gobj()));
	fSetMouse.show();
	fSetMouse.set_parameter(new SwitchParameter("system.set_mouse"));

	/*-- create option for saving midi controller settings in presets --*/
	set_label(fMidiInPreset, "Include MIDI in _presets");
	fMidiInPreset.show();
	gtk_menu_shell_append(GTK_MENU_SHELL(menucont), GTK_WIDGET(fMidiInPreset.gobj()));
	fMidiInPreset.set_parameter(new SwitchParameter("system.midi_in_preset"));

	/*-- create option for resetting gx_head settings --*/
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
		"gx_head menu-option");
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
	set_label(fShowTooltips, "Show _Tooltips");
	fShowTooltips.show();
	gtk_menu_shell_append(GTK_MENU_SHELL(menucont), GTK_WIDGET(fShowTooltips.gobj()));
	SwitchParameter *p = new SwitchParameter("system.show_tooltips");
	fShowTooltips.set_parameter(p);
	fShowTooltips.set_active(true);
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


void GxMainInterface::set_waveview_buffer()
{
	fWaveView.set_frame(gx_engine::get_frame, gx_jack::jack_bs);
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

		//string window_name = "gx_head"; FIXME is set by recall settings
		//gtk_window_set_title (GTK_WINDOW (fWindow), window_name.c_str());

	} else {
		gtk_widget_hide(gx_gui::gx_jackd_on_image);
		gtk_widget_show(gx_gui::gx_jackd_off_image);
	}

	gint mainxorg = gx_set_mx_oriantation(); 
	gint mainyorg = gx_set_my_oriantation();
	gtk_window_move(GTK_WINDOW(fWindow), mainxorg, mainyorg);
	gtk_widget_show  (fBox[0]);
	gtk_widget_show  (fWindow);
}

//---- show main GUI thread and more
void GxMainInterface::run()
{
	//----- set the state for the latency change warning widget
	gx_engine::set_latency_warning_change();

	//----- set the last used skin when no cmd is given
	int skin_index = gx_current_skin;
	if (no_opt_skin == 1)
		skin_index = (int)gx_engine::audio.fskin;

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

	//set_waveview_buffer();
	gtk_main();
}

} /* end of gx_gui namespace */

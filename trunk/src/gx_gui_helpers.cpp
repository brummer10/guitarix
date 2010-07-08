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
 *    This is the guitarix GUI related functionality
 *
 * ----------------------------------------------------------------------------
 */

#include <cstring>
#include <dirent.h>
#include "guitarix.h"

using namespace gx_system;
using namespace gx_preset;
using namespace gx_cairo;

/* --------------------------- gx_gui namespace ------------------------ */
namespace gx_gui
{

/* ----- Menu check item signaled from parameter ------ */

void MenuCheckItem::set(bool v)
{
	assert(item); // assign an item before calling
	gtk_check_menu_item_set_active(item, v);
}

void MenuCheckItem::activateMenuSetSwitch(GtkWidget *w, gpointer data)
{
	SwitchParameter *p = (SwitchParameter*)data;
	p->set(gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(w)));
}

void MenuCheckItem::init(GtkCheckMenuItem *it, SwitchParameter *p)
{
	item = it;
	parameter_map.insert(p);
	p->changed.connect(sigc::mem_fun(*this, &MenuCheckItem::set));
	g_signal_connect(GTK_OBJECT(item), "activate",
	                 G_CALLBACK(activateMenuSetSwitch), p);
}


/* ----- load a top level window from gtk builder file ------ */

GtkWidget *load_toplevel(GtkBuilder *builder, const char* filename, const char* windowname)
{
	string fname = gx_builder_dir+filename;
	GError *err = NULL;
	if (!gtk_builder_add_from_file(builder,fname.c_str(), &err)) {
		g_object_unref(G_OBJECT(builder));
		gx_print_fatal("gtk builder", err->message);
		g_error_free(err);
		return NULL;
	}
	GtkWidget *w = GTK_WIDGET(gtk_builder_get_object(builder, windowname));
	if (!w) {
		g_object_unref(G_OBJECT(builder));
		gx_print_fatal("gtk builder", string(windowname)+" not found in "+fname);
		return NULL;
	}
	gtk_builder_connect_signals(builder, 0);
	return w;
}

/* --------- menu function triggering engine on/off/bypass --------- */
void gx_engine_switch (GtkWidget* widget, gpointer arg)
{
	gx_engine::GxEngineState estate =
		(gx_engine::GxEngineState)gx_engine::checky;

	switch (estate)
	{
	case gx_engine::kEngineOn:
		estate = gx_engine::kEngineOff;
		if (arg)
		{
			// need to activate item
			gtk_check_menu_item_set_active(
				GTK_CHECK_MENU_ITEM(gx_engine_item), TRUE
				);
			estate = gx_engine::kEngineBypass;
		}

		break;

	case gx_engine::kEngineOff:
		if (!arg)
			estate = gx_engine::kEngineOn;
		break;

	default:
		estate = gx_engine::kEngineOn;
		gtk_check_menu_item_set_active(
			GTK_CHECK_MENU_ITEM(gx_engine_item), TRUE
			);
	}

	gx_engine::checky = (float)estate;
	gx_refresh_engine_status_display();
}

/* -------------- refresh engine status display ---------------- */
void gx_refresh_engine_status_display()
{
	gx_engine::GxEngineState estate =
		(gx_engine::GxEngineState)gx_engine::checky;

	string state;

	switch (estate)
	{

	case gx_engine::kEngineOff:
		gtk_widget_show(gx_engine_off_image);
		gtk_widget_hide(gx_engine_on_image);
		gtk_widget_hide(gx_engine_bypass_image);

		gtk_check_menu_item_set_active(
			GTK_CHECK_MENU_ITEM(gx_engine_item), FALSE
			);
		state = "OFF";
		break;

	case gx_engine::kEngineBypass:
		gtk_widget_show(gx_engine_bypass_image);
		gtk_widget_hide(gx_engine_off_image);
		gtk_widget_hide(gx_engine_on_image);

		gtk_check_menu_item_set_active(
			GTK_CHECK_MENU_ITEM(gx_gui::gx_engine_item), TRUE
			);
		state = "BYPASSED";
		break;

	case gx_engine::kEngineOn:
	default: // ON
		gtk_widget_show(gx_engine_on_image);
		gtk_widget_hide(gx_engine_off_image);
		gtk_widget_hide(gx_engine_bypass_image);

		gtk_check_menu_item_set_active(
			GTK_CHECK_MENU_ITEM(gx_gui::gx_engine_item), TRUE
			);
		state = "ON";
	}

	gx_print_info("Engine State: ", state);
}


// get the last used skin as default
void gx_set_skin_change(float fskin)
{
       last_skin = int(fskin);
}

// save the current used skin as default
void gx_get_skin_change(float *fskin)
{
	*fskin  = float(gx_current_skin);
}

void gx_jack_is_down()
{
	/* FIXME send to ui thread
	gx_print_warning("Jack Shutdown",
	                 "jack has bumped us out!!");
	*/
	cout << "jack has bumped us out!!" << endl;
	g_timeout_add_full(G_PRIORITY_LOW,200, gx_threads::gx_survive_jack_shutdown, 0, NULL);
}

void gx_jack_report_xrun()
{
	g_threads[2] = 0;
	if (g_threads[2] == 0 ||g_main_context_find_source_by_id(NULL, g_threads[2]) == NULL)
		g_threads[2] =g_idle_add(gx_threads::gx_xrun_report,gpointer (NULL));
}

//----menu function gx_show_oscilloscope
void gx_show_oscilloscope (GtkCheckMenuItem *menuitem, gpointer checkplay)
{
	if (gtk_check_menu_item_get_active(menuitem) == TRUE)
	{
		showwave = 1;
		g_timeout_add_full(G_PRIORITY_DEFAULT_IDLE, 60,  gx_threads::gx_refresh_oscilloscope, 0, NULL);
		GtkWidget * parent = gtk_widget_get_parent(GTK_WIDGET(livewa));
		gtk_widget_show(parent);
		gtk_widget_show(livewa);
	}
	else
	{
		showwave = 0;
		GtkWidget * parent = gtk_widget_get_parent(GTK_WIDGET(livewa));
		gtk_widget_hide(parent);
		gtk_widget_hide(livewa);
	}
}

//----menu function gx_tuner
void gx_tuner (GtkCheckMenuItem *menuitem, gpointer checkplay)
{
	if (gtk_check_menu_item_get_active(menuitem) == TRUE) {
		shownote = 1;
		gtk_widget_show(pb);
		//tuner_expose(pb,NULL,NULL);
	} else {
		shownote = 0;
		gtk_widget_hide(pb);
	}
}

//----menu function gx_tuner
void gx_patch(GtkCheckMenuItem *menuitem, gpointer checkplay)
{
    gtk_widget_show_all(patch_info);
}

//---- menu function gx_midi_out
void gx_midi_out (GtkCheckMenuItem *menuitem, gpointer checkplay)
{
	if (gtk_check_menu_item_get_active(menuitem) == TRUE)
	{
		gx_engine::turnOnMidi();
		gtk_widget_show(midibox);
	}
	else
	{
		gx_engine::turnOffMidi();
		gtk_widget_hide(midibox);
	}
}

//---- menu function gx_midi_out
void gx_log_window (GtkWidget* menuitem, gpointer arg)
{
	GtkExpander* const exbox = GxMainInterface::instance()->getLoggingBox();

	// we could be called before UI is built up
	if (!exbox) return;

	bool expanded = gtk_expander_get_expanded(exbox);
	bool checked = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(menuitem));
	if (!(expanded ^ checked)) {
		return;
	}
	gtk_signal_emit_by_name(GTK_OBJECT(exbox), "activate");
}

//----menu funktion about
void gx_show_about( GtkWidget *widget, gpointer data )
{
	static string about;
	if (about.empty())
	{
		about +=
			"\n  This Aplication is to a large extent provided"
			"\n  with the marvelous faust compiler.Yann Orlary"
			"\n  <http://faust.grame.fr/>"
			"\n  A large part is based on the work of Julius Orion Smith"
			"\n <http://ccrma.stanford.edu/realsimple/faust/>"
			"\n  and Albert Graef\n  <http://www.musikwissenschaft.uni-mainz.de/~ag/ag.html>  "
			"\n\n\n  guitarix ";

		about += GX_VERSION;

		about +=
			" use jack_capture >= 0.9.30for record"
			"\n  by Kjetil S. Matheussen "
			"\n  http://old.notam02.no/arkiv/src/?M=D"
			"\n  it will allways record to ~/guitarix_sessionX.xxx "
			"\n  for impulse response it use zita-convolver "
			"\n  byFons Adriaensen "
			"\n  http://www.kokkinizita.net/linuxaudio/index.html "
			"\n\n  authors: Hermann Meyer <brummer-@web.de>"
			"\n  authors: James Warden <warjamy@yahoo.com>"
			"\n  authors: Andreas Degert <andreas.degert@googlemail.com>    "
			"\n  home: http://guitarix.sourceforge.net/\n";
	}

	gx_message_popup(about.c_str());
}


//----- change the jack buffersize on the fly is still experimental, give a warning
gint gx_wait_latency_warn()
{
	GtkWidget* warn_dialog = gtk_dialog_new();
	gtk_window_set_destroy_with_parent(GTK_WINDOW(warn_dialog), TRUE);

	GtkWidget* box     = gtk_vbox_new (0, 4);
	GtkWidget* labelt  = gtk_label_new("\nWARNING\n");
	GtkWidget* labelt1 = gtk_label_new("CHANGING THE JACK_BUFFER_SIZE ON THE FLY \n"
	                                   "MAY CAUSE UNPREDICTABLE EFFECTS \n"
	                                   "TO OTHER RUNNING JACK APPLICATIONS. \n"
	                                   "DO YOU WANT TO PROCEED ?");
	GdkColor colorGreen;
	gdk_color_parse("#969292", &colorGreen);
	gtk_widget_modify_fg (labelt1, GTK_STATE_NORMAL, &colorGreen);

	GtkStyle *style1 = gtk_widget_get_style(labelt1);
	pango_font_description_set_size(style1->font_desc, 10*PANGO_SCALE);
	pango_font_description_set_weight(style1->font_desc, PANGO_WEIGHT_BOLD);
	gtk_widget_modify_font(labelt1, style1->font_desc);

	gdk_color_parse("#ffffff", &colorGreen);
	gtk_widget_modify_fg (labelt, GTK_STATE_NORMAL, &colorGreen);
	style1 = gtk_widget_get_style(labelt);
	pango_font_description_set_size(style1->font_desc, 14*PANGO_SCALE);
	pango_font_description_set_weight(style1->font_desc, PANGO_WEIGHT_BOLD);
	gtk_widget_modify_font(labelt, style1->font_desc);

	GtkWidget* button1 =
		gtk_dialog_add_button(GTK_DIALOG (warn_dialog),
		                      "Yes", gx_jack::kChangeLatency);

	GtkWidget* button2 =
		gtk_dialog_add_button(GTK_DIALOG (warn_dialog),
		                      "No",  gx_jack::kKeepLatency);


	GtkWidget* box1    = gtk_hbox_new (0, 4);
	GtkWidget* box2    = gtk_hbox_new (0, 4);

	GtkWidget* disable_warn = gtk_check_button_new();
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(disable_warn), FALSE);
	g_signal_connect(disable_warn, "clicked",
	                 G_CALLBACK(gx_user_disable_latency_warn), NULL);

	GtkWidget * labelt2 =
		gtk_label_new ("Don't bother me again with such a question, "
		               "I know what I am doing");

	gtk_container_add (GTK_CONTAINER(box),  labelt);
	gtk_container_add (GTK_CONTAINER(box),  labelt1);
	gtk_container_add (GTK_CONTAINER(box),  box2);
	gtk_container_add (GTK_CONTAINER(box),  box1);
	gtk_container_add (GTK_CONTAINER(box1), disable_warn);
	gtk_container_add (GTK_CONTAINER(box1), labelt2);
	gtk_container_add (GTK_CONTAINER(GTK_DIALOG(warn_dialog)->vbox), box);

	gtk_widget_modify_fg (labelt2, GTK_STATE_NORMAL, &colorGreen);

	GtkStyle *style = gtk_widget_get_style(labelt2);
	pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
	pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
	gtk_widget_modify_font(labelt2, style->font_desc);

	g_signal_connect_swapped(button1, "clicked",
	                         G_CALLBACK (gtk_widget_destroy), warn_dialog);
	g_signal_connect_swapped(button2, "clicked",
	                         G_CALLBACK (gtk_widget_destroy), warn_dialog);

	gtk_widget_show_all(box);

	return gtk_dialog_run (GTK_DIALOG (warn_dialog));
}

// check user's decision to turn off latency change warning
void gx_user_disable_latency_warn(GtkWidget* wd, gpointer arg)
{
	GtkToggleButton* button = GTK_TOGGLE_BUTTON(wd);
	gx_engine::fwarn = (int)gtk_toggle_button_get_active(button);
}

void gx_reset_effects( GtkWidget *widget, gpointer data )
{
	string pos(".position");
	for (ParamMap::iterator i = parameter_map.begin(); i != parameter_map.end(); i++) {
		string id = i->first;
		if (id.size() > pos.size() &&
		    id.compare(id.size()-pos.size(), pos.size(), pos) == 0) {
			i->second->set_std_value();
		}
	}
}

// reset the extended sliders to default settings
void gx_reset_units( GtkWidget *widget, gpointer data )
{
	string group_id = string((const char*)data) + ".";
	string on_off = group_id + "on_off";
	for (ParamMap::iterator i = parameter_map.begin(); i != parameter_map.end(); i++) {
		if (i->first.compare(0, group_id.size(), group_id) == 0) {
			if (i->second->isControllable()) {
				string id = i->first;
				if (i->first != on_off) {
					i->second->set_std_value();
				}
			}
		}
	}
}

/*
// FIXME add some presets for the eq
void gx_reset_eq( GtkWidget *widget, gpointer data )
{
	string group_id = string((const char*)data) + ".";
	string on_off = group_id + "on_off";

	string presetfile = gx_user_dir + "eq_rc";

	ifstream ofile(presetfile.c_str());
	JsonParser jp(ofile);

	try {
		jp.next(JsonParser::begin_array);
		readHeader(jp);

		while (jp.peek() != JsonParser::end_array) {
			jp.next(JsonParser::value_string);
				read_preset(jp);
		}
		jp.next(JsonParser::end_array);
		jp.next(JsonParser::end_token);
	}catch (JsonException& e) {
		gx_print_error("load preset", "invalid preset file: " + presetfile);
	}

}
*/

//----- show extendend settings slider
void gx_show_extended_settings(GtkWidget *widget, gpointer data)
{
	if (gtk_range_get_value(GTK_RANGE(widget)))
	{
		gtk_widget_show(GTK_WIDGET(data));
		gint root_x, root_y;
		gtk_window_get_position (GTK_WINDOW(data), &root_x, &root_y);
		if (root_y>160)root_y -= 120;
		else root_y +=120;
		gtk_window_move(GTK_WINDOW(data), root_x, root_y);
	}

	else gtk_widget_hide(GTK_WIDGET(data));
}

//----- hide the extendend settings slider
void gx_hide_extended_settings( GtkWidget *widget, gpointer data )
{

	if (gdk_window_get_state(fWindow->window)
	    & (GDK_WINDOW_STATE_ICONIFIED|GDK_WINDOW_STATE_WITHDRAWN)) {
		gtk_window_present(GTK_WINDOW(fWindow));
	} else {
		gtk_widget_hide(fWindow);
        //gtk_window_iconify(GTK_WINDOW(fWindow));
	}
}

/**----------------------------- cabinet impulse response data --------------------------------**/
int cab_ir_count = 1000;
int cab_ir_sr = 48000;
float cab_ir_data[] = {
0.0210554,0.0750885,0.139243,0.180713,0.184139,0.144903,0.0686037,-0.0185033,-0.0886042,-0.12552,
-0.121363,-0.0787852,-0.0213013,0.0229356,0.0411458,0.0370145,0.0195269,-0.00133213,-0.0152812,-0.0145159,
-0.00183383,0.0137818,0.0256187,0.0286779,0.0207782,0.0077942,-0.00120299,-0.0031918,-0.00206098,-0.00135227,
-0.00140983,-0.00497816,-0.0130377,-0.0218103,-0.0277226,-0.0286464,-0.0215221,-0.00951618,-0.00086607,0.0013951,
4.17435e-05,-0.00319773,-0.00740044,-0.00716618,-0.00255126,0.00219789,0.00519503,0.00521192,0.000273707,-0.00618929,
-0.00908,-0.010311,-0.0123735,-0.0142287,-0.017697,-0.0241029,-0.0284137,-0.0277091,-0.0227469,-0.0152625,
-0.00519387,0.00359817,0.00729039,0.00671523,0.00318916,-0.00156796,-0.0063908,-0.00976712,-0.0129904,-0.017544,
-0.022616,-0.0259348,-0.0261542,-0.0244839,-0.0203182,-0.0130093,-0.00603727,-0.0032797,-0.00488236,-0.00846209,
-0.0130562,-0.0172578,-0.019061,-0.0178728,-0.0150705,-0.0105603,-0.00434051,0.000776129,0.00313197,0.00289589,
0.00099021,-0.00304687,-0.00856731,-0.0134404,-0.0173033,-0.019982,-0.0200995,-0.0189035,-0.0176908,-0.0158077,
-0.0144982,-0.0144288,-0.0148401,-0.0143923,-0.0124568,-0.00914924,-0.00554664,-0.00161911,0.00204186,0.00466298,
0.00609433,0.00586043,0.00444049,0.00230369,-0.000460247,-0.00331487,-0.00620476,-0.00860464,-0.00977339,-0.0103904,
-0.010582,-0.010316,-0.00959965,-0.0079265,-0.00490751,-0.000773675,0.00326292,0.0060596,0.00712823,0.0062126,
0.00304346,-0.00120159,-0.00554078,-0.00940086,-0.0116814,-0.0115473,-0.00920741,-0.00570695,-0.00192381,0.00131636,
0.00313601,0.00310522,0.0019866,0.00024603,-0.00151895,-0.00254442,-0.00257635,-0.00162088,0.000189493,0.00233523,
0.00431406,0.00546426,0.00550678,0.00412306,0.00163322,-0.00135299,-0.00397516,-0.00564887,-0.00616138,-0.00556616,
-0.00411866,-0.00213908,-0.000414186,0.000858571,0.00146968,0.00134177,0.000706731,0.000101598,-2.74503e-05,0.000216126,
0.000921334,0.00170689,0.00206986,0.00178904,0.00108999,0.000418435,-0.000329494,-0.00108679,-0.00160318,-0.00186207,
-0.00184908,-0.00174925,-0.0017532,-0.00168678,-0.00128635,-0.000532894,0.000551346,0.00173037,0.00285549,0.00381329,
0.00444954,0.00483888,0.00505528,0.00517976,0.00536394,0.00566848,0.00582878,0.00582337,0.00573454,0.00568407,
0.005573,0.00543545,0.00536728,0.00536814,0.00553587,0.00596405,0.00663779,0.00725726,0.00749624,0.00707181,
0.00588561,0.00408059,0.00192134,3.47446e-05,-0.00100598,-0.000915017,4.2448e-05,0.00134795,0.00249509,0.00322568,
0.0035816,0.00386374,0.00451921,0.00540239,0.0062616,0.00694728,0.0072783,0.00703991,0.00629145,0.00535576,
0.00433242,0.0032916,0.00256128,0.00234155,0.00256369,0.00301814,0.00356167,0.00389767,0.00377937,0.00333664,
0.00305993,0.00308825,0.00323129,0.00347644,0.00368722,0.00369027,0.0035434,0.0033256,0.00313601,0.00318107,
0.00358381,0.00415188,0.00472327,0.00508203,0.00512893,0.00469563,0.00385072,0.00285837,0.00193384,0.0011745,
0.000625585,0.000444931,0.000447908,0.000509171,0.000766472,0.00131361,0.00198278,0.00252006,0.00288339,0.00305278,
0.00301612,0.00284385,0.0027595,0.0028841,0.00307673,0.00335143,0.00374592,0.00420453,0.00472283,0.00537605,
0.00605867,0.00667969,0.0071488,0.00726939,0.00694415,0.00626471,0.00550721,0.0049613,0.00471663,0.00477505,
0.00498066,0.00516581,0.00520946,0.00505574,0.00483425,0.00468391,0.00466834,0.00471656,0.00470018,0.00453961,
0.0042108,0.00375276,0.00315533,0.00236797,0.00148797,0.000770994,0.000356717,0.000263414,0.000411073,0.00065758,
0.000956942,0.00116598,0.00118259,0.0010794,0.00090411,0.000730068,0.000713639,0.00101561,0.00158903,0.0022272,
0.00269874,0.00283804,0.00266545,0.00230882,0.00195122,0.00177202,0.0018221,0.00198835,0.00219707,0.0024585,
0.00262623,0.00258478,0.00247114,0.00236725,0.00229178,0.00227378,0.00223327,0.0020942,0.0018775,0.00165049,
0.00145125,0.0013392,0.00133322,0.0013771,0.00146459,0.00154074,0.00148781,0.00131534,0.00115589,0.00110735,
0.00111562,0.00117102,0.0011977,0.00112514,0.000940195,0.000626312,0.000241008,-0.000110301,-0.000294454,-0.00026455,
-3.9153e-05,0.000364625,0.000848391,0.00124397,0.00133727,0.00111349,0.00081935,0.000737272,0.000979052,0.00152794,
0.00229764,0.00300549,0.00349459,0.00378848,0.00383738,0.00362037,0.00319689,0.00261696,0.00202673,0.00153753,
0.0010692,0.000529509,-3.48582e-05,-0.000518806,-0.000836461,-0.000893089,-0.000683757,-0.00041539,-0.000240531,-0.000199855,
-0.00040037,-0.000829803,-0.00130214,-0.00175941,-0.00214005,-0.00239538,-0.00255126,-0.00260319,-0.00258167,-0.00258312,
-0.00261625,-0.00257821,-0.00243703,-0.00224874,-0.002035,-0.0018443,-0.00177327,-0.00182376,-0.00196122,-0.00222559,
-0.00246046,-0.0023872,-0.00200267,-0.00146368,-0.000895475,-0.000426638,-0.000116391,8.54413e-05,0.000229487,0.000434546,
0.000783401,0.00125185,0.00170428,0.00195945,0.00191818,0.00165093,0.0013,0.000928947,0.00048422,-4.45158e-05,
-0.000552028,-0.000942422,-0.00123235,-0.00149559,-0.00177645,-0.00204586,-0.00228739,-0.00245312,-0.00249216,-0.00238563,
-0.00216864,-0.00195288,-0.00184076,-0.0018401,-0.00190445,-0.00195077,-0.0018578,-0.00162677,-0.00132209,-0.00103643,
-0.000946898,-0.00112221,-0.00150406,-0.00195615,-0.00229437,-0.00239499,-0.00218277,-0.0017268,-0.00124285,-0.00091104,
-0.000849391,-0.00104366,-0.00129184,-0.00138022,-0.00126944,-0.00107845,-0.000937854,-0.000922902,-0.00107965,-0.00139665,
-0.00174952,-0.00198203,-0.00202984,-0.00187962,-0.0015708,-0.00124176,-0.00109158,-0.00130834,-0.0019349,-0.00284735,
-0.00377169,-0.00432535,-0.00427272,-0.00367104,-0.00275803,-0.00184037,-0.00124326,-0.00112073,-0.00138117,-0.00175739,
-0.00199908,-0.00197451,-0.00163986,-0.00107954,-0.000508739,-0.000136274,-2.69049e-05,-0.000195924,-0.000604997,-0.00107277,
-0.00139074,-0.00147588,-0.00138458,-0.00119441,-0.00105561,-0.00112623,-0.00139983,-0.00174871,-0.00207738,-0.00232496,
-0.00235838,-0.00213469,-0.00182601,-0.00162957,-0.00156907,-0.00164833,-0.00185294,-0.00208449,-0.002181,-0.00207736,
-0.00181851,-0.00145291,-0.00105886,-0.000777402,-0.000693301,-0.000780538,-0.000966736,-0.00110846,-0.00100441,-0.000639605,
-0.000167997,0.000278684,0.000595589,0.000718707,0.000677736,0.000535644,0.000359331,0.000214058,0.000116118,-2.04741e-05,
-0.000248734,-0.000545983,-0.00088025,-0.00122061,-0.0015376,-0.00175523,-0.00175457,-0.00148886,-0.00107979,-0.000750293,
-0.000715752,-0.00112187,-0.0019394,-0.0029335,-0.00377016,-0.00421975,-0.00417837,-0.00370331,-0.00304405,-0.00245053,
-0.00210699,-0.00207797,-0.0022711,-0.00249086,-0.00253708,-0.00230403,-0.00181831,-0.00124433,-0.000780152,-0.000599361,
-0.00073175,-0.00104361,-0.00127435,-0.00119859,-0.000762859,-8.26917e-05,0.000629675,0.00112308,0.00126592,0.0011715,
0.00103854,0.000983915,0.00102964,0.00109781,0.00111035,0.000980961,0.000642923,0.000128366,-0.000457361,-0.000965123,
-0.00129109,-0.00143212,-0.00144318,-0.0014024,-0.00139796,-0.00148234,-0.00166874,-0.00191579,-0.00211699,-0.00215912,
-0.0020502,-0.00183696,-0.00155674,-0.00122281,-0.000867206,-0.000589227,-0.000474017,-0.000498718,-0.000541393,-0.000489083,
-0.000283456,6.39901e-05,0.000442908,0.000769699,0.000966486,0.000987869,0.000807193,0.000472449,6.91029e-05,-0.000300749,
-0.000520124,-0.000506989,-0.000277707,-7.49884e-07,0.000197924,0.000303067,0.000322268,0.000290614,0.000293023,0.000353695,
0.000410527,0.000420457,0.000342197,0.000133297,-0.000165088,-0.000453839,-0.000679258,-0.000834689,-0.000952602,-0.00110901,
-0.00138581,-0.00176734,-0.00213167,-0.00235534,-0.00238038,-0.0022105,-0.0018848,-0.00142392,-0.000878386,-0.000337561,
0.000124526,0.000442113,0.000576183,0.000579069,0.000590295,0.000704595,0.000887021,0.00101477,0.0010045,0.000847664,
0.000575138,0.000306771,0.000121299,3.08588e-05,9.36218e-06,-8.68729e-05,-0.000309611,-0.000568184,-0.000781879,-0.00090086,
-0.000816373,-0.000530804,-0.00015868,0.000212172,0.000470813,0.000541848,0.000420117,0.000213262,5.74002e-05,5.44461e-05,
0.000231169,0.000503149,0.000735295,0.000831939,0.000801057,0.00070564,0.000658602,0.000765108,0.00102202,0.00132866,
0.00158623,0.00171223,0.00161877,0.00138119,0.00109374,0.000773789,0.000429865,0.000119368,-0.000121345,-0.000232623,
-0.000125412,0.000170474,0.000515011,0.000714866,0.000659852,0.000381759,2.34736e-05,-0.000255279,-0.000353581,-0.00027348,
-8.40097e-05,0.000180108,0.000442772,0.000595703,0.00059443,0.000443181,0.00020006,-4.72427e-05,-0.000237849,-0.000336152,
-0.000260891,-1.77245e-06,0.000308816,0.000549233,0.000726773,0.000843596,0.000880568,0.000881363,0.000886135,0.000917471,
0.000981234,0.00105438,0.00110092,0.0011346,0.00116191,0.00120611,0.00130918,0.00150924,0.00173518,0.00188839,
0.0019312,0.00182619,0.00154596,0.00111546,0.000674054,0.000338175,0.000137615,6.37174e-05,9.953e-05,0.000188198,
0.000251211,0.000265322,0.000236736,0.000180904,0.000111483,2.96318e-05,-4.73336e-05,-8.53731e-05,-1.88834e-05,0.000190425,
0.000533576,0.000938581,0.00131834,0.00155549,0.00158925,0.00148725,0.0013572,0.00129875,0.00134022,0.00146789,
0.00163836,0.00174532,0.00169876,0.00147691,0.00111449,0.000735204,0.000492014,0.000435092,0.000515761,0.000663783,
0.000799262,0.00084905,0.000801557,0.000690779,0.000557527,0.000428524,0.000314815,0.00019497,5.04922e-05,-0.000104847,
-0.000234282,-0.000318564,-0.000372079,-0.000385258,-0.00035599,-0.0003227,-0.000303067,-0.000293341,-0.000320655,-0.000354127,
-0.000328881,-0.000232259,-0.000107938,1.18163e-05,0.000143091,0.000270049,0.000361626,0.000452498,0.00056314,0.000661147,
0.000724365,0.000744134,0.000727273,0.00072107,0.000736863,0.000779379,0.000855094,0.000962941,0.00110471,0.00125183,
0.001321,0.00125508,0.00107511,0.000815532,0.000494719,0.000180608,-4.70381e-05,-0.000147682,-0.000113164,2.06559e-05,
0.000179654,0.000301226,0.00036008,0.000352877,0.000314178,0.000264527,0.000197424,0.000127707,7.75789e-05,3.03816e-05,
-4.49248e-05,-0.000123981,-0.000188198,-0.000230032,-0.000205332,-9.22811e-05,8.61003e-05,0.000310111,0.000546188,0.00074752,
0.000886044,0.000967781,0.000983915,0.000906905,0.000743066,0.000538462,0.000377373,0.000343151,0.000430569,0.000540598,
0.000564958,0.000431751,0.000133502,-0.000251643,-0.000614836,-0.000844801,-0.00086966,-0.000704595,-0.000452021,-0.000232532,
-0.00011021,-9.40536e-05,-0.000144818,-0.000166747,-0.000102916,5.03785e-05,0.000256278,0.000434682,0.000496309,0.000419026,
0.000240804,4.47203e-05,-9.02133e-05,-0.000122117,-6.04452e-05,1.82926e-05,5.15602e-05,1.39297e-05,-0.00012089,-0.00033004,
-0.000557345,-0.000726751,-0.000759268,-0.000650285,-0.000450657,-0.00021608,3.68579e-05,0.000297704,0.000538644,0.000710049,
0.00077363,0.000723092,0.000614791,0.000532167,0.000514057,0.00058116,0.000682076,0.00072566,0.000673282,0.000508217,
0.000270299,6.37401e-05,-5.79001e-05,-0.000104257,-9.17585e-05,-6.15359e-05,-5.7741e-05,-7.34204e-05,-8.94407e-05,-0.000104779,
-0.00013891,-0.000166588,-0.000132638,-2.27237e-05,0.000174609,0.00045193,0.00072032,0.000864434,0.000871569,0.000768994,
0.00059284,0.00041948,0.000294795,0.000222579,0.000194515,0.000144409,-1.60202e-05,-0.000275753,-0.000566662,-0.00085005,
-0.00107913,-0.00119302,-0.00120593,-0.00115421,-0.00108797,-0.00107377,-0.00112567,-0.00117748,-0.00117754,-0.00112203,
-0.00103152,-0.000931128,-0.000873637,-0.000869274,-0.000861684,-0.000822599,-0.000761041,-0.000649717,-0.000460974,-0.000247598,
-6.14223e-05,9.10313e-05,0.000194265,0.000208968,0.000170814,0.000139069,0.000142114,0.000191107,0.000249529,0.000275162,
0.000279048,0.000277048,0.000268231,0.000283933,0.000336425,0.000397711,0.000432933,0.0004093,0.00032804,0.000203196,
6.06951e-05,-4.35841e-05,-8.5464e-05,-7.4602e-05,-3.88122e-05,-4.04483e-05,-0.000130343,-0.00030134,-0.000497514,-0.000679258,
-0.000815623,-0.000864775,-0.000821327,-0.000721615,-0.000589863,-0.000465223,-0.000387599,-0.000366648,-0.000385849,-0.000436
};
/**----------------------------- cabinet impulse response data end --------------------------------**/

void gx_cab_res(GtkWidget *widget, gpointer obj)
{
    GtkWidget *wid = (GtkWidget *)obj;
	if (!gtk_range_get_value(GTK_RANGE(wid))) {
		gx_engine::cab_conv.stop();
	} else {
		bool rc = gx_engine::cab_conv.configure(cab_ir_count, cab_ir_data, cab_ir_sr);
		if (!rc || !gx_engine::cab_conv.start()) {
			gtk_range_set_value(GTK_RANGE(wid), 0);
		}
	}

}

//----- systray menu
void gx_systray_menu( GtkWidget *widget, gpointer data )
{
	guint32 tim = gtk_get_current_event_time ();
	gtk_menu_popup (GTK_MENU(menuh),NULL,NULL,NULL,(gpointer) menuh,2,tim);
}

//---- choice dialog without text entry
gint gx_nchoice_dialog_without_entry (
	const char* window_title,
	const char* msg,
	const guint nchoice,
	const char* label[],
	const gint  resp[],
	const gint default_response
	)
{
	GtkWidget* dialog   = gtk_dialog_new();
	GtkWidget* text_label = gtk_label_new (msg);
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox), text_label);

	GdkColor colorGreen;
	gdk_color_parse("#969292", &colorGreen);
	gtk_widget_modify_fg (text_label, GTK_STATE_NORMAL, &colorGreen);

	GdkColor colorBlack;
	gdk_color_parse("#000000", &colorBlack);
	gtk_widget_modify_bg (dialog, GTK_STATE_NORMAL, &colorBlack);

	GtkStyle* text_style = gtk_widget_get_style(text_label);
	pango_font_description_set_size(text_style->font_desc, 10*PANGO_SCALE);
	pango_font_description_set_weight(text_style->font_desc, PANGO_WEIGHT_BOLD);

	gtk_widget_modify_font(text_label, text_style->font_desc);

	for (guint i = 0; i < nchoice; i++)
	{
		GtkWidget* button =
			gtk_dialog_add_button(GTK_DIALOG (dialog), label[i], resp[i]);

		gdk_color_parse("#555555", &colorBlack);
		gtk_widget_modify_bg(button, GTK_STATE_NORMAL, &colorBlack);

		g_signal_connect_swapped(button, "clicked",  G_CALLBACK (gtk_widget_destroy), dialog);
	}

	// set default
	gtk_dialog_set_has_separator(GTK_DIALOG(dialog), TRUE);
	gtk_dialog_set_default_response(GTK_DIALOG(dialog), default_response);
	gtk_window_set_title(GTK_WINDOW(dialog), window_title);

	gtk_widget_show(text_label);

	//--- run dialog and check response
	gint response = gtk_dialog_run (GTK_DIALOG (dialog));
	return response;
}

//---- choice dialog without text entry
gint gx_choice_dialog_without_entry (
	const char* window_title,
	const char* msg,
	const char* label1,
	const char* label2,
	const gint resp1,
	const gint resp2,
	const gint default_response
	)
{
	const guint nchoice     = 2;
	const char* labels[]    = {label1, label2};
	const gint  responses[] = {resp1, resp2};

	return gx_nchoice_dialog_without_entry(
		window_title,
		msg,
		nchoice,
		labels,
		responses,
		default_response);
}

//---- get text entry from dialog
void gx_get_text_entry(GtkEntry* entry, string& output)
{
	if (gtk_entry_get_text(entry)[0])
		output = gtk_entry_get_text(entry);
}

//---- choice dialog with text entry
gint gx_choice_dialog_with_text_entry (
	const char* window_title,
	const char* msg,
	const char* label1,
	const char* label2,
	const gint resp1,
	const gint resp2,
	const gint default_response,
	GCallback func
	)
{
	GtkWidget *dialog, *button1, *button2;
	dialog  = gtk_dialog_new();
	button1 = gtk_dialog_add_button(GTK_DIALOG (dialog), label1, resp1);
	button2 = gtk_dialog_add_button(GTK_DIALOG (dialog), label2, resp2);

	GtkWidget* text_label = gtk_label_new (msg);
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox), text_label);


	GtkWidget* gtk_entry = gtk_entry_new_with_max_length(32);
	gtk_entry_set_text(GTK_ENTRY(gtk_entry), "");
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox), gtk_entry);

	g_signal_connect_swapped (button1, "clicked",  G_CALLBACK (func), gtk_entry);

	gtk_dialog_set_has_separator(GTK_DIALOG(dialog), TRUE);
	gtk_dialog_set_default_response(GTK_DIALOG(dialog), default_response);
	gtk_entry_set_activates_default(GTK_ENTRY(gtk_entry), TRUE);
	GTK_BOX(GTK_DIALOG(dialog)->action_area)->spacing = 4;

	// some display style
	GdkColor colorGreen;
	gdk_color_parse("#969292", &colorGreen);
	gtk_widget_modify_fg (text_label, GTK_STATE_NORMAL, &colorGreen);

	GdkColor colorBlack;
	gdk_color_parse("#000000", &colorBlack);
	gtk_widget_modify_bg (dialog, GTK_STATE_NORMAL, &colorBlack);

	GtkStyle* text_style = gtk_widget_get_style(text_label);
	pango_font_description_set_size(text_style->font_desc, 10*PANGO_SCALE);
	pango_font_description_set_weight(text_style->font_desc, PANGO_WEIGHT_BOLD);

	gtk_widget_modify_font(text_label, text_style->font_desc);

	gdk_color_parse("#555555", &colorBlack);
	gtk_widget_modify_bg (button1, GTK_STATE_NORMAL, &colorBlack);

	gdk_color_parse("#555555", &colorBlack);
	gtk_widget_modify_bg (button2, GTK_STATE_NORMAL, &colorBlack);

	// display extra stuff
	gtk_widget_show (text_label);
	gtk_widget_show (gtk_entry);
	gtk_window_set_title(GTK_WINDOW(dialog), window_title);

	// run the dialog and wait for response
	gint response = gtk_dialog_run (GTK_DIALOG(dialog));

	if (dialog) gtk_widget_destroy(dialog);

	return response;
}

//---- retrive skin array index from skin name
void gx_actualize_skin_index(const string& skin_name)
{
	for (guint s = 0; s < skin_list.size(); s++) {
		if (skin_name == skin_list[s]) {
			gx_current_skin = s;
			return;
		}
	}
}

//------- count the number of available skins
unsigned int gx_fetch_available_skins()
{
	DIR *d;
	d = opendir(gx_style_dir.c_str());
	if (!d) {
		return 0;
	}
	// look for guitarix_*.rc and extract *-part
    struct dirent *de;
	while ((de = readdir(d)) != 0) {
		char *p = de->d_name;
		if (strncmp(p, "guitarix_", 9) != 0) {
			continue;
		}
		p += 9;
		int n = strlen(p) - 3;
		if (strcmp(p+n, ".rc") != 0) {
			continue;
		}
		skin_list.push_back(string(p, n));
		sort(skin_list.begin(), skin_list.end());
	}
	closedir(d);
	return skin_list.size();
}

// ----- skin change
void  gx_change_skin(GtkCheckMenuItem *menuitem, gpointer arg)
{
	// no action needed on false
	if (gtk_check_menu_item_get_active(menuitem) == FALSE)
		return;

	// update the skin to the one picked by user
	const int idx = (int)GPOINTER_TO_INT(arg);

	(void)gx_update_skin(idx, "gx_change_skin");
}

// ----- cycling through skin
void  gx_cycle_through_skin(GtkWidget *widget, gpointer arg)
{

	gint idx = gx_current_skin + 1;
	idx %= skin_list.size();

	// did it work ? if yes, update current skin
	if (gx_update_skin(idx, "gx_cycle_through_skin"))
		gx_current_skin = idx;

	// update menu item state
	gx_update_skin_menu_item(gx_current_skin);
}

// ----- cycling through skin
void  gx_update_skin_menu_item(const int index)
{
	// update menu item state
	GxMainInterface* gui = GxMainInterface::instance();
	GtkWidget* skinmenu = gui->getMenu("Skin");

	GList*     list = gtk_container_get_children(GTK_CONTAINER(skinmenu));
	GtkWidget* item = (GtkWidget*)g_list_nth_data(list, index);
	g_list_free(list);
	if (item) gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(item), TRUE);
}

// ---- skin changer, used internally frm callbacks
bool gx_update_skin(const gint idx, const char* calling_func)
{
	// check skin validity
	if (idx < 0 || idx >= (gint)skin_list.size())
	{
		gx_print_warning(calling_func, "skin index out of range, keeping actual skin");
		return false;
	}

	string rcfile = GX_STYLE_DIR + string("/") + "guitarix_";
	rcfile += skin_list[idx];
	rcfile += ".rc";

	gtk_rc_parse(rcfile.c_str());
	gtk_rc_reset_styles(gtk_settings_get_default());

	gx_current_skin = idx;

	// refresh wave view
	gx_waveview_refresh (GTK_WIDGET(livewa), NULL);
	if (int(float(gx_current_skin)==0))
	{
		if (set_knob !=1)
		{
			GtkRegler::gtk_regler_init_pixmaps(1);
			set_knob = 1;
		}
	}
	else if (int(float(gx_current_skin)==1))
	{
		if (set_knob !=2)
		{
			GtkRegler::gtk_regler_init_pixmaps(2);
			set_knob = 2;
		}
	}

	else if (int(float(gx_current_skin)==3))
	{
		if (set_knob !=3)
		{
			GtkRegler::gtk_regler_init_pixmaps(3);
			set_knob = 3;
		}
	}
	else if (int(float(gx_current_skin)==5))
	{
		if (set_knob !=4)
		{
			GtkRegler::gtk_regler_init_pixmaps(4);
			set_knob = 4;
		}
	}
	else if (int(float(gx_current_skin)==4))
	{
		if (set_knob !=5)
		{
			GtkRegler::gtk_regler_init_pixmaps(5);
			set_knob = 5;
		}
	}
	else if (int(float(gx_current_skin)==8))
	{
		if (set_knob !=3)
		{
			GtkRegler::gtk_regler_init_pixmaps(3);
			set_knob = 3;
		}
	}
	else
	{
		GtkRegler::gtk_regler_init_pixmaps(0);
		set_knob = 0;
	}

	// refresh latency check menu
	GxMainInterface* gui = GxMainInterface::instance();
	GtkWidget* wd = gui->getJackLatencyItem(gx_jack::jack_bs);
	if (wd) gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(wd), TRUE);

	return true;
}

// ---- set last used skin as default
bool gx_set_skin(GtkWidget *widget, gpointer data)
{
	return gx_update_skin(last_skin, "Set Skin");
}

//---- popup warning
int gx_message_popup(const char* msg)
{
	// check msg validity
	if (!msg)
	{
		gx_print_warning("Message Popup",
		                 string("warning message does not exist"));
		return -1;
	}

	// build popup window
	GtkWidget *about;
	GtkWidget *label;
	GtkWidget *ok_button;

	about = gtk_dialog_new();
	ok_button  = gtk_button_new_from_stock(GTK_STOCK_OK);

	label = gtk_label_new (msg);

	GtkStyle *style = gtk_widget_get_style(label);

	pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
	pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);

	gtk_widget_modify_font(label, style->font_desc);

	gtk_label_set_selectable(GTK_LABEL(label), TRUE);

	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(about)->vbox), label);

	GTK_BOX(GTK_DIALOG(about)->action_area)->spacing = 3;
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(about)->action_area), ok_button);

	g_signal_connect_swapped (ok_button, "clicked",
	                          G_CALLBACK (gtk_widget_destroy), about);

	g_signal_connect(label, "expose-event", G_CALLBACK(conv_widget_expose), NULL);
	gtk_widget_show (ok_button);
	gtk_widget_show (label);
	return gtk_dialog_run (GTK_DIALOG(about));
}

/* meter button release   */
void gx_meter_button_release(GdkEventButton* ev, gpointer arg)
{
	if (ev->button == 1)
	{
		cerr << " button event " << endl;
		GxMainInterface* gui = GxMainInterface::instance();

		GtkWidget* const*  meters = gui->getLevelMeters();

		for (int i = 0; i < 2; i++) {
			if (meters[i]) {
				gtk_fast_meter_clear(GTK_FAST_METER(meters[i]));
			}
		}
	}
}



/* ----- delete event ---- */
gboolean gx_delete_event( GtkWidget *widget, gpointer   data )
{
	gtk_range_set_value(GTK_RANGE(widget), 0);
	return TRUE;
}

gboolean gx_hide_eq( GtkWidget *widget, gpointer   obj )
{
	show_eq = (int) GTK_ADJUSTMENT (widget)->value;
	GtkWidget *wi = (GtkWidget *)obj;
	GtkWidget *box1 = gtk_widget_get_parent(GTK_WIDGET(wi));
	GtkWidget *box = gtk_widget_get_parent(GTK_WIDGET(box1));
	GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(box));
	GtkWidget *parent_eq = (GtkWidget *) g_list_nth_data(child_list,1);
	g_list_free(child_list);
	box = gtk_widget_get_parent(GTK_WIDGET(livewa));
	box1 = gtk_widget_get_parent(GTK_WIDGET(box1));

	// gtk_widget_set_size_request (parent_eq, 280,80);
	if (show_eq)
	{
		gtk_widget_show(parent_eq);
		//gtk_widget_set_size_request (box, -1, -1);
		if (GDK_IS_WINDOW (box1->window))
			gdk_window_invalidate_rect(GDK_WINDOW(box1->window),NULL,TRUE);
	}
	else
	{
		gtk_widget_hide(parent_eq);
		//gtk_widget_set_size_request (box, -1,-1);
		if (GDK_IS_WINDOW (box1->window))
			gdk_window_invalidate_rect(GDK_WINDOW(box1->window),NULL,TRUE);
	}

	return false;
}


} /* end of gx_gui namespace */

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
 * --------------------------------------------------------------------------
 */

/* --------------------------------------------------------------------------

   This is the guitarix preset handling functions

   ---------------------------------------------------------------------------*/

#include <cstring>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

#include <array>
#include <zita-convolver.h>
#include <fftw3.h>
#include <zita-resampler.h>

#include <cassert>
#include <sigc++/sigc++.h>
#include <semaphore.h>

using namespace std;

#include <sndfile.h>
#include <jack/jack.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#include "guitarix.h"

using namespace gx_system;

namespace gx_preset
{

/* get the accel path to connect the mnemonic key on the fly
   this is a replacement for gtk_widget_get_accel_path()
   witch is not avaluable in <= Gtk+2.12 */
string gx_get_accel_path(int lindex)
{

	// set accel_path
	string label  ;
	switch (lindex)
	{
	case 0:
		label = "Load";
		break;
	case 1:
		label = "Save";
		break;
	case 2:
		label = "Rename";
		break;
	case 3:
		label = "Delete";
		break;

	}
	//string acc_path = gtk_menu_get_accel_path(GTK_MENU(menu));
	string acc_path = "<guitarix>/";
	acc_path += label;
	acc_path += "/";

	return acc_path;
}

void gx_empty_preset_file(const char* filename)
{
	ofstream nfile(filename);
	JsonWriter jw(nfile);
	jw.begin_array();
	writeHeader(jw);
	jw.end_array(true);
	jw.close();
	nfile.close();
}

bool gx_modify_preset(const char* presname, const char* newname=0, bool remove=false, bool rewrite=false)
{
	string presetfile = gx_user_dir + guitarix_preset;
	string tmpfile    = presetfile + "_tmp";

	ifstream ofile(presetfile.c_str());
	ofstream nfile(tmpfile.c_str());
	JsonParser jp(ofile);
	JsonWriter jw(nfile);

	bool found = false;
	try {
		jp.next(JsonParser::begin_array);
		jw.begin_array();
		int major, minor;
		if (!readHeader(jp, &major, &minor)) {
			if (rewrite) {
				if (major == 0 && minor == 0) {
					gx_print_info("loading presets","rewriting convertet presets");
				} else {
					stringstream s;
					s << "major version mismatch in "+presetfile+": found "
					  << major << ", expected " << majorversion << endl;
					gx_print_warning("recall settings", s.str());
				}
			}
		}
		writeHeader(jw);

		while (jp.peek() != JsonParser::end_array) {
			jp.next(JsonParser::value_string);
			if (rewrite) {
				jw.write(jp.current_value());
				gx_gui::parameter_map.set_init_values();
				read_preset(jp);
				write_preset(jw);
			} else if (jp.current_value() == presname) {
				found = true;
				if (newname) {
					jw.write(newname);
					jp.copy_object(jw);
				} else if (remove) {
					jp.skip_object();
				} else {
					jw.write(presname);
					write_preset(jw);
					jp.skip_object();
				}
			} else {
				jw.write(jp.current_value().c_str());
				jp.copy_object(jw);
			}
		}
		jp.next(JsonParser::end_array);
		jp.next(JsonParser::end_token);

		if (!found && !remove && !newname && !rewrite) {
			jw.write(presname);
			write_preset(jw);
		}
		jw.end_array(true);
		jw.close();
		nfile.close();
		ofile.close();
		if (!nfile.good()) {
			gx_print_error("save preset","couldn't write " + tmpfile);
			return false;
		}

		int rc = rename(tmpfile.c_str(), presetfile.c_str());
		if (rc != 0) {
			gx_print_error("save preset","couldn't rename "
			               + tmpfile + " to " + presetfile);
			return false;
		}
	} catch (gx_system::JsonException& e) {
		gx_print_error("save/modify preset", "invalid preset file: " + presetfile);
	}
	return found;
}

//---- parsing preset file to build up a string vector of preset names
void gx_build_preset_list()
{
	// preset filename
	string filename = gx_user_dir + guitarix_preset;

	// initialize list
	plist.clear();

	// parse it if any
	ifstream f(filename.c_str());
	if (f.good()) {
		try {
			JsonParser jp(f);
			jp.next(JsonParser::begin_array);
			int samevers = readHeader(jp);
			while (jp.peek() == JsonParser::value_string) {
				jp.next();
				plist.push_back(jp.current_value());
				jp.skip_object();
			}
			jp.next(JsonParser::end_array);
			jp.next(JsonParser::end_token);
			f.close();
			// ---- how many did we get ?
			gx_print_info("Preset List Building",
			                 gx_i2a(plist.size()) + string(" presets found"));
			if (!samevers) {
				gx_modify_preset(0,0,false,true);
			}
			return;
		} catch (gx_system::JsonException& e) {
			gx_system::gx_print_warning("preset settings", "parse error");
		}
	}
	gx_empty_preset_file(filename.c_str());
}

// ----------- add new preset to menus
void gx_add_preset_to_menus(const string& presname)
{

	for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; i++)
		gx_add_single_preset_menu_item(presname, i, preset_action_func[i]);
}

//---- add a single preset to a given preset menu
void gx_add_single_preset_menu_item(const string& presname,
                                    const gint lindex,
                                    GCallback func)
{
	// menu
	GtkWidget* menu = presmenu[lindex];

	// index for keyboard shortcut (can take any list)
	int pos = preset_list[lindex].size() + 1;



	// add small mnemonic
	string name("_");
	name += gx_i2a(pos) + "  ";
	name += presname;

	// GDK numbers
	guint accel_key = GDK_1  + pos - 1;

	// create item
	GtkWidget* menuitem = gtk_menu_item_new_with_mnemonic (name.c_str());
	g_signal_connect (GTK_OBJECT (menuitem), "activate",
	                  G_CALLBACK (func),
	                  NULL);

	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuitem);

	// get accel_path for menuitem
	string acc_path = gx_get_accel_path(lindex);
	acc_path += gx_i2a(accel_key);

	if (pos < 10)
	{
		if (!gtk_accel_map_lookup_entry(acc_path.c_str(), NULL))
			gtk_accel_map_add_entry(acc_path.c_str(), accel_key, list_mod[lindex]);

		gtk_widget_set_accel_path(menuitem, acc_path.c_str(),
		                          gx_gui::GxMainInterface::instance()->fAccelGroup);
	}

	gtk_widget_show (menuitem);
	preset_list[lindex].insert(pair<GtkMenuItem*,string>(GTK_MENU_ITEM(menuitem), presname));
}

// ----------- remove old preset from menus
void gx_del_preset_from_menus(const string& presname)
{
	for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; i++)
		gx_del_single_preset_menu_item(presname, i);

	gx_refresh_preset_menus();
}

void  gx_del_single_preset_menu_item(const string& presname, const gint lindex)
{
	GtkMenuItem* const item = gx_get_preset_item_from_name(lindex, presname);
	if (item)
	{
		preset_list[lindex].erase(item);
		gtk_widget_destroy(GTK_WIDGET(item));
	}
}

// ----------- retrieve menu item given a name
GtkMenuItem* const gx_get_preset_item_from_name(int lindex, const string& name)
{
	map<GtkMenuItem*, string>::iterator it;
	for (it  = preset_list[lindex].begin(); it != preset_list[lindex].end(); it++)
		if (name == it->second)
			return it->first;

	return NULL;
}

// ----------- update preset numbering in menus
void gx_refresh_preset_menus()
{

	// string acc_path;

	for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; i++)
	{
		guint n = 1;

		map<GtkMenuItem*, string>::iterator it;
		for (it = preset_list[i].begin(); it != preset_list[i].end(); it++)
		{
			GtkMenuItem* const item = it->first;

			// add small mnemonic
			string name("_");
			name += gx_i2a(n) + "  ";

			// get menu label
			GtkWidget *menu_widget = gtk_bin_get_child(GTK_BIN(item));
			string label = gtk_label_get_text(GTK_LABEL(menu_widget));

			// replace accel key
			label.replace(0, 2, name);
			gtk_label_set_text_with_mnemonic(GTK_LABEL(menu_widget),label.c_str());


			// refresh acc key for this item
			guint accel_key = GDK_1 + n - 1;

			// get accel_path for menuitem
			string acc_path = gx_get_accel_path(i);
			acc_path += gx_i2a(accel_key);

			if (n < 10)
			{
				if (!gtk_accel_map_lookup_entry(acc_path.c_str(), NULL))
					gtk_accel_map_add_entry(acc_path.c_str(), accel_key, list_mod[i]);
			}

			// connect acc key with menuitem and group
			gtk_widget_set_accel_path(GTK_WIDGET(item), acc_path.c_str(),
			                          gx_gui::GxMainInterface::instance()->fAccelGroup);

			n++;
		}
	}
}

// ---------- load nth preset (return true if successful)
bool gx_nth_preset(unsigned char n)
{
	// check that we do have presets
	if (preset_list[LOAD_PRESET_LIST].size() == 0)
	{
		gx_print_warning("Preset Switching",
		                 "Preset list is empty, make some :)");
		return false;
	}

	map<GtkMenuItem*, string>::iterator it = preset_list[LOAD_PRESET_LIST].begin();
	while (n > 0) {
		it++;
		if (it == preset_list[LOAD_PRESET_LIST].end())
			return false;
		n--;
	}

	// load the preset
	gx_load_preset(it->first, NULL);
	return true;
}

// ---------- switch to next preset in queue
void gx_next_preset(GtkWidget* item, gpointer arg)
{
	// check that we do have presets
	if (preset_list[LOAD_PRESET_LIST].size() == 0)
	{
		gx_print_warning("Preset Switching",
		                 "Preset list is empty, make some :)");
		return;
	}

	// start from this element
	map<GtkMenuItem*, string>::iterator it;

	// initialize iterator
	if (!setting_is_preset)
		it = preset_list[LOAD_PRESET_LIST].begin();
	else
	{
		GtkMenuItem* const item =
			gx_get_preset_item_from_name(LOAD_PRESET_LIST, gx_current_preset);

		it = preset_list[LOAD_PRESET_LIST].find(item);

		// increment iterator and load preset
		it++;
	}


	// check if we are on edge
	if (it == preset_list[LOAD_PRESET_LIST].end())
		it = preset_list[LOAD_PRESET_LIST].begin();

	// load the preset
	gx_load_preset(it->first, NULL);
}

// ---------- switch to next preset in queue
void gx_previous_preset(GtkWidget* item, gpointer arg)
{
	// check that we do have presets
	if (preset_list[LOAD_PRESET_LIST].size() == 0)
	{
		gx_print_warning("Preset Switching",
		                 "Preset list is empty, make some :)");
		return;
	}

	// start from this element
	map<GtkMenuItem*, string>::iterator it;

	// initialize iterator
	if (!setting_is_preset)
		it = preset_list[LOAD_PRESET_LIST].end();
	else
	{
		GtkMenuItem* const item =
			gx_get_preset_item_from_name(LOAD_PRESET_LIST, gx_current_preset);

		it = preset_list[LOAD_PRESET_LIST].find(item);

	}

	// check if we are on edge
	if (it == preset_list[LOAD_PRESET_LIST].begin())
		it = preset_list[LOAD_PRESET_LIST].end();

	// decrement iterator and load preset
	it--;


	// load the preset
	gx_load_preset(it->first, NULL);
}

// ----------
void gx_delete_active_preset_dialog(GtkWidget* item, gpointer arg)
{

	if (!setting_is_preset || gx_current_preset.empty())
	{
		gx_print_warning("Deleting Active Preset",
		                 "No active preset, this is the main setting");
		return;
	}

	// tmp store
	string presname = gx_current_preset;

	// call dialog
	gx_delete_preset_dialog (NULL, NULL);

	if (gx_current_preset.empty() && !setting_is_preset)
		gx_print_info("Deleting Active Preset",
		              string("Deleted preset ") + presname +
		              string(", recalled main setting"));
}


//----preset deletion dialog
void gx_delete_preset_dialog (GtkMenuItem *menuitem, gpointer arg)
{
	string presname =
		menuitem ? preset_list[DELETE_PRESET_LIST][menuitem] : gx_current_preset;

	string msg = "   Are you sure you want to delete preset ";
	msg += presname;
	msg += " ?? ";

	string title = "Deleting preset ";
	title += presname;

	//--- run dialog and check response
	gint response =
		gx_gui::gx_choice_dialog_without_entry (
			title.c_str(), msg.c_str(),
			"Delete Preset", "Keep Preset",
			GTK_RESPONSE_YES, GTK_RESPONSE_CANCEL, GTK_RESPONSE_YES
			);

	// we are cancelling
	if (response == GTK_RESPONSE_CANCEL)
	{
		gx_print_warning("Preset Deleting",
		                 string(" Deletion of preset ") + presname +
		                 string(" has been cancelled"));
		return;
	}

	// we want to delete the bugger!
	gx_delete_preset (menuitem, arg);

}

//----delete all presets dialog
void gx_delete_all_presets_dialog (GtkMenuItem *menuitem, gpointer arg)
{
	//--- if no presets, then just pop up some info
	if (preset_list[DELETE_PRESET_LIST].empty())
	{
		gx_print_warning("Delete All Presets Dialog",
		                 string("There is no presets to delete"));
		return;
	}

	//--- run dialog and check response
	gint response =
		gx_gui::gx_choice_dialog_without_entry (
			"Deleting ALL Presets! ",
			"   Are you sure you want to delete ALL your cool presets ? ",
			"Yes, DO IT NOW!", "Maybe Later ...",
			GTK_RESPONSE_YES, GTK_RESPONSE_CANCEL, GTK_RESPONSE_YES
			);

	// we are cancelling
	if (response == GTK_RESPONSE_CANCEL)
	{
		gx_print_warning("Delete All Presets Dialog",
		                 "All Presets deletion has been cancelled");
		return;
	}

	// we want to delete all the buggers!
	gx_delete_all_presets ();

}

//----delete all presets
void  gx_delete_all_presets()
{
	// this function will simply delete the preset file,
	// clear the preset list and refresh the menus

	// write empty preset file
	ofstream f((gx_user_dir + guitarix_preset).c_str());
	JsonWriter jw(f);
	jw.begin_array();
	writeHeader(jw);
	jw.end_array(true);
	jw.close();
	f.close();

	// clear list
	for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; i++)
	{
		map<GtkMenuItem*, string>::iterator it = preset_list[i].begin();

		while (it != preset_list[i].end())
		{
			GtkMenuItem* item = it->first;
			gtk_widget_destroy(GTK_WIDGET(item));
			it++;
		}

		preset_list[i].clear();
	}

	gx_print_info("All Presets Deleting", string("deleted ALL presets!"));
}

bool gx_load_preset_from_file(const char* presname)
{
	string presetfile = gx_user_dir + guitarix_preset;

	ifstream ofile(presetfile.c_str());
	JsonParser jp(ofile);

	try {
		jp.next(JsonParser::begin_array);
		readHeader(jp);

		bool found = false;
		while (jp.peek() != JsonParser::end_array) {
			jp.next(JsonParser::value_string);
			if (jp.current_value() == presname) {
				found = true;
				read_preset(jp);
				return true;
			} else {
				jp.skip_object();
			}
		}
		jp.next(JsonParser::end_array);
		jp.next(JsonParser::end_token);
	} catch (JsonException& e) {
		gx_print_error("load preset", "invalid preset file: " + presetfile);
	}
	return false;
}

//----preset deletion
void gx_delete_preset (GtkMenuItem* item, gpointer arg)
{

	// delete it via interface
	const string presname =
		item ? preset_list[DELETE_PRESET_LIST][item] : gx_current_preset;

	(void)gx_modify_preset(presname.c_str(), NULL, true);

	// update menu
	gx_del_preset_from_menus(presname);

	// recalling main setting
	gx_recall_main_setting(NULL, NULL);

	gx_print_warning("Preset Deleting",
	                 string("Deleted preset ") +
	                 presname + string(", recalled main setting"));
}

// ----------
void gx_rename_active_preset_dialog(GtkWidget* item, gpointer arg)
{
	if (!setting_is_preset || gx_current_preset.empty())
	{
		gx_print_warning("Renaming Active Preset",
		                 "This is the main setting, "
		                 "load a preset first");
		return;
	}

	string presname = gx_current_preset;

	// get current preset menu item
	GtkMenuItem* const rnm_item =
		gx_get_preset_item_from_name(RENAME_PRESET_LIST, presname);

	// call delete dialog
	if (rnm_item)
		gx_rename_preset_dialog (rnm_item, NULL);

	if (presname == gx_current_preset)
	{
		gx_print_warning("Renaming Active Preset",
		                 "The preset name is unchanged");
		return;
	}

	if (!gx_current_preset.empty() && setting_is_preset)
		gx_print_info("Renaming Active Preset",
		              string("Renamed preset ") + presname +
		              string(" to ") + gx_current_preset);
}

static gboolean gx_convolver_restart(gpointer data)
{
    gx_engine::conv.stop();
    while (gx_engine::conv.is_runnable()) gx_engine::conv.checkstate();
    gx_jconv::GxJConvSettings* jcset = gx_jconv::GxJConvSettings::instance();
    bool rc = gx_engine::conv.configure(
    gx_jack::jack_bs, gx_jack::jack_sr, jcset->getIRDir()+"/"+jcset->getIRFile(),
        jcset->getGain(), jcset->getlGain(), jcset->getDelay(), jcset->getlDelay(),
        jcset->getOffset(), jcset->getLength(), jcset->getMem(), jcset->getBufferSize());

    if (!rc || !gx_engine::conv.start()) {
        gx_jconv::GxJConvSettings::checkbutton7 = 0;
    }
    return false;
}

static gboolean gx_rename_main_widget(gpointer data)
{
    // refresh main window name
    string title = string("guitarix ") + gx_current_preset;
	gtk_window_set_title (GTK_WINDOW (gx_gui::fWindow), title.c_str());
	// reload convolver settings widget
	gx_jconv::gx_reload_jcgui();
    return false;
}

//----menu funktion load
void gx_load_preset (GtkMenuItem *menuitem, gpointer load_preset)
{
	// check that we do have presets
	if (preset_list[LOAD_PRESET_LIST].size() == 0)
	{
		gx_print_warning("Preset Loading",
		                 "Preset list is empty, make some :)");
		return;
	}

	// retrieve preset name
	string preset_name = preset_list[LOAD_PRESET_LIST][menuitem];

	// recall preset by name
	// Note: the UI does not know anything about guitarix's directory stuff
	// Need to pass it on
	bool preset_ok = gx_load_preset_from_file(preset_name.c_str());

	// check result
	if (!preset_ok)
	{
		gx_print_error("Preset Loading", string("Could not load preset ") + preset_name);
		return;
	}

	// print out info
	gx_print_info("Preset Loading", string("loaded preset ") + preset_name);
	setting_is_preset = true;
	gx_current_preset = preset_name;

	/* do some GUI stuff*/
	g_idle_add(gx_rename_main_widget,NULL);

	/* reset convolver buffer for preset change*/
	if (gx_engine::conv.is_runnable() && gx_jconv::GxJConvSettings::checkbutton7 == 1)  {
		gx_engine::conv.stop();
        gx_gui::g_threads[3] = g_idle_add_full(G_PRIORITY_HIGH_IDLE+20,gx_convolver_restart,NULL,NULL);
	}
}

//---- funktion save
void gx_save_preset (const char* presname, bool expand_menu)
{
	bool found = gx_modify_preset(presname);

	// update preset menus if needed
	if (expand_menu == found) {
		assert(false);
	}
	if (expand_menu)
		gx_add_preset_to_menus(string(presname));

	// refresh display
	string ttle = string("guitarix ") + presname;
	gtk_window_set_title (GTK_WINDOW (gx_gui::fWindow), (gchar*)ttle.c_str());

	// we are now in a preset setting
	setting_is_preset = true;
	gx_current_preset = presname;

	gx_print_info("Preset Saving", string("saved preset ") + string(presname));
	gx_jconv::gx_reload_jcgui(); //FIXME why reload after saving?
}

//----menu funktion save
void gx_save_oldpreset (GtkMenuItem *menuitem, gpointer arg)
{
	guint save_active = GPOINTER_TO_UINT(arg);
	string presname;

	// are saving an active preset
	if (save_active)
	{
		if (gx_current_preset.empty())
		{
			gx_print_warning("Saving Active Preset",
			                 "We are in main setting, load a preset first");
			return;
		}
		presname = gx_current_preset;
	}

	// we are saving another preset from the menu
	else
		presname = preset_list[SAVE_PRESET_LIST][menuitem];

	gx_save_preset(presname.c_str(), false);
}

//----clean up preset name given by user
void gx_cleanup_preset_name(string& presname)
{
	gx_nospace_in_name(presname, "-");
}

//----menu funktion save
void gx_save_newpreset (GtkEntry* entry)
{
	string presname;
	gx_gui::gx_get_text_entry(entry, presname);

	// no text ?
	if (presname.empty())
	{
		gx_print_error("Saving new preset", "no preset name given");
		return;
	}

	// replace spaces by -
	gx_cleanup_preset_name(presname);

	// is the name alrady taken ?
	map<GtkMenuItem*, string>::iterator it;
	for (it  = preset_list[SAVE_PRESET_LIST].begin();
	     it != preset_list[SAVE_PRESET_LIST].end();
	     it++)
	{
		// found a match
		if (presname == it->second)
		{
			gx_print_error("New Preset Saving",
			               string("preset name ") +
			               presname +
			               string(" already in use, choose another one"));
			gx_save_newpreset_dialog(it->first, NULL);
			return;
		}
	}

	// finally save to preset file
	gx_save_preset(presname.c_str(), true);
	gx_jconv::gx_reload_jcgui();
}

// read name for presset
void gx_recall_main_setting(GtkMenuItem* item, gpointer)
{
	string jname = gx_jack::client_name;

	gx_system::recallState(gx_user_dir + jname + "_rc");
	jname = "guitarix";
	gtk_window_set_title(GTK_WINDOW(gx_gui::fWindow), jname.c_str());

	gx_print_info("Main Setting recalling","Called back main setting");

	setting_is_preset = false;
	gx_current_preset = "";
}

void gx_recall_settings_file( const string & filename )
{
	string jname = gx_jack::client_name;

	gx_system::recallState(filename);
	gtk_window_set_title(GTK_WINDOW(gx_gui::fWindow), jname.c_str());

	gx_print_info("loading Settings file","loaded settings file");

	setting_is_preset = false;
	gx_current_preset = "";
}

// ----- save current setting as main setting
void gx_save_main_setting(GtkMenuItem* item, gpointer arg)
{
	string jname = gx_jack::client_name;

	if (! saveStateToFile(gx_user_dir + jname + "_rc")) {
		gx_print_error("Main Setting","can't save main setting");
	} else if (setting_is_preset) {
		gx_print_info("Main Setting",
		              "Saved current preset into main setting");
	} else {
		gx_print_info("Main Setting", "Saved main setting");
	}
	gtk_window_set_title(GTK_WINDOW(gx_gui::fWindow), jname.c_str());
	setting_is_preset = false;
	gx_jconv::gx_reload_jcgui();
}

//----menu function save new preset
void gx_save_newpreset_dialog (GtkMenuItem *menuitem, gpointer save_preset)
{
	// preset name to save
	string presname;

	// running dialog and get response
	gint response =
		gx_gui::gx_choice_dialog_with_text_entry (
			"Save new preset ... ",
			"\n   Please enter a valid preset name:   \n",
			"Save Preset", "Cancel",
			GTK_RESPONSE_YES, GTK_RESPONSE_CANCEL, GTK_RESPONSE_YES,
			G_CALLBACK(gx_save_newpreset)
			);

	// check response
	if (response == GTK_RESPONSE_CANCEL)
	{
		gx_print_warning("Saving New Preset Dialog",
		                 " Preset saving has been cancelled");
		return;
	}
}


//----preset renaming
void gx_rename_preset (GtkEntry* entry)
{
	// rename preset
	string newname;
	gx_gui::gx_get_text_entry(entry, newname);

	if (newname.empty())
	{
		gx_print_error("Preset Renaming", "no preset name given");
		old_preset_name = "";
		return;
	}

	// replace spaces by -
	gx_cleanup_preset_name(newname);

	// get the UI to manipulate the preset file
	string presetfile = gx_user_dir + guitarix_preset;

	if (!gx_modify_preset(old_preset_name.c_str(), newname.c_str()))	{
		gx_print_error("Preset Renaming",
		               string("Could not rename preset ") + old_preset_name);
		old_preset_name = "";
		return;
	}

	// if jconv file
	string jc_preset   = gx_user_dir + string("jconv_") + old_preset_name + ".conf ";
	string jc_file     = gx_user_dir + string("jconv_") + newname + ".conf ";
	string file_move   = jc_preset + jc_file;
	(void)gx_system_call("mv", file_move.c_str(), true);

	// refresh the menus
	for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; i++) {
		GtkMenuItem* const item  =
			gx_get_preset_item_from_name(i, old_preset_name);

		if (!item) continue;

		//string label = gtk_menu_item_get_label(item);
		//label.erase(label.find("  ") + 2);
		//label.append(newname);
		//gtk_menu_item_set_label(item, label.c_str());

		// patch by Michal Šebeň for openSuse
		GtkWidget *menu_widget = gtk_bin_get_child(GTK_BIN(item));
		string label = gtk_label_get_text(GTK_LABEL(menu_widget));
		label.erase(label.find("  ") + 2);
		label.append(newname);

		gtk_label_set_text(GTK_LABEL(menu_widget), label.c_str());

		preset_list[i][item] = newname;

		// refresh main window name we were in preset context
		if (setting_is_preset)
		{
			string jname = "guitarix ";
			string title = jname + newname;
			gtk_window_set_title (GTK_WINDOW (gx_gui::fWindow), title.c_str());

			gx_current_preset = newname;
		}
	}

	gx_print_info("Preset Renaming", string("preset ") + old_preset_name +
	              string(" renamed into ") + newname);
	old_preset_name = "";
	gx_jconv::gx_reload_jcgui();
}

//----preset renaming dialog
void gx_rename_preset_dialog (GtkMenuItem *menuitem, gpointer arg)
{
	static string title;
	if (menuitem)
	{
		title += "Renaming preset ";
		title += preset_list[RENAME_PRESET_LIST][menuitem];
	}

	old_preset_name = preset_list[RENAME_PRESET_LIST][menuitem];

	// running dialog and get response
	gint response = gx_gui::gx_choice_dialog_with_text_entry (
		title.c_str(),
		" Please enter a valid preset name:                          ",
		"Validate", "Cancel",
		GTK_RESPONSE_YES, GTK_RESPONSE_CANCEL, GTK_RESPONSE_YES,
		G_CALLBACK(gx_rename_preset)
		);

	if (response == GTK_RESPONSE_CANCEL)
	{
		gx_print_warning("Rename Preset Dialog",
		                 " Preset renaming has been cancelled");
		old_preset_name = "";
		return;
	}
}

/* ----------------------------------------------------------------*/
} /* end of gx_preset namespace */

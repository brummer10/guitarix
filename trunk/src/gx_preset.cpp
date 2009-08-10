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
 * --------------------------------------------------------------------------
 */

/* --------------------------------------------------------------------------

   This is the guitarix preset handling functions

 ---------------------------------------------------------------------------*/

#include <cstring>
#include <list>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstdio>


using namespace std;

#include <sndfile.h>
#include <jack/jack.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include "guitarix.h"

using namespace gx_system;

namespace gx_preset
{

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
      string buffer;
      while (!f.eof()) {
	// get line
	getline(f, buffer);
	if (buffer.empty()) continue;

	// parse buffer
	istringstream values(buffer);

	// grab first item in line
	string pname; values >> pname;
	plist.push_back(pname);
      }
      f.close();
    }

    // ---- how many did we get ?
    gx_print_warning("Preset List Building",
		     gx_i2a(plist.size()) + string(" presets found"));
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

    string acc_path = gtk_menu_get_accel_path(GTK_MENU(menu));
    acc_path += "/";
    acc_path += gx_i2a(accel_key);

    // add accelerator in accel path if not added (up to pos = 9)
    if (pos < 10) {
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
    if (item) {
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

    string acc_path;

    for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; i++) {
      guint n = 1;

      map<GtkMenuItem*, string>::iterator it;
      for (it = preset_list[i].begin(); it != preset_list[i].end(); it++) {
	GtkMenuItem* const item = it->first;
	//string label = gtk_menu_item_get_label(item);
	//label.replace(1, 1, gx_i2a(n));
	//gtk_menu_item_set_label(item, label.c_str());

	// patch by Michal Šebeň for openSuse
    GtkWidget *menu_widget = gtk_bin_get_child(GTK_BIN(item));
    string label = gtk_label_get_text(GTK_LABEL(menu_widget));
    label.replace(1, 1, gx_i2a(n));
    gtk_label_set_text(GTK_LABEL(menu_widget), label.c_str());

	// refresh acc path for this item
	guint accel_key = GDK_1 + n - 1;
	acc_path = gtk_menu_get_accel_path(GTK_MENU(presmenu[i]));
	acc_path += "/";
	acc_path += gx_i2a(accel_key);
	gtk_widget_set_accel_path(GTK_WIDGET(item), acc_path.c_str(),
				  gx_gui::GxMainInterface::instance()->fAccelGroup);

	n++;
      }
    }
  }

  // ---------- switch to next preset in queue
  void gx_next_preset(GtkWidget* item, gpointer arg)
  {
    // check that we do have presets
    if (preset_list[LOAD_PRESET_LIST].size() == 0) {
      gx_print_warning("Preset Switching",
		       "Preset list is empty, make some :)");
      return;
    }

    // start from this element
    map<GtkMenuItem*, string>::iterator it;

    // initialize iterator
    if (!setting_is_preset)
      it = preset_list[LOAD_PRESET_LIST].begin();
    else {
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
    if (preset_list[LOAD_PRESET_LIST].size() == 0) {
      gx_print_warning("Preset Switching",
		       "Preset list is empty, make some :)");
      return;
    }

    // start from this element
    map<GtkMenuItem*, string>::iterator it;

    // initialize iterator
    if (!setting_is_preset)
      it = preset_list[LOAD_PRESET_LIST].end();
    else {
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

    if (!setting_is_preset || gx_current_preset.empty()) {
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

    // delete preset file
    string filename = gx_user_dir + guitarix_preset;
    (void)gx_system_call("rm -f", filename.c_str(), true);

    // delete jconv files
    ostringstream cmd; cmd << "cd " << gx_user_dir << " && ls -1";
    (void)gx_system_call(cmd.str(), "jconv* | grep -v jconv_set | xargs rm -f");

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

  //----preset deletion
  void gx_delete_preset (GtkMenuItem* item, gpointer arg)
  {

    // delete it via interface
    const string presname =
      item ? preset_list[DELETE_PRESET_LIST][item] : gx_current_preset;

    const string presfile = gx_user_dir + guitarix_preset;
    const string tmpfile  = presfile + "_tmp";
    const string space    = " ";

    // let's use a tmp file that does not contain the preset
    ostringstream cat_tmpfile("cat");
    cat_tmpfile << presfile << space
		<< "| grep -v" << space << presname << space
		<< ">" << tmpfile;

    cerr << cat_tmpfile.str() << endl;

    (void)gx_system_call("cat", cat_tmpfile.str());
    usleep(200);

    // rename tmp file
    rename(tmpfile.c_str(), presfile.c_str());

    // did we really delete it ?
    if (gx_system_call("grep", presname + space + presfile) == SYSTEM_OK)
      {
	gx_print_error("Preset Deleting",
		       string("Could not deleted preset ") +
		       preset_list[DELETE_PRESET_LIST][item]);
	return;
      }

    // remove tmp file (not necessary)
    (void)gx_system_call("rm -f", tmpfile);

    // remove jconv file
    string jc_preset = gx_user_dir + string("jconv_") + presname + ".conf";
    (void)gx_system_call("rm -f", jc_preset);

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

    gx_jconv::GxJConvSettings* jcset = gx_jconv::GxJConvSettings::instance();
    gx_jconv::GxJConvSettings::checkbutton7 = 0;

    gx_gui::GxMainInterface* interface = gx_gui::GxMainInterface::instance();
    interface->updateAllGuis();

    // retrieve preset name
    string preset_name = preset_list[LOAD_PRESET_LIST][menuitem];

    // load jconv setting
    string jc_preset   = gx_user_dir + string("jconv_") + preset_name + ".conf ";
    jcset->configureJConvSettings(preset_name);

    // recall preset by name
    // Note: the UI does not know anything about guitarix's directory stuff
    // Need to pass it on
    string presetfile = gx_user_dir + "guitarixprerc";
    bool preset_ok = interface->recallPresetByname(presetfile.c_str(),
						   preset_name.c_str());

    // check result
    if (!preset_ok) {
      gx_print_error("Preset Loading", string("Could not load preset ") + preset_name);
      return;
    }

    // refresh main window name
    string title = string("guitarix ") + preset_name;
    gtk_window_set_title (GTK_WINDOW (gx_gui::fWindow), title.c_str());

    // print out info
    gx_print_info("Preset Loading", string("loaded preset ") + preset_name);

    setting_is_preset = true;
    gx_current_preset = preset_name;
  }


  //---- funktion save
  void gx_save_preset (const char* presname, bool expand_menu)
  {

    string setting;
    gx_gui::GxMainInterface* interface =
      gx_gui::GxMainInterface::instance();

    interface->updateAllGuis();
    interface->dumpStateToString(setting);

    // save preset and update menus
    if (setting.empty()) {
      gx_print_error("Preset Saving",
		     string("setting EMPTY!! could not save preset ")
		     + string(presname));
      return;
    }

    // append preset name in front
    setting.insert(0, presname);

    // manipulate preset file
    string presetfile = gx_user_dir + guitarix_preset;
    string tmpfile    = presetfile + "_tmp";

    (void)gx_system_call("touch", presetfile.c_str());
    usleep(200);

    (void)gx_system_call("touch", tmpfile.c_str());
    usleep(200);

    // copy actual presetfile to tmpfile minus preset to be saved
    ostringstream cat_tmpfile; string space = " ";
    cat_tmpfile << presetfile << space
		<< "| grep -v" << space << presname << space
		<< ">" << tmpfile;

    (void)gx_system_call("cat", cat_tmpfile.str());
    usleep(200);

    // append saved preset to tmpfile
    (void)gx_system_call("echo", setting + string(" >> ") + tmpfile);
    usleep(200);

    // rename tmp file to preset file
    rename(tmpfile.c_str(), presetfile.c_str());


    // remove tmp file (not necessary)
    (void)gx_system_call("rm -f", tmpfile);

    // update preset menus if needed
    if (expand_menu)
      gx_add_preset_to_menus(string(presname));

    // refresh display
    string ttle = string("guitarix ") + presname;
    gtk_window_set_title (GTK_WINDOW (gx_gui::fWindow), (gchar*)ttle.c_str());

    // we are now in a preset setting
    setting_is_preset = true;
    gx_current_preset = presname;

    // save current jconv setting to jconv preset
    gx_jconv::gx_save_jconv_settings(NULL, NULL);

    gx_print_info("Preset Saving", string("saved preset ") + string(presname));
  }

  //----menu funktion save
  void gx_save_oldpreset (GtkMenuItem *menuitem, gpointer arg)
  {
    guint save_active = GPOINTER_TO_UINT(arg);
    string presname;

    // are saving an active preset
    if (save_active) {
      if (gx_current_preset.empty()) {
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
    if (presname.empty()) {
      gx_print_error("Saving new preset", "no preset name given");
      return;
    }

    // replace spaces by -
    gx_cleanup_preset_name(presname);

    // is the name alrady taken ?
    map<GtkMenuItem*, string>::iterator it;
    for (it  = preset_list[SAVE_PRESET_LIST].begin();
	 it != preset_list[SAVE_PRESET_LIST].end();
	 it++) {
      // found a match
      if (presname == it->second) {
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
  }

  // read name for presset
  void gx_recall_main_setting(GtkMenuItem* item, gpointer arg)
  {
    if (!gx_jack::client || !gx_jack::jack_is_running) {
      gx_print_warning("Main Setting recalling", "We are not a jack client!");
      return;
    }

    string jname = jack_get_client_name(gx_jack::client);
    string previous_state = gx_user_dir + jname + "rc";

    gx_gui::GxMainInterface* interface =
      gx_gui::GxMainInterface::instance();

    interface->recallState(previous_state.c_str());
    gtk_window_set_title(GTK_WINDOW(gx_gui::fWindow), jname.c_str());

    gx_print_info("Main Setting recalling",
		  string("Called back main setting"));

    setting_is_preset = false;
    gx_current_preset = "";

    // recall jconv main setting
    string s = ""; // empty string = main setting
    gx_jconv::GxJConvSettings::instance()->configureJConvSettings(s);
  }

  // ----- save current setting as main setting
  void gx_save_main_setting(GtkMenuItem* item, gpointer arg)
  {
    if (!gx_jack::client || !gx_jack::jack_is_running) {
      gx_print_warning("Main Setting Saving", "We are not a jack client!");
      return;
    }

    string jname = jack_get_client_name(gx_jack::client);
    string previous_state = gx_user_dir + jname + "rc";

    gx_gui::GxMainInterface* interface =
      gx_gui::GxMainInterface::instance();

    interface->saveStateToFile(previous_state.c_str());

    if (setting_is_preset)
      gx_print_info("Main Setting",
		    string("Saved current preset into main setting"));
    else
      gx_print_info("Main Setting",
		    string("Saved main setting"));

    gtk_window_set_title(GTK_WINDOW(gx_gui::fWindow), jname.c_str());
    setting_is_preset = false;
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
    if (response == GTK_RESPONSE_CANCEL) {
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

    if (newname.empty()) {
      gx_print_error("Preset Renaming", "no preset name given");
      old_preset_name = "";
      return;
    }

    // replace spaces by -
    gx_cleanup_preset_name(newname);

    // get the UI to manipulate the preset file
    string presetfile = gx_user_dir + guitarix_preset;

    gx_gui::GxMainInterface* interface =
      gx_gui::GxMainInterface::instance();

    if (!interface->renamePreset(presetfile.c_str(),
				 old_preset_name.c_str(),
				 newname.c_str())) {
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
      if (setting_is_preset) {
	string jname = string(jack_get_client_name(gx_jack::client)) + " ";
	string title = jname + newname;
	gtk_window_set_title (GTK_WINDOW (gx_gui::fWindow), title.c_str());

	gx_current_preset = newname;
      }
    }

    gx_print_info("Preset Renaming", string("preset ") + old_preset_name +
		  string(" renamed into ") + newname);
    old_preset_name = "";
  }

  //----preset renaming dialog
  void gx_rename_preset_dialog (GtkMenuItem *menuitem, gpointer arg)
  {
    static string title;
    if (menuitem) {
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

    if (response == GTK_RESPONSE_CANCEL) {
      gx_print_warning("Rename Preset Dialog",
		       " Preset renaming has been cancelled");
      old_preset_name = "";
      return;
    }
  }

  /* ----------------------------------------------------------------*/
} /* end of gx_preset namespace */

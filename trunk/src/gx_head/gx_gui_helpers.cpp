/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * ---------------------------------------------------------------------------
 *
 *    This is the gx_head GUI related functionality
 *
 * ----------------------------------------------------------------------------
 */

#include "guitarix.h"      //  NOLINT

#include <unistd.h>        //  NOLINT

#include <cstring>         //  NOLINT
#include <algorithm>       //  NOLINT
#include <string>          //  NOLINT
#include <iostream>        // NOLINT
#include <gdk/gdkkeysyms.h>            // NOLINT
#include <gtkmm/filechooserdialog.h>   // NOLINT


namespace gx_preset {

/****************************************************************
 */
GxPreset gxpreset;

/* get the accel path to connect the mnemonic key on the fly
   this is a replacement for gtk_widget_get_accel_path()
   witch is not avaluable in <= Gtk+2.12 */
string GxPreset::gx_get_accel_path(int lindex) {

    // set accel_path
    string label;
    switch (lindex) {
    case 0:
        label = _("Load");
        break;
    case 1:
        label = _("Save");
        break;
    case 2:
        label = _("Rename");
        break;
    case 3:
        label = _("Delete");
        break;
    }
    // string acc_path = gtk_menu_get_accel_path(GTK_MENU(menu));
    string acc_path = "<gx_head>/";
    acc_path += label;
    acc_path += "/";

    return acc_path;
}

// ---- parsing preset file to build up a string vector of preset names
bool GxPreset::gx_build_preset_list() {
    // initialize list
    gxpreset.plist.clear();
    // initialize menu pointer list
    for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; ++i) {
        gxpreset.pm_list[i].clear();
    }
    GxSettings::get_instance().fill_preset_names(gxpreset.plist);
    // ---- how many did we get ?
    gx_system::gx_print_info(
	_("Preset List Building"),
	boost::format(_("%1% presets found")) % gxpreset.plist.size());
    return true;
}

// ----------- add new preset to menus
void GxPreset::gx_add_preset_to_menus(const string& presname) {
    static callback_with_menuitem preset_action_func[] = {
        gxpreset.gx_load_preset,
        gxpreset.gx_save_oldpreset,
        gxpreset.gx_rename_preset_dialog,
        gxpreset.gx_delete_preset_dialog
    };
    for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; ++i)
        gx_add_single_preset_menu_item(presname, i, preset_action_func[i]);
}

// ---- add a single preset to a given preset menu
void GxPreset::gx_add_single_preset_menu_item(
    const string& presname, const gint lindex, callback_with_menuitem func) {
    // menu
    gx_gui::GxMainInterface& gui = gx_gui::GxMainInterface::get_instance();
    Gtk::Menu& menu = gui.mainmenu.preset_submenu[lindex];

    // index for keyboard shortcut (can take any list)
    vector<Gtk::MenuItem*>::iterator its;
    int pos = 0;
    for (its = pm_list[lindex].begin(); its != pm_list[lindex].end(); ++its) {
        ++pos;
    }
    pos += 1;

    // add small mnemonic
    string name = gx_system::to_string(pos) + "  " + presname;
    if (pos <= 9) {
	name = "_" + name;
    }

    // GDK numbers
    guint accel_key = GDK_1  + pos - 1;

    // create item
    Gtk::MenuItem* menuitem = manage(new Gtk::MenuItem(name, true));
    menuitem->signal_activate().connect(
	sigc::bind(sigc::ptr_fun(func), menuitem));

    menu.append(*menuitem);

    // get accel_path for menuitem
    string acc_path = gx_get_accel_path(lindex) + gx_system::to_string(accel_key);

    static GdkModifierType list_mod[] = {
        GDK_NO_MOD_MASK,
        GDK_CONTROL_MASK,
        GDK_MOD1_MASK,
        GdkModifierType(GDK_CONTROL_MASK|GDK_MOD1_MASK)
    };

    if (pos < 10) {
        if (!gtk_accel_map_lookup_entry(acc_path.c_str(), NULL))
            gtk_accel_map_add_entry(acc_path.c_str(), accel_key, list_mod[lindex]);

	menuitem->Gtk::Widget::set_accel_path(acc_path, gui.fAccelGroup); //FIXME
    }

    its = pm_list[lindex].end();
    // add a pointer to the menuitem to the preset menu list
    pm_list[lindex].insert(its, menuitem);
    menuitem->show();
}


// ----- get the preset number by name from preset list
int GxPreset::gx_get_single_preset_menu_pos(const string& presname, const gint lindex) {
    vector<string>::iterator its;
    int pos = 0;
    for (its = gxpreset.plist.begin(); its != gxpreset.plist.end(); ++its) {
        ++pos;
        if (presname == *its)
            return pos;
    }
    return 0;
}

// ----- get pointer to the menuitem
Gtk::MenuItem* const GxPreset::gx_get_preset_item_from_name(int lindex, const string& name) {
    vector<string>::iterator its;
    vector<Gtk::MenuItem*>::iterator it = pm_list[lindex].begin();
    int pos = 0;
    for (its = plist.begin(); its != plist.end(); ++its) {
        ++pos;
        if (name == *its)
            return *it;
        ++it;
    }
    return NULL;
}

// ----------- update preset numbering in menus
void GxPreset::gx_refresh_preset_menus() {
    for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; ++i) {
        vector<Gtk::MenuItem*>::iterator it = pm_list[i].begin();
        for (it = pm_list[i].begin(); it != pm_list[i].end(); ++it) {
            delete *it;
        }
    }

    if (!gx_build_preset_list()) {
        gx_system::gx_print_warning(
	    _("Load preset file"), _("selecting default preset bank"));
	GxSettings::get_instance().set_std_presetfile();
        gx_build_preset_list();
    }
    vector<string>::iterator its;
    for (its = plist.begin() ; its != plist.end(); ++its) {
        gx_add_preset_to_menus(*its);
    }
}

// ---------- load nth preset (return true if successful)
bool GxPreset::gx_nth_preset(unsigned char n) {
    // check that we do have presets
    if (!pm_list[LOAD_PRESET_LIST].size()) {
        gx_system::gx_print_warning(
	    _("Preset Switching"),
	    _("Preset list is empty, make some :)"));
        return false;
    }
    vector<Gtk::MenuItem*>::iterator it = pm_list[LOAD_PRESET_LIST].begin();
    while (n > 0) {
        ++it;
        if (it == pm_list[LOAD_PRESET_LIST].end())
            return false;
        --n;
    }

    // load the preset
    gx_load_preset(*it);
    return true;
}

// ---------- switch to next preset in queue
void GxPreset::gx_next_preset() {
    // check that we do have presets
    if (!gxpreset.pm_list[LOAD_PRESET_LIST].size()) {
        gx_system::gx_print_warning(_("Preset Switching"),
				    _("Preset list is empty, make some :)"));
        return;
    }

    // start from this element
    vector<Gtk::MenuItem*>::iterator it = gxpreset.pm_list[LOAD_PRESET_LIST].begin();
    if (GxSettings::get_instance().setting_is_preset()) {
	Gtk::MenuItem* const itemi =
            gxpreset.gx_get_preset_item_from_name(
		LOAD_PRESET_LIST, GxSettings::get_instance().get_current_name());
        for (it = gxpreset.pm_list[LOAD_PRESET_LIST].begin();
             it != gxpreset.pm_list[LOAD_PRESET_LIST].end();++it ) {
            if (itemi == *it)
                break;
        }
        ++it;
    }
    // check if we are on edge
    if (it == gxpreset.pm_list[LOAD_PRESET_LIST].end())
        it = gxpreset.pm_list[LOAD_PRESET_LIST].begin();

    // load the preset
    gx_load_preset(*it);
}

// ---------- switch to next preset in queue
void GxPreset::gx_previous_preset() {
    // check that we do have presets
    if (!gxpreset.pm_list[LOAD_PRESET_LIST].size()) {
        gx_system::gx_print_warning(_("Preset Switching"),
				    _("Preset list is empty, make some :)"));
        return;
    }

    // start from this element
    vector<Gtk::MenuItem*>::iterator it = gxpreset.pm_list[LOAD_PRESET_LIST].end();
    if (GxSettings::get_instance().setting_is_preset()) {
	Gtk::MenuItem* const itemi =
            gxpreset.gx_get_preset_item_from_name(LOAD_PRESET_LIST, GxSettings::get_instance().get_current_name());
        for (it = gxpreset.pm_list[LOAD_PRESET_LIST].begin();
             it != gxpreset.pm_list[LOAD_PRESET_LIST].end(); ++it) {
            if (itemi == *it)
                break;
        }
    }

    // check if we are on edge
    if (it == gxpreset.pm_list[LOAD_PRESET_LIST].begin())
        it = gxpreset.pm_list[LOAD_PRESET_LIST].end();

    // decrement iterator and load preset
    --it;

    // load the preset
    gxpreset.gx_load_preset(*it);
}

// ----------
void GxPreset::gx_delete_active_preset_dialog() {
    if (!GxSettings::get_instance().setting_is_preset() || GxSettings::get_instance().get_current_name().empty()) {
        gx_system::gx_print_warning(_("Deleting Active Preset"),
				    _("No active preset, this is the main setting"));
        return;
    }

    // tmp store
    string presname = GxSettings::get_instance().get_current_name();

    // call dialog
    gxpreset.gx_delete_preset_dialog(NULL);

    if (GxSettings::get_instance().get_current_name().empty() && !GxSettings::get_instance().setting_is_preset())
        gx_system::gx_print_info(_("Deleting Active Preset"),
				 string(_("Deleted preset ")) + presname +
				 string(_(", recalled main setting")));
}


// ----preset deletion dialog
void GxPreset::gx_delete_preset_dialog(Gtk::MenuItem *menuitem) {
    string presname = GxSettings::get_instance().get_current_name();

    string msg = _("   Are you sure you want to delete preset ");
    msg += presname;
    msg += " ?? ";

    string title =_("Deleting preset ");
    title += presname;

    // --- run dialog and check response
    gint response =
        gx_gui::gx_choice_dialog_without_entry(
            title.c_str(), msg.c_str(),
            _("Delete Preset"), _("Keep Preset"),
            GTK_RESPONSE_YES, GTK_RESPONSE_CANCEL, GTK_RESPONSE_YES
        );

    // we are cancelling
    if (response == GTK_RESPONSE_CANCEL) {
        gx_system::gx_print_warning(_("Preset Deleting"),
				    string(_(" Deletion of preset ")) + presname +
				    string(_(" has been cancelled")));
        return;
    }

    // we want to delete the bugger!
    gxpreset.gx_delete_preset(menuitem);
}

// ----delete all presets dialog
void GxPreset::gx_delete_all_presets_dialog() {
    // --- if no presets, then just pop up some info
    if (gxpreset.pm_list[LOAD_PRESET_LIST].empty()) {
        gx_system::gx_print_warning(_("Delete All Presets Dialog"),
				    _("There is no presets to delete"));
        return;
    }

    // --- run dialog and check response
    gint response =
        gx_gui::gx_choice_dialog_without_entry(
            _("Deleting ALL Presets! "),
            _("   Are you sure you want to delete ALL your cool presets ? "),
            _("Yes, DO IT NOW!"), _("Maybe Later ..."),
            GTK_RESPONSE_YES, GTK_RESPONSE_CANCEL, GTK_RESPONSE_YES
        );

    // we are cancelling
    if (response == GTK_RESPONSE_CANCEL) {
        gx_system::gx_print_warning(_("Delete All Presets Dialog"),
				    _("All Presets deletion has been cancelled"));
        return;
    }
    // we want to delete all the buggers!
    gxpreset.gx_delete_all_presets();
}

// ----delete all presets
void GxPreset::gx_delete_all_presets() {
    // this function will simply delete the preset file,
    GxSettings::get_instance().clear_preset();
    gx_system::gx_print_info(_("All Presets Deleting"), _("deleted ALL presets!"));
}

static bool gx_load_preset_from_file(const char* presname) {
    GxSettings::get_instance().load(
	GxSettings::preset,presname);
    return true;
}

// ----preset deletion
void GxPreset::gx_delete_preset(Gtk::MenuItem* item) {

    // delete it via interface
    const string presname = GxSettings::get_instance().get_current_name();

    GxSettings::get_instance().erase_preset(presname);

    // recalling main setting
    gxpreset.gx_recall_settings_file();

    gx_system::gx_print_warning(_("Preset Deleting"),
				string(_("Deleted preset ")) +
				presname + string(_(", recalled main setting")));
}

// ----------
void GxPreset::gx_rename_active_preset_dialog() {
    if (!GxSettings::get_instance().setting_is_preset() || GxSettings::get_instance().get_current_name().empty()) {
        gx_system::gx_print_warning(_("Renaming Active Preset"),
				    _("This is the main setting, "
				      "load a preset first"));
        return;
    }

    string presname = GxSettings::get_instance().get_current_name();

    // get current preset menu item
    Gtk::MenuItem* const rnm_item =
        gxpreset.gx_get_preset_item_from_name(RENAME_PRESET_LIST, presname);

    // call delete dialog
    if (rnm_item)
        gxpreset.gx_rename_preset_dialog(rnm_item);

    if (presname == GxSettings::get_instance().get_current_name()) {
        gx_system::gx_print_warning(_("Renaming Active Preset"),
				    _("The preset name is unchanged"));
        return;
    }

    if (!GxSettings::get_instance().get_current_name().empty() && GxSettings::get_instance().setting_is_preset())
        gx_system::gx_print_info(_("Renaming Active Preset"),
				 string(_("Renamed preset ")) + presname +
				 string(_(" to ")) + GxSettings::get_instance().get_current_name());
}

// ----menu funktion load
void GxPreset::gx_load_preset(Gtk::MenuItem *menuitem) {
    // check that we do have presets
    if (!gxpreset.pm_list[LOAD_PRESET_LIST].size()) {
        gx_system::gx_print_warning(_("Preset Loading"),
				    _("Preset list is empty, make some :)"));
        return;
    }

    // retrieve preset name
    vector<Gtk::MenuItem*>::iterator it = gxpreset.pm_list[LOAD_PRESET_LIST].begin();
    vector<string>::iterator its = gxpreset.plist.begin();
    for (it = gxpreset.pm_list[LOAD_PRESET_LIST].begin(); it != gxpreset.pm_list[LOAD_PRESET_LIST].end(); ++it) {
        if (menuitem == *it)
            break;
        ++its;
    }
    string preset_name = *its;

    // recall preset by name
    // Note: the UI does not know anything about gx_head's directory stuff
    // Need to pass it on
    bool preset_ok = gx_load_preset_from_file(preset_name.c_str());

    // check audio.result
    if (!preset_ok) {
        gx_system::gx_print_error(
	    _("Preset Loading"), string(_("Could not load preset ")) + preset_name);
        return;
    }

    // print out info
    gx_system::gx_print_info(_("Preset Loading"), string(_("loaded preset ")) + preset_name);
    /* collect info for stage info display*/
    gx_gui::guivar.show_patch_info = gx_get_single_preset_menu_pos(GxSettings::get_instance().get_current_name(), 0);
}

// ---- funktion save
void GxPreset::gx_save_preset(const char* presname, bool expand_menu) {
    bool found = GxSettings::get_instance().get_preset_index(presname) >= 0;
    GxSettings::get_instance().save_to_preset(presname);

    // update preset menus if needed
    if (expand_menu == found) {
        assert(false);
    }
    gx_system::gx_print_info(_("Preset Saving"), string(_("saved preset ")) + string(presname));
}

// ----menu funktion load preset from factory
void GxPreset::gx_load_factory_preset(
    const string& factory_name, const string& preset_name) {

    gx_gui::guivar.show_patch_info -= 9999;
    GxSettings& gxs = GxSettings::get_instance();
    gxs.load(GxSettings::factory, preset_name, factory_name);
    gx_gui::guivar.show_patch_info = -1;
    // print out info
    gx_system::gx_print_info(
	_("Preset Loading"), string(_("loaded preset ")) + preset_name);
}

// load the factory preset file
void GxPreset::gx_append_factory_file(const string& name, Gtk::Menu& menu) {
    vector<string> fp;
    GxSettings::get_instance().fill_factory_preset_names(name, fp);
    for (vector<string>::iterator it = fp.begin() ; it != fp.end(); ++it) {
	Gtk::MenuItem *menuitem = new Gtk::MenuItem(*it, true);
        menuitem->show();
	menuitem->signal_activate().connect(
	    sigc::bind(sigc::ptr_fun(gx_load_factory_preset), name, *it));
	menu.append(*manage(menuitem));
    }
}

///------ user preset handling------///
// load a preset file
void GxPreset::gx_recall_settings_file() {
    GxSettings::get_instance().load(GxSettings::state);
#if 0 //FIXME
    gx_system::gx_print_info(
	_("Main Setting recalling"),
	(boost::format(_("Called back main setting %1%")) % fname).str());
    gx_system::gx_print_info(
	_("loading Settings file"),
	(boost::format(_("loaded settings file %1%")) % *filename).str());
#endif
    gx_gui::guivar.show_patch_info = 0;
}

// ----- select a external preset file
void GxPreset::gx_load_preset_file() {
    Gtk::FileChooserDialog file_chooser(
	gx_gui::GxMainInterface::get_instance().fWindow,
        _("Select a preset *_rc file"),
        Gtk::FILE_CHOOSER_ACTION_OPEN);
    file_chooser.add_button(GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL);
    file_chooser.add_button(GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT);
    file_chooser.set_filename(GxSettings::get_instance().get_preset_filename());
    file_chooser.set_show_hidden(true);
    file_chooser.set_select_multiple(false);
    Gtk::FileFilter filter;
    filter.add_pattern("*_rc");
    filter.set_name("*_rc");
    file_chooser.add_filter(filter);
    Gtk::FileFilter filter1;
    filter1.add_pattern("*");
    filter1.set_name("all");
    file_chooser.add_filter(filter1);
    file_chooser.set_filter(filter);
    while (true) {
	if (file_chooser.run() != Gtk::RESPONSE_ACCEPT) {
	    break;
	}
	if (GxSettings::get_instance().set_preset_file(file_chooser.get_filename())) {
	    gx_gui::guivar.show_patch_info = 0;
	    break;
	}
    }
}

// ----- export preset file
void GxPreset::gx_save_preset_file() {
    Gtk::FileChooserDialog file_chooser(
        gx_gui::GxMainInterface::get_instance().fWindow,
        _("Save a preset *_rc File"),
        Gtk::FILE_CHOOSER_ACTION_SAVE);
    file_chooser.add_button(GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL);
    file_chooser.add_button(GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT);
    file_chooser.set_do_overwrite_confirmation(true);
    file_chooser.set_show_hidden(true);
    Gtk::FileFilter filter;
    filter.add_pattern("*_rc");
    file_chooser.set_filter(filter);
    file_chooser.set_current_folder(GxSettings::get_instance().get_preset_dirname());
    file_chooser.set_current_name("Untitled_rc");
    if (file_chooser.run() == Gtk::RESPONSE_ACCEPT) {
        string save_file = file_chooser.get_filename();
        int n = save_file.length() - 3;
        if (!(n >= 0 && save_file.substr(n) == "_rc")) { // FIXME: use a real extension
            save_file += "_rc";
        }
        try {
            GxSettings::get_instance().copy_preset_file(save_file);
        } catch(const Glib::Exception& ex) {
            gx_system::gx_print_error(_("Export preset"), ex.what());
        }
    }
}

void GxPreset::gx_save_active_preset() {
    if (GxSettings::get_instance().get_current_name().empty()) {
	gx_system::gx_print_warning(_("Saving Active Preset"),
				    _("We are in main setting, load a preset first"));
	return;
    }
    string presname = GxSettings::get_instance().get_current_name();
    gxpreset.gx_save_preset(presname.c_str(), false);
}

// ----menu funktion save
void GxPreset::gx_save_oldpreset(Gtk::MenuItem* menuitem) {
    string presname;
    vector<string>::iterator its = gxpreset.plist.begin();

    vector<Gtk::MenuItem*>::iterator it;

    for (it = gxpreset.pm_list[SAVE_PRESET_LIST].begin();
	 it != gxpreset.pm_list[SAVE_PRESET_LIST].end(); ++it) {
	if (menuitem == *it) {
	    break;
	}
	++its;
    }
    presname = *its;
    gxpreset.gx_save_preset(presname.c_str(), false);
}

// ----clean up preset name given by user
void GxPreset::gx_cleanup_preset_name(Glib::ustring& presname) {
    Glib::RefPtr<Glib::Regex> re = Glib::Regex::create(" ");
    re->replace_literal(presname, 0, "-", static_cast<Glib::RegexMatchFlags>(0));
}

// ----menu funktion save
void GxPreset::gx_save_newpreset(GtkEntry* entry) {
    Glib::ustring presname;
    gx_gui::gx_get_text_entry(entry, presname);

    // no text ?
    if (presname.empty()) {
        gx_system::gx_print_error(_("Saving new preset"), _("no preset name given"));
        return;
    }

    // replace spaces by -
    gxpreset.gx_cleanup_preset_name(presname);

    // is the name alrady taken ?
    vector<string>::iterator its;
    vector<Gtk::MenuItem*>::iterator it = gxpreset.pm_list[SAVE_PRESET_LIST].begin();

    for (its = gxpreset.plist.begin(); its != gxpreset.plist.end(); ++its) {
        // found a match
        if (presname == *its) {
            gx_system::gx_print_error(_("New Preset Saving"),
				      string(_("preset name ")) +
				      presname +
				      string(_(" already in use, choose another one")));
            gxpreset.gx_save_newpreset_dialog();
            return;
        }
        ++it;
    }

    // finally save to preset file
    gxpreset.gx_save_preset(presname.c_str(), true);
}

// ----- save current setting as main setting
void GxPreset::gx_save_main_setting() {
    gx_gui::GxMainInterface& gui = gx_gui::GxMainInterface::get_instance();
    if (gui.is_in_session()) {
	GxSettings::get_instance().set_source_to_state();
    } else {
	GxSettings::get_instance().save_to_state();
    }
#if 0 //FIXME
        gx_system::gx_print_error(_("Main Setting"), _("can't save main setting"));
    } else if (GxSettings::get_instance().setting_is_preset()) {
        gx_system::gx_print_info(_("Main Setting"),
				 _("Saved current preset into main setting"));
    } else {
        gx_system::gx_print_info(_("Main Setting"), _("Saved main setting"));
#endif
}

// ----menu function save new preset
void GxPreset::gx_save_newpreset_dialog() {
    // preset name to save
    string presname;

    // running dialog and get response
    gint response =
        gx_gui::gx_choice_dialog_with_text_entry(
            _("Save new preset ... "),
            _("\n   Please enter a valid preset name:   \n"),
            _("Save Preset"), _("Cancel"),
            GTK_RESPONSE_YES, GTK_RESPONSE_CANCEL, GTK_RESPONSE_YES,
            G_CALLBACK(gx_save_newpreset)
        );

    // check response
    if (response == GTK_RESPONSE_CANCEL) {
        gx_system::gx_print_warning(_("Saving New Preset Dialog"),
				    _(" Preset saving has been cancelled"));
        return;
    }
}


// ----preset renaming
void GxPreset::gx_rename_preset(GtkEntry* entry) {
    // rename preset
    Glib::ustring newname;
    gx_gui::gx_get_text_entry(entry, newname);

    if (newname.empty()) {
        gx_system::gx_print_error(_("Preset Renaming"), _("no preset name given"));
        gxpreset.old_preset_name = "";
        return;
    }
    if (GxSettings::get_instance().get_preset_index(newname) >= 0) {
        gx_system::gx_print_error(_("Preset Renaming"), _("name already exists"));
        gxpreset.old_preset_name = "";
        return;
    }

    // replace spaces by -
    gxpreset.gx_cleanup_preset_name(newname);

    // get the UI to manipulate the preset file
    if (!GxSettings::get_instance().rename_preset(gxpreset.old_preset_name, newname)) {
        gx_system::gx_print_error(_("Preset Renaming"),
				  string(_("Could not rename preset ")) + gxpreset.old_preset_name);
        gxpreset.old_preset_name = "";
        return;
    }
}

// ----preset renaming dialog
void GxPreset::gx_rename_preset_dialog(Gtk::MenuItem *menuitem) {
    vector<string>::iterator its = gxpreset.plist.begin();
    vector<Gtk::MenuItem*>::iterator it = gxpreset.pm_list[RENAME_PRESET_LIST].begin();
    for (it = gxpreset.pm_list[RENAME_PRESET_LIST].begin(); it != gxpreset.pm_list[RENAME_PRESET_LIST].end(); ++it) {
        if ( menuitem == *it)
            break;
        ++its;
    }

    static string title;
    if (menuitem) {
        title = _("Renaming preset ");
        title += *its;
    }

    gxpreset.old_preset_name = *its;
    // running dialog and get response
    gint response = gx_gui::gx_choice_dialog_with_text_entry(
                        title.c_str(),
                        _(" Please enter a valid preset name:                          "),
                        _("Validate"), _("Cancel"),
                        GTK_RESPONSE_YES, GTK_RESPONSE_CANCEL, GTK_RESPONSE_YES,
                        G_CALLBACK(gxpreset.gx_rename_preset)
                    );

    if (response == GTK_RESPONSE_CANCEL) {
        gx_system::gx_print_warning(_("Rename Preset Dialog"),
				    _(" Preset renaming has been cancelled"));
        gxpreset.old_preset_name = "";
        return;
    }
}

} //! namespace gx_preset

/* --------------------------- gx_gui namespace ------------------------ */
namespace gx_gui {

/* ----- Menu check item signaled from parameter ------ */

MenuCheckItem::MenuCheckItem(const char *label, const char *id, bool sv)
  : Gtk::CheckMenuItem(label, true),
    param() {
    set_parameter(new gx_engine::SwitchParameter(id, false, sv));
}

void MenuCheckItem::on_my_activate() {
    param->set(get_active());
}

gx_engine::SwitchParameter* MenuCheckItem::get_parameter() {
    return param;
}

void MenuCheckItem::set_parameter(gx_engine::SwitchParameter *p) {
    param = p;
    gx_engine::parameter_map.insert(p);
    p->signal_changed().connect(sigc::mem_fun(*this, &MenuCheckItem::set_active));
    set_active(p->get());
    signal_activate().connect(
        sigc::mem_fun(*this, &MenuCheckItem::on_my_activate));
}

void MenuCheckItem::add_parameter(gx_engine::SwitchParameter *p) {
    param = p;
    p->signal_changed().connect(sigc::mem_fun(*this, &MenuCheckItem::set_active));
    signal_activate().connect(
        sigc::mem_fun(*this, &MenuCheckItem::on_my_activate));
}

void RadioCheckItem::on_my_toggled() {
    param->set(get_active());
}

gx_engine::SwitchParameter* RadioCheckItem::get_parameter() {
    return param;
}

void RadioCheckItem::set_parameter(gx_engine::SwitchParameter *p) {
    param = p;
    gx_engine::parameter_map.insert(p);
    p->signal_changed().connect(sigc::mem_fun(*this, &RadioCheckItem::set_active));
    signal_activate().connect(
        sigc::mem_fun(*this, &RadioCheckItem::on_my_toggled));
}

/* ----- load a top level window from gtk builder file ------ */

GtkWidget *load_toplevel(GtkBuilder *builder, const char* filename, const char* windowname) {
    string fname = gx_system::get_options().get_builder_filepath(filename);
    GError *err = NULL;
    if (!gtk_builder_add_from_file(builder, fname.c_str(), &err)) {
        g_object_unref(G_OBJECT(builder));
        gx_system::gx_print_fatal(_("gtk builder"), err->message);
        g_error_free(err);
        return NULL;
    }
    GtkWidget *w = GTK_WIDGET(gtk_builder_get_object(builder, windowname));
    if (!w) {
        g_object_unref(G_OBJECT(builder));
        gx_system::gx_print_fatal(_("gtk builder"), string(windowname)+_(" not found in ")+fname);
        return NULL;
    }
    gtk_builder_connect_signals(builder, 0);
    return w;
}

// ----- pop up a dialog for starting jack
bool gx_start_jack_dialog() {
    // --- run dialog and check response
    const guint nchoices    = 3;

    const char* labels[]    = {
            _("Start Jack"), _("Ignore Jack"), _("Exit")
        };

    const gint  responses[] = {
            GTK_RESPONSE_YES, GTK_RESPONSE_NO, GTK_RESPONSE_CANCEL
        };

    gint response =
        gx_gui::gx_nchoice_dialog_without_entry(
            _(" Jack Starter "),
            _("\n                            WARNING                    \n\n"
            "   The jack server is not currently running\n"
            "   You can choose to activate it or terminate gx_head   \n\n"
            "       1) activate jack   \n"
            "       2) ignore jack, start gx_head anyway   \n"
            "       3) exit gx_head   \n"),
            nchoices,
            labels,
            responses,
            GTK_RESPONSE_YES);

    // we are cancelling
    bool retstat = false;

    switch (response) {
    case GTK_RESPONSE_NO:
        //set_jack_down(true); FIXME
        break;

    case GTK_RESPONSE_CANCEL:
	gx_system::GxExit::get_instance().exit_program();
        break;

    default:
    case GTK_RESPONSE_YES:
        retstat = gx_system::gx_start_jack();
        break;
    }

    // start jack
    return retstat;
}

/* -------------- for thread that checks jackd liveliness -------------- */
bool GxMainInterface::survive_jack_shutdown() {
    // return if jack is not down
    if (gx_system::gx_system_call("pgrep", "jackd", true) == SYSTEM_OK) {
        if (jack.is_jack_down()) {
        sleep(2);
	    jack.set_jack_down(false);
	}
	// let's make sure we get out of here
	gx_system::gx_print_warning("Jack Shutdown",
				    _("jack has bumped us out!!   "));
	mainmenu.jack_connect_item.set_active(true);
	// run only one time whem jackd is running
	return false;
    } else if (!jack.is_jack_down()) {
        // refresh some stuff. Note that it can be executed
        // more than once, no harm here
        mainmenu.jack_connect_item.set_active(false);
        jack.set_jack_down(true);
	gx_system::gx_print_error("Jack Shutdown",
				  _("jack has bumped us out!!   "));
    }
    // run as long jackd is down
    return true;
}

void GxMainInterface::gx_jack_is_down() {
    jack_connection_change();
    mainmenu.jack_connect_item.set_active(false);
    Glib::signal_timeout().connect(
	sigc::mem_fun(*this, &GxMainInterface::survive_jack_shutdown),
	200, Glib::PRIORITY_LOW);
}

#ifdef HAVE_JACK_SESSION
void GxMainInterface::jack_session_event() {
    const char *statefile = "gx_head.state";
    jack_session_event_t *event = jack.get_last_session_event();
    set_in_session();
    gx_settings.set_statefilename(string(event->session_dir) + statefile);
    gx_settings.save_to_state();

#ifndef NDEBUG
    string cmd(options.get_path_to_program());
#else
    string cmd("guitarix");
#endif
    cmd += " -U ";
    cmd += event->client_uuid;
    cmd += " -A ";
    cmd += jack.get_uuid_insert();
    cmd += " -f ${SESSION_DIR}";
    cmd += statefile; // no space after SESSION_DIR
    event->command_line = strdup(cmd.c_str());

    JackSessionEventType tp = event->type;
    if (jack.return_last_session_event() == 0) {
	if (tp == JackSessionSaveAndQuit) {
	    gx_system::GxExit::get_instance().exit_program("** session exit **");
	}
    }
}

void GxMainInterface::jack_session_event_ins() {
    jack_session_event_t *event = jack.get_last_session_event_ins();
    set_in_session();
    event->command_line = strdup("true ${SESSION_DIR}");
    JackSessionEventType tp = event->type;
    if (jack.return_last_session_event_ins() == 0) {
	if (tp == JackSessionSaveAndQuit) {
	    gx_system::GxExit::get_instance().exit_program("** session exit **");
	}
    }
}
#endif

void ReportXrun::clear() {
    blocked = false;
}

void ReportXrun::run() {
    if (blocked) {
	return;
    }
    blocked = true;
    Glib::signal_timeout().connect_once(sigc::mem_fun(*this, &ReportXrun::clear), 100);
    gx_system::gx_print_warning(
	_("Jack XRun"),
	(boost::format(_(" delay of at least %1% microsecs"))
	 % jack.get_last_xrun()).str());
}

// ----menu function gx_show_oscilloscope
void GxMainInterface::on_show_oscilloscope(bool v) {
    if (v) {
	// FIXME G_PRIORITY_DEFAULT_IDLE??
	Glib::signal_timeout().connect(
	    sigc::mem_fun(*this, &GxMainInterface::on_refresh_oscilloscope), 60); 
    }
}

void show_error_msg(const string& msg) {
    Gtk::MessageDialog dialog(
	msg, false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE, true);
    dialog.set_title("gx_head");
    dialog.run();
}

// show loggingbox
void GxMainInterface::on_log_activate() {
    if (mainmenu.fShowLogger.get_active()) {
        gint rxorg, ryorg;
        fWindow.get_position(rxorg, ryorg);
        fLoggingWindow.move(rxorg+5, ryorg+272);
        fLoggingWindow.show_all();
    } else {
        fLoggingWindow.hide();
    }
}

// ----menu function oatch info widget
void gx_patch() {
    gtk_widget_show_all(gw.patch_info);
}

void gx_show_help() {
    GError *error = NULL;
    gtk_show_uri(gdk_screen_get_default(), "http://sourceforge.net/apps/mediawiki/guitarix/index.php?title=Main_Page",
    gtk_get_current_event_time(), &error);
    if (error)
    {
        gx_system::gx_print_error("guitarix help",
				  _("failed to load online help   "));
        g_error_free(error);
    } 

}

// ----menu funktion about
void gx_show_about() {
    static string about;
    if (about.empty()) {
        about +=
            _("\n\n  This Aplication is to a large extent provided"
            "\n  with the marvelous faust compiler.Yann Orlary"
            "\n  http://faust.grame.fr/"
            "\n  A large part is based on the work of Julius Orion Smith"
            "\n  http://ccrma.stanford.edu/realsimple/faust/"
            "\n  and Albert Graef\n  http://q-lang.sourceforge.net/examples.html#Faust"
            "\n\n\n  gx_head ");

        about += GX_VERSION;

        about +=
            _("\n  for impulse response it use zita-convolver "
            "\n  byFons Adriaensen "
            "\n  http://www.kokkinizita.net/linuxaudio/index.html "
            "\n\n  authors: Hermann Meyer <brummer-@web.de>"
            "\n  authors: James Warden <warjamy@yahoo.com>"
            "\n  authors: Andreas Degert <andreas.degert@googlemail.com>    "
            "\n  authors: Pete Shorthose <pshorthose@gmail.com>    "
            "\n  home: http://guitarix.sourceforge.net/\n");
    }

    gx_message_popup(about.c_str());
}


void gx_reset_effects(GtkWidget *widget, gpointer data ) {
    string pos(".position");
    for (gx_engine::ParamMap::iterator i = gx_engine::parameter_map.begin(); i != gx_engine::parameter_map.end(); ++i) {
        string id = i->first;
        if (id.size() > pos.size() &&
            id.compare(id.size()-pos.size(), pos.size(), pos) == 0) {
            i->second->set_std_value();
        }
    }
}

// reset the extended sliders to default settings
void gx_reset_units(Glib::ustring group_id) {
    group_id += ".";
    string on_off = group_id + "on_off";
    for (gx_engine::ParamMap::iterator i = gx_engine::parameter_map.begin(); i != gx_engine::parameter_map.end(); ++i) {
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

gboolean gx_set_resizeable(gpointer data) {
    if (!gtk_window_get_resizable(GTK_WINDOW(data)))
        gtk_window_set_resizable(GTK_WINDOW(data), TRUE);
    return false;
}

gboolean gx_set_sresizeable(gpointer data) {
    if (!gtk_window_get_resizable(GTK_WINDOW(data)))
        gtk_window_set_resizable(GTK_WINDOW(data), FALSE);
    return false;
}

gboolean gx_set_default(gpointer data) {
    gtk_widget_set_size_request(GTK_WIDGET(data), -1, -1);
    return false;
}

gboolean gx_set_default_size(gpointer data) {
    gtk_widget_set_size_request(GTK_WIDGET(data), -1, 440);
    return false;
}

gboolean gx_set_default_ssize(gpointer data) {
    gtk_widget_set_size_request(GTK_WIDGET(data), -1, 460);
    return false;
}

// ----- show extendend settings slider
void gx_show_extended_settings(GtkWidget *widget, gpointer data) {
    gx_gui::GxMainInterface& gui = gx_gui::GxMainInterface::get_instance();
    GtkAllocation alloc;
    gtk_widget_get_allocation (GTK_WIDGET(gui.RBox), &alloc);
    if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget)) == TRUE) {

        GtkWidget *plug = gtk_widget_get_parent(GTK_WIDGET(data));
        gtk_widget_show_all(GTK_WIDGET(plug));
        GtkWidget *vbox = gtk_widget_get_parent(GTK_WIDGET(plug));
        GtkWidget *box1 = gtk_widget_get_parent(GTK_WIDGET(vbox));
        vbox = gtk_widget_get_parent(GTK_WIDGET(box1));
        box1 = gtk_widget_get_parent(GTK_WIDGET(vbox));
        vbox = gtk_widget_get_parent(GTK_WIDGET(box1));
        box1 = gtk_widget_get_parent(GTK_WIDGET(vbox));

        // if order is horizontal, force resize the rack widget width
        if (strcmp(gtk_widget_get_name(GTK_WIDGET(box1)), "GtkViewport") == 0) {
            gtk_widget_hide(GTK_WIDGET(vbox));
            if (gui.fWindow.get_resizable())
                gui.fWindow.set_resizable(false);
            gtk_widget_show(GTK_WIDGET(vbox));
            if (GDK_IS_WINDOW (gui.RBox->window)) {
                gtk_widget_set_size_request(GTK_WIDGET(gui.RBox), -1, alloc.height);
            } else {
                gtk_widget_set_size_request(GTK_WIDGET(gui.RBox), -1, 460);
            }
            if (guivar.g_threads[7] == 0 || g_main_context_find_source_by_id
                                    (NULL, guivar.g_threads[7]) == NULL)
                guivar.g_threads[7] = g_timeout_add_full(
                    G_PRIORITY_HIGH_IDLE + 10, 40, gx_gui::gx_set_resizeable,
                    gpointer(gui.fWindow.gobj()), NULL);
            if (guivar.g_threads[6] == 0 || g_main_context_find_source_by_id
                                    (NULL, guivar.g_threads[6]) == NULL)
                guivar.g_threads[6] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 50,
                               gx_gui::gx_set_default, gpointer(gui.RBox), NULL);
        }
    } else {
        GtkWidget *plug = gtk_widget_get_parent(GTK_WIDGET(data));
        gtk_widget_hide(GTK_WIDGET(plug));
        GtkWidget *vbox = gtk_widget_get_parent(GTK_WIDGET(plug));
        GtkWidget *box1 = gtk_widget_get_parent(GTK_WIDGET(vbox));
        vbox = gtk_widget_get_parent(GTK_WIDGET(box1));
        box1 = gtk_widget_get_parent(GTK_WIDGET(vbox));
        vbox = gtk_widget_get_parent(GTK_WIDGET(box1));
        box1 = gtk_widget_get_parent(GTK_WIDGET(vbox));

        // if order is horizontal, force resize the rack widget width
        if (strcmp(gtk_widget_get_name(GTK_WIDGET(box1)), "GtkViewport") == 0) {
            gtk_widget_hide(GTK_WIDGET(vbox));
            if (gui.fWindow.get_resizable())
                gui.fWindow.set_resizable(false);
            gtk_widget_show(GTK_WIDGET(vbox));

            if (GDK_IS_WINDOW (gui.RBox->window)) {
                gtk_widget_set_size_request(GTK_WIDGET(gui.RBox), -1, alloc.height);
            } else {
                gtk_widget_set_size_request(GTK_WIDGET(gui.RBox), -1, 460);
            }    
            if (guivar.g_threads[7] == 0 || g_main_context_find_source_by_id
                                        (NULL, guivar.g_threads[7]) == NULL)
            guivar.g_threads[7] = g_timeout_add_full(
                G_PRIORITY_HIGH_IDLE + 10, 40, gx_gui::gx_set_resizeable,
                gpointer(gui.fWindow.gobj()), NULL);
            if (guivar.g_threads[6] == 0 || g_main_context_find_source_by_id
                                    (NULL, guivar.g_threads[6]) == NULL)
                guivar.g_threads[6] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 50,
                               gx_gui::gx_set_default, gpointer(gui.RBox), NULL);
        }
    }
}

// ----- show extendend settings slider
void gx_show_menu_settings(GtkWidget *widget, gpointer data) {
    // done by the button allready
}


// ----menu function gx_mono_rack
void GxMainInterface::on_rack_activate() {
    if (mainmenu.fShowRack.get_active()) {
        gtk_widget_show(gw.rack_widget);
        if (!mainmenu.fShowRRack.get_active()) {
            mainmenu.fShowRRack.set_active(true);
        }
    } else {
        gtk_widget_hide(gw.rack_widget);
    }
}

// ----menu function gx_rack
void GxMainInterface::on_rrack_activate() {

    if (mainmenu.fShowRRack.get_active()) {
        gtk_widget_set_size_request(GTK_WIDGET(RBox), -1, 460);
        gtk_widget_show(RBox);
        // fShowRack.set_active(true);
        // fShowSRack.set_active(true);
    } else {
        if (fWindow.get_resizable())
            fWindow.set_resizable(false);
        gtk_widget_hide(RBox);
        // fShowRack.set_active(false);
        // fShowSRack.set_active(false);
    }
    if (guivar.g_threads[7] == 0 || g_main_context_find_source_by_id(NULL, guivar.g_threads[7]) == NULL)
            guivar.g_threads[7] = g_timeout_add_full(
		G_PRIORITY_HIGH_IDLE + 10, 40, gx_set_resizeable,
		gpointer(fWindow.gobj()), NULL);
    if (guivar.g_threads[6] == 0 || g_main_context_find_source_by_id(NULL, guivar.g_threads[6]) == NULL)
            guivar.g_threads[6] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 50,
                           gx_set_default, gpointer(RBox), NULL);
}

// ----menu function gx_rack
void GxMainInterface::on_srack_activate() {
    if (fWindow.get_resizable())
        fWindow.set_resizable(false);
    if (mainmenu.fShowSRack.get_active()) {
        gtk_widget_show(gw.srack_widget);

        GtkWidget *parent = gtk_widget_get_parent(GTK_WIDGET(gw.srack_widget));
        GtkWidget *vbox = gtk_widget_get_parent(GTK_WIDGET(parent));
        vbox = gtk_widget_get_parent(GTK_WIDGET(vbox));
        // vbox = gtk_widget_get_parent(GTK_WIDGET(vbox));
        // if order is horizontal, force resize the rack widget width
        if (strcmp(gtk_widget_get_name(GTK_WIDGET(vbox)), "GtkViewport") == 0) {
            gtk_widget_hide(GTK_WIDGET(vbox));
            parent = gtk_widget_get_parent(GTK_WIDGET(vbox));
            if (strcmp(gtk_widget_get_name(GTK_WIDGET(parent)), "HorizontalStereoBox") == 0) {
                if (!gtk_widget_is_drawable(GTK_WIDGET(parent)))
                    gtk_widget_show(GTK_WIDGET(parent));
            }
            gtk_widget_show(GTK_WIDGET(vbox));
        }
        if (!mainmenu.fShowRRack.get_active()) {
            mainmenu.fShowRRack.set_active(true);
        }
    } else {
        gtk_widget_hide(gw.srack_widget);

        GtkWidget *parent = gtk_widget_get_parent(GTK_WIDGET(gw.srack_widget));
        GtkWidget *vbox = gtk_widget_get_parent(GTK_WIDGET(parent));
        vbox = gtk_widget_get_parent(GTK_WIDGET(vbox));
        // vbox = gtk_widget_get_parent(GTK_WIDGET(vbox));
        // if order is horizontal, force resize the rack widget size
        if (strcmp(gtk_widget_get_name(GTK_WIDGET(vbox)), "GtkViewport") == 0) {
            gtk_widget_hide(GTK_WIDGET(vbox));
            parent = gtk_widget_get_parent(GTK_WIDGET(vbox));
            if (strcmp(gtk_widget_get_name(GTK_WIDGET(parent)), "HorizontalStereoBox") == 0) {
                if (gtk_widget_is_drawable(GTK_WIDGET(parent)))
                    gtk_widget_hide(GTK_WIDGET(parent));
            }
            gtk_widget_show(GTK_WIDGET(vbox));
        }
    }

    gtk_widget_set_size_request(GTK_WIDGET(RBox), -1, 460 );
    if (guivar.g_threads[7] == 0 || g_main_context_find_source_by_id(NULL, guivar.g_threads[7]) == NULL)
            guivar.g_threads[7] = g_timeout_add_full(
		G_PRIORITY_HIGH_IDLE + 10, 40, gx_set_resizeable,
		gpointer(fWindow.gobj()), NULL);
    if (guivar.g_threads[6] == 0 || g_main_context_find_source_by_id(NULL, guivar.g_threads[6]) == NULL)
            guivar.g_threads[6] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 50,
                           gx_set_default, gpointer(RBox), NULL);
}

// ----menu function gx_toolbar
void GxMainInterface::on_toolbar_activate() {

    if (mainmenu.fShowToolBar.get_active()) {
        gtk_widget_show_all(gw.rack_tool_bar);
    } else {
        GtkAllocation my_size;
        gtk_widget_get_allocation(GTK_WIDGET(RBox), &my_size);
        gtk_widget_set_size_request(GTK_WIDGET(RBox), -1, my_size.height);
        if (fWindow.get_resizable())
            fWindow.set_resizable(false);
        gtk_widget_hide(gw.rack_tool_bar);
    }
    if (guivar.g_threads[7] == 0 || g_main_context_find_source_by_id(NULL, guivar.g_threads[7]) == NULL)
            guivar.g_threads[7] = g_timeout_add_full(
		G_PRIORITY_HIGH_IDLE + 10, 40, gx_set_resizeable,
		gpointer(fWindow.gobj()), NULL);
    if (guivar.g_threads[6] == 0 || g_main_context_find_source_by_id(NULL, guivar.g_threads[6]) == NULL)
            guivar.g_threads[6] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 50,
                           gx_set_default, gpointer(RBox), NULL);
}

// ----menu function gx_tuner
void GxMainInterface::on_tuner_activate() {
    bool tuner_on = mainmenu.fShowTuner.get_active();
    engine.tuner.used_for_display(tuner_on);
    engine.set_rack_changed();
    if (tuner_on) {
        gtk_widget_show_all(gw.tuner_widget);
        fTuner.show();
    } else {
        GtkAllocation my_size;
        gtk_widget_get_allocation(GTK_WIDGET(RBox), &my_size);
        gtk_widget_set_size_request(GTK_WIDGET(RBox), -1, my_size.height);
        if (fWindow.get_resizable())
            fWindow.set_resizable(false);
        fTuner.hide();
        gtk_widget_hide(gw.tuner_widget);
    }
    if (guivar.g_threads[7] == 0 || g_main_context_find_source_by_id(NULL, guivar.g_threads[7]) == NULL)
            guivar.g_threads[7] = g_timeout_add_full(
		G_PRIORITY_HIGH_IDLE + 10, 40, gx_set_resizeable,
		gpointer(fWindow.gobj()), NULL);
    if (guivar.g_threads[6] == 0 || g_main_context_find_source_by_id(NULL, guivar.g_threads[6]) == NULL)
            guivar.g_threads[6] = g_timeout_add_full(G_PRIORITY_HIGH_IDLE + 10, 50,
                           gx_set_default, gpointer(RBox), NULL);
}

// ---- menu function gx_midi_out
void gx_midi_out(Gtk::CheckMenuItem& menuitem) {
    GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(gw.midibox));
    GtkWidget *child = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    g_list_free(child_list);
    gx_show_extended_settings(GTK_WIDGET(menuitem.gobj()), (gpointer) child);
    static bool first = true;
    if (menuitem.get_active()) {
        if (first) {
	    guivar.refresh_size = 0;
	}
        //gx_engine::turnOnMidi();//FIXME
    } else {
        //gx_engine::turnOffMidi();//FIXME
        string group = "midi_out.on_off";
        gx_engine::parameter_map[group].set_std_value();
    }
    first =false;
    GxMainInterface::get_instance().engine.set_rack_changed();
}

// ----- hide the extendend settings slider
void GxMainInterface::gx_hide_extended_settings() {
    if (fWindow.get_window()->get_state()
        & (Gdk::WINDOW_STATE_ICONIFIED|Gdk::WINDOW_STATE_WITHDRAWN)) {
        gint mainxorg = gx_set_mx_oriantation();
        gint mainyorg = gx_set_my_oriantation();
        fWindow.move(mainxorg, mainyorg);
        fWindow.present();
    } else {
        fWindow.hide();
        // fWindow.iconify();
    }
}

// ----- systray menu
void GxMainInterface::gx_systray_menu(guint button, guint32 activate_time) {
    mainmenu.engine_menu.popup(2, gtk_get_current_event_time());
}

// ---- choice dialog without text entry
gint gx_nchoice_dialog_without_entry(
    const char* window_title,
    const char* msg,
    const guint nchoice,
    const char* label[],
    const gint  resp[],
    const gint default_response) {
    GxMainInterface& gui = GxMainInterface::get_instance();
    GtkWidget* dialog   = gtk_dialog_new();
    GtkWidget* text_label = gtk_label_new(msg);
    GtkWidget* image   = gtk_image_new_from_pixbuf(gui.gw_ib->gobj());

    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), text_label);

    GdkColor colorGreen;
    gdk_color_parse("#e1e1ed", &colorGreen);
    gtk_widget_modify_fg(text_label, GTK_STATE_NORMAL, &colorGreen);

    GdkColor colorBlack;
    gdk_color_parse("#10101e", &colorBlack);
    gtk_widget_modify_bg(dialog, GTK_STATE_NORMAL, &colorBlack);
    g_signal_connect(GTK_DIALOG(dialog)->vbox, "expose-event",
                     G_CALLBACK(gx_cairo::start_box_expose), NULL);
    gtk_widget_set_redraw_on_allocate(GTK_WIDGET(GTK_DIALOG(dialog)->vbox),true);
    GtkStyle* text_style = gtk_widget_get_style(text_label);
    pango_font_description_set_size(text_style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(text_style->font_desc, PANGO_WEIGHT_BOLD);

    gtk_widget_modify_font(text_label, text_style->font_desc);
    gtk_container_add(GTK_CONTAINER(gtk_dialog_get_action_area(GTK_DIALOG(dialog))), image);
    for (guint i = 0; i < nchoice; i++) {
        GtkWidget* button =
            gtk_dialog_add_button(GTK_DIALOG(dialog), label[i], resp[i]);

        gdk_color_parse("#555555", &colorBlack);
        gtk_widget_modify_bg(button, GTK_STATE_NORMAL, &colorBlack);

        g_signal_connect_swapped(button, "clicked",  G_CALLBACK(gtk_widget_destroy), dialog);
    }

    // set default
    gtk_dialog_set_has_separator(GTK_DIALOG(dialog), FALSE);
    gtk_dialog_set_default_response(GTK_DIALOG(dialog), default_response);
    gtk_window_set_title(GTK_WINDOW(dialog), window_title);

    gtk_widget_show(text_label);
    gtk_widget_show(image);
    // --- run dialog and check response
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    return response;
}

// ---- choice dialog without text entry
gint gx_choice_dialog_without_entry(
    const char* window_title,
    const char* msg,
    const char* label1,
    const char* label2,
    const gint resp1,
    const gint resp2,
    const gint default_response) {

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

// ---- get text entry from dialog
void gx_get_text_entry(GtkEntry* entry, Glib::ustring& output) {
    if (gtk_entry_get_text(entry)[0])
        output = gtk_entry_get_text(entry);
}

// ---- choice dialog with text entry
gint gx_choice_dialog_with_text_entry(
    const char* window_title,
    const char* msg,
    const char* label1,
    const char* label2,
    const gint resp1,
    const gint resp2,
    const gint default_response,
    GCallback func) {

    GtkWidget *dialog, *button1, *button2;
    dialog  = gtk_dialog_new();
    button1 = gtk_dialog_add_button(GTK_DIALOG(dialog), label1, resp1);
    button2 = gtk_dialog_add_button(GTK_DIALOG(dialog), label2, resp2);

    GtkWidget* text_label = gtk_label_new(msg);
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), text_label);


    GtkWidget* gtk_entry = gtk_entry_new_with_max_length(32);
    gtk_entry_set_text(GTK_ENTRY(gtk_entry), "");
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), gtk_entry);

    g_signal_connect_swapped(button1, "clicked",  G_CALLBACK(func), gtk_entry);
    g_signal_connect(GTK_DIALOG(dialog)->vbox, "expose-event",
                     G_CALLBACK(gx_cairo::rectangle_skin_color_expose), NULL);

    gtk_dialog_set_has_separator(GTK_DIALOG(dialog), TRUE);
    gtk_dialog_set_default_response(GTK_DIALOG(dialog), default_response);
    gtk_entry_set_activates_default(GTK_ENTRY(gtk_entry), TRUE);
    GTK_BOX(GTK_DIALOG(dialog)->action_area)->spacing = 4;

    // some display style
    GdkColor colorGreen;
    gdk_color_parse("#969292", &colorGreen);
    gtk_widget_modify_fg(text_label, GTK_STATE_NORMAL, &colorGreen);

    GdkColor colorBlack;
    gdk_color_parse("#000000", &colorBlack);
    gtk_widget_modify_bg(dialog, GTK_STATE_NORMAL, &colorBlack);

    GtkStyle* text_style = gtk_widget_get_style(text_label);
    pango_font_description_set_size(text_style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(text_style->font_desc, PANGO_WEIGHT_BOLD);

    gtk_widget_modify_font(text_label, text_style->font_desc);

    gdk_color_parse("#555555", &colorBlack);
    gtk_widget_modify_bg(button1, GTK_STATE_NORMAL, &colorBlack);

    gdk_color_parse("#555555", &colorBlack);
    gtk_widget_modify_bg(button2, GTK_STATE_NORMAL, &colorBlack);

    // display extra stuff
    gtk_widget_show(text_label);
    gtk_widget_show(gtk_entry);
    gtk_window_set_title(GTK_WINDOW(dialog), window_title);

    // run the dialog and wait for response
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));

    if (dialog) gtk_widget_destroy(dialog);

    return response;
}

// ---- retrive skin array index from skin name
void gx_actualize_skin_index(gx_system::SkinHandling& skin, const string& skin_name) {
    for (guint s = 0; s < skin.skin_list.size(); s++) {
        if (skin_name == skin.skin_list[s]) {
            gx_engine::audio.fskin = s;
            return;
        }
    }
}

// ----- skin change
void  gx_change_skin(Gtk::RadioMenuItem& item, int idx) {
    // no action needed on false
    if (!item.get_active()) {
        return;
    }
    // update the skin to the one picked by user
    (void)gx_update_skin(idx, "gx_change_skin");
}

// ----- cycling through skin
void  gx_cycle_through_skin(GtkWidget *widget, gpointer arg) {
    GxMainInterface& gui = GxMainInterface::get_instance();
    gint idx = gx_engine::audio.fskin + 1;
    idx %= gui.options.skin.skin_list.size();

    // did it work ? if yes, update current skin
    if (gx_update_skin(idx, "gx_cycle_through_skin"))
        gx_engine::audio.fskin = idx;

    // update menu item state
    gx_update_skin_menu_item(gx_engine::audio.fskin);
}

// ----- cycling through skin
void  gx_update_skin_menu_item(const int index) {
    // update menu item state
    GxMainInterface& gui = GxMainInterface::get_instance();
    GList*     list = gtk_container_get_children(GTK_CONTAINER(gui.mainmenu.skin_menu.gobj()));
    GtkWidget* item = reinterpret_cast<GtkWidget*>(g_list_nth_data(list, index));
    g_list_free(list);
    if (item) gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(item), TRUE);
}

// ---- skin changer, used internally frm callbacks
bool gx_update_skin(const gint idx, const char* calling_func) {
    GxMainInterface& gui = GxMainInterface::get_instance();
    // check skin validity
    if (idx < 0 || idx >= (gint)gui.options.skin.skin_list.size()) {
        gx_system::gx_print_warning(calling_func,
                _("skin index out of range, keeping actual skin"));
        return false;
    }

    string rcfile = gui.options.get_style_filepath(
	"gx_head_" + gui.options.skin.skin_list[idx] + ".rc");
    gtk_rc_parse(rcfile.c_str());
    gtk_rc_reset_styles(gtk_settings_get_default());

    gx_engine::audio.fskin = idx;

    return true;
}

// ---- popup warning
int gx_message_popup(const char* msg) {
    // check msg validity
    if (!msg) {
        gx_system::gx_print_warning("Message Popup",
                         string(_("warning message does not exist")));
        return -1;
    }

    // build popup window
    GtkWidget *about;
    GtkWidget *label;
    GtkWidget *ok_button;

    about = gtk_dialog_new();
    ok_button  = gtk_button_new_from_stock(GTK_STOCK_OK);

    label = gtk_label_new(msg);

    GtkStyle *style = gtk_widget_get_style(label);

    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);

    gtk_widget_modify_font(label, style->font_desc);

    gtk_label_set_selectable(GTK_LABEL(label), TRUE);

    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(about)->vbox), label);

    GTK_BOX(GTK_DIALOG(about)->action_area)->spacing = 3;
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(about)->action_area), ok_button);

    g_signal_connect_swapped(ok_button, "clicked",
                              G_CALLBACK(gtk_widget_destroy), about);

    g_signal_connect(GTK_DIALOG(about)->vbox, "expose-event", G_CALLBACK(gx_cairo::start_box_expose), NULL);
    gtk_widget_set_redraw_on_allocate(GTK_WIDGET(GTK_DIALOG(about)->vbox),true);
    gtk_widget_show(ok_button);
    gtk_widget_show(label);
    return gtk_dialog_run (GTK_DIALOG(about));
}

/* meter button release   */
bool GxMainInterface::on_meter_button_release(GdkEventButton* ev) {
    if (ev->button == 1) {
        for (unsigned int i = 0; i < sizeof(fLevelMeters)/sizeof(fLevelMeters[0]); i++) {
            fLevelMeters[i].clear();
        }
        return true;
    }
    return false;
}



/* ----- delete event ---- */
gboolean gx_delete_event(GtkWidget *widget, gpointer   data ) {
    gtk_range_set_value(GTK_RANGE(widget), 0);
    return TRUE;
}
} /* end of gx_gui namespace */


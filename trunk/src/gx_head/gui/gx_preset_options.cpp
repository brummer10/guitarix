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
 *    This is the gx_head GUI related functionality of preset handling
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
//#include <gxw/GxControlParameter.h>      // NOLINT

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


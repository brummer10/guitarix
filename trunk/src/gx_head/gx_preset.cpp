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
 * --------------------------------------------------------------------------
 */

/* --------------------------------------------------------------------------

   This is the gx_head preset handling functions

   ---------------------------------------------------------------------------*/

#include "guitarix.h"                  // NOLINT

#include <gdk/gdkkeysyms.h>            // NOLINT
#include <gtkmm/filechooserdialog.h>   // NOLINT
#include <glibmm/i18n.h>               // NOLINT

#include <fstream>                     // NOLINT
#include <string>                      // NOLINT
#include <vector>                      // NOLINT

using namespace gx_system;             // NOLINT

// #define _(x) (x)

namespace gx_preset {

GxPreset gxpreset;

gx_gui::FileParameter gx_preset_file("system.current_preset_file");
gx_gui::FileParameter gx_factory_preset_file("system.factory_preset_file");


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

// ----- create a empty preset file
static void gx_empty_preset_file(const char* filename) {
    ofstream nfile(filename);
    JsonWriter jw(nfile);
    jw.begin_array();
    writeHeader(jw);
    jw.end_array(true);
    jw.close();
    nfile.close();
}

// ----- modify (add/sub/change) a existing preset file
static bool gx_modify_preset(const char* presname, const char* newname = 0,
                      bool remove = false, bool rewrite = false) {
    string tmpfile = gx_preset_file.get_path() + "_tmp";
    ifstream ofile(gx_preset_file.get_path().c_str());
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
                    gx_print_info(_("loading presets"), _("rewriting convertet presets"));
                } else {
                    const char *s;
                    if (major != majorversion) {
                        s = _("major version mismatch in %1%: found %2%.%3%, expected %4%.%5%");
                    } else {
                        assert(minor != minorversion);
                        s = _("minor version mismatch in %1%: found %2%.%3%, expected %4%.%5%");
                    }
                    gx_print_warning(
                        _("recall settings"),
                        (boost::format(s) % gx_preset_file.get_parse_name()
                               % major % minor % majorversion % minorversion).str());
                }
            }
        }
        writeHeader(jw);

        while (jp.peek() != JsonParser::end_array) {
            jp.next(JsonParser::value_string);
            if (rewrite) {
                jw.write(jp.current_value());
                gx_gui::parameter_map.set_init_values();
                bool has_midi;
                read_preset(jp, &has_midi, major, minor);
                write_preset(jw, false, has_midi);
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
            gx_print_error(_("save preset"), _("couldn't write ") + tmpfile);
            return false;
        }

        int rc = rename(tmpfile.c_str(), gx_preset_file.get_path().c_str());
        if (rc != 0) {
            gx_print_error(_("save preset"), _("couldn't rename ")
                           + tmpfile + " to " + gx_preset_file.get_parse_name());
            return false;
        }
    } catch(gx_system::JsonException& e) {
        gx_print_error(_("save/modify preset"), _("invalid preset file: ")
                       + gx_preset_file.get_parse_name());
    }
    return found;
}

// ---- parsing preset file to build up a string vector of preset names
static bool gx_build_preset_list() {
    // initialize list
    gxpreset.plist.clear();
    // initialize menu pointer list
    for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; i++)
        gxpreset.pm_list[i].clear();

    // parse it if any
    ifstream f(gx_preset_file.get_path().c_str());
    if (f.good()) {
        try {
            JsonParser jp(f);
            jp.next(JsonParser::begin_array);
            int samevers = readHeader(jp);
            while (jp.peek() == JsonParser::value_string) {
                jp.next();
                gxpreset.plist.push_back(jp.current_value());
                jp.skip_object();
            }
            jp.next(JsonParser::end_array);
            jp.next(JsonParser::end_token);
            f.close();
            // ---- how many did we get ?
            gx_print_info(_("Preset List Building"),
                          gx_i2a(gxpreset.plist.size()) + string(_(" presets found")));
            if (!samevers && gx_preset_file.is_standard()) {
                gx_modify_preset(0 , 0, false, true);
                gx_system::recallState(sysvar.gx_user_dir + gx_jack::gxjack.client_instance + "_rc"); // FIXME
            }
            return true;
        } catch(gx_system::JsonException& e) {
            gx_system::gx_print_warning(gx_preset_file.get_parse_name().c_str(), _("parse error"));
            return false;
        }
    }
    if (gx_preset_file.is_standard()) {
        gx_print_info(_("empty preset File "), gx_preset_file.get_display_name());
        gx_empty_preset_file(gx_preset_file.get_path().c_str());
        return true;
    } else {
        string msg = (boost::format(_("preset File %1% doesn't exist"))
                      % gx_preset_file.get_parse_name()).str();
        gx_print_error(_("Load preset file"), msg);
        gx_gui::gx_message_popup(msg.c_str());
        return false;
    }
}

// ----------- add new preset to menus
void GxPreset::gx_add_preset_to_menus(const string& presname) {
    static GCallback preset_action_func[] = {
        G_CALLBACK(gxpreset.gx_load_preset),
        G_CALLBACK(gxpreset.gx_save_oldpreset),
        G_CALLBACK(gxpreset.gx_rename_preset_dialog),
        G_CALLBACK(gxpreset.gx_delete_preset_dialog)
    };
    for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; i++)
        gx_add_single_preset_menu_item(presname, i, preset_action_func[i]);
}

// ---- add a single preset to a given preset menu
void GxPreset::gx_add_single_preset_menu_item(const string& presname,
                                    const gint lindex,
                                    GCallback func) {
    // menu
    GtkWidget* menu = presmenu[lindex];

    // index for keyboard shortcut (can take any list)
    vector<GtkMenuItem*>::iterator its;
    int pos = 0;
    for (its = pm_list[lindex].begin(); its != pm_list[lindex].end(); its++) {
        pos++;
    }
    pos += 1;

    // add small mnemonic
    string name("_");
    if (pos > 9) name = "";
    name += gx_i2a(pos) + "  ";
    name += presname;

    // GDK numbers
    guint accel_key = GDK_1  + pos - 1;

    // create item
    GtkWidget* menuitem = gtk_menu_item_new_with_mnemonic(name.c_str());
    g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(func),
                      NULL);

    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuitem);

    // get accel_path for menuitem
    string acc_path = gx_get_accel_path(lindex);
    acc_path += gx_i2a(accel_key);

    static GdkModifierType list_mod[] = {
        GDK_NO_MOD_MASK,
        GDK_CONTROL_MASK,
        GDK_MOD1_MASK,
        GdkModifierType(GDK_CONTROL_MASK|GDK_MOD1_MASK)
    };

    if (pos < 10) {
        if (!gtk_accel_map_lookup_entry(acc_path.c_str(), NULL))
            gtk_accel_map_add_entry(acc_path.c_str(), accel_key, list_mod[lindex]);

        gtk_widget_set_accel_path(menuitem, acc_path.c_str(),
                                  gx_gui::GxMainInterface::instance()->fAccelGroup);
    }

    its = pm_list[lindex].end();
    // add a pointer to the menuitem to the preset menu list
    pm_list[lindex].insert(its, GTK_MENU_ITEM(menuitem));
    gtk_widget_show(menuitem);
}


// ----- get the preset number by name from preset list
static int gx_get_single_preset_menu_pos(const string& presname, const gint lindex) {
    vector<string>::iterator its;
    int pos = 0;
    for (its = gxpreset.plist.begin(); its != gxpreset.plist.end(); its++) {
        pos++;
        if (presname == *its)
            return pos;
    }
    return 0;
}

// ----- get pointer to the menuitem
GtkMenuItem* const GxPreset::gx_get_preset_item_from_name(int lindex, const string& name) {
    vector<string>::iterator its;
    vector<GtkMenuItem*>::iterator it = pm_list[lindex].begin();
    int pos = 0;
    for (its = plist.begin(); its != plist.end(); its++) {
        pos++;
        if (name == *its)
            return *it;
        it++;
    }
    return NULL;
}

// ----------- update preset numbering in menus
void GxPreset::gx_refresh_preset_menus() {
    for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; i++) {
        vector<GtkMenuItem*>::iterator it = pm_list[i].begin();
        for (it = pm_list[i].begin(); it != pm_list[i].end(); it++) {
            gtk_widget_destroy(GTK_WIDGET(*it));
        }
    }

    if (!gx_build_preset_list()) {
        gx_print_warning(_("Load preset file"), _("selecting default preset bank"));
        gx_preset_file.set_std_value();
        gx_build_preset_list();
    }
    vector<string>::iterator its;
    for (its = plist.begin() ; its != plist.end(); its++) {
        gx_add_preset_to_menus(*its);
    }
}

// ---------- load nth preset (return true if successful)
bool GxPreset::gx_nth_preset(unsigned char n) {
    // check that we do have presets
    if (!pm_list[LOAD_PRESET_LIST].size()) {
        gx_print_warning(_("Preset Switching"),
                         _("Preset list is empty, make some :)"));
        return false;
    }
    vector<GtkMenuItem*>::iterator it = pm_list[LOAD_PRESET_LIST].begin();
    while (n > 0) {
        it++;
        if (it == pm_list[LOAD_PRESET_LIST].end())
            return false;
        n--;
    }

    // load the preset
    gx_load_preset(*it, NULL);
    return true;
}

// ---------- switch to next preset in queue
void GxPreset::gx_next_preset(GtkWidget* item, gpointer arg) {
    // check that we do have presets
    if (!gxpreset.pm_list[LOAD_PRESET_LIST].size()) {
        gx_print_warning(_("Preset Switching"),
                         _("Preset list is empty, make some :)"));
        return;
    }

    // start from this element
    vector<GtkMenuItem*>::iterator it = gxpreset.pm_list[LOAD_PRESET_LIST].begin();
    if (gxpreset.setting_is_preset) {
        GtkMenuItem* const itemi =
            gxpreset.gx_get_preset_item_from_name(LOAD_PRESET_LIST, gxpreset.gx_current_preset);
        for (it = gxpreset.pm_list[LOAD_PRESET_LIST].begin();
             it != gxpreset.pm_list[LOAD_PRESET_LIST].end();it++ ) {
            if (itemi == *it)
                break;
        }
        it++;
    }
    // check if we are on edge
    if (it == gxpreset.pm_list[LOAD_PRESET_LIST].end())
        it = gxpreset.pm_list[LOAD_PRESET_LIST].begin();

    // load the preset
    gx_load_preset(*it, NULL);
}

// ---------- switch to next preset in queue
void GxPreset::gx_previous_preset(GtkWidget* item, gpointer arg) {
    // check that we do have presets
    if (!gxpreset.pm_list[LOAD_PRESET_LIST].size()) {
        gx_print_warning(_("Preset Switching"),
                         _("Preset list is empty, make some :)"));
        return;
    }

    // start from this element
    vector<GtkMenuItem*>::iterator it = gxpreset.pm_list[LOAD_PRESET_LIST].end();
    if (gxpreset.setting_is_preset) {
        GtkMenuItem* const itemi =
            gxpreset.gx_get_preset_item_from_name(LOAD_PRESET_LIST, gxpreset.gx_current_preset);
        for (it = gxpreset.pm_list[LOAD_PRESET_LIST].begin();
             it != gxpreset.pm_list[LOAD_PRESET_LIST].end(); it++) {
            if (itemi == *it)
                break;
        }
    }

    // check if we are on edge
    if (it == gxpreset.pm_list[LOAD_PRESET_LIST].begin())
        it = gxpreset.pm_list[LOAD_PRESET_LIST].end();

    // decrement iterator and load preset
    it--;

    // load the preset
    gxpreset.gx_load_preset(*it, NULL);
}

// ----------
void GxPreset::gx_delete_active_preset_dialog(GtkWidget* item, gpointer arg) {
    if (!gxpreset.setting_is_preset || gxpreset.gx_current_preset.empty()) {
        gx_print_warning(_("Deleting Active Preset"),
                         _("No active preset, this is the main setting"));
        return;
    }

    // tmp store
    string presname = gxpreset.gx_current_preset;

    // call dialog
    gxpreset.gx_delete_preset_dialog(NULL, NULL);

    if (gxpreset.gx_current_preset.empty() && !gxpreset.setting_is_preset)
        gx_print_info(_("Deleting Active Preset"),
                      string(_("Deleted preset ")) + presname +
                      string(_(", recalled main setting")));
}


// ----preset deletion dialog
void GxPreset::gx_delete_preset_dialog(GtkMenuItem *menuitem, gpointer arg) {
    string presname = gxpreset.gx_current_preset;

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
        gx_print_warning(_("Preset Deleting"),
                         string(_(" Deletion of preset ")) + presname +
                         string(_(" has been cancelled")));
        return;
    }

    // we want to delete the bugger!
    gxpreset.gx_delete_preset(menuitem, arg);
}

// ----delete all presets dialog
void GxPreset::gx_delete_all_presets_dialog(GtkMenuItem *menuitem, gpointer arg) {
    // --- if no presets, then just pop up some info
    if (gxpreset.pm_list[LOAD_PRESET_LIST].empty()) {
        gx_print_warning(_("Delete All Presets Dialog"),
                         string(_("There is no presets to delete")));
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
        gx_print_warning(_("Delete All Presets Dialog"),
                         _("All Presets deletion has been cancelled"));
        return;
    }
    // we want to delete all the buggers!
    gxpreset.gx_delete_all_presets();
}

// ----delete all presets
void GxPreset::gx_delete_all_presets() {
    // this function will simply delete the preset file,
    // clear the preset list and refresh the menus

    // write empty preset file
    ofstream f(gx_preset_file.get_path().c_str());
    JsonWriter jw(f);
    jw.begin_array();
    writeHeader(jw);
    jw.end_array(true);
    jw.close();
    f.close();

    // clear list
    gx_refresh_preset_menus();
    gx_print_info(_("All Presets Deleting"), string(_("deleted ALL presets!")));
}

static bool gx_load_preset_from_file(const char* presname) {
    ifstream ofile(gx_preset_file.get_path().c_str());
    JsonParser jp(ofile);

    try {
        jp.next(JsonParser::begin_array);
        int major, minor;
        readHeader(jp, &major, &minor);

       // bool found = false;
        while (jp.peek() != JsonParser::end_array) {
            jp.next(JsonParser::value_string);
            if (jp.current_value() == presname) {
               // found = true;
                read_preset(jp, 0, major, minor);
                return true;
            } else {
                jp.skip_object();
            }
        }
        jp.next(JsonParser::end_array);
        jp.next(JsonParser::end_token);
    } catch(JsonException& e) {
        gx_print_error(_("load preset"), _("invalid preset file: ")
                       + gx_preset_file.get_parse_name());
    }
    return false;
}

// ----preset deletion
void GxPreset::gx_delete_preset(GtkMenuItem* item, gpointer arg) {

    // delete it via interface
    const string presname = gxpreset.gx_current_preset;

    (void)gx_modify_preset(presname.c_str(), NULL, true);

    // update menu
    gxpreset.gx_refresh_preset_menus();

    // recalling main setting
    gxpreset.gx_recall_settings_file(); // FIXME (wrong when loaded with -f ?)

    gx_print_warning(_("Preset Deleting"),
                     string(_("Deleted preset ")) +
                     presname + string(_(", recalled main setting")));
}

// ----------
void GxPreset::gx_rename_active_preset_dialog(GtkWidget* item, gpointer arg) {
    if (!gxpreset.setting_is_preset || gxpreset.gx_current_preset.empty()) {
        gx_print_warning(_("Renaming Active Preset"),
                         _("This is the main setting, "
                           "load a preset first"));
        return;
    }

    string presname = gxpreset.gx_current_preset;

    // get current preset menu item
    GtkMenuItem* const rnm_item =
        gxpreset.gx_get_preset_item_from_name(RENAME_PRESET_LIST, presname);

    // call delete dialog
    if (rnm_item)
        gxpreset.gx_rename_preset_dialog(rnm_item, NULL);

    if (presname == gxpreset.gx_current_preset) {
        gx_print_warning(_("Renaming Active Preset"),
                         _("The preset name is unchanged"));
        return;
    }

    if (!gxpreset.gx_current_preset.empty() && gxpreset.setting_is_preset)
        gx_print_info(_("Renaming Active Preset"),
                      string(_("Renamed preset ")) + presname +
                      string(_(" to ")) + gxpreset.gx_current_preset);
}

static gboolean gx_convolver_restart(gpointer data) {
    gx_engine::conv.stop();
    while (gx_engine::conv.is_runnable()) gx_engine::conv.checkstate();
    gx_jconv::GxJConvSettings* jcset = gx_jconv::GxJConvSettings::instance();
    bool rc = gx_engine::conv.configure(
                  gx_jack::gxjack.jack_bs, gx_jack::gxjack.jack_sr, jcset->getFullIRPath(),
                  jcset->getGain(), jcset->getGain(), jcset->getDelay(), jcset->getDelay(),
                  jcset->getOffset(), jcset->getLength(), 0, 0, jcset->getGainline());
    if (!rc || !gx_engine::conv.start()) {
        gx_jconv::GxJConvSettings::checkbutton7 = 0;
    }
    return false;
}

static gboolean gx_rename_main_widget(gpointer data) {
    // refresh main window name
    string title = string("gx_head ");
    if (gxpreset.setting_is_factory) {
        title += gxpreset.gx_factory_preset;
    } else {
        title += gxpreset.gx_current_preset;
    }
    gtk_window_set_title(GTK_WINDOW(gx_gui::gw.fWindow), title.c_str());
    // reload convolver settings widget
    // gx_jconv::gx_reload_jcgui();
    return false;
}

// ----menu funktion load
void GxPreset::gx_load_preset(GtkMenuItem *menuitem, gpointer load_preset) {
    // check that we do have presets
    if (!gxpreset.pm_list[LOAD_PRESET_LIST].size()) {
        gx_print_warning(_("Preset Loading"),
                         _("Preset list is empty, make some :)"));
        return;
    }

    // retrieve preset name
    vector<GtkMenuItem*>::iterator it = gxpreset.pm_list[LOAD_PRESET_LIST].begin();
    vector<string>::iterator its = gxpreset.plist.begin();
    for (it = gxpreset.pm_list[LOAD_PRESET_LIST].begin(); it != gxpreset.pm_list[LOAD_PRESET_LIST].end(); it++) {
        if (menuitem == *it)
            break;
        its++;
    }

    string preset_name = *its;

    // recall preset by name
    // Note: the UI does not know anything about gx_head's directory stuff
    // Need to pass it on
    bool preset_ok = gx_load_preset_from_file(preset_name.c_str());

    // check audio.result
    if (!preset_ok) {
        gx_print_error(_("Preset Loading"), string(_("Could not load preset ")) + preset_name);
        return;
    }

    // print out info
    gx_print_info(_("Preset Loading"), string(_("loaded preset ")) + preset_name);
    gxpreset.setting_is_preset = true;
    gx_engine::audio.preset_load = 12000/gx_jack::gxjack.jack_bs;
    gxpreset.setting_is_factory = false;

    gxpreset.gx_current_preset = preset_name;

    gx_jconv::gx_reload_jcgui();

    /* do some GUI stuff*/
    g_idle_add(gx_rename_main_widget, NULL);

    /* reset convolver buffer for preset change*/
    if (gx_engine::conv.is_runnable() && gx_jconv::GxJConvSettings::checkbutton7 == 1)  {
        gx_engine::conv.stop();
        gx_gui::guivar.g_threads[8] = g_idle_add_full(G_PRIORITY_HIGH_IDLE+20,
                                               gx_convolver_restart, NULL, NULL);
    }

    /* collect info for stage info display*/
    gx_gui::guivar.show_patch_info = gx_get_single_preset_menu_pos(gxpreset.gx_current_preset, 0);
}

// ---- funktion save
void GxPreset::gx_save_preset(const char* presname, bool expand_menu) {
    bool found = gx_modify_preset(presname);

    // update preset menus if needed
    if (expand_menu == found) {
        assert(false);
    }
    if (expand_menu)
        gx_add_preset_to_menus(string(presname));

    gx_refresh_preset_menus();

    // refresh display
    string ttle = string("gx_head ") + presname;
    gtk_window_set_title(GTK_WINDOW(gx_gui::gw.fWindow), (gchar*)ttle.c_str());  // NOLINT

    // we are now in a preset setting
    setting_is_preset = true;
    setting_is_factory = false;
    gx_current_preset = presname;

    gx_print_info(_("Preset Saving"), string(_("saved preset ")) + string(presname));
    gx_jconv::gx_reload_jcgui(); // FIXME why reload after saving?
}

///------factory presets--------///
// set factory preset file and path
static void  gx_set_factory_file(int i) {
    switch (i) {
    case 0:
        gx_factory_preset_file.set_path(gx_system::sysvar.gx_style_dir +"funkmuscle_rc");
        break;
    case 1:
        gx_factory_preset_file.set_path(gx_system::sysvar.gx_style_dir +"zettberlin_rc");
        break;
    case 2:
        gx_factory_preset_file.set_path(gx_system::sysvar.gx_style_dir +"dlp_ae_rc");
        break;
    case 3:
        gx_factory_preset_file.set_path(gx_system::sysvar.gx_style_dir +"autoandimat_rc");
        break;
    }
}

static bool gx_load_preset_from_factory(const char* presname, int i) {
    gx_set_factory_file(i);
    ifstream ofile(gx_factory_preset_file.get_path().c_str());

    JsonParser jp(ofile);

    try {
        jp.next(JsonParser::begin_array);
        int major, minor;
        readHeader(jp, &major, &minor);

       // bool found = false;
        while (jp.peek() != JsonParser::end_array) {
            jp.next(JsonParser::value_string);
            if (jp.current_value() == presname) {
               // found = true;
                read_preset(jp, 0, major, minor);
                return true;
            } else {
                jp.skip_object();
            }
        }
        jp.next(JsonParser::end_array);
        jp.next(JsonParser::end_token);
    } catch(JsonException& e) {
        // gx_print_error(_("load preset"), _("invalid factory file: ")
        // + factory_file.get_parse_name());
    }

    return false;
}

// ----menu funktion load preset from factory
static void gx_load_factory_preset(GtkMenuItem *menuitem, gpointer load_preset) {
    // retrieve preset name
    int i = GPOINTER_TO_INT(load_preset);
    vector<GtkMenuItem*>::iterator it = gxpreset.fpm_list[i].begin();
    vector<string>::iterator its = gxpreset.fplist[i].begin();
    for (it = gxpreset.fpm_list[i].begin(); it != gxpreset.fpm_list[i].end(); it++) {
        if (menuitem == *it)
            break;
        its++;
    }

    string preset_name = *its;
    // recall preset by name
    // Note: the UI does not know anything about gx_head's directory stuff
    // Need to pass it on
    bool preset_ok = gx_load_preset_from_factory(preset_name.c_str(), i);

    // check audio.result
    if (!preset_ok) {
        gx_print_error(_("Preset Loading"), string(_("Could not load preset ")) + preset_name);
        return;
    }

    // print out info
    gx_print_info(_("Preset Loading"), string(_("loaded preset ")) + preset_name);

    gxpreset.gx_factory_preset = preset_name;
    gx_engine::audio.preset_load = 12000/gx_jack::gxjack.jack_bs;
    gxpreset.setting_is_factory = true;
    gx_jconv::gx_reload_jcgui();

    /* do some GUI stuff*/
    g_idle_add(gx_rename_main_widget, NULL);

    /* reset convolver buffer for preset change*/
    if (gx_engine::conv.is_runnable() && gx_jconv::GxJConvSettings::checkbutton7 == 1) {
        gx_engine::conv.stop();
        gx_gui::guivar.g_threads[8] = g_idle_add_full(G_PRIORITY_HIGH_IDLE+20,
                                               gx_convolver_restart, NULL, NULL);
    }
}

// load the factory preset file
void GxPreset::gx_load_factory_file(int i) {
    // initialize list
    fplist[i].clear();
    // initialize menu pointer list
    fpm_list[i].clear();

    gx_set_factory_file(i);
    ifstream f(gx_factory_preset_file.get_path().c_str());

    if (f.good()) {
        JsonParser jp(f);
        jp.next(JsonParser::begin_array);
        readHeader(jp);
        while (jp.peek() == JsonParser::value_string) {
            jp.next();
            fplist[i].push_back(jp.current_value());
            jp.skip_object();
        }
        jp.next(JsonParser::end_array);
        jp.next(JsonParser::end_token);
        f.close();
    }

    vector<string>::iterator it;
    for (it = fplist[i].begin() ; it != fplist[i].end(); it++) {
        // menu
        GtkWidget* menu = ffpresmenu[i];
        vector<GtkMenuItem*>::iterator its;
        // create item
        string presna = *it;
        GtkWidget* menuitem = gtk_menu_item_new_with_mnemonic(presna.c_str());
        g_signal_connect(GTK_OBJECT(menuitem), "activate",
                         G_CALLBACK(gx_load_factory_preset), // FIXME LOAD FACTORY SETTINGS
                         GINT_TO_POINTER(i));

        gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuitem);
        its = fpm_list[i].end();
        // add a pointer to the menuitem to the preset menu list
        fpm_list[i].insert(its, GTK_MENU_ITEM(menuitem));
        gtk_widget_show(menuitem);
    }
}

///------ user preset handling------///
// load a preset file
void GxPreset::gx_recall_settings_file(const string *filename) {
    if (!filename) {
        string fname = sysvar.gx_user_dir + gx_jack::gxjack.client_instance + "_rc";
        gx_system::recallState(fname);
        gx_jconv::gx_reload_jcgui();
        gx_print_info(
            _("Main Setting recalling"),
            (boost::format(_("Called back main setting %1%")) % fname).str());
    } else {
        gx_system::recallState(*filename);
        gx_print_info(
            _("loading Settings file"),
            (boost::format(_("loaded settings file %1%")) % *filename).str());
    }
    gtk_window_set_title(GTK_WINDOW(gx_gui::gw.fWindow), gx_jack::gxjack.client_instance.c_str());
    setting_is_preset = false;
    setting_is_factory = false;
    gx_current_preset = "";
    gx_gui::guivar.show_patch_info = 0;
    gx_refresh_preset_menus();
}

// ----- select a external preset file
void GxPreset::gx_load_preset_file(const char* presname, bool expand_menu) {
    Gtk::FileChooserDialog file_chooser(
        *Glib::wrap(GTK_WINDOW(gx_gui::gw.fWindow)),
        _("Select a preset *_rc file"),
        Gtk::FILE_CHOOSER_ACTION_OPEN);
    file_chooser.add_button(GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL);
    file_chooser.add_button(GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT);
    file_chooser.set_filename(gx_preset_file.get_path());
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
    if (file_chooser.run() == Gtk::RESPONSE_ACCEPT) {
        gx_preset_file.set_path(file_chooser.get_filename());
        gxpreset.setting_is_preset = false;
        gxpreset.setting_is_factory = false;
        gxpreset.gx_current_preset = "";
        gx_gui::guivar.show_patch_info = 0;
        gxpreset.gx_refresh_preset_menus();
    }
}

// ----- export preset file
void GxPreset::gx_save_preset_file(const char* presname, bool expand_menu) {
    Gtk::FileChooserDialog file_chooser(
        *Glib::wrap(GTK_WINDOW(gx_gui::gw.fWindow)),
        _("Save a preset *_rc File"),
        Gtk::FILE_CHOOSER_ACTION_SAVE);
    file_chooser.add_button(GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL);
    file_chooser.add_button(GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT);
    file_chooser.set_do_overwrite_confirmation(true);
    file_chooser.set_show_hidden(true);
    Gtk::FileFilter filter;
    filter.add_pattern("*_rc");
    file_chooser.set_filter(filter);
    file_chooser.set_current_folder(gx_preset_file.get_directory_path());
    file_chooser.set_current_name("Untitled_rc");
    if (file_chooser.run() == Gtk::RESPONSE_ACCEPT) {
        string save_file = file_chooser.get_filename();
        int n = save_file.length() - 3;
        if (!(n >= 0 && save_file.substr(n) == "_rc")) { // FIXME: use a real extension
            save_file += "_rc";
        }
        try {
            gx_preset_file.copy(save_file);
        } catch(const Glib::Exception& ex) {
            gx_print_error(_("Export preset"), ex.what());
        }
    }
}

// ----menu funktion save
void GxPreset::gx_save_oldpreset(GtkMenuItem *menuitem, gpointer arg) {
    guint save_active = GPOINTER_TO_UINT(arg);
    string presname;
    vector<string>::iterator its = gxpreset.plist.begin();

    // are saving an active preset
    if (save_active) {
        if (gxpreset.gx_current_preset.empty()) {
            gx_print_warning(_("Saving Active Preset"),
                             _("We are in main setting, load a preset first"));
            return;
        }
        presname = gxpreset.gx_current_preset;

    } else {    // we are saving another preset from the menu

        vector<GtkMenuItem*>::iterator it;

        for (it = gxpreset.pm_list[SAVE_PRESET_LIST].begin();
             it != gxpreset.pm_list[SAVE_PRESET_LIST].end(); it++) {
            if (menuitem == *it) {
                break;
            }
            its++;
        }
        presname = *its;
    }
    gxpreset.gx_save_preset(presname.c_str(), false);
}

// ----clean up preset name given by user
void GxPreset::gx_cleanup_preset_name(string& presname) {
    gx_nospace_in_name(presname, "-");
}

// ----menu funktion save
void GxPreset::gx_save_newpreset(GtkEntry* entry) {
    string presname;
    gx_gui::gx_get_text_entry(entry, presname);

    // no text ?
    if (presname.empty()) {
        gx_print_error(_("Saving new preset"), _("no preset name given"));
        return;
    }

    // replace spaces by -
    gxpreset.gx_cleanup_preset_name(presname);

    // is the name alrady taken ?
    vector<string>::iterator its;
    vector<GtkMenuItem*>::iterator it = gxpreset.pm_list[SAVE_PRESET_LIST].begin();

    for (its = gxpreset.plist.begin(); its != gxpreset.plist.end(); its++) {
        // found a match
        if (presname == *its) {
            gx_print_error(_("New Preset Saving"),
                           string(_("preset name ")) +
                           presname +
                           string(_(" already in use, choose another one")));
            gxpreset.gx_save_newpreset_dialog(*it, NULL);
            return;
        }
        it++;
    }

    // finally save to preset file
    gxpreset.gx_save_preset(presname.c_str(), true);
    gx_jconv::gx_reload_jcgui();
}

// read name for preset
void GxPreset::gx_recall_main_setting(GtkMenuItem* item, gpointer) {
    gxpreset.gx_recall_settings_file(); // FIXME (wrong when loaded with -f ?)
}

// ----- save current setting as main setting
void GxPreset::gx_save_main_setting(GtkMenuItem* item, gpointer arg) {
    if (!saveStateToFile(sysvar.gx_user_dir + gx_jack::gxjack.client_instance + "_rc")) {
        gx_print_error(_("Main Setting"), _("can't save main setting"));
    } else if (gxpreset.setting_is_preset) {
        gx_print_info(_("Main Setting"),
                      _("Saved current preset into main setting"));
    } else {
        gx_print_info(_("Main Setting"), _("Saved main setting"));
    }
    gtk_window_set_title(GTK_WINDOW(gx_gui::gw.fWindow), gx_jack::gxjack.client_instance.c_str());
    gxpreset.setting_is_preset = false;
    gxpreset.setting_is_factory = false;
    gx_jconv::gx_reload_jcgui();
}

// ----menu function save new preset
void GxPreset::gx_save_newpreset_dialog(GtkMenuItem *menuitem, gpointer save_preset) {
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
        gx_print_warning(_("Saving New Preset Dialog"),
                         _(" Preset saving has been cancelled"));
        return;
    }
}


// ----preset renaming
void GxPreset::gx_rename_preset(GtkEntry* entry) {
    // rename preset
    string newname;
    gx_gui::gx_get_text_entry(entry, newname);

    if (newname.empty()) {
        gx_print_error(_("Preset Renaming"), _("no preset name given"));
        gxpreset.old_preset_name = "";
        return;
    }

    // replace spaces by -
    gxpreset.gx_cleanup_preset_name(newname);

    // get the UI to manipulate the preset file
    if (!gx_modify_preset(gxpreset.old_preset_name.c_str(), newname.c_str()))    {
        gx_print_error(_("Preset Renaming"),
                       string(_("Could not rename preset ")) + gxpreset.old_preset_name);
        gxpreset.old_preset_name = "";
        return;
    }

    // if jconv file
    string jc_preset   = sysvar.gx_user_dir + string("jconv_") + gxpreset.old_preset_name + ".conf ";
    string jc_file     = sysvar.gx_user_dir + string("jconv_") + newname + ".conf ";
    string file_move   = jc_preset + jc_file;
    (void)gx_system_call("mv", file_move.c_str(), true);

    // refresh the menus
    gxpreset.gx_refresh_preset_menus();

    if (gxpreset.setting_is_preset) {
        string jname = "gx_head ";
        string title = jname + newname;
        gtk_window_set_title(GTK_WINDOW(gx_gui::gw.fWindow), title.c_str());

        gxpreset.gx_current_preset = newname;
    }
    gx_jconv::gx_reload_jcgui();
}

// ----preset renaming dialog
void GxPreset::gx_rename_preset_dialog(GtkMenuItem *menuitem, gpointer arg) {
    vector<string>::iterator its = gxpreset.plist.begin();
    vector<GtkMenuItem*>::iterator it = gxpreset.pm_list[RENAME_PRESET_LIST].begin();
    for (it = gxpreset.pm_list[RENAME_PRESET_LIST].begin(); it != gxpreset.pm_list[RENAME_PRESET_LIST].end(); it++) {
        if ( menuitem == *it)
            break;
        its++;
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
        gx_print_warning(_("Rename Preset Dialog"),
                         _(" Preset renaming has been cancelled"));
        gxpreset.old_preset_name = "";
        return;
    }
}

void GxPreset::init() {
    gx_preset_file.set_standard(gx_system::sysvar.gx_user_dir + "gx_headpre_rc");
    // gx_factory_preset_file.set_standard(gx_system::sysvar.gx_style_dir +"funkmuscle_rc");

    gx_gui::parameter_map.insert(&gx_preset_file);
    // gx_gui::parameter_map.insert(&gx_factory_preset_file);
    setting_is_preset = false;
    setting_is_factory = false;
}
/* ----------------------------------------------------------------*/
} /* end of gx_preset namespace */

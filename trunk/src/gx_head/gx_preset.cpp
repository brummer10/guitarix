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

namespace gx_preset {

/****************************************************************
 ** class PresetIO
 */

PresetIO::PresetIO(gx_gui::MidiControllerList& mctrl_, gx_engine::ConvolverAdapter& cvr_)
    : gx_system::AbstractPresetIO(),
      mctrl(mctrl_),
      convolver(cvr_),
      plist(),
      m(0),
      jcset() {
}

PresetIO::~PresetIO() {
    clear();
}

void PresetIO::clear() {
    plist.clear();
    delete m;
    m = 0;
}

bool PresetIO::midi_in_preset() {
    return gx_gui::parameter_map["system.midi_in_preset"].getSwitch().get();
}

void PresetIO::read_preset(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader& head) {
    clear();
    read_intern(jp, 0, head);
}

void PresetIO::fixup_parameters(const gx_system::SettingsFileHeader& head) {
    assert(gx_gui::parameter_map.hasId("jconv.wet_dry"));
    if (head.is_current()) {
        return;
    }
    if (head.get_major() == 1 && head.get_minor() < 2) {
        if (gx_gui::parameter_map.hasId("jconv.wet_dry")) {
            gx_gui::Parameter& p = gx_gui::parameter_map["jconv.wet_dry"];
            if (p.isFloat()) {
                p.getFloat().convert_from_range(-1, 1);
            }
        }
    }
}

void PresetIO::read_parameters(JsonParser &jp, bool preset) {
    jp.next(JsonParser::begin_object);
    do {
        jp.next(JsonParser::value_key);
        if (!gx_gui::parameter_map.hasId(jp.current_value())) {
            gx_print_warning(_("recall settings"),
                             _("unknown parameter: ")+jp.current_value());
            jp.skip_object();
            continue;
        }
        gx_gui::Parameter& param = gx_gui::parameter_map[jp.current_value()];
        if (!preset and param.isInPreset()) {
            gx_print_warning(_("recall settings"),
                             _("preset-parameter ")+param.id()+_(" in settings"));
            jp.skip_object();
            continue;
        } else if (preset and !param.isInPreset()) {
            gx_print_warning(_("recall settings"),
                             _("non preset-parameter ")+param.id()+_(" in preset"));
            jp.skip_object();
            continue;
        }
        param.readJSON_value(jp);
        plist.push_back(&param);
    } while (jp.peek() == JsonParser::value_key);
    jp.next(JsonParser::end_object);
}

void PresetIO::write_parameters(JsonWriter &w, bool preset) {
    w.begin_object(true);
    for (gx_gui::ParamMap::iterator i = gx_gui::parameter_map.begin();
                                   i != gx_gui::parameter_map.end(); ++i) {
        gx_gui::Parameter *param = i->second;
        if ((preset and param->isInPreset()) or(!preset and !param->isInPreset())) {
            param->writeJSON(w);
            w.newline();
        }
    }
    w.end_object(true);
}

void PresetIO::read_intern(JsonParser &jp, bool *has_midi, const gx_system::SettingsFileHeader& head) {
    bool use_midi = (has_midi != 0) || midi_in_preset();
    if (has_midi) {
        *has_midi = false;
    }
    jp.next(JsonParser::begin_object);
    do {
        jp.next(JsonParser::value_key);
        if (jp.current_value() == "engine") {
            read_parameters(jp, true);
        } else if (jp.current_value() == "jconv") {
	    jcset = gx_engine::GxJConvSettings(jp);
        } else if (jp.current_value() == "midi_controller") {
            if (use_midi) {
                m = new gx_gui::MidiControllerList::controller_array
                               (gx_gui::MidiControllerList::controller_array_size);
                mctrl.readJSON(jp, *m);
                if (has_midi) {
                    *has_midi = true;
                }
            } else {
                jp.skip_object();
            }
        } else {
            gx_print_warning(_("recall settings"),
                             _("unknown preset section: ") + jp.current_value());
        }
    } while (jp.peek() == JsonParser::value_key);
    jp.next(JsonParser::end_object);
    mctrl.remove_controlled_parameters(plist, m);
    fixup_parameters(head);
}

void PresetIO::commit_preset() {
    convolver.jcset = jcset;
    for (gx_gui::paramlist::iterator i = plist.begin(); i != plist.end(); ++i) {
        (*i)->setJSON_value();
    }
    if (m) {
        mctrl.set_controller_array(*m);
    }
    clear();
}

void PresetIO::write_intern(JsonWriter &w, bool write_midi) {
    w.begin_object(true);
    w.write_key("engine");
    write_parameters(w, true);
    w.write_key("jconv");
    convolver.jcset.writeJSON(w);
    if (write_midi) {
        w.write_key("midi_controller");
        mctrl.writeJSON(w);
    }
    w.newline();
    w.end_object(true);
}

void PresetIO::write_preset(gx_system::JsonWriter& jw) {
    write_intern(jw, midi_in_preset());
}

void PresetIO::copy_preset(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader& head,
		    gx_system::JsonWriter &jw) {
    gx_gui::parameter_map.set_init_values();
    bool has_midi;
    clear();
    read_intern(jp, &has_midi, head);
    commit_preset();
    write_intern(jw, has_midi);
}


/****************************************************************
 ** class StateIO
 */

StateIO::StateIO(gx_gui::MidiControllerList& mctrl, gx_engine::ConvolverAdapter& cvr,
		 gx_gui::MidiStandardControllers& mstdctr, gx_jack::GxJack& jack_)
    : PresetIO(mctrl, cvr),
      midi_std_control(mstdctr),
      jack(jack_) {
}

StateIO::~StateIO() {
}

void StateIO::read_state(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader& head) {
    clear();
    try {
        do {
            jp.next(JsonParser::value_string);
            if (jp.current_value() == "settings") {
                read_parameters(jp, false);
            } else if (jp.current_value() == "current_preset") {
                read_intern(jp, 0, head);
            } else if (jp.current_value() == "midi_controller") {
                m = new gx_gui::MidiControllerList::controller_array
                               (gx_gui::MidiControllerList::controller_array_size);
                mctrl.readJSON(jp, *m);
            } else if (jp.current_value() == "midi_ctrl_names") {
                midi_std_control.readJSON(jp);
            } else if (jp.current_value() == "jack_connections") {
                jack.read_connections(jp);
            } else {
                gx_print_warning(_("recall settings"),
                                 _("unknown section: ") + jp.current_value());
                jp.skip_object();
            }
        } while (jp.peek() == JsonParser::value_string);
    } catch(JsonException& e) {
        //gx_print_error(_("recall settings"), _("invalid settings file: ") + filename);
        return /*false*/;
    }
    return /*true*/;
}

void StateIO::commit_state() {
    commit_preset();
}

void StateIO::write_state(gx_system::JsonWriter &jw) {
    //gx_print_info(_("writing to "), filename.c_str());

    jw.write("settings");
    write_parameters(jw, false);

    jw.write("midi_controller");
    gx_gui::controller_map.writeJSON(jw);

    jw.write("midi_ctrl_names");
    gx_gui::midi_std_ctr.writeJSON(jw);

    jw.write("current_preset");
    write_intern(jw, false);

    jw.write("jack_connections");
    jack.write_connections(jw);

    jw.newline();
}


/****************************************************************
 ** GxSettings
 */

static const char *std_presetname_postfix = "pre_rc";
static const char *statename_postfix = "_rc";

const char *factory_settings[][2] = { // FIXME in json file
    {"funkmuscle", "funkmuscle_rc"},
    {"zettberlin", "zettberlin_rc"},
    {"autoandimat", "dlp_ae_rc"},
    {"StudioDave", "autoandimat_rc"},
    {"JP", "jp_n_o_s_rc"},
    {0}
};

static string get_statefile_name(gx_system::CmdlineOptions& opt, gx_jack::GxJack& jack) {
    if (!opt.get_loadfile().empty()) {
	return opt.get_loadfile();
    }
    return opt.get_user_filepath(jack.get_instancename() + "_rc");
}

GxSettings::GxSettings(gx_system::CmdlineOptions& opt, gx_jack::GxJack& jack_, gx_engine::ConvolverAdapter& cvr,
		       gx_gui::MidiStandardControllers& mstdctr, gx_gui::MidiControllerList& mctrl,
		       gx_engine::ModuleSequencer& seq_)
    : GxSettingsBase(get_statefile_name(opt,jack_), seq_),
      preset_io(mctrl, cvr),
      state_io(mctrl, cvr, mstdctr, jack_),
      presetfile_parameter("system.current_preset_file"),
      state_loaded(false),
      jack(jack_),
      options(opt) {
    set_io(state_io, preset_io);
    jack.signal_client_change().connect(
	sigc::mem_fun(*this, &GxSettings::jack_client_changed));
    presetfile_parameter.set_standard(get_default_presetfile(opt));
    presetfile_parameter.signal_changed().connect(
	sigc::mem_fun(*this, &GxSettings::presetfile_changed));
    gx_gui::parameter_map.insert(&presetfile_parameter);

    for (const char *(*p)[2] = factory_settings; (*p)[0]; ++p) {
	Factory *f = new Factory((*p)[0]);
	factory_presets.push_back(f);
	string path = opt.get_factory_filepath((*p)[1]);
	try {
	    f->setting.open(path);
	} catch (JsonException& e) {
	    gx_print_error(path.c_str(), _("not found or parse error"));
	}
    }
    try {
	presetfile.open(get_default_presetfile(opt));
    } catch(JsonException& e) {
	gx_print_error(presetfile.get_filename().c_str(), _("parse error"));
	return;
    }
    if (!presetfile.get_header().is_current()) {
	convert_presetfile();
    }
    gx_system::GxExit::get_instance().signal_exit().connect(
	sigc::mem_fun(*this, &GxSettings::exit_handler));
    instance = this; //FIXME
}

GxSettings *GxSettings::instance = 0;//FIXME

GxSettings::~GxSettings() {
    instance = 0;
    if (current_source == state && state_loaded) {
	save_to_state();
    }
}

void GxSettings::exit_handler(bool otherthread) {
    if (otherthread) {
	return;
    }
    if (current_source == state && state_loaded) {
	save_to_state();
    }
}

void GxSettings::jack_client_changed() {
    string fn = make_state_filename();
    if (fn == statefile.get_filename()) {
	return;
    }
    statefile.set_filename(fn);
    presetfile_parameter.set_standard(make_std_preset_filename());
    if (current_source == state) {
	load(state);
    }
}

string GxSettings::get_default_presetfile(CmdlineOptions& opt) {
    return opt.get_user_filepath(
	gx_jack::GxJack::get_default_instancename() + std_presetname_postfix);
}

string GxSettings::make_state_filename() {
    return options.get_user_filepath(
	gx_jack::GxJack::get_default_instancename() + statename_postfix);
}

string GxSettings::make_std_preset_filename() {
    return options.get_user_filepath(
	jack.get_instancename() + std_presetname_postfix);
}

void GxSettings::check_settings_dir(CmdlineOptions& opt) {
    string user_dir = opt.get_user_dir();
    if (access((user_dir+".").c_str(), R_OK|W_OK|X_OK) != 0) {
	if (errno != ENOENT) {
	    throw GxFatalError(
		boost::format(_("no read/write access in guitarix config dir '%1%'"))
		% user_dir);
	}
	if (mkdir(user_dir.c_str(), 0777) != 0) {
	    throw GxFatalError(
		boost::format(_("can't create guitarix config dir '%1%'"))
		% user_dir);
	}
	// need to create so that old guitarix
	// versions (< 0.20) don't delete confing
	ofstream f(opt.get_user_filepath("version-0.03.3").c_str());
	f << string("gx_head-") + GX_VERSION << endl;
	f.close();
	if (!f.good()) {
	    throw GxFatalError(
		boost::format(_("can't create file in '%1%' !!??"))
		% user_dir);
	}
    }
    string tfile = get_default_presetfile(opt);
    if (access(tfile.c_str(), R_OK|W_OK) != 0) {
	if (errno != ENOENT) {
	    throw GxFatalError(
		boost::format(_("no read/write access to guitarix preset file '%1%'"))
		% tfile);
	}
	if (!SettingsFileHeader::make_empty_settingsfile(tfile)) {
	    throw GxFatalError(
		boost::format(_("can't create file in '%1%' !!??")) % user_dir);
	}
    }
}

void GxSettings::load(Source src, const string& name, const string& factory) {
    GxSettingsBase::load(src, name, factory);
    if (src == state) {
	state_loaded = true;
    }
}

void GxSettings::presetfile_changed() {
    change_preset_file(presetfile_parameter.get_path());
}


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

#if 0
// ----- modify (add/sub/change) a existing preset file
static bool gx_modify_preset(const char* presname, const char* newname = 0,
                      bool remove = false, bool rewrite = false) {
    string tmpfile = gx_preset_file.get_path() + "_tmp";
    ifstream ofile(gx_preset_file.get_path().c_str());
    ofstream nfile(tmpfile.c_str());
    JsonParser jp(&ofile);
    JsonWriter jw(&nfile);

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
                PresetReader p(jp, &has_midi, major, minor);
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
#endif

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
    gx_print_info(_("Preset List Building"),
		  boost::format(_("%1% presets found")) % gxpreset.plist.size());
    return true;
}

// ----------- add new preset to menus
void GxPreset::gx_add_preset_to_menus(const string& presname) {
    static GCallback preset_action_func[] = {
        G_CALLBACK(gxpreset.gx_load_preset),
        G_CALLBACK(gxpreset.gx_save_oldpreset),
        G_CALLBACK(gxpreset.gx_rename_preset_dialog),
        G_CALLBACK(gxpreset.gx_delete_preset_dialog)
    };
    for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; ++i)
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
    for (its = pm_list[lindex].begin(); its != pm_list[lindex].end(); ++its) {
        ++pos;
    }
    pos += 1;

    // add small mnemonic
    string name = to_string(pos) + "  " + presname;
    if (pos <= 9) {
	name = "_" + name;
    }

    // GDK numbers
    guint accel_key = GDK_1  + pos - 1;

    // create item
    GtkWidget* menuitem = gtk_menu_item_new_with_mnemonic(name.c_str());
    g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(func),
                      NULL);

    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuitem);

    // get accel_path for menuitem
    string acc_path = gx_get_accel_path(lindex) + to_string(accel_key);

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
                                  gx_gui::GxMainInterface::get_instance().fAccelGroup->gobj());
    }

    its = pm_list[lindex].end();
    // add a pointer to the menuitem to the preset menu list
    pm_list[lindex].insert(its, GTK_MENU_ITEM(menuitem));
    gtk_widget_show(menuitem);
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
GtkMenuItem* const GxPreset::gx_get_preset_item_from_name(int lindex, const string& name) {
    vector<string>::iterator its;
    vector<GtkMenuItem*>::iterator it = pm_list[lindex].begin();
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
        vector<GtkMenuItem*>::iterator it = pm_list[i].begin();
        for (it = pm_list[i].begin(); it != pm_list[i].end(); ++it) {
            gtk_widget_destroy(GTK_WIDGET(*it));
        }
    }

    if (!gx_build_preset_list()) {
        gx_print_warning(_("Load preset file"), _("selecting default preset bank"));
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
        gx_print_warning(_("Preset Switching"),
                         _("Preset list is empty, make some :)"));
        return false;
    }
    vector<GtkMenuItem*>::iterator it = pm_list[LOAD_PRESET_LIST].begin();
    while (n > 0) {
        ++it;
        if (it == pm_list[LOAD_PRESET_LIST].end())
            return false;
        --n;
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
    if (GxSettings::get_instance().setting_is_preset()) {
        GtkMenuItem* const itemi =
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
    if (GxSettings::get_instance().setting_is_preset()) {
        GtkMenuItem* const itemi =
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
    gxpreset.gx_load_preset(*it, NULL);
}

// ----------
void GxPreset::gx_delete_active_preset_dialog(GtkWidget* item, gpointer arg) {
    if (!GxSettings::get_instance().setting_is_preset() || GxSettings::get_instance().get_current_name().empty()) {
        gx_print_warning(_("Deleting Active Preset"),
                         _("No active preset, this is the main setting"));
        return;
    }

    // tmp store
    string presname = GxSettings::get_instance().get_current_name();

    // call dialog
    gxpreset.gx_delete_preset_dialog(NULL, NULL);

    if (GxSettings::get_instance().get_current_name().empty() && !GxSettings::get_instance().setting_is_preset())
        gx_print_info(_("Deleting Active Preset"),
                      string(_("Deleted preset ")) + presname +
                      string(_(", recalled main setting")));
}


// ----preset deletion dialog
void GxPreset::gx_delete_preset_dialog(GtkMenuItem *menuitem, gpointer arg) {
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

    GxSettings::get_instance().clear_preset();

    // clear list
    gx_refresh_preset_menus();
    gx_print_info(_("All Presets Deleting"), string(_("deleted ALL presets!")));
}

static bool gx_load_preset_from_file(const char* presname) {
    GxSettings::get_instance().load(
	GxSettings::preset,presname);
    return true;
}

// ----preset deletion
void GxPreset::gx_delete_preset(GtkMenuItem* item, gpointer arg) {

    // delete it via interface
    const string presname = GxSettings::get_instance().get_current_name();

    GxSettings::get_instance().erase_preset(presname);

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
    if (!GxSettings::get_instance().setting_is_preset() || GxSettings::get_instance().get_current_name().empty()) {
        gx_print_warning(_("Renaming Active Preset"),
                         _("This is the main setting, "
                           "load a preset first"));
        return;
    }

    string presname = GxSettings::get_instance().get_current_name();

    // get current preset menu item
    GtkMenuItem* const rnm_item =
        gxpreset.gx_get_preset_item_from_name(RENAME_PRESET_LIST, presname);

    // call delete dialog
    if (rnm_item)
        gxpreset.gx_rename_preset_dialog(rnm_item, NULL);

    if (presname == GxSettings::get_instance().get_current_name()) {
        gx_print_warning(_("Renaming Active Preset"),
                         _("The preset name is unchanged"));
        return;
    }

    if (!GxSettings::get_instance().get_current_name().empty() && GxSettings::get_instance().setting_is_preset())
        gx_print_info(_("Renaming Active Preset"),
                      string(_("Renamed preset ")) + presname +
                      string(_(" to ")) + GxSettings::get_instance().get_current_name());
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
        gx_print_error(_("Preset Loading"), string(_("Could not load preset ")) + preset_name);
        return;
    }

    // print out info
    gx_print_info(_("Preset Loading"), string(_("loaded preset ")) + preset_name);
    /* collect info for stage info display*/
    gx_gui::guivar.show_patch_info = gx_get_single_preset_menu_pos(GxSettings::get_instance().get_current_name(), 0);
}

// ---- funktion save
void GxPreset::gx_save_preset(const char* presname, bool expand_menu) {
    bool found = GxSettings::get_instance().is_in_preset(presname);
    GxSettings::get_instance().save_to_preset(presname);

    // update preset menus if needed
    if (expand_menu == found) {
        assert(false);
    }
    if (expand_menu)
        gx_add_preset_to_menus(string(presname));

    gx_refresh_preset_menus();

    gx_print_info(_("Preset Saving"), string(_("saved preset ")) + string(presname));
}

///------factory presets--------///
static bool gx_load_preset_from_factory(const char* presname, int i) {
    GxSettings& gxs = GxSettings::get_instance();
    gxs.load(GxSettings::factory,presname,gxs.get_factory(i));
    return true;
}

// ----menu funktion load preset from factory
void GxPreset::gx_load_factory_preset(GtkMenuItem *menuitem, gpointer load_preset) {
    // retrieve preset name
    int i = GPOINTER_TO_INT(load_preset);
    vector<GtkMenuItem*>::iterator it = gxpreset.fpm_list[i].begin();
    vector<string>::iterator its = gxpreset.fplist[i].begin();
    for (it = gxpreset.fpm_list[i].begin(); it != gxpreset.fpm_list[i].end(); ++it) {
        if (menuitem == *it)
            break;
        ++its;
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
}

// load the factory preset file
void GxPreset::gx_load_factory_file(int i) {
    // initialize list
    fplist[i].clear();
    // initialize menu pointer list
    fpm_list[i].clear();

    GxSettings& gxs = GxSettings::get_instance();
    gxs.fill_factory_preset_names(gxs.get_factory(i), fplist[i]);

    vector<string>::iterator it;
    for (it = fplist[i].begin() ; it != fplist[i].end(); ++it) {
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
void GxPreset::gx_recall_settings_file() {
    GxSettings::get_instance().load(GxSettings::state);
#if 0 //FIXME
    gx_print_info(
	_("Main Setting recalling"),
	(boost::format(_("Called back main setting %1%")) % fname).str());
    gx_print_info(
	_("loading Settings file"),
	(boost::format(_("loaded settings file %1%")) % *filename).str());
#endif
    gx_gui::guivar.show_patch_info = 0;
    gx_refresh_preset_menus();
}

// ----- select a external preset file
void GxPreset::gx_load_preset_file(const char* presname, bool expand_menu) {
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
    if (file_chooser.run() == Gtk::RESPONSE_ACCEPT) {
        GxSettings::get_instance().change_preset_file(file_chooser.get_filename());
        gx_gui::guivar.show_patch_info = 0;
        gxpreset.gx_refresh_preset_menus();
    }
}

// ----- export preset file
void GxPreset::gx_save_preset_file(const char* presname, bool expand_menu) {
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
        if (GxSettings::get_instance().get_current_name().empty()) {
            gx_print_warning(_("Saving Active Preset"),
                             _("We are in main setting, load a preset first"));
            return;
        }
        presname = GxSettings::get_instance().get_current_name();

    } else {    // we are saving another preset from the menu

        vector<GtkMenuItem*>::iterator it;

        for (it = gxpreset.pm_list[SAVE_PRESET_LIST].begin();
             it != gxpreset.pm_list[SAVE_PRESET_LIST].end(); ++it) {
            if (menuitem == *it) {
                break;
            }
            ++its;
        }
        presname = *its;
    }
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
        gx_print_error(_("Saving new preset"), _("no preset name given"));
        return;
    }

    // replace spaces by -
    gxpreset.gx_cleanup_preset_name(presname);

    // is the name alrady taken ?
    vector<string>::iterator its;
    vector<GtkMenuItem*>::iterator it = gxpreset.pm_list[SAVE_PRESET_LIST].begin();

    for (its = gxpreset.plist.begin(); its != gxpreset.plist.end(); ++its) {
        // found a match
        if (presname == *its) {
            gx_print_error(_("New Preset Saving"),
                           string(_("preset name ")) +
                           presname +
                           string(_(" already in use, choose another one")));
            gxpreset.gx_save_newpreset_dialog(*it, NULL);
            return;
        }
        ++it;
    }

    // finally save to preset file
    gxpreset.gx_save_preset(presname.c_str(), true);
}

// ----- save current setting as main setting
void GxPreset::gx_save_main_setting(GtkMenuItem* item, gpointer arg) {
    GxSettings::get_instance().save_to_state();
#if 0 //FIXME
        gx_print_error(_("Main Setting"), _("can't save main setting"));
    } else if (GxSettings::get_instance().setting_is_preset()) {
        gx_print_info(_("Main Setting"),
                      _("Saved current preset into main setting"));
    } else {
        gx_print_info(_("Main Setting"), _("Saved main setting"));
#endif
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
    Glib::ustring newname;
    gx_gui::gx_get_text_entry(entry, newname);

    if (newname.empty()) {
        gx_print_error(_("Preset Renaming"), _("no preset name given"));
        gxpreset.old_preset_name = "";
        return;
    }

    // replace spaces by -
    gxpreset.gx_cleanup_preset_name(newname);

    // get the UI to manipulate the preset file
    if (!GxSettings::get_instance().rename_preset(gxpreset.old_preset_name, newname)) {
        gx_print_error(_("Preset Renaming"),
                       string(_("Could not rename preset ")) + gxpreset.old_preset_name);
        gxpreset.old_preset_name = "";
        return;
    }

    // refresh the menus
    gxpreset.gx_refresh_preset_menus();

}

// ----preset renaming dialog
void GxPreset::gx_rename_preset_dialog(GtkMenuItem *menuitem, gpointer arg) {
    vector<string>::iterator its = gxpreset.plist.begin();
    vector<GtkMenuItem*>::iterator it = gxpreset.pm_list[RENAME_PRESET_LIST].begin();
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
        gx_print_warning(_("Rename Preset Dialog"),
                         _(" Preset renaming has been cancelled"));
        gxpreset.old_preset_name = "";
        return;
    }
}

/* ----------------------------------------------------------------*/
} /* end of gx_preset namespace */

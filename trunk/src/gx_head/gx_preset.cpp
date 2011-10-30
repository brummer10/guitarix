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

#include <sys/stat.h>

#include "engine.h"                  // NOLINT

namespace gx_preset {

/****************************************************************
 ** class PresetIO
 */

PresetIO::PresetIO(gx_gui::MidiControllerList& mctrl_,
		   gx_engine::ConvolverAdapter& cvr_,
		   const gx_system::CmdlineOptions& opt_)
    : gx_system::AbstractPresetIO(),
      mctrl(mctrl_),
      convolver(cvr_),
      opt(opt_),
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

void PresetIO::read_parameters(gx_system::JsonParser &jp, bool preset) {
    jp.next(gx_system::JsonParser::begin_object);
    do {
        jp.next(gx_system::JsonParser::value_key);
        if (!gx_gui::parameter_map.hasId(jp.current_value())) {
            gx_system::gx_print_warning(
		_("recall settings"),
		_("unknown parameter: ")+jp.current_value());
            jp.skip_object();
            continue;
        }
        gx_gui::Parameter& param = gx_gui::parameter_map[jp.current_value()];
        if (!preset and param.isInPreset()) {
            gx_system::gx_print_warning(
		_("recall settings"),
		_("preset-parameter ")+param.id()+_(" in settings"));
            jp.skip_object();
            continue;
        } else if (preset and !param.isInPreset()) {
            gx_system::gx_print_warning(
		_("recall settings"),
		_("non preset-parameter ")+param.id()+_(" in preset"));
            jp.skip_object();
            continue;
        }
        param.readJSON_value(jp);
        plist.push_back(&param);
    } while (jp.peek() == gx_system::JsonParser::value_key);
    jp.next(gx_system::JsonParser::end_object);
}

void PresetIO::write_parameters(gx_system::JsonWriter &w, bool preset) {
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

void PresetIO::read_intern(gx_system::JsonParser &jp, bool *has_midi, const gx_system::SettingsFileHeader& head) {
    bool use_midi = (has_midi != 0) || midi_in_preset();
    if (has_midi) {
        *has_midi = false;
    }
    jp.next(gx_system::JsonParser::begin_object);
    do {
        jp.next(gx_system::JsonParser::value_key);
        if (jp.current_value() == "engine") {
            read_parameters(jp, true);
        } else if (jp.current_value() == "jconv") {
	    jcset = gx_engine::GxJConvSettings();
	    jcset.readJSON(jp, opt.get_IR_pathlist());
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
            gx_system::gx_print_warning(
		_("recall settings"),
		_("unknown preset section: ") + jp.current_value());
	    jp.skip_object();
        }
    } while (jp.peek() == gx_system::JsonParser::value_key);
    jp.next(gx_system::JsonParser::end_object);
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

void PresetIO::write_intern(gx_system::JsonWriter &w, bool write_midi) {
    w.begin_object(true);
    w.write_key("engine");
    write_parameters(w, true);
    w.write_key("jconv");
    convolver.jcset.writeJSON(w, opt.get_IR_pathlist());
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
		 gx_gui::MidiStandardControllers& mstdctr, gx_jack::GxJack& jack_,
		 const gx_system::CmdlineOptions& opt_)
    : PresetIO(mctrl, cvr, opt_),
      midi_std_control(mstdctr),
      jack(jack_) {
}

StateIO::~StateIO() {
}

void StateIO::read_state(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader& head) {
    clear();
    do {
	jp.next(gx_system::JsonParser::value_string);
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
	    gx_system::gx_print_warning(
		_("recall settings"),
		_("unknown section: ") + jp.current_value());
	    jp.skip_object();
	}
    } while (jp.peek() == gx_system::JsonParser::value_string);
}

void StateIO::commit_state() {
    commit_preset();
}

void StateIO::write_state(gx_system::JsonWriter &jw, bool no_preset) {
    jw.write("settings");
    write_parameters(jw, false);

    jw.write("midi_controller");
    gx_gui::controller_map.writeJSON(jw);

    jw.write("midi_ctrl_names");
    gx_gui::midi_std_ctr.writeJSON(jw);

    if (!no_preset) {
	jw.write("current_preset");
	write_intern(jw, false);
    }

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

GxSettings::GxSettings(gx_system::CmdlineOptions& opt, gx_jack::GxJack& jack_, gx_engine::ConvolverAdapter& cvr,
		       gx_gui::MidiStandardControllers& mstdctr, gx_gui::MidiControllerList& mctrl,
		       gx_engine::ModuleSequencer& seq_)
    : GxSettingsBase(seq_),
      preset_io(mctrl, cvr, opt),
      state_io(mctrl, cvr, mstdctr, jack_, opt),
      presetfile_parameter("system.current_preset_file"),
      state_loaded(false),
      jack(jack_),
      options(opt) {
    set_io(&state_io, &preset_io);
    gx_gui::parameter_map.insert(&presetfile_parameter);
    statefile.set_filename(make_default_state_filename());
    for (const char *(*p)[2] = factory_settings; (*p)[0]; ++p) {
	Factory *f = new Factory((*p)[0]);
	factory_presets.push_back(f);
	string path = opt.get_factory_filepath((*p)[1]);
	try {
	    f->setting.open(path);
	} catch (gx_system::JsonException& e) {
	    gx_system::gx_print_error(path.c_str(), _("not found or parse error"));
	}
    }
    check_convert_presetfile();
    presetfile_parameter.set_standard(get_default_presetfile(opt));
    instance = this; //FIXME
    gx_system::GxExit::get_instance().signal_exit().connect(
	sigc::mem_fun(*this, &GxSettings::exit_handler));
    jack.signal_client_change().connect(
	sigc::mem_fun(*this, &GxSettings::jack_client_changed));
    presetfile_parameter.signal_changed().connect(
	sigc::mem_fun(*this, &GxSettings::presetfile_changed));
}

GxSettings *GxSettings::instance = 0;//FIXME

GxSettings::~GxSettings() {
    instance = 0;
    auto_save_state();
}

void GxSettings::check_convert_presetfile() {
    try {
	presetfile.open(get_default_presetfile(options));
    } catch(gx_system::JsonException& e) {
	gx_system::gx_print_error(presetfile.get_filename().c_str(), _("parse error"));
	return;
    }
    if (!presetfile.get_header().is_current()) {
	convert_presetfile();
    }
}

void GxSettings::exit_handler(bool otherthread) {
    if (otherthread) {
	return;
    }
    auto_save_state();
}

string GxSettings::get_displayname() {
    if (current_source == factory) {
	return "[" + current_factory + "] - " + current_name;
    } else if (current_source == preset) {
	if (presetfile_parameter.is_standard()) {
	    return current_name;
	} else {
	    return presetfile_parameter.get_display_name() + " - " + current_name;
	}
    } else {
	return "";
    }
}

void GxSettings::jack_client_changed() {
    string fn = make_state_filename();
    if (state_loaded && fn == statefile.get_filename()) {
	return;
    }
    if (!state_loaded && (access(fn.c_str(), R_OK|W_OK)) != 0) {
	string defname = make_default_state_filename();
	if (access(defname.c_str(), R_OK) == 0) {
	    statefile.set_filename(defname);
	    load(state);
	    jack.clear_insert_connections();
	}
    }
    statefile.set_filename(fn);
    if (current_source == state) {
	load(state);
    }
}

string GxSettings::get_default_presetfile(gx_system::CmdlineOptions& opt) {
    return opt.get_user_filepath(
	gx_jack::GxJack::get_default_instancename() + std_presetname_postfix);
}

string GxSettings::make_std_preset_filename() {
    return options.get_user_filepath(
	jack.get_instancename() + std_presetname_postfix);
}

string GxSettings::make_default_state_filename() {
    if (!options.get_loadfile().empty()) {
	return options.get_loadfile();
    }
    return options.get_user_filepath(
	jack.get_default_instancename() + statename_postfix);
}

string GxSettings::make_state_filename() {
    if (!options.get_loadfile().empty()) {
	return options.get_loadfile();
    }
    return options.get_user_filepath(
	jack.get_instancename() + statename_postfix);
}

void GxSettings::check_settings_dir(gx_system::CmdlineOptions& opt) {
    string user_dir = opt.get_user_dir();
    if (access((user_dir+".").c_str(), R_OK|W_OK|X_OK) != 0) {
	if (errno != ENOENT) {
	    throw gx_system::GxFatalError(
		boost::format(_("no read/write access in guitarix config dir '%1%'"))
		% user_dir);
	}
	if (mkdir(user_dir.c_str(), 0777) != 0) {
	    throw gx_system::GxFatalError(
		boost::format(_("can't create guitarix config dir '%1%'"))
		% user_dir);
	}
	// need to create so that old guitarix
	// versions (< 0.20) don't delete confing
	ofstream f(opt.get_user_filepath("version-0.03.3").c_str());
	f << string("gx_head-") + GX_VERSION << endl;
	f.close();
	if (!f.good()) {
	    throw gx_system::GxFatalError(
		boost::format(_("can't create file in '%1%' !!??"))
		% user_dir);
	}
    }
    string tfile = get_default_presetfile(opt);
    if (access(tfile.c_str(), R_OK|W_OK) != 0) {
	if (errno != ENOENT) {
	    throw gx_system::GxFatalError(
		boost::format(_("no read/write access to guitarix preset file '%1%'"))
		% tfile);
	}
	if (!gx_system::SettingsFileHeader::make_empty_settingsfile(tfile)) {
	    throw gx_system::GxFatalError(
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

bool GxSettings::rename_preset(const string& name, const string& newname) {
    bool rv = GxSettingsBase::rename_preset(name, newname);
    presetfile_parameter.signal_changed()();
    return rv;
}

void GxSettings::presetfile_changed() {
    try {
	change_preset_file(presetfile_parameter.get_path());
    } catch(gx_system::JsonException& e) {
	gx_system::gx_print_warning(
	    presetfile_parameter.get_path().c_str(), e.what());
    }
}

bool GxSettings::set_preset_file(const string& newfile) {
    string oldfile = presetfile_parameter.get_path();
    presetfile_parameter.set_path(newfile);
    if (presetfile_fail()) {
	presetfile_parameter.set_path(oldfile);
	return false;
    }
    return true;
}

/* ----------------------------------------------------------------*/
} /* end of gx_preset namespace */

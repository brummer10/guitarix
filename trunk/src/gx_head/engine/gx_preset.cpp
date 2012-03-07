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

PresetIO::PresetIO(gx_engine::MidiControllerList& mctrl_,
		   gx_engine::ConvolverAdapter& cvr_,
		   gx_engine::ParamMap& param_,
		   const gx_system::CmdlineOptions& opt_)
    : gx_system::AbstractPresetIO(),
      mctrl(mctrl_),
      convolver(cvr_),
      param(param_),
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
    return param["system.midi_in_preset"].getSwitch().get();
}

void PresetIO::read_preset(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader& head) {
    clear();
    for (gx_engine::ParamMap::iterator i = param.begin(); i != param.end(); ++i) {
 	if (i->second->isInPreset()) {
	    i->second->stdJSON_value();
	    plist.push_back(i->second);
	}
    }
    read_intern(jp, 0, head);
}

void PresetIO::fixup_parameters(const gx_system::SettingsFileHeader& head) {
    assert(param.hasId("jconv.wet_dry"));
    if (head.is_current()) {
        return;
    }
    if (head.get_major() == 1 && head.get_minor() < 2) {
        if (param.hasId("jconv.wet_dry")) {
            gx_engine::Parameter& p = param["jconv.wet_dry"];
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
        if (!param.hasId(jp.current_value())) {
            gx_system::gx_print_warning(
		_("recall settings"),
		_("unknown parameter: ")+jp.current_value());
            jp.skip_object();
            continue;
        }
        gx_engine::Parameter& p = param[jp.current_value()];
        if (!preset and p.isInPreset()) {
            gx_system::gx_print_warning(
		_("recall settings"),
		_("preset-parameter ")+p.id()+_(" in settings"));
            jp.skip_object();
            continue;
        } else if (preset and !p.isInPreset()) {
            gx_system::gx_print_warning(
		_("recall settings"),
		_("non preset-parameter ")+p.id()+_(" in preset"));
            jp.skip_object();
            continue;
        }
        p.readJSON_value(jp);
    } while (jp.peek() == gx_system::JsonParser::value_key);
    jp.next(gx_system::JsonParser::end_object);
}

void PresetIO::write_parameters(gx_system::JsonWriter &w, bool preset) {
    w.begin_object(true);
    for (gx_engine::ParamMap::iterator i = param.begin();
                                   i != param.end(); ++i) {
        gx_engine::Parameter *param = i->second;
	if (!param->isSavable()) {
	    continue;
	}
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
                m = gx_engine::MidiControllerList::create_controller_array();
                mctrl.readJSON(jp, param, *m);
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
    for (gx_engine::paramlist::iterator i = plist.begin(); i != plist.end(); ++i) {
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
    param.set_init_values();
    bool has_midi;
    clear();
    read_intern(jp, &has_midi, head);
    commit_preset();
    write_intern(jw, has_midi);
}


/****************************************************************
 ** class StateIO
 */

StateIO::StateIO(gx_engine::MidiControllerList& mctrl, gx_engine::ConvolverAdapter& cvr,
		 gx_engine::ParamMap& param, gx_engine::MidiStandardControllers& mstdctr,
		 gx_jack::GxJack& jack_, const gx_system::CmdlineOptions& opt_)
    : PresetIO(mctrl, cvr, param, opt_),
      midi_std_control(mstdctr),
      jack(jack_) {
}

StateIO::~StateIO() {
}

void StateIO::read_state(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader& head) {
    clear();
    for (gx_engine::ParamMap::iterator i = param.begin(); i != param.end(); ++i) {
	i->second->stdJSON_value();
	plist.push_back(i->second);
    }
    do {
	jp.next(gx_system::JsonParser::value_string);
	if (jp.current_value() == "settings") {
	    read_parameters(jp, false);
	} else if (jp.current_value() == "current_preset") {
	    read_intern(jp, 0, head);
	} else if (jp.current_value() == "midi_controller") {
	    m = gx_engine::MidiControllerList::create_controller_array();
	    mctrl.readJSON(jp, param, *m);
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
    gx_engine::controller_map.writeJSON(jw);

    jw.write("midi_ctrl_names");
    gx_engine::midi_std_ctr.writeJSON(jw);

    if (!no_preset) {
	jw.write("current_preset");
	write_intern(jw, false);
    }

    jw.write("jack_connections");
    jack.write_connections(jw);

    jw.newline();
}


/****************************************************************
 ** class PluginPresetList
 */

PluginPresetList::PluginPresetList(const std::string& fname, gx_engine::ParamMap& pmap_)
    : Glib::Object(), filename(fname), pmap(pmap_), is(), jp(&is) {
}

Glib::RefPtr<PluginPresetList> PluginPresetList::create(const std::string& fname, gx_engine::ParamMap& pmap) {
    return Glib::RefPtr<PluginPresetList>(new PluginPresetList(fname, pmap));
}

bool PluginPresetList::start() {
    is.close();
    is.open(filename.c_str());
    jp.set_streampos(0);
    if (is.fail()) {
	return false;
    }
    try {
	jp.next(gx_system::JsonParser::begin_array);
	jp.next(gx_system::JsonParser::value_string);
	if (jp.current_value() != "gx_plugin_version") {
	    throw gx_system::JsonException("invalid gx_plugin file header");
	}
	jp.next(gx_system::JsonParser::value_number);
    } catch (gx_system::JsonException& e) {
	gx_system::gx_print_error(filename.c_str(), _("parse error"));
	return false;
    }
    return true;
}

bool PluginPresetList::next(Glib::ustring& name, bool *is_set) {
    try {
	if (jp.peek() == gx_system::JsonParser::end_array) {
	    name = "";
	    if (is_set) {
		*is_set = false;
	    }
	    return false;
	}
	jp.next(gx_system::JsonParser::value_string);
	name = jp.current_value();
	if (is_set) {
	    jp.next(gx_system::JsonParser::begin_object);
	    *is_set = true;
	    while (jp.peek() != gx_system::JsonParser::end_object) {
		jp.next(gx_system::JsonParser::value_key);
		gx_engine::Parameter& p = pmap[jp.current_value()];
		p.readJSON_value(jp);
		if (!p.compareJSON_value()) {
		    *is_set = false;
		}
	    }
	    jp.next(gx_system::JsonParser::end_object);
	} else {
	    jp.skip_object();
	}
    } catch (gx_system::JsonException& e) {
	gx_system::gx_print_error(filename.c_str(), _("parse error"));
	return false;
    }
    return true;
}

void PluginPresetList::set(const Glib::ustring& name) {
    gx_engine::paramlist plist;
    if (!start()) {
	return;
    }
    try {
	while (jp.peek() != gx_system::JsonParser::end_array) {
	    jp.next(gx_system::JsonParser::value_string);
	    if (jp.current_value() != name) {
		jp.skip_object();
	    } else {
		jp.next(gx_system::JsonParser::begin_object);
		while (jp.peek() != gx_system::JsonParser::end_object) {
		    jp.next(gx_system::JsonParser::value_key);
		    gx_engine::Parameter& p = pmap[jp.current_value()];
		    p.readJSON_value(jp);
		    plist.push_back(&p);
		}
		jp.next(gx_system::JsonParser::end_object);
	    }
	}
	jp.next(gx_system::JsonParser::end_array);
	jp.next(gx_system::JsonParser::end_token);
    } catch (gx_system::JsonException& e) {
	gx_system::gx_print_error(filename.c_str(), _("parse error"));
	return;
    }
    gx_engine::controller_map.remove_controlled_parameters(plist, 0);
    for (gx_engine::paramlist::iterator i = plist.begin(); i != plist.end(); ++i) {
        (*i)->setJSON_value();
    }
}

static const int GX_PLUGIN_VERSION = 1;

void PluginPresetList::write_values(gx_system::JsonWriter& jw, std::string id) {
    //FIXME
    id += ".";
    string on_off = id + "on_off";
    string pp = id + "pp";
    jw.begin_object(true);
    for (gx_engine::ParamMap::iterator i = pmap.begin(); i != pmap.end(); ++i) {
	if (i->first.compare(0, id.size(), id) == 0) {
	    if (i->second->isControllable()) {
		if (i->first != on_off && i->first != pp) {
		    i->second->writeJSON(jw);
		    jw.newline();
		}
	    }
	}
    }
    jw.end_object(true);
}

void PluginPresetList::save(const Glib::ustring& name, const std::string& id) {
    try {
	std::string tmpfile(filename + "_tmp");
	ofstream os(tmpfile.c_str());
	gx_system::JsonWriter jw(&os);
	jw.begin_array();
	jw.write("gx_plugin_version");
	jw.write(GX_PLUGIN_VERSION, true);
	bool found = false;
	if (start()) {
	    while (jp.peek() != gx_system::JsonParser::end_array) {
		jp.next(gx_system::JsonParser::value_string);
		jw.write(jp.current_value());
		if (jp.current_value() == name) {
		    found = true;
		    write_values(jw, id);
		    jp.skip_object();
		} else {
		    jp.copy_object(jw);
		}
	    }
	}
	if (!found) {
	    jw.write(name);
	    write_values(jw, id);
	}
	jw.end_array(true);
	jw.close();
	os.close();
	if (!os.good()) {
	    gx_system::gx_print_error(_("save plugin preset"),
				      boost::format(_("couldn't write %1%")) % tmpfile);
	    return;
	}
	int rc = rename(tmpfile.c_str(), filename.c_str());
	if (rc != 0) {
	    gx_system::gx_print_error(_("save plugin preset"),
				      boost::format(_("couldn't rename %1% to %2%"))
				      % tmpfile % filename);
	}
    } catch (gx_system::JsonException& e) {
	gx_system::gx_print_error(filename.c_str(), _("parse error"));
    }
}

void PluginPresetList::remove(const Glib::ustring& name) {
    try {
	std::string tmpfile(filename + "_tmp");
	ofstream os(tmpfile.c_str());
	gx_system::JsonWriter jw(&os);
	jw.begin_array();
	jw.write("gx_plugin_version");
	jw.write(GX_PLUGIN_VERSION, true);
	if (start()) {
	    while (jp.peek() != gx_system::JsonParser::end_array) {
		jp.next(gx_system::JsonParser::value_string);
		if (jp.current_value() == name) {
		    jp.skip_object();
		} else {
		    jw.write(jp.current_value());
		    jp.copy_object(jw);
		}
	    }
	    jp.next(gx_system::JsonParser::end_array);
	    jp.next(gx_system::JsonParser::end_token);
	}
	jw.end_array(true);
	jw.close();
	os.close();
	if (!os.good()) {
	    gx_system::gx_print_error(_("save plugin preset"),
				      boost::format(_("couldn't write %1%")) % tmpfile);
	    return;
	}
	int rc = rename(tmpfile.c_str(), filename.c_str());
	if (rc != 0) {
	    gx_system::gx_print_error(_("save plugin preset"),
				      boost::format(_("couldn't rename %1% to %2%"))
				      % tmpfile % filename);
	}
    } catch (gx_system::JsonException& e) {
	gx_system::gx_print_error(filename.c_str(), _("parse error"));
    }
}


/****************************************************************
 ** GxSettings
 */

static const char *scratchpad_name = N_("Scratchpad");
static const char *scratchpad_file = "scratchpad.gx";
static const char *statename_postfix = "_rc";
static const char *bank_list = "banklist.js";

GxSettings::GxSettings(gx_system::CmdlineOptions& opt, gx_jack::GxJack& jack_, gx_engine::ConvolverAdapter& cvr,
		       gx_engine::MidiStandardControllers& mstdctr, gx_engine::MidiControllerList& mctrl,
		       gx_engine::ModuleSequencer& seq_, gx_engine::ParamMap& param_)
    : sigc::trackable(),
      GxSettingsBase(seq_),
      param(param_),
      preset_io(mctrl, cvr, param, opt),
      state_io(mctrl, cvr, param, mstdctr, jack_, opt),
      state_loaded(false),
      no_autosave(false),
      jack(jack_),
      options(opt),
      preset_parameter(*param.reg_string("system.current_preset", "?", &current_name, "")),
      bank_parameter(*param.reg_string("system.current_bank", "?", &current_bank, "")) {
    set_io(&state_io, &preset_io);
    statefile.set_filename(make_default_state_filename());
    banks.parse(opt.get_user_filepath(bank_list), opt.get_preset_dir(), opt.get_factory_dir(),
		scratchpad_name, scratchpad_file);
    instance = this;
    gx_system::GxExit::get_instance().signal_exit().connect(
	sigc::mem_fun(*this, &GxSettings::exit_handler));
    jack.signal_client_change().connect(
	sigc::mem_fun(*this, &GxSettings::jack_client_changed));
}

GxSettings *GxSettings::instance = 0;

GxSettings::~GxSettings() {
    instance = 0;
    auto_save_state();
}

void GxSettings::auto_save_state() {
    if (state_loaded) {
	if (setting_is_preset()) {
	    gx_system::PresetFile *pf = get_current_bank_file();
	    if (pf->get_type() == gx_system::PresetFile::PRESET_SCRATCH &&
		!pf->get_flags()) {
		save(*pf, current_name);
	    }
	}
	if (!no_autosave) {
	    save_to_state();
	}
    }
}

void GxSettings::exit_handler(bool otherthread) {
    if (otherthread) {
	return;
    }
    auto_save_state();
}

void GxSettings::jack_client_changed() {
    string fn = make_state_filename();
    if (state_loaded && fn == statefile.get_filename()) {
	selection_changed();
	return;
    }
    if (!state_loaded && access(fn.c_str(), R_OK|W_OK) != 0) {
	string defname = make_default_state_filename();
	if (access(defname.c_str(), R_OK) == 0) {
	    statefile.set_filename(defname);
	    loadsetting(0, "");
	    jack.clear_insert_connections();
	}
    }
    statefile.set_filename(fn);
    loadstate();
}

string GxSettings::make_default_state_filename() {
    if (!options.get_loadfile().empty()) {
	return options.get_loadfile();
    }
    std::string s = options.get_jack_instancename();
    if (!s.empty()) {
	s = options.get_user_filepath(s + statename_postfix);
	if (access(s.c_str(), R_OK|W_OK) == 0) {
	    return s;
	}
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

bool GxSettings::check_create_config_dir(const Glib::ustring& dir) {
    if (access((Glib::build_filename(dir, ".")).c_str(), R_OK|W_OK|X_OK) != 0) {
	if (errno != ENOENT) {
	    throw gx_system::GxFatalError(
		boost::format(_("no read/write access in guitarix config dir '%1%'"))
		% dir);
	}
	if (mkdir(dir.c_str(), 0777) != 0) {
	    throw gx_system::GxFatalError(
		boost::format(_("can't create guitarix config dir '%1%'"))
		% dir);
	}
	return true;
    }
    return false;
}

void GxSettings::create_default_scratch_preset() {
    save(*banks.get_file(scratchpad_name), "livebuffer1");
}

//static
bool GxSettings::check_settings_dir(gx_system::CmdlineOptions& opt, bool *need_new_preset) {
    bool copied_from_old = false;
    std::string oldpreset;
    *need_new_preset = false;
    if (check_create_config_dir(opt.get_user_dir())) {
	check_create_config_dir(opt.get_preset_dir());
	check_create_config_dir(opt.get_plugin_dir());
	check_create_config_dir(opt.get_pluginpreset_dir());
	std::string fname = gx_jack::GxJack::get_default_instancename() + statename_postfix;
	if (access(Glib::build_filename(opt.get_old_user_dir(), fname).c_str(), R_OK) == 0) {
	    copied_from_old = true;
	    Glib::RefPtr<Gio::File> f = Gio::File::create_for_path(
		Glib::build_filename(opt.get_old_user_dir(), fname));
	    try {
		f->copy(Gio::File::create_for_path(opt.get_user_filepath(fname)));
	    } catch (Gio::Error& e) {
		gx_system::gx_print_error(e.what().c_str(), _("can't copy to new config dir"));
	    }
	}
	fname = Glib::build_filename(
	    opt.get_old_user_dir(),
	    gx_jack::GxJack::get_default_instancename() + "pre_rc");
	if (access(fname.c_str(), R_OK) == 0) {
	    Glib::RefPtr<Gio::File> f = Gio::File::create_for_path(fname);
	    oldpreset = opt.get_preset_filepath("oldpresets.gx");
	    try {
		f->copy(Gio::File::create_for_path(oldpreset));
	    } catch (Gio::Error& e) {
		gx_system::gx_print_error(e.what().c_str(), _("can't copy to new config preset dir"));
		oldpreset = "";
	    }
	}
    } else {
	check_create_config_dir(opt.get_preset_dir());
	check_create_config_dir(opt.get_plugin_dir());
	check_create_config_dir(opt.get_pluginpreset_dir());
    }
    std::string fname = opt.get_preset_filepath(scratchpad_file);
    if (access(fname.c_str(), R_OK) != 0) {
	if (!gx_system::SettingsFileHeader::make_empty_settingsfile(fname)) {
	    throw gx_system::GxFatalError(
		boost::format(_("can't create file in '%1%' !!??")) % opt.get_preset_dir());
	}
	*need_new_preset = true;
    }
    fname = opt.get_user_filepath(bank_list);
    if (access(fname.c_str(), R_OK) != 0) {
	ofstream f(fname.c_str());
	if (!f.good()) {
	    throw gx_system::GxFatalError(
		boost::format(_("can't create '%1%' in directory '%2%'"))
		% bank_list % opt.get_user_dir());
	}
	gx_system::PresetFile pre;
	pre.open_file(scratchpad_name, opt.get_preset_filepath(scratchpad_file), gx_system::PresetFile::PRESET_SCRATCH, 0);
	gx_system::JsonWriter jw(&f);
	jw.begin_array(true);
	pre.writeJSON(jw);
	if (!oldpreset.empty() && pre.open_file("copied presets", oldpreset, gx_system::PresetFile::PRESET_FILE, 0)) {
	    pre.writeJSON(jw);
	}
	jw.end_array(true);
	jw.close();
	f.close();
    }
    return copied_from_old;
}

void GxSettings::loadstate() {
    GxSettingsBase::loadstate();
    if (current_source == preset) {
	gx_system::PresetFile *pf = banks.get_file(current_bank);
	if (pf && pf->get_type() == gx_system::PresetFile::PRESET_SCRATCH) {
	    /* make sure we see the content of the scratchpad,
	    ** not the state file (in case someone changed the
	    ** scratchpad while working with a different state file)
	    */
	    load_preset(pf, current_name);
	}
    }
    state_loaded = true;
}

Glib::RefPtr<PluginPresetList> GxSettings::load_plugin_preset_list(const Glib::ustring& id) {
    return PluginPresetList::create(options.get_pluginpreset_filepath(id), param);
}

/* ----------------------------------------------------------------*/
} /* end of gx_preset namespace */

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

#ifndef SCHED_IDLE
#define SCHED_IDLE SCHED_OTHER  // non-linux systems
#endif

namespace gx_preset {

/****************************************************************
 ** class PresetIO
 */

PresetIO::PresetIO(gx_engine::MidiControllerList& mctrl_,
                   gx_engine::ParamMap& param_,
                   gx_system::CmdlineOptions& opt_,
                   UnitRacks& rack_units_)
    : gx_system::AbstractPresetIO(),
      mctrl(mctrl_),
      param(param_),
      opt(opt_),
      plist(),
      m(0),
      rack_units(rack_units_) {
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
    const char *i = "system.midi_in_preset";
    if (param.hasId(i)) {
        return param[i].getBool().get_value();
    } else {
        return false;
    }
}

void PresetIO::read_preset(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader& head) {
    clear();
    for (gx_engine::ParamMap::iterator i = param.begin(); i != param.end(); ++i) {
        if (i->second->isInPreset() && i->second->isSavable()) {
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

static std::string replaced_id(const std::string& s, bool& warn) {
    const char *old_new[][2] = {
        { "beat_detector.stepper", nullptr },
        { "beat_detector.note_off", nullptr },
        { "beat_detector.atack_gain", nullptr },
        { "beat_detector.beat_gain", nullptr },
        { "beat_detector.midi_gain", nullptr },
        // begin ui.*
        // ui.<name> -> ui.<id> (rack unit visible)
        { "ui.3 Band EQ", "ui.tonemodul" },
        { "ui.BiQuad Filter", "ui.biquad" },
        { "ui.Cabinet", "ui.cab" },
        { "ui.Preamp", "ui.pre" },
        { "ui.Chorus", "ui.chorus" },
        { "ui.Chorus Mono", "ui.chorus_mono" },
        { "ui.Compressor", "ui.compressor" },
        { "ui.Convolver", "ui.jconv" },
        { "ui.Crybaby", "ui.crybaby" },
        { "ui.Delay", "ui.delay" },
        { "ui.Echo", "ui.echo" },
        { "ui.Feedback", "ui.feedback" },
        { "ui.Flanger", "ui.flanger" },
        { "ui.Flanger Mono", "ui.flanger_mono" },
        { "ui.Freeverb", "ui.freeverb" },
        { "ui.ImpulseResponse", "ui.IR" },
        { "ui.Midi Out", nullptr },
        { "ui.Moog Filter", "ui.moog" },
        { "ui.Multi Band Distortion", "ui.gx_distortion" },
        { "ui.Oscilloscope", "ui.oscilloscope" },
        { "ui.Overdrive", "ui.overdrive" },
        { "ui.Phaser", "ui.phaser" },
        { "ui.Phaser Mono", "ui.phaser_mono" },
        { "ui.Postamp", "ui.ampmodul" },
        { "ui.Scaleable EQ", "ui.eqs" },
        { "ui.Stereo Delay", "ui.stereodelay" },
        { "ui.Stereo Echo", "ui.stereoecho" },
        { "ui.Stereo Verb", "ui.stereoverb" },
        { "ui.Tonestack", "ui.amp.tonestack" },
        { "ui.Tremolo", "ui.tremolo" },
        { "ui.Vibe", "ui.univibe" },
        { "ui.Vibe Mono", "ui.univibe_mono" },
        { "ui.Zita Rev1", "ui.zita_rev1" },
        { "ui.abGate", "ui.abgate" },
        { "ui.low high pass", "ui.low_highpass" },
        { "Rev.Rocket.s_h", "rev_rocket.s_h"},
        { "Rev.Rocket.position", "rev_rocket.position"},
        { "Rev.Rocket.pp", "rev_rocket.pp"},
        { "ui.Rev.Rocket", "ui.rev_rocket"},
        // removed audio -> midi convert plugin
        { "midi_out.beat_detector.atack_gain", nullptr },
        { "midi_out.beat_detector.beat_gain", nullptr },
        { "midi_out.beat_detector.midi_gain", nullptr },
        { "midi_out.beat_detector.note_off", nullptr },
        { "midi_out.beat_detector.stepper", nullptr },
        { "midi_out.channel_1.auto_pitch", nullptr },
        { "midi_out.channel_1.autogain", nullptr },
        { "midi_out.channel_1.channel", nullptr },
        { "midi_out.channel_1.oktave", nullptr },
        { "midi_out.channel_1.program", nullptr },
        { "midi_out.channel_1.sensity", nullptr },
        { "midi_out.channel_1.velocity", nullptr },
        { "midi_out.channel_1.volume", nullptr },
        { "midi_out.channel_2.auto_pitch", nullptr },
        { "midi_out.channel_2.autogain", nullptr },
        { "midi_out.channel_2.channel", nullptr },
        { "midi_out.channel_2.oktave", nullptr },
        { "midi_out.channel_2.on_off", nullptr },
        { "midi_out.channel_2.program", nullptr },
        { "midi_out.channel_2.sensity", nullptr },
        { "midi_out.channel_2.velocity", nullptr },
        { "midi_out.channel_2.volume", nullptr },
        { "midi_out.channel_3.auto_pitch", nullptr },
        { "midi_out.channel_3.autogain", nullptr },
        { "midi_out.channel_3.channel", nullptr },
        { "midi_out.channel_3.oktave", nullptr },
        { "midi_out.channel_3.on_off", nullptr },
        { "midi_out.channel_3.program", nullptr },
        { "midi_out.channel_3.sensity", nullptr },
        { "midi_out.channel_3.velocity", nullptr },
        { "midi_out.channel_3.volume", nullptr },
        { "midi_out.on_off", nullptr },
        { "midi_out.s_h", nullptr },
        { "ui.midi_out", nullptr },
        // changes in dubber (livelooper)
        { "dubber.load1", nullptr },
        { "dubber.load2", nullptr },
        { "dubber.load3", nullptr },
        { "dubber.load4", nullptr },
        {0}
    };
    warn = true;
    for (const char *(*p)[2] = old_new; (*p)[0]; ++p) {
        if (s == (*p)[0]) {
            if ((*p)[1]) {
                return (*p)[1];
            } else {
                warn = false; // suppress warning for removed midi plugin (future additions might need to modify this)
                break;
            }
        }
    }
    return "";
}

//static
string PresetIO::try_replace_param_value(const std::string& id, const std::string& v_id, bool& found) {
    found = false;
    string res;
    if (id == "tremolo.SINE") {
        if (v_id == "os.triangle") {
            found = true;
            res = "triangle";
        } else if (v_id == "os.square") {
            found = true;
            res = "square";
        }
    }
#ifndef NDEBUG
    if (found) {
        gx_print_warning(
            _("recall settings"),
            boost::format("Parameter %1%: value %2% -> %3%") % id % v_id % res);
    }
#endif
    return res;
}

class UnitPositionID: public UnitPosition {
public:
    std::string id;
    int weight;
    UnitPositionID(const string& id_, const UnitPosition& u);
    bool operator<(const UnitPositionID& v) const { return weight < v.weight; }
};

UnitPositionID::UnitPositionID(const string& id_, const UnitPosition& u)
    : UnitPosition(u),
      id(id_),
      weight(position - 1000 * pp) {
}

void UnitsCollector::get_list(std::vector<std::string>& l, bool stereo, gx_engine::ParamMap& param) {
    std::vector<UnitPositionID> v;
    for (std::map<std::string,UnitPosition>::iterator i = m.begin(); i != m.end(); ++i) {
        if (i->first == "jconv" && i->second.position < 0) {
            i->second.position = 99; // very old presets
            gx_system::JsonStringParser jp;
            jp.get_ostream() << i->second.position;
            jp.start_parser();
            param[i->first+".position"].readJSON_value(jp);
        }
        if (i->first == "cab") {
            if (i->second.position < 0) {
                i->second.position = 98; // very old presets
                gx_system::JsonStringParser jp;
                jp.get_ostream() << i->second.position;
                jp.start_parser();
                param[i->first+".position"].readJSON_value(jp);
            }
            if (i->second.pp < 0) {
                i->second.pp = 0;
                gx_system::JsonStringParser jp;
                jp.get_ostream() << i->second.pp;
                jp.start_parser();
                param[i->first+".pp"].readJSON_value(jp);
            }
        }
        if (i->second.position >= 0 && i->second.show) {
            if ((stereo && i->second.pp < 0) || (!stereo && i->second.pp >= 0)) {
                if (!i->second.visible) { // make sure ui.XX is set for old presets
                    i->second.visible = true;
                    gx_system::JsonStringParser jp;
                    jp.put('1');
                    jp.start_parser();
                    param["ui."+i->first].readJSON_value(jp);
                }
                v.push_back(UnitPositionID(i->first, i->second));
            }
        }
    }
    l.clear();
    std::sort(v.begin(), v.end());
    int pp = 1;
    for (std::vector<UnitPositionID>::iterator j = v.begin(); j != v.end(); ++j) {
        if (!stereo && j->pp != pp) {
            pp = j->pp;
            l.push_back("ampstack");
        }
        l.push_back(j->id);
    }
    if (!stereo && pp) {
        l.push_back("ampstack");
    }
    /*
      cerr << "SL";
      for (std::vector<std::string>::iterator ii = l.begin(); ii != l.end(); ++ii) {
      cerr << " '" << *ii << "'";
      }
      cerr << endl;
    */
}

bool PresetIO::convert_old(gx_system::JsonParser &jp) {
    const std::string& s = jp.current_value();
    if (s == "system.mainwin_x") {
        jp.next(gx_system::JsonParser::value_number);
        opt.mainwin_x = jp.current_value_int();
        return true;
    }
    if (s == "system.mainwin_y") {
        jp.next(gx_system::JsonParser::value_number);
        opt.mainwin_y = jp.current_value_int();
        return true;
    }
    if (s == "system.mainwin_height") {
        jp.next(gx_system::JsonParser::value_number);
        opt.mainwin_height = jp.current_value_int();
        return true;
    }
    if (s == "system.mainwin_rack_height") {
        jp.next(gx_system::JsonParser::value_number);
        opt.window_height = jp.current_value_int();
        return true;
    }
    if (s == "system.preset_window_height") {
        jp.next(gx_system::JsonParser::value_number);
        opt.preset_window_height = jp.current_value_int();
        return true;
    }
    if (s == "oscilloscope.bufferset") {
        jp.next(gx_system::JsonParser::value_number);
        opt.mul_buffer = jp.current_value_int();
        return true;
    }
    if (s == "ui.skin_name") {
        jp.next(gx_system::JsonParser::value_string);
        opt.skin.name = jp.current_value();
        return true;
    }
    if (s == "ui.latency_nowarn") {
        jp.next(gx_system::JsonParser::value_number);
        opt.no_warn_latency = jp.current_value_int();
        return true;
    }
    if (s == "system.order_rack_h") {
        jp.next(gx_system::JsonParser::value_number);
        opt.system_order_rack_h = jp.current_value_int();
        return true;
    }
    if (s == "system.show_value") {
        jp.next(gx_system::JsonParser::value_number);
        opt.system_show_value = jp.current_value_int();
        return true;
    }
    if (s == "system.show_tooltips") {
        jp.next(gx_system::JsonParser::value_number);
        opt.system_show_tooltips = jp.current_value_int();
        return true;
    }
    if (s == "system.animations") {
        jp.next(gx_system::JsonParser::value_number);
        opt.system_animations = jp.current_value_int();
        return true;
    }
    if (s == "system.show_presets") {
        jp.next(gx_system::JsonParser::value_number);
        opt.system_show_presets = jp.current_value_int();
        return true;
    }
    if (s == "system.show_toolbar") {
        jp.next(gx_system::JsonParser::value_number);
        opt.system_show_toolbar = jp.current_value_int();
        return true;
    }
    if (s == "system.show_rack") {
        jp.next(gx_system::JsonParser::value_number);
        opt.system_show_rack = jp.current_value_int();
        return true;
    }
    if (s == "system.midiout") {
        jp.next(gx_system::JsonParser::value_number);
        opt.system_midiout = jp.current_value_int();
        return true;
    }

    return false;
}

static inline bool endswith(const std::string& s, int n, const char *t) {
    return s.compare(std::max<int>(0, s.size()-n), n, t) == 0;
}

static inline bool startswith(const std::string& s, int n, const char *t) {
    return s.compare(0, n, t) == 0;
}

void PresetIO::collectRackOrder(gx_engine::Parameter *p, gx_system::JsonParser &jp, UnitsCollector& u) {
    const std::string& s = p->id();
    if (startswith(s, 3, "ui.")) {
        if (jp.current_value_int()) {
            std::string ss = s.substr(3);
            u.set_visible(ss, true);
            u.set_show(ss, true);
        }
    } else if (endswith(s, 7, ".on_off")) {
        if (jp.current_value_int()) {
            u.set_show(s.substr(0, s.size()-7), true);
        }
    } else if (endswith(s, 9, ".position")) {
        u.set_position(s.substr(0, s.size()-9), jp.current_value_int());
    } else if (endswith(s, 3, ".pp")) {
        u.set_pp(s.substr(0, s.size()-3), (jp.current_value() == "pre" ? 1 : 0));
    }
}

void PresetIO::read_parameters(gx_system::JsonParser &jp, bool preset) {
    UnitsCollector u;
    jp.next(gx_system::JsonParser::begin_object);
    do {
        jp.next(gx_system::JsonParser::value_key);
        gx_engine::Parameter *p;
        if (!param.hasId(jp.current_value())) {
            if (convert_old(jp)) {
                continue;
            }
            bool warn;
            std::string s = replaced_id(jp.current_value(), warn);
            if (s.empty()) {
#ifndef NDEBUG
                warn = true;
#endif
                if (warn) {
                    gx_print_warning(
                        _("recall settings"),
                        _("unknown parameter: ")+jp.current_value());
                }
                jp.skip_object();
                continue;
            }
            p = &param[s];
        } else {
            p = &param[jp.current_value()];
        }
        if (!preset and p->isInPreset()) {
            gx_print_warning(
                _("recall settings"),
                _("preset-parameter ")+p->id()+_(" in settings"));
            jp.skip_object();
            continue;
        } else if (preset and !p->isInPreset()) {
            gx_print_warning(
                _("recall settings"),
                _("non preset-parameter ")+p->id()+_(" in preset"));
            jp.skip_object();
            continue;
        } else if (!p->isSavable()) {
            if (!p->isNoWarning()) {
                gx_print_warning(
                    _("recall settings"),
                    _("non saveable parameter ")+p->id()+_(" in settings"));
            }
            jp.skip_object();
            continue;
        }
        if (p->id() == "amp2.stage1.Pregain" || p->id() == "gxdistortion.drive") {
            gx_engine::FloatParameter& pf = p->getFloat();
            pf.rampJSON_value(jp);
        } else {
            p->readJSON_value(jp);
        }
        collectRackOrder(p, jp, u);
    } while (jp.peek() == gx_system::JsonParser::value_key);
    jp.next(gx_system::JsonParser::end_object);
    u.get_list(rack_units.mono, false, param);
    u.get_list(rack_units.stereo, true, param);
}

void PresetIO::write_parameters(gx_system::JsonWriter &w, bool preset) {
    w.begin_object(true);
#if 0
    int n = 0;
    int pp = 1;
    for (std::vector<std::string>::iterator j = mono_rack_units.begin(); j != mono_rack_units.end(); ++j) {
        if (*j == "ampstack") {
            n = 1;
            pp = 0;
        }
        w.write_key("ui."+*j);
        w.write(1);
        w.write_key(*j+".pp");
        w.write(pp);
        w.write_key(*j+".position");
        w.write(n);
        n++;
    }
#endif
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
        } else if (jp.current_value() == "jconv") { // for backwards compatibility
            dynamic_cast<gx_engine::JConvParameter*>(&param["jconv.convolver"])->readJSON_value(jp);
        } else if (jp.current_value() == "seq") { 
            dynamic_cast<gx_engine::SeqParameter*>(&param["seq.sequencer"])->readJSON_value(jp);
            //fprintf(stderr,"seq.sequencer found\n");
        } else if (jp.current_value() == "midi_controller") {
            if (use_midi) {
                m = new gx_engine::ControllerArray();
                m->readJSON(jp, param);
                if (has_midi) {
                    *has_midi = true;
                }
            } else {
                jp.skip_object();
            }
        } else {
            gx_print_warning(
                _("recall settings"),
                _("unknown preset section: ") + jp.current_value());
            jp.skip_object();
        }
    } while (jp.peek() == gx_system::JsonParser::value_key);
    jp.next(gx_system::JsonParser::end_object);
    fixup_parameters(head);
}

void PresetIO::commit_midi_feedback(gx_engine::Parameter *p) {
    const gx_engine::MidiController *pctrl;
    int nctl = mctrl.param2controller(*p, &pctrl);
    if (nctl > -1 && nctl < 128) {
        if (p->isFloat()) {
            const gx_engine::FloatParameter& pp = p->getFloat();
            int state = int(((pp.get_value() - pp.getLowerAsFloat()) /
                (pp.getUpperAsFloat() - pp.getLowerAsFloat())) * 127.0);
            mctrl.trigger_midi_feedback(nctl,state);
            if (pctrl->toggle_behaviour() != gx_engine::Parameter::toggle_type::OnOff)
                mctrl.set_last_midi_control_value(nctl, state);
        } else if (p->isInt()) {
            const gx_engine::IntParameter& pp = p->getInt();
            int state = int(((pp.get_value() - pp.getLowerAsFloat()) /
                (pp.getUpperAsFloat() - pp.getLowerAsFloat())) * 127.0);
            mctrl.trigger_midi_feedback(nctl,state);
            if (pctrl->toggle_behaviour() != gx_engine::Parameter::toggle_type::OnOff)
                mctrl.set_last_midi_control_value(nctl, state);
        } else if (p->isBool()) {
            const gx_engine::BoolParameter& pp = p->getBool();
            int state = int(pp.get_value() * 127);
            mctrl.trigger_midi_feedback(nctl,state);
            if (pctrl->toggle_behaviour() != gx_engine::Parameter::toggle_type::OnOff)
                mctrl.set_last_midi_control_value(nctl, state);
        }
    }
}

void PresetIO::commit_preset() {
    if (m) {
        mctrl.set_controller_array(*m);
    }
    for (gx_engine::paramlist::iterator i = plist.begin(); i != plist.end(); ++i) {
        (*i)->setJSON_value();
        commit_midi_feedback((*i));
    }
    if (m) {
        mctrl.update_from_controllers();
    }
    clear();
}

void PresetIO::write_intern(gx_system::JsonWriter &w, bool write_midi) {
    w.begin_object(true);
    w.write_key("engine");
    write_parameters(w, true);
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

StateIO::StateIO(gx_engine::MidiControllerList& mctrl, gx_engine::ParamMap& param,
                 gx_engine::MidiStandardControllers& mstdctr, gx_jack::GxJack& jack_,
                 gx_system::CmdlineOptions& opt_, UnitRacks& rack_units)
    : PresetIO(mctrl, param, opt_, rack_units),
      midi_std_control(mstdctr),
      jack(jack_) {
}

StateIO::~StateIO() {
}

void StateIO::read_state(gx_system::JsonParser &jp, const gx_system::SettingsFileHeader& head) {
    clear();
    for (gx_engine::ParamMap::iterator i = param.begin(); i != param.end(); ++i) {
        if (i->second->isSavable()) {
            i->second->stdJSON_value();
            plist.push_back(i->second);
        }
    }
    do {
        jp.next(gx_system::JsonParser::value_string);
        if (jp.current_value() == "settings") {
            read_parameters(jp, false);
        } else if (jp.current_value() == "current_preset") {
            read_intern(jp, 0, head);
        } else if (jp.current_value() == "midi_controller") {
            m = new gx_engine::ControllerArray();
            m->readJSON(jp, param);
        } else if (jp.current_value() == "midi_ctrl_names") {
            midi_std_control.readJSON(jp);
        } else if (jp.current_value() == "jack_connections") {
            jack.read_connections(jp);
        } else {
            gx_print_warning(
                _("recall settings"),
                _("unknown section: ") + jp.current_value());
            jp.skip_object();
        }
    } while (jp.peek() == gx_system::JsonParser::value_string);
}

void StateIO::commit_state() {
    if (!opt.get_cmdline_bank().empty()) {
        param["system.current_bank"].getString().get_json_value() = opt.get_cmdline_bank();
        param["system.current_preset"].getString().get_json_value() = opt.get_cmdline_preset();
    }
    commit_preset();
}

void StateIO::write_state(gx_system::JsonWriter &jw, bool no_preset) {
    jw.write("settings");
    write_parameters(jw, false);

    jw.write("midi_controller");
    mctrl.writeJSON(jw);

    jw.write("midi_ctrl_names");
    midi_std_control.writeJSON(jw);

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

PluginPresetList::PluginPresetList(const std::string& fname, gx_engine::ParamMap& pmap_,
                                   gx_engine::MidiControllerList& mctrl_)
    : filename(fname), pmap(pmap_), mctrl(mctrl_), is(), jp(&is) {
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
        gx_print_error(filename.c_str(), _("parse error"));
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
                if (!pmap.hasId(jp.current_value())) {
                    gx_print_warning(
                        _("recall plugin settings"),
                        _("unknown parameter: ")+jp.current_value());
                    jp.skip_object();
                    continue;
                }
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
        gx_print_error(filename.c_str(), _("parse error"));
        return false;
    }
    return true;
}

bool PluginPresetList::set(const Glib::ustring& name) {
    gx_engine::paramlist plist;
    if (!start()) {
        return false;
    }
    bool ret = false;
    try {
        while (jp.peek() != gx_system::JsonParser::end_array) {
            jp.next(gx_system::JsonParser::value_string);
            if (jp.current_value() != name) {
                jp.skip_object();
            } else {
                ret = true;
                jp.next(gx_system::JsonParser::begin_object);
                while (jp.peek() != gx_system::JsonParser::end_object) {
                    jp.next(gx_system::JsonParser::value_key);
                    if (pmap.hasId(jp.current_value())) {
                        gx_engine::Parameter& p = pmap[jp.current_value()];
                        p.readJSON_value(jp);
                        plist.push_back(&p);
                    }
                }
                jp.next(gx_system::JsonParser::end_object);
            }
        }
        jp.next(gx_system::JsonParser::end_array);
        jp.next(gx_system::JsonParser::end_token);
    } catch (gx_system::JsonException& e) {
        gx_print_error(filename.c_str(), _("parse error"));
        return false;
    }
    mctrl.remove_controlled_parameters(plist, 0);
    for (gx_engine::paramlist::iterator i = plist.begin(); i != plist.end(); ++i) {
        (*i)->setJSON_value();
    }
    return ret;
}

static const int GX_PLUGIN_VERSION = 1;

static inline bool compare_groups(const std::string& id, const char **groups) { //FIXME (is copy from gx_paramtable.cpp
    if (!groups) {
        return false;
    }
    for (const char **g = groups; *g; g += 2) {
        const char *p = *g;
        if ((*p) != '.') {
            continue;
        }
        p++;
        int n = strlen(p);
        if (strncmp(id.c_str(), p, n) == 0 && id[n] == '.') {
            return true;
        }
    }
    return false;
}

void PluginPresetList::write_values(gx_system::JsonWriter& jw, std::string id, const char **groups) {
    id += ".";
    string on_off = id + "on_off";
    string pp = id + "pp";
    std::string position = id + "position";
    jw.begin_object(true);
    for (gx_engine::ParamMap::iterator i = pmap.begin(); i != pmap.end(); ++i) {
        if (i->first.compare(0, id.size(), id) == 0 || compare_groups(i->first, groups)) {
            if (i->second->isInPreset() && i->second->isSavable()) {
                if (i->first != on_off && i->first != pp && i->first != position) {
                    i->second->writeJSON(jw);
                    jw.newline();
                }
            }
        }
    }
    jw.end_object(true);
}

void PluginPresetList::save(const Glib::ustring& name, const std::string& id, const char **groups) {
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
                    write_values(jw, id, groups);
                    jp.skip_object();
                } else {
                    jp.copy_object(jw);
                }
            }
        }
        if (!found) {
            jw.write(name);
            write_values(jw, id, groups);
        }
        jw.end_array(true);
        jw.close();
        os.close();
        if (!os.good()) {
            gx_print_error(_("save plugin preset"),
                           boost::format(_("couldn't write %1%")) % tmpfile);
            return;
        }
        int rc = rename(tmpfile.c_str(), filename.c_str());
        if (rc != 0) {
            gx_print_error(_("save plugin preset"),
                           boost::format(_("couldn't rename %1% to %2%"))
                           % tmpfile % filename);
        }
    } catch (gx_system::JsonException& e) {
        gx_print_error(filename.c_str(), _("parse error"));
    }
}

bool PluginPresetList::remove(const Glib::ustring& name) {
    bool ret = false;
    if (start()) {
        try {
            std::string tmpfile(filename + "_tmp");
            ofstream os(tmpfile.c_str());
            gx_system::JsonWriter jw(&os);
            jw.begin_array();
            jw.write("gx_plugin_version");
            jw.write(GX_PLUGIN_VERSION, true);
            while (jp.peek() != gx_system::JsonParser::end_array) {
                jp.next(gx_system::JsonParser::value_string);
                if (jp.current_value() == name) {
                    jp.skip_object();
                    ret = true;
                } else {
                    jw.write(jp.current_value());
                    jp.copy_object(jw);
                }
            }
            jp.next(gx_system::JsonParser::end_array);
            jp.next(gx_system::JsonParser::end_token);
            jw.end_array(true);
            jw.close();
            os.close();
            if (!os.good()) {
                gx_print_error(_("remove plugin preset"),
                               boost::format(_("couldn't write %1%")) % tmpfile);
                return false;
            }
            int rc = rename(tmpfile.c_str(), filename.c_str());
            if (rc != 0) {
                gx_print_error(_("remove plugin preset"),
                               boost::format(_("couldn't rename %1% to %2%"))
                               % tmpfile % filename);
                return false;
            }
        } catch (gx_system::JsonException& e) {
            gx_print_error(filename.c_str(), _("parse error"));
        }
        return ret;
    } else {
        return false;
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
                       gx_engine::MidiStandardControllers& mstdctr, gx_engine::MidiControllerList& mctrl_,
                       gx_engine::ModuleSequencer& seq_)
    : sigc::trackable(),
      GxSettingsBase(seq_),
      param(seq_.get_param()),
      preset_io(mctrl_, param, opt, rack_units),
      state_io(mctrl_, param, mstdctr, jack_, opt, rack_units),
      state_loaded(false),
      no_autosave(false),
      jack(jack_),
      mctrl(mctrl_),
      options(opt),
      preset_parameter(*param.reg_string("system.current_preset", "?", &current_name, "")),
      bank_parameter(*param.reg_string("system.current_bank", "?", &current_bank, "")),
      sync_name(""),
      set_preset(),
      get_sequencer_p(),
      sequencer_max(24),
      sequencer_pos(0) {
    set_io(&state_io, &preset_io);
    statefile.set_filename(make_default_state_filename());
    banks.parse(opt.get_preset_filepath(bank_list), opt.get_preset_dir(), opt.get_factory_dir(),
                scratchpad_name, scratchpad_file);
    instance = this;
    GxExit::get_instance().signal_exit().connect(
        sigc::mem_fun(*this, &GxSettings::exit_handler));
    jack.signal_client_change().connect(
        sigc::mem_fun(*this, &GxSettings::jack_client_changed));
    set_preset.connect(sigc::mem_fun(*this, &GxSettings::preset_sync_set));
    get_sequencer_p.connect(sigc::mem_fun(*this, &GxSettings::on_get_sequencer_pos));
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
        banks.check_save();
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
            throw GxFatalError(
                boost::format(_("no read/write access in guitarix config dir '%1%'"))
                % dir);
        }
        if (mkdir(dir.c_str(), 0777) != 0) {
            throw GxFatalError(
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

static inline std::vector<std::string>::iterator find_unit(std::vector<std::string>& r, const std::string& unit) {
    std::vector<std::string>::iterator i = r.begin();
    for (; i != r.end(); ++i) {
        if (unit == *i) {
            break;
        }
    }
    return i;
}

bool GxSettings::remove_rack_unit(const std::string& unit, bool stereo) {
    std::vector<std::string>& r = stereo ? rack_units.stereo : rack_units.mono;
    std::vector<std::string>::iterator i = find_unit(r, unit);
    if (i != r.end()) {
        r.erase(i);
        return true;
    }
    return false;
}

void GxSettings::insert_rack_unit(const std::string& unit, const std::string& before, bool stereo) {
    std::vector<std::string>& r = stereo ? rack_units.stereo : rack_units.mono;
    remove_rack_unit(unit, stereo);
    if (before.empty()) {
        r.push_back(unit);
    } else {
        r.insert(find_unit(r, before), unit);
    }
}

Glib::RefPtr<Gio::File> GxSettings::uri_to_name_filename(const Glib::ustring& uri, Glib::ustring& name, std::string& filename) {
    Glib::RefPtr<Gio::File> rem = Gio::File::create_for_uri(uri);
    filename = rem->get_basename();
    banks.strip_preset_postfix(filename);
    name = gx_system::decode_filename(filename);
    banks.make_valid_utf8(name);
    banks.make_bank_unique(name, &filename);
    return rem;
}

gx_system::PresetFile* GxSettings::bank_insert_uri(const Glib::ustring& uri, bool move, int position) {
    Glib::ustring name;
    std::string filename;
    Glib::RefPtr<Gio::File> rem = uri_to_name_filename(uri, name, filename);
    Glib::RefPtr<Gio::File> dest = Gio::File::create_for_path(filename);
    try {
        rem->copy(dest);
    } catch (Gio::Error& e) {
        gx_print_error(e.what().c_str(), _("can't copy to config dir"));
        return 0;
    }
    gx_system::PresetFile *f = new gx_system::PresetFile();
    if (f->open_file(name, filename, gx_system::PresetFile::PRESET_FILE, 0)) {
        banks.insert(f, position);
        presetlist_changed();
    } else {
        delete f;
        try {
            dest->remove();
        } catch (Gio::Error& e) {
            gx_print_error(e.what().c_str(), _("can't remove copied file!?"));
        }
        return 0;
    }
    if (move) {
        try {
            rem->remove();
        } catch (Gio::Error& e) {
            gx_print_error(e.what().c_str(), _("can't move; file has been copied"));
        }
    }
    return f;
}

gx_system::PresetFile* GxSettings::bank_insert_content(const Glib::ustring& uri, const std::string content, int position) {
    Glib::ustring name;
    std::string filename;
    uri_to_name_filename(uri, name, filename);
    Glib::RefPtr<Gio::File> dest = Gio::File::create_for_path(filename);
    try {
        Glib::RefPtr<Gio::FileOutputStream> s = dest->create_file();
        s->write(content);
        s->close();
    } catch (Gio::Error& e) {
        gx_print_error(e.what().c_str(), _("can't bank"));
        return 0;
    }
    gx_system::PresetFile *f = new gx_system::PresetFile();
    if (f->open_file(name, filename, gx_system::PresetFile::PRESET_FILE, 0)) {
        banks.insert(f, position);
        presetlist_changed();
    } else {
        delete f;
        try {
            dest->remove();
        } catch (Gio::Error& e) {
            gx_print_error(e.what().c_str(), _("can't remove copied file!?"));
        }
        return 0;
    }
    return f;
}

gx_system::PresetFile *GxSettings::bank_insert_new(const Glib::ustring& name) {
    Glib::ustring newname = name;
    std::string newfile;
    banks.make_bank_unique(newname, &newfile);
    gx_system::PresetFile *f = new gx_system::PresetFile();
    if (f->create_file(newname, newfile, gx_system::PresetFile::PRESET_FILE, 0)) {
        banks.insert(f);
        presetlist_changed();
        return f;
    } else {
        delete f;
        return 0;
    }
}

bool GxSettings::rename_bank(const Glib::ustring& oldname, Glib::ustring& newname) {
    std::string newfile;
    banks.make_bank_unique(newname, &newfile);
    return GxSettingsBase::rename_bank(oldname, newname, newfile);
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
        check_create_config_dir(opt.get_lv2_preset_dir());
        check_create_config_dir(opt.get_loop_dir());
        check_create_config_dir(opt.get_user_IR_dir());
        check_create_config_dir(opt.get_temp_dir());
        std::string fname = gx_jack::GxJack::get_default_instancename() + statename_postfix;
        if (access(Glib::build_filename(opt.get_old_user_dir(), fname).c_str(), R_OK) == 0) {
            copied_from_old = true;
            Glib::RefPtr<Gio::File> f = Gio::File::create_for_path(
                Glib::build_filename(opt.get_old_user_dir(), fname));
            try {
                f->copy(Gio::File::create_for_path(opt.get_user_filepath(fname)));
            } catch (Gio::Error& e) {
                gx_print_error(e.what().c_str(), _("can't copy to new config dir"));
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
                gx_print_error(e.what().c_str(), _("can't copy to new config preset dir"));
                oldpreset = "";
            }
        }
    } else {
        check_create_config_dir(opt.get_preset_dir());
        check_create_config_dir(opt.get_plugin_dir());
        check_create_config_dir(opt.get_pluginpreset_dir());
        check_create_config_dir(opt.get_lv2_preset_dir());
        check_create_config_dir(opt.get_loop_dir());
        check_create_config_dir(opt.get_user_IR_dir());
        check_create_config_dir(opt.get_temp_dir());
    }
    std::string fname = opt.get_preset_filepath(scratchpad_file);
    if (access(fname.c_str(), R_OK) != 0) {
        if (!gx_system::SettingsFileHeader::make_empty_settingsfile(fname)) {
            throw GxFatalError(
                boost::format(_("can't create file in '%1%' !!??")) % opt.get_preset_dir());
        }
        *need_new_preset = true;
    }
    fname = opt.get_preset_filepath(bank_list);
    if (access(fname.c_str(), R_OK) != 0) {
        ofstream f(fname.c_str());
        if (!f.good()) {
            throw GxFatalError(
                boost::format(_("can't create '%1%' in directory '%2%'"))
                % bank_list % opt.get_preset_dir());
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
#if 0
    /* This following code is commented out because
    **
    ** o its debatable which of state file or scratch preset should have
    **   priority in case both differ because 2 different instantiations
    **   accessed the same scratch preset but different statefiles.
    **
    ** o if the scratch preset has priority, the autosave function would
    **   have to save to statefile *and* scratch preset (in case of the
    **   current preset being a scratch preset).
    **
    ** As an aside: load_preset() would have to be changed to not save
    ** to the scratch preset before loading in the case that this code
    ** is activated.
    */
    if (setting_is_preset()) {
        gx_system::PresetFile *pf = banks.get_file(current_bank);
        if (pf && pf->get_type() == gx_system::PresetFile::PRESET_SCRATCH) {
            /* make sure we see the content of the scratchpad,
            ** not the state file (in case someone changed the
            ** scratchpad while working with a different state file)
            */
            load_preset(pf, current_name);
        }
    }
#endif
    if (setting_is_preset() && !banks.get_file(current_bank)) {
        gx_print_error(
            _("load state"),
            Glib::ustring::compose(
                _("bank '%1' not found (if it was a factory preset please check"
                  " if it's moved to the online repository)"), current_bank));
        current_bank.clear();
        current_name.clear();
        selection_changed();
    }
    state_loaded = true;
}

void GxSettings::add_plugin_preset_list(gx_preset::PluginPresetList& l,
                                        UnitPresetList &presetnames) {
    if (l.start()) {
        Glib::ustring name;
        bool is_set;
        while (l.next(name, &is_set)) {
            presetnames.push_back(PluginPresetEntry(name, is_set));
        }
    }
}

void GxSettings::plugin_preset_list_load(const PluginDef *pdef, UnitPresetList &presetnames) {
    PluginPresetList lv2sets(options.get_lv2_preset_filepath(pdef->id), param, mctrl);
    add_plugin_preset_list(lv2sets, presetnames);
    PluginPresetList user(options.get_pluginpreset_filepath(pdef->id, false), param, mctrl);
    add_plugin_preset_list(user, presetnames);
    presetnames.push_back(PluginPresetEntry("", false));
    PluginPresetList factory(options.get_pluginpreset_filepath(pdef->id, true), param, mctrl);
    add_plugin_preset_list(factory, presetnames);
}

void GxSettings::preset_sync_set() {
    PluginPresetList(options.get_pluginpreset_filepath("seq", false), param, mctrl).set(sync_name);
}

void GxSettings::on_get_sequencer_pos() {
    gx_system::atomic_set(&sequencer_pos,(int)param["seq.step"].getFloat().get_value());
}

void *GxSettings::sync_run() {
    while (true) {
        get_sequencer_p();
        usleep(50000);
        if (gx_system::atomic_get(sequencer_pos) == 0) {
            set_preset();
            break;
        }
    }    
    return NULL;
}

void *GxSettings::preset_sync_run(void *p) {
    struct sched_param  spar;
    spar.sched_priority = 0;
    pthread_setschedparam(pthread_self(), SCHED_IDLE, &spar);
    (reinterpret_cast< GxSettings*>(p))->sync_run();
    pthread_exit(NULL);
    return NULL;
}

void GxSettings::plugin_preset_list_sync_set(const PluginDef *pdef, bool factory, const Glib::ustring& name) {
    if(strcmp(pdef->id,"seq")==0) {
        sync_name = name;
        pthread_t pthr;
        gx_system::atomic_set(&sequencer_max,(int)param["seq.asequences"].getFloat().get_value()-1);
        if (pthread_create(&pthr, NULL, preset_sync_run, reinterpret_cast<void*>(this))) {
            gx_print_error("GxSettings sync", _("can't create thread"));
        }
    }
}

void GxSettings::plugin_preset_list_set(const PluginDef *pdef, bool factory, const Glib::ustring& name) {
    if (!PluginPresetList(options.get_pluginpreset_filepath(pdef->id, factory), param, mctrl).set(name))
        PluginPresetList(options.get_lv2_preset_filepath(pdef->id), param, mctrl).set(name);
}

void GxSettings::plugin_preset_list_save(const PluginDef *pdef, const Glib::ustring& name) {
    PluginPresetList(options.get_pluginpreset_filepath(pdef->id, false), param, mctrl).save(name, pdef->id, pdef->groups);
}

void GxSettings::plugin_preset_list_remove(const PluginDef *pdef, const Glib::ustring& name) {
    // remove loop files when delete a plugin preset
    if(strcmp(pdef->id,"dubber")==0) {
        std::string pPath = options.get_loop_dir();
        pPath += name;
        std::remove((pPath + "1.wav").c_str());
        std::remove((pPath + "2.wav").c_str());
        std::remove((pPath + "3.wav").c_str());
        std::remove((pPath + "4.wav").c_str());
    }
    if (!PluginPresetList(options.get_pluginpreset_filepath(pdef->id, false), param, mctrl).remove(name))
        PluginPresetList(options.get_lv2_preset_filepath(pdef->id), param, mctrl).remove(name);
}


/* ----------------------------------------------------------------*/
} /* end of gx_preset namespace */

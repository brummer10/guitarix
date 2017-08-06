/*
 * Copyright (C) 2013 Andreas Degert
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

#include "engine.h"

/****************************************************************
 ** class TunerSwitcher
 */

static const int no_note = 1000;
static const int bad_note = 1002;

inline bool is_no_note(float n) {
    return std::abs(n - no_note) < 1;
}

TunerSwitcher::TunerSwitcher(gx_preset::GxSettings& settings_, gx_engine::GxEngine& engine_)
    : settings(settings_),
      engine(engine_),
      display(),
      set_state(),
      selection_done(),
      switcher_conn(),
      timeout_conn(),
      current_note(),
      state(normal_mode),
      old_engine_state(),
      new_engine_state(),
      old_tuner_active(),
      new_tuner_active(),
      last_bank_idx(),
      last_preset_idx() {
}

bool TunerSwitcher::display_bank_key(int idx) {
    last_bank_idx = settings.banks.size() - idx - 1;
    Glib::ustring bank = settings.banks.get_name(last_bank_idx);
    if (bank.empty()) {
	display("--", "--");
	return false;
    }
    display(bank, "");
    return true;
}

bool TunerSwitcher::display_preset_key(int idx) {
    last_preset_idx = idx;
    Glib::ustring bank = settings.banks.get_name(last_bank_idx);
    if (bank.empty()) {
	display("??", gx_system::to_string(idx+1));
	return false;
    }
    gx_system::PresetFile *f = settings.banks.get_file(bank);
    if (idx >= f->size()) {
	display(bank, gx_system::to_string(idx+1));
	return false;
    }
    display(bank, f->get_name(idx));
    return true;
}

void TunerSwitcher::try_load_preset() {
    switch (last_bank_idx) {
    case mute_on:    new_engine_state = gx_engine::kEngineOff;    break;
    case mute_off:   new_engine_state = gx_engine::kEngineOn;     break;
    case bypass_on:  new_engine_state = gx_engine::kEngineBypass; break;
    case bypass_off: new_engine_state = gx_engine::kEngineOn;     break;
    case tuner_on:   new_tuner_active = true;  break;
    case tuner_off:  new_tuner_active = false; break;
    default:
	Glib::ustring bank = settings.banks.get_name(last_bank_idx);
	if (!bank.empty()) {
	    gx_system::PresetFile *f = settings.banks.get_file(bank);
	    if (last_preset_idx < f->size()) {
		Glib::ustring preset = f->get_name(last_preset_idx);
		if (preset != settings.get_current_name() || bank != settings.get_current_bank()) {
		    settings.load_preset(f, preset);
		}
	    }
	}
	break;
    }
}

void TunerSwitcher::change_state(SwitcherState newstate) {
    if (state == newstate) {
	return;
    }
    state = newstate;
    set_state(state);
}

bool TunerSwitcher::on_note_timeout() {
    if (-24 <= current_note && current_note < -10) {
	change_state(listening);
	display_bank_key(current_note - (-24));
    } else if (current_note >= -10 && current_note <= 7) {
	if (display_preset_key(current_note - (-10))) {
	    change_state(wait_stop);
	} else {
	    change_state(listening);
	}
    } else if (current_note == -25) {
	if (old_engine_state != gx_engine::kEngineOff) {
	    display("", _("MUTE"));
	    last_bank_idx = mute_on;
	} else {
	    display("", _("UNMUTE"));
	    last_bank_idx = mute_off;
	}
	change_state(wait_stop);
    } else if (current_note == -26) {
	if (old_engine_state != gx_engine::kEngineBypass) {
	    display("", _("BYPASS"));
	    last_bank_idx = bypass_on;
	} else {
	    display("", _("BYPASS OFF"));
	    last_bank_idx = bypass_off;
	}
	change_state(wait_stop);
    } else if (current_note < 26) {
	if (!old_tuner_active) {
	    display("", _("TUNER ON"));
	    last_bank_idx = tuner_on;
	} else {
	    display("", _("TUNER OFF"));
	    last_bank_idx = tuner_off;
	}
	change_state(wait_stop);
    }
    return false;
}

bool TunerSwitcher::on_state_timeout() {
    if (state == wait_start) {
	change_state(listening);
	current_note = no_note;
	if (settings.setting_is_preset()) {
	    last_bank_idx = settings.banks.get_index(settings.get_current_bank());
	    last_preset_idx = settings.get_current_bank_file()->get_index(settings.get_current_name());
	} else {
	    last_bank_idx = last_preset_idx = 0; //FIXME
	}
    } else {
	assert(state == wait_stop);
	try_load_preset();
	deactivate();
    }
    return false;
}

void TunerSwitcher::on_tuner_freq_changed() {
    const float precision = 0.3;
    float note = engine.tuner.get_note();
    if (state == wait_start) {
	if (is_no_note(note)) {
	    if (!timeout_conn.connected()) {
		current_note = no_note;
		timeout_conn = Glib::signal_timeout().connect(
		    sigc::mem_fun(this, &TunerSwitcher::on_state_timeout),
		    40);
	    }
	} else {
	    timeout_conn.disconnect();
	}
	return;
    }
    if (std::abs(current_note - note) < precision) {
	return;
    }
    if (state == wait_stop) {
	if (is_no_note(note)) {
	    if (!is_no_note(current_note)) {
		timeout_conn.disconnect();
	    }
	    if (!timeout_conn.connected()) {
		current_note = no_note;
		timeout_conn = Glib::signal_timeout().connect(
		    sigc::mem_fun(this, &TunerSwitcher::on_state_timeout),
		    40);
	    }
	    return;
	}
    }
    timeout_conn.disconnect();
    float n = round(note);
    if (std::abs(note - n) < precision) {
	current_note = n;
	if (!is_no_note(current_note)) {
	    timeout_conn = Glib::signal_timeout().connect(
		sigc::mem_fun(this, &TunerSwitcher::on_note_timeout),
		40);
	}
    } else {
	current_note = bad_note;
    }
}

void TunerSwitcher::activate(bool tuner_active) {
    if (get_active()) {
	return;
    }
    bool running = engine.tuner.plugin.get_on_off();
    engine.tuner.used_for_switching(true);
    state = normal_mode;
    change_state(wait_start);
    new_engine_state = old_engine_state = engine.get_state();
    engine.set_state(gx_engine::kEngineOff);
    new_tuner_active = old_tuner_active = tuner_active;
    switcher_conn = engine.tuner.signal_freq_changed().connect(
	sigc::mem_fun(this, &TunerSwitcher::on_tuner_freq_changed));
    if (running) {
	on_tuner_freq_changed();
    }
}

void TunerSwitcher::deactivate() {
    if (!get_active()) {
	return;
    }
    switcher_conn.disconnect();
    timeout_conn.disconnect();
    engine.tuner.used_for_switching(false);
    change_state(normal_mode);
    if (new_tuner_active && new_engine_state == gx_engine::kEngineOn) {
	new_engine_state = gx_engine::kEngineBypass;
    }
    engine.set_state(new_engine_state);
    selection_done(new_tuner_active);
}

void TunerSwitcher::toggle(bool tuner_active) {
    if (get_active()) {
	deactivate();
    } else {
	if (tuner_active) {
	    if (engine.get_state() == gx_engine::kEngineBypass) {
		engine.set_state(gx_engine::kEngineOn);
	    }
	    selection_done(false);
	} else {
	    activate(false);
	}
    }
}

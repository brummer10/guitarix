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

#pragma once

#ifndef SRC_HEADERS_TUNERSWITCHER_H_
#define SRC_HEADERS_TUNERSWITCHER_H_

/****************************************************************
 ** class TunerSwitcher
 */

class TunerSwitcher: public sigc::trackable {
public:
    enum SwitcherState { normal_mode, wait_start, listening, wait_stop };
private:
    enum SwitcherActions {
	mute_on    = -1,
	mute_off   = -2,
	bypass_on  = -3,
	bypass_off = -4,
	tuner_on   = -5,
	tuner_off  = -6,
    };
    gx_preset::GxSettings& settings;
    gx_engine::GxEngine& engine;
    sigc::signal<void,const Glib::ustring&,const Glib::ustring&> display;
    sigc::signal<void,SwitcherState> set_state;
    sigc::signal<void, bool> selection_done;
    sigc::connection switcher_conn;
    sigc::connection timeout_conn;
    int current_note;
    SwitcherState state;
    gx_engine::GxEngineState old_engine_state;
    gx_engine::GxEngineState new_engine_state;
    bool old_tuner_active;
    bool new_tuner_active;
    int last_bank_idx;
    int last_preset_idx;
private:
    bool on_note_timeout();
    bool on_state_timeout();
    void on_tuner_freq_changed();
    void try_load_preset();
    bool display_bank_key(int idx);
    bool display_preset_key(int idx);
    void change_state(SwitcherState newstate);
public:
    TunerSwitcher(gx_preset::GxSettings& settings, gx_engine::GxEngine& engine);
    bool get_active() { return switcher_conn.connected(); }
    void activate(bool tuner_active);
    void deactivate();
    void toggle(bool tuner_active);
    sigc::signal<void,const Glib::ustring&,const Glib::ustring&>& signal_display() { return display; }
    sigc::signal<void,SwitcherState>& signal_set_state() { return set_state; }
    sigc::signal<void, bool>& signal_selection_done() { return selection_done; }
};

#endif  // SRC_HEADERS_TUNERSWITCHER_H_

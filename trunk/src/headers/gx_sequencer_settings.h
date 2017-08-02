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
 */

#pragma once

#ifndef SRC_HEADERS_GX_SEQUENCER_SETTINGS_H_
#define SRC_HEADERS_GX_SEQUENCER_SETTINGS_H_


#include <string>

namespace gx_seq {

/****************************************************************
 ** Sequencer Parameter Window
 */

class SEQWindow: public sigc::trackable {
 private:
    gx_engine::GxMachineBase& machine;
    Glib::RefPtr<gx_gui::GxBuilder> builder;
    gx_engine::SeqParameter *tomp;
    gx_engine::SeqParameter *kickp;
    gx_engine::SeqParameter *snarep;
    gx_engine::SeqParameter *hatp;
    Gtk::Window* gtk_window;
    Gtk::ScrolledWindow *sequencerbox;

    // signal functions and widget pointers
    void on_window_hide();

    Gxw::Regler *bpm_seq;
    Gxw::Regler *tom_gain;
    Gxw::Regler *kick_gain;
    Gxw::Regler *snare_gain;
    Gxw::Regler *hat_gain;
    Gxw::Regler *tact_seq;
    Gxw::Regler *seq_gain;

    Gtk::ToggleButton *tom_seq[24];
    Gtk::ToggleButton *kick_seq[24];
    Gtk::ToggleButton *snare_seq[24];
    Gtk::ToggleButton *hat_seq[24];

    Gtk::Label *tom, *kick, *snare, *hat, *bpm, *gain;

    bool on_key_press_event(GdkEventKey *event);
    void tom_changed(const gx_engine::GxSeqSettings* tomp);
    void kick_changed(const gx_engine::GxSeqSettings* kickp);
    void snare_changed(const gx_engine::GxSeqSettings* snarep);
    void hat_changed(const gx_engine::GxSeqSettings* hatp);
    void make_state(gx_engine::GxSeqSettings& seqc, std::vector<int> seq);
    void on_seq_button_clicked(int i);

    void init_connect();
    SEQWindow(const Glib::RefPtr<gx_gui::GxBuilder>& builder, gx_engine::SeqParameter *tomp_,
         gx_engine::SeqParameter *kickp_, gx_engine::SeqParameter *snarep_,
         gx_engine::SeqParameter *hatp_, gx_engine::GxMachineBase& machine_);
    ~SEQWindow();

public:
    void reload_and_show();
    static SEQWindow *create(const std::string& unit_id, gx_engine::GxMachineBase& machine);
};

} /* end of gx_seq namespace*/
#endif  // SRC_HEADERS_GX_SEQUENCER_SETTINGS_H_

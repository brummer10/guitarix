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

    //  widget pointers
    Gtk::Window* gtk_window;
    Gtk::HBox* tom_box;
    Gtk::HBox* kick_box;
    Gtk::HBox* snare_box;
    Gtk::HBox* hat_box;
    Gxw::Regler *seq_pos;

    // signal functions
    void on_window_hide();
    bool get_sequencer_pos(Gxw::Regler * regler, const std::string id);
    bool on_key_press_event(GdkEventKey *event);
    void seq_changed(const gx_engine::GxSeqSettings* seqc, Gtk::HBox *box);
    void make_state(gx_engine::GxSeqSettings& seqc, std::vector<int> seq);
    void on_seq_button_clicked(Gtk::HBox *box, gx_engine::SeqParameter *p);

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

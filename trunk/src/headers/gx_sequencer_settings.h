/*
 * Copyright (C) 2017 Hermann Meyer, Andreas Degert
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

class Drums {
 public:
    gx_engine::SeqParameter *p;
    Gtk::HBox* box;
    Drums(gx_engine::SeqParameter *pa)
    : p(pa) {}
    ~Drums() {}
};

/****************************************************************
 ** Sequencer Parameter Window
 */

class SEQWindow: public sigc::trackable {
 private:
    gx_engine::GxMachineBase& machine;
    Glib::RefPtr<gx_gui::GxBuilder> builder;
    std::vector<Drums> drums;
    Drums tom;
    Drums tom1;
    Drums tom2;
    Drums kick;
    Drums snare;
    Drums hat;
    bool is_active;

    //  widget pointers
    Gtk::Window* gtk_window;
    Gtk::Viewport *vp;
    Gtk::HBox *preset_button;
    Gxw::Switch *add_button;
    Gxw::Regler *seq_pos;
    Gxw::Regler *seq_count;
    Gxw::Regler *seq_tact;
    Gxw::Switch *next_preset;
    Gxw::Switch *previus_preset;
    Gxw::Switch *set_step;
    Gxw::Switch *set_fstep;

    // signal functions
    void on_window_hide();
    void on_preset_popup_clicked();
    bool get_sequencer_pos(Gxw::Regler * regler, const std::string id);
    bool on_key_press_event(GdkEventKey *event);
    void seq_changed(const gx_engine::GxSeqSettings* seqc, Gtk::HBox *box);
    void make_state(gx_engine::GxSeqSettings& seqc, std::vector<int> seq);
    void on_seq_button_clicked(Gtk::HBox *box, gx_engine::SeqParameter *p);
    void on_seq_button_clicked_set(Gtk::HBox *box, gx_engine::SeqParameter *p);
    void on_sec_length_changed(bool update);
    void on_sec_tact_changed();
    void append_seq_block(Gtk::HBox * box, gx_engine::SeqParameter *p, int r, int r_save);
    void remove_seq_block(Gtk::HBox * box, int r);
    void reset_control(Glib::ustring id, float value);
    int append_sequence(const gx_engine::GxSeqSettings* seqc, gx_engine::SeqParameter *p, std::vector<int> *sequence);
    void make_preset_button(Gtk::HBox *box);
    void scroll_playhead(float value);
    void append_plugin_preset(Glib::ustring name);
    void append_plugin_preset_set(Glib::ustring name);
    void on_preset_add_clicked();
    void on_next_preset();
    void on_next_preset_set();
    void on_previus_preset();
    void on_previus_preset_set();
    void on_set_step();
    void on_set_fstep();
    void init_connect();
    void init_sequences(gx_engine::SeqParameter *p, Gtk::HBox* _box);
    SEQWindow(const Glib::RefPtr<gx_gui::GxBuilder>& builder, gx_engine::SeqParameter *tomp_,
         gx_engine::SeqParameter *tomp1_, gx_engine::SeqParameter *tomp2_,
         gx_engine::SeqParameter *kickp_, gx_engine::SeqParameter *snarep_,
         gx_engine::SeqParameter *hatp_, gx_engine::GxMachineBase& machine_);
    ~SEQWindow();

public:
    void reload_and_show();
    static SEQWindow *create(const std::string& unit_id, gx_engine::GxMachineBase& machine);
};

} /* end of gx_seq namespace*/
#endif  // SRC_HEADERS_GX_SEQUENCER_SETTINGS_H_

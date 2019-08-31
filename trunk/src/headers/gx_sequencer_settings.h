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
    Gtk::Box* box;
    Drums(gx_engine::SeqParameter *pa)
    : p(pa) {}
    ~Drums() {}
};

class UPresetListStore: public Gtk::ListStore {
 public:
    class UPresetListColumns : public Gtk::TreeModel::ColumnRecord {
     public:
        Gtk::TreeModelColumn<Glib::ustring> name;
        UPresetListColumns() { add(name); }
    } col;
 private:
    UPresetListStore(): Gtk::ListStore(), col() {
        set_column_types(col);
    }
 public:
    static Glib::RefPtr<UPresetListStore> create() {
        return Glib::RefPtr<UPresetListStore>(new UPresetListStore);
    }
};

/****************************************************************
 ** PluginPresetConnectWindow
 */

class PluginPresetConnectWindow: public Gtk::Window {
 private:
    Glib::RefPtr<UPresetListStore> upresetliststore;
    gx_engine::GxMachineBase& machine;
    Gtk::TreeView *treeview;
    Gtk::Button *connectbutton;
    void on_connect();
    void on_selection_changed();
    virtual bool on_key_press_event(GdkEventKey *event);
    static PluginPresetConnectWindow* create_from_builder(
      BaseObjectType* cobject, Glib::RefPtr<gx_gui::GxBuilder> bld,
      gx_engine::GxMachineBase& machine);
    PluginPresetConnectWindow(BaseObjectType* cobject,
      Glib::RefPtr<gx_gui::GxBuilder> bld, gx_engine::GxMachineBase& machine);
 public:
    ~PluginPresetConnectWindow();
    static PluginPresetConnectWindow *create(gx_engine::GxMachineBase& machine);
    void run();
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
    Gtk::Label *preset_label;
    Gtk::Box *preset_button;
    Gxw::Switch *add_button;
    Gxw::Regler *seq_pos;
    Gxw::Regler *seq_count;
    Gxw::Regler *seq_tact;
    Gxw::Switch *next_preset;
    Gxw::Switch *previus_preset;
    Gxw::Switch *set_step;
    Gxw::Switch *set_fstep;
    Gxw::Switch *set_sync;
    Gxw::Switch *reset_step;
    Gtk::Label *step_label;
    Gxw::ValueDisplay *step_value;

    // signal functions
    void on_window_hide();
    void on_preset_popup_clicked();
    void on_selection_done(Gtk::Menu *presetMenu);
    bool get_sequencer_pos(Gxw::Regler * regler, const std::string id);
    bool on_key_press_event(GdkEventKey *event);
    void check_preset_label();
    void seq_changed(const gx_engine::GxSeqSettings* seqc, Gtk::Box *box);
    void make_state(gx_engine::GxSeqSettings& seqc, std::vector<int> seq);
    void on_seq_button_clicked(Gtk::Box *box, gx_engine::SeqParameter *p);
    void on_seq_button_clicked_set(Gtk::Box *box, gx_engine::SeqParameter *p);
    void on_sec_length_changed(bool update);
    void on_sec_tact_changed();
    void append_seq_block(Gtk::Box * box, gx_engine::SeqParameter *p, int r, int r_save);
    void remove_seq_block(Gtk::Box * box, int r);
    void reset_control(Glib::ustring id, float value);
    int append_sequence(const gx_engine::GxSeqSettings* seqc, gx_engine::SeqParameter *p, std::vector<int> *sequence);
    void make_preset_button(Gtk::Box *box);
    void scroll_playhead(float value);
    void append_plugin_preset(Glib::ustring name);
    void append_plugin_preset_set(Glib::ustring name);
    void on_preset_add_clicked();
    void on_next_preset();
    void on_next_preset_set();
    void on_previus_preset();
    void on_previus_preset_set();
    void connect_midi();
    void on_set_step();
    void on_set_fstep();
    void on_sync_stepper();
    void on_reset_stepper();
    void init_connect();
    void init_sequences(gx_engine::SeqParameter *p, Gtk::Box* _box);
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

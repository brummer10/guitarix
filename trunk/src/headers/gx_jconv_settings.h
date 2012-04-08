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
 *
 *  This is the JConv settings handler class used by guitarix
 *  There can only be one instance at all time. To get a pointer
 *  to the unique instance, simply call
 *
 *  GxJConvSettings* jcset = GxJConvSettings::instance();
 *
 *  throughout the entire program.
 *
 *  This class belongs to the gx_jconv namespace
 *
 * --------------------------------------------------------------------------
 */

#pragma once

#ifndef SRC_HEADERS_GX_JCONV_SETTINGS_H_
#define SRC_HEADERS_GX_JCONV_SETTINGS_H_

#include <gxwmm/gainline.h>
#include <gxwmm/radiobutton.h>
#include <gxwmm/iredit.h>

#include <string>

namespace gx_jconv {

/****************************************************************
 ** Convolver Parameter Window
 */

class IRWindow: public sigc::trackable {
 private:
    Glib::RefPtr<gx_gui::GxBuilder> builder;
    Glib::ustring filename;
    double ms; // samples per millisecond
    float *audio_buffer;
    unsigned int audio_size;
    int audio_chan;
    gx_engine::ConvolverAdapter& convolver;
    Gtk::Window* gtk_window;
    sigc::connection autogain_conn;
    static IRWindow *instance;

    // helper functions
    int set_val(Gxw::ControlParameter *sample_display, Gxw::ControlParameter *ms_display,
                double value, int fs);
    inline int get_ms(Gxw::ControlParameter *w) {
         return static_cast<int>(round(w->cp_get_value()*ms));
    }
    void file_changed(Glib::ustring filename, int rate, int length,
                      int channels, Glib::ustring format);
    static Gainline gain0;
    bool load_data(Glib::ustring filename, int offset = 0, int delay = 0, int length = 0, const Gainline& gain = gain0);
    void load_state();
    bool save_state();
    void set_GainCor();
    double calc_normalized_gain(int offset, int length, const Gainline& points);
    void destroy_self();

    // signal functions and widget pointers
    void on_window_hide();

    Gxw::IREdit *wIredit;
    void on_delay_changed(int delay, int fs);
    void on_offset_changed(int offset, int fs);
    void on_length_changed(int length, int fs);
    void on_max_scale_reached(bool v);
    void on_min_scale_reached(bool v);

    Gxw::RadioButton *wLeft, *wRight, *wSum;
    void on_left();
    void on_right();
    void on_sum();

    Gxw::RadioButton *wLinear, *wLog;
    void on_linear();

    Gxw::ValueDisplay *wDelay, *wDelay_ms, *wOffset, *wOffset_ms, *wLength, *wLength_ms;
    void on_m_delay_changed();
    void on_ms_delay_changed();
    void on_m_offset_changed();
    void on_ms_offset_changed();
    void on_m_length_changed();
    void on_ms_length_changed();

    Gxw::Regler *wDelay_delta;
    Glib::ustring on_delay_delta_format_value(double v);

    Gtk::Button *wHome, *wJump_zoom_mark, *wIncr, *wDecr;
    void on_home();
    void on_jump_zoom_mark();
    void on_decr();
    void on_incr();

    Gtk::Button *wReset, *wOpen;
    void on_reset_clicked();
    void on_open();

    Gtk::Button *wOk, *wApply, *wCancel;
    void on_apply_button_clicked();
    void on_cancel_button_clicked();
    void on_ok_button_clicked();
    
    Gtk::ToggleButton *wGain_correction;
    void on_gain_button_toggled();

    Gtk::Label *wSamples, *wSampleRate, *wFormat, *wFilename;
    Gtk::Widget *wChannelbox;

    void on_help_clicked();
    Gtk::Window *wHelp;

    void on_preset_popup_clicked(const gx_preset::GxSettings& gx_settings);
    void on_enumerate();
    bool on_key_press_event(GdkEventKey *event);

    void init_connect(const gx_preset::GxSettings& gx_settings);
    IRWindow(const Glib::RefPtr<gx_gui::GxBuilder>& builder, gx_engine::ConvolverAdapter &convolver,
	     Glib::RefPtr<Gdk::Pixbuf> icon, const gx_preset::GxSettings& gx_settings,
	     Glib::RefPtr<Gtk::AccelGroup> accels);
    ~IRWindow();

    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
     public:
        ModelColumns() { add(displayname); add(filename); }
        Gtk::TreeModelColumn<Glib::ustring> displayname;
	Gtk::TreeModelColumn<std::string> filename;
    };
    Gtk::ComboBox *wcombo;
    ModelColumns columns;
    Glib::RefPtr<Gtk::TreeStore> model;
    std::string current_combo_dir;
    void on_combo_changed();
public:
    void reload_and_show();
    static IRWindow *create(gx_ui::GxUI& ui, gx_engine::ConvolverAdapter& convolver,
			    Glib::RefPtr<Gdk::Pixbuf> icon, const gx_preset::GxSettings& settings,
			    Glib::RefPtr<Gtk::AccelGroup> accels);
    friend class JConvPopup;
};

} /* end of gx_jconv namespace*/
#endif  // SRC_HEADERS_GX_JCONV_SETTINGS_H_

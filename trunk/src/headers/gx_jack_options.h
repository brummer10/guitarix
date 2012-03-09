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
 *    This file is part of the guitarix GUI main class
 * 
 * ----------------------------------------------------------------------------
 */

/* ------- This is the GUI namespace ------- */

#pragma once

#ifndef SRC_HEADERS_GX_JACK_OPTIONS_H_
#define SRC_HEADERS_GX_JACK_OPTIONS_H_
namespace gx_gui {
    
class GxBuilder;
/****************************************************************
 ** class SelectJackControlPgm
 */

class SelectJackControlPgm: public Gtk::Window {
private:
    Gtk::Label  *description;
    Gtk::Entry  *customstarter;
    Gtk::ComboBox *startercombo;
    Gtk::CheckButton *dontask;
    gx_engine::IntParameter& starter;
    gx_engine::StringParameter& starter_cmd;
    gx_engine::SwitchParameter& ask;
    sigc::signal<void> close;
    void on_starter_changed();
    void on_ok_button();
    void on_cancel_button();
    bool on_delete_event(GdkEventAny* event);
    bool on_key_press_event(GdkEventKey *event);
    static SelectJackControlPgm* create_from_builder(BaseObjectType* cobject, Glib::RefPtr<GxBuilder> bld, gx_engine::ParamMap& pmap) {
	return new SelectJackControlPgm(cobject, bld, pmap);
    }
    SelectJackControlPgm(BaseObjectType* cobject, Glib::RefPtr<GxBuilder> bld, gx_engine::ParamMap& pmap);
public:
    ~SelectJackControlPgm();
    static SelectJackControlPgm* create(gx_ui::GxUI *ui, gx_system::CmdlineOptions& opt, gx_engine::ParamMap& pmap);
    sigc::signal<void>& signal_close() { return close; }
};

/* jack client and port mapping functions */
bool gx_start_jack_dialog(Glib::RefPtr<Gdk::Pixbuf> gw_ib);
} // end namespace gx_gui
#endif // SRC_HEADERS_GX_JACK_OPTIONS_H_

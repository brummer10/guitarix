/*
 * Copyright (C) 2012 Hermann Meyer, Andreas Degert, Pete Shorthose, Steve Poskitt
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

#ifndef SRC_HEADERS_WIDGET_H_
#define SRC_HEADERS_WIDGET_H_

#include <gtkmm.h>
#include <gxwmm.h>
#include "gxredeye.h"
#include "../config.h" // for GX_STYLE_DIR
// LV2UI stuff
#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"

class Widget : public Gtk::HBox
{
private:
  void on_value_changed(uint32_t port_index);
  void change_skin(Glib::ustring plug_name);
  void make_controller_box(Gtk::VBox *box,
                           Gxw::Regler *regler,
                           Glib::ustring label,
                           float min, float max,
                           float digits, float value,
                           PortIndex port_name,
                           Glib::ustring plug_name);
  
  void make_switch_box(Gtk::Box *box,
                                 Gxw::Switch *toggle,
                                 Glib::ustring label,
                                 float min, float max,
                                 float digits, float value,
                                 PortIndex port_name,
                                 Glib::ustring plug_name);

  void make_logo(Gtk::Box *box,Glib::ustring label, bool start ) ;

  bool _draw(const Cairo::RefPtr<Cairo::Context> &cr);
  void set_value(uint32_t port_index,
                 uint32_t format,
                 const void * buffer);
public:

  // public Lv2 communication stuff
  LV2UI_Controller controller;
  LV2UI_Write_Function write_function;
  static void set_value_static(uint32_t port_index,
                               uint32_t buffer_size,
                               uint32_t format,
                               const void * buffer, Widget *self)
  {
    self->set_value(port_index,format,buffer);
  }

  Widget(Glib::ustring plug_name);
  ~Widget();

protected:
  Gtk::VBox      m_vbox_;
  Gtk::VBox      m_vbox1_;
  Gtk::VBox      m_vbox2_;
  Gtk::VBox      m_vbox3_;
  Gtk::VBox      m_vbox4_;
  Gtk::VBox      m_vbox5_;
  Gtk::VBox      m_vbox6_;
  Gtk::VBox      m_vbox7_;
  Gtk::VBox      m_vbox8_;
  Gtk::VBox      m_vbox9_;
  Gtk::VBox      m_vbox10_;
  Gtk::VBox      m_vbox11_;
  Gtk::VBox      m_vbox12_;
  Gtk::VBox      m_vbox13_;
  Gtk::VBox      m_vbox14_;
  Gtk::VBox      m_vbox21_;


Gtk::VBox      m_vbox15_;
Gtk::VBox      m_vbox16_;
Gtk::VBox      m_vbox17_;
Gtk::VBox      m_vbox18_;
Gtk::VBox      m_vbox19_;
Gtk::VBox      m_vbox20_;

  Gtk::HBox      m_hbox_;
  Gtk::HBox      m_hbox1_;
  Gtk::HBox      m_hbox2_;
  Gtk::HBox      m_hbox3_;
  Gtk::HBox      m_hbox4_;
  Gtk::HBox      m_hbox5_;

  Gtk::VBox      m_vbox;
  Gtk::VBox      m_vbox1;
  Gtk::VBox      m_vbox2;
  Gtk::VBox      m_vbox3;
  Gtk::VBox      m_vbox4;
  Gtk::VBox      m_vbox5;

  Gxw::PaintBox      m_paintbox;
  Gtk::HBox          m_hbox;
  Gxw::BigKnob       m_bigknob;
  Gxw::BigKnob       m_bigknob1;
  Gxw::BigKnob       m_bigknob2;
  Gxw::BigKnob       m_bigknob3;
  Gxw::BigKnob       m_bigknob4;

  Gxw::Switch	     m_switch;
  Gxw::Switch	     m_switch1;
  Gxw::Switch	     m_switch2;

  // stores port values we're currently at.
  float              gain;
  float              tone;
  float              volume;
  float              feedback;
  float              speed;
  float              intensity;
  float		sinewave ;
  float		vibe ;
  bool		vibrochump ;
};

#endif //SRC_HEADERS_WIDGET_H_

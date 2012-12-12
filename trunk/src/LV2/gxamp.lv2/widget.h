/*
 * Copyright (C) 2012 Hermann Meyer, Andreas Degert, Pete Shorthose
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
#include "gxamp.h"

// LV2UI stuff
#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"

class Widget : public Gtk::VBox
{
private:
  bool _expose_event(GdkEventExpose *event);
  void set_value(uint32_t port_index,
                 uint32_t format,
                 const void * buffer);
public:
  LV2_Atom_Forge forge;
  LV2_URID_Map* map;
  GXPluginURIs   uris;

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

  Widget();
  ~Widget();

protected:
  Gtk::VBox      m_vbox_;
  Gtk::HBox      m_hbox_;
  Gtk::HBox      m_hbox1_;
  Gtk::VBox      m_vbox2_;
  Gtk::VBox      m_vbox;
  Gtk::VBox      m_vbox1;
  Gtk::VBox      m_vbox2;
  Gtk::VBox      m_vbox3;
  Gtk::VBox      m_vbox4;
  Gtk::VBox      m_vbox5;
  Gtk::VBox      m_vbox6;
  Gtk::VBox      m_vbox7;
  Gtk::VBox      m_vbox8;
  Gtk::VBox      m_vboxa;
  Gtk::VBox      m_vboxb;
  Gtk::VBox      m_vboxc;
  Gtk::VBox      m_vboxd;
  Gtk::VBox      m_vboxe,m_vboxee;
  Gtk::VBox      m_vboxf,m_vboxff;
  Gtk::VBox      m_vboxg,m_vboxgg;
  Gtk::VBox      m_vboxh,m_vboxhh,m_vboxhi;
  Gtk::VBox      m_vboxi,m_vboxii,m_vboxih;
  Gxw::PaintBox  m_paintbox;
  //Gtk::HBox      m_paintbox;
  Gtk::HBox      m_hbox;
  Gxw::BigKnob   m_bigknob;
  Gxw::BigKnob   m_bigknob1;
  Gxw::BigKnob   m_bigknob2;
  Gxw::BigKnob   m_bigknob3;
  Gxw::SmallKnob   m_smallknob1;
  Gxw::SmallKnob   m_smallknob2;
  Gxw::SmallKnob   m_smallknob3;
  Gxw::SmallKnobR m_smallknob4;
  Gxw::SmallKnobR m_smallknob5;
  void on_knob_value_changed();
  void on_knob1_value_changed();
  void on_knob2_value_changed();
  void on_knob3_value_changed();
  void on_knob4_value_changed();
  void on_knob5_value_changed();
  void on_knob6_value_changed();
  void on_knob7_value_changed();
  void on_knob8_value_changed();
  // stores port values we're currently at.
  float          mastergain;
  float          pregain;
  float          wet_dry;
  float          drive;
  float          mid;
  float          bass;
  float          treble;
  float          clevel;
  float          alevel;
};

#endif //SRC_HEADERS_WIDGET_H_

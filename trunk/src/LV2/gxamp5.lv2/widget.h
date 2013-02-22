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
#include "gxamp5.h"
#include "../config.h" // for GX_STYLE_DIR
// LV2UI stuff
#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"

class Widget : public Gtk::HBox
{
private:
  void make_controller_box(Gtk::VBox *box,
                           Gxw::Regler *regler,
                           Glib::ustring label,
                           float min, float max,
                           float digits, float value,
                           Glib::ustring plug_name);
  bool _expose_event(GdkEventExpose *event);
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
  Gtk::HBox      m_hbox_;
  Gtk::HBox      m_hbox1_;
  Gtk::VBox      m_vbox;
  Gtk::VBox      m_vbox1;
  Gtk::VBox      m_vbox2;
  Gtk::VBox      m_vbox3;
  Gtk::VBox      m_vbox4;
  Gtk::VBox      m_vbox5;
  Gtk::VBox      m_vbox6;
  Gtk::VBox      m_vbox7;
  Gtk::VBox      m_vbox8;
  Gtk::VBox      m_vboxhh;
  Gtk::VBox      m_vboxii;

  Gxw::PaintBox  m_paintbox;
  Gtk::HBox      m_hbox;
  Gxw::BigKnob   m_bigknob;		// Master Gain
  Gxw::SmallKnobR   m_bigknob1;		// Pregain
  Gxw::SmallKnobR  m_bigknob2;		// Distortion
  Gxw::SmallKnobR   m_bigknob3;		// Drive
  Gxw::SmallKnob   m_smallknob1;	// Mid
  Gxw::SmallKnob   m_smallknob2;	// Bass
  Gxw::SmallKnob   m_smallknob3;	// Treble
  Gxw::SmallKnobR m_smallknob4;		//Presence
  Gxw::SmallKnobR m_smallknob5;		// Cabinet
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

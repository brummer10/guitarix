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
#include "gx_graphiceq.h"
#include "../config.h" // for GX_STYLE_DIR
// LV2UI stuff
#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"

class Widget : public Gtk::HBox
{
private:
  Gtk::Widget* get_controller_by_port(uint32_t port_index);

  void refresh_meter_level(int meter,float new_level);

  void on_value_changed(uint32_t port_index);

  void make_controller(Glib::ustring label,
                           float min, float max,
                           float digits,
                           PortIndex port_name,
                           bool show_value);

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

  Widget(Glib::ustring plugname);
  ~Widget();

protected:
  Glib::ustring     plug_name;
  Gtk::HBox         m_hbox[13];
  Gtk::VBox         m_vbox[12];
  Gtk::Label        m_label[11];

  Gxw::LevelSlider  m_levelslider[11];
  Gxw::FastMeter    fastmeter[11];
  Gxw::PaintBox     m_paintbox[12];
};

#endif //SRC_HEADERS_WIDGET_H_

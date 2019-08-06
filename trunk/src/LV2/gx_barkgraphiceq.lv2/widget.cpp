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


#include "widget.h"

#include "stdio.h"
#include <iostream>

#include "bark_freq_grid.h"

#define max(x, y) (((x) > (y)) ? (x) : (y))

/*    @get controller by port
 *  this function is used by make_selector() make_controller()
 *  set_value() and on_value_changed()
 *  so controller widgets needs only here asined to a port, 
 *  and all functions which need acess to the controller widget pointer 
 *  can receive them by port number
 */

Gtk::Widget* Widget::get_controller_by_port(uint32_t port_index)
{
  switch ((PortIndex)port_index )
  {
    case G1:
      return &m_levelslider[0];
    case G2:
      return &m_levelslider[1];
    case G3:
      return &m_levelslider[2];
    case G4:
      return &m_levelslider[3];
    case G5:
      return &m_levelslider[4];
    case G6:
      return &m_levelslider[5];
    case G7:
      return &m_levelslider[6];
    case G8:
      return &m_levelslider[7];
    case G9:
      return &m_levelslider[8];
    case G10:
      return &m_levelslider[9];
    case G11:
      return &m_levelslider[10];
	case G12:
      return &m_levelslider[11];
	case G13:
      return &m_levelslider[12];
	case G14:
      return &m_levelslider[13];
	case G15:
	  return &m_levelslider[14];
	case G16:
	  return &m_levelslider[15];
	case G17:
	  return &m_levelslider[16];
	case G18:
	  return &m_levelslider[17];
	case G19:
	  return &m_levelslider[18];
	case G20:
	  return &m_levelslider[19];
	case G21:
	  return &m_levelslider[20];
	case G22:
	  return &m_levelslider[21];
	case G23:
	  return &m_levelslider[22];
	case G24:
	  return &m_levelslider[23];

    default:
      return NULL;
  } 
}

Widget::Widget(Glib::ustring plugname):
plug_name(plugname)
{
  // set labels
	for(unsigned int i = 0; i < BARK_NUMBER_OF_BANDS; i++)
	{	
		char buffer[100];
		sprintf (buffer, "%d", bark_center_freqs[i]);
		m_label[i].set_text(buffer);
	}

  // make controllers
	double max_gain = 4;
	double min_gain = -40;
	double step = 0.01;
	make_controller( "", min_gain, max_gain, step, G1, false);
	make_controller( "", min_gain, max_gain, step, G2, false);
	make_controller( "", min_gain, max_gain, step, G3, false);
	make_controller( "", min_gain, max_gain, step, G4, false);
	make_controller( "", min_gain, max_gain, step, G5, false);
	make_controller( "", min_gain, max_gain, step, G6, false);
	make_controller( "", min_gain, max_gain, step, G7, false);
	make_controller( "", min_gain, max_gain, step, G8, false);
	make_controller( "", min_gain, max_gain, step, G9, false);
	make_controller( "", min_gain, max_gain, step, G10, false);
	make_controller( "", min_gain, max_gain, step, G11, false);
	make_controller( "", min_gain, max_gain, step, G12, false);
	make_controller( "", min_gain, max_gain, step, G13, false);
	make_controller( "", min_gain, max_gain, step, G14, false);
	make_controller( "", min_gain, max_gain, step, G15, false);
	make_controller( "", min_gain, max_gain, step, G16, false);
	make_controller( "", min_gain, max_gain, step, G17, false);
	make_controller( "", min_gain, max_gain, step, G18, false);
	make_controller( "", min_gain, max_gain, step, G19, false);
	make_controller( "", min_gain, max_gain, step, G20, false);
	make_controller( "", min_gain, max_gain, step, G21, false);
	make_controller( "", min_gain, max_gain, step, G22, false);
	make_controller( "", min_gain, max_gain, step, G23, false);
	make_controller( "", min_gain, max_gain, step, G24, false);

  // set propertys for the main paintbox holding the skin
  m_paintbox[0].set_border_width(25);
  m_paintbox[0].set_spacing(10);
  m_paintbox[0].set_homogeneous(false);
  m_paintbox[0].set_name(plug_name);
  m_paintbox[0].property_paint_func() = "gxhead_expose";
  add(m_paintbox[0]);
  // set a vertical box in the paintbox
  m_paintbox[0].pack_start(m_vbox[24]);
  m_vbox[24].pack_start(m_hbox[25],Gtk::PACK_EXPAND_WIDGET);
  m_vbox[24].pack_start(m_hbox[24],Gtk::PACK_SHRINK);
  m_hbox[24].set_homogeneous(true);
  m_hbox[24].set_border_width(25);
  // put boxed controllers into controller box
  for (uint32_t i = 0;i<24;i++) {
    fastmeter[i].set_hold_count(12);
    fastmeter[i].set_property("dimen",2);
    fastmeter[i].set_property("type",0);
    m_hbox[i].set_border_width(6);
    m_paintbox[i+1].property_paint_func() = "simple_level_meter_expose";
    m_paintbox[i+1].set_name(plug_name);
    m_paintbox[i+1].set_border_width(2);
    m_paintbox[i+1].pack_start(fastmeter[i]);
    m_paintbox[i+1].pack_start(m_levelslider[i]);
    m_hbox[i].pack_start(m_paintbox[i+1]);
    m_label[i].set_name("amplabel");
	//Change font little bit
	Pango::FontDescription fdsc("Arial");
	fdsc.set_size(8000);
	m_label[i].override_font(fdsc);
	m_vbox[i].add(m_label[i]);
    m_vbox[i].add(m_hbox[i]);
    m_hbox[24].pack_start(m_vbox[i],Gtk::PACK_SHRINK);
  }

  set_app_paintable(true);
  show_all();
}

Widget::~Widget()
{

}

// create stackboxes with controllers for port name
void Widget::make_controller( Glib::ustring label,
                                 float min, float max,
                                 float digits,
                                 PortIndex port_name,
                                 bool show_value)
{
  Gxw::Regler *regler = static_cast<Gxw::Regler*>(
                                    get_controller_by_port(port_name));
  if (regler)
  {

    regler->cp_configure("LEVELSLIDER", label, min, max, digits);
    regler->set_show_value(show_value);
    regler->set_name(plug_name);
    regler->signal_value_changed().connect(sigc::bind(sigc::mem_fun(
           *this, &Widget::on_value_changed), port_name));
  }
}

// receive controller value changes from host and set them to controller
void Widget::set_value(uint32_t port_index,
                       uint32_t format,
                       const void * buffer)
{
  if ( format == 0 )
  {
    Gxw::Regler *regler = static_cast<Gxw::Regler*>(
                                    get_controller_by_port(port_index));
    float value = *static_cast<const float*>(buffer);
    if (regler) regler->cp_set_value(value);
    if (port_index == V1) refresh_meter_level(0,value);
    else if (port_index == V2) refresh_meter_level(1,value);
    else if (port_index == V3) refresh_meter_level(2,value);
    else if (port_index == V4) refresh_meter_level(3,value);
    else if (port_index == V5) refresh_meter_level(4,value);
    else if (port_index == V6) refresh_meter_level(5,value);
    else if (port_index == V7) refresh_meter_level(6,value);
    else if (port_index == V8) refresh_meter_level(7,value);
    else if (port_index == V9) refresh_meter_level(8,value);
    else if (port_index == V10) refresh_meter_level(9,value);
    else if (port_index == V11) refresh_meter_level(10,value);
	else if (port_index == V12) refresh_meter_level(11,value);
	else if (port_index == V13) refresh_meter_level(12,value);
	else if (port_index == V14) refresh_meter_level(13,value);
	else if (port_index == V15) refresh_meter_level(14,value);
	else if (port_index == V16) refresh_meter_level(15,value);
	else if (port_index == V17) refresh_meter_level(16,value);
	else if (port_index == V18) refresh_meter_level(17,value);
	else if (port_index == V19) refresh_meter_level(18,value);
	else if (port_index == V20) refresh_meter_level(19,value);
	else if (port_index == V21) refresh_meter_level(20,value);
	else if (port_index == V22) refresh_meter_level(21,value);
	else if (port_index == V23) refresh_meter_level(22,value);
	else if (port_index == V24) refresh_meter_level(23,value);
  }
}

// write (UI) controller value changes to the host->engine
void Widget::on_value_changed(uint32_t port_index)
{
  Gxw::Regler *regler = static_cast<Gxw::Regler*>(
                                    get_controller_by_port(port_index));
  if (regler)
  {
    float value = regler->cp_get_value();
    write_function(controller, port_index, sizeof(float), 0,
                                    static_cast<const void*>(&value));
  }
}

void Widget::refresh_meter_level(int m, float new_level) {
  fastmeter[m].set_by_power(new_level);
}

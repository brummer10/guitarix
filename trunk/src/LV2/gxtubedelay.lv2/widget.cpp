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

#include <iostream>

Widget::Widget(Glib::ustring plug_name)
{
  // set propertys for the main paintbox holding the skin
  m_paintbox.set_border_width(20);
  m_paintbox.set_spacing(0);
  m_paintbox.set_homogeneous(false);
  m_paintbox.set_name(plug_name);
    m_paintbox.set_size_request(480,260);
  m_paintbox.property_paint_func() = "amp_skin_expose";
  add(m_paintbox);

  // box for the controllers
  m_hbox1_.set_spacing(0);
  m_hbox1_.set_border_width(0);
  m_hbox1_.set_homogeneous(false);
  m_hbox1_.set_size_request(340,30);

  // box for the controllers
  m_hbox_.set_spacing(10);
  m_hbox_.set_border_width(40);
  m_hbox_.set_homogeneous(false);
  // set a vertical box in the paintbox
  m_paintbox.pack_start(m_vbox_);
  // spacer
  m_vbox_.pack_start(m_hbox1_,Gtk::PACK_SHRINK);
  // and controller box on top
  m_vbox_.pack_start(m_hbox_,Gtk::PACK_SHRINK);

  // create all controllers
  make_controller_box(&m_vbox, &m_bigknob, "delay", 0, 2000, 0, gain, plug_name);
  m_bigknob.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob_value_changed));
  
  make_controller_box(&m_vbox1, &m_bigknob1, "feedback", -60, 0, 1, feedback, plug_name);
  m_bigknob1.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob1_value_changed));

  make_controller_box(&m_vbox2, &m_bigknob2, "level", -60, 0, 0.1, level, plug_name);
  m_bigknob2.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob2_value_changed));
  

  make_controller_box(&m_vbox3, &m_bigknob3, "gain", -60, 6, 0.1, gain, plug_name);
  m_bigknob3.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob3_value_changed));
  
  // put boxed controllers into controller box
  m_hbox_.pack_start(m_vbox);
  m_hbox_.pack_start(m_vbox1);
  m_hbox_.pack_start(m_vbox2);
  m_hbox_.pack_start(m_vbox3);
  

  // connect expose handler as resize handler
  m_paintbox.signal_expose_event().connect(
    sigc::mem_fun(this, &Widget::_expose_event), true);

  set_app_paintable(true);
  show_all();
}

Widget::~Widget()
{

}
// create stackboxes with controllers from gxw
void Widget::make_controller_box(Gtk::VBox *box,
                                 Gxw::Regler *regler,
                                 Glib::ustring label,
                                 float min, float max,
                                 float digits, float value,
                                 Glib::ustring plug_name)
{
  Gtk::Label* pr = new Gtk::Label(label, 0);
  pr->set_name("amplabel");
  /*Glib::ustring  label_image = GX_STYLE_DIR;
  label_image += "/";
  label_image += label;
  label_image += "-label.png";
  Gtk::Image *pr = new Gtk::Image(label_image);*/

  Gtk::VBox* b1 = new Gtk::VBox();
  box->pack_start( *Gtk::manage(b1), Gtk::PACK_EXPAND_PADDING);
  //box->pack_start( *Gtk::manage(pr),Gtk::PACK_SHRINK);
  regler->cp_configure("KNOB", label, min, max, digits);
  regler->set_show_value(false);
  regler->cp_set_value(value);
  regler->set_name(plug_name);
  box->pack_start(*regler,Gtk::PACK_SHRINK);
  box->pack_start( *Gtk::manage(pr),Gtk::PACK_SHRINK);
  Gtk::VBox* b2 = new Gtk::VBox();
  box->pack_start( *Gtk::manage(b2), Gtk::PACK_EXPAND_PADDING);
}
// set borderwith for paintbox when widget resize
// to hold controllers in place
bool Widget::_expose_event(GdkEventExpose *event)
{
  int x, y, width, height, depth;
  m_paintbox.get_window()->get_geometry(x, y, width, height, depth);
  //double_t height = m_paintbox.get_window()->get_height();
  m_paintbox.set_border_width(height/20);
  return false;
}
// receive controller value changes from host
void Widget::set_value(uint32_t port_index,
                       uint32_t format,
                       const void * buffer)
{
  if ( format == 0 )
    {
      float value =  *(float *)buffer;
      switch ((PortIndex)port_index )
        {
        case DELAY:
          delay = value;
          m_bigknob.cp_set_value(delay);
          break;
        case FEEDBACK:
          feedback = value;
          m_bigknob1.cp_set_value(feedback);
          break;
        case LEVEL:
          level = value;
          m_bigknob2.cp_set_value(level);
          break;
        case GAIN:
          gain = value;
          m_bigknob3.cp_set_value(gain);
          break;
        default:
          break;
        }
    }
}
// write value changes to the host->engine
void Widget::on_knob_value_changed()
{
  delay = m_bigknob.get_value();
//  std::cout << "delay = " << delay << std::endl;
  write_function(controller, (PortIndex)DELAY,
                 sizeof(float), 0, (const void*)&delay);
}

void Widget::on_knob1_value_changed()
{
  feedback = m_bigknob1.get_value();
//  std::cout << "feedback = " << feedback << std::endl;
  write_function(controller, (PortIndex)FEEDBACK,
                 sizeof(float), 0, (const void*)&feedback);
}
void Widget::on_knob2_value_changed()
{
  level = m_bigknob2.get_value();
//  std::cout << "level = " << level << std::endl;
  write_function(controller, (PortIndex)LEVEL,
                 sizeof(float), 0, (const void*)&level);
}
void Widget::on_knob3_value_changed()
{
  gain = m_bigknob3.get_value();
//  std::cout << "gain = " << gain << std::endl;
  write_function(controller, (PortIndex)GAIN,
                 sizeof(float), 0, (const void*)&gain);
}


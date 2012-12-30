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


#include "widget.h"

#include <iostream>

Widget::Widget(Glib::ustring plug_name)
{
  // init values set by host
  /*mastergain = -15.0;
  pregain    = -15.0;
  wet_dry    = 20.0;
  drive      = 0.25;
  mid        = 0.5;
  bass       = 0.5;
  treble     = 0.5;
  clevel     = 1.0;
  alevel     = 1.0;*/

  // init the gxwmm library
  Gxw::init();

  // set propertys for the main paintbox holding the skin
  m_paintbox.set_border_width(30);
  m_paintbox.set_spacing(12);
  m_paintbox.set_homogeneous(false);
  m_paintbox.set_name(plug_name);
  m_paintbox.property_paint_func() = "amp_skin_expose";
  add(m_paintbox);
  // box for the controllers
  m_hbox_.set_spacing(12);
  m_hbox_.set_homogeneous(false);
  // this box set space for the upper part of the skin
  m_hbox1_.set_spacing(12);
  m_hbox1_.set_border_width(65);
  // set a vertical box in the paintbox
  m_paintbox.pack_start(m_vbox_);
  // and put space box on top
  m_vbox_.pack_start(m_hbox1_, Gtk::PACK_EXPAND_PADDING);
  // and controller box on bottem
  m_vbox_.pack_start(m_hbox_,Gtk::PACK_SHRINK);

  // create all controllers
  make_controller_box(&m_vbox, &m_bigknob, "mastergain", -20, 20, 0.1, mastergain, plug_name);
  m_bigknob.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob_value_changed));

  make_controller_box(&m_vbox1, &m_bigknob1, "pregain", -20, 20, 0.1, pregain, plug_name);
  m_bigknob1.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob1_value_changed));

  make_controller_box(&m_vbox2, &m_bigknob2, "distortion", 1, 100, 1, wet_dry, plug_name);
  m_bigknob2.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob2_value_changed));

  make_controller_box(&m_vbox3, &m_bigknob3, "drive", 0.01, 1, 0.01, drive, plug_name);
  m_bigknob3.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob3_value_changed));

  make_controller_box(&m_vbox4, &m_smallknob1, "mid", 0, 1, 0.01, mid, plug_name);
  m_smallknob1.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob4_value_changed));

  make_controller_box(&m_vbox5, &m_smallknob2, "bass", 0, 1, 0.01, bass, plug_name);
  m_smallknob2.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob5_value_changed));

  make_controller_box(&m_vbox6, &m_smallknob3, "treble", 0, 1, 0.01, treble, plug_name);
  m_smallknob3.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob6_value_changed));

  make_controller_box(&m_vbox7, &m_smallknob4, "cabinet", 1, 20, 1, clevel, plug_name);
  m_smallknob4.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob7_value_changed));

  make_controller_box(&m_vbox8, &m_smallknob5, "presence", 1, 20, 1, alevel, plug_name);
  m_smallknob5.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob8_value_changed));

  // put boxed controllers into controller box
  m_hbox_.pack_start(m_vboxhh);
  m_hbox_.pack_start(m_vbox1);
  m_hbox_.pack_start(m_vbox2);
  m_hbox_.pack_start(m_vbox3);
  m_hbox_.pack_start(m_vbox7);
  m_hbox_.pack_start(m_vbox8);
  m_hbox_.pack_start(m_vbox);
  // etxra box for the boxed tonestack controllers
  m_hbox.set_border_width(8);
  m_hbox.pack_start(m_vbox5);
  m_hbox.pack_start(m_vbox4);
  m_hbox.pack_start(m_vbox6);
  m_hbox.pack_start(m_vboxii);
  m_hbox.set_spacing(5);
  // add tonestack controller box to main controller box
  m_hbox_.pack_start(m_hbox);

  // connect expose handler as resize handler
  m_paintbox.signal_expose_event().connect(
    sigc::mem_fun(this, &Widget::_expose_event), true);

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
  //Gtk::Label* pr = new Gtk::Label(label, 0);
  //pr->set_name("amplabel");
  Glib::ustring  label_image = GX_STYLE_DIR;
  label_image += "/";
  label_image += label;
  label_image += "-label.png";
  Gtk::Image *pr = new Gtk::Image(label_image);

  Gtk::VBox* b1 = new Gtk::VBox();
  box->pack_start( *Gtk::manage(b1), Gtk::PACK_EXPAND_PADDING);
  box->pack_start( *Gtk::manage(pr),Gtk::PACK_SHRINK);
  regler->cp_configure("KNOB", label, min, max, digits);
  regler->set_show_value(false);
  regler->cp_set_value(value);
  regler->set_name(plug_name);
  box->pack_start(*regler,Gtk::PACK_SHRINK);
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
  m_paintbox.set_border_width(height/10);
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
        case AMP_MASTERGAIN:
          mastergain = value;
          m_bigknob.cp_set_value(mastergain);
          break;
        case AMP_PREGAIN:
          pregain = value;
          m_bigknob1.cp_set_value(pregain);
          break;
        case AMP_WET_DRY:
          wet_dry = value;
          m_bigknob2.cp_set_value(wet_dry);
          break;
        case AMP_DRIVE:
          drive = value;
          m_bigknob3.cp_set_value(drive);
          break;
        case MID:
          mid = value;
          m_smallknob1.cp_set_value(mid);
          break;
        case BASS:
          bass = value;
          m_smallknob2.cp_set_value(bass);
          break;
        case TREBLE:
          treble = value;
          m_smallknob3.cp_set_value(treble);
          break;
        case CLevel:
          clevel = value;
          m_smallknob4.cp_set_value(clevel);
          break;
        case ALevel:
          alevel = value;
          m_smallknob5.cp_set_value(alevel);
          break;
        case AMP_CONTROL:
          break;
        case AMP_NOTIFY:
          break;
        case AMP_OUTPUT:
          break;
        case AMP_INPUT:
          break;
        case AMP_OUTPUT1:
          break;
        case AMP_INPUT1:
          break;
        }
    }
}
// write value changes to the host->engine
void Widget::on_knob_value_changed()
{
  mastergain = m_bigknob.get_value();
  //std::cout << "mastergain = " << mastergain << std::endl;
  write_function( controller, 0, sizeof(float), 0, (const void*)&mastergain);
}

void Widget::on_knob1_value_changed()
{
  pregain = m_bigknob1.get_value();
  //std::cout << "pregain = " << pregain << std::endl;
  write_function( controller, 1, sizeof(float), 0, (const void*)&pregain);
}

void Widget::on_knob2_value_changed()
{
  wet_dry = m_bigknob2.get_value();
  //std::cout << "wet_dry = " << wet_dry << std::endl;
  write_function( controller, 2, sizeof(float), 0, (const void*)&wet_dry);
}

void Widget::on_knob3_value_changed()
{
  drive = m_bigknob3.get_value();
  //std::cout << "drive = " << drive << std::endl;
  write_function( controller, 3, sizeof(float), 0, (const void*)&drive);
}

void Widget::on_knob4_value_changed()
{
  mid = m_smallknob1.get_value();
  //std::cout << "mid = " << mid << std::endl;
  write_function( controller, 4, sizeof(float), 0, (const void*)&mid);
}

void Widget::on_knob5_value_changed()
{
  bass = m_smallknob2.get_value();
  //std::cout << "bass = " << bass << std::endl;
  write_function( controller, 5, sizeof(float), 0, (const void*)&bass);
}

void Widget::on_knob6_value_changed()
{
  treble = m_smallknob3.get_value();
  //std::cout << "treble = " << treble << std::endl;
  write_function( controller, 6, sizeof(float), 0, (const void*)&treble);
}

void Widget::on_knob7_value_changed()
{
  clevel = m_smallknob4.get_value();
  //std::cout << "treble = " << clevel << std::endl;
  write_function( controller, 7, sizeof(float), 0, (const void*)&clevel);
}

void Widget::on_knob8_value_changed()
{
  alevel = m_smallknob5.get_value();
  //std::cout << "treble = " << alevel << std::endl;
  write_function( controller, 8, sizeof(float), 0, (const void*)&alevel);
}

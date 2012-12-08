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

Widget::Widget()
{
  /*mastergain = -15.0;
  pregain = -15.0;
  wet_dry = 20.0;
  drive = 0.25;
  mid = 0.5;
  bass= 0.5;
  treble= 0.5;*/
  Gxw::init();
  m_bigknob.cp_configure("KNOB", "MASTER", -20, 20, 0.1);
  m_bigknob.cp_set_value(mastergain);
  m_bigknob.set_show_value(false);
  m_bigknob.signal_value_changed().connect(sigc::mem_fun(*this,
    &Widget::on_knob_value_changed));
  
  m_bigknob1.cp_configure("KNOB", "PRE", -20, 20, 0.1);
  m_bigknob1.cp_set_value(pregain);
  m_bigknob1.set_show_value(false);
  m_bigknob1.signal_value_changed().connect(sigc::mem_fun(*this,
    &Widget::on_knob1_value_changed));
    
  m_bigknob2.cp_configure("KNOB", "WETDRY", 1, 100, 1);
  m_bigknob2.cp_set_value(wet_dry);
  m_bigknob2.set_show_value(false);
  m_bigknob2.signal_value_changed().connect(sigc::mem_fun(*this,
    &Widget::on_knob2_value_changed));
    
  m_bigknob3.cp_configure("KNOB", "DRIVE", 0.01, 1, 0.01);
  m_bigknob3.cp_set_value(drive);
  m_bigknob3.set_show_value(false);
  m_bigknob3.signal_value_changed().connect(sigc::mem_fun(*this,
    &Widget::on_knob3_value_changed));
     
  m_smallknob1.cp_configure("KNOB", "mid", 0, 1, 0.01);
  m_smallknob1.cp_set_value(mid);
  m_smallknob1.set_show_value(false);
  m_smallknob1.signal_value_changed().connect(sigc::mem_fun(*this,
    &Widget::on_knob4_value_changed));
     
  m_smallknob2.cp_configure("KNOB", "bass", 0, 1, 0.01);
  m_smallknob2.cp_set_value(bass);
  m_smallknob2.set_show_value(false);
  m_smallknob2.signal_value_changed().connect(sigc::mem_fun(*this,
    &Widget::on_knob5_value_changed));

  m_smallknob3.cp_configure("KNOB", "treble", 0, 1, 0.01);
  m_smallknob3.cp_set_value(treble);
  m_smallknob3.set_show_value(false);
  m_smallknob3.signal_value_changed().connect(sigc::mem_fun(*this,
    &Widget::on_knob6_value_changed));
  
  Gxw::PaintBox *m_paintbox = new Gxw::PaintBox(Gtk::ORIENTATION_HORIZONTAL,12,false);
  m_paintbox->show();
  m_paintbox->set_border_width(18);
  m_paintbox->set_spacing(22);
  m_paintbox->set_homogeneous(false);
  m_paintbox->property_paint_func() = "gxhead_expose";
  m_hbox.property_paint_func() = "RackBox_expose";
  m_hbox.set_border_width(8);
  pack_start(*Gtk::manage(m_paintbox));
  m_vbox.pack_start(m_vboxa, Gtk::PACK_EXPAND_PADDING);
  m_vbox.pack_start( *Gtk::manage(new Gtk::Label("Master Gain", 0)),Gtk::PACK_SHRINK);
  m_vbox.pack_start(m_bigknob,Gtk::PACK_SHRINK);
  m_vbox1.pack_start(m_vboxb, Gtk::PACK_EXPAND_PADDING);
  m_vbox1.pack_start( *Gtk::manage(new Gtk::Label("Pre Gain", 0)),Gtk::PACK_SHRINK);
  m_vbox1.pack_start( m_bigknob1,Gtk::PACK_SHRINK);
  m_vbox2.pack_start(m_vboxc, Gtk::PACK_EXPAND_PADDING);
  m_vbox2.pack_start( *Gtk::manage(new Gtk::Label("Distortion", 0)),Gtk::PACK_SHRINK);
  m_vbox2.pack_start( m_bigknob2,Gtk::PACK_SHRINK);
  m_vbox3.pack_start(m_vboxd, Gtk::PACK_EXPAND_PADDING); 
  m_vbox3.pack_start( *Gtk::manage(new Gtk::Label("Drive", 0)),Gtk::PACK_SHRINK);
  m_vbox3.pack_start( m_bigknob3,Gtk::PACK_SHRINK);
  
  m_vbox4.pack_start(m_vboxe, Gtk::PACK_EXPAND_PADDING);
  m_vbox4.pack_start( *Gtk::manage(new Gtk::Label("mid", 0)),Gtk::PACK_SHRINK);
  m_vbox4.pack_start(m_smallknob1,Gtk::PACK_SHRINK);
  m_vbox4.pack_start(m_vboxee, Gtk::PACK_EXPAND_PADDING);
  
  m_vbox5.pack_start(m_vboxf, Gtk::PACK_EXPAND_PADDING);
  m_vbox5.pack_start( *Gtk::manage(new Gtk::Label("bass", 0)),Gtk::PACK_SHRINK);
  m_vbox5.pack_start(m_smallknob2,Gtk::PACK_SHRINK);
  m_vbox5.pack_start(m_vboxff, Gtk::PACK_EXPAND_PADDING);
   
  m_vbox6.pack_start(m_vboxg, Gtk::PACK_EXPAND_PADDING);
  m_vbox6.pack_start( *Gtk::manage(new Gtk::Label("treble", 0)),Gtk::PACK_SHRINK);
  m_vbox6.pack_start(m_smallknob3,Gtk::PACK_SHRINK);
  m_vbox6.pack_start(m_vboxgg, Gtk::PACK_EXPAND_PADDING);
  
  
  m_paintbox->pack_start(m_vbox1);
  m_paintbox->pack_start(m_vbox2);
  m_paintbox->pack_start(m_vbox3);
  m_paintbox->pack_start(m_vbox);
  
  m_hbox.pack_start(m_vbox5);
  m_hbox.pack_start(m_vbox4);
  m_hbox.pack_start(m_vbox6);
  m_hbox.set_spacing(5);
  m_paintbox->pack_start(m_hbox);
  
  show_all();
  set_size_request(-1,-1);
}

Widget::~Widget() {
 
}

void Widget::set_value(uint32_t port_index,
               uint32_t format,
               const void * buffer)
{
  if ( format == 0 ) {
    float value =  *(float *)buffer;
      switch ( port_index )
      {
        case 0:
            mastergain = value;
            m_bigknob.cp_set_value(mastergain);
            break;
        case 1:
            pregain = value;
            m_bigknob1.cp_set_value(pregain);
            break;
        case 2:
            wet_dry = value;
            m_bigknob2.cp_set_value(wet_dry);
            break;
        case 3:
            drive = value;
            m_bigknob3.cp_set_value(drive);
            break;
        case 4:
            mid = value;
            m_smallknob1.cp_set_value(mid);
            break;
        case 5:
            bass = value;
            m_smallknob2.cp_set_value(bass);
            break;
        case 6:
            treble = value;
            m_smallknob3.cp_set_value(treble);
            break;
    }
  }
}

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

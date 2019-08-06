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
  m_paintbox.set_border_width(0);
  m_paintbox.set_spacing(0);
  m_paintbox.set_homogeneous(false);
  m_paintbox.set_name(plug_name);
  m_paintbox.property_paint_func() = "amp_skin_expose";
  add(m_paintbox);
  // box for the controllers
  m_hbox_.set_spacing(20);
  m_hbox_.set_homogeneous(false);
  // this box set space for the upper part of the skin
  m_hbox1_.set_spacing(32);
  m_hbox1_.set_border_width(12);
  make_logo( &m_vbox6, "preamp-guitarix-label" ) ;
  make_logo( &m_vbox7, "preamp-redeye-label" ) ;
  m_hbox1_.pack_start(m_vbox6);
  m_hbox1_.pack_start(m_vbox7);

  // set a vertical box in the paintbox
  m_paintbox.pack_start(m_vbox_);
  // and put space box on top
  m_vbox_.pack_start(m_hbox1_, Gtk::PACK_EXPAND_PADDING);
  // and controller box on bottem
  m_vbox_.pack_start(m_hbox_,Gtk::PACK_SHRINK);

  // create all controllers
  make_controller_box(&m_vbox, &m_bigknob, "output", -20, 20, 0.1, output_level, plug_name);
  m_bigknob.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob_value_changed));


  make_controller_box(&m_vbox1, &m_bigknob1, "drive", -12, 12, 0.1, drive, plug_name);
  m_bigknob1.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob1_value_changed));

  make_controller_box(&m_vbox2, &m_bigknob2, "input", -20, 20, 0.1,  input_level, plug_name);
  m_bigknob2.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob2_value_changed));

  make_controller_box(&m_vbox3, &m_bigknob3, "resonance", 0, 10, 0.1, resonance, plug_name);
  m_bigknob3.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob3_value_changed));

  make_controller_box(&m_vbox4, &m_bigknob4, "presence", 0, 10, 0.1, presence, plug_name);
  m_bigknob4.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob4_value_changed));

 make_controller_box(&m_vbox5, &m_bigknob5, "feedback", -75, -3, 0.1, feedback, plug_name);
  m_bigknob5.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob5_value_changed));
 
 // put boxed controllers into controller box
  m_hbox_.pack_start(m_vboxhh);

  m_hbox_.pack_start(m_vbox2);
  m_hbox_.pack_start(m_vbox1);
  m_hbox_.pack_start(m_vbox3);
  m_hbox_.pack_start(m_vbox4);

  // Feedback level depends on valves it seems - hide and set default value
//  m_hbox_.pack_start(m_vbox5);

  feedback = -3.0 ;
  
  m_hbox_.pack_start(m_vbox);
  m_hbox_.pack_start(m_vboxii);

  // connect expose handler as resize handler
  m_paintbox.signal_draw().connect(
    sigc::mem_fun(this, &Widget::_draw), true);

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
/*  Gtk::Label* pr = new Gtk::Label(label, 0);
  pr->set_name("amplabel");
*/
  Glib::ustring  label_image = GX_LV2_STYLE_DIR;
  label_image += "/preamp-";
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

// Create the Text Labels For Amp
void Widget::make_logo(Gtk::VBox *box,Glib::ustring label)
{
	Glib::ustring  label_image = GX_LV2_STYLE_DIR;
  	label_image += "/";
  	label_image += label;
  	label_image += ".png";
  	Gtk::Image *pr = new Gtk::Image(label_image);
        box->pack_start( *Gtk::manage(pr),Gtk::PACK_SHRINK);
} 

// set borderwith for paintbox when widget resize
// to hold controllers in place
bool Widget::_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
  int x, y, width, height;
  m_paintbox.get_window()->get_geometry(x, y, width, height);
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
        case OUTPUT_LEVEL:
          output_level = value;
          m_bigknob.cp_set_value(output_level);
          break;
        case DRIVE:
          drive = value;
          m_bigknob1.cp_set_value(drive);
          break;
        case INPUT_LEVEL:
          input_level = value;
          m_bigknob2.cp_set_value(input_level);
          break;
        case RESONANCE:
          resonance = value;
          m_bigknob3.cp_set_value(resonance);
          break;
        case PRESENCE:
          presence = value;
          m_bigknob4.cp_set_value(presence);
          break;
        case FEEDBACK:
          feedback = value;
          m_bigknob5.cp_set_value(feedback);
          break;
	case MAXLEVEL :
	fprintf(stderr, "MAXLEVEL MESSAGE THROUGH %f\n", value ) ;
	break;
        default:
          break;
        }
    }
}
// write value changes to the host->engine
void Widget::on_knob_value_changed()
{
  output_level = m_bigknob.get_value();
  //std::cout << "output_level = " << output_level << std::endl;
  write_function(controller, (PortIndex)OUTPUT_LEVEL,
                 sizeof(float), 0, (const void*)&output_level);
}

void Widget::on_knob1_value_changed()
{
  drive = m_bigknob1.get_value();
  //std::cout << "drive = " << drive << std::endl;
  write_function(controller, (PortIndex)DRIVE,
                 sizeof(float), 0, (const void*)&drive);
}

void Widget::on_knob2_value_changed()
{
  input_level = m_bigknob2.get_value();
  //std::cout << "input_level = " << input_level << std::endl;
  write_function(controller, (PortIndex)INPUT_LEVEL,
                 sizeof(float), 0, (const void*)&input_level);
}


void Widget::on_knob3_value_changed()
{
  resonance = m_bigknob3.get_value();
  //std::cout << "resonance = " << resonance << std::endl;
  write_function(controller, (PortIndex)RESONANCE,
                 sizeof(float), 0, (const void*)&resonance);
}

void Widget::on_knob4_value_changed()
{
  presence = m_bigknob4.get_value();
  //std::cout << "presence = " << presence << std::endl;
  write_function(controller, (PortIndex)PRESENCE,
                 sizeof(float), 0, (const void*)&presence);
}
void Widget::on_knob5_value_changed()
{
  feedback = m_bigknob5.get_value();
 // std::cout << "feedback = " << feedback << std::endl;
  write_function(controller, (PortIndex)FEEDBACK,
                 sizeof(float), 0, (const void*)&feedback);
}


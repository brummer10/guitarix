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
  Glib::ustring modes[] = {"linear","ping pong"};
  static const size_t modes_size = sizeof(modes) / sizeof(modes[0]);
  
  make_selector_box(&m_selector, "Echo Mode", modes, modes_size, 
                    INVERT, 0, static_cast<float>(modes_size+1), 1.0, plug_name);

  // create all controllers
  make_controller_box(&m_vbox2, &m_bigknob, "Time (R)", 1, 2000, 1,
                      TIME_R, plug_name);
  make_controller_box(&m_vbox3, &m_bigknob1, "Time (L)", 1, 2000, 1,
                      TIME_L, plug_name);

  make_controller_box(&m_vbox4, &m_smallknob3, "LFO", 0.2, 5, 0.01,
                      LFOFREQ, plug_name);
  m_vbox4.pack_start(m_selector,Gtk::PACK_SHRINK);
  
  make_controller_box(&m_vbox5, &m_smallknob4, "Level (R)", 0, 100, 1,
                     PERCENT_R, plug_name);
  make_controller_box(&m_vbox6, &m_smallknob5, "Level (L)", 0, 100, 1,
                      PERCENT_L, plug_name);
  
  // set propertys for the main paintbox holding the skin
  m_paintbox.set_border_width(10);
  m_paintbox.set_spacing(6);
  m_paintbox.set_homogeneous(false);
  m_paintbox.set_name(plug_name);
  m_paintbox.property_paint_func() = "amp_skin_expose";
  add(m_paintbox);
  // box for the controllers
  m_hbox_.set_spacing(14);
  m_hbox_.set_border_width(24);
  m_hbox_.set_homogeneous(false);
  // set a vertical box in the paintbox
  m_vbox.set_border_width(14);
  m_vbox1.set_border_width(14);
  m_paintbox.pack_start(m_vbox_);
  // and controller box on top
  m_vbox_.pack_start(m_hbox_, Gtk::PACK_SHRINK);
   // put boxed controllers into controller box
  m_hbox_.pack_start(m_vbox1, Gtk::PACK_EXPAND_PADDING);
  m_hbox_.pack_start(m_vbox3);
  m_hbox_.pack_start(m_vbox6);
  m_hbox_.pack_start(m_vbox4);
  m_hbox_.pack_start(m_vbox5);
  m_hbox_.pack_start(m_vbox2);
  m_hbox_.pack_start(m_vbox, Gtk::PACK_EXPAND_PADDING);


  // connect expose handler as resize handler
  m_paintbox.signal_expose_event().connect(
    sigc::mem_fun(this, &Widget::_expose_event), true);

  set_app_paintable(true);
  show_all();
}

Widget::~Widget()
{

}

// create selectors from gxwmm
void Widget::make_selector_box(Gxw::Selector *regler,
                                 Glib::ustring labela,
                                 Glib::ustring tables[],
                                 size_t _size,
                                 PortIndex port_name,
                                 float min, float max,
                                 float digits,
                                 Glib::ustring plug_name)
{
  Gtk::TreeModelColumn<Glib::ustring> label;
  Gtk::TreeModelColumnRecord rec;
  rec.add(label);
  Glib::RefPtr<Gtk::ListStore> ls = Gtk::ListStore::create(rec);

  for (uint32_t i = 0 ; i< _size; ++i) {
    ls->append()->set_value(0, tables[i]);
  }
    
  regler->set_model(ls);
  regler->set_has_tooltip();
  regler->set_tooltip_text(labela);
  regler->cp_configure("SELECTOR", labela, min, max, digits);
  regler->set_show_value(false);
  regler->set_name(plug_name);
  regler->signal_value_changed().connect(sigc::bind(sigc::mem_fun(*this,
      &Widget::on_selector_value_changed),regler, port_name));
}

// create stackboxes with controllers from gxw
void Widget::make_controller_box(Gtk::VBox *box,
                                 Gxw::Regler *regler,
                                 Glib::ustring label,
                                 float min, float max,
                                 float digits,
                                 PortIndex port_name,
                                 Glib::ustring plug_name)
{
  Gtk::Label* pr = new Gtk::Label(label, 0);
  pr->set_name("amplabel");
  /*Glib::ustring  label_image = GX_LV2_STYLE_DIR;
  label_image += "/";
  label_image += label;
  label_image += "-label.png";
  Gtk::Image *pr = new Gtk::Image(label_image);*/

  Gtk::VBox* b1 = new Gtk::VBox();
  box->pack_start( *Gtk::manage(b1), Gtk::PACK_EXPAND_PADDING);
  box->pack_start( *Gtk::manage(pr),Gtk::PACK_SHRINK);
  regler->cp_configure("KNOB", label, min, max, digits);
  regler->set_show_value(false);
  regler->set_name(plug_name);
  box->pack_start(*regler,Gtk::PACK_SHRINK);
  Gtk::VBox* b2 = new Gtk::VBox();
  box->pack_start( *Gtk::manage(b2), Gtk::PACK_EXPAND_PADDING);
  regler->signal_value_changed().connect(sigc::bind(sigc::mem_fun(*this,
      &Widget::on_regler_value_changed),regler, port_name));

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
        case TIME_R:
          m_bigknob.cp_set_value(value);
          break;
        case TIME_L:
          m_bigknob1.cp_set_value(value);
          break;
        case LFOFREQ:
          m_smallknob3.cp_set_value(value);
          break;
        case INVERT:
          m_selector.cp_set_value(value);
          break;
        case PERCENT_R:
          m_smallknob4.cp_set_value(value);
          break;
        case PERCENT_L:
          m_smallknob5.cp_set_value(value);
          break;
         default:
          break;
        }
    }
}

// write regler value changes to the host->engine
void Widget::on_regler_value_changed(Gxw::Regler *regler,uint32_t port_index)
{
  float value = regler->get_value();
  write_function(controller, port_index,
                 sizeof(float), 0, (const void*)&value);
}

// write selector value changes to the host->engine
void Widget::on_selector_value_changed(Gxw::Selector *regler, uint32_t port_index)
{
  float value = regler->get_value();
  write_function(controller, port_index,
                 sizeof(float), 0, (const void*)&value);
}


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

Widget::Widget(Glib::ustring plug_name)
{
  // set propertys for the main paintbox holding the skin
  m_paintbox.set_name(plug_name);
  m_paintbox.property_paint_func() = "amp_skin_expose";
  add(m_paintbox);
  if(strcmp("wah",plug_name.c_str()) == 0)
    {
      make_controller_box(&m_vbox, &m_bigknob, "wah", 0, 1, 0.01, wah, plug_name);
      m_bigknob.signal_value_changed().connect(sigc::mem_fun(*this,
        &Widget::on_knob_value_changed));

      m_paintbox.pack_start(m_vbox);
      set_size_request(225,157);
    } 
  else
    {
      set_size_request(175,100);
    }
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
  //Gtk::Label* pr = new Gtk::Label(label, 0);
  //pr->set_name("amplabel");
  /*Glib::ustring  label_image = GX_STYLE_DIR;
  label_image += "/";
  label_image += label;
  label_image += "-label.png";
  Gtk::Image *pr = new Gtk::Image(label_image);*/

  //Gtk::VBox* b1 = new Gtk::VBox();
  //box->set_border_width(5);
  //box->pack_start( *Gtk::manage(b1), Gtk::PACK_SHRINK);
  //box->pack_start( *Gtk::manage(pr),Gtk::PACK_SHRINK);
  regler->cp_configure("KNOB", label, min, max, digits);
  regler->set_show_value(false);
  regler->cp_set_value(value);
  regler->set_name(plug_name);
  box->pack_start(*regler,Gtk::PACK_SHRINK);
  Gtk::VBox* b2 = new Gtk::VBox();
  box->pack_start( *Gtk::manage(b2), Gtk::PACK_EXPAND_PADDING);
}

// receive controller value changes from host
void Widget::set_value(uint32_t port_index,
                       uint32_t format,
                       const void * buffer)
{
  if ( format == 0 )
    {
      float value =  *(float *)buffer;
      switch ((EffectPortIndex)port_index )
        {
        case WAH:
          wah = value;
          m_bigknob.cp_set_value(wah);
          break;
        default:
          break;
        }
    }
}
// write value changes to the host->engine
void Widget::on_knob_value_changed()
{
  wah = m_bigknob.get_value();
  //std::cout << "mastergain = " << mastergain << std::endl;
  write_function(controller, (EffectPortIndex)WAH,
                 sizeof(float), 0, (const void*)&wah);
}

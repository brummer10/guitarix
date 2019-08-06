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


/*    @get controller by port
 *  this function is used by make_selector() make_controller_box()
 *  set_value() and on_value_changed()
 *  so controller widgets needs only here asined to a port, 
 *  and all functions which need acess to the controller widget pointer 
 *  can receive them by port number
 */

/*
typedef enum
{
   DETUNE, 
   OCTAVE,
   COMPENSATE,
   LATENCY, 
   WET,
   DRY,
   LOW,
   MIDDLELOW,
   MIDDLETREBLE,
   TREBLE,
} PortIndex;
*/
Gtk::Widget* Widget::get_controller_by_port(uint32_t port_index)
{
  switch ((PortIndex)port_index )
  {
    case DETUNE:
      return &m_bigknob[0];
    case WET:
      return &m_bigknob[1];
    case OCTAVE:
      return &m_selector[0];
    case COMPENSATE:
      return &m_selector[1];
    case LATENCY:
      return &m_selector[2];
    case DRY:
      return &m_bigknob[2];
    case LOW:
      return &m_bigknob[4];
     case MIDDLELOW:
      return &m_bigknob[5];
    case MIDDLETREBLE:
      return &m_bigknob[6];
    case TREBLE:
      return &m_bigknob[7];
   default:
      return NULL;
  } 
}

Widget::Widget(Glib::ustring plugname):
plug_name(plugname)
{
  // create controllers for port name
  make_controller_box(&m_vbox[1], "DETUNE",  -12.0, 12.0, 0.1, DETUNE);
  make_controller_box(&m_vbox[2], "WET",  0.0, 100.0, 1, WET);
  make_controller_box(&m_vbox[3], "DRY", 0.0, 100.0, 1, DRY);
  make_controller_box(&m_vbox[4], "LOW",  0.0, 2.0, 0.01, LOW);
  make_controller_box(&m_vbox[5], "Lo MID", 0.0, 2.0, 0.01, MIDDLELOW);
  make_controller_box(&m_vbox[6], "Hi MID",  0.0, 2.0, 0.01, MIDDLETREBLE);
  make_controller_box(&m_vbox[7], "High",  0.0, 2.0, 0.01, TREBLE);
  
  Glib::ustring octaves[] = {"no shift","octave up","octave down"};  
  static const size_t _size1 = sizeof(octaves) / sizeof(octaves[0]);
  make_selector("OCTAVE", octaves, _size1, 0, 1.0, OCTAVE);
  Glib::ustring compensate[] = {"delay ","compensate"};  
  static const size_t _size2 = sizeof(compensate) / sizeof(compensate[0]);
  make_selector("COMPENSATE", compensate, _size2, 0, 1.0, COMPENSATE);
  Glib::ustring latency[] = {"high quality           ","low quality           ","realtime           "};  
  static const size_t _size3 = sizeof(latency) / sizeof(latency[0]);
  make_selector("LATENCY", latency, _size3, 0, 1.0, LATENCY);
  m_vbox[0].pack_start(m_selector[0]);
  m_vbox[0].pack_start(m_selector[1]);
  m_vbox[0].pack_start(m_selector[2]);
  m_latencyreport.set_name("lalabel");
  m_vbox[0].pack_start(m_latencyreport);
  // set propertys for the main paintbox holding the skin
  m_paintbox.set_border_width(10);
  m_paintbox.set_spacing(6);
  m_paintbox.set_homogeneous(false);
  m_paintbox.set_name(plug_name);
  m_paintbox.property_paint_func() = "compressor_expose";
  add(m_paintbox);
  // box for the controllers
  m_hbox.set_spacing(14);
  m_hbox.set_border_width(24);
  m_hbox.set_homogeneous(false);
  // set a vertical box in the paintbox
  m_vbox[8].set_border_width(14);
  m_vbox[10].set_border_width(14);
  m_paintbox.pack_start(m_vbox[9]);
  // and controller box on top
  m_vbox[9].pack_start(m_hbox, Gtk::PACK_SHRINK);
  // put boxed controllers into controller box
  m_hbox.pack_start(m_vbox[10], Gtk::PACK_EXPAND_PADDING);
  m_hbox.pack_start(m_vbox[0]);
  m_hbox.pack_start(m_vbox[1]);
  m_hbox.pack_start(m_vbox[2]);
  m_hbox.pack_start(m_vbox[3]);
  m_hbox.pack_start(m_vbox[4]);
  m_hbox.pack_start(m_vbox[5]);
  m_hbox.pack_start(m_vbox[6]);
  m_hbox.pack_start(m_vbox[7]);
  m_hbox.pack_start(m_vbox[8], Gtk::PACK_EXPAND_PADDING);

  // connect expose handler as resize handler
  // m_paintbox.signal_draw().connect(
  //   sigc::mem_fun(this, &Widget::_draw), true);

  set_app_paintable(true);
  show_all();
}

Widget::~Widget()
{

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

// create selectors from gxwmm
void Widget::make_selector(Glib::ustring labela,
                           Glib::ustring tables[],
                           size_t _size,
                           float min, float digits,
                           PortIndex port_name)
{
  Gxw::Selector *regler = static_cast<Gxw::Selector*>
                                    (get_controller_by_port(port_name));
  if (regler)
  {
    float max = static_cast<float>(_size+1);

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
    regler->signal_value_changed().connect(sigc::bind(sigc::mem_fun(
           *this, &Widget::on_value_changed), port_name));
  }
}

// create stackboxes with controllers for port name
void Widget::make_controller_box(Gtk::Box *box,
                                 Glib::ustring label,
                                 float min, float max,
                                 float digits,
                                 PortIndex port_name)
{
  Gxw::Regler *regler = static_cast<Gxw::Regler*>(
                                    get_controller_by_port(port_name));
  if (regler)
  {
    Gtk::Label* pr = new Gtk::Label(label, 0);
    pr->set_name("amplabel");
    // use label images instead simple string labes
    /*Glib::ustring  label_image = GX_LV2_STYLE_DIR;
    label_image += "/";
    label_image += label;
    label_image += "-label.png";
    Gtk::Image *pr = new Gtk::Image(label_image);*/

    Gtk::VBox* b1 = new Gtk::VBox();
    box->pack_start( *Gtk::manage(b1), Gtk::PACK_EXPAND_PADDING);
    box->pack_start( *Gtk::manage(pr),Gtk::PACK_SHRINK);
    regler->cp_configure("KNOB", label, min, max, digits);
    regler->set_show_value(true);
    regler->set_name(plug_name);
    box->pack_start(*regler,Gtk::PACK_SHRINK);
    Gtk::VBox* b2 = new Gtk::VBox();
    box->pack_start( *Gtk::manage(b2), Gtk::PACK_EXPAND_PADDING);
    regler->signal_value_changed().connect(sigc::bind(sigc::mem_fun(
           *this, &Widget::on_value_changed), port_name));
  }
}

// create stackboxes with switch controller for port name
void Widget::make_switch_box(Gtk::Box *box,
                             Glib::ustring label,
                             PortIndex port_name)
{
  Gxw::Switch *regler = static_cast<Gxw::Switch*>(
                                    get_controller_by_port(port_name));
  if (regler)
  {
    Gtk::Label* pr = new Gtk::Label(label, 0);
    pr->set_name("amplabel");
    // use label images instead simple string labes
    /*Glib::ustring  label_image = GX_LV2_STYLE_DIR;
    label_image += "/"+plug_name+"-";
    label_image += label;
    label_image += "-label.png";
     Gtk::Image *pr = new Gtk::Image(label_image);*/
 
    regler->cp_configure("switch", label, 0, 1, 1);
    regler->set_name(plug_name);
    regler->set_base_name( "button" );
    Gtk::VBox* b1 = new Gtk::VBox();
    box->pack_start( *Gtk::manage(b1), Gtk::PACK_EXPAND_PADDING);
    box->pack_start( *Gtk::manage(pr),Gtk::PACK_SHRINK); 
    box->pack_start(*regler,Gtk::PACK_SHRINK);
    Gtk::VBox* b2 = new Gtk::VBox();
    box->pack_start( *Gtk::manage(b2), Gtk::PACK_EXPAND_PADDING);
    regler->signal_toggled().connect(sigc::bind(sigc::mem_fun(
        *this, &Widget::on_value_changed), port_name));
  }
}

template <class T>
inline std::string to_string(const T& t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
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
    if (regler)
    {
      regler->cp_set_value(value);
    // FIXME latency report seems to be broken, it produce Xruns on startup  
    } else if (port_index == LATENCYREPORT) {
      m_latencyreport.set_text("Latency " +to_string(value));
    }
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


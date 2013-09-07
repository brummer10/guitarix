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

#define max(x, y) (((x) > (y)) ? (x) : (y))

/*    @get controller by port
 *  this function is used by make_selector() make_controller_box()
 *  set_value() and on_value_changed()
 *  so controller widgets needs only here asined to a port, 
 *  and all functions which need acess to the controller widget pointer 
 *  can receive them by port number
 */

Gtk::Widget* Widget::get_controller_by_port(uint32_t port_index)
{
  switch ((PortIndex)port_index )
  {
    case PERCENT1:
      return &m_smallknob[1];
    case PERCENT2:
      return &m_smallknob[2];
    case PERCENT3:
      return &m_smallknob[3];
    case PERCENT4:
      return &m_smallknob[4];
    case PERCENT5:
      return &m_smallknob[5];
//    case TIME:
//      return &m_smallknob[6];
    case TIME1:
      return &m_smallknob[7];
    case TIME2:
      return &m_smallknob[8];
    case TIME3:
      return &m_smallknob[9];
    case TIME4:
      return &m_smallknob[10];
    case TIME5:
      return &m_smallknob[11];
    case CROSSOVER_B1_B2:
      return &m_smallknob[12];
    case CROSSOVER_B2_B3:
      return &m_smallknob[13];
    case CROSSOVER_B3_B4:
      return &m_smallknob[14];
    case CROSSOVER_B4_B5:
      return &m_smallknob[15];
    default:
      return NULL;
  } 
}

Widget::Widget(Glib::ustring plugname):
plug_name(plugname)
{
  m_fr[0].set_label("BAND 1");
  m_fr[0].add(m_lbox[0]);
  m_fr[1].set_label("BAND 2");
  m_fr[1].add(m_lbox[1]);
  m_fr[2].set_label("BAND 3");
  m_fr[2].add(m_lbox[2]);
  m_fr[3].set_label("BAND 4");
  m_fr[3].add(m_lbox[3]);
  m_fr[4].set_label("BAND 5");
  m_fr[4].add(m_lbox[4]);
//  m_fr[5].set_label("OUT");
  m_fr[6].set_label("BAND PASS");
  // create controllers for port name
  make_controller_box(&m_vbox[1], "AMOUNT", 0.0, 1e+02, 0.1, PERCENT1, false);
  make_controller_box(&m_vbox[2], "AMOUNT", 0.0, 1e+02, 0.1, PERCENT2, false);
  make_controller_box(&m_vbox[3], "AMOUNT", 0.0, 1e+02, 0.1, PERCENT3, false);
  make_controller_box(&m_vbox[4], "AMOUNT", 0.0, 1e+02, 0.1, PERCENT4, false);
  make_controller_box(&m_vbox[5], "AMOUNT", 0.0, 1e+02, 0.1, PERCENT5, false);
  
 // make_controller_box(&m_vbox[6], "Gain ", -4e+01, 4.0, 0.1 , TIME, false);
  
  make_controller_box(&m_vbox[1], "BPM", 24.0, 3.6e+02, 1.0 , TIME1, true);
  make_controller_box(&m_vbox[2], "BPM", 24.0, 3.6e+02, 1.0 , TIME2, true);
  make_controller_box(&m_vbox[3], "BPM", 24.0, 3.6e+02, 1.0 , TIME3, true);
  make_controller_box(&m_vbox[4], "BPM", 24.0, 3.6e+02, 1.0 , TIME4, true);
  make_controller_box(&m_vbox[5], "BPM", 24.0, 3.6e+02, 1.0 , TIME5, true);
  
  make_controller_box(&m_vbox[7], "LOW PASS \n  B1><B2", 
    2e+01, 2e+04, 1.08 , CROSSOVER_B1_B2, true);
  make_controller_box(&m_vbox[8], "CROSSOVER \n   B2><B3", 
    2e+01, 2e+04, 1.08 , CROSSOVER_B2_B3, true);
  make_controller_box(&m_vbox[9], "CROSSOVER \n   B3><B4 ", 
    2e+01, 2e+04, 1.08 , CROSSOVER_B3_B4, true);
  make_controller_box(&m_vbox[10], "HIGH PASS \n  B4><B5", 
    2e+01, 2e+04, 1.08 , CROSSOVER_B4_B5, true);

  // set propertys for the main paintbox holding the skin
  m_paintbox[0].set_border_width(10);
  m_paintbox[0].set_spacing(6);
  m_paintbox[0].set_homogeneous(false);
  m_paintbox[0].set_name(plug_name);
  m_paintbox[0].property_paint_func() = "gxhead_expose";
  add(m_paintbox[0]);

  for (uint32_t i = 0;i<5;i++) {
    fastmeter[i].set_hold_count(8);
    fastmeter[i].set_property("dimen",5);
    m_paintbox[i+1].property_paint_func() = "RackBox_expose";
    m_paintbox[i+1].set_name(plug_name);
    m_paintbox[i+1].set_border_width(5);
    m_paintbox[i+1].pack_start(fastmeter[i]);
  }

  // set a vertical box in the paintbox
  m_vbox[11].set_border_width(14);
  m_vbox[12].set_border_width(14);
  m_hbox[2].set_border_width(4);
  m_paintbox[0].pack_start(m_vbox[0]);
  // box for the controllers
  m_hbox[0].set_spacing(4);
  m_hbox[0].set_border_width(4);
  m_hbox[0].set_homogeneous(false);
  m_vbox[0].pack_start(m_hbox[0]);
  m_fr[6].add(m_hbox[1]);
  m_vbox[0].pack_start(m_fr[6]);
  m_vbox[0].pack_start(m_hbox[2]);
  // put boxed controllers into controller box
  m_hbox[0].pack_start(m_vbox[11], Gtk::PACK_EXPAND_PADDING);
  m_hbox[0].pack_start(m_fr[0]);
  m_lbox[0].pack_start(m_vbox[1]);
  m_lbox[0].pack_start(m_paintbox[1],Gtk::PACK_SHRINK);
  m_hbox[0].pack_start(m_fr[1]);
  m_lbox[1].pack_start(m_vbox[2]);
  m_lbox[1].pack_start(m_paintbox[2],Gtk::PACK_SHRINK);
  m_hbox[0].pack_start(m_fr[2]);
  m_lbox[2].pack_start(m_vbox[3]);
  m_lbox[2].pack_start(m_paintbox[3],Gtk::PACK_SHRINK);
  m_hbox[0].pack_start(m_fr[3]);
  m_lbox[3].pack_start(m_vbox[4]);
  m_lbox[3].pack_start(m_paintbox[4],Gtk::PACK_SHRINK);
  m_hbox[0].pack_start(m_fr[4]);
  m_lbox[4].pack_start(m_vbox[5]);
  m_lbox[4].pack_start(m_paintbox[5],Gtk::PACK_SHRINK);
//  m_hbox[0].pack_start(m_fr[5]);
//  m_fr[5].add(m_vbox[6]);
  m_hbox[0].pack_start(m_vbox[12], Gtk::PACK_EXPAND_PADDING);
  // put boxed controllers into controller box
  m_hbox[1].pack_start(m_vbox[13], Gtk::PACK_EXPAND_PADDING);
  m_hbox[1].pack_start(m_vbox[7]);
  m_hbox[1].pack_start(m_vbox[8]);
  m_hbox[1].pack_start(m_vbox[9]);
  m_hbox[1].pack_start(m_vbox[10]);
  m_hbox[1].pack_start(m_vbox[14], Gtk::PACK_EXPAND_PADDING);

  set_app_paintable(true);
  show_all();
}

Widget::~Widget()
{

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
                                 PortIndex port_name,
                                 bool show_value)
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
    regler->set_show_value(show_value);
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

inline float Widget::power2db(float power) {
    return  20.*log10(power);
}

inline double Widget::log_meter (double db)
{
    // keep log_meter_inv in sync when changing anying!
    gfloat def = 0.0f; /* Meter deflection %age */

    if (db < -70.0f) {
        def = 0.0f;
    } else if (db < -60.0f) {
        def = (db + 70.0f) * 0.25f;
    } else if (db < -50.0f) {
        def = (db + 60.0f) * 0.5f + 2.5f;
    } else if (db < -40.0f) {
        def = (db + 50.0f) * 0.75f + 7.5f;
    } else if (db < -30.0f) {
        def = (db + 40.0f) * 1.5f + 15.0f;
    } else if (db < -20.0f) {
        def = (db + 30.0f) * 2.0f + 30.0f;
    } else if (db < 6.0f) {
        def = (db + 20.0f) * 2.5f + 50.0f;
    } else {
        def = 115.0f;
    }

    /* 115 is the deflection %age that would be
       when db=6.0. this is an arbitrary
       endpoint for our scaling.
    */

    return def/115.0f;
}

bool Widget::refresh_meter_level(int m, float new_level) {

    static const float falloff = 87 * 60 * 0.001;

    // Note: removed RMS calculation, we will only focus on max peaks
    static float old_peak_db[5] = {-INFINITY,-INFINITY,-INFINITY,-INFINITY,-INFINITY} ;

    // calculate peak dB and translate into meter
    float peak_db = -INFINITY;
    if (new_level > 0) {
        peak_db = power2db(new_level);
    }
    // retrieve old meter value and consider falloff
    if (peak_db < old_peak_db[m]) {
        peak_db = max(peak_db, old_peak_db[m] - falloff);
    }
    fastmeter[m].set(log_meter(peak_db));
    old_peak_db[m] = peak_db;
    return true;
}

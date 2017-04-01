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

/*
typedef enum
{
   MODE1, 
   MODE2, 
   MODE3, 
   MODE4, 
   MODE5, 
   MAKEUP1, 
   MAKEUP2, 
   MAKEUP3, 
   MAKEUP4, 
   MAKEUP5, 
   MAKEUPTHRESHOLD1, 
   MAKEUPTHRESHOLD2, 
   MAKEUPTHRESHOLD3, 
   MAKEUPTHRESHOLD4, 
   MAKEUPTHRESHOLD5, 
   RATIO1, 
   RATIO2, 
   RATIO3, 
   RATIO4, 
   RATIO5, 
   ATTACK1, 
   ATTACK2, 
   ATTACK3, 
   ATTACK4, 
   ATTACK5, 
   RELEASE1, 
   RELEASE2, 
   RELEASE3, 
   RELEASE4, 
   RELEASE5, 
   CROSSOVER_B1_B2, 
   CROSSOVER_B2_B3, 
   CROSSOVER_B3_B4, 
   CROSSOVER_B4_B5, 
   V1, 
   V2, 
   V3, 
   V4, 
   V5, 
} PortIndex;
*/


Gtk::Widget* Widget::get_controller_by_port(uint32_t port_index)
{
  switch ((PortIndex)port_index )
  {
    case MAKEUP1:
      return &m_smallknob[0];
    case MAKEUP2:
      return &m_smallknob[1];
    case MAKEUP3:
      return &m_smallknob[2];
    case MAKEUP4:
      return &m_smallknob[3];
    case MAKEUP5:
      return &m_smallknob[4];
    case MAKEUPTHRESHOLD1:
      return &m_smallknob[5];
    case MAKEUPTHRESHOLD2:
      return &m_smallknob[6];
    case MAKEUPTHRESHOLD3:
      return &m_smallknob[7];
    case MAKEUPTHRESHOLD4:
      return &m_smallknob[8];
    case MAKEUPTHRESHOLD5:
      return &m_smallknob[9];
    
    case RATIO1:
      return &m_smallknob[10];
    case RATIO2:
      return &m_smallknob[11];
    case RATIO3:
      return &m_smallknob[12];
    case RATIO4:
      return &m_smallknob[13];
    case RATIO5:
      return &m_smallknob[14];
     
    case ATTACK1:
      return &m_smallknob[15];
    case ATTACK2:
      return &m_smallknob[16];
    case ATTACK3:
      return &m_smallknob[17];
    case ATTACK4:
      return &m_smallknob[18];
    case ATTACK5:
      return &m_smallknob[19];
      
    case RELEASE1:
      return &m_smallknob[20];
    case RELEASE2:
      return &m_smallknob[21];
    case RELEASE3:
      return &m_smallknob[22];
    case RELEASE4:
      return &m_smallknob[23];
    case RELEASE5:
      return &m_smallknob[24];
      
    case MODE1:
      return &select[0];
    case MODE2:
      return &select[1];
    case MODE3:
      return &select[2];
    case MODE4:
      return &select[3];
    case MODE5:
      return &select[4];
      
    case CROSSOVER_B1_B2:
      return &m_smallknob[25];
    case CROSSOVER_B2_B3:
      return &m_smallknob[26];
    case CROSSOVER_B3_B4:
      return &m_smallknob[27];
    case CROSSOVER_B4_B5:
      return &m_smallknob[28];
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
  m_fr[5].set_label("BAND PASS");

  // create controllers for port name

  make_controller_box(&m_vbox[1], "RATIO ", 
    "Compression ratio", 1.0, 1e+02, 0.1, RATIO1, false);
  make_controller_box(&m_vbox[2], "RATIO ", 
    "Compression ratio", 1.0, 1e+02, 0.1, RATIO2, false);
  make_controller_box(&m_vbox[3], "RATIO ", 
    "Compression ratio", 1.0, 1e+02, 0.1, RATIO3, false);
  make_controller_box(&m_vbox[4], "RATIO ", 
    "Compression ratio", 1.0, 1e+02, 0.1, RATIO4, false);
  make_controller_box(&m_vbox[5], "RATIO ", 
    "Compression ratio", 1.0, 1e+02, 0.1, RATIO5, false);

  make_controller_box(&m_vbox[1], "ATTACK ", 
    "Time before the compressor starts to kick in", 0.001, 1.0, 0.001, ATTACK1, false);
  make_controller_box(&m_vbox[2], "ATTACK ", 
    "Time before the compressor starts to kick in", 0.001, 1.0, 0.001, ATTACK2, false);
  make_controller_box(&m_vbox[3], "ATTACK ", 
    "Time before the compressor starts to kick in", 0.001, 1.0, 0.001, ATTACK3, false);
  make_controller_box(&m_vbox[4], "ATTACK ", 
    "Time before the compressor starts to kick in", 0.001, 1.0, 0.001, ATTACK4, false);
  make_controller_box(&m_vbox[5], "ATTACK ", 
    "Time before the compressor starts to kick in", 0.001, 1.0, 0.001, ATTACK5, false);

  make_controller_box(&m_vbox[1], "RELEASE ", 
    "Time before the compressor releases the sound", 0.01, 1e+01, 0.01, RELEASE1, false);
  make_controller_box(&m_vbox[2], "RELEASE ", 
    "Time before the compressor releases the sound", 0.01, 1e+01, 0.01, RELEASE2, false);
  make_controller_box(&m_vbox[3], "RELEASE ", 
    "Time before the compressor releases the sound", 0.01, 1e+01, 0.01, RELEASE3, false);
  make_controller_box(&m_vbox[4], "RELEASE ", 
    "Time before the compressor releases the sound", 0.01, 1e+01, 0.01, RELEASE4, false);
  make_controller_box(&m_vbox[5], "RELEASE ", 
    "Time before the compressor releases the sound", 0.01, 1e+01, 0.01, RELEASE5, false);

  make_controller_box(&m_vbox[1], "MAKEUP", 
    "Post amplification and threshold", -5e+01, 5e+01, 0.1, MAKEUP1, false);
  make_controller_box(&m_vbox[2], "MAKEUP", 
    "Post amplification and threshold", -5e+01, 5e+01, 0.1, MAKEUP2, false);
  make_controller_box(&m_vbox[3], "MAKEUP", 
    "Post amplification and threshold", -5e+01, 5e+01, 0.1, MAKEUP3, false);
  make_controller_box(&m_vbox[4], "MAKEUP", 
    "Post amplification and threshold", -5e+01, 5e+01, 0.1, MAKEUP4, false);
  make_controller_box(&m_vbox[5], "MAKEUP", 
    "Post amplification and threshold", -5e+01, 5e+01, 0.1, MAKEUP5, false);

  make_controller_box(&m_vbox[1], "THRESHOLD ", 
    "Threshold correction, an anticlip measure", 0.0, 1e+01, 0.1, MAKEUPTHRESHOLD1, false);
  make_controller_box(&m_vbox[2], "THRESHOLD ", 
    "Threshold correction, an anticlip measure", 0.0, 1e+01, 0.1, MAKEUPTHRESHOLD2, false);
  make_controller_box(&m_vbox[3], "THRESHOLD ", 
    "Threshold correction, an anticlip measure", 0.0, 1e+01, 0.1, MAKEUPTHRESHOLD3, false);
  make_controller_box(&m_vbox[4], "THRESHOLD ", 
    "Threshold correction, an anticlip measure", 0.0, 1e+01, 0.1, MAKEUPTHRESHOLD4, false);
  make_controller_box(&m_vbox[5], "THRESHOLD ", 
    "Threshold correction, an anticlip measure", 0.0, 1e+01, 0.1, MAKEUPTHRESHOLD5, false);

  Glib::ustring modes[] = {"Compress","Bypass","Mute"};  
  static const size_t _size = sizeof(modes) / sizeof(modes[0]);
  make_selector(&m_vbox[1],"Compress or Mute the selected band, or Bypass The Compressor", modes, _size, 1.0, 1.0, MODE1);
  make_selector(&m_vbox[2],"Compress or Mute the selected band, or Bypass The Compressor", modes, _size, 1.0, 1.0, MODE2);
  make_selector(&m_vbox[3],"Compress or Mute the selected band, or Bypass The Compressor", modes, _size, 1.0, 1.0, MODE3);
  make_selector(&m_vbox[4],"Compress or Mute the selected band, or Bypass The Compressor", modes, _size, 1.0, 1.0, MODE4);
  make_selector(&m_vbox[5],"Compress or Mute the selected band, or Bypass The Compressor", modes, _size, 1.0, 1.0, MODE5);


  make_controller_box(&m_vbox[7], "LOW PASS \n  B1><B2", "Crossfrequency between Band1 and Band2",
    2e+01, 2e+04, 1.08 , CROSSOVER_B1_B2, true);
  make_controller_box(&m_vbox[8], "CROSSOVER \n   B2><B3", "Crossfrequency between Band2 and Band3",
    2e+01, 2e+04, 1.08 , CROSSOVER_B2_B3, true);
  make_controller_box(&m_vbox[9], "CROSSOVER \n   B3><B4 ", "Crossfrequency between Band3 and Band4",
    2e+01, 2e+04, 1.08 , CROSSOVER_B3_B4, true);
  make_controller_box(&m_vbox[10], "HIGH PASS \n  B4><B5", "Crossfrequency between Band4 and Band5",
    2e+01, 2e+04, 1.08 , CROSSOVER_B4_B5, true);
  
  // set propertys for the main paintbox holding the skin
  m_paintbox[0].set_border_width(10);
  m_paintbox[0].set_spacing(6);
  m_paintbox[0].set_homogeneous(false);
  m_paintbox[0].set_name(plug_name);
  m_paintbox[0].property_paint_func() = "gx_lv2_unit_expose";
  add(m_paintbox[0]);

  // set propertys and stack fastmeters
  for (uint32_t i = 0;i<5;i++) {
    fastmeter[i].set_hold_count(12);
    fastmeter[i].set_property("dimen",2);
    fastmeter[i].set_property("type",0);
    fastmeter[i].set_tooltip_text("Output");
    fastmeter[i+5].set_hold_count(12);
    fastmeter[i+5].set_property("dimen",2);
    fastmeter[i+5].set_property("type",0);
    fastmeter[i+5].set_tooltip_text("Input");
    m_paintbox[i+1].property_paint_func() = "RackBox_expose";
    m_paintbox[i+1].set_name(plug_name);
    m_paintbox[i+1].set_border_width(5);
    m_paintbox[i+1].set_spacing(2);
    m_paintbox[i+1].pack_start(fastmeter[i+5]);
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
  m_fr[5].add(m_hbox[1]);
  m_fr[5].set_border_width(25);
  m_vbox[0].pack_start(m_fr[5]);
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
  m_hbox[0].pack_start(m_vbox[12], Gtk::PACK_EXPAND_PADDING);
  // put boxed controllers into controller box
  m_hbox[1].pack_start(m_vbox[13], Gtk::PACK_EXPAND_PADDING);
  m_hbox[1].pack_start(m_vbox[7]);
  m_hbox[1].pack_start(m_vbox[8]);
  m_hbox[1].pack_start(m_vbox[9]);
  m_hbox[1].pack_start(m_vbox[10]);
  m_hbox[1].pack_start(m_vbox[15]);
  m_hbox[1].pack_start(m_vbox[14], Gtk::PACK_EXPAND_PADDING);
  // default disable tooltips
  gtk_settings_set_long_property(
        gtk_settings_get_default(), "gtk-enable-tooltips", false, "gx_mbcompressor");
  make_switch_box(&m_vbox[15], "Tooltips");
  m_switch.signal_toggled().connect(sigc::mem_fun(
        *this, &Widget::set_tooltips));
  
  set_app_paintable(true);
  show_all();
}

Widget::~Widget()
{

}

// create selectors from gxwmm
void Widget::make_selector(Gtk::Box *box,
                           Glib::ustring labela,
                           Glib::ustring tables[],
                           size_t _size,
                           float min, float digits,
                           PortIndex port_name)
{
  Gxw::Selector *regler = static_cast<Gxw::Selector*>
                                    (get_controller_by_port(port_name));
  if (regler)
  {
    float max = static_cast<float>(_size+2);

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
    box->pack_start(*regler,Gtk::PACK_SHRINK);
  }
}

// create stackboxes with controllers for port name
void Widget::make_controller_box(Gtk::Box *box,
                                 Glib::ustring label,
                                 Glib::ustring labela,
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
    Gtk::VBox* b1 = new Gtk::VBox();
    box->pack_start( *Gtk::manage(b1), Gtk::PACK_EXPAND_PADDING);
    box->pack_start( *Gtk::manage(pr),Gtk::PACK_SHRINK);
    regler->cp_configure("KNOB", label, min, max, digits);
    regler->set_show_value(show_value);
    regler->set_name(plug_name);
    regler->set_tooltip_text(labela);
    box->pack_start(*regler,Gtk::PACK_SHRINK);
    Gtk::VBox* b2 = new Gtk::VBox();
    box->pack_start( *Gtk::manage(b2), Gtk::PACK_EXPAND_PADDING);
    regler->signal_value_changed().connect(sigc::bind(sigc::mem_fun(
           *this, &Widget::on_value_changed), port_name));
  }
}

// create stackboxes with switch controller for internal use only
void Widget::make_switch_box(Gtk::Box *box, Glib::ustring label)
{
  Gxw::Switch *regler = static_cast<Gxw::Switch*>( &m_switch);
  if (regler)
  {
    Gtk::Label* pr = new Gtk::Label(label, 0);
    pr->set_name("amplabel");
    regler->cp_configure("switch", label, 0, 1, 1);
    regler->set_name(plug_name);
    regler->set_base_name( "button" );
    regler->set_relief(Gtk::RELIEF_NONE);
    Gtk::VBox* b1 = new Gtk::VBox();
    box->pack_start( *Gtk::manage(b1), Gtk::PACK_EXPAND_PADDING);
    box->pack_start( *Gtk::manage(pr),Gtk::PACK_SHRINK); 
    box->pack_start(*regler,Gtk::PACK_SHRINK);
    Gtk::VBox* b2 = new Gtk::VBox();
    box->pack_start( *Gtk::manage(b2), Gtk::PACK_EXPAND_PADDING);
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

void Widget::set_tooltips() {
    gtk_settings_set_long_property(
        gtk_settings_get_default(), "gtk-enable-tooltips", m_switch.get_active(), "gx_mbcompressor");
}

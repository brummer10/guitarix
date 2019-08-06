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
#include <iomanip>


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
    clip1,
    clip2,
    clip3,
    clip4,
    clips1,
    clips2,
    clips3,
    clips4,
    speed1,
    speed2,
    speed3,
    speed4,
    bar1,
    bar2,
    bar3,
    bar4,
    gain,
    level1,
    level2,
    level3,
    level4,
    mix,
    play1,
    play2,
    play3,
    play4,
    rplay1,
    rplay2,
    rplay3,
    rplay4,
    playh1,
    playh2,
    playh3,
    playh4,
    rec1,
    rec2,
    rec3,
    rec4,
    reset1,
    reset2,
    reset3,
    reset4,
} PortIndex;
*/
Gtk::Widget* Widget::get_controller_by_port(uint32_t port_index)
{
  switch ((PortIndex)port_index )
  {
    case clip1:
      return &m_slider[0];
    case clip2:
      return &m_slider[1];
    case clip3:
      return &m_slider[2];
    case clip4:
      return &m_slider[3];
    case clips1:
      return &m_slider[4];
    case clips2:
      return &m_slider[5];
    case clips3:
      return &m_slider[6];
    case clips4:
      return &m_slider[7];
    case speed1:
      return &m_slider[8];
    case speed2:
      return &m_slider[9];
    case speed3:
      return &m_slider[10];
    case speed4:
      return &m_slider[11];
    case bar1:
      return &m_pdisplay[0];
    case bar2:
      return &m_pdisplay[1];
    case bar3:
      return &m_pdisplay[2];
    case bar4:
      return &m_pdisplay[3];
    case gain:
      return &m_bigknob[0];
    case level1:
      return &m_slider[12];
    case level2:
      return &m_slider[13];
    case level3:
      return &m_slider[14];
    case level4:
      return &m_slider[15];
    case mix:
      return &m_bigknob[1];
    case play1:
      return &m_switch[0];
    case play2:
      return &m_switch[1];
    case play3:
      return &m_switch[2];
    case play4:
      return &m_switch[3];
    case rplay1:
      return &m_switch[4];
    case rplay2:
      return &m_switch[5];
    case rplay3:
      return &m_switch[6];
    case rplay4:
      return &m_switch[7];
    case playh1:
      return &m_pdisplay[4];
    case playh2:
      return &m_pdisplay[5];
    case playh3:
      return &m_pdisplay[6];
    case playh4:
      return &m_pdisplay[7];
    case rec1:
      return &m_switch[8];
    case rec2:
      return &m_switch[9];
    case rec3:
      return &m_switch[10];
    case rec4:
      return &m_switch[11];
    case reset1:
      return &m_switch[12];
    case reset2:
      return &m_switch[13];
    case reset3:
      return &m_switch[14];
    case reset4:
      return &m_switch[15];

   default:
      return NULL;
  } 
}

Widget::Widget(Glib::ustring plugname):
plug_name(plugname),
logo("Live Looper")
{
  for (uint32_t i = 1;i<5;i++) {
    m_paintbox[i].property_paint_func() = "box_uni_2_expose";
    m_paintbox[i].set_name(plug_name);
    m_paintbox[i].set_border_width(5);
    m_paintbox[i].pack_start(m_vbox[i]);
  }

  m_fr[0].set_label("Tape 1");
  m_fr[0].add(m_paintbox[1]);
  m_fr[1].set_label("Tape 2");
  m_fr[1].add(m_paintbox[2]);
  m_fr[2].set_label("Tape 3");
  m_fr[2].add(m_paintbox[3]);
  m_fr[3].set_label("Tape 4");
  m_fr[3].add(m_paintbox[4]);
  // create controllers for port name
  make_radio_controller_box(&m_vbox[1], "buffer", false,   0.0, 96.0, 1.0 , bar1, reset1, rec1);
  make_radio_controller_box(&m_vbox[2], "buffer",false,   0.0, 96.0, 1.0 , bar2, reset2, rec2);
  make_radio_controller_box(&m_vbox[3], "buffer",false,   0.0, 96.0, 1.0 , bar3, reset3, rec3);
  make_radio_controller_box(&m_vbox[4], "buffer",false,   0.0, 96.0, 1.0 , bar4, reset4, rec4);
  make_controller_box(&m_vbox[5], "gain", true, -2e+01f, 12.0f, 0.1f, gain);
  make_controller_box(&m_vbox[1], "gain", true,   0.0f, 1e+02f, 1.0f , level1);
  make_controller_box(&m_vbox[2], "gain", true,   0.0f, 1e+02f, 1.0f , level2);
  make_controller_box(&m_vbox[3], "gain", true,   0.0f, 1e+02f, 1.0f , level3);
  make_controller_box(&m_vbox[4], "gain", true,   0.0f, 1e+02f, 1.0f , level4);
  make_controller_box(&m_vbox[5], "mix", true,  0.0f, 1.5e+02f, 1.0f, mix);
  make_controller_box(&m_vbox[1], "speed", true,   -0.9f, 0.9f, 0.01f  , speed1);
  make_controller_box(&m_vbox[2], "speed", true,   -0.9f, 0.9f, 0.01f  , speed2);
  make_controller_box(&m_vbox[3], "speed", true,   -0.9f, 0.9f, 0.01f  , speed3);
  make_controller_box(&m_vbox[4], "speed", true,   -0.9f, 0.9f, 0.01f  , speed4);
  make_controller_box(&m_vbox[1], "", false,   0.0f, 1e+02f, 1.0f , clip1);
  make_controller_box(&m_vbox[2], "", false,   0.0f, 1e+02f, 1.0f , clip2);
  make_controller_box(&m_vbox[3], "", false,   0.0f, 1e+02f, 1.0f , clip3);
  make_controller_box(&m_vbox[4], "", false,  0.0f, 1e+02f, 1.0f , clip4);
  make_controller_box(&m_vbox[1], "", false,   0.0f, 1e+02f, 1.0f , clips1);
  make_controller_box(&m_vbox[2], "", false,   0.0f, 1e+02f, 1.0f , clips2);
  make_controller_box(&m_vbox[3], "", false,   0.0f, 1e+02f, 1.0f , clips3);
  make_controller_box(&m_vbox[4], "", false,   0.0f, 1e+02f, 1.0f , clips4);
  m_vbox[1].pack_start(m_hbox[13]);
  m_vbox[2].pack_start(m_hbox[14]);
  m_vbox[3].pack_start(m_hbox[15]);
  m_vbox[4].pack_start(m_hbox[16]);
  m_hbox[1].pack_start(m_hbox[5]);
  m_hbox[2].pack_start(m_hbox[6]);
  m_hbox[3].pack_start(m_hbox[7]);
  m_hbox[4].pack_start(m_hbox[8]);
  make_radio_switch_box(&m_hbox[1], play1, rplay1, "pbutton");
  make_radio_switch_box(&m_hbox[2], play2, rplay2, "pbutton");
  make_radio_switch_box(&m_hbox[3], play3, rplay3, "pbutton");
  make_radio_switch_box(&m_hbox[4], play4, rplay4, "pbutton");
  make_radio_switch_box(&m_hbox[1], rplay1, play1, "prbutton");
  make_radio_switch_box(&m_hbox[2], rplay2, play2, "prbutton");
  make_radio_switch_box(&m_hbox[3], rplay3, play3, "prbutton");
  make_radio_switch_box(&m_hbox[4], rplay4, play4, "prbutton");
  make_portdisplay(&m_hbox[13], "playh1",   0.0, 1000.0, 1.0 , playh1, clips1, clip1);
  make_portdisplay(&m_hbox[14], "playh2",   0.0, 1000.0, 1.0 , playh2, clips2, clip2);
  make_portdisplay(&m_hbox[15], "playh3",   0.0, 1000.0, 1.0 , playh3, clips3, clip3);
  make_portdisplay(&m_hbox[16], "playh4",   0.0, 1000.0, 1.0 , playh4, clips4, clip4);
  make_switch_box(&m_hbox[1], rec1, "rbutton");
  make_switch_box(&m_hbox[2], rec2, "rbutton");
  make_switch_box(&m_hbox[3], rec3, "rbutton");
  make_switch_box(&m_hbox[4], rec4, "rbutton");
  make_reset_switch_box(&m_hbox[1], reset1, clips1, clip1, "button");
  make_reset_switch_box(&m_hbox[2], reset2, clips2, clip2, "button");
  make_reset_switch_box(&m_hbox[3], reset3, clips3, clip3, "button");
  make_reset_switch_box(&m_hbox[4], reset4, clips4, clip4, "button");
  m_hbox[1].pack_start(m_hbox[9]);
  m_hbox[2].pack_start(m_hbox[10]);
  m_hbox[3].pack_start(m_hbox[11]);
  m_hbox[4].pack_start(m_hbox[12]);

 
 // set propertys for the main paintbox holding the skin
  m_paintbox[0].set_border_width(24);
  m_paintbox[0].set_spacing(4);
  m_paintbox[0].set_homogeneous(false);
  m_paintbox[0].set_name(plug_name);
  m_paintbox[0].property_paint_func() = "gx_rack_unit_expose";
  add(m_paintbox[0]);
  // box for the controllers
  m_hbox[0].set_spacing(4);
  m_hbox[0].set_border_width(4);
  m_hbox[0].set_homogeneous(false);
  // set a vertical box in the paintbox
  m_vbox[6].set_border_width(7);
  m_vbox[7].set_border_width(7);
  m_paintbox[0].pack_start(m_vbox[8]);
  //
  m_vbox[1].pack_start(m_hbox[1]);
  m_vbox[2].pack_start(m_hbox[2]);
  m_vbox[3].pack_start(m_hbox[3]);
  m_vbox[4].pack_start(m_hbox[4]);
  // modify logo layout
  Pango::FontDescription font_desc = logo.get_style_context()->get_font();
  font_desc.set_size(int(14*Pango::SCALE));
  font_desc.set_weight(Pango::WEIGHT_BOLD);
  logo.override_font(font_desc);
  m_hbox1_.set_spacing(64);
  logo.set_name("logo");
  m_vbox[8].pack_start(m_hbox1_, Gtk::PACK_SHRINK);
  m_hbox1_.pack_start(m_vbox1_, Gtk::PACK_EXPAND_PADDING);
  m_hbox1_.pack_end(m_vbox2_, Gtk::PACK_SHRINK);
  m_hbox1_.pack_end(logo, Gtk::PACK_SHRINK);
  // and controller box on top
  m_vbox[8].pack_start(m_hbox[0], Gtk::PACK_SHRINK);
  // put boxed controllers into controller box
  m_hbox[0].pack_start(m_vbox[6], Gtk::PACK_EXPAND_PADDING);
  m_hbox[0].pack_start(m_vbox[0]);
  m_hbox[0].pack_start(m_fr[0]);
  m_hbox[0].pack_start(m_fr[1]);
  m_hbox[0].pack_start(m_fr[2]);
  m_hbox[0].pack_start(m_fr[3]);
  m_hbox[0].pack_start(m_vbox[5]);
  m_hbox[0].pack_start(m_vbox[7], Gtk::PACK_EXPAND_PADDING);

  // connect expose handler as resize handler
  // m_paintbox.signal_draw().connect(
  //    sigc::mem_fun(this, &Widget::_draw), true);

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
  m_paintbox[0].get_window()->get_geometry(x, y, width, height);
  //double_t height = m_paintbox.get_window()->get_height();
  m_paintbox[0].set_border_width(height/10);
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
    regler->cp_set_var("no_log");
    regler->set_show_value(false);
    regler->set_name(plug_name);
    regler->signal_value_changed().connect(sigc::bind(sigc::mem_fun(
           *this, &Widget::on_value_changed), port_name));
  }
}

// create stackboxes with controllers for port name
void Widget::make_controller_box(Gtk::Box *box,
                                 Glib::ustring label,
                                 bool show_value,
                                 float min, float max,
                                 float digits,
                                 PortIndex port_name)
{
  Gxw::Regler *regler = static_cast<Gxw::Regler*>(
                                    get_controller_by_port(port_name));
  if (regler)
  {
    // use label images instead simple string labes
    /*Glib::ustring  label_image = GX_LV2_STYLE_DIR;
    label_image += "/";
    label_image += label;
    label_image += "-label.png";
    Gtk::Image *pr = new Gtk::Image(label_image);*/

    Gtk::VBox* b1 = new Gtk::VBox();
    box->pack_start( *Gtk::manage(b1), Gtk::PACK_EXPAND_PADDING);
    if (!label.empty()) {
    Gtk::Label* pr = new Gtk::Label(label, 0);
    pr->set_name("amplabel");
    box->pack_start( *Gtk::manage(pr),Gtk::PACK_SHRINK);
    }
    regler->cp_configure("KNOB", label, min, max, digits);
    regler->cp_set_var("no_log");
    regler->set_show_value(show_value);
    regler->set_name(plug_name);
    box->pack_start(*regler,Gtk::PACK_SHRINK);
    Gtk::VBox* b2 = new Gtk::VBox();
    box->pack_start( *Gtk::manage(b2), Gtk::PACK_EXPAND_PADDING);
    regler->signal_value_changed().connect(sigc::bind(sigc::mem_fun(
           *this, &Widget::on_value_changed), port_name));
  }
}

// create stackboxes with controllers for port name
void Widget::make_radio_controller_box(Gtk::Box *box,
                                 Glib::ustring label,
                                 bool show_value,
                                 float min, float max,
                                 float digits,
                                 PortIndex port_name,
                                 PortIndex port_name1,
                                 PortIndex port_name2)
{
  Gxw::Regler *regler = static_cast<Gxw::Regler*>(
                                    get_controller_by_port(port_name));
  Gxw::Switch *regler1 = static_cast<Gxw::Switch*>(
                                    get_controller_by_port(port_name1));
  if (regler)
  {
    // use label images instead simple string labes
    /*Glib::ustring  label_image = GX_LV2_STYLE_DIR;
    label_image += "/";
    label_image += label;
    label_image += "-label.png";
    Gtk::Image *pr = new Gtk::Image(label_image);*/

    Gtk::VBox* b1 = new Gtk::VBox();
    box->pack_start( *Gtk::manage(b1), Gtk::PACK_EXPAND_PADDING);
    if (!label.empty()) {
    Gtk::Label* pr = new Gtk::Label(label, 0);
    pr->set_name("amplabel");
    box->pack_start( *Gtk::manage(pr),Gtk::PACK_SHRINK);
    }
    regler->cp_configure("KNOB", label, min, max, digits);
    regler->cp_set_var("no_log");
    regler->set_show_value(show_value);
    regler->set_name(plug_name);
    box->pack_start(*regler,Gtk::PACK_SHRINK);
    Gtk::VBox* b2 = new Gtk::VBox();
    box->pack_start( *Gtk::manage(b2), Gtk::PACK_EXPAND_PADDING);
    regler->signal_value_changed().connect(sigc::bind(sigc::mem_fun(
           *this, &Widget::on_value_changed), port_name));
    regler->signal_value_changed().connect(sigc::bind(sigc::bind(sigc::bind(sigc::mem_fun(
           *this, &Widget::on_radio_value_changed), port_name), port_name1), port_name2));
    regler1->signal_toggled().connect(sigc::bind(sigc::bind(sigc::bind(sigc::mem_fun(
           *this, &Widget::on_radio_value_changed), port_name), port_name1), port_name2));
  }
}

// 
void Widget::on_radio_value_changed(uint32_t port_index2,
                                    uint32_t port_index1,
                                    uint32_t port_index)
{
  Gxw::PortDisplay *regler = static_cast<Gxw::PortDisplay*>(
                                    get_controller_by_port(port_index));
  Gxw::Regler *regler1 = static_cast<Gxw::Regler*>(
                                    get_controller_by_port(port_index1));
  Gxw::Regler *regler2 = static_cast<Gxw::Regler*>(
                                    get_controller_by_port(port_index2));
  if (regler)
  {
    float value = regler->cp_get_value();
    if (value > 87) regler1->cp_set_value(0);
    else if (value == 0) regler2->cp_set_value(0);
  }
}

void Widget::make_portdisplay(Gtk::Box *box,
                                 Glib::ustring label,
                                 float min, float max,
                                 float digits,
                                 PortIndex port_name,
                                 PortIndex port_low,
                                 PortIndex port_high)
{
  Gxw::Regler *regler = static_cast<Gxw::Regler*>(
                                    get_controller_by_port(port_name));
  Gxw::Regler *regler1 = static_cast<Gxw::Regler*>(
                                    get_controller_by_port(port_low));
  Gxw::Regler *regler2 = static_cast<Gxw::Regler*>(
                                    get_controller_by_port(port_high));
  if (regler)
  {
    regler->cp_configure("KNOB", label, min, max, digits);
    regler->cp_set_var("no_log");
    regler->set_show_value(false);
    regler->set_name("playhead");
    Gtk::HBox* b1 = new Gtk::HBox();
    box->pack_start( *Gtk::manage(b1), Gtk::PACK_EXPAND_PADDING);
    Gtk::EventBox* e_box = new Gtk::EventBox();
    e_box->set_name(plug_name);
    e_box->set_size_request(-1, -1);
    e_box->set_border_width(0);
    e_box->set_visible_window(true);
    e_box->set_above_child(true);
    e_box->add(*manage(static_cast<Gtk::Widget*>(regler)));
    box->pack_start(*Gtk::manage(e_box));
    Gtk::HBox* b2 = new Gtk::HBox();
    box->pack_start( *Gtk::manage(b2), Gtk::PACK_EXPAND_PADDING);
    regler->signal_value_changed().connect(sigc::bind(sigc::mem_fun(
           *this, &Widget::on_value_changed), port_name));
    regler1->signal_value_changed().connect(sigc::bind(sigc::bind(sigc::bind(sigc::mem_fun(
           *this, &Widget::on_portvalue_changed), port_name),port_low),port_high));
    regler2->signal_value_changed().connect(sigc::bind(sigc::bind(sigc::bind(sigc::mem_fun(
           *this, &Widget::on_portvalue_changed), port_name),port_low),port_high));
  }
}

// 
void Widget::on_portvalue_changed(uint32_t port_index2,
                                  uint32_t port_index1,
                                  uint32_t port_index)
{
  Gxw::PortDisplay *regler = static_cast<Gxw::PortDisplay*>(
                                    get_controller_by_port(port_index));
  Gxw::Regler *regler1 = static_cast<Gxw::Regler*>(
                                    get_controller_by_port(port_index1));
  Gxw::Regler *regler2 = static_cast<Gxw::Regler*>(
                                    get_controller_by_port(port_index2));
  if (regler)
  {
    float value = regler->cp_get_value();
    float low = regler1->cp_get_value();
    float high = 100 - regler2->cp_get_value();
    regler->set_state(int(low),int(high));
    float set = (low + high)*0.001;
    regler->cp_set_value(value+set);
  }
}

// create stackboxes with switch controller for port name
void Widget::make_switch_box(Gtk::Box *box,
                             PortIndex port_name,
                             Glib::ustring basename)
{
  Gxw::Switch *regler = static_cast<Gxw::Switch*>(
                                    get_controller_by_port(port_name));
  if (regler)
  {
    regler->cp_configure("switch", "", 0, 1, 1);
    regler->cp_set_var("no_log");
    regler->set_name(plug_name);
    regler->set_base_name( basename );
    //regler->set_relief(Gtk::RELIEF_NONE);
    box->pack_start(*regler,Gtk::PACK_SHRINK);
    regler->signal_toggled().connect(sigc::bind(sigc::mem_fun(
        *this, &Widget::on_value_changed), port_name));
  }
}

// create stackboxes with switch controller for port name
void Widget::make_reset_switch_box(Gtk::Box *box,
                             PortIndex port_name,
                             PortIndex port_name1,
                             PortIndex port_name2,
                             Glib::ustring basename)
{
  Gxw::Switch *regler = static_cast<Gxw::Switch*>(
                                    get_controller_by_port(port_name));
  if (regler)
  {
    regler->cp_configure("switch", "", 0, 1, 1);
    regler->cp_set_var("no_log");
    regler->set_name(plug_name);
    regler->set_base_name( basename );
    //regler->set_relief(Gtk::RELIEF_NONE);
    box->pack_start(*regler,Gtk::PACK_SHRINK);
    regler->signal_toggled().connect(sigc::bind(sigc::mem_fun(
        *this, &Widget::on_value_changed), port_name));
    regler->signal_toggled().connect(sigc::bind(sigc::bind(sigc::bind(sigc::mem_fun(
        *this, &Widget::on_reset), port_name), port_name1), port_name2));
  }
}

void Widget::on_reset(uint32_t port_index2, uint32_t port_index1, uint32_t port_index)
{
  Gxw::Regler *regler = static_cast<Gxw::Regler*>(
                                    get_controller_by_port(port_index));
  Gxw::Regler *regler1 = static_cast<Gxw::Regler*>(
                                    get_controller_by_port(port_index1));
  Gxw::Regler *regler2 = static_cast<Gxw::Regler*>(
                                    get_controller_by_port(port_index2));
   if (regler)
  {
    float value = regler->cp_get_value();
   if (value>0.) {
        regler1->cp_set_value(0);
        regler2->cp_set_value(100);
    }
   } 
}

// create stackboxes with switch controller for port name
void Widget::make_radio_switch_box(Gtk::Box *box,
                             PortIndex port_name,
                             PortIndex port_name1,
                             Glib::ustring basename)
{
  Gxw::Switch *regler = static_cast<Gxw::Switch*>(
                                    get_controller_by_port(port_name));
  if (regler)
  {
    regler->cp_configure("switch", "", 0, 1, 1);
    regler->cp_set_var("no_log");
    regler->set_name(plug_name);
    regler->set_base_name( basename );
    //regler->set_relief(Gtk::RELIEF_NONE);
    box->pack_start(*regler,Gtk::PACK_SHRINK);
    regler->signal_toggled().connect(sigc::bind(sigc::mem_fun(
        *this, &Widget::on_value_changed), port_name));
    regler->signal_toggled().connect(sigc::bind(sigc::bind(sigc::mem_fun(
        *this, &Widget::on_radio_changed), port_name), port_name1));
  }
}

void Widget::on_radio_changed(uint32_t port_index1, uint32_t port_index)
{
  Gxw::Regler *regler = static_cast<Gxw::Regler*>(
                                    get_controller_by_port(port_index));
  if (regler)
  {
    float value = regler->cp_get_value();
    Gxw::Regler *regler1 = static_cast<Gxw::Regler*>(
                                    get_controller_by_port(port_index1));
    if (value>0.) regler1->cp_set_value(0);
   } 
}

Glib::ustring logarithmic_format_value(double v, int prec) {
    if (v < -4) {
	return Glib::ustring::format(std::setprecision(prec+1), pow(10.0,v));
    } else {
	return Glib::ustring::format(std::fixed, std::setprecision(prec-floor(v)), pow(10.0,v));
    }
}

int logarithmic_input_value(gpointer obj, gpointer nv)
{
    GtkEntry *entry = GTK_ENTRY(obj);
    double *new_val = static_cast<double*>(nv);
    gchar *err = NULL;
    *new_val = g_strtod(gtk_entry_get_text(entry), &err);
    if (*err)
	return GTK_INPUT_ERROR;
    else {
	*new_val = log10(*new_val);
	return TRUE;
    }
}

// create stackboxes with controllers for port name
void Widget::make_log_controller_box(Gtk::Box *box,
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

    Gtk::VBox* b1 = new Gtk::VBox();
    box->pack_start( *Gtk::manage(b1), Gtk::PACK_EXPAND_PADDING);
    box->pack_start( *Gtk::manage(pr),Gtk::PACK_SHRINK);
    
	double up = log10(max);
	double step = log10(digits);
	regler->cp_configure("", label, log10(min), up, step);
	int prec = 0;
	float d = log10((digits-1)*max);
	if (up > 0) {
	    prec = up;
	    if (d < 0) {
		prec -= floor(d);
	    }
	} else if (d < 0) {
	    prec = -floor(d);
	}
	regler->signal_format_value().connect(
	    sigc::bind(
		sigc::ptr_fun(logarithmic_format_value),
		prec));
	regler->signal_input_value().connect(
	    sigc::ptr_fun(logarithmic_input_value));
     
    regler->set_show_value(true);
    regler->set_name(plug_name);
    box->pack_start(*regler,Gtk::PACK_SHRINK);
    Gtk::VBox* b2 = new Gtk::VBox();
    box->pack_start( *Gtk::manage(b2), Gtk::PACK_EXPAND_PADDING);
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
    if (regler)
    {
      Glib::ustring v = regler->cp_get_var();
      if (v.empty()) {
          //fprintf(stderr,"value get %f\n set %f\n",value,log10(value) );
          regler->cp_set_value(log10(value));
      } else {
          regler->cp_set_value(value);
      }
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
    
    Glib::ustring v = regler->cp_get_var();
    if (v.empty()) {
        //fprintf(stderr,"value set %f\n get %f\n",value,pow(10.0,value));
        value = pow(10.0,value);
        write_function(controller, port_index, sizeof(float), 0,
                                    static_cast<const void*>(&value));
    } else {
       write_function(controller, port_index, sizeof(float), 0,
                                    static_cast<const void*>(&value));
    }
   } 
}


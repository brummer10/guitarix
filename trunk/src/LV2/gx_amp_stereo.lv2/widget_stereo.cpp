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


#include "widget_stereo.h"

#include <iostream>

#define min(x, y) (((x) < (y)) ? (x) : (y))

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
    case GAIN1:
      return &m_bigknob;
    case PREGAIN:
      return &m_bigknob1;
    case WET_DRY:
      return &m_bigknob2;
    case DRIVE:
      return &m_bigknob3;
    case MIDDLE:
      return &m_smallknob1;
    case BASS:
      return &m_smallknob2;
    case TREBLE:
      return &m_smallknob3;
    case MODEL:
      return &m_selector;
    case T_MODEL:
      return &t_selector;
    case C_MODEL:
      return &c_selector;
    case CLevel:
      return &m_smallknob4;
    case ALevel:
      return &m_bigknob4;
    default:
      return NULL;
  }
}

Widget::Widget(Glib::ustring plugname):
plug_name(plugname),
pir(GX_LV2_STYLE_DIR"/logo.png")
{

  // create all selectors
  Glib::ustring tubes[] = {"12ax7","12AU7","12AT7","6DJ8","6C16","6V6","12ax7 feedback",
  "12AU7 feedback","12AT7 feedback","6DJ8 feedback","pre 12ax7/ master 6V6","pre 12AU7/ master 6V6",
  "pre 12AT7/ master 6V6","pre 6DJ8/ master 6V6","pre 12ax7/ push-pull 6V6","pre 12AU7/ push-pull 6V6",
  "pre 12AT7/ push pull 6V6","pre 6DJ8/ push-pull 6V6"
  };
  tubes_size = sizeof(tubes) / sizeof(tubes[0]);
  
  make_selector("Tubes", tubes, tubes_size, 0, 1.0, MODEL);

  m_hboxsel1.pack_start(m_selector,Gtk::PACK_SHRINK);
  m_hboxsel1.pack_start(m_hboxsel2,Gtk::PACK_EXPAND_PADDING);
  m_vboxsel.pack_start(m_hboxsel1,Gtk::PACK_EXPAND_PADDING);

  Glib::ustring ts[] = {"default","Bassman Style","Twin Reverb Style","Princeton Style","JCM-800 Style",
  "JCM-2000 Style","M-Lead Style","M2199 Style","AC-30 Style","Mesa Boogie Style","SOL 100 Style","JTM-45 Style","AC-15 Style",
  "Peavey Style","Ibanez Style","Roland Style","Ampeg Style","Rev.Rocket Style","MIG 100 H Style","Triple Giant Style",
  "Trio Preamp Style","Hughes&Kettner Style","Fender Junior Style","Fender Style","Fender Deville Style",
  "Gibsen", "Off"
  };
  static const size_t ts_size = sizeof(ts) / sizeof(ts[0]);
  
  make_selector("Tonestacks", ts, ts_size, 0,1.0, T_MODEL);


  Glib::ustring cab[] = {"4x12","2x12","1x12","4x10","2x10","HighGain Style","Twin Style",
  "Bassman Style","Marshall Style","AC30 Style","Princeton Style","A2 Style","1x15","Mesa Style","Briliant","Vitalize",
  "Charisma","1x8", "Off"
  };
  static const size_t cab_size = sizeof(cab) / sizeof(cab[0]);
  
  make_selector("Cabinets", cab, cab_size, 0, 1.0, C_MODEL);

  // create all controllers
  make_controller_box(&m_vbox, "Mastergain", -20, 20, 0.1, GAIN1);
  make_controller_box(&m_vbox1, "Pregain", -20, 20, 0.1, PREGAIN);
  make_controller_box(&m_vbox2, "Distortion", 1, 100, 1, WET_DRY);
  make_controller_box(&m_vbox3, "Drive", 0.01, 1, 0.01, DRIVE);
  make_controller_box(&m_vbox4, "Mid", 0, 1, 0.01, MIDDLE);
  make_controller_box(&m_vbox5, "Bass", 0, 1, 0.01, BASS);
  make_controller_box(&m_vbox6, "Treble", 0, 1, 0.01, TREBLE);
  // put cabinet selector above cab controller
  m_vbox7.pack_start(c_selector,Gtk::PACK_SHRINK);
  make_controller_box(&m_vbox7, "Cabinet", 1, 20, 1, CLevel);
  make_controller_box(&m_vbox8, "Presence", 1, 10, 1, ALevel);

  // set propertys for the main paintbox holding the skin
 // m_paintbox.set_border_width(30);
 // m_paintbox.set_spacing(12);
  m_paintbox.set_homogeneous(false);
  m_paintbox.set_name(plug_name);
  m_paintbox.property_paint_func() = "gx_lv2_unit_expose";
  add(m_paintbox);
  // box for the controllers
  m_hbox_.set_spacing(12);
  m_hbox_.set_homogeneous(false);
  // this box set space for the upper part of the skin
 // m_hbox1_.set_spacing(12);
  m_hbox1_.set_border_width(10);
  m_hbox1_.pack_end(pir, Gtk::PACK_SHRINK);
  // set a vertical box in the paintbox
  m_paintbox.pack_start(m_vbox_, Gtk::PACK_EXPAND_PADDING, 35);
 // m_vbox_.set_border_width(25);
  // and put space box on top
  m_vbox_.pack_start(m_hbox1_, Gtk::PACK_EXPAND_PADDING);
  // and controller box on bottem
  m_vbox_.pack_start(m_hbox_,Gtk::PACK_SHRINK);
  // amp controllers including the tube selector
  m_hboxsel.set_spacing(12);
  m_hboxsel.set_homogeneous(false);
  m_hboxsel.pack_start(m_vbox1);
  m_hboxsel.pack_start(m_vbox2);
  m_hboxsel.pack_start(m_vbox3);
  m_hboxsel.pack_start(m_vbox8);
  m_hboxsel.pack_start(m_vbox);
  m_vboxsel.pack_start(m_hboxsel);

  // put boxed controllers into controller box
  m_hbox_.pack_start(m_vboxhh);
  m_hbox_.pack_start(m_vboxsel);
  m_hbox_.pack_start(m_vbox7);
  // etxra box for the boxed tonestack controllers
  m_hboxtonestack1.pack_start(m_hboxtonestack3,Gtk::PACK_EXPAND_PADDING);
  m_hboxtonestack1.pack_start(t_selector,Gtk::PACK_SHRINK);
  m_hboxtonestack1.pack_start(m_hboxtonestack2,Gtk::PACK_EXPAND_PADDING);
  
  m_vboxtonestack.pack_start(m_hboxtonestack1,Gtk::PACK_SHRINK);
  m_vboxtonestack.pack_start(m_hbox,Gtk::PACK_EXPAND_PADDING);
  m_hbox.set_border_width(8);
  m_hbox.pack_start(m_vbox5);
  m_hbox.pack_start(m_vbox4);
  m_hbox.pack_start(m_vbox6);
  m_hbox.pack_start(m_vboxii);
  m_hbox.set_spacing(5);
  // add tonestack controller box to main controller box
  m_hbox_.pack_start(m_vboxtonestack);

  // connect expose handler as resize handler
 // m_paintbox.signal_draw().connect(
  //  sigc::mem_fun(this, &Widget::_draw), true);

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
    Glib::ustring  label_image = GX_LV2_STYLE_DIR;
    //label_image += "/";
    //label_image += label;
    //label_image += "-label.png";
    //Gtk::Image *pr = new Gtk::Image(label_image);

    Gtk::VBox* b1 = new Gtk::VBox();
    box->pack_start( *Gtk::manage(b1), Gtk::PACK_EXPAND_PADDING);
    box->pack_start( *Gtk::manage(pr),Gtk::PACK_SHRINK);
    regler->cp_configure("KNOB", label, min, max, digits);
    regler->set_show_value(false);
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

void Widget::set_sensitive_state(float state)
{
  bool set;
  if (( state > 0) ? (set = false) : (set = true));
  c_selector.set_sensitive(set);
  m_smallknob4.set_sensitive(set);
  m_bigknob4.set_sensitive(set);
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
    if (regler)
    {
      float value = *static_cast<const float*>(buffer);
      regler->cp_set_value(value);
     //  check_for_skin(port_index, static_cast<int>(value));
    }
    if (port_index == SCHEDULE)
    {
      float value = *static_cast<const float*>(buffer);
      set_sensitive_state(value);
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
    //check_for_skin(port_index, static_cast<int>(min(tubes_size-1,value)));
  }
}

void Widget::check_for_skin(uint32_t port_index, float model)
{
  if (port_index == MODEL)
    change_skin(static_cast<int>(model));
}

inline std::string to_string(int _Val)
{   // convert int to string
        char _Buf[4];
        sprintf(_Buf, "%d", _Val);
        return (std::string(_Buf));
}
void Widget::change_skin(int model)
{
  Glib::ustring rcfile =GX_LV2_STYLE_DIR;
  rcfile +="/gx_lv2-";
  rcfile += to_string(model);
  rcfile += ".rc";
  gtk_rc_parse(rcfile.c_str());
  //gtk_rc_reparse_all_for_settings(gtk_settings_get_default(),true);
  Glib::ustring o = "widget \"*." + plug_name + "\" style:highest \"gx_lv2-" + to_string(model) + "\"";
  gtk_rc_parse_string(o.c_str());
  gtk_rc_reset_styles(gtk_settings_get_default());
}

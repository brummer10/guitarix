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


#include "widget_stereo.h"

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
  
  // create all selectors
  Glib::ustring tubes[] = {"12ax7","12AU7","12AT7","6DJ8","6C16","6V6","12ax7 feedback",
  "12AU7 feedback","12AT7 feedback","6DJ8 feedback","pre 12ax7/ master 6V6","pre 12AU7/ master 6V6",
  "pre 12AT7/ master 6V6","pre 6DJ8/ master 6V6","pre 12ax7/ push-pull 6V6","pre 12AU7/ push-pull 6V6",
  "pre 12AT7/ push pull 6V6","pre 6DJ8/ push-pull 6V6"
  };
  static const size_t tubes_size = sizeof(tubes) / sizeof(tubes[0]);
  
  make_selector_box(&m_selector, "Tubes", tubes, tubes_size, 
                    MODEL, 0, static_cast<float>(tubes_size+1), 1.0, model, plug_name);

  m_hboxsel1.pack_start(m_selector,Gtk::PACK_SHRINK);
  m_hboxsel1.pack_start(m_hboxsel2,Gtk::PACK_EXPAND_PADDING);
  m_vboxsel.pack_start(m_hboxsel1,Gtk::PACK_EXPAND_PADDING);

  Glib::ustring ts[] = {"default","Bassman","Twin Reverb","Princeton","JCM-800",
  "JCM-2000","M-Lead","M2199","AC-30","Mesa Boogie","SOL 100","JTM-45","AC-15",
  "Peavey","Ibanez","Roland","Ampeg","Rev.Rocket","MIG 100 H","Triple Giant",
  "Trio Preamp","Hughes&Kettner","Fender Junior","Fender","Fender Deville",
  "Gibsen",
  };
  static const size_t ts_size = sizeof(ts) / sizeof(ts[0]);
  
  make_selector_box(&t_selector, "Tonestacks", ts, ts_size, 
                    T_MODEL, 0, static_cast<float>(ts_size+1), 1.0, t_model, plug_name);


  Glib::ustring cab[] = {"4x12","2x12","1x12","4x10","2x10","HighGain","Twin",
  "Bassman","Marshall","AC30","Princeton","A2","1x15","Mesa","Briliant","Vitalize",
  "Charisma","1x8",
  };
  static const size_t cab_size = sizeof(cab) / sizeof(cab[0]);
  
  make_selector_box(&c_selector, "Cabinets", cab, cab_size, 
                    C_MODEL, 0, static_cast<float>(cab_size+1), 1.0, c_model, plug_name);

  // create all controllers
  make_controller_box(&m_vbox, &m_bigknob, "mastergain", -20, 20, 0.1,
                      mastergain,GAIN1, plug_name);
  make_controller_box(&m_vbox1, &m_bigknob1, "pregain", -20, 20, 0.1,
                      pregain,PREGAIN, plug_name);
  make_controller_box(&m_vbox2, &m_bigknob2, "distortion", 1, 100, 1,
                      wet_dry,WET_DRY, plug_name);
  make_controller_box(&m_vbox3, &m_bigknob3, "drive", 0.01, 1, 0.01,
                      drive,DRIVE, plug_name);
  make_controller_box(&m_vbox4, &m_smallknob1, "mid", 0, 1, 0.01,
                      mid,MIDDLE, plug_name);
  make_controller_box(&m_vbox5, &m_smallknob2, "bass", 0, 1, 0.01,
                      bass,BASS, plug_name);
  make_controller_box(&m_vbox6, &m_smallknob3, "treble", 0, 1, 0.01,
                      treble,TREBLE, plug_name);
  // put cabinet selector above cab controller
  m_vbox7.pack_start(c_selector,Gtk::PACK_SHRINK);
  make_controller_box(&m_vbox7, &m_smallknob4, "cabinet", 1, 20, 1,
                     clevel,CLevel, plug_name);
  make_controller_box(&m_vbox8, &m_smallknob5, "presence", 1, 10, 1,
                      alevel,ALevel, plug_name);

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
  
  m_vboxtonestack.pack_start(m_hboxtonestack1);
  m_vboxtonestack.pack_start(m_hbox);
  m_hbox.set_border_width(8);
  m_hbox.pack_start(m_vbox5);
  m_hbox.pack_start(m_vbox4);
  m_hbox.pack_start(m_vbox6);
  m_hbox.pack_start(m_vboxii);
  m_hbox.set_spacing(5);
  // add tonestack controller box to main controller box
  m_hbox_.pack_start(m_vboxtonestack);

  // connect expose handler as resize handler
  m_paintbox.signal_expose_event().connect(
    sigc::mem_fun(this, &Widget::_expose_event), true);

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
                                 float digits, float value,
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
  regler->cp_set_value(value);
  regler->set_name(plug_name);
  regler->signal_value_changed().connect(sigc::bind(sigc::mem_fun(*this,
      &Widget::on_value_changed),port_name));
}

// create stackboxes with controllers from gxw
void Widget::make_controller_box(Gtk::VBox *box,
                                 Gxw::Regler *regler,
                                 Glib::ustring label,
                                 float min, float max,
                                 float digits, float value,
                                 PortIndex port_name,
                                 Glib::ustring plug_name)
{
  //Gtk::Label* pr = new Gtk::Label(label, 0);
  //pr->set_name("amplabel");
  Glib::ustring  label_image = GX_LV2_STYLE_DIR;
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
  regler->signal_value_changed().connect(sigc::bind(sigc::mem_fun(*this,
      &Widget::on_value_changed), port_name));

}
// set borderwith for paintbox when widget resize
// to hold controllers in place
bool Widget::_expose_event(GdkEventExpose *event)
{
  int x, y, width, height, depth;
  m_paintbox.get_window()->get_geometry(x, y, width, height, depth);
  //double_t height = m_paintbox.get_window()->get_height();
  m_paintbox.set_border_width(height/12);
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
        case GAIN1:
          mastergain = value;
          m_bigknob.cp_set_value(mastergain);
          break;
        case PREGAIN:
          pregain = value;
          m_bigknob1.cp_set_value(pregain);
          break;
        case WET_DRY:
          wet_dry = value;
          m_bigknob2.cp_set_value(wet_dry);
          break;
        case DRIVE:
          drive = value;
          m_bigknob3.cp_set_value(drive);
          break;
        case MIDDLE:
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
        case MODEL:
          model = value;
          m_selector.cp_set_value(model);
          break;
        case T_MODEL:
          t_model = value;
          t_selector.cp_set_value(t_model);
          break;
        case C_MODEL:
          c_model = value;
          c_selector.cp_set_value(c_model);
          break;
        case CLevel:
          clevel = value;
          m_smallknob4.cp_set_value(clevel);
          break;
        case ALevel:
          alevel = value;
          m_smallknob5.cp_set_value(alevel);
          break;
        default:
          break;
        }
    }
}
// write value changes to the host->engine
void Widget::on_value_changed(uint32_t port_index)
{
  switch ((PortIndex)port_index )
    {
    case GAIN1:
      mastergain = m_bigknob.get_value();
      //std::cout << "mastergain = " << mastergain << std::endl;
      write_function(controller, (PortIndex)GAIN1,
                 sizeof(float), 0, (const void*)&mastergain);
      break;
    case PREGAIN:
       pregain = m_bigknob1.get_value();
       //std::cout << "pregain = " << pregain << std::endl;
       write_function(controller, (PortIndex)PREGAIN,
                 sizeof(float), 0, (const void*)&pregain);
      break;
    case WET_DRY:
      wet_dry = m_bigknob2.get_value();
      //std::cout << "wet_dry = " << wet_dry << std::endl;
      write_function(controller, (PortIndex)WET_DRY,
                 sizeof(float), 0, (const void*)&wet_dry);
      break;
    case DRIVE:
      drive = m_bigknob3.get_value();
      //std::cout << "drive = " << drive << std::endl;
      write_function(controller, (PortIndex)DRIVE,
                 sizeof(float), 0, (const void*)&drive);
      break;
    case MIDDLE:
      mid = m_smallknob1.get_value();
      //std::cout << "mid = " << mid << std::endl;
      write_function(controller, (PortIndex)MIDDLE,
                 sizeof(float), 0, (const void*)&mid);
      break;
    case BASS:
      bass = m_smallknob2.get_value();
      //std::cout << "bass = " << bass << std::endl;
      write_function(controller, (PortIndex)BASS,
                 sizeof(float), 0, (const void*)&bass);
      break;
    case TREBLE:
      treble = m_smallknob3.get_value();
      //std::cout << "treble = " << treble << std::endl;
      write_function(controller, (PortIndex)TREBLE,
                 sizeof(float), 0, (const void*)&treble);
      break;
    case MODEL:
      model = m_selector.get_value();
      //std::cout << "model = " << model << std::endl;
      write_function(controller, (PortIndex)MODEL,
                 sizeof(float), 0, (const void*)&model);
      change_skin(static_cast<int>(model));
      break;
    case T_MODEL:
      t_model = t_selector.get_value();
      //std::cout << "t_model = " << t_model << std::endl;
      write_function(controller, (PortIndex)T_MODEL,
                 sizeof(float), 0, (const void*)&t_model);
      break;
    case C_MODEL:
      c_model = c_selector.get_value();
      //std::cout << "c_model = " << c_model << std::endl;
      write_function(controller, (PortIndex)C_MODEL,
                 sizeof(float), 0, (const void*)&c_model);
      break;
    case CLevel:
      clevel = m_smallknob4.get_value();
      //std::cout << "clevel = " << clevel << std::endl;
      write_function(controller, (PortIndex)CLevel,
                 sizeof(float), 0, (const void*)&clevel);
      break;
    case ALevel:
      alevel = m_smallknob5.get_value();
      //std::cout << "alevel = " << alevel << std::endl;
      write_function(controller, (PortIndex)ALevel,
                 sizeof(float), 0, (const void*)&alevel);
      break;
    default:
      break;
    }
}

inline std::string to_string(int _Val)
{   // convert int to string
        char _Buf[4];
        sprintf(_Buf, "%d", _Val);
        return (std::string(_Buf));
}
void Widget::change_skin(int model)
{
  std::string rcfile =GX_LV2_STYLE_DIR;
  rcfile +="/gx_lv2-";
  rcfile += to_string(model);
  rcfile += ".rc";
  gtk_rc_parse(rcfile.c_str());
  gtk_rc_reset_styles(gtk_settings_get_default());
}

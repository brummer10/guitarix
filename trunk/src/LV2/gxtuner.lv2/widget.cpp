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
Gtk::Widget* Widget::get_controller_by_port(uint32_t port_index)
{
  switch ((PortIndex)port_index )
  {
    case REFFREQ:
      return &m_bigknob;
    case TUNEMODE:
      return &tuner_tuning;
    case THRESHOLD: 
      return &m_bigknob1;
    default:
      return NULL;
  } 
}

void Widget::set_tuning() {
    static struct TuningTab {
	const char *name;
	const char* key;
	bool flat;
	int notes[6];
    } tuning_tab[] = {
	{ "Standard",    "E",  false, {40, 45, 50, 55, 59, 64}},
	{ "Standard/Es", "Es", true,  {39, 44, 49, 54, 58, 63}},
	{ "Open E",      "E",  false, {40, 47, 52, 56, 59, 64}},
    };
    int mode = tuner_tuning.get_value();
    m_tuner.clear_notes();
    if (mode > 0) {
	m_tuner.set_display_flat(tuning_tab[mode-1].flat);
	for (int i = 0; i < 6; ++i) {
	    m_tuner.push_note(tuning_tab[mode-1].notes[i]);
	}
    } else {
	m_tuner.set_display_flat(false);
    }
}


Widget::Widget(Glib::ustring plugname):
plug_name(plugname)
{
  // create controllers for port name
  
  Glib::ustring modes[] = {"(Chromatic)","Standard/E","Standard/Es", "Open E"};  
  static const size_t _size = sizeof(modes) / sizeof(modes[0]);
  make_selector("Tunning Modes", modes, _size, 0, 1.0, TUNEMODE);
  m_hbox2_.pack_start(tuner_tuning);
  
  make_controller_box(&m_vbox4, "Reference Pitch", 427.0, 453.0, 0.1, REFFREQ);
  make_controller_box(&m_vbox5, "Threshold", 0.001, 0.1, 0.001, THRESHOLD);
  m_hbox2_.pack_start(m_vbox5);
  m_hbox2_.pack_start(m_vbox4);
  m_hbox1_.pack_start(m_tuner);
  m_hbox1_.set_border_width(5);
  m_vbox2.pack_start(m_hbox1_);
  m_vbox2.pack_start(m_hbox2_,Gtk::PACK_SHRINK);
  m_vbox2.set_border_width(5);
  // set propertys for the tuner widget
  m_tuner.set_size_request( 440, 35 ) ;
  m_tuner.set_streaming(true);
  m_tuner.set_display_flat(false);
  m_tuner.set_reference_pitch(440.0);
  // set propertys for the main paintbox holding the skin
  m_paintbox.set_border_width(20);
  m_paintbox.set_spacing(0);
  m_paintbox.set_homogeneous(false);
  m_paintbox.set_name(plug_name);
  m_paintbox.property_paint_func() = "gxhead_expose";
  //m_paintbox.set_size_request( 425, 160 ) ;

  add(m_paintbox);
  m_paintbox.pack_start(m_paintbox1);
  m_paintbox1.property_paint_func() = "RackBox_expose";
  m_paintbox1.set_name(plug_name);
  m_paintbox1.set_border_width(1);
  // One vertical box to wrap all in
  m_vbox2.set_homogeneous(false);
  m_paintbox1.pack_start(m_vbox2);

  // connect expose handler as resize handler
  m_paintbox.signal_expose_event().connect(
    sigc::mem_fun(this, &Widget::_expose_event), true);

  set_app_paintable(true);
  show_all();
}

Widget::~Widget()
{

}

// set borderwith for paintbox when widget resize
// to hold controllers in place
bool Widget::_expose_event(GdkEventExpose *event)
{
  int x, y, width, height, depth;
  m_paintbox.get_window()->get_geometry(x, y, width, height, depth);
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
    //regler->set_show_value(true);
    regler->set_name("amplabel");
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
                             Glib::ustring label2,
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
    regler->set_can_focus( false ) ;

    regler->set_name(plug_name);
    regler->set_base_name( "button" );
    Gtk::VBox* b1 = new Gtk::VBox();
    box->pack_start( *Gtk::manage(b1), Gtk::PACK_EXPAND_PADDING);
    box->pack_start( *Gtk::manage(pr),Gtk::PACK_SHRINK); 
    box->pack_start(*regler,Gtk::PACK_SHRINK);

    // 2nd Label
    Gtk::Label* pr2 = new Gtk::Label(label2, 0);
    pr2->set_name("amplabel");
    box->pack_start( *Gtk::manage(pr2),Gtk::PACK_SHRINK); 

    Gtk::VBox* b2 = new Gtk::VBox();
    box->pack_start( *Gtk::manage(b2), Gtk::PACK_EXPAND_PADDING);
    regler->signal_toggled().connect(sigc::bind(sigc::mem_fun(
        *this, &Widget::on_value_changed), port_name));
  }
}

// Create the Text Labels from images For Amp
void Widget::make_image(Gtk::Box *box,Glib::ustring label, bool start )
{
	Glib::ustring  label_image = GX_LV2_STYLE_DIR;
  	label_image += "/";
  	label_image += label;
  	label_image += ".png";
  	Gtk::Image *pr = new Gtk::Image(label_image);


 	Gtk::VBox* b1 = new Gtk::VBox();
        box->pack_start( *Gtk::manage(b1), Gtk::PACK_EXPAND_PADDING);
	if( start ){
//		std::cout << "Pack Start "<<label<<std::endl;
	        box->pack_start( *Gtk::manage(pr),Gtk::PACK_SHRINK, 0);
	}else{
//	       std::cout << "Pack End " << label << std::endl;
	        box->pack_end( *Gtk::manage(pr),Gtk::PACK_SHRINK, 0);
	}

 	Gtk::VBox* b2 = new Gtk::VBox();
       box->pack_end( *Gtk::manage(b2), Gtk::PACK_EXPAND_PADDING);

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
      //printf("port event %i, value %f\n",port_index,value);
      
    }
    if(port_index == FREQ) m_tuner.set_freq(*static_cast<const float*>(buffer));
    if (port_index == TUNEMODE) set_tuning();
    
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
  if (port_index == TUNEMODE) set_tuning();
}


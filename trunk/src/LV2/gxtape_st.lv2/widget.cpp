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
    case DRIVE:
      return &m_bigknob;
    case WOWDEPTH:
      return &m_smallknob1;
    case WOWFREQ:
      return &m_smallknob2;
    case FLUTTERDEPTH:
      return &m_smallknob3;
    case FLUTTERFREQ:
      return &m_smallknob4;
    case TAPEHISS:
      return &m_smallknob5;
   case GAIN:
      return &m_bigknob1;
   case METERLEVEL:
      return &m_vumeter;
    case ON:
      return &m_switch;
    case TAPETYPE:
      return &m_switch1;
    case SPEED:
      return &m_switch2;

//    case SATURATION_METER:
//      return &m_meter;	// See guitarix fastmeter for this
    default:
      return NULL;
  } 
}

Widget::Widget(Glib::ustring plugname):
plug_name(plugname)
{
  // create controllers for port name
  make_controller_box(&m_vbox2, "Input", 0, 1.0, 0.01, DRIVE);

  make_controller_box(&m_vbox3, "depth", 0, 0.03, 0.001, WOWDEPTH);
  make_controller_box(&m_vbox4, "freq", 0.0, 4.0, 0.01, WOWFREQ);

  make_controller_box(&m_vbox5, "depth", 0, 0.03, 0.001, FLUTTERDEPTH);
  make_controller_box(&m_vbox6, "freq", 4.0, 60.0, 0.01, FLUTTERFREQ);

  make_controller_box(&m_vbox7, "noise", 0, 1.0, 0.01, TAPEHISS);
  make_switch_box(&m_vbox8, "Mach. 1","Mach. 2", TAPETYPE);

  make_controller_box(&m_vbox9, "Output", 0, 1.0, 0.01, GAIN);

// This is bodge
//  make_controller_box(&m_vbox10, "", -20.0, 10.0, 0.01, METERLEVEL);
  make_switch_box(&m_vbox11, "ON", "OFF", ON);
  make_switch_box(&m_vbox12, "7.5 ips", "15 ips", SPEED);

// Need to sort the VUMeter
//  make_controller_box(&m_vbox2, "DEPTH", 0, 1.0, 0.01, DEPTH);

// Rough layout Sat+Meter WOW FLUTTER HISS
  
  // set propertys for the main paintbox holding the skin
  m_paintbox.set_border_width(0);
  m_paintbox.set_spacing(0);
  m_paintbox.set_homogeneous(false);
  m_paintbox.set_name(plug_name);
  m_paintbox.property_paint_func() = "amp_skin_expose";
  m_paintbox.set_size_request( 600, 360 ) ;

  add(m_paintbox);

  // One vertical box to wrap all in
  m_vbox_.set_spacing(65);
  m_vbox_.set_border_width(0);
  m_vbox_.set_homogeneous(true);
  
  m_paintbox.pack_start(m_vbox_ , Gtk::PACK_EXPAND_PADDING, 0);

  
 // This is the top controller strip	  
  m_hbox1_.set_spacing(20);
  m_hbox1_.set_border_width(0);
  m_hbox1_.set_homogeneous(false);

 // This is the bottom controller strip	  
  m_hbox2_.set_spacing(30);
  m_hbox2_.set_border_width(0);
  m_hbox2_.set_homogeneous(false);

  // put boxed controllers into controller box
  m_vbox2.set_spacing(4);
  m_vbox3.set_spacing(4);
  m_vbox4.set_spacing(4);
  m_vbox5.set_spacing(4);
  m_vbox6.set_spacing(4);
  m_vbox7.set_spacing(4);
  m_vbox8.set_spacing(0);
  m_vbox9.set_spacing(4);
  m_vbox10.set_spacing(4);
  m_vbox11.set_spacing(0);
  m_vbox12.set_spacing(0);

  // Top box has Saturation - Meter - Output Level( Not Yet Implemented
  m_hbox1_.pack_start(m_vbox1_, Gtk::PACK_EXPAND_PADDING);

	// Bypass
   m_hbox1_.pack_start(m_vbox11);
   // Saturation
  m_hbox1_.pack_start(m_vbox2);
  m_hbox1_.pack_start(m_vbox10);
  // Output Level
  m_hbox1_.pack_start(m_vbox9);
  // Tape Speed
  m_hbox1_.pack_start(m_vbox8);
  
  m_hbox1_.pack_start(m_vbox2_, Gtk::PACK_EXPAND_PADDING);

  // Bottom box has WOW - FLUTTER - HISS

  m_hbox2_.pack_start(m_vbox3_, Gtk::PACK_EXPAND_PADDING);

  // Start with vbox and add label

  // vbox for wow section
  m_hbox3_.set_spacing(20);
  m_hbox3_.set_border_width(0);
  m_hbox3_.set_homogeneous(false);
  make_label( &m_vbox5_, "WOW", true ) ;
  m_vbox5_.pack_start(m_hbox3_);
  m_hbox3_.pack_start(m_vbox3);
  m_hbox3_.pack_start(m_vbox4);
  m_hbox2_.pack_start(m_vbox5_, Gtk::PACK_SHRINK);

   // vbox for flutter section
  m_hbox4_.set_spacing(20);
  m_hbox4_.set_border_width(0);
  m_hbox4_.set_homogeneous(false);
  make_label( &m_vbox6_, "FLUTTER", true ) ;
  m_vbox6_.pack_start(m_hbox4_);
  m_hbox4_.pack_start(m_vbox5);
  m_hbox4_.pack_start(m_vbox6);
  m_hbox2_.pack_start(m_vbox6_, Gtk::PACK_SHRINK);

  // Add the Tape Hiss and Speed control
  m_hbox5_.set_spacing(20);
  m_hbox5_.set_border_width(0);
  m_hbox5_.set_homogeneous(false);
  make_label( &m_vbox7_, "TAPE", true ) ;
  m_vbox7_.pack_start(m_hbox5_);
  m_hbox5_.pack_start(m_vbox7);
  m_hbox5_.pack_start(m_vbox12);
  m_hbox2_.pack_start(m_vbox7_, Gtk::PACK_SHRINK);
  
  m_hbox2_.pack_start(m_vbox4_, Gtk::PACK_EXPAND_PADDING);

  // End 2nd Controllers
  // Now put all layers in main vbox

  m_vbox_.pack_start(m_hbox1_, Gtk::PACK_EXPAND_PADDING, 0);
  m_vbox_.pack_start(m_hbox2_, Gtk::PACK_EXPAND_PADDING, 0);

 
  // connect expose handler as resize handler
  m_paintbox.signal_draw().connect(
    sigc::mem_fun(this, &Widget::_draw), true);

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
  m_paintbox.set_border_width(height/20);
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
    regler->set_relief(Gtk::RELIEF_NONE);
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
//		std:::cout << "Pack Start "<<label<<std:::endl;
	        box->pack_start( *Gtk::manage(pr),Gtk::PACK_SHRINK, 0);
	}else{
//	       std:::cout << "Pack End " << label << std:::endl;
	        box->pack_end( *Gtk::manage(pr),Gtk::PACK_SHRINK, 0);
	}

 	Gtk::VBox* b2 = new Gtk::VBox();
       box->pack_end( *Gtk::manage(b2), Gtk::PACK_EXPAND_PADDING);

} 

// Create the Text Labels
void Widget::make_label(Gtk::Box *box,Glib::ustring label, bool start  )
{
    Gtk::Label* pr = new Gtk::Label(label, 0);
    pr->set_name("amplabel");

   Gtk::VBox* b1 = new Gtk::VBox();
   Gtk::VBox* b2 = new Gtk::VBox();
    		
    if( start ){
//		std:::cout << "Pack Start "<<label<<std:::endl;  Gtk::VBox* b1 = new Gtk::VBox();
	    //box->pack_start( *Gtk::manage(b1), Gtk::PACK_EXPAND_PADDING);
	    box->pack_start( *Gtk::manage(pr),Gtk::PACK_SHRINK); 
	    //box->pack_start( *Gtk::manage(b2), Gtk::PACK_EXPAND_PADDING);
	}else{
//	       std:::cout << "Pack End " << label << std:::endl;
	      // box->pack_end( *Gtk::manage(b1), Gtk::PACK_EXPAND_PADDING);
   		 box->pack_end( *Gtk::manage(pr),Gtk::PACK_SHRINK); 
   	 	//box->pack_end( *Gtk::manage(b2), Gtk::PACK_EXPAND_PADDING);
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
    if (regler)
    {
      float value = *static_cast<const float*>(buffer);
//std:::cout << "Widget Value " << value << " port "<< port_index << std:::endl;
      regler->cp_set_value(value);
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


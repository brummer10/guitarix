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
  // set propertys for the main paintbox holding the skin
  m_paintbox.set_border_width(0);
  m_paintbox.set_spacing(0);
  m_paintbox.set_homogeneous(false);
  m_paintbox.set_name(plug_name);
  m_paintbox.property_paint_func() = "amp_skin_expose";
  add(m_paintbox);

  // My layout
  // Top Layout Spacer - request width/height 576,166 expand off
  m_vbox2_.set_spacing(0);
  m_vbox2_.set_border_width(0);
  m_vbox2_.set_homogeneous(false);
  m_vbox2_.set_size_request(576,188);

 // set a vertical box in the paintbox
  m_paintbox.pack_start(m_vbox_);

  m_vbox_.pack_start( m_vbox2_,false, true ) ;

  // Wrapper for Logo in centre 
  m_hbox1_.set_spacing(0);
  m_hbox1_.set_border_width(0);
  m_hbox1_.set_homogeneous(false);

  // Left spacer - request width 146 expand off
  m_vbox3_.set_spacing(0);
  m_vbox3_.set_border_width(0);
  m_vbox3_.set_homogeneous(false);
  m_vbox3_.set_size_request(146);
  

  // Logo in centre add images to this 
  m_hbox2_.set_spacing(0);
  m_hbox2_.set_border_width(0);
  m_hbox2_.set_size_request(312);
  m_hbox2_.set_homogeneous(false);
  // Add each image request size and expand off
  make_logo( &m_hbox2_,"guitarix-logo", false );
  make_logo( &m_hbox2_,"redeye-logo", true );
  
  
 // Right spacer - request width 146 expand off
  m_vbox4_.set_spacing(0);
  m_vbox4_.set_border_width(0);
  m_vbox4_.set_homogeneous(false);
  m_vbox4_.set_size_request(166);
  
  m_hbox1_.pack_end( m_vbox4_, false, true ) ;
  m_hbox1_.pack_end( m_hbox2_, false, true ) ;
  m_hbox1_.pack_end( m_vbox3_,false, true ) ;

  m_vbox_.pack_start( m_hbox1_ ) ;

 // Wrapper for lower layer with knobs in centre
  m_hbox3_.set_spacing(20);
  m_hbox3_.set_border_width(0);
  m_hbox3_.set_homogeneous(false);
 
 // Vbox 5 is spacer - request width 146 expand off
  m_vbox5_.set_spacing(0);
  m_vbox5_.set_border_width(0);
  m_vbox5_.set_homogeneous(false);
  m_vbox5_.set_size_request(146);
  
  m_hbox3_.pack_start( m_vbox5_, false, true ) ;

 // Vbox 6 is container for knob widget and label
  m_vbox6_.set_spacing(0);
  m_vbox6_.set_border_width(0);
  m_vbox6_.set_homogeneous(false);

  make_controller_box(&m_vbox6_, &m_bigknob, "gain", -20, 20, 0.1, gain, plug_name);
  m_bigknob.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob_value_changed));

  m_hbox3_.pack_start( m_vbox6_ ) ;

 // Vbox 7 is container for knob widget and label
  m_vbox7_.set_spacing(0);
  m_vbox7_.set_border_width(0);
  m_vbox7_.set_homogeneous(false);
 
  make_controller_box(&m_vbox7_, &m_bigknob1, "tone", -9, 9, 0.1, tone, plug_name);
  m_bigknob1.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob1_value_changed));

  m_hbox3_.pack_start( m_vbox7_ ) ;


 // Vbox 8 is container for knob widget and label
  m_vbox8_.set_spacing(0);
  m_vbox8_.set_border_width(0);
  m_vbox8_.set_homogeneous(false);

  make_controller_box(&m_vbox8_, &m_bigknob2, "volume", -60, 0, 0.1, volume, plug_name);
  m_bigknob2.signal_value_changed().connect(sigc::mem_fun(*this,
      &Widget::on_knob2_value_changed));
   
  m_hbox3_.pack_start( m_vbox8_ ) ;


// Vbox 9 is container for switch widget and label
// Make this a hbox and put 2 in, one for Chump Logo one for switch
  m_vbox9_.set_spacing(0);
  m_vbox9_.set_border_width(0);
  m_vbox9_.set_homogeneous(false);
  make_logo( &m_vbox9_,"chump-logo", true );


  m_vbox10_.set_spacing(0);
  m_vbox10_.set_border_width(0);
  m_vbox10_.set_homogeneous(false);

  make_switch_box(&m_vbox9_, &m_switch, "feedback", 0.0, 1.0, 1.0, feedback, plug_name);
  m_switch.signal_toggled().connect(sigc::mem_fun(*this,
      &Widget::on_switch_value_changed));
   
  m_hbox3_.pack_start( m_vbox9_ ) ;
//  m_hbox3_.pack_start( m_vbox10_ ) ;

 // Vbox 11 is spacer - request width 146 expand off
  m_vbox11_.set_spacing(0);
  m_vbox11_.set_border_width(0);
  m_vbox11_.set_homogeneous(false);
  m_vbox11_.set_size_request(146);
  // Set expand to false.
  m_hbox3_.pack_start( m_vbox11_, false, true ) ;

  m_vbox_.pack_end( m_hbox3_ ) ;
  
  // connect expose handler as resize handler
  m_paintbox.signal_expose_event().connect(
    sigc::mem_fun(this, &Widget::_expose_event), true);

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
/*  Gtk::Label* pr = new Gtk::Label(label, 0);
  pr->set_name("amplabel");*/
  Glib::ustring  label_image = GX_LV2_STYLE_DIR;
  label_image += "/"+plug_name+"-";
  label_image += label;
  label_image += "-label.png";
  Gtk::Image *pr = new Gtk::Image(label_image);
 
  regler->cp_configure("KNOB", label, min, max, digits);
  regler->set_show_value(false);
  regler->cp_set_value(value);
  regler->set_name(plug_name);

  //regler->set_size_request( 60, 60 ) ;

  box->pack_end( *Gtk::manage(pr),false,true); 

  box->pack_end(*regler,false, true);
  
  
}

void Widget::make_switch_box(Gtk::Box *box,
                                 Gxw::Switch *toggle,
                                 Glib::ustring label,
                                 float min, float max,
                                 float digits, float value,
                                 Glib::ustring plug_name)
{
/*  Gtk::Label* pr = new Gtk::Label(label, 0);
  pr->set_name("amplabel");*/
  Glib::ustring  label_image = GX_LV2_STYLE_DIR;
  label_image += "/"+plug_name+"-";
  label_image += label;
  label_image += "-label.png";
   Gtk::Image *pr = new Gtk::Image(label_image);
 
  //Have to work out how the style is added to pick up correct images
  toggle->cp_configure("KNOB", label, min, max, digits);
  toggle->cp_set_value(value);
  toggle->set_name("chump");
  toggle->set_base_name( "button" ) ;
  //std::cout << "basename = " << toggle->get_base_name(  ) << std::endl;
  //  toggle->set_size_request( 60, 60 ) ;

  box->pack_end( *Gtk::manage(pr),false,true); 

  box->pack_end(*toggle,false, true);
  
  
}

// Create the Text Labels For Amp
void Widget::make_logo(Gtk::Box *box,Glib::ustring label, bool start )
{
	Glib::ustring  label_image = GX_LV2_STYLE_DIR;
  	label_image += "/";
  	label_image += label;
  	label_image += ".png";
  	Gtk::Image *pr = new Gtk::Image(label_image);

//	Glib::RefPtr<Gdk::Pixbuf> pb = pr->get_pixbuf() ;
//	int width = pb->get_width() ;
//	int height = pb->get_height() ;  
//	pr->set_size_request( width, height ) ;
 
	if( start ){
//		std::cout << "Pack Start "<<label<<std::endl;
		 //box->pack_start( *Gtk::manage(pr),false, true);
	        box->pack_start( *Gtk::manage(pr),Gtk::PACK_SHRINK);
	}else{
//	       std::cout << "Pack End " << label << std::endl;
//	        box->pack_end( *Gtk::manage(pr),false, true);
	        box->pack_end( *Gtk::manage(pr),Gtk::PACK_SHRINK);
	}
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
        case GAIN:
          gain = value;
          m_bigknob.cp_set_value(gain);
          break;
        case TONE:
          tone = value;
          m_bigknob1.cp_set_value(tone);
          break;
        case VOLUME:
          volume = value;
          m_bigknob2.cp_set_value(volume);
          break;
        case FEEDBACK:
          feedback = value;
          m_switch.cp_set_value(feedback);
          break;
 	
        default:
          break;
        }
    }
}
// write value changes to the host->engine
void Widget::on_knob_value_changed()
{
  gain = m_bigknob.get_value();
  //std::cout << "gain = " << gain << std::endl;
  write_function(controller, (PortIndex)GAIN,
                 sizeof(float), 0, (const void*)&gain);
}


void Widget::on_knob1_value_changed()
{
  tone = m_bigknob1.get_value();
  //std::cout << "tone = " << tone << std::endl;
  write_function(controller, (PortIndex)TONE,
                 sizeof(float), 0, (const void*)&tone);
}

void Widget::on_knob2_value_changed()
{
  volume = m_bigknob2.get_value();
  //std::cout << "volume = " << volume << std::endl;
  write_function(controller, (PortIndex)VOLUME,
                 sizeof(float), 0, (const void*)&volume);
}
void Widget::on_switch_value_changed()
{
  // Will this work
  feedback = m_switch.cp_get_value();
//  std::cout << "feedback = " << feedback << std::endl;
  write_function(controller, (PortIndex)FEEDBACK,
                 sizeof(float), 0, (const void*)&feedback);
}


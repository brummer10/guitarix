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

Widget::Widget(Glib::ustring plug_name)
{
  // init values set by host
  /* amp definition based on plug_name
   So at present only 2 plug names
	chump 		gain/tone/volume/feedback
	bigchump	gain/tone/volume/feedback
	vibrochump	gain/tone/volume/feedback/speed/depth/sinewave
  */

  if( strcmp( "vibrochump", plug_name.c_str() ) == 0 ){
	vibrochump = true ;
  }else{
	vibrochump = false ;
  }
  change_skin( plug_name ) ;
 
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

  if( vibrochump ){
    m_vbox2_.set_size_request(750,174);

  }else{
    m_vbox2_.set_size_request(576,220);
  }
 // set a vertical box in the paintbox
  m_paintbox.pack_start(m_vbox_);

  m_vbox_.pack_start( m_vbox2_,false, true ) ;


  if( !vibrochump ){
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
	  m_hbox2_.set_size_request(312, 38);
	  m_hbox2_.set_homogeneous(false);

	  // Add each image request size and expand off

	  make_logo( &m_hbox2_,"redeye-logo-medium", true );

	  // Create vbox with Guitarix and Chump logo

	  make_logo( &m_vbox20_,"guitarix-logo-blue", true );
   
          make_logo( &m_vbox20_,plug_name+"-logo", true );
  	  m_hbox2_.pack_end( m_vbox20_, false, true ) ;
 
  
  
 	// Right spacer - request width 146 expand off
 	 m_vbox4_.set_spacing(0);
 	 m_vbox4_.set_border_width(0);
 	 m_vbox4_.set_homogeneous(false);
 	 m_vbox4_.set_size_request(166);
  
  	m_hbox1_.pack_end( m_vbox4_, false, true ) ;
  	m_hbox1_.pack_end( m_hbox2_, false, true ) ;
  	m_hbox1_.pack_end( m_vbox3_,false, true ) ;

  	m_vbox_.pack_start( m_hbox1_ ) ;
  }
 // Wrapper for lower layer with knobs in centre
  m_hbox3_.set_spacing(6); // Calculate more accurately
  m_hbox3_.set_border_width(0);
  m_hbox3_.set_homogeneous(false);
  m_hbox3_.set_size_request(678,72);
 
 // Vbox 5 is spacer - request width 146 expand off
  m_vbox5_.set_spacing(0);
  m_vbox5_.set_border_width(0);
  m_vbox5_.set_homogeneous(false);
  if( vibrochump ){
	m_vbox5_.set_size_request(16);
  }else{
  	m_vbox5_.set_size_request(146);
  }
  m_hbox3_.pack_start( m_vbox5_, false, true ) ;

 // Vbox 6 is container for knob widget and label
  m_vbox6_.set_spacing(0);
  m_vbox6_.set_border_width(0);
  m_vbox6_.set_homogeneous(false);

  make_controller_box(&m_vbox6_, &m_bigknob, "gain", 0, 1, 0.01,
                      gain,GAIN, plug_name);

  m_hbox3_.pack_start( m_vbox6_ ) ;

 // Vbox 7 is container for knob widget and label
  m_vbox7_.set_spacing(0);
  m_vbox7_.set_border_width(0);
  m_vbox7_.set_homogeneous(false);


 
  make_controller_box(&m_vbox7_, &m_bigknob1, "tone", 0, 1, 0.01,
                      tone,TONE, plug_name);

  m_hbox3_.pack_start( m_vbox7_ ) ;


 // Vbox 8 is container for knob widget and label
  m_vbox8_.set_spacing(0);
  m_vbox8_.set_border_width(0);
  m_vbox8_.set_homogeneous(false);

  make_controller_box(&m_vbox8_, &m_bigknob2, "volume", 0, 1, 0.01,
                      volume,VOLUME, plug_name);
   
  m_hbox3_.pack_start( m_vbox8_ ) ;


// Vbox 9 is container for switch widget and label
// Make this a hbox and put 2 in, one for Chump Logo one for switch

  m_vbox9_.set_spacing(0);
  m_vbox9_.set_border_width(0);
  m_vbox9_.set_homogeneous(false);

 if( strcmp( "bigchump", plug_name.c_str() ) == 0 ){
  make_switch_box( &m_vbox9_, &m_switch, "feedback", 0.0, 1.0, 1.0, feedback, FEEDBACK, plug_name);
 }
   
  m_hbox3_.pack_start( m_vbox9_ ) ;

  // This is for the Vibro amps

  if( vibrochump ){
	  m_vbox21_.set_spacing(0);
	  m_vbox21_.set_border_width(0);
	  m_vbox21_.set_homogeneous(false);
	  make_switch_box( &m_vbox21_, &m_switch2, "vibe", 0.0, 1.0, 1.0, vibe, VIBE, plug_name);
          m_hbox3_.pack_start( m_vbox21_ ) ;
	  m_vbox10_.set_spacing(0);
	  m_vbox10_.set_border_width(0);
	  m_vbox10_.set_homogeneous(false);
  	  make_controller_box(&m_vbox10_, &m_bigknob3, "speed", 2, 10, 0.1,
                      speed,SPEED, plug_name);
	  m_hbox3_.pack_start( m_vbox10_ ) ;
          m_vbox11_.set_spacing(0);
	  m_vbox11_.set_border_width(0);
	  m_vbox11_.set_homogeneous(false);
  	  make_controller_box(&m_vbox11_, &m_bigknob4, "intensity", 0.1, 10, 0.1,
                      intensity,INTENSITY, plug_name);
	  m_hbox3_.pack_start( m_vbox11_ ) ;

	  m_vbox12_.set_spacing(0);
	  m_vbox12_.set_border_width(0);
	  m_vbox12_.set_homogeneous(false);
	  make_switch_box( &m_vbox12_, &m_switch1, "sine", 0.0, 1.0, 1.0, sinewave, SINEWAVE, plug_name);
          m_hbox3_.pack_start( m_vbox12_ ) ;
   
	// And the logo 
        make_logo( &m_vbox13_,plug_name+"-logo", true );
	// May move this to top of the amp
	 make_logo( &m_vbox13_,"redeye-logo", true );

        m_hbox3_.pack_start( m_vbox13_ ) ;

  }

 // Vbox 14 is spacer - request width 146 expand off
  m_vbox14_.set_spacing(0);
  m_vbox14_.set_border_width(0);
  m_vbox14_.set_homogeneous(false);
  if( vibrochump ){
	m_vbox14_.set_size_request(16);
  }else{
  	m_vbox14_.set_size_request(146);
  }
  // Set expand to false.
  m_hbox3_.pack_start( m_vbox14_, false, true ) ;
  m_vbox_.pack_start( m_hbox3_ ) ;

  
  if( vibrochump ){
	// Bottom spacer box 
	m_hbox4_.set_spacing(0);
  	m_hbox4_.set_border_width(0);
  	m_hbox4_.set_homogeneous(false);
	m_hbox4_.set_size_request(750, 24);
        m_vbox_.pack_start( m_hbox4_ ) ;
  
  }


  // connect expose handler as resize handler
  m_paintbox.signal_draw().connect(
    sigc::mem_fun(this, &Widget::_draw), true);

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
                                 PortIndex port_name,
                                 Glib::ustring plug_name)
{
  //Gtk::Label* pr = new Gtk::Label(label, 0);
  //pr->set_name("amplabel");
  Glib::ustring plugname = "";
  if( strcmp( "bigchump", plug_name.c_str() ) == 0 ){
    plugname = "chump";
  } else {
    plugname = plug_name;
  }
  Glib::ustring  label_image = GX_LV2_STYLE_DIR;
  label_image += "/"+plugname+"-";
  label_image += label;
  label_image += "-label.png";
  Gtk::Image *pr = new Gtk::Image(label_image);
  
//  std::cout << "label_image = " << label_image << std::endl;
 
/*  Gtk::VBox* b1 = new Gtk::VBox();
  box->pack_start( *Gtk::manage(b1), Gtk::PACK_EXPAND_PADDING);
*/
  regler->cp_configure("KNOB", label, min, max, digits);
  regler->set_show_value(false);
  regler->cp_set_value(value);
  regler->set_name(plug_name);
  box->pack_end( *Gtk::manage(pr),Gtk::PACK_SHRINK);
  box->pack_end(*regler,Gtk::PACK_SHRINK);
/*  Gtk::VBox* b2 = new Gtk::VBox();
  box->pack_start( *Gtk::manage(b2), Gtk::PACK_EXPAND_PADDING);
*/
  regler->signal_value_changed().connect(sigc::bind(sigc::mem_fun(*this,
      &Widget::on_value_changed), port_name));

}

void Widget::make_switch_box(Gtk::Box *box,
                                 Gxw::Switch *toggle,
                                 Glib::ustring label,
                                 float min, float max,
                                 float digits, float value,
                                 PortIndex port_name,
                                 Glib::ustring plug_name)

{
/*  Gtk::Label* pr = new Gtk::Label(label, 0);
  pr->set_name("amplabel");*/
  Glib::ustring plugname = "";
  if( strcmp( "bigchump", plug_name.c_str() ) == 0 ){
    plugname = "chump";
  } else {
    plugname = plug_name;
  }
  Glib::ustring  label_image = GX_LV2_STYLE_DIR;
  label_image += "/"+plugname+"-";
  label_image += label;
  label_image += "-label.png";
   Gtk::Image *pr = new Gtk::Image(label_image);
 
  //Have to work out how the style is added to pick up correct images
  toggle->cp_configure("KNOB", label, min, max, digits);
  toggle->cp_set_value(value);
  toggle->set_name("chump");
  toggle->set_base_name( "switchit" ) ;
  toggle->set_relief(Gtk::RELIEF_NONE);
  toggle->set_can_focus( false ) ;
  //  toggle->set_size_request( 60, 60 ) ;
  box->pack_end( *Gtk::manage(pr),false,true); 
  box->pack_end(*toggle,false, true);

  toggle->signal_toggled().connect(sigc::bind(sigc::mem_fun(*this,
      &Widget::on_value_changed), port_name));
  
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
bool Widget::_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
  int x, y, width, height;
  m_paintbox.get_window()->get_geometry(x, y, width, height);
  //double_t height = m_paintbox.get_window()->get_height();
  m_paintbox.set_border_width(height/12);//SHP Needs a tweak
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
        case SPEED:
          speed = value;
          m_bigknob3.cp_set_value(speed);
          break;
        case INTENSITY:
          intensity = value;
          m_bigknob4.cp_set_value(intensity);
          break;
        case FEEDBACK:
          feedback = value;
          m_switch.cp_set_value(feedback);
          break;
        case SINEWAVE:
          sinewave = value;
          m_switch1.cp_set_value(sinewave);
          break;
        case VIBE:
          vibe = value;
          m_switch2.cp_set_value(vibe);
          break;
        default:
          break;
        }
    }
}
// write value changes to the host->engine
void Widget::on_value_changed(uint32_t port_index)
{
//  	std::cout << "Port = " << port_index << std::endl;
  switch ((PortIndex)port_index )
    {
    case GAIN:
      gain = m_bigknob.get_value();
      //std::cout << "gain = " << gain << std::endl;
      write_function(controller, (PortIndex)GAIN,
                 sizeof(float), 0, (const void*)&gain);
      break;
    case TONE:
       tone = m_bigknob1.get_value();
       //std::cout << "tone = " << tone << std::endl;
       write_function(controller, (PortIndex)TONE,
                 sizeof(float), 0, (const void*)&tone);
      break;

    case VOLUME:
      volume = m_bigknob2.get_value();
      //std::cout << "volume = " << volume << std::endl;
      write_function(controller, (PortIndex)VOLUME,
                 sizeof(float), 0, (const void*)&volume);
      break;

    case SPEED:
      speed = m_bigknob3.get_value();
      //std::cout << "speed = " << speed << std::endl;
      write_function(controller, (PortIndex)SPEED,
                 sizeof(float), 0, (const void*)&speed);
      break;

   case VIBE:
      vibe = m_switch2.cp_get_value();
     // std::cout << "vibe = " << sinewave << std::endl;
      write_function(controller, (PortIndex)VIBE,
                 sizeof(float), 0, (const void*)&vibe);
      break;
    case INTENSITY:
      intensity = m_bigknob4.get_value();
   //   std::cout << "intensity = " << intensity << std::endl;
      write_function(controller, (PortIndex)INTENSITY,
                 sizeof(float), 0, (const void*)&intensity);
      break;

   case SINEWAVE:
      sinewave = m_switch1.cp_get_value();
   //   std::cout << "sinewave = " << sinewave << std::endl;
      write_function(controller, (PortIndex)SINEWAVE,
                 sizeof(float), 0, (const void*)&sinewave);
      break;
 
    case FEEDBACK:
      feedback = m_switch.cp_get_value();
 //     std::cout << "feedback = " << feedback << std::endl;
      write_function(controller, (PortIndex)FEEDBACK,
                 sizeof(float), 0, (const void*)&feedback);
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
// This is called at startup depending on the amp model so need to look at how to do this
void Widget::change_skin(Glib::ustring plug_name)
{
  std::string rcfile =GX_LV2_STYLE_DIR;
  rcfile +="/gx_redeye-";
  rcfile += plug_name;
  rcfile += ".rc";
  //std::cout << "rcfile = " << rcfile << std::endl;
    
  gtk_rc_parse(rcfile.c_str());
  gtk_rc_reset_styles(gtk_settings_get_default());
}

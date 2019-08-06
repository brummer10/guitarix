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
   BPM, 
   FEEDBACK, 
   GAIN, 
   HIGHPASS, 
   HOWPASS, 
   LEVEL, 
   MODE, 
   NOTES, 
} PortIndex;
*/
Gtk::Widget* Widget::get_controller_by_port(uint32_t port_index)
{
  switch ((PortIndex)port_index )
  {
    case BPM:
      return &m_bigknob[0];
    case FEEDBACK:
      return &m_bigknob[1];
    case GAIN:
      return &m_bigknob[2];
    case HIGHPASS:
      return &m_bigknob[4];
     case HOWPASS:
      return &m_bigknob[5];
    case LEVEL:
      return &m_bigknob[6];
    case MODE:
      return &m_selector[0];
    case NOTES:
      return &m_selector[1];
   default:
      return NULL;
  } 
}

Widget::Widget(Glib::ustring plugname):
plug_name(plugname),
logo("Digital Stereo Delay")
{
  // create controllers for port name
  make_controller_box(&m_vbox[1], "BPM",  24.0, 3.6e+02, 1.0 , BPM);
  make_controller_box(&m_vbox[2], "FEEDBACK",  1.0, 1e+02, 1.0 , FEEDBACK);
  make_controller_box(&m_vbox[3], "GAIN", 0.0, 1.2e+02, 1.0 , GAIN);
  make_log_controller_box(&m_vbox[4], "HIGHPASS",  2e+01, 2e+04, 1.08 , HIGHPASS);
  make_log_controller_box(&m_vbox[5], "LOWPASS", 2e+01, 2e+04, 1.08, HOWPASS);
  make_controller_box(&m_vbox[6], "LEVEL",  1.0, 1e+02, 1.0, LEVEL);
  
  Glib::ustring modes[] = {"plain","presence","tape","tape2"};  
  static const size_t _size1 = sizeof(modes) / sizeof(modes[0]);
  make_selector("MODE", modes, _size1, 0, 1.0, MODE);
  Glib::ustring notes[] = {"Dotted 1/2 note","1/2 note","1/2 note triplets"," Dotted 1/4 note","1/4 note","1/4 note triplets","Dotted 1/8 note","1/8 note","1/8 note triplets"," Dotted 1/16 note","1/16 note","1/16 note triplets","Dotted 1/32 note","1/32 note","1/32 note triplets"," Dotted 1/64 note","1/64 note","1/64 note triplets"};  
  static const size_t _size2 = sizeof(notes) / sizeof(notes[0]);
  make_selector("NOTES", notes, _size2, 0, 1.0, NOTES);
  m_vbox[0].pack_start(m_selector[0]);
  m_vbox[0].pack_start(m_selector[1]);
  // set propertys for the main paintbox holding the skin
  m_paintbox.set_border_width(10);
  m_paintbox.set_spacing(6);
  m_paintbox.set_homogeneous(false);
  m_paintbox.set_name(plug_name);
  m_paintbox.property_paint_func() = "rack_unit_expose";
  add(m_paintbox);
  // box for the controllers
  m_hbox.set_spacing(14);
  m_hbox.set_border_width(24);
  m_hbox.set_homogeneous(false);
  // set a vertical box in the paintbox
  m_vbox[8].set_border_width(7);
  m_vbox[10].set_border_width(7);
  m_paintbox.pack_start(m_vbox[9]);
  // modify logo layout
  Pango::FontDescription font_desc = logo.get_style_context()->get_font();
  font_desc.set_size(int(14*Pango::SCALE));
  font_desc.set_weight(Pango::WEIGHT_BOLD);
  logo.override_font(font_desc);
  m_hbox1_.set_spacing(64);
  logo.set_name("amplabel");
  m_vbox[9].pack_start(m_hbox1_, Gtk::PACK_SHRINK);
  m_hbox1_.pack_start(m_vbox1_, Gtk::PACK_EXPAND_PADDING);
  m_hbox1_.pack_end(m_vbox2_, Gtk::PACK_SHRINK);
  m_hbox1_.pack_end(logo, Gtk::PACK_SHRINK);
  // and controller box on top
  m_vbox[9].pack_start(m_hbox, Gtk::PACK_SHRINK);
  // put boxed controllers into controller box
  m_hbox.pack_start(m_vbox[10], Gtk::PACK_EXPAND_PADDING);
  m_hbox.pack_start(m_vbox[0]);
  m_hbox.pack_start(m_vbox[1]);
  m_hbox.pack_start(m_vbox[6]);
  m_hbox.pack_start(m_vbox[2]);
  m_hbox.pack_start(m_vbox[4]);
  m_hbox.pack_start(m_vbox[5]);
  m_hbox.pack_start(m_vbox[3]);
  m_hbox.pack_start(m_vbox[8], Gtk::PACK_EXPAND_PADDING);

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
    regler->cp_set_var("no_log");
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
    regler->cp_set_var("no_log");
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



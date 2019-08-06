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

Gtk::Widget* Widget::get_controller_by_port(uint32_t port_index)
{
  switch ((PortIndex)port_index )
  {
    case LEVEL:
      return &m_bigknob;
    case EQ2_FREQ:
      return &m_bigknob1;
    case EQ1_LEVEL:
      return &m_smallknob3;
    case EQ1_FREQ:
      return &m_smallknob4;
    case IN_DELAY:
      return &m_smallknob5;
    case LOW_RT60:
      return &m_smallknob6;
    case LF_X:
      return &m_smallknob7;
    case HF_DAMPING:
      return &m_smallknob8;
    case MID_RT60:
      return &m_smallknob9;
    case DRY_WET_MIX:
      return &m_smallknob10;
    case EQ2_LEVEL:
      return &m_smallknob11;
    default:
      return NULL;
  } 
}

Widget::Widget(Glib::ustring plugname):
plug_name(plugname)
{
  // create controllers for port name
  m_fr5.set_label("In");
  m_fr5.add(m_vbox2);
  make_controller_box(&m_vbox2, "DELAY",  2e+01, 1e+02, 1.0 , IN_DELAY);
  
  m_fr1.set_label("EQ2");
  m_fr1.add(m_vbox3);
  make_controller_box(&m_vbox3, "LEVEL",  -1.0, 1.0, 0.01  , EQ2_LEVEL);
  make_log_controller_box(&m_vbox3, "FREQ",  160, 10000, 1.08 , EQ2_FREQ);
  
  m_fr2.set_label("EQ1");
  m_fr2.add(m_vbox4);
  make_controller_box(&m_vbox4, "LEVEL", -15.0, 15.0, 0.1, EQ1_LEVEL);
  make_log_controller_box(&m_vbox4, "FREQ",  4e+01, 2.5e+03, 1.08 , EQ1_FREQ);
  
  m_fr3.set_label("Reverb Time T60");
  m_fr3.add(m_hbox1);
  m_hbox1.add(m_vbox5);
  m_hbox1.add(m_vbox6);
  make_log_controller_box(&m_vbox5, "LOW",  1.0, 8.0, 1.08, LOW_RT60);
  make_log_controller_box(&m_vbox5, "MID",  1.0, 8.0, 1.08 , MID_RT60);
  make_log_controller_box(&m_vbox6, "FREQ X", 5e+01, 1e+03, 1.08  , LF_X);
  make_log_controller_box(&m_vbox6, "DAMP", 1.5e+03, 2.352e+04, 1.08, HF_DAMPING);
  
  m_fr4.set_label("Output");
  m_fr4.add(m_vbox7);
  make_controller_box(&m_vbox7, "LEVEL", -7e+01, 4e+01, 0.1, LEVEL);
  make_controller_box(&m_vbox7, "DRY/WET",  -1.0, 1.0, 0.01  , DRY_WET_MIX);
  
  // set propertys for the main paintbox holding the skin
  m_paintbox.set_border_width(2);
  m_paintbox.set_spacing(6);
  m_paintbox.set_homogeneous(false);
  m_paintbox.set_name(plug_name);
  m_paintbox.property_paint_func() = "gxhead_expose";
  add(m_paintbox);
  // box for the controllers
  m_hbox_.set_spacing(14);
  m_hbox_.set_border_width(4);
  m_hbox_.set_homogeneous(false);
  // set a vertical box in the paintbox
  m_vbox.set_border_width(4);
  m_vbox1.set_border_width(4);
  m_paintbox.pack_start(m_vbox_);
  // and controller box on top
  m_vbox_.pack_start(m_hbox_, Gtk::PACK_SHRINK);

   // put boxed controllers into controller box
  m_hbox_.pack_start(m_vbox1, Gtk::PACK_EXPAND_PADDING);
  m_hbox_.pack_start(m_fr5);
  m_hbox_.pack_start(m_fr2);
  m_hbox_.pack_start(m_fr1);
  m_hbox_.pack_start(m_fr3);
  m_hbox_.pack_start(m_fr4);
  m_hbox_.pack_start(m_vbox, Gtk::PACK_EXPAND_PADDING);

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


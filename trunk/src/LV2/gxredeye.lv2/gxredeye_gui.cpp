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


#include <string>
#include <iostream>

#include <gtkmm.h>
#include "gxredeye.h"
#include "widget.h"


#include <lv2.h>
#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>

using namespace std;

class GxRedeyeGUI
{
private:
  Glib::ustring plugskin;
  Glib::ustring addKnob;
  Glib::ustring plug_name;
  void set_knob( Glib::ustring prefix) ;
  void set_skin();
  void set_plug_name(const char * plugin_uri);
  GtkWidget* make_gui();
public:

  Widget* widget;
  static void set_plug_name_static(GxRedeyeGUI *self, const char * plugin_uri)
  {
    self->set_plug_name(plugin_uri);
  }
  static GtkWidget* make_gui_static(GxRedeyeGUI *self)
  {
    return self->make_gui();
  }

  GxRedeyeGUI () {};
  ~GxRedeyeGUI () {};
} ;

void GxRedeyeGUI::set_knob( Glib::ustring prefix)
{
  
  addKnob =   " style 'gx_";
  addKnob +=  plug_name;
  addKnob +=   "_icons'\n";

  addKnob +=   " { \n"
               "   stock['bigknob'] = {{'";
  addKnob +=  prefix;
  addKnob +=  "-knob.png'}}\n";
  addKnob +=  "   stock['switchit_on'] = {{'";
  addKnob +=  prefix;
  addKnob +=  "-switch_on.png'}}\n";
  addKnob +=   "   stock['switchit_off'] = {{'";
  addKnob +=  prefix;
  addKnob +=  "-switch_off.png'}}\n"
              " }\n"
              "widget '*.";
  addKnob +=  plug_name;
  addKnob +=  "' style 'gx_";
  addKnob +=  plug_name;
  addKnob +=  "_icons'\n";
  addKnob +=  "class '*GxToggleImage' style'gx_"; 
  addKnob +=  plug_name;
  addKnob +=  "_icons'\n";
  addKnob +=  "style 'guitarix_switch'\n"
              "{\n"
              "xthickness = 0\n"
              "ythickness = 0\n"
              "GtkButton::inner-border = {0, 0, 0, 0}\n"
              "GtkButton::default-border = {0, 0, 0, 0}\n"
              "GtkButton::focus-line-width = 0\n"
              "GtkButton::focus-padding = 0\n"
              "GtkButton::interior-focus = 0\n"
              "GtkButton::child-displacement-x = 0\n"
              "GtkButton::child-displacement-y = 0\n"
              " }\n"
              "class '*GxSwitch' style:highest 'guitarix_switch'";
  
}

//  std::cout << "addKnob = " << addKnob << std::endl;



void GxRedeyeGUI::set_skin()
{

  Glib::ustring toparse = "pixmap_path  ";
  toparse +=     " '";
  toparse +=        GX_LV2_STYLE_DIR;
  toparse +=     "/'\n";
  toparse +=     "style \"gx_";
  toparse +=     plug_name;
  toparse +=     "-paintbox\"\n"
                 " { \n"
                 "    GxPaintBox::icon-set =4\n"
                 "    stock['amp_skin'] = {{'";
  toparse +=     plugskin;
  toparse +=     "'}}\n"
                 " }\n"
                 "\n"
                 "style 'gx_chump_box' \n"
                 " { \n"
                 "    fg[NORMAL] = '#ffffff' \n"
                 " }\n";
  toparse +=     addKnob;

  toparse +=     "widget '*.amplabel' style:highest 'gx_chump_box'\n"
                 "widget '*.";
  toparse +=     plug_name;
  toparse +=     "' style 'gx_";
  toparse +=     plug_name;
  toparse +=     "-paintbox'\n";

//  std::cout << "style = " << toparse << std::endl;


  gtk_rc_parse_string (toparse.c_str());
}

void GxRedeyeGUI::set_plug_name( const char * plugin_uri)
{
  addKnob = "";

  if (strcmp("http://guitarix.sourceforge.net/plugins/gxredeye#chump", plugin_uri) == 0)
    {
      plugskin = "chump.png";
      plug_name = "chump";
      set_knob("chump");
    }
  else

    {
      plugskin = "chump.png";
      plug_name = "chump";
      set_knob("chump");
    }
}

GtkWidget* GxRedeyeGUI::make_gui()
{
  // init the gxwmm library
  Gxw::init();
  set_skin();
  GtkWidget* container = gtk_vbox_new(FALSE, 0);
  widget = new Widget(plug_name);

  GtkWidget* cWidget = (GtkWidget*)widget->gobj();
  gtk_container_add( (GtkContainer*)container, cWidget );

  return container;
}


static LV2UI_Handle instantiate(const struct _LV2UI_Descriptor * descriptor,
                                const char * plugin_uri,
                                const char * bundle_path,
                                LV2UI_Write_Function write_function,
                                LV2UI_Controller controller,
                                LV2UI_Widget * widget,
                                const LV2_Feature * const * features)
{
  GxRedeyeGUI* self = new GxRedeyeGUI();
  if (self == NULL) return NULL;
  self->set_plug_name_static(self, plugin_uri);
  *widget = (LV2UI_Widget)self->make_gui_static(self);
  self->widget->controller = controller;
  self->widget->write_function = write_function;
  return (LV2UI_Handle)self;
}

static void cleanup(LV2UI_Handle ui)
{
  GxRedeyeGUI *pluginGui = (GxRedeyeGUI *) ui;
  delete pluginGui->widget;
  delete pluginGui;
}

static void port_event(LV2UI_Handle ui,
                       uint32_t port_index,
                       uint32_t buffer_size,
                       uint32_t format,
                       const void * buffer)
{
  GxRedeyeGUI *self = (GxRedeyeGUI *) ui;
  self->widget->set_value_static( port_index, buffer_size, format, buffer, self->widget);
  return;
}

static LV2UI_Descriptor descriptors[] =
{
  {GXPLUGIN_UI_URI, instantiate, cleanup, port_event, NULL}
};

const LV2UI_Descriptor * lv2ui_descriptor(uint32_t index)
{
  //printf("lv2ui_descriptor(%u) called\n", (uint32_t)index);
  if (index >= sizeof(descriptors) / sizeof(descriptors[0]))
    {
      return NULL;
    }
  return descriptors + index;
}


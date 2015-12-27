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


#include <string>
#include <iostream>

#include <gtkmm.h>
#include "gx_graphiceq.h"
#include "widget.h"


#include <lv2.h>
#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>

using namespace std;

class Gx_graphiceq_GUI
{
private:
  Glib::ustring plugskin;
  Glib::ustring addKnob;
  Glib::ustring plug_name;
  void set_skin();
  void set_plug_name(const char * plugin_uri);
  GtkWidget* make_gui();
public:

  Widget* widget;
  static void set_plug_name_static(Gx_graphiceq_GUI *self, const char * plugin_uri)
  {
    self->set_plug_name(plugin_uri);
  }
  static GtkWidget* make_gui_static(Gx_graphiceq_GUI *self)
  {
    return self->make_gui();
  }

  Gx_graphiceq_GUI () {};
  ~Gx_graphiceq_GUI () {};
} ;

void Gx_graphiceq_GUI::set_skin()
{
  Glib::ustring toparse = "pixmap_path  ";
  toparse +=     " '";
  toparse +=        GX_LV2_STYLE_DIR;
  toparse +=     "/'\n";
  toparse +=     "style \"gx_";
  toparse +=     plug_name;
  toparse +=     "_dark-paintbox\"\n"
                 " { \n"
                 "GxPaintBox::skin-gradient = {\n"
                 "{ 65536, 983, 983, 983, 65536 }, \n"
                 "{ 32768, 6276, 6276, 6276, 65536 },\n"
                 "{ 0, 22760, 22760, 22760, 65536 }}\n"
                 " GxPaintBox::box-gradient = {\n"
                 "{ 0, 6142, 6142, 6142, 62428 }, \n"
                 "{ 22768, 53, 53, 53, 42428 }, \n"
                 "{ 52428, 8, 8, 80, 32428 }, \n"
                 "{ 65536, 5364, 5364, 5364, 52428 }} \n"
                 "    base[NORMAL]     = '#000000'      \n"
                 "    GxPaintBox::icon-set =11\n"
                 " }\n"
                 "\n"
                 "style 'gx_head_expander_box' \n"
                 " { \n"
                 "    fg[NORMAL] = '#c0c6d0' \n"
                 "    font_name = 'sans 7.5 bold' \n"
                 " }\n";

  toparse +=     " widget '*.amplabel' style:highest 'gx_head_expander_box'\n";
  toparse +=     " style \"gx_";
  toparse +=     plug_name;
  toparse +=     "_slevel\"\n"
                 "{\n"
                 "stock['levelslider'] = {{'simplelevelslider.png'}}\n"
                 "GxLevelSlider::slider-width = 3\n"
                 "GxRegler::show-value = 0\n"
                 "}\n"
                 "widget '*.";
  toparse +=     plug_name;
  toparse +=     "' style 'gx_";
  toparse +=     plug_name;
  toparse +=     "_slevel' "

                 "widget '*.";
  toparse +=     plug_name;
  toparse +=     "' style 'gx_";
  toparse +=     plug_name;
  toparse +=     "_dark-paintbox' "
                 "style 'gx_fastmeter'\n"
                 " {\n"
                 "   base[NORMAL]     = '#000000'      \n"
                 "   GxFastMeter::clr-bottom = '#003808'\n"
                 "   GxFastMeter::clr-middle = '#00ff00'\n"
                 "   GxFastMeter::clr-top    = '#ff0000'\n"
                 "   GxFastMeter::over       = '#ff0000'\n"
                 " }\n"
                 " class '*GxFastMeter' style:highest 'gx_fastmeter'\n";

  gtk_rc_parse_string (toparse.c_str());
}

void Gx_graphiceq_GUI::set_plug_name( const char * plugin_uri)
{

  if (strcmp("http://guitarix.sourceforge.net/plugins/gx_graphiceq_#_graphiceq_", plugin_uri) == 0)
    {
      plug_name = "_graphiceq_";
    }
  else
    {
      plug_name = "_graphiceq_";
    }
}

GtkWidget* Gx_graphiceq_GUI::make_gui()
{
  // init the gxwmm library
  Gxw::init();
  set_skin();
  GtkWidget* container = gtk_vbox_new(FALSE, 2);
  widget = new Widget(plug_name);
  GtkWidget* cWidget = GTK_WIDGET(widget->gobj());
  gtk_container_add(GTK_CONTAINER(container), cWidget );

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
  Gx_graphiceq_GUI* self = new Gx_graphiceq_GUI();
  if (self == NULL) return NULL;
  self->set_plug_name_static(self, plugin_uri);
  *widget = (LV2UI_Widget)self->make_gui_static(self);
  self->widget->controller = controller;
  self->widget->write_function = write_function;
  return (LV2UI_Handle)self;
}

static void cleanup(LV2UI_Handle ui)
{
  Gx_graphiceq_GUI *pluginGui = static_cast<Gx_graphiceq_GUI*>(ui);
  delete pluginGui->widget;
  delete pluginGui;
}

static void port_event(LV2UI_Handle ui,
                       uint32_t port_index,
                       uint32_t buffer_size,
                       uint32_t format,
                       const void * buffer)
{
  Gx_graphiceq_GUI *self = static_cast<Gx_graphiceq_GUI*>(ui);
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


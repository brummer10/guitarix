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
#include "gx_chorus.h"
#include "widget.h"


#include <lv2.h>
#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>

using namespace std;

class Gx_chorus_stereoGUI
{
private:
  Glib::ustring plugskin;
  Glib::ustring addKnob;
  Glib::ustring plug_name;
  void set_knob(Glib::ustring knob);
  void set_skin();
  void set_plug_name(const char * plugin_uri);
  GtkWidget* make_gui();
public:

  Widget* widget;
  static void set_plug_name_static(Gx_chorus_stereoGUI *self, const char * plugin_uri)
  {
    self->set_plug_name(plugin_uri);
  }
  static GtkWidget* make_gui_static(Gx_chorus_stereoGUI *self)
  {
    return self->make_gui();
  }

  Gx_chorus_stereoGUI () {};
  ~Gx_chorus_stereoGUI () {};
} ;

void Gx_chorus_stereoGUI::set_knob( Glib::ustring knob)
{
  addKnob =   " style 'gx_";
  addKnob +=  plug_name;
  addKnob +=   "_dark_skin_icons'\n"
               " { \n"
               "    GxKnob::x_center          = -1\n"
               "    GxKnob::y_center          = -1\n"
               "    GxKnob::ring_radius       = 26\n"
               "    GxKnob::ring_width        = 3\n"
               "    GxKnob::ring_led_size     = 3\n"
               "    GxKnob::ring_led_distance = 2\n"
               "    GxKnob::indicator_radius  = 12\n"
               "    GxKnob::indicator_width   = 3\n"
               "    GxKnob::indicator_length  = 3\n"
               "   stock['bigknob'] = {{'";
  addKnob +=  "knob_small_r.png'}}\n"
              "   stock['smallknob'] = {{'";
  addKnob +=  "knob_small_r.png'}}\n"
              "   stock['smallknobr'] = {{'";
  addKnob +=  "knob_small_r.png'}}\n"
              "   stock['button_on'] = {{'"
              "echo-switch_on.png'}}\n"
              "   stock['button_off'] = {{'"
              "echo-switch_off.png'}}\n"
              " }\n"
              "widget '*.";
  addKnob +=  plug_name;
  addKnob +=  "' style 'gx_";
  addKnob +=  plug_name;
  addKnob +=  "_dark_skin_icons' \n"
              "class '*GxToggleImage' style'gx_"; 
  addKnob +=  plug_name;
  addKnob +=  "_dark_skin_icons' \n";
}

void Gx_chorus_stereoGUI::set_skin()
{
  Glib::ustring toparse = "pixmap_path  ";
  toparse +=     " '";
  toparse +=        GX_LV2_STYLE_DIR;
  toparse +=     "/'\n";
  toparse +=     "style \"gx_";
  toparse +=     plug_name;
  toparse +=     "_dark-paintbox\"\n"
                 " { \n"
                 "    GxPaintBox::icon-set =9\n"
                 " }\n"
                 "\n"
                 "style 'gx_head_black_box' \n"
                 " { \n"
                 "    font_name = 'sans bold 7.5'\n"
                 "    fg[NORMAL] = '#ff9000' \n"
                 " }\n";
  toparse +=     addKnob;

  toparse +=     " widget '*.amplabel' style:highest 'gx_head_black_box'\n"
                 "widget '*.";
  toparse +=     plug_name;
  toparse +=     "' style 'gx_";
  toparse +=     plug_name;
  toparse +=     "_dark-paintbox' ";

  toparse +=     "style 'guitarix_default' {\n"
    
                 "    GxPaintBox::bevel                  = 0.11\n"
                 "    GxPaintBox::inverse                = 0\n"
                 "    GxPaintBox::alternate-box          = { 0, 0, 10, 10 }\n"

                 "    fg[NORMAL]              = '#ff9000'\n"
                 "    fg[ACTIVE]              = { 1.0, 1.0, 1.0 }\n"
                 "    fg[PRELIGHT]            = { 1.0, 1.0, 1.0 }\n"
                 "    fg[INSENSITIVE]         = { 0.5, 0.5, 0.5 }\n"
                 "    fg[SELECTED]            = { 0.9, 0.9, 0.9 }\n"
    
                 "    bg[NORMAL]              = { 0.13, 0.13, 0.13 }\n"
                 "    bg[ACTIVE]              = { 0.0, 0.0, 0.0 }\n"
                 "    bg[PRELIGHT]            = { 0.25, 0.25, 0.25 }\n"
                 "    bg[INSENSITIVE]         = { 0.2, 0.2, 0.2 }\n"
                 "    bg[SELECTED]            = { 0.25, 0.25, 0.25 }\n"
    
                 "    text[NORMAL]            = { 0.9, 0.9, 0.9 }\n"
                 "    text[ACTIVE]            = '#ff9000'\n"
                 "    text[PRELIGHT]          = { 1.0, 1.0, 1.0 }\n"
                 "    text[INSENSITIVE]       = { 0.5, 0.5, 0.5 }\n"
                 "    text[SELECTED]          = { 1.0, 1.0, 1.0 }\n"
    
                 "    base[NORMAL]            = { 0.0, 0.0, 0.0 }\n"
                 "    base[ACTIVE]            = { 0.18, 0.18, 0.18 }\n"
                 "    base[PRELIGHT]          = { 0.1, 0.1, 0.1 }\n"
                 "    base[INSENSITIVE]       = { 0.2, 0.2, 0.2 }\n"
                 "    base[SELECTED]          = { 0.8, 0.18, 0.18 }\n"
                 "}\n"
                 "widget '*.";
  toparse +=     plug_name;
  toparse +=     "' style:highest 'guitarix_default'\n";
  toparse +=     " style 'gx_selector'\n"
                 " {\n"
                 " fg[NORMAL]     = '#ff9000'   \n"
                 " fg[PRELIGHT]   = '#ffffff'    \n"
                 " bg[NORMAL]     = '#2f2f2f'     \n"
                 " bg[PRELIGHT]   = '#2f2f2f'      \n"
                 " base[NORMAL]   = { 0.05, 0.05, 0.05 } \n"
                 " base[PRELIGHT] = '#000000'      \n"
                 " text[NORMAL]   = '#ff9000'     \n"
                 " text[PRELIGHT] = '#ffffff'    \n"
                 " GxRegler::value-border      = { 4, 4, 2, 2 } \n"
                 " GxRegler::border-radius     = 6\n"
                 " GxRegler::bevel             = 0.12\n"
                 " GtkRange::trough-border = 2\n"
                 " GtkRange::stepper-size = 8\n"
                 " GtkRange::stepper-spacing = 2\n"
                 " GxRegler::value-border = { 2, 0, 0, 0 }\n"
                 " font_name = 'sans bold 7.5'\n"
                 " xthickness = 8\n"
                 " ythickness = 4\n"
                 " }\n"
                 "class '*GxSelector' style:highest 'gx_selector'\n";

  gtk_rc_parse_string (toparse.c_str());
}

void Gx_chorus_stereoGUI::set_plug_name( const char * plugin_uri)
{
  addKnob = "";

  if (strcmp("http://guitarix.sourceforge.net/plugins/gx_chorus_stereo#_chorus_stereo", plugin_uri) == 0)
    {
      plug_name = "_chorus_stereo";
      set_knob("nk-knob");
    }
  else
    {
      plug_name = "_chorus_stereo";
    }
}

GtkWidget* Gx_chorus_stereoGUI::make_gui()
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
  Gx_chorus_stereoGUI* self = new Gx_chorus_stereoGUI();
  if (self == NULL) return NULL;
  self->set_plug_name_static(self, plugin_uri);
  *widget = (LV2UI_Widget)self->make_gui_static(self);
  self->widget->controller = controller;
  self->widget->write_function = write_function;
  return (LV2UI_Handle)self;
}

static void cleanup(LV2UI_Handle ui)
{
  Gx_chorus_stereoGUI *pluginGui = static_cast<Gx_chorus_stereoGUI*>(ui);
  delete pluginGui->widget;
  delete pluginGui;
}

static void port_event(LV2UI_Handle ui,
                       uint32_t port_index,
                       uint32_t buffer_size,
                       uint32_t format,
                       const void * buffer)
{
  Gx_chorus_stereoGUI *self = static_cast<Gx_chorus_stereoGUI*>(ui);
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


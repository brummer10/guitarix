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
#include "gx_colwah.h"
#include "widget.h"


#include <lv2.h>
#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>

using namespace std;

class Gx_colwah_GUI
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
  static void set_plug_name_static(Gx_colwah_GUI *self, const char * plugin_uri)
  {
    self->set_plug_name(plugin_uri);
  }
  static GtkWidget* make_gui_static(Gx_colwah_GUI *self)
  {
    return self->make_gui();
  }

  Gx_colwah_GUI () {};
  ~Gx_colwah_GUI () {};
} ;

void Gx_colwah_GUI::set_knob( Glib::ustring knob)
{
  addKnob =   " style 'gx_";
  addKnob +=  plug_name;
  addKnob +=   "_dark_skin_icons'\n"
               " { \n"
               "   stock['bigknob'] = {{'";
  addKnob +=  knob;
  addKnob +=  ".png'}}\n"
              "   stock['smallknob'] = {{'";
  addKnob +=  knob;
  addKnob +=  "-small.png'}}\n"
              "   stock['smallknobr'] = {{'";
  addKnob +=  knob;
  addKnob +=  "-middle.png'}}\n"
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

void Gx_colwah_GUI::set_skin()
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
                 "    stock['gxhead'] = {{'";
  toparse +=     plugskin;
  toparse +=     "'}}\n"
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
                 "    GxPaintBox::alternate-box          = { 0, 0, 30, 15 }\n"

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
  toparse +=     " style 'guitarix_knobs' {\n"
                 "    fg[INSENSITIVE] = '#211006'\n"
                 "}\n"
                 "class 'GxKnob' style:highest 'guitarix_knobs'\n"

                 "style 'guitarix_small_knob' {\n"
                 "    GxKnob::x_center          = -1\n"
                 "    GxKnob::y_center          = -1\n"
                 "    GxKnob::ring_radius       = 15\n"
                 "    GxKnob::ring_width        = 2\n"
                 "    GxKnob::ring_led_size     = 3\n"
                 "    GxKnob::ring_led_distance = 2\n"
                 "    GxKnob::indicator_radius  = 11\n"
                 "    GxKnob::indicator_width   = 2\n"
                 "    GxKnob::indicator_length  = 5\n"
                 "}\n"
                 "widget_class '*GxSmallKnob' style:highest 'guitarix_small_knob'\n"

                 "style 'guitarix_small_knob_r' {\n"
                 "    GxKnob::x_center          = -1\n"
                 "    GxKnob::y_center          = -1\n"
                 "    GxKnob::ring_radius       = 26\n"
                 "    GxKnob::ring_width        = 3\n"
                 "    GxKnob::ring_led_size     = 3\n"
                 "    GxKnob::ring_led_distance = 2\n"
                 "    GxKnob::indicator_radius  = 12\n"
                 "    GxKnob::indicator_width   = 3\n"
                 "    GxKnob::indicator_length  = 3\n"
                 "}\n"
                 "widget_class '*GxSmallKnobR' style:highest 'guitarix_small_knob_r'\n"

                 "style 'guitarix_mid_knob' {\n"
                 "    GxKnob::x_center          = -1\n"
                 "    GxKnob::y_center          = -1\n"
                 "    GxKnob::ring_radius       = 35\n"
                 "    GxKnob::ring_width        = 6\n"
                 "    GxKnob::ring_led_size     = 2\n"
                 "    GxKnob::ring_led_distance = 2\n"
                 "    GxKnob::indicator_radius  = 27\n"
                 "    GxKnob::indicator_width   = 2\n"
                 "    GxKnob::indicator_length  = 6\n"
                 "}\n"
                 "widget_class '*GxMidKnob' style:highest 'guitarix_mid_knob'\n"

                 "style 'guitarix_big_knob' {\n"
                 "    GxKnob::x_center          = -1\n"
                 "    GxKnob::y_center          = -1\n"
                 "    GxKnob::ring_radius       = 50.5\n"
                 "    GxKnob::ring_width        = 3\n"
                 "    GxKnob::ring_led_size     = 0\n"
                 "    GxKnob::ring_led_distance = 0\n"
                 "    GxKnob::indicator_radius  = 46\n"
                 "    GxKnob::indicator_width   = 3\n"
                 "    GxKnob::indicator_length  = 6\n"
                 "}\n"
                 "widget_class '*GxBigKnob' style:highest 'guitarix_big_knob'\n"
              " \n";

  gtk_rc_parse_string (toparse.c_str());
}

void Gx_colwah_GUI::set_plug_name( const char * plugin_uri)
{
  addKnob = "";

  if (strcmp("http://guitarix.sourceforge.net/plugins/gx_colwah_gui#_colwah_", plugin_uri) == 0)
    {
      plug_name = "Wahwah";
      //set_knob("nk-knob");
    }
  else
    {
      plug_name = "Wahwah";
    }
}

GtkWidget* Gx_colwah_GUI::make_gui()
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
  Gx_colwah_GUI* self = new Gx_colwah_GUI();
  if (self == NULL) return NULL;
  self->set_plug_name_static(self, plugin_uri);
  *widget = (LV2UI_Widget)self->make_gui_static(self);
  self->widget->controller = controller;
  self->widget->write_function = write_function;
  return (LV2UI_Handle)self;
}

static void cleanup(LV2UI_Handle ui)
{
  Gx_colwah_GUI *pluginGui = static_cast<Gx_colwah_GUI*>(ui);
  delete pluginGui->widget;
  delete pluginGui;
}

static void port_event(LV2UI_Handle ui,
                       uint32_t port_index,
                       uint32_t buffer_size,
                       uint32_t format,
                       const void * buffer)
{
  Gx_colwah_GUI *self = static_cast<Gx_colwah_GUI*>(ui);
  self->widget->set_value_static( port_index, buffer_size, format, buffer, self->widget);
  return;
}

static LV2UI_Descriptor descriptors[] =
{
  {GXPLUGIN_UI_URI"#_colwah_", instantiate, cleanup, port_event, NULL}
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


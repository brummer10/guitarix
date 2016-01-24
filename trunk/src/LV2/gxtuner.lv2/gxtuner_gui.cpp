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
#include "gxtuner.h"
#include "widget.h"


#include <lv2.h>
#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>

using namespace std;

class GxtunerGUI
{
private:

  Glib::ustring plugskin;
  Glib::ustring addKnob;
  Glib::ustring plug_name;
  void set_knob(Glib::ustring knob);
  void set_skin();
  void set_plug_name(const char * plugin_uri);
  GtkWidget* make_gui();
  Widget* widget;

public:

  static LV2UI_Handle instantiate(const struct _LV2UI_Descriptor * descriptor,
                                  const char * plugin_uri,
                                  const char * bundle_path,
                                  LV2UI_Write_Function write_function,
                                  LV2UI_Controller controller,
                                  LV2UI_Widget * widget,
                                  const LV2_Feature * const * features);

  static void port_event(LV2UI_Handle ui, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void *                   buffer);

  static LV2UI_Descriptor descriptors[];
  static void cleanup(LV2UI_Handle ui);

  GxtunerGUI () {};
  ~GxtunerGUI () {};
} ;

void GxtunerGUI::set_knob(Glib::ustring knob)
{
  addKnob =   " style 'gx_";
  addKnob +=  plug_name;
  addKnob +=   "_dark_skin_icons'\n"
               " { \n"
               "   stock['bigknob'] = {{'";
  addKnob +=  knob;
  addKnob +=  ".png'}}\n";
  addKnob +=  "   stock['smallknobr'] = {{'";
  addKnob +=  knob;
  addKnob +=  "-middle.png'}}\n";
  addKnob +=  "   stock['button_on'] = {{'"
              "push-switch-on.png'}}\n"
              "   stock['button_off'] = {{'"
              "push-switch-off.png'}}\n"
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

void GxtunerGUI::set_skin()
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
                 "{ 65536, 0, 0, 13107, 52428 }, \n"
                 "{ 52428, 0, 0, 0, 52428 },\n"
                 "{ 13107, 0, 0, 13107, 13107 }}\n"
                 " GxPaintBox::box-gradient = {\n"
                 "{ 0, 61, 61, 61, 62428 }, \n"
                 "{ 22768, 80, 83, 80, 42428 }, \n"
                 "{ 52428, 8, 8, 80, 32428 }, \n"
                 "{ 65536, 4, 4, 4, 52428 }} \n"

                 "   base[NORMAL]     = '#000000'      \n"
                 "    GxPaintBox::icon-set =11\n"
                 "    stock['gxhead'] = {{'";
  toparse +=     plugskin;
  toparse +=     "'}}\n"
                 " }\n";
  toparse +=     "style 'gx_headvalue_box' \n"
                 " { \n"
                 "    fg[NORMAL] = '#ff9000' \n"
                 "    fg[PRELIGHT] ='#00ffff'\n"
                 "    base[PRELIGHT] ='#222222'\n"
                 "    base[NORMAL] ='#000000'\n"
                 "    font_name = 'sans  7.5' \n"
                 " }\n";
  toparse +=     " widget '*.valuelabel' style:highest 'gx_headvalue_box'\n";
  toparse +=     "style 'gx_headtuner_box' \n"
                 " { \n"
                 "    fg[NORMAL] = '#888888' \n"
                 "    bg[PRELIGHT] ='#262640'\n"
                 "    font_name = 'sans  7.5' \n"
                 " }\n";
  toparse +=     addKnob;
  toparse +=     " widget '*.amplabel' style:highest 'gx_headtuner_box'\n"
                 "widget '*.";
  toparse +=     plug_name;
  toparse +=     "' style 'gx_";
  toparse +=     plug_name;
  toparse +=     "_dark-paintbox' ";
  toparse +=     "style 'gx_switch'\n"
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
                 "widget '*.";
  toparse +=     plug_name;
  toparse +=     "' style:highest 'gx_switch'\n";
  toparse +=     " style 'gx_selector_";
  toparse +=     plug_name;
  toparse +=     "'\n"
                 " {\n"
                 " fg[NORMAL] = '#888888'\n"
                 " GtkRange::trough-border = 2\n"
                 " GtkRange::stepper-size = 8\n"
                 " GtkRange::stepper-spacing = 2\n"
                 " GxRegler::value-border = { 2, 0, 0, 0 }\n"
                 " font_name = 'sans 7.5'\n"
                 " xthickness = 10\n"
                 " ythickness = 1\n"
                 " }\n"
                 "widget '*.";
  toparse +=     plug_name;
  toparse +=     "' style:highest 'gx_selector_";
  toparse +=     plug_name;
  toparse +=     "'\n";
  toparse +=     "style 'gx_fastmeter'\n"
                 " {\n"
                 "   base[NORMAL]     = '#000000'      \n"
                 "   GxFastMeter::clr-bottom = '#003808'\n"
                 "   GxFastMeter::clr-middle = '#00ff00'\n"
                 "   GxFastMeter::clr-top    = '#ff0000'\n"
                 "   GxFastMeter::over       = '#ff0000'\n"
                 " }\n"
                 " class '*GxFastMeter' style:highest 'gx_fastmeter'\n";
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
  toparse +=     "_slevel' ";
  toparse +=     "style 'guitarix_hslider' {\n"
                 "    GxHSlider::slider-width = 36\n"
                 "}\n"
                 "widget_class '*GxHSlider' style:highest 'guitarix_hslider'\n";

  toparse +=     "style 'guitarix_default' {\n"
    
                 "    GxPaintBox::bevel                  = 0.11\n"
                 "    GxPaintBox::inverse                = 0\n"
                 "    GxPaintBox::alternate-box          = { 0, 0, 15, 15 }\n"

                 "    fg[NORMAL]              = '#999999'\n"
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
                 "    text[ACTIVE]            = '#999999'\n"
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
                 " fg[NORMAL]     = '#999999'   \n"
                 " fg[PRELIGHT]   = '#ffffff'    \n"
                 " bg[NORMAL]     = '#2f2f2f'     \n"
                 " bg[PRELIGHT]   = '#2f2f2f'      \n"
                 " base[NORMAL]   = { 0.05, 0.05, 0.05 } \n"
                 " base[PRELIGHT] = '#000000'      \n"
                 " text[NORMAL]   = '#999999'     \n"
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

  toparse +=     "style 'gx_notes_style'\n"
                 "{\n"

                 "  bg[ACTIVE] = '#000000'\n"
                 "  bg[NORMAL] = '#49495a'\n"
                 "  bg[PRELIGHT] ='#262640'\n"

                 "  fg[NORMAL] = '#f1eded'\n"
                 "  fg[ACTIVE] = '#c5c5c5'\n"
                 "  fg[PRELIGHT] = '#ede9e9'\n"
                 "}\n"
                 "widget_class '*GtkToggleButton*' style:highest 'gx_notes_style'\n";


  gtk_rc_parse_string (toparse.c_str());
}

void GxtunerGUI::set_plug_name(const char * plugin_uri)
{
  addKnob = "";

  if (strcmp("http://guitarix.sourceforge.net/plugins/gxtuner#tuner", plugin_uri) == 0)
    {
      plugskin = "metalamp.png";
      plug_name = "gxtuner";
      set_knob("sn-knob");
    }
  else
    {
      plugskin = "preampmono.png";
      plug_name = "gxtuner";
    }
}

GtkWidget* GxtunerGUI::make_gui()
{
  // init the gxwmm library
  Gxw::init();
  set_skin();
  GtkWidget* container = gtk_vbox_new(FALSE, 0);
  widget = new Widget(plug_name);
  GtkWidget* cWidget = GTK_WIDGET(widget->gobj());
  gtk_container_add(GTK_CONTAINER(container), cWidget );

  return container;
}


LV2UI_Handle GxtunerGUI::instantiate(const struct _LV2UI_Descriptor * descriptor,
                                const char * plugin_uri,
                                const char * bundle_path,
                                LV2UI_Write_Function write_function,
                                LV2UI_Controller controller,
                                LV2UI_Widget * widget,
                                const LV2_Feature * const * features)
{
  GxtunerGUI* self = new GxtunerGUI();
  if (self == NULL) return NULL;
  self->set_plug_name(plugin_uri);
  *widget = (LV2UI_Widget)self->make_gui();
  self->widget->controller = controller;
  self->widget->write_function = write_function;
  return (LV2UI_Handle)self;
}

void GxtunerGUI::cleanup(LV2UI_Handle ui)
{
  GxtunerGUI *pluginGui = static_cast<GxtunerGUI*>(ui);
  delete pluginGui->widget;
  delete pluginGui;
}

void GxtunerGUI::port_event(LV2UI_Handle ui,
                       uint32_t port_index,
                       uint32_t buffer_size,
                       uint32_t format,
                       const void * buffer)
{
  GxtunerGUI *self = static_cast<GxtunerGUI*>(ui);
  self->widget->set_value_static( port_index, buffer_size, format, buffer, self->widget);
  return;
}

LV2UI_Descriptor GxtunerGUI::descriptors[] =
{
  {
    GXPLUGIN_UI_URI,
    GxtunerGUI::instantiate,
    GxtunerGUI::cleanup,
    GxtunerGUI::port_event,
    NULL
  }
};

const LV2UI_Descriptor * lv2ui_descriptor(uint32_t index)
{
  //printf("lv2ui_descriptor(%u) called\n", (uint32_t)index);
  if (index >= sizeof(GxtunerGUI::descriptors) /
               sizeof(GxtunerGUI::descriptors[0]))
    {
      return NULL;
    }
  return GxtunerGUI::descriptors + index;
}


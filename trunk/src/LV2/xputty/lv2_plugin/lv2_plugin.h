/*
 * Copyright (C) 2020 Hermann Meyer, Andreas Degert
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

#include "lv2/lv2plug.in/ns/lv2core/lv2.h"
#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"

// xwidgets.h includes xputty.h and all defined widgets from Xputty
#include "xwidgets.h"

// struct to define the knob pattern colors
typedef struct {
    double p1f[4];
    double p2f[4];
    double p3f[4];
    double p4f[4];
    double p5f[4];
    double p1k[4];
    double p2k[4];
    double p3k[4];
    double p4k[4];
    double p5k[4];
} KnobColors;


// main window struct
typedef struct {
    void *parentXwindow;
    Xputty main;
    Widget_t *win;
    Widget_t *widget[CONTROLS];
    KnobColors *kp;
    cairo_surface_t *screw;
    int block_event;

    void *controller;
    LV2UI_Write_Function write_function;
    LV2UI_Resize* resize;
} X11_UI;

// controller value changed, forward value to host when needed
void plugin_value_changed(X11_UI *ui, Widget_t *w, PortIndex index);

// set the plugin initial window size
void plugin_set_window_size(int *w,int *h);

// set the plugin name
const char* plugin_set_name();

// create all needed controller 
void plugin_create_controller_widgets(X11_UI *ui);

// add a knob to the main window
Widget_t* add_my_knob(Widget_t *w, PortIndex index, const char * label,
                                X11_UI* ui, int x, int y, int width, int height);

// add a image knob to the main window
Widget_t* add_my_image_knob(Widget_t *w, PortIndex index, const char * label,
                                X11_UI* ui, int x, int y, int width, int height);

// add a combobox to the main window
Widget_t* add_my_combobox(Widget_t *w, PortIndex index, const char * label, const char** items,
                                size_t len, int active, X11_UI* ui, int x, int y, int width, int height);

// free used mem on exit
void plugin_cleanup(X11_UI *ui);

// controller value changed message from host
void plugin_port_event(LV2UI_Handle handle, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void * buffer);

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

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define PortIndex and plugin uri
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#include "gxts9.h"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define controller numbers
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#define CONTROLS 3

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                include the LV2 interface
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#include "lv2_plugin.cc"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define the plugin settings
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

// setup a color theme
static void set_my_theme(Xputty *main) {
    main->color_scheme->normal = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.45, 0.45, 0.45, 1.0},
        .bg =       { 0.00, 0.33, 0.20, 1.00},
        .base =     { 0.00, 0.33, 0.20, 1.00},
        .text =     { 0.55, 0.55, 0.55, 1.0},
        .shadow =   { 0.0, 0.0, 0.0, 0.2},
        .frame =    { 0.0, 0.0, 0.0, 1.0},
        .light =    { 0.1, 0.1, 0.2, 1.0}
    };

    main->color_scheme->prelight = (Colors) {
        .fg =       { 1.0, 1.0, 1.0, 1.0},
        .bg =       { 0.16, 0.43, 0.20, 1.00},
        .base =     { 0.16, 0.43, 0.20, 1.00},
        .text =     { 0.7, 0.7, 0.7, 1.0},
        .shadow =   { 0.1, 0.1, 0.1, 0.4},
        .frame =    { 0.3, 0.3, 0.3, 1.0},
        .light =    { 0.3, 0.3, 0.3, 1.0}
    };

    main->color_scheme->selected = (Colors) {
        .fg =       { 0.9, 0.9, 0.9, 1.0},
        .bg =       { 0.16, 0.43, 0.20, 1.00},
        .base =     { 0.16, 0.43, 0.20, 1.00},
        .text =     { 1.0, 1.0, 1.0, 1.0},
        .shadow =   { 0.18, 0.18, 0.18, 0.2},
        .frame =    { 0.18, 0.18, 0.18, 1.0},
        .light =    { 0.18, 0.18, 0.28, 1.0}
    };
}

// set knob colors
static void set_my_knob_color(KnobColors* kp) {
    *kp = (KnobColors) {
         /* cairo    / r  / g  / b  / a  /  */
        .p1f =       { 0.20, 0.43, 0.20, 1.00},
        .p2f =       { 0.10, 0.33, 0.20, 1.0},
        .p3f =       { 0.15, 0.15, 0.15, 1.0},
        .p4f =       { 0.1, 0.1, 0.1, 1.00},
        .p5f =       { 0.05, 0.05, 0.05, 1.0},
        .p1k =       { 0.25, 0.25, 0.25, 1.00},
        .p2k =       { 0.2, 0.2, 0.2, 1.0},
        .p3k =       { 0.15, 0.15, 0.15, 1.0},
        .p4k =       { 0.1, 0.1, 0.1, 1.00},
        .p5k =       { 0.05, 0.05, 0.05, 1.0},
    };
}

void plugin_value_changed(X11_UI *ui, Widget_t *w, PortIndex index) {
    // do special stuff when needed
}

void plugin_set_window_size(int *w,int *h,const char * plugin_uri) {
    (*w) = 260; //initial widht of main window
    (*h) = 300; //initial heigth of main window
}

const char* plugin_set_name() {
    return "GxTubeScreamer"; //plugin name to display on UI
}

void plugin_create_controller_widgets(X11_UI *ui, const char * plugin_uri) {
    set_my_theme(&ui->main);
    set_my_knob_color(ui->kp);
    widget_get_png(ui->win, LDVAR(guitarix_png));
    ui->widget[0] = add_my_knob(ui->widget[0], TS9_DRIVE,"Drive", ui,30, 50, 80, 105);
    set_adjustment(ui->widget[0]->adj,0.5, 0.5, 0.0, 1.0, 0.01, CL_CONTINUOS);

    ui->widget[1] = add_my_knob(ui->widget[1], TS9_LEVEL,"Level", ui,150, 50, 80, 105);
    set_adjustment(ui->widget[1]->adj,-16.0, -16.0, -20.0, 4.0, 0.01, CL_LOGSCALE);

    ui->widget[2] = add_my_knob(ui->widget[2], TS9_TONE,"Tone", ui,100, 120, 60, 85);
    set_adjustment(ui->widget[2]->adj,400.0, 400.0, 100.0, 1000.0, 0.001, CL_LOGARITHMIC);
    adj_set_scale(ui->widget[2]->adj, 2.0);
}

void plugin_cleanup(X11_UI *ui) {
}

void plugin_port_event(LV2UI_Handle handle, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void * buffer) {
}

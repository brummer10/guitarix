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

#include "gx_zita_rev1.h"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define controller numbers
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#define CONTROLS 11

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
        .p1f =       { 0.25, 0.25, 0.25, 1.00},
        .p2f =       { 0.20, 0.20, 0.20, 1.0},
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

void plugin_set_window_size(int *w,int *h) {
    (*w) = 900; //initial widht of main window
    (*h) = 180; //initial heigth of main window
}

const char* plugin_set_name() {
    return "GxZitaReverb1"; //plugin name to display on UI
}

void plugin_create_controller_widgets(X11_UI *ui) {
    set_my_theme(&ui->main);
    set_my_knob_color(ui->kp);
    widget_get_png(ui->win, LDVAR(guitarix_png));
    ui->widget[0] = add_my_knob(ui->widget[0], IN_DELAY,"Delay", ui,40, 50, 80, 115);
    set_adjustment(ui->widget[0]->adj,60.0, 60.0, 20.0, 100.0, 0.1, CL_CONTINUOS);

    ui->widget[1] = add_my_knob(ui->widget[1], LF_X,"Freq X", ui,140, 20, 60, 85);
    set_adjustment(ui->widget[1]->adj,2.3, 2.3, 1.7, 3.0, 0.001, CL_LOGARITHMIC);
    adj_set_scale(ui->widget[1]->adj, 2.0);

    ui->widget[2] = add_my_knob(ui->widget[2], LOW_RT60,"Low", ui,210, 20, 60, 85);
    set_adjustment(ui->widget[2]->adj,0.477, 0.477, 0.004, 0.9, 0.001, CL_LOGARITHMIC);
    adj_set_scale(ui->widget[2]->adj, 2.0);

    ui->widget[3] = add_my_knob(ui->widget[3], MID_RT60,"Mid", ui,280, 20, 60, 85);
    set_adjustment(ui->widget[3]->adj,0.477, 0.477, 0.004, 0.9, 0.001, CL_LOGARITHMIC);
    adj_set_scale(ui->widget[3]->adj, 2.0);

    ui->widget[4] = add_my_knob(ui->widget[4], HF_DAMPING,"HF Damp", ui,350, 20, 60, 85);
    set_adjustment(ui->widget[4]->adj,3.78, 3.78, 3.17, 4.37, 0.001, CL_LOGARITHMIC);
    adj_set_scale(ui->widget[4]->adj, 2.0);

    ui->widget[5] = add_my_knob(ui->widget[5], EQ1_FREQ,"EQ1 Freq", ui,430, 60, 60, 85);
    set_adjustment(ui->widget[5]->adj,2.5, 2.5, 1.6, 3.4, 0.001, CL_LOGARITHMIC);
    adj_set_scale(ui->widget[5]->adj, 3.0);

    ui->widget[6] = add_my_knob(ui->widget[6], EQ1_LEVEL,"Level", ui,500, 20, 60, 85);
    set_adjustment(ui->widget[6]->adj,0.0, 0.0, -15.0, 15.0, 0.01, CL_CONTINUOS);
    adj_set_scale(ui->widget[6]->adj, 5.0);

    ui->widget[7] = add_my_knob(ui->widget[7], EQ2_FREQ,"EQ2 Freq", ui,580, 60, 60, 85);
    set_adjustment(ui->widget[7]->adj,3.17, 3.17, 2.2, 4.0, 0.001, CL_LOGARITHMIC);
    adj_set_scale(ui->widget[7]->adj, 3.0);

    ui->widget[8] = add_my_knob(ui->widget[8], EQ2_LEVEL,"Level", ui,650, 20, 60, 85);
    set_adjustment(ui->widget[8]->adj,0.0, 0.0, -15.0, 15.0, 0.01, CL_CONTINUOS);
    adj_set_scale(ui->widget[8]->adj, 5.0);

    ui->widget[9] = add_my_knob(ui->widget[9], DRY_WET_MIX,"Mix", ui,730, 70, 60, 85);
    set_adjustment(ui->widget[9]->adj,0.0, 0.0, -1.0, 1.0, 0.01, CL_CONTINUOS);

    ui->widget[10] = add_my_knob(ui->widget[10], LEVEL,"Level", ui,800, 30, 60, 85);
    set_adjustment(ui->widget[10]->adj,0.0, 0.0, -70.0, 40.0, 0.1, CL_CONTINUOS);
    adj_set_scale(ui->widget[7]->adj, 2.0);
}

void plugin_cleanup(X11_UI *ui) {
}

void plugin_port_event(LV2UI_Handle handle, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void * buffer) {
}

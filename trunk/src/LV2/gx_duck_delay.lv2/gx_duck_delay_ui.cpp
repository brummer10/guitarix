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

#include "gx_duck_delay.h"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define controller numbers
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#define CONTROLS 6 

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
        /*fg */       { 0.45, 0.45, 0.45, 1.0},
        /*bg */       { 0.24, 0.09, 0.00, 1.00},
        /*base */     { 0.24, 0.09, 0.00, 1.00},
        /*text */     { 0.45, 0.45, 0.45, 1.0},
        /*shadow */   { 0.0, 0.0, 0.0, 0.2},
        /*frame */    { 0.0, 0.0, 0.0, 1.0},
        /*light */    { 0.1, 0.1, 0.2, 1.0}
    };

    main->color_scheme->prelight = (Colors) {
        /*fg */       { 1.0, 1.0, 1.0, 1.0},
        /*bg */       { 0.36, 0.11, 0.17, 1.00},
        /*base */     { 0.36, 0.11, 0.17, 1.00},
        /*text */     { 0.7, 0.7, 0.7, 1.0},
        /*shadow */   { 0.1, 0.1, 0.1, 0.4},
        /*frame */    { 0.3, 0.3, 0.3, 1.0},
        /*light */    { 0.3, 0.3, 0.3, 1.0}
    };

    main->color_scheme->selected = (Colors) {
        /*fg */       { 0.9, 0.9, 0.9, 1.0},
        /*bg */       { 0.36, 0.11, 0.17, 1.00},
        /*base */     { 0.36, 0.11, 0.17, 1.00},
        /*text */     { 1.0, 1.0, 1.0, 1.0},
        /*shadow */   { 0.18, 0.18, 0.18, 0.2},
        /*frame */    { 0.18, 0.18, 0.18, 1.0},
        /*light */    { 0.18, 0.18, 0.28, 1.0}
    };
}

void plugin_value_changed(X11_UI *ui, Widget_t *w, PortIndex index) {
    // do special stuff when needed
}

void plugin_set_window_size(int *w,int *h,const char * plugin_uri) {
    (*w) = 650; //set initial widht of main window
    (*h) = 180; //set initial heigth of main window
}

const char* plugin_set_name() {
    return "GxDuckDelay"; //set plugin name to display on UI
}

void plugin_create_controller_widgets(X11_UI *ui, const char * plugin_uri) {
    set_my_theme(&ui->main);
    widget_get_png(ui->win, LDVAR(guitarix_png));
    // create all controllers needed
    ui->widget[0] = add_my_knob(ui->widget[0], TIME,"Time", ui,120, 35, 80, 105);
    set_adjustment(ui->widget[0]->adj,500.0, 500.0, 1.0, 2000.0, 1.0, CL_CONTINUOS);
    adj_set_scale(ui->widget[0]->adj, 10.0);
    
    ui->widget[1] = add_my_knob(ui->widget[1], FEEDBACK,"Feedback", ui,220, 35, 80, 105);
    set_adjustment(ui->widget[1]->adj,0.0, 0.0, 0.0, 1.0, 0.01, CL_CONTINUOS);

    ui->widget[2] = add_my_knob(ui->widget[2], ATTACK,"Attack", ui,320, 35, 80, 105);
    set_adjustment(ui->widget[2]->adj,0.1, 0.1, 0.05, 0.5, 0.001, CL_CONTINUOS);
    adj_set_scale(ui->widget[2]->adj, 2.0);

    ui->widget[3] = add_my_knob(ui->widget[3], RELESE,"Release", ui,420, 35, 80, 105);
    set_adjustment(ui->widget[3]->adj,0.1, 0.1, 0.05, 2.0, 0.01, CL_CONTINUOS);
    adj_set_scale(ui->widget[3]->adj, 2.0);

    ui->widget[4] = add_my_knob(ui->widget[4], AMOUNT,"Amount", ui,520, 35, 80, 105);
    set_adjustment(ui->widget[4]->adj,0.5, 0.5, 0.0, 56.0, 0.1, CL_CONTINUOS);
    adj_set_scale(ui->widget[4]->adj, 5.0);

    ui->widget[5] = add_on_off_button(ui->win, "Power", 50, 50, 40, 80);
    ui->widget[5]->scale.gravity = ASPECT;
    ui->widget[5]->data = BYPASS;
    ui->widget[5]->parent_struct = ui;
    ui->widget[5]->func.value_changed_callback = value_changed;
}

void plugin_cleanup(X11_UI *ui) {
    // clean up used sources when needed
}

void plugin_port_event(LV2UI_Handle handle, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void * buffer) {
    // port value change message from host
    // do special stuff when needed
}


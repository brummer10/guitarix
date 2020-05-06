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

#include "gx_colwah.h"

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
        /*bg */       { 0.35, 0.0, 0.0, 1.0},
        /*base */     { 0.35, 0.0, 0.0, 1.0},
        /*text */     { 0.45, 0.45, 0.45, 1.0},
        /*shadow */   { 0.0, 0.0, 0.0, 0.2},
        /*frame */    { 0.0, 0.0, 0.0, 1.0},
        /*light */    { 0.1, 0.1, 0.2, 1.0}
    };

    main->color_scheme->prelight = (Colors) {
        /*fg */       { 1.0, 1.0, 1.0, 1.0},
        /*bg */       { 0.25, 0.25, 0.25, 1.0},
        /*base */     { 0.35, 0.13, 0.17, 1.0},
        /*text */     { 0.7, 0.7, 0.7, 1.0},
        /*shadow */   { 0.1, 0.1, 0.1, 0.4},
        /*frame */    { 0.3, 0.3, 0.3, 1.0},
        /*light */    { 0.3, 0.3, 0.3, 1.0}
    };

    main->color_scheme->selected = (Colors) {
        /*fg */       { 0.9, 0.9, 0.9, 1.0},
        /*bg */       { 0.35, 0.13, 0.17, 1.00 },
        /*base */     { 0.35, 0.0, 0.0, 1.0},
        /*text */     { 1.0, 1.0, 1.0, 1.0},
        /*shadow */   { 0.18, 0.18, 0.18, 0.2},
        /*frame */    { 0.18, 0.18, 0.18, 1.0},
        /*light */    { 0.18, 0.18, 0.28, 1.0}
    };
}

static void set_my_knob_color(KnobColors* kp) {
    *kp = (KnobColors) {
         /* cairo    / r  / g  / b  / a  /  */
        /*p1f */       { 0.35, 0.13, 0.17, 1.0},
        /*p2f */       { 0.35, 0.0, 0.0, 1.0},
        /*p3f */       { 0.15, 0.15, 0.15, 1.0},
        /*p4f */       { 0.1, 0.1, 0.1, 1.00},
        /*p5f */       { 0.05, 0.05, 0.05, 1.0},
        /*p1k */       { 0.35, 0.0, 0.0, 1.0},
        /*p2k */       { 0.35, 0.13, 0.17, 1.0},
        /*p3k */       { 0.15, 0.15, 0.15, 1.0},
        /*p4k */       { 0.1, 0.1, 0.1, 1.00},
        /*p5k */       { 0.05, 0.05, 0.05, 1.0},
    };
}

void plugin_value_changed(X11_UI *ui, Widget_t *w, PortIndex index) {
    // do special stuff when needed
}

void plugin_set_window_size(int *w,int *h,const char * plugin_uri) {
    (*w) = 740; //set initial widht of main window
    (*h) = 180; //set initial heigth of main window
}

const char* plugin_set_name() {
    return "GxWahwah"; //set plugin name to display on UI
}

void plugin_create_controller_widgets(X11_UI *ui, const char * plugin_uri) {
    set_my_theme(&ui->main);
    set_my_knob_color(ui->kp);
    // create all controllers needed
    ui->widget[0] = add_my_knob(ui->widget[0], WAH,"Wah", ui,340, 25, 100, 125);
    set_adjustment(ui->widget[0]->adj,0.5, 0.5, 0.0, 1.0, 0.01, CL_CONTINUOS);

    ui->widget[1] = add_my_knob(ui->widget[1], FREQ,"Alien Freq", ui,460, 25, 100, 125);
    set_adjustment(ui->widget[1]->adj,24.0, 24.0, 24.0, 360.0, 1.0, CL_CONTINUOS);

    ui->widget[2] = add_my_knob(ui->widget[2], WET_DRY,"Dry/Wet", ui,580, 25, 100, 125);
    set_adjustment(ui->widget[2]->adj,50.0, 50.0, 0.0, 100.0, 1.0, CL_CONTINUOS);


    ui->widget[5] = add_on_off_button(ui->win, "Power", 50, 50, 40, 80);
    ui->widget[5]->scale.gravity = ASPECT;
    ui->widget[5]->data = BYPASS;
    ui->widget[5]->parent_struct = ui;
    ui->widget[5]->func.value_changed_callback = value_changed;
 
    const char* model[] = {"Colorsound Wah","Dallas Wah","Foxx Wah","Jen Wah","Maestro Wah","Selmer Wah","Vox Wah V847"};
    size_t len = sizeof(model) / sizeof(model[0]);
    ui->widget[3] = add_my_combobox(ui->widget[3], MODEL, "Model", model, len, 0, ui, 120, 40, 170, 30);

    const char* mode[] = {"manual","auto","alien"};
    len = sizeof(mode) / sizeof(mode[0]);
    ui->widget[4] = add_my_combobox(ui->widget[4], MODE, "Mode", mode, len, 0, ui, 120, 100, 170, 30);
}

void plugin_cleanup(X11_UI *ui) {
    // clean up used sources when needed
}

void plugin_port_event(LV2UI_Handle handle, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void * buffer) {
    X11_UI* ui = (X11_UI*)handle;
    if (port_index == (uint32_t) BYPASS) ui->block_event = -1;
}


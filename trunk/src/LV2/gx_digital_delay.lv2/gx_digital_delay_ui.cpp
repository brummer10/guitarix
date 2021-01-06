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

#include "gx_digital_delay.h"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define controller numbers
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#define CONTROLS 10 

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
        /*bg */       { 0.00, 0.00, 0.14, 1.00},
        /*base */     { 0.00, 0.00, 0.14, 1.00},
        /*text */     { 0.45, 0.45, 0.45, 1.0},
        /*shadow */   { 0.0, 0.0, 0.0, 0.2},
        /*frame */    { 0.0, 0.0, 0.0, 1.0},
        /*light */    { 0.1, 0.1, 0.1, 1.0}
    };

    main->color_scheme->prelight = (Colors) {
        /*fg */       { 1.0, 1.0, 1.0, 1.0},
        /*bg */       { 0.10, 0.31, 0.47, 1.00},
        /*base */     { 0.10, 0.31, 0.47, 1.00},
        /*text */     { 0.7, 0.7, 0.7, 1.0},
        /*shadow */   { 0.1, 0.1, 0.1, 0.4},
        /*frame */    { 0.3, 0.3, 0.3, 1.0},
        /*light */    { 0.3, 0.3, 0.3, 1.0}
    };

    main->color_scheme->selected = (Colors) {
        /*fg */       { 0.9, 0.9, 0.9, 1.0},
        /*bg */       { 0.10, 0.31, 0.47, 1.00},
        /*base */     { 0.10, 0.31, 0.47, 1.00},
        /*text */     { 1.0, 1.0, 1.0, 1.0},
        /*shadow */   { 0.18, 0.18, 0.18, 0.2},
        /*frame */    { 0.18, 0.18, 0.18, 1.0},
        /*light */    { 0.18, 0.18, 0.18, 1.0}
    };
}

static void set_my_knob_color(KnobColors* kp) {
    *kp = (KnobColors) {
         /* cairo    / r  / g  / b  / a  /  */
        /*p1f */       { 0.15, 0.15, 0.25, 1.0},
        /*p2f */       { 0.12, 0.12, 0.2, 1.0},
        /*p3f */       { 0.15, 0.15, 0.15, 1.0},
        /*p4f */       { 0.1, 0.1, 0.1, 1.00},
        /*p5f */       { 0.05, 0.05, 0.05, 1.0},
        /*p1k */       { 0.00, 0.00, 0.14, 1.0},
        /*p2k */       { 0.2, 0.2, 0.24, 1.0},
        /*p3k */       { 0.15, 0.15, 0.15, 1.0},
        /*p4k */       { 0.1, 0.1, 0.1, 1.00},
        /*p5k */       { 0.05, 0.05, 0.05, 1.0},
    };
}

void plugin_value_changed(X11_UI *ui, Widget_t *w, PortIndex index) {
    // do special stuff when needed
}

void plugin_set_window_size(int *w,int *h,const char * plugin_uri) {
    (*w) = 840; //set initial width of main window
    (*h) = 180; //set initial height of main window
}

const char* plugin_set_name() {
    return "GxDigitalDelay"; //set plugin name to display on UI
}

void plugin_create_controller_widgets(X11_UI *ui, const char * plugin_uri) {
    set_my_theme(&ui->main);
    set_my_knob_color(ui->kp);
    widget_get_png(ui->win, LDVAR(guitarix_png));
    // create all controllers needed
    ui->widget[0] = add_my_knob(ui->widget[0], BPM,"BPM", ui,290, 25, 100, 125);
    set_adjustment(ui->widget[0]->adj,120.0, 120.0, 24.0, 360.0, 1.0, CL_CONTINUOS);

    ui->widget[1] = add_my_knob(ui->widget[1], FEEDBACK,"Feedback", ui,550, 25, 60, 80);
    set_adjustment(ui->widget[1]->adj,50.0, 50.0, 1.0, 100.0, 1.0, CL_CONTINUOS);

    ui->widget[2] = add_my_knob(ui->widget[2], GAIN,"Gain", ui,690, 25, 100, 125);
    set_adjustment(ui->widget[2]->adj,100.0, 100.0, 0.0, 120.0, 1.0, CL_CONTINUOS);

    ui->widget[3] = add_my_knob(ui->widget[3], HIGHPASS,"HighPass", ui,400, 25, 60, 80);
    set_adjustment(ui->widget[3]->adj,120.0, 120.0, 20.0, 20000.0, 5.0, CL_CONTINUOS);
    adj_set_scale(ui->widget[3]->adj, pow(10,1.08));

    ui->widget[4] = add_my_knob(ui->widget[4], HOWPASS,"LowPass", ui,480, 25, 60, 80);
    set_adjustment(ui->widget[4]->adj,12000.0, 12000.0, 20.0, 20000.0, 5.0, CL_CONTINUOS);
    adj_set_scale(ui->widget[4]->adj, pow(10,1.08));

    ui->widget[5] = add_my_knob(ui->widget[5], LEVEL,"Level", ui,620, 25, 60, 80);
    set_adjustment(ui->widget[5]->adj,50.0, 50.0, 1.0, 100.0, 1.0, CL_CONTINUOS);

    // create combobox widgets
    const char* model[] = {"plain","presence","tape","tape2"};
    size_t len = sizeof(model) / sizeof(model[0]);
    ui->widget[6] = add_my_combobox(ui->widget[6], MODE, "Mode", model, len, 0, ui, 460, 110, 160, 30);

    const char* notes[] = {"Dotted 1/2 note","1/2 note","1/2 note triplets", 
                          "Dotted 1/4 note","1/4 note","1/4 note triplets", 
                          "Dotted 1/8 note","1/8 note","1/8 note triplets", 
                          "Dotted 1/16 note","1/16 note","1/16 note triplets", 
                          "Dotted 1/32 note","1/32 note","1/32 note triplets", 
                          "Dotted 1/64 note","1/64 note","1/64 note triplets"};
    len = sizeof(notes) / sizeof(notes[0]);
    ui->widget[7] = add_my_combobox(ui->widget[7], NOTES, "Notes",notes, len, 0, ui, 110, 50, 160, 30);

    const char* mode[] = {"BPM free scale","BPM host sync"};
    len = sizeof(mode) / sizeof(mode[0]);
    ui->widget[8] = add_my_combobox(ui->widget[8], SYNC, "BPM SYNC",mode, len, 0, ui, 110, 100, 160, 30);

    ui->widget[9] = add_on_off_button(ui->win, "Power", 50, 50, 40, 80);
    ui->widget[9]->scale.gravity = ASPECT;
    ui->widget[9]->data = BYPASS;
    ui->widget[9]->parent_struct = ui;
    ui->widget[9]->func.value_changed_callback = value_changed;
}

void plugin_cleanup(X11_UI *ui) {
    // clean up used sources when needed
}

void plugin_port_event(LV2UI_Handle handle, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void * buffer) {
    X11_UI* ui = (X11_UI*)handle;
    if (port_index == DD_NOTIFY) {
        float value = *(float*)buffer;
        if(adj_get_value(ui->widget[8]->adj)>0.1) {
            check_value_changed(ui->widget[0]->adj, &value);
        }
    } else if (port_index == (uint32_t) BYPASS) {
        ui->block_event = -1;
    }
}


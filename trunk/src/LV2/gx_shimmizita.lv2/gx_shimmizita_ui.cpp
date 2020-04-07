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

#include "gx_shimmizita.h"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define controller numbers
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#define CONTROLS 12

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

void plugin_value_changed(X11_UI *ui, Widget_t *w, PortIndex index) {
    // do special stuff when needed
}

void plugin_set_window_size(int *w,int *h,const char * plugin_uri) {
    (*w) = 500; //initial widht of main window
    (*h) = 380; //initial heigth of main window
}

const char* plugin_set_name() {
    return "Gxshimmizita"; //plugin name to display on UI
}

void plugin_create_controller_widgets(X11_UI *ui, const char * plugin_uri) {
    ui->widget[0] = add_my_knob(ui->widget[0], MODE,"Mode", ui,50, 40, 70, 95);
    set_adjustment(ui->widget[0]->adj,0.0, 0.0, -3.0, 3.0, 0.01, CL_CONTINUOS);
    adj_set_scale(ui->widget[0]->adj, 1.5);

    ui->widget[1] = add_my_knob(ui->widget[1], SHIFT,"PitchShift", ui,150, 40, 70, 95);
    set_adjustment(ui->widget[1]->adj,0.0, 0.0, -6.0, 6.0, 0.01, CL_CONTINUOS);
    adj_set_scale(ui->widget[1]->adj, 2.0);

    ui->widget[2] = add_my_knob(ui->widget[2], PSDRYWET,"PitchMix", ui,250, 40, 70, 95);
    set_adjustment(ui->widget[2]->adj,0.5, 0.5, 0.0, 1.0, 0.01, CL_CONTINUOS);

    ui->widget[3] = add_my_knob(ui->widget[3], ENVELOPE,"EnvTime", ui,30, 140, 70, 95);
    set_adjustment(ui->widget[3]->adj,1.0, 1.0, 0.1, 3.0, 0.01, CL_CONTINUOS);

    ui->widget[4] = add_my_knob(ui->widget[4], CONTROL,"ModSource", ui,110, 140, 70, 95);
    set_adjustment(ui->widget[4]->adj,0.5, 0.5, 0.0, 1.0, 0.01, CL_CONTINUOS);

    ui->widget[5] = add_my_knob(ui->widget[5], SPEED,"LFO Speed", ui,190, 140, 70, 95);
    set_adjustment(ui->widget[5]->adj,0.1, 0.1, 0.1, 10.0, 0.01, CL_CONTINUOS);
    adj_set_scale(ui->widget[5]->adj, 2.0);

    ui->widget[6] = add_my_knob(ui->widget[6], DEPTH,"ModDepth", ui,270, 140, 70, 95);
    set_adjustment(ui->widget[6]->adj,0.0, 0.0, 0.0, 1.0, 0.01, CL_CONTINUOS);

    ui->widget[7] = add_my_knob(ui->widget[7], F1,"FreqLow", ui,30, 245, 70, 95);
    set_adjustment(ui->widget[7]->adj,200.0, 200.0, 50.0, 1000.0, 0.01, CL_LOGARITHMIC);

    ui->widget[8] = add_my_knob(ui->widget[8], T60DS,"DecayLow", ui,110, 245, 70, 95);
    set_adjustment(ui->widget[8]->adj,3.0, 3.0, 1.0, 8.0, 0.01, CL_LOGARITHMIC);

    ui->widget[9] = add_my_knob(ui->widget[9], F2,"FreqHigh", ui,190, 245, 70, 95);
    set_adjustment(ui->widget[9]->adj,6000.0, 6000.0, 1500.0, 23520.0, 0.01, CL_LOGARITHMIC);

    ui->widget[10] = add_my_knob(ui->widget[10], T60M,"DecayHigh", ui,270, 245, 70, 95);
    set_adjustment(ui->widget[10]->adj,2.0, 2.0, 1.0, 8.0, 0.01, CL_LOGARITHMIC);

    ui->widget[11] = add_my_knob(ui->widget[11], DRYWET,"Mix", ui,360, 110, 100, 125);
    set_adjustment(ui->widget[11]->adj,0.5, 0.5, 0.0, 1.0, 0.01, CL_CONTINUOS);

}

void plugin_cleanup(X11_UI *ui) {
}

void plugin_port_event(LV2UI_Handle handle, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void * buffer) {
}

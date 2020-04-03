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

#include "gx_susta.h"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define controller numbers
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#define CONTROLS 2

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
    (*w) = 260; //initial widht of main window
    (*h) = 300; //initial heigth of main window
}

const char* plugin_set_name() {
    return "GxSustainer"; //plugin name to display on UI
}

void plugin_create_controller_widgets(X11_UI *ui, const char * plugin_uri) {
    ui->widget[0] = add_my_knob(ui->widget[0], SUSTAIN,"Sustain", ui,30, 40, 80, 105);
    set_adjustment(ui->widget[0]->adj,0.5, 0.5, 0.0, 1.0, 0.01, CL_CONTINUOS);

    ui->widget[1] = add_my_knob(ui->widget[1], VOLUME,"Volume", ui,150, 40, 80, 105);
    set_adjustment(ui->widget[1]->adj,0.5, 0.5, 0.0, 1.0, 0.01, CL_CONTINUOS);
}

void plugin_cleanup(X11_UI *ui) {
}

void plugin_port_event(LV2UI_Handle handle, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void * buffer) {
}

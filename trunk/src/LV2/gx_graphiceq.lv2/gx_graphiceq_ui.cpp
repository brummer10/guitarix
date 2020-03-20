
#include "lv2/lv2plug.in/ns/lv2core/lv2.h"
#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"

// xwidgets.h includes xputty.h and all defined widgets from Xputty
#include "xwidgets.h"

#include "gx_graphiceq.h"

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                define controller numbers
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#define CONTROLS 11

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                the main LV2 handle->XWindow
-----------------------------------------------------------------------
----------------------------------------------------------------------*/


// main window struct
typedef struct {
    void *parentXwindow;
    Xputty main;
    Widget_t *win;
    Widget_t *widget[CONTROLS];
    Widget_t *meter_widget[CONTROLS];
    cairo_surface_t *screw;
    int block_event;
    float db_zero;

    void *controller;
    LV2UI_Write_Function write_function;
    LV2UI_Resize* resize;
} X11_UI;

// setup a color theme
static void set_my_theme(Xputty *main) {
    main->color_scheme->normal = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.45, 0.45, 0.45, 1.0},
        .bg =       { 0.07, 0.05, 0.14, 1.00},
        .base =     { 0.0, 0.0, 0.0, 1.00},
        .text =     { 0.45, 0.45, 0.45, 1.0},
        .shadow =   { 0.28, 0.34, 0.62, 0.43},
        .frame =    { 0.0, 0.0, 0.0, 1.0},
        .light =    { 0.1, 0.1, 0.1, 1.0}
    };

    main->color_scheme->prelight = (Colors) {
        .fg =       { 1.0, 1.0, 1.0, 1.0},
        .bg =       { 0.14, 0.14, 0.22, 1.00},
        .base =     { 0.0, 0.0, 0.0, 1.00},
        .text =     { 0.7, 0.7, 0.7, 1.0},
        .shadow =   { 0.28, 0.34, 0.62, 0.63},
        .frame =    { 0.3, 0.3, 0.3, 1.0},
        .light =    { 0.3, 0.3, 0.3, 1.0}
    };

    main->color_scheme->selected = (Colors) {
        .fg =       { 0.9, 0.9, 0.9, 1.0},
        .bg =       { 0.14, 0.14, 0.22, 1.00},
        .base =     { 0.0, 0.0, 0.18, 1.00},
        .text =     { 1.0, 1.0, 1.0, 1.0},
        .shadow =   { 0.28, 0.34, 0.62, 0.93},
        .frame =    { 0.18, 0.18, 0.18, 1.0},
        .light =    { 0.18, 0.18, 0.28, 1.0}
    };
}

// draw the window
static void draw_window(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    X11_UI* ui = (X11_UI*)w->parent_struct;
    set_pattern(w,&w->app->color_scheme->selected,&w->app->color_scheme->normal,BACKGROUND_);
    cairo_paint (w->crb);
    set_pattern(w,&w->app->color_scheme->normal,&w->app->color_scheme->selected,BACKGROUND_);
    cairo_rectangle (w->crb,4,4,w->width-8,w->height-8);
    cairo_set_line_width(w->crb,4);
    cairo_stroke(w->crb);

    cairo_set_source_surface (w->crb, ui->screw,5,5);
    cairo_paint (w->crb);
    cairo_set_source_surface (w->crb, ui->screw,5,w->height-37);
    cairo_paint (w->crb);
    cairo_set_source_surface (w->crb, ui->screw,w->width-37,w->height-37);
    cairo_paint (w->crb);
    cairo_set_source_surface (w->crb, ui->screw,w->width-37,5);
    cairo_paint (w->crb);
    cairo_new_path (w->crb);

    cairo_text_extents_t extents;
    use_text_color_scheme(w, get_color_state(w));
    cairo_set_source_rgb (w->crb,0.45, 0.45, 0.45);
    float font_size = min(20.0,((w->height/2.2 < (w->width*0.5)/3) ? w->height/2.2 : (w->width*0.5)/3));
    cairo_set_font_size (w->crb, font_size);
    cairo_text_extents(w->crb,w->label , &extents);
    double tw = extents.width/2.0;

    widget_set_scale(w);
    cairo_move_to (w->crb, 390-tw, 210 );
    cairo_show_text(w->crb, w->label);
    cairo_new_path (w->crb);
    cairo_scale (w->crb, 0.95, 0.95);
    cairo_set_source_surface (w->crb, w->image,680,10);
    cairo_paint (w->crb);
    cairo_scale (w->crb, 1.05, 1.05);
    widget_reset_scale(w);
}

// if controller value changed send notify to host
static void value_changed(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    X11_UI* ui = (X11_UI*)w->parent_struct;
    if (ui->block_event != w->data) 
        ui->write_function(ui->controller,w->data,sizeof(float),0,&w->adj->value);
    ui->block_event = -1;
}

// shortcut to create knobs with portindex binding
Widget_t* add_my_slider(Widget_t *w, PortIndex index, const char * label,
                                X11_UI* ui, int x, int y, int width, int height) {
    w = add_vslider(ui->win, label, x, y, width, height);
    w->parent_struct = ui;
    w->data = index;
    w->func.value_changed_callback = value_changed;
    return w;
}

// init the xwindow and return the LV2UI handle
static LV2UI_Handle instantiate(const struct _LV2UI_Descriptor * descriptor,
            const char * plugin_uri, const char * bundle_path,
            LV2UI_Write_Function write_function,
            LV2UI_Controller controller, LV2UI_Widget * widget,
            const LV2_Feature * const * features) {

    X11_UI* ui = (X11_UI*)malloc(sizeof(X11_UI));

    if (!ui) {
        fprintf(stderr,"ERROR: failed to instantiate plugin with URI %s\n", plugin_uri);
        return NULL;
    }

    ui->parentXwindow = 0;
    LV2UI_Resize* resize = NULL;
    ui->block_event = -1;
    ui->db_zero = 20.*log10(0.0000003); // -130db

    int i = 0;
    for (; features[i]; ++i) {
        if (!strcmp(features[i]->URI, LV2_UI__parent)) {
            ui->parentXwindow = features[i]->data;
        } else if (!strcmp(features[i]->URI, LV2_UI__resize)) {
            resize = (LV2UI_Resize*)features[i]->data;
        }
    }

    if (ui->parentXwindow == NULL)  {
        fprintf(stderr, "ERROR: Failed to open parentXwindow for %s\n", plugin_uri);
        free(ui);
        return NULL;
    }
    // init Xputty
    main_init(&ui->main);
    set_my_theme(&ui->main);
    // create the toplevel Window on the parentXwindow provided by the host
    ui->win = create_window(&ui->main, (Window)ui->parentXwindow, 0, 0, 780, 220);
    ui->win->parent_struct = ui;
    ui->win->label = "GxGraphicEQ";
    widget_get_png(ui->win, LDVAR(guitarix_png));
    ui->screw = surface_get_png(ui->win, ui->screw, LDVAR(screw_png));
    // connect the expose func
    ui->win->func.expose_callback = draw_window;

    int iw=0;
    int w_pos = 60;
    int port = (PortIndex) V1;
    for (;iw<CONTROLS;iw++) {
        ui->meter_widget[iw] = add_vmeter(ui->win, "Meter", false, w_pos, 40, 20, 140);
        ui->meter_widget[iw]->parent_struct = ui;
        ui->meter_widget[iw]->data = port;
        port +=1;
        w_pos +=20;
    }


    iw=0;
    w_pos = 300;
    port = (PortIndex) G1;
    const char* frequencys[] = {">31", "62", "125", "250", "500", "1k", "2k", "4k", "8k", "16k", "<"};
    for (;iw<CONTROLS;iw++) {
        ui->widget[iw] = add_my_slider(ui->widget[iw], (PortIndex)port,frequencys[iw], ui,w_pos, 40, 40, 160);
        set_adjustment(ui->widget[iw]->adj,0.0, 0.0, -30.0, 20.0, 0.1, CL_CONTINUOS);
        //adj_set_scale(ui->widget[iw]->adj, 2.0);
        port +=1;
        w_pos +=40;
    }

    // map all widgets into the toplevel Widget_t
    widget_show_all(ui->win);
    // set the widget pointer to the X11 Window from the toplevel Widget_t
    *widget = (void*)ui->win->widget;
    // request to resize the parentXwindow to the size of the toplevel Widget_t
    if (resize){
        ui->resize = resize;
        resize->ui_resize(resize->handle, 780, 220);
    }
    // store pointer to the host controller
    ui->controller = controller;
    // store pointer to the host write function
    ui->write_function = write_function;
    
    return (LV2UI_Handle)ui;
}

// map power to db for meter widgets
static void set_meter_value(X11_UI* ui, Widget_t*w, float value) {
    float new_val = power2db(w,20.*log10(max(ui->db_zero,value)));
    check_value_changed(w->adj,&new_val);
}

// cleanup after usage
static void cleanup(LV2UI_Handle handle) {
    X11_UI* ui = (X11_UI*)handle;
    cairo_surface_destroy(ui->screw);
    // Xputty free all memory used
    main_quit(&ui->main);
    free(ui);
}

/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                        LV2 interface
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

// port value change message from host
static void port_event(LV2UI_Handle handle, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void * buffer) {
    X11_UI* ui = (X11_UI*)handle;
    float value = *(float*)buffer;
    int i=0;
    for (;i<CONTROLS;i++) {
        if (port_index == (uint32_t)ui->widget[i]->data) {
            // prevent event loop between host and plugin
            ui->block_event = (int)port_index;
            // Xputty check if the new value differs from the old one
            // and set new one, when needed
            check_value_changed(ui->widget[i]->adj, &value);
        }
    }
    if (port_index == V1) set_meter_value(ui,ui->meter_widget[0],value);
    else if (port_index == V2) set_meter_value(ui,ui->meter_widget[1],value);
    else if (port_index == V3) set_meter_value(ui,ui->meter_widget[2],value);
    else if (port_index == V4) set_meter_value(ui,ui->meter_widget[3],value);
    else if (port_index == V5) set_meter_value(ui,ui->meter_widget[4],value);
    else if (port_index == V6) set_meter_value(ui,ui->meter_widget[5],value);
    else if (port_index == V7) set_meter_value(ui,ui->meter_widget[6],value);
    else if (port_index == V8) set_meter_value(ui,ui->meter_widget[7],value);
    else if (port_index == V9) set_meter_value(ui,ui->meter_widget[8],value);
    else if (port_index == V10) set_meter_value(ui,ui->meter_widget[9],value);
    else if (port_index == V11) set_meter_value(ui,ui->meter_widget[10],value);
}

// LV2 idle interface to host
static int ui_idle(LV2UI_Handle handle) {
    X11_UI* ui = (X11_UI*)handle;
    // Xputty event loop setup to run one cycle when called
    run_embedded(&ui->main);
    return 0;
}

// LV2 resize interface to host
static int ui_resize(LV2UI_Feature_Handle handle, int w, int h) {
    X11_UI* ui = (X11_UI*)handle;
    // Xputty sends configure event to the toplevel widget to resize itself
    if (ui) send_configure_event(ui->win,0, 0, w, h);
    return 0;
}

// connect idle and resize functions to host
static const void* extension_data(const char* uri) {
    static const LV2UI_Idle_Interface idle = { ui_idle };
    static const LV2UI_Resize resize = { 0 ,ui_resize };
    if (!strcmp(uri, LV2_UI__idleInterface)) {
        return &idle;
    }
    if (!strcmp(uri, LV2_UI__resize)) {
        return &resize;
    }
    return NULL;
}

static const LV2UI_Descriptor descriptor = {
    GXPLUGIN_UI_URI,
    instantiate,
    cleanup,
    port_event,
    extension_data
};



extern "C"
LV2_SYMBOL_EXPORT
const LV2UI_Descriptor* lv2ui_descriptor(uint32_t index) {
    switch (index) {
        case 0:
            return &descriptor;
        default:
        return NULL;
    }
}


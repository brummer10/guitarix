/*
 *                           0BSD 
 * 
 *                    BSD Zero Clause License
 * 
 *  Copyright (c) 2019 Hermann Meyer
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.

 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 */

#pragma once

#ifndef XWIDGET_H
#define XWIDGET_H

#include "xputty.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------
-----------------------------------------------------------------------	
					basic X11 widgets
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

#define SYSTEM_TRAY_REQUEST_DOCK   0
#define SYSTEM_TRAY_BEGIN_MESSAGE   1
#define SYSTEM_TRAY_CANCEL_MESSAGE  2

/**
 * @brief *vfunc      - function pointer to connect Xevents from the main loop to Widget_t
 * @param *widget     - void pointer to the Widget_t
 * @param *main       - pointer to Xputty main struct running the loop
 * @param *event      - void pointer to the XEvent
 * @param *user_data  - void pointer to attached user_data, maybe NULL
 * @return void
 */

typedef void (*vfunc)(void * widget, void * event, Xputty *main, void* user_data);

/**
 * @brief *evfunc     - function pointer to connect Xevents from a Widget_t to a event handler
 * @param *widget     - void pointer to the Widget_t
 * @param *event      - void pointer to the XEvent
 * @param *user_data  - void pointer to attached user_data, maybe NULL
 * @return void
 */

typedef void (*evfunc)(void * widget, void * event, void* user_data);


/**
 * @brief *xevfunc     - function pointer to connect XEvents from a Widget_t to a event handler
 * @param *widget      - void pointer to the widget
 * @param *user_data   - void pointer to attached user_data, maybe NULL
 * @return void
 */

typedef void (*xevfunc)(void * widget, void* user_data);

/**
 * 
 * @brief Func_t     - struct to hold all supported event callbacks
 * 
 */

typedef struct {
    xevfunc expose_callback;
    xevfunc configure_callback;
    xevfunc enter_callback;
    xevfunc leave_callback;
    xevfunc adj_callback;
    xevfunc value_changed_callback;
    xevfunc user_callback;
    xevfunc mem_free_callback;
    xevfunc configure_notify_callback;
    xevfunc map_notify_callback;
    xevfunc unmap_notify_callback;
    xevfunc dialog_callback;

    evfunc button_press_callback;
    evfunc button_release_callback;
    evfunc motion_callback;
    evfunc key_press_callback;
    evfunc key_release_callback;
} Func_t;

/**
 * 
 * @brief EventType         - enum to hold identifier for all supported event callbacks
 * \n Events could be connected to a handler by using this identifier
 * @param EXPOSE            - (*xevfunc) expose_callback(void * widget, void* user_data)
 * @param CONFIGURE         - (*xevfunc) configure_callback(void * widget, void* user_data)
 * @param ENTER             - (*xevfunc) enter_callback(void * widget, void* user_data)
 * @param LEAVE             - (*xevfunc) leave_callback(void * widget, void* user_data)
 * @param ADJ_INTERN        - (*xevfunc) adj_callback(void * widget, void* user_data)
 * @param VALUE_CHANGED     - (*xevfunc) value_changed_callback(void * widget, void* user_data)
 * @param USER              - (*xevfunc) user_callback(void * widget, void* user_data)
 * @param MEM_FREE_CB       - (*xevfunc) mem_free_callback(void * widget, void* user_data)
 * @param CONFIGURE_NOTIFY  - (*xevfunc) configure_notify_callback(void * widget, void* user_data)
 * @param MAP_NOTIFY        - (*xevfunc) map_notify_callback(void * widget, void* user_data)
 * @param UNMAP_NOTIFY      - (*xevfunc) unmap_notify_callback(void * widget, void* user_data)
 * @param DIALOG_RESPONS    - (*xevfunc) dialog_callback(void * widget, void* user_data)
 * @param BUTTON_PRESS      - (*evfunc) button_press_callback(void * widget, void * event, void* user_data)
 * @param BUTTON_RELEASE    - (*evfunc) button_release_callback(void * widget, void * event, void* user_data)
 * @param POINTER_MOTION    - (*evfunc) motion_callback(void * widget, void * event, void* user_data)
 * @param KEY_PRESS         - (*evfunc) key_press_callback(void * widget, void * event, void* user_data)
 * @param KEY_RELEASE       - (*evfunc) key_release_callback(void * widget, void * event, void* user_data)
 */

typedef enum {
    EXPOSE = 1,
    CONFIGURE,
    ENTER,
    LEAVE,
    ADJ_INTERN,
    VALUE_CHANGED,
    USER,
    MEM_FREE_CB,
    CONFIGURE_NOTIFY,
    MAP_NOTIFY,
    UNMAP_NOTIFY,
    DIALOG_RESPONSE,
    BUTTON_PRESS,
    BUTTON_RELEASE,
    POINTER_MOTION,
    KEY_PRESS,
    KEY_RELEASE,
} EventType;

/**
 * 
 * @brief Gravity              - enum to indicate how to resize a widget
 * @param NORTHWEST            - Widget_t adjust nord/west
 * @param NORTHEAST            - Widget_t adjust nord/east
 * @param SOUTHWEST            - Widget_t adjust south/west
 * @param SOUTHEAST            - Widget_t adjust south/east
 * @param CENTER               - Widget_t adjust centered
 * @param ASPECT               - Widget_t adjust in a aspect frame
 * @param NONE                 - Widget_t request no adjustment in frame
 */

typedef enum {
/** Widget_t adjust nord/west */
    NORTHWEST    ,
/** Widget_t adjust nord/east */
    NORTHEAST    ,
/** Widget_t adjust south/west */
    SOUTHWEST     ,
/** Widget_t adjust south/east */
    SOUTHEAST     ,
/** Widget_t adjust centered */
    CENTER        ,
/** Widget_t adjust in a aspect frame */
    ASPECT        ,
/** Widget_t has fixed size */
    FIXEDSIZE        ,
/** Widget_t adjust in a aspect frame */
    MENUITEM      ,
/** Widget_t request no adjustment in frame */
    NONE          ,   
}Gravity;

/**
 * 
 * @brief Resize_t             - struct used to resize child widgets
 * @param init_x               - initial x position on Parent
 * @param init_y               - initial y position on Parent
 * @param init_width           - initial width
 * @param init_height          - initial height
 * @param scale_x              - scalling size of the x axsis
 * @param scale_y              - scalling size of the y axsis
 * @param cscale_x             - scalling factor of the x axsis
 * @param cscale_y             - scalling factor of the y axsis
 * @param ascale               - scalling factor for aspect scalling
 */

typedef struct {
/** indicate how the widget wish to be resized */
    Gravity gravity;
/** initial x position on Parent */
    int init_x;
/** initial y position on Parent */
    int init_y;
/** initial width */
    int init_width;
/** initial height */
    int init_height;
/** scalling size of the x axsis */
    float scale_x;
/** scalling size of the y axsis */
    float scale_y;
/** scalling factor of the x axsis */
    float cscale_x;
/** scalling factor of the y axsis */
    float cscale_y;
/** rescalling factor of the x axsis */
    float rcscale_x;
/** rescalling factor of the y axsis */
    float rcscale_y;
/** scalling factor for aspect scalling */
    float ascale;
} Resize_t;

/**
 * 
 * @brief anonymous enum       - flags to set Widget_t properties
 * @param IS_WIDGET            - Widget_t is a sub widget
 * @param IS_WINDOW            - Widget_t has no Widget_t parent 
 * @param IS_POPUP             - Widget_t is a pop up widget
 * @param IS_RADIO             - Widget_t is part of a radio group
 * @param USE_TRANSPARENCY     - Widget_t need transparent draw (buffer)
 * @param HAS_FOCUS            - Mouse pointer is above Widget_t
 * @param HAS_POINTER          - Mouse pointer is pressed on Widget_t
 * @param HAS_TOOLTIP          - Widget_t have tooltip
 * @param HAS_MEM              - Widget_t have mem to be released
 */

enum {
    /** Widget_t is a sub widget */
    IS_WIDGET         = 1<<0,
    /** Widget_t has no Widget_t parent */
    IS_WINDOW         = 1<<1,
    /** Widget_t is a pop up widget */
    IS_POPUP          = 1<<2,
    /** Widget_t is part of a radio group */
    IS_RADIO          = 1<<3,
    /** Widget_t is a tooltip widget */
    IS_TOOLTIP        = 1<<4,
    /** Widget_t need transparent draw (buffer) */
    USE_TRANSPARENCY  = 1<<5,
    /** Mouse pointer is above Widget_t */
    HAS_FOCUS         = 1<<6,
    /** Mouse pointer is pressed on Widget_t */
    HAS_POINTER       = 1<<7,
    /** Widget_t have tooltip */
    HAS_TOOLTIP       = 1<<8,
    /** Widget_t have mem to be released */
    HAS_MEM           = 1<<9,
    /** Widget_t didn't receive autorepeated keys */
    NO_AUTOREPEAT     = 1<<10,
    /** Widget_t need fast redrawing  */
    FAST_REDRAW       = 1<<11,
    /** Hide Widget_t instead delete on "WM_DELETE_WINDOW"  */
    HIDE_ON_DELETE    = 1<<12,
    /** Widget_t reuse a surface from a other Widget_t  */
    REUSE_IMAGE       = 1<<13,
};

/**
 * 
 * @brief Widget_t           - struct to hold the basic Widget_t info
 * @param *app               - pointer to the main struct
 * @param widget             - the X11 Window
 * @param *parent            - pointer to the Parent Window or Widget_t
 * @param event_callback     - the main XEvent callback
 * @param func               - struct holding the event callbacks
 * @param *surface           - pointer to the cairo xlib surface
 * @param *cr                - pointer to the cairo xlib surface context
 * @param *buffer            - pointer to the cairo buffer surface
 * @param *crb               - pointer to the cairo buffer surface context
 * @param *image             - pointer to the cairo image surface
 * @param data               - int to hold user data 
 * @param flags              - unsigned int to hold Widget_t flags 
 * @param *label             - pointer to the widget label
 * @param input_label        - char array the widget input label
 * @param state              - int to hold the widget state
 * @param pos_x              - mouse pointer x position on button press
 * @param pos_y              - mouse pointer y position on button press
 * @param x                  - x position of Window on Parent
 * @param y                  - y position of Window on Parent
 * @param width              - widget width
 * @param height             - widget height
 * @param scale              - struct used to resize child widgets
 * @param *adj_x             - pointer to the x axis adjustment
 * @param *adj_y             - pointer to the y axis adjustment
 * @param *adj               - pointer to the adjustment in use
 * @param *childlist         - pointer to Widget_t child list
 * @param xic                - Locale and UTF 8 support interface
 * @param xim                - Context to Locale and UTF 8 support
 */

struct Widget_t {
/** pointer to the main struct */
    Xputty *app;
/** the X11 newly created Window */
    Window widget;
/** pointer to the Parent Window or Widget_t */
    void *parent;
/** pointer to the Parent struct */
    void *parent_struct;
/** the main XEvent callback */
    vfunc event_callback;
/** struct holding the event callbacks */
    Func_t func;
/** pointer to the cairo xlib surface */
    cairo_surface_t *surface;
/** pointer to the cairo xlib surface context */
    cairo_t *cr;
/** pointer to the cairo buffer surface used for transparency */
    cairo_surface_t *buffer;
/** pointer to the cairo buffer surface context */
    cairo_t *crb;
/** pointer to the cairo image surface used to load a png */
    cairo_surface_t *image;
/** int to hold user data */
    int data;
/** int to hold Widget_t flags */
    long int flags;
/** pointer to the widget label */
    const char* label;
/** char array to hold user input */
    char input_label[32];
/** pointer to the x axis adjustment */
    Adjustment_t *adj_x;
/** pointer to the y axis adjustment */
    Adjustment_t *adj_y;
/** pointer to the adjustment in use*/
    Adjustment_t *adj;
/** pointer to Widget_t child list */
    Childlist_t *childlist;
/** Locale and UTF 8 support */
    XIC xic;
/** Context to Locale and UTF 8 support */
    XIM xim;
/** int to hold the widget state default = 0 */
    int state;
/** mouse pointer x position on button press */
    int pos_x;
/** mouse pointer y position on button press */
    int pos_y;
/** x position of Window related to the Parent */
    int x;
/** y position of Window related to the Parent */
    int y;
/** the widget size x-axis */
    int width;
/** the widget size y-axis */
    int height;
/** struct used to resize child widgets */
    Resize_t scale;
};


/**
 * @brief *create_window     - create a Window 
 * \n You need to create as least minimum one Window to get started.
 * \n The first created Window is the top_level_widget()
 * \n A Window could be created on the DefaultRootWindow() or embeded
 * into a other XWindow
 * @param *app               - pointer to the Xputty *main struct to use
 * @param win                - pointer to the Parent Window (may be Root)
 * @param x,y,width,height   - the position/geometry to create the window
 * @return Widget_t *        - pointer to the Widget_t struct
 */

Widget_t *create_window(Xputty *app, Window win,
                          int x, int y, int width, int height);

/**
 * @brief *create_widget      - create a widget
 * \n A Widget_t could only be created as child of a other Widget_t
 * \n To create a Widget_t you need to create a Widget_t with create_window()
 * before.
 * @param *app                - pointer to the Xputty *main struct to use
 * @param *parent             - pointer to the Parent Widget_t
 * @param x,y,width,height    - the position/geometry to create the widget
 * @return Widget_t*          - pointer to the Widget_t struct
 */

Widget_t *create_widget(Xputty *app, Widget_t *win,
                          int x, int y, int width, int height);

/**
 * @brief connect_func      - connect a event with a handler
 * without type check. For supported events see: Func_t
 * @param **event           - the event to connect
 * @param *handler          - the handler to handle the event
 * @return void
 */

void connect_func(void (**event)(), void (*handler)());

/**
 * @brief widget_set_title  - set window title for a Widget_t
 * @param *w                - pointer to the Widget_t to set the title
 * @param *title            - the title to store
 * @return void 
 */

void widget_set_title(Widget_t *w, const char *title);

/**
 * @brief widget_show       - map/show widget
 * @param *w                - pointer to the Widget_t to map
 * @return void 
 */

void widget_show(Widget_t *w);

/**
 * @brief pop_widget_show_all   - map/show popup widget with all it's childs
 * @param *w                    - pointer to the Widget_t to map
 * @return void 
 */

void pop_widget_show_all(Widget_t *w);

/**
 * @brief widget_hide       - unmap/hide a Widget_t
 * @param *w                - pointer to the Widget_t to unmap
 * @return void 
 */

void widget_hide(Widget_t *w);

/**
 * @brief widget_show_all   - map/show Widget_t with all childs
 * @param *w                - pointer to the Widget_t to map
 * @return void 
 */

void widget_show_all(Widget_t *w);

/**
 * @brief show_tooltip      - check if a Widget_t have a tooltip,
 * and show it, if a tooltip is available. 
 * @param *wid              - pointer to the Widget_t receiving the event
 * @return void
 */

void show_tooltip(Widget_t *wid);

/**
 * @brief hide_tooltip     - check if a Widget_t have a tooltip,
 * and hide it, if a tooltip is mapped. 
 * @param *wid              - pointer to the Widget_t receiving the event
 * @return void
 */

void hide_tooltip(Widget_t *wid);

/**
 * @brief *get_toplevel_widget - get pointer to the top level Widget_t
 * @param *main                - pointer to the main Xputty struct
 * @return void 
 */

Widget_t *get_toplevel_widget(Xputty *main);

/**
 * @brief quit              - exit the main loop
 * @param *w                - pointer to the Widget_t sending the request
 * @return void 
 */

void quit(Widget_t *w);

/**
 * @brief quit_widget       - remove a widget from the processing loop
 * @param *w                - pointer to the Widget_t sending the request
 * @return void 
 */

void quit_widget(Widget_t *w);

/**
 * @brief transparent_draw  - copy parent surface to child surface
 * \n you usaualy didn't need to call this, it's used automatically
 * when a Widget_t have set the flag USE_TRANSPARENCY
 * \n this is the default setting for Widget_t
 * @param *wid              - pointer to the Widget_t receiving the event
 * @param *user_data        - void pointer to attached user_data
 * @return void 
 */

void transparent_draw(void * wid, void* user_data);

/**
 * @brief widget_reset_scale - used to reset scaling mode after a image surface
 * is drawn to the Widget_t surface with widget_set_scale()
 * @param *w                 - pointer to the Widget_t sending the request
 * @return void 
 */

void widget_reset_scale(Widget_t *w);

/**
 * @brief widget_set_scale   - set scaling mode to scale a image surface
 * to the size of the Widget_t surface
 * @param *w                 - pointer to the Widget_t sending the request
 * @return void 
 */

void widget_set_scale(Widget_t *w);

/**
 * @brief destroy_widget    - destroy a widget 
 * \n When a Widget_t receive a destroy_widget() call, it will propagate that
 * to all childs in it's Childlist_t. So all childs get destroyed before the 
 * Widget_t itself close.
 * @param *w                - pointer to the Widget_t sending the request
 * @param *main             - pointer to main struct
 * @return void 
 */

void destroy_widget(Widget_t *w, Xputty *main);

/**
 * @brief widget_event_loop - the internal widget event loop
 * @param *w                - void pointer to the Widget_t receiving the event
 * @param *event            - void pointer to the XEvent
 * @param *main             - void pointer to the Xputty *main struct running 
 * the event loop
 * @param *user_data        - void pointer to attached user_data
 * @return void 
 */

void widget_event_loop(void *w_, void* event, Xputty *main, void* user_data);

/**
 * @brief send_configure_event - send a ConfigureNotify to Widget_t
 * \n used to resize a Widget_t
 * @param *w                   - pointer to the Widget_t to send the notify
 * @param x,y                  - the new Widget_t position
 * @param width,height         - the new Widget_t size
 * @return void 
 */

void send_configure_event(Widget_t *w,int x, int y, int width, int height);

/**
 * @brief send_button_press_event   - send ButtonPress event to Widget_t
 * \n simulate a BUTTON_PRESS Event
 * @param *w                        - pointer to the Widget_t to send the notify
 * @return void 
 */

void send_button_press_event(Widget_t *w);

/**
 * @brief send_button_release_event - send ButtonRelease event to Widget_t
 * \n simulate a BUTTON_RELEASE Event
 * @param *w                        - pointer to the Widget_t to send the notify
 * @return void 
 */

void send_button_release_event(Widget_t *w);

/**
 * @brief send_systray_message      - request a systray icon for Widget_t
 * \n currently not working
 * @param *w                        - pointer to the Widget_t to send the notify
 * @return void 
 */

void send_systray_message(Widget_t *w);

/**
 * @brief expose_widgets    - send a expose event (EXPOSE) to a Widget_t
 * @param w                 - the Widget_t to send the event to
 * @return void 
 */

void expose_widget(Widget_t *w);

/**
 * @brief _key_mapping      - modifier key's mapped to a integer value
 * @param *dpy              - pointer to the Display in use
 * @param *xkey             - the key to map
 * @return int              - value (1-10) or 0 when not mapped 
 */

int key_mapping(Display *dpy, XKeyEvent *xkey);

#ifdef __cplusplus
}
#endif

#endif //XWIDGET_H

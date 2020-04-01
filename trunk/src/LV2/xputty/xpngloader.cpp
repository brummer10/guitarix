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

#include "xpngloader.h"

/* 
 * @brief      load png data from binary blob into cairo surface
*/

cairo_status_t png_stream_reader (void *_stream, unsigned char *data, unsigned int length) {
    binary_stream * stream = (binary_stream *) _stream;
    memcpy(data, &stream->data[stream->position],length);
    stream->position += length;
    return CAIRO_STATUS_SUCCESS;
}

cairo_surface_t *cairo_image_surface_create_from_stream ( const unsigned char* name) {
    binary_stream png_stream;
    png_stream.data = name;
    png_stream.position = 0;
    return cairo_image_surface_create_from_png_stream(&png_stream_reader, (void *)&png_stream);
}

void widget_get_png(Widget_t *w, const unsigned char* name) {
    cairo_surface_t *getpng = cairo_image_surface_create_from_stream (name);
    int width = cairo_image_surface_get_width(getpng);
    int height = cairo_image_surface_get_height(getpng);
    cairo_surface_destroy(w->image);
    w->image = NULL;
    
    w->image = cairo_surface_create_similar (w->surface, 
                        CAIRO_CONTENT_COLOR_ALPHA, width, height);
    cairo_t *cri = cairo_create (w->image);
    cairo_set_source_surface (cri, getpng,0,0);
    cairo_paint (cri);
    cairo_surface_destroy(getpng);
    cairo_destroy(cri);
}

void widget_get_scaled_png(Widget_t *w, const unsigned char* name) {
    cairo_surface_t *getpng = cairo_image_surface_create_from_stream (name);
    int width = cairo_image_surface_get_width(getpng);
    int height = cairo_image_surface_get_height(getpng);
    int width_t = w->scale.init_width;
    int height_t = w->scale.init_height;
    double x = (double)width_t/(double)width;
    double y = (double)height_t/(double)height;
    cairo_surface_destroy(w->image);
    w->image = NULL;

    w->image = cairo_surface_create_similar (w->surface, 
                        CAIRO_CONTENT_COLOR_ALPHA, width_t, height_t);
    cairo_t *cri = cairo_create (w->image);
    cairo_scale(cri, x,y);    
    cairo_set_source_surface (cri, getpng,0,0);
    cairo_paint (cri);
    cairo_surface_destroy(getpng);
    cairo_destroy(cri);
}

void widget_get_surface_ptr(Widget_t *w, Widget_t *wid) {
    w->image = wid->image;
    w->flags |= REUSE_IMAGE;
}

cairo_surface_t * surface_get_png(Widget_t *w, cairo_surface_t *sf, const unsigned char* name) {
    cairo_surface_t *getpng = cairo_image_surface_create_from_stream (name);
    int width = cairo_image_surface_get_width(getpng);
    int height = cairo_image_surface_get_height(getpng);
    
    sf = cairo_surface_create_similar (w->surface, 
                        CAIRO_CONTENT_COLOR_ALPHA, width, height);
    cairo_t *cri = cairo_create (sf);
    cairo_set_source_surface (cri, getpng,0,0);
    cairo_paint (cri);
    cairo_surface_destroy(getpng);
    cairo_destroy(cri);
    return sf;
}

void widget_set_icon_from_surface(Widget_t *w, Pixmap *icon_, cairo_surface_t *image) {
    int width = cairo_xlib_surface_get_width(image);
    int height = cairo_xlib_surface_get_height(image);
    XWindowAttributes atr;
    XGetWindowAttributes (w->app->dpy, w->widget, &atr);
    Pixmap icon = XCreatePixmap(w->app->dpy, w->widget, width, height, atr.depth);
    cairo_surface_t *surface = cairo_xlib_surface_create (w->app->dpy, icon,  
                  DefaultVisual(w->app->dpy, DefaultScreen(w->app->dpy)), width, height);
    cairo_t *cri = cairo_create (surface);
    Colors *c = get_color_scheme(w->app, PRELIGHT_);
    cairo_set_source_rgba(cri, c->bg[0],  c->bg[1], c->bg[2],  c->bg[3]);
    cairo_paint(cri);
    cairo_set_source_surface (cri, image,0,0);
    cairo_paint(cri);
    cairo_surface_destroy(surface);
    cairo_destroy(cri);
    icon_ = &icon;
    
    XWMHints* win_hints = XAllocWMHints();
    assert(win_hints);
    win_hints->flags = IconPixmapHint;
    win_hints->icon_pixmap = icon;
    XSetWMHints(w->app->dpy, w->widget, win_hints);
    XFree(win_hints);
}

void widget_set_icon_from_png(Widget_t *w, Pixmap *icon_, const unsigned char* name) {
    cairo_surface_t *image = cairo_image_surface_create_from_stream (name);
    int width = cairo_image_surface_get_width(image);
    int height = cairo_image_surface_get_height(image);
    XWindowAttributes atr;
    XGetWindowAttributes (w->app->dpy, w->widget, &atr);
    Pixmap icon = XCreatePixmap(w->app->dpy, w->widget, width, height, atr.depth);
    cairo_surface_t *surface = cairo_xlib_surface_create (w->app->dpy, icon,  
                  DefaultVisual(w->app->dpy, DefaultScreen(w->app->dpy)), width, height);
    cairo_t *cri = cairo_create (surface);
    Colors *c = get_color_scheme(w->app, PRELIGHT_);
    cairo_set_source_rgba(cri, c->bg[0],  c->bg[1], c->bg[2],  c->bg[3]);
    cairo_paint(cri);
    cairo_set_source_surface (cri, image,0,0);
    cairo_paint(cri);
    cairo_surface_destroy(image);
    cairo_surface_destroy(surface);
    cairo_destroy(cri);
    icon_ = &icon;
    
    XWMHints* win_hints = XAllocWMHints();
    assert(win_hints);
    win_hints->flags = IconPixmapHint;
    win_hints->icon_pixmap = icon;
    XSetWMHints(w->app->dpy, w->widget, win_hints);
    XFree(win_hints);
}

/*
cairo_surface_t* iamge = cairo_image_surface_create_from_stream( LDVAR(image_name_png));
*/

/* vim:ts=4:sw=4:et:
 *
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

#ifdef _WIN32 //PlatformWrappers

#ifdef __cplusplus
extern "C" {
#endif

#include <windowsx.h>

#include "xwidget.h"
#include "xwidget_private.h"

TCHAR szMainUIClassName[]   = TEXT("xputtyMainUI____0123456789ABCDEF");
TCHAR szWidgetUIClassName[] = TEXT("xputtyWidgetUI__0123456789ABCDEF");

// forward declarations
void SetClientSize(HWND hwnd, int clientWidth, int clientHeight);
BOOL SetMouseTracking(HWND hwnd, BOOL enable);
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT onPaint( HWND hwnd, WPARAM wParam, LPARAM lParam );

/*---------------------------------------------------------------------
-----------------------------------------------------------------------
            common functions (required)
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

Window os_get_root_window(Widget_t *w) {
    return HWND_DESKTOP;
}

void os_translate_coords(Widget_t *w, Window from_window, Window to_window,
                          int from_x, int from_y, int *to_x, int *to_y) {
    POINT Point = {from_x, from_y};
    MapWindowPoints(from_window, to_window, &Point, 1);
    *to_x = Point.x;
    *to_y = Point.y;
}

void os_get_window_metrics(Widget_t *w_, Metrics_t *metrics) {
    RECT WindowRect;
    RECT ClientRect;
    POINT Point;
    Widget_t *parent = (Widget_t *)w_->parent;

    if (GetWindowRect(w_->widget, &WindowRect) \
     && GetClientRect(w_->widget, &ClientRect)) {
        Point.x = WindowRect.left; // WindowRect has correct coords, but wrong width/height
        Point.y = WindowRect.top;  // ClientRect has correct width/height, but top/left == 0
        ScreenToClient(parent->widget, &Point); // "parent" is intentional (coords are relative to owner widget)
        metrics->x = Point.x;
        metrics->y = Point.y;
        metrics->width = ClientRect.right - ClientRect.left;
        metrics->height = ClientRect.bottom - ClientRect.top;
    }
    metrics->visible = IsWindowVisible(w_->widget);
}

// values are checked on WM_SIZE
void os_set_window_min_size(Widget_t *w, int min_width, int min_height,
                            int base_width, int base_height) {
    w->metrics_min.width = min_width;
    w->metrics_min.height = min_height;
}

void os_move_window(Display *dpy, Widget_t *w, int x, int y) {
    SetWindowPos(w->widget, NULL, //hWnd, hWndInsertAfter
      x, y, 0, 0, SWP_NOSIZE|SWP_NOZORDER); //X, Y, width, height, uFlags
}

void os_create_main_window_and_surface(Widget_t *w, Xputty *app, Window win,
                          int x, int y, int width, int height) {
    // Event callbacks already start during CreateWindow(),
    // so prepare childlist before that call on MSWin
    // (on Linux, adding to childlist starts message events)
    childlist_add_child(app->childlist,w);
    // prepare window class
    WNDCLASS wndclass = {0};
    HINSTANCE hInstance = NULL;

    snprintf(szMainUIClassName+16, 16, "%p", WndProc);
    snprintf(szWidgetUIClassName+16, 16, "%p", WndProc);

    // create a permanent surface for drawing (see onPaint() event)
    w->surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);

    wndclass.lpfnWndProc   = WndProc;
    wndclass.hInstance     = hInstance;
    wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = NULL;
    wndclass.lpszClassName = szMainUIClassName;
    wndclass.cbWndExtra    = sizeof(w); // reserve space for SetWindowLongPtr
    RegisterClass(&wndclass);
    // TODO: pass window style (mainwindow,childwidget,popup,...) to create_window()
    // _WIN32 doesnt allow changing the style afterwards, as it is done in xmenu.cpp
    // (this also removes duplicate code for window/widget creation).
    // For the current situation it is sufficient to set popup style if parent is HWND_DESKTOP.
    DWORD dwStyle = 0;
    DWORD dwExStyle = 0;
    // dwExStyle:
    //   WS_EX_APPWINDOW - force(!) taskbar icon
    //   WS_EX_CONTROLPARENT - contains children, uses tab+cursor nav.
    //   WS_EX_NOPARENTNOTIFY - no PARENTNOTIFY on create/destroy
    //   WS_EX_TOOLWINDOW - no taskbar icon
    //   WS_EX_TOPMOST - above all others
    if (win == (HWND)-1) {
        // Dialogs with border
        dwStyle = WS_OVERLAPPEDWINDOW;
        dwExStyle = WS_EX_CONTROLPARENT;
        win = HWND_DESKTOP;
        // include border widths
        RECT Rect = {0};
        BOOL bMenu = false;
        Rect.right = width;
        Rect.bottom = height;
        if (AdjustWindowRectEx(&Rect, dwStyle, bMenu, dwExStyle)) {
            width = Rect.right - Rect.left;
            height = Rect.bottom - Rect.top;
        }
    } else
    if (win == HWND_DESKTOP) {
        // Floating without border (popup, tooltip)
        dwStyle = WS_POPUP;
        dwExStyle = WS_EX_CONTROLPARENT | WS_EX_TOOLWINDOW;
    } else {
        // Embedded widget
        dwStyle = WS_CHILD;
        dwExStyle = WS_EX_CONTROLPARENT | WS_EX_TOOLWINDOW;
    }
    // create the window
    w->widget = CreateWindowEx(dwExStyle, szMainUIClassName,
                            TEXT("Draw Surface"), // lpWindowName
                            dwStyle, // dwStyle
                            CW_USEDEFAULT, CW_USEDEFAULT, // X, Y
                            width, height, // nWidth, nHeight
                            win, // hWndParent (no embeddeding takes place yet)
                            NULL, hInstance, (LPVOID)w); // hMenu, hInstance, lpParam
    SetParent(w->widget, win); // embed into parentWindow
    SetMouseTracking(w->widget, true); // for receiving WM_MOUSELEAVE

    os_set_window_min_size(w, width/2, height/2, width, height);
}

void os_create_widget_window_and_surface(Widget_t *w, Xputty *app, Widget_t *parent,
                          int x, int y, int width, int height) {
    // Event callbacks already start during CreateWindow(),
    // so prepare childlist before that call on MSWin
    // (on Linux, adding to childlist starts message events)
    childlist_add_child(app->childlist,w);
    // prepare window class
    WNDCLASS wndclass = {0};
    HINSTANCE hInstance = NULL;

    // create a permanent surface for drawing (see onPaint() event)
    w->surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);

    wndclass.lpfnWndProc   = WndProc;
    wndclass.hInstance     = hInstance;
    wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = NULL;
    wndclass.lpszClassName = szWidgetUIClassName;
    wndclass.cbWndExtra    = sizeof(w); // reserve space for SetWindowLongPtr
    RegisterClass(&wndclass);
    // create the window
    DWORD dwExStyle = WS_EX_CONTROLPARENT;
    w->widget = CreateWindowEx(dwExStyle, szWidgetUIClassName,
                            TEXT("Draw Surface"), // lpWindowName
                            WS_CHILD, // dwStyle
                            x, y, // X, Y
                            width, height, // nWidth, nHeight
                            parent->widget, // hWndParent (no embeddeding takes place yet)
                            NULL, hInstance, (LPVOID)w); // hMenu, hInstance, lpParam

    SetParent(w->widget, parent->widget); // embed into parentWindow
    SetMouseTracking(w->widget, true); // for receiving WM_MOUSELEAVE
}

void os_widget_event_loop(void *w_, void* event, Xputty *main, void* user_data) {
    // nothing to do
}

void os_main_run(Xputty *main) {
    MSG msg;
    BOOL bRet;
    while( (bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
        if (bRet == -1) {
          return; // error
        } else {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}

void os_run_embedded(Xputty *main) {
    // messageloop already polled by plugin host
}

/*---------------------------------------------------------------------
----------------------------------------------------------------------- 
            private functions
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

/*------------- the event loop ---------------*/

void build_xkey_event(XKeyEvent *ev, UINT msg, WPARAM wParam, LPARAM lParam) {
    UINT uVirtKey = (UINT)wParam;
    UINT uScanCode = (UINT)(HIWORD(lParam) & 0x1FF);
    BYTE lpKeyState[256];
    if (GetKeyboardState(lpKeyState)) {
        //https://stackoverflow.com/questions/42667205/maximum-number-of-characters-output-from-win32-tounicode-toascii
        // required size for the return buffer isn't exactly clear, maybe 255, so 1K should be a safe guess
        WCHAR lpChar[1024];
        UINT uFlags = 0x04; // 1=menu is active, 4=dont change anything
        if (msg == WM_CHAR) {
            ev->vk = uVirtKey;
            ev->vk_is_final_char = 1;
        } else {
            ToUnicode(uVirtKey, uScanCode, lpKeyState, lpChar, 2, uFlags);
            ev->vk = lpChar[0];
            ev->vk_is_final_char = 0;
        }
    }
    // handle special characters (only in KEYUP/DOWN?)
    switch (uScanCode) {
        case 0x0029: ev->keycode = XK_dead_circumflex;  break;
        case 0x000e: ev->keycode = XK_BackSpace;        break;
        case 0x000f: ev->keycode = XK_Tab;              break;
        case 0x001c: ev->keycode = XK_Return;           break;
        case 0x0147: ev->keycode = XK_Home;             break;
        case 0x014b: ev->keycode = XK_Left;             break;
        case 0x0148: ev->keycode = XK_Up;               break;
        case 0x014d: ev->keycode = XK_Right;            break;
        case 0x0150: ev->keycode = XK_Down;             break;
        case 0x014f: ev->keycode = XK_End;              break;
        case 0x0152: ev->keycode = XK_Insert;           break;
        case 0x011c: ev->keycode = XK_KP_Enter;         break;
        case 0x0047: ev->keycode = XK_KP_Home;          break;
        case 0x004b: ev->keycode = XK_KP_Left;          break;
        case 0x0048: ev->keycode = XK_KP_Up;            break;
        case 0x004d: ev->keycode = XK_KP_Right;         break;
        case 0x0050: ev->keycode = XK_KP_Down;          break;
        case 0x004f: ev->keycode = XK_KP_End;           break;
        case 0x0052: ev->keycode = XK_KP_Insert;        break;
        case 0x004e: ev->keycode = XK_KP_Add;           break;
        case 0x004a: ev->keycode = XK_KP_Subtract;      break;
        default:
            if (ev->vk == 0xfc) //'ü'
                ev->keycode = XK_udiaeresis;
            else if (ev->vk == 0xdc) //'Ü'
                ev->keycode = XK_dead_diaeresis;
            else
                ev->keycode = ev->vk;
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    POINT pt;
    XButtonEvent xbutton;
    XMotionEvent xmotion;
    XKeyEvent xkey;
    void *user_data = NULL;

    // be aware: "wid" can be NULL during window creation (esp. if there is a debugger attached)
    Widget_t *wid = (Widget_t *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    Xputty *main = wid ? wid-> app : NULL;

    xbutton.window = hwnd;
    xbutton.x = GET_X_LPARAM(lParam);
    xbutton.y = GET_Y_LPARAM(lParam);
    xmotion.window = hwnd;
    xmotion.x = GET_X_LPARAM(lParam);
    xmotion.y = GET_Y_LPARAM(lParam);

    switch (msg) {
        case WM_CREATE:
            debug_print("WM:WM_CREATE:hwnd=%p:wid=%p",hwnd,wid);
            {
                CREATESTRUCT *pCreate = (CREATESTRUCT *)lParam;
                wid = (Widget_t *)pCreate->lpCreateParams;
                // CreateWindowEx() hasnt returned yet, so wid->widget is not set
                wid->widget = hwnd;
                // make "wid" available in messageloop events via GetWindowLongPtr()
                SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)wid);
            }
            return 0;

        // MSWin only: React to close requests
        case WM_CLOSE:
            // standalone
            if (hwnd == main->childlist->childs[0]->widget) {
                // is main window: end application
                PostQuitMessage(0); // end messageloop (continuing to main_quit())
            } else // is sub window (menu, dialog, ...): close
                DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            if (!wid) return DefWindowProc(hwnd, msg, wParam, lParam);
            return 0;

        // X11:ConfigureNotify
        case WM_SIZE:
            if (!wid) return DefWindowProc(hwnd, msg, wParam, lParam);
            else {
                // Limit window size:
                // The plugin doesnt receive WM_MINMAXINFO or WM_SIZING.
                // SWP_NOSIZE in WM_WINDOWPOSCHANGING cant handle width/height separately.
                // Setting the client size afterwards turned out to be the best working option so far.
                // Plugin: Limits the "zoom" (as the hosts window can always become smaller)
                // Standalone: Limits the window size
                int width = LOWORD(lParam);
                int height = HIWORD(lParam);
                if ((width < wid->metrics_min.width)
                    || (height < wid->metrics_min.height)) {
                    SetClientSize(hwnd, max(width, wid->metrics_min.width),
                            max(height, wid->metrics_min.height));
                    return 0;
                }
                // Resize handler
                if (!wid->func.configure_callback) return 0;
                wid->func.configure_callback(wid, user_data);
                RedrawWindow(wid->widget, NULL, NULL, RDW_NOERASE | RDW_INVALIDATE | RDW_UPDATENOW);
                return 0;
            }
        // X11:Expose
        case WM_PAINT:
            if (!wid) return DefWindowProc(hwnd, msg, wParam, lParam);
            if (!(wid->crb)) {
                debug_print("WM_PAINT:BAILOUT:wid->crb==NULL\n");
                return 0;
            }
            return onPaint(hwnd, wParam, lParam); // not possible on mswin: (only fetch the last expose event)

        // MSWin only: Allow keyboard input
        case WM_ACTIVATE:
            SetFocus(hwnd);
            return 0;
        case WM_MOUSEACTIVATE:
            SetFocus(hwnd);
            return MA_ACTIVATE;

        // X11:ButtonPress
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
            if (!wid) return DefWindowProc(hwnd, msg, wParam, lParam);
            SetCapture(hwnd); // also receive WM_MOUSEMOVE from outside this window
            if (msg == WM_LBUTTONDOWN)
                xbutton.button = Button1;
            else
                xbutton.button = Button3;
            if (wid->state == 4) break;
            if (wid->flags & HAS_TOOLTIP) hide_tooltip(wid);
            _button_press(wid, &xbutton, user_data);
            debug_print("Widget_t  ButtonPress %i\n", xbutton.button);
            return 0;
        case WM_MOUSEWHEEL:
            if (!wid) return DefWindowProc(hwnd, msg, wParam, lParam);
            // opposed to X11, WM_MOUSEWHEEL doesnt contain mouse coordinates
            {
                DWORD pos = GetMessagePos();
                pt.x = GET_X_LPARAM(pos);
                pt.y = GET_Y_LPARAM(pos);
                if (ScreenToClient(hwnd, &pt)) {
                    wid->pos_x = pt.x;
                    wid->pos_y = pt.y;
                }
            }
            if (GET_WHEEL_DELTA_WPARAM(wParam) <= 0) {
                xbutton.button = Button5;
                _button_press(wid, &xbutton, user_data);
            } else {
                xbutton.button = Button4;
                _button_press(wid, &xbutton, user_data);
            }
            return 0;
        // X11:ButtonRelease
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
            ReleaseCapture();
            if (msg == WM_LBUTTONUP)
                xbutton.button = Button1;
            else
                xbutton.button = Button3;
            _check_grab(wid, &xbutton, wid->app);
            if (wid->state == 4) break;
            _has_pointer(wid, &xbutton);
            if(wid->flags & HAS_POINTER) wid->state = 1;
            else wid->state = 0;
            _check_enum(wid, &xbutton);
            wid->func.button_release_callback((void*)wid, &xbutton, user_data);
            debug_print("Widget_t  ButtonRelease %i\n", xbutton.button);
            return 0;

        // X11:KeyPress and X11:KeyRelease
        // The resulting character (e.g. from dead-key combinations) cannot be
        // determined from WM_KEYUP or WM_KEYDOWN: WM_CHAR has to be used instead.
        // To workaround that, WM_CHAR fires key_press- and key_release_event()
        // after another, with the flag "->vk_is_final_char" set, so the client
        // code can differentiate between real KEYUP/DOWN and fake CHAR events.
        case WM_CHAR:
        case WM_KEYDOWN:
        case WM_KEYUP:
            build_xkey_event(&xkey, msg, wParam, lParam);
            // X11:KeyPress
            if (msg != WM_KEYUP) { // WM_KEYDOWN and WM_CHAR: key_press_callback()
                if (!wid) return DefWindowProc(hwnd, msg, wParam, lParam);
                if (wid->state == 4) return 0;
                // on Linux, retrigger check happens in KeyRelease (WM_KEYUP)
                unsigned short is_retriggered = 0;
                if(wid->flags & NO_AUTOREPEAT) {
                    if ((HIWORD(lParam) & KF_REPEAT) == KF_REPEAT)
                        is_retriggered = 1;
                }
                if (!is_retriggered) {
                    _check_keymap(wid, xkey);
                    wid->func.key_press_callback((void *)wid, &xkey, user_data);
                    debug_print("Widget_t KeyPress %x\n", xkey.keycode);
                }
            }
            //X11:KeyRelease
            if (msg != WM_KEYDOWN) { // WM_KEYUP and WM_CHAR: key_release_callback()
                if (wid->state == 4) return 0;
                // On MSWin, the REPEAT flag is always set for WM_KEYUP,
                // so the retrigger check has to take place in WM_KEYDOWN instead
                wid->func.key_release_callback((void *)wid, &xkey, user_data);
                debug_print("Widget_t KeyRelease %x\n", xkey.keycode);
            }
            return 0;

        // X11:LeaveNotify (X11:EnterNotify: see WM_MOUSEMOVE)
        case WM_MOUSELEAVE:
            if (!wid) return DefWindowProc(hwnd, msg, wParam, lParam);
            // xputty -> xwidget: handled by "ButtonPress" event on Linux
            // for emulating X11:EnterNotify
            wid->mouse_inside = false;

            wid->flags &= ~HAS_FOCUS;
            if (wid->state == 4) break;
            //if(!(xev->xcrossing.state & Button1Mask)) {
            if (!(wParam & MK_LBUTTON)) {
                wid->state = 0;
                wid->func.leave_callback((void*)wid, user_data);
                if (!(wid->flags & IS_WINDOW))
                    RedrawWindow(hwnd, NULL, NULL, RDW_NOERASE | RDW_INVALIDATE | RDW_UPDATENOW);
            }
            if (wid->flags & HAS_TOOLTIP) hide_tooltip(wid);
            debug_print("Widget_t LeaveNotify:hwnd=%p",hwnd);

            return 0;

        // X11:MotionNotify
        case WM_MOUSEMOVE:
            if (!wid) return DefWindowProc(hwnd, msg, wParam, lParam);
            if (!wid->mouse_inside) {
                // emulate X11:EnterNotify
                wid->mouse_inside = true;

                wid->flags |= HAS_FOCUS;
                if (wid->state == 4) break;
                //if(!(xev->xcrossing.state & Button1Mask)) {
                if (!(wParam & MK_LBUTTON)) {
                    wid->state = 1;
                    wid->func.enter_callback((void*)wid, user_data);
                    if (!(wid->flags & IS_WINDOW))
                        RedrawWindow(hwnd, NULL, NULL, RDW_NOERASE | RDW_INVALIDATE | RDW_UPDATENOW);
                    if (wid->flags & HAS_TOOLTIP) show_tooltip(wid);
                    else _hide_all_tooltips(wid);
                }
                debug_print("Widget_t EnterNotify:hwnd=%p",hwnd);

                SetMouseTracking(hwnd, true); // for receiving (next) WM_MOUSELEAVE
            }
            // hovering, etc.
            if (wid->state == 4) return 0;
            if (wParam & MK_LBUTTON) // TODO: why is this if() required here, but not on linux?
                adj_set_motion_state(wid, xmotion.x, xmotion.y);
            wid->func.motion_callback((void*)wid, &xmotion, user_data);
            debug_print("Widget_t MotionNotify x = %li Y = %li hwnd=%p\n",pt.x,pt.y,hwnd );
            return 0;

        // X11:ClientMessage: not implemented (could be done with WM_USER / RegisterWindowMessage())
        case WM_USER + 01: // WM_DELETE_WINDOW
            // xwidget -> xputty (main_run())
            if (wid) {
                if (hwnd == main->childlist->childs[0]->widget) { // main window (this is not invoked for any other window?)
                    main->run = false;
                    destroy_widget(wid, main);
                } else {
                    int i = childlist_find_widget(main->childlist, (Window)wParam);
                    if(i<1) return 0;
                    Widget_t *w = main->childlist->childs[i];
                    if(w->flags & HIDE_ON_DELETE) widget_hide(w);
                    else { destroy_widget(main->childlist->childs[i],main);
                    }
                }
            }
            return 1;
        // X11:ClientMessage:WIDGET_DESTROY
        case WM_USER + 02: // WIDGET_DESTROY
            //os_widget_event_loop()
            if (wid) {
                int ch = childlist_has_child(wid->childlist);
                if (ch) {
                    int i = ch;
                    for(;i>0;i--) {
                        quit_widget(wid->childlist->childs[i-1]);
                    }
                    quit_widget(wid);
                } else {
                    destroy_widget(wid,wid->app);
                }
                return 0;
            }
            return 2;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

LRESULT onPaint( HWND hwnd, WPARAM wParam, LPARAM lParam ) {
    PAINTSTRUCT ps ;
    Widget_t *w = (Widget_t *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

    // The cairo_win32_surface should only exist between BeginPaint()/EndPaint(),
    // otherwise it becomes unusable once the HDC of the owner window changes
    // (what can happen anytime, e.g. on resize).
    // Therefore, w->surface is created as a simple cairo_image_surface,
    // that can exist throughout the plugins lifetime (exception: see resize_event())
    // and is copied to a win32_surface in the onPaint() event (see WM_PAINT).

    // draw onto the image surface first
    transparent_draw(w, NULL);

    // prepare to update window
    HDC hdc = BeginPaint(hwnd, &ps );

    // create the cairo surface and context
    cairo_surface_t *surface = cairo_win32_surface_create (hdc);
    cairo_t *cr = cairo_create (surface);
    // copy contents of the (permanent) image_surface to the win32_surface
    cairo_set_source_surface(cr, w->surface, 0.0, 0.0);
    cairo_paint(cr);

    // cleanup
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    EndPaint( hwnd, &ps );
    return 0 ;
}

/*---------------------------------------------------------------------
---------------------------------------------------------------------*/ 

void SetClientSize(HWND hwnd, int clientWidth, int clientHeight) {
    if (IsWindow(hwnd)) {
        DWORD dwStyle = GetWindowLongPtr(hwnd, GWL_STYLE) ;
        DWORD dwExStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE) ;
        HMENU menu = GetMenu(hwnd) ;
        RECT rc = {0, 0, clientWidth, clientHeight} ;
        AdjustWindowRectEx(&rc, dwStyle, menu ? TRUE : FALSE, dwExStyle);
        SetWindowPos(hwnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
                SWP_NOZORDER | SWP_NOMOVE) ;
    }
}

// WM_MOUSELEAVE is only reported ONCE after calling TrackMouseEvent(TME_LEAVE)
BOOL SetMouseTracking(HWND hwnd, BOOL enable) {
    TRACKMOUSEEVENT tme;

    tme.cbSize = sizeof(tme);
    tme.dwFlags = TME_LEAVE;
    if (!enable)
        tme.dwFlags |= TME_CANCEL;
    tme.hwndTrack = hwnd;
    tme.dwHoverTime = HOVER_DEFAULT;
    return TrackMouseEvent(&tme);
}

/*---------------------------------------------------------------------
---------------------------------------------------------------------*/ 


#ifdef __cplusplus
}
#endif

#endif /* _WIN32 */

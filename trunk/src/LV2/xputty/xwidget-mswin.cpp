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

#if 0
void gx_gui_create_window_and_surface(gx_CreamMachineUI *ui) {
    // prepare window class
    static TCHAR szClassName[] = TEXT("gx_CreamMachineUIClass");
    WNDCLASS wndclass = {0};
    HINSTANCE hInstance = NULL;

    wndclass.style         = CS_HREDRAW | CS_VREDRAW; // clear on resize
    wndclass.lpfnWndProc   = WndProc;
    wndclass.hInstance     = hInstance;
    wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground =(HBRUSH)COLOR_WINDOW;
    wndclass.lpszClassName = szClassName;
    wndclass.cbWndExtra    = sizeof(ui); // reserve space for SetWindowLongPtr
    RegisterClass(&wndclass);
    // create the window
    ui->win = CreateWindowEx(WS_EX_TOPMOST, // dwExStyle
                            szClassName, // lpClassName
                            TEXT("Draw Surface"), // lpWindowName
                            (WS_CHILD | WS_VISIBLE), // dwStyle
                            CW_USEDEFAULT, CW_USEDEFAULT, // X, Y
                            ui->width, ui->height, // nWidth, nHeight
                            (HWND)ui->parentWindow, // hWndParent (no embeddeding takes place yet)
                            NULL, hInstance, NULL); // hMenu, hInstance, lpParam
                                                    //
    // attach a pointer to "ui" to this window (so ui is available in WndProc)
    SetWindowLongPtr(ui->win, GWLP_USERDATA, (LONG_PTR)ui);
    SetParent(ui->win, (HWND)ui->parentWindow); // embed into parentWindow
    ShowWindow(ui->win, SW_SHOW);
    SetClientSize(ui->win, ui->width, ui->height);
    SetMouseTracking(ui->win, true); // for receiving WM_MOUSELEAVE

    // create a permanent surface for drawing (see onPaint() event)
    ui->surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, ui->width, ui->height); 
}
#endif

/*---------------------------------------------------------------------
----------------------------------------------------------------------- 
            private functions
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

/*------------- the event loop ---------------*/

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
#if 0
    static double start_value = 0.0;
    static bool blocked = false;
    POINT pt;

    // be aware: "wid" can be NULL during window creation (esp. if there is a debugger attached)
    Widget_t *wid = (Widget_t *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

    switch (msg) {
        // MSWin only: React to close requests
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        // X11:ConfigureNotify
        case WM_SIZE:
            if (!wid) return DefWindowProc(hwnd, msg, wParam, lParam);
            resize_event(wid); // configure event, we only check for resize events here
            return 0;
        // X11:Expose
        case WM_PAINT:
            if (!wid) return DefWindowProc(hwnd, msg, wParam, lParam);
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
            if (!wid) return DefWindowProc(hwnd, msg, wParam, lParam);
            return 0;
        case WM_MOUSEWHEEL:
            if (!wid) return DefWindowProc(hwnd, msg, wParam, lParam);
            // opposed to X11, WM_MOUSEWHEEL doesnt contain mouse coordinates
            //if (GetCursorPos(&pt) && ScreenToClient(hwnd, &pt)) {
            //  wid->pos_x = pt.x;
            //  wid->pos_y = pt.y;
            //}
            //if (GET_WHEEL_DELTA_WPARAM(wParam) <= 0)
            //  scroll_event(wid, -1); // mouse wheel scroll down
            //else
            //  scroll_event(wid, 1); // mouse wheel scroll up
            return 0;
        // X11:ButtonRelease
        case WM_LBUTTONUP:
            return 0;

        // X11:KeyPress
        case WM_KEYUP:
            if (!wid) return DefWindowProc(hwnd, msg, wParam, lParam);
            return DefWindowProc(hwnd, msg, wParam, lParam);

        // X11:LeaveNotify (X11:EnterNotify: see WM_MOUSEMOVE)
        case WM_MOUSELEAVE:
            if (!wid) return DefWindowProc(hwnd, msg, wParam, lParam);
            //wid->mouse_inside = false;
            return 0;

        // X11:MotionNotify
        case WM_MOUSEMOVE:
            if (!wid) return DefWindowProc(hwnd, msg, wParam, lParam);
            //if (!wid->mouse_inside) {
            //  // emulate X11:EnterNotify
            //  wid->mouse_inside = true;
            //  if (!blocked) get_last_active_controller(wid, true);
            //  SetMouseTracking(wid->win, true); // for receiving (next) WM_MOUSELEAVE
            //}
            // mouse move while button1 is pressed
            //if (wParam & MK_LBUTTON) {
            //  motion_event(wid, start_value, GET_Y_LPARAM(lParam));
            //}
            return 0;

        // X11:ClientMessage: not implemented (could be done with WM_USER / RegisterWindowMessage())

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
#endif
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

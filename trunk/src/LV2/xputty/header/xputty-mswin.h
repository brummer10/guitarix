/* vim:ts=4:sw=4:et:
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

/**
 * compatibility definitions
 */

#ifdef _WIN32 //XCompatibility

#pragma once

#ifndef XPUTTY_MSWIN_H_
#define XPUTTY_MSWIN_H_

#include <windows.h>
#include <cairo-win32.h>

#ifdef __cplusplus
extern "C" {
#endif

// typedefs for mimicking Xlib structs & definitions

typedef unsigned long int XID;
typedef unsigned long int Atom;
typedef XID Display;
typedef HWND Window;
typedef XID Pixmap;
typedef XID KeySym;
typedef void *XIC;
typedef void *XIM;

typedef struct {
  Window window;
  int x;
  int y;
  int button;
  int keycode;
  unsigned int state;   /* key or button mask */
  bool vk_is_final_char; // (from WM_CHAR) readily composed character (after processing dead keys and other input methods)
  WORD vk;
} XEvent;
typedef XEvent XButtonEvent;
typedef XEvent XKeyEvent;
typedef XEvent XMotionEvent;

#define True 1
#define False 0

#define Button1 1
#define Button2 2
#define Button3 3
#define Button4 4
#define Button5 5

#define ShiftMask       (1<<0)
#define Button1Mask     (1<<8)

// xmidi_keyboard.cpp
#define XK_0    '0'
#define XK_2    '2'
#define XK_3    '3'
#define XK_5    '5'
#define XK_6    '6'
#define XK_7    '7'
#define XK_9    '9'
#define XK_a    'a'
#define XK_b    'b'
#define XK_c    'c'
#define XK_d    'd'
#define XK_e    'e'
#define XK_g    'g'
#define XK_h    'h'
#define XK_i    'i'
#define XK_j    'j'
#define XK_m    'm'
#define XK_n    'n'
#define XK_o    'o'
#define XK_p    'p'
#define XK_q    'q'
#define XK_r    'r'
#define XK_s    's'
#define XK_t    't'
#define XK_u    'u'
#define XK_v    'v'
#define XK_w    'w'
#define XK_x    'x'
#define XK_y    'y'
#define XK_z    'z'
#define XK_space        VK_SPACE // 0x20
#define XK_quotedbl     '"' //0x22
#define XK_parenleft    '(' //0x28
#define XK_plus         '+' //0x2b
#define XK_comma        ',' //0x2c
#define XK_minus        '-' //0x2d
#define XK_agrave       0xe0 //'à'
#define XK_ccedilla     0xe7 //'ç'
#define XK_eacute       0xe9 //'é'
#define XK_egrave       0xe8 //'è'
#define XK_udiaeresis   0xfc //'ü'
#define XK_dead_circumflex      0xfe52 //0x5e '^'
#define XK_dead_diaeresis       0xfe57 //0xfc 'ü' - unsure: pass uppercase 'Ü' 0xdc
#define XK_BackSpace    0xff08
#define XK_Tab          0xff09
#define XK_Return       0xff0d
#define XK_Home         0xff50
#define XK_Left         0xff51
#define XK_Up           0xff52
#define XK_Right        0xff53
#define XK_Down         0xff54
#define XK_End          0xff57
#define XK_Insert       0xff63
#define XK_KP_Enter     0xff8d
#define XK_KP_Home      0xff95
#define XK_KP_Left      0xff96
#define XK_KP_Up        0xff97
#define XK_KP_Right     0xff98
#define XK_KP_Down      0xff99
#define XK_KP_End       0xff9c
#define XK_KP_Insert    0xff9e
#define XK_KP_Add       0xffab
#define XK_KP_Subtract  0xffad

#define XKeysymToKeycode(A,B) B

#ifdef __cplusplus
}
#endif

#endif //XPUTTY_MSWIN_H_

#endif //_WIN32 //XCompatibility

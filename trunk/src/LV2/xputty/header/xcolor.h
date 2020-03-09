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

#ifndef XCOLOR_H_
#define XCOLOR_H_

#include "xputty.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * 
 * @brief Color_state         - select color mode to use on Widget_t
 */

typedef enum {
    NORMAL_,
    PRELIGHT_,
    SELECTED_,
    ACTIVE_,
    INSENSITIVE_,
} Color_state;

/**
 * 
 * @brief Color_set         - select color set to use on draw
 */

typedef enum {
    FORGROUND_,
    BACKGROUND_,
    BASE_,
    TEXT_,
    SHADOW_,
    FRAME_,
    LIGHT_,
} Color_mod;

/**
 * 
 * @brief Color_t               - struct used to set cairo color for Widget_t
 * @param fg[4]                 - forground {red, green, blue, alpha}
 * @param bg[4]                 - background {red, green, blue, alpha}
 * @param base[4]               - base {red, green, blue, alpha}
 * @param text[4]               - text {red, green, blue, alpha}
 * @param shadow[4]             - shadow {red, green, blue, alpha}
 * @param frame[4]              - frame {red, green, blue, alpha}
 * @param light[4]              - light {red, green, blue, alpha}
 */

typedef struct {
    double fg[4];
    double bg[4];
    double base[4];
    double text[4];
    double shadow[4];
    double frame[4];
    double light[4];
} Colors;

/**
 * @brief XColor_t           - the Widget_t Color struct
 * \n XColor_t could be used for theming you Widget_t set
 */

struct XColor_t {
    Colors normal;
    Colors prelight;
    Colors selected;
    Colors active;
    Colors insensitive;
};

/**
 * @brief set_dark_theme    - init the XColor_t struct to the default 
 * dark theme 
 * @param *main             - pointer to the main Xputty struct
 * @return void
 */

void set_dark_theme(Xputty *main);

/**
 * @brief set_light_theme   - init the XColor_t struct to the default 
 * light theme 
 * @param *main             - pointer to the main Xputty struct
 * @return void
 */

void set_light_theme(Xputty *main);

/**
 * @brief get_color_scheme  - get pointer to the Colors struct to use
 * in relation to the Color_state
 * @param *st               - the Color state to use
 * @return void
 */

Colors *get_color_scheme(Xputty *main, Color_state st);

/**
 * @brief get_color_state   - get the Color_state to use in relation to the
 * Widget_t state
 * @param *wid              - pointer to the Widget_t
 * @return Color_state      - the Color_state related to the Widget_t state
 */

Color_state get_color_state(Widget_t *wid);

/**
 * @brief use_fg_color_scheme  - use forground Colors to paint on Widget_t
 * @param *w                   - the Widget_t to set the Colors
 * @param st                   - the Color_state to use
 * @return void
 */

void use_fg_color_scheme(Widget_t *w, Color_state st);

/**
 * @brief use_bg_color_scheme  - use background Colors to paint on Widget_t
 * @param w                    - the Widget_t to set the Colors
 * @param st                   - the Color_state to use
 * @return void
 */

void use_bg_color_scheme(Widget_t *w, Color_state st);

/**
 * @brief use_base_color_scheme  - use base Colors to paint on Widget_t
 * @param w                      - the Widget_t to set the Colors
 * @param st                     - the Color_state to use
 * @return void
 */

void use_base_color_scheme(Widget_t *w, Color_state st);

/**
 * @brief use_text_color_scheme  - use text Colors to paint on Widget_t
 * @param w                      - the Widget_t to set the Colors
 * @param st                     - the Color_state to use
 * @return void
 */

void use_text_color_scheme(Widget_t *w, Color_state st);

/**
 * @brief use_shadow_color_scheme  - use shadow Colors to paint on Widget_t
 * @param w                        - the Widget_t to set the Colors
 * @param st                       - the Color_state to use
 * @return void
 */

void use_shadow_color_scheme(Widget_t *w, Color_state st);

/**
 * @brief use_frame_color_scheme   - use frame Colors to paint on Widget_t
 * @param w                        - the Widget_t to set the Colors
 * @param st                       - the Color_state to use
 * @return void
 */

void use_frame_color_scheme(Widget_t *w, Color_state st);

/**
 * @brief use_light_color_scheme   - use light Colors to paint on Widget_t
 * @param w                        - the Widget_t to set the Colors
 * @param st                       - the Color_state to use
 * @return void
 */

void use_light_color_scheme(Widget_t *w, Color_state st);

/**
 * @brief set_pattern       - set pattern for the selected Colors
 * @param *w_               - pointer to the Widget_t to set the pattern
 * @param *from             - the Colors set to pattern from (0)
 * @param *to               - the Colors set to pattern to (1)
 * @param mod               - the Color_mod to use
 * @return void
 */

void set_pattern(Widget_t *w, Colors *from, Colors *to, Color_mod mod);

#ifdef __cplusplus
}
#endif

#endif //XCOLOR_H_

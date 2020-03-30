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

#ifndef XADJUSTMENT_H_
#define XADJUSTMENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "xputty.h"


/**
 * 
 * @brief CL_type        - define the type of the controller adjustment
 * one of this types must be given when set up a Adjustment_t for a Wdiget_t
 * @param CL_NONE        - Widget_t didn't request a adjustment
 * @param CL_CONTINUOS   - Widget_t request a continuos adjustment
 * @param CL_TOGGLE      - Widget_t request a toggle adjustment
 * @param CL_BUTTON      - Widget_t request a button adjustment
 * @param CL_ENUM        - Widget_t request a enum adjustment
 * @param CL_LOGARITHMIC - Widget_t request a logarithmic adjustment
 */

typedef enum {
/** Widget_t didn't request a adjustment */
    CL_NONE         = 0x0001,
/** Widget_t request a continuos adjustment */
    CL_CONTINUOS    = 0x0002,
/** Widget_t request a toggle adjustment */
    CL_TOGGLE       = 0x0004,
/** Widget_t request a button adjustment */
    CL_BUTTON       = 0x0008,
/** Widget_t request a enum adjustment */
    CL_ENUM         = 0x0016,
/** Widget_t request a viewport adjustment */
    CL_VIEWPORT     = 0x0032,
/** Widget_t request a viewport adjustment */
    CL_METER        = 0x0064,
/** Widget_t request a logarithmic adjustment */
    CL_LOGARITHMIC  = 0x0128,
}CL_type;

/**
 * 
 * @brief Adjustment_t     - struct to hold a controller adjustment
 * @param *w               - pointer to the Widget_t contain the adjustment
 * @param std_value        - the standart value for the adjustment
 * @param value            - the current value of the adjustment
 * @param min_value        - the minimal value of the adjustment
 * @param max_value        - the maximal value of the adjustment
 * @param step             - the step to increase/decrease the adjustment
 * @param start_value      - internal use to store the current value when pointer
 * movement starts
 * @param type             - should be on of the CL_type
 */

struct  Adjustment_t {
/** pointer to the Widget_t contain the adjustment */
    Widget_t *w;
/** the standart value for the adjustment */
    float std_value;
/** the current value of the adjustment */
    float value;
/** the minimal value of the adjustment */
    float min_value;
/** the maximal value of the adjustment */
    float max_value;
/** the step to increase/decrease the adjustment */
    float step;
/** internal use to store the current value when pointer movement starts */
    float start_value;
/** the scalling to increase/decrease the adjustment on pointer motion*/
    float scale;
/** should be on of the CL_ type */
    CL_type type;
};

/**
 * @brief *add_adjustment    - adding a adjustment to a Widget_t
 * @param *w                 - pointer to the Widget_t request a Adjustment_t
 * @param std_value          - standard value of the Adjustment_t
 * @param value              - current value of the Adjustment_t
 * @param min_value          - minimum value of the Adjustment_t
 * @param max_value          - maximal value of the Adjustment_t
 * @param step               - step to increase/decrease the Adjustment_t
 * @param type               - set CL_type of Adjustment_t
 * @return *adj              - pointer to the Adjustment_t
 */

Adjustment_t *add_adjustment(Widget_t *w, float std_value, float value,
                     float min_value,float max_value, float step, CL_type type);


/**
 * @brief *set_adjustment    - set a new range to a existing Adjustment_t
 * it will be created if it not exsits yet
 * @param *w                 - pointer to the Widget_t request a Adjustment_t
 * @param std_value          - standard value of the Adjustment_t
 * @param value              - current value of the Adjustment_t
 * @param min_value          - minimum value of the Adjustment_t
 * @param max_value          - maximal value of the Adjustment_t
 * @param step               - step to increase/decrease the Adjustment_t
 * @param type               - set CL_type of Adjustment_t
 * @return *adj              - pointer to Adjustment_t
 */

void set_adjustment(Adjustment_t *adj, float std_value, float value,
                float min_value,float max_value, float step, CL_type type);

/**
 * @brief delete_adjustment  - freeing the memory of the Adjustment_t
 * You usually don't need to call this, as it get handled by main_quit() -> destroy_widget()
 * @param *adj               - pointer to the Adjustment to free 
 * @return *void
 */

void *delete_adjustment(Adjustment_t *adj);

/**
 * @brief adj_get_state      - get the current state of the Adjustment_t
 * @param *adj               - pointer to the Adjustment_t
 * @return float             - return the Adjustment_t state mapped to (0<->1)
 */

float adj_get_state(Adjustment_t *adj);

/**
 * @brief adj_set_state      - set the current state of the Adjustment_t
 * @param *adj               - pointer to the Adjustment_t
 * @return float             - set the Adjustment_t state mapped to (0<->1)
 */

void adj_set_state(Adjustment_t *adj, float state);

/**
 * @brief adj_get_value      - get the current value of the Adjustment_t
 * @param *adj               - pointer to the Adjustment_t
 * @return float             - return the Adjustment_t value
 */

float adj_get_value(Adjustment_t *adj);

/**
 * @brief adj_set_value      - set the current value to the Adjustment_t
 * @param *adj               - pointer to the Adjustment_t
 * @param value              - value to set the Adjustment_t to 
 * @return void
 */

void adj_set_value(Adjustment_t *adj, float value);

/**
 * @brief adj_set_start_value - internal use to store the value when pointer movment starts
 * @param *w                  - pointer to Widget_t containing the Adjustment_t
 * @return void
 */

void adj_set_start_value(void *w);

/**
 * @brief adj_set_scale      - internal use to scale the pointer movement (0.1 -1.0)
 * @param *adj               - pointer to the Adjustment_t
 * @param value              - value to set the scaleing factor to 
 * @return void
 */

void adj_set_scale(Adjustment_t *adj, float value);

/**
 * @brief adj_set_motion_state   - internal use to set value and state of the Adjustment_t
 * on mouse pointer movment
 * @param *w                     - pointer to Widget_t containing Adjustment_t
 * @param x                      - movment on the x-axis
 * @param y                      - movement on the y-axis
 * @return void
 */

void adj_set_motion_state(void *w, float x, float y);

/**
 * @brief check_value_changed   - check if Adjustment_t value have changed and send
 * value_changed_callback (VALUE_CHANGED) and adj_callback (ADJ_INTERN) if so
 * @param *adj                  - pointer to the Adjustment_t
 * @param value                 - value to check
 * @return void
 */

void check_value_changed(Adjustment_t *adj, float *value);

#ifdef __cplusplus
}
#endif

#endif //XADJUSTMENT_H_

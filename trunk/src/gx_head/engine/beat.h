/*
 * Copyright (C) 2013, Hermann Meyer, Andreas Degert
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
 *
 *
 *    This file is part of the Guitarix Audio Engine
 *
 *
 * --------------------------------------------------------------------------
 */



#pragma once

#ifndef SRC_HEADERS_BEAT_H_
#define SRC_HEADERS_BEAT_H_

/*
 *  definition for ffunction(float B2N(int,float), "beat.h", "");
 *  in digital_delay.dsp 
 *  set delaytime in relation of notation to ms(bpm(samples)) 
 */

static double always_inline B2N(int ta, double beat) {
    double beatta = beat;
    switch(ta) {
      case(0):
        break;
      case(1):
        beatta *=3.0;
        break;
      case(2):
        beatta *=2.0;
        break;
      case(3):
        beatta *=1.3333;
        break;
      case(4):
        beatta *=1.5;
        break;
      case(5):
        beatta =beat;
        break;
      case(6):
        beatta *=0.6666;
        break;
      case(7):
        beatta *=0.75;
        break;
      case(8):
        beatta *=0.5;
        break;
      case(9):
        beatta *=0.333;
        break;
      case(10):
        beatta *=0.45;
        break;
      case(11):
        beatta *=0.25;
        break;
      case(12):
        beatta *=0.1666;
        break;
      case(13):
        beatta *=0.1875;
        break;
      case(14):
        beatta *=0.125;
        break;
      case(15):
        beatta *=0.083334;
        break;
      case(16):
        beatta *=0.09375;
        break;
      case(17):
        beatta *=0.0625;
        break;
      case(18):
        beatta *=0.041666;
        break;
      default:
        break;
    }
    return beatta;
}
#endif //SRC_HEADERS_BEAT_H_

/*
 * Copyright (C) 2012 Hermann Meyer, Andreas Degert, Pete Shorthose, Steve Poskitt
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

#include "cab_data.cc"


struct CabEntry {
    CabDesc *data;
} cab_table[] = {
    { &static_cast<CabDesc&>(cab_data_4x12) },
    { &static_cast<CabDesc&>(cab_data_2x12) },
    { &static_cast<CabDesc&>(cab_data_1x12) },
    { &static_cast<CabDesc&>(cab_data_4x10) },
    { &static_cast<CabDesc&>(cab_data_2x10) },
    { &static_cast<CabDesc&>(cab_data_HighGain) },
    { &static_cast<CabDesc&>(cab_data_Twin) },
    { &static_cast<CabDesc&>(cab_data_Bassman) },
    { &static_cast<CabDesc&>(cab_data_Marshall) },
    { &static_cast<CabDesc&>(cab_data_AC30) },
    { &static_cast<CabDesc&>(cab_data_Princeton) },
    { &static_cast<CabDesc&>(cab_data_A2) },
    { &static_cast<CabDesc&>(cab_data_1x15) },
    { &static_cast<CabDesc&>(cab_data_mesa) },
    { &static_cast<CabDesc&>(cab_data_briliant) },
    { &static_cast<CabDesc&>(cab_data_vitalize) },
    { &static_cast<CabDesc&>(cab_data_charisma) },
    { &static_cast<CabDesc&>(cab_data_1x8) },
};
static const size_t cab_table_size = sizeof(cab_table) / sizeof(cab_table[0]);

static inline CabEntry& getCabEntry(uint32_t n) {
    if (n >= cab_table_size) {
	n = cab_table_size - 1;
    }
    return cab_table[n];
}

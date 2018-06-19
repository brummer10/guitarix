/*
 * Copyright (C) 2011 Hermann Meyer, James Warden, Andreas Degert, Pete Shorthose
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
 *
 * 
 * ----------------------------------------------------------------------------
 */

#include <unistd.h>

#ifdef _POSIX_MEMLOCK_RANGE
#include <sys/mman.h>

class GX_LOCK
{
public:
  struct rt_lock {
    char *start;
    long int len;
  };
  static void lock_rt_memory();
  static void unlock_rt_memory();
};

void GX_LOCK::lock_rt_memory() {
#ifndef __APPLE__    
  extern char __rt_text__start[], __rt_text__end[];
  extern char __rt_data__start[], __rt_data__end[];
  rt_lock regions[] = {
    { __rt_text__start, __rt_text__end - __rt_text__start },
    { __rt_data__start, __rt_data__end - __rt_data__start },
  };
  long int total_size = 0;
  for (uint32_t i = 0; i < sizeof(regions)/sizeof(regions[0]); i++) {
    total_size +=regions[i].len;
    if (mlock(regions[i].start, regions[i].len) != 0) {
      fprintf(stderr,"failed to lock memory\n");
      return;
    }
  }
  fprintf(stderr,"mlock %ld bytes\n",total_size);
#endif
}

void GX_LOCK::unlock_rt_memory() {
#ifndef __APPLE__    
  extern char __rt_text__start[], __rt_text__end[];
  extern char __rt_data__start[], __rt_data__end[];
  rt_lock regions[] = {
    { __rt_text__start, __rt_text__end - __rt_text__start },
    { __rt_data__start, __rt_data__end - __rt_data__start },
  };
  long int total_size = 0;
  for (uint32_t i = 0; i < sizeof(regions)/sizeof(regions[0]); i++) {
    total_size +=regions[i].len;
    if (munlock(regions[i].start, regions[i].len) != 0) {
      fprintf(stderr,"failed to unlock memory\n");
      return;
    }
  }
  fprintf(stderr,"munlock %ld bytes\n",total_size);
#endif  
}
#endif

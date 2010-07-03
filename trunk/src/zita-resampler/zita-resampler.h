//---------------------------------------------------------------------------------
//
//    Copyright (C) 2007 Fons Adriaensen <fons@kokkinizita.net>
//    
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//---------------------------------------------------------------------------------


#ifndef __RESAMPLER_H
#define __RESAMPLER_H

#include <cstdlib>  // for abort()
#include <pthread.h>

class Resampler_mutex
{
private:

    friend class Resampler_table;

    Resampler_mutex (void) { if (pthread_mutex_init (&_mutex, 0)) abort (); }
    ~Resampler_mutex (void) { pthread_mutex_destroy (&_mutex); }
    void lock (void) { if (pthread_mutex_lock (&_mutex)) abort (); }
    void unlock (void){ if (pthread_mutex_unlock (&_mutex)) abort (); }

    pthread_mutex_t  _mutex;
};


class Resampler_table
{
public:

    static void print_list (void);

private:

    Resampler_table (unsigned int ra, unsigned int rb, unsigned int hl, unsigned int fr);
    ~Resampler_table (void);

    friend class Resampler;

    Resampler_table     *_next;
    unsigned int         _refc;
    float               *_ctab;
    unsigned int         _ra;
    unsigned int         _rb;
    unsigned int         _hl;
    unsigned int         _fr;

    double sinc (double x);
    double wind (double x);

    static Resampler_table *create (unsigned int ra, unsigned int rb, unsigned int hl, unsigned int fr);
    static void destroy (Resampler_table *T);

    static Resampler_table  *_list;
    static Resampler_mutex   _mutex;
};



class Resampler
{
public:

    Resampler (void);
    ~Resampler (void);

    int  setup (unsigned int fs_inp, unsigned int fs_out, unsigned int nchan, unsigned int hlen);
    int  setup (unsigned int fs_inp, unsigned int fs_out, unsigned int nchan, unsigned int hlen, unsigned int freq);
    void clear (void);
    int  reset (void);
    int  nchan (void) { return _nchan; }
    int  ratio_a (void) { return _table ? _table->_ra : 0; }
    int  ratio_b (void) { return _table ? _table->_rb : 0; }
    int  filtlen (void) { return _table ? (2 * _table->_hl) : 0; }
    int  process (void);

    unsigned int         inp_count;
    unsigned int         out_count;
    float               *inp_data;
    float               *out_data;

private:

    unsigned int gcd (unsigned int a, unsigned int b);

    Resampler_table     *_table;
    float               *_buff;
    unsigned int         _nchan;
    unsigned int         _inmax;
    unsigned int         _index;
    unsigned int         _nread;
    unsigned int         _phase;
};



#endif

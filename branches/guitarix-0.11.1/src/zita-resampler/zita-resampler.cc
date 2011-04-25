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


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "zita-resampler.h"


Resampler_table  *Resampler_table::_list = 0;
Resampler_mutex   Resampler_table::_mutex;


Resampler_table::Resampler_table (unsigned int ra,
                                  unsigned int rb,
                                  unsigned int hl,
                                  unsigned int fr) :
    _next (0),
    _refc (0),
    _ra (ra),
    _rb (rb),
    _hl (hl),
    _fr (fr)
{
    unsigned int  i, j;
    double        s, t, w;
    float         *p;

    _ctab = new float [hl * (rb + 1)];
    p = _ctab;
    s = (double) rb / (double) ra;
    w = 1e-4 * fr;
    if (s < 1.0) w *= s;
    for (j = 0; j <= rb; j++)
    {
	t = (double) j / (double) rb;
	for (i = 0; i < hl; i++)
	{
	    p [hl - i - 1] = (float)(w * sinc (t * w) * wind (t / hl));
	    t += 1;
	}
	p += hl;
    }
}


Resampler_table::~Resampler_table (void)
{
    delete[] _ctab;
}


double Resampler_table::sinc (double x)
{
    x = fabs (x);
    if (x < 1e-6) return 1.0;
    x *= M_PI;
    return sin (x) / x;
}


double Resampler_table::wind (double x)
{
    x = fabs (x);
    if (x >= 1.0) return 0.0f;
    x *= M_PI;
    return 0.384 + 0.500 * cos (x) + 0.116 * cos (2 * x);
}


Resampler_table *Resampler_table::create (unsigned int ra,
                                          unsigned int rb,
                                          unsigned int hl,
                                          unsigned int fr)
{
    Resampler_table *P;

    _mutex.lock ();
    P = _list;
    while (P)
    {
	if ((ra == P->_ra) && (rb == P->_rb) && (hl == P->_hl) && (fr == P->_fr))
	{
	    P->_refc++;
            _mutex.unlock ();
            return P;
	}
	P = P->_next;
    }
    P = new Resampler_table (ra, rb, hl, fr);
    P->_refc = 1;
    P->_next = _list;
    _list = P;
    _mutex.unlock ();
    return P;
}


void Resampler_table::destroy (Resampler_table *T)
{
    Resampler_table *P, *Q;

    _mutex.lock ();
    if (T)
    {
	T->_refc--;
	if (T->_refc == 0)
	{
	    P = _list;
	    Q = 0;
	    while (P)
	    {
		if (P == T)
		{
		    if (Q) Q->_next = T->_next;
		    else      _list = T->_next;
		    break;
		}
		Q = P;
		P = P->_next;
	    }
	    delete T;
	}
    }
    _mutex.unlock ();
}


void Resampler_table::print_list (void)
{
    Resampler_table *P;

    printf ("Resampler table\n----\n");
    for (P = _list; P; P = P->_next)
    {
	printf ("refc = %3d   ra = %5d   rb = %5d   hl = %3d\n", P->_refc, P->_ra, P->_rb, P->_hl);
    }
    printf ("----\n\n");
}




Resampler::Resampler (void) :
    _table (0),
    _buff (0),
    _nchan (0)
{
    reset ();
}


Resampler::~Resampler (void)
{
    clear ();
}


void Resampler::clear (void)
{
    Resampler_table::destroy (_table);
    delete[] _buff;
    _buff  = 0;
    _table = 0;
    _nchan = 0;
    reset ();
}


int Resampler::setup (unsigned int fs_inp,
                      unsigned int fs_out,
                      unsigned int nchan,
                      unsigned int hlen)
{
    if ((hlen < 16) || (hlen > 96)) return 1;
    return setup (fs_inp, fs_out, nchan, hlen, 10000 - 26000 / hlen);
}


int Resampler::setup (unsigned int fs_inp,
                      unsigned int fs_out,
                      unsigned int nchan,
                      unsigned int hlen,
                      unsigned int freq)
{
    unsigned int       a, b, h, k = 0;
    float              *B = 0;
    Resampler_table    *T = 0;

    if (fs_inp && fs_out && nchan)
    {
        k = gcd (fs_inp, fs_out);
        a = fs_inp / k;
        b = fs_out / k;
        if ((16 * a >= b) && (b <= 1000))
	{
	    h = hlen;
	    k = 250;
	    if (a > b) 
	    {
		h = (h * a + b - 1) / b;
		k = (k * a + b - 1) / b;
	    }
            T = Resampler_table::create (a, b, h, freq);
	    B = new float [nchan * (2 * h - 1 + k)];
	}
    }
    clear ();
    if (T)
    {
	_table = T;
	_buff  = B;
	_nchan = nchan;
	_inmax = k;
	return reset ();
    }
    else return 1;
}


int Resampler::reset (void)
{
    if (!_table) return 1;

    inp_count = 0;
    out_count = 0;
    inp_data = 0;
    out_data = 0;
    _index = 0;
    _nread = 2 * _table->_hl;
    _phase = 0;
    return 0;
}


int Resampler::process (void)
{
    unsigned int   hl, ra, rb, in, nr, ph, i, n, c;
    float          *p1, *p2;

    if (!_table) return 1;

    hl = _table->_hl;
    ra = _table->_ra * hl;
    rb = _table->_rb * hl;
    in = _index;
    nr = _nread;
    ph = _phase;
    n = (2 * hl - nr) * _nchan;
    p1 = _buff + in * _nchan;
    p2 = p1 + n;

    while (out_count)
    {
	if (nr)
	{
	    if (inp_count == 0) break;
  	    if (inp_data)
	    {
                for (c = 0; c < _nchan; c++) p2 [c] = inp_data [c];
		inp_data += _nchan;
	    }
	    else
	    {
                for (c = 0; c < _nchan; c++) p2 [c] = 0;
	    }
	    nr--;
	    p2 += _nchan;
	    inp_count--;
	}
        else
	{
	    if (out_data)
	    {
		float *c1 = _table->_ctab + ph;
		float *c2 = _table->_ctab + rb - ph;
		for (c = 0; c < _nchan; c++)
		{
		    float *q1 = p1 + c;
		    float *q2 = p2 + c;
		    float s = 1e-20f;
		    for (i = 0; i < hl; i++)
		    {
			q2 -= _nchan;
			s += *q1 * c1 [i] + *q2 * c2 [i];
			q1 += _nchan;
		    }
		    *out_data++ = s - 1e-20f;
		}
	    }
	    out_count--;
	    ph += ra;
	    if (ph >= rb)
	    {
		nr = ph / rb;
		ph -= nr * rb;
		in += nr;
                p1 += nr * _nchan;;
		if (in >= _inmax)
		{
		    n = (2 * hl - nr) * _nchan;
  		    memcpy (_buff, p1, n * sizeof (float));
		    in = 0;
		    p1 = _buff;
		    p2 = p1 + n;
		}
	    }
	}
    }

    _index = in;
    _nread = nr;
    _phase = ph;

    return 0;
}


unsigned int Resampler::gcd (unsigned int a, unsigned int b)
{
    if (a == 0) return b;
    if (b == 0) return a;
    while (1)
    {
	if (a > b)
	{
	    a = a % b;
	    if (a == 0) return b;
	    if (a == 1) return 1;
	}
	else
	{
	    b = b % a;
	    if (b == 0) return a;
	    if (b == 1) return 1;
	}
    }    
    return 1; 
}



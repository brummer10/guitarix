/*
    Copyright (C) 2006-2009 Fons Adriaensen <fons@kokkinizita.net>
    
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "zita-convolver.h"




Convproc::Convproc (void) :
    _state (ST_IDLE),
    _flags (0),
    _ninp (0),
    _nout (0),
    _nproc (0),
    _fftwopt (FFTW_ESTIMATE),
    _vectopt (0)
{
    memset (_inpbuff, 0, MAXINP * sizeof (float *));
    memset (_outbuff, 0, MAXOUT * sizeof (float *));
}


Convproc::~Convproc (void)
{
    cleanup ();
}


int Convproc::configure (unsigned int ninp,
                         unsigned int nout,
                         unsigned int maxsize,
                         unsigned int quantum,
                         unsigned int minpart,
			 unsigned int maxpart)
{
    unsigned int offs, npar, size, pind, i, m, n, r;
    int prio;

    if (_state != ST_IDLE) return Converror::BAD_STATE;
    if (   (quantum & (quantum - 1))
        || (quantum < MINQUANT)
        || (quantum > MAXQUANT)
        || (minpart & (minpart - 1))
	|| (minpart < MINPART)
        || (minpart < quantum)
        || (minpart > MAXDIVIS * quantum)
        || (maxpart & (maxpart - 1))
	|| (maxpart > MAXPART)
	|| (maxpart < minpart)) return Converror::BAD_PARAM;

    cleanup ();

    prio = 0;
    size = quantum;
    while (size < minpart)
    {
	prio -= 1;
	size <<= 1;
    }
    if (size & PMASK2)
    {
	n = 2;
	r = 1;
    }
    else if (size & PMASK4)
    {
	n = 6;
	r = 2;
    }
    else return Converror::BAD_PARAM;
    if (minpart == quantum) n++;

    try
    {
	for (offs = pind = 0; offs < maxsize; pind++)
	{
	    npar = (maxsize - offs + size - 1) / size;
	    if (size < maxpart)
	    {
		m = (ninp * nout < 16) ? n : n + 2;
		if (npar > m) npar = n;
	    }
	    _procs [pind].configure (prio, offs, npar, size, _fftwopt, _vectopt);
	    offs += size * npar;
	    if (offs < maxsize)
	    {
		prio -= r;
		size <<= r;
		n = 6;
		r = 2;
	    }
	}	

	_ninp = ninp;
	_nout = nout;
	_nproc = pind;
	_quantum = quantum;
	_minpart = minpart;
	_maxpart = size;
	_inpsize = 2 * size;
	 
	for (i = 0; i < ninp; i++) _inpbuff [i] = new float [_inpsize];
	for (i = 0; i < nout; i++) _outbuff [i] = new float [_minpart];
    }
    catch (...)
    {
	cleanup ();
	return Converror::MEM_ALLOC;
    }

    _state = ST_STOP;
    return 0;
}


int Convproc::reset (void)
{
    unsigned int i;

    if (_state == ST_IDLE) return Converror::BAD_STATE;
    for (i = 0; i < _ninp; i++) memset (_inpbuff [i], 0, _inpsize * sizeof (float));
    for (i = 0; i < _nout; i++) memset (_outbuff [i], 0, _minpart * sizeof (float));
    for (i = 0; i < _nproc; i++) _procs [i].reset ();

    return 0;
}


int Convproc::impdata_create (unsigned int inp,
                              unsigned int out,
                              unsigned int step,
                              float       *data,
                              int          ind0,
                              int          ind1)
{
    unsigned int j;

    if (_state != ST_STOP) return Converror::BAD_STATE;
    try
    {
        for (j = 0; j < _nproc; j++)
	{
            _procs [j].impdata_create (inp, out, step, data, ind0, ind1);
	}
    }
    catch (...)
    {
	cleanup ();
	return Converror::MEM_ALLOC;
    }
    return 0;
}


int Convproc::impdata_update (unsigned int inp,
                              unsigned int out,
                              unsigned int step,
                              float       *data, 
                              int          ind0,
                              int          ind1)
{
    unsigned int j;

    if (_state < ST_STOP) return Converror::BAD_STATE;
    for (j = 0; j < _nproc; j++)
    {
        _procs [j].impdata_update (inp, out, step, data, ind0, ind1);
    }
    return 0;
}


int Convproc::impdata_copy (unsigned int inp1,
                            unsigned int out1,
                            unsigned int inp2,
                            unsigned int out2) 
{
    unsigned int j;

    if (_state != ST_STOP) return Converror::BAD_STATE;
    try
    {
        for (j = 0; j < _nproc; j++)
	{
            _procs [j].impdata_copy (inp1, out1, inp2, out2);
	}
    }
    catch (...)
    {
	cleanup ();
	return Converror::MEM_ALLOC;
    }

    return 0;
}


int Convproc::start_process (int maxprio, int schclass)
{
    unsigned int k;

    if (_state != ST_STOP) return Converror::BAD_STATE;

    _flags = 0;
    _inpoffs = 0;
    _outoffs = 0;
    _procdel = 0;
    _state = ST_PROC;

    for (k = 0; k < _nproc; k++)
    {
        _procs [k]._inpsize = _inpsize;
        _procs [k]._outsize = _minpart;
        _procs [k]._inpbuff = _inpbuff;
        _procs [k]._outbuff = _outbuff;
    }

    reset ();

    for (k = (_minpart == _quantum) ? 1 : 0; k < _nproc; k++)
    {
         _procs [k].start (maxprio, schclass);
    }

    return 0;
}


int Convproc::stop_process (void)
{
    unsigned int k;

    if (_state != ST_PROC) return Converror::BAD_STATE;

    _state = ST_WAIT;
    for (k = 0; k < _nproc; k++) _procs [k].stop ();
    check ();
    
    return 0;
}


int Convproc::cleanup (void)
{
    unsigned int k;

    if (_state != ST_STOP) return Converror::BAD_STATE;

    for (k = 0; k < _ninp; k++) delete[] _inpbuff [k];
    for (k = 0; k < _nout; k++) delete[] _outbuff [k];
    for (k = 0; k < _nproc; k++) _procs [k].cleanup ();
    memset (_inpbuff, 0, MAXINP * sizeof (float *));
    memset (_outbuff, 0, MAXOUT * sizeof (float *));

    _ninp = 0;
    _nout = 0;
    _nproc = 0;
    _minpart = 0;
    _inpsize = 0;
    _state = ST_IDLE;

    return 0;
}


void Convproc::process (bool skip)
{
    unsigned int f, k;

    if (_state != ST_PROC) return;
    
    _inpoffs += _quantum;
    if (_inpoffs == _inpsize) _inpoffs = 0;

    _outoffs += _quantum;
    if (_outoffs == _minpart)
    {
        _outoffs = f = 0;
	for (k = 0; k < _nout; k++) memset (_outbuff [k], 0, _minpart * sizeof (float));
	for (k = 0; k < _nproc; k++) f |= _procs [k].readout (skip);
        if (f)
	{
	    _flags |= f;
            if (++_procdel >= 3)
            {
	        stop_process ();
	        _flags = FL_LOAD;
	    }
	}
        else _procdel = 0;
    }
}


void Convproc::check (void)
{
    unsigned int k;

    for (k = 0; (k < _nproc) && _procs [k].idle (); k++);
    if (k == _nproc) _state = ST_STOP;
}


void Convproc::print (void)
{
    unsigned int k;

    for (k = 0; k < _nproc; k++) _procs [k].print ();
}



typedef float FV4 __attribute__ ((vector_size(16)));


Convlevel::Convlevel (void) :
    _stat (ST_IDLE),
    _npar (0),
    _parsize (0),
    _vectopt (0),
    _pthr (0),
    _inp_list (0),
    _out_list (0),
    _plan_r2c (0),
    _plan_c2r (0),
    _time_data (0),
    _prep_data (0),
    _freq_data (0)
{
}


Convlevel::~Convlevel (void)
{
    cleanup ();
}


void *Convlevel::alloc_aligned (size_t size)
{
    void *p;

    if (posix_memalign (&p, 16, size)) throw (Converror (Converror::MEM_ALLOC));
    memset (p, 0, size);
    return p;
}


void Convlevel::configure (int prio,
                           unsigned int offs,
                           unsigned int npar,
                           unsigned int parsize,
			   unsigned int fftwopt,
			   unsigned int vectopt)
{
    _prio = prio;
    _offs = offs;
    _npar = npar;
    _parsize = parsize;
    _vectopt = vectopt;
    
    _time_data = (float *)(alloc_aligned (2 * _parsize * sizeof (float)));
    _prep_data = (float *)(alloc_aligned (2 * _parsize * sizeof (float)));
    _freq_data = (fftwf_complex *)(alloc_aligned ((_parsize + 1) * sizeof (fftwf_complex)));
    _plan_r2c = fftwf_plan_dft_r2c_1d (2 * _parsize, _time_data, _freq_data, fftwopt);
    _plan_c2r = fftwf_plan_dft_c2r_1d (2 * _parsize, _freq_data, _time_data, fftwopt);
    if (_plan_r2c && _plan_c2r) return;
    throw (Converror (Converror::MEM_ALLOC));
}


void Convlevel::impdata_create (unsigned int inp,
                                unsigned int out,
                                unsigned int step,
                                float *data,
                                int i0,
                                int i1)
{
    unsigned int   k;
    int            j, j0, j1, n;
    float          norm;
    fftwf_complex  *fftb;
    Macnode        *M;

    n = i1 - i0;
    i0 = _offs - i0;
    i1 = i0 + _npar * _parsize;
    if ((i0 >= n) || (i1 <= 0)) return;

    M = findmacnode (inp, out, true);
    if (! (M->_fftb))
    {
	M->_fftb = new fftwf_complex * [_npar];
	memset (M->_fftb, 0, _npar * sizeof (fftwf_complex *));
    }

    norm = 0.5f / _parsize;
    for (k = 0; k < _npar; k++)
    {
	i1 = i0 + _parsize;
	if ((i0 < n) && (i1 > 0))
	{
	    if (! (M->_fftb [k]))
	    {
		M->_fftb [k] = (fftwf_complex *)(alloc_aligned ((_parsize + 1) * sizeof (fftwf_complex)));
	    }
	    memset (_prep_data, 0, 2 * _parsize * sizeof (float));
	    j0 = (i0 < 0) ? 0 : i0;
	    j1 = (i1 > n) ? n : i1;
	    for (j = j0; j < j1; j++) _prep_data [j - i0] = norm * data [j * step];
	    fftwf_execute_dft_r2c (_plan_r2c, _prep_data, _freq_data);
#ifdef VECTORIZE
	    if (_vectopt) fftswap (_freq_data);
#endif
  	    fftb = M->_fftb [k];
	    for (j = 0; j <= (int)_parsize; j++)
	    {
	        fftb [j][0] += _freq_data [j][0];
	        fftb [j][1] += _freq_data [j][1];
	    }
	}
	i0 = i1;
    }
}


void Convlevel::impdata_update (unsigned int inp,
                                unsigned int out,
                                unsigned int step,
                                float *data,
                                int i0,
                                int i1)
{
    unsigned int   k;
    int            j, j0, j1, n;
    float          norm;
    fftwf_complex  *fftb;
    Macnode        *M;

    M = findmacnode (inp, out, false);
    if (! M) return;

    n = i1 - i0;
    i0 = _offs - i0;
    i1 = i0 + _npar * _parsize;
    if ((i0 >= n) || (i1 <= 0)) return;

    norm = 0.5f / _parsize;
    for (k = 0; k < _npar; k++)
    {
	i1 = i0 + _parsize;
	fftb = M->_fftb [k];
	if (fftb && (i0 < n) && (i1 > 0))
	{
	    memset (_prep_data, 0, 2 * _parsize * sizeof (float));
	    j0 = (i0 < 0) ? 0 : i0;
	    j1 = (i1 > n) ? n : i1;
	    for (j = j0; j < j1; j++) _prep_data [j - i0] = norm * data [j * step];
	    fftwf_execute_dft_r2c (_plan_r2c, _prep_data, fftb);
#ifdef VECTORIZE
	    if (_vectopt) fftswap (fftb);
#endif
	}
	i0 = i1;
    }
}


void Convlevel::impdata_copy (unsigned int inp1,
                              unsigned int out1,
                              unsigned int inp2,
                              unsigned int out2)
{
    Macnode  *M1;
    Macnode  *M2;

    M1 = findmacnode (inp1, out1, false);
    if (! M1) return;
    M2 = findmacnode (inp2, out2, true);
    if (M2->_fftb) return;
    M2->_fftb = M1->_fftb;
    M2->_copy = true;
}


void Convlevel::reset (void)
{
    unsigned int  i;
    Inpnode       *X;
    Outnode       *Y;

    for (X = _inp_list; X; X = X->_next)
    {
        for (i = 0; i < _npar; i++)
	{
            memset (X->_ffta [i], 0, (_parsize + 1) * sizeof (fftwf_complex));
	}
    }
    for (Y = _out_list; Y; Y = Y->_next) 
    {
	for (i = 0; i < 3; i++)
	{
            memset (Y->_buff [i], 0, _parsize * sizeof (float));
	}
    }
    if (_parsize == _outsize)
    {
        _outoffs = 0;
        _inpoffs = 0;
    }
    else
    {
        _outoffs = _parsize / 2;
        _inpoffs = _inpsize - _outoffs;
    }
    _bits = _parsize / _outsize;
    _late = 0;
    _ipar = 0;
    _opi1 = 0;
    _opi2 = 1;
    _opi3 = 2;
    sem_init (&_trig, 0, 0);
}


void Convlevel::start (int priority, int schclass)
{
    int                min, max;
    pthread_attr_t     attr;
    struct sched_param parm;

    _pthr = 0;
    min = sched_get_priority_min (schclass);
    max = sched_get_priority_max (schclass);
    priority += _prio;
    if (priority > max) priority = max;
    if (priority < min) priority = min;
    parm.sched_priority = priority;
    pthread_attr_init (&attr);
    pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
    pthread_attr_setschedpolicy (&attr, schclass);
    pthread_attr_setschedparam (&attr, &parm);
    pthread_attr_setscope (&attr, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setinheritsched (&attr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setstacksize (&attr, 0x10000);
    pthread_create (&_pthr, &attr, static_main, this);
    pthread_attr_destroy (&attr);
}


void Convlevel::stop (void)
{
    if (_stat != ST_IDLE)
    {
        _stat = ST_TERM;
	sem_post (&_trig);
    }
}


void Convlevel::cleanup (void)
{
    unsigned int  i;
    Inpnode       *X, *X1;
    Outnode       *Y, *Y1;
    Macnode       *M, *M1;

    X = _inp_list;
    while (X)
    {
        for (i = 0; i < _npar; i++) free (X->_ffta [i]);
	delete[] X->_ffta;
	X1 = X->_next;
	delete X;
	X = X1;
    }
    _inp_list = 0;

    Y = _out_list;
    while (Y)
    {
	M = Y->_list;
	while (M)
	{
	    if ((M->_fftb) && !(M->_copy))
	    {
	        for (i = 0; i < _npar; i++) 
		{
                    free (M->_fftb [i]);
		}
	        delete[] M->_fftb;
	    }
	    M1 = M->_next;
	    delete M;
	    M = M1;
	}
	for (i = 0; i < 3; i++) free (Y->_buff [i]);
	Y1 = Y->_next;
	delete Y;
	Y = Y1;
    }
    _out_list = 0;

    fftwf_destroy_plan (_plan_r2c);
    fftwf_destroy_plan (_plan_c2r);
    free (_time_data);
    free (_prep_data);
    free (_freq_data);
    _plan_r2c = 0;
    _plan_c2r = 0;
    _time_data = 0;
    _prep_data = 0;
    _freq_data = 0;
}


void *Convlevel::static_main (void *arg)
{
    ((Convlevel *) arg)->main ();
    return 0;
}


void Convlevel::main (void)
{
    _stat = ST_PROC;
    while (true)
    {
	sem_wait (&_trig);
	if (_stat == ST_TERM)
	{
            _stat = ST_IDLE;
	    _pthr = 0;
            return;
        }
	process (false);
    }
}


void Convlevel::process (bool skip)
{
    unsigned int    i, j, k;
    unsigned int    i1, n1, n2;

    Inpnode         *X;
    Macnode         *M;
    Outnode         *Y;
    fftwf_complex   *ffta;
    fftwf_complex   *fftb;
    float           *inpd;
    float           *outd;

    i1 = _inpoffs;
    n1 = _parsize;
    n2 = 0;
    _inpoffs = i1 + n1;
    if (_inpoffs >= _inpsize)
    {
        _inpoffs -= _inpsize;
	n2 = _inpoffs;
	n1 -= n2;
    }

    for (X = _inp_list; X; X = X->_next)
    {
	inpd = _inpbuff [X->_inp];
	if (n1) memcpy (_time_data, inpd + i1, n1 * sizeof (float));
	if (n2) memcpy (_time_data + n1, inpd, n2 * sizeof (float));
	memset (_time_data + _parsize, 0, _parsize * sizeof (float));
	fftwf_execute_dft_r2c (_plan_r2c, _time_data, X->_ffta [_ipar]);
#ifdef VECTORIZE
	if (_vectopt) fftswap (X->_ffta [_ipar]);
#endif
    }

    if (skip)
    {
        for (Y = _out_list; Y; Y = Y->_next)
	{
	    outd = Y->_buff [_opi3];
	    memset (outd, 0, _parsize * sizeof (float));
	}
    }
    else
    {
	for (Y = _out_list; Y; Y = Y->_next)
	{
	    memset (_freq_data, 0, (_parsize + 1) * sizeof (fftwf_complex));
	    for (M = Y->_list; M; M = M->_next)
	    {
		X = M->_inpn;
		i = _ipar;
		for (j = 0; j < _npar; j++)
		{
		    ffta = X->_ffta [i];
		    fftb = M->_fftb [j];
		    if (fftb)
		    {
#ifdef VECTORIZE
			if (_vectopt)
			{
			    FV4 *A = (FV4 *) ffta;
			    FV4 *B = (FV4 *) fftb;
			    FV4 *D = (FV4 *) _freq_data;
			    for (k = 0; k < _parsize; k += 4)
			    {
				D [0] += A [0] * B [0] - A [1] * B [1];
				D [1] += A [0] * B [1] + A [1] * B [0];
				A += 2;
				B += 2;
				D += 2;
			    }
			    _freq_data [_parsize][0] += ffta [_parsize][0] * fftb [_parsize][0];
			    _freq_data [_parsize][1] = 0;
			}
			else
#endif
			{
			    for (k = 0; k <= _parsize; k++)
			    {
				_freq_data [k][0] += ffta [k][0] * fftb [k][0] - ffta [k][1] * fftb [k][1];
				_freq_data [k][1] += ffta [k][0] * fftb [k][1] + ffta [k][1] * fftb [k][0];
			    }
			}
		    }
		    if (i == 0) i = _npar;
		    i--;
		}
	    }

#ifdef VECTORIZE
	    if (_vectopt) fftswap (_freq_data);
#endif
	    fftwf_execute_dft_c2r (_plan_c2r, _freq_data, _time_data);
	    outd = Y->_buff [_opi2];
	    for (k = 0; k < _parsize; k++) outd [k] += _time_data [k];
	    outd = Y->_buff [_opi3];
	    memcpy (outd, _time_data + _parsize, _parsize * sizeof (float));
	}
    }

    _ipar++;
    if (_ipar == _npar) _ipar = 0;
}


int Convlevel::readout (bool skip)
{
    unsigned int    k;
    Outnode        *Y;
    float           *p, *q;	

    _outoffs += _outsize;
    if (_outoffs == _parsize)
    {
	_outoffs = 0;
	if (_stat == ST_PROC)
	{
            k = _opi1;
	    _opi1 = _opi2;
	    _opi2 = _opi3;
	    _opi3 = k;
	    sem_getvalue (&_trig, &_late);
            sem_post (&_trig);
	}
        else
	{
            process (skip);
            k = _opi1;
	    _opi1 = _opi2;
	    _opi2 = _opi3;
	    _opi3 = k;
	}
    }

    if (! skip)
    {
        for (Y = _out_list; Y; Y = Y->_next)
        {
            p = Y->_buff [_opi1] + _outoffs;
	    q = _outbuff [Y->_out];
            for (k = 0; k < _outsize; k++) q [k] += p [k];
        }
    }

    return _late ? _bits : 0;
}


void Convlevel::print (void)
{
    printf ("prio = %4d, offs = %6d,  parsize = %5d,  npar = %3d\n", _prio, _offs, _parsize, _npar);
}


Macnode *Convlevel::findmacnode (unsigned int inp, unsigned int out, bool create)
{
    unsigned int  i;
    Inpnode       *X;
    Outnode       *Y;
    Macnode       *M;

    for (X = _inp_list; X && (X->_inp != inp); X = X->_next);
    if (! X)
    {
	if (! create) return 0;
	X = new Inpnode;
	X->_next = _inp_list;
	_inp_list = X;
	X->_inp = inp;
	X->_ffta = new fftwf_complex * [_npar];
	memset (X->_ffta, 0, _npar * sizeof (fftw_complex *));
        for (i = 0; i < _npar; i++)
	{
            X->_ffta [i] = (fftwf_complex *)(alloc_aligned ((_parsize + 1) * sizeof (fftwf_complex)));
	}
    }

    for (Y = _out_list; Y && (Y->_out != out); Y = Y->_next);
    if (! Y)
    {
	if (! create) return 0;
	Y = new Outnode;
	Y->_next = _out_list;
	_out_list = Y;
	Y->_out = out;
	Y->_list = 0;
        for (i = 0; i < 3; i++)
	{
	    Y->_buff [i] = 0;
	}
        for (i = 0; i < 3; i++)
	{
	    Y->_buff [i] = (float *)(alloc_aligned (_parsize * sizeof (float)));
	}
    }

    for (M = Y->_list; M && (M->_inpn != X); M = M->_next);
    if (! M)
    {
	if (! create) return 0;
	M = new Macnode;
	M->_next = Y->_list;
	Y->_list = M;
	M->_inpn = X;
	M->_fftb = 0;
	M->_copy = false;
    }

    return M;
}


#ifdef VECTORIZE

void Convlevel::fftswap (fftwf_complex *p)
{
    unsigned int  n = _parsize;
    float         a, b;

    while (n)
    {
	a = p [2][0];
	b = p [3][0];
        p [2][0] = p [0][1];
        p [3][0] = p [1][1];
        p [0][1] = a;
        p [1][1] = b;
	p += 4;
        n -= 4;
    }
}

#endif



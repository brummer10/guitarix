// ----------------------------------------------------------------------------
//
//  Copyright (C) 2006-2011 Fons Adriaensen <fons@linuxaudio.org>
//    
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// ----------------------------------------------------------------------------


#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "zita-convolver.h"

#ifdef _WIN32
#define posix_memalign_free _aligned_free
#define posix_memalign(p, a, s) (((*(p)) = _aligned_malloc((s), (a))), *(p) ?0 :errno)
#else
#define posix_memalign_free free
#endif


int zita_convolver_major_version (void)
{
    return ZITA_CONVOLVER_MAJOR_VERSION;
}


float Convproc::_mac_cost = 1.0f;
float Convproc::_fft_cost = 5.0f;


Convproc::Convproc (void) :
    _state (ST_IDLE),
    _options (0),
    _skipcnt (0),
    _density (0),
    _ninp (0),
    _nout (0),
    _quantum (0),
    _minpart (0),
    _maxpart (0),
    _nlevels (0),
    _latecnt (0)
{
    memset (_inpbuff, 0, MAXINP * sizeof (float *));
    memset (_outbuff, 0, MAXOUT * sizeof (float *));
    memset (_convlev, 0, MAXLEV * sizeof (Convlevel *));
}


Convproc::~Convproc (void)
{
    cleanup ();
}


void Convproc::set_options (unsigned int options)
{
    _options = options;
}


void Convproc::set_density (float density)
{
    _density = density;
}


void Convproc::set_skipcnt (unsigned int skipcnt)
{
    if ((_quantum == _minpart) && (_quantum == _maxpart)) _skipcnt = skipcnt;
}


int Convproc::configure (unsigned int ninp,
                         unsigned int nout,
                         unsigned int maxsize,
                         unsigned int quantum,
                         unsigned int minpart,
			 unsigned int maxpart)
{
    unsigned int  offs, npar, size, pind, nmin, nmax, step, i;
    int           prio, d, r, s;
    float         cfft, cmac, t;
    
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

    if (ninp < nout) { nmin = ninp; nmax = nout; }
    else             { nmin = nout; nmax = ninp; }

    if (_density <= 0) _density = 1.0 / nmin;
    else
    {
        t = 1.0f / nmax;
        if (_density < t) _density = t;
        if (_density > 1) _density = 1;
    }

    cfft = _fft_cost * (ninp + nout);
    cmac = _mac_cost * ninp * nout * _density;
    step = (cfft < 4 * cmac) ? 1 : 2;

    if (step == 2)
    {
        r = maxpart / minpart;
        s = (r & 0xAAAA) ? 1 : 2;
    }
    else s = 1;
    nmin = (s == 1) ? 2 : 6;
    if (minpart == quantum) nmin++;

    prio = 0;
    size = quantum;
    while (size < minpart)
    {
	prio -= 1;
	size <<= 1;
    }

    try
    {
	for (offs = pind = 0; offs < maxsize; pind++)
	{
	    npar = (maxsize - offs + size - 1) / size;
	    if ((size < maxpart) && (npar > nmin))
	    {
		r = 1 << s;
		d = npar - nmin;
		d = d - (d + r - 1) / r;
		if (cfft < d * cmac) npar = nmin;
	    }
	    _convlev [pind] = new Convlevel ();
	    _convlev [pind]->configure (prio, offs, npar, size, _options);

	    offs += size * npar;
	    if (offs < maxsize)
	    {
		prio -= s;
		size <<= s;
		s = step;
                nmin = (s == 1) ? 2 : 6;
	    }
	}	

	_ninp = ninp;
	_nout = nout;
	_quantum = quantum;
	_minpart = minpart;
	_maxpart = size;
	_nlevels = pind;
	_latecnt = 0;
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
        for (j = 0; j < _nlevels; j++)
	{
            _convlev [j]->impdata_create (inp, out, step, data, ind0, ind1);
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
    for (j = 0; j < _nlevels; j++)
    {
        _convlev [j]->impdata_update (inp, out, step, data, ind0, ind1);
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
        for (j = 0; j < _nlevels; j++)
	{
            _convlev [j]->impdata_copy (inp1, out1, inp2, out2);
	}
    }
    catch (...)
    {
	cleanup ();
	return Converror::MEM_ALLOC;
    }
    return 0;
}


int Convproc::reset (void)
{
    unsigned int k;

    if (_state == ST_IDLE) return Converror::BAD_STATE;
    for (k = 0; k < _ninp; k++) memset (_inpbuff [k], 0, _inpsize * sizeof (float));
    for (k = 0; k < _nout; k++) memset (_outbuff [k], 0, _minpart * sizeof (float));
    for (k = 0; k < _nlevels; k++) _convlev [k]->reset (_inpsize, _minpart, _inpbuff, _outbuff);
    return 0;
}


int Convproc::start_process (int abspri, int policy)
{
    unsigned int k;

    if (_state != ST_STOP) return Converror::BAD_STATE;

    _latecnt = 0;
    _inpoffs = 0;
    _outoffs = 0;
    reset ();
    for (k = (_minpart == _quantum) ? 1 : 0; k < _nlevels; k++)
    {
         _convlev [k]->start (abspri, policy);
    }
    _state = ST_PROC;
    return 0;
}


int Convproc::process (bool sync)
{
    unsigned int k;
    int f = 0;

    if (_state != ST_PROC) return 0;
    
    _inpoffs += _quantum;
    if (_inpoffs == _inpsize) _inpoffs = 0;

    _outoffs += _quantum;
    if (_outoffs == _minpart)
    {
        _outoffs = 0;
	for (k = 0; k < _nout; k++) memset (_outbuff [k], 0, _minpart * sizeof (float));
	for (k = 0; k < _nlevels; k++) f |= _convlev [k]->readout (sync, _skipcnt);
	if (_skipcnt < _minpart) _skipcnt = 0;
	else _skipcnt -= _minpart;
        if (f)
	{
            if (++_latecnt >= 5)
            {
	        stop_process ();
	        f |= FL_LOAD;
	    }
	}
        else _latecnt = 0;
    }
    return f;
}


int Convproc::stop_process (void)
{
    unsigned int k;

    if (_state != ST_PROC) return Converror::BAD_STATE;
    for (k = 0; k < _nlevels; k++) _convlev [k]->stop ();
    _state = ST_WAIT;
    return 0;
}


int Convproc::cleanup (void)
{
    unsigned int k;

    while (! check_stop ())
    {
        usleep (100000);
    }
    if (_state != ST_STOP)
    {
        return Converror::BAD_STATE;
    }

    for (k = 0; k < _ninp; k++)
    {
        delete[] _inpbuff [k];
	_inpbuff [k] = 0;
    }
    for (k = 0; k < _nout; k++)
    {
        delete[] _outbuff [k];
	_outbuff [k] = 0;
    }
    for (k = 0; k < _nlevels; k++)
    {
	delete _convlev [k];
	_convlev [k] = 0;
    }

    _state = ST_IDLE;
    _options = 0;
    _skipcnt = 0;
    _density = 0;
    _ninp = 0;
    _nout = 0;
    _quantum = 0;
    _minpart = 0;
    _maxpart = 0;
    _nlevels = 0;
    _latecnt = 0;
    return 0;
}


bool Convproc::check_stop (void)
{
    unsigned int k;

    for (k = 0; (k < _nlevels) && (_convlev [k]->_stat == Convlevel::ST_IDLE); k++);
    if (k == _nlevels)
    {
	_state = ST_STOP;
	return true;
    }
    return false;
}


void Convproc::print (FILE *F)
{
    unsigned int k;

    for (k = 0; k < _nlevels; k++) _convlev [k]->print (F);
}



typedef float FV4 __attribute__ ((vector_size(16)));


Convlevel::Convlevel (void) :
    _stat (ST_IDLE),
    _npar (0),
    _parsize (0),
    _options (0),
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
			   unsigned int options)
{
    int fftwopt = (options & OPT_FFTW_MEASURE) ? FFTW_MEASURE : FFTW_ESTIMATE;

    _prio = prio;
    _offs = offs;
    _npar = npar;
    _parsize = parsize;
    _options = options;
    
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
#ifdef ENABLE_VECTOR_MODE
	    if (_options & OPT_VECTOR_MODE) fftswap (_freq_data);
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
#ifdef ENABLE_VECTOR_MODE
	    if (_options & OPT_VECTOR_MODE) fftswap (fftb);
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


void Convlevel::reset (unsigned int  inpsize,
                       unsigned int  outsize,
		       float         **inpbuff,
		       float         **outbuff)
{
    unsigned int  i;
    Inpnode      *X; 
    Outnode      *Y; 

    _inpsize = inpsize;
    _outsize = outsize;
    _inpbuff = inpbuff;
    _outbuff = outbuff;
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
    _wait = 0;
    _ptind = 0;
    _opind = 0;
    _trig.init (0, 0);
    _done.init (0, 0);
}


void Convlevel::start (int abspri, int policy)
{
    int                min, max;
    pthread_attr_t     attr;
    struct sched_param parm;

    _pthr = 0;
    min = sched_get_priority_min (policy);
    max = sched_get_priority_max (policy);
    abspri += _prio;
    if (abspri > max) abspri = max;
    if (abspri < min) abspri = min;
    parm.sched_priority = abspri;
    pthread_attr_init (&attr);
    pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
    pthread_attr_setschedpolicy (&attr, policy);
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
	_trig.post ();
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
        for (i = 0; i < _npar; i++) posix_memalign_free (X->_ffta [i]);
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
                    posix_memalign_free (M->_fftb [i]);
		}
	        delete[] M->_fftb;
	    }
	    M1 = M->_next;
	    delete M;
	    M = M1;
	}
	for (i = 0; i < 3; i++) posix_memalign_free (Y->_buff [i]);
	Y1 = Y->_next;
	delete Y;
	Y = Y1;
    }
    _out_list = 0;

    fftwf_destroy_plan (_plan_r2c);
    fftwf_destroy_plan (_plan_c2r);
    posix_memalign_free (_time_data);
    posix_memalign_free (_prep_data);
    posix_memalign_free (_freq_data);
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
	_trig.wait ();
	if (_stat == ST_TERM)
	{
            _stat = ST_IDLE;
	    _pthr = 0;
            return;
        }
	process (false);
	_done.post ();
    }
}


void Convlevel::process (bool skip)
{
    unsigned int    i, j, k;
    unsigned int    i1, n1, n2, opi1, opi2;

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

    opi1 = (_opind + 1) % 3;
    opi2 = (_opind + 2) % 3;

    for (X = _inp_list; X; X = X->_next)
    {
	inpd = _inpbuff [X->_inp];
	if (n1) memcpy (_time_data, inpd + i1, n1 * sizeof (float));
	if (n2) memcpy (_time_data + n1, inpd, n2 * sizeof (float));
	memset (_time_data + _parsize, 0, _parsize * sizeof (float));
	fftwf_execute_dft_r2c (_plan_r2c, _time_data, X->_ffta [_ptind]);
#ifdef ENABLE_VECTOR_MODE
	if (_options & OPT_VECTOR_MODE) fftswap (X->_ffta [_ptind]);
#endif
    }

    if (skip)
    {
        for (Y = _out_list; Y; Y = Y->_next)
	{
	    outd = Y->_buff [opi2];
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
		i = _ptind;
		for (j = 0; j < _npar; j++)
		{
		    ffta = X->_ffta [i];
		    fftb = M->_fftb [j];
		    if (fftb)
		    {
#ifdef ENABLE_VECTOR_MODE
			if (_options & OPT_VECTOR_MODE)
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

#ifdef ENABLE_VECTOR_MODE
	    if (_options & OPT_VECTOR_MODE) fftswap (_freq_data);
#endif
	    fftwf_execute_dft_c2r (_plan_c2r, _freq_data, _time_data);
	    outd = Y->_buff [opi1];
	    for (k = 0; k < _parsize; k++) outd [k] += _time_data [k];
	    outd = Y->_buff [opi2];
	    memcpy (outd, _time_data + _parsize, _parsize * sizeof (float));
	}
    }

    _ptind++;
    if (_ptind == _npar) _ptind = 0;
}


int Convlevel::readout (bool sync, unsigned int skipcnt)
{
    unsigned int  i;
    float         *p, *q;	
    Outnode       *Y;

    _outoffs += _outsize;
    if (_outoffs == _parsize)
    {
	_outoffs = 0;
	if (_stat == ST_PROC)
	{
   	    while (_wait)
	    {
		if (sync) _done.wait ();
		else if (_done.trywait ()) break;
  	        _wait--;
	    }
	    if (++_opind == 3) _opind = 0;
            _trig.post ();
	    _wait++;
	}
        else
	{
            process (skipcnt >= 2 * _parsize);
	    if (++_opind == 3) _opind = 0;
	}
    }

    for (Y = _out_list; Y; Y = Y->_next)
    {
        p = Y->_buff [_opind] + _outoffs;
        q = _outbuff [Y->_out];
        for (i = 0; i < _outsize; i++) q [i] += p [i];
    }

    return (_wait > 1) ? _bits : 0;
}


void Convlevel::print (FILE *F)
{
    fprintf (F, "prio = %4d, offs = %6d,  parsize = %5d,  npar = %3d\n", _prio, _offs, _parsize, _npar);
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


#ifdef ENABLE_VECTOR_MODE

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



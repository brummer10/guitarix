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


#ifndef _ZITA_CONVOLVER_H
#define _ZITA_CONVOLVER_H


#include <pthread.h>
#include <fftw3.h>


#define ZITA_CONVOLVER_MAJOR_VERSION 3


extern int zita_convolver_major_version (void);


// ----------------------------------------------------------------------------


#ifdef ZCSEMA_IS_IMPLEMENTED
#undef ZCSEMA_IS_IMPLEMENTED
#endif

#ifndef __APPLE__
#include <semaphore.h>

class ZCsema
{
public:

    ZCsema (void) { init (0, 0); }
    ~ZCsema (void) { sem_destroy (&_sema); }

    ZCsema (const ZCsema&); // disabled
    ZCsema& operator= (const ZCsema&); // disabled

    int init (int s, int v) { return sem_init (&_sema, s, v); }
    int post (void) { return sem_post (&_sema); }
    int wait (void) { return sem_wait (&_sema); }
    int trywait (void) { return sem_trywait (&_sema); }

private:

    sem_t  _sema;
};

#define ZCSEMA_IS_IMPLEMENTED


#else

// NOTE:  ***** I DO NOT REPEAT NOT PROVIDE SUPPORT FOR OSX *****
// 
// The following code partially emulates the POSIX sem_t for which
// OSX has only a crippled implementation. It may or may not compile,
// and if it compiles it may or may not work correctly. Blame APPLE
// for not following POSIX standards.

class ZCsema
{
public:

    ZCsema (void) : _count (0)
    {
        init (0, 0);
    }

    ~ZCsema (void)
    {
        pthread_mutex_destroy (&_mutex);
        pthread_cond_destroy (&_cond);
    }

    ZCsema (const ZCsema&); // disabled
    ZCsema& operator= (const ZCsema&); // disabled

    int init (int s, int v)
    {
	_count = v;
        return pthread_mutex_init (&_mutex, 0) || pthread_cond_init (&_cond, 0);
    }

    int post (void)
    {
	pthread_mutex_lock (&_mutex);
	_count++;
	if (_count == 1) pthread_cond_signal (&_cond);
	pthread_mutex_unlock (&_mutex);
	return 0;
    }

    int wait (void)
    {
	pthread_mutex_lock (&_mutex);
	while (_count < 1) pthread_cond_wait (&_cond, &_mutex);
	_count--;
	pthread_mutex_unlock (&_mutex);
	return 0;
    }

    int trywait (void)
    {
	if (pthread_mutex_trylock (&_mutex)) return -1;
	if (_count < 1)
	{
	    pthread_mutex_unlock (&_mutex);
	    return -1;
	}
        _count--;
        pthread_mutex_unlock (&_mutex);
        return 0;
    }

private:

    int              _count;
    pthread_mutex_t  _mutex;
    pthread_cond_t   _cond;
};

#define ZCSEMA_IS_IMPLEMENTED
#endif


#ifndef ZCSEMA_IS_IMPLEMENTED
#error "The ZCsema class is not implemented."
#endif


// ----------------------------------------------------------------------------


class Inpnode   
{
private:

    friend class Convlevel;

    Inpnode        *_next;
    fftwf_complex **_ffta;
    unsigned int    _inp;
};


class Macnode  
{
private:

    friend class Convlevel;

    Macnode        *_next;
    Inpnode        *_inpn;
    fftwf_complex **_fftb;
    bool            _copy;
};


class Outnode   
{
private:

    friend class Convlevel;

    Outnode        *_next;
    Macnode        *_list;
    float          *_buff [3];
    unsigned int    _out;
};


class Converror
{
public:

    enum
    {
	BAD_STATE = -1,
	BAD_PARAM = -2,
        MEM_ALLOC = -3
    };

private:

    friend class Convlevel;
    friend class Convproc;

    Converror (int error) : _error (error) {}

    int _error;
};


class Convlevel
{
private:

    friend class Convproc;

    enum 
    {
        OPT_FFTW_MEASURE = 1,
        OPT_VECTOR_MODE  = 2
    };

    enum
    {
        ST_IDLE,
        ST_TERM,
        ST_PROC
    };

    Convlevel (void);
    ~Convlevel (void);

    void *alloc_aligned (size_t size);

    void configure (int prio,
                    unsigned int offs,
                    unsigned int npar,
                    unsigned int parsize,
		    unsigned int options);

    void impdata_create (unsigned int inp,
                         unsigned int out,
                         unsigned int step,
                         float *data,
                         int ind0,
                         int ind1); 

    void impdata_update (unsigned int inp,
                         unsigned int out,
                         unsigned int step,
                         float *data,
                         int ind0,
                         int ind1); 

    void impdata_copy (unsigned int inp1,
                       unsigned int out1,
                       unsigned int inp2,
                       unsigned int out2);

    void reset (unsigned int inpsize,
                unsigned int outsize,
	        float **inpbuff,
	        float **outbuff);

    void start (int absprio, int policy);

    void process (bool sync);

    int  readout (bool sync, unsigned int skipcnt);

    void stop (void);

    void cleanup (void);

    void fftswap (fftwf_complex *p);

    void print (FILE *F);

    static void *static_main (void *arg);

    void main (void);

    Macnode *findmacnode (unsigned int inp, unsigned int out, bool create);

    volatile unsigned int _stat;           // current processing state
    int                   _prio;           // relative priority
    unsigned int          _offs;           // offset from start of impulse response
    unsigned int          _npar;           // number of partitions
    unsigned int          _parsize;        // partition and output buffer size
    unsigned int          _outsize;        // step size for output buffer
    unsigned int          _outoffs;        // offset into output buffer
    unsigned int          _inpsize;        // size of shared input buffer 
    unsigned int          _inpoffs;        // offset into input buffer
    unsigned int          _options;        // various options
    unsigned int          _ptind;          // rotating partition index
    unsigned int          _opind;          // rotating output buffer index
    int                   _bits;           // bit identifiying this level
    int                   _wait;           // number of unfinished cycles
    pthread_t             _pthr;           // posix thread executing this level
    ZCsema                _trig;           // sema used to trigger a cycle
    ZCsema                _done;           // sema used to wait for a cycle
    Inpnode              *_inp_list;       // linked list of active inputs
    Outnode              *_out_list;       // linked list of active outputs
    fftwf_plan            _plan_r2c;       // FFTW plan, forward FFT
    fftwf_plan            _plan_c2r;       // FFTW plan, inverse FFT
    float                *_time_data;      // workspace
    float                *_prep_data;      // workspace
    fftwf_complex        *_freq_data;      // workspace
    float               **_inpbuff;        // array of shared input buffers
    float               **_outbuff;        // array of shared output buffers
};


// ----------------------------------------------------------------------------


class Convproc
{
public:

    Convproc (void);
    ~Convproc (void);

    enum
    {
        ST_IDLE,
	ST_STOP,
        ST_WAIT,
        ST_PROC
    };

    enum
    {
        FL_LATE = 0x0000FFFF,
	FL_LOAD = 0x01000000
    };

    enum 
    {
        OPT_FFTW_MEASURE = Convlevel::OPT_FFTW_MEASURE, 
        OPT_VECTOR_MODE  = Convlevel::OPT_VECTOR_MODE
    };

    enum
    {
	MAXINP   = 64,
	MAXOUT   = 64,
	MAXLEV   = 8,
	MINPART  = 64,
	MAXPART  = 8192,
	MAXDIVIS = 16,
	MINQUANT = 16,
	MAXQUANT = 8192
    };

    unsigned int state (void) const
    {
	return _state;
    }

    float *inpdata (unsigned int inp) const
    {
	return _inpbuff [inp] + _inpoffs;
    }

    float *outdata (unsigned int out) const
    {
	return _outbuff [out] + _outoffs;
    }

    void set_density (float density);

    void set_options (unsigned int options);

    void set_skipcnt (unsigned int skipcnt);

    int configure (unsigned int ninp,
                   unsigned int nout,
                   unsigned int maxsize,
                   unsigned int quantum,
                   unsigned int minpart,
                   unsigned int maxpart);

    int impdata_create (unsigned int inp,
                        unsigned int out,
                        unsigned int step,
                        float       *data,
                        int          ind0,
                        int          ind1); 

    int impdata_update (unsigned int inp,
                        unsigned int out,
                        unsigned int step,
                        float       *data,
                        int          ind0,
                        int          ind1); 

    int impdata_copy (unsigned int inp1,
                      unsigned int out1,
                      unsigned int inp2,
                      unsigned int out2);

    int reset (void);

    int start_process (int abspri, int policy);

    int process (bool sync = false);

    int stop_process (void);

    bool check_stop (void);

    int cleanup (void);

    void print (FILE *F = stdout);

    static float _mac_cost;
    static float _fft_cost;

private:

    unsigned int    _state;                   // current state
    float          *_inpbuff [MAXINP];        // input buffers
    float          *_outbuff [MAXOUT];        // output buffers
    unsigned int    _inpoffs;                 // current offset in input buffers
    unsigned int    _outoffs;                 // current offset in output buffers
    unsigned int    _options;                 // option bits
    unsigned int    _skipcnt;                 // number of frames to skip 
    float           _density;                 // matrix density hint
    unsigned int    _ninp;                    // number of inputs
    unsigned int    _nout;                    // number of outputs
    unsigned int    _quantum;                 // processing block size
    unsigned int    _minpart;                 // smallest partition size
    unsigned int    _maxpart;                 // largest allowed partition size
    unsigned int    _nlevels;                 // number of partition sizes
    unsigned int    _inpsize;                 // size of input buffers
    unsigned int    _latecnt;                 // count of cycles ending too late
    Convlevel      *_convlev [MAXLEV];        // array of processors 
    void           *_dummy [64];
};


// ----------------------------------------------------------------------------


#endif


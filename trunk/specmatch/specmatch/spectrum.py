#! /usr/bin/python
# -*- coding: utf-8 -*-

import numpy as np
import numpy.fft as fft
import scipy.signal as sig
from scipy.interpolate import LSQUnivariateSpline

def clipdb(s, cutoff):
    """
    Clip magnitude of s at its maximum + cutoff in dB.
    Example: clip(s,-100) makes sure the minimum magnitude
    of s is not more than 100dB below its maximum magnitude.
    If s is zero, nothing is done.
    """
    if cutoff >= 0:
        return s
    ss = abs(s)
    mas = np.amax(ss)
    if mas == 0:
        return s
    thresh = mas * 10**(float(cutoff) / 20)  # db to linear
    return np.where(ss >= thresh, s, thresh)

def fold(r):
    """Fold left wing of vector in "FFT buffer format" onto right wing"""
    n = len(r)
    if n < 3:
        return r
    if n % 2 == 1:
        nt = (n+1)/2
        rt = r[:,:]
        rt[1:nt,:] += np.conj(r[n-1:nt-1:-1,:])
        rt[nt:,:] = 0
        return rt
    else:
        nt = n/2
        rt = r[:,:]
        rt[1:nt,:] += np.conj(r[n-1:nt:-1,:])
        rt[nt+1:,:] = 0
        return rt

def r2c_fft(a, n=None):
    if n is None:
        n = 2*(len(a)-1)
    if n & 1:
        return np.append(a, np.conj(a[-1:0:-1]), axis=0)
    else:
        return np.append(a, np.conj(a[-2:0:-1]), axis=0)

def mps(s, n=0, clip=-100):
    """
    create minimum-phase spectrum from complex spectrum s, use hanning window
    to mask out higher "quefrencys" in the cepstrum.
    https://ccrma.stanford.edu/~jos/filters/Creating_Minimum_Phase_Filters.html
    http://www.dsprelated.com/dspbooks/sasp/Spectral_Envelope_Cepstral_Windowing.html
    """
    clip=-100
    cp = fft.ifft(np.log(clipdb(s,clip)),axis=0)
    if n:
        n = min(n, len(s))
        nh = n // 2
        if n & 1:
            cp = np.append(cp[:nh+1], cp[-nh:], axis=0)
        else:
            cp[-nh,:] = 0
            cp = np.append(cp[:nh], cp[-nh:], axis=0)
    cp = fold(cp)
    r = np.exp(fft.fft(cp, axis=0))
    return r

def fftfreq2(n, T):
    return abs(fft.fftfreq(n, T)[:n//2+1])

def fft2spectrum(f):
    return 20*np.log10(abs(f[:len(f)//2+1]))

def spectrum2fft(y, n=None):
    if n is None:
        n = 2*(len(y)-1)
    return r2c_fft(10**(y/20))


class SmoothSpectrumSpline(object):

    def __init__(self, x, y, rate, nk=100, start=2.0):
        nk = round(100 * np.log(rate)/np.log(44100))
        knots = np.exp(np.linspace(np.log(start), np.log(x[-1]), nk, False))
        self.spl = []
        for i in range(y.shape[1]):
            self.spl.append(LSQUnivariateSpline(x, y[:,i], knots))

    def __call__(self, v, d=0, chan=-1):
        if chan == -1:
            try:
                n = len(v)
            except TypeError:
                n = 1
            a = np.empty((n, len(self.spl)))
            for i, s in enumerate(self.spl):
                a[:,i] = s(v, d)
            return a
        else:
            return self.spl[chan](v, d)


################################################################
# class SmoothedIR
#

class SmoothedIR(object):

    def __init__(self, f1, f2, lim, rate, nk=100, start=2.0):
        self.rate = rate

        # smoothed spline for f1
        y1 = fft2spectrum(f1)
        x = abs(fft.fftfreq(len(f1), 1.0/rate)[:len(y1)])  # abs: last element is -rate/2
        s1 = SmoothSpectrumSpline(x, y1, rate, nk, start)
        sf1 = s1(x)
        l1 = lim + np.amax(sf1, axis=0)

        # smoothed spline for f2
        y2 = fft2spectrum(f2)
        s2 = SmoothSpectrumSpline(x, y2, rate, nk, start)
        sf2 = s2(x)
        l2 = lim + np.amax(sf2, axis=0)

        # quotient
        yq = fft2spectrum(f1/f2)
        sq = SmoothSpectrumSpline(x, yq, rate, nk, start)

        # find invalid ranges
        valid = np.array((sf1 > l1) * (sf2 > l2), dtype=int)

        # calculate piecewise
        self.calc = []
        for i in range(valid.shape[1]):
            val = valid[:,i]
            sqm = lambda x, d=0, chan=i: sq(x, d, chan=chan)
            r = np.nonzero(np.diff(val, axis=0))[0]
            start = 0
            l = []
            for p in np.append(r, len(val)-1):
                if val[start]:
                    f = sqm
                else:
                    if start == 0:
                        f = self.startslope(sqm, x, p)
                    elif p == len(val)-1:
                        f = self.endslope(sqm, x, start)
                    else:
                        f = self.segment(sqm, x, start, p)
                p += 1
                l.append((x[start], x[p] if p < len(val) else None, val[start], f))
                start = p
            self.calc.append(l)

    def startslope(self, sq, x, p):
        x0 = x[0]
        x1 = x[p+1]
        y1 = sq(x1)
        dy1 = sq(x1, 1)
        s = 2
        h = x1 - x0
        p = [(dy1 - s)/(3*h**2), 0, s, -h*s - h*(dy1 - s)/3 + y1]
        def calc_startslope(v):
            return np.polyval(p, v-x0)
        return calc_startslope

    def endslope(self, sq, x, start):
        log = np.log
        x0 = x[start]
        y0 = sq(x0)
        dy0 = sq(x0, 1)*x0
        x1 = x[-1]
        s = -5
        h = x1 / x0
        p = [(dy0 + h*s*log(h) - h*s)/(3*log(h)**2), -(2*dy0 + h*s*log(h) - 2*h*s)/(2*log(h)), dy0, y0]
        def calc_endslope(v):
            return np.polyval(p, log(v/x0))
        return calc_endslope

    def segment(self, sq, x, start, p):
        x0 = x[start]
        y0 = sq(x0)
        dy0 = sq(x0, 1)
        x1 = x[p+1]
        y1 = sq(x1)
        dy1 = sq(x1, 1)
        h = x1 - x0
        p = [(dy0*h + dy1*h + 2*y0 - 2*y1)/h**3, (-2*dy0*h - dy1*h - 3*y0 + 3*y1)/h**2, dy0, y0]
        def calc_segment(v):
            return np.polyval(p, v-x0)
        return calc_segment

    def get_indexlist(self, x, channel, valid):
        l = []
        for v in self.calc[channel]:
            if bool(v[2]) != bool(valid):
                continue
            s = x.searchsorted(v[0])
            e = v[1]
            if e is None:
                e = len(x)
            else:
                e = x.searchsorted(e)
            l.append(np.arange(s,e))
        if not l:
            return np.arange(0)
        else:
            return np.concatenate(l)

    def get_ir(self, sz, wd=50):
        x = fftfreq2(sz, 1.0/self.rate)
        ir = np.real(fft.ifft(mps(spectrum2fft(self(x)),0,0),axis=0))
        if wd:
            w = sig.hamming(2*wd)[-wd:]
            for i in range(ir.shape[1]):
                ir[-wd:,i] *= w
        return ir

    def __call__(self, x):
        res = []
        n = len(x)
        for l in self.calc:
            r = np.empty(n)
            for start, end, val, f in l:
                start = np.searchsorted(x, start)
                if end is not None:
                    end = np.searchsorted(x, end)
                r[start:end] = f(x[start:end])
            res.append(r)
        if len(res) == 1:
            return res[0].reshape((n,1))
        else:
            return np.vstack(res).T


def pow2roundup(x):
    "return smallest 2**Y which is >= x (with x < 2**32)"
    if x <= 0:
        return 0
    x -= 1
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x+1;


class CalcIR(object):
    """
    calculates the IR

    The variables are defined as class properties to get deferred calculation.
    Audio signals (a1, a2) have the numpy shape (nframes, channels)
    The formulas are:

    a1: the reference signal
    a2: recorded Guitarix output signal (without IR)

    n = pow2roundup(max(len(a1), len(a2)))
    f1 = fft(a1, n, axis=0)
    f2 = fft(a2, n, axis=0)
    f3 = mps(f1/f2, sz, 0)
    ir = real(ifft(f3, axis=0))
    """

    def __init__(self, status, rate, compute, orig_ir):
        self.status = status
        self.rate = rate
        self.orig_ir = orig_ir
        self.compute = compute
        self._recorded_sound = None
        self._original_sound_file = None
        self._original_range = (None, None)
        self._original_mode = -1
        self.ir_smoother = None
        self._a1 = self._a2 = self._sz = self._irfile = self._sound = None
        self._n = self._f1 = self._f2 = self._ir = None
        self._cutoff = None

    def read_sndfile(self):
        f = self.original_sound_file
        s, e = self.original_range
        if s is None:
            s = 0
        else:
            s = min(f.nframes-1, s * f.samplerate)
        if e is None:
            e = f.nframes
        else:
            e = min(f.nframes, e * f.samplerate)
        n = e - s
        if n <= 0:
            n = 1
        f.seek(s)
        a = f.read_frames(n)
        channel = self.original_mode
        if f.channels > 1 and channel >= -1:
            if channel < 0:
                a = np.sum(a, axis=1)
            else:
                a = a[:, channel]
        if len(a.shape) == 1:
            a = a.reshape((len(a), 1))
        return a

    @property
    def original_sound_file(self):
        return self._original_sound_file
    @original_sound_file.setter
    def original_sound_file(self, n):
        self._original_sound_file = n
        self.a1 = None

    @property
    def original_range(self):
        return self._original_range
    @original_range.setter
    def  original_range(self, rng):
        rng = tuple(rng)
        if self._original_range != rng:
            self._original_range = rng
            self.a1 = None

    @property
    def original_mode(self):
        return self._original_mode
    @original_mode.setter
    def original_mode(self, v):
        self._original_mode = v
        self.a1 = None

    @property
    def a1(self):
        if self._a1 is None:
            if self.orig_ir is None:
                self.a1 = self.read_sndfile()
            else:
                self.a1 = self.compute(self.recorded_sound, self.orig_ir)
        return self._a1
    @a1.setter
    def a1(self, v):
        self._a1 = v
        self.f1 = None

    @property
    def recorded_sound(self):
        return self._recorded_sound
    @recorded_sound.setter
    def recorded_sound(self, v):
        self._recorded_sound = v
        self.a2 = None

    @property
    def a2(self):
        if self._a2 is None:
            self.status("recording Guitarix output")
            self.a2 = self.compute(self.recorded_sound)
            #write_sndfile(self.a2, "proc.flac", self.rate, "pcm24")
            #self.a2 = self.recorded_sound
            self.status.clear()
        return self._a2
    @a2.setter
    def a2(self, v):
        self._a2 = v
        self.f2 = None

    @property
    def sz(self):
        return self._sz
    @sz.setter
    def sz(self, v):
        self._sz = v
        self.ir = None

    @property
    def cutoff(self):
        return self._cutoff
    @cutoff.setter
    def cutoff(self, v):
        self._cutoff = v
        self._ir = None

    @property
    def n(self):
        if self._n is None:
            self.n = pow2roundup(max(len(self.a1), len(self.a2)))
        return self._n
    @n.setter
    def n(self, v):
        self._n = v

    @property
    def f1(self):
        if self._f1 is None:
            self.status("FFT of original")
            self.f1 = fft.fft(self.a1, self.n, axis=0)
            self.status.clear()
        return self._f1
    @f1.setter
    def f1(self, v):
        self._f1 = v
        self.n = None
        self.ir = None

    @property
    def f2(self):
        if self._f2 is None:
            self.status("FFT of recording")
            self.f2 = fft.fft(self.a2, self.n, axis=0)
            self.status.clear()
        return self._f2
    @f2.setter
    def f2(self, v):
        self._f2 = v
        self.n = None
        self.ir = None

    @property
    def ir(self):
        if self._ir is None:
            self.status("minimum phase filter")
            #self.ir = np.real(fft.ifft(mps(self.f1/self.f2, self.sz, 0), axis=0))
            self.ir_smoother = SmoothedIR(self.f1, self.f2, self.cutoff, self.rate)
            self.ir = self.ir_smoother.get_ir(self.sz)
            self.status.clear()
        return self._ir
    @ir.setter
    def ir(self, v):
        self._ir = v
        self._irfile = None
        self._sound = None

    def invalidate_guitarix_output(self):
        self.a2 = None
        if self.orig_ir is not None:
            self.a1 = None

    def irfile_changed(self):
        i = self._irfile
        self._irfile = True
        return i

    @property
    def sound(self):
        if self._sound is None:
            self.status("generating sound")
            rlen = len(self.a2)+len(self.ir)
            n = pow2roundup(rlen)
            f = fft.fft(self.ir, n, axis=0)
            self._sound = np.real(fft.ifft(fft.fft(self.a2,n,axis=0)*f,axis=0))[:rlen]
            self.status.clear()
        return self._sound

    def sound_ready(self):
        return self._sound is not None

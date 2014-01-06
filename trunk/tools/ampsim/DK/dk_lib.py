from __future__ import division
import contextlib, math
import numpy as np
import numpy.core.arrayprint as npap

class CircuitException(Exception):
    pass

# http://stackoverflow.com/questions/2891790/pretty-printing-of-numpy-array
@contextlib.contextmanager
def printoptions(strip_zeros=True, **kwargs):
    """Context manager to apply Numpy printoptions locally.

    Example usage:
    >>> x = np.array([0.078, 0.480, 0.413, 0.830, 0.776])
    >>> with printoptions(precision=3, suppress=True, strip_zeros=False):
            print(x)

    """
    origcall = npap.FloatFormat.__call__
    def __call__(self, x, strip_zeros=strip_zeros):
        return origcall.__call__(self, x, strip_zeros)
    npap.FloatFormat.__call__ = __call__
    original = np.get_printoptions()
    np.set_printoptions(**kwargs)
    yield
    np.set_printoptions(**original)
    npap.FloatFormat.__call__ = origcall

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

def genlogsweepX(fmin, fmax, rate, k0, k1, k2, dtype=np.float64):
    """generate logarithmic sweep signal
    
    fmin: start frequency
    fmax: end frequency
    rate: sample rate
    k0: fade in before start of signal (samples)
    k1: length of signal (samples)
    k2: fade out after end of signal (samples)
    dtype: data type of signal

    returns: (logsweep signal, inverse logsweep signal)
    """
    s1 = np.empty(k0 + k1 + k2, dtype=dtype)
    s2 = np.empty_like(s1)
    b = math.log(fmax / fmin) / k1
    a = fmin / (b * rate)
    q0 = a * math.exp(-b * k0)
    def sweep(t, g=None):
        q = a * np.exp(b * t)
        p = q - q0
        x = np.sin(2 * np.pi * (p - np.floor(p)))
        if g is not None:
            x *= g
        return x, x * q
    if k0:
        t = np.arange(-k0,0)
        s1[:k0], s2[:k0] = sweep(t, np.cos(0.5 * np.pi * t / k0))
    t = np.arange(k1)
    s1[k0:k0+k1], s2[k0:k0+k1] = sweep(t)
    if k2:
        t = np.arange(k1,k1+k2)
        s1[k0+k1:], s2[k0+k1:] = sweep(t, np.sin(0.5 * np.pi * (k1 + k2 - t) / k2))
    s2 = s2[::-1] * 4 * b * b
    return s1, s2, fmin, fmax, k1 / math.log(fmax / fmin)

def genlogsweep(fmin, fmax, rate, k0, k1, k2, dtype=np.float64):
    nyq = rate / 2
    if fmax <= fmin:
        fmax = nyq
    p = np.ceil(np.log2(nyq / fmin)) + 1
    #p1 = np.floor(np.log2(nyq / fmax))
    p1 = 0
    ep = 2 ** p
    fmin = nyq / ep
    fmax = nyq / (2 ** p1)
    lep = np.log(ep)
    L1 = 2 * ep * lep
    L = np.ceil(k1 / L1) * L1
    N = np.ceil(L)
    NN = np.ceil(L - p1 * N / p)
    epN = 2 ** (p/N)
    n = np.arange(NN)
    pp = L / L1 * epN**n
    s = np.sin(2 * np.pi * pp)
    #if k0:
    #    nn = int(round(N/p))
    #    s[:nn] = s[:nn] * np.hanning(2*nn)[:nn]
    si = 2/N * lep * s[::-1] / epN**n
    if p1:
        si *= 2 ** -p1
    return s, si, fmin, fmax, N / lep

def fft_convolve(h, xd, invert=False):
    n = len(h) + len(xd) - 1
    n2 = pow2roundup(n)
    H = np.fft.rfft(h[2:], n2, axis=0)
    XD = np.fft.rfft(xd, n2, axis=0)
    if len(XD.shape) == 2 and len(H.shape) == 1:
        H = H.reshape(len(H), 1)
    if invert:
        XD /= H
    else:
        XD *= H
    s = np.fft.irfft(XD, n2, axis=0)
    return s[:n]

def calc_grid(func, grd, nvals):
    grd_shape = grd.shape
    numpoints = np.product(grd_shape[1:])
    grd = grd.reshape(grd_shape[0], numpoints)
    fnc = func(grd.T).T
    return fnc.reshape((nvals,)+grd_shape[1:])

def mkgrid(axeslist):
    if len(axeslist) > 1:
        grd = np.array(np.meshgrid(*axeslist, indexing='ij'))
    else:
        grd = np.empty((1, len(axeslist[0])))
        grd[0] = axeslist[0]
    return grd

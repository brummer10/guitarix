from __future__ import division
import sympy, numpy, types, math
import dk_lib
import pylab, scipy.signal

class GeneratedSignal(object):

    def __init__(self, func, op, fs, freq, start_freq, stop_freq):
        self.op = op
        self.fs = fs
        self.freq = freq
        self.start_freq = start_freq
        self.stop_freq = stop_freq
        self.generate_spectrum = False
        self.generate_harmonics = False
        self.make_spectrum = self._default_make_spectrum
        m = [dict(sweep = self._sweep, impulse = self._impulse, time = self._time, null=self._null, asin=numpy.arcsin, atan=numpy.arctan), numpy]
        self.signal = sympy.lambdify((), func, modules=m)()
        samples = len(self.signal)
        self.input_signal = numpy.array((op,), dtype=numpy.float64).repeat(samples, axis=0)
        for i in range(self.input_signal.shape[1]):
            self.input_signal[:,i] = self.signal
        self.timeline = numpy.linspace(0, samples/fs, samples)

    def _sweep_make_spectrum(self, response, freqlist, shift=True):
        return self._sweep_harmonics_responses(response, 1, freqlist, shift)[0]

    @staticmethod
    def _fft_convolve(h, xd):
        n = len(h) + len(xd) - 1
        np = dk_lib.pow2roundup(n)
        if len(xd.shape) == 2 and len(h.shape) == 1:
            h = h.reshape((len(h), 1))
        s = numpy.fft.irfft(numpy.fft.rfft(h, np, axis=0) * numpy.fft.rfft(xd, np, axis=0), np, axis=0)
        return s[:n]

    def _sweep_harmonics_responses(self, response, N, freqlist, shift=True):
        di = self._fft_convolve(self.sweep_inverse_signal, response)  # deconvolved impulse response
        imp_indices = numpy.zeros(N+1, dtype=int)  # the indices of each impulse (1st linear, 2nd the first harm. dist. etc.)
        imp_indices[0] = len(self.sweep_inverse_signal) - 1
        for n in range(1, N+1):
            imp_indices[n] = imp_indices[0] - int(round(math.log(n+1) * self.sweep_rate))
        imps = []
        for n in range(N):
            dl = (imp_indices[n] - imp_indices[n+1]) // 2
            lo = imp_indices[n] - dl  # the low limit where to cut
            hi = imp_indices[n] + dl  # the high limit where to cut
            di_w = di[lo:hi]
            win = numpy.blackman(len(di_w))
            if len(di.shape) == 2:
                win = win.reshape((len(win), 1))
            di_w *= win  # smoothed version
            w = freqlist
            if shift:
                w = w * (n + 1)
            h = scipy.signal.freqz(di_w, worN=w)[1]
            off = imp_indices[n] - lo
            h *= numpy.exp(off * 1j * freqlist)
            imps.append(h)
        return imps

    def _sweep(self, t, start, stop, pre, post, fs):
        self.generate_spectrum = True
        self.generate_harmonics = True
        self.make_spectrum = self._sweep_make_spectrum
        self.make_harmonics_responses = self._sweep_harmonics_responses
        post = int(round(post * fs))
        if pre < 0:
            pre = int(round((len(t) - post) * 0.1))
        else:
            pre = int(round(pre * fs))
        span = len(t) - (pre + post)
        self.pre = pre
        self.post = post
        self.fs = fs
        sig, self.sweep_inverse_signal, self.start, self.stop, self.sweep_rate = \
          dk_lib.genlogsweep(start, stop, fs, pre, span, post)
        return sig

    def _impulse_make_spectrum(self, response, freqlist):
        return scipy.signal.freqz(response, worN=freqlist)[1]

    def _impulse(self, t):
        self.generate_spectrum = True
        self.make_spectrum = self._impulse_make_spectrum
        a = numpy.zeros_like(t)
        a[0] = 1
        return a

    def _time(self, samples, fs):
        return numpy.linspace(0, samples/fs, samples)

    def _null(self, s):
        return 0*s

    def _default_make_spectrum(self, response, freqlist):
        n = dk_lib.pow2roundup(len(response))
        return numpy.fft.rfft(response, n, axis=0)

    def has_spectrum(self):
        return self.generate_spectrum

    def get_spectrum(self, response, freqlist, **kw):
        return self.make_spectrum(response, freqlist, **kw)

    def has_harmonics(self):
        return self.generate_harmonics

    def get_harmonics_responses(self, response, N, freqlist, shift=True):
        return self.make_harmonics_responses(response, N, freqlist, shift)

    def _plot_setup(self, lower_freq, upper_freq, plotfunc, freqlist):
        if lower_freq is None:
            lower_freq = self.start_freq
        if upper_freq is None:
            upper_freq = self.stop_freq
        if plotfunc is None:
            plotfunc = pylab.semilogx
        if isinstance(freqlist, int):
            freqlist = numpy.logspace(numpy.log10(lower_freq), numpy.log10(upper_freq), freqlist)
        return lower_freq, upper_freq, plotfunc, freqlist

    def plot_spectrum(self, response, lower_freq=None, upper_freq=None, plotfunc=None, freqlist=200):
        lower_freq, upper_freq, plotfunc, freqlist = self._plot_setup(lower_freq, upper_freq, plotfunc, freqlist)
        h = self.get_spectrum(response, 2 * numpy.pi * freqlist / self.fs)
        return plotfunc(freqlist, 20 * numpy.log10(abs(h)))

    def plot_harmonic_spectrum(self, response, nharmonics=6, lower_freq=None, upper_freq=None, plotfunc=None, freqlist=200):
        lower_freq, upper_freq, plotfunc, freqlist = self._plot_setup(lower_freq, upper_freq, plotfunc, freqlist)
        lines = []
        for i, h in enumerate(self.get_harmonics_responses(response, nharmonics, 2*numpy.pi*freqlist/self.fs)):
            if h.size:
                lines.extend(plotfunc(freqlist, 20 * numpy.log10(abs(h))))
        return lines


class Signal(object):

    _s_FS, _s_freq, _s_start_freq, _s_stop_freq, _s_sweep_pre, _s_sweep_post, _s_samples = sympy.symbols(
        "FS, freq, start_freq, stop_freq, sweep_pre, sweep_post, samples")
    _s_sweep, _s_impulse, _s_time, _s_null = sympy.symbols("sweep,impulse,time,null", cls=sympy.Function)
    t = sympy.symbols("t")

    def __init__(self, timespan=0.01):
        self._freq = 440
        self._start_freq = 20
        self._stop_freq = 10000
        self._timespan = timespan
        self._sweep_pre = -1
        self._sweep_post = 0.1

    @property
    def freq(self):
        return self._freq
    @freq.setter
    def freq(self, v):
        self._freq = v

    @property
    def start_freq(self):
        return self._start_freq
    @start_freq.setter
    def start_freq(self, v):
        self._start_freq = v

    @property
    def stop_freq(self):
        return self._stop_freq
    @stop_freq.setter
    def stop_freq(self, v):
        self._stop_freq = v

    @property
    def timespan(self):
        return self._timespan
    @timespan.setter
    def timespan(self, v):
        self._timespan = v

    @property
    def sweep_pre(self):
        return self._sweep_pre
    @sweep_pre.setter
    def sweep_pre(self, v):
        self._sweep_pre = v

    @property
    def sweep_post(self):
        return self._sweep_post
    @sweep_post.setter
    def sweep_post(self, v):
        self._sweep_post = v

    def sine(self, freq=None):
        if freq is None:
            freq = self.freq
        return sympy.sin(self.t * freq * 2 * sympy.pi)

    def triangle(self, freq=None):
        if freq is None:
            freq = self.freq
        return 2 / sympy.pi * sympy.asin(self.sine(freq))

    def sawtooth(self, freq=None):
        if freq is None:
            freq = self.freq
        return -2 / sympy.pi * sympy.atan(1/sympy.tan(sympy.pi * self.t))

    def square(self, freq=None):
        return self.triangle(freq).diff()/2

    def sweep(self, start_freq=None, stop_freq=None, pre=None, post=None):
        if start_freq is None:
            start_freq = self._s_start_freq
        if stop_freq is None:
            stop_freq = self._s_stop_freq
        if stop_freq is None:
            stop_freq = self._s_stop_freq
        if pre is None:
            pre = self._s_sweep_pre
        if post is None:
            post = self._s_sweep_post
        return self._s_sweep(self.t, start_freq, stop_freq, pre, post, self._s_FS)

    def impulse(self):
        return self._s_impulse(self.t)

    def generate(self, sig, fs, op=None, channels=None):
        if op is None:
            if channels is None:
                op = [0]
            else:
                op = [0] * channels
        d = {
            self._s_FS: fs,
            self._s_freq: self.freq,
            self._s_start_freq: self.start_freq,
            self._s_stop_freq: self.stop_freq,
            self._s_sweep_pre: self.sweep_pre,
            self._s_sweep_post: self.sweep_post,
            }
        return GeneratedSignal(self(sig).subs(d), op, fs, self.freq, self.start_freq, self.stop_freq)

    def __call__(self, expr, samples=None, timespan=None, periods=None):
        if isinstance(expr, types.FunctionType):
            expr = expr()
        if timespan is not None:
            samples = self._s_FS * timespan
        elif periods is not None:
            samples = self._s_FS / _freq ##FIXME
        elif samples is None:
            samples = self._s_FS * self.timespan
        if isinstance(expr, (int,float)) or not (self.t in expr.atoms() or expr.atoms(self._s_time)):
            expr += self._s_null(self.t)
        return expr.subs(self.t, self._s_time(samples, self._s_FS))

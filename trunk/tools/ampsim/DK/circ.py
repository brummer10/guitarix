# -*- coding: utf-8 -*-
from __future__ import division

import math
import pylab as pl
import numpy as np
from models import *
import dk_simulator, dk_lib
from numpy.fft import fftfreq

class Test(object):
    FS = 96000
    max_error = 1e-7
    result_count = 10
    timespan = 0.01
    solver = None  ## use default

    def get_samples(self, data):
        return data[np.array(np.linspace(0, len(data)-1, self.result_count).round(), dtype=int)]

    def compare_data(self, data):
        error = np.max(abs(self.result - self.get_samples(data))) / np.max(abs(data))
        if (error > self.max_error).any():
            return False, "Difference = %g (> %g)" % (error, self.max_error)
        else:
            return True, "OK"

    def check_signal(self, p):
        try:
            y = p(self.signal())
        except ValueError as v:
            return False, v
        else:
            return self.compare_data(y)

    def check(self, name, args):
        parser = dk_simulator.Parser(self.S, self.V, self.FS, not args.backward_euler)
        p = dk_simulator.get_executor(
            name, parser, self.solver, args.pure_python, c_tempdir=args.c_tempdir,
            c_verbose=args.c_verbose, c_debug_load=args.c_debug_load, linearize=args.linearize)
        if args.print_result:
            self.print_data(p(self.signal()), "\nresult = np.")
            return ""
        res = self.check_signal(p)  # side-effect: calculate time_per_sample
        if hasattr(p, "time_per_sample"):
            s = " [%.2g]" % p.time_per_sample
        else:
            s = ""
        return "%s%s" % (res[1], s)

    def print_data(self, data, prefix=""):
        print prefix + repr(self.get_samples(data))

    def op_signal(self, op=None, samples=None, timespan=None):
        if timespan is None:
            timespan = self.timespan
        if op is None:
            op = self.V["OP"]
        if samples is None:
            samples = timespan*self.FS
        return np.array((op,),dtype=np.float64).repeat(samples, axis=0)

    def constant_signal(self, *values):
        a = np.zeros((self.timespan*self.FS, len(values)))
        for i, v in enumerate(values):
            a[:,i] = v
        return a

    def sine_signal(self, freq, channels=1, timespan=None):
        if timespan is None:
            timespan = self.timespan
        a = np.zeros((timespan*self.FS, channels))
        s = np.sin(np.linspace(0, 2*np.pi*freq*timespan, self.FS*timespan))
        for i in range(channels):
            a[:,i] = s
        return a

    def timeline(self):
        return np.linspace(0, self.timespan, self.timespan*self.FS)

    def finish_plot(self, args, loc=None, timeline=None):
        if timeline is not None:
            pl.plot(self.get_samples(timeline), self.result, "rx")
        pl.grid()
        pl.legend(args, loc=loc)
        pl.show()

    def impulse(self, p, magnitude=1e-3):
        a = self.op_signal(samples=64*1024, op=self.V.get("OP",[0.]))
        a[0,0] += magnitude
        return (p(a)-p.o0) / magnitude

    def make_sweep(self, pre=None, span=0.5, post=0.1, magnitude=1e-2, start=20, stop=10000):
        smpl = lambda tm: int(round(tm*self.FS))
        if pre is None:
            pre = span/2
        s, d = dk_lib.genlogsweep(
            start, stop, self.FS, smpl(pre), smpl(span), smpl(post))
        s *= magnitude
        n = dk_lib.pow2roundup(len(s))
        #d /= np.mean(abs(np.fft.fft(dk_lib.fft_convolve(d, s), n))[n*start/self.FS:n*stop/self.FS])
        #return s, d
        return s

    def sweep(self, p, pre=None, span=0.5, post=0.1, magnitude=1e-2, start=20, stop=10000):
        #s, d = self.make_sweep(pre, span, post, magnitude, start, stop)
        s = self.make_sweep(pre, span, post, magnitude, start, stop)
        a = self.op_signal(samples=len(s), op=self.V.get("OP",[0.]))
        a[:,0] += s
        y = p(a)-p.o0
        #return dk_lib.fft_convolve(d, y[:,0])
        return dk_lib.fft_convolve(s, y[:,0], invert=True)

    #spectrum_signal = impulse
    spectrum_signal = sweep

    def plot_spectrum(self, p, plot_variable):
        y = self.spectrum_signal(p)
        n = dk_lib.pow2roundup(len(y))
        cut = slice(n*20.0/self.FS, n*10000.0/self.FS)
        w = fftfreq(n,1.0/self.FS)[cut]
        def spec(y):
            s = 20*np.log10(abs(np.fft.fft(y,n,axis=0)[cut]))
            return np.where(s > -80, s, np.nan)
        pl.semilogx(w, spec(y))
        self.finish_plot(p.out_labels)


class Pot_test(Test):

    S = ((P(), GND, 1, 2),
         (IN, 1),
         (OUT, 2),
         )
    V = {P(): 100,
         }

    timespan = 0.001
    result_count = 1
    result = np.array([[5.]])

    def signal(self):
        return self.constant_signal(10)

    def plot(self, p):
        x = self.timeline()
        y = p(self.signal())
        pl.plot(x, y)
        self.finish_plot(p.out_labels)


class Choke_test(Test):

    Trans_ = Trans_GC
    S = ((R(), "Vin", 1),
         (Trans_(nw=1), 1, GND),
         (IN, "Vin"),
         (OUT, 1),
         )

    V = {R(): 100,
         Trans_L(): dict(windings=[100], R = 358.),
         Trans_F(): dict(windings=[100], b = 255., c = 358.),
         Trans_GC(): dict(windings=[100], C = 3e-3, a = 5, o = 0, n = 7),
         "OP": [0],
         }

    timespan = 0.1

    result = np.array([[  9.99982639e+00],
       [  9.63192390e+00],
       [  8.83713207e+00],
       [  4.81529457e+00],
       [  9.32319453e-01],
       [  1.15845534e-01],
       [  1.34415129e-02],
       [  1.54332593e-03],
       [  1.77387615e-04],
       [  2.03450473e-05]])

    def signal(self):
        return self.constant_signal(10)

    def plot(self, p):
        x = self.timeline()
        y = p(self.signal())
        pl.plot(x, y)
        self.finish_plot(p.out_labels, timeline=x)


class Transformer_GC_test(Test): # transformer
    Trans_ = Trans_GC
    #Trans_ = Trans_L
    #Trans_ = Trans_F
    S = ((R("p1"), "Vin1", 1),
         (R("p2"), "Vin2", 2),
         (R("s"), 3, GND),
         (Trans_(nw=3), 1, GND, GND, 2, 3, GND),
         (IN, "Vin1", "Vin2"),
         (OUT, Trans_()('phi',1e2), Trans_()('v'), Trans_()("W1")),
         #(OUT, 3),
         )
    V = {R("p1"): 100,
         R("p2"): 100,
         R("s"): 1e3,
         Trans_GC(): dict(windings=[100, 100, 100], C=2e-3, a=1e-5, o=0, n=25),
         Trans_F(): dict(windings=[100, 100, 100], b = 255., c = 358.),
         Trans_L(): dict(windings=[100, 100, 100], R = 358.),
         }

    result = np.array([
        [ 0.        ,  0.        ,  0.        ],
        [ 0.3992909 , -0.00938712, -1.61537868],
        [ 0.38494716,  0.08242046, -0.64855777],
        [ 0.04203609,  1.36258321,  0.06707826],
        [-0.3932343 , -0.04269338,  1.10292514],
        [-0.20936599, -1.01472959, -0.04550217],
        [ 0.3975867 ,  0.02137891, -1.45104038],
        [ 0.31854514,  0.55214928,  0.01398803],
        [-0.3746337 ,  1.22787577,  0.39689002],
        [-0.36713395, -0.19608725,  0.19608725]])

    solver = dict(method='hybr')
    freq = 40.
    timespan = 2 / freq

    def signal(self):
        a = 165*self.sine_signal(self.freq, 2)
        a[:,1] = -a[:,1]
        return a

    def plot(self, p):
        x = self.timeline()
        y = p(self.signal())
        pl.plot(x, y)
        self.finish_plot(p.out_labels, timeline=x)

    def spectrum_signal(self, p):
        if 0:
            s, d = self.make_sweep()
            a = self.op_signal(samples=len(s), op=self.V.get("OP",[0.,0.]))
            a[:,0] += s
            a[:,1] -= s
            y = p(a)-p.o0
            return dk_lib.fft_convolve(d, y)
        else:
            magnitude = 1e-3
            a = self.op_signal(samples=64*1024, op=self.V.get("OP",[0.,0.]))
            a[0,0] += magnitude
            a[0,1] -= magnitude
            return (p(a)-p.o0) / magnitude
        

class PushPullTransformer_test(Test): # 2 push-pull pentodes with transformer
    #Trans_ = Trans_F
    #Trans_ = Trans_L
    Trans_ = Trans_GC
    S = ((NODES, 1, 2, "Vps", 4, 5, "Vo", "Vin1", "Vin2"),
         (Pentode(1), "Vin1", 1, 2, GND),
         (Pentode(2), "Vin2", 4, 5, GND),
         (R("s1"), 1, "Vps"),
         (R("s2"), 4, "Vps"),
         (R("L"), "Vo", GND),
         (Trans_(nw=3), 2, "Vps", "Vps", 5, "Vo", GND),
         (IN, "Vin1", "Vin2", "Vps"),
         (OUT, Trans_()('phi',100), Trans_()('v'), Trans_()("W1"), Trans_()("W2")),
         )

    EL34 = dict(mu = 8.7,
                Ex = 1.35,
                Kp = 48.0,
                Kvb = 12.0,
                Kg1 = 1460.0,
                Kg2 = 4500.0,
                Gco = -0.2,
                Gcf = 1e-5,
                )

    V = {Pentode(1): EL34,
         Pentode(2): EL34,
         R("s1"): 470,
         R("s2"): 470,
         R("L"): 8,
         R(1): 100,
         R(2): 100,
         Trans_L(nw=3): dict(windings=[1000, 1000, 64], R=358),
         Trans_GC(nw=3): dict(windings=[100.0, 100.0, 6.4], C=24e-3, a=900, o=0, n=7),
         #Trans_GC(nw=3): dict(windings=[1000, 1000, 64], C=2e-3, a=1e-5, n=25),
         Trans_F(nw=3): dict(windings=[1000, 1000, 64], b = 255., c = 358.),
         "Vps": 394,
         "OP": [-37., -37., 394.],
         }

    result = np.array([[  8.85087837e-11,   7.12940817e-12,   5.26565523e-02,
         -5.26565523e-02],
       [ -1.58278792e+00,   1.14670412e-01,   5.00849572e-01,
         -4.28188725e-05],
       [ -1.38833333e+00,  -7.39092672e-01,   1.69924724e-01,
         -6.89825386e-03],
       [  5.73079885e-01,  -3.83696969e+00,   1.14213877e-04,
         -1.99353250e-01],
       [  1.49571385e+00,   4.47570165e-01,   6.88773238e-04,
         -3.12632460e-01],
       [  1.32753760e-01,   3.77081469e+00,   1.93209752e-01,
         -6.97194440e-04],
       [ -1.55895858e+00,  -2.42708781e-01,   4.33324817e-01,
         -1.12964367e-04],
       [ -7.93509924e-01,  -3.08007847e+00,   6.98993965e-03,
         -1.57496524e-01],
       [  1.58649719e+00,   3.56694151e-02,   4.27872401e-05,
         -5.01235149e-01],
       [  1.19796324e+00,   1.43745392e+00,   5.20594452e-02,
         -5.29346715e-02]])

    freq = 30.
    timespan = 2 / freq
    solver = dict(method='hybr', xtol=1e-8)

    def signal(self):
        a = 50*self.sine_signal(self.freq, 3)
        a[:,0] = a[:,0] + self.V["OP"][0]
        a[:,1] = -a[:,1] + self.V["OP"][1]
        a[:,2] = self.V["OP"][2]
        return a

    def plot(self, p):
        x = self.timeline()
        y = p(self.signal())
        pl.plot(x, y)
        self.finish_plot(p.out_labels, timeline=x)

    def spectrum_signal(self, p):
        if 0:
            s, d = self.make_sweep()
            a = self.op_signal(samples=len(s), op=self.V["OP"])
            a[:,0] += s
            a[:,1] -= s
            y = p(a)-p.o0
            return dk_lib.fft_convolve(d, y)
        else:
            magnitude = 1e-3
            a = self.op_signal(samples=64*1024, op=self.V["OP"])
            a[0,0] += magnitude
            a[0,1] -= magnitude
            return (p(a)-p.o0) / magnitude
        

class Resonator_test(Test): # LC-resonator
    S = ((R(), "V0", "V1"),
         (L(),"V0","V1"),
         #(Trans_GC(nw=1), "V0", "V1"),
         (C(),"V1",GND),
         #(OUT, "V1",Trans_GC()("phi",1e6)),
         (OUT, "V1"),
         (IN, "V0"),
         )

    V = {L(): 1e-3,
         C(): 1e-5,
         R(): 1e+2,
         Trans_GC(nw=1): dict(windings=[100], C = 1e-3/100**2, a = 5e-1, o = 0, n = 4),
         "OP": [0],
         }

    result = np.array([[ 0.        ],
       [ 1.745916  ],
       [ 1.01468553],
       [-3.07344884],
       [ 3.12017221],
       [-3.56599345],
       [ 4.03218786],
       [-4.01662343],
       [ 3.60790549],
       [-2.8083471 ]])

    timespan = 0.01
    
    def signal(self):
        res_freq = 1592
        return self.sine_signal(res_freq-200)

    def plot(self, p):
        x = self.timeline()
        y = p(self.signal())
        pl.plot(x, y)
        self.finish_plot(p.out_labels, timeline=x)


class Tonestack_test(Test):
    S = ((R(4), 1, 2),
         (C(1), 1, 3),
         (C(2), 2, 4),
         (C(3), 2, 5),
         (P(3), GND, 6, 5),
         (P(2), None, 6, 4),
         (P(1), 4, 3, 7),
         (IN, 1),
         (OUT, 7),
         )
    V = {C(1): 0.25e-9,
         C(2): 20e-9,
         C(3): 20e-9,
         P(1): dict(value=250e3, var='t'),
         P(2): dict(value=1e6, var='l'),
         P(3): dict(value=25e3, var='m'),
         R(4): 56e3,
         "POT": dict(l=0.5, m=0.5, t=0.5),
         }

    timespan = 0.01

    def signal(self):
        return self.sine_signal(400)

    def plot(self, p):
        x = self.timeline()
        y = p(self.signal())
        pl.plot(x, y)
        self.finish_plot(p.out_labels)


class Diode_test(Test):
    S = ((D(), "V+", GND),
         (IN, "V+"),
         (OUT, IN("V+")),
         )
    V = {D(): dict(Is=10e-12, mUt=30e-3),
         }

    result = np.array([[ -7.84771994e-09],
       [ -4.30320159e-08],
       [ -3.31279654e-07],
       [ -1.81468620e-06],
       [ -1.39675067e-05],
       [ -7.65094713e-05],
       [ -5.88885037e-04],
       [ -3.22571938e-03],
       [ -2.48280067e-02],
       [ -1.35999688e-01]])

    def signal(self):
        self.sig = np.linspace(0.2, 0.7)
        a = self.op_signal([0], samples=len(self.sig))
        a[:,0] = self.sig
        return a

    def plot(self, p):
        y = p(self.signal())
        pl.semilogy(self.sig, -y)
        pl.plot(self.get_samples(self.sig), -self.result, "rx")
        self.finish_plot(p.out_labels)


class Diode_clipper(Test): # diode clipper
    D_ = D2  # 2 antisymmetric diodes
    #D_ = D  # one diode
    S = (#C(), 0, 1),
         (R(1), 1, 2),
         (D_(), 2, GND),
         #(R(2), 2, GND),
         (IN, 1),
         (OUT, 1, IN(1), 2),
         )

    V = {R(): 100,
         R(1): 0.1,
         R(2): 1.,
         D_(): dict(Is=10e-12, mUt=30e-3),
         C(): 3e-7,
         "OP": [0],
         }
    solver = dict(method='lm')

    result = np.array([[ -1.20000000e+00,   3.98658844e+00,  -8.01341156e-01],
       [ -9.34673367e-01,   1.60606646e+00,  -7.74066721e-01],
       [ -6.69346734e-01,   4.24890680e-02,  -6.65097827e-01],
       [ -4.04020101e-01,   7.05959501e-06,  -4.04019395e-01],
       [ -1.38693467e-01,   1.01800915e-09,  -1.38693467e-01],
       [  1.38693467e-01,  -1.01800915e-09,   1.38693467e-01],
       [  4.04020101e-01,  -7.05959501e-06,   4.04019395e-01],
       [  6.69346734e-01,  -4.24890680e-02,   6.65097827e-01],
       [  9.34673367e-01,  -1.60606646e+00,   7.74066721e-01],
       [  1.20000000e+00,  -3.98658844e+00,   8.01341156e-01]])

    def signal(self):
        self.sig = np.linspace(-1.2, 1.2, 200)
        a = self.op_signal([0], samples=len(self.sig))
        a[:,0] = self.sig
        return a

    def plot(self, p):
        y = p(self.signal())
        pl.plot(self.sig, -y)
        pl.plot(self.get_samples(self.sig), -self.result, "rx")
        self.finish_plot(p.out_labels)


# class LFO_test(Test): # LFO, fail, finds wrong roots (c.f. Mačák thesis)

#     OPA_ = OPA
#     S = ((R(1), "V1", "V2"),
#          (C(1), "V2", "V3"),
#          (R(2), "V3", "V4"),
#          (R(3), "V4", "V1"),
#          (OPA_(1), GND, "V2", "V3"),# "Vee", "Vcc"),
#          (OPA_(2), "V4", GND, "V1"),# "Vee", "Vcc"),
#          #(IN, "Vee", "Vcc"),
#          (OUT, "V3"),
#          )

#     V = {R(1): 25e3,
#          R(2): 33e3,
#          R(3): 47e3,
#          C(1): 5e-6,
#          OPA_(1): 1e5,
#          OPA_(2): 1e5,
#          "OP": [],
#          }

class LinOpAmp_test(Test): # linear inverting OPAMP

    S = ((R(2), "V-", "Vout"),
         (R(1), GND, "V-"),
         (OPA_L(), "V+", "V-", "Vout"),
         (OUT, "V-", "Vout"),
         (IN, "V+"),
         )

    V = {OPA_L(): 1e5,
         R(1): 1e3,
         R(2): 1e3,
         }

    timespan = 0.02

    result = np.array([[  0.00000000e+00,   0.00000000e+00],
       [  6.37209653e-01,   1.27441931e+00],
       [  9.82196290e-01,   1.96439258e+00],
       [  8.60534149e-01,   1.72106830e+00],
       [  3.38606060e-01,   6.77212121e-01],
       [ -3.38606060e-01,  -6.77212121e-01],
       [ -8.60534149e-01,  -1.72106830e+00],
       [ -9.82196290e-01,  -1.96439258e+00],
       [ -6.37209653e-01,  -1.27441931e+00],
       [ -2.44934259e-15,  -4.89868517e-15]])

    def signal(self):
        return self.sine_signal(500)

    def plot(self, p):
        x = self.timeline()
        y = p(self.signal())
        pl.plot(x, y)
        self.finish_plot(p.out_labels, timeline=x)


class InvOpAmp_test(Test): # inverting OPAMP
    S = ((R(2), "V-", "Vout"),
         (R(1), "Vin", "V-"),
         (OPA(), GND, "V-", "Vout"),
         (OUT, "Vin", "V-", "Vout"),
         (IN, "Vin"),
         )

    V = {OPA(): dict(Vcc = 10, Vee = -10, A = 1e5),
         R(1): 1e3,
         R(2): 1e3,
         }

    timespan = 0.01
    solver = dict(method='hybr', factor=1e-1)

    result = np.array([[  0.00000000e+00,   0.00000000e+00,   0.00000000e+00],
       [ -4.26797924e+00,  -4.55963690e-05,   4.26788804e+00],
       [  7.67994044e+00,   1.01536941e-04,  -7.67973737e+00],
       [ -1.04572021e+01,  -2.28601029e-01,   1.00000000e+01],
       [  1.18022106e+01,   9.01105283e-01,  -1.00000000e+01],
       [ -1.18022106e+01,  -9.01105283e-01,   1.00000000e+01],
       [  1.04572021e+01,   2.28601029e-01,  -1.00000000e+01],
       [ -7.67994044e+00,  -1.01536941e-04,   7.67973737e+00],
       [  4.26797924e+00,   4.55963690e-05,  -4.26788804e+00],
       [ -1.46957616e-14,  -1.46954677e-19,   1.46954677e-14]])

    def signal(self):
        return 12*self.sine_signal(500)

    def plot(self, p):
        x = self.timeline()
        y = p(self.signal())
        pl.plot(x, y)
        self.finish_plot(p.out_labels, timeline=x)

class WahWah_test(Test): # wah-wah
    S = ((R(1), "V1", "V2"),
         (C(1), "V2", "V3"),
         (T(1), "V4", "V3", "V5"),
         (R(4), "V4", "V6"),
         (R(7), "V6", "V7"),
         (C(4), "V4", "V8"),
         (P(), GND, "V8", "V9"),
         #(R("va"), "V8", "V9"),
         #(R("vb"), "V9", GND),
         (T(2), "V11", "V10", "V12"),
         (C(5), "V9", "V10"),
         (R(5), "V4", "V10"),
         (R(10), "V13", "V11"),
         (R(9), "V12", GND),
         (C(3), "V7", "V12"),
         (R(2), "V13", "V4"),
         (R(3), "V5", GND),
         (C(2), "V6", GND),
         (R(8), "V6", GND),
         (R(6), "V7", "V3"),
         #(L(1), "V6", 7),
         (Trans_GC(1, nw=1), "V6", 7),
         #(Trans_L(1, nw=1), "V6", 7),
         (R('L'), 7, "V7"),
         (V(), "V13"),
         (IN, "V1"),
         (OUT, "V8"),
         #(OUT, "V1","V2","V3","V4","V5","V6","V7","V8","V9","V10","V11","V12","V13"),
         #(OUT, Trans_GC(1, nw=1)("W1"), Trans_GC(1, nw=1)("phi",1e3)),
         #(OUT, "V4", "V6","V7"),
         )

    V = {R(1): 68e3,
         R(2): 22e3,
         R(3): 390,
         R(4): 470e3,
         R(5): 470e3,
         R(6): 1.5e3,
         R(7): 33e3,
         R(8): 82e3,
         R(9): 10e3,
         R(10): 1e3,
         P(): dict(value=100e3, a=3, inv=1, var='hotpotz', name='Wah'),
         R("va"): 50e3,
         R("vb"): 50e3,
         C(1): 10e-9,
         C(2): 4.7e-6,
         C(3): 10e-9,
         C(4): 220e-9,
         C(5): 220e-9,
         L(1): 500e-3,
         R('L'): 60.,
         # a = (4e-3/(0.5/100**2))**7
         Trans_GC(1, nw=1): dict(windings=[100], C = 0.5/100**2, a = (8287.159*0.5/100)**7*100, o = 1e-3, n = 7),
         Trans_L(1, nw=1): dict(windings=[100], R = 100**2/0.5),
         T(1): dict(Vt=26e-3, Is=20.3e-15, Bf=1430, Br=4),
         T(2): dict(Vt=26e-3, Is=20.3e-15, Bf=1430, Br=4),
         V(): 8.15,
         "OP": [0],
         "POT": dict(Pv=0.5),
         }

    timespan = 0.02

    def signal(self):
        a = self.op_signal()
        a[:,0] += 0.2*self.sine_signal(555.*1.2)[:,0]
        #a[:,0] += 10*self.sine_signal(555.*1.02)[:,0]
        return a

    max_error = 5e-7  # presumable due to different numeric implementation of nonlinear vector function
    result = np.array([[ -1.52955659e-09], # linear inductivity
       [ -5.05823249e-01],
       [  6.48561512e-01],
       [ -4.12448688e-01],
       [  3.39214923e-01],
       [ -4.18385401e-01],
       [  3.80384337e-01],
       [ -3.10358628e-01],
       [  2.61649974e-01],
       [ -2.30510286e-01]])

    result = np.array([[  3.38299440e-09], # nonlinear inductivity
       [ -5.05702356e-01],
       [  6.50565393e-01],
       [ -4.16306149e-01],
       [  3.38903677e-01],
       [ -4.17551679e-01],
       [  3.81734262e-01],
       [ -3.11947188e-01],
       [  2.61606410e-01],
       [ -2.30657192e-01]])

    def plot(self, p):
        x = self.timeline()
        y = p(self.signal())
        pl.plot(x, y)
        self.finish_plot(p.out_labels, timeline=x)

    def plot_spectrum(self, p, plot_variable):
        varlist = []
        if plot_variable:
            if plot_variable not in p.pot_list:
                raise ArgumentError("variable %s not found" % plot_variable)
            ##hack
            for k, t in self.V.items():
                if isinstance(k, P):
                    if not isinstance(t, dict):
                        t = dict(value=t)
                    var = t.get('var')
                    if var is None:
                        var = str(k)+'v'
                    if var == plot_variable:
                        break
            loga = t.get('a', 0)
            inv = t.get('inv', 0)
            for i in range(5):
                pot = i/4
                lbl = "%s" % pot
                if inv:
                    pot = 1 - pot
                if loga:
                    pot = (math.exp(loga * pot) - 1) / (math.exp(loga) - 1)
                varlist.append((plot_variable, pot, lbl))
        else:
            varlist.append((None, None, p.out_labels))
        n = None
        cut = None
        def spec(y):
            s = 20*np.log10(abs(np.fft.fft(y,n,axis=0)[cut]))
            return np.where(s > -80, s, np.nan)
        labels = []
        for var, val, lbl in varlist:
            if var is not None:
                p.set_variable(var, val)
            y = self.spectrum_signal(p, magnitude=1e-4)
            if n is None:
                n = dk_lib.pow2roundup(len(y))
                cut = slice(n*20.0/self.FS, n*10000.0/self.FS)
                w = fftfreq(n,1.0/self.FS)[cut]
            pl.semilogx(w, spec(y))
            if isinstance(lbl, basestring):
                labels.append(lbl)
            else:
                labels.extend(lbl)
        self.finish_plot(labels, loc='upper left')


class WahWah_ss(WahWah_test): # wah-wah small signal model

    result = np.array([ # RL = 0
        [-7.06631563e-02, 3.63685251e-01, -7.61920610e-01, 8.24081826e-01, -4.77626993e-01, 1.36243627e-01, -1.37999458e-02],
        [ 1.00000000e+00, -5.95793948e+00, 1.47953386e+01, -1.96017943e+01, 1.46127463e+01, -5.81176668e+00, 9.63415573e-01]])
    result = np.array([ # RL = 60
        [-7.06620964e-02, 3.63509088e-01, -7.61193126e-01, 8.22912278e-01, -4.76737510e-01, 1.35937831e-01, -1.37664640e-02],
        [ 1.00000000e+00, -5.95545306e+00, 1.47829908e+01, -1.95772669e+01, 1.45883870e+01, -5.79967105e+00, 9.61013231e-01]])

    def plot(self, p):
        x = self.timeline()
        y = p(self.signal())
        pl.plot(x, y)
        self.finish_plot(p.out_labels)

    def check(self, name, args):
        p = dk_simulator.Parser(self.S, self.V, self.FS, not args.backward_euler, create_filter=True, symbolic=False)
        p1 = dk_simulator.Parser(self.S, self.V, self.FS, not args.backward_euler)
        sim = dk_simulator.SimulatePy(dk_simulator.EquationSystem(p1), self.solver)
        J = sim.jacobi()
        f = dk_simulator.LinearFilter(p, J)
        b, a = f.get_z_coeffs(samplerate=48000, subst_var=f.convert_variable_dict({}))
        res = np.array([[float(v) for v in b],[float(v) for v in a]])
        if np.allclose(res, self.result):
            return "Ok"
        else:
            return "Fail"


class Transistor_test(Test): # transitor test
    S = ((R(1), "Vcc", "Vc"),
         (R(2), "Ve", GND),
         (R(3), "Vi", "Vb"),
         (T(1), "Vc", "Vb", "Ve"),
         (IN, "Vi", "Vcc"),
         (OUT, "Vi", "Vb", "Vc"),
         )

    V = {R(1): 22e3,
         R(2): 3900,
         R(3): 1e6,
         T(1): dict(Vt=26e-3, Is=20.3e-15, Bf=1430, Br=4),
         "OP": [1, 10],
         "v0": [1, 1],
         }

    result = np.array([[  0.00000000e+00,   5.07500000e-09,   1.00000000e+01],
       [  2.55102041e-01,   2.55101787e-01,   9.99999186e+00],
       [  5.61224490e-01,   5.54726496e-01,   9.79571591e+00],
       [  8.16326531e-01,   7.78051696e-01,   8.79671559e+00],
       [  1.12244898e+00,   1.04063290e+00,   7.42786606e+00],
       [  1.37755102e+00,   1.25843293e+00,   6.25516528e+00],
       [  1.68367347e+00,   1.51928439e+00,   4.83193585e+00],
       [  1.93877551e+00,   1.73642085e+00,   3.63837400e+00],
       [  2.24489796e+00,   1.99680450e+00,   2.20043766e+00],
       [  2.50000000e+00,   2.09652273e+00,   1.65153038e+00]])

    def signal(self):
        self.sig = np.linspace(0,2.5)
        a = self.op_signal([0,10], len(self.sig))
        a[:,0] += self.sig
        return a

    def plot(self, p):
        y = p(self.signal())
        pl.plot(self.sig, y)
        self.finish_plot(p.out_labels, timeline=self.sig)


class Triode1_test(Test): # triode test
    S = ((Triode(), "Vg", "Va", GND),
         (IN, "Vg", "Va"),
         (OUT, IN("Vg")),
         )

    V = {Triode(): dict(mu = 100.0, Ex = 1.4, Kp = 600.0, Kvb = 300.0, Kg1 = 1060.0, Gco = -0.2, Gcf = 1e-5),
         "OP": [0, 200],
         }

    result = np.array([[  0.00000000e+00],
       [ -1.19744249e-05],
       [ -3.38687882e-05],
       [ -6.22209369e-05],
       [ -9.57953991e-05],
       [ -1.35707894e-04],
       [ -1.77991025e-04],
       [ -2.23933047e-04],
       [ -2.73262818e-04],
       [ -3.25761876e-04]])

    def signal(self):
        self.sig = np.linspace(-0.2, 10, 200)
        a = self.op_signal(samples=len(self.sig))
        a[:,0] += self.sig
        return a

    def plot(self, p):
        y = p(self.signal())
        pl.plot(self.sig, -y)
        pl.plot(self.get_samples(self.sig), -self.result, "rx")
        self.finish_plot(p.out_labels)

Tubes = {
    "12ax7": dict(mu = 100.0, Ex = 1.4, Kp = 600.0, Kvb = 300.0, Kg1 = 1060.0, Gco = -0.2, Gcf = 1e-5),
    }

class Triode2_test(Test): # triode test 2
    S = ((Triode(), "Vg", "Va", "Vk"),
         (R("g"), "Vi", "Vg"),
         (R("a"), "Va", "Vcc"),
         (R("k"), "Vk", GND),
         (IN, "Vi", "Vcc"),
         (OUT, "Vi", "Vg", "Vk", Out("Va",5e-2)),
         )

    V = {Triode(): dict(mu = 100.0, Ex = 1.4, Kp = 600.0, Kvb = 300.0, Kg1 = 1060.0, Gco = -0.2, Gcf = 1e-5),
         R("a"): 100e3,
         R("k"): 1e3,
         R("g"): 1e5,
         "OP": [0, 200],
         }

    result = np.array([[ -3.50000000e+00,  -3.50000000e+00,   7.72550710e-04,
          9.99613725e+00],
       [ -2.00753769e+00,  -2.00753769e+00,   1.07424037e-01,
          9.46287981e+00],
       [ -5.15075377e-01,  -5.15075377e-01,   5.57235813e-01,
          7.21382094e+00],
       [  9.77386935e-01,   9.70474217e-01,   1.13418598e+00,
          4.32941573e+00],
       [  2.46984925e+00,   1.96653045e+00,   1.53378538e+00,
          2.35623905e+00],
       [  4.03015075e+00,   2.75954335e+00,   1.78642745e+00,
          1.13139312e+00],
       [  5.52261307e+00,   3.35356923e+00,   1.87793631e+00,
          7.18770664e-01],
       [  7.01507538e+00,   3.86821124e+00,   1.92078300e+00,
          5.53428225e-01],
       [  8.50753769e+00,   4.33885772e+00,   1.94866325e+00,
          4.65117726e-01],
       [  1.00000000e+01,   4.77961288e+00,   1.97029218e+00,
          4.09558453e-01]])

    def signal(self):
        self.sig = np.linspace(-3.5, 10, 200)
        a = self.op_signal(samples=len(self.sig))
        a[:,0] += self.sig
        return a

    def plot(self, p):
        y = p(self.signal())
        pl.plot(self.sig, y)
        self.finish_plot(p.out_labels, loc="upper center", timeline=self.sig)


class Preamp_test(Test):
    S = ((P(6), GND, 8, 9),
         #(R(61), 8, 9),
         #(R(62), 9, GND),
         (V('cc3'), 18),
         (CC(2), 11, 13),
         (V('cc2'), 12),
         (Triode(2), 9, 11, 10),
         (V('cc1'), 5),
         (CC(1), 4, 6),
         (Triode(3), 15, 17, 16),
         (Triode(1), 2, 4, 3),
         (C('m3'), 15, 17),
         (C(7), 14, 15),
         (C(6), 13, 14),
         (C('m2'), 9, 11),
         (C(5), 8, 9),
         (C(4), 7, 8),
         (C(3), 6, 7),
         (C(2), 4, 3),
         (C(1), 3, GND),
         (C('m1'), 2, 4),
         (R(12), 18, 17),
         (R(11), 16, GND),
         (R(10), 15, GND),
         (R(9), 15, 14),
         (R(7), 10, GND),
         (R(8), 12, 11),
         (R(5), 7, 8),
         (R(4), 5, 4),
         (R(3), 3, GND),
         (R(2), 2, 1),
         (R(1), 1, GND),
         (OUT, 17),
         (IN, 1),
         )

    V = {C('m1'): 2.e-12,
         C('m2'): 2.e-12,
         C('m3'): 2.e-12,
         C(1): 680.e-9,
         C(2): 100.e-12,
         C(3): 22.e-9,
         C(4): 470.e-12,
         C(5): 1.e-9,
         C(6): 22.e-9,
         C(7): 470.e-12,
         R(1): 1.e6,
         R(10): 470.e3,
         R(11): 820.,
         R(12): 100.e3,
         R(2): 68.e3,
         R(3): 2.7e3,
         R(4): 100.e3,
         R(5): 470.e3,
         R(7): 10.e3,
         R(8): 100.e3,
         R(9): 470.e3,
         P(6): 1.e6,
         R(61): 0.5e6,
         R(62): 0.5e6,
         Triode(1): Tubes['12ax7'],
         Triode(2): Tubes['12ax7'],
         Triode(3): Tubes['12ax7'],
         V('cc1'): 385.,
         V('cc2'): 385.,
         V('cc3'): 385.,
         }

    result = np.array(
        [[ 221.71522314],
         [ 171.55513962],
         [ 384.87040955],
         [  87.6985932 ],
         [ 175.15609089],
         [ 384.87745145],
         [  88.35549583],
         [ 176.31730901],
         [ 384.87680835],
         [  88.18246137]])

    timespan = 0.2
    solver = dict(method='hybr', xtol=1e-8, factor=1e5)

    def signal(self):
        return 0.15*self.sine_signal(150.0)

    def plot(self, p):
        x = self.timeline()
        y = p(self.signal())
        pl.plot(x, y)
        self.finish_plot(p.out_labels, timeline=x)

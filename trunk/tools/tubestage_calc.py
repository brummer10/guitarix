from pylab import *
from scipy.optimize import newton
import faustmod

tubelist = ("12AX7_68k", "12AX7_250k",
            "6V6_68k",   "6V6_250k",
            "12AU7_68k", "12AU7_250k",
            "6DJ8_68k",  "6DJ8_250k",
            "12AT7_68k", "12AT7_250k",
            )
tubetab = dict((j,i) for i,j in enumerate(tubelist))

def plot_dsp(dsp):
    #a = 5*sin(arange(0,10*pi,0.1,dtype=float32))
    a = zeros(2000,dtype=float32)
    plot(dsp.compute(a))
    show()

def timing(dsp):
    a = 5*sin(arange(0,10*pi,0.1,dtype=float32))
    dsp.compute(a)
    print dsp.nanosec_per_sample

def Vk0(dsp):
    a = zeros(50,dtype=float32)
    def f(v):
        dsp["Vk0"] = v
        return dsp.compute(a)[-1]
    return newton(f, 0, tol=1e-7)

def show_Vk0(dsp):
    dsp.init(3000) # low sampling rate because of RC time constant
    for tb, Rk in (("12AX7_68k",2700), ("12AX7_250k",1500), ("12AX7_250k",820),
                   ("6V6_68k",2700), ("6V6_250k",1500), ("6V6_250k",820), ("6V6_68k",820), ("6V6_250k",410), ("6V6_68k",410),
                   ("12AU7_68k",2700), ("12AU7_250k",1500), ("12AU7_250k",820),
                   ("12AT7_68k",2700), ("12AT7_250k",1500), ("12AT7_250k",820),
                   ):
        dsp["tb"] = tubetab[tb]
        dsp["Rk"] = Rk
        print "%-10s / %4g: %f" % (tb, Rk, Vk0(dsp))
    print "vplus = 130:"
    dsp["vplus"] = 130
    for tb, Rk in (("12AU7_68k",2700), ("12AU7_250k",1500), ("12AU7_250k",820),
                   ("6DJ8_68k",2700), ("6DJ8_250k",1500), ("6DJ8_250k",820), ("6DJ8_68k",820),
                   ):
        dsp["tb"] = tubetab[tb]
        dsp["Rk"] = Rk
        print "%-10s / %4g: %f" % (tb, Rk, Vk0(dsp))

def display_param(dsp):
    n = int(amax([len(k) for k in dsp.keys()]))
    for k in dsp.keys():
        print "%-*s: %g" % (n, k, dsp[k])

if __name__ == "__main__":
    dsp = faustmod.dsp()
    #display_param(dsp)
    show_Vk0(dsp)
    #dsp.init(44100)
    #plot_dsp(dsp)

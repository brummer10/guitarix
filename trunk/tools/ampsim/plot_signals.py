import circuit as cp
from pylab import *

def mkplot(inp, *args, **kw):
    if isinstance(inp, (cp.pycircuit.CalcBase, Func)):
        inp = inp.captured[:,0]
    x = linspace(0, timespan, len(inp))
    plot(x, inp, "r", label="Uin")
    legend(loc=2)
    twinx()
    for a in args:
        lb = None
        if isinstance(a, tuple):
            lb = a[1]
            a = a[0]
        if isinstance(a, (cp.pycircuit.CalcBase, Func)):
            if lb is None:
                lb = a.capture_signals
            elif isinstance(lb, basestring):
                    lb = [lb]
            for v, n in zip(a.captured.T, lb):
                plot(x, v, label=n)
        else:
            if lb is None:
                lb = "Ua"
            plot(x, a, label=lb)
    legend(loc=1)
    if kw["head"]:
        title(kw["head"])


class Func(object):

    def __init__(self, p, capt=None):
        self.p = p()
        self.p.init()
        if capt:
            self.p.capture_signals = capt

    def __call__(self, s):
        self.max_in = amax(s, axis=0)
        self.min_in = amin(s, axis=0)
        r = self.p(s)
        self.max_out = amax(r, axis=0)
        self.min_out = amin(r, axis=0)
        return r

    @property
    def captured(self):
        return self.p.captured

    @property
    def capture_signals(self):
        return self.p.capture_signals

    def show_stat(self, l, s, mn, mx):
        if mn.shape == ():
            l.append("%s: %g..%g" % (s, mn, mx))
        else:
            l += [(s+": %g..%g") % v for v in  zip(mn, mx)]

    def print_statist(self):
        l = []
        self.show_stat(l, "IN", self.min_in, self.max_in)
        self.show_stat(l, "OUT", self.min_out, self.max_out)
        l += ["%s: %g..%g" % v for v in  zip(self.p.state_names, self.p.min_state, self.p.max_state)]
        s = ", ".join(l)
        print "%s: %.0fnsec, %s" % (self.p.comp_id, self.p.nanosec_per_sample, s)


def sine(freq):
    return sin(linspace(0, 2*pi*freq*timespan, cp.FS*timespan), dtype=float32)

pr1 = Func(cp.CoupledTriode, "Ua")
pr2 = Func(cp.CoupledTriode, "Ua")
pr3 = Func(cp.CoupledTriode, "Ua")
sp = Func(cp.PhaseSplitter_JCM800, "Ua1")
g1 = Func(cp.PPGate_JCM800, "Ug")
g2 = Func(cp.PPGate_JCM800)
pl = Func(cp.PPPlate_JCM800)

freq = 150.0
timespan = 9/freq
s = 0.1*sine(freq)
y = sp(0.4*pr3(0.4*pr2(0.5*pr1(s))))
s1 = g1(y[:,0])
s2 = g2(y[:,1])
#s2 += s1
res = pl(vstack((s1,s2)).T)
for v in pr1, pr2, pr3, sp, g1, g2, pl:
    v.print_statist()
subplot(221)
mkplot(s, (pr2,"Ua Stage2"), (pr3,"Ua Stage3"), head="Preamp")
subplot(222)
mkplot(pr3, sp, head="Phase Splitter")
subplot(223)
mkplot(sp, g1, head="Poweramp Gate")
subplot(224)
mkplot(g1, res, head="Poweramp Out")
show()

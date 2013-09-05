import circuit as cp
from pylab import *

def mkplot(inp, *args, **kw):
    if isinstance(inp, cp.Func):
        inp = inp.captured[0]
    x = linspace(0, timespan, len(inp))
    plot(x, inp, "r", label="Uin")
    legend(loc=2)
    twinx()
    for a in args:
        lb = None
        if isinstance(a, tuple):
            lb = a[1]
            a = a[0]
        if isinstance(a, cp.Func):
            if lb is None:
                lb = a.capt
            elif isinstance(lb, basestring):
                    lb = [lb]
            for v, n in zip(a.captured, lb):
                plot(x, v, label=n)
        else:
            if lb is None:
                lb = "Ua"
            plot(x, a, label=lb)
    legend(loc=1)
    if kw["head"]:
        title(kw["head"])

def sine(freq):
    return sin(linspace(0, 2*pi*freq*timespan, cp.FS*timespan), dtype=float32)

pr1 = cp.Func(cp.CoupledTriode, capt="Ua")
pr2 = cp.Func(cp.CoupledTriode, capt="Ua")
pr3 = cp.Func(cp.CoupledTriode, capt="Ua")
sp = cp.Func(cp.PhaseSplitter, capt="Ua1")
g1 = cp.Func(cp.PPGate, capt="Ug")
g2 = cp.Func(cp.PPGate)
pl = cp.Func(cp.PPPlate)
freq = 150.0
timespan = 9/freq
s = 0.1*sine(freq)
res = empty((len(s),1))
for i, v in enumerate(s):
    y = sp(0.4*pr3(0.4*pr2(0.5*pr1(v))))
    s1 = g1(y[0])[0]
    s2 = g2(y[1])[0]
    s2 += s1
    res[i] = pl([s1,s2])
subplot(221)
mkplot(s, (pr2,"Ua Stage2"), (pr3,"Ua Stage3"), head="Preamp")
subplot(222)
mkplot(pr3, sp, head="Phase Splitter")
subplot(223)
mkplot(sp, g1, head="Poweramp Gate")
subplot(224)
mkplot(g1, res, head="Poweramp Out")
show()

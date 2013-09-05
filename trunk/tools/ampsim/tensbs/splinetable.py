import sys, tensbs
import numpy as np
import pylab

################################################################

def print_float_array(o, name, a, prefix):
    print >>o, "%sfloat %s[%d] = {" % (prefix, name, a.size)
    s = "  "
    i = 0
    for v in a.ravel('C'):
        o.write(s+repr(v))
        s = ","
        i += 1
        if i % 10 == 0:
            print >>o, ","
            s = "  "
    print >>o, "};"
    return a.size

def print_intpp_data(o, tag, prefix, func, n_in, nvals, *rgdata):
    if prefix:
        prefix += " "
    sz = 0
    int_sz = np.int32().nbytes
    float_sz = np.float32().nbytes
    n = len(rgdata)
    ranges = []
    orderletter = "xyzv"
    orderdict = {}
    for i, (r, k) in enumerate(rgdata):
        ranges.append(r)
        orderdict["k%s" % orderletter[i]] = k
    print >>o, "%sreal x0%s[%d] = {%s};" % (prefix, tag, n, ", ".join([str(float(v.start)) for v in ranges]))
    print >>o, "%sreal h%s[%d] = {%s};" % (prefix, tag, n, ", ".join([str(float(v.stop-v.start)/(v.step.imag-1)) for v in ranges]))
    print >>o, "%sint n%s[%d] = {%s};" % (prefix, tag, n, ", ".join([str(int(v.step.imag)) for v in ranges]))
    sz += (2*int_sz+2*float_sz) * n;
    grd = np.mgrid[ranges]
    grd_shape = grd.shape
    numpoints = np.product(grd_shape[1:])
    grd = grd.reshape(grd_shape[0], numpoints, order='F')
    grd = grd.T
    fnc = np.empty((nvals, numpoints), np.float32)
    for i, p in enumerate(grd):
        ain = p[:n_in]
        state = list(p[n_in:])
        res = func(p[:n_in], state)
        fnc[:,i] = res + state
    fnc.shape = (nvals,)+tuple(reversed(grd_shape[1:]))
    fnc = fnc.T
    b_ink = eval("tensbs.b%dink" % n)
    args = [np.arange(s.step.imag,dtype=np.float32) for s in ranges]
    ti = []
    ci = []
    idx = [slice(None)]*n+[0]
    for i in range(nvals):
        idx[n] = i
        res = b_ink(*(args+[fnc[idx]]),**orderdict)
        iflag = res[n+1]
        if iflag != 1:
            raise ValueError("b2ink ret value %d", iflag)
        if i == 0:
            for j in range(n):
                t = "t%d%s" % (j, tag)
                ti.append(t)
                sz += print_float_array(o, t, res[j], prefix) * float_sz
        t = "c%d%s" % (i, tag)
        ci.append(t)
        sz += print_float_array(o, t, res[n], prefix) * float_sz
    print >>o, "%sfloat *t%s[%d] = {%s};" % (prefix, tag, n, ", ".join(ti))
    print >>o, "%sfloat *c%s[%d] = {%s};" % (prefix, tag, nvals, ", ".join(ci))
    sz += (n + nvals) * float_sz
    return sz

################################################################

class PlotManager(object):
    def __init__(self, r, c):
        self.r = r
        self.c = c
        self.i = 1

    def __call__(self):
        pylab.subplot(self.r,self.c,self.i)
        self.i += 1

def check_error_grid2(name, ranges, func1, func2, labels, pm):
    points = np.array(np.mgrid[ranges].T, dtype=np.float32, order="C")
    points = points.view(",".join(['float32']*len(ranges))).reshape(points.shape[:-1])
    def f1(x):
        return tuple(func1(x))
    def f2(x):
        return tuple(func2(x))
    print name
    for i, (l, a1, a2) in enumerate(zip(labels, np.vectorize(f1)(points),np.vectorize(f2)(points))):
        a = abs(a2 - a1)
        print "%s: %g" % (l, max(a.flat))
        if False:
            m = argsort(a, axis=None)
            for i in range(10):
                n = m[-(1+i)]
                idx = unravel_index(n, a.shape)
                print idx, ",".join(["%g" % v for v in points[idx]]), a.flat[n]
        if pm:
            pm()
            pylab.title("%s/%s" % (name,l))
            pylab.hist(a.flat)

def check_error_func2(name, func, funcrange, func0, val, pm):
    l = []
    for i, (x0, h, n) in enumerate(funcrange):
        stop = x0 + (n-1)*h - 1e-6
        l.append(slice(x0+h/2,stop-h/2,(n-1)*1j))
    check_error_grid2(name, l, func, func0, val, pm)

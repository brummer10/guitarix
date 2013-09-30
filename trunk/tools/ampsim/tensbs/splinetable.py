import sys
import itertools, fractions
import numpy as np
import pylab
from scipy.interpolate import LSQUnivariateSpline, InterpolatedUnivariateSpline, UnivariateSpline

################################################################

class KnotData(object):

    def __init__(self, knots, mapping, sl, order):
        self.knots = knots
        self.mapping = mapping
        self.slice_data = sl
        self.order = order

    def used(self):
        return self.order is not None

    def inv_h(self):
        sl = self.slice_data
        return (sl.step.imag - 1) / (sl.stop - sl.start)

    def count(self):
        return int(self.slice_data.step.imag)

    def get_knots(self):
        k = self.order
        return self.knots[k:-k]

    def num_coeffs(self):
        return len(self.knots) - self.order

    def get_bbox(self):
        return self.knots[0], self.knots[-1]

    def get_order(self):
        return self.order


class TensorSpline(object):

    def __init__(self, func, ranges, basegrid):
        self.func = func
        self.ranges = ranges
        self.basegrid = basegrid
        self.knot_data = np.empty((len(basegrid), len(ranges)), dtype=object)
        self.find_knots()

    def calc_coeffs(self):
        coeff = []
        for v, (g, kdata) in enumerate(zip(self.basegrid, self.knot_data)):
            ranges = [(slice(r[0], r[1], t[0]*1j) if kd.used() else slice((r[1]-r[0])/2.0,r[1],1j)) for r, t, kd in zip(self.ranges,g[0],kdata)]
            fnc = self.calc_grid(ranges, g[1], g[2])[v]
            for n in range(len(ranges)):
                kd = self.knot_data[v,n]
                if not kd.used():
                    continue
                s = list(fnc.shape)
                s[n] = kd.num_coeffs()
                out = np.empty(s)
                s[n] = 1
                x = np.mgrid[ranges[n]]
                for i in np.ndindex(tuple(s)):
                    i = list(i)
                    i[n] = slice(None)
                    ss = LSQUnivariateSpline(x, fnc[i], kd.get_knots(), bbox=kd.get_bbox(), k=kd.get_order()-1)
                    out[i] = ss.get_coeffs()
                fnc = out
            coeff.append(fnc)
        return coeff

    @staticmethod
    def get_interpolating_knots(x, k):
        x_e = x[-1]
        x_e += (x_e - x[-2]) * 0.1
        start = k // 2
        end = -(k - start)
        knots = np.zeros((3,len(x)-k))
        knots[0] = x[start:end]
        knots[1] = np.arange(start, len(x)+end)
        if k % 2:
            knots[0,:-1] += knots[0,1:]
            knots[0,-1] += x[end]
            knots[0] *= 0.5
        return knots, (x[0], x_e)

    @staticmethod
    def spline_diff(n, x, kn, bbox, k, fnc):
        s = list(fnc.shape)
        s[n] = 1
        out = np.empty_like(fnc)
        for idx in np.ndindex(tuple(s)):
            idx = list(idx)
            idx[n] = slice(None)
            f = fnc[idx]
            ss = LSQUnivariateSpline(x, f, kn, bbox=bbox, k=k-1)
            out[idx] = abs(ss(x) - f)
        return out

    @staticmethod
    def max_df(n, x, kn, bbox, k, fnc):
        s = list(fnc.shape)
        s[n] = 1
        mx = 0
        for idx in np.ndindex(tuple(s)):
            idx = list(idx)
            idx[n] = slice(None)
            f = fnc[idx]
            ss = LSQUnivariateSpline(x, f, kn, bbox=bbox, k=k-1)
            mx = max(mx, np.amax(abs(ss(x) - f)))
        return mx #/ np.ptp(fnc)

    def calc_grid(self, ranges, pre, post):
        grd = np.mgrid[ranges]
        pre_grd = grd.copy()
        if pre:
            grd = pre(grd)
        grd_shape = grd.shape
        numpoints = np.product(grd_shape[1:])
        grd = grd.reshape(grd_shape[0], numpoints)
        fnc = self.func(grd.T, True).T
        fnc.shape = (len(self.basegrid),)+tuple(grd_shape[1:])
        if post:
            fnc = post(pre_grd, fnc)
        return fnc

    @staticmethod
    def max_diff(n, kn, pos, val):
        ki = np.unique(np.digitize(pos, kn), True)[1]
        idx = [slice(None)]*val.ndim
        l = []
        for i, j in itertools.izip_longest(ki, ki[1:]):
            idx[n] = slice(i, j)
            l.append(np.amax(val[idx]))
        a = np.array(l)
        return a[1:] + a[:-1]

    @staticmethod
    def mk_result(kn, bbox, k, r):
        idx = np.zeros(len(kn[1])+2, dtype=np.int32)
        idx[1:-1] = kn[1]
        idx[-1] = r.step.imag
        f = reduce(fractions.gcd, idx)
        idx /= f
        a = np.empty(idx[-1], dtype=np.int32)
        for m, (i, j) in enumerate(itertools.izip_longest(idx[:-1], idx[1:])):
            a[i:j] = m
        a += k-1
        return KnotData(np.pad(kn[0], k, 'constant', constant_values=bbox), a, slice(r.start, r.stop, r.step/f), k)

    def get_support(self, i, fnc, dlim):
        def apply_subcube(op, a, axis):
            j = a.shape[axis]
            return op(np.rollaxis(a, axis, 1).reshape(j, a.size/j), axis=1)
        dfnc = np.diff(fnc, 1, axis=i)
        supp1 = apply_subcube(np.amax, abs(dfnc), i) >= dlim
        nz1 = np.flatnonzero(supp1)
        d2fnc = np.diff(dfnc, 1, axis=i)
        d2lim = 1e-7
        supp2 = apply_subcube(np.amax, abs(d2fnc), i) >= d2lim
        nz2 = np.flatnonzero(supp2)
        istart, iend, llim, rlim = None, None, None, None
        if len(nz1):
            istart = nz1[0]
            iend = nz1[-1]
        if len(nz2):
            istart = min(istart, nz2[0])
            iend = max(iend, nz2[-1])
        if istart < 2:
            istart = None
        if iend > d2fnc.shape[i]-1:
            iend = None
        if istart:
            istart -= 1
            if np.amax(apply_subcube(np.amax, abs(dfnc), i)[:istart]) < dlim:
                llim = 0
            else:
                llim = (np.amin(apply_subcube(np.amin, dfnc, i)[:istart]), np.amax(apply_subcube(np.amax, dfnc, i)[:istart]))
        if iend:
            iend += 1
            if np.amax(apply_subcube(np.amax, abs(dfnc), i)[iend:]) < dlim:
                rlim = 0
            else:
                rlim = (np.amin(apply_subcube(np.amin, dfnc, i)[:iend]), np.amax(apply_subcube(np.amax, dfnc, i)[:iend]))
                print apply_subcube(np.amax, abs(dfnc), i)[iend:]; print iend, dlim; raise SystemExit
        print "##", dlim, (istart, iend), (llim, rlim)
        return (istart, iend), (llim, rlim)

    def find_knots(self):
        for v, g in enumerate(self.basegrid):
            order = [t[1] for t in g[0] if t is not None]
            for n in range(len(self.ranges)):
                ranges = [slice(r[0], r[1], (2j * t[0] + 1 if i == n else 0.5j * t[0])) for i, (r, t) in enumerate(zip(self.ranges,g[0]))]
                fnc = self.calc_grid(ranges, g[1], g[2])[v]
                #self.get_support(n, fnc, np.amax(abs(fnc))*(ranges[n].stop-ranges[n].start)/ranges[n].step.imag * 1e-4)
                ptp = fnc.ptp()
                if np.amax(fnc.ptp(axis=n)) < 1e-6 * ptp:
                    print "%s[%d,%d]: const: %g" % (self.func.comp_id, v, n, np.amax(fnc.ptp(axis=n)) / ptp)
                    self.knot_data[v, n] = KnotData(None,None,None,None)
                    continue
                k = order[n]
                x = np.mgrid[ranges[n]]
                rng = slice(self.ranges[n][0], self.ranges[n][1], g[0][n][0]*1j)
                kn, bbox = self.get_interpolating_knots(np.mgrid[rng], k)
                #e_max = 1.1 * self.max_df(n, x, kn, bbox, k, fnc)
                try:
                    e_rel = g[3]
                except IndexError:
                    e_rel = None
                if e_rel is None:
                    #e_rel = 4e-5
                    e_rel = 4e-4
                e_max = ptp * e_rel
                good = kn
                am = None
                kn0 = kn
                try:
                    opt = g[4]
                except IndexError:
                    opt = True
                while opt:
                    df = self.spline_diff(n, x, kn[0], bbox, k, fnc)
                    mx = np.amax(df)
                    if mx > e_max:
                        if am is None:
                            raise ValueError("bad approximation for %s[%d,%d]: %g > %g" % (self.func.comp_id, v, n, mx, e_max))
                        kn = good
                        kn[2,am] = 1
                    else:
                        good = kn
                    if False:
                        xd = np.square(np.diff(ss(kn[:-1], k))).argsort()+1
                    else:
                        xd = self.max_diff(n, np.pad(kn[0],(1,0),'constant',constant_values=(x[0],)), x, df).argsort()
                    for am in xd:
                        if not kn[2,am]:
                            break
                    else:
                        break
                    kn = np.append(kn[:,:am],kn[:,am+1:], axis=1)
                self.knot_data[v, n] = self.mk_result(kn, bbox, k, rng)
                print "%s[%d,%d]: (%g), %d -> %d" % (self.func.comp_id, v, n, e_max, len(kn0[0]), len(kn[0]))
                #print "#", fnc.shape, x.shape, e_max
                #print kn[:1]
                #pylab.plot(x, fnc[:,0,:])
                #pylab.plot(kn, np.zeros(len(kn)),"x")
                #pylab.show(); raise SystemExit


def b_ink(x, fnca, k):
    "return t, bcoef"
    ca = []
    for fnc in fnca:
        t = [None]*len(x)
        for n in range(len(x)):
            cf = np.empty_like(fnc)
            s = list(fnc.shape)
            s[n] = 1
            xx = x[n]
            xxe = xx[-1]
            xxe += (xxe-xx[-2]) * 0.1
            kk = k[n]
            start = kk // 2
            end = -(kk - start)
            knots = xx[start:end].copy()
            if kk % 2:
                knots[:-1] += knots[1:]
                knots[-1] += xx[end]
                knots *= 0.5
            for idx in np.ndindex(tuple(s)):
                idx = list(idx)
                idx[n] = slice(None)
                #ss = InterpolatedUnivariateSpline(x[n], fnc[idx], bbox=(xx[0],xxe), k=k[n]-1)
                ss = LSQUnivariateSpline(xx, fnc[idx], knots, bbox=(xx[0],xxe), k=kk-1)
                cf[idx] = ss.get_coeffs()
            t[n] = np.pad(knots, kk, 'constant', constant_values=(xx[0],xxe))
            fnc = cf
        ca.append(fnc)
    return t, ca

def print_float_array(o, name, a, prefix):
    print >>o, "%sfloat %s[%d] = {" % (prefix, name, a.size)
    s = "  "
    i = 0
    a = np.where(abs(a) < 100*np.finfo(np.float32).tiny, 0, a)
    for v in a.ravel('C'):
        #o.write(s+repr(float(v)))
        o.write(s + "%.8g" % v)
        s = ","
        i += 1
        if i % 10 == 0:
            print >>o, ","
            s = "  "
    print >>o, "};"
    return a.size * np.float32().nbytes

def print_int_array(o, name, a, prefix):
    print >>o, "%sint %s[%d] = {" % (prefix, name, a.size)
    s = "  "
    i = 0
    for v in a.ravel('C'):
        o.write(s + str(v))
        s = ","
        i += 1
        if i % 10 == 0:
            print >>o, ","
            s = "  "
    print >>o, "};"
    return a.size * np.int32().nbytes

def print_char_array(o, name, a, prefix):
    print >>o, "%sunsigned char %s[%d] = {" % (prefix, name, a.size)
    s = "  "
    i = 0
    for v in a.ravel('C'):
        if v > 255:
            raise ValueError("value > 255 for unsigned char in %s" % name)
        o.write(s + str(v))
        s = ","
        i += 1
        if i % 10 == 0:
            print >>o, ","
            s = "  "
    print >>o, "};"
    align = 4
    return ((a.size + align - 1) // align) * align

def print_intpp_data(o, tag, prefix, func, rgdata, basegrid):
    if prefix:
        prefix += " "
    sz = 0
    int_sz = np.int32().nbytes
    float_sz = np.float32().nbytes
    #ranges = []
    #orderlist = []
    #for r, k in rgdata:
    #    ranges.append(r)
    #    orderlist.append(k)
    spl = TensorSpline(func, rgdata, basegrid)
    coeffs = spl.calc_coeffs()
    for iv, val in enumerate(spl.knot_data):
        n = len([v for v in val if v.used()])
        print >>o, "%sreal x0%s_%d[%d] = {%s};" % (prefix, tag, iv, n, ", ".join([str(float(r[0])) for r, v in zip(rgdata, val) if v.used()]))
        print >>o, "%sreal xe%s_%d[%d] = {%s};" % (prefix, tag, iv, n, ", ".join([str(float(r[1])) for r, v in zip(rgdata, val) if v.used()]))
        print >>o, "%sreal hi%s_%d[%d] = {%s};" % (prefix, tag, iv, n, ", ".join([str(v.inv_h()) for v in val if v.used()]))
        print >>o, "%sint nmap%s_%d[%d] = {%s};" % (prefix, tag, iv, n, ", ".join([str(v.count()) for v in val if v.used()]))
        print >>o, "%sint n%s_%d[%d] = {%s};" % (prefix, tag, iv, n, ", ".join([str(v.num_coeffs()) for v in val if v.used()]))
        sz += (2*int_sz+2*float_sz) * n;
        #grd = np.mgrid[ranges]
        #grd_shape = grd.shape
        #numpoints = np.product(grd_shape[1:])
        #grd = grd.reshape(grd_shape[0], numpoints, order='F')
        #grd = grd.T
        #fnc = np.array(func(grd, True).T, order='C')
        #fnc.shape = (nvals,)+tuple(reversed(grd_shape[1:]))
        #fnc = fnc.T
        #args = [np.arange(s.step.imag) for s in ranges]
        ti = []
        ai = []
        ci = []
        #idx = [slice(None)]*n+[0]
        #fnca = []
        #for i in range(nvals):
        #    idx[n] = i
        #    fnca.append(fnc[idx])
        #tl, ca = b_ink(args, fnca, orderlist)
        for j in range(len(val)):
            if not val[j].used():
                continue
            t = "t%d_%d%s" % (j, iv, tag)
            ti.append(t)
            sz += print_float_array(o, t, val[j].knots, prefix)
            a = "a%d_%d%s" % (j, iv, tag)
            ai.append(a)
            sz += print_char_array(o, a, val[j].mapping, prefix)
        for i in range(1):
            t = "c%d_%d%s" % (i, iv, tag)
            ci.append(t)
            sz += print_float_array(o, t, coeffs[iv], prefix)
        print >>o, "%sunsigned char *map%s_%d[%d] = {%s};" % (prefix, tag, iv, n, ", ".join(ai))
        print >>o, "%sfloat *t%s_%d[%d] = {%s};" % (prefix, tag, iv, n, ", ".join(ti))
        print >>o, "%sfloat *c%s_%d[%d] = {%s};" % (prefix, tag, iv, 1, ", ".join(ci))
    sz += (n + len(basegrid)) * float_sz
    return sz, [[v.order for v in val] for val in spl.knot_data]

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

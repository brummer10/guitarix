# -*- coding: utf-8 -*-
from __future__ import division

for pyname, package in (
        ('scipy', 'python-scipy'),
        ('sympy', 'python-sympy'),
        ('pylab', 'python-matplotlib'),
        ):
    try:
        __import__(pyname)
    except ImportError:
        raise SystemExit("Need module %s (Debian package: %s)" % (pyname, package))

import sys, itertools, fractions, os, argparse, math, logging
from cStringIO import StringIO
from scipy.interpolate import LSQUnivariateSpline, PchipInterpolator
import pylab as pl
import numpy as np
from scipy.signal import correlate
from scipy.interpolate import splev
import dk_simulator, dk_lib, circ, models


class KnotData(object):

    def __init__(self, knots, mapping, sl, order):
        self.knots = knots
        self.mapping = mapping
        self.slice_data = sl
        if order is None:
            self.tp = None
            self.order = None
            self.bbox = None
        else:
            if isinstance(order, int):
                self.tp = 's'
                self.order = order
            else:
                self.tp = order[0]
                self.order = order[1]
            self.bbox = [self.knots[0], self.knots[-1]]

    def cut_mapping(self):
        m = self.mapping
        i0, i1 = np.searchsorted(m, (m[0]+1, m[-1]))
        i0 -= 1
        i1 += 1
        self.bbox[0] += i0 / self.inv_h()
        self.bbox[1] -= (len(m) - i1) / self.inv_h()
        self.mapping = m[i0:i1]

    def used(self):
        return self.order is not None

    def inv_h(self):
        sl = self.slice_data
        return (sl.step.imag - 1) / (sl.stop - sl.start)

    def count(self):
        return len(self.mapping) + 1

    def get_knots(self):
        k = self.order
        return self.knots[k:-k]

    def get_knot_grid(self):
        d = self.slice_data
        k = self.order
        if k is None:
            return np.array(((d.start+d.stop)*0.5,))
        else:
            a = self.knots[k//2:-k//2].copy()
            n = d.step.imag
            if n == 1:
                n = k
            h = (d.stop - d.start) / (n - 1)
            for i in range(k//2):
                a[i] = d.start + i * h
                a[-(i+1)] = d.stop - i * h
            return a

    def num_coeffs(self):
        return len(self.knots) - self.order

    def get_bbox(self):
        return self.bbox

    def get_order(self):
        return self.order

class TensorSpline(object):

    def __init__(self, func, ranges, basegrid):
        self.func = func
        self.ranges = ranges
        self.basegrid = basegrid
        self.knot_data = np.empty((len(basegrid), len(ranges)), dtype=object)
        self.get_grid_estimate()
        self.find_knots()
        self.save_grid_estimate()

    @staticmethod
    def max_idx_to_maptype(max_idx):
        if max_idx >= 2**16:
            return "int"
        elif max_idx >= 2**8:
            return "unsigned short"
        else:
            return "unsigned char"

    def grid_estimate_fname(self):
        return "%s_grid.cache" % self.func.comp_id

    def get_grid_estimate(self):
        try:
            self.grid_estimate = pickle.load(open(self.grid_estimate_fname()))
        except (IOError, EOFError):
            self.grid_estimate = np.empty((len(self.basegrid), len(self.ranges)), dtype=object)
            for v, g in enumerate(self.basegrid):
                self.grid_estimate[v][:] = [np.mgrid[slice(r[0], r[1], 0.5j * t[0])] for r, t in zip(self.ranges,g[0])]

    def save_grid_estimate(self):
        with open(self.grid_estimate_fname(),"w") as f:
            pickle.dump(self.grid_estimate, f)

    @staticmethod
    def insert_points(a, n, kd):
        o = []
        for x, k in zip(a, kd):
            if k.tp == 'h':
                o.append(x)
                continue
            i = len(x)
            b = np.zeros(i + n * (i -  1))
            b[::n+1] = x
            for j in range(n):
                w = (j+1) / (n+1)
                b[j+1::n+1] = x[:-1] * w + x[1:] * (1-w)
            o.append(b)
        return o

    def calc_coeffs(self):
        coeff = []
        for v, (g, kdata) in enumerate(zip(self.basegrid, self.knot_data)):
            coords = []
            for kd in kdata:
                if kd.used():
                    if kd.tp in ('s', 'pp'):
                        k = kd.get_order()
                        x = kd.knots.copy()
                        x[:k] = np.linspace(x[0], x[k], k, False)
                        x[-k:] = np.linspace(x[-(k+1)], x[-1], k, False)
                    else:
                        assert kd.tp == 'h'
                        k = kd.get_order() - 1
                        x = kd.knots[k:-k]
                else:
                    x = kd.get_knot_grid()
                coords.append(x)
            add_num_points = 0
            coords = self.insert_points(coords, add_num_points, self.knot_data[v])
            fnc = self.calc_grid(self.make_grid(coords), g[1], g[2])[v]
            for n in range(len(self.ranges)):
                kd = self.knot_data[v,n]
                if not kd.used():
                    continue
                s = list(fnc.shape)
                if kd.tp == 'h':
                    s[n] = 4 * (len(coords[n]) - 1)
                else:
                    s[n] = kd.num_coeffs()
                out = np.empty(s)
                s[n] = 1
                x = coords[n]
                kn = kd.get_knots()
                bb = kd.get_bbox()
                k = kd.get_order() - 1
                for i in np.ndindex(tuple(s)):
                    i = list(i)
                    i[n] = slice(None)
                    if kd.tp in ('s', 'pp'):
                        ss = LSQUnivariateSpline(x, fnc[i], kn, bbox=bb, k=k)
                        out[i] = ss.get_coeffs()
                    else:
                        ss = PchipInterpolator(x, fnc[i])
                        def mklist(kr):
                            c = kr.c[:,0]
                            return [c[3], c[2]-c[3]*(kr.xi[-1]-kr.xi[0]), c[1], c[0]]
                        out[i] = np.array([mklist(kr) for kr in ss.polynomials]).flat
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

    def make_grid(self, coords, sparse=False):
        if len(coords) == 1:
            r = coords[0]
            res = np.empty((1, r.shape[0]))
            res[0] = r
        else:
            r = np.meshgrid(*coords, indexing="ij", sparse=sparse)
            res = np.empty((len(coords),)+r[0].shape)
            res[:] = r
        return res

    def calc_grid(self, grd, pre, post):
        if post:
            pre_grd = grd.copy()
        if pre:
            grd = pre(grd)
        grd_shape = grd.shape
        numpoints = np.product(grd_shape[1:])
        grd = grd.reshape(grd_shape[0], numpoints)
        fnc = self.func(grd.T, True).T
        fnc = fnc.reshape(fnc.shape[:1]+tuple(grd_shape[1:]))
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
                coords = self.grid_estimate[v].copy()
                coords[n] = np.mgrid[self.ranges[n][0]:self.ranges[n][1]:g[0][n][0]*2j]
                #ranges = [slice(r[0], r[1], (2j * t[0] + 1 if i == n else 0.5j * t[0])) for i, (r, t) in enumerate(zip(self.ranges,g[0]))]
                #fnc = self.calc_grid(np.mgrid[ranges], g[1], g[2])[v]
                fnc = self.calc_grid(self.make_grid(coords), g[1], g[2])[v]
                #self.get_support(n, fnc, np.amax(abs(fnc))*(ranges[n].stop-ranges[n].start)/ranges[n].step.imag * 1e-4)
                ptp = fnc.ptp()
                if np.amax(fnc.ptp(axis=n)) < 1e-6 * ptp and False: ##FIXME
                    print "%s[%d,%d]: const: %g" % (self.func.comp_id, v, n, np.amax(fnc.ptp(axis=n)) / ptp)
                    self.knot_data[v, n] = KnotData(None,None,slice(self.ranges[n][0], self.ranges[n][1], 1j),None)
                    continue
                k = order[n]
                #x = np.mgrid[ranges[n]]
                x = coords[n]
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
                if e_rel < 0:
                    e_max = -e_rel
                else:
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
                self.grid_estimate[v,n] = self.knot_data[v,n].get_knot_grid()
                print "%s[%d,%d]: (%g), %d -> %d [%s]" % (self.func.comp_id, v, n, e_max, len(kn0[0]), len(kn[0]), fnc.shape)
                #print "#", fnc.shape, x.shape, e_max
                #print kn[:1]
                #pylab.plot(x, fnc[:,0,:])
                #pylab.plot(kn, np.zeros(len(kn)),"x")
                #pylab.show(); raise SystemExit


#dtp = "float"
#tiny = np.finfo(np.float32).tiny
dtp = "treal"
tiny = np.finfo(np.float64).tiny

def print_float_array(o, name, a, prefix):
    print >>o, "%s%s %s[%d] = {" % (prefix, dtp, name, a.size)
    s = "  "
    i = 0
    a = np.where(abs(a) < 100*tiny, 0, a)
    for v in a.ravel('C'):
        o.write(s+repr(float(v)))
        #o.write(s + "%.8g" % v)
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

def print_maptype_array(o, name, a, prefix):
    print >>o, "%smaptype %s[%d] = {" % (prefix, name, a.size)
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
    align = 4
    return ((a.size + align - 1) // align) * align

def print_intpp_data(o, tag, prefix, func, rgdata, basegrid, Spline=TensorSpline):
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
    spl = Spline(func, rgdata, basegrid)
    coeffs = spl.calc_coeffs()
    max_idx = 0
    for iv, val in enumerate(spl.knot_data):
        for v in val:
            if not v.used():
                continue
            max_idx = max(max_idx, v.mapping[-1])
    print >>o, "typedef %s maptype;" % Spline.max_idx_to_maptype(max_idx)
    n = 0
    for iv, val in enumerate(spl.knot_data):
        for v in val:
            if v.used():
                n += 1
                v.cut_mapping()
        print >>o, "%sreal x0%s_%d[%d] = {%s};" % (prefix, tag, iv, n, ", ".join([str(float(v.get_bbox()[0])) for v in val if v.used()]))
        print >>o, "%sreal xe%s_%d[%d] = {%s};" % (prefix, tag, iv, n, ", ".join([str(float(v.get_bbox()[1])) for v in val if v.used()]))
        print >>o, "%sreal hi%s_%d[%d] = {%s};" % (prefix, tag, iv, n, ", ".join([str(v.inv_h()) for v in val if v.used()]))
        print >>o, "%sint k%s_%d[%d] = {%s};" % (prefix, tag, iv, n, ", ".join([str(v.get_order()) for v in val if v.used()]))
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
            sz += print_maptype_array(o, a, val[j].mapping, prefix)
        for i in range(1):
            t = "c%d_%d%s" % (i, iv, tag)
            ci.append(t)
            sz += print_float_array(o, t, coeffs[iv], prefix)
        print >>o, "%smaptype *map%s_%d[%d] = {%s};" % (prefix, tag, iv, n, ", ".join(ai))
        print >>o, "%s%s *t%s_%d[%d] = {%s};" % (prefix, dtp, tag, iv, n, ", ".join(ti))
        print >>o, "%s%s *c%s_%d[%d] = {%s};" % (prefix, dtp, tag, iv, 1, ", ".join(ci))
    sz += (n + len(basegrid)) * float_sz
    return sz, max_idx, spl

def print_header_file_start(h):
    print >>h, """\
#ifndef _DATA_H
#define _DATA_H 1

#ifndef NO_INTPP_INCLUDES
#include "intpp.h"
#endif

namespace AmpData {
    extern real b0;
    extern real b1;
    extern real a1;
    extern int fs;

"""

def print_header_file_end(h):
    print >>h, """\
}

#endif /* !_DATA_H */
"""

def print_header_file_entry(h, f):
    print >>h, "namespace %s { extern splinedata sd; }" % f

def print_header(o):
    print >>o, '#ifndef NO_INTPP_INCLUDES'
    print >>o, '#include "intpp.h"'
    print >>o, '#endif'
    print >>o, "namespace AmpData {"
    if 0:
        b0, b1, a1 = circuit.PhaseSplitter().feedback_coeff(1.0)
        print >>o, "real b0 = %g;" % b0
        print >>o, "real b1 = %g;" % b1
        print >>o, "real a1 = 1 - %g;" % (1 - a1)
    #print >>o, "int fs = %d;" % circuit.FS
    return 3 * np.float32().nbytes + np.int32().nbytes

def print_footer(o):
    print >>o, "} // namespace AmpData"
    return 0


class ArgumentError(ValueError):
    pass

class ValueGrid(object):

    def __init__(self, func, ranges, nvals):
        self.ranges = ranges
        self.grd = np.mgrid[ranges]
        self.values = dk_lib.calc_grid(func, self.grd, nvals)
        #print "%.2e" % np.max(self.values)

    def max_jacobi_row(self, vals):
        return np.array()

    def max_jacobi(self):
        n = self.values.shape[0]
        m = len(self.ranges)
        mj = np.zeros((n,m))
        for i in range(n):
            mj[i] = [np.max(abs(np.diff(self.values[i], axis=j))) for j in range(m)]
        for i in range(m):
            r = self.ranges[i]
            if r.start != r.stop:
                mj[:,i] /= (r.stop - r.start) / (r.step.imag-1)
            else:
                mj[:,i] = 0
        return mj

def estimate_max_jacobi(func, ranges, error, nvals):
    J = None
    n = np.ones(len(ranges), dtype=int) * 2
    while True:
        v = ValueGrid(func, [slice(r[0],r[1],i*1j) for i, r in zip(n, ranges)], nvals)
        J1 = v.max_jacobi()
        if J is not None:
            dv = np.max(abs(J1)+abs(J), axis=0)
            m = 2 * np.max(abs(J1-J), axis=0) / np.where(dv == 0, 1., dv)
            print "#%s: %s" % (n, m)
            if np.max(m) < error:
                #print "##", np.max(J1), np.max(v.values)
                return J1, v
            for i, e in enumerate(m):
                if e >= error:
                    n[i] *= 2
        else:
            n *= 2
        J = J1


class MyTensorSpline(TensorSpline):
    def __init__(self, func, ranges, basegrid):
        self.func = func
        self.ranges = ranges
        self.basegrid = basegrid
        self.knot_data = np.empty((len(basegrid), len(ranges)), dtype=object)
        self.logger = logging.getLogger("approx")
        #bg = []
        self.coeffs = []
        for i_fnc, (rng, pre, post, err, opt) in enumerate(basegrid):
            #if i_fnc < 3: continue
            grd, fnc, axes, axgrids = self.table_approximation(err, i_fnc, rng)
            #print fnc.ptp(), grd.shape, fnc.shape, len(axes), axgrids
            #grd.dump("grd.data")
            #fnc.dump("fnc.data")
            #import pickle
            #pickle.dump(axes, file("axes.data","w"))
            #raise SystemExit
            self.coeffs.append(fnc)
            for i, (ax, ag, cg, r) in enumerate(zip(axes, axgrids, func.basegrid[i_fnc][0], rng)):
                order_type = r[1]
                w = ax[-1]-ax[0]
                if w == 0:
                    order_type = None
                if order_type is not None:
                    if np.amax(fnc.ptp(axis=i)) < 1e-6 * fnc.ptp():
                        print "%s[%d,%d]: const: %g" % (func.comp_id, i_fnc, i, np.amax(fnc.ptp(axis=i)) / fnc.ptp())
                        order_type = None
                if order_type is not None:
                    if isinstance(order_type, int):
                        tp = 's'
                        order = order_type
                    else:
                        tp = order_type[0]
                        order = order_type[1]
                    idx = np.array(np.rint((ax-ax[0])/w * ag), dtype=int)
                    if order > len(ax):
                        order = 2
                    self.knot_data[i_fnc, i] = self.mk_result(idx, ax, order, tp, slice(ax[0], ax[-1], (ag+1)*1j))
                else:
                    self.knot_data[i_fnc, i] = KnotData(None,None,slice(ax[0], ax[-1], 1j),None)

    @staticmethod
    def fromspline(xk, cvals, order):
        xk2 = xk[order:-order]
        N = len(xk2)-1
        sivals = np.empty((order+1, N), dtype=float)
        for m in xrange(order, -1, -1):
            fact = np.product(np.arange(m)+1)
            res = splev(xk2[:-1], (xk, cvals, order), m)
            res /= fact
            sivals[order-m, :] = res
        return sivals

    def calc_coeffs(self):
        coeffs = TensorSpline.calc_coeffs(self)
        cf = []
        for c, k in zip(coeffs, self.knot_data):
            k = [v for v in k if v.used()]
            if len(k) == 1 and k[0].tp == 'pp' and k[0].get_order() == 4:
                if len(c.shape) == 2:
                    assert c.shape[-1] == 1, c.shape
                    c = self.fromspline(k[0].knots, c[:,0], 3).T
                    c = c.reshape(len(c)*4,1)
                else:
                    assert len(c.shape) == 1
                    c = self.fromspline(k[0].knots, c, 3).T
                    c = c.reshape(len(c)*4)
            elif k[0].tp == 'h':
                k[0].tp = 'pp'
            else:
                # no other orders implemented
                k[0].tp = 's'
            cf.append(c)
        return cf

    def mk_result(self, idx, kn, k, tp, r):
        if k is None:
            return KnotData(None,None,slice(r.start, r.stop, 1j),None)
        f = reduce(fractions.gcd, idx)
        idx /= f
        a = np.empty(idx[-1], dtype=np.int32)
        for m, (i, j) in enumerate(itertools.izip_longest(idx[:-1], idx[1:])):
            a[i:j] = m
        a += k-1
        return KnotData(np.pad(kn, k-1, 'edge'), a, slice(r.start, r.stop, 1+(r.step-1)/f), (tp, k))

    def table_approximation(self, prec, i_fnc, rng):
        #print rng, prec
        def ncalc_grid(grd):
            return self.calc_grid(grd, None, None)[i_fnc]
        n = len(self.ranges)
        axes = []
        for r, g in zip(self.ranges, rng):
            if g[1] is None:
                axes.append(np.array(((r[0]+r[1])*0.5,), dtype=np.float64))
            else:
                axes.append(np.array((r[0],r[1]), dtype=np.float64))
        axgrids = np.ones(n)
        grd = dk_lib.mkgrid(axes)
        fnc = ncalc_grid(grd)
        s1 = [slice(None)]*n
        s2 = [slice(None)]*n
        g1 = [slice(None)]*(n+1)
        g2 = [slice(None)]*(n+1)
        nn = 0
        while True:
            nn += 1 
            inserted = False
            for i in range(len(axes)):
                a = axes[i]
                if len(a) == 1:
                    continue
                ax2 = (a[:-1]+a[1:]) * 0.5
                axeslist = axes[:i] + [ax2] + axes[i+1:]
                grd2 = dk_lib.mkgrid(axeslist)
                fnc2 = ncalc_grid(grd2)
                s1[i] = slice(None, -1)
                s2[i] = slice(1, None)
                fnc_intp = (fnc[s1] + fnc[s2]) * 0.5
                if callable(prec):
                    df = prec(fnc_intp, fnc2, self.func.i0[i]).any(axis=tuple([k for k in range(n) if k != i]))
                else:
                    df = (abs(fnc_intp - fnc2) > prec).any(axis=tuple([k for k in range(n) if k != i]))
                k = np.count_nonzero(df)
                if k == 0:
                    s1[i] = slice(None)
                    s2[i] = slice(None)
                    continue
                axgrids[i] *= 2
                inserted = True
                newshape = list(grd.shape)
                newshape[i+1] += k
                newgrd = np.empty(newshape)
                newshape = list(fnc.shape)
                newshape[i] += k
                newfnc = np.empty(newshape)
                newax = np.empty(len(a)+k)
                j = 0
                for k in range(len(a)):
                    g1[i+1] = j
                    g2[i+1] = k
                    newgrd[g1] = grd[g2]
                    s1[i] = j
                    s2[i] = k
                    newfnc[s1] = fnc[s2]
                    newax[j] = a[k]
                    j += 1
                    if k < len(df) and df[k]:
                        g1[i+1] = j
                        newgrd[g1] = grd2[g2]
                        s1[i] = j
                        newfnc[s1] = fnc2[s2]
                        newax[j] = ax2[k]
                        j += 1
                s1[i] = slice(None)
                s2[i] = slice(None)
                g1[i+1] = slice(None)
                g2[i+1] = slice(None)
                axes[i] = newax
                fnc = newfnc
                grd = newgrd
            self.logger.debug("%d, %s, %s" % (i_fnc, fnc.shape, axgrids))
            if not inserted:
                self.logger.info("%d, %s, %s" % (i_fnc, fnc.shape, axgrids))
                return grd, fnc, axes, axgrids


class TableGenerator(object):

    def __init__(self, v, args, name, param):
        parser = dk_simulator.Parser(v.S, v.V, v.FS, not args.backward_euler)
        if args.c_debug_load:
            raise NotImplemented("option c-debug-load with table generation")
        else:
            sim = dk_simulator.SimulatePy(dk_simulator.EquationSystem(parser), v.solver)
            cmod = dk_simulator.BuildCModule(
                name, sim, c_tempdir=args.c_tempdir, c_verbose=args.c_verbose,
                linearize=args.linearize, c_real="double")
            eq = cmod.eq
            p = cmod.get_executor()
        a = v.op_signal(timespan=1.02, op=parser.op)
        smpl = lambda tm: int(round(tm*v.FS))
        a[:,0] += param.input_signal.amplitude * dk_lib.genlogsweep(
            param.input_signal.startfreq, param.input_signal.stopfreq, v.FS,
            smpl(param.input_signal.pre), smpl(param.input_signal.timespan),
            smpl(param.input_signal.post))[0]
        ptp = p(a).ptp()
        print "ptp =", ptp
        print "nonlin function: OP value, range:"
        print np.column_stack((p.p0, p.minmax))

        nvals = p.nno
        J, vals = estimate_max_jacobi(p.nonlin, p.minmax, param.jacobi_estimate_error, nvals)
        J = np.matrix(J)
        dv = np.amax(np.append(abs(eq.Fo), abs(eq.Fo)*J*abs(eq.G0)*abs(eq.Co), axis=0), axis=0).A
        E = param.maxerr * ptp / np.where(dv == 0, 1e-20, dv)
        print "function error limits for max out error %g: %s" % (param.maxerr, ", ".join(["%.2g" % vv for vv in E.T]))

        grd_shape = vals.grd.shape
        numpoints = np.product(grd_shape[1:])
        grd = vals.grd.reshape(grd_shape[0], numpoints)
        fnc = vals.values.reshape(nvals, numpoints)
        with dk_lib.printoptions(precision=2, linewidth=200):
            print "covariance matrix (rows: variables, columns: functions):"
            print np.cov(grd, fnc)[:len(grd),len(grd):]

        o = StringIO()
        inst = StringIO()
        h = StringIO()
        class Comp:
            comp_id = name
            comp_name = name
            ranges = p.minmax
            basegrid = [
                [((1024, 2),), None, None, -E.T[0], True],
                ]
            # basegrid = [[((64, 2),(8, 2),(16, 2),(32, 2)), None, None, -E.T[0], True],
            #             [((280, 2),(8, 2),(16, 2),(32, 2)), None, None, -E.T[1], True],
            #             [((64, 2),(8, 2),(16, 2),(32, 2)), None, None, -E.T[2], True],
            #             [((64, 2),(8, 2),(16, 2),(32, 2)), None, None, -E.T[3], True],
            #             ]
            NVALS = nvals
            N_IN = grd_shape[0]
            NDIM = grd_shape[0]
            @staticmethod
            def __call__(v, with_state):
                return p.nonlin(v)
        if 1:
            maptype = self.write_files(Comp(), o, inst, h)
            c_debug_load = None
        else:
            c_debug_load = "gencode/dk_sim_0.so"
        extra_sources = dict(data_c=o.getvalue(), data_h=h.getvalue(), intpp_inst=inst.getvalue())
        sim = dk_simulator.SimulatePy(dk_simulator.EquationSystem(parser), v.solver)
        cmodt = dk_simulator.BuildCModule(
            name+"_table", sim, dict(method="table",name=name,maptype=maptype), extra_sources=extra_sources,
            c_tempdir="gencode", c_verbose=args.c_verbose, linearize=args.linearize, c_real=("float" if args.c_float else "double"))
        pt = cmodt.get_executor()
        self.p = p
        self.pt = pt
        ##
        rng = []
        for r, b in zip(Comp.ranges, Comp.basegrid[0][0]):
            off = 0.5 * (r[1]-r[0]) / (b[0]-1)
            rng.append(slice(r[0]+off, r[1]-off, (b[0]-1)*1j))
        v1 = ValueGrid(p.nonlin, rng, nvals)
        v2 = ValueGrid(pt.nonlin, rng, nvals)
        for i in range(len(Comp.basegrid)):
            print np.max(abs(v1.values[i]-v2.values[i]))

    @staticmethod
    def max_idx_to_maptype(max_idx):
        if max_idx >= 2**16:
            return "int"
        elif max_idx >= 2**8:
            return "unsigned short"
        else:
            return "unsigned char"

    @staticmethod
    def print_intpp_data(p):
        o = StringIO()
        print >>o, "namespace %s {" % p.comp_id
        r, max_idx, spl = print_intpp_data(o, "", "", p, p.ranges, p.basegrid, MyTensorSpline)
        maptype = TableGenerator.max_idx_to_maptype(max_idx)
        print >>o, "splinecoeffs<maptype> sc[%d] = {" % p.NVALS
        f_set = set()
        for j, kn in enumerate(spl.knot_data):
            fu = "splev"
            if kn[0].tp == 'pp':
                fu = "splev_pp"
            inst = "splinedata<%s>::%s<%s>" % (maptype, fu, ",".join([str(v.get_order()) for v in kn if v.used()]))
            f_set.add((inst,maptype))
            print >>o, "\t{x0_%d, xe_%d, hi_%d, k_%d, n_%d, nmap_%d, map_%d, t_%d, c_%d, %s}," % (j, j, j, j, j, j, j, j, j, inst)
        print >>o, "};"
        print >>o, "splinedata<maptype> sd = {"
        print >>o, "\tsc,"
        print >>o, "\t%d, /* number of calculated values */" % p.NVALS
        print >>o, "\t%d, /* number of input values */" % p.N_IN
        print >>o, "\t%d, /* number of output values */" % (p.NVALS-(p.NDIM-p.N_IN))
        print >>o, "\t%d, /* number of state values */" % (p.NDIM-p.N_IN)
        print >>o, '\t"%s",' % p.comp_id
        print >>o, "};"
        print >>o, "}; /* ! namespace %s */" % p.comp_id
        o.seek(0)
        return r, o.read(), f_set, p.comp_name, p.comp_id, max_idx, spl

    @staticmethod
    def write_files(comp, o, inst, h):
        procs = [TableGenerator.print_intpp_data(comp)]
        max_idx_all = 0
        for p in procs:
            s, f, i, comp_name, comp_id, max_idx, spl = p
            max_idx_all = max(max_idx_all, max_idx)
        #maptype = max_idx_to_maptype(max_idx_all)
        #o.write("typedef %s maptype;\n" % maptype)
        print_header_file_start(h)
        sz = print_header(o)
        l = []
        templ = set()
        for p in procs:
            s, f, i, comp_name, comp_id, max_idx, spl = p
            o.write(f)
            templ |= i
            l.append("%s: %d bytes" % (comp_name, s))
            sz += s
            print_header_file_entry(h, comp_id)
        sz += print_footer(o)
        l.append("data size sum: %d bytes" % sz)
        print >>o, "".join(["\n// " + s for s in l])
        print_header_file_end(h)
        for v, maptype in sorted(templ):
            print >>inst, "template int %s(splinecoeffs<%s> *p, real xi[2], real *res);" % (v, maptype)
        return maptype, spl


class LoadedSchema(circ.Test):
    def __init__(self, params):
        v = vars(models)
        v["Tubes"] = circ.Tubes
        v["math"] = math
        if hasattr(params, "load_schema"):
            import mk_netlist
            exec mk_netlist.read_netlist(params.load_schema) in v
        else:
            with open(params.load_netlist) as f:
                exec f in v
        self.S = v["S"]
        self.V = v["V"]
        self.V["OP"] = getattr(params, "OP", [0.])
        if hasattr(params, "test_signal"):
            if hasattr(params.test_signal, "timespan"):
                self.timespan = params.test_signal.timespan
            def signal():
                a = self.op_signal()
                a[:,0] += params.test_signal.amplitude * self.sine_signal(params.test_signal.freq)[:,0]
                return a
            setattr(self, "signal", signal)


def generate_faust_module(plugindef, b, a, potlist, flt, pre_filter=None, build_script=None):
    import dk_templates
    d = {}
    if not potlist:
        d['have_master_slider'] = False
    else:
        d['have_master_slider'] = True
        d['master_slider_id'] = potlist[0][0]
    d['knob_ids'] = [t[0] for t in potlist]
    ui = dk_templates.module_ui_template.render(d)
    d = {}
    d['plugindef'] = plugindef
    d['build_script'] = build_script
    d['sliders'] = [dict(id=t[0], name=t[1], loga=t[2], inv=t[3]) for t in potlist]
    d['pre_filter'] = '_' if pre_filter is None else pre_filter
    d['b_list'] = ",".join(["b%d/a0" % i for i in range(len(b))])
    d['a_list'] = ",".join(["a%d/a0" % i for i in range(1,len(a))])
    d['coeffs'] = "\n\n    ".join(flt.coeffs_as_faust_code('b', b) + flt.coeffs_as_faust_code('a', a))
    dsp = dk_templates.faust_filter_template.render(d)
    return dsp, ui

def build_faust_module(plugindef, b, a, potlist, flt, datatype="float", pre_filter=None, build_script=None):
    dsp, ui = generate_faust_module(plugindef, b, a, potlist, flt, pre_filter, build_script)
    modname = plugindef.id
    dspname = "/tmp/%s.dsp" % modname
    uiname = "/tmp/%s_ui.cc" % modname
    with open(dspname,"w") as f:
        f.write(dsp)
    with open(uiname,"w") as f:
        f.write(ui)
    pgm = os.path.abspath("../../build-faust")
    opts = "-s" if datatype == "float" else ""
    os.system("%s %s -c %s" % (pgm, opts, dspname))

def get_circuit_instance(g, tests, args):
    if args.schema:
        class params(object):
            load_schema = args.schema
        t = os.path.splitext(os.path.basename(args.schema))[0]
        v = LoadedSchema(params)
        return v, t
    elif args.netlist:
        class params(object):
            load_netlist = args.netlist
        t = os.path.splitext(os.path.basename(args.netlist))[0]
        v = LoadedSchema(params)
        return v, t
    else:
        t = tests[0]
        return g[t](), t

def create_filter(g, tests, args):
    v, t = get_circuit_instance(g, tests, args)
    p = dk_simulator.Parser(v.S, v.V, v.FS, not args.backward_euler, create_filter=True, symbolic=args.filter_symbolic)
    if len(p.get_nonlin_funcs()) > 0:
        if args.filter_symbolic:
            raise ArgumentError("ciruit is nonlinear: symbolic formula generation not supported")
        p1 = dk_simulator.Parser(v.S, v.V, v.FS, not args.backward_euler)
        sim = dk_simulator.SimulatePy(dk_simulator.EquationSystem(p1), v.solver)
        J = sim.jacobi()
    else:
        J = None
    f = dk_simulator.LinearFilter(p, J)
    if args.filter_symbolic:
        if args.filter_s_coeffs:
            b, a, terms = f.get_s_coeffs()
            f.print_coeffs('b', b)
            f.print_coeffs('a', a)
            print "\nH = %s;" % terms
        else:
            b, a, terms = f.get_s_coeffs()
            f.print_coeffs('b', b)
            f.print_coeffs('a', a)
            B, A, c = f.transform_bilinear(terms)
            print "\nc = %s;" % c
            f.print_coeffs('B', B)
            f.print_coeffs('A', A)
    else:
        if args.filter_variable is None:
            if args.plot_spectrum:
                svar = f.convert_variable_dict({})
            else:
                svar = None
        else:
            try:
                svar = f.convert_variable_dict(dict([(s, float(vv)) for s, vv in [par.split("=") for par in args.filter_variable if par]]))
            except ValueError as e:
                raise ArgumentError(e)
        if args.filter_samplerate is None:
            if args.plot_spectrum:
                samplerate = 48000
            else:
                samplerate = None
        else:
            samplerate = args.filter_samplerate
        if args.plot_spectrum and args.plot_variable:
            pvar = [k for k in svar if args.plot_variable == str(k)]
            if not pvar:
                raise ArgumentError("variable %s not found" % args.plot_variable)
            pvar = pvar[0]
            del svar[pvar]
        b, a = f.get_z_coeffs(samplerate=samplerate, subst_var=svar)
        if args.plot_spectrum:
            if args.plot_variable:
                for e in p.element_name["P"]:
                    t = v.V[e[0]]
                    var = None
                    if isinstance(t, dict):
                        var = t.get("var")
                    if var is None:
                        var = "%sv" % e[0]
                    if var == args.plot_variable:
                        break
                else:
                    raise ArgumentError("variable %s not found" % args.plot_variable)
                if not isinstance(t, dict):
                    t = dict(value=t)
                loga = t.get('a', 0)
                inv = t.get('inv', 0)
                for i in range(5):
                    pot = i/4
                    lbl = "%s" % pot
                    if inv:
                        pot = 1 - pot
                    if loga:
                        pot = (math.exp(loga * pot) - 1) / (math.exp(loga) - 1)
                    w, h = f.spectrum([j.subs(pvar, pot) for j in b], [j.subs(pvar, pot) for j in a], 20, 10000)
                    pl.semilogx(w, np.where(h < -60, np.nan, h), label=lbl)
                pl.legend(loc='upper left')
            else:
                w, h = f.spectrum(b, a, 20, 10000)
                pl.semilogx(w, np.where(h < -60, np.nan, h))
            pl.grid()
            pl.show()
        elif args.create_module:
            l = []
            for e in set([e[0] for e in p.element_name["P"]]):
                t = v.V[e]
                if not isinstance(t, dict):
                    t = dict(value=t)
                var = t.get('var')
                if var is None:
                    var = str(e)+"v"
                name = t.get('name', var)
                loga = t.get('a', 0)
                inv = t.get('inv', 0)
                l.append((var, name, loga, inv))
            build_faust_module(dk_simulator.PluginDef(args.create_module), b, a, l, f)
        else:
            f.print_coeffs('b', b)
            f.print_coeffs('a', a)

def is_test(v):
    return isinstance(v, type) and issubclass(v, circ.Test) and v is not circ.Test

def plot_one(v, args, t):
    parser = dk_simulator.Parser(v.S, v.V, v.FS, not args.backward_euler)
    p = dk_simulator.get_executor(
        t, parser, v.solver, args.pure_python, c_tempdir=args.c_tempdir, c_verbose=args.c_verbose,
        c_debug_load=args.c_debug_load, linearize=args.linearize, c_real=("float" if args.c_float else "double"))
    if args.plot_spectrum:
        v.plot_spectrum(p, args.plot_variable)
    else:
        v.plot(p)
        if 0:
            for i, (p0, (s, e)) in enumerate(zip(p.p0, p.minmax)):
                print "%d: %g [%g .. %g]" % (i, p0, s, e)

def plot_output(g, tests, args):
    if args.schema or args.netlist:
        v, t = get_circuit_instance(g, tests, args)
        plot_one(v, args, t)
        return
    if not tests:
        testlist = [k for k, v in g.items() if is_test(v)]
        testlist.sort()
        for i, k in enumerate(testlist):
            if k.endswith("_test"):
                k = k[:-5]
            print "%2d: %s" % (i, k)
        print
        try:
            k = testlist[int(raw_input("Please select: "))]
        except (ValueError, KeyError):
            print "not found"
            raise SystemExit, 1
        except KeyboardInterrupt:
            print
            raise SystemExit, 1
        tests = [k]
    for t in tests:
        plot_one(g[t](), args, t)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('test', nargs="*",
                        help='name of test')
    parser.add_argument('-c', '--check', action='store_true',
                        help='check results of tests')
    parser.add_argument('-b', '--backward-euler', action='store_true',
                        help='use Backward-Euler integration instead of trapezoidal')
    parser.add_argument('-p', '--pure-python', action='store_true',
                        help='do not generate C code to speed up calculations')
    parser.add_argument('-f', '--func',
                        help='function table generation')
    parser.add_argument('-s', '--show', action='store_true',
                        help='plot nonlinear function')
    parser.add_argument('-S', '--schema',
                        help='use gschem .sch file as input')
    parser.add_argument('-N', '--netlist',
                        help='use netlist file as input (TBD: document file format)')
    parser.add_argument('--linearize', action='store_true',
                        help='build a linear small signal model')
    parser.add_argument('-y', '--filter', action='store_true',
                        help='calculate coefficients for linear filter (small signal model for nonlinear circuits)')
    parser.add_argument('--plot-spectrum', action='store_true',
                        help='plot spectrum of curcuit')
    parser.add_argument('--plot-variable',
                        help='display a set of curves by sweeping this the pot position for this variable from 0 to 1')
    parser.add_argument('--filter-s-coeffs', action='store_true',
                        help='calculate s coefficients (Laplace tranform for analog circuit)')
    parser.add_argument('--filter-symbolic', action='store_true',
                        help="use component symbols, don't replace by values (only valid for linear circuits)")
    parser.add_argument('--filter-samplerate', type=float,
                        help='sample rate for calculation of filter z coefficients (with this option the symbol fs will be used)')
    parser.add_argument('--filter-variable', action='append',
                        help='set a potentiometer variable in the form name=value (can be specified multiple times)')
    parser.add_argument('--create-module',
                        help='create a loadable Guitarix module (use with --filter)')
    parser.add_argument('--print-result', action='store_true',
                        help='print result (to be used as reference)')
    parser.add_argument('--c-verbose', action='store_true',
                        help='show compiler messages when generating internal module')
    parser.add_argument('--c-tempdir',
                        help='temp dir for module generation; not removed when finished')
    parser.add_argument('--c-float', action='store_true',
                        help='use float instead of double in c module')
    parser.add_argument('--c-debug-load',
                        help='load module (generated with --c-tempdir) instead of generating a new one')
    parser.add_argument('--c-samplerate', type=float,
                        help='sample rate for calculation of c module)')

    args = parser.parse_args()
    g = vars(circ)
    tests = []
    for t in args.test:
        if not (t in g and is_test(g[t])):
            tt = t + "_test"
            if not (tt in g and is_test(g[tt])):
                parser.error("%s is not a test" % t)
            t = tt
        tests.append(t)
    if args.check:
        if not tests:
            tests = [k for k, v in g.items() if is_test(v) and hasattr(v, 'result')]
            tests.sort()
        tn = [t[:-5] if t.endswith("_test") else t for t in tests]
        mlen = reduce(max, [len(t) for t in tn], 0)
        for t, nm in zip(tests, tn):
            sys.stdout.write("%-*s: " % (mlen, nm))
            sys.stdout.flush()
            v = g[t]()
            sys.stdout.write("%s\n" % v.check(t, args))
    elif args.func:
        t = os.path.splitext(os.path.basename(args.func))[0]
        class sweep(object):
            def __init__(self, startfreq=30, stopfreq=20000, timespan=1, pre = 0.01, post = 0.01):
                for i in "startfreq", "stopfreq", "timespan", "pre", "post":
                    setattr(self, i, vars()[i])
                self.amplitude = 1
            def __rmul__(self, m):
                self.amplitude *= m
                return self
            __mul__ = __rmul__
        class sine_signal(object):
            def __init__(self, freq=200, timespan=0.1):
                self.freq = freq
                self.timespan=timespan
                self.amplitude = 1
            def __rmul__(self, m):
                self.amplitude *= m
                return self
            __mul__ = __rmul__

        d = dict(sweep=sweep, sine_signal=sine_signal, circ=circ)
        try:
            with open(args.func) as f:
                exec f in d
        except IOError:
            raise SystemExit("error: can't open %s" % args.func)
        class params(object):
            jacobi_estimate_error = 0.1
        for k, v in d.items():
            if k != 'sweep' and not k.startswith("__"):
                setattr(params, k, v)
        if hasattr(params, "load_schema") or hasattr(params, "load_netlist"):
            v = LoadedSchema(params)
        else:
            v = params.schema()
        tg = TableGenerator(v, args, t, params)
        if hasattr(v, "signal"):
            x = v.timeline()
            s = v.signal()
            tg.p.x = tg.p.x0
            tg.p.v0 = tg.p.v00
            y1 = tg.p(s)
            pl.plot(x, y1, label="solver")
            y2 = tg.pt(s)
            pl.plot(x, y2, label="table")
            #
            #parser = dk_simulator.Parser(v.S, v.V, v.FS, not args.backward_euler)
            #p2 = dk_simulator.get_executor(t+"_table", parser, v.solver, args.pure_python,
            #                               c_debug_load="gencode/dk_sim_1.so")
            #y3 = p2(s)
            #pl.plot(x, y3, label="reloaded")
            #print np.max(abs(y3 - y1))
            #
            pl.grid()
            pl.legend()
            pl.show()
    elif args.show:
        t = tests[0]
        v = g[t]()
        parser = dk_simulator.Parser(v.S, v.V, v.FS, not args.backward_euler)
        p = dk_simulator.get_executor(
            t, parser, v.solver, args.pure_python, c_tempdir=args.c_tempdir,
            c_verbose=args.c_verbose, c_debug_load=args.c_debug_load)
        a = v.op_signal(timespan=1.02)
        smpl = lambda tm: int(round(tm*v.FS))
        a[:,0] += 2 * dk_lib.genlogsweep(30, 20000, v.FS, smpl(0.01), smpl(1), smpl(0.01))[0]
        ptp = p(a).ptp()
        rng = p.minmax
        ifunc = 3
        j = 0
        i = 1
        for k in range(4):
            if j == k:
            #if j <= k:
            #if k <= j:
                continue
            x = np.linspace(rng[j][0],rng[j][1],100)
            z = np.linspace(rng[k][0],rng[k][1],20)
            a = [[p0] for p0 in p.p0]
            a[j] = x
            a[k] = z
            y = dk_lib.calc_grid(p.nonlin, dk_lib.mkgrid(a))[ifunc]
            s = [slice(None)] * len(a)
            for n in range(len(s)):
                if n not in (j,k):
                    s[n] = 0
            pl.subplot(3,1,i)
            i += 1
            t = y[s]
            if j > k:
                t = t.T
            else:
                t = t
            if 0:
                t = np.diff(t, 2, axis=0)
                x = x[:-2]
            if 0:
                t = np.diff(t, 1, axis=0)
                x = x[:-1]
            for ii, tt in enumerate(t.T):
                off = 0
                if j == 0 and k == 1:
                    off = -0.55 * z[ii]
                if j == 0 and k == 2:
                    off = 0.9 * z[ii]
                if j == 0 and k == 3:
                    off = -0.9 * z[ii]
                off = 0
                pl.plot(x+off, tt)
            t = correlate(t[:,1:],t[:,:1],'same')
            m = t.argmax(axis=0)
            #pl.plot(np.diff(m))
            idx = (m, range(len(m)))
            #pl.plot(x[m], t[idx])
            pl.title("%d, %d" % (j, k))
            pl.grid()
        pl.show()
    elif args.filter:
        try:
            create_filter(g, tests, args)
        except ArgumentError as e:
            parser.error(e)
    else:
        plot_output(g, tests, args)


if __name__ == "__main__":
    main()

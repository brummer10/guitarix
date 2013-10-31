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

import dk_simulator
import sys; sys.path.extend(["..","../tensbs"]); import gentables, splinetable; from cStringIO import StringIO
import itertools, fractions, os
import pylab as pl
import numpy as np
from scipy.signal import correlate
from dk_lib import printoptions
import circ, models

def calc_grid(func, grd, nvals):
    grd_shape = grd.shape
    numpoints = np.product(grd_shape[1:])
    grd = grd.reshape(grd_shape[0], numpoints)
    fnc = func(grd.T).T
    return fnc.reshape((nvals,)+grd_shape[1:])

class ValueGrid(object):

    def __init__(self, func, ranges, nvals):
        self.ranges = ranges
        self.grd = np.mgrid[ranges]
        self.values = calc_grid(func, self.grd, nvals)
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


class MyTensorSpline(splinetable.TensorSpline):
    def __init__(self, func, ranges, basegrid):
        self.func = func
        self.ranges = ranges
        self.basegrid = basegrid
        self.knot_data = np.empty((len(basegrid), len(ranges)), dtype=object)
        bg = []
        self.coeffs = []
        for i_fnc, (rng, pre, post, err, opt) in enumerate(basegrid):
            len_order = []
            grd, fnc, axes, axgrids = self.table_approximation(-err, i_fnc)
            self.coeffs.append(fnc)
            for i, (ax, ag, cg) in enumerate(zip(axes, axgrids, func.basegrid[i_fnc][0])):
                #order = cg[1]
                order = 2
                idx = np.array(np.rint((ax-ax[0])/(ax[-1]-ax[0])*ag), dtype=int)
                self.knot_data[i_fnc, i] = self.mk_result(idx, ax, order, slice(ax[0], ax[-1], (ag+1)*1j))
                len_order.append((ag+1, order))
            bg.append([len_order, pre, post, err, opt])
        self.basegrid = bg
        print bg

    def calc_coeffs(self):
        return self.coeffs

    def mk_result(self, idx, kn, k, r):
        f = reduce(fractions.gcd, idx)
        idx /= f
        a = np.empty(idx[-1], dtype=np.int32)
        for m, (i, j) in enumerate(itertools.izip_longest(idx[:-1], idx[1:])):
            a[i:j] = m
        a += k-1
        return splinetable.KnotData(np.pad(kn, k-1, 'edge'), a, slice(r.start, r.stop, 1+(r.step-1)/f), k)

    def table_approximation(self, prec, i_fnc):
        def ncalc_grid(grd):
            return self.calc_grid(grd, None, None)[i_fnc]
        n = len(self.ranges)
        axes = [np.array((r[0],r[1]), dtype=np.float64) for r in self.ranges]
        axgrids = np.ones(n)
        if len(axes) > 1:
            grd = np.array(np.meshgrid(*axes, indexing='ij'))
        else:
            grd = np.empty((1, len(axes[0])))
            grd[0] = axes[0]
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
                ax2 = (a[:-1]+a[1:]) * 0.5
                axeslist = axes[:i] + [ax2] + axes[i+1:]
                if len(axeslist) > 1:
                    grd2 = np.array(np.meshgrid(*axeslist, indexing='ij'))
                else:
                    grd2 = np.empty((1, len(axeslist[0])))
                    grd2[0] = axeslist[0]
                fnc2 = ncalc_grid(grd2)
                s1[i] = slice(None, -1)
                s2[i] = slice(1, None)
                fnc_intp = (fnc[s1] + fnc[s2]) * 0.5
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
            print i_fnc, axgrids
            if not inserted:
                return grd, fnc, axes, axgrids


class TableGenerator(object):

    def __init__(self, v, args, name, param):
        p = dk_simulator.Parser(v.S, v.V, v.FS, v.solver, not args.backward_euler, args.pure_python,
                                c_tempdir=args.c_tempdir, c_verbose=args.c_verbose, c_debug_load=args.c_debug_load)
        a = v.op_signal(timespan=1.02, op=p.op)
        smpl = lambda tm: int(round(tm*v.FS))
        a[:,0] += param.input_signal.amplitude * circ.genlogsweep(
            param.input_signal.startfreq, param.input_signal.stopfreq, v.FS,
            smpl(param.input_signal.pre), smpl(param.input_signal.timespan), smpl(param.input_signal.post))[0]
        ptp = p(a).ptp()
        print "ptp =", ptp
        print "nonlin function: OP value, range:"
        print np.column_stack((p.p0, p.minmax))

        nvals = p.Mi.shape[0]
        J, vals = estimate_max_jacobi(p.nonlin, p.minmax, param.jacobi_estimate_error, nvals)
        J = np.matrix(J)
        dv = np.amax(np.append(abs(p.Fo), abs(p.Fo)*J*abs(p.G0)*abs(p.Co), axis=0), axis=0).A
        E = param.maxerr * ptp / np.where(dv == 0, 1e-20, dv)
        print "function error limits for max out error %g: %s" % (param.maxerr, ", ".join(["%.2g" % vv for vv in E.T]))

        grd_shape = vals.grd.shape
        numpoints = np.product(grd_shape[1:])
        grd = vals.grd.reshape(grd_shape[0], numpoints)
        fnc = vals.values.reshape(nvals, numpoints)
        with printoptions(precision=2, linewidth=200):
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
                [((1500, 4),), None, None, -E.T[0], True],
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
        extra_sources = (",'data.cc'", ("data.cc", o.getvalue()), ("data.h", h.getvalue()), ("intpp_inst.cc", inst.getvalue()))
        pt = dk_simulator.Parser(
            v.S, v.V, v.FS, dict(method="table",name=name,maptype=maptype), not args.backward_euler, args.pure_python,
            "gencode", c_verbose=args.c_verbose, extra_sources=extra_sources, c_debug_load=c_debug_load)
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

    def print_intpp_data(self, p):
        o = StringIO()
        print >>o, "namespace %s {" % p.comp_id
        r, order_tab, max_idx = splinetable.print_intpp_data(o, "", "", p, p.ranges, p.basegrid)#, MyTensorSpline)
        print >>o, "splinecoeffs sc[%d] = {" % p.NVALS
        f_set = set()
        for j, row in enumerate(order_tab):
            inst = "splinedata::splev<%s>" % ",".join([str(v) for v in row if v is not None])
            f_set.add(inst)
            print >>o, "\t{x0_%d, xe_%d, hi_%d, n_%d, nmap_%d, map_%d, t_%d, c_%d, %s}," % (j, j, j, j, j, j, j, j, inst)
        print >>o, "};"
        print >>o, "splinedata sd = {"
        print >>o, "\tsc,"
        print >>o, "\t%d, /* number of calculated values */" % p.NVALS
        print >>o, "\t%d, /* number of input values */" % p.N_IN
        print >>o, "\t%d, /* number of output values */" % (p.NVALS-(p.NDIM-p.N_IN))
        print >>o, "\t%d, /* number of state values */" % (p.NDIM-p.N_IN)
        print >>o, '\t"%s",' % p.comp_id
        print >>o, "};"
        print >>o, "}; /* ! namespace %s */" % p.comp_id
        o.seek(0)
        return r, o.read(), f_set, p.comp_name, p.comp_id, max_idx

    def write_files(self, comp, o, inst, h):
        procs = [self.print_intpp_data(comp)]
        max_idx_all = 0
        for p in procs:
            s, f, i, comp_name, comp_id, max_idx = p
            max_idx_all = max(max_idx_all, max_idx)
        if max_idx >= 2**16:
            maptype = "int"
        elif max_idx >= 2**8:
            maptype = "unsigned short"
        else:
            maptype = "unsigned char"
        o.write("typedef %s maptype;\n" % maptype)
        gentables.print_header_file_start(h)
        sz = gentables.print_header(o)
        l = []
        templ = set()
        for p in procs:
            s, f, i, comp_name, comp_id, max_idx = p
            o.write(f)
            templ |= i
            l.append("%s: %d bytes" % (comp_name, s))
            sz += s
            gentables.print_header_file_entry(h, comp_id)
        sz += gentables.print_footer(o)
        l.append("data size sum: %d bytes" % sz)
        print >>o, "".join(["\n// " + s for s in l])
        gentables.print_header_file_end(h)
        for v in sorted(templ):
            print >>inst, "template int %s(splinecoeffs *p, real xi[2], real *res);" % v
        return maptype

def load_schema(params):
    import mk_netlist
    v = vars(models)
    v["Tubes"] = circ.Tubes
    exec mk_netlist.read_netlist(params.load_schema) in v
    class LoadedSchema(circ.Test):
        def __init__(self, v, params):
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
    return LoadedSchema(v, params)

def main():
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('test', nargs="*", help='name of test')
    parser.add_argument('-c', '--check', action='store_true', help='check results of tests')
    parser.add_argument('-b', '--backward-euler', action='store_true', help='use Backward-Euler integration instead of trapezoidal')
    parser.add_argument('-p', '--pure-python', action='store_true', help='do not generate C code to speed up calculations')
    parser.add_argument('-f', '--func', help='function table generation')
    parser.add_argument('-s', '--show', action='store_true', help='plot nonlinear function')
    parser.add_argument('-y', '--symbolic', action='store_true', help='show formula for linear circuit')
    parser.add_argument('-S', '--schema', help='use gschem .sch file as input')
    parser.add_argument('--print-result', action='store_true', help='print result (to be used as reference)')
    parser.add_argument('--c-verbose', action='store_true', help='show compiler messages when generating internal module')
    parser.add_argument('--c-tempdir', help='temp dir for module generation; not removed when finished')
    parser.add_argument('--c-debug-load', help='load module (generated with --c-tempdir) instead of generating a new one')
    
    args = parser.parse_args()
    def is_test(v):
        return isinstance(v, type) and issubclass(v, circ.Test) and v is not circ.Test
    g = vars(circ)
    tests = []
    for t in args.test:
        if not (t in g and is_test(g[t])):
            tt = t + "_test"
            if not (tt in g and is_test(g[tt])):
                if args.symbolic:
                    continue
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
            try:
                p = dk_simulator.Parser(v.S, v.V, v.FS, v.solver, not args.backward_euler, args.pure_python,
                                        c_tempdir=args.c_tempdir, c_verbose=args.c_verbose, c_debug_load=args.c_debug_load)
            except Exception as v:
                raise
            else:
                try:
                    y = p(v.signal())
                except ValueError as v:
                    print v
                else:
                    sys.stdout.write("%s [%.2g]\n" % (v.compare_data(y), p.time_per_sample))
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
                
        d = dict(sweep=sweep, sine_signal=sine_signal)
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
        v = load_schema(params)
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
            #p2 = dk_simulator.Parser(v.S, v.V, v.FS, v.solver, not args.backward_euler, args.pure_python,
            #                         c_debug_load="gencode/dk_sim_1.so")
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
        p = dk_simulator.Parser(v.S, v.V, v.FS, v.solver, not args.backward_euler, args.pure_python,
                                c_tempdir=args.c_tempdir, c_verbose=args.c_verbose, c_debug_load=args.c_debug_load)
        a = v.op_signal(timespan=1.02)
        smpl = lambda tm: int(round(tm*v.FS))
        a[:,0] += 2 * genlogsweep(30, 20000, v.FS, smpl(0.01), smpl(1), smpl(0.01))[0]
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
            y = calc_grid(p.nonlin, np.array(np.meshgrid(*a, indexing='ij')))[ifunc]
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
    elif args.symbolic:
        if args.schema:
            v = load_schema(args.schema)
        else:
            v = g[tests[0]]()
        dk_simulator.Parser(v.S, v.V, v.FS, v.solver, not args.backward_euler, args.pure_python,
                            c_tempdir=args.c_tempdir, c_verbose=args.c_verbose, c_debug_load=args.c_debug_load, symbolic=True)
    else:
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
            v = g[t]()
            p = dk_simulator.Parser(v.S, v.V, v.FS, v.solver, not args.backward_euler, args.pure_python,
                                    c_tempdir=args.c_tempdir, c_verbose=args.c_verbose, c_debug_load=args.c_debug_load)
            y = p(v.signal())
            if 0:
                for i, (p0, (s, e)) in enumerate(zip(p.p0, p.minmax)):
                    print "%d: %g [%g .. %g]" % (i, p0, s, e)
            v.plot(y, p.out_labels())
            if args.print_result:
                v.print_data(y)


if __name__ == "__main__":
    main()

from __future__ import division
import sympy, math, shutil, sys, os, numpy, pylab, warnings, tempfile
from cStringIO import StringIO
import dk_simulator, models, circ, mk_netlist, dk_lib, simu, signals, generate_code
from signals import Signal
from dk_lib import CircuitException

try:
    get_ipython
except NameError:
    pass
else:
    def _circuit_exception_handler(self, etype, value, tb, tb_offset=None):
        print "error:", value
    get_ipython().set_custom_exc((CircuitException,), _circuit_exception_handler)


def check_keywords(fname, kw, *keywords):
    for k in kw:
        if k not in keywords:
            raise CircuitException("%s: unknown keyword '%s'" % (fname, k))

class NonlinComponent(object):

    def __init__(self):
        self.max_jacobi_error = None
        self.max_jacobi = None
        self.ptp = None
        self.nonlin_range = None
        self.max_error = None
        self.basegrid = None


class DC_Values(object):
    def __init__(self, v, x, p, o):
        self.v = v
        self.x = x
        self.p = p
        self.o = o
    def show(self):
        with dk_lib.printoptions(linewidth=200):
            print "v =", self.v
            print "x =", self.x
            print "p =", self.p.A1
            print "o =", self.o

SIM_PY, SIM_C, SIM_TABLE = range(3)

class Circuit(object):

    have_plot = False

    def __init__(self, copy_from=None, FS=96000):
        self.tempdir = None
        self.tempdir_keep = False
        self.backward_euler = False
        self.solver = None
        self.build_verbose = False
        self.module_id = None
        self.module_name = None
        self.module_desc = None
        self.c_datatype = "double"
        self.table_datatype = "double" #"float"
        self.pre_filter = None
        self.post_filter = None
        self.code_generator = None
        self.FS = FS
        self.use_sim = SIM_C
        self._clear()
        self._rmtree = shutil.rmtree
        if copy_from is not None:
            self.backward_euler = copy_from.backward_euler
            self.solver = copy_from.solver
            self.FS = copy_from.FS
            self.S = copy_from.S
            self.V = copy_from.V
    
    #
    # internal routines
    #

    def _clear(self):
        self.max_homotopy_iter = None
        self.dc_method = "A"
        self.sys_reduce_tol = 0
        self.solver_params = None
        self.partition = False
        self._clear_all()

    def _clear_calculated(self):
        self.eq = None
        self.sim_py = None
        self.sim_c = None
        self.sim_table = None
        self.sim_filter = None
        self.dc_values = None
        self.components = None
        self.ptp = None
        self.minmax = None
        self.E = None
        self.basegrid = None
        self.knot_positions = None
        self.table_source = None

    def _clear_all(self):
        self.S = None
        self.V = None
        self.loaded_filename = None
        self.parser = None
        self._clear_calculated()

    def __del__(self):
        self._remove_tempdir(True)

    def _remove_tempdir(self, ignore_errors=False):
        if self.tempdir is None:
            return
        if self.tempdir_keep:
            return
        self._rmtree(self.tempdir, ignore_errors=ignore_errors)

    def _ensure_parser(self, symbolic=False, for_filter=False):
        if self.parser is None or not self.parser.matches(symbolic, for_filter):
            if self.S is None:
                raise CircuitException("no netlist defined")
            if self.V is None and not symbolic:
                raise CircuitException("no netlist values defined")
            self.parser = dk_simulator.Parser(self.S, self.V, self.FS, not self.backward_euler, for_filter, symbolic)

    def _ensure_eq(self):
        if self.eq is None:
            self._ensure_parser()
            self.eq = dk_simulator.EquationSystem(self.parser, partition=self.partition)

    def _ensure_sim_py(self):
        if self.sim_py is None:
            self._ensure_eq()
            try:
                self.sim_py = dk_simulator.SimulatePy(self.eq, self.solver, self.dc_method)
                if self.sys_reduce_tol >= 0:
                    self.sim_py.balance_realization(self.sys_reduce_tol)
            except dk_simulator.ConvergenceError as e:
                raise CircuitException(e)

    def _ensure_dc_values(self):
        if self.dc_values is None:
            self._ensure_sim_py()
            self.dc_values = DC_Values(self.sim_py.v00, self.sim_py.x0, self.sim_py.p0, self.sim_py.o0)

    def _ensure_sim_c(self):
        if self.sim_c is None:
            self._ensure_dc_values()
            if self.tempdir is None:
                self.tempdir = tempfile.mkdtemp("_dk_compile")
            modc = dk_simulator.BuildCModule(
                self._get_module_id(), self.sim_py, c_tempdir=self.tempdir,
                c_verbose=self.build_verbose, c_real=self.c_datatype, pre_filter=self.pre_filter, post_filter=self.post_filter)
            if self.max_homotopy_iter is not None:
                modc.max_homotopy_iter = self.max_homotopy_iter
            if self.solver_params is not None:
                modc.solver_params = self.solver_params
            self.c_module, self.sim_c = modc.get_executor()

    def calc_range(self, signal):
        self._ensure_sim_c()
        s = self.make_signal_vector(signal)
        self.ptp = self.sim_c(s.input_signal).ptp()
        pot_arr = numpy.array([[0., 1.] * len(self.sim_c.pot_list)])
        if pot_arr.size:
            self.minmax = numpy.append(pot_arr, self.sim_c.minmax, axis=0)
        else:
            self.minmax = self.sim_c.minmax
        print self.ptp
        print repr(self.minmax)

    def _ensure_range(self):
        if self.minmax is None:
            sig = Signal()
            self.calc_range(sig(3*sig.sweep(), timespan=2))

    def _ensure_max_error(self):
        if self.E is None:
            if not self.sim_c.nno:
                self.E = [0]
                return
            self._ensure_eq()
            jacobi_estimate_error = 10#1e-1
            maxerr = 1e-4
            J, vals = simu.estimate_max_jacobi(self.sim_c.nonlin, self.minmax, jacobi_estimate_error, self.sim_c.nno)
            J = J[:,J.shape[1]-J.shape[0]:] ##FIXME
            J = numpy.matrix(J)
            dv = numpy.amax(numpy.append(abs(self.eq.Fo), abs(self.eq.Fo)*J*abs(self.eq.G0)*abs(self.eq.Co), axis=0), axis=0).A1
            self.E = maxerr * self.ptp / numpy.where(dv == 0, 1e-20, dv)
            print "E =", self.E

            grd_shape = vals.grd.shape
            numpoints = numpy.product(grd_shape[1:])
            grd = vals.grd.reshape(grd_shape[0], numpoints)
            fnc = vals.values.reshape(self.eq.nno, numpoints)
            self.cov = numpy.cov(grd, fnc)[:len(grd),len(grd):]
            print self.cov

    def _ensure_basegrid(self):
        if self.basegrid is None:
            raise CircuitException("missing base grid values")

    def _ensure_knot_positions(self):
        #if self.knot_positions is None:
        #    xx
        pass

    def _ensure_table_source(self):
        if self.table_source is None:
            if self.sim_c.nno == 0:
                self.table_source = {}
                self.maptype = None
                return
            self._ensure_eq()
            o = StringIO()
            inst = StringIO()
            h = StringIO()
            npl = self.sim_c.npl
            tables = []
            if not npl:
                i0v = self.sim_c.nonlin_c(self.sim_c.p0.T)[0]
            if len(self.sim_c.comp_sz) > 1:
                j = 0
                for i, sz in enumerate(self.sim_c.comp_sz):
                    #sl = [0]+range(j+1, j+1+sz[1])
                    sl = range(j, j+sz[1]) ##FIXME
                    class Comp:
                        comp_id = "nonlin_%d" % i
                        comp_name = "nonlin_%d" % i
                        ranges = self.minmax[sl] ##FIXME
                        basegrid = numpy.array([(g, None, None, e, True) for g, e in zip(self.basegrid, self.E)])[j:j+sz[1]]
                        NVALS = sz[2] # nno
                        N_IN = sz[1]+npl # nni+npl
                        NDIM = sz[1]+npl # nni+npl
                        if not npl:
                            i0 = i0v[sl]
                        @staticmethod
                        def __call__(v, with_state):
                            return self.sim_c.c_calc_comp[i](v)
                    j += sz[1]
                    ##FIXME: maptype
                    self.maptype, spl = simu.TableGenerator.write_files(Comp(), o, inst, h)
                    c = Comp()
                    tables.append(spl)
            else:
                class Comp:
                    comp_id = "nonlin"
                    comp_name = self._get_module_id()
                    ranges = self.minmax
                    basegrid = [(g, None, None, e, False) for g, e in zip(self.basegrid, self.E)]
                    NVALS = self.eq.nno
                    N_IN = self.eq.nni+npl
                    NDIM = self.eq.nni+npl
                    @staticmethod
                    def __call__(v, with_state):
                        return self.sim_c.nonlin(v)
                self.maptype, spl = simu.TableGenerator.write_files(Comp(), o, inst, h)
                tables.append(spl)
            intpp_inst = "\n".join(set(inst.getvalue().split("\n")))
            self.table_source = dict(data_c=o.getvalue(), data_h=h.getvalue(), intpp_inst=intpp_inst, tables=tables)

    def _ensure_sim_table(self):
        if self.sim_table is None:
            self._ensure_sim_c()
            self.sim_c.reset()
            self._ensure_range()
            self._ensure_max_error()
            self._ensure_basegrid()
            self._ensure_knot_positions()
            self._ensure_table_source()
            name = self._get_module_id()
            self._ensure_sim_py()
            if self.solver is None:
                solver = {}
            else:
                solver = self.solver.copy()
            solver["method"] = "table"
            modc = dk_simulator.BuildCModule(
                name, self.sim_py, solver=solver,
                extra_sources=self.table_source, c_tempdir="gencode",
                c_verbose=self.build_verbose, c_real=self.table_datatype,
                pre_filter=self.pre_filter, post_filter=self.post_filter,
                generator=self.code_generator)
            modc.resample = True
            self.table_module, self.sim_table = modc.get_executor()

    def _get_sim(self):
        if self.use_sim == SIM_C:
            self._ensure_sim_c()
            return self.sim_c
        elif self.use_sim == SIM_TABLE:
            self._ensure_sim_table()
            return self.sim_table
        else:
            assert self.use_sim == SIM_PY
            self._ensure_sim_py()
            return self.sim_py

    def _ensure_filter(self, symbolic):
        self._ensure_parser(symbolic=symbolic, for_filter=True)
        if len(self.parser.get_nonlin_funcs()) > 0:
            if symbolic:
                raise CircuitException("ciruit is nonlinear: symbolic formula generation not supported")
            p = dk_simulator.Parser(self.S, self.V, self.FS, not self.backward_euler)
            sim = dk_simulator.SimulatePy(dk_simulator.EquationSystem(p), self.solver, self.dc_method)
            J = sim.jacobi()
        else:
            J = None
        self.sim_filter = dk_simulator.LinearFilter(self.parser, J)

    def _check_netlist(self):
        if self.S is None:
            raise CircuitException("no netlist loaded")

    def _get_module_id(self, module_id=None):
        if module_id is not None:
            return module_id
        if self.module_id is not None:
            return self.module_id
        if self.loaded_filename is not None:
            return os.path.splitext(os.path.basename(self.loaded_filename))[0]
        return "sim_module"

    def _nodes_from_names(self, elements):
        d = {}
        elset = set()
        for e in self.parser.element_name["N"]:
            e = e[0]
            elset.add(e)
            d[str(e)] = e
        l = []
        for e in elements:
            if e in d:
                l.append(d[e])
            elif e in elset:
                l.append(e)
            else:
                raise CircuitException("%s unknown. nonlinear circuit elements: %s"
                                       % (e, ", ".join(d.keys())))
        return l

    def _nonlin_function_list(self, elements):
        elements = self._nodes_from_names(elements)
        el = {}
        if elements:
            for i, e in enumerate(self.parser.element_name["N"]):
                if e[0] in elements:
                    e = e[0]
                    if e not in el:
                        el[e] = []
                    el[e].append(i)
        else:
            for i, e in enumerate(self.parser.element_name["N"]):
                e = e[0]
                if e not in el:
                    el[e] = []
                el[e].append(i)
        return el

    #
    # user interface
    #

    def show_status(self):
        if self.loaded_filename:
            print "circuit loaded from: %s" % self.loaded_filename
        if self.S:
            print "circuit element count: %d" % len(self.S)
        if self.module_id:
            print "module id: %s" % self.module_id
        if self.tempdir:
            print "temp dir: %s" % self.tempdir
        if self.tempdir_keep:
            print "keep temp dir: %s" % self.tempdir_keep
        if self.parser:
            print "Parser: %s" % self.parser.get_status()
        if self.eq:
            print "EquationSystem: %s" % self.eq.get_status()
        if self.sim_c:
            print "C Executor: %s, %d" % (self.sim_c.soname, self.sim_c.nx)

    def make_signal_vector(self, signal):
        if self.sim_py:
            op = self.sim_py.op
        if self.sim_c:
            op = self.sim_c.op
        else:
            self._ensure_parser()
            op = self.parser.op
        return Signal().generate(signal, self.FS, op)

    def print_netlist(self):
        self._check_netlist()
        for row in self.S:
            print "%s: %s" % (row[0], ", ".join([str(v) for v in row[1:]]))

    def read_gschem(self, filename):
        self._clear_all()
        v = vars(models)
        v["Tubes"] = circ.Tubes
        v["math"] = math
        exec mk_netlist.read_netlist(filename) in v
        self.S = v["S"]
        self.V = v["V"]
        self.loaded_filename = filename

    def read_netlist(self, filename):
        self._clear_all()
        v = vars(models)
        v["Tubes"] = circ.Tubes
        v["math"] = math
        with open(filename) as f:
            exec f in v
        self.S = v["S"]
        self.V = v["V"]
        self.loaded_filename = filename

    def set_netlist(self, S, V=None):
        self._clear_all()
        self.S = S
        self.V = V

    def set_tempdir(self, path):
        self._remove_tempdir()
        self.tempdir = path

    def keep_tempdir(self, keep=True):
        self.tempdir_keep = keep
        self._remove_tempdir()

    def set_use(self, use):
        self.use_sim = use

    def set_samplerate(self, fs):
        self._clear_calculated()
        self.parser = None
        self.FS = fs

    def set_float(self, use_float=True):
        self.c_datatype = "float" if use_float else "double"

    def set_solver(self, solver):
        self.solver = generate_code.solver_set_defaults(solver)

    def load_module(self, filename, clear_all=True):
        sim_c = dk_simulator.SimulateC(filename)
        if not clear_all and self.FS != sim_c.fs:
            raise CircuitException("Samplerate mismatch: %d / %d" % (self.FS, sim_c.FS))
        if clear_all:
            self._clear_all()
            self.FS = sim_c.fs
        self.sim_c = sim_c

    def set_module_id(self, module_id):
        self.module_id = module_id

    def add_element(self, element, connections, value):
        self._check_netlist()
        self.S = list(self.S) + [(element,)+tuple(connections)]
        self.V[element] = value
        self._clear_calculated()
        if self.parser is not None:
            self.parser.update(self.S, self.V)
        return

    def remove_element(self, element):
        self._check_netlist()
        self.S = list(self.S)
        for i, row in enumerate(self.S):
            if str(row[0]) == element:
                del self.S[i]
                self._clear_calculated()
                if self.parser is not None:
                    self.parser.update(self.S, self.V)
                return
        raise CircuitException("%s not found int netlist" % element)

    def remove_connected(self, net):
        self._check_netlist()
        self.S = list(self.S)
        comp = set(net)
        found = False
        while True:
            for i, row in enumerate(self.S):
                for c in row[1:]:
                    if c in comp:
                        comp |= set(row[1:])
                        del self.S[i]
                        found = True
                        break
        if not found:
            raise CircuitException("net %s not found" % net)
        self._clear_calculated()
        self.parser.update(self.S, self.V)

    def join_net(self, net, target_net):
        self._check_netlist()
        l = []
        found = False
        for i, row in enumerate(self.S):
            for j, c in enumerate(row[1:]):
                if c == net:
                    l.append((i, j, c))
                elif c == target_net:
                    found = True
        if not found:
            raise CircuitException("target_net %s not found" % target_net)
        if not l:
            raise CircuitException("net %s not found" % net)
        S = list(self.S)
        for i, j, c in l:
            S[i] = list(S[i])
            S[i][j+1] = target_net
        self.S = S
        self._clear_calculated()
        if self.parser is not None:
            self.parser.update(self.S, self.V)

    def print_func_names(self):
        self._ensure_parser()
        print ", ".join(["%s:%s" % e for e in self.parser.element_name["N"]])

    def get_dc_values(self):
        self._ensure_dc_values()
        return self.dc_values

    def linearize(self, *elements, **kw):
        check_keywords("linearize", kw, "keep_dc")
        keep_dc = kw.get('keep_dc', len(elements) != 0)
        self._ensure_parser()
        el = self._nonlin_function_list(elements)
        S = [tuple([models.NODES]+[v[1] for v in sorted([(v, k) for k, v in self.parser.nodes.items()])])]
        for e in self.S:
            if e[0] in el:
                if isinstance(e[0], models.CC_N):
                    e = (models.CC_L(e[0].d),) + e[1:]
                elif isinstance(e[0], (models.Trans_F, models.Trans_GC)):
                    #FIXME calculate R (Trans_L parameter)
                    e = (models.Trans_L(e[0].d),) + e[1:]
            S.append(e)
        self.S = S
        self.parser.update(S, self.V)
        self.eq = None
        self.sim_py = None
        self.dc_values = None
        self._ensure_dc_values()
        el = self._nonlin_function_list(elements)
        J = self.sim_py.jacobi()
        Jc = self.sim_py.calc_i(self.dc_values.v)
        S = []
        V = dict(self.V)
        Nr = self.parser.N["Nr"]
        Nl = self.parser.N["Nl"]
        nodes = list(sorted(self.parser.nodes.keys(), key=lambda v: self.parser.nodes[v]))
        def idx(a, v):
            a = numpy.nonzero(numpy.ravel(a == v))[0]
            if len(a) == 0:
                return models.GND
            else:
                return nodes[int(a)]
        for e in self.S:
            if e[0] in el:
                for i in el[e[0]]:
                    jl = J[i].nonzero()[1].A1
                    for j in jl:
                        v = models.VCCS(str(e) + "l%d%d" % (i, j))
                        S.append((v, idx(Nl[j], 1), idx(Nl[j], -1), idx(Nr[i], 1), idx(Nr[i], -1)))
                        dG = -J[i,j]
                        if keep_dc:
                            i0 = Jc[i]/len(jl) + dG*self.dc_values.v[j]
                        else:
                            i0 = 0
                        V[v] = dict(dG = dG, i0 = i0)
            elif not keep_dc and isinstance(e[0], models.V):
                V[e[0]] = 0
                S.append(e)
            else:
                S.append(e)
        self.S = S
        self.V = V
        self.parser.update(S, V)
        self.eq = None
        self.sim_py = None
        self.dc_values = None

    def print_filter_coeffs(self, symbolic=False, filename=None):
        self._ensure_filter(symbolic=symbolic)
        if filename is not None:
            f = open(filename, "w")
        else:
            f = sys.stdout
        b, a, terms = self.sim_filter.get_s_coeffs()
        self.sim_filter.print_coeffs('b', b, f)
        self.sim_filter.print_coeffs('a', a, f)
        B, A, c = self.sim_filter.transform_bilinear(terms)
        print >>f, "\nc = %s;" % c
        self.sim_filter.print_coeffs('B', B, f)
        self.sim_filter.print_coeffs('A', A, f)
        if filename is not None:
            f.close()

    def save_faust_code(self, symbolic=False, filename=None):
        self._ensure_filter(symbolic=symbolic)
        b, a = self.sim_filter.get_z_coeffs(samplerate=self.FS)
        l = self.parser.get_pot_attr()
        m_id = self._get_module_id()
        dsp, ui = simu.generate_faust_module(m_id, b, a, l, self.sim_filter)
        ##FIXME where to save ui code?
        if filename is None:
            sys.stdout.write(dsp)
        else:
            with open(filename,"w") as f:
                f.write(dsp)

    def create_faust_module(self, module_id=None, symbolic=False, FS=None, pre_filter=None):
        self._ensure_filter(symbolic=symbolic)
        b, a = self.sim_filter.get_z_coeffs(samplerate=FS)
        l = self.parser.get_pot_attr()
        m_id = self._get_module_id(module_id)
        simu.build_faust_module(m_id, b, a, l, self.sim_filter, self.c_datatype, pre_filter)

    def stream(self, signal):
        if not isinstance(signal, signals.GeneratedSignal):
            signal = self.make_signal_vector(signal)
        sim = self._get_sim()
        self.last_signal = signal
        self.last_output = sim(signal.input_signal)
        return self.last_output

    def plot(self, sig=None, label=None, clip=-80, nharmonics=8, spectrum=None, freq_range=None):
        if sig is not None:
            self.stream(sig)
        if self.last_output is None:
            raise CircuitException("nothing to plot")
        ls = self.last_signal
        if freq_range is not None:
            lower_freq, upper_freq = freq_range
        else:
            lower_freq = upper_freq = None
        if lower_freq is None:
            lower_freq = ls.start_freq
        if upper_freq is None:
            upper_freq = ls.stop_freq
        if  ls.has_harmonics() and nharmonics > 1 and (spectrum is None or spectrum):
            lines = ls.plot_harmonic_spectrum(self.last_output, nharmonics=nharmonics, lower_freq=lower_freq, upper_freq=upper_freq)
            pylab.xlim(left=lower_freq, right=upper_freq)
            for i, line in enumerate(lines):
                if label:
                    line.set_label("%d, %s" % (i+1, label))
                else:
                    line.set_label("%d" % (i+1))
        elif (spectrum is None and ls.has_spectrum()) or spectrum:
            f = numpy.logspace(numpy.log10(lower_freq), numpy.log10(upper_freq), 200)
            h = ls.get_spectrum(self.last_output, 2*numpy.pi * f / ls.fs)
            s = 20*numpy.log10(abs(h))
            pylab.plot(f, numpy.where(s > clip, s, numpy.nan), label=label)
            pylab.xscale('log')
        else:
            lines = pylab.plot(ls.timeline, self.last_output)
            if not label:
                label = self._get_sim().out_labels
            elif isinstance(label, basestring):
                l = []
                for lbl in self._get_sim().out_labels:
                    l.append(label + "." + lbl)
                label = l
            for line, lbl in zip(lines, label):
                line.set_label(lbl)
        Circuit.have_plot = True

    def deploy(self, path=None):
        sim = self._get_sim()
        if sim is self.sim_py:
            self._ensure_sim_c()
            sim = self.sim_c
        if sim is self.sim_table:
            mod = self.table_module
            s = "table"
        else:
            mod = self.c_module
            s = "C"
        if path is None:
            path = os.path.expanduser("~/.config/guitarix/plugins/.")
        fname = os.path.join(path, self._get_module_id()+".so")
        shutil.copy(mod, fname)
        print "%s module copied to '%s'" % (s, fname)

    def set_pot_variable(self, name, val):
        self._get_sim().set_variable(name, val)

    def calc_nonlin_range(self, signal):
        pass

    def set_nonlin_range(self, idx, low=None, high=None):
        pass

    def estimate_max_jacobi(self, max_error):
        pass

    def set_max_jacobi(self, jacobi):
        pass

    def generate_table(self):
        pass


def _create_funcs():
    gcircuit = Circuit()
    g = globals()
    g['get_global_circuit'] = lambda: gcircuit
    for v in dir(Circuit):
        if not v.startswith("_"):
            g[v] = getattr(gcircuit, v)
_create_funcs()

def show_plots(loc=None):
    if Circuit.have_plot:
        pylab.grid()
        pylab.legend(loc=loc)
        pylab.show()
        Circuit.have_plot = False

if __name__ == "__main__":
    c1 = Circuit()
    c2 = Circuit()
    c1.set_samplerate(44100)
    c2.set_samplerate(44100)
    #c1.read_gschem("wahwah.sch")
    c2.set_tempdir("gencode")
    c2.keep_tempdir()
    #set_module_id("testtest")
    if 0:
        S = ((models.NODES, 1, 2),
             (models.D(), 2, models.GND),
             (models.R(), 1, 2),
             (models.V(), 1),
             #(models.IN, 0),
             (models.OUT, 1, 2),
            )
        V = {models.D(): dict(Is=10e-12, mUt=30e-3),
             models.R(): 1e3,
             models.V(): 2,
             }
    if 0:
        S = ((models.NODES, 1, 2, 3, 4),
             (models.T(), 1, 2, 3),
             (models.R(1), 4, 2),
             (models.R(2), 4, 1),
             (models.R(3), 3, models.GND),
             (models.V(), 4),
             (models.OUT, 1, 2, 3, 4, models.V()(None)),
             )
        V = {models.T(): dict(Vt=26e-3, Is=20.3e-15, Bf=1430, Br=4),
             models.R(1): 2e6,
             models.R(2): 1e3,
             models.R(3): 1e3,
             models.V(): 5,
             }

    numpy.set_printoptions(linewidth=2000)
    c1.set_netlist(circ.WahWah_test.S, circ.WahWah_test.V)
    c2.set_netlist(circ.WahWah_test.S, circ.WahWah_test.V)
    #c1.set_netlist(S, V)
    #c2.set_netlist(S, V)
    #c1.solver = dict(method='lm', factor=1e2)
    c2.linearize(models.T(1), models.T(2))
    #c2.linearize(models.T(2))
    c2.remove_element("C2")
    c2.remove_element("R8")
    c2.join_net("V6", models.GND)
    c2.remove_element("C1")
    c2.join_net("V3", "V2")
    c2._ensure_sim_py()
    #c2.show_status()
    c1._ensure_sim_py()
    #c1.show_status()
    sig = Signal()
    if True:#False:
        c2._ensure_sim_c()
        #c2.deploy(); raise SystemExit
    else:
        c2.load_module("./%s.so" % c2._get_module_id(), False)
    c2.basegrid = [[[64, 4],[64, 4]]]  # no knot optimization
    #c2.basegrid = [[[128*8, 4],[64*2, 4]]]
    vv = 0.1
    #c2.set_use(SIM_TABLE)
    f0 = 228.606785544
    w0 = numpy.pi * f0 / c2.FS
    a1 = (w0 - 1) / (w0 + 1)
    c2.pre_filter = ("static DTP_U y; {\n"
                     "            static double xm1;\n"
                     "            y = GET_U[0] - xm1 + %s * y;\n"
                     "            xm1 = GET_U[0];\n"
                     "        }\n"
                     "#undef GET_U\n"
                     "#define GET_U (&y)\n"
                     % a1)
    if 0:
        s = c2.make_signal_vector(sig(0.8*sig.sweep(pre=1, post=0.1), timespan=10))

        c2.set_use(SIM_C)
        c2.sim_c.reset()
        c2.set_pot_variable('hotpotz', vv)
        c2.stream(s)
        c2.show_status()
        c2.plot(clip=-100, nharmonics=1, label="std")

        c2.remove_element("C1")
        c2.join_net("V3", "V2")
        c2.set_pot_variable('hotpotz', vv)
        c2.sim_c.reset()
        c2.stream(s)
        c2.show_status()
        #c2.plot(clip=-100, nharmonics=1, label="no C1")
        from scipy.signal import lfilter
        t = -0.9685
        c2.last_output = lfilter((1+t)/2*numpy.array([1, -1]), [1, t], c2.last_output, axis=0)
        c2.plot(clip=-100, nharmonics=1, label="no C1")
        if 0:
            c2.set_pot_variable('hotpotz', 0.0)
            c2.set_use(SIM_TABLE)
            c2._ensure_sim_table()
            c2.sim_table.reset()
            c2.set_pot_variable('hotpotz', vv)
            c2.stream(s)
            c2.plot(clip=-100, nharmonics=8, label="Table")

        #sg = sig(0.02*sig.sweep(), timespan=2)
        #s1 = c1.make_signal_vector(sg)
        #s2 = c2.make_signal_vector(sg)
        # for v in numpy.linspace(0,1,5):
        #     for c, s in (c1, s1), (c2, s2):
        #         c.set_pot_variable('hotpotz', v)
        #         c.stream(s)
        #         c.plot(v)
    elif 0:
        freq = 412
        c2.set_pot_variable('hotpotz', 1)
        c2.stream(sig(1*sig.sine(freq), timespan=2))
        c2.plot("0.5/%s" % freq, spectrum=True)
        c2.set_use(SIM_C)
        c2.set_pot_variable('hotpotz', 1)
        c2.stream(sig(1*sig.sine(freq), timespan=2))
        c2.plot("0.5/%s" % freq, spectrum=True)
    #pylab.legend(loc="upper left")
    #deploy("/tmp")
    #show_plots()
    c2.set_use(SIM_TABLE)
    c2.deploy()

from __future__ import division
import matplotlib
# matplotlib.use('Qt4Agg') # set when you prefer to use the Qt backend over the Tk one
import sympy, math, shutil, sys, os, numpy, pylab, warnings, tempfile, logging, argparse
from cStringIO import StringIO
import dk_simulator, models, circ, mk_netlist, dk_lib, simu, signals, generate_code
from signals import Signal
from dk_lib import CircuitException, error
import scipy.optimize as opt

try:
    get_ipython
except NameError:
    pass
else:
    def _circuit_exception_handler(self, etype, value, tb, tb_offset=None):
        print "error:", value
    get_ipython().set_custom_exc((CircuitException,), _circuit_exception_handler)


def eng_str(x):
    y = abs(x)
    exponent = int(math.log10(y))
    engr_exponent = exponent - exponent % 3
    y /= 10**engr_exponent
    if engr_exponent:
        engr_exponent = 'e' + str(engr_exponent)
    else:
        engr_exponent = ''
    return "%s%g%s" % ('-' if x < 0 else '', y, engr_exponent)

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
        self.plugindef = None
        self.build_script = None
        self.resample = True
        self.FS = FS
        self.use_sim = SIM_C
        self.sig = Signal()
        self._clear()
        self._rmtree = shutil.rmtree
        self.subcircuits = {}
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
        self.grid_error_limit = None
        self.transform_opts = dk_simulator.TransformOptions()
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
        self.input_amplitude = None
        self.sensitivity = None

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
            self.eq = dk_simulator.EquationSystem(self.parser, opts=self.transform_opts)

    def _ensure_sim_py(self):
        if self.sim_py is None:
            self._ensure_eq()
            try:
                self.sim_py = dk_simulator.SimulatePy(self.eq, self.solver, self.dc_method)
                if self.sys_reduce_tol >= 0:
                    self.sim_py.balance_realization(self.sys_reduce_tol)
                if (isinstance(self.eq.nonlin, dk_simulator.PartitionedNonlinEquations)
                    and self.transform_opts.decompose):
                    self.eq.F, self.eq.C = self.eq.nonlin.decompose_blocks(self.eq.F, self.eq.C)
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

    def _check_input_amplitude(self):
        if self.input_amplitude is None:
            raise CircuitException("please define input_amplitude")

    def calc_range(self, signal):
        self._ensure_sim_c()
        s = self.make_signal_vector(signal)
        self.ptp = self.sim_c(s.input_signal).ptp()
        pot_arr = numpy.array([[0., 1.]] * len(self.sim_c.pot_list))
        if pot_arr.size:
            self.minmax = numpy.append(pot_arr, self.sim_c.minmax, axis=0)
        else:
            self.minmax = self.sim_c.minmax
        logger = logging.getLogger("range")
        for i, r in enumerate(self.sim_c.minmax):
            logger.debug("nonlin range %d: %g .. %g" % (i, r[0], r[1]))
        #print self.ptp
        #print repr(self.minmax)

    def _ensure_range(self):
        if self.minmax is None:
            self._check_input_amplitude()
            self.calc_range(self.sig(self.input_amplitude*self.sig.sweep()))

    def _get_op(self):
        if self.sim_py:
            return self.sim_py.op
        if self.sim_c:
            return self.sim_c.op
        else:
            self._ensure_parser()
            return self.parser.op

    def _estimate_sensitivity(self, i_ptp, ii):
        self._check_input_amplitude()
        s = self.input_amplitude * self.sig.sweep()
        pert = i_ptp * 1e-7 * self.sig.sine(freq=1000)
        p = self.sig(sympy.Tuple(s, pert))
        self.sim_c.reset()
        ch = len(self._get_op()) + 1
        signal = self.sig.generate(p, self.FS, channels=ch)
        out_t = self.sim_c(signal.input_signal, ii)
        max_pert = max(abs(signal.signal[:,-1]))
        self.sim_c.reset()
        signal = self.make_signal_vector(self.sig(s))
        out_c = self.sim_c(signal.input_signal)
        df = out_t-out_c
        err = 2 * max(abs(df)) / out_c.ptp()
        return err / max_pert

    def _calc_ptp(self, idx):
        self._ensure_sim_c()
        self._ensure_range()
        def calc(sgn):
            def ff(p):
                return -sgn * self.sim_c.nonlin_c(p[numpy.newaxis,:])[0,idx]
            return -sgn * ff(opt.brute(ff, self.minmax, finish=None))
        return calc(1) - calc(-1)

    def _ensure_sensitivity(self):
        if self.sensitivity is None:
            self._ensure_sim_c()
            self.sensitivity = [
                self._estimate_sensitivity(self._calc_ptp(i), i) if self.basegrid[i] is not None else 1
                for i in range(self.sim_c.nno)]
            logger = logging.getLogger("approx")
            logger.info("nonlin function sensitivity: %s"
                        % ", ".join(["%g" % v for v in self.sensitivity]))

    def _ensure_max_error(self):
        if self.E is None:
            if not self.sim_c.nno:
                self.E = []
                return
            self._ensure_sensitivity()
            lim = self.grid_error_limit
            if lim is None:
                lim = 1e-2
            self.E = [lim / self.sensitivity[i] for i in range(self.sim_c.nno)]

            #self._ensure_eq()
            #jacobi_estimate_error = 10#1e-1
            #maxerr = 1e-4
            #J, vals = simu.estimate_max_jacobi(self.sim_c.nonlin, self.minmax, jacobi_estimate_error,# self.sim_c.nno)
            #J = J[:,J.shape[1]-J.shape[0]:] ##FIXME
            #J = numpy.matrix(J)
            #dv = numpy.amax(numpy.append(abs(self.eq.F), abs(self.eq.F)*J*abs(self.eq.G)*abs(self.eq.C), axis=0), axis=0).A1
            #self.E = maxerr * self.ptp / numpy.where(dv == 0, 1e-20, dv)
            #print "E =", self.E

            #grd_shape = vals.grd.shape
            #numpoints = numpy.product(grd_shape[1:])
            #grd = vals.grd.reshape(grd_shape[0], numpoints)
            #fnc = vals.values.reshape(self.eq.nonlin.nno, numpoints)
            #self.cov = numpy.cov(grd, fnc)[:len(grd),len(grd):]
            #print self.cov

    def _ensure_basegrid(self):
        if self.basegrid is None:
            self._ensure_sim_c()
            self.basegrid = [[[None,('s',4)]] * (self.sim_c.npl + self.sim_c.nni)] * self.sim_c.nno

    def _ensure_knot_positions(self):
        #if self.knot_positions is None:
        #    xx
        pass

    def _check_basegrid(self, basegrid, ns, nni, npl, nno):
        if nno != len(basegrid):
            error("basegrid needs %d rows (found %d)"
                  % (nno, len(basegrid)), "approx")
        for i, row in enumerate(basegrid):
            if row is None:
                continue
            if nni+npl != len(row):
                if npl:
                    t = "%d parameters + %d inputs" % (nni, npl)
                else:
                    t = "%d" % nni
                error("basegrid[%d] has %d elements for function %s, input dimension: %s "
                      % (i, len(row), ns, t), "approx")

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
            tables = {}
            i0v = self.sim_c.nonlin_c(numpy.append(numpy.matrix([0.5]*npl),self.sim_c.p0.T,axis=1))[0]
            if len(self.sim_c.comp_sz) > 1:
                for i, ((v_slice, p_slice, i_slice), ns) in enumerate(zip(self.sim_c.comp_sz, self.sim_c.comp_namespace)):
                    nni = p_slice.stop - p_slice.start
                    nno = i_slice.stop - i_slice.start
                    self._check_basegrid(self.basegrid[i_slice], ns, nni, npl, nno)
                    slc = range(npl) + range(p_slice.start+npl, p_slice.stop+npl)
                    class Comp:
                        comp_id = ns
                        comp_name = ns
                        ranges = self.minmax[slc]
                        basegrid = numpy.array([(g, None, None, e, True) for g, e in zip(self.basegrid, self.E)])[i_slice]
                        NVALS = nno
                        N_IN = nni+npl
                        NDIM = nni+npl
                        i0 = i0v[i_slice]
                        @staticmethod
                        def __call__(v, with_state):
                            return self.sim_c.c_calc_comp[i](v)
                    ##FIXME: maptype
                    self.maptype, spl = simu.TableGenerator.write_files(Comp(), o, inst, h)
                    tables[ns] = spl
            else:
                ns = "nonlin"
                self._check_basegrid(self.basegrid, ns, self.eq.nonlin.nni, npl, self.eq.nonlin.nno)
                class Comp:
                    comp_id = ns
                    comp_name = self._get_module_id()
                    ranges = self.minmax
                    basegrid = [(g, None, None, e, False) for g, e in zip(self.basegrid, self.E)]
                    NVALS = self.eq.nonlin.nno
                    N_IN = self.eq.nonlin.nni+npl
                    NDIM = self.eq.nonlin.nni+npl
                    i0 = i0v
                    @staticmethod
                    def __call__(v, with_state):
                        return self.sim_c.nonlin(v)
                self.maptype, spl = simu.TableGenerator.write_files(Comp(), o, inst, h)
                tables[ns] = spl
            intpp_inst = "\n".join(set(inst.getvalue().split("\n")))
            self.table_source = dict(data_c=o.getvalue(), data_h=h.getvalue(), intpp_inst=intpp_inst, tables=tables)

    def _build_sim_table(self, dev_interface=True):
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
        modc.dev_interface = dev_interface
        modc.resample = self.resample
        modc.build_script = self.build_script
        if self.solver_params is not None:
            modc.solver_params = self.solver_params
        if self.plugindef:
            modc.plugindef = self.plugindef
        return modc

    def _ensure_sim_table(self):
        if self.sim_table is None:
            self.table_module, self.sim_table = self._build_sim_table().get_executor()

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
                raise CircuitException("circuit is nonlinear: symbolic formula generation not supported")
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
        return self.sig.generate(signal, self.FS, self._get_op())

    def print_netlist(self, values=False):
        self._check_netlist()
        for row in self.S:
            print "%s: %s" % (row[0], ", ".join([str(v) for v in row[1:]]))
        if values:
            print
            for e, v in sorted((str(e), v) for e, v in self.V.items()):
                if isinstance(v, float):
                    v = eng_str(v)
                print "%s = %s" % (e, v)

    def read_gschem(self, filename, defs=None):
        self._clear_all()
        v = dict(vars(models))
        v["Transistors"] = circ.Transistors
        v["Diodes"] = circ.Diodes
        v["Tubes"] = circ.Tubes
        v["math"] = math
        if defs:
            v.update(defs)
        exec mk_netlist.read_netlist(filename) in v
        self.S = v["S"]
        self.V = v["V"]
        self.loaded_filename = filename

    def read_netlist(self, filename):
        self._clear_all()
        v = vars(models)
        v["Transistors"] = circ.Transistors
        v["Diodes"] = circ.Diodes
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

    def set_in_nets(self, *connections):
        self._check_netlist()
        self.S = list(self.S)
        l = (models.IN,) + tuple(connections)
        for i, row in enumerate(self.S):
            if row[0] == models.IN:
                self.S[i] = l
                break
        else:
            self.S.append(l)
        self._clear_calculated()
        if self.parser is not None:
            self.parser.update(self.S, self.V)

    def set_out_nets(self, *connections):
        self._check_netlist()
        self.S = list(self.S)
        l = (models.OUT,) + tuple(connections)
        for i, row in enumerate(self.S):
            if row[0] == models.OUT:
                self.S[i] = l
                break
        else:
            self.S.append(l)
        self._clear_calculated()
        if self.parser is not None:
            self.parser.update(self.S, self.V)

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

    def remove_connected(self, net, exclude=None):
        self._check_netlist()
        if exclude is None:
            exclude = {}
        self.S = list(self.S)
        comp = {net}
        found = False
        last_size = 0
        def excluded_row(row):
            for c in row[1:]:
                if c in exclude and str(row[0]) in exclude[c]:
                    return True
            return False
        while len(comp) > last_size:
            last_size = len(comp)
            dl =[]
            for i, row in enumerate(self.S):
                for c in row[1:]:
                    if c in comp and not excluded_row(row):
                        comp |= set([j for j in row[1:] if j != models.GND])
                        dl.append(i)
                        found = True
                        break
            for i in reversed(dl):
                del self.S[i]
        if not found:
            raise CircuitException("net %s not found" % net)
        self._clear_calculated()
        if self.parser is not None:
            self.parser.update(self.S, self.V)

    def split_circuit(self, parts):
        for block, (cuts, inputs, outputs) in parts.items():
            c = Circuit(copy_from=self)
            for net, els in cuts.items():
                c.remove_connected(net, exclude=cuts)
            if inputs:
                c.set_in_nets(*[p[0] for p in inputs])
                c.inputs = [p[1] for p in inputs]
            if outputs:
                c.set_out_nets(*[p[0] for p in outputs])
                c.outputs = [p[1] for p in outputs]
            self.subcircuits[block] = c

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
        V = dict(self.V)
        for e in self.S:
            if e[0] in el:
                if isinstance(e[0], models.CC_N):
                    e = (models.CC_L(e[0].d),) + e[1:]
                elif isinstance(e[0], (models.Trans_F, models.Trans_GC)):
                    #FIXME calculate R (Trans_L parameter)
                    e = (models.Trans_L(e[0].d),) + e[1:]
                elif isinstance(e[0], models.OPA):
                    p = V[e[0]]
                    if isinstance(p, dict):
                        p = p["A"]
                    V[e[0]] = p
            S.append(e)
        self.S = S
        self.parser.update(S, V)
        self.eq = None
        self.sim_py = None
        self.dc_values = None
        self._ensure_dc_values()
        el = self._nonlin_function_list(elements)
        J = self.sim_py.jacobi()
        Jc = self.sim_py.calc_i(self.dc_values.v)
        S = []
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
                    jl = numpy.ravel(J[i].nonzero()[1])
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

    def get_faust_code(self, module_id=None, symbolic=False, filename=None, FS=None, pre_filter=None):
        self._ensure_filter(symbolic=symbolic)
        b, a = self.sim_filter.get_z_coeffs(samplerate=FS)
        l = self.parser.get_pot_attr()
        m_id = self._get_module_id(module_id)
        plugindef = self.plugindef
        if not plugindef:
            plugindef = PluginDef(m_id)
        dsp, ui = simu.generate_faust_module(plugindef, b, a, l, self.sim_filter, pre_filter, build_script=self.build_script)
        return dsp, ui

    def get_simple_faust_code(self, module_id=None, symbolic=False, filename=None, FS=None, pre_filter=None):
        self._ensure_filter(symbolic=symbolic)
        b, a = self.sim_filter.get_z_coeffs(samplerate=FS)
        l = self.parser.get_pot_attr()
        m_id = self._get_module_id(module_id)
        plugindef = self.plugindef
        if not plugindef:
            plugindef = PluginDef(m_id)
        dsp, ui = simu.generate_simple_faust_module(plugindef, b, a, l, self.sim_filter, pre_filter, build_script=self.build_script)
        return dsp, ui

    def save_faust_code(self, module_id=None, symbolic=False, filename=None, FS=None, pre_filter=None):
        self._ensure_filter(symbolic=symbolic)
        b, a = self.sim_filter.get_z_coeffs(samplerate=FS)
        l = self.parser.get_pot_attr()
        m_id = self._get_module_id(module_id)
        plugindef = self.plugindef
        if not plugindef:
            plugindef = PluginDef(m_id)
        dsp, ui = simu.generate_faust_module(plugindef, b, a, l, self.sim_filter, pre_filter, build_script=self.build_script)
        if filename is None:
            sys.stdout.write(dsp)
            sys.stdout.write(ui)
        else:
            dspname = "{0}.dsp".format(filename)
            uiname = "{0}_ui.cc".format(filename)
            with open(dspname,"w") as f:
                f.write(dsp)
            with open(uiname,"w") as f:
                f.write(ui)

    def create_faust_module(self, module_id=None, symbolic=False, FS=None, pre_filter=None):
        self._ensure_filter(symbolic=symbolic)
        b, a = self.sim_filter.get_z_coeffs(samplerate=FS)
        l = self.parser.get_pot_attr()
        m_id = self._get_module_id(module_id)
        plugindef = self.plugindef
        if not plugindef:
            plugindef = PluginDef(m_id)
        simu.build_faust_module(plugindef, b, a, l, self.sim_filter, self.c_datatype, pre_filter, build_script=self.build_script)

    def stream(self, signal, ii=-1):
        if not isinstance(signal, signals.GeneratedSignal):
            signal = self.make_signal_vector(signal)
        sim = self._get_sim()
        self.last_signal = signal
        self.last_output = sim(signal.input_signal, ii)
        return self.last_output

    def plot(self, sig=None, label=None, clip=-80, nharmonics=8, spectrum=None, freq_range=None):
        if sig is not None:
            self.stream(sig)
        if self.last_output is None:
            raise CircuitException("nothing to plot")
        lines = self.last_signal.plot(self.last_output, sig, label, clip, nharmonics, spectrum, freq_range)
        #if label is None:
        #    label = self._get_sim().out_labels
        #elif not hasattr(label, "__iter__"):
        #    l = []
        #    for lbl in self._get_sim().out_labels:
        #        l.append("%s.%s" % (label, lbl))
        #    label = l
        Circuit.have_plot = True
        return lines

    def build_guitarix_module(self, include_paths=()):
        modc = self._build_sim_table(dev_interface=False)
        cw = modc.compile_c_func()
        cw.script_dict["includes"] += "".join([" -I%s" % os.path.abspath(p) for p in include_paths])
        cw.wrap_code(load_module=False)

    def deploy(self, path=None):
        sim = self._get_sim()
        if sim is self.sim_py:
            self._ensure_sim_c()
            sim = self.sim_c
        if is_test():
            return
        if sim is self.sim_table:
            mod = self.table_module
            s = "table"
        else:
            mod = self.c_module
            s = "C"
        if self.plugindef.lv2_plugin_type:
            def try_mkdir(path):
                try:
                    os.mkdir(path)
                except OSError as e:
                    if e.errno != 17: # EEXIST
                        raise
            vid = self.plugindef.lv2_versioned_id
            if path is None:
                path = os.path.expanduser("~/.lv2")
                try_mkdir(path)
            path = os.path.join(path, "gx_%s.lv2" % vid)
            try_mkdir(path)
            base = os.path.dirname(mod)
            ttlname = os.path.join(base, vid+".ttl")
            shutil.copy(ttlname, path)
            shutil.copy(os.path.join(base, "manifest.ttl"), path)
            fname = os.path.join(path, vid+".so")
            s = "LV2 bundle [%s]" % s
            shutil.copy(mod, fname)
            print "LV2 bundle [%s module] copied to '%s'" % (s, path)
        else:
            if path is None:
                path = os.path.expanduser("~/.config/guitarix/plugins/.")
            fname = os.path.join(path, self._get_module_id()+".so")
            shutil.copy(mod, fname)
            print "%s module copied to '%s'" % (s, fname)

    @staticmethod
    def _get_samples(data, count):
        return data[numpy.array(numpy.linspace(0, len(data)-1, count).round(), dtype=int)]

    def check_result(self, sig, result, max_error=1e-7, count=None):
        if not is_test():
            return True
        test = get_test()
        if count is None:
            if result is None:
                count = 10
            else:
                count = len(result)
        y = self.stream(sig)
        samples = self._get_samples(y, count)
        if test.plot:
            timeline = self.last_signal.timeline
            pylab.plot(timeline, y)
            if result is not None:
                pylab.plot(self._get_samples(timeline, count), result, "rx")
            pylab.show()
        if test.printout:
            print repr(samples)
            return True
        error = numpy.max(abs(result - samples)) / numpy.max(abs(result))
        if (error > max_error).any():
            print "%s: Difference = %g (> %g)" % (self._get_module_id(), error, max_error)
            return False
        else:
            print "%s: OK" % self._get_module_id()
            return True
        
    def set_pot_variable(self, name, val):
        self._get_sim().set_variable(name, val)

    def set_pot_position(self, name, val):
        self._ensure_parser()
        expr = dict([(row[0], row[4]) for row in self.parser.get_pot_attr()])[name]
        self.set_pot_variable(name, expr(val))

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
        pylab.grid(which="both")
        pylab.legend(loc=loc)
        pylab.show()
        Circuit.have_plot = False

INFO = logging.INFO
DEBUG = logging.DEBUG

def set_log_level(lvl, logger=None):
    logging.getLogger(logger).setLevel(lvl)

class TestSettings:
    active = False
    plot = False
    printout = False

_display_traceback = True #False
_testing = TestSettings

def is_test():
    return _testing.active

def get_test():
    return _testing

def display_traceback(v):
    global _display_traceback
    _display_traceback = v

def _init():
    global _testing
    def _catch_circuit_error(tp, value, traceback):
        if tp == CircuitException:
            if _display_traceback:
                logging.getLogger(value.logger).error(value)
            else:
                print "ERROR:%s:%s" % (value.logger or "root", value)
                return
        if _excepthook is not None:
            _excepthook(tp, value, traceback)

    logging.basicConfig()
    _excepthook = sys.excepthook
    sys.excepthook = _catch_circuit_error
    parser = argparse.ArgumentParser()
    parser.add_argument('--test', action='store_true', help='check results of tests')
    parser.add_argument('--test-plot', action='store_true', help='plot the test-data with markers')
    parser.add_argument('--test-print', action='store_true', help='print the result array')
    args = parser.parse_args()
    _testing.active = args.test or args.test_plot or args.test_print
    _testing.plot = args.test_plot
    _testing.printout = args.test_print

_init()

import numpy as np
cimport numpy as np

cdef extern from "circuit.hpp":
    ctypedef struct N_Vector:
        pass
    N_Vector N_VNew_Serial(long int vec_length)
    void N_VDestroy_Serial(N_Vector v)
    double *NV_DATA_S(N_Vector v)
    int NV_LENGTH_S(N_Vector v)

    int FS "fs"

    int tcNEQ "TriodeCircuit::NEQ"
    int tcNDIM "TriodeCircuit::NDIM"
    int tcNVALS "TriodeCircuit::NVALS"
    int tcN_IN "TriodeCircuit::N_IN"
    int tcN_OUT "TriodeCircuit::N_OUT"
    int triodecircuit "TriodeCircuit::triodecircuit"(N_Vector x, N_Vector u)
    void tcupdate "TriodeCircuit::update"(N_Vector y, N_Vector state)
    int tc_set_range "TriodeCircuit::set_range"(int i, double lower, double upper, int size)
    void tc_init "TriodeCircuit::init"(double *u0) #tcNEQ
    double tc_Gco "TriodeCircuit::Gco"
    double tc_Gcf "TriodeCircuit::Gcf"
    double tc_mu "TriodeCircuit::mu"
    double tc_Ex "TriodeCircuit::Ex"
    double tc_Kg1 "TriodeCircuit::Kg1"
    double tc_Kp "TriodeCircuit::Kp"
    double tc_Kvb "TriodeCircuit::Kvb"
    double tc_G1 "TriodeCircuit::G1"
    double tc_G2 "TriodeCircuit::G2"
    double tc_Gg "TriodeCircuit::Gg"
    double tc_Gk "TriodeCircuit::Gk"
    double tc_Ga "TriodeCircuit::Ga"
    double tc_Gl "TriodeCircuit::Gl"
    double tc_Ck "TriodeCircuit::Ck"

    int coupledtriodecircuit "CoupledTriodeCircuit::coupledtriodecircuit"(N_Vector x, N_Vector u)
    void ctcupdate "CoupledTriodeCircuit::update"(N_Vector y, N_Vector state)
    int ctc_set_range "CoupledTriodeCircuit::set_range"(int i, double lower, double upper, int size)
    void ctc_init "CoupledTriodeCircuit::init"(double *u0) #ctcNEQ
    int ctcNEQ "CoupledTriodeCircuit::NEQ"
    int ctcNDIM "CoupledTriodeCircuit::NDIM"
    int ctcNVALS "CoupledTriodeCircuit::NVALS"
    int ctcN_IN "CoupledTriodeCircuit::N_IN"
    int ctcN_OUT "CoupledTriodeCircuit::N_OUT"
    double ctc_Gco "CoupledTriodeCircuit::Gco"
    double ctc_Gcf "CoupledTriodeCircuit::Gcf"
    double ctc_mu "CoupledTriodeCircuit::mu"
    double ctc_Ex "CoupledTriodeCircuit::Ex"
    double ctc_Kg1 "CoupledTriodeCircuit::Kg1"
    double ctc_Kp "CoupledTriodeCircuit::Kp"
    double ctc_Kvb "CoupledTriodeCircuit::Kvb"
    double ctc_Ck "CoupledTriodeCircuit::Ck"
    double ctc_Ca "CoupledTriodeCircuit::Ca"
    double ctc_Un "CoupledTriodeCircuit::Un"
    double ctc_G1 "CoupledTriodeCircuit::G1"
    double ctc_G2 "CoupledTriodeCircuit::G2"
    double ctc_Gg "CoupledTriodeCircuit::Gg"
    double ctc_Gk "CoupledTriodeCircuit::Gk"
    double ctc_Ga "CoupledTriodeCircuit::Ga"
    double ctc_G3 "CoupledTriodeCircuit::G3"
    double ctc_Gg2 "CoupledTriodeCircuit::Gg2"
    double ctc_Gk2 "CoupledTriodeCircuit::Gk2"
    double ctc_Ga2 "CoupledTriodeCircuit::Ga2"
    double ctc_Gl "CoupledTriodeCircuit::Gl"

    int powerampgate "PowerAmpCircuit::powerampgate"(N_Vector x, N_Vector u)
    void pagupdate "PowerAmpCircuit::updateGate"(N_Vector y, N_Vector state)
    int pag_set_range "PowerAmpCircuit::set_range_gate"(int i, double lower, double upper, int size)
    void pag_init "PowerAmpCircuit::init_gate"(double *u0) #pagNEQ
    int pagNEQ "PowerAmpCircuit::NEQ_GATE"
    int pagNDIM "PowerAmpCircuit::NDIM_GATE"
    int pagNVALS "PowerAmpCircuit::NVALS_GATE"
    int pagN_IN "PowerAmpCircuit::N_IN_GATE"
    int pagN_OUT "PowerAmpCircuit::N_OUT_GATE"
    double pag_Gco "PowerAmpCircuit::Gco"
    double pag_Gcf "PowerAmpCircuit::Gcf"
    double pag_C1 "PowerAmpCircuit::C1"
    double pag_G1 "PowerAmpCircuit::G1"
    double pag_Gb "PowerAmpCircuit::Gb"
    double pag_Gg "PowerAmpCircuit::Gg"
    double pag_Ub "PowerAmpCircuit::Ub"

    int powerampplate "PowerAmpCircuit::powerampplate"(N_Vector x, N_Vector u)
    void papupdate "PowerAmpCircuit::updatePlate"(N_Vector y, N_Vector state)
    int pap_set_range "PowerAmpCircuit::set_range_plate"(int i, double lower, double upper, int size)
    void pap_init "PowerAmpCircuit::init_plate"(double *u0) #papNEQ
    int papNEQ "PowerAmpCircuit::NEQ_PLATE"
    int papNDIM "PowerAmpCircuit::NDIM_PLATE"
    int papNVALS "PowerAmpCircuit::NVALS_PLATE"
    int papN_IN "PowerAmpCircuit::N_IN_PLATE"
    int papN_OUT "PowerAmpCircuit::N_OUT_PLATE"
    double pap_Kp "PowerAmpCircuit::Kp"
    double pap_mu "PowerAmpCircuit::mu"
    double pap_Ex "PowerAmpCircuit::Ex"
    double pap_Kg1 "PowerAmpCircuit::Kg1"
    double pap_Kg2 "PowerAmpCircuit::Kg2"
    double pap_Kvb "PowerAmpCircuit::Kvb"
    double pap_Un "PowerAmpCircuit::Un"
    double pap_Gd "PowerAmpCircuit::Gd"
    double pap_C2 "PowerAmpCircuit::C2"
    double pap_Ga "PowerAmpCircuit::Ga"
    double pap_Gs "PowerAmpCircuit::Gs"
    double pap_Gd "PowerAmpCircuit::Gd"

    int phasesplittercircuit "PhaseSplitterCircuit::phasesplittercircuit"(N_Vector x, N_Vector u)
    void psupdate "PhaseSplitterCircuit::update"(N_Vector y, N_Vector state)
    int ps_set_range "PhaseSplitterCircuit::set_range"(int i, double lower, double upper, int size)
    void ps_init "PhaseSplitterCircuit::init"(double *u0) #psNEQ
    void ps_fb_coeff "PhaseSplitterCircuit::feedback_coeff"(double *b0, double *b1, double *a1, double pres)
    int psNEQ "PhaseSplitterCircuit::NEQ"
    int psNDIM "PhaseSplitterCircuit::NDIM"
    int psNVALS "PhaseSplitterCircuit::NVALS"
    int psN_IN "PhaseSplitterCircuit::N_IN"
    int psN_OUT "PhaseSplitterCircuit::N_OUT"
    double ps_Gco "PhaseSplitterCircuit::Gco"
    double ps_Gcf "PhaseSplitterCircuit::Gcf"
    double ps_mu "PhaseSplitterCircuit::mu"
    double ps_Ex "PhaseSplitterCircuit::Ex"
    double ps_Kg1 "PhaseSplitterCircuit::Kg1"
    double ps_Kp "PhaseSplitterCircuit::Kp"
    double ps_Kvb "PhaseSplitterCircuit::Kvb"
    double ps_C1 "PhaseSplitterCircuit::C1"
    double ps_C2 "PhaseSplitterCircuit::C2"
    double ps_C3 "PhaseSplitterCircuit::C3"
    double ps_Un "PhaseSplitterCircuit::Un"
    double ps_G1 "PhaseSplitterCircuit::G1"
    double ps_Gg1 "PhaseSplitterCircuit::Gg1"
    double ps_Gg2 "PhaseSplitterCircuit::Gg2"
    double ps_Gk "PhaseSplitterCircuit::Gk"
    double ps_G2 "PhaseSplitterCircuit::G2"
    double ps_G3 "PhaseSplitterCircuit::G3"
    double ps_G4 "PhaseSplitterCircuit::G4"
    double ps_G5 "PhaseSplitterCircuit::G5"
    double ps_Ga1 "PhaseSplitterCircuit::Ga1"
    double ps_Ga2 "PhaseSplitterCircuit::Ga2"
    double ps_Gl1 "PhaseSplitterCircuit::Gl1"
    double ps_Gl2 "PhaseSplitterCircuit::Gl2"

    cdef cppclass CSpline "Spline":
        CSpline(double *, int, double, double)
        double eval(double)

fs = FS


cdef class CalcBase:

    cdef int capture

    def __cinit__(self):
        self.capture = 0
        self.u = np.zeros(self.NEQ, dtype=np.float32)

    property capture:
        def __get__(self):
            return self.capture
        def __set__(self, v):
            self.capture = v

    property values:
        def __get__(self):
            return self.u

    cdef store(self, N_Vector *u):
        for i in range(NV_LENGTH_S(u[0])):
            self.u[i] = NV_DATA_S(u[0])[i]


class tcParams(CalcBase):
    NDIM = tcNDIM
    NEQ = tcNEQ
    NVALS = tcNVALS
    N_IN = tcN_IN
    N_OUT = tcN_OUT

    @staticmethod
    def func(a):
        cdef N_Vector x = N_VNew_Serial(2)
        cdef N_Vector u = N_VNew_Serial(tcNEQ)
        NV_DATA_S(x)[0] = a[0]
        NV_DATA_S(x)[1] = a[1]
        if triodecircuit(x,u):
            raise ValueError
        NV_DATA_S(x)[0] = NV_DATA_S(u)[1]  # Uk
        tcupdate(u, x)
        ret = [NV_DATA_S(u)[2], NV_DATA_S(x)[0]]
        N_VDestroy_Serial(x)
        N_VDestroy_Serial(u)
        return ret

    @classmethod
    def init(self):
        for k, v in self.circuit.items():
            global tc_Gco, tc_Gcf, tc_mu, tc_Ex, tc_Kg1, tc_Kp, tc_Kvb, tc_G1, tc_G2
            global tc_Gg, tc_Gk, tc_Ga, tc_Gl, tc_Ck
            if k == "Gco":
                tc_Gco = v
            elif k == "Gcf":
                tc_Gcf = v
            elif k == "mu":
                tc_mu = v
            elif k == "Ex":
                tc_Ex = v
            elif k == "Kg1":
                tc_Kg1 = v
            elif k == "Kp":
                tc_Kp = v
            elif k == "Kvb":
                tc_Kvb = v
            elif k == "G1":
                tc_G1 = v
            elif k == "G2":
                tc_G2 = v
            elif k == "Gg":
                tc_Gg = v
            elif k == "Gk":
                tc_Gk = v
            elif k == "Ga":
                tc_Ga = v
            elif k == "Gl":
                tc_Gl = v
            elif k == "Ck":
                tc_Ck = v
            else:
                raise KeyError("unknown %s" % k)
        for i, l in enumerate(self.start_grid):
            if not tc_set_range(i, l[0], l[1], l[2]):
                raise ValueError("can't set range nr %d" % i)
        if len(self.u0) != tcNEQ:
            raise ValueError("lenght %d expected for u0" % tcNEQ)
        cdef double U0[5] #tcNEQ
        for i, v in enumerate(self.u0):
            U0[i] = v
        tc_init(U0)


class ctcParams(CalcBase):
    NDIM = ctcNDIM
    NEQ = ctcNEQ
    NVALS = ctcNVALS
    N_IN = ctcN_IN
    N_OUT = ctcN_OUT

    @staticmethod
    def func(a):
        cdef N_Vector x = N_VNew_Serial(3)
        cdef N_Vector u = N_VNew_Serial(ctcNEQ)
        NV_DATA_S(x)[0] = a[0]
        NV_DATA_S(x)[1] = a[1]
        NV_DATA_S(x)[2] = a[2]
        if coupledtriodecircuit(x,u):
            raise ValueError
        NV_DATA_S(x)[0] = NV_DATA_S(u)[1]  # Uk
        NV_DATA_S(x)[1] = NV_DATA_S(u)[2]-NV_DATA_S(u)[3]  # Ua-U2
        ctcupdate(u, x)
        ret = [NV_DATA_S(u)[3], NV_DATA_S(x)[0], NV_DATA_S(x)[1]]
        N_VDestroy_Serial(x)
        N_VDestroy_Serial(u)
        return ret

    @classmethod
    def init(self):
        for k, v in self.circuit.items():
            global ctc_Gco, ctc_Gcf, ctc_mu, ctc_Ex, ctc_Kg1, ctc_Kp, ctc_Kvb, ctc_Ck
            global ctc_Ca, ctc_Un, ctc_G1, ctc_G2, ctc_Gg, ctc_Gk, ctc_Ga, ctc_G3
            global ctc_Gg2, ctc_Gk2, ctc_Ga2, ctc_Gl
            if k == "Gco":
                ctc_Gco = v
            elif k == "Gcf":
                ctc_Gcf = v
            elif k == "mu":
                ctc_mu = v
            elif k == "Ex":
                ctc_Ex = v
            elif k == "Kg1":
                ctc_Kg1 = v
            elif k == "Kp":
                ctc_Kp = v
            elif k == "Kvb":
                ctc_Kvb = v
            elif k == "Ck":
                ctc_Ck = v
            elif k == "Ca":
                ctc_Ca = v
            elif k == "Un":
                ctc_Un = v
            elif k == "G1":
                ctc_G1 = v
            elif k == "G2":
                ctc_G2 = v
            elif k == "Gg":
                ctc_Gg = v
            elif k == "Gk":
                ctc_Gk = v
            elif k == "Ga":
                ctc_Ga = v
            elif k == "G3":
                ctc_G3 = v
            elif k == "Gg2":
                ctc_Gg2 = v
            elif k == "Gk2":
                ctc_Gk2 = v
            elif k == "Ga2":
                ctc_Ga2 = v
            elif k == "Gl":
                ctc_Gl = v
            else:
                raise KeyError("unknown %s" % k)
        for i, l in enumerate(self.start_grid):
            if not ctc_set_range(i, l[0], l[1], l[2]):
                raise ValueError("can't set range nr %d" % i)
        if len(self.u0) != ctcNEQ:
            raise ValueError("lenght %d expected for u0" % ctcNEQ)
        cdef double U0[7] #ctcNEQ
        for i, v in enumerate(self.u0):
            U0[i] = v
        ctc_init(U0)


class pagParams(CalcBase):
    NDIM = pagNDIM
    NEQ = pagNEQ
    NVALS = pagNVALS
    N_IN = pagN_IN
    N_OUT = pagN_OUT

    def func(self, a):
        cdef N_Vector x = N_VNew_Serial(2)
        cdef N_Vector u = N_VNew_Serial(pagNEQ)
        cdef int i
        for i in range(2):
            NV_DATA_S(x)[i] = a[i]
        if powerampgate(x,u):
            raise ValueError
        NV_DATA_S(x)[0] = NV_DATA_S(u)[0] - NV_DATA_S(u)[1]  # Uc1 = U0 - U1
        pagupdate(u, x)
        if self.capture:
            self.store(u)
        ret = [NV_DATA_S(u)[2], NV_DATA_S(x)[0]]
        N_VDestroy_Serial(x)
        N_VDestroy_Serial(u)
        return ret

    @classmethod
    def init(self):
        for k, v in self.circuit.items():
            global pag_Gco, pag_Gcf, pag_C1, pag_G1, pag_Gb, pag_Gg, pag_Ub
            if k == "Gco":
                pag_Gco = v
            elif k == "Gcf":
                pag_Gcf = v
            elif k == "C1":
                pag_C1 = v
            elif k == "G1":
                pag_G1 = v
            elif k == "Gb":
                pag_Gb = v
            elif k == "Gg":
                pag_Gg = v
            elif k == "Ub":
                pag_Ub = v
            else:
                raise KeyError("unknown %s" % k)
        for i, l in enumerate(self.start_grid):
            if not pag_set_range(i, l[0], l[1], l[2]):
                raise ValueError("can't set range nr %d" % i)
        if len(self.u0) != pagNEQ:
            raise ValueError("lenght %d expected for u0" % pagNEQ)
        cdef double U0[3] #pagNEQ
        for i, v in enumerate(self.u0):
            U0[i] = v
        pag_init(U0)


class papParams(CalcBase):
    NDIM = papNDIM
    NEQ = papNEQ
    NVALS = papNVALS
    N_IN = papN_IN
    N_OUT = papN_OUT

    @staticmethod
    def func(a):
        # expects [Ug1, Ug1+Ug2]
        # returns Ua1 - Ua2
        cdef N_Vector x = N_VNew_Serial(3)
        cdef N_Vector u = N_VNew_Serial(papNEQ)
        cdef int i
        for i in range(3):
            NV_DATA_S(x)[i] = a[i]
        NV_DATA_S(x)[1] -= NV_DATA_S(x)[0]
        if powerampplate(x,u):
            raise ValueError
        # x[0], x[1] still Ug1, Ug2
        NV_DATA_S(x)[2] = NV_DATA_S(u)[2]  # Uc2 = Ud
        papupdate(u, x)
        ret = [NV_DATA_S(u)[3] - NV_DATA_S(u)[4], NV_DATA_S(x)[2]]
        N_VDestroy_Serial(x)
        N_VDestroy_Serial(u)
        return ret

    @classmethod
    def init(self):
        for k, v in self.circuit.items():
            global pap_Kp, pap_mu, pap_Ex, pap_Kg1, pap_Kg2, pap_Kvb, pap_Un
            global pap_Gd, pap_C2, pap_Ga, pap_Gs, pap_Gd
            if k == "Kp":
                pap_Kp = v
            elif k == "mu":
                pap_mu = v
            elif k == "Ex":
                pap_Ex = v
            elif k == "Kg1":
                pap_Kg1 = v
            elif k == "Kg2":
                pap_Kg2 = v
            elif k == "Kvb":
                pap_Kvb = v
            elif k == "Un":
                pap_Un = v
            elif k == "Gd":
                pap_Gd = v
            elif k == "C2":
                pap_C2 = v
            elif k == "Ga":
                pap_Ga = v
            elif k == "Gs":
                pap_Gs = v
            elif k == "Gd":
                pap_Gd = v
            else:
                raise KeyError("unknown %s" % k)
        for i, l in enumerate(self.start_grid):
            if not pap_set_range(i, l[0], l[1], l[2]):
                raise ValueError("can't set range nr %d" % i)
        if len(self.u0) != papNEQ:
            raise ValueError("lenght %d expected for u0" % papNEQ)
        cdef double U0[5] #papNEQ
        for i, v in enumerate(self.u0):
            U0[i] = v
        pap_init(U0)


class psParams(CalcBase):
    NDIM = psNDIM
    NEQ = psNEQ
    NVALS = psNVALS
    N_IN = psN_IN
    N_OUT = psN_OUT

    @staticmethod
    def func(a):
        cdef N_Vector x = N_VNew_Serial(4)
        cdef N_Vector u = N_VNew_Serial(psNEQ)
        cdef int i
        for i in range(4):
            NV_DATA_S(x)[i] = a[i]
        if phasesplittercircuit(x,u):
            raise ValueError
        NV_DATA_S(x)[0] = NV_DATA_S(u)[0] - NV_DATA_S(u)[1]  # Uc1 = U1 - Ug1
        NV_DATA_S(x)[1] = NV_DATA_S(u)[7] - NV_DATA_S(u)[5]  # Uc2 = Ug2 - U3
        NV_DATA_S(x)[2] = NV_DATA_S(u)[5] - NV_DATA_S(u)[6]  # Uc3 = U3 - U4
        psupdate(u, x)
        ret = [NV_DATA_S(u)[3], NV_DATA_S(u)[8], NV_DATA_S(x)[0], NV_DATA_S(x)[1], NV_DATA_S(x)[2]]
        N_VDestroy_Serial(x)
        N_VDestroy_Serial(u)
        return ret

    @classmethod
    def init(self):
        for k, v in self.circuit.items():
            global ps_Gco, ps_Gcf, ps_mu, ps_Ex, ps_Kg1, ps_Kp, ps_Kvb, ps_C1, ps_C2
            global ps_C3, ps_Un, ps_G1, ps_Gg1, ps_Gg2, ps_Gk, ps_G2, ps_G3, ps_G4
            global ps_G5, ps_Ga1, ps_Ga2, ps_Gl1, ps_Gl2
            if k == "Gco":
                ps_Gco = v
            elif k == "Gcf":
                ps_Gcf = v
            elif k == "mu":
                ps_mu = v
            elif k == "Ex":
                ps_Ex = v
            elif k == "Kg1":
                ps_Kg1 = v
            elif k == "Kp":
                ps_Kp = v
            elif k == "Kvb":
                ps_Kvb = v
            elif k == "C1":
                ps_C1 = v
            elif k == "C2":
                ps_C2 = v
            elif k == "C3":
                ps_C3 = v
            elif k == "Un":
                ps_Un = v
            elif k == "G1":
                ps_G1 = v
            elif k == "Gg1":
                ps_Gg1 = v
            elif k == "Gg2":
                ps_Gg2 = v
            elif k == "Gk":
                ps_Gk = v
            elif k == "G2":
                ps_G2 = v
            elif k == "G3":
                ps_G3 = v
            elif k == "G4":
                ps_G4 = v
            elif k == "G5":
                ps_G5 = v
            elif k == "Ga1":
                ps_Ga1 = v
            elif k == "Ga2":
                ps_Ga2 = v
            elif k == "Gl1":
                ps_Gl1 = v
            elif k == "Gl2":
                ps_Gl2 = v
            else:
                raise KeyError("unknown %s" % k)
        for i, l in enumerate(self.start_grid):
            if not ps_set_range(i, l[0], l[1], l[2]):
                raise ValueError("can't set range nr %d" % i)
        if len(self.u0) != psNEQ:
            raise ValueError("lenght %d expected for u0" % psNEQ)
        cdef double U0[9] #psNEQ
        for i, v in enumerate(self.u0):
            U0[i] = v
        ps_init(U0)

    @staticmethod
    def feedback_coeff(double pres):
        cdef double b0, b1, a1
        ps_fb_coeff(&b0, &b1, &a1, pres)
        return b0, b1, a1


cdef class Spline:
    cdef CSpline *spl
    cdef np.ndarray y

    def __cinit__(self, np.ndarray[np.float_t,ndim=1] y, double xstart, double h):
        self.y = y
        self.spl = new CSpline(<double*>np.PyArray_DATA(y), len(y), xstart, h)

    def __dealloc__(self):
        del self.spl

    def __call__(self, np.ndarray[np.float_t,ndim=1] x):
        cdef int i
        cdef double v
        out = np.empty_like(x)
        for i in range(len(x)):
            out[i] = self.spl.eval(x[i])
        return out
    
# Local Variables:
# compile-command: "rm -f pycircuit.so; python setup.py build_ext --inplace"
# End:

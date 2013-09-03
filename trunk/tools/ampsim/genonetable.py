import sys, os
basepath = os.path.dirname(sys.argv[0])
sys.path.append(os.path.join(basepath, "circuit"))
sys.path.append(os.path.join(basepath, "tensbs"))
import pycircuit, splinetable

class tcParams(pycircuit.tcParams):

    u0 = (-37, -14, 341, 341-(-14), 341-350)  #Un = 350

    start_grid = (
        (-40.0, 40.0, 2),
        (-15.0, 15.0, 2),
        )

    ranges = ()

    circuit = dict(
        Gco = -0.2,
        Gcf = 1e-5,
        mu  = 100.0,
        Ex  = 1.4,
        Kg1 = 1060.0,
        Kp  = 600.0,
        Kvb = 300.0,

        Ck  = 680e-9,

        G1  = 1/68e3,   # 1/R1
        G2  = 1/1e0,    # 1/R2
        Gg  = 1/1e6,    # 1/Rg
        Gk  = 1/2.7e3,  # 1/Rk
        Ga  = 1/100e3,  # 1/Ra
        Gl  = 1/4e6,    # 1/Rl
        )


class ctcParams(pycircuit.ctcParams):

    u0 = (-18, 0, 313, 214, 45, 35, 37)

    start_grid = (
        (-20.0, 20.0, 80),
        (0.0, 10.0, 30),
        (100.0, 350.0, 8),
        )

    ranges = (
        (slice(-20,20,161j), 3),
        (slice(0,10,50j), 3),
        (slice(100,350,10j), 3),
        )

    circuit = dict(
        Gco = -0.2,
        Gcf = 1e-5,
        mu  = 100.0,
        Ex  = 1.4,
        Kg1 = 1060.0,
        Kp  = 600.0,
        Kvb = 300.0,
        Ck = 680e-9,
        Ca = 22e-9,
        Un = 350,
        G1 = 1/68e3,
        G2 = 1/1e0,
        Gg = 1/1e6,
        Gk = 1/2.7e3,
        Ga = 1/100e3,
        G3 = 1/470e3,
        Gg2 = 1/1e6,
        Gk2 = 1/10e3,
        Ga2 = 1/100e3,
        Gl = 1/4e6,
        )


class psParams(pycircuit.psParams):

    u0 = (-4.99999142644, -4.99999053336, 3.7459813383, 391.962467113,
          3.57356994824, 0.0264493076678, 0.0264491824349, 0.0264496771595,
          354.458081186)

    start_grid = (
        (-40.0, 40.0, 30),
        (-31.0, -30.0, 2),
        (30.0, 31.0, 2),
        (0.13, 0.15, 3),
        )

    ranges = (
        (slice(-40,40,81j), 3),
        (slice(-31.2,-30,5j), 3),
        (slice(30.4,33.0,5j), 3),
        (slice(0.13,0.18,2j), 2),
        )

    circuit = dict(
        Gco = -0.2,
        Gcf = 1e-5,
        mu  = 100.0,
        Ex  = 1.4,
        Kg1 = 1060.0,
        Kp  = 600.0,
        Kvb = 300.0,
        C1 = 100e-9,   # corrected from 100e-6
        C2 = 100e-9,   # corrected from 100e-6
        C3 = 100e-9,   # corrected from 100e-6
        Un = 400,
        G1 = 1/1e0,    # 1/R1
        Gg1 = 1/1e6,   # 1/Rg1
        Gg2 = 1/1e6,   # 1/Rg2
        Gk = 1/470e0,  # 1/Rk
        G2 = 1/10e3,   # 1/R2
        G3 = 1/100e3,  # 1/R3
        G4 = 1/22e3,   # 1/R4
        G5 = 1/4.7e3,  # 1/R5
        Ga1 = 1/82e3,  # 1/Ra1
        Ga2 = 1/100e3, # 1/Ra2
        Gl1 = 1/4e6,   # 1/Rl1
        Gl2 = 1/4e6,   # 1/Rl2
        )


class ppgParams(pycircuit.pagParams):

    u0 = (-49.011342155, -93.9168241966, -93.9168241966)

    start_grid = (
        (-200,200,41),
        (-70,170,8),
        )

    ranges = (
        (slice(45,395,60j), 3),
        (slice(95,445,60j), 3),
        )

    circuit = dict(
        Gco = -0.2,
        Gcf = 1e-5,
        C1  = 22e-9,
        G1  = 1/30e3,
        Gg  = 1/5e3,
        )


class pppParams(pycircuit.papParams):

    u0 = (-93.9168241966, 400.010411242, 400.010411241, 399.983840905, 399.983840905)

    start_grid = (
        (-200,200,41),
        (-200,200,41),
        (350.0,450.0,2),
        )

    ranges = (
        (slice(-260,185,110j), 3),
        (slice(-168,-51,40j), 3),
        (slice(302,428,10j), 3),
        )

    circuit = dict(
        Kp = 48.0,
        mu = 8.7,
        Ex = 1.35,
        Kg1 = 1460.0,
        Kg2 = 4500.0,
        Kvb = 12.0,
        Un = 450,
        C2 = 100e-6,
        Gd = 1/500e0,
        Ga = 1/1.7e3,
        Gs = 1/1e3,
        )

functions = {
    "ps":  psParams,
    "ppg": ppgParams,
    "ppp": pppParams,
    "ct":  ctcParams,
    }

def print_intpp_data(o, f):
    p = functions[f]
    if hasattr(p, "init"):
        p.init()
    print >>o, "namespace %s {" % f
    r = splinetable.print_intpp_data(o, "", "", p.func, p.NVALS, *p.ranges)
    print >>o, "splinedata sd = {"
    print >>o, "\tx0,"
    print >>o, "\th,"
    print >>o, "\tk,"
    print >>o, "\tn,"
    print >>o, "\tt,"
    print >>o, "\tc,"
    print >>o, "\t%d, /* number of calculated values */" % p.NVALS
    print >>o, "\t%d, /* number of input values */" % p.N_IN
    print >>o, "\t%d, /* number of output values */" % p.N_OUT
    n_state = p.NVALS-p.N_OUT
    print >>o, "\t%d, /* number of state values */" % n_state
    n = p.N_IN + n_state
    print >>o, "\tsplinedata::splev%s," % (n if n > 1 else "")
    print >>o, "};"
    print >>o, "}; /* ! namespace %s */" % f
    return r;

def main():
    sys.stderr.write("%s\n" % print_intpp_data(sys.stdout, sys.argv[1]))

if __name__ == "__main__":
    main()

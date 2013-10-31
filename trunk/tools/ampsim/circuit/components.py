from circuit import pycircuit

FS = pycircuit.fs

class Triode(pycircuit.tcParams):

    comp_id = "tc"
    comp_name = "single triode"

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

        Un = 350,
        )


class CoupledTriode(pycircuit.ctcParams):

    comp_id = "ct"
    comp_name = "coupled triodes"

    u0 = (-18, 0, 313, 214, 45, 35, 37)

    start_grid = (
        (-80.0, 80.0, 220),
        (0.0, 10.0, 2*30),
        (30.0, 350.0, 2*18),
        )

    @property
    def operating_point(self):
        return [2.2423, 266.95][:]

    ranges = (
        (-40,40),
        (0,10),
        (100,350),
        )

    def pre(a):
        a[0] += a[1]
        return a

    def post(a, o):
        o[1] -= a[1]
        o[2] -= a[2]
        return o

    basegrid = (
        (((331, 4), (4, 4), (10, 4)), pre, post),
        #L(((351, 2), (4, 2), (10, 2)), pre, post),
        (((331, 2), (10, 2), (10, 2)), pre, post, 1e-3),
        (((331, 2), (20, 2), (40, 2)), pre, post, 1e-3),
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


class PhaseSplitter(pycircuit.psParams):

    comp_id = "ps"
    comp_name = "phasesplitter"

    u0 = (-4.99999142644, -4.99999053336, 3.7459813383, 391.962467113,
          3.57356994824, 0.0264493076678, 0.0264491824349, 0.0264496771595,
          354.458081186)

    start_grid = (
        (-40.0, 40.0, 60),
        (-36.0, 0.0, 4),
        (20.0, 35.0, 4),
        (0.07, 0.25, 3),
        )

    @property
    def operating_point(self):
        return [-30.5966, 30.4599, 0.1367][:]

    ranges = (
        (slice(-40,40,81j), 3),
        (slice(-36.0,-1.0,30j), 3),
        (slice(23.0,35.0,8j), 3),
        (slice(0.07,0.26,2j), 2),
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


class PPGate(pycircuit.pagParams):

    comp_id = "ppg"
    comp_name = "poweramp gate"

    u0 = (-49.011342155, -93.9168241966, -93.9168241966)

    start_grid = (
        (-200,200,41),
        (-70,170,8),
        )

    @property
    def operating_point(self):
       return [311.045][:]

    ranges = (
        (slice(45,425,60j), 3),
        (slice(95,445,60j), 3),
        )

    circuit = dict(
        Gco = -0.2,
        Gcf = 1e-5,
        C1  = 22e-9,
        G1  = 1/30e3,
        Gb  = 1/220e3,
        Gg  = 1/5e3,
        Ub  = -48,
        )


class PPPlate(pycircuit.papParams):

    comp_id = "ppp"
    comp_name = "poweramp plate"

    u0 = (-93.9168241966, 400.010411242, 400.010411241, 399.983840905, 399.983840905)

    start_grid = (
        (-200,200,41),
        (-200,200,41),
        (350.0,450.0,2),
        )

    @property
    def operating_point(self):
        return [427.582][:]

    ranges = (
        (slice(-287,185,110j), 3),
        (slice(-265,-51,40j), 3),
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


################################################################
# JCM800 Poweramp
#

class PhaseSplitter_JCM800(pycircuit.psParams):

    comp_id = "ps_jcm800"
    comp_name = "jcm800 phasesplitter"

    u0 = (-4.99999142644, -4.99999053336, 3.7459813383, 391.962467113,
          3.57356994824, 0.0264493076678, 0.0264491824349, 0.0264496771595,
          354.458081186)

    start_grid = (
        (-70.0, 105.0, 60),
        (-76.0, 45.0, 25),
        (25.0, 35.0, 4),
        (0.07, 0.25, 3),
        )

    @property
    def operating_point(self):
        return [-29.77995343, 29.64688073, 0.13308519][:]

    ranges = (
        (-105,60),
        (-51.0,0.0),
        (25.0,35.0),
        (0.07,0.26),
        )

    def pre(a):
        a[0] += a[1]
        return a

    def post(a, o):
        o[2] -= a[1]
        o[3] -= a[2]
        o[4] -= a[3]
        return o

    basegrid = (
        (((301,4), (2,2), (20,4), (2,2)), pre, post, 4e-5),
        (((301,4), (2,2), (30,4), (2,2)), pre, post, 4e-5),
        #L(((950,2), (2,2), (80,2), (2,2)), pre, post, 4e-5),
        #L(((1100,2), (2,2), (100,2), (2,2)), pre, post, 4e-5),
        (((600,2), (2,2), (30,2), (2,2)), pre, post, 1e-4),
        (((700,2), (2,2), (50,2), (2,2)), pre, post, 1e-3),
        (((700,2), (2,2), (50,2), (2,2)), pre, post, 1e-3),
        )

    circuit = dict(
        # 12AX7 tube parameters
        Gco = -0.2,
        Gcf = 1e-5,
        mu  = 100.0,
        Ex  = 1.4,
        Kg1 = 1060.0,
        Kp  = 600.0,
        Kvb = 300.0,
        # other parameters
        C1 = 22e-9,
        C2 = 100e-9,
        C3 = 100e-9,
        Un = 390,
        G1 = 1/1e0,    # ??
        Gg1 = 1/1e6,
        Gg2 = 1/1e6,
        Gk = 1/470e0,
        G2 = 1/10e3,
        G3 = 1/100e3,
        G4 = 1/22e3,
        #G4 = 1/1.0,
        G5 = 1/4.7e3,
        Ga1 = 1/82e3,
        Ga2 = 1/100e3,
        Gl1 = 1/4e6,
        Gl2 = 1/4e6,
        )


class PPGate_JCM800(pycircuit.pagParams):

    comp_id = "ppg_jcm800"
    comp_name = "jcm800 poweramp gate"

    u0 = (-49.011342155, -93.9168241966, -93.9168241966)

    start_grid = (
        (-200,200,41),
        (-70,170,8),
        )

    @property
    def operating_point(self):
       return [311.045][:]

    ranges = (
        (-40, 500),
        (95, 445),
        )

    def pre_c1(a):
        a[0] += a[1] - 311.045
        return a

    def post_c1(a, o):
        o[1] -= a[1] - 311.045
        return o

    basegrid = (
        #S(((120, 4), (2, 2)), pre_c1, None),
        (((120, 2), (2, 2)), pre_c1, None),
        (((120, 2), (2, 2)), pre_c1, post_c1, 1e-3),
        )

    circuit = dict(
        Gco = -0.2,
        Gcf = 1e-5,
        C1  = 22e-9,
        G1  = 1/30e3,  # ??
        Gb  = 1/150e3,
        Gg  = 1/5.6e3,
        #Ub  = -57,
        Ub  = -60,
        )


class PPPlate_JCM800(pycircuit.papParams):

    comp_id = "ppp_jcm800"
    comp_name = "jcm800 poweramp plate"

    u0 = (-93.9168241966, 400.010411242, 400.010411241, 399.983840905, 399.983840905,
          (-93.9168241966+400.010411241/2), (400.010411242+400.010411241/2))

    start_grid = (
        #(-290,200,16*41),
        #(-290,200,4*41),
        #(300.0,440.0,2*2),
        (-200,200,41),
        (-200,200,41),
        (335.0,430.0,20),
        )

    @property
    def operating_point(self):
        return [427.582][:]

    ranges = (
        (-56.59-240,-56.59+210),
        #(-265,-51),
        (-56.59-240,-56.59+210),
        (340,468),
        )

    #def pre_in1(a):
    #    a[1] += a[0]
    #    return a

    def post(a, o):
        o[1] -= a[2]
        return o

    # basegrid = (
    #     (((110, 3), (110, 3), (10, 3)), None, None),
    #     (((110, 3), (110, 3), (10, 3)), None, None, 1e-6),
    #     #(((150, 4), (70, 4), (10, 4)), pre_in1, None),
    #     #(((4, 2), (4, 2), (4, 2)), None, None),
    #     )
    basegrid = (
        (((2*110, 4), (2*110, 4), (10, 4)), None, post, 1e-4),
        #L(((270, 2), (270, 2), (20, 2)), None, post, 1e-4),
        (((110, 2), (110, 2), (10, 2)), None, post, 1e-3),
        #(((150, 4), (70, 4), (10, 4)), pre_in1, None),
        #(((4, 2), (4, 2), (4, 2)), None, None),
        )

    circuit = dict(
        # EL34 tube parameters
        Kp = 60.0,
        mu = 11.0,
        Ex = 1.35,
        Kg1 = 650.0,
        Kg2 = 4200.0,
        Kvb = 24.0,
        #
        Un = 468,
        C2 = 100e-6,
        Gd = 1/500e0,  # ??
        Ga = 1/1.7e3,  # ??
        Gs = 1/1.5e3,
        )

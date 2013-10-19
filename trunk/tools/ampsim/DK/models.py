import math
import numpy as np
import sympy as sp

class GNDclass(object): pass
GND = GNDclass()

class NODESclass(object):
    def add_count(self, tc, conn): pass
    def process(self, p, conn, param, fs, m): pass
NODES = NODESclass()

class Node(object):
    def __init__(self, nm, d):
        self.nm = nm
        self.d = d
    def __repr__(self):
        return "%s%s" % (self.nm, self.d or "")
    def __hash__(self):
        return hash((self.nm,self.d))
    def __eq__(self, o):
        return self.nm == o.nm and self.d == o.d
    def __call__(self, s, fact=1.0):
        return OutU(self, s, fact)

class INclass(Node):
    def __init__(self):
        Node.__init__(self, "IN", None)
    def add_count(self, tc, conn):
        self.conn = conn
        tc["V"] += len(conn)
        tc["I"] = len(conn)
    def process(self, p, conn, param, fs, m):
        for i, c in enumerate(conn):
            idx = p.new_row("V", self, self.conn[i])
            p.S[idx, c] += 1
            p.S[c, idx] += 1
            n = p.new_row("I", self, self.conn[i])
            p.N["I"][n, idx] = 1
IN = INclass()


class Out(object):
    def __init__(self, node, fact=1.0):
        self.node = node
        self.fact = fact

    def get_index(self, p):
        return p.nodes[self.node], self.fact

    def __repr__(self):
        if self.fact != 1.0:
            return "%s*%g" % (self.node, self.fact)
        else:
            return self.node


class OutU(Out):
    def __init__(self, node, f, fact):
        self.node = node
        self.f = f
        self.fact = fact

    def get_index(self, p):
        return p.extra_variable_by_name((self.node,self.f)), self.fact

    def __repr__(self):
        return "%s%s" % (self.node, self.f and ("[%s]" % self.f) or "")

class OUTclass(Node):
    def __init__(self):
        Node.__init__(self, "OUT", None)
    def add_count(self, tc, conn):
        self.conn = conn
        tc["O"] += len(conn)
    def process(self, p, conn, param, fs, m):
        for c in conn:
            v = 1
            if isinstance(c, Out):
                c, fact = c.get_index(p)
                v = fact
            p.N["O"][p.new_row("O", self), c] = v
OUT = OUTclass()

class R(Node):
    def __init__(self, n=None):
        Node.__init__(self, "R", n)
    def add_count(self, tc, conn):
        tc["R"] += 1
    def process(self, p, conn, param, fs, m):
        idx = p.new_row("R", self)
        p.add_2conn("R", idx, conn)
        p.Gr[idx] = 1.0 / param

class C(Node):
    def __init__(self, n=None):
        Node.__init__(self, "C", n)
    def add_count(self, tc, conn):
        tc["X"] += 1
    def process(self, p, conn, param, fs, m):
        idx = p.new_row("X", self)
        value = m * param * fs
        p.add_S_currents(conn, value)
        p.add_2conn("Xl", idx, conn, value)
        p.add_2conn("Xr", idx, conn)
        p.Z[idx] = 1

class L(Node):
    def __init__(self, n=None):
        Node.__init__(self, "L", n)
    def add_count(self, tc, conn):
        tc["X"] += 1
    def process(self, p, conn, param, fs, m):
        idx = p.new_row("X", self)
        value = 1 / (m * param * fs)
        p.add_S_currents(conn, value)
        p.add_2conn("Xl", idx, conn, value)
        p.add_2conn("Xr", idx, conn)
        p.Z[idx] = -1

class D(Node):
    def __init__(self, n=None):
        Node.__init__(self, "D", n)
    def add_count(self, tc, conn):
        tc["N"] += 1
    def process(self, p, conn, param, fs, m):
        Is, mUt = const = sp.symbols("Is,mUt")
        v0, = v = sp.symbols("v:1", seq=True)
        calc = -Is * (sp.exp(v0/mUt) - 1)
        calc = calc.subs(dict([(k,param[str(k)]) for k in const]))
        idx = p.new_row("N", self)
        p.add_2conn("Nl", idx, conn)
        p.add_2conn("Nr", idx, conn)
        p.f[idx] = (calc, v, idx)

class D2(Node):
    def __init__(self, n=None):
        Node.__init__(self, "D", n)
    def add_count(self, tc, conn):
        tc["N"] += 1
    def process(self, p, conn, param, fs, m):
        Is, mUt = const = sp.symbols("Is,mUt")
        v0, = v = sp.symbols("v:1", seq=True)
        calc = -2 * Is * sp.sinh(v0/mUt)
        calc = calc.subs(dict([(k,param[str(k)]) for k in const]))
        idx = p.new_row("N", self)
        p.add_2conn("Nl", idx, (conn[0], conn[1]))
        p.add_2conn("Nr", idx, (conn[0], conn[1]))
        p.f[idx] = (calc, v, idx)

class T(Node):
    def __init__(self, n=None):
        Node.__init__(self, "T", n)
    def add_count(self, tc, conn):
        tc["N"] += 2
    def process(self, p, conn, param, fs, m):
        Is, Bf, Vt, Br = const = sp.symbols("Is,Bf,Vt,Br")
        v0, v1 = v = sp.symbols("v:2")
        calc_ib = Is / Bf * (sp.exp((v1-v0)/Vt)-1) + Is/Br * (sp.exp(-v0/Vt)-1)
        calc_ib = calc_ib.subs(dict([(k,param[str(k)]) for k in const]))
        calc_ic = -Is*(sp.exp((v1-v0)/Vt)-1) + Is*(Br-1)/Br * (sp.exp(-v0/Vt)-1)
        calc_ic = calc_ic.subs(dict([(k,param[str(k)]) for k in const]))
        idx1 = p.new_row("N", self)
        p.add_2conn("Nl", idx1, (conn[1],conn[0]))
        p.add_2conn("Nr", idx1, (conn[1],conn[0]))
        p.f[idx1] = (calc_ib, v, idx1)
        idx2 = p.new_row("N", self)
        p.add_2conn("Nl", idx2, (conn[1],conn[2]))
        p.add_2conn("Nr", idx2, (conn[1],conn[2]))
        p.f[idx2] = (calc_ic, v, idx1)

class Triode(Node):
    def __init__(self, n=None):
        Node.__init__(self, "Triode", n)
    def add_count(self, tc, conn):
        tc["N"] += 2
    def process(self, p, conn, param, fs, m):
        mu, Ex, Kp, Kvb, Kg1, Gco, Gcf = const = sp.symbols("mu,Ex,Kp,Kvb,Kg1,Gco,Gcf")
        Ugk, Uak = v = sp.symbols("Ugk,Uak")
        t = Kp*(1/mu+Ugk/sp.sqrt(Kvb+Uak*Uak))
        E1 = Uak/Kp*sp.log(1+sp.exp(t))
        E1_ = Uak/Kp*t
        calc_Ia = sp.Piecewise(
            (0, Uak < 0),
            (0, t < -500),
            (-pow(E1_,Ex) / Kg1 * 2*(E1_ > 0.0), t > 500),
            (-pow(E1,Ex) / Kg1 * 2*(E1 > 0.0), True))
        calc_Ia = calc_Ia.subs(dict([(k,param[str(k)]) for k in const]))
        calc_Ig = sp.Piecewise((0, Ugk < Gco), (-Gcf*pow(Ugk-Gco, 1.5), True))
        calc_Ig = calc_Ig.subs(dict([(k,param[str(k)]) for k in const]))
        # def calc_Ia(v):
        #     Ugk = float(v[0])
        #     Uak = float(v[1])
        #     if Uak < 0:
        #         return 0
        #     t = Kp*(1/mu+Ugk/math.sqrt(Kvb+Uak*Uak))
        #     if t > 500:
        #         E1 = Uak/Kp*t
        #     elif t < -500:
        #         return 0
        #     else:
        #         E1 = Uak/Kp*math.log(1+math.exp(t))
        #     r = pow(E1,Ex) / Kg1 * 2*(E1 > 0.0)
        #     return -r
        # def calc_Ig(v):
        #     Ugk = float(v[0])
        #     if Ugk < Gco:
        #         return 0
        #     r = Gcf*pow(Ugk-Gco, 1.5)
        #     return -r
        idx1 = p.new_row("N", self, "Ig")
        p.add_2conn("Nl", idx1, (conn[0],conn[2]))
        p.add_2conn("Nr", idx1, (conn[0],conn[2]))
        p.f[idx1] = (calc_Ig, v, idx1)
        idx2 = p.new_row("N", self, "Ip")
        p.add_2conn("Nl", idx2, (conn[1],conn[2]))
        p.add_2conn("Nr", idx2, (conn[1],conn[2]))
        p.f[idx2] = (calc_Ia, v, idx1)

class Pentode(Node):
    def __init__(self, n=None):
        Node.__init__(self, "Pentode", n)
    def add_count(self, tc, conn):
        tc["N"] += 3
    def process(self, p, conn, param, fs, m):
        mu, Ex, Kp, Kg1, Kg2, Kvb, Gco, Gcf = const = sp.symbols("mu,Ex,Kp,Kg1,Kg2,Kvb,Gco,Gcf")
        Ug1k, Ug2k, Uak = v = sp.symbols("Ug1k,Ug2k,Uak")
        t = Kp * (1 / mu + Ug1k / Ug2k)
        E1 = Ug2k / Kp * sp.log(1 + sp.exp(t))
        E1_ = Ug2k / Kp * t
        calc_Ia = sp.Piecewise(
            (0, Ug2k <= 0),
            (0, t < -500),
            (-pow(E1_,Ex)/Kg1 * 2*(E1_ > 0.0) * sp.atan(Uak/Kvb), t > 500),
            (-pow(E1,Ex)/Kg1 * 2*(E1 > 0.0) * sp.atan(Uak/Kvb), True))
        calc_Ia = calc_Ia.subs(dict([(k,param[str(k)]) for k in const]))
        calc_Ig = sp.Piecewise((0, Ug1k < Gco), (-Gcf*pow(Ug1k-Gco, 1.5), True))
        calc_Ig = calc_Ig.subs(dict([(k,param[str(k)]) for k in const]))
        t = Ug2k / mu + Ug1k
        calc_Is = sp.Piecewise((0, t <= 0), (-sp.exp(Ex*sp.log(t)) / Kg2, True))
        calc_Is = calc_Ig.subs(dict([(k,param[str(k)]) for k in const]))
        # def calc_Ia(v):
        #     Ug1k = float(v[0])
        #     Ug2k = float(v[1])
        #     Uak = float(v[2])
        #     if Ug2k <= 0.0:
        #         return 0
        #     t = Kp * (1 / mu + Ug1k / Ug2k)
        #     if t > 500:
        #         E1 = Ug2k / Kp * t
        #     elif t < -500:
        #         return 0
        #     else:
        #         E1 = Ug2k / Kp * math.log(1 + math.exp(t))
        #     r = pow(E1,Ex)/Kg1 * 2*(E1 > 0.0) * math.atan(Uak/Kvb);
        #     #print Ug1k, Ug2k, Uak, r
        #     return -r
        # def calc_Ig(v):
        #     Ugk = float(v[0])
        #     if Ugk < Gco:
        #         return 0
        #     r = Gcf*pow(Ugk-Gco, 1.5)
        #     return -r
        # def calc_Is(v):
        #     Ug1k = float(v[0])
        #     Ug2k = float(v[1])
        #     t = Ug2k / mu + Ug1k
        #     if t <= 0:
        #         return 0
        #     r = math.exp(Ex*math.log(t)) / Kg2
        #     return -r

        idx1 = p.new_row("N", self, "Ig")
        p.add_2conn("Nl", idx1, (conn[0],conn[3]))
        p.add_2conn("Nr", idx1, (conn[0],conn[3]))
        p.f[idx1] = (calc_Ig, v, idx1)
        idx2 = p.new_row("N", self, "Is")
        p.add_2conn("Nl", idx2, (conn[1],conn[3]))
        p.add_2conn("Nr", idx2, (conn[1],conn[3]))
        p.f[idx2] = (calc_Is, v, idx1)
        idx3 = p.new_row("N", self, "Ip")
        p.add_2conn("Nl", idx3, (conn[2],conn[3]))
        p.add_2conn("Nr", idx3, (conn[2],conn[3]))
        p.f[idx3] = (calc_Ia, v, idx1)

class Trans_L(Node):
    def __init__(self, n=None, nw=3):
        self.nw = nw
        Node.__init__(self, "TL", n)
    def add_count(self, tc, conn):
        tc["X"] += 1
        tc["V"] += self.nw + 2
    def process(self, p, conn, param, fs, m):
        alpha = m * fs
        start = p.current_row("V") + 1
        end = start + self.nw + 1
        for i in range(self.nw):
            s = "W%d" % (i+1)
            idx = p.new_row("V", self, s)
            p.add_S(idx, conn[2*i:], 1)
            p.S[idx, end] += param["windings"][i]
        idx = p.new_row("V", self, "phi")
        p.S[idx, start:end-1] += np.array(param["windings"])
        p.S[idx, end-1] += param["R"]
        idx_v = p.new_row("V", self, "v")
        p.S[idx_v, idx_v] += 1
        p.S[idx_v, idx] += alpha
        idx_xv = p.new_row("X", self, "v")
        p.N["Xl"][idx_xv, idx] = alpha
        p.N["Xr"][idx_xv, idx_v] = 1
        p.Z[idx_xv] = 1

class Trans_F(Node):
    def __init__(self, n=None, nw=3):
        self.nw = nw
        Node.__init__(self, "TF", n)
    def add_count(self, tc, conn):
        tc["X"] += 1
        tc["V"] += self.nw + 2
        tc["N"] += 1
    def process(self, p, conn, param, fs, m):
        b, c = const = sp.symbols("b,c")
        v0, = v = sp.symbols("v:1", seq=True)
        calc_frohlich = -(c * v0) / (1 - b * abs(v0))
        calc_frohlich = calc_frohlich.subs(dict([(k,param[str(k)]) for k in const]))
        # def calc_frohlich(v):
        #     v = float(v[0])
        #     #b = 255.
        #     #c = 358.
        #     r = (c * v) / (1 - b * abs(v))
        #     return -r
        alpha = m * fs
        start = p.current_row("V") + 1
        end = start + self.nw + 1
        for i in range(self.nw):
            s = "W%d" % (i+1)
            idx = p.new_row("V", self, s)
            p.add_S(idx, conn[2*i:], 1)
            p.S[idx, end] += param["windings"][i]
        idx = p.new_row("V", self, "phi")
        p.S[idx, start:end-1] += np.array(param["windings"])
        idx_v = p.new_row("V", self, "v")
        p.S[idx_v, idx_v] += 1
        p.S[idx_v, idx] += alpha
        idx_xv = p.new_row("X", self, "v")
        p.N["Xl"][idx_xv, idx] = alpha
        p.N["Xr"][idx_xv, idx_v] = 1
        p.Z[idx_xv] = 1
        idx = p.new_row("N", self, "phi")
        p.N["Nl"][idx, end-1] = 1
        p.N["Nr"][idx, end-1] = 1
        p.f[idx] = (calc_frohlich, v, idx)

class Trans_GC(Node):
    def __init__(self, n=None, nw=3):
        self.nw = nw
        Node.__init__(self, "TG", n)
    def add_count(self, tc, conn):
        tc["X"] += 1
        tc["V"] += self.nw + 2
        tc["N"] += 1
    def process(self, p, conn, param, fs, m):
        C, a, n = const = sp.symbols("C,a,n")
        v0, = v = sp.symbols("v:1", seq=True)
        t = v0 / C
        calc_gc_MMF = -(t + a * pow(abs(t), n) * sp.sign(t))
        calc_gc_MMF = calc_gc_MMF.subs(dict([(k,param[str(k)]) for k in const]))
        # def calc_gc_MMF(v):
        #     v = float(v[0])
        #     #C = 2e-3
        #     #a = 1e-5
        #     #n = 25
        #     t = v / C
        #     if v >= 0:
        #         t2 = pow(t, n)
        #     else:
        #         t2 = -pow(-t, n)
        #     r = -(t + a * t2)
        #     return r
        alpha = m * fs
        start = p.current_row("V") + 1
        end = start + self.nw + 1
        for i in range(self.nw):
            s = "W%d" % (i+1)
            idx = p.new_row("V", self, s)
            p.add_S(idx, conn[2*i:], 1)
            p.S[idx, end] += param["windings"][i]
        idx = p.new_row("V", self, "phi")
        p.S[idx, start:end-1] += np.array(param["windings"])
        idx_v = p.new_row("V", self, "v")
        p.S[idx_v, idx_v] += 1
        p.S[idx_v, idx] += alpha
        idx_xv = p.new_row("X", self, "v")
        p.N["Xl"][idx_xv, idx] = alpha
        p.N["Xr"][idx_xv, idx_v] = 1
        p.Z[idx_xv] = 1
        idx = p.new_row("N", self, "phi")
        p.N["Nl"][idx, end-1] = 1
        p.N["Nr"][idx, end-1] = 1
        p.f[idx] = (calc_gc_MMF, v, idx)

class OPA_L(Node):
    def __init__(self, n=None):
        Node.__init__(self, "OPA_L", n)
    def add_count(self, tc, conn):
        tc["V"] += 1
    def process(self, p, conn, param, fs, m):
        idx = p.new_row("V", self)
        p.S[idx, conn[2]] += 1
        p.S[conn[2], idx] += 1
        p.S[idx, conn[0]] += param
        p.S[idx, conn[1]] += -param

class OPA(Node):
    def __init__(self, n=None):
        Node.__init__(self, "OPA", n)
    def add_count(self, tc, conn):
        tc["V"] += 1
        tc["N"] += 1
    def process(self, p, conn, param, fs, m):
        Vcc, Vee, A = const = sp.symbols("Vcc,Vee,A")
        v0, = v = sp.symbols("v:1", seq=True)
        a = 2*A/(Vcc-Vee)
        calc = 0.5 * (sp.tanh(a*v0) * (Vcc-Vee) + Vcc + Vee)
        calc = calc.subs(dict([(k,param[str(k)]) for k in const]))
        # def calc(v):
        #     Vcc = 10
        #     Vee = -10
        #     A = 1e5
        #     a = 2*A/(Vcc-Vee)
        #     return 0.5 * (np.tanh(a*v[0]) * (Vcc-Vee) + Vcc + Vee)
        idx_s = p.new_row("V", self)
        p.S[idx_s, conn[2]] += 1
        p.S[conn[2], idx_s] += 1
        idx = p.new_row("N", self)
        p.add_conn("Nl", idx, conn[0], 1)
        p.add_conn("Nl", idx, conn[1], -1)
        p.add_conn("Nr", idx, idx_s, 1)
        p.f[idx] = (calc, v, idx)

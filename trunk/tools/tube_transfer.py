# -*- coding: utf-8 -*-
#
# Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
# Copyright (C) 2011 Pete Shorthose
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#----------------------------------------------------------------
#
# lots of hints and some numerical values taken from
# Virtual Air Guitar (Matti Karjalainen, Teemu Maki-Patola, Aki Kanerva, Antti Huovilainen)
#

import sys
from pylab import *
from scipy.optimize import newton

#
#                                 o V+         
#                                 |            
#                                 |            
#                                 |            
#                                +-+           
#                                | |           
#                             Rp | |           
#                                | |    Co     
#                                +-+           
#                                 |     ||       
#                                 +-----++---o Vo
#                              Vp |     ||
#                                 |
#     Ci                        --+--  
#                    Ri        /--+--  
#     ||  Vi      +-----+  Vg /         12AX7
# o---++--+-------|     |-----+- - - - 
#     ||  |       +-----+     \        
#         |                    \/----
#         |                    /-----
#         |                   /
#        +-+               Vk |
#        | |                  +------+    
#        | |                  |      |    
#        | |                  |      |    
#        +-+                 +-+     |    
#         |                  | |    -+-   
#         |               Rk | |    -+- Ck
#         |                  | |     |
#       -----                +-+     |
#        ---                  |      |
#         o                   |      |
#                             |      |
#                           -----  -----
#                            ---    ---
#                             o      o
#
#
# mu    Amplification factor.
# kx    Exponent:
# kg1   Inversely proportional to overall plate current
# kp    Affects opration in region of large plate voltage and large negative grid voltage
# kvb   Knee volts
#
names  = ("mu", "kx", "kg1", "kg2", "kp", "kvb", "ccg", "cpg", "ccp", "rgi")
factor = ( 1.0,  1.0,   1.0,   1.0,  1.0,   1.0, 1e-12, 1e-12, 1e-12,   1e3)
tubes  = {
    #TUBE        MU    EX      KG1     KG2     KP    KVB   CCG*  CPG*   CCP*  RGI**
    "6DJ8" : ( 28.0,  1.3,   330.0,   None, 320.0, 300.0,  2.3,  2.1,   0.7,  2.0),
    "6L6CG": (  8.7,  1.35, 1460.0, 4500.0,  48.0,  12.0, 14.0,  0.85, 12.0,  1.0),
    "12AX7": (100.0,  1.4,  1060.0,   None, 600.0, 300.0,  2.3,  2.4,   0.9,  2.0),
    "12AT7": ( 60.0,  1.35,  460.0,   None, 300.0, 300.0,  2.7,  2.2,   1.0,  2.0),
    "12AU7": ( 21.5,  1.3,  1180.0,   None,  84.0, 300.0,  2.3,  2.2,   1.0,  2.0),
    "6550" : (  7.9,  1.35,  890.0, 4800.0,  60.0,  24.0, 14.0,  0.85, 12.0,  1.0),
    "KT88" : (  8.8,  1.35,  730.0, 4200.0,  32.0,  16.0, 14.0,  0.85, 12.0,  1.0),
    #"EL34" : ( 60.0,  4.8,  2000.0,   None, 800.0,  50.0, None, None,  None, None),
    "EL34" : ( 11.0,  1.35,  650.0, 4200.0,  60.0,  24.0, 15.0,  1.0,   8.0,  1.0),
    "2A3"  : (  4.2,  1.4,  1500.0,   None,  60.0, 300.0,  8.0, 17.0,   6.0,  1.0),
    "300B" : (  3.95, 1.4,  1550.0,   None,  65.0, 300.0, 10.0, 16.0,   5.0,  1.0),
    "6C33C": (  3.1,  1.4,   163.0,   None,  15.0, 300.0, 31.0, 31.0,  11.0,  0.5),
    "6C16": (  42.2,  2.21,  393.0,   None, 629.0, 446.0,  9.0,  1.8,  0.48,  2.0),
    # * : 10^-12 (pF)
    # **: 10^3 (kOhm)
}

class Circuit(object):

    # Parameters for circuit / approximation
    table_size = 2001
    Uin_range = (-5.0, 5.0)
    # This could be user choice
#    Vp = 250
    Vp = 300	# Better for output section
    # For power valves this Rp is too high???
#    Rp  = 100e3
#    Rp  = 7e3	# Transformer for Pentode around this
    Rp  = 3.5e3   # Transformer for triode wired 
# These values are also not right for po
    Ri_values = (68e3, 250e3)

    # class data
    used_names = ("mu", "kx", "kg1", "kp", "kvb")
    ipk_tab = { "triode": "Ipk_triode", "pentode": "Ipk_triode_pentode" }
    Vi = linspace(Uin_range[0],Uin_range[1],table_size)

    @classmethod
    def help(self):
        return ("tube: %s\nplate current functions: %s" % (
            ", ".join(sorted(tubes.keys())),
            ", ".join(sorted(self.ipk_tab.keys()))))

    def __init__(self, tube, ipk_func):
        self.tube = tube
        self.ipk_func = ipk_func
        error = False
        if tube not in tubes:
            print "tube '%s' not found" % tube
            error = True
        if ipk_func not in self.ipk_tab:
            print "plate current function '%s' not found" % ipk_func
            error = True
        if error:
            print
            usage()
        for n, f, v in zip(names, factor, tubes[tube]):
            if v is not None:
                setattr(self, n, f*v)
        self.Ipk = getattr(self, self.ipk_tab[ipk_func])
        self.FtubeV = vectorize(self.Ftube)

    def Igk_Vgk(self, Vgk):
        """gate current as function of gate-kathode voltage"""
        return exp(7.75*Vgk-10.3)

    def Ipk_triode_pentode(self, Vgk, Vpk):
        """Koren model of pentode connected as class A triode
        (screen connected to plate):
        plate current as function of gate-kathode voltage
        and plate-kathode voltage
        """
        E1 = Vpk/self.kp*log(1+exp(self.kp*(1/self.mu+Vgk/Vpk)))
        return 2*E1**self.kx/self.kg1*(E1>0.0)*arctan(Vpk/self.kvb)

    def Ipk_triode(self, Vgk, Vpk):
        """
        Koren model of triode:
        plate current as function of gate-kathode voltage
        and plate-kathode voltage
        """
        E1 = Vpk/self.kp*log(1+exp(self.kp*(1/self.mu+Vgk/sqrt(self.kvb+Vpk*Vpk))))
        return 2*E1**self.kx/self.kg1*(E1>0.0)

    def Ftube(self, Vi, Ri):
        """calculate output voltage of a tube circuit as function of input voltage
        Vi  input voltage
        Ri  value of resistor Ri
        """
        def fi(Vgk, Vi, Ri):
            return Vi - Vgk - Ri * self.Igk_Vgk(Vgk) # sum of voltages -> zero

        Vgk = newton(fi, self.Igk_Vgk(0), args=(Vi, Ri))   # Vgk(Vi)

        def fp(Vpk, Vgk, Ipk):
            return Vpk + self.Rp * Ipk(Vgk, Vpk) - self.Vp

        return newton(fp, self.Vp/2, args=(Vgk,self.Ipk))   # Vpk(Vgk)

    def Vk0(self, Ri, Rk):
        v0 = 0
        def f(v):
            return (self.Ftube(-v, Ri)-self.Vp)*(Rk/self.Rp) + v
        return newton(f, v0)

    def write_ftube_table(self, Ri, Vi, Vp):
        """write C source"""
        sys.stdout.write("\t{ // Ri = %dk\n" % (Ri/1e3))
        sys.stdout.write('\t%g,%g,%g,%d, {' % (Vi[0], Vi[-1], (len(Vi)-1)/(Vi[-1]-Vi[0]), self.table_size))
        s = ""
        for i, v in enumerate(Vi):
            if i % 5 == 0:
                sys.stdout.write(s+"\n\t")
                s = ""
            sys.stdout.write(s+str(Vp[i]))
            s = ","
        sys.stdout.write("\n\t}}")

    def write_tables(self, prgname):
        sys.stdout.write("// generated by %s\n" % prgname)
        sys.stdout.write("// tube: %s\n" % self.tube)
        sys.stdout.write("// plate current function: %s\n" % self.ipk_func)
        for n in self.used_names:
            sys.stdout.write("// %s: %g\n" % (n, getattr(self, n)))
        sys.stdout.write("\n")
        sys.stdout.write("table1d_imp<%d> tubetable_%s[%d] = {\n"
                         % (self.table_size, self.tube, len(self.Ri_values)))
        s = ""
        for Ri in self.Ri_values:
            sys.stdout.write(s)
            s = ",\n"
            Vp = self.FtubeV(self.Vi, Ri)
            self.write_ftube_table(Ri, self.Vi, Vp)
        sys.stdout.write("\n};\n")

    def R_name(self, r):
        for f, n in (1e6,"M"),(1e3,"k"),(1,""):
            if r >= f:
                return ("%g%s" % (r/f, n)).replace(".","_")

    def show_vk0(self, args):
        if args:
            Ri = float(args[0])
            Rk = float(args[1])
        else:
            try:
                while True:
                    vl = ["%d: %s" % (i, self.R_name(r)) for i, r in enumerate(self.Ri_values)]
                    i = raw_input("Ri [%s]: " % ", ".join(vl))
                    try:
                        i = int(i)
                    except ValueError:
                        pass
                    else:
                        if 0 <= i < len(self.Ri_values):
                            Ri = self.Ri_values[i]
                            break
                    print "error: illegal input"
                while True:
                    try:
                        Rk = float(raw_input("Rk: "))
                        break
                    except ValueError:
                        print "error: please enter float value"
            except KeyboardInterrupt:
                print
                return
        print "%f" % self.Vk0(Ri,Rk)

    def check_table_accuracy(self, Ri):
        """maximal relative table error at half interval"""
        def ip(x):
            return (x[:-1]+x[1:])/2
        Vp = self.FtubeV(self.Vi, Ri)
        VpM = self.FtubeV(ip(self.Vi), Ri)
        VpD = (ip(Vp) - VpM) / VpM
        return max(VpD)

    def display_accuracy(self):
        for Ri in self.Ri_values:
            print "Ri=%dk: %g" % (Ri/1e3, self.check_table_accuracy(Ri))
    
    def plot_Ftube(self):
        title(self.tube)
        for Ri in self.Ri_values:
            Vp = self.FtubeV(self.Vi, Ri)
            plot(self.Vi, Vp, label="Ri=%dk" % (Ri/1e3))
        xlabel("Vik")
        ylabel("Vp")
        legend()
        axis
        show()


def usage():
    print "usage: %s plot|accuracy|table|vk0 tube-name plate-func" % sys.argv[0]
    print Circuit.help()
    raise SystemExit, 1

def main():
    if len(sys.argv) < 4:
        usage()
    cmd = sys.argv[1]
    c = Circuit(sys.argv[2], sys.argv[3])
    if cmd == "plot":
        c.plot_Ftube()
    elif cmd == "accuracy":
        c.display_accuracy()
    elif cmd == "table":
        c.write_tables(sys.argv[0])
    elif cmd == "vk0":
        c.show_vk0(sys.argv[4:])
    else:
        usage()

if __name__ == "__main__":
    main()

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
    #TUBE         MU    EX      KG1     KG2     KP     KVB    CCG*  CPG*   CCP*  RGI**
    "6DJ8"   : ( 28.0,  1.3,   330.0,      0,  320.0, 300.0,  2.3,  2.1,   0.7,  2.0),
    "6L6CG"  : (  8.7,  1.35, 1460.0, 4500.0,   48.0,  12.0, 14.0,  0.85, 12.0,  1.0),
    "12AX7"  : (100.0,  1.4,  1060.0,      0,  600.0, 300.0,  2.3,  2.4,   0.9,  2.0),
    "12AT7"  : ( 60.0,  1.35,  460.0,      0,  300.0, 300.0,  2.7,  2.2,   1.0,  2.0),
   #"12AT7"  : ( 67.5,  1.23,  419.1,      0,  214.0, 300.0,  2.3,  2.2,   1.0,  2.0),
   #"12AT7WA": ( 72.8,  1.67,  341.8,      0,  233.2, 267.8,  2.3,  2.2,   1.0,  2.0),
    "12AU7"  : ( 21.5,  1.3,  1180.0,      0,   84.0, 300.0,  2.3,  2.2,   1.0,  2.0),
   #"12AU7"  : ( 20.2,  1.23, 1108.0,      0,   84.9, 551.0,  2.3,  2.2,   1.0,  2.0),
    "12AY7"  : (44.16,  1.11, 1192.4,      0, 409.96, 300.0,  2.0,  2.0,   1.0,  2.0),
    "12AZ7"  : (74.08,  1.37,  382.4,      0, 190.11, 300.0,  2.3,  2.2,   1.0,  2.0),
    "12BH7A" : (24.59,  1.34,  594.4,      0,  73.01, 300.0,  3.9,  3.2,   1.0,  2.0),
    "6550"   : (  7.9,  1.35,  890.0, 4800.0,   60.0,  24.0, 14.0, 0.85,  12.0,  1.0),
    "KT88"   : (  8.8,  1.35,  730.0, 4200.0,   32.0,  16.0, 14.0, 0.85,  12.0,  1.0),
   #"EL34"   : ( 60.0,   4.8, 2000.0,      0,  800.0,  50.0,    0,    0,     0,    0),
    "EL34_o" : ( 11.0,  1.35,  650.0, 4200.0,   60.0,  24.0, 15.0,  1.0,   8.0,  1.0),
    "EL34"   : ( 12.3,  1.17,  353.9, 4500.0,   61.1,  29.9, 15.0,  1.0,   8.0,  1.0),
    "SVEL34" : ( 11.5,  1.35,  608.9, 4500.0,   41.2,  30.1, 15.0,  1.0,   8.0,  1.0),
    "SV6N1P" : ( 36.6,  1.53, 1020.2,      0,  193.2, 300.0,  3.7,  2.3,   2.2,  2.0),
    "EL84"   : ( 21.3,  1.24,  401.7, 4500.0,  111.1,  17.9, 10.0,  0.6,   5.1,  1.0),
    "6AB8"   : ( 39.1,  0.93,  228.9, 4500.0,   50.2,  21.2,  6.7,  0.6,   4.1,  2.0),
   #"2A3"    : ( 4.05,  1.63, 3652.2,      0,   58.5, 300.0, 17.0,  8.2,   6.0,  1.0),
   #"300B"   : ( 3.92,   1.5, 2140.3,      0,   64.0, 300.0, 17.0, 11.0,   7.5,  1.0),
   #"6C33C"  : (  3.1,   1.4,  163.0,      0,   15.0, 300.0, 31.0, 31.0,  11.0,  0.5),
    "6C16"   : ( 42.2,  2.21,  393.0,      0,  629.0, 446.0,  9.0,  1.8,  0.48,  2.0),
    "ECL80T" : ( 29.3,  1.33, 1443.9,      0,   45.5, 300.0,  3.2,  2.7,   1.8,  2.0),
    "ECL81T" : ( 66.3,  1.39, 1400.2,      0,  369.3,   2.5,  3.2,  2.7,   1.8,  2.0),
    "ECL83T" : (119.1,  1.32,  732.7,      0,  305.2,   1.8,  3.2,  2.7,   1.8,  2.0),
    "JJECC81": ( 77.1,  1.08,  320.0,      0,  230.0, 300.0,  2.3,  2.2,   1.0,  2.0),
    "JJECC82": ( 24.1,  1.25, 1023.1,      0,   65.2, 300.0,  2.3,  2.2,   1.0,  2.0),
    "JJECC83S":( 98.3,  1.45, 1722.8,      0,  749.4, 131.2,  2.3,  2.4,   0.9,  2.0),
    "JJECC99": ( 23.1,  1.46,  455.3,      0,  191.9, 300.0,  2.3,  2.2,   1.0,  2.0),
    # * : 10^-12 (pF)
    # **: 10^3 (kOhm)
}

class Circuit(object):

    # Parameters for circuit / approximation
    table_size = 2001
    Uin_range = (-5.0, 5.0)
    # This could be user choice
    Vp = 250
#    Vp = 300	# Better for output section
    # For power valves this Rp is too high???
    Rp  = 100e3
#    Rp  = 7e3	# Transformer for Pentode around this
#    Rp  = 3.5e3   # Transformer for triode wired 
# These values are also not right for po
    Ri_values = (68e3, 250e3)

    # class data
    used_names = ("mu", "kx", "kg1","kg2", "kp", "kvb")
    ipk_tab = { "triode": "Ipk_triode", "pentode": "Ipk_triode_pentode", "pentode2": "Ipk_pentode" }
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

    def Ipk_pentode(self, Vgk, Vpk):
        """
        LOGICAL ERROR in this, should become this:
        E1  ={V(2,4)/KP*LOG(1+EXP((1/MU+V(3,4)/V(2,4))*KP))} ; E1 BREAKS UP LONG EQUATION FOR G1.
        G1   ={(PWR(V(7),EX)+PWRS(V(7),EX))/KG1*ATAN(V(1,4)/KVB)}
        G2   ={(EXP(EX*(LOG((V(2,4)/MU)+V(3,4)))))/KG2}
        """
        E1 = Vpk/self.kp*log(1+exp(self.kp*(1/self.mu+Vgk/Vpk)))
        G1 = 2*E1**self.kx/self.kg1*(E1>0.0)*arctan(Vpk/self.kvb)
        return (G1+exp(self.kx*(log(Vpk/self.mu)+Vgk)))/self.kg2

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
        sys.stdout.write("table1d_imp<%d> tubetable_%s[%d] __rt_data = {\n"
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
    
    def s_plot_Ftube(self):
        title(self.tube)
        for Ri in self.Ri_values:
            Vp = self.FtubeV(self.Vi, Ri)
            plot(self.Vi, Vp, label="Ri=%dk" % (Ri/1e3))
        xlabel("Vik")
        ylabel("Vp")
        legend()
        axis
        savefig("%s.png" % self.tube)


def usage():
    print "usage: %s plot|s_plot|accuracy|table|vk0 tube-name plate-func" % sys.argv[0]
    print Circuit.help()
    raise SystemExit, 1

def main():
    if len(sys.argv) < 4:
        usage()
    cmd = sys.argv[1]
    c = Circuit(sys.argv[2], sys.argv[3])
    if cmd == "plot":
        c.plot_Ftube()
    elif cmd == "s_plot":
        c.s_plot_Ftube()
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

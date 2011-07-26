# -*- coding: utf-8 -*-
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

#		TUBE 	MU 	    EX  	KG1 	KG2 	KP  	KVB 	CCG 	CPG 	CCP 	RGI
#		6DJ8 	28 	    1.3 	330 	    	320 	300 	2.3P 	2.1P 	0.7P 	2k
#		6L6CG 	8.7 	1.35 	1460 	4500 	48  	12  	14P 	0.85P 	12P 	1k
#		12AX7 	100 	1.4 	1060 	    	600 	300 	2.3P 	2.4P 	0.9P 	2k
#       12AT7	60  	1.35	460 	    	300 	300 	2.7P	2.2P	1P  	2k
#		12AU7 	21.5 	1.3 	1180 	    	84  	300 	2.3P 	2.2P 	1.0P 	2k
#		6550 	7.9 	1.35 	890 	4800 	60  	24  	14P 	0.85P 	12P 	1k
#		KT88 	8.8 	1.35 	730 	4200 	32   	16  	14P 	0.85P 	12P 	1k
#       EL34    60.0    4.8     2000            800     50
#       EL34	11  	1.35	650 	4200	60  	24  	15P 	1P  	8P  	1K
#       2A3 	4.2 	1.4 	1500	    	60  	300 	8P  	17P 	6P  	1K
#       300B	3.95	1.4 	1550	    	65   	300 	10P 	16P 	5P  	1K
#       6C33C	3.1 	1.4 	163 	    	15  	300 	31P 	31P 	11P 	500


def Igk_Vgk(Vgk):
    """gate current as function of gate-kathode voltage"""
    return exp(7.75*Vgk-10.3)

def Ipk(Vgk, Vpk):
    """plate current as function of gate-kathode voltage and plate-kathode voltage"""
    mu = 100.0      # Amplification factor.
    kx = 1.4        # Exponent:
    kg1 = 1060.0    # Inversely proportional to overall plate current
    kp = 600.0      # Affects opration in region of large plate voltage and large negative grid voltage.
    kvb = 300.0     # Knee volts. 
    #E1 = Vpk /kp*log(1+exp(kp*(1/mu+ Vgk/Vpk)))
    #return 2*E1**kx/kg1*(E1>0.0)*arctan(Vpk /kvb)
    E1 = Vpk/kp*log(1+exp(kp*(1/mu+Vgk/sqrt(kvb+Vpk*Vpk))))
    return 2*E1**kx/kg1*(E1>0.0)

def Ftube(Vi, Ri, Ipk):
    """calculate output voltage of a tube circuit as function of input voltage
    Vi  array of input voltages
    Ri  value of resistor Ri
    Ipk plate current Ip as function of Vgk and Vpk
    """
    def fi(Vgk, Vi, Ri):
        return Vi - Vgk - Ri * Igk_Vgk(Vgk) # sum of voltages -> zero
    Vgk = newton(fi, 1e-3, args=(Vi, Ri))   # Vgk(Vi)
    def fp(Vpk, Vgk, Ipk):
        return Vpk + 100e3 * Ipk(Vgk, Vpk) - 250 # Vp 250V, Rp 100k

    l = 110.0 # start value for iteration
    return newton(fp, l, args=(Vgk, Ipk))   # Vpk(Vgk)

def calc_ftube(Ri, st, en, cnt):
    """calculate table Vp(Vi)"""
    Vi = linspace(st,en,cnt)
    Vp = zeros_like(Vi)
    for i, v in enumerate(Vi):
        Vp[i] = Ftube(v, Ri, Ipk)
    return Vi, Vp

def write_ftube_table(Ri, Vi, Vp):
    """write C source"""
    sys.stdout.write("\t{ // Ri = %dk\n" % (Ri/1e3))
    sys.stdout.write('\t%g,%g,%g, {' % (Vi[0], Vi[-1], (len(Vi)-1)/(Vi[-1]-Vi[0])))
    s = ""
    for i, v in enumerate(Vi):
        if i % 5 == 0:
            sys.stdout.write(s+"\n\t")
            s = ""
        sys.stdout.write(s+str(Vp[i]))
        s = ","
    sys.stdout.write("\n\t}}")

def write_tables():
    sys.stdout.write("struct table1d tubetable[] = {\n")
    s = ""
    for Ri in 68e3, 250e3:
        sys.stdout.write(s)
        s = ",\n"
        Vi, Vp = calc_ftube(Ri, -5, 5, 2001)
        write_ftube_table(Ri, Vi, Vp)
    sys.stdout.write("\n};\n")

def check_table_accuracy(Ri, st, en, cnt):
    """maximal table error at half interval"""
    Vi, Vp = calc_ftube(Ri, st, en, cnt)
    d = zeros((len(Vp)-1,))
    for i in range(1,len(Vp)):
        vi = (Vi[i-1]+Vi[i])/2
        v = Ftube(vi, Ri, Ipk)
        d[i-1] = (0.5*(Vp[i-1]+Vp[i]) - v)/v
    return max(d)

def display_accuracy():
    for Ri in 250e3, 68e3:
        print "Ri=%dk: %g" % (Ri/1e3, check_table_accuracy(Ri, -5, 5, 2001))
    
def plot_Ftube():
    Vi = linspace(-4,2)
    Vp = zeros_like(Vi)
    for Ri in 250e3, 68e3:
        for i, v in enumerate(Vi):
            Vp[i] = Ftube(v, Ri, Ipk)
        plot(Vi, Vp, label="Ri=%dk" % (Ri/1e3))
    xlabel("Vik")
    ylabel("Vp")
    legend()
    axis
    show()

def main():
    if len(sys.argv) == 2:
        arg = sys.argv[1]
    else:
        arg = ""
    if arg == "plot":
        plot_Ftube()
    elif arg == "accuracy":
        display_accuracy()
    elif arg == "table":
        write_tables()
    else:
        print "usage: %s plot|accuracy|table" % sys.argv[0]

if __name__ == "__main__":
    main()

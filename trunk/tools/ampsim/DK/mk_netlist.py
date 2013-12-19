from __future__ import division
import sys, os, re

def mksym(sym, nm, dev=None):
    if dev is None:
        dev = nm
    if sym.startswith(nm):
        sym = sym[len(nm):]
    try:
        int(sym)
    except ValueError:
        sym = "'%s'" % sym
    return "%s(%s)" % (dev, sym)

R_dict = {
    "k" : "e3",
    "M" : "e6",
    "." : "",
    ""  : "",
    }

C_dict = {
    "n" : "e-9",
    "p" : "e-12",
    "." : "e-6",
    ""  : "",
    }

L_dict = {
    "m" : "e-3",
    "u" : "e-6",
    "H" : "",
    "." : "",
    ""  : "",
    }

def resistor_value(val):
    m = re.match("([0-9]*)([kM.]?)([0-9]*)$", val)
    return m.group(1)+"."+m.group(3)+R_dict[m.group(2)]

mag_dict = {
    "M": "e6",
    "k": "e3",
    "m": "e-3",
    "u": "e-6",
    "n": "e-9",
    "p": "e-12",
    "f": "e-15",
    }

def convert_with_suffix(v):
    try:
        v = v[:-1] + mag_dict[v[-1]]
    except KeyError:
        pass
    return v

def Voltage(v):
    if v.endswith("V"):
        v = v[:-1]
    return convert_with_suffix(v)
    
def Current(v):
    if v.endswith("A"):
        v = v[:-1]
    return convert_with_suffix(v)
    
def Number(v):
    return convert_with_suffix(v)

def Text(v):
    return "'%s'" % v

def Resistance(v):
    return resistor_value(v)

def mk_dict(val, **kw):
    l = []
    for k, v in [v.split("=") for v in val.split(",")]:
        if k not in kw:
            print "warning: unknown parameter %s" % k
            try:
                v = float(v)
            except ValueError:
                pass
        else:
            v = kw[k](v)
        l.append("%s=%s" % (k, v))
    return "dict(%s)" % ", ".join(l)

def read_netlist(fname):
    cmd = "echo '(ampsim \"/dev/fd/3\")' | gnetlist -l ampsim.scm -i %s 3>&1 >/dev/null"
    rows = []
    values = {}
    with os.popen(cmd % fname) as f:
        out = []
        inp = []
        for line in f:
            line = line.split()
            sym = line[0]
            dev = line[1]
            val = line[2]
            conn = []
            for v in line[3:]:
                if v == "GND":
                    pass
                elif v.startswith("unnamed_net"):
                    v = "'p"+v[11:]+"'"
                elif v.startswith("unconnected_"):
                    v = None
                else:
                    try:
                        int(v)
                    except ValueError:
                        v = "'%s'" % v
                conn.append(v)
            if dev == "INPUT":
                inp += conn
                continue
            if dev == "OUTPUT":
                out += conn
                continue
            if dev == "OPAMP":
                conn = conn[:2] + conn[4:]
                sym = mksym(sym, "O", "OPA")
            elif dev == "RESISTOR":
                sym = mksym(sym, "R")
                val = resistor_value(val)
            elif dev == "CAPACITOR":
                sym = mksym(sym, "C")
                m = re.match("([0-9]*)([np.]?)([0-9]*)$", val)
                val = m.group(1)+"."+m.group(3)+C_dict[m.group(2)]
            elif dev == "INDUCTOR":
                sym = mksym(sym, "L")
                m = re.match("([0-9]*)([muH.]?)([0-9]*)H?$", val)
                val = m.group(1)+"."+m.group(3)+L_dict[m.group(2)]
            elif dev == "TRANSFORMER":
                ##FIXME
                sym = mksym(sym, "Trans_L")
                conn = [conn[0], conn[4], conn[4], conn[1], conn[2], conn[3]]
                vl = {}
                d = {}
                for k, v in [v.split("=") for v in val.split(",")]:
                    if k == "R":
                        vl[k] = float(v)
                    elif k.startswith("w"):
                        d[int(k[1:])] = float(v)
                    else:
                        print "warning: unknown parameter %s" % k
                vl["windings"] = [v[1] for v in sorted(d.items())]
                val = repr(vl)
            elif dev == "NPN_TRANSISTOR":
                sym = mksym(sym, "T")
                if "=" in val:
                    val = mk_dict(val,Vt=Voltage,Is=Current,Bf=Number,Br=Number)
                else:
                    val = "Transistors['%s']" % val
            elif dev == "TRIODE":
                sym = mksym(sym, "U", "Triode")
                val = "Tubes['%s']" % val
            elif dev == "PENTODE":
                sym = mksym(sym, "U", "Pentode")
                conn = [conn[0], conn[1], conn[3], conn[4]]
                val = "Tubes['%s']" % val
            elif dev == "VARIABLE_RESISTOR":
                sym = mksym(sym, "P")
                if "=" in val:
                    val = mk_dict(val,value=Resistance,a=Number,inv=Number,var=Text,name=Text)
                else:
                    val = resistor_value(val)
            elif dev == "CONNECTION_CURRENT":
                sym = mksym(sym, "CC")
                val = None
            elif dev == "POWER":
                sym = mksym(sym, "V")
                if val.endswith("V"):
                    val = val[:-1]
                if "." not in val:
                    val += "."
            else:
                assert False, dev
            if val is not None:
                values[sym] = val
            rows.append([sym]+conn)
        rows.append(['OUT']+out)
        rows.append(['IN']+inp)
    return ("S = ((%s),\n     )" % "),\n     (".join([", ".join([v for v in row]) for row in rows]) +
            "\n" +
            "V = {%s}" % "".join(['%s: %s,\n     ' % v for v in sorted(values.items())])
            )
    return rows, values

if __name__ == "__main__":
    print read_netlist(sys.argv[1])

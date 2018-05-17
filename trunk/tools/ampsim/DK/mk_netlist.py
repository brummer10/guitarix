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
    "u" : "e-6",
    "." : "e-6",
    ""  : "e-6",
    }

L_dict = {
    "m" : "e-3",
    "u" : "e-6",
    "H" : "",
    "." : "",
    ""  : "",
    }

def resistor_value(val):
    m = re.match("(?P<l>[0-9]*)(\\.(?P<t>[0-9]*))?(?P<m>[kM])?$", val)
    if not m:
        m = re.match("(?P<l>[0-9]*)(?P<m>[kM.]?)(?P<t>[0-9]*)$", val)
    return m.group('l') + "." + (m.group('t') or '') + R_dict[m.group('m') or '']

def capacitor_value(val):
    m = re.match("(?P<l>[0-9]*)(\\.(?P<t>[0-9]*))?(?P<m>[npu])?F?$", val)
    if not m:
        m = re.match("(?P<l>[0-9]*)(?P<m>[npu.]?)(?P<t>[0-9]*)$", val)
    return m.group('l') + "." + (m.group('t') or '') + C_dict[m.group('m') or '']

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
            print line
            sym = line[0]
            dev = line[1]
            val = line[2]
            conn = []
            for v in line[3:]:
                if v == "GND":
                    pass
                elif v.startswith("unnamed_net"):
                    v = "'u"+v[11:]+"'"
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
            if dev in ("OPAMP"):
                conn = conn[:2] + conn[4:]
                sym = mksym(sym, "U", "OPA")
                if "=" in val:
                    val = mk_dict(val,Vcc=Voltage,Vee=Voltage,A=Current)
                else:
                    val = "Opamps['%s']" % val
            elif dev == "RESISTOR":
                sym = mksym(sym, "R")
                val = resistor_value(val)
            elif dev in ("CAPACITOR", "POLARIZED_CAPACITOR"):
                sym = mksym(sym, "C")
                val = capacitor_value(val)
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
                    elif k == "nw":
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
            elif dev == "PNP_TRANSISTOR":
                ##FIXME
                sym = mksym(sym, "Tp")
                if "=" in val:
                    val = mk_dict(val,Vt=Voltage,Is=Current,Bf=Number,Br=Number)
                else:
                    val = "Transistors['%s']" % val
            elif dev == "DIODE":
                sym = mksym(sym, "D")
                if "=" in val:
                    ##FIXME
                    val = mk_dict(val,Is=Current,mUt=Number)
                    #val = mk_dict(val,Is=Current,Rs=Number,Bv=Number)
                    #Is=Saturation current=mA, RS=Ohmic resistance=Om, BV=Reverse breakdown voltage=V
                else:
                    val = "Diodes['%s']" % val
            elif dev == "DIODE2":
                sym = mksym(sym, "D2")
                if "=" in val:
                    ##FIXME
                    val = mk_dict(val,Is=Current,mUt=Number)
                    #val = mk_dict(val,Is=Current,Rs=Number,Bv=Number)
                    #Is=Saturation current=mA, RS=Ohmic resistance=Om, BV=Reverse breakdown voltage=V
                else:
                    val = "Diodes['%s']" % val
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
            elif dev == "VOLTAGE_SOURCE":
                sym = mksym(sym, "V")
                if val == "DC":
                    val = conn[0][1:-1]
                    conn = conn[1:]
                if val.endswith("V"):
                    val = val[:-1]
                if "." not in val:
                    val += "."
            elif dev == "vsin":
                continue
            else:
                assert False, dev
            if val is not None:
                values[sym] = val
            rows.append([sym]+conn)
        rows.append(['OUT']+out)
        rows.append(['IN']+inp)
    fmt_row = lambda row: " ".join(["None," if v is None else v+"," for v in row])
    nt = ("S = ((%s),\n     )" % "),\n     (".join([fmt_row(row) for row in rows]) +
            "\n" +
            "V = {%s}" % "".join(['%s: %s,\n     ' % v for v in sorted(values.items())])
            )
    print '\n %s \n' % nt
    return nt
    return rows, values

if __name__ == "__main__":
    print read_netlist(sys.argv[1])

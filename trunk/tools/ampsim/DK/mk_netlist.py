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

def resistor_value(val):
    m = re.match("([0-9]*)([kM.]?)([0-9]*)$", val)
    return m.group(1)+"."+m.group(3)+R_dict[m.group(2)]

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
            elif dev == "TRIODE":
                sym = mksym(sym, "U", "Triode")
                val = "Tubes['%s']" % val
            elif dev == "PENTODE":
                sym = mksym(sym, "U", "Pentode")
                val = "Tubes['%s']" % val
            elif dev == "VARIABLE_RESISTOR":
                sym = mksym(sym, "P")
                if "=" in val:
                    val = dict([v.split("=") for v in val.split(",")])
                    val["value"] = resistor_value(val["value"])
                else:
                    val = resistor_value(val)
                if conn[1] is None:
                    conn = [conn[0], conn[2]]
                else:
                    conn = [conn[0], conn[2], conn[1]]
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
                assert False
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

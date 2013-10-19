import sys, os

cmd = "echo '(ampsim \"/dev/fd/3\")' | gnetlist -l ampsim.scm -i %s 3>&1 >/dev/null"
rows = []
values = {}
with os.popen(cmd % sys.argv[1]) as f:
    out = []
    inp = []
    for line in f:
        line = line.split()
        sym = line[0]
        dev = line[1]
        val = line[2]
        conn = [('"%s"' if v != "GND" else '%s') % v for v in line[3:]]
        if dev == "INPUT":
            out += conn
            continue
        if dev == "OUTPUT":
            inp += conn
            continue
        if dev == "OPAMP":
            conn = conn[:2] + conn[4:]
            if sym.startswith("O"):
                sym = sym[1:]
            sym = "OPA(%s)" % sym
        elif dev == "RESISTOR":
            if sym.startswith("R"):
                sym = sym[1:]
            sym = "R(%s)" % sym
        sym = "%s" % sym
        values[sym] = val
        rows.append([sym]+conn)
    rows.append(['OUT']+out)
    rows.append(['IN']+inp)
print "S = ((%s),\n     )" % "),\n     (".join([", ".join([v for v in row]) for row in rows])
print
print "V = {%s}" % "".join(['%s: %s,\n     ' % v for v in sorted(values.items())])

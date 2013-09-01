import sys; sys.path.append("circuit")
import pycircuit
import numpy as np
import subprocess, os

def print_header(o):
    print >>o, '#include "intpp.h"'
    print >>o, "namespace AmpData {"
    b0, b1, a1 = pycircuit.psParams.feedback_coeff(1.0)
    print >>o, "real b0 = %g;" % b0
    print >>o, "real b1 = %g;" % b1
    print >>o, "real a1 = 1 - %g;" % (1 - a1)
    print >>o, "int fs = %d;" % pycircuit.fs
    return 3 * np.float32().nbytes + np.int32().nbytes

def print_footer(o):
    print >>o, "} // namespace AmpData"
    return 0

def calc_table(name):
    f = os.tmpfile()
    p = subprocess.Popen(["python","genonetable.py", name], stdout=f, stderr=subprocess.PIPE)
    return p, f

proclist = (
    ("ps", "phasesplitter"),
    ("ppg","poweramp gate"),
    ("ppp","poweramp plate"),
    ("ct","coupled triodes"),
    )

def main():
    if len(sys.argv) > 1:
        o = open(sys.argv[1], "w")
    else:
        o = sys.stdout
    procs = [(n, d, calc_table(n)) for n, d in proclist]
    sz = print_header(o)
    l = []
    for n, d, (p, f) in procs:
        s = int(p.stderr.read())
        f.seek(0)
        o.write(f.read())
        l.append("%s: %d bytes" % (d, s))
        sz += s
    sz += print_footer(o)
    l.append("data size sum: %d bytes" % sz)
    print >>o, "".join(["\n// " + s for s in l])

if __name__ == "__main__":
    main()

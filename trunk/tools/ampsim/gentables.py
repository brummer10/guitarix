import subprocess, sys, os
basepath = os.path.dirname(sys.argv[0])
sys.path.append(os.path.join(basepath, "circuit"))
import pycircuit
import numpy as np

def print_header_file_start(h):
    print >>h, """\
#ifndef _DATA_H
#define _DATA_H 1

#include "intpp.h"

namespace AmpData {
    extern real b0;
    extern real b1;
    extern real a1;
    extern int fs;

"""

def print_header_file_end(h):
    print >>h, """\
}

#endif /* !_DATA_H */
"""

def print_header_file_entry(h, f):
    print >>h, "namespace %s { extern splinedata sd; }" % f

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
    p = subprocess.Popen(["python",os.path.join(basepath, "genonetable.py"), name], stdout=f, stderr=subprocess.PIPE)
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
        h = open(sys.argv[2], "w")
    else:
        o = sys.stdout
        h = sys.stdout
    procs = [(n, d, calc_table(n)) for n, d in proclist]
    print_header_file_start(h)
    sz = print_header(o)
    l = []
    for n, d, (p, f) in procs:
        s = int(p.stderr.read())
        f.seek(0)
        o.write(f.read())
        l.append("%s: %d bytes" % (d, s))
        sz += s
        print_header_file_entry(h, n)
    sz += print_footer(o)
    l.append("data size sum: %d bytes" % sz)
    print >>o, "".join(["\n// " + s for s in l])
    print_header_file_end(h)

if __name__ == "__main__":
    main()

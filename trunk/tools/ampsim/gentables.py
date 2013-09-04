import sys, os, traceback
basepath = os.path.dirname(sys.argv[0])
sys.path.append(os.path.join(basepath, "circuit"))
sys.path.append(os.path.join(basepath, "tensbs"))
import pycircuit, splinetable, components
import multiprocessing as mp
import numpy as np
from cStringIO import StringIO

def print_intpp_data(p):
    o = StringIO()
    if hasattr(p, "init"):
        p.init()
    print >>o, "namespace %s {" % p.comp_id
    try:
        r = splinetable.print_intpp_data(o, "", "", p.func, p.NVALS, *p.ranges)
    except Exception:
        traceback.print_exc()
        raise
    print >>o, "splinedata sd = {"
    print >>o, "\tx0,"
    print >>o, "\th,"
    print >>o, "\tn,"
    print >>o, "\tt,"
    print >>o, "\tc,"
    print >>o, "\t%d, /* number of calculated values */" % p.NVALS
    print >>o, "\t%d, /* number of input values */" % p.N_IN
    print >>o, "\t%d, /* number of output values */" % p.N_OUT
    n_state = p.NVALS-p.N_OUT
    print >>o, "\t%d, /* number of state values */" % n_state
    s = ",".join([str(row[1]) for row in p.ranges])
    inst = "splinedata::splev%d<%s>" % (p.N_IN + n_state, s)
    print >>o, "\t%s," % inst
    print >>o, '\t"%s",' % p.comp_id
    print >>o, "};"
    print >>o, "}; /* ! namespace %s */" % p.comp_id
    o.seek(0)
    return r, o.read(), inst;

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

components_list = [
    components.psParams,
    components.ppgParams,
    components.pppParams,
    components.ctcParams,
    ]

def main():
    if len(sys.argv) > 1:
        o = open(sys.argv[1], "w")
        inst = open(sys.argv[2], "w")
        h = open(sys.argv[3], "w")
    else:
        o = sys.stdout
        inst = sys.stdout
        h = sys.stdout
    pool = mp.Pool(mp.cpu_count())
    procs = [(c, pool.apply_async(print_intpp_data, [c()])) for c in components_list]
    print_header_file_start(h)
    sz = print_header(o)
    l = []
    templ = set()
    for c, p in procs:
        s, f, i = p.get()
        o.write(f)
        templ.add(i)
        l.append("%s: %d bytes" % (c.comp_name, s))
        sz += s
        print_header_file_entry(h, c.comp_id)
    sz += print_footer(o)
    l.append("data size sum: %d bytes" % sz)
    print >>o, "".join(["\n// " + s for s in l])
    print_header_file_end(h)
    for v in sorted(templ):
        print >>inst, "template int %s(splinedata *p, real xi[2], real *res);" % v

if __name__ == "__main__":
    main()

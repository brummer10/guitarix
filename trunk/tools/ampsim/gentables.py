import sys, os, traceback
import circuit
from tensbs import splinetable
import multiprocessing as mp
import numpy as np
from cStringIO import StringIO

def print_intpp_data(i):
    p = components_list[i]()
    o = StringIO()
    if hasattr(p, "init"):
        p.init()
    print >>o, "namespace %s {" % p.comp_id
    r, order_tab = splinetable.print_intpp_data(o, "", "", p, p.ranges, p.basegrid)
    print >>o, "splinecoeffs sc[%d] = {" % p.NVALS
    f_set = set()
    for j, row in enumerate(order_tab):
        inst = "splinedata::splev<%s>" % ",".join([str(v) for v in row if v is not None])
        f_set.add(inst)
        print >>o, "\t{x0_%d, xe_%d, hi_%d, n_%d, nmap_%d, map_%d, t_%d, c_%d, %s}," % (j, j, j, j, j, j, j, j, inst)
    print >>o, "};"
    print >>o, "splinedata sd = {"
    print >>o, "\tsc,"
    print >>o, "\t%d, /* number of calculated values */" % p.NVALS
    print >>o, "\t%d, /* number of input values */" % p.N_IN
    print >>o, "\t%d, /* number of output values */" % (p.NVALS-(p.NDIM-p.N_IN))
    print >>o, "\t%d, /* number of state values */" % (p.NDIM-p.N_IN)
    print >>o, '\t"%s",' % p.comp_id
    print >>o, "};"
    print >>o, "}; /* ! namespace %s */" % p.comp_id
    o.seek(0)
    return r, o.read(), f_set, p.comp_name, p.comp_id;

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
    if 0:
        b0, b1, a1 = circuit.PhaseSplitter().feedback_coeff(1.0)
        print >>o, "real b0 = %g;" % b0
        print >>o, "real b1 = %g;" % b1
        print >>o, "real a1 = 1 - %g;" % (1 - a1)
    print >>o, "int fs = %d;" % circuit.FS
    return 3 * np.float32().nbytes + np.int32().nbytes

def print_footer(o):
    print >>o, "} // namespace AmpData"
    return 0

components_list = [
    circuit.PhaseSplitter_JCM800,
    circuit.PPGate_JCM800,
    circuit.PPPlate_JCM800,
    circuit.CoupledTriode,
    ]

def write_files(o, inst, h):
    if True: # set to False for sequential computation in the current process
        pool = mp.Pool(mp.cpu_count()+1)
        procs = [pool.apply_async(print_intpp_data, [i]) for i in range(len(components_list))]
    else:
        procs = [print_intpp_data(i) for i in range(len(components_list))]
    print_header_file_start(h)
    sz = print_header(o)
    l = []
    templ = set()
    for p in procs:
        if hasattr(p, "get"):
            p = p.get()
        s, f, i, comp_name, comp_id = p
        o.write(f)
        templ |= i
        l.append("%s: %d bytes" % (comp_name, s))
        sz += s
        print_header_file_entry(h, comp_id)
    sz += print_footer(o)
    l.append("data size sum: %d bytes" % sz)
    print >>o, "".join(["\n// " + s for s in l])
    print_header_file_end(h)
    for v in sorted(templ):
        print >>inst, "template int %s(splinecoeffs *p, real xi[2], real *res);" % v

def main():
    if len(sys.argv) > 1:
        o = open(sys.argv[1], "w")
        inst = open(sys.argv[2], "w")
        h = open(sys.argv[3], "w")
        files = sys.argv[1:4]
    else:
        o = sys.stdout
        inst = sys.stdout
        h = sys.stdout
        files = []
    try:
        write_files(o, inst, h)
    except Exception:
        traceback.print_exc()
        for f in files:
            try:
                os.remove(f)
            except:
                pass
        raise SystemExit(1)

if __name__ == "__main__":
    main()

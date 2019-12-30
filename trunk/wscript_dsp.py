"""
support for generating .cc files from faust .dsp files with dsp2cc

for examples look at src/faust/wscript
"""

from waflib import Task, TaskGen, Logs, Utils
import os, re, shutil

# task function for task "dsp"
def dsp2cc(task):
    # use the specified processor to create the output file and copy
    # the output file into faust-generated in the source tree
    src = task.inputs[0].bldpath()
    o = task.outputs[0]
    dst = o.abspath()
    p = o.parent
    gendir = p.parent.get_src().find_dir(p.name+task.gen_dir_suffix)
    cpy = gendir.make_node(o.name).abspath()
    lst = [task.proc.abspath(), "-o", dst]
    if len(task.outputs) == 2:
        o_h = task.outputs[1]
        dst_h = o_h.abspath()
        cpy_h = gendir.make_node(o_h.name).abspath()
        lst += ["-H", dst_h]
    else:
        cpy_h = None
    lst += task.proc_args + [src]
    Logs.debug("runner: system command -> %s" % " ".join(lst))
    ret = task.exec_command(lst,shell=False)
    if ret != 0:
        return ret
    try:
        shutil.copy2(dst, cpy)
        if cpy_h:
            shutil.copy2(dst_h, cpy_h)
    except (OSError, IOError) as e:
        Logs.error("runner: cannot copy file -> %s" % e)
        return e.errno
    return 0

class FaustScanner(object):

    scan_re = "|".join([
        r'\bimport\s*\(\s*"(?P<I>[^"]+)"\s*\)\s*;',
        r'\bcomponent\s*\(\s*"(?P<C>[^"]+)"\s*\)',
        ])

    def scan_file(self, task, node):
        for s in "_ui.cc", "_ui.glade":
            n = node.parent.find_resource(node.name.replace(".dsp",s))
            if n:
                self.deps.append(n)
        pname = node.parent.abspath()
        for m in re.finditer(self.scan_re, node.read()):
            for fname in m.groupdict().values():
                if not fname:
                    continue
                key = (pname, fname)
                if key in self.scanned:
                    continue
                self.scanned.add(key)
                n = node.parent.find_resource(fname)
                if n:
                    self.deps.append(n)
                    self.scan_file(task, n)

    def scan(self, task):
        self.deps = []
        self.scanned = set()
        for node in task.inputs:
            self.scan_file(task, node)
        return self.deps, []

dsp_scanner = FaustScanner()

def scan_dsp(task):
    return dsp_scanner.scan(task)

# definition of task "dsp"
Task.task_factory(
    name    = 'dsp',
    func    = dsp2cc,
    color   = 'BLUE',
    ext_in  = '.dsp',
    ext_out = '.cc',
    before  = 'cxx',
    ).scan = scan_dsp

@TaskGen.extension('.dsp')
def dsp_file(self, node):
    tsk = self.create_task('dsp')
    tsk.proc = self.bld.bldnode.find_node(self.proc)
    tsk.proc_args = getattr(self, "proc_args", [])
    tsk.gen_dir_suffix = getattr(self, "gen_dir_suffix", "-generated")
    tsk.set_inputs(node)
    tsk.dep_vars = ['DSP2CC_ARGS']
    tsk.env['DSP2CC_ARGS'] = tsk.proc_args
    parent = node.parent
    o = node.change_ext('.cc')
    tsk.set_outputs(o)
    if getattr(self, "separate_header", False):
        o = node.change_ext('.h')
        tsk.set_outputs(o)
    self.bld.add_manual_dependency(node, tsk.proc)

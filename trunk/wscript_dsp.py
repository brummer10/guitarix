"""
support for generating .cc files from faust .dsp files with dsp2cc

for examples look at src/faust/wscript
"""

import Task, TaskGen, Logs, Utils, os, re, shutil

# task function for task "dsp"
def dsp2cc(task):
    # use the specified processor to create the output file and copy
    # the output file into faust-generated in the source tree
    src = task.inputs[0].srcpath(task.env)
    o = task.outputs[0]
    dst = o.bldpath(task.env)
    
    cpy = os.path.join(o.parent.srcpath(task.env)+task.gen_dir_suffix,o.file())
    lst = [task.proc,"-o",dst] + task.proc_args + [src]
    Logs.debug("runner: system command -> %s" % " ".join(lst))
    ret = Utils.exec_command(lst,shell=False)
    if ret != 0:
        return ret
    try:
        shutil.copy2(dst, cpy)
    except (OSError, IOError), e:
        Logs.error("runner: cannot copy file -> %s" % e)
        return e.errno
    return 0

class FaustScanner(object):

    scan_re = "|".join([
        r'\bimport\s*\(\s*"(?P<I>[^"]+)"\s*\)\s*;',
        r'\bcomponent\s*\(\s*"(?P<C>[^"]+)"\s*\)',
        ])

    def scan_file(self, task, node):
        n = node.parent.find_resource(node.name.replace(".dsp","_ui.cc"))
        if n:
            self.deps.append(n)
        pname = node.parent.abspath(task.env)
        for m in re.finditer(self.scan_re, node.read(task.env)):
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
Task.task_type_from_func(
    name    = 'dsp',
    func    = dsp2cc,
    color   = 'BLUE',
    ext_in  = '.dsp',
    ext_out = '.cc',
    before  = 'cc cxx',
    ).scan = scan_dsp

@TaskGen.extension('.dsp')
def dsp_file(self, node):
    tsk = self.create_task('dsp')
    tsk.proc = self.proc
    tsk.proc_args = getattr(self, "proc_args", [])
    tsk.gen_dir_suffix = getattr(self, "gen_dir_suffix", "-generated")
    tsk.set_inputs(node)
    tsk.dep_vars = ['DSP2CC_ARGS']
    tsk.env['DSP2CC_ARGS'] = tsk.proc_args
    parent = node.parent
    o = node.change_ext('.cc')
    tsk.set_outputs(o)
    self.bld.add_manual_dependency(node,self.bld.bldnode.find_resource(self.proc))

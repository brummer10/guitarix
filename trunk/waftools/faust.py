import re, shutil
from waflib import Task, Configure, Logs, Options, Context
from waflib.TaskGen import extension

good_faust_versions = Context.g_module.good_faust_versions

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

@extension('.dsp')
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

@Configure.conf
def get_faust_args(bld):
    float_arg = ["-s","40000","--float"]
    double_arg = ["--double"]
    if bld.env['FAUST_DOUBLE']:
        arg = ["--double"]
    else:
        arg = ["--float"]
    if bld.env['FAUST_VECTORIZE']:
        float_arg.append('--vectorize')
        arg.append('--vectorize')
        double_arg.append('--vectorize')
    elif bld.env['FAUST_VECTORIZE_FLOAT']:
        float_arg.append('--vectorize')
        if not bld.env['FAUST_DOUBLE']:
            arg.append('--vectorize')
    add_args = bld.env['FAUST_OPTIONS']
    if add_args:
        add_args = "--add=%s" % add_args
        float_arg.append(add_args)
        double_arg.append(add_args)
        arg.append(add_args)
    return arg, float_arg, double_arg

def options(opt):
    faust = opt.add_option_group("Faust-Compiler")

    if len(good_faust_versions) == 1:
        faust_vers_str = good_faust_versions[0]
    else:
        faust_vers_str = "in [%s]" % ", ".join(good_faust_versions)

    faust.add_option(
        '--faust',
        action='store_const',
        default=False,
        const=True,
        help=('use faust even if the installed version is not %s'
              % faust_vers_str))

    faust.add_option(
        '--no-faust',
        action='store_const',
        default=False,
        const=True,
        help="don't use faust, use the pre-built files in faust-generated")

    o = []
    o.append(faust.add_option(
        '--faust-float',
        action='store_const',
        default=False,
        const=True,
        help="build with faust, single precision"))

    o.append(faust.add_option(
        '--faust-vectorize',
        action='store_const',
        default=False,
        const=True,
        help="call faust with --vectorize"))

    o.append(faust.add_option(
        '--faust-vectorize-float',
        action='store_const',
        default=False,
        const=True,
        help=("call faust with --vectorize for sources built"
              "in single (float) precision")))

    o.append(faust.add_option('--faust-options', help="additional faust options"))
    Context.g_module.faust_params = [(v.dest, v.get_opt_string()) for v in o]

def check_faust(conf):
    opt = conf.options
    env = conf.env
    if opt.no_faust:
        env.FAUST = None
        return
    conf.find_program("faust", var='FAUST')
    if not env.FAUST:
        return
    try:
        s = conf.cmd_and_log(env['FAUST']+['--version'], quiet=True)
    except ValueError:
        Logs.warn('could not execute faust')
        return
    m = re.match(r".*Version\s*(.*)", s)
    if not m:
        Logs.warn('could not determine faust version')
    vers = m.group(1)
    env.FAUST_VERSION = vers
    if vers not in good_faust_versions and not opt.faust:
        env.FAUST = None
        conf.msg(msg='Checking for faust version',result="can't use %s (check ./waf --help)" % vers,color='YELLOW')
    else:
        conf.msg('Checking for faust version','ok ({})'.format(vers))
    env.FAUST_DOUBLE = not opt.faust_float
    env.FAUST_VECTORIZE = opt.faust_vectorize
    env.FAUST_VECTORIZE_FLOAT = opt.faust_vectorize_float
    env.FAUST_OPTIONS = opt.faust_options

def validate_config(conf):
    opt = conf.options
    if conf.env.FAUST:
        if opt.faust_vectorize and opt.faust_vectorize_float:
            raise conf.errors.WafError("conflicting options --faust-vectorize and --faust-vectorize-float")
        return
    for v, o in Context.g_module.faust_params:
        if getattr(opt, v):
            raise conf.errors.WafError("can't use %s without faust" % o)

def configure(conf):
    check_faust(conf)
    validate_config(conf)

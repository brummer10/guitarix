from waflib import Task, Utils
from waflib.TaskGen import extension

@extension('.scss')
def scss_file(self, node):
    tsk = self.create_task('scss')
    tsk.set_inputs(node)
    o = node.change_ext('.css')
    tsk.set_outputs(o)
    if getattr(self, 'install_path', None):
        self.install_task = self.add_install_files(
            install_to=self.install_path, install_from=tsk.outputs,
            chmod=getattr(self,'chmod',Utils.O644))

def scss2css(task):
    src = task.inputs[0].bldpath()
    o = task.outputs[0]
    dst = o.abspath()
    p = o.parent
    #gendir = p.parent.get_src().find_dir(p.name+task.gen_dir_suffix)
    #cpy = gendir.make_node(o.name).abspath()
    task.proc_args = []
    lst = task.env['SASSC'] + task.proc_args + [src, dst]
    ret = task.exec_command(lst, shell=False)
    return ret
    if ret != 0:
        return ret
    try:
        shutil.copy2(dst, cpy)
    except (OSError, IOError) as e:
        Logs.error("runner: cannot copy file -> %s" % e)
        return e.errno
    return 0

def scan_scss(task):
    return [], []

Task.task_factory(
    name    = 'scss',
    func    = scss2css,
    color   = 'BLUE',
    ext_in  = '.scss',
    ext_out = '.css',
    ).scan = scan_scss

def configure(conf):
    conf.find_program("sassc", var='SASSC', mandatory=True)

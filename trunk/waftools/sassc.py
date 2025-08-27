from waflib import Task, Utils
from waflib.TaskGen import extension, feature
import os, re

def scan_scss(fname):
    defn = re.compile(' *\\* *([-a-zA-Z0-9_]+) *: *([-a-zA-Z0-9_.]+)').match
    with open(fname) as fd:
        for line in fd:
            if line.strip() == '/* ICON THEME':
                break
        else:
            raise ValueError("icon table start not found: '/* ICON THEME'")
        for line in fd:
            m = defn(line)
            if not m:
                if line.strip() == ('* ICON THEME'):
                    break
                continue
            yield m.group(1, 2)
        else:
            raise ValueError("icon table end not found: ' * ICON THEME'")

def link_icon(self):
    dst = self.link_dest
    lpath = self.outputs[0].abspath()
    if os.path.islink(lpath):
        if os.readlink(lpath) == dst:
            return
        os.remove(lpath)
    elif os.path.exists(lpath):
        os.remove(lpath)
    os.symlink(dst, lpath)

Task.task_factory(
    name    = 'link-icon',
    func    = link_icon,
    )

@feature('generate_symlink_icons')
def add_install_icons(self):
    pass

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
    if 'generate_symlink_icons' not in self.features:
        return
    theme = re.match('gx_head_([^.]*).scss', node.name).group(1)
    dest = o.parent.find_or_declare(theme)
    for src, dst in scan_scss(node.abspath()):
        src += os.path.splitext(dst)[1]
        lpath = dest.find_or_declare(src)
        lnk_tgt = os.path.join('..', dst)
        lnk = self.create_task('link-icon', link_dest = lnk_tgt, keyword = lambda: 'Symlinking')
        lnk.set_inputs(o.parent.find_resource(dst))
        lnk.set_outputs(lpath)
        if getattr(self, 'install_path', None):
            to = os.path.join(self.install_path, theme, src)
            self.add_symlink_as(install_to=to, install_from=lnk_tgt)

def scss2css(task):
    src = task.inputs[0].bldpath()
    o = task.outputs[0]
    dst = o.abspath()
    p = o.parent
    #gendir = p.parent.get_src().find_dir(p.name+task.gen_dir_suffix)
    #cpy = gendir.make_node(o.name).abspath()
    proc_args = Utils.to_list(getattr(task.generator, 'proc_args', ''))
    lst = task.env['SASSC'] + proc_args + [src, dst]
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

def scan_scss_imports(task):
    is_import = re.compile(r"\s*@import\s+([^;]+?)\s*;").match
    found = []
    not_found = []
    def get_fname(p, v):
        v = v.strip(" '")
        for suffix in '', '.scss', '.css':
            for prefix in '', '_':
                f = prefix + v + suffix
                f = p.find_resource(f)
                if f:
                    found.append(f)
                    return
        not_found.append(v)
    for f in task.inputs:
        p = f.parent
        with open(f.abspath()) as fd:
            for line in fd:
                m = is_import(line)
                if m:
                    for v in m.group(1).split(','):
                        get_fname(p, v)
    return found, not_found

Task.task_factory(
    name    = 'scss',
    func    = scss2css,
    color   = 'BLUE',
    ext_in  = '.scss',
    ext_out = '.css',
    ).scan = scan_scss_imports

def configure(conf):
    conf.find_program("sassc", var='SASSC', mandatory=True)

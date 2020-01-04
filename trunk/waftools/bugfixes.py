import re, os
from waflib.TaskGen import after_method, feature

# fix bug in intltool (waf 2.0.19): add missing dependencies
@feature('intltool_in')
@after_method('apply_intltool_in_f')
def fix_intltool_in(self):
    for task in self.tasks:
        podir=getattr(self,'podir','.')
        linguas=self.path.find_node(os.path.join(podir,'LINGUAS'))
        if linguas:
            with open(linguas.abspath())as f:
                langs=[]
                for line in f.readlines():
                    if not line.startswith('#'):
                        langs+=line.split()
        re_linguas=re.compile('[-a-zA-Z_@.]+')
        for lang in langs:
            if re_linguas.match(lang):
                node=self.path.find_resource(os.path.join(podir,re_linguas.match(lang).group()+'.po'))
                task.dep_nodes.append(node)

def configure(conf):
    pass

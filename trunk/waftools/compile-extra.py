from waflib.TaskGen import feature, before_method, after_method

@feature('cxx','c')
@before_method('apply_link')
def add_ldscript(self):
    if not hasattr(self, 'ldflags'):
        self.ldflags = []
    if hasattr(self, 'ldscript'):
        ldscript = self.ldscript
        if isinstance(ldscript, str):
            ldscript = self.path.find_resource(self.ldscript)
            self.ldscript = ldscript
        self.ldflags.append('-Wl,%s' % ldscript.bldpath())

@feature('cxx','c')
@before_method('apply_link')
def add_mapfile(self):
    if hasattr(self, 'mapfile'):
        mapfile = self.path.find_or_declare(self.mapfile)
        self.ldflags.append('-Wl,-Map=%s' % mapfile.bldpath())

@feature('cxx','c')
@after_method('apply_link')
def add_ldscript_dep(self):
    if hasattr(self, 'ldscript'):
        self.link_task.dep_nodes.append(self.ldscript)


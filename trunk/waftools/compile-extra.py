import sys
from waflib.TaskGen import feature, before_method

@feature('cxx','c')
@before_method('apply_link')
def add_mapfile(self):
    if not hasattr(self, 'ldflags'):
        self.ldflags = []
    if hasattr(self, 'mapfile'):
        mapfile = self.path.find_or_declare(self.mapfile)
        self.ldflags.append('-fno-lto')
        if sys.platform == 'darwin':
            self.ldflags.append('-Wl,-map,%s' % mapfile.bldpath())
        else:
            self.ldflags.append('-Wl,-Map=%s' % mapfile.bldpath())

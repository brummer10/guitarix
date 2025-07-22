from waflib import Task, Configure
from waflib.TaskGen import feature, before_method, after_method
import sys
class strip(Task.Task):
    run_str = '${STRIP} ${SRC}'
    color   = 'BLUE'

    def runnable_status(self):
        if self in self.run_after:
            self.run_after.remove(self)
        ret = super(strip, self).runnable_status()
        if ret == Task.ASK_LATER:
            return ret

        if self.generator.link_task.hasrun == Task.SUCCESS:
            return Task.RUN_ME
        return Task.SKIP_ME

@feature('strip -x')
@after_method('apply_link')
def add_strip_task(self):
    try:
        link_task = self.link_task
    except:
        return
    tsk = self.create_task('strip', self.link_task.outputs[0])

def configure(conf):
    conf.find_program('strip')
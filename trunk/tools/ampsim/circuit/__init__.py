import numpy as np
from components import *

class Func(object):

    @property
    def captured(self):
        return self.captbuf[:,:self.captlen]

    def __init__(self, circ, capt=None):
        self.circ = circ()
        self.circ.init()
        self.state = self.circ.operating_point
        self.var_names = self.circ.var_names
        self.idx = None
        if isinstance(capt, basestring):
            capt = [capt]
        self.capt = capt
        if capt:
            try:
                self.idx = [self.var_names.index(v) for v in capt]
            except ValueError as e:
                raise ValueError("%s: %s: %s" % (self.circ.comp_id, e, ", ".join(self.var_names)))
            self.circ.capt_flag = True
            self.captbuf = np.zeros((len(self.idx),0))
            self.captlen = 0
        self.r = np.zeros(self.circ.NVALS-self.circ.NDIM+self.circ.N_IN)

    def __call__(self, x):
        try:
            len(x)
        except TypeError:
            x = [x]
        self.r[:] = self.circ.func(x, self.state)
        if self.idx:
            if self.captlen == self.captbuf.shape[1]:
                self.captbuf = np.append(self.captbuf, np.zeros((len(self.idx),1000)), axis=1)
            self.captbuf[:,self.captlen] = self.circ.captured[self.idx]
            self.captlen += 1
        return self.r

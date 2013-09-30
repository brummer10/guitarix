import numpy as np
from components import *

class Func(object):

    def __init__(self, circ):
        self.circ = circ()
        self.circ.init()
        self.var_names = self.circ.var_names

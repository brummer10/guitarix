import sympy as sp
import numpy as np

class VariableAccess(object):

    def __init__(self, name, param, pointer):
        if isinstance(name, MatrixDefinition):
            self.name = name.name
            self.pointer = name.pointer
        else:
            assert isinstance(name, basestring)
            self.name = name
            if pointer is None:
                self.pointer = param
            else:
                self.pointer = pointer
        self.param = param

    @staticmethod
    def _len(s):
        if isinstance(s, slice):
            return s.stop - s.start
        return s[1] - s[0]

    @staticmethod
    def _start(s):
        if isinstance(s, slice):
            return s.start
        return s[0]

    def address_of(self):
        if self.param:
            if self.pointer:
                return "par.%s" % self.name
            else:
                return "&par.%s" % self.name
        else:
            if self.pointer:
                return self.name
            else:
                return "&%s" % self.name

    def __str__(self):
        if self.param:
            if self.pointer:
                return "(*par.%s)" % self.name
            else:
                return "par.%s" % self.name
        else:
            if self.pointer:
                return "*%s" % self.name
            else:
                return self.name


class VectorAccess(VariableAccess):

    def __init__(self, name, block=None, param=False, pointer=None):
        VariableAccess.__init__(self, name, param, pointer)
        self.block = block

    @staticmethod
    def block_expr(start, ln):
        if start == 0:
            return ".head<%d>()" % ln
        else:
            return ".segment<%d>(%d)" % (ln, start)

    def __str__(self):
        s = VariableAccess.__str__(self)
        if self.block:
            s += self.block_expr(self._start(self.block), self._len(self.block))
        return s


class MatrixAccess(VariableAccess):

    def __init__(self, name, block=None, param=False, pointer=None):
        VariableAccess.__init__(self, name, param, pointer)
        self.block = block

    def __str__(self):
        s = VariableAccess.__str__(self)
        if self.block:
            r = self.block[0]
            c = self.block[1]
            s += ".block<%d,%d>(%d,%d)" % (self._len(r), self._len(c), self._start(r), self._start(c))
        return s


class MatrixDeclaration(object):

    def __init__(self, name, rows, cols=1, mapping=False, pointer=False, aligned=True, array=False):
        self.name = name
        self.rows = rows
        self.cols = cols
        self.mapping = mapping
        self.pointer = pointer
        self.aligned = aligned
        self.array = array

    def generate(self, postfix=""):
        n = self.name
        if postfix:
            n += postfix
        if self.pointer:
            n = "*" + n
        m = "Matrix"
        if self.array:
            m = "Array"
        attr = " "
        if self.mapping:
            if self.aligned:
                attr = ", Aligned"
            return "Map<%s<creal, %d, %d>%s>%s" % (m, self.rows, self.cols, attr, n)
        else:
            return "%s<creal, %d, %d> %s" % (m, self.rows, self.cols, n)

    def generate_lines(self, indent=""):
        return "%s%s;\n" % (indent, self.generate())

    def __str__(self):
        return self.generate()


class MatrixDefinition(object):

    templ_def = "%(prefix)s%(tp)s<creal, %(rows)d, %(cols)d> %(definition)s;\n"

    templ_data = "%(indent)sstatic const creal __attribute__((aligned(16))) %(data_name)s[%(rows)d*%(cols)d] = { %(data)s };\n"

    templ_init = "%(prefix)s%(const)sMap<%(const)s%(tp)s<creal, %(rows)d, %(cols)d>%(attr)s> %(definition)s;\n"

    def __init__(self, name, value=None, rows=None, cols=None, pointer=False, aligned=True, const=None, array=False):
        if isinstance(name, VariableAccess):
            name = name.name
        try:
            s = value.shape
            if len(s) == 1:
                s = (s[0], 1)
            if rows is not None or cols is not None:
                if s != (rows, cols):
                    raise ValueError("inconsistent shape for matrix %s: %s != %s" % (name, s, (rows, cols)))
            rows, cols = s
            if not isinstance(value, sp.Matrix):
                value = sp.Matrix(value)
            self.value_is_matrix = True
        except AttributeError:
            self.value_is_matrix = False
        if rows is None or cols is None:
            raise ValueError("rows and cols must be set or matrix value supplied")
        self.name = name
        self.value = value
        self.rows = rows
        self.cols = cols
        self.pointer = pointer
        self.aligned = aligned
        self.const = const
        self.array = array

    def generate(self, indent=""):
        l = []
        n = self.name
        tp = "Matrix"
        if self.array:
            tp = "Array"
        if self.pointer:
            n = "*" + n
        if self.value is not None:
            const = ""
            if self.value_is_matrix:
                aligned = True
                if self.const is None or self.const:
                    const = "const "
                static = "static "
                data_name = self.name.lower() + "_data"
                l.append(self.templ_data % dict(
                    indent = indent,
                    data_name = data_name,
                    tp = tp,
                    rows = self.rows,
                    cols = self.cols,
                    data = ",".join([sp.ccode(c) for c in self.value.T]), # col-major order is eigen3 default
                    ))
            else:
                aligned = self.aligned
                if self.const:
                    const = "const "
                static = ""
                data_name = self.value
            attr = " "
            if self.aligned:
                attr = ", Aligned"
            l.append(self.templ_init % dict(
                prefix = "%s%s" % (indent, static),
                tp = tp,
                rows = self.rows,
                cols = self.cols,
                attr = attr,
                const = const,
                definition = "%s(%s)" % (n, data_name),
                ))
        else:
            l.append(self.templ_def % dict(
                prefix = indent,
                tp = tp,
                rows = self.rows,
                cols = self.cols,
                definition = n,
                ))
        return "".join(l)

    generate_lines = generate

    def __str__(self):
        return self.generate()


class Namespace(object):

    def __init__(self, indent=""):
        self.indent = indent
        self.ns = {}
        self.generated = set()

    def add(self, m):
        if m.name in self.ns:
            mm = self.ns[m.name]
            if m.rows != mm.rows or m.cols != mm.cols:
                raise ValueError("inkonsistent definition of %s" % m)
            return
        self.ns[m.name] = m

    def generate_lines(self):
        l = []
        for n, m in sorted(self.ns.items()):
            if m in self.generated:
                continue
            l.append(m.generate_lines(self.indent))
            self.generated.add(m)
        return l

    def __str__(self):
        return "".join(self.generate_lines())


def expr_list_to_ccode(ret, ex, idx='[%d]', off=0):
    """
    ret: name of variable
    ex: vector expression (iterable)
    idx: syntax for index access
    """
    ret += idx
    l = []
    for i, ee in enumerate(ex):
        l += [v+"\n" for v in sp.ccode(ee, ret % (i+off)).split("\n")]
    return l

def make_symbol_vector(s, n, idx="[%d]"):
    return sp.symbols(['%s%s' % (s, idx % i) for i in range(n)])

def matrix_is_zero(m):
    return np.allclose(m, np.zeros_like(m))

def matrix_is_identity(m):
    if m.shape[0] != m.shape[1]:
        return False
    return np.allclose(m, np.identity(m.shape[0]))

def join_with_indent(lines, indent="    "):
    return "".join([l+indent for l in lines])

def gen_linear_combination(ns, resname, varname, mult, mult_data, add=None, add_data=None, cast=None):
    if not isinstance(resname, VectorAccess):
        resname = VectorAccess(resname)
    if not isinstance(varname, VectorAccess):
        varname = VectorAccess(varname)
    if not isinstance(mult, MatrixAccess):
        mult = MatrixAccess(mult)
    if not isinstance(add, (VectorAccess,type(None))):
        add = VectorAccess(add)
    if mult_data.shape[0] == 0:
        if add is None or add_data.shape[0] == 0:
            return ""
        else:
            ns.add(MatrixDefinition(add, add_data))
            e = "%s" % add
    else:
        if not matrix_is_identity(mult_data):
            ns.add(MatrixDefinition(mult, mult_data))
            e = "%s * %s" % (mult, varname)
        else:
            e = "%s" % varname
        if add is not None and not matrix_is_zero(add_data):
            ns.add(MatrixDefinition(add, add_data))
            e += " + %s" % add
    if cast is not None:
        e = "(%s).cast<%s>()" % (e, cast)
    return "%s = %s;" % (resname, e)

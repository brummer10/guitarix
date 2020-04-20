from cython.operator cimport dereference as deref, preincrement as inc
import numpy as np
cimport numpy as np
from libcpp cimport bool

cdef extern from "dlfcn.h":
    cdef enum:
        RTLD_LOCAL
        RTLD_GLOBAL
        RTLD_NOW
    void *dlopen(char *__file, int __mode)
    void *dlsym (void *__handle, char *__name)
    char *dlerror()
    void dlclose(void *)

cdef extern from "time.h":
    cdef struct timespec:
        int tv_sec
        int tv_nsec
    ctypedef int clockid_t
    int CLOCK_MONOTONIC
    int clock_gettime(clockid_t clk_id, timespec *tp)

DEF UseDouble = False

IF UseDouble:
    ctypedef double realt
    np_realt = np.float64
ELSE:
    ctypedef float realt
    np_realt = np.float32

ctypedef realt *realtp

cdef extern from "gx_plugin.h":
    cdef struct value_pair:
        char *value_id
        char *value_label
    ctypedef value_pair* const_value_pair_ptr "const value_pair*"
    cppclass Var:
        char *id
        char *name
        realt *var
        int   *ivar
        bool  *bvar
        realt val
        realt low
        realt up
        value_pair *values
    cppclass string:
        char *c_str()
    cppclass pair:
        string first
        Var *second
    cppclass variter:
        variter operator++()
        bint operator!=(variter)
        bint operator==(variter)
        pair operator*()
    cppclass PluginDef
    cppclass VarMap:
        variter begin()
        variter end()
        variter find(char *pname)
    cppclass ParamRegImpl:
        PluginDef *plugin
        ParamRegImpl(VarMap *v, PluginDef *p)
    ctypedef int (*registerfunc)(ParamRegImpl& reg)
    ctypedef void (*process_mono_audio) (int count, realt *input, realt *output, PluginDef *plugin)
    ctypedef void (*inifunc)(unsigned int samplingFreq, PluginDef *plugin)
    ctypedef int (*activatefunc)(int start, PluginDef *plugin)
    ctypedef void (*clearstatefunc)(PluginDef *plugin)
    ctypedef void (*deletefunc)(PluginDef *plugin)
    ctypedef void (*process_stereo_audio)(int count, realt *input1, realt *input2,
                                           realt *output1, realt *output2, PluginDef *plugin)
    cppclass PluginDef:
        int version
        int flags
        char* id
        char* name
        char** groups
        char* decription
        char* category
        char* shortname
        registerfunc register_params
        process_mono_audio mono_audio
        process_stereo_audio stereo_audio
        inifunc set_samplerate
        activatefunc activate_plugin
        clearstatefunc clear_state
        deletefunc delete_instance
    ctypedef int (*plugin_inifunc)(unsigned int idx, PluginDef **p)

cdef extern from "pluginloader.h":
    int compare_plugin_version(PluginDef *p)

cdef inline double ts_diff(timespec ts1, timespec ts2):
    cdef double df = ts1.tv_sec - ts2.tv_sec
    return df * 1e9 + (ts1.tv_nsec - ts2.tv_nsec)

cdef class Plugin:
    cdef void *handle
    cdef PluginDef *p
    cdef VarMap *varmap
    cdef dict d
    cdef double time_per_sample
    cdef int _samplerate

    def __cinit__(self, path, unsigned int idx = 0):
        cdef int n
        self.varmap = new VarMap()
        self.p = <PluginDef*>0
        if "/" not in path:
            path = "./" + path # do not search system dirs
        self.handle = dlopen(path.encode(), RTLD_LOCAL|RTLD_NOW)
        if not self.handle:
            raise RuntimeError("Cannot open library: %s [%s]" % (path, dlerror()))
        cdef plugin_inifunc get_gx_plugin = <plugin_inifunc>dlsym(self.handle, "get_gx_plugin")
        cdef char *dlsym_error = dlerror()
        if dlsym_error:
            dlclose(self.handle)
            self.handle = <void*>0
            raise RuntimeError("Cannot load symbol 'get_gx_plugin': %s" % dlsym_error)
        n = get_gx_plugin(0, <PluginDef**>0)
        if n < 0:
            raise RuntimeError("error loading plugins")
        if n == 0:
            raise RuntimeError("no plugin found")
        if idx >= <unsigned int>n:
            raise RuntimeError("idx too big (%d > %d)" % (idx, n-1))
        if get_gx_plugin(idx, &self.p) < 0:
            raise RuntimeError("plugin loader error")
        if not compare_plugin_version(self.p):
            raise ValueError("bad plugin version 0x%x" % self.p[0].version)
        cdef ParamRegImpl *pr
        cdef variter i
        d = {}
        cdef object p_id, p_name
        if self.p[0].register_params:
            pr = new ParamRegImpl(self.varmap, &self.p[0])
            self.p[0].register_params(pr[0])
            del pr
            i = self.varmap[0].begin()
            while i != self.varmap[0].end():
                p_id = deref(i).second[0].id
                p_name = deref(i).second[0].name
                d[p_id.decode()] = (
                    p_name.decode(), deref(i).second[0].val,
                    deref(i).second[0].low, deref(i).second[0].up,
                    self.get_vp_list(deref(i).second))
                inc(i)
        self.d = d
        self.time_per_sample = 0
        self._samplerate = 0

    property nanosec_per_sample:
        "time in nanoseconds measured for last compute call"
        def __get__(self):
            return self.time_per_sample

    def keys(self):
        "List of parameters names"
        return self.d.keys()

    def get_var_attr(self, key):
        """argument: parameter name
        returns: name, stdval, lower, upper"""
        return self.d[key]

    cdef get_vp_list(self, Var *p):
        # typecast needed because assignment uses variable without const internally (bug?)
        cdef const_value_pair_ptr vp = <value_pair*>p.values
        if not vp:
            return []
        l = []
        for i in range(int(p.up)+1):
            l.append((vp[i].value_id, vp[i].value_label))
        return l

    def get_range(self, key):
        "return (lower,upper) range for parameter name"
        f = self.d[key]
        return (f[2], f[3])

    def __getitem__(self, str pname):
        cdef variter p = self.varmap[0].find(pname.encode())
        if p == self.varmap[0].end():
            raise KeyError("not found: %s" % pname)
        if deref(p).second.var:
            return deref(p).second.var[0]
        if deref(p).second.ivar:
            return deref(p).second.ivar[0]
        assert(False)

    def __setitem__(self, str pname, pval):
        cdef variter p = self.varmap[0].find(pname.encode())
        if p == self.varmap[0].end():
            raise KeyError("not found: %s" % pname)
        if not (deref(p).second[0].low <= pval <= deref(p).second[0].up):
            raise ValueError(
                "parameter %s value %s outside range [%s, %s]"
                % (pname, pval, deref(p).second[0].low, deref(p).second[0].up))
        if deref(p).second[0].var:
            deref(p).second[0].var[0] = pval
        elif deref(p).second[0].ivar:
            deref(p).second[0].ivar[0] = pval
        else:
            assert(False)

    property num_inputs:
        "number of input channels"
        def __get__(self):
            if self.p[0].mono_audio:
                return 1
            elif self.p[0].stereo_audio:
                return 2
            else:
                return 0

    property num_outputs:
        "number of output channels"
        def __get__(self):
            if self.p[0].mono_audio:
                return 1
            elif self.p[0].stereo_audio:
                return 2
            else:
                return 0

    property samplerate:
        "initialized samplerate"
        def __get__(self):
            return self._samplerate

    def init(self, int samplingRate):
        """argument: sample rate
        must be called before calling compute"""
        if self.p[0].activate_plugin:
            self.p[0].activate_plugin(True, self.p)
        if self.p[0].set_samplerate:
            self.p[0].set_samplerate(samplingRate, self.p)
        self._samplerate = samplingRate

    def clear_state(self):
        if self.p[0].clear_state:
            self.p[0].clear_state(self.p)

    def compute(self, np.ndarray inp_data not None):
        """execute dsp algorithm

        argument: numpy array
        returns: float32 numpy array

        specify type when creating an array, e.g. zeros(200, dtype=float32)
        """
        if not self._samplerate:
            raise ValueError("Plugin not initialized")
        cdef int transposed = False
        if self.p[0].mono_audio:
            if np.PyArray_NDIM(inp_data) == 2:
                if np.PyArray_DIMS(inp_data)[0] != 1:
                    if np.PyArray_DIMS(inp_data)[1] == 1:
                        transposed = True
                        inp_data = inp_data.T
                    else:
                        raise ValueError("plugin has only channel")
            elif not np.PyArray_NDIM(inp_data) == 1:
                raise ValueError("plugin has only channel")
        elif self.p[0].stereo_audio:
            if np.PyArray_NDIM(inp_data) != 2:
                raise ValueError("plugin has 2 channels")
            if np.PyArray_DIMS(inp_data)[0] != 2 and np.PyArray_DIMS(inp_data)[1] == 2:
                transposed = True
                inp_data = inp_data.T
        else:
            raise ValueError("no process function available")
        cdef np.ndarray inp = np.array(inp_data, dtype=np_realt, order='C', copy=False)
        cdef int count = np.PyArray_DIMS(inp)[np.PyArray_NDIM(inp)-1]
        cdef timespec t0, t1
        cdef np.ndarray o
        if self.p[0].mono_audio:
            o = np.empty(count,dtype=np_realt)
            clock_gettime(CLOCK_MONOTONIC, &t0)
            self.p[0].mono_audio(count, <realtp>np.PyArray_DATA(inp), <realtp>np.PyArray_DATA(o), self.p)
            clock_gettime(CLOCK_MONOTONIC, &t1)
            if np.PyArray_NDIM(inp_data) == 2:
                o = o.reshape(1, count)
        else:
            o = np.empty((2,count),dtype=np_realt)
            clock_gettime(CLOCK_MONOTONIC, &t0)
            self.p[0].stereo_audio(
                count, <realtp>np.PyArray_DATA(inp), <realtp>(<char*>np.PyArray_DATA(inp)+np.PyArray_STRIDES(inp)[0]),
                <realtp>np.PyArray_DATA(o), <realtp>(<char*>np.PyArray_DATA(o)+np.PyArray_STRIDES(o)[0]), self.p)
            clock_gettime(CLOCK_MONOTONIC, &t1)
        self.time_per_sample = ts_diff(t1,t0)/count
        if transposed:
            o = o.T
        return o

    def __dealloc__(self):
        del self.varmap
        if self.handle:
            if self.p and self.p[0].delete_instance:
                self.p[0].delete_instance(self.p)
            dlclose(self.handle)

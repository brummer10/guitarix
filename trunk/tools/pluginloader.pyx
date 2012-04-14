from cython.operator cimport dereference as deref, preincrement as inc
import numpy as np
cimport numpy as np

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

cdef extern from "gx_plugin.h":
    cdef struct value_pair:
        char *value_id
        char *value_label
    ctypedef value_pair* const_value_pair_ptr "const value_pair*"
    cppclass Var:
        char *id
        char *name
        float *var
        float *uvar
        float val
        float low
        float up
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
    ctypedef void (*process_mono_audio) (int count, float *input, float *output, PluginDef *plugin)
    ctypedef void (*inifunc)(unsigned int samplingFreq, PluginDef *plugin)
    ctypedef int (*activatefunc)(int start, PluginDef *plugin)
    ctypedef void (*process_stereo_audio)(int count, float *input1, float *input2,
                                           float *output1, float *output2, PluginDef *plugin)
    cppclass PluginDef:
        int version
        int flags
        char* id
        char* name
        char** groups
        registerfunc register_params
        process_mono_audio mono_audio
        process_stereo_audio stereo_audio
        inifunc set_samplerate
        activatefunc activate_plugin
    ctypedef int (*plugin_inifunc)(unsigned int idx, PluginDef **p)

cdef extern from "pluginloader.h":
    pass

cdef inline double ts_diff(timespec ts1, timespec ts2):
    cdef double df = ts1.tv_sec - ts2.tv_sec
    return df * 1e9 + (ts1.tv_nsec - ts2.tv_nsec)

ctypedef float *floatp

cdef class Plugin:
    cdef void *handle
    cdef PluginDef *p
    cdef VarMap *varmap
    cdef dict d
    cdef double time_per_sample

    def __cinit__(self, char *path, unsigned int idx = 0):
        cdef int n
        self.varmap = new VarMap()
        self.p = <PluginDef*>0
        self.handle = dlopen(path, RTLD_LOCAL|RTLD_NOW)
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
        if idx >= n:
            raise RuntimeError("idx too big (%d > %d)" % (idx, n-1))
        if get_gx_plugin(idx, &self.p) < 0:
            raise RuntimeError("plugin loader error")
        cdef ParamRegImpl *pr
        cdef variter i
        d = {}
        if self.p[0].register_params:
            pr = new ParamRegImpl(self.varmap, &self.p[0])
            self.p[0].register_params(pr[0])
            del pr
            i = self.varmap[0].begin()
            while i != self.varmap[0].end():
                d[deref(i).second[0].id] = (
                    deref(i).second[0].name, deref(i).second[0].val,
                    deref(i).second[0].low, deref(i).second[0].up,
                    self.get_vp_list(deref(i).second))
                inc(i)
        self.d = d
        self.time_per_sample = 0

    property nanosec_per_sample:
        "time in nanoseconds measured for last compute call"
        def __get__(self):
            return self.time_per_sample

    def keys(self):
        return self.d.keys()

    def get_var_attr(self, key):
        """argument: parameter name
        returns: name, stdval, lower, upper"""
        return self.d[key]

    cdef get_vp_list(self, Var *p):
        cdef const_value_pair_ptr vp = p.values
        if not vp:
            return []
        l = []
        for i in range(int(p.up)+1):
            l.append((vp[i].value_id, vp[i].value_label))
        return l

    def get_range(self, key):
        f = self.d[key]
        return (f[2], f[3])

    def __getitem__(self, char *pname):
        cdef variter p = self.varmap[0].find(pname)
        if p == self.varmap[0].end():
            raise KeyError("not found: %s" % pname)
        if deref(p).second.var:
            return deref(p).second.var[0]
        if deref(p).second.uvar:
            return deref(p).second.uvar[0]
        assert(False)

    def __setitem__(self, char* pname, float pval):
        cdef variter p = self.varmap[0].find(pname)
        if p == self.varmap[0].end():
            raise KeyError("not found: %s" % pname)
        if pval < deref(p).second[0].low:
            pval = deref(p).second[0].low
        if pval > deref(p).second[0].up:
            pval = deref(p).second[0].up
        if deref(p).second[0].var:
            deref(p).second[0].var[0] = pval
        elif deref(p).second[0].uvar:
            deref(p).second[0].uvar[0] = pval
        else:
            assert(False)

    def init(self, int samplingRate):
        """argument: sample rate
        must be called before calling compute"""
        if self.p[0].activate_plugin:
            self.p[0].activate_plugin(True, self.p)
        if self.p[0].set_samplerate:
            self.p[0].set_samplerate(samplingRate, self.p)

    def compute(self, np.ndarray inp = None):
        """execute dsp algorithm

        argument: float32 numpy array
        returns: float32 numpy array

        specify type when creating an array, e.g. zeros(200, dtype=float32)
        """
        if not isinstance(inp, np.ndarray):
            raise ValueError("need ndarray")
        if inp.dtype != np.float32:
            raise ValueError("need float32")
        cdef int count = inp.shape[inp.ndim-1]
        cdef timespec t0, t1
        cdef np.ndarray o
        if self.p[0].mono_audio:
            if not inp.ndim == 1:
                raise ValueError("need vector")
            o = np.empty(count,dtype=np.float32)
            clock_gettime(CLOCK_MONOTONIC, &t0)
            self.p[0].mono_audio(count, <floatp>inp.data, <floatp>o.data, self.p)
            clock_gettime(CLOCK_MONOTONIC, &t1)
        elif self.p[0].stereo_audio:
            if not (inp.ndim == 2 and inp.shape[1] >= 2):
                raise ValueError("need 2-dim array with at least %d rows" % 2)
            o = np.empty((2,count),dtype=np.float32)
            clock_gettime(CLOCK_MONOTONIC, &t0)
            self.p[0].stereo_audio(
                count, <floatp>(inp.data), <floatp>(inp.data+inp.strides[0]),
                <floatp>(o.data), <floatp>(o.data+o.strides[0]), self.p)
            clock_gettime(CLOCK_MONOTONIC, &t1)
        self.time_per_sample = ts_diff(t1,t0)/count
        return o

    def __dealloc__(self):
        del self.varmap
        if self.handle:
            dlclose(self.handle)

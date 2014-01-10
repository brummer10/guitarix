cimport libc.stdlib
cimport numpy as np
import numpy as np

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

cdef extern from "ladspa.h":
    ctypedef int LADSPA_PortDescriptor
    ctypedef int LADSPA_Properties
    ctypedef int LADSPA_PortRangeHintDescriptor
    ctypedef void * LADSPA_Handle
    ctypedef float LADSPA_Data
    enum:
        LADSPA_PROPERTY_REALTIME        = 0x1
        LADSPA_PROPERTY_INPLACE_BROKEN  = 0x2
        LADSPA_PROPERTY_HARD_RT_CAPABLE = 0x4
    enum:
        LADSPA_PORT_INPUT   = 0x1
        LADSPA_PORT_OUTPUT  = 0x2
        LADSPA_PORT_CONTROL = 0x4
        LADSPA_PORT_AUDIO   = 0x8
    enum:
        LADSPA_HINT_BOUNDED_BELOW   = 0x1
        LADSPA_HINT_BOUNDED_ABOVE   = 0x2
        LADSPA_HINT_TOGGLED         = 0x4
        LADSPA_HINT_SAMPLE_RATE     = 0x8
        LADSPA_HINT_LOGARITHMIC     = 0x10
        LADSPA_HINT_INTEGER         = 0x20
        LADSPA_HINT_DEFAULT_MASK    = 0x3C0
        LADSPA_HINT_DEFAULT_NONE    = 0x0
        LADSPA_HINT_DEFAULT_MINIMUM = 0x40
        LADSPA_HINT_DEFAULT_LOW     = 0x80
        LADSPA_HINT_DEFAULT_MIDDLE  = 0xC0
        LADSPA_HINT_DEFAULT_HIGH    = 0x100
        LADSPA_HINT_DEFAULT_MAXIMUM = 0x140
        LADSPA_HINT_DEFAULT_0       = 0x200
        LADSPA_HINT_DEFAULT_1       = 0x240
        LADSPA_HINT_DEFAULT_100     = 0x280
        LADSPA_HINT_DEFAULT_440     = 0x2C0
    struct LADSPA_PortRangeHint:
        LADSPA_PortRangeHintDescriptor HintDescriptor
        LADSPA_Data LowerBound
        LADSPA_Data UpperBound
    ctypedef struct LADSPA_Descriptor:
        unsigned long UniqueID
        char * Label
        LADSPA_Properties Properties
        char * Name
        char * Maker
        char * Copyright
        unsigned long PortCount
        LADSPA_PortDescriptor * PortDescriptors
        char ** PortNames
        LADSPA_PortRangeHint * PortRangeHints
        void * ImplementationData
        LADSPA_Handle (*instantiate)(LADSPA_Descriptor * Descriptor,
                                     unsigned long       SampleRate)
        void (*connect_port)(LADSPA_Handle Instance,
                             unsigned long Port,
                             LADSPA_Data * DataLocation)
        void (*activate)(LADSPA_Handle Instance)
        void (*run)(LADSPA_Handle Instance,
                    unsigned long SampleCount)
        void (*run_adding)(LADSPA_Handle Instance,
                           unsigned long SampleCount)
        void (*set_run_adding_gain)(LADSPA_Handle Instance,
                                    LADSPA_Data   Gain)
        void (*deactivate)(LADSPA_Handle Instance)
        void (*cleanup)(LADSPA_Handle Instance)
    ctypedef LADSPA_Descriptor * (*LADSPA_Descriptor_Function)(unsigned long Index)
    ctypedef LADSPA_Descriptor* cp_LADSPA_Descriptor "const LADSPA_Descriptor*"

cdef inline double ts_diff(timespec ts1, timespec ts2):
    cdef double df = ts1.tv_sec - ts2.tv_sec
    return df * 1e9 + (ts1.tv_nsec - ts2.tv_nsec)

ctypedef float *floatp

cdef void *open_ladspa(char *path, LADSPA_Descriptor_Function *ladspa_descriptor):
    cdef void* handle
    handle = dlopen(path, RTLD_LOCAL|RTLD_NOW)
    if not handle:
        raise RuntimeError("Cannot open plugin: %s [%s]" % (path, dlerror()))
    ladspa_descriptor[0] = <LADSPA_Descriptor_Function>dlsym(handle, "ladspa_descriptor")
    cdef char *dlsym_error = dlerror()
    if dlsym_error:
        raise RuntimeError("Cannot load symbol 'ladspa_descriptor': %s" % dlsym_error)
    return handle

def plugin_list(char *path):
    """lists the LADSPA plugins contained in a share library.
    
    argument: path name of the share library
    returns: list of (UniqueID, Name)
    """
    cdef LADSPA_Descriptor_Function ladspa_descriptor
    cdef void *handle = open_ladspa(path, &ladspa_descriptor)
    cdef cp_LADSPA_Descriptor desc
    cdef idx = 0
    l = []
    while True:
        desc = ladspa_descriptor(idx)
        if not desc:
            break
        l.append((desc.UniqueID, desc.Name))
        idx += 1
    dlclose(handle)
    return l


cdef class Ladspa:
    cdef cp_LADSPA_Descriptor desc
    cdef void* handle
    cdef LADSPA_Handle instance
    cdef LADSPA_Data *ctrl_ports
    cdef dict ctrl
    cdef list params
    cdef int num_ctrl
    cdef int _num_inputs
    cdef int _num_outputs
    cdef double time_per_sample
    cdef int _samplerate

    @staticmethod
    def open_unique_id(char *path, unsigned long UniqueID):
        """open a LADSPA plugin by path name and unique id.
	
	arguments:
	  path: path name of share library
	  UniqueID: id of plugin

	returns: Ladspa instance
	"""
        cdef int i
        for i, (uid, name) in enumerate(plugin_list(path)):
            if uid == UniqueID:
                return Ladspa(path, i)
        raise ValueError("UniqueID %d not found" % UniqueID)

    def __cinit__(self, char *path, unsigned int idx = 0):
        cdef LADSPA_Descriptor_Function ladspa_descriptor
        self.handle = open_ladspa(path, &ladspa_descriptor)
        self.desc = ladspa_descriptor(idx)
        cdef int i
        d = {}
        self.params = []
        for i in range(self.desc[0].PortCount):
            if self.desc[0].PortDescriptors[i] & LADSPA_PORT_CONTROL:
                d[self.desc[0].PortNames[i]] = (i, self.num_ctrl)
                self.params.append(self.desc[0].PortNames[i])
                self.num_ctrl += 1
            elif self.desc[0].PortDescriptors[i] & LADSPA_PORT_INPUT:
                self._num_inputs += 1
            else:
                self._num_outputs += 1
        self.ctrl_ports = <LADSPA_Data*>libc.stdlib.calloc(self.num_ctrl, sizeof(LADSPA_Data))
        self.ctrl = d
        self.instance = NULL
        self.time_per_sample = 0
        self._samplerate = 0

    def init(self, int samplingRate):
        """argument: sample rate
        must be called before calling compute"""
        self.instance = self.desc[0].instantiate(self.desc, samplingRate)
        cdef int n = 0
        cdef int i
        for i in range(self.desc[0].PortCount):
            if self.desc[0].PortDescriptors[i] & LADSPA_PORT_CONTROL:
                self.desc[0].connect_port(self.instance, i, &self.ctrl_ports[n])
                n += 1
        self.activate()
        self._samplerate = samplingRate

    property num_inputs:
        "number of input channels"
        def __get__(self):
            return self._num_inputs

    property num_outputs:
        "number of output channels"
        def __get__(self):
            return self._num_outputs

    property samplerate:
        "initialized samplerate"
        def __get__(self):
            return self._samplerate

    property nanosec_per_sample:
        "time in nanoseconds measured for last compute call"
        def __get__(self):
            return self.time_per_sample

    property UniqueID:
        "LADSPA UniqueID"
        def __get__(self):
            return self.desc.UniqueID

    property Name:
        "LADSPA Name"
        def __get__(self):
            return self.desc.Name

    def keys(self):
        "List of LADSPA parameters names (in correct order)"
        return self.params

    def get_var_attr(self, key):
        """argument: parameter name
        returns: name, stdval, lower, upper"""
        low, up = self.get_range(key)
        return (key, None, low, up)

    def get_range(self, key):
        "return (lower,upper) range for parameter name"
        cdef int i, n
        i, n = self.get_ctrl_idx(key)
        low = up = None
        if self.desc[0].PortRangeHints[i].HintDescriptor & LADSPA_HINT_BOUNDED_BELOW:
            low = self.desc[0].PortRangeHints[i].LowerBound
        if self.desc[0].PortRangeHints[i].HintDescriptor & LADSPA_HINT_BOUNDED_ABOVE:
            up = self.desc[0].PortRangeHints[i].UpperBound
        return low, up

    cdef get_ctrl_idx(self, port):
        cdef int i, n
        if isinstance(port, basestring):
            i, n = self.ctrl[port]
        else:
            i = port
            if i < 0 or i >= self.desc[0].PortCount:
                raise ValueError("index out of range")
            if not (self.desc[0].PortDescriptors[i] & LADSPA_PORT_CONTROL):
                raise ValueError("not a control port")
            n = self.ctrl[self.desc[0].PortNames[i]][1]
        return i, n

    def __getitem__(self, port):
        cdef int i, n
        i, n = self.get_ctrl_idx(port)
        return self.ctrl_ports[n]

    def __setitem__(self, port, value):
        cdef int n
        i, n = self.get_ctrl_idx(port)
        if not (self.desc[0].PortDescriptors[i] & LADSPA_PORT_INPUT):
            raise ValueError("not an input control port")
        self.ctrl_ports[n] = value

    def activate(self):
        "activate LADSPA plugin (called automatically by init())"
        if self.desc[0].activate:
            self.desc[0].activate(self.instance)

    cdef connect(self, int tp, int i, floatp v):
        cdef int n
        for n in range(self.desc[0].PortCount):
            if not (self.desc[0].PortDescriptors[n] & LADSPA_PORT_AUDIO):
                continue
            if self.desc[0].PortDescriptors[n] & tp:
                if i == 0:
                    self.desc[0].connect_port(self.instance, n, v)
                    return
                i -= 1
        raise ValueError("audio port not found")
        
    def compute(self, np.ndarray inp_data = None):
        """execute dsp algorithm

        argument: 2-dim float32 numpy array with at least num_inputs rows
        returns: numpy float32 array with num_outputs rows

        when num_inputs == 0 the output will be size default_size (can be set)
        or call with an array of requested size

        when num_inputs == 1 you can use a 1-dim array

        some other input format will be converted automatically
        """
        if not self.instance:
            raise ValueError("ladspa plugin not initialized")
        cdef int ni = self._num_inputs
        cdef int count
        cdef np.ndarray inp
        cdef int transposed = False
        if ni == 0 and inp_data is None:
            count = self.defsize
            inp = None
        else:
            if inp_data.ndim == 2 and inp_data.shape[0] > ni and inp_data.shape[1] == ni:
                inp_data = inp_data.T
                transposed = True
            inp = np.array(inp_data, dtype=np.float32, order='C', copy=False)
            count = inp.shape[inp.ndim-1]
        if ni == 1:
            if not (inp.ndim == 1 or (inp.ndim == 2 and inp.shape[1] >= 1)):
                raise ValueError("need vector or 2-dim array with 1 row")
        elif ni > 1:
            if not (inp.ndim == 2 and inp.shape[1] >= ni):
                raise ValueError("need 2-dim array with at least %d rows" % ni)
        cdef int i, n
        n = inp.strides[0]
        for i in range(ni):
            self.connect(LADSPA_PORT_INPUT, i, <floatp>(inp.data+i*n))
        cdef int no = self._num_outputs
        cdef np.ndarray o
        if no == 1:
            if inp_data.ndim == 2:
                o = np.empty((1,count),dtype=np.float32)
            else:
                o = np.empty(count,dtype=np.float32)
        else:
            o = np.empty((no,count),dtype=np.float32)
        for i in range(no):
            self.connect(LADSPA_PORT_OUTPUT, i, <floatp>(o.data + i*n))
        cdef timespec t0, t1
        clock_gettime(CLOCK_MONOTONIC, &t0)
        self.desc[0].run(self.instance, count)
        clock_gettime(CLOCK_MONOTONIC, &t1)
        self.time_per_sample = ts_diff(t1,t0)/count
        if transposed:
            o = o.T
        return o

    def __dealloc__(self):
        if self.instance:
            self.desc[0].cleanup(self.instance)
        if self.ctrl_ports:
            libc.stdlib.free(self.ctrl_ports)
        if self.handle:
            dlclose(self.handle)

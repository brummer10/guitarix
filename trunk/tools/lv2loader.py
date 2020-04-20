import lilv, numpy, time

class LV2_Port:
    def __init__(self, symbol, idx, name, default, rng, is_output, val):
        self.symbol = symbol
        self.idx = idx
        self.name = name
        self.default = default
        self.rng = rng
        self.is_output = is_output
        self.val = val

class LV2_Plugin:
    def __init__(self, path, idx=0):
        world = lilv.World()
        ns = world.ns
        #world.load_all()
        world.load_bundle(world.new_file_uri(None, path))
        plugins = world.get_all_plugins()
        #plugin_uri_node = world.new_uri("XXX")
        #plugin = plugins[plugin_uri_node]
        self._plugin = plugin = plugins[idx]
        self._uri = str(plugin.get_uri())
        self._bundle = str(plugin.get_bundle_uri())
        self._name = str(plugin.get_name())
        self._num_ports = plugin.get_num_ports()
        self._params = {}
        self._input_idx = []
        self._output_idx = []
        self._instance = None
        self._samplerate = None
        self._time_per_sample = 0.0
        self._control_input_buffers  = []
        self._control_output_buffers = []
        for i in range(self._num_ports):
            port = plugin.get_port(i)
            if port.is_a(ns.lv2.ControlPort):
                symbol = str(port.get_symbol())
                lst = tuple(float(v) for v in port.get_range())
                val = numpy.array([lst[0]], numpy.float32)
                self._params[symbol] = LV2_Port(
                    symbol, i, str(port.get_name()), lst[0], lst[1:],
                    port.is_a(ns.lv2.OutputPort), val)
            else:
                assert port.is_a(ns.lv2.AudioPort)
                if port.is_a(ns.lv2.InputPort):
                    self._input_idx.append(i)
                else:
                    assert port.is_a(ns.lv2.OutputPort)
                    self._output_idx.append(i)

    def init(self, samplingRate):
        """argument: sample rate
        must be called before calling compute"""
        self._instance = lilv.Instance(self._plugin, samplingRate)
        n = 0
        for port in self._params.values():
            self._instance.connect_port(port.idx, port.val)
        self.activate()
        self._samplerate = samplingRate

    @property
    def num_inputs(self):
        "number of input channels"
        return len(self._input_idx)

    @property
    def num_outputs(self):
        "number of output channels"
        return len(self._output_idx)

    @property
    def samplerate(self):
        "initialized samplerate"
        return self._samplerate

    @property
    def nanosec_per_sample(self):
        "time in nanoseconds measured for last compute call"
        return self._time_per_sample

    @property
    def Uri(self):
        "LV2 plugin ID (URI)"
        return self._uri

    @property
    def Name(self):
        "Plugin Name"
        return self._name

    def keys(self):
        "List of parameters names (in correct order)"
        return [s for i, s in sorted((p.idx, p.symbol) for p in self._params.values())]

    def get_var_attr(self, key):
        """argument: parameter name
        returns: name, stdval, lower, upper"""
        port = self._params[key]
        return port.name, port.default, port.rng[0], port.rng[1]

    def get_range(self, key):
        "return (lower,upper) range for parameter name"
        return self._params[key].rng

    def __getitem__(self, port):
        return self._params[port].val[0]

    def __setitem__(self, port, value):
        self._params[port].val[0] = value

    def activate(self):
        "activate LADSPA plugin (called automatically by init())"
        if self._instance is None:
            raise ValueError('activate() before init()')
        self._instance.activate()

    def compute(self, inp_data = None):
        """execute dsp algorithm

        argument: 2-dim float32 numpy array with at least num_inputs rows
        returns: numpy float32 array with num_outputs rows

        when num_inputs == 0 the output will be size default_size (can be set)
        or call with an array of requested size

        when num_inputs == 1 you can use a 1-dim array

        some other input format will be converted automatically
        """
        if not self._instance:
            raise ValueError("LV2 plugin not initialized")
        ni = self.num_inputs
        transposed = False
        if ni == 0 and inp_data is None:
            count = self.defsize
            inp = None
        else:
            if inp_data.ndim == 2 and inp_data.shape[0] > ni and inp_data.shape[1] == ni:
                inp_data = inp_data.T
                transposed = True
            inp = numpy.array(inp_data, dtype=numpy.float32, order='C', copy=False)
            count = inp.shape[inp.ndim-1]
        if ni == 1:
            if not (inp.ndim == 1 or (inp.ndim == 2 and inp.shape[1] >= 1)):
                raise ValueError("need vector or 2-dim array with 1 row")
        elif ni > 1:
            if not (inp.ndim == 2 and inp.shape[1] >= ni):
                raise ValueError("need 2-dim array with at least %d rows" % ni)
        n = inp.strides[0]
        for i in range(ni):
            x = inp[i] if inp.ndim == 2 else inp
            self._instance.connect_port(self._input_idx[i], x)
        no = self.num_outputs
        if no == 1:
            if inp_data.ndim == 2:
                o = numpy.empty((1,count),dtype=numpy.float32)
            else:
                o = numpy.empty(count,dtype=numpy.float32)
        else:
            o = numpy.empty((no,count),dtype=numpy.float32)
        for i in range(no):
            x = o[i] if o.ndim == 2 else o
            self._instance.connect_port(self._output_idx[i], x)
        t0 = 0.0 #time.clock_gettime(time.CLOCK_MONOTONIC)
        self._instance.run(count)
        t1 = 0.0 #time.clock_gettime(time.CLOCK_MONOTONIC)
        self._time_per_sample = (t1 - t0) / count
        if transposed:
            o = o.T
        return o

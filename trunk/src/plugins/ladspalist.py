import os, json, locale
from math import log, exp, sqrt, log10
from ctypes import *
import gtk, glib, gobject

################################################################
# LRDF
#
LADSPA_BASE = "http://ladspa.org/ontology#"

class lrdf_uris(Structure):
    _fields_ = [
        ("size", c_uint),
        ("count", c_uint),
        ("items", POINTER(c_char_p))
        ]

class lrdf_portvalue(Structure):
    _fields_ = [
        ("pid", c_ulong),
	("label", c_char_p),
	("value", c_float)
        ]

class lrdf_defaults(Structure):
    _fields_ = [
	("count", c_uint),
	("items", POINTER(lrdf_portvalue))
        ]

def checkret(val):
    if val != 0:
        raise ValueError("return value != 0: %d" % val)

lrdf = cdll.LoadLibrary("liblrdf.so.0")

lrdf_init = lrdf.lrdf_init
lrdf_init.restype = None
lrdf_init.argtypes = []

lrdf_read_file = lrdf.lrdf_read_file
lrdf_read_file.restype = checkret
lrdf_read_file.argtypes = [c_char_p]

lrdf_read_files = lrdf.lrdf_read_files
lrdf_read_files.restype = checkret
lrdf_read_files.argtypes = [POINTER(c_char_p)]

lrdf_get_subclasses = lrdf.lrdf_get_subclasses
lrdf_get_subclasses.restype = POINTER(lrdf_uris)
lrdf_get_subclasses.argtypes = [c_char_p]

lrdf_get_label = lrdf.lrdf_get_label
lrdf_get_label.restype = c_char_p
lrdf_get_label.argtypes = [c_char_p]

lrdf_free_uris = lrdf.lrdf_free_uris
lrdf_free_uris.restype = None
lrdf_free_uris.argtypes = [POINTER(lrdf_uris)]

lrdf_get_instances = lrdf.lrdf_get_instances
lrdf_get_instances.restype = POINTER(lrdf_uris)
lrdf_get_instances.argtypes = [c_char_p]

lrdf_get_uid = lrdf.lrdf_get_uid
lrdf_get_uid.restype = c_ulong
lrdf_get_uid.argtypes = [c_char_p]

lrdf_get_scale_values = lrdf.lrdf_get_scale_values
lrdf_get_scale_values.restype = POINTER(lrdf_defaults)
lrdf_get_scale_values.argtypes = [c_ulong, c_ulong]

lrdf_get_setting_values = lrdf.lrdf_get_setting_values
lrdf_get_setting_values.restype = POINTER(lrdf_defaults)
lrdf_get_setting_values.argtypes = [c_char_p]

lrdf_free_setting_values = lrdf.lrdf_free_setting_values
lrdf_free_setting_values.restype = None
lrdf_free_setting_values.argtypes = [POINTER(lrdf_defaults)]

lrdf_get_default_uri = lrdf.lrdf_get_default_uri
lrdf_get_default_uri.restype = c_char_p
lrdf_get_default_uri.argtypes = [c_ulong]

lrdf_get_setting_metadata = lrdf.lrdf_get_setting_metadata
lrdf_get_setting_metadata.restype = c_char_p
lrdf_get_setting_metadata.argtypes = [c_char_p, c_char_p]


################################################################
# LADSPA
#

LADSPA_Properties = c_int
LADSPA_PortDescriptor = c_int
LADSPA_PortRangeHintDescriptor = c_int
LADSPA_Data = c_float

class LADSPA_PortRangeHint(Structure):
    _fields_ = [
        ("HintDescriptor", LADSPA_PortRangeHintDescriptor),
        ("LowerBound", LADSPA_Data),
        ("UpperBound", LADSPA_Data)
        ]

class LADSPA_Descriptor(Structure):
    _fields_ = [
        ("UniqueID", c_ulong),
        ("Label", c_char_p),
        ("Properties", LADSPA_Properties),
        ("Name", c_char_p),
        ("Maker", c_char_p),
        ("Copyright", c_char_p),
        ("PortCount", c_ulong),
        ("PortDescriptors", POINTER(LADSPA_PortDescriptor)),
        ("PortNames", POINTER(c_char_p)),
        ("PortRangeHints", POINTER(LADSPA_PortRangeHint)),
        ]

LADSPA_PORT_INPUT   = 0x1
LADSPA_PORT_OUTPUT  = 0x2
LADSPA_PORT_CONTROL = 0x4
LADSPA_PORT_AUDIO   = 0x8

LADSPA_IS_PORT_INPUT   = lambda x: x & LADSPA_PORT_INPUT
LADSPA_IS_PORT_OUTPUT  = lambda x: x & LADSPA_PORT_OUTPUT
LADSPA_IS_PORT_CONTROL = lambda x: x & LADSPA_PORT_CONTROL
LADSPA_IS_PORT_AUDIO   = lambda x: x & LADSPA_PORT_AUDIO

LADSPA_HINT_BOUNDED_BELOW = 0x1
LADSPA_HINT_BOUNDED_ABOVE = 0x2

LADSPA_IS_HINT_BOUNDED_BELOW = lambda x: x & LADSPA_HINT_BOUNDED_BELOW
LADSPA_IS_HINT_BOUNDED_ABOVE = lambda x: x & LADSPA_HINT_BOUNDED_ABOVE

LADSPA_HINT_DEFAULT_MASK    = 0x3C0
LADSPA_HINT_DEFAULT_MINIMUM = 0x040
LADSPA_HINT_DEFAULT_LOW     = 0x080
LADSPA_HINT_DEFAULT_MIDDLE  = 0x0C0
LADSPA_HINT_DEFAULT_HIGH    = 0x100
LADSPA_HINT_DEFAULT_MAXIMUM = 0x140
LADSPA_HINT_DEFAULT_0       = 0x200
LADSPA_HINT_DEFAULT_1       = 0x240
LADSPA_HINT_DEFAULT_100     = 0x280
LADSPA_HINT_DEFAULT_440     = 0x2C0

LADSPA_IS_HINT_HAS_DEFAULT     = lambda x: x & LADSPA_HINT_DEFAULT_MASK
LADSPA_IS_HINT_DEFAULT_MINIMUM = lambda x: (x & LADSPA_HINT_DEFAULT_MASK) == LADSPA_HINT_DEFAULT_MINIMUM
LADSPA_IS_HINT_DEFAULT_LOW     = lambda x: (x & LADSPA_HINT_DEFAULT_MASK) == LADSPA_HINT_DEFAULT_LOW
LADSPA_IS_HINT_DEFAULT_MIDDLE  = lambda x: (x & LADSPA_HINT_DEFAULT_MASK) == LADSPA_HINT_DEFAULT_MIDDLE
LADSPA_IS_HINT_DEFAULT_HIGH    = lambda x: (x & LADSPA_HINT_DEFAULT_MASK) == LADSPA_HINT_DEFAULT_HIGH
LADSPA_IS_HINT_DEFAULT_MAXIMUM = lambda x: (x & LADSPA_HINT_DEFAULT_MASK) == LADSPA_HINT_DEFAULT_MAXIMUM
LADSPA_IS_HINT_DEFAULT_0       = lambda x: (x & LADSPA_HINT_DEFAULT_MASK) == LADSPA_HINT_DEFAULT_0
LADSPA_IS_HINT_DEFAULT_1       = lambda x: (x & LADSPA_HINT_DEFAULT_MASK) == LADSPA_HINT_DEFAULT_1
LADSPA_IS_HINT_DEFAULT_100     = lambda x: (x & LADSPA_HINT_DEFAULT_MASK) == LADSPA_HINT_DEFAULT_100
LADSPA_IS_HINT_DEFAULT_440     = lambda x: (x & LADSPA_HINT_DEFAULT_MASK) == LADSPA_HINT_DEFAULT_440

LADSPA_HINT_TOGGLED     = 0x4
LADSPA_HINT_SAMPLE_RATE = 0x8
LADSPA_HINT_LOGARITHMIC = 0x10
LADSPA_HINT_INTEGER     = 0x20

LADSPA_IS_HINT_TOGGLED     = lambda x: x & LADSPA_HINT_TOGGLED
LADSPA_IS_HINT_SAMPLE_RATE = lambda x: x & LADSPA_HINT_SAMPLE_RATE
LADSPA_IS_HINT_LOGARITHMIC = lambda x: x & LADSPA_HINT_LOGARITHMIC
LADSPA_IS_HINT_INTEGER     = lambda x: x & LADSPA_HINT_INTEGER


blacklist = set((
    4069, 4070,		    # ladspa_guitarix
    1044, 1045, 1046, 1047, # sine
    1912,                   # jamincont
))

class LADSPA:
    def add_plugin(self, desc, d, path, i):
        if desc.UniqueID in blacklist:
            return
        n_in = n_out = 0
        ctrl_ports = []
        pos = 0
        for n in range(desc.PortCount):
            pd = desc.PortDescriptors[n]
            if LADSPA_IS_PORT_AUDIO(pd):
                if LADSPA_IS_PORT_INPUT(pd):
                    n_in += 1
                else:
                    n_out += 1
            else:
                pd = PortDesc(n, pos, LADSPA_IS_PORT_OUTPUT(pd), desc.PortNames[n], desc.PortRangeHints[n])
                ctrl_ports.append(pd)
                pos += 1
        if n_in == 1 and n_out == 1:
            tp = 0
        elif n_in == 2 and n_out == 2:
            tp = 1
        else:
            return
        p = PluginDesc(desc, tp, ctrl_ports, path, i)
        d[desc.UniqueID] = p

    def __init__(self, path, d):
        dll = cdll.LoadLibrary(path)
        ladspa_descriptor = dll.ladspa_descriptor
        ladspa_descriptor.restype = POINTER(LADSPA_Descriptor)
        ladspa_descriptor.argtypes = [c_ulong]
        i = 0
        while True:
            desc = ladspa_descriptor(i)
            if not desc:
                break
            self.add_plugin(desc[0], d, path, i)
            i += 1

################################################################
# PluginDesc, PortDesc
#

tp_scale, tp_scale_log, tp_toggle, tp_enum, tp_display, tp_display_toggle, tp_none = range(7)
display_type_names = "Scale", "Log. Scale", "Toggle", "Enum", "Display", "Led", "Hide"
display_type_dict = dict((v, i) for i, v in enumerate(display_type_names))

stp_coarse, stp_normal, stp_fine = range(3)
step_type_names = "coarse", "normal", "fine"
step_type_dict = dict((v, i) for i, v in enumerate(step_type_names))

class ChangeableValues:
    def __init__(self):
        self.name = None
        self.dflt = None
        self.low = None
        self.up = None
        self.step = None
        self.tp = None
        self.enumdict = {}
        self.newrow = None

    def has_settings(self):
        for k, v in vars(self).items():
            if k == "enumdict":
                if v:
                    return True
            elif k == "step":
                continue
            elif v is not None:
                return True
        return False

class PortDesc:
    def __init__(self, idx, pos, is_output, name, hint):
        self.idx = idx
        self.pos = pos
        self.is_output = is_output
        self.hint_desc = hint.HintDescriptor
        self.fake_low = False
        self.fake_up = False
        self.fake_dflt = False
        self.step = stp_normal
        self.use_sr = False
        self.has_sr = LADSPA_IS_HINT_SAMPLE_RATE(self.hint_desc)
        factory = ChangeableValues()
        self.factory = factory
        self.user = ChangeableValues()
        factory.name = name
        self.set_range_default(hint, factory)
        self.set_default_value(hint, factory)
        self.set_tp_default(hint, factory)

    def has_settings(self):
        return self.user.has_settings()

    def fixup(self):
        f = self.factory
        if LADSPA_IS_HINT_LOGARITHMIC(self.hint_desc):
            if f.low is None and f.up is None:
                if f.dflt is None:
                    f.up = 1.0
                    f.low = 1.0/1000.0
                    f.dflt = sqrt(f.low*f.up)
                    self.fake_dflt = True
                elif f.dflt <= 0:
                    f.dflt = 1.0
                    self.fake_dflt = True
                    f.low = f.dflt/100.0
                    f.up = f.dflt*100.0
                else:
                    f.low = f.dflt/100.0
                    f.up = f.dflt*100.0
                self.fake_low = self.fake_up = True
            elif f.low is None:
                if f.dflt is None:
                    f.low = f.up/1000.0
                    f.dflt = f.low
                    f.fake_dflt = True
                else:
                    if f.dflt >= f.up:
                        f.dflt = f.up
                        f.low = f.up / 1000.0
                    else:
                        f.low = f.dflt
                self.fake_low = True
            elif f.up is None:
                if f.low == 0:
                    f.low = 1e-1
                    self.fake_low = True
                if f.dflt is None:
                    f.up = f.low * 1000.0
                    f.dflt = f.low
                    self.fake_dflt = True
                else:
                    if f.dflt <= f.low:
                        f.dflt = f.low
                        f.up = f.low * 1000.0
                    else:
                        f.up = f.dflt
                self.fake_up = True
            elif f.low <= 0:
                f.low = 1e-7
                self.fake_low = True
            f.step = pow(f.up/f.low, 1.0/200)
        else:
            if f.low is None and f.up is None:
                if f.dflt is None:
                    f.low = -1000
                    f.up = 1000
                    f.dflt = 0
                    self.fake_dflt = True
                else:
                    f.low = f.dflt - 100
                    f.up = f.dflt + 100
                self.fake_low = self.fake_up = True
            elif f.low is None:
                if f.dflt is None:
                    f.low = f.up - 1000
                    f.dflt = f.low
                    self.fake_dflt = True
                else:
                    if f.dflt >= f.up:
                        f.dflt = f.up
                        f.low = f.up - 1000
                    else:
                        f.low = f.dflt
                self.fake_low = True
            elif f.up is None:
                if f.dflt is None:
                    f.up = f.low + 1000
                    f.dflt = f.low
                    self.fake_dflt = True
                else:
                    if f.dflt <= f.low:
                        f.dflt = f.low
                        f.up = f.low + 1000
                    else:
                        f.up = f.dflt
                self.fake_up = True
            f.step = (f.up - f.low) / 100.0
            if f.tp in (tp_toggle, tp_enum):
                f.step = 1.0
        if f.dflt is None:
            self.fake_dflt = True
            f.dflt = f.low
        if f.tp == tp_enum:
            for k in range(int(f.low), int(f.up+1)):
                f.enumdict[k] = f.enumdict.get(k,str(k))

    def calc_step(self):
        if self.get_tp() in (tp_toggle, tp_enum):
            return 1.0
        up = self.get_up()
        low = self.get_low()
        if self.get_tp() == tp_scale_log:
            if self.step == stp_coarse:
                return pow(up/low, 1.0/50)
            if self.step == stp_normal:
                return pow(up/low, 1.0/100)
            if self.step == stp_fine:
                return pow(up/low, 1.0/500)
        else:
            if self.step == stp_coarse:
                s = (up - low) / 30.0
            if self.step == stp_normal:
                s = (up - low) / 300.0
            if self.step == stp_fine:
                s = (up - low) / 3000.0
            if self.has_sr and not self.use_sr:
                s *= SR
            return pow(10.0, round(log10(s)))

    def get_enum(self, idx):
        try:
            return self.user.enumdict[idx]
        except KeyError:
            pass
        try:
            return self.factory.enumdict[idx]
        except KeyError:
            return ""

    def get_name(self):
        n = self.user.name
        if n is not None:
            return n
        return self.factory.name

    def set_low(self, v):
        if not self.fake_low and v == self.factory.low:
            self.user.low = None
        else:
            self.user.low = v

    def get_low(self):
        low = self.user.low
        if low is not None:
            return low
        return self.factory.low

    def set_up(self, v):
        if not self.fake_up and v == self.factory.up:
            self.user.up = None
        else:
            self.user.up = v

    def get_up(self):
        up = self.user.up
        if up is not None:
            return up
        return self.factory.up

    def set_dflt(self, v):
        if  not self.fake_dflt and v == self.factory.dflt:
            self.user.dflt = None
        else:
            self.user.dflt = v

    def get_dflt(self):
        dflt = self.user.dflt
        if dflt is not None:
            return dflt
        return self.factory.dflt

    def get_step(self):
        step = self.user.step
        if step is not None:
            return step
        return self.factory.step

    def set_tp(self, v):
        if v == self.factory.tp:
            self.user.tp = None
        else:
            self.user.tp = v

    def get_tp(self):
        tp = self.user.tp
        if tp is not None:
            return tp
        return self.factory.tp

    def get_newrow(self):
        newrow = self.user.newrow
        if newrow is not None:
            return newrow
        return self.factory.newrow

    def set_default_value(self, h, store):
        if not LADSPA_IS_HINT_HAS_DEFAULT(h.HintDescriptor):
            store.dflt = None
        elif LADSPA_IS_HINT_DEFAULT_0(h.HintDescriptor):
            store.dflt = 0
        elif LADSPA_IS_HINT_DEFAULT_1(h.HintDescriptor):
            store.dflt = 1
        elif LADSPA_IS_HINT_DEFAULT_100(h.HintDescriptor):
            store.dflt = 100
        elif LADSPA_IS_HINT_DEFAULT_440(h.HintDescriptor):
            store.dflt = 440
        elif LADSPA_IS_HINT_DEFAULT_MINIMUM(h.HintDescriptor):
            store.dflt = self.get_low()
        elif LADSPA_IS_HINT_DEFAULT_MAXIMUM(h.HintDescriptor):
            store.dflt = self.get_up()
        else:
            low = self.get_low()
            up = self.get_up()
            if low is None or up is None:
                store.dflt = None
            elif LADSPA_IS_HINT_LOGARITHMIC(self.hint_desc):
                if low > 0:
                    if LADSPA_IS_HINT_DEFAULT_LOW(h.HintDescriptor):
                        store.dflt = exp(log(low)*0.75 + log(up)*0.25)
                    elif LADSPA_IS_HINT_DEFAULT_MIDDLE(h.HintDescriptor):
                        store.dflt = exp(log(low)*0.5 + log(up)*0.5)
                    elif LADSPA_IS_HINT_DEFAULT_HIGH(h.HintDescriptor):
                        store.dflt = exp(log(low)*0.25 + log(up)*0.75)
                else:
                    store.dflt = None
            else:
                if LADSPA_IS_HINT_DEFAULT_LOW(h.HintDescriptor):
                    store.dflt = low * 0.75 + up * 0.25
                elif LADSPA_IS_HINT_DEFAULT_MIDDLE(h.HintDescriptor):
                    store.dflt = low * 0.5 + up * 0.5
                elif LADSPA_IS_HINT_DEFAULT_HIGH(h.HintDescriptor):
                    store.dflt = low * 0.25 + up * 0.75

    def set_range_default(self, h, store):
        if LADSPA_IS_HINT_TOGGLED(h.HintDescriptor):
            store.low = 0
            store.up = 1
            store.step = 1
        else:
            if LADSPA_IS_HINT_BOUNDED_BELOW(h.HintDescriptor):
                store.low = h.LowerBound
            else:
                store.low = None
            if LADSPA_IS_HINT_BOUNDED_ABOVE(h.HintDescriptor):
                store.up = h.UpperBound
            else:
                store.up = None
            if store.low is None or store.up is None:
                store.step = None
            else:
                if LADSPA_IS_HINT_LOGARITHMIC(self.hint_desc):
                    if store.low > 0:
                        store.step = pow(store.up/store.low, 1.0/200)
                    else:
                        store.step = None
                        self.error = 1
                else:
                    store.step = (store.up - store.low) / 100.0
        if self.is_output:
            store.step = None

    def set_tp_default(self, h, store):
        if self.is_output:
            if LADSPA_IS_HINT_TOGGLED(h.HintDescriptor):
                store.tp = tp_display_toggle
                store.step = 1
            elif self.get_name() == "latency":
                store.tp = tp_none
            else:
                store.tp = tp_display
        elif LADSPA_IS_HINT_TOGGLED(h.HintDescriptor):
            store.tp = tp_toggle
            store.step = 1
        elif LADSPA_IS_HINT_LOGARITHMIC(self.hint_desc):
            store.tp = tp_scale_log
        elif LADSPA_IS_HINT_INTEGER(h.HintDescriptor):
            store.tp = tp_enum
            store.step = 1
        else:
            store.tp = tp_scale

    def set_enum(self, l):
        assert not self.factory.enumdict
        self.factory.enumdict = dict([(int(k),v) for k, v in l])

    def set_default(self, value, label):
        if self.factory.dflt is None:
            self.factory.dflt = value

    def output(self):
        dflt = self.get_dflt()
        low = self.get_low()
        up = self.get_up()
        step = self.get_step()
        if self.has_sr and not self.use_sr:
            if dflt is not None:
                dflt *= SR
            if low is not None:
                low *= SR
            if up is not None:
                up *= SR
            if step is not None and self.get_tp() == tp_scale_log:
                step *= SR
        el = [self.get_enum(i) for i in range(int(low), int(up)+1)] if self.get_tp() == tp_enum else []
        return [self.idx, [self.step], self.user.name or "", int(self.use_sr), dflt, low, up, self.calc_step(), self.get_tp(), int(self.get_newrow()), el]

    def set_state(self, v):
        assert self.idx == v[0]
        self.step = v[1][0]
        self.use_sr = v[3]
        dflt = v[4]
        low = v[5]
        up = v[6]
        step = v[7]
        if self.has_sr and not self.use_sr:
            dflt /= SR
            low /= SR
            up /= SR
            if not v[8] == tp_scale_log:
                step /= SR
        if dflt != self.factory.dflt:
            self.user.dflt = dflt
        if low != self.factory.low:
            self.user.low = low
        if up != self.factory.up:
            self.user.up = up
        if step != self.factory.step:
            self.user.step = step
        if v[2]:
            self.user.name = v[2]
        if v[8] != self.factory.tp:
            self.user.tp = v[8]
        if v[9] != self.factory.newrow:
            self.user.newrow = bool(v[9])
        s = int(low)
        for i, x in enumerate(v[10]):
            idx = s + i
            if x and self.factory.enumdict.get(idx) != x:
                self.user.enumdict[idx] = x

cat_dict = {
    "Reverbs": "Reverb",
    "Filters": "Tone control",
    "EQs": "Tone control",
    "Compressors": "Guitar Effects",
    "Utilities": "Misc",
    "Delays": "Echo / Delay",
    "Phasers": "Modulation",
    "Chorus": "Modulation",
    "Flangers": "Modulation",
    "Modulators": "Modulation",
    "Distortions": "Distortion",
    "Waveshapers": "Distortion",
    "Amplifiers": "Distortion",
}
    
class PluginDesc:
    def __init__(self, desc, tp, ctrl_ports, path, index):
        self.UniqueID = desc.UniqueID
        self.Label = desc.Label
        self.short = self.Name = desc.Name
        self.Maker = desc.Maker
        self.tp = tp
        self.ctrl_ports = ctrl_ports
        self.path = path
        self.index = index
        self.category = self.deduced_category = "External"
        self.ladspa_category = ""
        self.active = False
        self.has_settings = False

    def _i_check_has_settings(self):
        if self.short != self.Name:
            return True
        if self.category != self.deduced_category:
            return True
        for q in self.ctrl_ports:
            if q.has_settings():
                return True
        return False

    def check_has_settings(self):
        self.has_settings = self._i_check_has_settings()

    def set_active(self, v):
        self.active = v

    def fixup(self):
        for i, p in enumerate(self.ctrl_ports):
            p.factory.newrow = (i % 4 == 0 and i != 0)
            p.fixup()

    def set_category(self, s):
        self.ladspa_category = s
        for t in s.split("/"):
            try:
                self.category = self.deduced_category = cat_dict[t]
                return
            except KeyError:
                pass

    def set_enum(self, idx, l):
        for p in self.ctrl_ports:
            if p.idx == idx:
                p.set_enum(l)
                return
        assert(False)

    def set_default(self, idx, value, label):
        for p in self.ctrl_ports:
            if p.idx == idx:
                p.set_default(value, label)
                return
        #print "##", idx, label, self.UniqueID, self.Label, [p.idx for p in self.ctrl_ports]
        #assert(False)

    def __str__(self):
        return "%(UniqueID)s/%(Name)s [%(path)s:%(index)s]" % vars(self)

    def output(self):
        s = self.short
        if s == self.Name:
            s = ""
        return [1, s, self.category, [p.output() for p in self.ctrl_ports]]

    def output_entry(self):
        return [self.path, self.index, self.UniqueID, self.Label]

    def set_state(self, l):
        version = l[0]
        if l[1]:
            self.short = l[1]
        else:
            self.short = self.Name
        self.category = l[2]
        ctrl_ports = []
        for v in l[3]:
            for p in self.ctrl_ports:
                if p.idx == v[0]:
                    p.set_state(v)
                    ctrl_ports.append(p)
                    break
            else:
                assert False
        self.ctrl_ports = ctrl_ports
        self.check_has_settings()

    def print_ports(self):
        for p in self.ctrl_ports:
            print p.name


################################################################
# interative
#

def search_equal(model, column, key, it):
    txt = model[it][0].lower()
    for k in key.lower().split():
        if k not in txt:
            return True
    return False

def display_step(column, cell, model, it):
    q = model[it][8]
    cell.props.visible = (q.get_tp() in (tp_scale, tp_scale_log))

def display_ladspa(column, cell, model, it):
    p = model[it][2]
    if p.has_settings:
        cell.props.foreground = "red"
    else:
        cell.props.foreground_set = False

def display_label(column, cell, model, it):
    row = model[it]
    if int(row[0]) in row[2].user.enumdict:
        cell.props.foreground = "red"
    else:
        cell.props.foreground_set = False

def display_idx(column, cell, model, it):
    q = model[it][8]
    if int(model.get_path(it)[0]) != q.pos:
        cell.props.foreground = "red"
    else:
        cell.props.foreground_set = False

def display_name(column, cell, model, it):
    q = model[it][8]
    if q.user.name is not None:
        cell.props.foreground = "red"
    else:
        cell.props.foreground_set = False

def display_default(column, cell, model, it):
    q = model[it][8]
    cell.props.foreground_set = False
    cell.props.background_set = False
    if q.get_tp() in (tp_display, tp_display_toggle, tp_none):
        cell.props.visible = False
        return
    cell.props.visible = True
    if q.user.dflt is not None:
        cell.props.foreground = "red"
    elif q.fake_dflt:
        cell.props.background = "grey"

def display_lower(column, cell, model, it):
    q = model[it][8]
    cell.props.foreground_set = False
    cell.props.background_set = False
    if q.get_tp() in (tp_toggle, tp_display_toggle, tp_none):
        cell.props.visible = False
        return
    cell.props.visible = True
    if q.user.low is not None:
        cell.props.foreground = "red"
    elif q.fake_low:
        cell.props.background = "grey"

def display_upper(column, cell, model, it):
    q = model[it][8]
    cell.props.foreground_set = False
    cell.props.background_set = False
    if q.get_tp() in (tp_toggle, tp_display_toggle, tp_none):
        cell.props.visible = False
        return
    cell.props.visible = True
    if q.user.up is not None:
        cell.props.foreground = "red"
    elif q.fake_up:
        cell.props.background = "grey"

def display_SR(column, cell, model, it):
    cell.props.visible = model[it][8].has_sr

def display_type(column, cell, model, it):
    q = model[it][8]
    if q.user.tp is None:
        cell.props.foreground_set = False
    else:
        cell.props.foreground = "red"

SR = 44100

menudef = """
<ui>
  <menubar>
    <menu action="FileMenuAction">
      <menuitem action="SaveAction" />
      <menuitem action="QuitAction" />
    </menu>
    <menu action="ViewMenuAction">
      <menuitem action="FindAction" />
    </menu>
  </menubar>
</ui>
"""

class PluginDisplay:
    def __init__(self, d, old_not_found):
        self.plugindict = d
        self.current_plugin = None
        self.bld = bld = gtk.Builder()
        bld.add_from_file("ladspaliste.glade")
        self.window = bld.get_object("window1")
        uimanager = gtk.UIManager()
        actiongroup = gtk.ActionGroup("main")
        actiongroup.add_actions([('FileMenuAction',None,"_File"),
                                 ('SaveAction',None,"_Save","<control>s",None,self.on_save),
                                 ('QuitAction',None,"_Quit","<control>q",None,gtk.main_quit),
                                 ('ViewMenuAction',None,"_View"),
                                 ('FindAction',None,"_Find","<control>f",None,self.on_find),
                                 ])
        uimanager.insert_action_group(actiongroup, 0)
        uimanager.add_ui_from_string(menudef)
        bld.get_object("menubox").pack_start(uimanager.get_widget('/menubar'))
        self.window.add_accel_group(uimanager.get_accel_group())

        w = bld.get_object("invert_selection").connect("clicked", self.on_invert_selection)
        w = bld.get_object("show_details").connect("clicked", self.on_show_details)
        w = bld.get_object("treeview3")
        sel = w.get_selection()
        sel.set_mode(gtk.SELECTION_BROWSE)
        l = gtk.ListStore(int,str,gobject.TYPE_PYOBJECT)
        w.set_model(l)
        bld.get_object("cellrenderer_label").connect("edited", self.on_label_edited)
        bld.get_object("treeviewcolumn_label").set_cell_data_func(bld.get_object("cellrenderer_label"), display_label)

        w = bld.get_object("treeview2")
        sel = w.get_selection()
        sel.set_mode(gtk.SELECTION_BROWSE)
        sel.connect("changed", self.on_parameter_selection_changed)
        l = gtk.ListStore(int,str,str,str,str,str,str,gtk.ListStore,gobject.TYPE_PYOBJECT,bool,bool)
        l.connect("row-deleted", self.on_reordered)
        w.set_model(l)
        bld.get_object("cellrenderer_type").connect("edited", self.on_type_edited)
        bld.get_object("cellrenderer_step").connect("edited", self.on_step_edited)
        bld.get_object("cellrenderer_newrow").connect("toggled", self.on_newrow_toggled, l)
        bld.get_object("cellrenderer_name").connect("edited", self.on_name_edited)
        bld.get_object("cellrenderer_dflt").connect("edited", self.on_dflt_edited)
        bld.get_object("cellrenderer_low").connect("edited", self.on_low_edited)
        bld.get_object("cellrenderer_up").connect("edited", self.on_up_edited)
        bld.get_object("treeviewcolumn_idx").set_cell_data_func(bld.get_object("cellrenderer_idx"), display_idx)
        bld.get_object("treeviewcolumn_name").set_cell_data_func(bld.get_object("cellrenderer_name"), display_name)
        bld.get_object("treeviewcolumn_dflt").set_cell_data_func(bld.get_object("cellrenderer_dflt"), display_default)
        bld.get_object("treeviewcolumn_low").set_cell_data_func(bld.get_object("cellrenderer_low"), display_lower)
        bld.get_object("treeviewcolumn_up").set_cell_data_func(bld.get_object("cellrenderer_up"), display_upper)
        bld.get_object("treeviewcolumn_step").set_cell_data_func(bld.get_object("cellrenderer_step"), display_step)
        bld.get_object("treeviewcolumn_type").set_cell_data_func(bld.get_object("cellrenderer_type"), display_type)
        bld.get_object("treeviewcolumn_SR").set_cell_data_func(bld.get_object("cellrenderer_SR"), display_SR)

        self.display_type_list = gtk.ListStore(str)
        for tp in tp_scale, tp_scale_log, tp_toggle, tp_enum, tp_none:
            self.display_type_list.append((display_type_names[tp],))
        self.display_type_list_sr = gtk.ListStore(str)
        for tp in tp_scale, tp_scale_log, tp_none:
            self.display_type_list_sr.append((display_type_names[tp],))
        self.output_type_list = gtk.ListStore(str)
        for tp in tp_display, tp_display_toggle, tp_none:
            self.output_type_list.append((display_type_names[tp],))

        w = bld.get_object("treeview1")
        w.connect("row-activated", lambda w, m, p: bld.get_object("show_details").clicked())
        w.set_search_equal_func(search_equal)
        w.set_search_entry(bld.get_object("search_entry"))
        sel = w.get_selection()
        sel.set_mode(gtk.SELECTION_BROWSE)
        sel.connect("changed", self.selection_changed)
        l = gtk.ListStore(str, bool, gobject.TYPE_PYOBJECT)
        w.set_model(l)
        bld.get_object("cellrenderer_active").connect("toggled", self.on_active_toggled, l)
        bld.get_object("treeviewcolumn_ladspa").set_cell_data_func(bld.get_object("cellrenderer_ladspa"), display_ladspa)

        bld.get_object("plugin_category").set_cell_data_func(bld.get_object("cellrenderer_category"), self.display_category)

        bld.get_object("selected_only").connect("toggled", self.on_selected_only_changed)
        w = bld.get_object("combobox_mono_stereo")
        w.connect("changed", self.on_mono_stereo_changed)
        w.set_active(0)

        self.window.connect("destroy", gtk.main_quit)
        bld.get_object("button_cancel").set_related_action(actiongroup.get_action("QuitAction"))
        bld.get_object("button_save").set_related_action(actiongroup.get_action("SaveAction"))
        self.window.show()

    def on_find(self, a):
        self.bld.get_object("search_entry").grab_focus()

    def display_category(self, column, cell, model, it):
        if self.current_plugin is None:
            cell.props.foreground_set = False
        else:
            c = model[it][0]
            if c == self.current_plugin.deduced_category:
                cell.props.foreground_set = False
            else:
                cell.props.foreground = "red"

    def load(self):
        a = self.bld.get_object("combobox_mono_stereo").get_active()
        o = self.bld.get_object("selected_only").get_active()
        l = self.bld.get_object("treeview1").get_model()
        l.clear()
        for v in sorted(self.plugindict.values(), cmp=lambda a, b: cmp(a.Name.lower(),b.Name.lower())):
            if (o and not v.active):
                continue
            if (a == 1 and v.tp != 0) or (a == 2 and v.tp != 1):
                continue
            l.append((v.Name, v.active, v))

    def on_save(self, w):
        self.save_current()
        l = []
        fl = []
        for row in self.bld.get_object("treeview1").get_model():
            p = row[2]
            if p.active:
                l.append(p.output_entry())
            fname = get_ladspa_plugin_config(p.UniqueID)
            if p.active or p.has_settings:
                tfname = fname + ".tmp"
                tfile = file(tfname,"w")
                json.dump(p.output(), tfile, sort_keys=True, indent=2)
                tfile.close()
                fl.append((tfname, fname))
            else:
                fl.append((None, fname))
        fname = get_config_filename()
        tfname = fname + ".tmp"
        tfile = file(tfname,"w")
        json.dump(l, tfile, sort_keys=True, indent=2)
        tfile.close()
        os.rename(tfname, fname)
        for tfname, fname in fl:
            if tfname is None:
                try:
                    os.remove(fname)
                except OSError:
                    pass
            else:
                try:
                    os.rename(tfname, fname)
                except OSError:
                    print "cannot rename %s to %s" % (tfname, fname)
        gtk.main_quit()

    def on_select_all(self, w, v): ##unused
        for row in self.bld.get_object("treeview1").get_model():
            row[1] = v
            row[2].set_active(v)

    def on_invert_selection(self, w):
        for row in self.bld.get_object("treeview1").get_model():
            v = not row[1]
            row[1] = v
            row[2].set_active(v)

    def on_show_details(self, w):
        self.bld.get_object("details_box").set_visible(w.get_active())
        self.window.resize(1, self.window.get_size()[1])

    def on_selected_only_changed(self, w):
        self.load()

    def on_mono_stereo_changed(self, w):
        self.load()

    def save_current(self):
        if self.current_plugin is None:
            return
        p = self.current_plugin
        s = self.bld.get_object("plugin_name").get_text().strip()
        if not s:
            p.short = p.Name
        else:
            p.short = s
        w = self.bld.get_object("plugin_category")
        p.category = w.get_model()[w.get_active_iter()][0]
        p.check_has_settings()

    def selection_changed(self, sel):
        self.save_current()
        w = self.bld.get_object("treeview2")
        ls2 = w.get_model()
        ls, it = sel.get_selected()
        ls2.handler_block_by_func(self.on_reordered)
        ls2.clear()
        ls2.handler_unblock_by_func(self.on_reordered)
        self.bld.get_object("ladspa_category").set_text("")
        self.bld.get_object("ladspa_maker").set_text("")
        self.bld.get_object("ladspa_uniqueid").set_text("")
        self.bld.get_object("plugin_name").set_text("")
        self.bld.get_object("plugin_category").set_active(-1)
        if it is None:
            self.current_plugin = None
            return
        self.current_plugin = p = ls[it][2]
        w = self.bld.get_object("plugin_name")
        if p.short != p.Name:
            w.modify_text(gtk.STATE_NORMAL, gtk.gdk.Color("red"))
        else:
            w.modify_text(gtk.STATE_NORMAL, None)
        w.set_text(p.short)
        w = self.bld.get_object("plugin_category")
        for i, row in enumerate(w.get_model()):
            if row[0] == p.category:
                w.set_active(i)
                break
        self.bld.get_object("ladspa_category").set_text(p.ladspa_category)
        self.bld.get_object("ladspa_maker").set_text(p.Maker)
        self.bld.get_object("ladspa_uniqueid").set_text(str(p.UniqueID))
        for i, q in enumerate(p.ctrl_ports):
            if q.is_output:
                tls = self.output_type_list
            elif q.has_sr:
                tls = self.display_type_list_sr
            else:
                tls = self.display_type_list
            dflt = q.get_dflt()
            low = q.get_low()
            up = q.get_up()
            if q.has_sr and not q.use_sr:
                if dflt is not None:
                    dflt *= SR
                if low is not None:
                    low *= SR
                if up is not None:
                    up *= SR
            dflt = "%g" % dflt
            low = "%g" % low 
            up = "%g" % up
            ls2.append((q.pos, q.get_name(), dflt, low, up, step_type_names[q.step],
                        display_type_names[q.get_tp()], tls, q, q.get_newrow(), q.has_sr and not q.use_sr))

    def on_parameter_selection_changed(self, sel):
        ls, it = sel.get_selected()
        ls2 = self.bld.get_object("treeview3").get_model()
        ls2.clear()
        if it:
            q = ls[it][8]
            if q.get_tp() == tp_enum:
                for idx in range(int(q.get_low()), int(q.get_up())+1):
                    ls2.append((idx,q.get_enum(idx),q))

    def on_reordered(self, model, path):
        assert self.current_plugin
        d = dict([(p.pos, i) for i, p in enumerate(self.current_plugin.ctrl_ports)])
        l = []
        for row in model:
            l.append(self.current_plugin.ctrl_ports[d[row[0]]])
        self.current_plugin.ctrl_ports = l

    def on_type_edited(self, w, path, text):
        tv = self.bld.get_object("treeview2")
        row = tv.get_model()[path]
        q = row[8]
        tp_old = q.user.tp
        tp = display_type_dict[text]
        q.set_tp(tp)
        if tp != tp_old:
            if tp == tp_scale_log:
                if q.get_low() <= 0:
                    q.set_low(1e-7)
                if q.get_up() <= q.get_low():
                    q.set_up(q.get_low()*1000)
                if not (q.get_low() <= q.get_dflt() <= q.get_up()):
                    q.set_dflt(q.get_low())
            elif tp == tp_toggle:
                q.set_dflt(int(q.get_dflt() != 0))
                q.set_low(0)
                q.set_up(1)
            elif tp == tp_enum:
                q.set_dflt(round(q.get_dflt()))
                q.set_low(round(q.get_low()))
                q.set_up(round(q.get_up()))
            dflt = q.get_dflt()
            low = q.get_low()
            up = q.get_up()
            if q.has_sr and not q.use_sr:
                dflt *= SR
                low *= SR
                up *= SR
            row[2] = "%g" % dflt
            row[3] = "%g" % low
            row[4] = "%g" % up
        row[6] = text
        self.on_parameter_selection_changed(self.bld.get_object("treeview2").get_selection())

    def on_step_edited(self, w, path, text):
        tv = self.bld.get_object("treeview2")
        row = tv.get_model()[path]
        q = row[8]
        q.step = step_type_dict[text]
        row[5] = text

    def on_label_edited(self, w, path, text):
        tv = self.bld.get_object("treeview3")
        row = tv.get_model()[path]
        q = row[2]
        text = text.strip()
        idx = row[0]
        if not text or q.factory.enumdict.get(idx,"") == text:
            try:
                del q.user.enumdict[idx]
            except KeyError:
                pass
            text = q.factory.enumdict.get(idx,str(idx))
        else:
            q.user.enumdict[idx] = text
        row[1] = text

    def on_name_edited(self, w, path, text):
        tv = self.bld.get_object("treeview2")
        row = tv.get_model()[path]
        q = row[8]
        text = text.strip()
        if not text or q.factory.name == text:
            q.user.name = None
        else:
            q.user.name = text
        row[1] = q.get_name()

    def on_dflt_edited(self, w, path, text):
        tv = self.bld.get_object("treeview2")
        row = tv.get_model()[path]
        q = row[8]
        text = text.strip()
        if not text:
            q.user.dflt = None
            val = q.factory.dflt
            if val < q.get_low():
                q.set_low(val)
            if val > q.get_up():
                q.set_up(val)
            if q.has_sr and not q.use_sr:
                val *= SR
        else:
            try:
                val = float(text)
            except ValueError:
                return
            if q.has_sr and not q.use_sr:
                val2 = val / SR
            else:
                val2 = val
            if not (q.get_low() <= val2 <= q.get_up()):
                return
            q.set_dflt(val2)
        row[2] = "%g" % val

    def on_low_edited(self, w, path, text):
        tv = self.bld.get_object("treeview2")
        row = tv.get_model()[path]
        q = row[8]
        if not text:
            q.user.low = None
            val = q.factory.low
            if q.get_dflt() < val:
                q.set_dflt(val)
            if q.get_up() < val:
                q.set_up(min(q.get_up(),val+1))
            if q.has_sr and not q.use_sr:
                val *= SR
        else:
            try:
                val = float(text)
            except ValueError:
                return
            if q.has_sr and not q.use_sr:
                val2 = val/SR
            else:
                val2 = val
            if not (val2 < q.get_up()):
                return
            if q.get_dflt() < val2:
                q.user.dflt = val2
            row[2] = "%g" % q.get_dflt()
            q.set_low(val2)
            if q.get_tp() == tp_enum:
                self.on_parameter_selection_changed(self.bld.get_object("treeview2").get_selection())
        row[3] = "%g" % val

    def on_up_edited(self, w, path, text):
        tv = self.bld.get_object("treeview2")
        row = tv.get_model()[path]
        q = row[8]
        if not text:
            q.user.up = None
            val = q.factory.up
            if q.get_dflt() > val:
                q.set_dflt(val)
            if q.get_low() > val:
                q.set_low(max(q.get_low(),val-1))
            if q.has_sr and not q.use_sr:
                val *= SR
        else:
            try:
                val = float(text)
            except ValueError:
                return
            if q.has_sr and not q.use_sr:
                val2 = val/SR
            else:
                val2 = val
            if not (val2 > q.get_low()):
                return
            if q.get_dflt() > val2:
                q.user.dflt = val2
            row[2] = "%g" % q.get_dflt()
            q.set_up(val2)
            if q.get_tp() == tp_enum:
                self.on_parameter_selection_changed(self.bld.get_object("treeview2").get_selection())
        row[4] = "%g" % val

    def on_newrow_toggled(self, w, path, model):
        row = model[path]
        q = row[8]
        s = not w.get_active()
        row[9] = s
        if s == q.factory.newrow:
            q.user.newrow = None
        else:
            q.user.newrow = s

    def on_active_toggled(self, w, path, model):
        row = model[path]
        p = row[2]
        s = not w.get_active()
        row[1] = s
        p.set_active(s)


###############################################################
# program
#

ranges_1_based = (
    # swh
    (1181, 1440),
    (1605, 1605),
    (1881, 1922),
    # blop
    (1641, 1680),
    (2021, 2038),
    )

def in_1_based_range(uid):
    for f, t in ranges_1_based:
        if uid >= f and uid <= t:
            return True
    return False

def set_instances(uri, d, label, not_found, seen):
    uris = lrdf_get_instances(uri)
    if uris:
        for i in range(uris[0].count):
            u = uris[0].items[i]
            uid = lrdf_get_uid(u)
            if uid not in d:
                not_found.append(uid)
                seen.add(uid)
                continue
            if uid not in seen:
                d[uid].set_category(label)
                for n, p in enumerate(d[uid].ctrl_ports):
                    sval = lrdf_get_scale_values(uid, p.idx)
                    if sval:
                        l = []
                        for nn in range(sval[0].count):
                            t = sval[0].items[nn]
                            l.append((t.value, t.label))
                        p.set_enum(l)
                        lrdf_free_setting_values(sval)
                uri = lrdf_get_default_uri(uid)
                if uri:
                    sval = lrdf_get_setting_values(uri)
                    if sval:
                        for nn in range(sval[0].count):
                            t = sval[0].items[nn]
                            idx = t.pid
                            if in_1_based_range(uid):
                                idx -= 1
                            d[uid].set_default(idx, t.value, t.label)
                        lrdf_free_setting_values(sval)
            seen.add(uid)
        lrdf_free_uris(uris)

def descend(uri, d, not_found, seen, base=""):
    uris = lrdf_get_subclasses(uri)
    if uris:
        for u in ((uris[0].items[i] for i in range(uris[0].count))):
            label = base+"/"+lrdf_get_label(u)
            set_instances(u, d, label, not_found, seen)
            descend(u, d, not_found, seen, label)
        lrdf_free_uris(uris)

def get_config_filename():
    return os.path.join(glib.get_user_config_dir(), "guitarix", "ladspa_defs.js")

def get_ladspa_plugin_config(uid):
    return os.path.join(glib.get_user_config_dir(), "guitarix", "plugins", "ladspa%d.js" % uid)

def main():
    lc = locale.setlocale(locale.LC_ALL, "")
    d = {}

    try:
        ladspa_path = os.environ["LADSPA_PATH"]
    except KeyError:
        ladspa_path = "/usr/lib/ladspa:/usr/local/lib/ladspa"
    for path in ladspa_path.split(":"):
        if not path:
            continue
        try:
            files = os.listdir(path)
        except OSError:
            pass
        else:
            for f in files:
                if f.endswith(".so") and f != "dssi-vst.so":
                    LADSPA(os.path.join(path, f), d)

    locale.setlocale(locale.LC_ALL, "C")
    lrdf_init()
    locale.setlocale(locale.LC_ALL, lc)
    try:
        rdf_path = os.environ["LADSPA_RDF_PATH"]
    except KeyError:
        rdf_path = "/usr/share/ladspa/rdf:/usr/local/share/ladspa/rdf"
    for path in rdf_path.split(":"):
        if not path:
            continue
        try:
            files = os.listdir(path)
        except OSError:
            pass
        else:
            for f in files:
                if not f.endswith((".rdf",".rdfs")):
                    continue
                lrdf_read_file("file://"+os.path.join(path,f))

    not_found = []
    seen = set()
    descend(LADSPA_BASE+"Plugin", d, not_found, seen)

    old_not_found = []
    try:
        f = file(get_config_filename())
    except IOError:
        pass
    else:
        for row in json.load(f):
            uid = row[2]
            if uid not in d:
                old_not_found.append(uid)
            else:
                d[uid].set_active(True)
        f.close()
    for v in d.values():
        v.fixup()
        try:
            f = file(get_ladspa_plugin_config(v.UniqueID))
        except IOError:
            pass
        else:
            v.set_state(json.load(f))
            f.close()

    PluginDisplay(d, old_not_found)
    gtk.main()

if __name__ == "__main__":
    main()

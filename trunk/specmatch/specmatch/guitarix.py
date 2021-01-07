#! /usr/bin/python
# -*- coding: utf-8 -*-

guitarix_pgm = "guitarix -p 7000"

import socket, json, os, gtk, time
import numpy as np

class RpcNotification:

    def __init__(self, method, params):
        self.method = method
        self.params = params


class RpcResult:

    def __init__(self, id, result):
        self.id = id
        self.result = result


class RpcSocket:

    def __init__(self, address=("localhost",7000)):
        self.s = socket.socket()
        self.s.connect(address)
        self.buf = ""

    def send(self, method, id=None, params=[]):
        d = dict(jsonrpc="2.0", method=method, params=params)
        if id is not None:
            d["id"] ="1"
        self.s.send(json.dumps(d)+"\n")

    def call(self, method, params=[]):
        self.send(method=method, id="1", params=params)

    def notify(self, method, params=[]):
        self.send(method=method, params=params)

    def receive(self):
        l = [self.buf]
        while True:
            p = l[-1]
            if  "\n" in p:
                ln, sep, tail = p.partition('\n')
                l[-1] = ln
                st = "".join(l)
                self.buf = tail
                break;
            l.append(self.s.recv(10000))
        try:
            d = json.loads(st)
        except ValueError as e:
            print e
            print st
            return None
        if "params" in d:
            return RpcNotification(d["method"], d["params"])
        elif "result" in d:
            return RpcResult(d["id"], d["result"])
        else:
            raise ValueError("rpc error: %s" % d)


class Guitarix(object):

    def open_socket(self):
        try:
            self.sock = RpcSocket()
        except socket.error as e:
            if e.errno != 111:
                raise
            return False
        return True

    def __init__(self, jackplayer):
        self.current_params = {}
        if not self.open_socket():
            if jackplayer and jackplayer.check_for_port('^gx_head_amp:in_0$'):
                d = gtk.MessageDialog(None, 0, gtk.MESSAGE_WARNING, gtk.BUTTONS_OK_CANCEL,
                                      u"can't connect to running Guitarix instance\n"
                                      u"please close it before continuing")
                res = d.run()
                d.destroy()
                if res != gtk.RESPONSE_OK:
                    raise SystemExit(1)
            os.system(guitarix_pgm+"&")
            for i in range(10):
                time.sleep(1)
                if self.open_socket():
                    break
            else:
                raise RuntimeError("Can't connect to Guitarix")
            self
        self.sock.call("parameterlist", [])
        self.parameterlist = []
        r = self.sock.receive().result
        for tp, d in zip(r[::2], r[1::2]):
            if tp == "Enum":
                d = d["IntParameter"]
            elif tp == "FloatEnum":
                d = d["FloatParameter"]
            d = d["Parameter"]
            n = d["id"]
            if "non_preset" in d and n not in ("system.current_preset", "system.current_bank"):
                continue
            self.parameterlist.append(d["id"])
        self.parameterlist.sort()

    def get_jack_amp_clientname(self):
        return "gx_head_amp"

    def get_jack_fx_clientname(self):
        return "gx_head_fx"

    def get_jname(self, stereo):
        if stereo:
            return "jconv"
        else:
            return "jconv_mono"

    def ensure_convolver(self, stereo):
        jname = self.get_jname(stereo)
        self.sock.call("get_rack_unit_order", [int(stereo)])
        units = self.sock.receive().result
        if jname not in units: # or units[-1] != jname:
            self.sock.notify("insert_rack_unit", [jname, "", int(stereo)])
        self.set_convolver_state(0, stereo)
        if not stereo:
            self.sock.call("get_rack_unit_order", [1])
            stereo_units = self.sock.receive().result
            if stereo_units:
                l = []
                for unit in stereo_units:
                    l.append(unit+".on_off")
                    l.append(0)
                self.sock.notify("set", l)

    def set_convolver_state(self, state, stereo):
        self.sock.notify("set", [self.get_jname(stereo)+".on_off", state])

    def set_engine_on(self):
        self.sock.call("getstate")
        self.engine_state = self.sock.receive().result
        if self.engine_state != "running":
            self.sock.notify("setstate",["running"])

    def restore_engine_state(self):
        if self.engine_state != "running":
            self.sock.notify("setstate",[self.engine_state])

    def get_parameters(self):
        return self.current_params

    def set_parameters(self, d, tmpdir):
        """Send parameters in d to guitarix

        if an IR file is located in tmpdir, the corresponding convolver
        will be set to off, to avoid trying to use a wrong or non-existing
        file (used for startup, when the files are not yet created)
        """
        if d:
            if list(sorted(d.keys())) != self.parameterlist:
                raise ValueError("Guitarix Settings: list of parameters differ from saved")
            for n in "jconv", "jconv_mono":
                if d[n+".convolver"]["jconv.IRDir"] == tmpdir:
                    d[n+".on_off"] = 0
            l = []
            for p in self.parameterlist:
                if p == "system.current_preset":
                    preset = d[p]
                elif p == "system.current_bank":
                    bank = d[p]
                l += [p, d[p]]
            self.sock.notify("setpreset", [bank, preset])
            self.sock.notify("set", l)
        else:
            d = self.read_params()
        self.current_params = d

    def read_params(self):
        self.sock.call("get", self.parameterlist)
        return self.sock.receive().result

    def check_changed(self):
        old = self.current_params
        self.current_params = self.read_params()
        return self.current_params != old

    def set_convolver_ir(self, fname, ir=None, gaincor=False):
        if ir is None:
            ir = read_sndfile(open_sndfile(fname), channel=-2)
        stereo = ir.shape[1] == 2
        jname = self.get_jname(stereo)
        if gaincor:
            g = np.sqrt(np.sum(ir*ir))
            if g != 0.0:
                g = 1/g
            gaincor = 1
        else:
            g = 1.0
            gaincor = 0
        fname = os.path.abspath(fname)
        d = {
            'jconv.IRFile': os.path.basename(fname),
            'jconv.IRDir': os.path.dirname(fname),
            'jconv.Gain': g,
            'jconv.Length': len(ir),
            'jconv.GainCor': gaincor,
            'jconv.Offset': 0,
            'jconv.Delay': 0,
            'jconv.gainline': [[0, 0], [len(ir)-1, 0]],
            }
        l =  [
            jname+".convolver", d,
            jname+".on_off", 1,
            jname+".balance", 0,
            jname+".gain", 0,
            jname+".wet_dry", 100,
            ]
        if stereo:
            l += [ jname+".diff_delay",  0 ]
        self.sock.notify("set", l)
        self.current_params = self.read_params()

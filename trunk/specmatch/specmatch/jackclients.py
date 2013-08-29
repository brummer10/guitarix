#! /usr/bin/python
# -*- coding: utf-8 -*-

import os, gtk, subprocess, jackx, signal
import numpy as np

class JackRecord(object):

    pgm = "jack-stdout"
    _available = None

    def __init__(self, rate, capture, start=None, over=None):
        self.rate = rate
        self.jack_capture = capture
        self.notify_start = start
        self.notify_over = over

    def readbuf(self):
        s = self.p.stdout.read(self.N*4)
        if not s:
            raise RuntimeError
        return np.fromstring(s, dtype=np.float32)

    @classmethod
    def available(cls):
        if cls._available is None:
            cls._available = cls._get_available()
        return cls._available

    @classmethod
    def _get_available(cls):
        for p in os.path.defpath.split(os.pathsep):
            if os.path.exists(os.path.join(p, cls.pgm)):
                return True
        return False

    def start(self):
        cmd = [self.pgm, "--encoding", "floating-point", "--quiet", self.jack_capture]
        self.N = 1024
        threshold_in_DB = -40
        hyst_in_DB = -10
        start_thresh = 10**(threshold_in_DB/10)
        stop_thresh = 10**((threshold_in_DB+hyst_in_DB)/10)
        silent_limit = (1.0*self.rate)/self.N # 1 second of silence
        def check():
            while gtk.events_pending():
                gtk.main_iteration(False)
        try:
            self.p = subprocess.Popen(cmd, stdout=subprocess.PIPE)
            # wait for signal
            while True:
                check()
                a = self.readbuf()
                if np.sum(a*a) > start_thresh*self.N:
                    break
            if self.notify_start:
                self.notify_start()
            # record until silence
            silent_cnt = 0
            while True:
                check()
                b = self.readbuf()
                if self.notify_over and max(abs(b)) > 1.0-1e-4:
                    self.notify_over()
                if np.sum(b*b) < stop_thresh*self.N:
                    silent_cnt += 1
                    if silent_cnt > silent_limit:
                        break
                else:
                    silent_cnt = 0
                a = np.append(a, b)
            self.stop()
            a = a[:-int((silent_limit-1)*self.N)]
            r = np.empty((len(a),1))
            r[:,0] = a
            return r
        except RuntimeError:
            return None

    def stop(self):
        self.p.send_signal(signal.SIGINT)
        self.p.wait()


def jack_guitarix_processor(indata, guitarix_amp, guitarix_fx, stereo):
    channels = 2 if stereo else 1
    thisname = "specproc"
    client = jackx.Client(thisname)
    inport = guitarix_amp+":in_0"
    if stereo:
        client.register_port("in_0", jackx.IsInput)
        client.register_port("in_1", jackx.IsInput)
        outportL = guitarix_fx+":out_0"
        outportR = guitarix_fx+":out_1"
    else:
        client.register_port("in", jackx.IsInput)
        outport = guitarix_amp+":out_0"
    client.register_port("out", jackx.IsOutput)
    N = client.get_buffer_size()
    Sr = float(client.get_sample_rate())
    s = np.zeros((1,N), dtype=np.float32)
    outbuf = np.empty((channels,N), dtype=np.float32)
    inbuf = np.empty((1,N), dtype=np.float32)
    client.activate()
    if stereo:
        client.connect(outportL, thisname+":in_0")
        client.connect(outportR, thisname+":in_1")
    else:
        client.connect(outport, thisname+":in")
    client.connect(thisname+":out", inport)
    try:
        client.freewheel(True)
        # prepend half a second of silence
        for i in range(int((0.5*Sr)/N)):
            client.process(s, outbuf)
        outdata = np.empty((channels,0), dtype=np.float32)
        inbuf[0] = indata[:N,0]
        client.process(inbuf, outbuf)
        i = N
        while i <= len(indata)-N:
            inbuf[0] = indata[i:i+N,0]
            client.process(inbuf, outbuf)
            outdata = np.append(outdata, outbuf, axis=1)
            i += N
        if i < len(indata):
            s = np.zeros((1,N), dtype=np.float32)
            s[0,:len(indata)-i] = indata[i:,0]
            client.process(s, outbuf)
            outdata = np.append(outdata, outbuf, axis=1)
        # append half a second of silence
        s = np.zeros((1,N), dtype=np.float32)
        for i in range(int((0.5*Sr)/N)):
            client.process(s, outbuf)
    finally:
        client.freewheel(False)
    client.disconnect(thisname+":out", inport)
    if stereo:
        client.disconnect(outportL, thisname+":in_0")
        client.disconnect(outportR, thisname+":in_1")
    else:
        client.disconnect(outport, thisname+":out")
    client.deactivate()
    #outdata = outdata./(np.amax(abs(outdata))*1.01)
    return outdata.T


class JackPlayer(object):

    def __init__(self, volume_min_db=60):
        self.volume_min_db = volume_min_db
        try:
            jackx.attach("spec")
        except jackx.NotConnectedError:
            d = gtk.MessageDialog(None, 0, gtk.MESSAGE_ERROR, gtk.BUTTONS_OK,
                                  u"Jack daemon not running (can't connect)")
            res = d.run()
            d.destroy()
            raise SystemExit(1)
        self.clientname = jackx.get_client_name()
        self.sample_rate = float(jackx.get_sample_rate())
        jackx.register_port("out_1", jackx.IsOutput)
        jackx.register_port("out_2", jackx.IsOutput)
        a = np.zeros((0,2))
        self.set_a_b(a,a)
        jackx.activate()

    def check_for_port(self, pat):
        return jackx.get_ports(pat)

    def get_input_terminals(self):
        return [(p, jackx.get_port_short_name(p))
                for p in jackx.get_ports("", ".*audio.*", jackx.IsOutput|jackx.IsTerminal|jackx.IsPhysical)]

    def set_connections(self, ports):
        for p in ports[0]:
            jackx.connect("spec:out_1", p)
        for p in ports[1]:
            jackx.connect("spec:out_2", p)

    def get_connections(self):
        return [jackx.get_connections("%s:out_%d" % (self.clientname, i)) for i in 1, 2]

    def get_sample_rate(self):
        return self.sample_rate

    def set_a_b(self, a, b):
        jackx.set_a_b(a, b)

    def switch_a_b(self, val):
        jackx.switch_a_b(val)

    def get_position(self):
        return jackx.get_position()

    def set_position(self, v):
        jackx.set_position(v)

    def set_volume(self, v):
        jackx.a_b_volume(10**(((v-1)*self.volume_min_db)/20))

    def loop(self):
        jackx.enable(True)

    def stop(self):
        jackx.enable(False)

    def __del__(self):
        try:
            jackx.deactivate()
            jackx.detach()
        except jackx.NotConnectedError:
            pass

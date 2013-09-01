#! /usr/bin/python
# -*- coding: utf-8 -*-
#

import gtk, glib, os, pkg_resources, json, argparse
import numpy as np
import numpy.fft as fft
import matplotlib;
if matplotlib.get_backend() != "GTKAgg":
    matplotlib.use("GTKAgg")
import matplotlib.pyplot as plt
from guitarix import Guitarix
from jackclients import JackRecord, JackPlayer, jack_guitarix_processor
from spectrum import CalcIR, fftfreq2, fft2spectrum, SmoothSpectrumSpline, clipdb
from audiofiles import open_sndfile, write_sndfile, read_sndfile, wav_format_only

class FileDialog(object):

    def __init__(self, set_file, get_file, nr, create, audio=True):
        self.set_file = set_file
        self.get_file = get_file
        self.nr = nr
        self.create = create
        self.audio = audio

    def __call__(self, o=None):
        a = gtk.FILE_CHOOSER_ACTION_SAVE if self.create else gtk.FILE_CHOOSER_ACTION_OPEN
        self.w = gtk.FileChooserDialog(
            action=a,
            buttons=(gtk.STOCK_CANCEL,gtk.RESPONSE_CANCEL,gtk.STOCK_OPEN,gtk.RESPONSE_OK))
        f = gtk.FileFilter()
        if self.audio:
            if wav_format_only:
                f.add_pattern("*.wav")
                f.set_name("WAV Files")
            else:
                f.add_mime_type("audio/*")
                f.add_pattern("*.raw")
                f.set_name("Audio Files")
        else:
            f.add_pattern("*.specmatch")
            f.set_name("Project Files")
        self.w.add_filter(f)
        f = gtk.FileFilter()
        f.set_name("All Files")
        self.w.add_filter(f)
        n = self.get_file(self.nr)
        if n:
            if n.endswith("/"):
                self.w.set_current_folder(n)
            else:
                self.w.set_filename(n)
        if self.w.run() == gtk.RESPONSE_OK:
            self.set_file(self.nr, self.w.get_filename())
        self.w.destroy()


class DisplayStatus(object):

    def __init__(self, widget):
        self.widget = widget
        self.stack = []
        self.default = ""

    def set_default(self, s):
        self.default = s
        if not self.stack:
            self.disp(s)

    def disp(self, s):
        self.widget.set_text(s)
        while gtk.events_pending():
            gtk.main_iteration(False)

    def __call__(self, s):
        if not self.stack:
            self.widget.get_toplevel().set_sensitive(False)
        self.stack.append(s)
        self.disp(s)

    def clear(self):
        if self.stack:
            self.stack.pop()
        if self.stack:
            s = self.stack[-1]
        else:
            self.widget.get_toplevel().set_sensitive(True)
            s = self.default
        self.disp(s)

def format_time(v):
    if v is None:
        return ""
    m = int(v / 60)
    return "%02d:%04.1f" % (m, v - m*60)

class SpecWindow(object):

    def __init__(self, guitarix, jackplayer, args):
        self.guitarix = guitarix
        self.jackplayer = jackplayer
        self.fixed_samplerate = args.samplerate
        self.sound_outfile = args.soundfile
        self.orig_ir = args.orig_ir
        self.processed = args.processed
        spec_file = args.specfile
        self.builder = gtk.Builder()
        self.builder.add_from_file(
            pkg_resources.resource_filename(__name__, "specmatch.glade"))
        g = self.builder.get_object
        self.volume_button = gtk.VolumeButton()
        self.volume_button.show()
        g("soundbox").pack_start(self.volume_button, 0, 0)

        self.convolver_box = g("convolver_box")
        self.convolver_label = g("convolver_label")
        if not guitarix:
            self.convolver_label.hide()
            self.convolver_box.hide()
        if not jackplayer:
            g("record").hide()
            g("record_box").hide()
            g("sound_box").hide()
            g("audition_label").hide()
            g("audition_box").hide()
        if not JackRecord.available():
            g("record_box").hide()

        # files
        self.original_sound = g("original_sound")
        self.original_sound_name = g("original_sound_name")
        self.recorded_guitar = g("recorded_guitar")
        self.recorded_guitar_name = g("recorded_guitar_name")
        self.guitarix_output = g("guitarix_output")

        # other buttons
        self.display_time = g("display_time")
        self.display_time.connect("clicked", self.on_display_time)
        self.display_freq = g("display_freq")
        self.display_freq.connect("clicked", self.on_display_freq)
        self.generate_ir = g("generate_ir")
        self.generate_ir.connect("clicked", self.on_generate_ir)
        self.play = g("play")
        self.play.connect("toggled", self.on_play)
        self.a_b = g("a_b")
        self.a_b.connect("toggled", self.on_a_b)
        g("close").connect("clicked", lambda o: self.window.destroy())
        self.audition = g("audition")
        self.audition.connect("toggled", self.on_audition)
        self.audition_time = g("audition_time")
        self.record = g("record")
        self.record.connect("toggled", self.on_record)
        self.recorder = None
        g("open").connect("clicked",FileDialog(self.set_file, self.get_file, 2, True, False))
        self.deploy = g("deploy")
        self.deploy.connect("clicked",FileDialog(self.set_file, self.get_file, 3, True))

        # entry elements
        self.ir_size = g("ir_size")
        self.ir_size.connect("value-changed", self.on_ir_size)
        self.ir_cut = g("ir_cut")
        self.ir_cut.connect("value-changed", self.on_ir_cut)
        self.range_from_input = g("range_from")
        self.range_from_input.connect("changed", self.on_range_changed, 0)
        self.range_from_input.connect("focus-out-event", self.on_range_focus_out, 0)
        self.range_to_input = g("range_to")
        self.range_to_input.connect("changed", self.on_range_changed, 1)
        self.range_to_input.connect("focus-out-event", self.on_range_focus_out, 1)
        self.channel_left = g("left")
        self.channel_right = g("right")
        self.channel_sum = g("sum")
        self.channel_stereo = g("stereo")
        self.channel_sum.set_active(True)
        self.channel_left.connect("toggled", self.on_channel, 0)
        self.channel_right.connect("toggled", self.on_channel, 1)
        self.channel_sum.connect("toggled", self.on_channel, -1)
        self.channel_stereo.connect("toggled", self.on_channel, -2)
        self.jconv_stereo = g("jconv_stereo")
        self.jconv_stereo.connect("toggled", self.on_convolver_toggled)
        self.channelbox = g("channelbox")
        self.channel_label = g("channel_label")
        self.display_smooth = g("display_smooth")

        # other
        self.window = g("SpecMatch")
        self.window.connect("destroy", self.on_destroy)
        self.status = g("status")
        self.volume_button.connect("value-changed", self.on_volume_changed)
        self.status_display = g("status")
        self.play_position = g("play_position")
        self.play_position.parent.connect("button-press-event", self.on_play_position_clicked)
        self.recording_status = g("recording_status")
        self.recording_clipping = None

        self.guitarix_dir = os.path.join(glib.get_user_config_dir(), "guitarix")
        self.guitarix_temp_dir = os.path.join(self.guitarix_dir, "temp")
        self.spec_filename = None
        self.original_sound_filename = None
        self.recorded_guitar_filename = None
        self.impulse_response_filename = os.path.join(self.guitarix_temp_dir, "ir.wav")
        self.original_sound_name.set_text("---")
        self.recorded_guitar_name.set_text("---")
        self.original_sound.connect("clicked", FileDialog(self.set_file, self.get_file, 0, False))
        self.recorded_guitar.connect("clicked", FileDialog(self.set_file, self.get_file, 1, True))

        if self.jackplayer:
            l = g("capture_store")
            for n in self.jackplayer.get_input_terminals():
                l.append(n)
        self.last_position = None
        self.timeout_id = None

        self.calc = CalcIR(DisplayStatus(self.status_display), self.get_sample_rate(),
                           self.process_guitarix, self.orig_ir, self.processed)

        fn = self.load_global_settings()
        if not spec_file:
            spec_file = fn
        if spec_file:
            self.load_startvalues(spec_file)
        else:
            FileDialog(self.set_file, self.get_file, 2, True, False)()
            if self.spec_filename is None:
                raise SystemExit(0)
        self.set_button_status()

        self.window.show()

    def get_sample_rate(self):
        if self.jackplayer:
            return self.jackplayer.get_sample_rate()
        return self.fixed_samplerate

    def recording_status_clipping(self):
        if self.recording_clipping:
            glib.source_remove(self.recording_clipping)
        else:
            self.recording_status.set_from_stock(gtk.STOCK_CUT, gtk.ICON_SIZE_BUTTON)
        def reset():
            self.recording_status_running(1)
            self.recording_clipping = None
            return False
        self.recording_clipping = glib.timeout_add(1500, reset)

    def recording_status_running(self, status=1):
        rs = self.recording_status
        if status == 0:
            rs.set_from_stock(gtk.STOCK_MEDIA_PAUSE, gtk.ICON_SIZE_BUTTON)
        elif status == 1:
            rs.set_from_stock(gtk.STOCK_MEDIA_RECORD, gtk.ICON_SIZE_BUTTON)
        else:
            if self.recording_clipping:
                glib.source_remove(self.recording_clipping)
            rs.clear()

    def stop_recorder(self):
        if self.recorder:
            self.recorder.stop()
            self.recorder = None

    def on_record(self, o):
        if o.get_active():
            rate = self.get_sample_rate()
            self.recorder = JackRecord(
                rate, self.get_capture_port(),
                self.recording_status_running, self.recording_status_clipping)
            self.recording_status_running(0)
            a = self.recorder.start()
            self.recording_status_running(-1)
            self.recorder = None
            if a is not None:
                if self.processed:
                    a = self.process_guitarix(a)
                write_sndfile(a, self.recorded_guitar_filename, rate, "pcm24")
                self.calc.recorded_sound = a
                self.set_button_status()
            o.set_active(False)
        else:
            self.stop_recorder()

    def process_guitarix(self, s, irfile=None):
        if not self.guitarix:
            return s
        stereo = self.jconv_stereo.get_active()
        if self.calc.a1.shape[1] == 2:
            stereo = True
        self.guitarix.ensure_convolver(stereo)
        if irfile:
            self.guitarix.set_convolver_ir(irfile, gaincor=False)
        try:
            self.guitarix.set_engine_on()
            return jack_guitarix_processor(
                s, self.guitarix.get_jack_amp_clientname(), self.guitarix.get_jack_fx_clientname(), stereo)
        finally:
            self.guitarix.set_convolver_state(1, stereo)
            self.guitarix.restore_engine_state()

    def display_audition_time(self):
        rate = self.get_sample_rate()
        pos, length, idx = self.jackplayer.get_position()
        spos = (self.calc.original_range[0] or 0.0) + pos / rate
        self.audition_time.set_text(format_time(spos))
        return True

    def on_range_changed(self, o, idx):
        s = o.get_text().replace(" ","")
        m, sep, sec = s.partition(":")
        if not sep:
            sec = m
            m = ''
        try:
            v = float(sec.replace(",","."))
            if m:
                v += int(m)*60
        except ValueError:
            v = None
        r = list(self.calc.original_range)
        r[idx] = v
        self.calc.original_range = r
        if self.audition.get_active():
            a = self.normalize_to_stereo(self.calc.a1)
            self.jackplayer.set_a_b(a,a)

    def on_range_focus_out(self, o, ev, idx):
        o.set_text(format_time(self.calc.original_range[idx]))
        return False

    def stop_player(self):
        self.jackplayer.stop()

    def on_audition(self, o):
        if o.get_active():
            if self.play.get_active():
                self.play.set_active(False)
            a = self.normalize_to_stereo(self.calc.a1)
            self.jackplayer.set_a_b(a,a)
            self.timeout_id = glib.timeout_add(100, self.display_audition_time)
            self.jackplayer.loop()
        else:
            if self.timeout_id:
                glib.source_remove(self.timeout_id)
                self.timeout_id = None
            self.jackplayer.stop()
            self.audition_time.set_text("")

    def get_capture_port(self):
        if not self.jackplayer:
            return self.saved_capture_port
        i = self.builder.get_object("capture").get_active()
        if i < 0:
            return None
        return self.builder.get_object("capture_store")[i][0]

    def set_capture_port(self, v):
        if not self.jackplayer:
            self.saved_capture_port = v
        for i, row in enumerate(self.builder.get_object("capture_store")):
            if row[0] == v:
                self.builder.get_object("capture").set_active(i)
                if JackRecord.available():
                    self.builder.get_object("record").set_sensitive(True)
                return True
        return False

    def load_global_settings(self):
        g = self.builder.get_object
        try:
            with open(os.path.join(self.guitarix_dir, "specmatch.js")) as fp:
                d = json.load(fp)
        except (IOError, ValueError, TypeError):
            d = {}
        self.volume_button.set_value(d.get("volume",0.8))
        g("plot_ir").set_active(d.get("plot_ir", True))
        g("plot_orig").set_active(d.get("plot_orig", True))
        g("plot_rec").set_active(d.get("plot_rec", True))
        g("plot_diff").set_active(d.get("plot_diff", True))
        self.display_smooth.set_active(d.get("display_smooth", True))
        g("log").set_active(d.get("log", True))
        g("lin").set_active(d.get("lin", False))
        g("display_expander").set_expanded(d.get("display_expander", False))
        conn = d.get("jack_playback", [["system:playback_1"], ["system:playback_2"]])
        if self.jackplayer:
            self.jackplayer.set_connections(conn)
        else:
            self.saved_connections = conn
        self.set_capture_port(d.get("jack_capture", "system:capture_1"))
        return d.get("spec_filename")

    def save_global_settings(self):
        g = self.builder.get_object
        if self.jackplayer:
            conn = self.jackplayer.get_connections()
        else:
            conn = self.saved_connections
        d = dict(spec_filename = os.path.abspath(self.spec_filename),
                 display_expander = g("display_expander").get_expanded(),
                 volume = self.volume_button.get_value(),
                 plot_ir = g("plot_ir").get_active(),
                 plot_orig = g("plot_orig").get_active(),
                 plot_rec = g("plot_rec").get_active(),
                 plot_diff = g("plot_diff").get_active(),
                 display_smooth = self.display_smooth.get_active(),
                 log = g("log").get_active(),
                 lin = g("lin").get_active(),
                 jack_playback = conn,
                 jack_capture = self.get_capture_port(),
                 )
        with open(os.path.join(self.guitarix_dir, "specmatch.js"),"w") as fp:
            json.dump(d, fp, indent=2, sort_keys=True)

    def change_file(self, spec_file):
        if self.spec_filename:
            self.save_specfile()
        self.load_startvalues(spec_file)

    def load_startvalues(self, spec_file):
        if os.path.splitext(spec_file)[1] != ".specmatch":
            spec_file += ".specmatch"
        initial = not self.spec_filename
        self.spec_filename = spec_file
        g = self.builder.get_object
        self.calc.status.set_default("File: %s" % spec_file)
        self.window.set_title(
            "SpecMatch: %s" % os.path.splitext(os.path.split(spec_file)[1])[0])
        d = {}
        try:
            with open(spec_file) as fp:
                d = json.load(fp)
        except IOError as e:
            if e.errno != 2: # no such file
                raise
            if not initial:
                return
        except ValueError:
            print "bad spec.. skipping"
            if not initial:
                return
        def set_file(nr, n):
            try:
                n = d[n]
            except KeyError:
                return
            if n is not None:
                self.set_file(nr, n)
        def set_range(w, v):
            if v is None:
                w.set_text("")
            else:
                w.set_text(format_time(v))
        set_file(0, "original_sound_filename")
        set_file(1, "recorded_guitar_filename")
        sz = d.get("ir_size",0)
        if sz:
            self.ir_size.set_value(sz)
        self.ir_cut.set_value(d.get("ir_cutoff", -80))
        r = d.get("original_range", (None,None))
        set_range(self.range_from_input, r[0])
        set_range(self.range_to_input, r[1])
        self.calc.original_mode = d.get("original_mode",-1)
        { 0: self.channel_left,
          1: self.channel_right,
         -1: self.channel_sum,
         -2: self.channel_stereo,
         }[self.calc.original_mode].set_active(True)
        gpar = d.get("guitarix_settings", {})
        if self.guitarix:
            try:
                self.guitarix.set_parameters(gpar, self.guitarix_temp_dir)
            except ValueError as e:
                d = gtk.MessageDialog(self.window, 0, gtk.MESSAGE_WARNING, gtk.BUTTONS_OK, unicode(e))
                d.run()
                d.destroy()
        else:
            self.saved_guitarix_parameters = gpar

    def save_specfile(self):
        g = self.builder.get_object
        if self.guitarix:
            gpar = self.guitarix.get_parameters()
        else:
            gpar = self.saved_guitarix_parameters
        d = dict(original_sound_filename = self.original_sound_filename,
                 recorded_guitar_filename = self.recorded_guitar_filename,
                 ir_size = self.calc.sz,
                 ir_cutoff = self.calc.cutoff,
                 original_range = self.calc.original_range,
                 original_mode = self.calc.original_mode,
                 guitarix_settings = gpar,
                 )
        with open(self.spec_filename,"w") as fp:
            json.dump(d, fp, indent=2, sort_keys=True)

    def on_destroy(self, o):
        self.stop_recorder()
        self.save_specfile()
        self.save_global_settings()
        gtk.main_quit()

    def on_ir_size(self, o):
        self.calc.sz = self.ir_size.get_value_as_int()

    def on_convolver_toggled(self, o):
        self.calc.a2 = None

    def on_ir_cut(self, o):
        self.calc.cutoff = self.ir_cut.get_value()

    def on_channel(self, o, mode):
        self.calc.original_mode = mode
        self.convolver_box.set_sensitive(mode != -2)

    def set_file(self, nr, name):
        if nr == 0:
            f = open_sndfile(name)
            rate = self.get_sample_rate()
            if rate != f.samplerate:
                raise ValueError("%s: rate missmatch (%d / %d)" % (name, f.samplerate, rate))
            self.original_sound_filename = name
            self.original_sound_name.set_text(name)
            self.calc.original_sound_file = f
        elif nr == 1:
            if os.path.exists(name):
                f = open_sndfile(name)
                rate = self.get_sample_rate()
                if rate != f.samplerate:
                    raise ValueError("%s: rate missmatch (%d / %d)" % (fname, f.samplerate, rate))
                a = f.read_frames(f.nframes)
                if len(a.shape) == 1:
                    a = a.reshape((len(a), 1))
                self.calc.recorded_sound = a
                self.ir_size.set_range(0, len(a))
                self.ir_size.set_increments(1, 10)
                if self.ir_size.get_value_as_int() == 0:
                    self.ir_size.set_value(min(3500, len(a)))
            self.recorded_guitar_filename = name
            self.recorded_guitar_name.set_text(name)
        elif nr == 2:
            self.change_file(name)
            return
        elif nr == 3:
            self.invalidate_on_change()
            if not os.path.splitext(name)[1]:
                name += ".wav"
            write_sndfile(self.calc.ir, name, self.get_sample_rate(), "pcm24")
            if self.guitarix:
                self.guitarix.set_convolver_ir(name, self.calc.ir)
            return
        self.set_button_status()

    def get_file(self, nr):
        if nr == 0:
            return self.original_sound_filename
        elif nr == 1:
            return self.recorded_guitar_filename
        elif nr == 2:
            return self.spec_filename
        elif nr == 3:
            return os.path.join(self.guitarix_dir, "IR", "")

    def set_button_status(self):
        orig_fn = self.original_sound_filename is not None and os.path.exists(self.original_sound_filename)
        rec_fn = self.recorded_guitar_filename is not None and os.path.exists(self.recorded_guitar_filename)
        for p in self.audition, self.range_from_input, self.range_to_input:
            p.set_sensitive(orig_fn)
        gen = orig_fn and self.calc.original_sound_file.channels == 2
        for p in self.channel_label, self.channelbox, self.convolver_label, self.convolver_box:
            p.set_visible(gen)
        gen = orig_fn and rec_fn
        for p in self.play, self.a_b:
            p.set_sensitive(gen)
        gen = orig_fn and rec_fn
        for p in self.generate_ir, self.display_time, self.display_freq, self.ir_size, self.deploy:
            p.set_sensitive(gen)

    def display_position_text(self, idx):
        legend = "Original", "Guitarix"
        if self.last_position is None:
            s = "[%s] --.-" % legend[idx]
        else:
            s = "[%s] %4.1f" % (legend[idx], self.last_position)
        self.play_position.set_text(s)

    def invalidate_on_change(self):
        if not self.guitarix:
            return
        if self.guitarix.check_changed():
            self.calc.invalidate_guitarix_output()

    def on_generate_ir(self, o):
        playing = self.play.get_active()
        if playing:
            self.play.set_active(False)
        self.invalidate_on_change()
        self.calc.sound  # side-effect
        if playing:
            self.play.set_active(True)
        rate = self.get_sample_rate()
        write_sndfile(self.calc.ir, self.impulse_response_filename, rate, "pcm24")
        if self.guitarix:
            self.guitarix.set_convolver_ir(self.impulse_response_filename, self.calc.ir)
        if self.sound_outfile:
            write_sndfile(self.calc.sound, self.sound_outfile, rate, "pcm24")

    def display_position(self, ):
        pos, length, idx = self.jackplayer.get_position()
        frac = float(pos)/length
        self.play_position.set_fraction(max(0.0, min(1.0, frac)))
        self.last_position = float(pos)/self.get_sample_rate()
        self.display_position_text(idx)
        return True

    def on_play_position_clicked(self, o, ev):
        left_margin = 2
        pos, length, idx = self.jackplayer.get_position()
        if length:
            self.jackplayer.set_position(
                int(length * (ev.x - left_margin) /
                    (self.play_position.get_allocation().width - left_margin)))
            if not self.play.get_active() and self.calc.sound_ready():
                self.play.set_active(True)
        return True

    def on_volume_changed(self, o, v):
        if self.jackplayer:
            self.jackplayer.set_volume(v)

    @staticmethod
    def normalize_to_stereo(a):
        a /= np.amax(a)
        if a.shape[1] == 1:
            a = np.append(a, a, axis=1)
        return a

    def on_play(self, o):
        if o.get_active():
            if self.audition.get_active():
                self.audition.set_active(False)
            self.jackplayer.set_a_b(
                self.normalize_to_stereo(self.calc.a1),
                self.normalize_to_stereo(self.calc.sound))
            self.timeout_id = glib.timeout_add(100, self.display_position)
            self.jackplayer.loop()
        else:
            if self.timeout_id:
                glib.source_remove(self.timeout_id)
                self.timeout_id = None
            self.jackplayer.stop()
            self.play_position.set_fraction(0)

    def on_a_b(self, o):
        v = o.get_active()
        self.jackplayer.switch_a_b(v)
        self.display_position_text(v)

    @staticmethod
    def plot_fft(ax, f, rate, **kw):
        y = fft2spectrum(f)
        x = abs(fft.fftfreq(len(f), 1.0/rate)[:len(y)])
        i = np.searchsorted(x, 20) # index for first freq >= 20 Hz
        label = kw.pop("label", None)
        l = ax.semilogx(x[i:], y[i:], **kw)
        if label is not None:
            l[0].set_label(label)

    def plot_orig_ir(self, ax, rate, **kw):
        if 'label' not in kw:
            kw['label'] = os.path.splitext(os.path.split(self.orig_ir)[1])[0]
        a = read_sndfile(open_sndfile(self.orig_ir))
        n = max(2**14, len(a))
        self.plot_fft(ax, fft.fft(a, n, axis=0), rate, **kw)

    def diff_plot(self, valid, ax, x, fd, fmt, color, label=None):
        idx = self.calc.ir_smoother.get_indexlist(x, 0, valid)
        if len(idx) == len(x):
            return
        if len(idx) > 0:
            x = x.copy()
            x[idx] = "nan"
            fd = fd.copy()
            fd[idx] = "nan"
        l = ax.semilogx(x, fd, fmt, color=color)
        if label is not None:
            l[0].set_label(label)

    def on_display_freq(self, o):
        self.calc.status("generating plot")
        g = self.builder.get_object
        plot_ir = g("plot_ir").get_active()
        plot_orig = g("plot_orig").get_active()
        plot_rec = g("plot_rec").get_active()
        plot_diff = g("plot_diff").get_active()
        display_smooth = self.display_smooth.get_active()
        self.invalidate_on_change()
        rate = self.get_sample_rate()
        if plot_ir or plot_diff:
            n = max(2**16, len(self.calc.ir))
            ir_fft = fft.fft(self.calc.ir, n, axis=0)
        freq = fftfreq2(len(self.calc.f1), 1.0/rate)
        if display_smooth:
            x = np.logspace(np.log10(20), np.log10(rate/2), 1000)
        else:
            x = freq
        if plot_orig or (plot_diff and not self.orig_ir):
            f1 = fft2spectrum(self.calc.f1)
            if display_smooth:
                f1 = SmoothSpectrumSpline(freq, f1, rate)(x)
        if plot_rec or (plot_diff and not self.orig_ir):
            f2 = fft2spectrum(self.calc.f2)
            if display_smooth:
                f2 = SmoothSpectrumSpline(freq, f2, rate)(x)
        fig = plt.figure("mainplot")
        fig.canvas.set_window_title('Spec - IR Frequency Domain')
        fig.clear()
        ax = fig.add_subplot(111)
        if plot_orig:
            ax.semilogx(x, f1, color='green')[0].set_label("Original")
        if plot_rec:
            ax.semilogx(x, f2, color='blue')[0].set_label("Recorded")
        if plot_diff:
            if self.orig_ir:
                self.plot_orig_ir(ax, rate, linestyle='--', color='red')
            else:
                fd = f1-f2
                self.diff_plot(True, ax, x, fd, ':', "red")
                self.diff_plot(False, ax, x, fd, '--', "red", "Difference")
        if plot_ir:
            self.plot_fft(ax, ir_fft, rate, color='black', label="IR [%d frames]" % len(self.calc.ir))
        ax.legend(loc='best')
        self.calc.status.clear()

    def on_display_time(self, o):
        self.calc.status("generating plot")
        self.invalidate_on_change()
        f = self.calc.ir
        x = np.arange(len(f))/self.get_sample_rate()
        fig = plt.figure("mainplot")
        fig.canvas.set_window_title('Spec - IR Time Domain') 
        fig.clear()
        ax = fig.add_subplot(111)
        f = f / np.amax(abs(f))
        if self.builder.get_object("log").get_active():
            l = ax.plot(x, 20*np.log10(abs(clipdb(f,-100))))
        else:
            l = ax.plot(x, f)
        if len(l) == 1:
            l[0].set_label("IR [%d frames]" % len(f))
        else:
            l[0].set_label("IR left")
            l[1].set_label("IR right")
        ax.legend(loc='best')
        self.calc.status.clear()


def main():
    parser = argparse.ArgumentParser(
        description='Calculate an IR to match a spectrum')
    parser.add_argument("specfile", nargs="?", help="project file")
    parser.add_argument("orig_ir", nargs="?", help="debug: IR to reproduce")
    parser.add_argument("--no-guitarix", action="store_true",
                        help="run without connecting to Guitarix")
    parser.add_argument("--no-jack", action="store_true",
                        help="run without connecting to jackd, implies --no-guitarix")
    parser.add_argument("--samplerate", metavar="SR", type=float, default=44100.0,
                        help="set samplerate (when --no-jack), default: %(default)s")
    parser.add_argument("-p", "--processed", action="store_true",
                        help="input file doesn't processing by Guitarix; when Recording"
                        " capture Guitarix output instead of dry guitar")
    parser.add_argument("--soundfile", metavar="name",
                        help="debug: writeout input file convoluted with calculated IR")
    args = parser.parse_args()
    jackplayer = None if args.no_jack else JackPlayer()
    guitarix = None if args.no_guitarix or args.no_jack else Guitarix(jackplayer)
    matplotlib.interactive(True)
    SpecWindow(guitarix, jackplayer, args)
    gtk.main()

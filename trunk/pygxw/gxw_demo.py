import sys, os, ctypes
basedir = os.path.dirname(sys.argv[0])
try:
    ctypes.CDLL('libgxw.so')
except OSError:
    if sys.argv[1:2] == ['--no-spawn--']:
        raise
    os.environ['LD_LIBRARY_PATH'] = os.path.join(basedir, '../build/libgxw/gxw')
    print("restart with LD_LIBRARY_PATH=%s" % os.environ['LD_LIBRARY_PATH'])
    os.execl(sys.executable, sys.executable, sys.argv[0], '--no-spawn--', *sys.argv[1:])
    raise
os.environ['GI_TYPELIB_PATH'] = os.path.join(basedir, '../build/pygxw')
import gi
gi.require_version('Gxw','0.1')
from gi.repository import Gxw, Gtk, Gdk
Gxw.init()

cssdef = b"""
"""

def lm(db):
    if db < -70.0:
        df = 0.0
    elif db < -60.0:
        df = (db + 70.0) * 0.25
    elif db < -50.0:
        df = (db + 60.0) * 0.5 + 2.5
    elif db < -40.0:
        df = (db + 50.0) * 0.75 + 7.5
    elif db < -30.0:
        df = (db + 40.0) * 1.5 + 15.0
    elif db < -20.0:
        df = (db + 30.0) * 2.0 + 30.0
    elif db < 6.0:
        df = (db + 20.0) * 2.5 + 50.0
    else:
        df = 115.0
    return df/115.0

def demo(w):
    v = Gtk.VBox()
    #h = MyBox()
    h = Gxw.PaintBox()
    h.props.paint_func = "amp_expose"
    #h = Gtk.HBox()
    h.props.border_width = 10
    h.props.spacing = 10
    w.add(v)

    r = Gxw.Wheel(adjustment=Gtk.Adjustment(
        value=0, lower=-999, upper=999, step_increment=0.1, page_increment=10))
    r.props.show_value = True
    r.props.value_position = Gtk.PositionType.LEFT
    h.pack_start(r,0,0,0)

    if True:
        for base in "led", "switch", "switchit", "minitoggle", "button":
            b = Gxw.Switch(base_name=base)
            #b = Gxw.ToggleImage()
            #print b.get_has_window()
            #b.props.base_name = base+"_off"
            h.pack_start(b,0,0,padding=0)
        h.pack_start(Gtk.CheckButton(), 0, 0, 0)

    v.add(h)

    h = Gtk.HBox()
    h.set_spacing(20)
    v.add(h)

    adj = Gtk.Adjustment(
        value=0, lower=-1, upper=1, step_increment=0.01, page_increment=0.1)

    r = Gxw.BigKnob(adjustment=adj)
    r.props.show_value = True
    #r.props.value_position = Gtk.POS_LEFT
    h.add(r)

    r = Gxw.SmallKnob(adjustment=adj)
    r.props.show_value = True
    r.props.value_position = Gtk.PositionType.RIGHT
    h.add(r)

    r = Gxw.ValueDisplay(adjustment=adj)
    h.add(r)

    r = Gxw.HSlider(adjustment=adj)
    r.props.show_value = True
    r.props.value_position = Gtk.PositionType.LEFT
    h.add(r)

    r = Gxw.MiniSlider(adjustment=adj)
    h.add(r)

    r = Gxw.EQSlider(adjustment=adj)
    h.add(r)

    r = Gxw.EQSlider(adjustment=adj)
    r.props.show_value = True
    h.add(r)

    r = Gxw.VSlider(adjustment=adj)
    h.add(r)

    r = Gxw.VSlider(adjustment=adj)
    r.props.show_value = True
    h.add(r)

    r = Gxw.Selector()
    model = Gtk.ListStore(str)
    for s in "Amp 1", "Amp 2", "Amp 3":
        model.append((s,))
    r.props.model = model
    h.add(r)

    r = Gxw.PortDisplay(adjustment=adj)
    r.props.show_value = False
    h.add(r)

    orientation = Gtk.Orientation.HORIZONTAL
    #orientation = Gtk.Orientation.VERTICAL
    h1 = Gtk.Box(orientation=not orientation)
    h1.set_size_request(200, -1)
    h.add(h1)

    r = Gxw.FastMeter(orientation=orientation, hold=30)
    def set_meter(o, r=r):
        v = o.get_value()
        r.set(v)
    adj.connect('value-changed', set_meter)
    h1.add(r)

    global ms
    r = ms = Gxw.MeterScale()
    r.props.tick_pos = Gxw.TickPosition.BOTH
    for p in -50, -40, -20, -30, -10, -3, 0, 4:
        r.add_mark(lm(p), str(p));
    h1.add(r)

    r = Gxw.FastMeter(orientation=orientation)
    r.set(0.7)
    h1.add(r)

    h = Gtk.HBox()
    h.set_spacing(20)
    r_before = None
    for i in range(3):
        r = Gxw.RadioButton()
        r.join_group(r_before)
        r_before = r
        #r = Gtk.RadioButton(r)
        #r.props.image = Gxw.ToggleImage("minitoggle")
        #r.props.draw_indicator = 0
        r.props.base_name = "minitoggle"
        r.set_label("bla %d" % i)
        h.pack_start(r,0,0,0)
    #print list(r.props)
    v.add(h)

itheme = Gtk.IconTheme
deftheme = itheme.get_default()
deftheme.prepend_search_path(os.path.join(basedir, '../build/rcstyle'))
deftheme.prepend_search_path('../build/rcstyle/Guitarix')
style = Gtk.StyleContext()
provider = Gtk.CssProvider()
provider.load_from_path(os.path.join(basedir, '../build/rcstyles/gx_head_Guitarix.css'))
style.add_provider_for_screen(
    Gdk.Screen.get_default(),
    provider,
    Gtk.STYLE_PROVIDER_PRIORITY_APPLICATION
)
prov2 = Gtk.CssProvider()
prov2.load_from_data(cssdef)
style.add_provider_for_screen(
    Gdk.Screen.get_default(),
    prov2,
    Gtk.STYLE_PROVIDER_PRIORITY_APPLICATION+1
)
w = Gtk.Window()
demo(w)
w.show_all()

try:
    __IPYTHON__
except:
    w.connect("destroy",Gtk.main_quit)
    try:
        Gtk.main()
    except KeyboardInterrupt:
        print()

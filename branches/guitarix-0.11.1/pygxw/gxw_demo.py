import os, sys; sys.path.append("../build/default/pygxw")
import gxw, gtk

rc_style = """
pixmap_path "%s"

style "Wheel" {
  stock["wheel_back"] = {{"wheel_back.png"}}
  stock["wheel_fringe"] = {{"wheel_fringe.png"}}
  stock["wheel_pointer"] = {{"wheel_pointer.png"}}

}

style "ToggleImage" {
  stock["led_on"] = {{"led_on.png"}}
  stock["led_off"] = {{"led_off.png"}}
  stock["button_on"] = {{"button_on.png"}}
  stock["button_off"] = {{"button_off.png"}}
  stock["minitoggle_on"] = {{"minitoggle_on.png"}}
  stock["minitoggle_off"] = {{"minitoggle_off.png"}}
  stock["switchit_on"] = {{"switchit_on.png"}}
  stock["switchit_off"] = {{"switchit_off.png"}}
  stock["switch_on"] = {{"switch_on.png"}}
  stock["switch_off"] = {{"switch_off.png"}}
  GxRadioButton::indicator-size = 10
}

style "Switch" {
  xthickness = 0
  ythickness = 0
  GtkButton::inner-border = {0, 0, 0, 0}
  GtkButton::default-border = {0, 0, 0, 0}
  GtkButton::focus-line-width = 0
  GtkButton::focus-padding = 0
  GtkButton::interior-focus = 0
  bg[PRELIGHT] = { 0.03, 0.03, 0.03 }
}

style "BigKnob" {
  stock["knob"] = {{"knob1.png"}}
  GxKnob::arc-inset = 2
}

style "SmallKnob" {
  stock["smallknob"] = {{"smallknob1.png"}}
  GxKnob::arc-inset = 0
}

style "Slider" {
  stock["hslider"] = {{"slider.png"}}
  stock["minislider"] = {{"minislider.png"}}
  GtkRange::slider-width = 20
}

style "MiniSlider" {
  stock["minislider"] = {{"minislider.png"}}
  GtkRange::slider-width = 6
}

style "VSlider" {
  stock["vslider"] = {{"vslider.png"}}
  GtkRange::slider-width = 20
}

style "MiniSlider" {
  stock["minislider"] = {{"minislider.png"}}
  GtkRange::slider-width = 6
}

style "EqSlider" {
  stock["eqslider"] = {{"eqslider.png"}}
  GtkRange::slider-width = 5
}

class "GxWheel" style "Wheel"
class "GxToggleImage" style "ToggleImage"
class "GxSwitch" style "Switch"
class "GxBigKnob" style "BigKnob"
class "GxSmallKnob" style "SmallKnob"
class "GxHSlider" style "Slider"
class "GxMiniSlider" style "MiniSlider"
class "GxVSlider" style "VSlider"
class "GxEQSlider" style "EqSlider"
class "GxRadioButton" style "ToggleImage"
"""

rc_style = """
pixmap_path "%s"

style "BigKnob" {
  stock["bigknob"] = {{"knob3.png"}}
}

style "SmallKnob" {
  stock["smallknob"] = {{"smallknob5.png"}}
}

style "Switch" {
  xthickness = 0
  ythickness = 0
  GtkButton::focus-padding = 0
  bg_pixmap[NORMAL] = "<parent>"
}

style "ToggleImage" {
  bg_pixmap[NORMAL] = "<parent>"
}

style "PaintBox" {
    GxPaintBox::skin-gradient = {
        {    0, 65536, 65536, 65536, 58982},
        {52429, 58982, 58982, 65536, 58982},
        {65536, 52429, 52429, 58982, 32768}}
    GxPaintBox::paint-func = "rectangle_expose"
}


style "BigKnob" {
  stock["knob"] = {{"knob4.png"}}
  GxKnob::arc-inset = 2
}

class "GxBigKnob" style "BigKnob"
class "GxSmallKnob" style "SmallKnob"
class "GxSwitch" style "Switch"
class "GxPaintBox" style "PaintBox"
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
    v = gtk.VBox()
    #h = MyBox()
    h = gxw.PaintBox()
    h.props.paint_func = "amp_expose"
    #h = gtk.HBox()
    h.props.border_width = 10
    h.props.spacing = 10
    w.add(v)

    r = gxw.Wheel(gtk.Adjustment(0,-999,999,0.1,10))
    r.props.show_value = True
    r.props.value_position = gtk.POS_LEFT
    h.pack_start(r,0,0)

    if True:
        for base in "led", "switch", "switchit", "minitoggle", "button":
            b = gxw.Switch(base)
            #b = gxw.ToggleImage()
            #print b.get_has_window()
            #b.props.base_name = base+"_off"
            h.pack_start(b,0,0)

    v.add(h)

    h = gtk.HBox()
    h.set_spacing(20)
    v.add(h)

    adj = gtk.Adjustment(0,-1,1,0.01,0.1)

    r = gxw.BigKnob(adj)
    r.props.show_value = True
    #r.props.value_position = gtk.POS_LEFT
    h.add(r)

    r = gxw.SmallKnob(adj)
    r.props.show_value = True
    r.props.value_position = gtk.POS_RIGHT
    h.add(r)

    r = gxw.HSlider(adj)
    r.props.show_value = True
    r.props.value_position = gtk.POS_LEFT
    h.add(r)

    r = gxw.MiniSlider(adj)
    h.add(r)

    r = gxw.EQSlider(adj)
    h.add(r)

    r = gxw.EQSlider(adj)
    r.props.show_value = True
    h.add(r)

    r = gxw.VSlider(adj)
    h.add(r)

    r = gxw.VSlider(adj)
    r.props.show_value = True
    h.add(r)

    r = gxw.Selector()
    model = gtk.ListStore(str)
    for s in "Amp 1", "Amp 2", "Amp 3":
        model.append((s,))
    r.props.model = model
    h.add(r)

    h1 = gtk.HBox()
    h.add(h1)

    r = gxw.FastMeter()
    r.set(0.6)
    h1.add(r)

    global ms
    r = ms = gxw.MeterScale()
    r.props.tick_pos = gxw.TICK_BOTH
    for p in -50, -40, -20, -30, -10, -3, 0, 4:
        r.add_mark(lm(p), str(p));
    h1.add(r)

    r = gxw.FastMeter()
    r.set(0.7)
    h1.add(r)

    h = gtk.HBox()
    h.set_spacing(20)
    r = None
    for i in range(3):
        r = gxw.RadioButton(r)
        #r = gtk.RadioButton(r)
        #r.props.image = gxw.ToggleImage("minitoggle")
        #r.props.draw_indicator = 0
        r.props.base_name = "minitoggle"
        r.set_label("bla %d" % i)
        h.pack_start(r,0,0)
    #print list(r.props)
    v.add(h)


#gtk.rc_parse("../rcstyles/guitarix_default.rc")
gtk.rc_parse_string(rc_style % os.path.abspath("../libgxw"))
w = gtk.Window()
#b = gxw.ToggleImage()
#w.add(b)
demo(w)
w.show_all()

try:
    __IPYTHON__
except:
    w.connect("destroy",gtk.main_quit)
    gtk.main()

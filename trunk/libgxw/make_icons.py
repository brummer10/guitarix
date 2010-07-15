#
# python script to generate icons form base icons
# in the first place this can be seen as documentation
#
from gtk.gdk import (pixbuf_new_from_file, Pixbuf, INTERP_HYPER,
                     PIXBUF_ROTATE_CLOCKWISE)
pb = pixbuf_new_from_file

def sliders_knobs():
    pb("hslider.png").scale_simple(
        40, 6, INTERP_HYPER).save("minislider.png","png")

    pb("hslider.png").rotate_simple(
        PIXBUF_ROTATE_CLOCKWISE).flip(True).save("vslider.png","png")

    # shorten the original eqslider and store under the same name:
    #b = pb("eqslider.png")
    #b.subpixbuf(0,8,b.get_width(),105).save("eqslider.png","png")

    for i in range(6):
        f = "knob%d.png" % (i+1)
        pb(f).scale_simple(25,25,INTERP_HYPER).save("small"+f,"png")


def transform_pixbuf(p, dest_size, scale):
    dest = Pixbuf(p.props.colorspace, p.props.has_alpha,
                  p.props.bits_per_sample, dest_size, dest_size)
    dest.fill(0)
    s = dest_size * scale / max(p.get_width(), p.get_height())
    offset_x = int(round((dest_size - p.get_width() * s) / 2))
    offset_y = int(round((dest_size - p.get_height() * s) / 2))
    dest_width = int(round(min(dest_size-offset_x, s*p.get_width())))
    dest_height = int(round(min(dest_size-offset_y, s*p.get_height())))
    p.scale(dest, offset_x, offset_y, dest_width, dest_height, offset_x, offset_y, s, s, INTERP_HYPER)
    return dest

def make_glade_icon(f, name=None, offset_x=0, offset_y=0,
                    width=None, height=None, scale=1.0):
    p = pb(f)
    if not width:
        width = p.get_width()
    if not height:
        height = p.get_height()
    if offset_x != 0 or offset_y != 0 or width != p.get_width() or height != p.get_height():
        p = p.subpixbuf(offset_x, offset_y, width, height)
    if name is None:
        name = f
    else:
        name = name + ".png"
    pre = "glade-icons/hicolor/%s/actions/widget-gxwidgets-"
    ps = transform_pixbuf(p, 16, scale)
    ps.save(pre%"16x16"+name,"png")
    ps = transform_pixbuf(p, 22, scale)
    ps.save(pre%"22x22"+name,"png")

def glade_icons():
    make_glade_icon("gxknob.png","gxbigknob")
    make_glade_icon("gxknob.png","gxsmallknob",scale=0.7)
    make_glade_icon("gxhslider.png")
    make_glade_icon("gxvslider.png")
    make_glade_icon("gxswitch.png")
    make_glade_icon("gxeqslider.png", scale=0.9)
    make_glade_icon("gxminislider.png", scale=0.8)
    make_glade_icon("gxtoggleimage.png")
    make_glade_icon("gxwheel.png")
    make_glade_icon("gxpaintbox.png")
    make_glade_icon("gxradiobutton.png")
    make_glade_icon("gxfastmeter.png")
    make_glade_icon("gxselector.png")
    make_glade_icon("gxwaveview.png")
    make_glade_icon("gxtuner.png")
    make_glade_icon("gxiredit.png")

if __name__ == "__main__":
    #sliders_knobs()
    glade_icons()

#
# python script to generate icons form base icons
# in the first place this can be seen as documentation
#
from gtk.gdk import (pixbuf_new_from_file, INTERP_HYPER,
                     PIXBUF_ROTATE_CLOCKWISE)
pb = pixbuf_new_from_file

pb("slider.png").scale_simple(
    40, 6, INTERP_HYPER).save("minislider.png","png")

pb("slider.png").rotate_simple(
    PIXBUF_ROTATE_CLOCKWISE).flip(True).save("vslider.png","png")

# shorten the original eqslider and store under the same name:
#
#b = pb("eqslider.png")
#b.subpixbuf(0,8,b.get_width(),105).save("eqslider.png","png")

for i in range(6):
    f = "knob%d.png" % (i+1)
    pb(f).scale_simple(25,25,INTERP_HYPER).save("small"+f,"png")

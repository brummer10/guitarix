# -*- coding: utf-8 -*-
#
# Copyright (C) 2013, 2010 Hermann Meyer, Andreas Degert, Steve Poskitt
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#----------------------------------------------------------------
#


import sys, os, gtk, StringIO, glib
from pylab import *

from tube_transfer import *

class tube_transfer(gtk.Window):
    
    def on_exit(self, widget):
        self.destroy()
    
    def set_tube(self):
        tubelist = sorted(tubes.keys())
        for tube in tubelist:
            self.tube.append_text(tube)
    def get_param(self, c):
        self.table_size = c.table_size
        self.Ri_values = c.Ri_values
        self.scale6.set_value(c.Ri_values[0]/1e3)
        self.scale7.set_value(c.Ri_values[1]/1e3)
        self.scale1.set_value(c.Vp)
        self.scale2.set_value(c.Rp/1e3)
        self.scale3.set_value(c.Uin_min)
        self.scale4.set_value(c.Uin_max)
    
    def on_tube_changed(self,widget):
        c = Circuit(self.tube.get_active_text(), self.func.get_active_text())
        self.get_param(c)
        tubevalues = ""
        i = 0
        for n in c.used_names:
            tubevalues += " %s: %g " % (n, getattr(c, n))
            i +=1
            if i>5:
                 break
        self.labeltv.set_text(tubevalues)
    
    def set_func(self):
        self.func.append_text("triode")
        self.func.append_text("pentode")
        self.func.set_active(0)
    
    def set_param(self, c):
        self.Ri_values = (self.scale6.get_value()*1e3, self.scale7.get_value()*1e3)
        self.table_size = c.table_size
        c.Ri_values    = self.Ri_values
        c.Vp           = self.scale1.get_value()
        c.Rp           = self.scale2.get_value()*1e3
        c.Vi = linspace(self.scale3.get_value(),self.scale4.get_value(),self.table_size)
    
    def on_accuracy(self, widget):
        c = Circuit(self.tube.get_active_text(), self.func.get_active_text())
        self.set_param(c)
        old_stdout = sys.stdout
        capturer = StringIO.StringIO()
        sys.stdout = capturer
        c.display_accuracy()
        sys.stdout = old_stdout
        output = capturer.getvalue() #.replace('\n','')
        output = os.linesep.join([s for s in output.splitlines() if s])
        self.labelaccuracy.set_text(output)
    
    def on_plot(self, widget):
        self.sw.set_size_request (-1, 480)
        c = Circuit(self.tube.get_active_text(), self.func.get_active_text())
        self.set_param(c)
        myfile="/tmp/tube.png"
        if os.path.isfile(myfile):
            os.remove(myfile)
        title(self.tube.get_active_text())
        for Ri in c.Ri_values:
            Vp = c.FtubeV(c.Vi, Ri)
            plot(c.Vi, Vp, label="Ri=%dk " % (Ri/1e3))
        xlabel("Vik")
        ylabel("Vp")
        legend()
        axis
        savefig(myfile, dpi=80, bbox_inches=0)
        close()
        self.image.set_from_file(myfile)
        glib.idle_add(self.on_plot_finish)
    def on_plot_finish(self):
        self.sw.set_size_request (-1, -1)
        
    def on_vk0(self, widget):
        c = Circuit(self.tube.get_active_text(), self.func.get_active_text())
        self.set_param(c)
        old_stdout = sys.stdout
        capturer = StringIO.StringIO()
        sys.stdout = capturer
        args = [0, self.scale5.get_value()*1e3]
        c.show_vk0(args)
        sys.stdout = old_stdout
        output = capturer.getvalue().replace('\n','')
        c = Circuit(self.tube.get_active_text(), self.func.get_active_text())
        self.set_param(c)
        old_stdout = sys.stdout
        capturer = StringIO.StringIO()
        sys.stdout = capturer
        args = [1, self.scale5.get_value()*1e3]
        c.show_vk0(args)
        sys.stdout = old_stdout
        output1 = capturer.getvalue().replace('\n','')
        self.labelvk01.set_text("Ri(%s) Rk(%s) vk0(%s) \nRi(%s) Rk(%s) vk0(%s)" % 
            (self.scale7.get_value(),self.scale5.get_value() ,output, self.scale6.get_value(),self.scale5.get_value() ,output1) )
        
    def on_table(self, widget, argv):
        c = Circuit(self.tube.get_active_text(), self.func.get_active_text())
        self.set_param(c)
        old_stdout = sys.stdout
        capturer = StringIO.StringIO()
        sys.stdout = capturer
        c.write_tables(argv)
        sys.stdout = old_stdout
        output = capturer.getvalue()
        script_dir = sys.path[0]
        save_path = os.path.join(script_dir, 'gxtubes')
        if not os.path.exists(save_path):
            os.makedirs(save_path)
        
        f = open('%s/%s.cc' % (save_path,self.tube.get_active_text()), 'w')
        f.write(output)
        f.close
    
    def __init__(self, argv):        
        super(tube_transfer, self).__init__()
        self.set_default_size(550, 200)
        self.set_border_width(10)
        self.connect("destroy", lambda w: gtk.main_quit())
        self.set_title("Tube Calculator")
        vbox = gtk.VBox(False, 10)
        hbox = gtk.HBox(False, 8)
        hbox1 = gtk.HBox(False, 8)
        self.sw = gtk.ScrolledWindow()
        self.sw.set_shadow_type(gtk.SHADOW_ETCHED_IN)
        self.sw.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_AUTOMATIC)
        table = gtk.Table(2,9,False)
        table.set_col_spacings(5)
        label = gtk.Label("Tube")
        self.tube = gtk.combo_box_new_text()
        self.set_tube()
        label1 = gtk.Label("Type")
        self.func = gtk.combo_box_new_text()
        self.set_func()
        
        self.labelvk01 = gtk.Label("\n")
        self.labelvk01.set_selectable(True)
        self.labeltv = gtk.Label("")
        hbox1.pack_end(self.labeltv, False, False, 0)
        self.image = gtk.Image()
        self.sw.add_with_viewport(self.image)
        
        label2 = gtk.Label("Rk (*e3)")
        self.scale5 = gtk.SpinButton()
        self.scale5.set_range(0, 1e3)
        self.scale5.set_increments(0.01, 10)
        self.scale5.set_value(2.7)
        self.scale5.set_digits(2)
        
        label3 = gtk.Label("Vp")
        self.scale1 = gtk.SpinButton()
        self.scale1.set_range(0, 1e3)
        self.scale1.set_increments(0.01, 10)
        self.scale1.set_value(250)
        self.scale1.set_digits(2)
        
        label4 = gtk.Label("Rp (*e3)")
        self.scale2 = gtk.SpinButton()
        self.scale2.set_range(0, 1e3)
        self.scale2.set_increments(0.01, 10)
        self.scale2.set_value(100)
        self.scale2.set_digits(2)
        
        label5 = gtk.Label("Uin_min")
        self.scale3 = gtk.SpinButton()
        self.scale3.set_range(-1e3, 0)
        self.scale3.set_increments(1, 10)
        self.scale3.set_value(-5)
        self.scale3.set_digits(0)
        
        label6 = gtk.Label("Uin_max")
        self.scale4 = gtk.SpinButton()
        self.scale4.set_range(0, 1e3)
        self.scale4.set_increments(1, 10)
        self.scale4.set_value(5)
        self.scale4.set_digits(0)
        
        label7 = gtk.Label("Ri[0] (*e3)")
        self.scale6 = gtk.SpinButton()
        self.scale6.set_range(0, 1e3)
        self.scale6.set_increments(1, 10)
        self.scale6.set_value(68)
        self.scale6.set_digits(0)
        
        label8 = gtk.Label("Ri[1] (*e3)")
        self.scale7 = gtk.SpinButton()
        self.scale7.set_range(0, 1e3)
        self.scale7.set_increments(1, 10)
        self.scale7.set_value(250)
        self.scale7.set_digits(0)
        
        fun = gtk.Button("plot")
        fun.connect("clicked", self.on_plot)
        fun1 = gtk.Button("table")
        fun1.connect("clicked", self.on_table, argv)
        fun2 = gtk.Button("vk0")
        fun2.connect("clicked", self.on_vk0)
        self.labelaccuracy = gtk.Label("")
        fun3 = gtk.Button("accuracy")
        fun3.connect("clicked", self.on_accuracy)
        fun4 = gtk.Button("exit")
        fun4.connect("clicked", self.on_exit)
        
        self.tube.connect("changed", self.on_tube_changed)
        self.tube.set_active(2)
        
        table.attach_defaults(label,0,1,0,1)
        table.attach_defaults(label1,1,2,0,1)
        table.attach_defaults(label2,2,3,0,1)
        table.attach_defaults(label3,3,4,0,1)
        table.attach_defaults(label4,4,5,0,1)
        table.attach_defaults(label5,5,6,0,1)
        table.attach_defaults(label6,6,7,0,1)
        table.attach_defaults(label7,7,8,0,1)
        table.attach_defaults(label8,8,9,0,1)
        
        table.attach_defaults(self.tube,0,1,1,2)
        table.attach_defaults(self.func,1,2,1,2)
        table.attach_defaults(self.scale5,2,3,1,2)
        table.attach_defaults(self.scale1,3,4,1,2)
        table.attach_defaults(self.scale2,4,5,1,2)
        table.attach_defaults(self.scale3,5,6,1,2)
        table.attach_defaults(self.scale4,6,7,1,2)
        table.attach_defaults(self.scale6,7,8,1,2)
        table.attach_defaults(self.scale7,8,9,1,2)
        
        vbox.pack_start(table, False, False, 0)
        vbox.pack_start(hbox1, False, False, 0)
        vbox.pack_start(self.sw, True, True, 0)
        vbox.pack_end(hbox, False, False, 0)
        
        hbox.pack_end(fun4, False, False, 0)
        hbox.pack_end(fun3, False, False, 0)
        hbox.pack_end(fun, False, False, 0)
        hbox.pack_end(fun1, False, False, 0)
        hbox.pack_end(fun2, False, False, 0)
        hbox.pack_end(self.labelvk01, False, False, 0)
        hbox.pack_start(self.labelaccuracy, False, False, 0)
        self.add(vbox)
        self.show_all()

def main():
    tube_transfer(sys.argv[0])
    gtk.main()


if __name__ == "__main__":
    main()

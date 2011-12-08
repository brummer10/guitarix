"""Support module for gtkparasite

This module contains functions for use in the gtkparasite console. It
uses some python magic to keep it compact (worth several thousand
lines of C code :-D)

usage:

start guitarix with gtkparasite:

$ GTK_MODULES=gtkparasite PYTHONPATH=<gx tool dir> ../build/default/src/gx_head/guitarix

Then shift the divider at the bottom of the gtkparasite window up to
enlarge the console and load this module:

>>> from psup import *

You can use the python help: e.g. help(psup) or help(pstyle) and of
course "pydoc psup" from the command line.

Select interesting widgets (with inspect and / or selecting from the
list) and use the context menu to copy them to the shell. If you type
a prefix like "w = " you will get the complete line assigning the
widget to the variable.

pstyle() prints style attributes of a widget while going up the widget
hierarchy. You can specify all x_XX attributes directly, xs_XX
attributes have to be called with a widget state constant (numeric or
symbolic).

diffstyle() prints attributes and values which differ between two
widgets. The last printed line is the command you can use with
copy-and-paste to view the differing attributes with pstyle(). You
need to change the widget name if it's not called w.

ls_style() print all registered style properties.

To reload the module if you did some changes while gtkparasite is
running:

>>> reload(psup); from psup import *
"""
from itertools import chain, izip
from pprint import pprint
import gtk
from gtk import (STATE_NORMAL, STATE_ACTIVE, STATE_PRELIGHT,
                 STATE_SELECTED, STATE_INSENSITIVE)
from gtk import widget_class_list_style_properties
import psup # self import for easy reload

def print_table(rows, enum=False, reverse=False):
    """print table of rows, formatted with optimal column width
    rows:    list of equal length rows
    enum:    prepend row number if True
    reverse: print list in reverse order
    """
    if not rows:
        return
    n = len(rows[0])
    fmt = " ".join(n * ["%-*s"])
    if enum:
        n += 1
        fmt = "%*s: " + fmt
    m = [0] * n
    lines = []
    for i, row in enumerate(rows):
        if enum:
            row.insert(0, str(i))
        r = []
        for j, v in enumerate(row):
            v = str(v)
            m[j] = max(m[j], len(v))
            r.append(v)
        lines.append(r)
    if reverse:
        lines.reverse()
    for row in lines:
        print fmt % tuple(chain.from_iterable(izip(m, row)))

def ls_style(widget):
    """print all style properties of widget"""
    l = []
    for p in widget_class_list_style_properties(widget):
        n = p.name
        v = widget.style_get_property(n)
        if isinstance(v, gtk.Border):
            v = "Border(left=%d,right=%d,top=%d,bottom=%d)" % (v.left, v.right, v.top, v.bottom)
        elif isinstance(v, str):
            v = repr(v)
        elif isinstance(v, float):
            v = "%g" % v
        l.append((n, v))
    print_table(l)

def pstyle(widget, *args):
    """tabulate a list of styles for the widget hierarchy
    use any number or "xs_XX(..)"- or "x_XX"-accessors as args after widget

    example: pstyle(w, xs_bg[1], xs_fg[STATE_NORMAL], x_black)

    state argument for color state accessor builders (xs_XX(state)):
    STATE_NORMAL      (0)
    STATE_ACTIVE      (1)
    STATE_PRELIGHT    (2)
    STATE_SELECTED    (3)
    STATE_INSENSITIVE (4)
    """
    l = []
    while True:
        s = widget.style
        l.append([widget.get_name()] + [f(s) for f in args])
        widget = widget.get_parent()
        if not widget:
            break
    last = None
    l2 = []
    for row in reversed(l):
        if last and row[1:] == last[1:]:
            s = ""
        else:
            s = "*"
        l2.append([s]+row)
        last = row
    l2.reverse()
    print_table(l2, enum=True, reverse=True)

def diffstyle(w1, w2):
    s1 = w1.style
    s2 = w2.style
    g = globals()
    d = []
    l = []
    def pdiff(f, n):
        v1 = f(s1)
        v2 = f(s2)
        if v1 == v2:
            return
        l.append((n, v1, v2))
        d.append(n)
    for v in sorted(g.keys()):
        if not v.startswith("x"):
            continue
        f = g[v]
        if v.startswith("xs"):
            for i in range(5):
                pdiff(f(i), "%s(%s)" % (v, i))
        else:
            pdiff(f, v)
    print_table(l)
    if l:
        print "pstyle(w,%s)" % ",".join(d)

for _v in "fg", "bg", "light", "dark", "mid", "text", "base", "text_aa":
    exec ("def xs_%(fld)s(state):\n"
          "    'field accessor builder (color state), use with pstyle'\n"
          "    def %(fld)s(s):\n"
          "        return s.%(fld)s[state]\n"
          "    return %(fld)s\n"
          ) % dict(fld=_v)

for _v in "black", "white", "xthickness", "ythickness":
    exec ("def x_%(fld)s(s):\n"
          "    'field accessor, use with pstyle'\n"
          "    return s.%(fld)s\n"
          ) % dict(fld=_v)

for _v in "family", "style", "variant", "weight", "stretch", "size", "size_is_absolute":
    exec ("def x_%(fld)s(s):\n"
          "    'field accessor, use with pstyle'\n"
          "    v = s.font_desc.get_%(fld)s()\n"
          "    try:\n"
          "        return v.value_nick\n"
          "    except AttributeError:\n"
          "        return v\n"
          ) % dict(fld=_v)
    

def x_font(s):
    "field accessor (pango font name), use with pstyle"
    return s.font_desc.to_string()

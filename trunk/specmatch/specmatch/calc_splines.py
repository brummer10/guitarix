#! /usr/bin/python
# -*- coding: utf-8 -*-

from sympy import var, diff, solve, Eq, log

# Function to compute the spline formulas used in
# SmoothedIR startslope, segment and endslope (look for the
# "p = [...]" definitions.
# It not needed for running the program, just included for
# reference here (and not tested as an included function)
#
def calc_formulas():
    var("x,h,y:2,dy:2,a:d,s")
    f = a + b * x + c * x**2 + d * x**3
    df = diff(f, x)
    d2f = diff(df, x)
    segment = solve([
        Eq( f.subs(x,0),    y0  ),
        Eq( df.subs(x,0),   dy0 ),
        Eq( f.subs(x,h),    y1  ),
        Eq( df.subs(x,h),   dy1 ),
        ],
        [a,b,c,d])
    left_slope = solve([
        Eq( df.subs(x,0),   s   ),
        Eq( d2f.subs(x,0),  0   ),
        Eq( f.subs(x,h),    y1  ),
        Eq( df.subs(x,h),   dy1 ),
        ],
        [a,b,c,d])

    # change to logarithmic x-coordinate for right_slope:
    f = f.subs(x, log(x))
    df = diff(f, x)
    d2f = diff(df, x)
    right_slope = solve([
        Eq( f.subs(x,1),    y0  ),
        Eq( df.subs(x,1),   dy0 ),
        Eq( df.subs(x,h),   s   ),
        Eq( d2f.subs(x,h),  0   ),
        ],
        [a,b,c,d])

    for name in "left_slope","segment", "right_slope":
        print "%s = %s" % (name, [v[1] for v in sorted(vars()[name].items(),reverse=True)])

if __name__ == "__main__":
    calc_formulas()

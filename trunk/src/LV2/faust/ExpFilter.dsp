
import("stdfaust.lib");
import("guitarix.lib");

filter = fi.tf2(b0,b1,b2,a1,a2) with
{
    c = 1.059;
    R = 0.9221;
    lc0 = 0.00506158;
    lc1 = 0.06446806;
    lc2 = 0.27547621;
    lc3 = 0.43359433;
    lc4 = 1.31282248;
    lc5 = 0.07238887;
    fc = vslider("Freq",1200,300,3000,5) : *(2*ma.PI/ma.SR) : log;
    p = lc0*pow(fc,5) + lc1*pow(fc,4) + lc2*pow(fc,3) + lc3*pow(fc,2) + lc4*fc + lc5 : exp;
    //b0 = 1;
    //b1 = -1.01;
    //b2 = 0;
    //a1 = -1.84;
    //a2 = 0.846416;
    b0 = 1;
    b1 = -c;
    b2 = 0;
    a1 = -2*R*cos(p);
    a2 = R*R;
};

process = hgroup("1 Filter",BP(filter : *(ba.db2linear(-10))));

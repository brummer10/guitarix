declare name "Tremolo";
declare category "Modulation";
declare gladefile "tremolo_ui.glade";

/*
** Model of a vactrol tremolo unit by "transmogrify"
** c.f. http://sourceforge.net/apps/phpbb/guitarix/viewtopic.php?f=7&t=44&p=233&hilit=transmogrifox#p233
** http://transmogrifox.webs.com/vactrol.m
*/

import("stdfaust.lib");

/* vactrol model */

/* transcendental functions in fast signal path:
** cds: 2 exp() (2 alpha containing each 1 exp())
** vactrol: 1 exp(), 1 pow(), 1 log()
*/

R1 = 2700;
Ra = 1e6;
Rb = 300;
b = exp(log(Ra)/log(Rb)) - exp(1);
dTC = 0.06;
minTC = log(0.005/dTC);

cds = ((_ <: _,_),_ : _+(1-alpha)*_) ~ (_<:*(alpha)) with {
    iSR = 1/ma.SR;
    dRC = dTC * exp(*(minTC));
    alpha = 1 - iSR / (dRC + iSR);
};

vactrol = pow(_,1.9) : cds : *(b) + exp(1) : exp(log(Ra)/log) : R1/(_ + R1);

/* os.triangle oscillator (not bandlimited, frequency is approximate) */

trianglewave(freq) = _ ~ (_ <: _ + hyst) : /(periodsamps) with {
   if(c,t,e) = select2(c,e,t);
    hyst(x) = if(_ > 0, 2 * (x < periodsamps) - 1, 1 - 2 * (x > 0)) ~ _;
    periodsamps = int(ma.SR / (2*float(freq)));
};

/* tremolo unit, using os.triangle or sine oscillator as lfo */

tremolo(freq, depth) = lfo * depth + 1 - depth : vactrol with {
    sine(freq) = (os.oscs(freq) + 1) / 2 : max(0); // max(0) because of numerical inaccuracy
    SINE=checkbox("SINE[enum:os.triangle|sine|os.square]");
    lfo = select3(SINE, trianglewave(freq), sine(freq), os.lf_squarewavepos(freq));
};

wet = vslider("wet_dry[name:Dry/Wet][tooltip:percentage of processed signal in output signal]",  100, 0, 100, 1) : /(100);
dry = 1 - wet;

process =  _<:*(dry),(*(wet): *(tremolo(vslider("freq[name:Freq]",5,0.1,50,0.1),vslider("depth[name:Depth]",0.5,0,1,0.01)))):>_;

declare name "Tube Tremolo";
declare category "Modulation";

/*
** Model of a vactrol tremolo unit by "transmogrify"
** c.f. http://sourceforge.net/apps/phpbb/guitarix/viewtopic.php?f=7&t=44&p=233&hilit=transmogrifox#p233
** http://transmogrifox.webs.com/vactrol.m
*/

import("music.lib");
import("oscillator.lib");

import("guitarix.lib");
import("redeye.lib");

/* vactrol model */

R1 = 2700;
Ra = 1e6;
Rb = 300;

b = exp(log(Ra)/log(Rb)) - exp(1);
dTC = 0.06;
minTC = log(0.005/dTC);

cds = ((_ <: _,_),_ : _+(1-alpha)*_) ~ (_<:*(alpha)) with {
    iSR = 1/SR;
    dRC = dTC * exp(*(minTC));
    alpha = 1 - iSR / (dRC + iSR);
};

vactrol = pow(_,1.9) : cds : *(b) + exp(1) : exp(log(Ra)/log) : R1/(_ + R1);


/* triangle oscillator (not bandlimited, frequency is approximate) */

trianglewave(freq) = _ ~ (_ <: _ + hyst) : /(periodsamps) with {
    if(c,t,e) = select2(c,e,t);
    hyst(x) = if(_ > 0, 2 * (x < periodsamps) - 1, 1 - 2 * (x > 0)) ~ _;
    periodsamps = int(SR / (2*float(freq)));
};

/* tremolo unit, using triangle or sine oscillator as lfo */

tremolo(freq, depth) = lfo * depth + 1 - depth : vactrol with {
    sine(freq) = (oscs(freq) + 1) / 2 : max(0); // max(0) because of numerical inaccuracy
    SINE=checkbox("SINEWAVE[enum:triangle|sine]");
    lfo = select2(SINE, trianglewave(freq), sine(freq));
};


process = input12at7:*(0.1):*(tremolo(vslider("speed[style:knob]",5,0.1,14,0.1),vslider("depth[style:knob]",0.5,0,1,0.01))):output12au7;


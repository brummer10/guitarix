
import("stdfaust.lib"); 
import("guitarix.lib");

/****************************************************************
 ** unused
 */

/*
distort(x) = x : *(pregain) : (+ : flt : BP(vtu) : flt) ~ *(back) : gain with
{
    back = vslider("FB",0.95,0.6,0.99,0.001);
    mapper(v) = 1 - 19.7 * v * v;
    flt(x) = +(x - x') ~ *(mapper(vslider("FreqT", 1250, 200, 3000, 1)/ma.SR));
    vtu(x) = valve.vtu_(dist, q, g, x);
    g = vslider("Duty", 0, -1.0, 1.0, 0.01) : *(1-log(2)) : +(1);
    q = vslider("Qual", 0.5, 0, 1, 0.01)*1.75 - 1.04 : pow(_, 9);
    dist = pow(10, 4*(vslider("Dist", 0.5, 0, 1, 0.01)));
    pregain = 0.7*sqrt(1-back);
    gain = BP(*(0.4/(vtu(0.2)-vtu(-0.2))));
};
*/

/*
process = hgroup("Tube [option : detachable]", BP(
	hgroup("1 Amp",distort) :
        vgroup("2 Highpass",BP(highpass1(fch))) :
        vgroup("3 Lowpass",BP(lowpass1(fcl)))
	)) with
{
    fch = vslider("freq",130,50,200,1);
    fcl = vslider("freq",200,1400,8000,10);
};
*/

/*
process = hgroup("2 Tube",
    hgroup("1a Distortion", BP(vtu)):
    hgroup("1b Distortion", BP(vtu)):
    hgroup("1c Distortion", BP(vtu)):
    hgroup("1d Distortion", BP(vtu)):
    hgroup("2 Highpass",BP(highpass2(fch))) :
    hgroup("3 Lowpass",BP(lowpass1(fcl)))
    ) with
{
    vtu = valve.vtu(dist, q, g) : *(0.1/(valve.vtu(dist, q, g, 0.05)-valve.vtu(dist, q, g, -0.05)));
    dist = pow(10, 4*vslider("dist", 0.5, 0, 1, 0.01));
    q = vslider("qual", 0.5, 0, 1, 0.01) : -(0.9) : /(10);
    g = vslider("duty", 0, -1.0, 1.0, 0.01) : *(1-log(2)) : +(1);
    fch = vslider("freq",130,50,200,1);
    fcl = vslider("freq",200,1400,8000,10);
};
*/

// envelope meter for insertion
// the log10 function might be slow, with execution
// time depending on input
meter = _ <: (graph*1e-50,_) :> _ with {
    t = 0.05;
    g = exp(-1/(ma.SR*t));
    env = abs : *(1-g) : + ~ *(g);
    graph = env : 20*log10 :  clip(-20,20) : vbargraph("ENV",-20,20);
};

wet_dry = vslider("wet_dry[name:wet/dry]", 0, -1, 1, 0.1);

process = hgroup("test", hgroup("tremolo",wet_dry_mix(wet_dry, BP(component("tremolo.dsp")))));

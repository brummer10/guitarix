import("music.lib");
import("filter.lib");
import("effect.lib"); 
import("guitarix.lib");

/****************************************************************
 ** unused
 */

/*
distort(x) = x : *(pregain) : (+ : flt : BP(vtu) : flt) ~ *(back) : gain with
{
    back = vslider("FB",0.95,0.6,0.99,0.001);
    mapper(v) = 1 - 19.7 * v * v;
    flt(x) = +(x - x') ~ *(mapper(vslider("FreqT", 1250, 200, 3000, 1)/SR));
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


/****************************************************************
 ** Tube Preamp Emulation
 */

// envelope meter for insertion in front of tube
// the log10 function might be slow, with execution
// time depending on input
meter = _ <: (graph*1e-50,_) :> _ with {
    t = 0.05;
    g = exp(-1/(SR*t));
    env = abs : *(1-g) : + ~ *(g);
    graph = env : 20*log10 :  clip(-20,20) : vbargraph("ENV",-20,20);
};

tubestage(tb,fck,Rk) = tube : hpf with {
    lpfk = lowpass1(fck);
    Ftube = ffunction(float Ftube(int,float), "valve.h", "");
    vplus = 250.0;
    divider = 40;
    Rp = 100.0e3;
    tube = (+ : Ftube(tb)) ~ (-(vplus) : *(Rk/Rp) : lpfk) : /(divider);
    hpf = highpass1(31.0);
};

process = hgroup("test", *(vslider("Pregain",30,-10,80,0.1):db2linear) :
          hgroup("stage1", BP(stage1)) :
          hgroup("stage2", BP(stage2)) :
          hgroup("stage3", BP(stage3)) //:
         // hgroup("tone", BP(tonestack(ts.jcm2000)))
          ) with {
    stage1 = tubestage(0,86.0,2700.0) : *(gain1) with {
        gain1 = vslider("gain1", 6, -10.0, 20.0, 0.1) : db2linear;
    };
    stage2 = lowpass1(6531.0) : tubestage(1,132.0,1500.0) : *(gain2) with {
        gain2 = vslider("gain2", 6, -10.0, 20.0, 0.1) : db2linear;
    };
    stage3 = lowpass1(6531.0) : tubestage(1,194.0,820.0) : *(gain3) with {
        gain3 = vslider("gain3", 6, -10.0, 20.0, 0.1) : db2linear;
    };    
};

// generated automatically
// DO NOT MODIFY!
declare id "ruin";
declare name "Ruiner";
declare category "Fuzz";
declare shortname "Ruiner";
declare description "Devi Ever Dark Boost";
declare drywetbox "true";
declare samplerate "96000";

import("stdfaust.lib");
import("trany.lib");

ruinerp1 = pre : fi.iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0)) with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;

    
        
        Intensity = vslider("Intensity[name:Intensity]", 0.5, 0, 1, 0.01) : Inverted(1) : si.smooth(s);
            
    b0 = -3.68740376472719e-5*fs;

    b1 = 0;

    b2 = 3.68740376472719e-5*fs;

    a0 = Intensity*fs*(3.23341143501596e-10*fs + 1.83849805831657e-6) + fs*(2.50211258533327e-10*fs + 1.41841348392955e-7) + 9.19249029158284e-5;

    a1 = -6.46682287003193e-10*Intensity*pow(fs,2) - 5.00422517066654e-10*pow(fs,2) + 0.000183849805831657;

    a2 = Intensity*fs*(3.23341143501596e-10*fs - 1.83849805831657e-6) + fs*(2.50211258533327e-10*fs - 1.41841348392955e-7) + 9.19249029158284e-5;
};

ruinerp2  = pre : fi.iir((b0/a0,b1/a0,b2/a0,b3/a0),(a1/a0,a2/a0,a3/a0)) with {
    LogPot(a, x) = ba.if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = ba.if(b, 1 - x, x);
    s = 0.993;
    fs = float(ma.SR);
    pre = _;

    
        
        Level = vslider("Level[name:Level]", 0.5, 0, 1, 0.01) : Inverted(0) : si.smooth(s);
            
    b0 = -1.11891193819806e-10*Level*pow(fs,2) - 1.11891193819806e-12*pow(fs,2);

    b1 = 1.11891193819806e-10*Level*pow(fs,2) + 1.11891193819806e-12*pow(fs,2);

    b2 = 1.11891193819806e-10*Level*pow(fs,2) + 1.11891193819806e-12*pow(fs,2);

    b3 = -1.11891193819806e-10*Level*pow(fs,2) - 1.11891193819806e-12*pow(fs,2);

    a0 = Level*(Level*fs*(fs*(-8.62067474057856e-16*fs - 4.46379387426086e-13) - 5.75832602737396e-11) + fs*(fs*(8.53446799317278e-16*fs + 5.28122340957611e-13) + 7.99957173492034e-11) + 2.87916301368698e-9) + fs*(fs*(8.71550216272493e-15*fs + 5.37582514840965e-12) + 8.12279541046302e-10) + 2.88204217670067e-8;

    a1 = Level*(Level*fs*(fs*(2.58620242217357e-15*fs + 4.46379387426086e-13) - 5.75832602737396e-11) + fs*(fs*(-2.56034039795183e-15*fs - 5.28122340957611e-13) + 7.99957173492034e-11) + 8.63748904106094e-9) + fs*(fs*(-2.61465064881748e-14*fs - 5.37582514840965e-12) + 8.12279541046302e-10) + 8.646126530102e-8;

    a2 = Level*(Level*fs*(fs*(-2.58620242217357e-15*fs + 4.46379387426086e-13) + 5.75832602737396e-11) + fs*(fs*(2.56034039795183e-15*fs - 5.28122340957611e-13) - 7.99957173492034e-11) + 8.63748904106094e-9) + fs*(fs*(2.61465064881748e-14*fs - 5.37582514840965e-12) - 8.12279541046302e-10) + 8.646126530102e-8;

    a3 = Level*(Level*fs*(fs*(8.62067474057856e-16*fs - 4.46379387426086e-13) + 5.75832602737396e-11) + fs*(fs*(-8.53446799317278e-16*fs + 5.28122340957611e-13) - 7.99957173492034e-11) + 2.87916301368698e-9) + fs*(fs*(-8.71550216272493e-15*fs + 5.37582514840965e-12) - 8.12279541046302e-10) + 2.88204217670067e-8;
};

    preclip =  min(1) : max(-1); 
    //clip(x) = ((exp(x*4)-exp(-x*4*1.2))/(exp(x*4)+exp(-x*4)))/4;
    clip = ffunction(float symclip(float), "clipping.h", "");
    aclip(x) = atan(x)/ma.PI;
    //tclip = tranystageb(TB_SVEL34_68k,86.0,2700.0,25.922163) : tranystageb(TB_SVEL34_68k,86.0,2700.0,25.922163) ;
    tclip = tranystageb(TB_7199P_68k,86.0,2700.0,5.571981) : tranystageb(TB_7199P_68k,86.0,2700.0,5.571981) ;
process = ruinerp1 : clip : ruinerp2  ;

// generated automatically
// DO NOT MODIFY!
declare id "buffb";
declare name "Buffer Booster";
declare category "Tone Control";
declare shortname "Buffer Boost";
declare description "Buffer Booster";

import("filter.lib");

process = pre : iir((b0/a0,b1/a0,b2/a0,b3/a0,b4/a0),(a1/a0,a2/a0,a3/a0,a4/a0)) with {
    LogPot(a, x) = if(a, (exp(a * x) - 1) / (exp(a) - 1), x);
    Inverted(b, x) = if(b, 1 - x, x);
    s = 0.993;
    fs = float(SR);
    pre = _;

    
        Volume = vslider("Volume[name:Volume]", 0.5, 0, 1, 0.01) : Inverted(0) : LogPot(0) : smooth(s);
    
        Intensity = vslider("Intensity[name:Intensity]", 0.5, 0, 1, 0.01) : Inverted(0) : LogPot(0) : smooth(s);
    
    b0 = Intensity*(Intensity*Volume*pow(fs,3)*(-2.84995035519639e-20*fs - 6.45077038297955e-16) + Volume*pow(fs,3)*(2.97690025361778e-20*fs - 3.02300377935444e-13)) + Volume*pow(fs,2)*(6.76568239458587e-19*fs - 6.87046313489645e-12);

    b1 = Intensity*(Intensity*Volume*pow(fs,3)*(1.13998014207856e-19*fs + 1.29015407659591e-15) + Volume*pow(fs,3)*(-1.19076010144711e-19*fs + 6.04600755870888e-13)) - 1.35313647891717e-18*Volume*pow(fs,3);

    b2 = Intensity*(-1.70997021311783e-19*Intensity*Volume*pow(fs,4) + 1.78614015217067e-19*Volume*pow(fs,4)) + 1.37409262697929e-11*Volume*pow(fs,2);

    b3 = Intensity*(Intensity*Volume*pow(fs,3)*(1.13998014207856e-19*fs - 1.29015407659591e-15) + Volume*pow(fs,3)*(-1.19076010144711e-19*fs - 6.04600755870888e-13)) + 1.35313647891717e-18*Volume*pow(fs,3);

    b4 = Intensity*(Intensity*Volume*pow(fs,3)*(-2.84995035519639e-20*fs + 6.45077038297955e-16) + Volume*pow(fs,3)*(2.97690025361778e-20*fs + 3.02300377935444e-13)) + Volume*pow(fs,2)*(-6.76568239458587e-19*fs - 6.87046313489645e-12);

    a0 = Intensity*(Intensity*fs*(fs*(fs*(-2.88228949502788e-20*fs - 3.1353376203179e-14) - 9.57866164137552e-13) - 4.00199516463868e-12) + fs*(fs*(fs*(3.01067992749548e-20*fs + 3.28941142776728e-14) + 4.37053187936949e-12) + 2.10094331121784e-11)) + fs*(fs*(6.84245438067155e-19*fs + 7.47593506310745e-13) + 9.93302699856702e-11) + 4.77487116185873e-10;

    a1 = Intensity*(Intensity*fs*(pow(fs,2)*(1.15291579801115e-19*fs + 6.27067524063581e-14) - 8.00399032927735e-12) + fs*(pow(fs,2)*(-1.20427197099819e-19*fs - 6.57882285553455e-14) + 4.20188662243568e-11)) + fs*(-1.36849087613431e-18*pow(fs,2) + 1.9866053997134e-10) + 1.90994846474349e-9;

    a2 = Intensity*(Intensity*pow(fs,2)*(-1.72937369701673e-19*pow(fs,2) + 1.9157323282751e-12) + pow(fs,2)*(1.80640795649729e-19*pow(fs,2) - 8.74106375873897e-12)) - 1.49518701262149e-12*pow(fs,2) + 2.86492269711524e-9;

    a3 = Intensity*(Intensity*fs*(pow(fs,2)*(1.15291579801115e-19*fs - 6.27067524063581e-14) + 8.00399032927735e-12) + fs*(pow(fs,2)*(-1.20427197099819e-19*fs + 6.57882285553455e-14) - 4.20188662243568e-11)) + fs*(1.36849087613431e-18*pow(fs,2) - 1.9866053997134e-10) + 1.90994846474349e-9;

    a4 = Intensity*(Intensity*fs*(fs*(fs*(-2.88228949502788e-20*fs + 3.1353376203179e-14) - 9.57866164137552e-13) + 4.00199516463868e-12) + fs*(fs*(fs*(3.01067992749548e-20*fs - 3.28941142776728e-14) + 4.37053187936949e-12) - 2.10094331121784e-11)) + fs*(fs*(-6.84245438067155e-19*fs + 7.47593506310745e-13) - 9.93302699856702e-11) + 4.77487116185873e-10;
};

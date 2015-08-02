//BOSS OC-2 partial emulation.
//This file uses data from oc_2.include. 
//*.include file was generated using oc_2.py.
//Also, see schematic description in the .odg file

import("effect.lib");
import("music.lib");
import("filter.lib");

import("../../../tools/plugins/oc_2/oc_2.lib");

//Filters
f1 = _:iir((b0_f1,b1_f1,b2_f1,b3_f1),(a1_f1,a2_f1,a3_f1)):_;
f2 = _:iir((b0_f2,b1_f2,b2_f2,b3_f2),(a1_f2,a2_f2,a3_f2)):_;
f3 = _:iir((b0_f3,b1_f3,b2_f3,b3_f3),(a1_f3,a2_f3,a3_f3)):_;

//Switch implementation
switch_impl(x, state) = select2((state >= 1.7),sw_opened(x),sw_closed(x));

//Trigger integrator
fint=_:iir((b0_fint,b1_fint),(a1_fint)):_;

//Trigger prefilters
f4_11=_:iir((b0_f41_1,b1_f41_1),(a1_f41_1)):_;
f4_12=_:iir((b0_f41_2,b1_f41_2),(a1_f41_2)):_;

f4_2=_:iir((b0_f42,b1_f42,b2_f42),(a1_f42,a2_f42)):_;

f4=_<:f4_2,(f4_11:f4_12):_,_;

//Frequency divider
X = (_,_)<:(!,_,_,!);

comparator(plus,minus)=(0.005 + plus) > minus,-4,4:select2:_;
cmos = ffunction(float FF_D_4013_2 (float, float), "triggers_logic.h", "");
div1 = ffunction(float FF_D_4013_1 (float), "triggers_logic.h", "");
div2 = ffunction(float FF_JK_4027 (float), "triggers_logic.h", "");

//Rectifier
hist_plus = _<:_>0,0,_:select2:_;
hist_minus = _<:_<0,0,_:select2:_;

rectifier_plus = hist_plus:fint;
rectefier_minus = hist_minus:fint;

c0 = _<:rectifier_plus,rectefier_minus:_,_;
trigger = dcblocker:_<:f4:_,(_<:_,_):_,_,_:X,_:_,(_<:_,_),_:(rectifier_plus,_:comparator),(_,rectefier_minus:comparator);

freq_divider = _:trigger:cmos:div1<:_,_:_,div2;

//Controls
p_oc1 = hslider("OCTAVE 1", 0.5, 0, 1, 0.05);
p_oc2 = hslider("OCTAVE 2", 0.5, 0, 1, 0.05);
p_direct = hslider("DIRECT", 0.5, 0, 1, 0.05);
 
wet_part = _,_:_,f1:_,(_:freq_divider):(switch_impl),_:((f2<:_,_),_):_,(switch_impl):_,_:_,f3:_,_;
effect = _:_*(1+10/2.7):_<:_,_,_:(_*p_direct),(wet_part):_,_*p_oc1,_*p_oc2:>_;
process = effect;

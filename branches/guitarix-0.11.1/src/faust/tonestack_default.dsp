declare name "amp.tonestack";
tstack = component("tonestack.dsp");
process = component("tone.dsp").tone((tstack.l*20)-10,(tstack.m*10)-5,(tstack.t*20)-10);

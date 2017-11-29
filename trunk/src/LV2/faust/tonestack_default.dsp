declare id "default"; // in tonestack ba.selector
declare name "default";

tstack = component("tonestack.dsp");
tone_controll = component("tone.dsp").tone(((tstack.l-0.5)*20),((tstack.m-0.5)*10),((tstack.t-0.5)*20));
process = tone_controll;

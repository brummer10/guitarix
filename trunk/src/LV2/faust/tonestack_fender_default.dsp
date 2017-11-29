declare id "Fender"; // in tonestack ba.selector
declare name "Fender";

tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.fender_default;];

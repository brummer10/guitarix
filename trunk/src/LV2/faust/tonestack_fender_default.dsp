declare id "Fender"; // in tonestack selector
declare name "Fender";

tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.fender_default;];

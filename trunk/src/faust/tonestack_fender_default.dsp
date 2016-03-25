declare id "Fender"; // in tonestack selector
declare name "Fender Style";

tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.fender_default;];

declare id "Roland"; // in tonestack ba.selector
declare name "Roland";

tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.roland;], tstack[tse=tstack.ts.roland;];

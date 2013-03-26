declare id "Roland"; // in tonestack selector
declare name "Roland";

tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.roland;], tstack[tse=tstack.ts.roland;];

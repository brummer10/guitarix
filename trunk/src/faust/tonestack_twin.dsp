declare id "Twin Reverb"; // in tonestack selector
declare name "Twin Reverb Style";

tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.twin;];

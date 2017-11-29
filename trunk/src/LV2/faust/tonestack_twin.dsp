declare id "Twin Reverb"; // in tonestack ba.selector
declare name "Twin Reverb";

tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.twin;];

declare id "Twin Reverb"; // in tonestack selector
declare name "Twin Reverb";

tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.twin;],tstack[tse=tstack.ts.twin;];

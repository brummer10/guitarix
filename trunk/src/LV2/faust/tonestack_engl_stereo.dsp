declare id "Engl"; // in tonestack ba.selector
declare name "Engl";

tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.engl;], tstack[tse=tstack.ts.engl;];

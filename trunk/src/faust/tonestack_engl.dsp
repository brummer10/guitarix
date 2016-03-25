declare id "Engl"; // in tonestack selector
declare name "Engl Style";

tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.engl;];

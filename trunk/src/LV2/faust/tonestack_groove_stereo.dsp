declare id "Trio Preamp"; // in tonestack selector
declare name "Trio Preamp";

tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.groove;], tstack[tse=tstack.ts.groove;];

declare id "M-Lead"; // in tonestack ba.selector
declare name "M-Lead";

tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.mlead;], tstack[tse=tstack.ts.mlead;];

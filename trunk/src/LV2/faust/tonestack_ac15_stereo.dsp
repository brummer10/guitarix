declare id "AC-15"; // in tonestack selector
declare name "AC-15"; 
tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.ac15;],tstack[tse=tstack.ts.ac15;];

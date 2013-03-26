declare id "Bassman"; // in tonestack selector
declare name "Bassman";

tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.bassman;], tstack[tse=tstack.ts.bassman;];

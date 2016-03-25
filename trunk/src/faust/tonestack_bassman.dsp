declare id "Bassman"; // in tonestack selector
declare name "Bassman Style";

tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.bassman;];

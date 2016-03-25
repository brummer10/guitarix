declare id "Peavey"; // in tonestack selector
declare name "Peavey Style";

tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.peavey;];

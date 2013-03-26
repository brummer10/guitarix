declare id "Peavey"; // in tonestack selector
declare name "Peavey";

tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.peavey;], tstack[tse=tstack.ts.peavey;];

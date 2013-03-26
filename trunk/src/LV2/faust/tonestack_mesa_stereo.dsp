declare id "Mesa Boogie"; // in tonestack selector
declare name "Mesa Boogie";

tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.mesa;], tstack[tse=tstack.ts.mesa;];

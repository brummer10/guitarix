declare id "JCM-800"; // in tonestack selector
declare name "JCM-800 Style";

tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.jcm800;];

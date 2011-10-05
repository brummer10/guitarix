declare id "JCM-2000"; // in tonestack selector
declare name "JCM-2000";

tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.jcm2000;];

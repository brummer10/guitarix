declare id "JCM-2000"; // in tonestack ba.selector
declare name "JCM-2000 Style";

tstack = component("tonestack.dsp");
process = tstack[tse=tstack.ts.jcm2000;];

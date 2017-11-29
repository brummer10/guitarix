declare id "didest";
declare name "Digital Stereo Delay";
declare shortname "Digi Delay S";
declare category "Echo / Delay";
declare description "Digital Delay Stereo Version";

dds = component("digital_delay.dsp");

process    = dds,dds;

declare id "didest";
declare name "Digital Stereo Delay";
declare shortname "Digital Delay St";
declare category "Echo / Delay";
declare description "Digital Delay Stereo Version";


dds = component("digital_delay.dsp");

process    = dds,dds;

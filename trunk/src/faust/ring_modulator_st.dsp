declare id "ringModulatorSt";
declare name "Ring Modulator";
declare category "Modulation";
declare description "Ring Modulator Stereo Version";

rm = component("ring_modulator.dsp");

process    = rm,rm;

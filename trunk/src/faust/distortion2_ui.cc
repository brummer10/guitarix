// -----distortion2
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("drive"), _(" drive "));
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalTableBox("");
    {
	b.create_small_rackknob(PARAM("gain"), _(" Gain "));
	b.create_small_rackknobr(PARAM("drive"), _(" Drive "));
    b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_TOP);
	b.create_small_rackknob(PARAM("Hfreq"), _("HighPass (hz)"));
    b.set_next_flags(UI_NUM_SHOW_ALWAYS|UI_NUM_TOP);
	b.create_small_rackknob(PARAM("freq"), _("LowPass (hz)"));
	b.create_small_rackknob(PARAM("wet_dry"), _(" wet/dry "));
    }
    b.closeBox();
}
b.closeBox();

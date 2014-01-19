// ----- bass enhancer
b.openHorizontalhideBox("");
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalTableBox("");
    {
	b.create_small_rackknob(PARAM("Frequency"),   _("   frequency  "));
	b.create_small_rackknob(PARAM("HarmonicsdB"), _(" harmonics dB "));
    }
    b.closeBox();
}
b.closeBox();


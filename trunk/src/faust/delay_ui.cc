// -----delay
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("bpm"), _(" delay (bpm) "));
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalTableBox("");
    {
	b.create_small_rackknobr(PARAM("bpm"), _(" delay (bpm) "));
	b.create_small_rackknob(PARAM("gain"), _("  gain "));
    }
    b.closeBox();
}
b.closeBox();

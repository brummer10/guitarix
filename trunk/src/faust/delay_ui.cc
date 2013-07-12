// -----delay
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("delay"), _(" delay "));
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalTableBox("");
    {
	b.create_small_rackknobr(PARAM("delay"), _(" delay "));
	b.create_small_rackknob(PARAM("gain"), _("  gain "));
    }
    b.closeBox();
}
b.closeBox();

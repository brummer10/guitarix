// ----- ring - modulator
b.openHorizontalhideBox("");
b.create_master_slider(PARAM("freq"), "Hz");
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalTableBox("");
    {
	b.create_small_rackknob(PARAM("freq"),     _("Frequency"));
	b.create_small_rackknobr(PARAM("dry/wet"), _("   Mix   "));
    }
    b.closeBox();
}
b.closeBox();


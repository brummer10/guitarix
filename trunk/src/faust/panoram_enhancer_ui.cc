// ----- panoram enhancer
b.openHorizontalhideBox("");
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalTableBox("");
    {
	b.create_small_rackknob(PARAM("Delay width"), _("  delay width  "));
	b.create_small_rackknob(PARAM("Frequency width"), _("  freq width   "));
    }
    b.closeBox();
}
b.closeBox();

